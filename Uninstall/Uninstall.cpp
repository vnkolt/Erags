// Uninstall.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Uninstall.h"
#include "UninstallDlg.h"

#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString g_szERAPath;


BOOL IsERAGSInstalled() {
  BOOL fRet = false;
  HKEY hKey;
  if(::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Vladimir Koltsov\\Erags\\Settings", 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
    DWORD lSize = MAX_PATH;
    DWORD dwType = REG_SZ;
    if ( ::RegQueryValueEx(hKey, "InstallLocation", NULL, &dwType, (LPBYTE)g_szERAPath.GetBuffer(MAX_PATH), &lSize) != ERROR_SUCCESS ) {
      DWORD dwError = GetLastError();
    }
    g_szERAPath.ReleaseBuffer();
    CString s;
    s.Format(_T("%s\\Erags.exe"), g_szERAPath);
    if ( FileExists(s, NULL ) ) {
      fRet = true;
    }
    else {
      fRet = false;
      g_szERAPath.Empty();
    }
    ::RegCloseKey(hKey);
  }
  if ( false==fRet ) {
    DWORD dwDriveMask = GetLogicalDrives();
    DWORD dwDrive = 1;
    for( int i(0); i < 32; i++ ) {
      CString szPath;
      if ( dwDrive & dwDriveMask ) {
        szPath.Format(_T("%c:\\"), 'A' + i);
        if ( DRIVE_FIXED==GetDriveType(szPath) ) {
          szPath.Format(_T("%c:\\Erags\\Erags.exe"), 'A' + i);
          if ( FileExists(szPath, NULL ) ) {
            g_szERAPath = szPath;
            fRet = true;
            break;
          }
        }
      }
      dwDrive <<= 1;
    }
  }
  return fRet;
}


/////////////////////////////////////////////////////////////////////////////
// CUninstallApp

BEGIN_MESSAGE_MAP(CUninstallApp, CWinApp)
	//{{AFX_MSG_MAP(CUninstallApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUninstallApp construction

CUninstallApp::CUninstallApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUninstallApp object

CUninstallApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUninstallApp initialization

BOOL CUninstallApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

  if ( false==IsERAGSInstalled() ) {
    return false;
  }

  if(!AfxOleInit()) { // Your addition starts here
    AfxMessageBox("Could not initialize COM dll");
    return FALSE;
  }                   // End of your addition


	CUninstallDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
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

int CUninstallApp::ExitInstance() {
	// TODO: Add your specialized code here and/or call the base class
  // ::CoUninitialize();	
	return CWinApp::ExitInstance();
}
