
// Updater.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Updater.h"
#include "UpdaterDlg.h"

#include <Psapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL FileExists(PCSTR pszFilename, WIN32_FIND_DATA* pFindData/*=NULL*/) {
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = FindFirstFile(pszFilename, &FindFileData);

  if (INVALID_HANDLE_VALUE==hFind)
    return false;
  FindClose(hFind);
  if ( pFindData )
    memcpy(pFindData, &FindFileData, sizeof(WIN32_FIND_DATA));
  return true;
}

CString GetFilePath(LPCTSTR szFileName) {
  CString sPath(szFileName);
  return sPath.Mid( 0, sPath.ReverseFind('\\') );
}
void RemoveQuotes(CString& s) {
  if ( s.Find(_T("\"")) >= 0 ) {
    s.Replace(_T("\""), _T(""));
  }
}

BOOL IsActiveProcess(LPCTSTR szProcess) {
  DWORD aProcesses[1024], cbNeeded, cProcesses;
  unsigned int i;

  memset(aProcesses, 0, sizeof(aProcesses));

  if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    return false;

  // Calculate how many process identifiers were returned.
  cProcesses = cbNeeded / sizeof(DWORD);

  for ( i = 0; i < cProcesses; i++ ) {
    if( aProcesses[i] != 0 ) {

      HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
      if ( hProcess ) {
        TCHAR szProcessName[MAX_PATH];
        HMODULE hMod;
        DWORD cbNeeded;
        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),  &cbNeeded) ) {
          if ( GetModuleBaseName( hProcess, hMod, szProcessName,  sizeof(szProcessName)/sizeof(TCHAR)) ) {
            if ( _stricmp(szProcessName, szProcess)==0 ) {
              return true;
            }
          }
        }
        CloseHandle( hProcess );
      }
    }
  }
  return false;
}

BOOL CloseProcess(LPCTSTR szProcess, LPCTSTR szWindowPrefix) {
  int nLen = strlen(szWindowPrefix);
  HWND hWnd = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
  while ( hWnd ) {
    CString szTitle;
    CWnd* pWnd = CWnd::FromHandle(hWnd);
    pWnd->GetWindowText(szTitle);
    if ( szTitle.Find(szWindowPrefix) ==0 ||
        (szTitle.GetLength() > nLen && szTitle.Right(nLen)==szWindowPrefix ) ) {
      //::SendMessage(hWnd, WM_QUIT, 0, 0);
      ::SendMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
      return true;
    }
    hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
  }
  return true;
}

// CUpdaterApp

BEGIN_MESSAGE_MAP(CUpdaterApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CUpdaterApp construction

CUpdaterApp::CUpdaterApp() {
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CUpdaterApp object

CUpdaterApp theApp;


// CUpdaterApp initialization

BOOL CUpdaterApp::InitInstance() {
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

  if ( __argc > 1 ) {
    m_szEraPath = __argv[1];
  }
  else {
    m_szEraPath = GetFilePath(__argv[0]);
  }

  m_szDownloadsPath.Format(_T("%s\\Downloads"), m_szEraPath);
  m_szNewFileInfo.Format(_T("%s\\FileInfo.txt"), m_szDownloadsPath);
  RemoveQuotes(m_szEraPath);
  RemoveQuotes(m_szDownloadsPath);
  RemoveQuotes(m_szNewFileInfo);

  if ( false==FileExists(m_szEraPath, NULL) ) {
    return false;
  }
  if ( false==FileExists(m_szDownloadsPath, NULL) ) {
    return false;
  }
  if ( false==FileExists(m_szNewFileInfo, NULL) ) {
    return false;
  }

_try_again:
  CloseProcess(_T("Erags.exe"), _T("Erags"));
  CloseProcess(_T("EraABC.exe"), _T("EraABC"));
  if ( IsActiveProcess(_T("Erags.exe")) ) {
    if ( IDRETRY==AfxMessageBox(_T("Будь ласка, закрийте програму Erags і натисніть \"Повтор\"."), MB_RETRYCANCEL) ) {
      goto _try_again;
    }
    return false;
  }
  if ( IsActiveProcess(_T("EraABC.exe")) ) {
    if ( IDRETRY==AfxMessageBox(_T("Будь ласка, закрийте програму EraABC і натисніть \"Повтор\"."), MB_RETRYCANCEL) ) {
      goto _try_again;
    }
    return false;
  }

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Vladimir Koltsov"));
  try {
    AfxDaoInit();
  }
  catch(CDaoException* e) {
    e->Delete();
  }


	CUpdaterDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
