//
// IniCache.cpp
//
#include "stdafx.h"
#include "EraABC.h"
#include "IniCache.h"

#include "..\Common\MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIniCache class members
CIniCache::CIniCache() {
  m_prs = NULL;
}
CIniCache::~CIniCache() {
  Close();
}
BOOL CIniCache::IsOpen() {
  return ( m_prs && m_prs->IsOpen() );
}
BOOL CIniCache::Open(CDaoDatabase& db) {
  if ( IsOpen() )
    return TRUE;
  try {
    if ( m_prs )
      delete m_prs;
    m_prs = new CDaoRecordset(&db);
    m_prs->Open(dbOpenTable, "[DEFAULTS]");
    return m_prs->IsOpen();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
	}
  if ( m_prs ) {
    delete m_prs;
    m_prs = NULL;
  }
  return FALSE;
}

void CIniCache::Close() {
  if ( m_prs ) {
    m_prs->Close();
    delete m_prs;
    m_prs = NULL;
  }
}
UINT CIniCache::HashKey(LPCTSTR szKey) {
  CString sKey = szKey;
	UINT nHash = 0;
  LPCTSTR key = sKey;
	while (*key)
		nHash = (nHash<<5) + nHash + *key++;
	return nHash;
}
CString CIniCache::GetPrivateProfileString(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal, BOOL fWrite/*=FALSE*/) {
  CString szMapKey;
  szMapKey.Format(_T("%s_%s"), szSect, szKey);
  CString sValue;
  if ( FALSE==fWrite ) {
    if ( m_keys.Lookup(szMapKey, sValue) )
      return sValue;  // found!
  }
  sValue = szDefVal;
  if ( IsOpen() ) {
    try {
      BOOL bFound = FALSE;
      m_prs->SetCurrentIndex(_T("SECTION"));
      UINT hash = HashKey(szSect);
      COleVariant ovHash((long)hash, VT_I4);
      if ( m_prs->Seek(_T("="), &ovHash) ) {
        while ( FALSE==m_prs->IsEOF() ) {
          UINT hHash = (UINT)GetFieldLong(m_prs, _T("SECTION"));
          if ( hHash != hash) {
            break;
          }
          CString sKey = GetFieldString(m_prs, _T("KEY"));
          if ( sKey.CompareNoCase(szKey)==0 ) {
            if ( fWrite ) {
              m_prs->Edit(); 
              m_prs->SetFieldValue(_T("VALUE"), (LPCTSTR)sValue);
              m_prs->Update();
            }
            else
              sValue = GetFieldString(m_prs, _T("VALUE"));
            bFound = TRUE;
            break;
          }
          m_prs->MoveNext();
        }
      }
      if ( FALSE==bFound ) {
        if ( FALSE==sValue.IsEmpty() && m_prs->CanAppend() ) {
          m_prs->AddNew();
          m_prs->SetFieldValue(_T("SECTION"), &ovHash);
          m_prs->SetFieldValue(_T("KEY"), szKey);
          m_prs->SetFieldValue(_T("VALUE"), (LPCTSTR)sValue);
          m_prs->Update();
        }
      }
    }
    catch (CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
  	}
  }
  m_keys.SetAt(szMapKey, sValue);
  return sValue;
}
CString CIniCache::GetPrivateProfileString(LPCTSTR szSect, LPCTSTR szKey) {
  CString sValue;
  if ( IsOpen() ) {
    try {
      m_prs->SetCurrentIndex(_T("SECTION"));
      UINT hash = HashKey(szSect);
      COleVariant ovHash((long)hash, VT_I4);
      if ( m_prs->Seek(_T("="), &ovHash) ) {
        while ( FALSE==m_prs->IsEOF() ) {
          UINT hHash = (UINT)GetFieldLong(m_prs, _T("SECTION"));
          if ( hHash != hash) {
            break;
          }
          CString sKey = GetFieldString(m_prs, _T("KEY"));
          if ( sKey.CompareNoCase(szKey)==0 ) {
            sValue = GetFieldString(m_prs, _T("VALUE"));
            break;
          }
          m_prs->MoveNext();
        }
      }
    }
    catch (CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
  	}
  }
  return sValue;
}

BOOL CIniCache::Load(CDaoDatabase& db) {
  if ( Open(db) ) {
    return TRUE;
	}
  return FALSE;
}

CString CIniCache::GetRAGS() {
  return GetPrivateProfileString(_T("COMMON"), _T("RAGS"), _T(""));
}

