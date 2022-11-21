//
// RegReader.cpp
//
#include "stdafx.h"
#include "Erags.h"
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

int CRegReader::GetLastUpdatingChecked() {
  return theApp.GetProfileInt(_T("Settings"), _T("LastUpdChecked"), 0);
}

int CRegReader::Now() {
  SYSTEMTIME st;
  GetLocalTime(&st);
  return st.wYear * 10000  + st.wMonth*100 + st.wDay;
}
void CRegReader::SetLastUpdatingChecked() {
  theApp.WriteProfileInt(_T("Settings"), _T("LastUpdChecked"), Now());
}

BOOL CRegReader::IsNeedDownloadingUpdates() {
  if ( false==OpenKey() ) {
    return false;
  }
  int nChecked = GetLastUpdatingChecked();
  int nNow     = Now();
  CloseKey();
  return (abs(nNow-nChecked) >= 7);
}

void CRegReader::RunDownloadUpdates() {
}