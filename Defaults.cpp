//
// Defaults.cpp
//
#include "stdafx.h"
#include "Erags.h"
#include "DataManager.h"

#include "Caches.h"
#include "Defaults.h"
#include "RList.h"
#include "RNames.h"
#include "Utils.h"

#include "xMachine.h"

#include "..\Common\Crypto.h"
#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"
#include "..\Common\MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ERA_VERSION 51001

CString GetCity(LPCTSTR szCity, bool fTypeCity=false);

// HKEY_USERS\.DEFAULT\Control Panel\PowerCfg\GlobalPowerPolicy\Policies - real value
LPCTSTR szRegKey   = _T(".DEFAULT\\Control Panel\\PowerCfg\\GlobalPowerPolicy");
//LPCTSTR szRegValue = _T("Policies");
LPCTSTR szRegValue = _T("CurrentPolicyData");
// HKEY_USERS\.DEFAULT\Control Panel\PowerCfg\GlobalPowerPolicy\CurrentPolicyData - my value

SecurityData* ReadSecurityFromReg() {
  SecurityData* pSecurityData = NULL;
  LONG   lResult;
  HKEY   hKey = NULL;
  DWORD  dwType = NULL;
  DWORD  cbData = NULL;
  lResult = RegOpenKeyEx(HKEY_USERS, szRegKey, 0, KEY_QUERY_VALUE, &hKey);
  //lResult = RegOpenKey(HKEY_USERS, szRegKey, &hKey);
  if (lResult != ERROR_SUCCESS) {
    return NULL;
  }
  lResult = RegQueryValueEx(hKey, szRegValue, NULL, &dwType, NULL, &cbData);
  if (ERROR_SUCCESS==lResult && REG_BINARY == dwType) {
    BYTE* pData = new BYTE[cbData];
    lResult = RegQueryValueEx(hKey, szRegValue, NULL, &dwType, pData, &cbData);
    pSecurityData = new SecurityData;
    memcpy(pSecurityData, pData, sizeof(SecurityData));
    delete pData;
  }
  RegCloseKey(hKey);
  return pSecurityData;
}
void SetSecurityCheckSum(SecurityData* pSecurityData) {
  char* pCheckSum = (char*)&pSecurityData->cbSize;
  for( int i(0); i < sizeof(SecurityData)-sizeof(short); i++ ) {
    pSecurityData->CheckSum += pCheckSum[i];
  }
}
SecurityData* BuildSecurityStruct(SecurityData* pSecurityData) {
  memset(pSecurityData, 0, sizeof(SecurityData) );
  pSecurityData->EraVersion = ERA_VERSION;
  pSecurityData->cbSize = sizeof(SecurityData);
  pSecurityData->OsVersion = g_Shell;
  SetSecurityCheckSum(pSecurityData);
  return pSecurityData;
}
BOOL WriteSecurityToReg(SecurityData* pData) {
  LONG   lResult;
  HKEY   hKey = NULL;
  BOOL   bRet = FALSE;
  lResult = RegOpenKeyEx(HKEY_USERS, szRegKey, 0, KEY_WRITE, &hKey);
  if (lResult != ERROR_SUCCESS) {
    return bRet;
  }
  lResult = RegSetValueEx(hKey, szRegValue, 0, REG_BINARY, (BYTE*)pData, sizeof(SecurityData));
  if (ERROR_SUCCESS == lResult) {
    bRet++;
  }
  RegCloseKey(hKey);

  return bRet;
}


CIniCache theIniCache;

LPCTSTR g_szSvNeVidano = _T("Свідоцтво не ");
LPCTSTR g_szCNume = _T("000001");

void  HexToMyBin(LPTSTR szBin, LPCTSTR szHex, int binSize, DWORD dwXor);
DWORD GetXorValue(int nHour);

/////////////////////////////////////////////////////////////////////////////
// CIniCache class members
CIniCache::CIniCache() {
  m_prs = NULL;
  m_szCommonSect   = _T("COMMON");
  m_szBirthSect    = _T("BIRTH_FORM");
  m_szMarriageSect = _T("MARRIAGE_FORM");
  m_szDivorceSect  = _T("DIVORCE_FORM");
  m_szChangeSect   = _T("CHANGE_FORM");
  m_szDeathSect    = _T("DEATH_FORM");
  m_szAbbrSect     = _T("Abbreviations");
  memset(&m_Security, 0, sizeof(m_Security));
}
CIniCache::~CIniCache() {
  Close();
}
BOOL CIniCache::IsOpen() {
  return ( m_prs && m_prs->IsOpen() );
}
BOOL CIniCache::Open() {
  if ( IsOpen() )
    return TRUE;
  try {
    if ( m_prs )
      delete m_prs;
    m_prs = new CDaoRecordset(&theDataManager.m_dbLists);
    m_prs->Open(dbOpenTable, "[DEFAULTS]");

    g_fValidLKey = IsValidLKey();
    if ( FALSE==g_fValidLKey ) {
      int nDates = CalcDates();
      if ( nDates > 100 ) {
        
      }
    }
   
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
BOOL CIniCache::IsEmpty() {
  BOOL fRet = FALSE;
  if ( Open() ) {
    try {
      if ( m_prs->IsEOF() )
        fRet = TRUE;
      else {
        m_prs->MoveFirst();
        if ( m_prs->IsEOF() )
          fRet = TRUE;
      }
    }
    catch (CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
  	}
  }
  return fRet;
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

UINT CIniCache::GetPrivateProfileInt(LPCTSTR szSect, LPCTSTR szKey, UINT nDefVal) {
  CString szDefVal;
  szDefVal.Format(_T("%d"), nDefVal);
  return (UINT)( atol(GetPrivateProfileString(szSect, szKey, szDefVal)) );
}
BOOL CIniCache::GetPrivateProfileBinary(LPCTSTR szSect, LPCTSTR szKey, void* pData, UINT cbBytes) {
	ASSERT(szSect != NULL);
	ASSERT(szKey != NULL);
	ASSERT(pData != NULL);
	ASSERT(cbBytes != 0);
  memset(pData, 0, cbBytes);

  CString szValue = GetPrivateProfileString(szSect, szKey);
  if ( (UINT)szValue.GetLength() !=  cbBytes*2  )
    return false;

  HexStringToBin(szValue, szValue.GetLength(), pData, cbBytes);
  return true;
}
void CIniCache::WritePrivateProfileString(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal) {
  GetPrivateProfileString(szSect, szKey, szDefVal, TRUE);
}

void CIniCache::WritePrivateProfileInt(LPCTSTR szSect, LPCTSTR szKey, UINT nDefVal) {
  CString szDefVal;
  szDefVal.Format(_T("%d"), nDefVal);
  WritePrivateProfileString(szSect, szKey, szDefVal);
}
void CIniCache::WritePrivateProfileBinary(LPCTSTR szSect, LPCTSTR szKey, void* pData, UINT cbBytes) {
  CString szValue = BinToHexString((const char*)pData, cbBytes);
  WritePrivateProfileString(szSect, szKey, szValue);
}
CString CIniCache::GetSVal(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal) {
  return GetPrivateProfileString(szSect, szKey, szDefVal);
}
void CIniCache::SetSVal(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szValue) {
  WritePrivateProfileString(szSect, szKey, szValue);
}
UINT CIniCache::GetIVal(LPCTSTR szSect, LPCTSTR szKey, UINT iDefVal) {
  return GetPrivateProfileInt(szSect, szKey, iDefVal);
}
void CIniCache::SetIVal(LPCTSTR szSect, LPCTSTR szKey, UINT uValue) {
  CString sValue;
  sValue.Format(_T("%u"), uValue);
  WritePrivateProfileString(szSect, szKey, sValue);
}

void CIniCache::MakeFromIni() {
  CString sIniFile;
  sIniFile.Format(_T("%s\\Defaults.ini"), GetFilePath(theApp.GetHelperMDB()) );
  const int BUF_SIZE = 0x7F00;
  LPTSTR lpBuf = new TCHAR[BUF_SIZE];
  DWORD dwSize = ::GetPrivateProfileSectionNames(lpBuf, BUF_SIZE, sIniFile);
  if ( dwSize ) {
    TCHAR* p = lpBuf;
    LPTSTR pSectBuf = new TCHAR[BUF_SIZE];
    while( *p ) {
      dwSize = ::GetPrivateProfileSection(p, pSectBuf, BUF_SIZE, sIniFile);
      CString szSect(p);
      if ( dwSize ) {
        char* p = pSectBuf;
        while( *p ) {
          CString sKey   = GetTok(p, 0, _T("="));
          CString sValue = GetTok(p, 1, _T("="));
          if ( FALSE==sValue.IsEmpty() ) {
            WritePrivateProfileString(szSect, sKey, sValue);
          }
          p += strlen(p)+1;
        }
      }
      p += strlen(p)+1;
    }
    delete pSectBuf;
  }
  delete lpBuf;
}
BOOL CIniCache::Load() {
  if ( Open() ) {
    if ( IsEmpty() ) {
      MakeFromIni();
    }
/************************************** : by VK at 24.07.2005 9:00:58 **\
    try {
      m_prs->MoveFirst();
      while ( FALSE==m_prs->IsEOF() ) {
        
      }
    }
    catch (CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
  	}
\************************************** : by VK at 24.07.2005 9:01:03 **/
    FillAbbrCache();
    return TRUE;
	}
  return FALSE;
}

void CIniCache::FillAbbrCache() {
  m_AbbrMap.RemoveAll();
  if ( IsOpen() ) {
    try {
      m_prs->SetCurrentIndex(_T("SECTION"));
      UINT hash = HashKey(m_szAbbrSect);
      COleVariant ovHash((long)hash, VT_I4);
      if ( m_prs->Seek(_T("="), &ovHash) ) {
        while ( FALSE==m_prs->IsEOF() ) {
          UINT hHash = (UINT)GetFieldLong(m_prs, _T("SECTION"));
          if ( hHash != hash) {
            break;
          }
          CString sKey   = GetFieldString(m_prs, _T("KEY"));
          CString sValue = GetFieldString(m_prs, _T("VALUE"));

          if ( FALSE==sKey.IsEmpty() && FALSE==sValue.IsEmpty() )
            m_AbbrMap.SetAt(sKey, sValue);

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
}
POSITION CIniCache::GetAbbrStartPosition() {
  return m_AbbrMap.GetStartPosition();
}
BOOL CIniCache::LookupAbbr(LPCTSTR szKey, CString& sValue) {
  return m_AbbrMap.Lookup(szKey, sValue);
}
void CIniCache::GetNextAbbr(POSITION& pos, CString& sKey, CString& sValue) {
  m_AbbrMap.GetNextAssoc(pos, sKey, sValue);
}
CString CIniCache::GetCOUNTRY() {  
  return GetSVal(m_szCommonSect, _T("COUNTRY"), _T("Україна") );
}
void CIniCache::SetCOUNTRY(LPCTSTR szCountry) {
  SetSVal(m_szCommonSect, _T("COUNTRY"), szCountry );
}
CString CIniCache::GetREGION() {
  return GetSVal(m_szCommonSect, _T("REGION"), _T("") );
}
void CIniCache::SetREGION(LPCTSTR szRegion) {
  SetSVal(m_szCommonSect, _T("REGION"), szRegion );
}
CString CIniCache::GetCITY() {
  return GetSVal(m_szCommonSect, _T("CITY"), _T("") );
}
CString CIniCache::GetCITY_() {
  return GetCity(GetCITY());
}
void CIniCache::SetCITY(LPCTSTR szCity) {
  SetSVal(m_szCommonSect, _T("CITY"), szCity);
}
CString CIniCache::GetDISTRICT() {
  return GetSVal(m_szCommonSect, _T("DISTRICT"), _T("") );
}
void CIniCache::SetDISTRICT(LPCTSTR szDistrict) {
  SetSVal(m_szCommonSect, _T("DISTRICT"), szDistrict);
}
CString CIniCache::GetRAGS() {
  return GetSVal(m_szCommonSect, _T("RAGS"), _T("") );
}
void CIniCache::SetRAGS(LPCTSTR szRags) {
  SetSVal(m_szCommonSect, _T("RAGS"), szRags);
}
CString CIniCache::GetBoss() {
  return GetSVal(m_szCommonSect, _T("BOSS"), _T("") );
}
void CIniCache::SetBoss(LPCTSTR szBoss) {
  SetSVal(m_szCommonSect, _T("BOSS"), szBoss);
}
CString CIniCache::GetParent() {
  return GetSVal(m_szCommonSect, _T("PARENT"), _T("") );
}
void CIniCache::SetParent(LPCTSTR szParent) {
  SetSVal(m_szCommonSect, _T("PARENT"), szParent);
}

BOOL CIniCache::IsChildRags(const CString& szRags) {
  CRListRecord* pRecord = theRList.Lookup(theApp.m_RagsID);
  if ( NULL==pRecord )
    return false;
  if ( DBCompare(pRecord->m_Fullname, szRags)==0 ) {
    return true;
  }
  for( int i(0); i < pRecord->m_array.GetSize(); i++ ) {
    CRListRecord* pChildRecord = (CRListRecord*)pRecord->m_array.GetAt(i);
    if ( DBCompare(pChildRecord->m_Fullname, szRags)==0 )
      return true;
  }
  return false;
}
BOOL CIniCache::IsVyconcom(const CString& szRags) {
  if ( szRags.Left(2)==_T("В ") )
    return TRUE;
  if ( szRags.Left(2)==_T("в ") )
    return TRUE;
  if ( szRags.Find(_T("Виконком") )==0 )
    return TRUE;
  if ( szRags.Find(_T("виконком") )==0 )
    return TRUE;
  return FALSE;
}
CString CIniCache::GetVyconcomParent(const CString& sRags) {
  CString s;
  CRListRecord* pRecord = theRList.Lookup(sRags);
  if ( pRecord ) {
    pRecord  = theRList.Lookup(pRecord->m_ParentID);
    if ( pRecord )
      s = pRecord->m_Fullname;
  }
  return s;
}

CString CIniCache::GetByROVD() {
  return GetSVal(m_szCommonSect, _T("BYUMVS"), _T("") );
}
void CIniCache::SetByROVD(LPCTSTR szBy) {
  SetSVal(m_szCommonSect, _T("BYUMVS"), szBy );
}
CString CIniCache::GetToROVD() {
  return GetSVal(m_szCommonSect, _T("TOUMVS"), _T("") );
}
void CIniCache::SetToROVD(LPCTSTR szTo) {
  SetSVal(m_szCommonSect, _T("TOUMVS"), szTo );
}

CString CIniCache::GetByMil() {
  return GetSVal(m_szCommonSect, _T("BYMIL"), _T("") );
}
void CIniCache::SetByMil(LPCTSTR szBy) {
  SetSVal(m_szCommonSect, _T("BYMIL"), szBy );
}
CString CIniCache::GetToMil() {
  return GetSVal(m_szCommonSect, _T("TOMIL"), _T("") );
}
void CIniCache::SetToMil(LPCTSTR szTo) {
  SetSVal(m_szCommonSect, _T("TOMIL"), szTo );
}
CString CIniCache::GetByCourt() {
  return GetSVal(m_szCommonSect, _T("BYCOURT"), _T("") );
}
void CIniCache::SetByCourt(LPCTSTR szBy) {
  SetSVal(m_szCommonSect, _T("BYCOURT"), szBy );
}
CString CIniCache::GetToTax() {
  return GetSVal(m_szCommonSect, _T("TOTAX"), _T("") );
}
void CIniCache::SetToTax(LPCTSTR szTo) {
  SetSVal(m_szCommonSect, _T("TOTAX"), szTo );
}

CString CIniCache::GetNoCert() {
  return GetSVal(m_szCommonSect, _T("NOCERT"), _T("Свідоцтво не видано.") );
}
CString CIniCache::GetBIRTH_BP_COUNTRY() {
  return GetSVal(m_szBirthSect, _T("CHILD_BP_COUNTRY"), _T("Україна") );
}
void CIniCache::SetBIRTH_BP_COUNTRY(LPCTSTR szCountry) {
  SetSVal(m_szBirthSect, _T("CHILD_BP_COUNTRY"), szCountry );
}
UINT    CIniCache::GetBIRTH_BP_COUNTRY_CHECK() {
  return GetIVal(m_szBirthSect, _T("CHILD_BP_COUNTRY_CHECK"), 1);
}
void CIniCache::SetBIRTH_BP_COUNTRY_CHECK(UINT uCheck) {
  SetIVal(m_szBirthSect, _T("CHILD_BP_COUNTRY_CHECK"), uCheck);
}
CString CIniCache::GetBIRTH_BP_REGION() {
  return GetSVal(m_szBirthSect, _T("CHILD_BP_REGION"), _T("") );
}
void CIniCache::SetBIRTH_BP_REGION(LPCTSTR szRegion) {
  SetSVal(m_szBirthSect, _T("CHILD_BP_REGION"), szRegion );
}
UINT    CIniCache::GetBIRTH_BP_REGION_CHECK() {
  return GetIVal(m_szBirthSect, _T("CHILD_BP_REGION_CHECK"), 1);
}
void CIniCache::SetBIRTH_BP_REGION_CHECK(UINT uCheck) {
  SetIVal(m_szBirthSect, _T("CHILD_BP_REGION_CHECK"), uCheck);
}
CString CIniCache::GetBIRTH_BP_DISTRICT() {
  return GetSVal(m_szBirthSect, _T("CHILD_BP_DISTRICT"), _T("") );
}
void CIniCache::SetBIRTH_BP_DISTRICT(LPCTSTR szDistrict) {
  SetSVal(m_szBirthSect, _T("CHILD_BP_DISTRICT"), szDistrict );
}
UINT    CIniCache::GetBIRTH_BP_DISTRICT_CHECK() {
  return GetIVal(m_szBirthSect, _T("CHILD_BP_DISTRICT_CHECK"), 1);
}
void CIniCache::SetBIRTH_BP_DISTRICT_CHECK(UINT uCheck) {
  SetIVal(m_szBirthSect, _T("CHILD_BP_DISTRICT_CHECK"), uCheck);
}
CString CIniCache::GetBIRTH_BP_CITY() {
  return GetSVal(m_szBirthSect, _T("CHILD_BP_CITY"), _T("") );
}
void CIniCache::SetBIRTH_BP_CITY(LPCTSTR szCity) {
  SetSVal(m_szBirthSect, _T("CHILD_BP_CITY"), szCity );
}
UINT CIniCache::GetBIRTH_BP_CITY_CHECK() {
  return GetIVal(m_szBirthSect, _T("CHILD_BP_CITY_CHECK"), 1);
}
void CIniCache::SetBIRTH_BP_CITY_CHECK(UINT uCheck) {
  SetIVal(m_szBirthSect, _T("CHILD_BP_CITY_CHECK"), uCheck);
}

CString CIniCache::GetMDN() {
  return GetSVal(m_szBirthSect, _T("МДН"), _T("Медичне свідоцтво про народження") );
}

CString CIniCache::GetBIRTH_Seria() {
  return GetSVal(m_szBirthSect, _T("SERIA"), _T("І-НО") );
}
void CIniCache::SetBIRTH_Seria(LPCTSTR szSeria) {
  SetSVal(m_szBirthSect, _T("SERIA"), szSeria );
}
int CIniCache::GetBIRTH_NActPages() {
  int nPages = GetIVal(m_szBirthSect, _T("NActPages"), 2);
  if ( nPages < 1 || nPages > 2 )
    nPages = 2;
  return nPages;
}
void CIniCache::SetBIRTH_NActPages(int nPages) {
  SetIVal(m_szBirthSect, _T("NActPages"), nPages);
}

CString CIniCache::GetMARRIAGE_Seria() {
  return GetSVal(m_szMarriageSect, _T("SERIA"), _T("І-НО") );
}
void CIniCache::SetMARRIAGE_Seria(LPCTSTR szSeria) {
  SetSVal(m_szMarriageSect, _T("SERIA"), szSeria );
}
int CIniCache::GetMARRIAGE_NActPages() {
  int nPages = GetIVal(m_szMarriageSect, _T("NActPages"), 2);
  if ( nPages < 1 || nPages > 2 )
    nPages = 2;
  return nPages;
}
void CIniCache::SetMARRIAGE_NActPages(int nPages) {
  SetIVal(m_szMarriageSect, _T("NActPages"), nPages);
}

CString CIniCache::GetDIVORCE_Seria() {
  return GetSVal(m_szDivorceSect, _T("SERIA"), _T("І-НО") );
}
void CIniCache::SetDIVORCE_Seria(LPCTSTR szSeria) {
  SetSVal(m_szDivorceSect, _T("SERIA"), szSeria );
}
int CIniCache::GetDIVORCE_NActPages() {
  int nPages = GetIVal(m_szDivorceSect, _T("NActPages"), 2);
  if ( nPages < 1 || nPages > 2 )
    nPages = 2;
  return nPages;
}
void CIniCache::SetDIVORCE_NActPages(int nPages) {
  SetIVal(m_szDivorceSect, _T("NActPages"), nPages);
}

CString CIniCache::GetCHANGE_Seria() {
  return GetSVal(m_szChangeSect, _T("SERIA"), _T("І-НО") );
}
void CIniCache::SetCHANGE_Seria(LPCTSTR szSeria) {
  SetSVal(m_szChangeSect, _T("SERIA"), szSeria );
}
int CIniCache::GetCHANGE_NActPages() {
  int nPages = GetIVal(m_szChangeSect, _T("NActPages"), 2);
  if ( nPages < 1 || nPages > 2 )
    nPages = 2;
  return nPages;
}
void CIniCache::SetCHANGE_NActPages(int nPages) {
  SetIVal(m_szChangeSect, _T("NActPages"), nPages);
}

CString CIniCache::GetDEATH_Seria() {
  return GetSVal(m_szDeathSect, _T("SERIA"), _T("І-НО") );
}
void CIniCache::SetDEATH_Seria(LPCTSTR szSeria) {
  SetSVal(m_szDeathSect, _T("SERIA"), szSeria );
}
int CIniCache::GetDEATH_NActPages() {
  int nPages = GetIVal(m_szDeathSect, _T("NActPages"), 2);
  if ( nPages < 1 || nPages > 2 )
    nPages = 2;
  return nPages;
}
void CIniCache::SetDEATH_NActPages(int nPages) {
  SetIVal(m_szDeathSect, _T("NActPages"), nPages);
}

CString CIniCache::GetBIRTH_CNum() {
  return GetSVal(m_szBirthSect, _T("CNUM"), g_szCNume );
}
CString CIniCache::GetMARRIAGE_CNum() {
  return GetSVal(m_szMarriageSect, _T("CNUM"), g_szCNume );
}
CString CIniCache::GetDIVORCE_CNum() {
  return GetSVal(m_szDivorceSect, _T("CNUM"), g_szCNume );
}
CString CIniCache::GetCHANGE_CNum() {
  return GetSVal(m_szChangeSect, _T("CNUM"), g_szCNume );
}
CString CIniCache::GetDEATH_CNum() {
  return GetSVal(m_szDeathSect, _T("CNUM"), g_szCNume );
}

CString CIniCache::GetRenew() {
  return GetSVal(m_szCommonSect, _T("Renew"), _T("Запис поновлено") );
}

CString CIniCache::GetDIVORCE_NoChildren() {
  return GetSVal(m_szDivorceSect, _T("NOCHILDREN"), _T("Дітей немає.") );
}
void CIniCache::SetDIVORCE_NoChildren(LPCTSTR szNoChildren) {
  SetSVal(m_szDivorceSect, _T("NOCHILDREN"), szNoChildren );
}

CString CIniCache::GetDIVORCE_SingleChild() {
  return GetSVal(m_szDivorceSect, _T("SINGLECHILD"), _T("Одна дитина."));
}
void CIniCache::SetDIVORCE_SingleChild(LPCTSTR szSingleChild) {
  SetSVal(m_szDivorceSect, _T("SINGLECHILD"), szSingleChild);
}

/************************************** : by VK at 22.07.2005 21:04:02 **\
void CIniCache::FillChildList(CListBox& lb) {
  const int KEYBUF_SIZE = 0x4000;
  TCHAR* pKBuffer = new TCHAR[KEYBUF_SIZE];
  LPCTSTR szSection = _T("Childs");

  ::GetPrivateProfileSection(szSection, pKBuffer, KEYBUF_SIZE, m_sIniFile);
  char* pKey = pKBuffer;
  DWORD dwIndex(0);
  while( *pKey ) {
    CString sValue;
    CString sKey = GetSectionKey(pKey);
    ::GetPrivateProfileString(szSection, sKey, _T(""), sValue.GetBuffer(256), 256, m_sIniFile);
    sValue.ReleaseBuffer();
    sValue = Trim(sValue);
    if ( lb.FindString(-1, sValue)==LB_ERR ) {
      int nIndex = lb.AddString(sValue);
      lb.SetItemData(nIndex, dwIndex);
    }
    pKey += strlen(pKey)+1;
    dwIndex++;
  }

  delete pKBuffer;
}
\************************************** : by VK at 22.07.2005 21:04:08 **/

CString CIniCache::GetRPChild(long ID, LPCTSTR szSect) {
  CString sKey, s;
  sKey.Format(_T("RP%06d"), ID );
  s = GetSVal(szSect, sKey, _T(""));
  return FindAndReplace(s, _T("\\n"), _T("\r\n"), true);
}

void CIniCache::SetRPChild(long ID, LPCTSTR szSection, LPCTSTR szRP) {
  CString sKey;
  sKey.Format(_T("RP%06d"), ID);
  CString sValue = szRP;
  sValue = FindAndReplace(sValue, _T("\r\n"), _T("\\n"), true);
  SetSVal(szSection, sKey, sValue);
}

CString CIniCache::GetOverByDistrict(LPCTSTR szDistr) {
  return GetSVal(_T("ForList"), szDistr, _T("") );
}

bool CIniCache::FillForLists(CComboBox& cb) {
  bool bFilled = false;
/************************************** : by VK at 24.07.2005 7:28:33 **\
  const int KEYBUF_SIZE = 0x4000;
  TCHAR* pKBuffer = new TCHAR[KEYBUF_SIZE];
  LPCTSTR szSection = _T("Childs");

  ::GetPrivateProfileSection(_T("ForLists"), pKBuffer, KEYBUF_SIZE, m_sIniFile);
  char* pKey = pKBuffer;
  DWORD dwIndex(0);
  while( *pKey ) {
    CString sValue;
    CString sKey = GetSectionKey(pKey);
    if ( cb.FindStringExact(-1, sKey)==LB_ERR ) {
      int nIndex = cb.AddString(sKey);
      cb.SetItemData(nIndex, dwIndex);
      bFilled = true;
    }
    pKey += strlen(pKey)+1;
    dwIndex++;
  }
  delete pKBuffer;
\************************************** : by VK at 24.07.2005 7:28:37 **/
  return bFilled;
}

CString CIniCache::GetOwner(LPCTSTR szSection) {
  CString s;
  s = GetSVal(szSection, _T("OWN"), _T(""));
  return FindAndReplace(s, _T("\\n"), _T("\r\n"), true);
}

void CIniCache::SetOwner(LPCTSTR szSection, LPCTSTR szOwner) {
  CString sValue = szOwner;
  sValue = FindAndReplace(sValue, _T("\r\n"), _T("\\n"), true);
  SetSVal(szSection, _T("OWN"), sValue);
}

void CIniCache::FillBanks() {
  theBanks.RemoveAll();
  for( int i(1); i < MAX_BANKS; i++ ) {
    CString sKey, sValue;
    sKey.Format(_T("%02d"), i);
    sValue = GetSVal(_T("Banks"), sKey, _T(""));
    if ( !sValue.IsEmpty() )
      theBanks.Add( sValue );
  }
  theBanks.Sort(TRUE);
}

void CIniCache::SetNextCNum(LPCSTR szSect, CWnd* pWnd) {
  CString s;
  pWnd->GetWindowText(s);
  if ( !s.IsEmpty() ) {
    s.Format(_T("%06d"), atoi(s)+1 );
    SetSVal(szSect, _T("CNUM"), s);
  }
}
void CIniCache::SetBIRTH_CNum(CWnd* pWnd) {
  SetNextCNum(m_szBirthSect, pWnd);
}
void CIniCache::SetMARRIAGE_CNum(CWnd* pWnd) {
  SetNextCNum(m_szMarriageSect, pWnd);
}
void CIniCache::SetDIVORCE_CNum(CWnd* pWnd) {
  SetNextCNum(m_szDivorceSect, pWnd);
}
void CIniCache::SetCHANGE_CNum(CWnd* pWnd) {
  SetNextCNum(m_szChangeSect, pWnd);
}
void CIniCache::SetDEATH_CNum(CWnd* pWnd) {
  SetNextCNum(m_szDeathSect, pWnd);
}

CString CIniCache::GetNextNum(LPCSTR szSection, int num) {
  CString sNum;
  sNum.Format(_T("%02dNUM"), num);
  return GetNumFromStr(GetSVal(szSection, sNum, _T("0") ), NULL, true);
}

void CIniCache::SetNum(LPCSTR szSection, int num, LPCSTR szValue) {
  CString sNum;
  sNum.Format(_T("%02dNUM"), num);
  SetSVal(szSection, sNum, szValue);
}

CString CIniCache::GetNext41Num() {
  return GetNextNum(m_szBirthSect, 41);
}
void CIniCache::Set41Num(LPCTSTR szNum) {
  SetNum(m_szBirthSect, 41, szNum);
}

CString CIniCache::GetNext42Num() {
  return GetNextNum(m_szBirthSect, 42);
}
void CIniCache::Set42Num(LPCTSTR szNum) {
  SetNum(m_szBirthSect, 42, szNum);
}

CString CIniCache::GetNext43Num() {
  return GetNextNum( m_szDeathSect, 43 );
}

void CIniCache::Set43Num(LPCTSTR szNum) {
  SetNum(m_szDeathSect, 43, szNum);
}

UINT CIniCache::GetRagsID() {
  return GetIVal(m_szCommonSect, _T("RID"), -1);
}
void CIniCache::SetRagsID(UINT id) {
  SetIVal(m_szCommonSect, _T("RID"), id);
}
CString CIniCache::GetLKey() {
  CString szComputerName, s;
  BOOL fRet;
  DWORD dwName = 30;
  fRet = GetComputerName(szComputerName.GetBuffer(MAX_COMPUTERNAME_LENGTH + 1), &dwName);
  szComputerName.ReleaseBuffer();
  if ( FALSE==fRet )
    szComputerName = _T("PC");
  s.Format(_T("L%s"), szComputerName);
  if ( s.GetLength() > 32 )
    s = s.Left(32);
  return GetSVal(_T("LK"), s, _T(""));
}
void CIniCache::SetLKey(const CString& szLKey) {
  CString szComputerName, s;
  BOOL fRet;
  DWORD dwName = 30;
  fRet = GetComputerName(szComputerName.GetBuffer(MAX_COMPUTERNAME_LENGTH + 1), &dwName);
  szComputerName.ReleaseBuffer();
  if ( FALSE==fRet )
    szComputerName = _T("PC");
  s.Format(_T("L%s"), szComputerName);
  if ( s.GetLength() > 32 )
    s = s.Left(32);
  SetSVal(_T("LK"), s, szLKey);
}
BOOL CIniCache::IsValidLKey(LIC_KEY* pLC/*=NULL*/, CString* pszLKey/*=NULL*/) {
  CString szLKey = GetLKey();
  if ( szLKey.GetLength() != sizeof(LIC_KEY)*2 )
    return FALSE;

  for( int i(-1); i < 2; i++ ) {
    LIC_KEY lc;
    HexToMyBin((LPTSTR)&lc, szLKey, sizeof(lc)-sizeof(lc.rcSum), GetXorValue(i));

    CCyrString sRegion( GetREGION() ),
               sDistrict( GetDISTRICT() ),
               sCity( MakeKeysForRagsName(GetCITY_()) ),
               sRags( MakeKeysForRagsName(GetRAGS()) );

    CString sRegKey  = sRegion.GetKeyLetters().Left(4),
            sDistKey = sDistrict.GetKeyLetters().Left(4),
            sCityKey = sCity.GetKeyLetters().Left(4),
            sRagsKey = sRags.GetKeyLetters().Left(4);


    if ( sRegKey  == CString((LPCTSTR)lc.RegionKey,4)   && 
         sDistKey == CString((LPCTSTR)lc.DistrictKey,4) &&
         sCityKey == CString((LPCTSTR)lc.CityKey,4)     &&
         sRagsKey == CString((LPCTSTR)lc.RagsKey,4) ) {
      if ( pLC )
        memcpy(pLC, &lc, sizeof(LIC_KEY));
      if ( pszLKey )
        *pszLKey = szLKey;
      return true;
    }
  }
  return false;
}
CString CIniCache::GetDateCountStr() {
  CString s  = GetSVal(_T("DATES"), _T("DC"), _T(""));
  if ( s.IsEmpty() ) {
    s = CString('0', 16);
  }
  SecurityData* pSecData = ReadSecurityFromReg();
  if ( NULL==pSecData ) {
    BuildSecurityStruct(&m_Security);
  }
  else {
    memcpy(&m_Security, pSecData, sizeof(m_Security));
    delete pSecData;
  }
  BOOL fWriteSecurity  = FALSE;
  BOOL fWriteDateCount = FALSE;
  for( int i(0); i < 8; i++ ) {
    BYTE nDates = 0;
    CString sDate = s.Mid(i*2, 2);
    sscanf(sDate, "%02X", &nDates);
    if ( nDates > m_Security.nDates[i] ) {
      m_Security.nDates[i] = nDates;
      fWriteSecurity = TRUE;
    }
    else if ( nDates < m_Security.nDates[i] ) {
      sDate.Format(_T("%02X"), m_Security.nDates[i]);
      fWriteDateCount = TRUE;
      s.SetAt(i*2  , sDate[0]);
      s.SetAt(i*2+1, sDate[1]);
    }
  }
  if ( fWriteSecurity ) {
    SetSecurityCheckSum(&m_Security);
    WriteSecurityToReg(&m_Security);
  }
  if ( fWriteDateCount ) {
    SetSVal(_T("DATES"), _T("DC"), s);
  }
  return s;
}
void CIniCache::SetDateCount(const COleDateTime& odt) {
  CString s = GetDateCountStr();
  if ( odt.GetStatus()==COleDateTime::valid) {
    int nDates = 0;
    int dow = odt.GetDayOfWeek() - 1;
    CString sDate = s.Mid(dow*2, 2);
    sscanf(sDate, "%02X", &nDates);
    nDates++;
    CString sNewDate;
    sNewDate.Format(_T("%02X"), nDates);
    s.SetAt(dow*2  , sNewDate.GetAt(0));
    s.SetAt(dow*2+1, sNewDate.GetAt(1));
    SetSVal(_T("DATES"), _T("DC"), s);
  }
}
int CIniCache::CalcDates() {
  int nCount = 0;
  CString s = GetDateCountStr();
  for( int i(0); i < 7; i++ ) {
    int nDates = 0;
    CString sDate = s.Mid(i*2, 2);
    sscanf(sDate, "%02X", &nDates);
    nCount += nDates;
  }
  return nCount;
}

UINT CIniCache::GetPrintCitizen(LPCSTR szSection) {
  return GetIVal(szSection, _T("PRINTCITIZEN"), PRINT_CITIZENSHIP_ALL);
}
UINT CIniCache::GetPrintCitizenBIRTH() {
  return GetPrintCitizen(m_szBirthSect);
}
UINT CIniCache::GetPrintCitizenMARRIAGE() {
  return GetPrintCitizen(m_szMarriageSect);
}
UINT CIniCache::GetPrintCitizenDIVORCE() {
  return GetPrintCitizen(m_szDivorceSect);
}
UINT CIniCache::GetPrintCitizenCHANGE() {
  return GetPrintCitizen(m_szChangeSect);
}
UINT CIniCache::GetPrintCitizenDEATH() {
  return GetPrintCitizen(m_szDeathSect);
}
void CIniCache::SetPrintCitizen(LPCSTR szSection, UINT nValue) {
  SetIVal(szSection, _T("PRINTCITIZEN"), nValue);
}
void CIniCache::SetPrintCitizenBIRTH(UINT nValue) {
  SetPrintCitizen(m_szBirthSect, nValue);
}
void CIniCache::SetPrintCitizenMARRIAGE(UINT nValue) {
  SetPrintCitizen(m_szMarriageSect, nValue);
}
void CIniCache::SetPrintCitizenDIVORCE(UINT nValue) {
  SetPrintCitizen(m_szDivorceSect, nValue);
}
void CIniCache::SetPrintCitizenCHANGE(UINT nValue) {
  SetPrintCitizen(m_szChangeSect, nValue);
}
void CIniCache::SetPrintCitizenDEATH(UINT nValue) {
  SetPrintCitizen(m_szDeathSect, nValue);
}
