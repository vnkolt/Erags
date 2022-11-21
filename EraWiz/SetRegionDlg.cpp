// SetRegionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EraWiz.h"
#include "SetRegionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetRegionDlg dialog


CSetRegionDlg::CSetRegionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetRegionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetRegionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetRegionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetRegionDlg)
	DDX_Control(pDX, IDC_REGLIST, m_Regions);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetRegionDlg, CDialog)
	//{{AFX_MSG_MAP(CSetRegionDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetRegionDlg message handlers
