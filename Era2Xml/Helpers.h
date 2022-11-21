//
// Helpers.h
//
#pragma once

extern BOOL    g_bWriteEmptyTags;
extern CString g_szXMLHeader;
extern CString g_szExtSystemId;

extern CString g_szHelpersMDB;


void LoadIniValues();

BOOL CreateXMLFile(CStdioFile& xml, LPCTSTR szOutFolder, LPCTSTR szFileMask, LPCTSTR szTypeMask,
                   BOOL fPeriod, COleDateTime& odtFrom, COleDateTime& odtTill,
                   long lTableRecs, long lStartRec, long lMaxRecs
                  );


CString Win1251ToUTF8(LPCTSTR s);

LPCTSTR GetRagsType();
int     GetRagsRegionId();
CString GetExtNotesValue(const CString& szExtNotes, LPCTSTR szBOS, LPCTSTR szEOS);
BOOL    IsEmptyRecord(CDaoRecordset& rs);