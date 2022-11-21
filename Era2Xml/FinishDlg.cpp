// FinishDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Era2Xml.h"
#include "FinishDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFinishDlg dialog


CFinishDlg::CFinishDlg(LPCTSTR szOutFolder, CWnd* pParent /*=NULL*/)
	         :CDialog(CFinishDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CFinishDlg)
	m_fOpenFolder = true;
	m_fCloseApp = true;
	//}}AFX_DATA_INIT
  m_szOutFolder = szOutFolder;
}


void CFinishDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFinishDlg)
	DDX_Check(pDX, IDC_OPENFOLDER, m_fOpenFolder);
	DDX_Check(pDX, IDC_CLOSEAPP, m_fCloseApp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFinishDlg, CDialog)
	//{{AFX_MSG_MAP(CFinishDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFinishDlg message handlers
BOOL CFinishDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  CString s;
  s.Format(_T("Відкрити папку \"%s\""), m_szOutFolder);
  GetDlgItem(IDC_OPENFOLDER)->SetWindowText(s);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
