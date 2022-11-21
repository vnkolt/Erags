//
// RegReader.cpp
//
#include "stdafx.h"
#include "RegReader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRegReader::CRegReader() {
  m_hKey = NULL;
}

CRegReader::~CRegReader() {
  CloseKey();
}

BOOL CRegReader::OpenKey(HKEY hKey) {
  CString szRegPath = _T("Software\\Vladimir Koltsov\\Erags\\Settings");
  if ( ERROR_SUCCESS != RegOpenKeyEx(hKey, szRegPath, 0, KEY_READ, &m_hKey) ) {
    m_hKey = NULL;
    return false;
  }
  return true;
}

void CRegReader::CloseKey() {
  if ( m_hKey ) {
    ::RegCloseKey(m_hKey);
    m_hKey = NULL;
  }
}

CString CRegReader::GetDatabase() {
  CString s;
  if ( NULL==m_hKey ) {
    OpenKey(HKEY_CURRENT_USER);
  }
  if ( m_hKey ) {
    TCHAR  sz[MAX_PATH];
    DWORD dwSize = sizeof(sz);
    DWORD dwType = REG_SZ;
    ::RegQueryValueEx(m_hKey, _T("Database"), NULL, &dwType, (BYTE*)sz, &dwSize);
    s = sz;
    CloseKey();
  }
  return s;
}

CString CRegReader::GetInstallLocation() {
  CString s;
  if ( NULL==m_hKey ) {
    OpenKey(HKEY_LOCAL_MACHINE);
  }
  if ( m_hKey ) {
    TCHAR  sz[MAX_PATH];
    DWORD dwSize = sizeof(sz);
    DWORD dwType = REG_SZ;
    ::RegQueryValueEx(m_hKey, _T("InstallLocation"), NULL, &dwType, (BYTE*)sz, &dwSize);
    s = sz;
    CloseKey();
  }
  return s;
}