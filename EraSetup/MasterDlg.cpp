// MasterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EraSetup.h"
#include "MasterDlg.h"

#include "FinishPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL g_fSuccessful;

/////////////////////////////////////////////////////////////////////////////
// CMasterDlg dialog
CMasterDlg::CMasterDlg(CWnd* pParent /*=NULL*/)
           :CNewWizDialog(CMasterDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CMasterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CMasterDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMasterDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMasterDlg, CNewWizDialog)
	//{{AFX_MSG_MAP(CMasterDlg)
	ON_WM_CTLCOLOR()
  ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMasterDlg message handlers
BOOL CMasterDlg::OnInitDialog() {

	SetPlaceholderID(IDC_SHEETRECT);

	CNewWizDialog::OnInitDialog();

	m_Brush.CreateSolidBrush(CLR_BK);

  HICON hIcon = theApp.LoadIcon(IDR_MAINFRAME);
  SetIcon(hIcon, TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CMasterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
/************************************** : by VK at 26.07.2005 22:45:56 **\
	HBRUSH hbr = CNewWizPage::OnCtlColor(pDC, pWnd, nCtlColor);
\************************************** : by VK at 26.07.2005 22:45:58 **/
	switch (nCtlColor) {	   
		case CTLCOLOR_STATIC:
		case CTLCOLOR_EDIT:
		case CTLCOLOR_LISTBOX:
		case CTLCOLOR_SCROLLBAR:
		case CTLCOLOR_BTN:
		case CTLCOLOR_DLG:	    
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(CLR_BK);
			return m_Brush;
	}	
	// TODO: Return a different brush if the default is not desired
	return m_Brush;
}

void CMasterDlg::OnDestroy() {
  CNewWizDialog::OnDestroy();

  if ( g_fSuccessful ) {
    CFinishPage FinishPage;
    FinishPage.DoModal();
  }
}