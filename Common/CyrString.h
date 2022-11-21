#if !defined(CYRSTRING_H_INCLUDED)
#define CYRSTRING_H_INCLUDED

#define	MAX_SARRAY	16

int  CyrCompare(LPCTSTR s1, LPCTSTR s2);
int  DBCompare(LPCTSTR sz1, LPCTSTR sz2);
int  DBFind(LPCTSTR szWhere, LPCTSTR szSubstring);
void ReplaceIgnoreCase(CString& szWhere, LPCTSTR szWhat, LPCTSTR szReplace);

class CCyrString : public CString {
public:
// Constructors
  CCyrString();
  CCyrString(LPCSTR lpsz);
public:
  void    Trim();
  void    MakeUpperFirstChar();
  void    MakeUpperWords();
  void    MakeLower();
  void    MakeUpper();
  void    MakeCanonical();
  CString GetKeyLetters();
};

void    MakeLower(TCHAR *sz);
CString UpperString(const CString& s);
CString LowerString(const CString& s);
CString LatinToCyr(const CString& s);
CString MakeCanonicalName(LPCTSTR szString);
//
// Uppers flags
//
#define	UF_NONE				0
#define	UF_FIRSTCHAR	1
#define	UF_ALLWORDS		2

CString GetTok(const char* szSrc, int nTok, const char* sep);
void    FillTokenArray(const char* szSrc, CStringArray& tokens);

CString GetTokSpace(const char* szSrc, int nTok);
CString FindAndReplace(const CString& s, const char* szFind, const char* szReplace, bool fAll=false);
CString Trim(LPCTSTR lpsz);

// int   CalcFirstSpaces(const CString& s);

BOOL  IsCyrChar(TCHAR c);
BOOL  IsCyrString(LPCTSTR szString);
BOOL  IsCyrLower(TCHAR c);
BOOL  IsCyrLower(LPCTSTR szString);
BOOL  IsCyrUpper(TCHAR c);
BOOL  IsCyrUpper(LPCTSTR szString);
TCHAR CyrUpper(unsigned char tc);
TCHAR CyrLower(unsigned char tc);
BOOL  IsDelim(TCHAR tc);

bool IsDigit(TCHAR c);
bool IsDigit(const CString& s);
bool IsEmptyText(LPCTSTR szText);
void TrimRight(CString& s, LPCTSTR szSubstring);

int     CyrStriCmp(LPCTSTR s1, LPCTSTR s2);
bool    CyrInStr(LPCTSTR szStr, LPCTSTR szSubStr);
CString GetTokenBefore(const CString& s, int offset);
CString GetFullBracketString(const CString& src, LPCTSTR szKey);
CString GetBracketString(const CString& src, LPCTSTR szKey);
void    MakeBracketString(CString& src, LPCTSTR szKey, LPCTSTR szValue);
void    MakeBracketString(CString& src, LPCTSTR szKey, CWnd* pWnd);
CString GetSentence(const CString& szSrc, LPCTSTR szBOS, LPCTSTR szEOS=_T("."));
CString GetDateFromStr(LPCTSTR szMemo);
CString GetNumFromStr(LPCTSTR szMemo, LPCTSTR szWhat, bool fAdd=true);
CString GetStringPart(const CString& sFrom, int nLex);

#if defined(_ERAGS) || defined(_ERAREG)
CString Pad(LPCTSTR sz, TCHAR cPad, int len);
CString RegCrypt(const CString& szPwd, const CString& szAddler, BOOL fAdd);
#endif

#endif //CYRSTRING_H_INCLUDED