//
// Geography.cpp
//

#include "stdafx.h"
#include "Erags.h"

#include "AddGeoDlg.h"


#include "ChildFrm.h"
#include "DataManager.h"
#include "Geography.h"
#include "MainFrm.h"

#include "..\Common\CyrString.h"
#include "..\Common\MDB.h"


CGeoCache theGeoCache;

/*
void GeoRefillGeoArray(CDaoRecordset& rs, CPtrArray& array) {
  for( int i(0); i < array.GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)array.GetAt(i);
    if ( rs.CanAppend() ) {
      if ( pRecord->m_pParent )
        pRecord->m_ParentID = pRecord->m_pParent->m_ID;
      rs.AddNew();
      rs.SetFieldValue(_T("PARENT"), &COleVariant(pRecord->m_ParentID, VT_I4) );
      rs.SetFieldValue(_T("NAME"),   (LPCTSTR)pRecord->m_Name );
      if ( pRecord->m_Name != pRecord->m_AltName && !pRecord->m_AltName.IsEmpty() ) {
        rs.SetFieldValue(_T("FULLNAME"),   (LPCTSTR)pRecord->m_AltName );
      }
      rs.SetFieldValue(_T("TYPE"),   (LPCTSTR)pRecord->m_Type );

      if ( false==pRecord->m_ZipCode.IsEmpty() ) {
        rs.SetFieldValue(_T("ZIPCODE")  ,(LPCTSTR)pRecord->m_ZipCode);
      }
      if ( false==pRecord->m_PhoneCode.IsEmpty() ) {
        rs.SetFieldValue(_T("PHONECODE"),(LPCTSTR)pRecord->m_PhoneCode);
      }
      if ( false==pRecord->m_Directory.IsEmpty() ) {
        rs.SetFieldValue(_T("DIRINQ")   ,(LPCTSTR)pRecord->m_Directory);
      }

      rs.Update();
      rs.SetBookmark( rs.GetLastModifiedBookmark( ) );
      COleVariant varID = rs.GetFieldValue(_T("ID"));
      pRecord->m_ID = varID.lVal;

      if ( pRecord->m_array.GetSize() ) {
        GeoRefillGeoArray(rs, pRecord->m_array);
      }
    }
  }
}

void GeoRefill(CDaoDatabase& db) {
  CDaoRecordset rs(&db);
  try {
    rs.Open(dbOpenTable, "[GEO]");
    GeoRefillGeoArray(rs, theGeoCache.m_array);
    rs.Close();
  }
  catch (CDaoException* e) {
    e->ReportError(); // to do logstring
    e->Delete();
	}
}
*/

CString GetGeoPath(CGeoRecord* pRecord) {
  CString sPath;
  if ( pRecord ) {
    sPath = pRecord->m_Name;
    while ( pRecord ) {
      pRecord = pRecord->m_pParent;
      if ( pRecord ) {
        CString s;
        s.Format(_T("%s/%s"), pRecord->m_Name, sPath);
        sPath = s;
      }
    }
  }
  return sPath;
}

int CompareGeoType(CGeoRecord* p1, CGeoRecord* p2) {
  if ( p1->m_Type.IsEmpty() || p2->m_Type.IsEmpty() ) {
    if ( p1->m_Type.IsEmpty() && p2->m_Type.IsEmpty() )
      return 0;
    return p1->m_Type.IsEmpty() ? 1 : -1;
  }
  if ( p1->m_Type==p2->m_Type )
    return 0;

  return (p1->GetGeoTypeWeight() - p2->GetGeoTypeWeight());
}

/*
int CALLBACK GetSortCmp(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  CGeoRecord* p1 = (CGeoRecord*)lParam1;
  CGeoRecord* p2 = (CGeoRecord*)lParam2;

  int w1 = p1->GetGeoTypeWeight();
  int w2 = p2->GetGeoTypeWeight();
  if ( w1==w2 )
    return CyrCompare(p1->m_Name, p2->m_Name);
  return w1-w2;
}
*/

int GeoRecCmp(const void *a1, const void *a2) {
  CGeoRecord *p1 = *(CGeoRecord**)a1,
             *p2 = *(CGeoRecord**)a2;

  if ( 1==p1->m_ID ) return -1;
  if ( 1==p2->m_ID ) return 1;
  int w1 = p1->GetGeoTypeWeight();
  int w2 = p2->GetGeoTypeWeight();
  if ( w1==w2 )
    return CyrCompare(p1->m_Name, p2->m_Name);
  return w1-w2;
}

int FindInStringArray(const CStringArray& sa, const CString s) {
  for( int i(0); i < sa.GetSize(); i++ ) {
    if ( sa[i]==s ) {
      return i;
    }
  }
  return -1;
}


///////////////////////////////////////////////////////
// CGeoRecord
CGeoRecord::CGeoRecord() {
  m_ID = m_ParentID = 0;
  m_hItem = NULL;
  m_pParent = NULL;
  //m_fLoaded = false;
  m_dwFlags = 0;
}
CGeoRecord::~CGeoRecord() {
  for( int i(0); i < m_array.GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)m_array.GetAt(i);
    delete pRecord;
  }
  m_array.RemoveAll();
}

bool CGeoRecord::IsCountry() const {
  if ( m_Type.IsEmpty() )
    return false;
  if ( m_Type == _T("держава") )
    return true;
  return false;
}
bool CGeoRecord::IsRegion() const {
  if ( 1==m_ParentID ) {
    return true;
  }
  if ( m_Type.IsEmpty() )
    return false;
  TCHAR type = m_Type.GetAt(0);
  if ( type == 'о' || type=='к' )
    return true;
  return false;
}
bool CGeoRecord::IsDistrict() const {
  if ( m_Type.IsEmpty() )
    return false;
  if ( m_Type.GetAt(0)==TCHAR('р') )
    return true;
  return false;
}
bool CGeoRecord::IsCity() const {
  if ( m_Type.IsEmpty() )
    return false;
  if ( m_Type.GetAt(0)==_T('м') )
    return true;
  return false;
}
bool CGeoRecord::IsMainCity() const {
  if ( NULL==m_pParent )
    return false;
  if ( m_pParent->IsCountry() )
    return true;
  if ( m_pParent->IsRegion() ) {
    if ( m_Type==_T("мср") )
      return true;
  }
  return false;
}
bool CGeoRecord::IsVillage(CString* pDest/*=NULL*/) const {
  if ( m_Type.IsEmpty() )
    return true;
  TCHAR c = m_Type.GetAt(0);
  switch(c) {
    case TCHAR('д'): case TCHAR('к'):
    case TCHAR('м'):
    case TCHAR('о'): case TCHAR('р'):
      return false;
  }
  if ( pDest ) {
    if ( m_Type==_T("с") || m_Type==_T("с.") || m_Type==_T("село") )
      *pDest = _T("село");
    else if ( m_Type==_T("слщ") || m_Type==_T("с-ще") || m_Type==_T("сще") || m_Type==_T("сщ") || m_Type==_T("селище") )
      *pDest = _T("селище");
    else if ( m_Type==_T("смт") || m_Type==_T("смт.") )
      *pDest = _T("смт");
    else if ( m_Type==_T("х") || m_Type==_T("х.") || m_Type==_T("х-р") || m_Type==_T("хутір") )
      *pDest = _T("хутір");
    else if ( m_Type==_T("ст.") || m_Type==_T("ст-ція") || m_Type==_T("станція") )
      *pDest = _T("станція");
    else if ( m_Type==_T("ст-ця") || m_Type==_T("с-ця") || m_Type==_T("станиця") )
      *pDest = _T("станиця");
    else if ( m_Type.GetAt(0)=='с' )
      *pDest = _T("село");
  }
  return true;
}

int CGeoRecord::GetGeoTypeWeight() {
  if ( IsCountry() ) {
/************************************** : by VK at 03.07.2005 22:05:19 **\
    if ( m_Name==_T("Україна") ) {
      return -1;
    }
\************************************** : by VK at 03.07.2005 22:05:22 **/
    return 0;
  }
  if ( IsRegion() )
    return 1;
  if ( IsCity() )
    return 2;
  if ( IsDistrict() )
    return 9;
  if ( m_Type.Find(_T("смт"))==0 )
    return 3;
  return 4;
/************************************** : by VK at 27.06.2005 23:01:32 **\
  if ( IsVillage() ) {
    if ( m_Type.Find(_T("смт"))==0 )
      return 3;
    if ( m_Type.Find(_T("с-ще"))==0 )
      return 4;
    return 5;
  }
  if ( IsDistrict() )
    return 9;
  return 10;
\************************************** : by VK at 27.06.2005 23:01:35 **/
  
}
CString CGeoRecord::GetTypeName() {
  if ( IsCountry() ) {
    return _T("держава");
  }
  if ( IsDistrict() ) {
    return _T("район");
  }
  if ( IsRegion() ) {
    TCHAR type = m_Type.GetAt(0);
    if ( type == 'о' )
      return _T("область");
    if ( type=='к' )
      return _T("край");
    return m_Type;
  }
  if ( IsCity() ) {
    return "місто";
  }
  CString s;
  IsVillage(&s);
  return s;
}

CString CGeoRecord::GetShortTypeName() {
  CString s;
  if ( IsDistrict() ) {
    s = _T("р-н");
  }
  else if ( IsRegion() ) {
    TCHAR type = m_Type.GetAt(0);
    if ( type == 'о' )
      s = _T("обл.");
    if ( type=='к' )
      s = _T("кр.");
  }
  else if ( IsCity() ) {
    s = _T("м.");
  }
  else {
    if ( m_Type==_T("смт") || m_Type==_T("с-ще") || m_Type==_T("село") ) {
      s = m_Type;
    }
    else {
      s = m_Type + '.';
      s.TrimLeft('.');
      if ( s.Right(2)==_T("..") ) {
        s.TrimRight('.');
        s += '.';
      }
    }
  }
  return s;
}


CString CGeoRecord::GetName() {
  if ( IsCity() ) {
    CString s;
    s.Format(_T("%s м."), m_Name);
    return s;
  }
  if ( IsVillage() ) {
    CString s;
    s.Format(_T("%s %s"), m_Name, m_Type);
    return Trim(s);
  }
  return m_Name;
}

CString CGeoRecord::GetAltName() {
  CString s;
  if ( false==m_AltName.IsEmpty() ) {
    if ( IsCity() ) {
      if ( m_AltName.Left(2) != _T("м.") ) {
        s.Format(_T("%s м."), m_AltName);
      }
      else {
        s = m_AltName;
      }
      return s;
    }
    if ( IsVillage() ) {
      CString s;
      s.Format(_T("%s %s"), m_AltName, m_Type);
      return Trim(s);
    }
  }
  return GetName();
}


CString CGeoRecord::GetNameWithAltName() {
  if ( !m_AltName.IsEmpty() ) {
    CString s;
    s.Format(_T("%s (%s)"), m_Name, m_AltName);
    return s;
  }
  return m_Name;
}

bool CGeoRecord::HasChildren() {
  return m_array.GetSize() ? true : false;
}

bool CGeoRecord::Insert() {
  CString sql;
  if ( m_Name.IsEmpty() )
    return false;
  if ( m_Type.IsEmpty() )
    return false;

  try {
    CDaoRecordset rs(&theDataManager.m_dbLists);
    rs.Open(dbOpenTable, _T("[GEOGRAPHY]"));
    if ( rs.CanAppend() ) {
      rs.AddNew();
      rs.SetFieldValue(_T("PARENT"), &COleVariant(m_ParentID, VT_I4) );
      rs.SetFieldValue(_T("NAME"),   (LPCTSTR)m_Name );
      if ( m_Name != m_AltName && !m_AltName.IsEmpty() ) {
        rs.SetFieldValue(_T("FULLNAME"),   (LPCTSTR)m_AltName );
      }
      rs.SetFieldValue(_T("TYPE"),   (LPCTSTR)m_Type );
      rs.Update();
      rs.SetBookmark( rs.GetLastModifiedBookmark( ) );
      COleVariant varID = rs.GetFieldValue(_T("ID"));
      m_ID = varID.lVal;
    }
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return false;
	}
  return true;
}

bool CGeoRecord::Update() {
  if ( m_Name.IsEmpty() )
    return false;
  if ( m_Type.IsEmpty() )
    return false;

  CString sql;
  sql.Format(_T("SELECT ID,PARENT,NAME,FULLNAME,TYPE,ZIPCODE,PHONECODE,DIRINQ FROM GEOGRAPHY WHERE ID=%ld"), m_ID);

  CDaoRecordset rs(&theDataManager.m_dbLists);
  try {
    rs.Open(dbOpenDynaset, sql);
    if ( !rs.IsEOF() ) {
      COleVariant ovar;
      ovar.Clear(); ovar.vt = VT_NULL;
      rs.Edit();
      rs.SetFieldValue(_T("NAME"), (LPCTSTR)m_Name);


      if ( m_AltName.IsEmpty() )    { rs.SetFieldValue(_T("FULLNAME"), ovar);                }
      else                          { rs.SetFieldValue(_T("FULLNAME"), (LPCTSTR)m_AltName);  }
      if ( !m_Type.IsEmpty() )      { rs.SetFieldValue(_T("TYPE"), (LPCTSTR)m_Type);         }

      ovar.Clear(); ovar.vt = VT_NULL;
      if ( m_ZipCode.IsEmpty() ) { rs.SetFieldValue(_T("ZIPCODE"), ovar);               }
      else                       { rs.SetFieldValue(_T("ZIPCODE"), (LPCTSTR)m_ZipCode); }

      ovar.Clear(); ovar.vt = VT_NULL;
      if ( m_PhoneCode.IsEmpty() ) { rs.SetFieldValue(_T("PHONECODE"), ovar);                 }
      else                         { rs.SetFieldValue(_T("PHONECODE"), (LPCTSTR)m_PhoneCode); }

      ovar.Clear(); ovar.vt = VT_NULL;
      if ( m_Directory.IsEmpty() ) { rs.SetFieldValue(_T("DIRINQ"), ovar);                 }
      else                         { rs.SetFieldValue(_T("DIRINQ"), (LPCTSTR)m_Directory); }

      rs.Update();

      m_dwFlags |= GRF_UPDATED;
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return false;
	}
  return true;
}

bool CGeoRecord::RemoveRecord() {
  CString sql;

  sql.Format(_T("DELETE FROM GEOGRAPHY WHERE ID=%ld"), m_ID);

  CDaoQueryDef qd(&theDataManager.m_dbLists);
  try {
    qd.Create(NULL,sql);
    qd.Execute();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return false;
	}
  return true;
}

void CGeoRecord::RemoveRecordFromArray(CGeoRecord* pRecord) {
  for( int i(0); i < m_array.GetSize(); i++ ) {
    if ( m_array.GetAt(i)==pRecord ) {
      m_array.RemoveAt(i);
      pRecord->RemoveRecord();
      delete pRecord;
      break;
    }
  }
}

///////////////////////////////////////////////////////
// CGeoCache
CGeoCache::CGeoCache() {
}
CGeoCache::~CGeoCache() {
  Clear();
}

void CGeoCache::Clear() {
  for( int i(0); i < m_array.GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)m_array.GetAt(i);
    if ( pRecord )
      delete pRecord;
  }
  m_array.RemoveAll();
}

void CGeoCache::Sort(CPtrArray* pArray) {
  qsort( pArray->GetData(), pArray->GetSize(), sizeof(CGeoRecord*), GeoRecCmp);
}

BOOL CGeoCache::Load(CDaoDatabase& db, CProgressCtrl* pProgressCtrl, CStatic* pStatic) {
  Clear();
  #ifdef _DEBUG
    SYSTEMTIME st1;
    GetLocalTime(&st1);
    CString sMsg;
    sMsg.Format(_T("SYSTEMTIME=%02d:%02d:%02d.%03d\n"),
                st1.wHour, st1.wMinute, st1.wSecond, st1.wMilliseconds);
    TRACE0(sMsg);
  #endif

  CDaoRecordset rs(&db);
  //CMapStringToPtr map;
  CMapPtrToPtr map;
  try {
    rs.Open(dbOpenTable, "[GEOGRAPHY]", dbReadOnly);
    rs.SetCurrentIndex(_T("PrimaryKey"));
    int OldPercent = 0;
    while ( !rs.IsEOF() ) {
      CGeoRecord* pRecord = new CGeoRecord();
      pRecord->m_ID        = GetFieldLong  (&rs, "ID");
      pRecord->m_ParentID  = GetFieldLong  (&rs, "PARENT");
      pRecord->m_Type      = GetFieldString(&rs, "TYPE");
      pRecord->m_Name      = GetFieldString(&rs, "NAME");
      pRecord->m_AltName   = GetFieldString(&rs, "FULLNAME");
      pRecord->m_ZipCode   = GetFieldString(&rs, "ZIPCODE");
      pRecord->m_PhoneCode = GetFieldString(&rs, "PHONECODE");
      pRecord->m_Directory = GetFieldString(&rs, "DIRINQ");
      rs.MoveNext();

#ifdef _DEBUG
      if ( pRecord->m_Name==_T("Буча") ) {
        int i = 0;
        int j = i++;
      }
#endif

      CGeoRecord* pParentRecord = NULL;
      map.SetAt((void*)pRecord->m_ID, pRecord);
      if ( map.Lookup((void*)pRecord->m_ParentID, (void*&)pParentRecord) ) {
        pParentRecord->m_array.Add(pRecord);
        pRecord->m_pParent = pParentRecord;
      }
      else {
        m_array.Add( pRecord );
      }
      int NewPercent = (int)(rs.GetPercentPosition()*10);
      if ( NewPercent != OldPercent ) {
        pProgressCtrl->SetPos(NewPercent);
        pStatic->SetWindowText(GetGeoPath(pRecord));
        OldPercent = NewPercent;
        PeekAndPump();
      }
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return FALSE;
	}

  if ( m_array.GetSize() > 1 )
    Sort(&m_array);

  POSITION pos = map.GetStartPosition();
  while( pos ) {
    long key;
    CGeoRecord* pRecord = NULL;
    map.GetNextAssoc(pos, (void*&)key, (void*&)pRecord);
    if ( pRecord->m_array.GetSize() > 1 )
      Sort(&pRecord->m_array);
  }
  #ifdef _DEBUG
    SYSTEMTIME st2;
    GetLocalTime(&st2);
    sMsg.Format(_T("SYSTEMTIME=%02d:%02d:%02d.%03d\n"),
                st2.wHour, st2.wMinute, st2.wSecond, st2.wMilliseconds);
    TRACE0(sMsg);
    sMsg.Format(_T("CGeoCache::Load %d milliseconds\n"), 
                (st2.wHour*3600*1000 - st1.wHour*3600*1000) +
                (st2.wMinute*60*1000 - st1.wMinute*60*1000) +
                (st2.wSecond*1000 - st1.wSecond*1000) +
                (st2.wMilliseconds - st1.wMilliseconds) );
    TRACE0(sMsg); // 2704 before optimization
                  // 1079 - first optimization
                  // 640 - second optimization
  #endif

/*
#ifdef _DEBUG
  GeoRefill(db);
#endif
*/

  return TRUE;
}

int CGeoCache::GetIndex(CGeoRecord* pRecord, CPtrArray*& pArray) {
  if ( pRecord->m_pParent ) {
    pArray = &pRecord->m_pParent->m_array;
  }
  else {
    pArray = &m_array;
  }
  for( int i(0); i < pArray->GetSize(); i++ ) {
    CGeoRecord* p = (CGeoRecord*)pArray->GetAt(i);
    if ( p==pRecord ) {
      return i;
    }
  }
  return -1;
}
CGeoRecord* CGeoCache::GetFirstRecord() {
  CGeoRecord* pRecord = NULL;
  if ( m_array.GetSize() > 0 ) {
    pRecord = (CGeoRecord*)m_array.GetAt(0);
  }
  return pRecord;
}
CGeoRecord* CGeoCache::GetPrevRecord(CGeoRecord* pRecord) {
  CPtrArray* pArray = NULL;
  int nIndex = GetIndex(pRecord, pArray);
  if ( nIndex > 0 && pArray ) {
    return (CGeoRecord*)pArray->GetAt(nIndex-1);
  }
  if ( pRecord->m_pParent ) {
    return pRecord->m_pParent;
  }
  return NULL;
}
CGeoRecord* CGeoCache::GetNextRecord(CGeoRecord* pRecord) {
  CPtrArray* pArray = NULL;
  int nIndex = GetIndex(pRecord, pArray);
  if ( nIndex > 0 && pArray && nIndex < pArray->GetSize()-1) {
    return (CGeoRecord*)pArray->GetAt(nIndex+1);
  }
  if ( pRecord->m_pParent ) {
    return GetNextRecord(pRecord->m_pParent);
  }
//  if ( m_array.GetSize() > 0 ) {
//    return 
//  }
  return NULL;
}
CGeoRecord* CGeoCache::GetLastRecord(CPtrArray& array) {
  CGeoRecord* pRecord = NULL;
  if ( array.GetSize() > 0 ) {
    pRecord = (CGeoRecord*)array.GetAt(array.GetSize()-1);
    if ( pRecord->m_array.GetSize() > 0 )
      return GetLastRecord(pRecord->m_array);
  }
  return pRecord;
}

CGeoRecord* CGeoCache::GetCountry(CPtrArray* pArray, const CString& s) {
  for( int i(0); i < pArray->GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)pArray->GetAt(i);
    if ( pRecord->IsCountry() ) {
      if ( pRecord->m_Name==s || pRecord->m_AltName==s )
        return pRecord;
      if ( pRecord->HasChildren() ) {
        pRecord = GetCountry(&pRecord->m_array, s);
        if ( pRecord )
          return pRecord;
      }
    }
  }
  return NULL;
}
CGeoRecord* CGeoCache::GetCountry(const CString& s) {
  return GetCountry(&m_array, s);
}
CGeoRecord* CGeoCache::GetRegion(CPtrArray* pArray, const CString& s) {
  for( int i(0); i < pArray->GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)pArray->GetAt(i);
    if ( (pRecord->m_Name==s || pRecord->m_AltName==s) && pRecord->IsRegion() ) {
      return pRecord;
    }
  }
  return NULL;
}

#ifdef _GEO
CGeoRecord* CGeoCache::GetCity(CPtrArray* pArray, const CString& s, char typeLetter/*=0*/) {
  if ( s.IsEmpty() ) {
    return NULL;
  }
  for( int i(0); i < pArray->GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)pArray->GetAt(i);
    if ( pRecord->m_Name==s || pRecord->m_AltName==s || pRecord->GetName()==s ) {
      if ( 0==typeLetter ) {
        return pRecord;
      }
      else if ( pRecord->m_Type.GetAt(0)==typeLetter ) {
        return pRecord;
      }
    }
  }
  return NULL;
}
#else
CGeoRecord* CGeoCache::GetCity(CPtrArray* pArray, const CString& s) {
  if ( s.IsEmpty() )
    return NULL;

  CString sCity = Trim(s);
  CString s2 = sCity.Right(2),
          s3 = sCity.Right(3),
          s4 = sCity.Right(4);
  if (    s2==" м"      // місто
       || s2==" с"      // село
       || s2==" х" )    // хутір
    sCity = sCity.Left( sCity.GetLength()-2 );
  else if(   s3==" м."   // місто
          || s3==" с."   // село
          || s3==" ст"   // станція, станиця
          || s3==" х." ) // хутір
    sCity = sCity.Left( sCity.GetLength()-3 );
  else if (   s4==" ст."  // станція, станиця
           || s4==" х-р" )// хутір
    sCity = sCity.Left( sCity.GetLength()-4 );
  else if ( s.Right(5)==" с-ще" ) // селище
    sCity = sCity.Left( sCity.GetLength()-5 );

/************************************** : by VK at 21/06/2007 00:13:47 **\
  for( int i(0); i < pArray->GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)pArray->GetAt(i);
    if ( pRecord->IsCity() ) {
      if ( pRecord->m_Name==sCity || pRecord->GetName()==s )
        return pRecord;
    }
  }
\************************************** : by VK at 21/06/2007 00:13:55 **/
  // It's need to test this new code 21/06/2007 00:13:55 !!!!!!!!
  for( int i(0); i < pArray->GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)pArray->GetAt(i);
    if ( pRecord->m_Name==sCity || pRecord->GetName()==s ) {
      return pRecord;
    }
  }

  return NULL;
}
#endif

CGeoRecord* CGeoCache::GetDistrict(CPtrArray* pArray, const CString& s) {
  if ( !s.IsEmpty() ) {
    for( int i(0); i < pArray->GetSize(); i++ ) {
      CGeoRecord* pRecord = (CGeoRecord*)pArray->GetAt(i);
      if ( pRecord->IsDistrict() ) {
        if ( pRecord->m_Name==s || pRecord->m_AltName==s /* New !!! */ )
          return pRecord;
      }
    }
  }
  return NULL;
}

void CGeoCache::SelectCBDefault(CEraComboBox& cb) {
  CString s = cb.GetDefault();
  if ( !s.IsEmpty() ) {
    int nIndex = cb.FindString(-1, s);
    if ( CB_ERR != nIndex )
      cb.SetCurSel(nIndex);
  }
}
void CGeoCache::FillCountryCB(CEraComboBox& cb, CPtrArray* pArray) {
  for( int i(0); i < pArray->GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)pArray->GetAt(i);
    if ( pRecord->IsCountry() ) {
      int nNewIndex = cb.AddString( pRecord->m_Name );
      cb.SetItemData( nNewIndex, (DWORD)pRecord );
      if ( pRecord->HasChildren() )
        FillCountryCB(cb, &pRecord->m_array);
    }
  }
}

void CGeoCache::FillCountryCB(CEraComboBox& cb, const CString& sNewValue) {
  if ( false==cb.m_bFilled ) {
    FillCountryCB(cb, &m_array);
    cb.m_bFilled = true;
  }

  if ( false==IsEmptyText(sNewValue) ) {
    int nIndex = cb.FindString(-1, sNewValue);
    if ( CB_ERR==nIndex ) {
      nIndex = cb.AddString(sNewValue);
    }
    cb.SetCurSel(nIndex);
  }
}

void CGeoCache::FillRegionCB(CEraComboBox& cb, CEraComboBox& cbCountry, const CString& sNewValue) {
  int nIndex = cbCountry.GetCurSel();
  CString s, sCountry;
  if ( CB_ERR!=nIndex ) {
    cbCountry.GetLBText(nIndex, s);
    sCountry = s;
    CGeoRecord* pRecord = (CGeoRecord*)cbCountry.GetItemData(nIndex);
    cb.ResetContent();
    if ( NULL==pRecord || CB_ERR==(DWORD)pRecord )
      pRecord = GetCountry(&m_array, s);
    if ( pRecord ) {  // country record found
      for( int i(0); i < pRecord->m_array.GetSize(); i++ ) {
        CGeoRecord* pRegionRecord = (CGeoRecord*)pRecord->m_array.GetAt(i);
        if ( pRegionRecord->IsRegion() ) {
          int nNewIndex = cb.AddString(pRegionRecord->m_Name);
          cb.SetItemDataPtr( nNewIndex, pRegionRecord );
        }
      }
    }
  }
  if ( sNewValue.IsEmpty() ) {
    if ( !sCountry.IsEmpty() && sCountry==cbCountry.GetDefault() ) {
      SelectCBDefault(cb);
    }
  }
  else {
    nIndex = cb.FindString(-1, sNewValue);
    if ( CB_ERR==nIndex )
      nIndex = cb.AddString(sNewValue);
    cb.SetCurSel(nIndex);
  }
}

void CGeoCache::FillDistrictCB(CEraComboBox& cb, CEraComboBox& cbRegion, const CString& sNewValue) {
  CString s, sRegion;
  int nIndex = cbRegion.GetCurSel();
  CMapStringToPtr map;
  if ( CB_ERR!=nIndex ) {
    cbRegion.GetLBText(nIndex, s);
    sRegion = s;
    CGeoRecord* pRecord = (CGeoRecord*)cbRegion.GetItemData(nIndex);
    cb.ResetContent();
    if ( NULL==pRecord || CB_ERR==(DWORD)pRecord )
      pRecord = GetRegion(&m_array, s);
    if ( pRecord ) {  // country record found
      for( int i(0); i < pRecord->m_array.GetSize(); i++ ) {
        CGeoRecord* pChildRecord = (CGeoRecord*)pRecord->m_array.GetAt(i);
        if ( pChildRecord->IsDistrict() ) {
          map.SetAt(pChildRecord->m_Name, pChildRecord);
        }
        else if ( pChildRecord->IsCity() && pChildRecord->HasChildren() ) {
          map.SetAt(pChildRecord->m_Name, pChildRecord);
          for( int i(0); i < pChildRecord->m_array.GetSize(); i++ ) {
            CGeoRecord* pRecord = (CGeoRecord*)pChildRecord->m_array.GetAt(i);
            if ( pRecord->IsDistrict() ) {
              map.SetAt(pRecord->m_Name, pRecord);
            }
            /*
            else if ( pRecord->IsCity() && pRecord->HasChildren() ) {
              map.SetAt(pRecord->m_Name, pRecord);
            }
            map.SetAt(pRecord->m_Name, pRecord);
            */
          }
        }
      }
    }
  }
  POSITION pos = map.GetStartPosition();
  CStringArray sa;
  while ( pos ) {
    CString sKey;
    CGeoRecord* pRecord = NULL;
    map.GetNextAssoc(pos, sKey, (void *&)pRecord);
    if ( pRecord ) {
      CString s = pRecord->GetName();
      int nNewIndex;
      if ( FindInStringArray(sa, s) == -1 ) {
        nNewIndex = cb.AddString(s);
        cb.SetItemDataPtr( nNewIndex, pRecord );
        sa.Add(s);
      }
      s = pRecord->GetAltName();
      if ( false==s.IsEmpty() && FindInStringArray(sa, s) == -1 ) {
        nNewIndex = cb.AddString(s);
        cb.SetItemDataPtr( nNewIndex, pRecord );
        sa.Add(s);
      }
    }
  }
  if ( false==IsEmptyText(sNewValue) ) {
    nIndex = cb.FindString(-1, sNewValue);
    if ( CB_ERR==nIndex )
      nIndex = cb.AddString(sNewValue);
    cb.SetCurSel(nIndex);
  }
}

void CGeoCache::FillCityCB(CEraComboBox& cb, CEraComboBox& cbRegion, CEraComboBox& cbDistrict, const CString& sNewValue) {

  CString s, sRegion, sDistrict;
  CGeoRecord* pRegionRecord = NULL;
  int nIndex = cbRegion.GetCurSel();
  CMapStringToPtr map;
  if ( CB_ERR != nIndex ) {
    cbRegion.GetLBText(nIndex, sRegion);
    pRegionRecord = (CGeoRecord*)cbRegion.GetItemDataPtr(nIndex);
    if ( NULL==pRegionRecord || CB_ERR == (DWORD)pRegionRecord ) // region record not found...
      pRegionRecord = NULL;
  }
  nIndex = cbDistrict.GetCurSel();
  if ( CB_ERR != nIndex )
    cbDistrict.GetLBText(nIndex, sDistrict);

  if ( pRegionRecord ) {
    if ( !sDistrict.IsEmpty() ) { // District IS NOT empty
      for( int i(0); i < pRegionRecord->m_array.GetSize(); i++ ) {
        CGeoRecord* pRecord = (CGeoRecord*)pRegionRecord->m_array.GetAt(i);
        if ( pRecord->IsCity() ) {  // city can have districts as well
          if ( pRecord->m_Name==sDistrict || (false==pRecord->m_AltName.IsEmpty() && pRecord->m_AltName==sDistrict) ) { // the same district
            for( int i(0); i < pRecord->m_array.GetSize(); i++ ) {
              CGeoRecord* pChildRecord = (CGeoRecord*)pRecord->m_array.GetAt(i);
              map.SetAt(pChildRecord->m_Name, pChildRecord);
              for( int i(0); i < pChildRecord->m_array.GetSize(); i++ ) { // Бывают города, подчинённые районнам других городов: Донецкая обл, Пролетраский р-н (г. Донецка), г. Моспино
                CGeoRecord* pCityRecord = (CGeoRecord*)pChildRecord->m_array.GetAt(i);
                map.SetAt(pCityRecord->m_Name, pCityRecord);   // so add parent record to map
                /*
                if ( false==pCityRecord->m_AltName.IsEmpty() ) {
                  map.SetAt(pCityRecord->m_AltName, pCityRecord);   // so add parent record to map
                }
                */
              }
            }
          }
          else if ( pRecord->HasChildren() ) { // City can has districts
            for( int i(0); i < pRecord->m_array.GetSize(); i++ ) {
              CGeoRecord* pChildRecord = (CGeoRecord*)pRecord->m_array.GetAt(i);
              if ( pChildRecord->m_Name==sDistrict || (false==pChildRecord->m_AltName.IsEmpty() && pChildRecord->m_AltName==sDistrict) ) { // the same district
                map.SetAt(pRecord->m_Name, pRecord);
                for( int i(0); i < pChildRecord->m_array.GetSize(); i++ ) {
                  CGeoRecord* pCityRecord = (CGeoRecord*)pChildRecord->m_array.GetAt(i);
                  map.SetAt(pCityRecord->m_Name, pCityRecord);   // so add parent record to map
                }
              }
            }
          }
        }
        else if ( pRecord->IsDistrict() && pRecord->m_Name==sDistrict ) { // district in region can have a cities
          for( int i(0); i < pRecord->m_array.GetSize(); i++ ) {
            CGeoRecord* pChildRecord = (CGeoRecord*)pRecord->m_array.GetAt(i);
            map.SetAt(pChildRecord->m_Name, pChildRecord);
          }
        }
      }
    }
    else { // District IS empty
      for( int i(0); i < pRegionRecord->m_array.GetSize(); i++ ) {
        CGeoRecord* pRecord = (CGeoRecord*)pRegionRecord->m_array.GetAt(i);
        if ( pRecord->IsCity() ) {  // cities of region
          map.SetAt(pRecord->m_Name, pRecord);
          for( int i(0); i < pRecord->m_array.GetSize(); i++ ) { // city can have city as well
            CGeoRecord* pChildRecord = (CGeoRecord*)pRecord->m_array.GetAt(i);
            if ( pChildRecord->IsCity() ) {
              map.SetAt(pChildRecord->m_Name, pChildRecord);
            }
          }
        }
        else {
          for( int i(0); i < pRecord->m_array.GetSize(); i++ ) {
            CGeoRecord* pChildRecord = (CGeoRecord*)pRecord->m_array.GetAt(i);
            if ( pChildRecord->IsCity() ) { // the same district
              map.SetAt(pChildRecord->m_Name, pChildRecord);   // so add parent record to map
              break;
            }
          }
        }
      }
    }
  }

  cb.ResetContent();
  POSITION pos = map.GetStartPosition();
  CStringArray sa;
  while ( pos ) {
    CString sKey;
    CGeoRecord* pRecord = NULL;
    map.GetNextAssoc(pos, sKey, (void *&)pRecord);
    if ( pRecord ) {
      int nNewIndex;
      CString s = pRecord->GetName();
      if ( FindInStringArray(sa, s) == -1 ) {
        nNewIndex = cb.AddString(s);
        cb.SetItemDataPtr( nNewIndex, pRecord );
        sa.Add(s);
      }
      s = pRecord->GetAltName();
      if ( false==s.IsEmpty() && FindInStringArray(sa, s) == -1 ) {
        nNewIndex = cb.AddString(s);
        cb.SetItemDataPtr( nNewIndex, pRecord );
        sa.Add(s);
      }
    }
  }

  if ( false==IsEmptyText(sNewValue) ) {
    nIndex = cb.FindString(-1, sNewValue);
    if ( CB_ERR==nIndex )
      nIndex = cb.AddString(sNewValue);
    cb.SetCurSel(nIndex);
  }
}

void CGeoCache::FillCityCBByCountryCities(CEraComboBox& cb, CEraComboBox& cbCountry, const CString& sNewValue) {
  CPtrArray Cities;
  cb.ResetContent();
  CString szCountry;
  int nIndex = cbCountry.GetCurSel();
  if ( CB_ERR != nIndex )
    cbCountry.GetLBText(nIndex, szCountry);
  if ( false==szCountry.IsEmpty() )  {
    CGeoRecord* pCountry = GetCountry(szCountry);
    if ( pCountry ) {
      for( int i(0); i < pCountry->m_array.GetSize(); i++ ) {
        CGeoRecord* pRecord = (CGeoRecord*)pCountry->m_array.GetAt(i);
        if ( pRecord->IsCity() ) {
          int nNewIndex = cb.AddString(pRecord->GetName());
          cb.SetItemDataPtr( nNewIndex, pRecord );
        }
      }
    }
  }
  if ( false==IsEmptyText(sNewValue) ) {
    nIndex = cb.FindString(-1, sNewValue);
    if ( CB_ERR==nIndex )
      nIndex = cb.AddString(sNewValue);
    cb.SetCurSel(nIndex);
  }
}

CString CGeoCache::FindFullCountry(const CString& sCountry) {
  CGeoRecord* pRecord = theGeoCache.GetCountry(&m_array, sCountry);
  if ( pRecord && !IsEmptyText(pRecord->m_AltName) ) {
    return pRecord->m_AltName;
  }
  return sCountry;
}

void CGeoCache::RemoveRecordFromArray(CGeoRecord* pRecord) {
  for( int i(0); i < m_array.GetSize(); i++ ) {
    if ( m_array.GetAt(i)==pRecord ) {
      m_array.RemoveAt(i);
      pRecord->RemoveRecord();
      delete pRecord;
      break;
    }
  }
}


/************************************** : by VK at 27.01.2008 10:59:17 **\

/////////////////////////////////////////////////////////////////////////////
// CGeoListView dialog
BEGIN_MESSAGE_MAP(CGeoListView, CGeoListViewBase)
  //{{AFX_MSG_MAP(CGeoListView)
  ON_WM_DESTROY()
	ON_NOTIFY(TVN_SELCHANGED, IDC_GEOTREE, OnSelchangedGeoTree)
	ON_NOTIFY(NM_CLICK, IDC_GEOTREE, OnClickGeotree)
	ON_NOTIFY(NM_RCLICK, IDC_GEOTREE, OnRclickGeoTree)
	ON_NOTIFY(NM_RCLICK, IDC_GEOLIST, OnRclickGeoList)
	ON_COMMAND(IDD_ADDCOUNTRY, OnAddCountry)
	ON_COMMAND(IDD_ADDDISTRICT, OnAddDistrict)
	ON_COMMAND(IDD_ADDREGION, OnAddRegion)
	ON_COMMAND(IDD_ADDCITY, OnAddCity)
	ON_COMMAND(IDD_RENAME, OnRename)
	ON_COMMAND(IDD_SETTYPE_COUNTRY, OnSetCountry)
  ON_COMMAND(IDD_SETTYPE_REGION, OnSetRegion)
  ON_COMMAND(IDD_SETTYPE_TERRITORY, OnSetTerritory)
  ON_COMMAND(IDD_SETTYPE_DISTRICT, OnSetDistrict)
  ON_COMMAND(IDD_SETTYPE_CITY, OnSetCity)
  ON_COMMAND(IDD_SETTYPE_MAINCITY, OnSetMainCity)
  ON_COMMAND(IDD_SETTYPE_SMT, OnSetSMT)
  ON_COMMAND(IDD_SETTYPE_HAMLET, OnSetHamlet)
  ON_COMMAND(IDD_SETTYPE_VILLAGE, OnSetVillage)
	ON_COMMAND(IDD_DELETE, OnDelete)
	ON_NOTIFY(TVN_KEYDOWN, IDC_GEOTREE, OnKeydownGeoTree)
  ON_WM_MENUSELECT()
	ON_NOTIFY(NM_RETURN, IDC_GEOTREE, OnReturnGeotree)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_GEOTREE, OnEndlabeleditGeoTree)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_GEOLIST, OnEndlabeleditGeoList)
  ON_UPDATE_COMMAND_UI(ID_RECORD_NEW, OnUpdateRecordNew)
  ON_COMMAND(ID_RECORD_NEW, OnRecordNew)
  ON_COMMAND(ID_HELP, OnHelp)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CGeoListView, CGeoListViewBase)
CGeoListView::CGeoListView()
           :CGeoListViewBase(IDD_GEOGRAPHY) {
  m_fGradientFill = TRUE;
  m_MenuType = GEO_MENU_TYPE_TREE;
}
CGeoListView::~CGeoListView() {
}
void CGeoListView::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
}
void CGeoListView::DoDataExchange(CDataExchange* pDX) {
  CGeoListViewBase::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CGeoListView)
	DDX_Control(pDX, IDC_GEOTREE, m_GeoTree);
	DDX_Control(pDX, IDC_GEOLIST, m_GeoList);
//}}AFX_DATA_MAP
}

int CGeoListView::GetImageIndex(const CGeoRecord* pRecord) {
  int imageIndex = 0;
  if ( pRecord->IsCountry() ) {
    if ( pRecord->m_Name==_T("Україна") )
      imageIndex = 7;
    else
      imageIndex = 0;
  }
  else if ( pRecord->IsRegion() )
    imageIndex = 1;
  else if ( pRecord->IsCity() )
    imageIndex = 2;
  else if ( pRecord->IsDistrict() )
    imageIndex = 3;
  else if ( pRecord->m_Type.Find("смт")==0 )
    imageIndex = 4;
  else if ( pRecord->m_Type==_T("с") || pRecord->m_Type==_T("с.") )
    imageIndex = 6;
  else if ( pRecord->m_Type.Find("слщ")==0 || pRecord->m_Type.Find("с-ще")==0 || pRecord->m_Type.Find("сще")==0 || pRecord->m_Type==_T("селище") )
    imageIndex = 5;
  else
    imageIndex = 6;
  return imageIndex;
}
void CGeoListView::Load(CPtrArray* pArray, HTREEITEM hParent) {
  for( int i(0); i < pArray->GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)pArray->GetAt(i);
    if ( pRecord ) {
      int imageIndex = GetImageIndex(pRecord);
      CString s = pRecord->m_Name;
      if ( !pRecord->m_AltName.IsEmpty() )
        s.Format(_T("%s (%s)"), pRecord->m_Name, pRecord->m_AltName );
      
      HTREEITEM hInsertAfter = TVI_LAST;
      if ( s==_T("Україна") )
        hInsertAfter = TVI_FIRST;
      HTREEITEM hItem = m_GeoTree.InsertItem(s, imageIndex, imageIndex, hParent, hInsertAfter);
      m_GeoTree.SetItemData( hItem, (DWORD)pRecord);
      pRecord->m_hItem = hItem;
      if ( pRecord->m_array.GetSize() )
        Load(&pRecord->m_array, hItem);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// CGeoListView message handlers
void CGeoListView::OnInitialUpdate()  {
  CGeoListViewBase::OnInitialUpdate();
  CChildFrame* pFrame = (CChildFrame*)GetParentFrame();
  pFrame->m_pView = this;
  theApp.m_pGeoFrame = pFrame;

  CString strTitle = _T("Список географічних назв");
  if ( theDataManager.m_dbLists.IsOpen() ) {
    strTitle.Format(_T("%s - Список географічних назв"), theDataManager.m_dbLists.GetName());
  }

  GetDocument()->SetTitle(strTitle);
  CRect rc;
  GetClientRect(&rc);
  OnSize(SIZE_MAXIMIZED, rc.Width(), rc.Height());

	//
	// Assign an image list to the tree view control.
	//
  m_ImageList.Create( IDIL_GEOTREE, 16, 1, RGB(255, 0, 255) );

  m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_UKRAINE));

  m_GeoTree.SetImageList (&m_ImageList, TVSIL_NORMAL);

  m_GeoList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);
  m_GeoList.InsertColumn(0, _T("Назва"), LVCFMT_LEFT, 256);
  m_GeoList.InsertColumn(1, _T("Тип"),   LVCFMT_LEFT,  64);
  m_GeoList.SetImageList (&m_ImageList, LVSIL_SMALL);

	//
	// Add items to the tree.
	//
  Load(&theGeoCache.m_array, TVI_ROOT);

}
void CGeoListView::OnDestroy() {
  theApp.m_pGeoFrame = NULL;
	CGeoListViewBase::OnDestroy();
}

void CGeoListView::RedrawListItem(int nItem, CGeoRecord* pRecord) {
  m_GeoList.SetItem(nItem, 0, LVIF_TEXT|LVIF_IMAGE, pRecord->m_Name, GetImageIndex(pRecord), 0, 0, (LPARAM)pRecord);
  m_GeoList.SetItemText(nItem, 1, pRecord->GetTypeName());
  m_GeoList.SetItemData(nItem, (DWORD)pRecord);
}
void CGeoListView::FillGeoList(CGeoRecord* pParentRecord) {
  m_GeoList.DeleteAllItems();
  if ( NULL==pParentRecord )
    return;
  for( int i(0); i < pParentRecord->m_array.GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)pParentRecord->m_array.GetAt(i);
    m_GeoList.InsertItem(i, pRecord->m_Name, GetImageIndex(pRecord) );
    RedrawListItem(i, pRecord);
  }
}
void CGeoListView::OnSelchangedGeoTree(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_GeoTree.GetSelectedItem();
  if ( NULL==hItem ) {
    return;
  }
  CGeoRecord* pRecord = (CGeoRecord*)m_GeoTree.GetItemData(hItem);
  if ( pRecord ) {
    FillGeoList(pRecord);
  }
	*pResult = 0;
}
void CGeoListView::OnClickGeotree(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: Add your control notification handler code here
	CPoint p;
  GetCursorPos(&p);
  m_GeoTree.ScreenToClient(&p);
  UINT uFlags;
  HTREEITEM hItem = m_GeoTree.HitTest(p, &uFlags);
  m_GeoTree.SelectItem(hItem);
	*pResult = 0;
}

void CGeoListView::TrackGeoAddMenu(CPoint& p) {
	CNewMenu menu;
  menu.LoadMenu(IDM_GEOMENU);
  CNewMenu* pPopup = (CNewMenu*)menu.GetSubMenu(0);
  if ( pPopup )
    pPopup = (CNewMenu*)pPopup->GetSubMenu(0);
  pPopup->SetMenuTitle(_T("Додати"), MFT_GRADIENT|MFT_SIDE_TITLE|MFT_LINE);
  pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON, p.x, p.y, this);
}
void CGeoListView::OnRclickGeoTree(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: Add your control notification handler code here
  m_MenuType = GEO_MENU_TYPE_TREE;
  OnClickGeotree(pNMHDR, pResult);
  CPoint p;
	CNewMenu menu;
  GetCursorPos(&p);
  //m_GeoTree.ScreenToClient(hWnd, &p);
  menu.LoadMenu(IDM_GEOMENU);
  CNewMenu* pPopup = (CNewMenu*)menu.GetSubMenu(0);
  pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON, p.x, p.y, this);
	*pResult = 0;
}
void CGeoListView::OnRclickGeoList(NMHDR* pNMHDR, LRESULT* pResult) {
  m_MenuType = GEO_MENU_TYPE_LIST;
  CPoint p;
  GetCursorPos(&p);
	CNewMenu menu;
  menu.LoadMenu(IDM_GEOMENU);
  CNewMenu* pPopup = (CNewMenu*)menu.GetSubMenu(0);
  pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON, p.x, p.y, this);
	*pResult = 0;
}

HTREEITEM CGeoListView::FindRecordOnTree(CGeoRecord* pRecord, HTREEITEM hItem) {
  if ( NULL==hItem ) {
    hItem = m_GeoTree.GetSelectedItem();
  }
  if ( hItem ) {
    if ( (CGeoRecord*)m_GeoTree.GetItemData(hItem)==pRecord )
      return hItem;
     HTREEITEM hChildItem = m_GeoTree.GetChildItem(hItem);
     while ( hChildItem ) {
        if ( (CGeoRecord*)m_GeoTree.GetItemData(hChildItem)== pRecord )
          return hChildItem;
        HTREEITEM hNextItem = m_GeoTree.GetNextItem(hChildItem, TVGN_NEXT);
        if ( hNextItem ) {
          if ( (CGeoRecord*)m_GeoTree.GetItemData(hNextItem)==pRecord )
            return hNextItem;
          else {
            HTREEITEM hItem = FindRecordOnTree(pRecord, hNextItem);
            if ( hItem )
              return hItem;
          }
        }
        hChildItem = hNextItem;
     }
  }
  return NULL;
}
int CGeoListView::FindRecordInList(CGeoRecord* pRecord) {
  LVFINDINFO fi;
  fi.flags = LVFI_PARAM;
  fi.lParam = (LPARAM)pRecord;
  return m_GeoList.FindItem(&fi);
}

CGeoRecord* CGeoListView::GetSelectedTreeRecord() {
  HTREEITEM hItem = m_GeoTree.GetSelectedItem();
  if ( hItem )
    return (CGeoRecord*)m_GeoTree.GetItemData(hItem);
  return NULL;
}
CGeoRecord* CGeoListView::GetSelectedListRecord() {
  POSITION pos = m_GeoList.GetFirstSelectedItemPosition();
  if ( pos ) {
    int nItem = m_GeoList.GetNextSelectedItem(pos);
    return (CGeoRecord*)m_GeoList.GetItemData(nItem);
  }
  return NULL;
}

CGeoRecord* CGeoListView::GetSelectedRecord() {
  CGeoRecord* pRecord = NULL;
  switch(m_MenuType) {
    case GEO_MENU_TYPE_TREE:
      pRecord = GetSelectedTreeRecord();
      if ( pRecord )
        return pRecord;
      return GetSelectedListRecord();
    case GEO_MENU_TYPE_LIST:
      pRecord = GetSelectedListRecord();
      if ( pRecord )
        return pRecord;
      return GetSelectedTreeRecord();
  }
  return NULL;
}

void CGeoListView::AddToTreeAndList(CGeoRecord* pRecord) {
  int imageIndex = GetImageIndex(pRecord);
  CGeoRecord* pParentRecord = pRecord->m_pParent;
  HTREEITEM hParentItem = NULL;
  if ( NULL==pParentRecord )
    hParentItem = TVI_ROOT;
  else {
    hParentItem = pParentRecord->m_hItem;
  }
  CString s = pRecord->m_Name;
  if ( !pRecord->m_AltName.IsEmpty() )
    s.Format(_T("%s (%s)"), pRecord->m_Name, pRecord->m_AltName);

  HTREEITEM hNewItem = m_GeoTree.InsertItem(s, imageIndex, imageIndex, hParentItem);
  if ( hNewItem ) {
    m_GeoTree.SetItemData(hNewItem, (DWORD)pRecord);
    pRecord->m_hItem = hNewItem;
    m_GeoTree.SetItem(hNewItem, TVIF_STATE, NULL, 0, 0, TVIS_BOLD, TVIS_BOLD, 0);

    TVSORTCB tvSort;
    tvSort.hParent      = hParentItem; // hParent Item
    tvSort.lParam       = (LPARAM)&m_GeoTree;
    tvSort.lpfnCompare  = GetSortCmp;

    m_GeoTree.SortChildrenCB(&tvSort);
    m_GeoTree.EnsureVisible(hNewItem);

    HTREEITEM hSelectedItem = m_GeoTree.GetSelectedItem();
    if ( hSelectedItem==hParentItem ) {
      int nItem = m_GeoList.InsertItem(m_GeoList.GetItemCount(), pRecord->m_Name, GetImageIndex(pRecord) );
      RedrawListItem(nItem, pRecord);
      m_GeoList.EnsureVisible(nItem, FALSE);
    }
  }
}
void CGeoListView::OnAddCountry() {
	// TODO: Add your command handler code here
  CAddGeoDlg dlg(this, GT_COUNTRY);
  //dlg.m_pParentGeoRecord = GetSelectedRecord();
  dlg.DoModal();
  if ( dlg.m_fOk && dlg.m_pRecord ) {
    AddToTreeAndList(dlg.m_pRecord);
  }
}
void CGeoListView::OnAddDistrict() {
	CAddGeoDlg dlg(this, GT_DISTRICT);
  dlg.m_pParentGeoRecord = GetSelectedRecord();
  dlg.DoModal();
  if ( dlg.m_fOk && dlg.m_pRecord ) {
    AddToTreeAndList(dlg.m_pRecord);
  }
}

void CGeoListView::OnAddRegion() {
	CAddGeoDlg dlg(this, GT_REGION);
  dlg.m_pParentGeoRecord = GetSelectedRecord();
  dlg.DoModal();
}

void CGeoListView::OnAddCity() {
	CAddGeoDlg dlg(this, GT_CITY);
  dlg.m_pParentGeoRecord = GetSelectedRecord();
  dlg.DoModal();
  if ( dlg.m_fOk && dlg.m_pRecord ) {
    AddToTreeAndList(dlg.m_pRecord);
  }
}

void CGeoListView::OnRename() {
  CGeoRecord* pRecord = NULL;
  CEdit* pEdit = NULL;
  if ( GEO_MENU_TYPE_TREE==m_MenuType ) {
    HTREEITEM hItem = m_GeoTree.GetSelectedItem();
    if ( hItem ) {
      pRecord = (CGeoRecord*)m_GeoTree.GetItemData(hItem);
      pEdit = m_GeoTree.EditLabel(hItem);
    }
  }
  else if ( GEO_MENU_TYPE_LIST==m_MenuType ) {
    int nItem = -1;
    POSITION pos = m_GeoList.GetFirstSelectedItemPosition();
    if ( pos )
      nItem = m_GeoList.GetNextSelectedItem(pos);
    if ( nItem != -1 ) {
      pRecord = (CGeoRecord*)m_GeoList.GetItemData(nItem);
      pEdit = m_GeoList.EditLabel(nItem);
    }
  }
  if ( pEdit && pEdit->GetSafeHwnd() ) {
    CString sText;
    pEdit->GetWindowText(sText);
  }
}
void CGeoListView::SetType(LPCTSTR szType) {
  CGeoRecord* pRecord = GetSelectedRecord();
  if ( pRecord ) {
    pRecord->m_Type = szType;
    int nListItem = FindRecordInList(pRecord);
    if ( nListItem >=0 ) {
      RedrawListItem(nListItem, pRecord);      
    }
    HTREEITEM hItem = FindRecordOnTree(pRecord);
    if ( hItem ) {
      int nImage = GetImageIndex(pRecord);
      m_GeoTree.SetItem(hItem, TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_STATE, pRecord->m_Name, nImage, nImage, TVIS_BOLD, TVIS_BOLD, 0);
    }
    pRecord->Update();
  }
}
void CGeoListView::OnSetCountry() {
  SetType(_T("держава"));
}
void CGeoListView::OnSetRegion() {
  SetType(_T("обл."));
}
void CGeoListView::OnSetTerritory() {
  SetType(_T("край"));
}
void CGeoListView::OnSetDistrict() {
  SetType(_T("район"));
}
void CGeoListView::OnSetCity() {
  SetType(_T("м."));
}
void CGeoListView::OnSetMainCity() {
  SetType(_T("мср"));
}
void CGeoListView::OnSetSMT() {
  SetType(_T("смт"));
}
void CGeoListView::OnSetHamlet() {
  SetType(_T("с-ще"));
}
void CGeoListView::OnSetVillage() {
  SetType(_T("с."));
}
void CGeoListView::OnDelete() {
  HTREEITEM hItem = m_GeoTree.GetSelectedItem();
  if ( hItem ) {
    CString sText;
    CString sItemText = m_GeoTree.GetItemText(hItem);
    if ( m_GeoTree.ItemHasChildren(hItem) ) {
      sText.Format(_T("Назва \"%s\" має залежні назви. Знищить спочатку їх."), sItemText );
      AfxMessageBox(sText);
    }
    else {
      // theGeoCache.Load 
      CGeoRecord* pRecord = (CGeoRecord*)m_GeoTree.GetItemData(hItem);
      if ( pRecord ) {
        if ( pRecord->m_pParent )
          pRecord->m_pParent->RemoveRecordFromArray( pRecord );
        else
          theGeoCache.RemoveRecordFromArray( pRecord );
      }
      m_GeoTree.DeleteItem(hItem);
    }
  }
}

void CGeoListView::OnKeydownGeoTree(NMHDR* pNMHDR, LRESULT* pResult) {
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if ( pTVKeyDown->wVKey==VK_DELETE ) { 
    OnDelete();
  }
	*pResult = 0;
}
void CGeoListView::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) {
//	CMainFrameBase::OnMenuSelect(nItemID, nFlags, hSysMenu);
//  SendMessage(WM_SETMESSAGESTRING, nItemID); 
  AfxGetMainWnd()->SendMessage(WM_SETMESSAGESTRING, nItemID); 
}

void CGeoListView::OnReturnGeotree(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CGeoListView::OnEndlabeleditGeoTree(NMHDR* pNMHDR, LRESULT* pResult) {
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
  if ( pTVDispInfo->item.pszText ) {
    HTREEITEM hItem = pTVDispInfo->item.hItem;
    m_GeoTree.SetItemText(hItem, pTVDispInfo->item.pszText);
    CGeoRecord* pRecord = (CGeoRecord*)m_GeoTree.GetItemData(hItem);
    CString sName, sFullName;
    int lBracket(0), rBracket(0);
    sName = pTVDispInfo->item.pszText;
    lBracket = sName.Find('(');
    rBracket = sName.Find(')');
    // Абхазія (Республіка Абхазія)
    //         9                  28
    if ( lBracket >= 0 && rBracket > lBracket ) {
      pRecord->m_Name = Trim(sName.Left(lBracket));
      pRecord->m_AltName = sName.Mid(lBracket+1,rBracket-lBracket-1);
      pRecord->m_AltName.TrimRight('(');
      pRecord->m_AltName.TrimRight(')');
    }
    else {
      pRecord->m_Name = pTVDispInfo->item.pszText;
      pRecord->m_AltName.Empty();
    }
    pRecord->Update();
  }
  //pTVDispInfo->item.pszText
	*pResult = 0;
}

void CGeoListView::OnEndlabeleditGeoList(NMHDR* pNMHDR, LRESULT* pResult) {
	NMLVDISPINFO* pDispInfo = (NMLVDISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
  if ( pDispInfo->item.pszText ) {
    int nItem = pDispInfo->item.iItem;
    m_GeoList.SetItemText(nItem, 0, pDispInfo->item.pszText);
    CGeoRecord* pRecord = (CGeoRecord*)m_GeoList.GetItemData(nItem);
    CString sName, sFullName;
    int lBracket(0), rBracket(0);
    sName = pDispInfo->item.pszText;
    lBracket = sName.Find('(');
    rBracket = sName.Find(')');
    // Абхазія (Республіка Абхазія)
    //         9                  28
    if ( lBracket >= 0 && rBracket > lBracket ) {
      pRecord->m_Name = Trim(sName.Left(lBracket));
      pRecord->m_AltName = sName.Mid(lBracket+1,rBracket-lBracket-1);
      pRecord->m_AltName.TrimRight('(');
      pRecord->m_AltName.TrimRight(')');
    }
    else {
      pRecord->m_Name = pDispInfo->item.pszText;
      pRecord->m_AltName.Empty();
    }
    pRecord->Update();
  }
	*pResult = 0;
}

void CGeoListView::OnUpdateRecordNew(CCmdUI* pCmdUI) {
  pCmdUI->Enable( TRUE );
}
void CGeoListView::OnRecordNew() {
  CRect r;
  if ( ((CMainFrame*)AfxGetMainWnd())->GetCommandButtonRect(ID_RECORD_NEW, &r) ) {
    CPoint p(r.left, r.bottom);
    TrackGeoAddMenu(p);
  }
}

BOOL CGeoListView::PreTranslateMessage(MSG* pMsg) {
	// TODO: Add your specialized code here and/or call the base class
  if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) {
    CEdit* edit = m_GeoTree.GetEditControl();
    if (edit) {
      edit->SendMessage(WM_KEYDOWN, pMsg->wParam, pMsg->lParam);
      return TRUE;
    }
  }
      
	return CGeoListViewBase::PreTranslateMessage(pMsg);
}

void CGeoListView::OnHelp() {
  theApp.OnHelp(_T("Lists"), _T("#GeoList"));
}

\************************************** : by VK at 27.01.2008 10:59:30 **/
