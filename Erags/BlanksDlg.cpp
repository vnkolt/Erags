// BlanksDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "BlanksDlg.h"
#include "DataManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern SHORT        g_iMonth;
extern BOOL         g_fPeriod;
extern COleDateTime g_odtFrom;
extern COleDateTime g_odtTill;

DWORD  g_dwPrintBlanks  = 0;

/////////////////////////////////////////////////////////////////////////////
// CBlanksDlg dialog
CBlanksDlg::CBlanksDlg(const COleDateTime& odt, CWnd* pParent /*=NULL*/)
	         :CDialogEx(CBlanksDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CBlanksDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

  if ( COleDateTime::valid==odt.GetStatus() )
    m_odt = odt;
  else
    m_odt = COleDateTime::GetCurrentTime();

  m_bCheckPeriod = false;
}

void CBlanksDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlanksDlg)
	DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_MONLIST, m_MonList);
	DDX_Control(pDX, IDC_PERIOD, m_chkPeriod);
	DDX_Control(pDX, IDC_TILL, m_Till);
	DDX_Control(pDX, IDC_FROM, m_From);
  DDX_Control(pDX, IDC_CHECK_BIRTH, m_chkBirth);
  DDX_Control(pDX, IDC_CHECK_MARRIAGE, m_chkMarriage);
  DDX_Control(pDX, IDC_CHECK_DEATH, m_chkDeath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBlanksDlg, CDialogEx)
	//{{AFX_MSG_MAP(CBlanksDlg)
  ON_LBN_SELCHANGE(IDC_MONLIST, OnSelchangeMonlist)
	ON_BN_CLICKED(IDC_PERIOD, OnPeriod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlanksDlg message handlers
BOOL CBlanksDlg::OnInitDialog() {
  CDialogEx::OnInitDialog();
  // Создаём иммидж-лист для чек-боксов
  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_chkPeriod  .SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkBirth   .SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkMarriage.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkDeath   .SetCheckBoxImageList(&m_CheckBoxIL);
  }
  CString s;
  for (int i(0); i < 12; i++) {
    s.LoadString(i+IDS_UM01);
    m_MonList.AddString(s);
  }

  m_chkBirth   .SetCheck(true);
  m_chkMarriage.SetCheck(true);
  m_chkDeath   .SetCheck(true);

  COleDateTime dt;
  dt = COleDateTime::GetCurrentTime();
  g_iMonth = (SHORT)dt.GetMonth();
  if(dt.GetDay()<28 && g_iMonth>1)
    g_iMonth--;
  m_MonList.SetCurSel(g_iMonth-1);

  OnSelchangeMonlist();

  if ( m_bCheckPeriod )
    m_chkPeriod.SetCheck(1);
  else
    m_chkPeriod.SetCheck(0);
  OnPeriod();

  return true;
}
void CBlanksDlg::OnSelchangeMonlist() {
	// TODO: Add your control notification handler code here
  g_iMonth = (SHORT)(m_MonList.GetCurSel() + 1);

  COleDateTime odt = m_From.GetDate();
  if ( COleDateTime::valid!=odt.GetStatus() ) {
    odt = COleDateTime::GetCurrentTime();
  }
  int y = theDataManager.m_Year;
  if ( -1== y ) {
    y = odt.GetYear();
  }
  m_From.SetDate(COleDateTime(y, g_iMonth, 1, 0, 0, 0));

  odt = m_From.GetDate();

  odt += COleDateTimeSpan(1, 0, 0, 0); // 2nd
  while ( odt.GetDay() != 1 ) { // 1st
    odt += COleDateTimeSpan(1, 0, 0, 0);
  }
  odt -= COleDateTimeSpan(1, 0, 0, 0); // last day od the month
  m_Till.SetDate(odt);
}
void CBlanksDlg::OnPeriod() {
	// TODO: Add your control notification handler code here
  BOOL bEnable = m_chkPeriod.GetCheck() ? true : false;
  m_Till.EnableWindow(bEnable);
  m_From.EnableWindow(bEnable);
}

void CBlanksDlg::OnYes() {
  if ( UpdateData(TRUE) ) {
    g_fPeriod = m_chkPeriod.GetCheck() ? TRUE : FALSE;
    g_odtFrom = m_From.GetDate();
    g_odtTill = m_Till.GetDate();

    g_dwPrintBlanks = 0;
    if ( m_chkBirth.GetCheck() ) {
      g_dwPrintBlanks |= RF_BIRTH;
    }
    if ( m_chkMarriage.GetCheck() ) {
      g_dwPrintBlanks |= RF_MARRIAGE;
    }
    if ( m_chkDeath.GetCheck() ) {
      g_dwPrintBlanks |= RF_DEATH;
    }
    EndDialog(IDYES);
  }
}
