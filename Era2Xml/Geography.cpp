//
// Geography.cpp
//

#include "stdafx.h"
#include "Geography.h"
#include "db.h"

#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BOOL PeekAndPump();

CGeoCache    theGeoCache;


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
    else if ( m_Type==_T("х") || m_Type==_T("х.") || m_Type==_T("х-р") || m_Type==_T("хут≥р") )
      *pDest = _T("хут≥р");
    else if ( m_Type==_T("ст.") || m_Type==_T("ст-ц≥€") || m_Type==_T("станц≥€") )
      *pDest = _T("станц≥€");
    else if ( m_Type==_T("ст-ц€") || m_Type==_T("с-ц€") || m_Type==_T("станиц€") )
      *pDest = _T("станиц€");
    else if ( m_Type.GetAt(0)=='с' )
      *pDest = _T("село");
  }
  return true;
}

int CGeoRecord::GetGeoTypeWeight() {
  if ( IsCountry() ) {
/************************************** : by VK at 03.07.2005 22:05:19 **\
    if ( m_Name==_T("”крањна") ) {
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
    return "м≥сто";
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
    int OldPercent = 0;
    while ( !rs.IsEOF() ) {
      CGeoRecord* pRecord = new CGeoRecord();
      pRecord->m_ID        = GetFieldLong  (rs, "ID");
      pRecord->m_ParentID  = GetFieldLong  (rs, "PARENT");
      pRecord->m_Type      = GetFieldString(rs, "TYPE");
      pRecord->m_Name      = GetFieldString(rs, "NAME");
      pRecord->m_AltName   = GetFieldString(rs, "FULLNAME");
      pRecord->m_ZipCode   = GetFieldString(rs, "ZIPCODE");
      pRecord->m_PhoneCode = GetFieldString(rs, "PHONECODE");
      pRecord->m_Directory = GetFieldString(rs, "DIRINQ");
      rs.MoveNext();

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
        if ( pProgressCtrl ) {
          pProgressCtrl->SetPos(NewPercent);
        }
        if ( pStatic ) {
          pStatic->SetWindowText(GetGeoPath(pRecord));
        }
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
  GeoRefill(db);
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
CGeoRecord* CGeoCache::GetCity(CPtrArray* pArray, const CString& s, CGeoRecord** ppCity) {
  if ( s.IsEmpty() )
    return NULL;

  CString sCity = Trim(s);
  CString s2 = sCity.Right(2),
          s3 = sCity.Right(3),
          s4 = sCity.Right(4);
  if (    s2==" м"      // м≥сто
       || s2==" с"      // село
       || s2==" х" )    // хут≥р
    sCity = sCity.Left( sCity.GetLength()-2 );
  else if(   s3==" м."   // м≥сто
          || s3==" с."   // село
          || s3==" ст"   // станц≥€, станиц€
          || s3==" х." ) // хут≥р
    sCity = sCity.Left( sCity.GetLength()-3 );
  else if (   s4==" ст."  // станц≥€, станиц€
           || s4==" х-р" )// хут≥р
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

  if ( sCity.Find(' ')>0 && (sCity.Find("м.")>0 || sCity.Find("м≥сто ")>0 || sCity.Find("смт")>0 || sCity.Find("с.")>0 || sCity.Find("с-ще")>0 || sCity.Find("слщ")>0) ) {
    CString szCity = sCity; 
    szCity.Replace(_T("м."), _T(""));
    szCity.Replace(_T("м≥сто "), _T(""));
    szCity.Replace(_T("с."), _T(""));
    szCity.Replace(_T("смт."), _T(""));
    szCity.Replace(_T("смт"), _T(""));
    szCity.Replace(_T("слщ"), _T(""));
    szCity.Replace(_T("с-ще"), _T(""));
    szCity.Replace(_T(","), _T(" "));
    CString szTok1 = GetTok(szCity, 0, _T(" "));
    CString szTok2 = GetTok(szCity, 1, _T(" "));
    CString szTok3 = GetTok(szCity, 2, _T(" "));
    CString szCity1 = szTok1;
    CString szCity2 = szTok2;
    if ( szTok3.IsEmpty() ) { // ƒве лексемы
      CGeoRecord* pRecord = GetCity(pArray, szCity1, NULL);
      if ( pRecord ) {
        if ( ppCity ) {
          *ppCity = GetCity(&pRecord->m_array, szCity2, NULL);
        }
        return pRecord;
      }
      pRecord = GetCity(pArray, szCity2, NULL);
      if ( pRecord ) {
        if ( ppCity ) {
          *ppCity = GetCity(&pRecord->m_array, szCity1, NULL);
        }
        return pRecord;
      }
    }
    else {
      szCity1.Format(_T("%s %s"), szTok1, szTok2);
      szCity2 = szTok3;
      CGeoRecord* pRecord = GetCity(pArray, szCity1, NULL);
      if ( pRecord ) {
        if ( ppCity ) {
          *ppCity = GetCity(&pRecord->m_array, szCity2, NULL);
        }
        return pRecord;
      }
      pRecord = GetCity(pArray, szCity2, NULL);
      if ( pRecord ) {
        if ( ppCity ) {
          *ppCity = GetCityInCity(&pRecord->m_array, szCity1);
        }
        return pRecord;
      }
    }
  }

  return NULL;
}

CGeoRecord* CGeoCache::GetCityInCity(CPtrArray* pArray, const CString& sCity) {
  for( int i(0); i < pArray->GetSize(); i++ ) {
    CGeoRecord* pChildRecord = (CGeoRecord*)pArray->GetAt(i);
    if ( pChildRecord->IsCity() ) {
      if ( pChildRecord->m_Name==sCity || pChildRecord->m_AltName==sCity ) {
        return pChildRecord;
      }
    }
    if ( pChildRecord->IsDistrict() ) {
      for( int i(0); i < pChildRecord->m_array.GetSize(); i++ ) {
        CGeoRecord* pCityRecord = (CGeoRecord*)pChildRecord->m_array.GetAt(i);
        if ( pCityRecord->m_Name==sCity || pCityRecord->m_AltName==sCity ) {
          return pCityRecord;
        }
      }
    }
  }
  return NULL;
}

#endif

CGeoRecord* CGeoCache::GetDistrict(CPtrArray* pArray, const CString& s, CGeoRecord** ppCity) {

  if ( s.IsEmpty() ) {
    return NULL;
  }

  for( int i(0); i < pArray->GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)pArray->GetAt(i);
    if ( pRecord->IsDistrict() ) {
      if ( pRecord->m_Name==s || pRecord->m_AltName==s /* New !!! */ ) {
        return pRecord;
      }
    }
  }

  if ( ppCity ) {
    for( int i(0); i < pArray->GetSize(); i++ ) {
      CGeoRecord* pCityRecord = (CGeoRecord*)pArray->GetAt(i);
      if ( pCityRecord->IsCity() && pCityRecord->HasChildren() ) {
        for( int i(0); i < pCityRecord->m_array.GetSize(); i++ ) {
          CGeoRecord* pDistrictRecord = (CGeoRecord*)pCityRecord->m_array.GetAt(i);
          if ( pDistrictRecord->IsDistrict() ) {
            if ( pDistrictRecord->m_Name==s || pDistrictRecord->m_AltName==s /* New !!! */ ) {
              *ppCity = pCityRecord;
              return pDistrictRecord;
            }
          }
        }
      }
    }
  }

  return NULL;
}

CString CGeoCache::FindFullCountry(const CString& sCountry) {
  CGeoRecord* pRecord = theGeoCache.GetCountry(&m_array, sCountry);
  if ( pRecord && !IsEmptyText(pRecord->m_AltName) ) {
    return pRecord->m_AltName;
  }
  return sCountry;
}


CString GetCity(LPCTSTR szCityWithType) {
  CString szCity(szCityWithType);

  TrimRight(szCity, _T(" м."));
  TrimRight(szCity, _T(" м"));
  TrimRight(szCity, _T(" м≥сто"));
  TrimRight(szCity, _T(" с"));
  TrimRight(szCity, _T(" с."));
  TrimRight(szCity, _T(" село"));
  TrimRight(szCity, _T(" слщ"));
  TrimRight(szCity, _T(" слщ."));
  TrimRight(szCity, _T(" смт"));
  TrimRight(szCity, _T(" смт."));
  TrimRight(szCity, _T(" х-р"));
  TrimRight(szCity, _T(" хут≥р"));
  TrimRight(szCity, _T(" ст-ц≥€"));
  TrimRight(szCity, _T(" ст-ц€"));
  TrimRight(szCity, _T(" ст."));

  return szCity;
}

BOOL PASCAL IsDistrictInCity(LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szDistrict, LPCTSTR szCity) {
  CString sCountry(szCountry), sRegion(szRegion), sCity(szCity), sDistrict(szDistrict);
  CGeoRecord* pCountryRecord  = NULL;
  CGeoRecord* pRegionRecord   = NULL;
  CGeoRecord* pCityRecord     = NULL;
  CGeoRecord* pDistrictRecord = NULL;

  pCountryRecord = theGeoCache.GetCountry(&theGeoCache.m_array, sCountry);

  if ( pCountryRecord ) {
    if ( NULL==pRegionRecord )
      pRegionRecord = theGeoCache.GetRegion( &pCountryRecord->m_array, sRegion );
    if ( pRegionRecord ) {
      if ( NULL==pCityRecord )
        pCityRecord = theGeoCache.GetCity( &pRegionRecord->m_array, sCity, NULL);
      if ( pCityRecord ) {
        if ( NULL==pDistrictRecord )
          pDistrictRecord = theGeoCache.GetDistrict( &pCityRecord->m_array, sDistrict, NULL);
      }
      else { // city not found
        if ( NULL==pDistrictRecord )
          pDistrictRecord = theGeoCache.GetDistrict( &pRegionRecord->m_array, sDistrict, NULL );
        if ( pDistrictRecord ) { // district in region
          if ( NULL==pCityRecord )
            pCityRecord = theGeoCache.GetCity( &pDistrictRecord->m_array, sCity, NULL );
        }
      }
    }
    if ( pCountryRecord && NULL==pCityRecord ) {
      pCityRecord = theGeoCache.GetCity( &pCountryRecord->m_array, sCity, NULL );
      if ( pCityRecord && NULL==pDistrictRecord) { // City in the country, region not need
        pDistrictRecord = theGeoCache.GetDistrict( &pCityRecord->m_array, sDistrict, NULL );
      }
    }
  }

  if ( pCityRecord && theGeoCache.GetDistrict(&pCityRecord->m_array, sDistrict, NULL) )
    return TRUE;
  return FALSE;
}

