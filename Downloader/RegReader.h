
//
// RegReader.h
//
#pragma once

class CRegReader {
public:
  CRegReader();
  ~CRegReader();
private:
  HKEY    m_hKey;
public:
  BOOL    OpenKey();
  void    CloseKey();
public:
  CString GetDatabase();
  CString GetValidOwner();
  CString GetRegTimerData();
};