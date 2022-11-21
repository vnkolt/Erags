// EraSetup.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "EraSetup.h"
#include "MasterDlg.h"

#include "WelcomePage.h"
#include "AgreementPage.h"
#include "EraPathPage.h"
#include "ProgressPage.h"
#include "FinishPage.h"

#include "CDMenu.h"

#include "UnzipDlg.h"

#include <Tlhelp32.h>
#include <direct.h>
#include <comdef.h>

#include "..\Controls\ShellType.h"
#include "..\Common\DAO36.h"
#include "..\Common\IsAdmin.h"
#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HINSTANCE g_hHHCTRLInstance = NULL;

/*
CString GetFilePath(LPCTSTR szFileName) {
  CString sPath(szFileName);
  return sPath.Mid( 0, sPath.ReverseFind('\\') );
}

CString GetModulePath() {
  TCHAR acBuf[MAX_PATH];
  CString sRet;
  GetModuleFileName(NULL, acBuf, MAX_PATH);
  return GetFilePath(acBuf);
}
*/
void DeleteFileTree(const CString& szFolder) {
  CString sMask = szFolder + _T("\\*.*");  
  WIN32_FIND_DATA findData;
  HANDLE hFindFile;
  if((hFindFile = FindFirstFile(sMask, &findData)) != INVALID_HANDLE_VALUE){
    BOOL bFind = true;
    while(bFind) {
      if(findData.cFileName[0] != '.') {
        CString szFileName;
        szFileName.Format(_T("%s\\%s"), szFolder, findData.cFileName);
        if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { // Folder?
          DeleteFileTree(szFileName);
        }
        else {
          DeleteFileIfExist(szFileName);
        }
      }
      bFind = FindNextFile(hFindFile, &findData);
    }
    FindClose(hFindFile);
  }
  _rmdir(szFolder);
}

/////////////////////////////////////////////////////////////////////////////
// CEraSetupApp

BEGIN_MESSAGE_MAP(CEraSetupApp, CWinApp)
	//{{AFX_MSG_MAP(CEraSetupApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraSetupApp construction
CEraSetupApp::CEraSetupApp() {
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
  m_fServer = true;
  // m_fInstallLaws = false;
  m_sEraPath = _T("C:\\Erags");
  m_sEraGroup = _T("ПК ЕРАГС");
  m_HelpLang = IDC_RADIO_UKR;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEraSetupApp object

CEraSetupApp theApp;

BOOL WaitForProcess(LPCTSTR szProcess) {

  while ( TRUE) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if ( hSnapshot==(HANDLE)-1 )
      return FALSE;

    PROCESSENTRY32 ProcessEntry;

    BOOL fProcess = Process32First(hSnapshot, &ProcessEntry);
    BOOL fPresent = FALSE;
    while ( fProcess ) {
      if ( stricmp(ProcessEntry.szExeFile, szProcess)==0 ) {
        fPresent = TRUE;
        break;
      }
      fProcess = Process32Next(hSnapshot, &ProcessEntry);
    }
    CloseHandle(hSnapshot);
    if ( FALSE==fPresent )
      break;
    Sleep(100);
  }
  return TRUE;
}

/*
BOOL InstallDAO() {
  CString szDAOPath, szErr;
  szDAOPath.Format(_T("%s\\DAO\\SETUP.EXE"), GetModulePath());
  if ( FALSE==FileExists(szDAOPath) ) {
    CString szErr;
    szErr.Format(_T("Не існує програми установки DAO \"%s\".\n")
                 _T("На оригінальному компакт-диску ПК ЕРАГС установка DAO присутня.\n")
                 _T("Використувуйте оригінальний компакт-диск ПК ЕРАГС."),
                 szDAOPath
                 );

    ::MessageBox(NULL, szErr, _T("Помилка під час установки DAO"), MB_ICONSTOP|MB_OK);
    return FALSE;
  }
  PROCESS_INFORMATION pi;
  STARTUPINFO         si;
  DWORD               exitCode;


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

  if (!CreateProcess(NULL,
                     (LPTSTR)(LPCTSTR)szDAOPath,
                     NULL,
                     NULL,
                     TRUE,
                     NORMAL_PRIORITY_CLASS,
                     NULL,
                     NULL,
                     &si,
                     &pi)) {

    szErr.Format(_T("Не вдається виконати програму \"%s\"."), szDAOPath);
    ::MessageBox(NULL, szErr, _T("Помилка під час установки DAO"), MB_ICONSTOP|MB_OK);
    return FALSE;
  }

  // Give the process time to execute and finish
  DWORD dwWaitRes = WaitForSingleObject(pi.hProcess, INFINITE);
  exitCode = CloseHandle(pi.hProcess);
  WaitForProcess(_T("_INS0432._MP") );

  return TRUE;
}
*/

CString GetSpecialFolder(int nFolderID) {
   // Allocate a pointer to an Item ID list
   LPITEMIDLIST pidl;

   // Get a pointer to an item ID list that
   // represents the path of a special folder
   HRESULT hr = SHGetSpecialFolderLocation(NULL, nFolderID, &pidl);

   // Convert the item ID list's binary
   // representation into a file system path
   char szPath[_MAX_PATH];
   BOOL f = SHGetPathFromIDList(pidl, szPath);

   // Allocate a pointer to an IMalloc interface
   LPMALLOC pMalloc;

   // Get the address of our task allocator's IMalloc interface
   hr = SHGetMalloc(&pMalloc);

   // Free the item ID list allocated by SHGetSpecialFolderLocation
   pMalloc->Free(pidl);

   // Free our task allocator
   pMalloc->Release();

   // Work with the special folder's path (contained in szPath)
   return CString(szPath);
}

CString GetCOMError(HRESULT hRes) {
  _com_error com_error(hRes);
  const TCHAR* pMess = com_error.ErrorMessage();
  CString szErr;
  szErr.Format(_T("Помилка COM(%x) : %s."),hRes, pMess);
  return szErr;
}

CString GetLastErrorAsString() {
	DWORD dwLastError = GetLastError();

  TCHAR szMessage[1024];
  szMessage[0] = '\0';
  LPCTSTR szError = szMessage;
  if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, dwLastError, 0, szMessage, sizeof(szMessage)-1, NULL))
  {
    szMessage[0] = '\0';
  }

  CString mess;
  mess.Format("%s (%d)", szError, dwLastError);
	mess.Replace("\r\n", " ");
  return mess;
}


BOOL RegisterDAODll(const CString& szDAODll, CString& szErr) {
  HRESULT (FAR STDAPICALLTYPE * lpDllEntryPoint)(void);
  HINSTANCE hDLL = ::LoadLibrary(szDAODll);

  HRESULT hRes = S_OK;

  if (hDLL < (HINSTANCE)HINSTANCE_ERROR) {
    szErr = GetLastErrorAsString();
    return false;
  }

  (FARPROC&)lpDllEntryPoint = GetProcAddress(hDLL, _T("DllRegisterServer"));

  if ( lpDllEntryPoint ) {
    hRes = (*lpDllEntryPoint)();
    if ( FAILED((*lpDllEntryPoint)()) ) {
      szErr = GetCOMError(hRes);
    }
  }
  ::FreeLibrary(hDLL);
  return (S_OK==hRes);
}

void CreateFolder(const CString& szFolder) {
  int nPos = szFolder.Find('\\', 3);
  
  while ( nPos > 0 ) {
    CString szSubFolder = szFolder.Left(nPos);
    if ( FALSE==FileExists(szSubFolder) ) {
      _mkdir(szSubFolder);
    }
    nPos = szFolder.Find('\\', nPos+1);
  }
  _mkdir(szFolder);
}

BOOL InstallDAO() {
  CString s, szDAOPath, szErr;
  CStringArray saDaoFiles;

  szDAOPath.Format(_T("%s\\DAO\\"), GetModulePath());
  s.Format(_T("%sdao360.dll"), szDAOPath);
  saDaoFiles.Add(s);
/*
  s.Format(_T("%sdao360.chm"), szDAOPath);
  saDaoFiles.Add(s);
  s.Format(_T("%sdaoread.txt"), szDAOPath);
  saDaoFiles.Add(s);
*/
  if ( FALSE==FileExists(saDaoFiles[0]) ) {
    s.Format(_T("Не існує бібліотеки DAO 3.6 \"%s\".\n")
             _T("На оригінальному компакт-диску ПК ЕРАГС бібліотека DAO 3.6 присутня.\n")
             _T("Використовуйте оригінальний компакт-диск ПК ЕРАГС."),
             saDaoFiles[0]
            );

    ::MessageBox(NULL, s, _T("Помилка під час установки DAO"), MB_ICONSTOP|MB_OK);
    return FALSE;
  }

  CString szMSSharedFolder;
  szMSSharedFolder.Format(_T("%s\\Microsoft Shared\\DAO"), GetSpecialFolder(0x002b/*CSIDL_PROGRAM_FILES_COMMON*/));

  if ( false==FileExists(szMSSharedFolder) ) {
    CreateFolder(szMSSharedFolder);
  }


  int nFiles = saDaoFiles.GetSize();
  for( int i(0); i < nFiles; i++ ) {
    CString szDestFile;
    szDestFile.Format(_T("%s\\%s"), szMSSharedFolder, GetFileName(saDaoFiles[i]));
    CopyFile(saDaoFiles[i], szDestFile, false);
  }

  s.Format(_T("%s\\%s"), szMSSharedFolder, GetFileName(saDaoFiles[0]));
  if ( false==RegisterDAODll(s, szErr) ) {
    ::MessageBox(NULL, szErr, _T("Помилка під час установки DAO"), MB_ICONSTOP|MB_OK);
    return false;
  }

  return true;
}

BOOL InstalledTheLatestDao() {
  CString szMSSharedFolder, szDaoDLL, szCDDaoDLL;

  szCDDaoDLL.Format(_T("%s\\DAO\\dao360.dll"), GetModulePath());
  WIN32_FIND_DATA fdCDao;
  if ( false==FileExists(szCDDaoDLL, &fdCDao) ) {
    CString s;
    s.Format(_T("Не існує бібліотеки DAO 3.6 \"%s\".\n")
             _T("На оригінальному компакт-диску ПК ЕРАГС бібліотека DAO 3.6 присутня.\n")
             _T("Використовуйте оригінальний компакт-диск ПК ЕРАГС."),
             szCDDaoDLL
            );
    ::MessageBox(NULL, s, _T("Установка ПК ЕРАГС"), MB_OK);
    ExitProcess(1);
    return false;
  }
  
  szMSSharedFolder.Format(_T("%s\\Microsoft Shared\\DAO"), GetSpecialFolder(0x002b/*CSIDL_PROGRAM_FILES_COMMON*/));

  if ( false==FileExists(szMSSharedFolder) ) {
    CreateFolder(szMSSharedFolder);
  }
  szDaoDLL.Format(_T("%s\\dao360.dll"), szMSSharedFolder);


  WIN32_FIND_DATA fd;
  BOOL fExists = FileExists(szDaoDLL, &fd);
  if ( false==fExists /*|| fd.ftLastWriteTime.dwHighDateTime < fdCDao.ftLastWriteTime.dwHighDateTime*/ ) {
    return false;
  }
  return true;
}

BOOL CheckAndInstallDAO() {
  BOOL fNeedDAOInstall = FALSE;


  fNeedDAOInstall = (InstalledTheLatestDao()==false);

  if ( false==fNeedDAOInstall ) {
    try {
      AfxDaoInit36();
    }
    catch(...) {
      fNeedDAOInstall = TRUE;
    }
  }
_try_again:
  if ( fNeedDAOInstall ) {
    LPCTSTR szText = _T("Увага! Комплекс ЕРАГС використовує компоненти бібліотеки DAO 3.6.\n")
                     _T("На Вашому комп'ютері необхідно встановити DAO 3.6.\n\n")
                     _T("Встановити DAO 3.6 прямо зараз?");
    if ( IDYES==::MessageBox(NULL, szText, _T("Установка ПК ЕРАГС"), MB_ICONQUESTION|MB_YESNO) ) {
      InstallDAO();
      fNeedDAOInstall = FALSE;
      try {
        AfxDaoInit36();
      }
      catch(...) {
        fNeedDAOInstall = TRUE;
      }
      if ( fNeedDAOInstall ) {
        LPCTSTR szText = _T("Увага! Помилка під час установки бібліотеки DAO 3.6.\n")
                         _T("Бібліотека DAO не встановлена коректно.\n\n")
                         _T("Можливі причини:\n")
                         _T("1. Вам не вистачає прав для виконання операцій встановлення.\n")
                         _T("   У цьому випадку зверніться до системного адміністратора.\n\n")
                         _T("2. У Вашій операційній системі зараз активні процеси,\n")
                         _T("   які заважають встановити бібліотеку DAO.\n")
                         _T("   Такими процесами можуть бути деякі антивірусні\n")
                         _T("   монітори, наприклад AVP.\n")
                         _T("   Щоб уникнути цієї проблеми, закінчіть ці процеси.\n\n")
                         _T("Спробувати встановити DAO ще раз?")
                         ;
        if ( IDYES==::MessageBox(NULL, szText, _T("Установка ПК ЕРАГС"), MB_ICONQUESTION|MB_YESNO) ) {
          goto _try_again;
        }
      }
    }
    else {
      return FALSE;
    }
  }
  return (fNeedDAOInstall==FALSE);
}

BOOL CEraSetupApp::PreInitInstance() {
  switch(g_Shell) {
    case Win32s:
    case WinNT3:
    case Win95:
      AfxMessageBox(_T("Програма ERAGS не підтримує цю операційну систему.\n")
                    _T("Для роботи ERAGS потрібна будь-яка із операціїних систем:\n\n")
                    _T("Windows 98, Windows Me, Windows 2000, Windows XP, Windows 7."));
      return FALSE;
  }
  return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CEraSetupApp initialization
BOOL CEraSetupApp::InitInstance() {
	AfxEnableControlContainer();

  if ( FALSE==PreInitInstance() )
    return FALSE;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

  if ( false==IsAdmin() ) {
    ::MessageBox(NULL,
                 _T("Увага! Ця програма вимагає адміністраторських прав.\n")
                 _T("Для того, щоб встановити цю програму, вам потрібно зайти в систему як адміністратору.\n")
                 _T("Якщо Ви не знаєте, як цього зробити, зверніться до адміністратора комп'ютера.\n"),
                 _T("Установка ПК ЕРАГС"), MB_ICONSTOP|MB_OK
                );
    return false;
  }

  OleInitialize(NULL);

  AfxInitRichEdit();
/*
  CCDMenu cdMenu;
  m_pMainWnd = &cdMenu;
  cdMenu.DoModal();
*/

  if ( false==CheckAndInstallDAO() ) {
    return false;
  }
  
  m_szSourceZip.Format(_T("%s\\DATA\\eradat.z"), GetModulePath());
  if ( !FileExists(m_szSourceZip) ) {
    return false;
  }

  CString szPFFolder;
  szPFFolder = GetSpecialFolder(0x0026/*CSIDL_PROGRAM_FILES*/);
  m_sEraPath.Format(_T("%s\\Erags"),  szPFFolder.Left(2));


  // Создаём времененную папку для распаковки в неё файлов
  GetTempPath(MAX_PATH, m_szUnzipFolder.GetBuffer(MAX_PATH));
  m_szUnzipFolder.ReleaseBuffer();
  m_szUnzipFolder += _T("EraCD.tmp");
  CreateDirectory(m_szUnzipFolder, NULL);

  // Распаковываем zip-файл с данными для установки
  CUnzipDlg UnzipDlg;
  if ( IDOK == UnzipDlg.DoModal() ) {

    m_Font.CreateFont(-12, 0, 0, 0, 
	  	                FW_BOLD, FALSE, FALSE, 0, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, 
		                  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

  	CMasterDlg dlg;
    CWelcomePage    WelcomePage;
    CAgreementPage  AgreementPage;
    CEraPathPage    EraPathPage;
    CProgressPage   ProgressPage;

    dlg.AddPage(&WelcomePage,   CWelcomePage::IDD);
    dlg.AddPage(&AgreementPage, CAgreementPage::IDD);
    dlg.AddPage(&EraPathPage,   CEraPathPage::IDD);
    dlg.AddPage(&ProgressPage,  CProgressPage::IDD);

  	m_pMainWnd = &dlg;
	  dlg.DoModal();

    if ( g_hHHCTRLInstance ) {
      FreeLibrary(g_hHHCTRLInstance);
    }
  }

  DeleteFileTree(m_szUnzipFolder); // Удаляем временную папку

  OleUninitialize();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
