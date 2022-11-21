//
// db.cpp
//
#include "stdafx.h"
#include "db.h"

long GetRecordCount(CDaoDatabase& db, LPCTSTR szTablename) {
  long lRecords = 0;

  CDaoRecordset rs(&db);
  CString sql;
  sql.Format(_T("[%s]"), szTablename);

  try {
    rs.Open(dbOpenTable, sql);
    lRecords += rs.GetRecordCount();
    rs.Close();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
    e->ReportError();
    #endif
    e->Delete();
  }

  return lRecords;
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


LONG GetFieldLong(CDaoRecordset& rs, LPCTSTR lpszFldName) {
  COleVariant ovar;
  try {
    ovar = rs.GetFieldValue(lpszFldName);
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    ovar.lVal = 0;
  }
  return ovar.lVal;
}

SHORT GetFieldShort(CDaoRecordset& rs, LPCTSTR lpszFldName) {
  COleVariant ovar;
  try {
    ovar = rs.GetFieldValue(lpszFldName);
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    ovar.intVal = 0;
  }
  return ovar.intVal;
}

BYTE GetFieldByte(CDaoRecordset& rs, LPCTSTR lpszFldName) {
  COleVariant ovar;
  try {
    ovar = rs.GetFieldValue(lpszFldName);
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    ovar.bVal = 0;
  }
  return ovar.bVal;
}

CString GetFieldString(CDaoRecordset& rs, LPCTSTR lpszFldName) {
  CString sRet;
  COleVariant ovar;
  try {
    ovar = rs.GetFieldValue(lpszFldName);
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
  sRet.Replace('\"', '\'');
  return sRet;
}

CString GetFieldDate(CDaoRecordset& rs, LPCTSTR lpszFldName, COleDateTime* pDate/* = NULL*/) {
  CString sRet;
  COleVariant ovar;
  try {
    ovar = rs.GetFieldValue(lpszFldName);
    if ( VT_DATE==ovar.vt ) {
      COleDateTime odt (ovar.date);
      if ( COleDateTime::valid == odt.m_status && odt.m_dt != (DATE)NULL) {
        sRet.Format(_T("%02d.%02d.%04d"), odt.GetDay(), odt.GetMonth(), odt.GetYear() );
      }
      if ( pDate ) {
        *pDate = odt;
      }
    }
  }
  catch(CDaoException* e) {
    e->Delete();
  }
  return sRet;
}



BOOL IsUALang(CDaoRecordset& rs) {
  short nFields = rs.GetFieldCount();
  CString s;

  for( short i(0); i < rs.GetFieldCount(); i++ ) {
    CDaoFieldInfo fi;
    rs.GetFieldInfo(i, fi);
    switch( fi.m_nType ) {
      case dbText  :
      case dbMemo  :
        s = GetFieldString(rs, fi.m_strName);
        if ( s.FindOneOf(_T("³¿º²¯ª")) >= 0 ) {
          return true;
        }
        break;
    }
  }
  return false;
}