//
// RegWriter.cpp
//
#include "stdafx.h"
#include "RegWriter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRegWriter::CRegWriter(HKEY hParentKey) {
  m_hParentKey = hParentKey;
  m_hKey = NULL;
}

CRegWriter::~CRegWriter() {
  CloseKey();
}

BOOL CRegWriter::OpenKey() {
  CString szRegPath = _T("Software\\Vladimir Koltsov\\Erags\\Settings");
  if ( ERROR_SUCCESS != RegOpenKeyEx(m_hParentKey, szRegPath, 0, KEY_ALL_ACCESS, &m_hKey) ) {
    m_hKey = NULL;
    return false;
  }
  return true;
}

void CRegWriter::CloseKey() {
  if ( m_hKey ) {
    ::RegCloseKey(m_hKey);
    m_hKey = NULL;
  }
}

void CRegWriter::SetLastUpdated() {
  if ( m_hKey ) {
    SYSTEMTIME st;
    GetLocalTime(&st);
    DWORD LastUpdatedDate = st.wYear * 10000  + st.wMonth*100 + st.wDay;
    ::RegSetValueEx(m_hKey, _T("LastUpdatedDate"), 0, REG_DWORD, (const BYTE*)&LastUpdatedDate, sizeof(LastUpdatedDate));
  }
}