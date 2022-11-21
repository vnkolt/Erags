#pragma once

//
// RegFinder.h
//

class CRegFinder : public CObject {
public:
  CRegFinder(HKEY hStartKey, LPCTSTR szSubkey);
  ~CRegFinder();
protected:
  HKEY  m_hKey;
public:
  BOOL  IsOk()  { return (m_hKey != NULL); }
  BOOL  Find(LPCTSTR szInstallRegPath, LPCTSTR szInstallKeyName, LPCTSTR szAppName, CString& szExePath);
};