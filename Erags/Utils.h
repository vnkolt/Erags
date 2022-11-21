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
CString GetDateFromStr(LPCTSTR szMemo);
void    SetControlsFont(CWnd* pParentWnd, CFont& font);

CString GetNumFromStr(LPCTSTR szMemo, LPCTSTR szWhat, bool fAdd=true);
CString GetNumFromStr(CDaoRecordset* pSet, LPCTSTR szFieldName, LPCTSTR szWhat, bool fAdd/*=true*/);
CString GetStringPart(const CString& sFrom, int nLex);

void    IconToBitmap(CWnd* pWnd, CBitmap* pBitmap, HICON hIcon, int bmWidth, int bmHeight);

int GetIndexOf(DWORD dwValue, const CDWordArray* pArray);

#endif//UTILS_H_INCLUDED
