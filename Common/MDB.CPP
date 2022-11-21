//
// MDB.cpp
//
#include "stdafx.h"
#include "MDB.h"

#include "Monthes.h"
#include "DaoErr.h"

#include "CyrString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/*
void AFXAPI DDX_FieldCBStringExact(CDataExchange* pDX,
                                   int nIDC,
                                   CString& value,
                                   CRecordset* pRecordset )
{
}

*/

BOOL IsTablePresent(CDaoDatabase& db, LPCTSTR szTableName) {
  if ( db.IsOpen()==false )
    return false;

  CDaoTableDefInfo tdInfo;
  short nTables = db.GetTableDefCount();
  try {
    for( short i(0); i < nTables; i++ ) {
      db.GetTableDefInfo(i, tdInfo);
      if ( 0==CyrStriCmp(tdInfo.m_strName, szTableName) ) {
        return true;
      }
    }
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
  return false;
/*
  try {
    db.GetTableDefInfo(szTableName, tdInfo);
  }
  catch ( CDaoException* e ) {
    //#ifdef _DEBUG
    //  e->ReportError();
    //#endif
    e->Delete();
    return false;
  }

  return true;
*/
}

BOOL IsFieldPresent(CDaoRecordset& rs, LPCTSTR szFieldName) {
  try {
    for( int i(0); i < rs.GetFieldCount(); i++ ) {
      CDaoFieldInfo fi;
      rs.GetFieldInfo(i, fi);
      if ( stricmp(fi.m_strName, szFieldName)==0 )
        return true;
    }
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      // e->ReportError(); // to do logstring
    #endif
    e->Delete();
  }
  return false;
}

long GetRecordCount(CDaoDatabase& db, LPCTSTR szTableName) {
  long nRecords = 0;
  CDaoRecordset rs(&db);
  CString sql;
  sql.Format(_T("SELECT ID FROM %s"), szTableName);
  try {
    rs.Open(dbOpenDynaset, sql, dbReadOnly);// See Article ID: Q165563 in MSDN
    if ( !rs.IsEOF() ) {
      rs.MoveLast();
      nRecords = rs.GetRecordCount();
    }
    rs.Close();
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
  return nRecords;
}

LONG GetFieldLong(CDaoRecordset* pRS, LPCTSTR lpszFldName){
  COleVariant ovar;
  ovar = pRS->GetFieldValue(lpszFldName);
  return ovar.lVal;
}
SHORT GetFieldShort(CDaoRecordset* pRS, LPCTSTR lpszFldName){
  COleVariant ovar;
  ovar = pRS->GetFieldValue(lpszFldName);
  return ovar.intVal;
}
BYTE GetFieldByte(CDaoRecordset* pRS, LPCTSTR lpszFldName){
  COleVariant ovar;
  ovar = pRS->GetFieldValue(lpszFldName);
  return ovar.bVal;
}

CString GetFieldString(CDaoRecordset* pRS, LPCTSTR lpszFldName){
  CString sRet;
  COleVariant ovar;
  try {
    ovar = pRS->GetFieldValue(lpszFldName);
    switch(ovar.vt) {
      case VT_UI2:
        sRet.Format(_T("%d"), ovar.uiVal);
        break;
      case VT_I2:
        sRet.Format(_T("%d"), ovar.iVal);
        break;
      case VT_UI4:
        sRet.Format(_T("%d"), ovar.ulVal);
        break;
      case VT_I4:
        sRet.Format(_T("%d"), ovar.lVal);
        break;
      case VT_UINT:
        sRet.Format(_T("%d"), ovar.uintVal);
        break;
      case VT_INT:
        sRet.Format(_T("%d"), ovar.intVal);
        break;
      case VT_BSTR:
        sRet = V_BSTRT(&ovar);
        break;
      case VT_I1:
      case VT_UI1:
        sRet.Format(_T("%c"), ovar.bVal);
        break;
    }
  }
  catch(CDaoException* e) {
    e->Delete();
  }
  sRet.TrimLeft();
  sRet.TrimRight();
  return sRet;
}

bool GetFieldBool(CDaoRecordset* pRS, LPCTSTR lpszFldName) {
  COleVariant ovar;
  ovar = pRS->GetFieldValue(lpszFldName);
  if (ovar.vt == VT_NULL)
			return false;
  return V_BOOL(&ovar) ? true : false;
}

COleDateTime GetFieldOleDateTime(CDaoRecordset* pRS, LPCTSTR lpszFldName) {
  COleDateTime odt;
  try {
    odt = pRS->GetFieldValue(lpszFldName);
  }
  catch(CDaoException* e) {
    e->Delete();
  }
  return odt;
}

CString GetFieldDate(CDaoRecordset* pRS, LPCTSTR lpszFldName, bool fFullDate/*=false*/) {
  CString sRet;
  COleVariant ovar;
  try {
    ovar = pRS->GetFieldValue(lpszFldName);
    if ( VT_DATE==ovar.vt ) {
      COleDateTime odt (ovar.date);
      if ( COleDateTime::valid == odt.m_status && odt.m_dt != (DATE)NULL) {
        if ( fFullDate )
          sRet.Format(_T("%02d %s %04d"), odt.GetDay(), GetMonth(odt.GetMonth()), odt.GetYear() );
        else
          sRet.Format(_T("%02d.%02d.%04d"), odt.GetDay(), odt.GetMonth(), odt.GetYear() );
      }
    }
  }
  catch(CDaoException* e) {
    e->Delete();
  }
  return sRet;
}

LONG GetIDField(CDaoRecordset* pRS) {
  return GetFieldLong(pRS, _T("ID") );
}

BOOL IsYearInDate(CDaoRecordset* pRS, LPCTSTR lpszFldName, int Year) {
  COleDateTime odt = GetFieldOleDateTime(pRS, lpszFldName);
  return odt.GetYear()==Year;
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
