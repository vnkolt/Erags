// FinishPage.cpp : implementation file
//

#include "stdafx.h"
#include "EraSetup.h"
#include "FinishPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFinishPage dialog


CFinishPage::CFinishPage(CWnd* pParent /*=NULL*/)
	: CDialog(CFinishPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFinishPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFinishPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFinishPage)
	DDX_Control(pDX, IDC_FINMSG, m_RichText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFinishPage, CDialog)
	//{{AFX_MSG_MAP(CFinishPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFinishPage message handlers

BOOL CFinishPage::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  GetDlgItem(IDC_TITLE)->SetFont(&theApp.m_Font);

  HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(IDR_FINISH), _T("RTF"));
  if ( hResource ) {
  	HGLOBAL hResData = LoadResource(NULL, hResource);
    if ( hResData ) {
      CString sRTF((char*)hResData);
      m_RichText.SetRTF(sRTF);
      m_RichText.SetSel(0,0);
      m_RichText.PostMessage(EM_SETSEL, 0, 0);
    }
  	FreeResource(hResData);
  }

  if ( IDC_RADIO_UKR==theApp.m_HelpLang )
    CheckDlgButton(IDC_OPEN_UKR, 1);
  else
    CheckDlgButton(IDC_OPEN_RUS, 1);

	CheckDlgButton(IDC_OPEN_ERAGS, 1);

  if ( theApp.m_fServer ) {
    GetDlgItem(IDC_OPEN_ERAGS)->EnableWindow(false);
  }

/*
  if ( theApp.m_fServer ) {
    GetDlgItem(IDC_OPEN_ERAGS)->EnableWindow(false);
  }
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void RunErags(LPCTSTR szCmdLine) {
  PROCESS_INFORMATION pi;
  STARTUPINFO         si;

  si.cb              = sizeof(STARTUPINFO);
  si.lpReserved      = NULL;
  si.lpReserved2     = NULL;
  si.cbReserved2     = 0;
  si.lpDesktop       = NULL;
  si.lpTitle         = NULL;
  si.dwFlags         = 0;
  si.dwX             = 0;
  si.dwY             = 0;
  si.dwFillAttribute = 0;
  si.wShowWindow     = SW_SHOW;

  CreateProcess(NULL, (LPTSTR)(LPCTSTR)szCmdLine, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
}

void CFinishPage::OnOK() {
	// TODO: Add extra validation here
  CString szShell;

  if ( theApp.m_fServer || IsDlgButtonChecked(IDC_OPEN_ERAGS) ) {
    LPCTSTR szParameters = NULL;
    szShell.Format(_T("\"%s\\Erags.exe\" -Setup"), theApp.m_sEraPath);
    RunErags(szShell);
  }

  if ( IsDlgButtonChecked(IDC_OPEN_UKR) ) {
    szShell.Format(_T("%s\\Help\\Erags_u.chm"), theApp.m_sEraPath);
    ShellExecute(NULL, "open", szShell, NULL, NULL, SW_SHOW);
  }
  else if ( IsDlgButtonChecked(IDC_OPEN_RUS) ) {
    szShell.Format(_T("%s\\Help\\Erags_r.chm"), theApp.m_sEraPath);
    ShellExecute(NULL, "open", szShell, NULL, NULL, SW_SHOW);
  }
	
	CDialog::OnOK();
}
