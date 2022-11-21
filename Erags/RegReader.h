
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
private:
  BOOL    OpenKey();
  void    CloseKey();
public:
  int     Now();
  int     GetLastUpdatingChecked();
  void    SetLastUpdatingChecked();
  BOOL    IsNeedDownloadingUpdates();
};