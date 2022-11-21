
//
// RegWriter.h
//
#pragma once

class CRegWriter {
public:
  CRegWriter(HKEY hParentKey);
  ~CRegWriter();
private:
  HKEY    m_hParentKey;
  HKEY    m_hKey;
public:
  BOOL    OpenKey();
  void    CloseKey();
public:
  void    SetLastUpdated();
};