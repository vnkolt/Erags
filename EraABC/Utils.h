#if !defined(UTILS_H_INCLUDED)
#define UTILS_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

CString GetFullBracketString(const CString& src, LPCTSTR szKey);
CString GetBracketString(const CString& src, LPCTSTR szKey);
void    MakeBracketString(CString& src, LPCTSTR szKey, LPCTSTR szValue);
void    MakeBracketString(CString& src, LPCTSTR szKey, CWnd* pWnd);
CString GetSentence(const CString& szSrc, LPCTSTR szBOS, LPCTSTR szEOS=_T("."));
CString GetFilePath(LPCTSTR szFileName);
CString GetFileExt(LPCTSTR szPath);
CString GetFileName(LPCTSTR szPath);
CString GetModulePath();


BOOL    FileExists(PCSTR pszFilename);
void    DeleteFileIfExist(PCSTR pszFilename);

void SetControlsFont(CWnd* pParentWnd, CFont& font);
CString SetFileExt(LPCTSTR szPath, LPCTSTR szExt);

CString GetNumFromStr(LPCTSTR szMemo, LPCTSTR szWhat, bool fAdd=true);
CString GetNumFromStr(CDaoRecordset* pSet, LPCTSTR szFieldName, LPCTSTR szWhat, bool fAdd/*=true*/);
CString GetStringPart(const CString& sFrom, int nLex);

BOOL    getFileTime(LPCTSTR szFileName, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);
BOOL    setFileTime(LPCTSTR szFileName, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);

void    IconToBitmap(CWnd* pWnd, CBitmap* pBitmap, HICON hIcon, int bmWidth, int bmHeight);

#endif//UTILS_H_INCLUDED
