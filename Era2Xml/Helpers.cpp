//
// Helpers.cpp
//
#include "stdafx.h"
#include "Helpers.h"
#include "Globals.h"
#include "Dictionaries.h"
#include "db.h"


#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL    g_bWriteEmptyTags = false;
CString g_szXMLHeader     = _T("<?xml version=\"1.0\"?>\r\n");
CString g_szExtSystemId   = _T("123");


CString g_szHelpersMDB;


CString GetIniValue(LPCTSTR szIniFilename, LPCTSTR szSection, LPCTSTR szKeyname, LPCTSTR szDefault) {
  CString s;
  ::GetPrivateProfileString(szSection, szKeyname, szDefault, s.GetBuffer(512), 512, szIniFilename);
  s.ReleaseBuffer();
  return s;
}

void LoadIniValues() {
  CString szIniFile;
  szIniFile.Format(_T("%s\\Era2Xml.ini"), GetModulePath());

  g_szXMLHeader = GetIniValue(szIniFile, _T("Settings"), _T("XMLHeader"), g_szXMLHeader);
  g_szXMLHeader.TrimRight(_T("\r\n"));
  g_szXMLHeader += _T("\r\n");

  g_szExtSystemId = GetIniValue(szIniFile, _T("Settings"), _T("ExtSystemId"), g_szExtSystemId);

  g_szHelpersMDB   = GetIniValue(szIniFile, _T("Settings"), _T("HelpersMDB"), _T(""));

  if ( false==FileExists(g_szHelpersMDB) ) {
    g_szHelpersMDB.Format(_T("%s\\DB\\Helpers.mdb"), GetModulePath());
  }

  g_bWriteEmptyTags = ::GetPrivateProfileInt(_T("Settings"), _T("WriteEmptyTags"), false, szIniFile);

}

BOOL CreateXMLFile(CStdioFile& xml, LPCTSTR szOutFolder, LPCTSTR szFileMask, LPCTSTR szTypeMask,
                   BOOL fPeriod, COleDateTime& odtFrom, COleDateTime& odtTill,
                   long lTableRecs, long lStartRec, long lMaxRecs
                  )
{
  CString szFilename;

  long lFinishRec = lTableRecs;
  if ( lTableRecs > lMaxRecs ) {
    lFinishRec = lStartRec + lMaxRecs - 1;
  }
  if ( lFinishRec > lTableRecs ) {
    lFinishRec = lTableRecs;
  }
  if ( fPeriod ) {
    szFilename.Format(_T("%s\\%s_%s%04d-%04d_%02d.%02d.%04d-%02d.%02d.%04d.xml"),
                      szOutFolder, szFileMask, szTypeMask, lStartRec, lFinishRec,
                      odtFrom.GetDay(), odtFrom.GetMonth(), odtFrom.GetYear(),
                      odtTill.GetDay(), odtTill.GetMonth(), odtTill.GetYear()
                     );
  }
  else {
    szFilename.Format(_T("%s\\%s_%s%04d-%04d.xml"), szOutFolder, szFileMask, szTypeMask, lStartRec, lFinishRec);
  }

  return xml.Open(szFilename, CFile::modeCreate |  CFile::modeWrite | CFile::typeText);
}

CString Win1251ToUTF8(LPCTSTR s) {
  CString str;
  int wbuflen = MultiByteToWideChar(1251, 0, s, -1, 0, 0);
  WCHAR * wbuf = new WCHAR[wbuflen];
  MultiByteToWideChar(1251, 0, s, -1, wbuf, wbuflen);
  int buflen = WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, 0, 0, NULL, NULL);
  char * buf = new char[buflen];
  WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, buf, buflen, NULL, NULL);
  delete [] wbuf;
  while ( buflen && buf[buflen-1]==0 ) buflen--;
  str = CString(buf, buflen);
  delete buf;
  return str;
}

LPCTSTR GetRagsType() {
  CString szRags = theIniCache.GetRAGS();
  if ( theIniCache.IsVyconcom(szRags) ) {
    return _T("98");
  }
  return _T("97");
}

int GetRagsRegionId() {
  CString szRegion = theIniCache.GetREGION();
  return GetRegionId(szRegion, szRegion);
}

CString GetExtNotesValue(const CString& szExtNotes, LPCTSTR szBOS, LPCTSTR szEOS) {
  CString szValue;
  szValue = GetSentence(szExtNotes, szBOS, _T("}"));
  szValue.Replace(szBOS, _T(""));
  szValue.Replace(szEOS, _T(""));
  szValue.TrimLeft();
  szValue.TrimRight();
  return szValue;
}

BOOL IsEmptyRecord(CDaoRecordset& rs) {
  long lNumber      = GetFieldLong(rs, _T("NUMBER"));
  CString szDateReg = GetFieldDate(rs, _T("DATEREG"));
  CString szSurname = GetFieldString(rs, _T("SURNAME"));
  if ( 0==lNumber || szDateReg.IsEmpty() || szSurname.IsEmpty() ) {
    return true;
  }
  return false;
}
