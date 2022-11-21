// EmptyTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "EmptyTableDlg.h"
#include "DataManager.h"
#include "Menu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL dm_fNewBirth;
extern BOOL dm_fNewMarrige;
extern BOOL dm_fNewDivorce;
extern BOOL dm_fNewChange;
extern BOOL dm_fNewDeath;

/////////////////////////////////////////////////////////////////////////////
// CEmptyTableDlg dialog
CEmptyTableDlg::CEmptyTableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEmptyTableDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmptyTableDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_nPrinPos = CONTEXT_UNKNWOWN;
  m_FormID = ID_UNKNOWN;
}


void CEmptyTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmptyTableDlg)
	DDX_Control(pDX, IDC_INFO, m_Info);
  DDX_Control(pDX, IDC_RADIO1, m_Radio1);
  DDX_Control(pDX, IDC_RADIO2, m_Radio2);
  DDX_Control(pDX, IDC_RADIO3, m_Radio3);
  DDX_Control(pDX, IDC_RADIO4, m_Radio4);
  DDX_Control(pDX, IDC_RADIO5, m_Radio5);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEmptyTableDlg, CDialogEx)
	//{{AFX_MSG_MAP(CEmptyTableDlg)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CEmptyTableDlg message handlers
BOOL CEmptyTableDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_Radio1.SetRadioImageList(&m_RadioIL); m_Radio1.SetRadio(IDC_RADIO1, IDC_RADIO5);
    m_Radio2.SetRadioImageList(&m_RadioIL); m_Radio2.SetRadio(IDC_RADIO1, IDC_RADIO5);
    m_Radio3.SetRadioImageList(&m_RadioIL); m_Radio3.SetRadio(IDC_RADIO1, IDC_RADIO5);
    m_Radio4.SetRadioImageList(&m_RadioIL); m_Radio4.SetRadio(IDC_RADIO1, IDC_RADIO5);
    m_Radio5.SetRadioImageList(&m_RadioIL); m_Radio5.SetRadio(IDC_RADIO1, IDC_RADIO5);
  }

  CString szFormName;
  int BtnID = 0;
  switch(m_nPrinPos) {
    case CONTEXT_BIRTH       : 
      szFormName = _T("ÍÀÐÎÄÆÅÍÍß");
      BtnID = IDC_RADIO1;
      break;
    case CONTEXT_MARRIAGE    :
      szFormName = _T("ØËÞÁ");
      BtnID = IDC_RADIO2;
      break;
    case CONTEXT_DIVORCE     :
      szFormName = _T("ÐÎÇ²ÐÂÀÍÍß ØËÞÁÓ");
      BtnID = IDC_RADIO3;
      break;
    case CONTEXT_CHANGE      :
      szFormName = _T("ÇÌ²ÍÓ");
      BtnID = IDC_RADIO4;
      break;
    case CONTEXT_DEATH       :
      szFormName = _T("ÑÌÅÐÒÜ");
      BtnID = IDC_RADIO5;
      break;
  }

  CString s;
  s.Format(_T("Â³äêðèòà áàçà äàíèõ ÅÐÀÃÑ \"%s\", çàïèñè ïðî %s â³äñóòí³. Îáåð³òü, áóäü ëàñêà, ùî ïîòð³áíî çðîáèòè."),
           theDataManager.m_dbYear.GetName(), szFormName);
  GetDlgItem(IDC_INFO)->SetWindowText(s);
  s.Format(_T("Ñòâîðèòè íîâèé çàïèñ ïðî %s."), szFormName);
  GetDlgItem(BtnID)->SetWindowText(s);
  CheckRadioButton(IDC_RADIO1, IDC_RADIO5, BtnID);
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmptyTableDlg::OnYes() {
	// TODO: Add your control notification handler code here
  switch( GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO9) ) {
    case IDC_RADIO1:  m_FormID = ID_BIRTH;     dm_fNewBirth   = TRUE; break;
    case IDC_RADIO2:  m_FormID = ID_MARRIAGE;  dm_fNewMarrige = TRUE; break;
    case IDC_RADIO3:  m_FormID = ID_DIVORCE;   dm_fNewDivorce = TRUE; break;
    case IDC_RADIO4:  m_FormID = ID_CHANGE;    dm_fNewChange  = TRUE; break;
    case IDC_RADIO5:  m_FormID = ID_DEATH;     dm_fNewDeath   = TRUE; break;
    default:          m_FormID = ID_UNKNOWN;   break;
  }
	EndDialog(IDYES);
}
