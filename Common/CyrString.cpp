//
// CyrString.cpp
//
#include "stdafx.h"

#include "CyrString.h"
//#include "MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString sArray[MAX_SARRAY];

static const TCHAR szCyrChars[] = _T("'’ÀÁÂÃ¥ÄÅªÆÇÈ²¯É¨ÊËÌÍÎÏĞÑÒÓÔÕÖ×ÚØÙÛÜİŞßàáâã´äåºæçè³¿é¸êëìíîïğñòóôõö÷úøùûüışÿ");
static const TCHAR szCyrUpper[] = _T("'’ÀÁÂÃ¥ÄÅªÆÇÈ²¯É¨ÊËÌÍÎÏĞÑÒÓÔÕÖ×ÚØÙÛÜİŞß");
static const TCHAR szCyrLower[] = _T("'’àáâã´äåºæçè³¿é¸êëìíîïğñòóôõö÷úøùûüışÿ");
static const TCHAR szDelim[]    = _T("~!%^&*()-+\\{}[];:<>.,?/ ");

int GetCyrIndex(TCHAR c) {
  for( int i= 0; i < sizeof(szCyrChars); i++) {
    if ( szCyrChars[i]==c )
      return i;
  }
  return -1;
}

int CyrCompare(LPCTSTR s1, LPCTSTR s2) {
  while( *s1 && *s2 ) {
    if ( *s1 != *s2 ) {
      int ind1 = GetCyrIndex(*s1);
      if ( ind1 == -1 ) break;
      int ind2 = GetCyrIndex(*s2);
      if ( ind2 == -1 ) break;
      return (ind1-ind2);
    }
    s1++; s2++;
  }
  return ((unsigned char)*s1 - (unsigned char)*s2);
}
int DBCompare(LPCTSTR sz1, LPCTSTR sz2) {
  CCyrString s1 = sz1;
  CCyrString s2 = sz2;
  s1.Replace(_T(" "), _T(""));
  s2.Replace(_T(" "), _T(""));
  s1.MakeLower();
  s2.MakeLower();
  return s1.Compare(s2);
}

int DBFind(LPCTSTR szWhere, LPCTSTR szSubstring) {
  CCyrString s1 = szWhere;
  CCyrString s2 = szSubstring;
  s1.Replace(_T(" "), _T(""));
  s2.Replace(_T(" "), _T(""));
  s1.MakeLower();
  s2.MakeLower();
  return s1.Find(s2);
}
void ReplaceIgnoreCase(CString& szWhere, LPCTSTR szWhat, LPCTSTR szReplace) {
  CCyrString s1 = szWhere;
  CCyrString s2 = szWhat;
  s1.MakeLower();
  s2.MakeLower();
  int nFound = s1.Find(s2);
  if ( nFound >= 0 ) {
    CString szRes;
    if ( nFound > 0 ) {
      szRes = szWhere.Mid(0, nFound);
    }
    szRes += szReplace;
    szRes += szWhere.Mid(nFound+strlen(szWhat));
    szWhere = szRes;
  }
}
CString GetTok(const char* szSrc, int nTok, const char* sep) {
  CString sRet(_T(""));
  if( szSrc!=NULL && szSrc[0]!=0) {
    char* szString = new char[strlen(szSrc)+1];
    char* pTok;
    strcpy(szString, szSrc);
    pTok = strtok(szString, sep);
    for( int i(0); i < nTok; i++ ) {
      if ( pTok==NULL )
        break;
      pTok = strtok(NULL, sep);
    }
    if( pTok )
      sRet = pTok;
    delete szString;
  }
  return sRet;
}
void FillTokenArray(const char* szSrc, CStringArray& tokens) {
  CString s(szSrc), sToken;
  for( int i(0); i < s.GetLength(); i++ ) {
    TCHAR c = s[i];
    if ( IsDelim(c) ) {
      if ( FALSE==sToken.IsEmpty() ) {
        tokens.Add( sToken );
        sToken.Empty();
        continue;
      }
      tokens.Add( CString(c) );
    }
    else {
      sToken += c;
    }
  }
  if ( FALSE==sToken.IsEmpty() ) {
    tokens.Add( sToken );
  }
}

CString GetTokSpace(const char* szSrc, int nTok) {
  return GetTok(szSrc, nTok, _T(" \t\r\n"));
}

CString Trim(LPCTSTR lpsz) {
  CString s = lpsz;
	s.TrimLeft();
	s.TrimRight();
	return s;
}

/*
int CalcFirstSpaces(const CString& s) {
  int i, nLen = s.GetLength();
  for( i = 0; i < nLen; i++ ) {
    if ( s.GetAt(i) != TCHAR(' ') )
      break;
  }
  return i;
}
*/

BOOL IsDelim(TCHAR tc) {
	for(int i(0); i < sizeof(szDelim); i++)
		if(tc==szDelim[i])
			return true;
	return false;
}

BOOL IsCyrLower(TCHAR c) {
  return (strchr(szCyrLower, c) != NULL);
}
BOOL  IsCyrLower(LPCTSTR szString) {
  int nLen = strlen(szString);
  for( int i(0); i < nLen; i++ ) {
    if ( IsCyrUpper( szString[i] ) )
      return FALSE;
  }
  return TRUE;
}
BOOL IsCyrUpper(TCHAR c) {
  return (strchr(szCyrUpper, c) != NULL);
}
BOOL IsCyrUpper(LPCTSTR szString) {
  int nLen = strlen(szString);
  for( int i(0); i < nLen; i++ ) {
    if ( IsCyrLower( szString[i] ) )
      return FALSE;
  }
  return TRUE;
}

BOOL IsCyrChar(TCHAR c) {
  return IsCyrLower(c) || IsCyrUpper(c);
}
BOOL IsCyrString(LPCTSTR szString) {
  if ( NULL==szString ) {
    return false;
  }
  while ( *szString ) {
    if ( IsCyrChar(*szString) ) {
      return true;
    }
    szString++;
  }
  return false;
}

TCHAR CyrUpper(unsigned char tc) {
  if ( (unsigned char)'À' <= tc && tc <= (unsigned char)'ß') {
    return tc;
  }
  for(int i(0); i < sizeof(szCyrLower); i++) {
		if(tc==(unsigned char)szCyrLower[i]) return szCyrUpper[i];
  }
	return (TCHAR)toupper((unsigned char)tc);
}
TCHAR CyrLower(unsigned char tc) {
  if ( (unsigned char)'à' <= tc && tc <= (unsigned char)'ÿ') {
    return tc;
  }
	for(int i(0); i < sizeof(szCyrUpper); i++)
		if(tc==(unsigned char)szCyrUpper[i])
			return szCyrLower[i];
	return (TCHAR)tolower(tc);
}

bool IsDigit(TCHAR c) {
  return (c>='0' && c<='9');
}
bool IsDigit(const CString& s) {
  if ( s.IsEmpty() )
    return false;
  for( int i(0); i < s.GetLength(); i++ ) {
    if ( false==IsDigit(s[i]) )
      return false;
  }
  return true;
}

bool IsEmptyText(LPCTSTR szText) {
  CString s = Trim(szText);
  return s.IsEmpty() ? true : false;
}

void TrimRight(CString& s, LPCTSTR szSubstring) {
  CString sz(szSubstring);
  int nslen = s.GetLength();
  int nsublen = sz.GetLength();
  if ( nslen >=nsublen ) {
    while ( s.Right(nsublen)==sz ) {
      s = s.Left(nslen-nsublen);
      nslen = s.GetLength();
    }
  }
}

/////////////////////
// CCyrString
CCyrString::CCyrString():CString(){}
CCyrString::CCyrString(LPCSTR lpsz):CString(lpsz) {}

void CCyrString::Trim() {
  TrimLeft();
  TrimRight();
}

void CCyrString::MakeUpperFirstChar() {
  if( GetLength() )
    SetAt( 0,CyrUpper( GetAt(0) ) );
}

void CCyrString::MakeUpperWords() {
int iLen(GetLength());
BOOL bWord(TRUE);
	for(int i(0); i < iLen; i++) {
		if( IsDelim( GetAt(i) ) )
      bWord = TRUE;
		else if(bWord){
			SetAt( i, CyrUpper(GetAt(i)) );
			bWord = FALSE;
		}
	}
}
void CCyrString::MakeLower() {
  int iLen(GetLength());
	for(int i(0); i < iLen; i++)
    SetAt( i, CyrLower(GetAt(i)) );
}
void CCyrString::MakeUpper(){
int iLen(GetLength());
	for(int i(0); i < iLen; i++)
    SetAt( i, CyrUpper(GetAt(i)) );
}

void CCyrString::MakeCanonical() {
  MakeLower();
  MakeUpperWords();
  if ( GetLength() > 2 && Left(2)==_T("Ì.") ) {
    SetAt(0, TCHAR('ì'));
  }
}
CString CCyrString::GetKeyLetters() {
  static const TCHAR* szKeyLetters = _T("ÁÂÃÄÆÇÉÊËÌÍÏĞÑÒÔÕÖ×ØÙÜ");
  MakeUpper();
  CString s, szKey = szKeyLetters;
  for( int i(0); i < GetLength(); i++ ) {
    TCHAR c = GetAt(i);
    if ( szKey.Find(c, 0) >= 0 )
      s += c;
  }
  return s;
}

CString UpperWords(LPCTSTR szString){
  CString s = szString;
  int iLen(s.GetLength());
  BOOL bWord(TRUE);

	for(int i(0); i < iLen; i++){
		if(IsDelim(s[i]))
				bWord = TRUE;
		else if(bWord){
				s.SetAt(i,CyrUpper(s[i]));
				bWord = FALSE;
		}
	}
	return s;
}

void MakeLower(TCHAR *sz) {
  if ( NULL==sz ) {
    return;
  }
  while ( *sz ) {
    *sz++ = CyrLower(*sz);
  }
}
CString UpperString(const CString& s) {
  CCyrString sCyrString(s);
  sCyrString.MakeUpper();
  return sCyrString;
}
CString LowerString(const CString& s) {
  CCyrString sCyrString(s);
  sCyrString.MakeLower();
  return sCyrString;
}
CString LatinToCyr(const CString& s) {
  CString sRet = s;
  sRet.Replace('a', 'à'); sRet.Replace('A', 'à');
                          sRet.Replace('B', 'Â');
  sRet.Replace('c', 'ñ'); sRet.Replace('C', 'Ñ');
  sRet.Replace('e', 'å'); sRet.Replace('E', 'Å');
  sRet.Replace('i', '³'); sRet.Replace('I', '²');
  sRet.Replace('o', 'î'); sRet.Replace('O', 'Î');
                          sRet.Replace('H', 'Í');
                          sRet.Replace('M', 'Ì');
  sRet.Replace('k', 'ê'); sRet.Replace('K', 'Ê');
  sRet.Replace('p', 'ğ'); sRet.Replace('P', 'Ğ');
                          sRet.Replace('T', 'Ò');
  sRet.Replace('x', 'õ'); sRet.Replace('X', 'Õ');
  return sRet;
}

CString MakeCanonicalName(LPCTSTR szString) {
  CString s = szString;
  s = LowerString(s);
  s = UpperWords(s);
  return s;
}

int CyrStriCmp(LPCTSTR s1, LPCTSTR s2) {
  int iLen1 = lstrlen(s1),
      iLen2 = lstrlen(s2);

  if(iLen1 > iLen2)
    return s1[iLen2];
  else if(iLen1 < iLen2)
    return s2[iLen1];

  for(int i(0); i < iLen1; i++){
    TCHAR t1 = CyrUpper(s1[i]),
          t2 = CyrUpper(s2[i]);
    if(t1 != t2)
      return (s1[i]-s2[i]);
  }
  return 0;
}

bool CyrInStr(LPCTSTR szStr, LPCTSTR szSubStr) {
  CString str    = UpperString(szStr),
          subStr = UpperString(szSubStr);
  return (str.Find(subStr, 0)==-1) ? false : true;
}

CString FindAndReplace(const CString& s, const char* szFind, const char* szReplace, bool fAll/*=false*/) {
  CString sRet = s;
  int iFound(0), nFrom(0);

  while( iFound != -1 ) {
    iFound = sRet.Find(szFind, nFrom);
    if( iFound != -1 ) {
      nFrom = iFound + strlen(szReplace);
      sRet.Replace(szFind, szReplace);
      if ( false==fAll )
        break;
    }
  }
  return sRet;
}

/*
void InitSArray(){
	for(int i(0); i < MAX_SARRAY; i++)
		sArray[i] = _T("");
}
extern "C" DWORD PASCAL EXPORT GetLenFSA(UINT ind){
	return sArray[ind].GetLength();
}

extern "C" DWORD PASCAL EXPORT FromSArray(LPTSTR& szDest,
																			   DWORD cbLen,
																			   UINT ind){
DWORD uLen = sArray[ind].GetLength();
	if(uLen < cbLen)
		cbLen = uLen;
	memcpy(szDest, sArray[ind], cbLen);
	return cbLen;
}
*/

CString GetTokenBefore(const CString& s, int offset) {
  CString sToken;
  while ( offset >= 0 ) {
    sToken = s.Mid(offset);
    if ( sToken.GetLength() && (sToken.GetAt(0)==' ' || sToken.GetAt(0)=='.') ) {
      sToken.TrimLeft('.');
      sToken.TrimLeft(' ');
      return GetTok(sToken, 0, " ");
    }
    offset--;
  }
  sToken.TrimLeft('.');
  sToken.TrimLeft(' ');
  return GetTok(sToken, 0, " ");
}

CString GetFullBracketString(const CString& src, LPCTSTR szKey) {
  CString s;
  int iFound = src.Find(szKey, 0);
  if ( iFound >= 0) {
    while( --iFound >= 0 ) {          // Find open '{'
      if ( src.GetAt(iFound)=='{')
        break;
    }
    if ( iFound >= 0 ) {
      while( iFound < src.GetLength() ) {// Find close '}'
        TCHAR c = src.GetAt(iFound);
        s += c;
        if ( '}'==c )
          break;
        iFound++;
      }
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

CString GetDateFromStr(LPCTSTR szMemo) {
  CString s = GetSentence(szMemo, _T("â³ä "), _T("ğ."));
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

#if defined(_ERAGS) || defined(_ERAREG)
CString RegCrypt(const CString& szPwd, const CString& szAddler, BOOL fAdd) {
  CString szRet;
  if ( szPwd.GetLength() != szAddler.GetLength() ) {
    return szAddler;
  }
  for( int i(0); i < szPwd.GetLength(); i++ ) {
    TCHAR c1 = szPwd.GetAt(i)    - '0';
    TCHAR c2 = szAddler.GetAt(i) - '0';
    if ( fAdd ) {
      szRet += (TCHAR)((c1 + c2)%10 + '0');
    }
    else {
      szRet += (TCHAR)((10 + c2 - c1)%10 + '0');
    }
  }
  return szRet;
}
#endif

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

#if defined(_ERAGS) || defined(_ERAREG)
CString Pad(LPCTSTR sz, TCHAR cPad, int len) {
  CString szRet = sz;
  if ( szRet.GetLength() >= len ) {
    return szRet.Left(len);
  }
  while ( szRet.GetLength() < len ) {
    szRet += cPad;
  }
  return szRet;
}
#endif

/*
//
// Sort functions
//
extern "C" void PASCAL EXPORT BSort(){
  if( pSStrings==NULL )
    pSStrings = new CSortStringArray;
}
extern "C" void PASCAL EXPORT ASort(LPCTSTR szDest){
  if( pSStrings )
    pSStrings->Add(szDest);
}
extern "C" void PASCAL EXPORT SSort(){
  if( pSStrings )
    pSStrings->Sort(TRUE);
}
extern "C" LPCTSTR PASCAL EXPORT GSort(SHORT nIndex){
  if( pSStrings )
    pSStrings->GetAt(nIndex);
  return "";
}

extern "C" void PASCAL EXPORT ESort(){
  if( pSStrings ) {
    pSStrings->RemoveAll();
    pSStrings = NULL;
  }
}
*/