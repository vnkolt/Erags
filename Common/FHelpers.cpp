//
// FHelpers.cpp
//
#include "stdafx.h"
#include "FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString GetFilePath(LPCTSTR szFileName) {
CString sPath(szFileName);
  return sPath.Mid( 0, sPath.ReverseFind('\\') );
}

CString GetFileName(LPCTSTR szPath) {
CString sPath(szPath);
  return sPath.Mid( sPath.ReverseFind('\\')+1 );
}
CString GetFileExt(LPCTSTR szPath) {
CString sRet( _T("") );
CString sPath(szPath);
int iDot, iSlash;
  iDot = sPath.ReverseFind('.');
  iSlash = sPath.ReverseFind('\\');

  if ( iDot > iSlash )
    sRet = sPath.Mid( iDot + 1 );
  return sRet;
}

CString GetModuleFileName() {
  CString s;
  GetModuleFileName(NULL, s.GetBuffer(MAX_PATH), MAX_PATH);
  s.ReleaseBuffer();
  return s;
}
CString GetModulePath() {
  return GetFilePath(GetModuleFileName());
}

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

CString SetFileExt(LPCTSTR szFilename, LPCTSTR szExt) {
  CString szFile = szFilename;
  int dot = szFile.ReverseFind('.');
  if ( dot >= 0 ) {
    szFile = szFile.Left(dot);
  }
  if ( szExt[0] != '.' ) {
    szFile += '.';
  }
  szFile += szExt;
  return szFile;
/*
  CString sFileName = szPath;
  LPTSTR pBuf = new TCHAR[strlen(szPath) + strlen(szExt)+2];
  strcpy(pBuf, szPath);
  if ( PathRenameExtension(pBuf, szExt))
    sFileName = pBuf;
  delete pBuf;
  return sFileName;
*/
}

void DeleteFileIfExist(PCSTR pszFilename) {
  if( SetFileAttributes(pszFilename, FILE_ATTRIBUTE_NORMAL) )
    DeleteFile(pszFilename);
}

CString GetHostName() {
  CString s;
  DWORD dwName = MAX_COMPUTERNAME_LENGTH;
  GetComputerName(s.GetBuffer(MAX_COMPUTERNAME_LENGTH + 1), &dwName);
  s.ReleaseBuffer();
  return s;
}

CString FormatError(DWORD dwError/*=0*/) {
  if ( 0==dwError ) {
    dwError = GetLastError();
  }
  LPVOID lpMsgBuf;
  FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |  FORMAT_MESSAGE_IGNORE_INSERTS,
                 NULL,
                 dwError,
                 0, // Default language
                 (LPTSTR) &lpMsgBuf,
                 0,
                 NULL 
                );
  CString szError;
  szError.Format(_T("%s"), lpMsgBuf);
  LocalFree( lpMsgBuf );
  szError.TrimRight("\r\n");
  szError.TrimRight(".");
  return szError;
}
