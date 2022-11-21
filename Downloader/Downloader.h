
// Downloader.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

struct SFileInfo {
  CString   szFilename;
  // long      lUnixFileTime;
  FILETIME  ft;
  DWORD     dwFilesize;
  CString   szMD5;
  CString   szUrl;
  bool      fDownload;
  int       nItem;
  
  SFileInfo() {
    ft.dwLowDateTime = ft.dwHighDateTime = 0;
    dwFilesize = nItem = 0;
    fDownload = false;
  }
};
typedef CArray<SFileInfo, SFileInfo&> FIArray;

void FillArray(FIArray& fiArray, LPCTSTR szFileInfo);

// CDownloaderApp:
// See Downloader.cpp for the implementation of this class
//
class CDownloaderApp : public CWinAppEx {
public:
	CDownloaderApp();

private:
  BOOL  DownloadInfo(LPCTSTR szServer, LPCTSTR szUrl, LPCTSTR szTarget);

// Data members:
public:
  CString m_szServer;
  CString m_szDownloadUrl;
  CString m_szTargetFilePath;
  CString m_szDownloadPath;
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

BOOL    FileExists(PCSTR pszFilename, WIN32_FIND_DATA* pFindData=NULL);
BOOL    CreateFileFolder(LPCTSTR szFolder);
CString GetFilePath(LPCTSTR szFileName);


extern CDownloaderApp theApp;