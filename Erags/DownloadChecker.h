
//
// DownloadChecker.h
//
#pragma once

class CDownloadChecker {
public:
  CDownloadChecker();
  ~CDownloadChecker();
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

void  RunDownloadUpdates();