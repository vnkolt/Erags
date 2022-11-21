// ZipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "ZipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZipDlg dialog


CZipDlg::CZipDlg(CWnd* pParent /*=NULL*/)
      	:CDialog(CZipDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CZipDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CZipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZipDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZipDlg, CDialog)
	//{{AFX_MSG_MAP(CZipDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZipDlg message handlers
