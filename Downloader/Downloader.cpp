
// Downloader.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Downloader.h"
#include "DownloaderDlg.h"

#include <direct.h>
#include <Winhttp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL FileExists(PCSTR pszFilename, WIN32_FIND_DATA* pFindData/*=NULL*/) {
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = FindFirstFile(pszFilename, &FindFileData);

  if (INVALID_HANDLE_VALUE==hFind)
    return false;
  FindClose(hFind);
  if ( pFindData )
    memcpy(pFindData, &FindFileData, sizeof(WIN32_FIND_DATA));
  return true;
}

CString GetFilePath(LPCTSTR szFileName) {
  CString sPath(szFileName);
  return sPath.Mid( 0, sPath.ReverseFind('\\') );
}

BOOL CreateFileFolder(LPCTSTR szFilepath) {
  if ( FileExists(szFilepath, NULL) ) {
    return true;
  }
  if ( _mkdir(szFilepath)== 0 ) {
    return true;
  }
  return false;
}

BOOL IsFileName(const CString& s) {
  if ( s.Find(_T(".")) == -1 ) {
    return false;
  }
  return true;
}
BOOL IsDigits(const CString& s) {
  int nLen = s.GetLength();
  for( int i(0); i < nLen; i++ ) {
    if ( 0==isdigit(s[i]) ) {
      return false;
    }
  }
  return true;
}
BOOL IsHex(const CString& s) {
  int nLen = s.GetLength();
  for( int i(0); i < nLen; i++ ) {
    if ( 0==isxdigit(s[i]) ) {
      return false;
    }
  }
  return true;
}

BOOL IsURL(const CString& s) {
  CString sz = s;
  sz.MakeLower();
  if ( sz.Left(7) != _T("http://") ) {
    return false;
  }
  return true;
}

BOOL IsValidTokens(const CString& s) {
  int nPos = 0;
  CString szToken;
  szToken = s.Tokenize(_T(" \t"), nPos);
  // Filename
  if ( szToken.IsEmpty() || false==IsFileName(szToken) ) {
    return false;
  }
  // DateTime
  szToken = s.Tokenize(_T(" \t"), nPos);
  if ( szToken.GetLength() != 14 || false==IsDigits(szToken) ) {
    return false;
  }
  // Filesize
  szToken = s.Tokenize(_T(" \t"), nPos);
  if ( szToken.IsEmpty() || false==IsDigits(szToken) ) {
    return false;
  }
  // MD5
  szToken = s.Tokenize(_T(" \t"), nPos);
  if ( szToken.GetLength() != 32 || false==IsHex(szToken) ) {
    return false;
  }
  // URL
  szToken = s.Tokenize(_T(" \t"), nPos);
  if ( szToken.IsEmpty() || false==IsURL(szToken) ) {
    return false;
  }
  return true;
}

void FillArray(FIArray& fiArray, LPCTSTR szFileInfo) {
  CStdioFile f;
  if ( false==f.Open(szFileInfo, CFile::modeRead) ) {
    return;
  }
  CString s;
  while ( f.ReadString(s) ) {
    s.Trim();
    if ( false==s.IsEmpty() && IsValidTokens(s) ) {
      CString szTime;
      SFileInfo fi;
      int nPos = 0;

      fi.szFilename    = s.Tokenize(_T(" \t"), nPos);
      // fi.lUnixFileTime = atol(s.Tokenize(_T(" \t"), nPos));
      szTime           = s.Tokenize(_T(" \t"), nPos);
      if ( szTime.GetLength()==14 ) {
        SYSTEMTIME st;
        memset(&st, 0, sizeof(st));
        st.wYear   = atoi(szTime.Mid(0,4));
        st.wMonth  = atoi(szTime.Mid(4,2));
        st.wDay    = atoi(szTime.Mid(6,2));
        st.wHour   = atoi(szTime.Mid(8,2));
        st.wMinute = atoi(szTime.Mid(10,2));
        st.wSecond = atoi(szTime.Mid(12,2));
        SystemTimeToFileTime(&st, &fi.ft);
        /*
        //               YYYY                    MM                  DD
        odt.SetDateTime( atoi(s.Mid(0,4)), atoi(s.Mid(4,2)), atoi(s.Mid(6,2)), 
        //                 hh                    mm                  ss
                         atoi(s.Mid(8,2)), atoi(s.Mid(10,2)), atoi(s.Mid(12,2))
                       );
        if ( odt.GetStatus()==COleDateTime::valid ) {
        }
        */

      }

      if ( nPos >= 0 ) fi.dwFilesize = atol(s.Tokenize(_T(" \t"), nPos));
      if ( nPos >= 0 ) fi.szMD5      = s.Tokenize(_T(" \t"), nPos);
      if ( nPos >= 0 ) fi.szUrl      = s.Tokenize(_T(" \t"), nPos);
      fiArray.Add(fi);
    }
  }

  f.Close();
}

int FindFile(FIArray& fiArray, LPCTSTR szFilename) {
  int nCount = fiArray.GetSize();
  for( int i(0); i < nCount; i++ ) {
    SFileInfo& si = fiArray.GetAt(i);
    if ( si.szFilename.CompareNoCase(szFilename)==0 ) {
      return i;
    }
  }
  return -1;
}

int SetDownloads(FIArray& fiaOld, FIArray& fiaNew, LPCTSTR szTargetPath) {
  int nDownloads = 0;
  int nCount = fiaNew.GetSize();
  for( int i(0); i < nCount; i++ ) {
    SFileInfo& fiNew = fiaNew.GetAt(i);
    int nOld = FindFile(fiaOld, fiNew.szFilename);
    if ( fiNew.szFilename.CompareNoCase(_T("EraWiz.zip"))==0 ) {
      CString szFullPath;
      szFullPath.Format(_T("%s\\%s"), szTargetPath, _T("EraWiz.zip"));
      if ( false==FileExists(szFullPath, NULL) ) { // do not update EraWiz.dll for station, only for server
        continue;
      }
    }
    if ( -1==nOld ) {
      fiNew.fDownload = true;
      nDownloads++;
    }
    else {
      SFileInfo& fiOld = fiaOld.GetAt(nOld);
      if ( memcmp(&fiNew.ft, &fiOld.ft, sizeof(fiNew.ft)) != 0 || fiNew.dwFilesize != fiOld.dwFilesize || fiNew.szMD5 != fiOld.szMD5 ) {
        fiNew.fDownload = true;
        nDownloads++;
      }
    }
  }
  return nDownloads;
}

// CDownloaderApp

BEGIN_MESSAGE_MAP(CDownloaderApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDownloaderApp construction

CDownloaderApp::CDownloaderApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CDownloaderApp object

CDownloaderApp theApp;

BOOL CDownloaderApp::DownloadInfo(LPCTSTR szServer, LPCTSTR szUrl, LPCTSTR szTarget) {
	//Variables 
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPBYTE pszOutBuffer;
	BOOL  bResults = false;

  CComBSTR bstrServer(szServer);
  CComBSTR bstrUrl(szUrl);

  HINTERNET  hSession = NULL, hConnect = NULL, hRequest = NULL;
	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen( L"PKErags Downloader/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	// Specify an HTTP server.
  if (hSession)
    hConnect = WinHttpConnect( hSession, bstrServer /*L"sites.google.com"*/, INTERNET_DEFAULT_HTTP_PORT, 0);

  // Create an HTTP request handle.
	if (hConnect)
		hRequest = WinHttpOpenRequest( hConnect, L"GET", bstrUrl/*L"/site/pkerags/Files/FileInfo.txt"*/, NULL, WINHTTP_NO_REFERER, NULL, NULL);

	// Send a request.
  if (hRequest) {
		bResults = WinHttpSendRequest( hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
  }
	// End the request.
	if (bResults)    
		bResults = WinHttpReceiveResponse( hRequest, NULL );/**/
	// Keep checking for data until there is nothing left.
  if (bResults) {
  	HANDLE hFile = CreateFile(szTarget, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		do {        
			// Check for available data.
			dwSize = 0;        
      if (!WinHttpQueryDataAvailable( hRequest, &dwSize)) {
				; // printf( "Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
      }
			// Allocate space for the buffer.       
			pszOutBuffer = new byte[dwSize+1];
			if (!pszOutBuffer) {
				// printf("Out of memory\n");
        bResults = false;
				dwSize = 0;
			}
			else {       
				// Read the Data.
				ZeroMemory(pszOutBuffer, dwSize+1);
				if (!WinHttpReadData( hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded)) {
					; // printf( "Error %u in WinHttpReadData.\n", GetLastError());
				}
				else {
					//printf("%s", pszOutBuffer);
					DWORD wmWritten;
					BOOL fWrite = WriteFile(hFile, pszOutBuffer, dwSize, &wmWritten, NULL);
					int n = GetLastError();
				}
				// Free the memory allocated to the buffer.
				delete [] pszOutBuffer;
			}
		} while (dwSize>0);
		CloseHandle(hFile);
  }
  // Report any errors.
/*
  if (!bResults) {
    // return false
  }
*/
  // Close any open handles.
  if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);
  return bResults;
}

// CDownloaderApp initialization
BOOL CDownloaderApp::InitInstance() {

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
  
  // Downloader.exe /Check:server.com /Url:"xxx" /T:"filename"
  // OR
  // Downloader.exe /NewFile:"FileInfo.txt" /OldFile:"FileInfo.txt"

  BOOL fCheckDownload = false;

/*
	CStringList stringList;
	ConvertCommandLineToStringList(GetCommandLine(), stringList);

	POSITION pos = stringList.GetHeadPosition();

  if ( pos != NULL ) { // skip argv[0] - full executable filename
    stringList.GetNext(pos);
  }
*/
  for( int i(1); i < __argc; i++ ) {
		//CString szParam = stringList.GetNext(pos);
    CString szParam = __argv[i];

		CString szParameterName;
		CString szValue;

		int nSemicolonPos = szParam.Find(':');
		if (nSemicolonPos > 0) {
			szParameterName = szParam.Left(nSemicolonPos);
			szValue = szParam.Right(szParam.GetLength() - nSemicolonPos - 1);
		}else{
			szParameterName = szParam;
		}

		szParameterName.MakeUpper();

		if (szParameterName == _T("/CHECK") ) {
			m_szServer = szValue;
			m_szServer.Trim("\"' ");
      fCheckDownload = true;
		}
		else if (szParameterName == _T("/URL") ) {
			m_szDownloadUrl = szValue;
			m_szDownloadUrl.Trim("\"' ");
		}
    else if (szParameterName == _T("/T") ) {
			m_szTargetFilePath = szValue;
			m_szTargetFilePath.Trim("\"' ");
      m_szDownloadPath.Format(_T("%s\\Downloads"), m_szTargetFilePath);
    }
	}

  // /check:sites.google.com /Url:"/site/pkerags/Files/FileInfo.txt" /T:"E:\Erags\Downloads\FileInfo.txt"

  FIArray fiOldFiles, fiNewFiles;

  if ( fCheckDownload && false==m_szTargetFilePath.IsEmpty() ) {
    CString szFileInfoName, szNewFileInfoName;
    szFileInfoName.Format(_T("%s\\FileInfo.txt"), m_szTargetFilePath);
    szNewFileInfoName.Format(_T("%s\\FileInfo.txt"), m_szDownloadPath);

    if ( false==CreateFileFolder(m_szDownloadPath) ) {
      return false;
    }

    if ( false==DownloadInfo(m_szServer, m_szDownloadUrl, szNewFileInfoName) ) {
      return false;
    }

    // http://cid-515b2bdbc0357dfa.office.live.com/self.aspx/Erags/Templates.info
    // http://public.bay.livefilestore.com/y1pb26OxBT9lRa6pfZvjKkWLhtwzPD666C6bcDJkIUEDafXv_o6O1J4gea3BMMletPPf74K8Z11A8g4YYebqnMiUA/Templates.info?download&psid=1

    // http://cid-515b2bdbc0357dfa.office.live.com/self.aspx/Erags/Templates.info

    FillArray(fiOldFiles, szFileInfoName);
    FillArray(fiNewFiles, szNewFileInfoName);

    if ( 0 == SetDownloads(fiOldFiles, fiNewFiles, m_szTargetFilePath) ) {
      return false;
    }
/*
    if ( false==DownloadInfo(_T("cid-515b2bdbc0357dfa.office.live.com"), _T("/self.aspx/Erags/Templates.info"), _T("E:\\Erags\\Downloads\\Templates.info")) ) {
    }
*/
  }
  else {
    AfxMessageBox(_T("Downloader ПК ЕРАГС автоматично завантажується програмою Erags."));
    return false;
  }

	cmdInfo.m_strFileName.Empty();
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNew;

  // InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Vladimir Koltsov"));

	CDownloaderDlg dlg(&fiNewFiles);
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
