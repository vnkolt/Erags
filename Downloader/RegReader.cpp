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

BOOL CRegReader::OpenKey() {
  CString szRegPath = _T("Software\\Vladimir Koltsov\\Erags\\Settings");
  if ( ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, szRegPath, 0, KEY_READ, &m_hKey) ) {
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
  if ( m_hKey ) {
    TCHAR  sz[MAX_PATH];
    DWORD dwSize = sizeof(sz);
    DWORD dwType = REG_SZ;
    ::RegQueryValueEx(m_hKey, _T("Database"), NULL, &dwType, (BYTE*)sz, &dwSize);
    s = sz;
  }
  return s;
}

CString CRegReader::GetValidOwner() {
  CString s;
  if ( m_hKey ) {
    BYTE sz[MAX_PATH];
    DWORD dwSize = sizeof(sz);
    DWORD dwType = REG_BINARY;
    if ( ERROR_SUCCESS  == ::RegQueryValueEx(m_hKey, _T("RFLInfo"), NULL, &dwType, (BYTE*)sz, &dwSize) ) {
      for( DWORD i(0); i < dwSize; i++ ) {
        s.AppendFormat("%02X ", sz[i]);
      }
    }
  }
  s += _T("\r\n");
  return s;
}

CString CRegReader::GetRegTimerData() {
  CString s;
  if ( m_hKey ) {
    BYTE  sz[MAX_PATH];
    DWORD dwSize = sizeof(sz);
    DWORD dwType = REG_BINARY;
    if ( ERROR_SUCCESS  == ::RegQueryValueEx(m_hKey, _T("RTInfo"), NULL, &dwType, (BYTE*)sz, &dwSize) ) {
      for( DWORD i(0); i < dwSize; i++ ) {
        s.AppendFormat("%02X ", sz[i]);
      }
    }
  }
  s += _T("\r\n");
  return s;
}
