//
// DownloadChecker.cpp
//
#include "stdafx.h"
#include "Erags.h"
#include "DownloadChecker.h"

#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDownloadChecker::CDownloadChecker() {
  m_hKey = NULL;
}

CDownloadChecker::~CDownloadChecker() {
  CloseKey();
}

BOOL CDownloadChecker::OpenKey() {
  CString szRegPath = _T("Software\\Vladimir Koltsov\\Erags\\Settings");
  if ( ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, szRegPath, 0, KEY_READ, &m_hKey) ) {
    m_hKey = NULL;
    return false;
  }
  return true;
}

void CDownloadChecker::CloseKey() {
  if ( m_hKey ) {
    ::RegCloseKey(m_hKey);
    m_hKey = NULL;
  }
}

int CDownloadChecker::GetLastUpdatingChecked() {
  return theApp.GetProfileInt(_T("Settings"), _T("LastUpdChecked"), 0);
}

int CDownloadChecker::Now() {
  SYSTEMTIME st;
  GetLocalTime(&st);
  return st.wYear * 10000  + st.wMonth*100 + st.wDay;
}
void CDownloadChecker::SetLastUpdatingChecked() {
  theApp.WriteProfileInt(_T("Settings"), _T("LastUpdChecked"), Now());
}

BOOL CDownloadChecker::IsNeedDownloadingUpdates() {
  if ( false==OpenKey() ) {
    return false;
  }
  int nChecked = GetLastUpdatingChecked();
  int nNow     = Now();
  CloseKey();
  return (abs(nNow-nChecked) >= 7);
}

void RunDownloadUpdates() {
  CDownloadChecker rr;
  if ( rr.IsNeedDownloadingUpdates() ) {
    rr.SetLastUpdatingChecked();
    CString szEraPath = GetModulePath();
    CString szDownloadModule;
    szDownloadModule.Format(_T("%s\\Downloader.exe"), szEraPath);
    if ( FileExists(szDownloadModule) ) {
      // /check:sites.google.com /Url:"/site/pkerags/Files/FileInfo.txt" /T:"E:\Erags"
      CString szCommandLine;
      szCommandLine.Format(_T("\"%s\" /check:sites.google.com /Url:\"/site/pkerags/Files/FileInfo.txt\" /T:\"%s\""),
                           szDownloadModule, szEraPath
                          );

      TCHAR szExe[MAX_PATH*2];
      strncpy(szExe, szCommandLine, sizeof(szExe)-1);

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

      CreateProcess(NULL,
                    szExe,
                    NULL,
                    NULL,
                    TRUE,
                    NORMAL_PRIORITY_CLASS,
                    NULL,
                    NULL,
                    &si,
                    &pi);
    }
  }
}