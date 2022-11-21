// XCnv.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "XCnv.h"

#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define B_KEYWORD '!'
#define E_KEYWORD '!'

BOOL  g_fRTFConvert = true;

CONVERT_TYPE g_ConvertType = CNV_NONE;

void UTF8ToWin1251(CString& str) {
  g_ConvertType = CNV_ODT;
  int wbuflen = MultiByteToWideChar(CP_UTF8, 0, str, -1, 0, 0);
  WCHAR * wbuf = new WCHAR[wbuflen];
  MultiByteToWideChar(CP_UTF8, 0, str, -1, wbuf, wbuflen);
  int buflen = WideCharToMultiByte(1251, 0, wbuf, -1, 0, 0, NULL, NULL);
  char * buf = new char[buflen];
  WideCharToMultiByte(1251, 0, wbuf, -1, buf, buflen, NULL, NULL);
  delete [] wbuf;
  while ( buflen && buf[buflen-1]==0 ) buflen--;
  str = CString(buf, buflen);
  delete buf;
}

void Win1251ToUTF8(CString& str) {
  int wbuflen = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
  WCHAR * wbuf = new WCHAR[wbuflen];
  MultiByteToWideChar(1251, 0, str, -1, wbuf, wbuflen);
  int buflen = WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, 0, 0, NULL, NULL);
  char * buf = new char[buflen];
  WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, buf, buflen, NULL, NULL);
  delete [] wbuf;
  while ( buflen && buf[buflen-1]==0 ) buflen--;
  str = CString(buf, buflen);
  delete buf;
}

int HexVal(char c) {
	if (isupper (c))
		c = tolower (c);
	if (isdigit (c))
		return (c - '0');	/* '0'..'9' */
	return (c - 'a' + 10);		/* 'a'..'f' */
}

CString RTFToWin1251(LPCTSTR szRTF) {
  CString s;
  g_ConvertType = CNV_RTF;
  while( *szRTF ) {
    if ( !isalpha(*szRTF) ) {
      if ( strncmp(szRTF, "\\\'",2)==0 && isalpha(szRTF[2]) ) {  // "\'" cyrillic letter
        unsigned char c = HexVal(szRTF[2]) * 16 + HexVal(szRTF[3]);
        s += c;
        szRTF += 4;
        continue;
      }
    }
    s += *szRTF++;
  }
  return s;
}
CString Win1251ToRTF(LPCTSTR sz) {
  CString s;
  char szRTFChar[8];
  while ( *sz ) {
    if ( (unsigned char)*sz >= 128 ) {
      sprintf(szRTFChar, "\\\'%02x", (unsigned char)*sz);
      s += szRTFChar;
      sz++;
      continue;
    }
    s += *sz++;
  }
  return s;
}

void Win1251ToRTF(CFile& f, LPCTSTR sz) {
  char szRTFChar[8];
  while ( *sz ) {
    if ( (unsigned char)*sz >= 128 ) {
      sprintf(szRTFChar, "\\\'%02x", (unsigned char)*sz);
      f.Write(szRTFChar, 4);
    }
    else {
      f.Write(sz, 1);
    }
    sz++;
  }
}

/////////////////////////////////////////////////////////////////////////////
// CXCnv
CXCnv::CXCnv() {
  m_tcKeywordB = B_KEYWORD;
  m_tcKeywordE = E_KEYWORD;
  m_fError = 0;
  m_Cnv = CNV_ODT;
}
CXCnv::~CXCnv() {
}
void CXCnv::SetWorkFile(LPCTSTR szFilename) {
  m_szFilename = szFilename;
}
BOOL CXCnv::Read() {
  return ReadContent();
}
BOOL CXCnv::Read(LPCTSTR szFilename) {
  SetWorkFile(szFilename);
  return Read();
}
BOOL CXCnv::Write() {
  return WriteContent();
}
BOOL CXCnv::Write(LPCTSTR szFilename) {
  SetWorkFile(szFilename);
  return Write();
}
CString CXCnv::GetRow(LPCTSTR pszKeyB, LPCTSTR pszKeyE) {
  CString szRow;
  CString szKeyB, szKeyE;
  szKeyB.Format(_T("%c%s%c"), m_tcKeywordB, pszKeyB, m_tcKeywordE);
  szKeyE.Format(_T("%c%s%c"), m_tcKeywordB, pszKeyE, m_tcKeywordE);
  switch( m_Cnv ) {
    case  CNV_ODT:
      Win1251ToUTF8(szKeyB);
      Win1251ToUTF8(szKeyE);
      break;
  }
  int nFind1, nFind2;
  nFind1 = m_szContent.Find(szKeyB, 0);
  if ( nFind1 >= 0 ) {
    if ( CNV_RTF==m_Cnv ) {
      while ( m_szContent[nFind1] != '}' ) nFind1++;
      nFind1++;
    }
    nFind2 = m_szContent.Find(szKeyE, nFind1);
    if ( nFind2 >= 0 ) {
      if ( CNV_RTF==m_Cnv ) {
        while ( m_szContent[nFind2] != '{' ) nFind2--;
        nFind2--;
      }
      szRow = m_szContent.Mid(nFind1, nFind2-nFind1+1);
      switch( m_Cnv ) {
        case  CNV_ODT:
          UTF8ToWin1251(szRow);
          break;
      }
    }
  }
  return szRow;
}

CString CXCnv::GetKeyword(LPCTSTR pszKeyword) {
  CString szKeyword(pszKeyword);
  szKeyword.Remove('\r');
  szKeyword.Remove('\n');

  if ( CNV_RTF==m_Cnv ) {
    szKeyword.Replace("\\loch\\f0 ", "");
    szKeyword.Replace("\\hich\\f0 ", "");
  }

  szKeyword.TrimLeft(m_tcKeywordB);
  szKeyword.TrimRight(m_tcKeywordE);
  return szKeyword;
}

void CXCnv::ReplaceEOLForOO(CString& szReplace, int nKeywordB) {
  int nEOL = szReplace.Find(_T("\r\n"));
  if ( nEOL >= 0 ) {
    int nBegin = nKeywordB;
    while ( --nBegin > 0 ) {
      char c = m_szContent[nBegin];
      if ( c=='<' ) {
        CString szPar = m_szContent.Mid(nBegin, 7);
        if ( szPar != _T("<text:p") ) {
          continue;
        }
        int nEnd = m_szContent.Find('>', nBegin);
        if ( nEnd > nBegin) {
          CString szOOEOL;
          szOOEOL.Format(_T("</text:p>%s"), m_szContent.Mid(nBegin, nEnd-nBegin+1));
          szReplace.Replace(_T("\r\n"), szOOEOL);
        }
        break;
      }
    }
  }
}

void CXCnv::ReplaceSpacesForOO(CString& szReplace) {
  int nFound = szReplace.Find(_T("  "));
  int nCount = 0;
  if ( nFound >= 0) {
    while ( szReplace[nFound++] == ' ') {
      nCount++;
    }
    CString sOOSpaces, sOldOSpaces(' ', nCount);
    sOOSpaces.Format(_T(" <text:s text:c=\"%d\"/>"), nCount);
    szReplace.Replace(sOldOSpaces, sOOSpaces);
  }
}

void CXCnv::ReplaceContent(void (*OnKeyword)(LPCTSTR szKeyword, CString& szReplace, DWORD dwData), DWORD dwData, BOOL fReplaceIfEmpty) {
  int nKeywordB = 0;
  int nKeywordE = 0;
  int nStart    = 0;
  while ( true ) {
    nKeywordB = m_szContent.Find(m_tcKeywordB, nStart);
    if ( -1==nKeywordB ) {
      break;
    }
    nKeywordE = m_szContent.Find(m_tcKeywordE, nKeywordB+1);
    if ( -1==nKeywordE ) {
      break;
    }
    int nKeylen = nKeywordE-nKeywordB+1;
    CString szKeyword;
    switch( m_Cnv ) {
      case  CNV_ODT:
        szKeyword = m_szContent.Mid(nKeywordB, nKeylen);
        UTF8ToWin1251(szKeyword);
        break;
      default:
        szKeyword = m_szContent.Mid(nKeywordB, nKeylen);
        break;
    }
    CString szReplace;
    OnKeyword(GetKeyword(szKeyword), szReplace, dwData);
    if ( fReplaceIfEmpty || false==szReplace.IsEmpty() ) {
      if ( CNV_ODT==m_Cnv ) {
        ReplaceEOLForOO(szReplace, nKeywordB);
        ReplaceSpacesForOO(szReplace);
      }
      m_szContent.Delete(nKeywordB, nKeylen);
      switch( m_Cnv ) {
        case  CNV_ODT:
          Win1251ToUTF8(szReplace);
          break;
      }
      m_szContent.Insert(nKeywordB, szReplace);
    }
    //nStart = nKeywordE+1;
    nStart = nKeywordB+szReplace.GetLength()+1;
  }
}

void CXCnv::ReplaceRow(CString& szRow, void (*OnKeyword)(LPCTSTR szKeyword, CString& szReplace, DWORD dwData), DWORD dwData) {
  int nKeywordB = 0;
  int nKeywordE = 0;
  int nStart    = 0;
  while ( true ) {
    nKeywordB = szRow.Find(m_tcKeywordB, nStart);
    if ( -1==nKeywordB ) {
      break;
    }
    nKeywordE = szRow.Find(m_tcKeywordE, nKeywordB+1);
    if ( -1==nKeywordE ) {
      break;
    }
    int nKeylen = nKeywordE-nKeywordB+1;
    CString szKeyword;
    switch( m_Cnv ) {
      case  CNV_ODT:
        szKeyword = szRow.Mid(nKeywordB, nKeylen);
        UTF8ToWin1251(szKeyword);
        break;
      default:
        szKeyword = szRow.Mid(nKeywordB, nKeylen);
        break;
    }
    CString szReplace;
    OnKeyword(GetKeyword(szKeyword), szReplace, dwData);
    szRow.Delete(nKeywordB, nKeylen);
    switch( m_Cnv ) {
      case  CNV_ODT:
        Win1251ToUTF8(szReplace);
        break;
    }
    szRow.Insert(nKeywordB, szReplace);
    nStart = nKeywordB+szReplace.GetLength()+1;
  }
}
CString CXCnv::EncodeRow(const CString& szRow, void (*OnKeyword)(LPCTSTR szKeyword, CString& szReplace, DWORD dwData), DWORD dwData) {
  CString szEncodedRow = szRow;
  ReplaceRow(szEncodedRow, OnKeyword, dwData);
  return szEncodedRow;
}
/////////////////////////////////////////////////////////////////////////////
// CODTCnv
CODTCnv::CODTCnv() {
  m_wCntIndex = (WORD)-1;
  m_fError = 0;
  m_Cnv = CNV_ODT;
}

CODTCnv::~CODTCnv() {
  if ( false==m_za.IsClosed() ) {
    m_za.Close();
  }
}

BOOL CODTCnv::ReadContent() {
  BOOL fOk = true;
  m_fError = false;
  try {
    m_za.Open(m_szFilename, CZipArchive::zipOpen);
  }
  catch(...) {
    fOk = false;
  }
  if ( fOk ) {
    int nCount = m_za.GetCount();
    CZipString zsFileName;
    CZipFileHeader zh;
    BOOL bFound = false;

    for( int i(0); i < nCount; i++ ) {
      m_za.GetFileInfo(zh, (WORD)i);
      zsFileName = zh.GetFileName();
      if ( stricmp(zsFileName, "content.xml")==0 ) {
        bFound = true;
        m_wCntIndex = (WORD)i;
        break;
      }
    }
    fOk = bFound;
  }
  if ( fOk ) {
    CZipMemFile zmf;
    if ( m_za.ExtractFile(m_wCntIndex, zmf) ) {
      int nLen = (int)zmf.GetLength();
      BYTE* pBuffer = zmf.Detach();
      m_szContent = CString((char*)pBuffer, nLen);
      delete pBuffer;
    }
    else {
      fOk = false;
      m_fError = true;
    }
  }
  m_fError = !fOk;
  return fOk;
}

BOOL CODTCnv::WriteContent() {
  if ( m_fError ) {
    return false;
  }
  // Win1251ToUTF8(m_szContent);
  BOOL fOk = true;
  CZipMemFile zmf;
  zmf.Write((LPCTSTR)m_szContent, m_szContent.GetLength());

  if ( m_wCntIndex != (WORD)-1 ) {
    try {
      m_za.DeleteFile(m_wCntIndex);
      m_za.AddNewFile(zmf, "content.xml");
    }
    catch(...) {
      fOk = false;
    }
  }
  m_za.Close();
  
  return fOk;
}

void CODTCnv::InsertUnderlineStyle() {
  LPCTSTR szUnd = _T("<style:style style:name=\"Underline\" style:family=\"text\"><style:text-properties style:text-underline-style=\"solid\" style:text-underline-width=\"auto\" style:text-underline-color=\"font-color\"/></style:style>");
  int lFind = m_szContent.Find("<style:style style:name=", 0);
  if ( lFind >= 0 ) {
    m_szContent.Insert(lFind, szUnd);
  }
}

/////////////////////////////////////////////////////////////////////////////
// CRTFCnv
CRTFCnv::CRTFCnv() {
  m_fError = 0;
  m_Cnv = CNV_RTF;
}

CRTFCnv::~CRTFCnv() {
}

BOOL CRTFCnv::ReadContent() {
  BOOL fOk = true;
  m_fError = false;
  if ( false==m_rtf.Open(m_szFilename, CFile::modeRead|CFile::shareDenyWrite) ) {
    m_dwError = GetLastError();
    fOk = false;
  }
  if ( fOk ) {
    DWORD dwLen = m_rtf.GetLength();
    BYTE* pBuffer = new BYTE[dwLen+1];
    m_rtf.Read(pBuffer, dwLen);
    pBuffer[dwLen] = 0;
    m_szContent = RTFToWin1251((LPCTSTR)pBuffer);
    delete pBuffer;
    m_rtf.Close();
  }
  m_fError = !fOk;
  return fOk;
}

BOOL CRTFCnv::WriteContent() {
  if ( m_fError ) {
    return false;
  }
  if ( m_rtf.Open(m_szFilename, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) ) {
    if ( g_fRTFConvert ) {
      Win1251ToRTF(m_rtf, m_szContent);
    }
    else {
      m_rtf.Write((LPCTSTR)m_szContent, m_szContent.GetLength());
    }
    m_rtf.Close();
  }
  else {
    return false;
  }
  
  return true;
}

/////////////////////////////////////////////////////////////////////////////
// CUCnv
CUCnv::CUCnv() {
  m_cnvFormat = CNV_FORMAT_UNK; // Default format is unknown
}
CUCnv::~CUCnv() {
}

BOOL CUCnv::Copy(LPCTSTR szIn, LPCTSTR szOut) {
  if ( false==FileExists(szIn, NULL) ) {
    ErrorBox(_T("Файл шаблону \"%s\" відсутній.\nСпробуйте відновити файл шаблону або переустановити ПК ЕРАГС."), szIn);
    return false;
  }
  if ( false==CopyFile(szIn, szOut, false) ) {
    DWORD dwError = GetLastError();
    ErrorBox(_T("Помилка при спробі створити файл \"%s\".\n")
             _T("Можливо, цей файл вже відкритий іншою програмою.\n")
             _T("Системна помилка %d(0x%04X): %s."),
             szOut, dwError, dwError, FormatError(dwError));
    return false;
  }
  return true;
}

BOOL CUCnv::ReadContent() {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  return m_odtCnv.ReadContent();
    case CNV_FORMAT_RTF:  return m_rtfCnv.ReadContent();
  }
  return false;
}
BOOL CUCnv::WriteContent() {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  return m_odtCnv.WriteContent();
    case CNV_FORMAT_RTF:  return m_rtfCnv.WriteContent();
  }
  return false;
}

BOOL CUCnv::IsError() {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  return m_odtCnv.IsError();
    case CNV_FORMAT_RTF:  return m_rtfCnv.IsError();
  }
  return true;
}

CString CUCnv::GetData() {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  return m_odtCnv.GetData();
    case CNV_FORMAT_RTF:  return m_rtfCnv.GetData();
  }
  return _T("CUCnv::GetData");
}
void CUCnv::SetData(const CString& szData) {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  m_odtCnv.SetData(szData);
    case CNV_FORMAT_RTF:  m_rtfCnv.SetData(szData);
  }
}

void CUCnv::SetWorkFile(LPCTSTR szFilename) {
  CString sFilename(szFilename);
  if ( sFilename.Right(4).CompareNoCase(".odt")==0 ) {
    m_cnvFormat = CNV_FORMAT_ODT;
  }
  else if ( sFilename.Right(4).CompareNoCase(".rtf")==0 ) {
    m_cnvFormat = CNV_FORMAT_RTF;
  }
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  m_odtCnv.SetWorkFile(szFilename); break;
    case CNV_FORMAT_RTF:  m_rtfCnv.SetWorkFile(szFilename); break;
  }
}
BOOL CUCnv::Read() {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  return m_odtCnv.Read();
    case CNV_FORMAT_RTF:  return m_rtfCnv.Read();
  }
  return false;
}
BOOL CUCnv::Read(LPCTSTR szFilename) {
  SetWorkFile(szFilename);
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  return m_odtCnv.Read(szFilename);
    case CNV_FORMAT_RTF:  return m_rtfCnv.Read(szFilename);
  }
  return false;
}
void CUCnv::InsertUnderlineStyle() {
  if ( CNV_FORMAT_ODT==m_cnvFormat ) {
    m_odtCnv.InsertUnderlineStyle();
  }
}
BOOL CUCnv::Write() {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  return m_odtCnv.Write();
    case CNV_FORMAT_RTF:  return m_rtfCnv.Write();
  }
  return false;
}
BOOL CUCnv::Write(LPCTSTR szFilename) {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  return m_odtCnv.Write(szFilename);
    case CNV_FORMAT_RTF:  return m_rtfCnv.Write(szFilename);
  }
  return false;
}
CString CUCnv::GetRow(LPCTSTR pszKeyB, LPCTSTR pszKeyE) {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  return m_odtCnv.GetRow(pszKeyB, pszKeyE);
    case CNV_FORMAT_RTF:  return m_rtfCnv.GetRow(pszKeyB, pszKeyE);
  }
  return _T("CUCnv::GetRow");
}
CString CUCnv::GetKeyword(LPCTSTR pszKeyword) {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  return m_odtCnv.GetKeyword(pszKeyword);
    case CNV_FORMAT_RTF:  return m_rtfCnv.GetKeyword(pszKeyword);
  }
  return _T("CUCnv::GetKeyword");
}
void CUCnv::ReplaceContent(void (*OnKeyword)(LPCTSTR szKeyword, CString& szReplace, DWORD dwData), DWORD dwData, BOOL fReplaceIfEmpty) {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  m_odtCnv.ReplaceContent(OnKeyword, dwData, fReplaceIfEmpty);
    case CNV_FORMAT_RTF:  m_rtfCnv.ReplaceContent(OnKeyword, dwData, fReplaceIfEmpty);
  }
}
void CUCnv::ReplaceRow(CString& szRow, void (*OnKeyword)(LPCTSTR szKeyword, CString& szReplace, DWORD dwData), DWORD dwData) {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  m_odtCnv.ReplaceRow(szRow, OnKeyword, dwData);
    case CNV_FORMAT_RTF:  m_rtfCnv.ReplaceRow(szRow, OnKeyword, dwData);
  }
}
CString CUCnv::EncodeRow(const CString& szRow, void (*OnKeyword)(LPCTSTR szKeyword, CString& szReplace, DWORD dwData), DWORD dwData) {
  switch( m_cnvFormat ) {
    case CNV_FORMAT_ODT:  return m_odtCnv.EncodeRow(szRow, OnKeyword, dwData);
    case CNV_FORMAT_RTF:  return m_rtfCnv.EncodeRow(szRow, OnKeyword, dwData);
  }
  return _T("CUCnv::EncodeRow");
}
