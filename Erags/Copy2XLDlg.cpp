// Copy2XLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "Copy2XLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL  g_fAllToOne = true;

/////////////////////////////////////////////////////////////////////////////
// CCopy2XLDlg dialog
CCopy2XLDlg::CCopy2XLDlg(CWnd* pParent /*=NULL*/):CDialogEx(CCopy2XLDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CCopy2XLDlg)
	//}}AFX_DATA_INIT
}

void CCopy2XLDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopy2XLDlg)
  DDX_Control(pDX, IDC_EACH_TO_EACH, m_rbEachToEach);
  DDX_Control(pDX, IDC_ALL_TO_ONE,   m_rbAllToOne);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCopy2XLDlg, CDialogEx)
	//{{AFX_MSG_MAP(CCopy2XLDlg)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopy2XLDlg message handlers
BOOL CCopy2XLDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_rbEachToEach.SetRadioImageList(&m_RadioIL);  m_rbEachToEach.SetRadio(IDC_EACH_TO_EACH, IDC_ALL_TO_ONE);
    m_rbAllToOne  .SetRadioImageList(&m_RadioIL);  m_rbAllToOne  .SetRadio(IDC_EACH_TO_EACH, IDC_ALL_TO_ONE);
  }

  CheckRadioButton(IDC_EACH_TO_EACH, IDC_ALL_TO_ONE, g_fAllToOne ? IDC_ALL_TO_ONE : IDC_EACH_TO_EACH);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCopy2XLDlg::OnYes() {
	// TODO: Add your control notification handler code here
  UpdateData(TRUE);
  g_fAllToOne = IsDlgButtonChecked(IDC_ALL_TO_ONE);
	CDialogEx::OnYes();
}
