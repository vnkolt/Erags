//
// Caches.cpp
//

#include "stdafx.h"
#include "Erags.h"

#include "Caches.h"
#include "DataManager.h"
#include "..\Common\CyrString.h"
#include "..\Common\DB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNameCache theMNames;
CNameCache theWNames;
CNameCache theMPatronymics;
CNameCache theWPatronymics;
CCitizenshipCache theCitizenships;
CHospitalCache theHospitals;
CStringCache theMIAs;
CStringCache theStreets;
CSortStringArray theBanks;
/////////////////////////////////////////////////////////////////////////////
// CNameCache
CNameCache::CNameCache() {
}
CNameCache::~CNameCache() {
  RemoveAll();
}

bool CNameCache::Load(LPCTSTR szTableName, LPCTSTR szFieldName, BOOL fSex) {
  RemoveAll();
  CString sql;
  sql.Format(_T("SELECT %s FROM %s WHERE SEX=%s"),
             szFieldName, szTableName, fSex ? "TRUE" : "FALSE");

  try {
    CDaoRecordset rs(&theDataManager.m_dbLists);
    rs.Open(dbOpenDynaset, sql, dbReadOnly);
    while ( !rs.IsEOF() ) {
      CString s = iDBStringField(rs, 0);
      CCyrString sCanonical(s), sLower(s);
      sCanonical.MakeCanonical();
      sLower.MakeLower();
      SetAt(sLower, sCanonical);
      rs.MoveNext();
    }
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return FALSE;
	}
  return true;
}

void CNameCache::FillCombo(CComboBox& cb, const CString& sFieldValue, bool reFill) {
  if ( reFill )
    cb.ResetContent();
  if ( 0==cb.GetCount() ) {
    POSITION pos = GetStartPosition();
    while( pos ) {
      CCyrString sKey, sValue;
      GetNextAssoc(pos, sKey, sValue);
      if ( !sValue.IsEmpty() )
        cb.AddString(sValue);
    }
  }

  if ( IsEmptyText(sFieldValue) ) {
    cb.SetCurSel(-1);
  }
  else  {
    int nIndex = cb.FindStringExact(-1, sFieldValue);
    if ( CB_ERR==nIndex )
      nIndex = cb.AddString(sFieldValue);
    cb.SetCurSel(nIndex);
  }
}

/////////////////////////////////////////////////////////////////////////////
// CCitizenshipCache
CCitizenshipCache::CCitizenshipCache() {
}
CCitizenshipCache::~CCitizenshipCache() {
  RemoveAll();
}
bool CCitizenshipCache::Load() {
  RemoveAll();
  CString sql = _T("SELECT CITIZENSHIP, FULLCITIZENSHIP FROM CITIZENSHIPS");

  try {
    CDaoRecordset rs(&theDataManager.m_dbLists);
    rs.Open(dbOpenDynaset, sql, dbReadOnly);
    while ( !rs.IsEOF() ) {
      CString sCitizenship, sFullCitizenship;
      sCitizenship     = iDBStringField(rs, 0);
      sFullCitizenship = iDBStringField(rs, 1);
      SetAt(sCitizenship, sFullCitizenship);
      rs.MoveNext();
    }
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return FALSE;
	}
  return true;
}

void CCitizenshipCache::FillCombo(CComboBox& cb, const CString& sFieldValue) {
  if ( 0==cb.GetCount() ) {
    POSITION pos = GetStartPosition();
    while( pos ) {
      CString sKey, sValue;
      GetNextAssoc(pos, sKey, sValue);
      if ( !sKey.IsEmpty() )
        cb.AddString(sKey);
    }
  }
  if ( IsEmptyText(sFieldValue) ) {
    cb.SetCurSel(-1);
  }
  else {
    int nIndex = cb.FindStringExact(-1, sFieldValue);
    if ( CB_ERR==nIndex )
      nIndex = cb.AddString(sFieldValue);
    cb.SetCurSel(nIndex);
  }
}

CString CCitizenshipCache::GetValue(const CString& sKey) {
  CString sValue;
  Lookup(sKey, sValue);
  return sValue;
}
//
// CStringCache class members
//
CStringCache::CStringCache() {
}
CStringCache::~CStringCache() {
  Clear();
}
void CStringCache::Clear() {
  m_array.RemoveAll();
}
bool CStringCache::Load(LPCSTR szSQL) {
  Clear();
  try {
    CDaoRecordset rs(&theDataManager.m_dbLists);
    rs.Open(dbOpenDynaset, szSQL, dbReadOnly);
    while ( !rs.IsEOF() ) {
      CString sName = iDBStringField(rs, 0);
      if ( !sName.IsEmpty() )
        m_array.Add( sName );
      rs.MoveNext();
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return false;
	}
  return true;
}

int CStringCache::Add(CComboBox& cb, const CString& sValue) {
  int nIndex = CB_ERR;
  CString s = Trim(sValue);
  if ( FALSE==s.IsEmpty() ) {
    nIndex = cb.FindStringExact(-1, sValue);
    if ( CB_ERR==nIndex ) 
      nIndex = cb.AddString(sValue);
    else
      cb.SetCurSel(nIndex);
  }
  return nIndex;
}
void CStringCache::FillCombo(CComboBox& cb, const CString& sValue) {
  if ( 0==cb.GetCount() ) {
    for( int i(0); i < m_array.GetSize(); i++ ) {
      CString s = m_array.GetAt(i);
      if ( !s.IsEmpty() ) {
        cb.AddString(s);
      }
    }
  }
  if ( IsEmptyText(sValue) ) {
    cb.SetCurSel(-1);
  }
  else {
    int nIndex = cb.FindStringExact(-1, sValue);
    if ( CB_ERR==nIndex ) {
      nIndex = Add(cb, sValue);
      cb.SetCurSel(nIndex);
    }
  }
}

//
// CHospitalCache members
//
CHospitalCache::CHospitalCache() {
}
CHospitalCache::~CHospitalCache() {
  Clear();
}
void CHospitalCache::Clear() {
  m_map.RemoveAll();
}
bool CHospitalCache::Load() {
  Clear();
  CString sql = _T("SELECT PSEUDO, HOSPITAL FROM HOSPITALS");

  try {
    CDaoRecordset rs(&theDataManager.m_dbLists);
    rs.Open(dbOpenDynaset, sql, dbReadOnly);
    while ( !rs.IsEOF() ) {
      CString sPseudo   = iDBStringField(rs, 0);
      CString sHospital = iDBStringField(rs, 1);
      if ( !sPseudo.IsEmpty() ) {
        m_map.SetAt(sPseudo, sHospital);
      }
      rs.MoveNext();
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return false;
	}

  return true;
}

//void CHospitalCache::FillCombo(CComboBox& cb1, CComboBox& cb2, const CString& sFieldValue)
void CHospitalCache::FillCombo(CComboBox& cbMedCertPseudo, CComboBox& cbMedCertBy, const CString& sFieldValue) {
  if ( 0==cbMedCertPseudo.GetCount() || 0==cbMedCertBy.GetCount() ) {
    POSITION pos = m_map.GetStartPosition();
    while ( pos ) {
      CCyrString sKey, sValue;
      m_map.GetNextAssoc(pos, sKey, sValue);
      if ( !sKey.IsEmpty() ) {
        cbMedCertPseudo.AddString(sKey);
        cbMedCertBy.AddString(sValue);    
      }
    }
  }
  if ( IsEmptyText(sFieldValue) ) {
    cbMedCertBy.SetCurSel(-1);
  }
  else {
    int nIndex = cbMedCertBy.FindStringExact(-1, sFieldValue);
    if ( CB_ERR==nIndex ) {
      nIndex = cbMedCertBy.AddString(sFieldValue);
    }
    cbMedCertBy.SetCurSel(nIndex);
  }
}

BOOL CHospitalCache::Lookup(const CString& sKey, CString& sValue) {
  return m_map.Lookup(sKey, sValue);
}

//
// CSortStringArray
//
int CSortStringArray::CompareAsc(int iA, int iB){
	return strcoll(GetAt(iA), GetAt(iB));
}
int CSortStringArray::CompareDesc(int iA, int iB){
	return strcoll(GetAt(iB), GetAt(iA));
}

void CSortStringArray::Swap(int iA, int iB){
CString sA(GetAt(iA)), sB(GetAt(iB));
	SetAt(iA, sB);
	SetAt(iB, sA);
}

void CSortStringArray::Sort(BOOL bAscending){
int i,j,g;
int  nelem = GetSize();
	for( g = nelem/2; g>0; g /= 2 )
		for( i = g; i < nelem; i++)
			for( j = i-g; j >= 0; j -= g ){
				int iA(j), iB(j+g);
        int iSortRes = (bAscending) ? CompareAsc(iA, iB)
                                    : CompareDesc(iA, iB);
				if( iSortRes > 0 ){
					Swap(iA, iB);
				}
	 			else break;
	}
}
