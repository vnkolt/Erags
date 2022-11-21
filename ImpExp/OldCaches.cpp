//
// OldCaches.cpp
//
#include "stdafx.h"
#include "ImpExp.h"
#include "OldCaches.h"

#include "..\Common\CyrString.h"
#include "..\Common\DaoErr.h"
#include "..\Common\DB.h"
#include "..\Common\MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CStringMap  theNames;       // Мужские и женские имена
CStringMap  thePatronymics; // Мужские и женские отчества
CStringMap  theBanks;       // Банки
CRecordMap  theCountries;   // Страны и гражданства
CStringMap  theRegions;     // Области
CRecordMap  theCities;      // Название НП и тип НП
CStringMap  theDistricts;   // Районы
CStringMap  theStreets;     // Улицы
CRecordMap  theNations;     // Национальности (отдельно для м. и ж. рода)
CStringMap  theRAGSes;      // РАГСы
CStringMap  theROVDs;       // РОВД
CStringMap  theMHospitals;  // Родильные дома
CStringMap  theHospitals;   // Больницы
//////////////////////////////////////////////////////////
// CSexMap
CSexMap::CSexMap() {
}
CSexMap::~CSexMap() {
  Clear();
}
void CSexMap::Clear() {
  POSITION pos = m_map.GetStartPosition();
  while ( pos ) {
    CSexRecord* pRecord = NULL;
    long ID = 0;
    m_map.GetNextAssoc(pos, ID, pRecord);
    ASSERT(pRecord);
    delete pRecord;
  }
  m_map.RemoveAll();
}
CSexRecord* CSexMap::Lookup(long ID) {
  CSexRecord* pRecord = NULL;
  if ( m_map.Lookup(ID, pRecord) )
    return pRecord;
  return NULL;
}
void CSexMap::Add(long ID, CSexRecord* pRecord) {
  ASSERT ( Lookup(ID)==NULL );
  m_map.SetAt(ID, pRecord);
}

BOOL CSexMap::Fill(CDaoDatabase& db, LPCTSTR szTableName, LPCTSTR szKeyField, LPCTSTR szValueField) {
  BOOL fRet = true;
  Clear();
  CString sql;
  sql.Format(_T("SELECT [%s], [%s], [Пол] FROM [%s]"), szKeyField, szValueField, szTableName);
  CDaoRecordset rs(&db);
  try {
    rs.Open(dbOpenDynaset, sql);
    while ( !rs.IsEOF() ) {
      long    lID    = iDBLongField(rs, 0);
      CString szName = Trim(iDBStringField(rs, 1));
      bool    fSex   = iDBBoolField(rs, 2);
      if ( false==szName.IsEmpty() ) { // Пустые записи не добавляем
        Add(lID, new CSexRecord(szName, fSex));
      }
      rs.MoveNext();
    }
    rs.Close();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    OnMessage(MT_ERROR, FormatDaoError(e));
    e->Delete();
    fRet = false;
  }
  return fRet;
}

//////////////////////////////////////////////////////////
// CRecordMap
CRecordMap::CRecordMap() {
}
CRecordMap::~CRecordMap() {
  Clear();
}
void CRecordMap::Clear() {
  POSITION pos = m_map.GetStartPosition();
  while ( pos ) {
    C2FieldRecord* pRecord = NULL;
    long ID = 0;
    m_map.GetNextAssoc(pos, ID, pRecord);
    ASSERT(pRecord);
    delete pRecord;
  }
  m_map.RemoveAll();
}
C2FieldRecord* CRecordMap::Lookup(long ID) {
  C2FieldRecord* pRecord = NULL;
  if ( m_map.Lookup(ID, pRecord) )
    return pRecord;
  return NULL;
}
void CRecordMap::Add(long ID, C2FieldRecord* pRecord) {
  ASSERT ( Lookup(ID)==NULL );
  m_map.SetAt(ID, pRecord);
}
BOOL CRecordMap::Fill(CDaoDatabase& db, LPCTSTR szTableName, LPCTSTR szKeyField, LPCTSTR szField1, LPCTSTR szField2) {
  BOOL fRet = true;
  Clear();
  CString sql;
  sql.Format(_T("SELECT [%s],[%s],[%s] FROM [%s]"), szKeyField, szField1, szField2, szTableName);
  CDaoRecordset rs(&db);
  try {
    rs.Open(dbOpenDynaset, sql);
    while ( !rs.IsEOF() ) {
      long      ID      = iDBLongField(rs, 0);
      CString   sField1 = Trim(iDBStringField(rs, 1)),
                sField2 = Trim(iDBStringField(rs, 2));

      if ( false==sField1.IsEmpty() || sField2.IsEmpty() ) {  // Пустые записи не добавляем
        Add(ID, new C2FieldRecord(sField1, sField2));
      }
      rs.MoveNext();
    }
    rs.Close();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    fRet = false;
  }
  return fRet;
}

//////////////////////////////////////////////////////////
// CStringMap
CStringMap::CStringMap() {
}
CStringMap::~CStringMap() {
  Clear();
}
void CStringMap::Clear() {
  m_map.RemoveAll();
}
CString CStringMap::Lookup(long ID) {
  CString s;
  m_map.Lookup(ID, s);
  return s;
}
void CStringMap::Add(long ID, const CString& s) {
//  ASSERT ( Lookup(ID).IsEmpty() ); // Только для уникальных ID
//  ASSERT ( !s.IsEmpty() );         // Нельзя добавлять пустые строки
  m_map.SetAt(ID, s);
}
BOOL CStringMap::Fill(CDaoDatabase& db, LPCTSTR szTableName, LPCTSTR szKeyField, LPCTSTR szValueField) {
  BOOL fRet = true;
  Clear();
  CString sql;
  sql.Format(_T("SELECT [%s], [%s] FROM [%s]"), szKeyField, szValueField, szTableName);
  CDaoRecordset rs(&db);
  try {
    rs.Open(dbOpenDynaset, sql);
    while ( !rs.IsEOF() ) {
      long    key  = iDBLongField(rs, 0);
      CString sVal = Trim(iDBStringField(rs, 1));
      if ( false==sVal.IsEmpty() ) {
        Add(key, sVal);
      }
      rs.MoveNext();
    }
    rs.Close();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG 
      e->ReportError();
    #endif
    e->Delete();
    fRet = false;
  }
  return fRet;
}