// LoadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EraWiz.h"
#include "LoadDlg.h"

#include "SetRagsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadDlg dialog
CLoadDlg::CLoadDlg(CWnd* pParent /*=NULL*/)
         :CDialog(CLoadDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CLoadDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CLoadDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoadDlg)
	DDX_Control(pDX, IDC_WHAT, m_Description);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLoadDlg, CDialog)
	//{{AFX_MSG_MAP(CLoadDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CLoadDlg::LoadRegistrars() {
  SetWindowText("Завантажуеться список органів реєстрації. Зачекайте, будь ласка.");
  m_Progress.SetRange(0, 1000);
  theRList.Load(&m_Progress, &m_Description);
}
/////////////////////////////////////////////////////////////////////////////
// CLoadDlg message handlers
BOOL CLoadDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	CWaitCursor wc;
	// TODO: Add extra initialization here
  CenterWindow();
  ShowWindow(SW_SHOW);
  LoadRegistrars();
  m_Description.ShowWindow(SW_SHOW);
  EndDialog(IDOK);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
