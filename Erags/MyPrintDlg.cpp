// MyPrintDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "MyPrintDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COLLATE_ICON_ID  1086
#define NCOPIES_ID       1154

/////////////////////////////////////////////////////////////////////////////
// CMyPrintDlg

IMPLEMENT_DYNAMIC(CMyPrintDlg, CPrintDialog)

CMyPrintDlg::CMyPrintDlg(BOOL bPrintSetupOnly, DWORD dwFlags, CWnd* pParentWnd)
            :CPrintDialog(bPrintSetupOnly, dwFlags, pParentWnd) {


//  m_pd.Flags |= PD_ENABLEPRINTHOOK | PD_ENABLESETUPHOOK;
  // _AfxCommDlgProc is exported from static MFC libraries
//  m_pd.lpfnPrintHook = _AfxCommDlgProc;
//  m_pd.lpfnSetupHook = _AfxCommDlgProc;
}


BEGIN_MESSAGE_MAP(CMyPrintDlg, CPrintDialog)
	//{{AFX_MSG_MAP(CMyPrintDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CMyPrintDlg::OnInitDialog() {
	CPrintDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  CWnd* pCollateIcon = GetDlgItem(COLLATE_ICON_ID);
  if ( pCollateIcon ) {
    //CRect rect;
    //pCollateIcon->GetWindowRect(&rect);
    //ScreenToClient(&rect);
    //rect.right = rect.left + 102;
    //rect.bottom = rect.top + 64;
    pCollateIcon->SetWindowPos(NULL, 0, 0, 102, 64, SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);
  }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyPrintDlg::OnOK() {
//  CString s;
  CPrintDialog::OnOK();
//  GetDlgItem(NCOPIES_ID)->GetWindowText(s);
//  m_pd.nCopies = atoi(s);
}