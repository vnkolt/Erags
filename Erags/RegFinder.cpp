//
// RegFinder.cpp
//
#include "stdafx.h"
#include "RegFinder.h"

#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegFinder
CRegFinder::CRegFinder(HKEY hStartKey, LPCTSTR szSubkey) {
  if(RegOpenKeyEx(hStartKey, szSubkey, 0, KEY_READ, &m_hKey) != ERROR_SUCCESS) {
    m_hKey = NULL;
  }
}
CRegFinder::~CRegFinder() {
  if ( m_hKey != NULL ) {
    RegCloseKey(m_hKey);
  }
}

BOOL CRegFinder::Find(LPCTSTR szInstallRegPath, LPCTSTR szInstallKeyName, LPCTSTR szAppName, CString& szExePath) {
  TCHAR szSubkey[MAX_PATH + 1];
  DWORD dwIndex = 0;
  CString szRegPath;
  BOOL fRet = false;
  while( false==fRet && ERROR_SUCCESS==RegEnumKey(m_hKey, dwIndex, szSubkey, sizeof(szSubkey)) ) {
    szRegPath.Format(_T("%s\\%s"), szSubkey, szInstallRegPath);
    HKEY hKey;
    if ( RegOpenKeyEx(m_hKey, szRegPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
      TCHAR szPath[MAX_PATH + 1];
      DWORD dwSize = sizeof(szPath);
      DWORD dwType = REG_SZ;
      if ( ERROR_SUCCESS==RegQueryValueEx(hKey, szInstallKeyName, NULL, &dwType, (LPBYTE)szPath, &dwSize) ) {
        CString szAppPath;
        szAppPath.Format(_T("%s\\%s.exe"), szPath, szAppName);
        while ( szAppPath.Find(_T("\\\\"), 0) != -1 ) {
          szAppPath.Replace(_T("\\\\"), _T("\\"));
        }
        // szAppPath.Replace(_T("\""), _T(""));
        if ( FileExists(szAppPath) ) {
          szExePath = szAppPath;
          fRet = true;
        }
      }
      RegCloseKey(hKey);
    }
    dwIndex++;
  }
  return fRet;
}