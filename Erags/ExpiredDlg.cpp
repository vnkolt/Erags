// ExpiredDlg.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "ExpiredDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExpiredDlg dialog


CExpiredDlg::CExpiredDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExpiredDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExpiredDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CExpiredDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpiredDlg)
	DDX_Control(pDX, IDC_EMAIL, m_Email);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExpiredDlg, CDialog)
	//{{AFX_MSG_MAP(CExpiredDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpiredDlg message handlers

BOOL CExpiredDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_Font.CreateFont(-12, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

  GetDlgItem(IDC_TITLE)->SetFont(&m_Font);
  GetDlgItem(IDC_PHONES)->SetFont(&m_Font);
  GetDlgItem(IDC_EMAIL)->SetFont(&m_Font);
  m_Email.SetLink(TRUE, FALSE)
         .SetTextColor(RGB(0,0,255))
		     .SetFontUnderline(TRUE)
		     .SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND_CURSOR));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
