#include "stdafx.h"
#include <windowsx.h>
#include <Shlwapi.h>

#include "..\Common\MDB.h"
#include "..\Common\CyrString.h"

CString GetFullBracketString(const CString& src, LPCTSTR szKey) {
  CString s;
  int iFound = src.Find(szKey, 0);
  if ( iFound >= 0) {
    while( --iFound >= 0 ) {          // Find open '{'
      if ( src.GetAt(iFound)=='{')
        break;
    }
    while( iFound < src.GetLength() ) {// Find close '}'
      TCHAR c = src.GetAt(iFound);
      s += c;
      if ( '}'==c )
        break;
      iFound++;
    }
  }
  return s;
}
CString GetBracketString(const CString& src, LPCTSTR szKey) {
  CString s = GetFullBracketString(src, szKey);
  if ( !s.IsEmpty() ) {
    s.TrimLeft('{');
    s.TrimRight('}');
    s = Trim(s);
    s.Replace(szKey, _T("") );
    s = Trim(s);
  }
  return s;
}
void MakeBracketString(CString& src, LPCTSTR szKey, LPCTSTR szValue) {
  CString sNew, sOld, sValue;
  sValue = Trim(szValue);
  sOld = GetFullBracketString(src, szKey);
  sNew = _T("");
  if ( sValue.IsEmpty() ) { // We should delete key string
    if ( !sOld.IsEmpty() ) {
      src.Replace(sOld, sNew);
    }
  }
  else {
    sNew.Format(_T("{%s %s}"), szKey, sValue);
    if ( !sOld.IsEmpty() )
      src.Replace(sOld, sNew);
    else
      src += sNew;
  }
  src = Trim(src);
}
void MakeBracketString(CString& src, LPCTSTR szKey, CWnd* pWnd) {
  CString sValue;
  pWnd->GetWindowText(sValue);
  MakeBracketString(src, szKey, sValue);
}

CString GetSentence(const CString& szSrc, LPCTSTR szBOS, LPCTSTR szEOS/*=_T(".")*/) {
  CString sRet = _T("");
  int iFound = szSrc.Find(szBOS,0);
  int nEndLen = lstrlen(szEOS);
  if ( iFound != -1 ) {
    int i = 0;
    CString s;
    TCHAR c;
    s = szSrc.Mid(iFound);
    c = s.Mid(i, 1)[0];
    while( c != 0 ) {
      sRet += c;
      i++;
      if ( s.Mid(i, nEndLen)==szEOS) {
        sRet += szEOS;
        break;
      }
      if ( s.GetLength()==i )
        break;
      c = s.Mid(i, 1)[0];
    }
  }
  return sRet;
}


CString GetFilePath(LPCTSTR szFileName){
CString sPath(szFileName);
  return sPath.Mid( 0, sPath.ReverseFind('\\') );
}

CString GetFileName(LPCTSTR szPath){
CString sPath(szPath);
  return sPath.Mid( sPath.ReverseFind('\\')+1 );
}
CString GetFileExt(LPCTSTR szPath){
CString sRet( _T("") );
CString sPath(szPath);
int iDot, iSlash;
  iDot = sPath.ReverseFind('.');
  iSlash = sPath.ReverseFind('\\');

  if ( iDot > iSlash )
    sRet = sPath.Mid( iDot + 1 );
  return sRet;
}

CString GetModulePath() {
  CString s;
  GetModuleFileName(NULL, s.GetBuffer(MAX_PATH), MAX_PATH);
  s.ReleaseBuffer();
  return GetFilePath(s);
}

BOOL FileExists(PCSTR pszFilename){
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = FindFirstFile(pszFilename, &FindFileData);

  if (INVALID_HANDLE_VALUE==hFind)
    return FALSE;
  FindClose(hFind);
  return TRUE;
}

void DeleteFileIfExist(PCSTR pszFilename) {
  if( SetFileAttributes(pszFilename, FILE_ATTRIBUTE_NORMAL) )
    DeleteFile(pszFilename);
}
void SetControlsFont(CWnd* pParentWnd, CFont& font) {
	CWnd* pItemWnd = pParentWnd->GetWindow(GW_CHILD);
  if ( pItemWnd ) {
    LOGFONT lf;
		CFont* pFont = pItemWnd->GetFont();
		if(pFont && pFont->GetLogFont(&lf)){
			lf.lfWeight =  FW_BOLD;
			lf.lfHeight = -12;
			strcpy(lf.lfFaceName, _T("Ms Sans Serif"));
			font.CreateFontIndirect(&lf);
			while(pItemWnd){
				pItemWnd->SetFont(&font);
				pItemWnd = pItemWnd->GetWindow(GW_HWNDNEXT);
			}
    }
	}
}

/************************************** : by VK at 13.10.2004 22:40:15 **\
CString SetFileExt(LPCTSTR szPath, LPCTSTR szExt) {
  CString sFileName = szPath;
  LPTSTR pBuf = new TCHAR[strlen(szPath) + strlen(szExt)+2];
  strcpy(pBuf, szPath);
  if ( PathRenameExtension(pBuf, szExt))
    sFileName = pBuf;
  delete pBuf;
  return sFileName;
}
\************************************** : by VK at 13.10.2004 22:40:18 **/

CString GetStringPart(const CString& sFrom, int nLex) {
  CString sRet = sFrom;

  int lHalfLen = sRet.GetLength()/2;
  int iHalfIndex = lHalfLen;
  while ( iHalfIndex > 0 ) {
    if ( sRet.GetAt(iHalfIndex) == ' ')
      break;
    iHalfIndex--;
  }
  CString sLeft  = Trim(sRet.Left(iHalfIndex)),
          sRight = Trim(sRet.Mid(iHalfIndex));
  if     (nLex == 1) sRet = sLeft;
  else if(nLex == 2) sRet = sRight;
  else {
    sRet = sLeft;
    sRet += _T("\r\n");
    sRet += sRight;
    sRet = Trim(sRet);
  }
  return sRet;
}

HANDLE OpenExistingFile_for_Read(LPCTSTR lpFileName) {
  return CreateFile(lpFileName,     // lpFileName
                    GENERIC_READ,   // dwDesiredAccess
                    FILE_SHARE_READ,// dwShareMode
                    NULL,           // lpSecurityAttributes
                    OPEN_EXISTING,  // dwCreationDisposition
                    FILE_ATTRIBUTE_ARCHIVE |
                    FILE_ATTRIBUTE_HIDDEN |
                    FILE_ATTRIBUTE_READONLY,
                    NULL);
}

BOOL getFileTime(LPCTSTR szFileName, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime) {
  BOOL bRet = FALSE;
  HANDLE hFile = OpenExistingFile_for_Read(szFileName);
  if ( INVALID_HANDLE_VALUE ==hFile )
    return bRet;
  bRet = ::GetFileTime(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
  CloseHandle(hFile);
  return bRet;
}

BOOL setFileTime(LPCTSTR szFileName, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime) {
  BOOL bRet = FALSE;
  HANDLE hFile = OpenExistingFile_for_Read(szFileName);
  if ( INVALID_HANDLE_VALUE ==hFile )
    return bRet;
  bRet = ::SetFileTime(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
  CloseHandle(hFile);
  return bRet;
}

void IconToBitmap(CWnd* pWnd, CBitmap* pBitmap, HICON hIcon, int bmWidth, int bmHeight) {
  CWindowDC dc(pWnd);
  CDC memdc;
	memdc.CreateCompatibleDC(&dc);

  pBitmap->CreateCompatibleBitmap(&dc, bmWidth, bmHeight);

  // select toolbar bitmap
 	CBitmap *poldbm = memdc.SelectObject(pBitmap);

  // draw into the dc/bitmap
	CBrush brush;
	brush.CreateSysColorBrush(COLOR_BTNFACE);
	VERIFY(::DrawIconEx(memdc, 0, 0,	 // dc, x, y
	    	 hIcon,			               // HICON (first small one)
			   GetSystemMetrics(SM_CXSMICON), // cx
			   GetSystemMetrics(SM_CYSMICON), // cy
			   0, brush, DI_NORMAL));			 // frame, brush, flags
  memdc.SelectObject(poldbm);

}