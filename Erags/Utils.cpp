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

CString GetDateFromStr(LPCTSTR szMemo) {
  CString s = GetSentence(szMemo, _T("â³ä "), _T("ð."));
  if ( false==s.IsEmpty() ) {
    s.Replace(_T("â³ä "), _T(""));
  }
  return s;
}
CString GetNumFromStr(LPCTSTR szMemo, LPCTSTR szWhat, bool fAdd/*=true*/) {
  CString sRet;
  CString sMemo = Trim(szMemo);
  int nLen = sMemo.GetLength();
  int nFound(-1);

  if ( szWhat ) {
    nFound = sMemo.Find(szWhat);
    if ( -1==nFound )
      return sRet;
  }

  // At first find any digit
  while( ++nFound < nLen ) {
    TCHAR c = sMemo.GetAt(nFound);
    if ( '0'<=c && c <='9' )
      break;
  }
  while( nFound < nLen ) {
    TCHAR c = sMemo.GetAt(nFound);
    if ( '-'== c || ('0'<=c && c <='9') ) {
      sRet += c;
    }
    else
      break;
    nFound++;
  }

  if ( sRet.IsEmpty() )
    return sRet;

  if ( fAdd ) {
    for( int i=sRet.GetLength()-1; i >= 0; i-- ) {
      TCHAR c = sRet.GetAt(i);
      if ( '9'==c ) {
        sRet.SetAt(i, '0');
        continue;
      }
      else if ( '0'<=c && c <='8' ) {
        sRet.SetAt(i, ++c);
      }
      break;
    }
  }
  return sRet;
}

CString GetNumFromStr(CDaoRecordset* pSet, LPCTSTR szFieldName, LPCTSTR szWhat, bool fAdd/*=true*/) {
  CString sNewNumber;
  try {
    COleVariant bm = pSet->GetBookmark();
    pSet->MovePrev();
    while( !pSet->IsBOF() ) {
      CString s = GetFieldString(pSet, szFieldName);
      if ( !s.IsEmpty() ) {
        sNewNumber = GetNumFromStr(s, szWhat, fAdd);
        if ( !sNewNumber.IsEmpty() )
          break;
      }
      pSet->MovePrev();
    }
    pSet->SetBookmark(bm);
  }

  catch(CDaoException* e) {
    e->Delete();
  }

  if ( sNewNumber.IsEmpty() )
    sNewNumber = _T("1");
  return sNewNumber;  
}
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

int GetIndexOf(DWORD dwValue, const CDWordArray* pArray) {
  for( int i(0); i < pArray->GetSize(); i++ ) {
    if ( dwValue==pArray->GetAt(i) )
      return i;
  }
  return -1;
}