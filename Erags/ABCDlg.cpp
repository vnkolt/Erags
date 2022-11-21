// ABCDlg.cpp : implementation file
//
#include "stdafx.h"
#include "Erags.h"
#include "ABCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL g_fNewSurnamesABC;
extern BOOL g_fNewPageForLetter;

/////////////////////////////////////////////////////////////////////////////
// CABCDlg dialog
CABCDlg::CABCDlg(BOOL fHideNewSurname, CWnd* pParent /*=NULL*/)
        :CDialogEx(CABCDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CABCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_fHideNewSurname = fHideNewSurname;
}

void CABCDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CABCDlg)
  DDX_Control(pDX, IDC_CHECK1, m_CheckBox1);
  DDX_Control(pDX, IDC_CHECK2, m_CheckBox2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CABCDlg, CDialogEx)
	//{{AFX_MSG_MAP(CABCDlg)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CABCDlg message handlers
BOOL CABCDlg::OnInitDialog()  {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_CheckBox1.SetCheckBoxImageList(&m_CheckBoxIL);
    m_CheckBox2.SetCheckBoxImageList(&m_CheckBoxIL);
  }
  CheckDlgButton(IDC_CHECK1, g_fNewSurnamesABC);
  CheckDlgButton(IDC_CHECK2, g_fNewPageForLetter);

  if ( m_fHideNewSurname ) {
    m_CheckBox1.ShowWindow(SW_HIDE);
  }

  if ( false==m_AfterTitle.IsEmpty() ) {
    GetDlgItem(IDC_CHECK1)->SetWindowText(m_AfterTitle);
  }
  	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CABCDlg::OnCheck1() {
	// TODO: Add your control notification handler code here
	g_fNewSurnamesABC = IsDlgButtonChecked(IDC_CHECK1);
}

void CABCDlg::OnCheck2()  {
	// TODO: Add your control notification handler code here
	g_fNewPageForLetter = IsDlgButtonChecked(IDC_CHECK2);
}

BOOL CABCDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintDocs"), _T("#PrintLists"));
  return true;
}
