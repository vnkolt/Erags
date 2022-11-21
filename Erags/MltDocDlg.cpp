// MltDocDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "MltDocDlg.h"

#include "Defaults.h"
#include "RSDeathes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMltDocDlg dialog
CMltDocDlg::CMltDocDlg(CRSDeathes* pSet, CWnd* pParent /*=NULL*/)
	         :CDialogEx(CMltDocDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CMltDocDlg)
	//}}AFX_DATA_INIT
  m_pSet = pSet;
  m_odt = COleDateTime::GetCurrentTime();
}

void CMltDocDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMltDocDlg)
  DDX_Control(pDX, IDC_NODATA, m_chkNoData);
	DDX_Control(pDX, IDC_SERIA, m_Seria);
	DDX_Control(pDX, IDC_NUMBER, m_Number);
	DDX_Control(pDX, IDC_DATE, m_Date);
	DDX_Control(pDX, IDC_MILOFFICE, m_By);
	DDX_Control(pDX, IDC_EXTNOTICE, m_ExtNotice);
	//}}AFX_DATA_MAP
  DDX_OleDate(pDX, IDC_DATE, m_Date, m_odt);
}

void CMltDocDlg::EnableControls() {
  BOOL fEnable = IsDlgButtonChecked(IDC_NODATA) ? TRUE : FALSE;
  CWnd* pWnd = GetWindow(GW_CHILD);
  while( pWnd ) {
    if ( pWnd->IsKindOf(RUNTIME_CLASS(CEdit)) || pWnd->IsKindOf(RUNTIME_CLASS(CComboBox)) ) {
      pWnd->EnableWindow(fEnable);
    }
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
}

BEGIN_MESSAGE_MAP(CMltDocDlg, CDialogEx)
	//{{AFX_MSG_MAP(CMltDocDlg)
	ON_BN_CLICKED(IDC_NODATA, OnNodata)
	ON_EN_CHANGE(IDC_SERIA, OnSetAll)
	ON_EN_CHANGE(IDC_NUMBER, OnSetAll)
	ON_EN_CHANGE(IDC_DATE, OnSetAll)
	ON_EN_CHANGE(IDC_MILOFFICE, OnSetAll)
	ON_EN_SETFOCUS(IDC_MILOFFICE, OnSetfocusMiloffice)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMltDocDlg message handlers
BOOL CMltDocDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO: Add extra initialization here
  CString sSeria  = m_pSet->GetMilitaryCardSeria();
  CString sNumber = m_pSet->GetMilitaryCardNumber();

  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_chkNoData.SetCheckBoxImageList(&m_CheckBoxIL);
  }

  CheckDlgButton(IDC_NODATA, !(sSeria.IsEmpty() && sNumber.IsEmpty()) );
  EnableControls();

  m_Seria.SetWindowText(m_pSet->GetMilitaryCardSeria());
  m_Number.SetWindowText(m_pSet->GetMilitaryCardNumber());
  m_Date.SetWindowText(m_pSet->GetMilitaryCardDate());
  m_By.SetWindowText(m_pSet->GetMilitaryCardBy());

  m_ExtNotice.SetWindowText( m_pSet->m_EXTNOTES );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMltDocDlg::OnNodata() {
  EnableControls();	
}

void CMltDocDlg::OnSetAll() {
  CString sMemo;
  sMemo = m_pSet->SetMilitaryCard( m_ExtNotice.GetText(), m_Seria.GetText(), m_Number.GetText(), m_Date.GetDate(), m_By.GetText() );
  m_ExtNotice.SetWindowText( sMemo );
}

void CMltDocDlg::OnSetfocusMiloffice() {
	// TODO: Add your control notification handler code here
  CString s;
  m_By.GetWindowText(s);
  if ( s.IsEmpty() ) {
    if ( FALSE==m_Seria.GetText().IsEmpty() && FALSE==m_Number.GetText().IsEmpty() )
      m_By.SetWindowText( theIniCache.GetByMil() );
  }
}

void CMltDocDlg::OnYes() {
	UpdateData(TRUE);
  m_pSet->m_EXTNOTES = Trim(m_ExtNotice.GetText());
  EndDialog(IDYES);
}
BOOL CMltDocDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("RegDeath2"));
  return true;
}

