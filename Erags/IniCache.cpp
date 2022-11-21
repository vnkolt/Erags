//
// IniCache.cpp
//
#include "stdafx.h"
#include "Erags.h"

#include "Caches.h"
#include "IniCache.h"
#include "RNames.h"

#include "..\Common\CyrString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_BANKS 20

CString GetSectionKey(const char* pKey);

LPCTSTR g_szSvNeVidano = _T("Свідоцтво не ");
LPCTSTR g_szCNume = _T("000001");
CAbbrCache  theAbbrCache;
CFormsCache theIniCache;

///////////////////////////////////////////
// CAbbrCache
CAbbrCache::CAbbrCache() {
}
CAbbrCache::~CAbbrCache() {
  m_map.RemoveAll();
}
void CAbbrCache::Load(LPCTSTR szFileName) {
  const int KEYBUF_SIZE = 0x4000;
  LPCTSTR szSection = _T("Abbreviations");
  TCHAR* pKBuffer = new TCHAR[KEYBUF_SIZE];
  ::GetPrivateProfileSection(szSection, pKBuffer, KEYBUF_SIZE, szFileName);
  char* pKey = pKBuffer;
  while( *pKey ) {
    CString sValue;
    CString sKey = GetSectionKey(pKey);
    ::GetPrivateProfileString(szSection, sKey, _T(""), sValue.GetBuffer(128), 128, szFileName);
    sValue.ReleaseBuffer();
    sValue = Trim(sValue);
    m_map.SetAt(sKey, sValue);
    pKey += strlen(pKey)+1;
  }

  delete pKBuffer;
}

BOOL CAbbrCache::Lookup(LPCTSTR key, CString& rValue) {
  return m_map.Lookup(key, rValue);
}

///////////////////////////////////////////
// CFormsCache
CFormsCache::CFormsCache() {
  m_sCommonSect   = _T("COMMON");
  m_sBirthSect    = _T("BIRTH_FORM");
  m_sMarriageSect = _T("MARRIAGE_FORM");
  m_sDivorceSect  = _T("DIVORCE_FORM");
  m_sChangeSect   = _T("CHANGE_FORM");
  m_sDeathSect    = _T("DEATH_FORM");
}
CFormsCache::~CFormsCache() {
}
void CFormsCache::Load(LPCTSTR szFileName) {
  m_sIniFile = szFileName;
}
CString CFormsCache::GetSVal(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal) {
  CString s;
  ::GetPrivateProfileString(szSect, szKey, szDefVal, s.GetBuffer(512), 512, m_sIniFile);
  s.ReleaseBuffer();
  return s; 
}
void CFormsCache::SetSVal(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szValue) {
  ::WritePrivateProfileString(szSect, szKey, szValue, m_sIniFile);
}
UINT CFormsCache::GetIVal(LPCTSTR szSect, LPCTSTR szKey, UINT iDefVal) {
  return ::GetPrivateProfileInt(szSect, szKey, iDefVal, m_sIniFile);
}
void CFormsCache::SetIVal(LPCTSTR szSect, LPCTSTR szKey, UINT uValue) {
  CString sValue;
  sValue.Format(_T("%u"), uValue);
  ::WritePrivateProfileString(szSect, szKey, sValue, m_sIniFile);
}

CString CFormsCache::GetCOUNTRY() {  
  return GetSVal(m_sCommonSect, _T("COUNTRY"), _T("Україна") );
}
void CFormsCache::SetCOUNTRY(LPCTSTR szCountry) {
  SetSVal(m_sCommonSect, _T("COUNTRY"), szCountry );
}
CString CFormsCache::GetREGION() {
  return GetSVal(m_sCommonSect, _T("REGION"), _T("") );
}
void CFormsCache::SetREGION(LPCTSTR szRegion) {
  SetSVal(m_sCommonSect, _T("REGION"), szRegion );
}
CString CFormsCache::GetCITY() {
  return GetSVal(m_sCommonSect, _T("CITY"), _T("") );
}
void CFormsCache::SetCITY(LPCTSTR szCity) {
  SetSVal(m_sCommonSect, _T("CITY"), szCity);
}
CString CFormsCache::GetDISTRICT() {
  return GetSVal(m_sCommonSect, _T("DISTRICT"), _T("") );
}
void CFormsCache::SetDISTRICT(LPCTSTR szDistrict) {
  SetSVal(m_sCommonSect, _T("DISTRICT"), szDistrict);
}
CString CFormsCache::GetRAGS() {
  return GetSVal(m_sCommonSect, _T("RAGS"), _T("") );
}
void CFormsCache::SetRAGS(LPCTSTR szRags) {
  SetSVal(m_sCommonSect, _T("RAGS"), szRags);
}
CString CFormsCache::GetBoss() {
  return GetSVal(m_sCommonSect, _T("BOSS"), _T("") );
}
void CFormsCache::SetBoss(LPCTSTR szBoss) {
  SetSVal(m_sCommonSect, _T("BOSS"), szBoss);
}
CString CFormsCache::GetParent() {
  return GetSVal(m_sCommonSect, _T("PARENT"), _T("") );
}
void CFormsCache::SetParent(LPCTSTR szParent) {
  SetSVal(m_sCommonSect, _T("PARENT"), szParent);
}

BOOL CFormsCache::IsChildRags(const CString& szRags) {
  BOOL bRet(FALSE);
  CString sRags = DecodeRagsName(szRags);

  const int KEYBUF_SIZE = 0x4000;
  TCHAR* pKBuffer = new TCHAR[KEYBUF_SIZE];
  ::GetPrivateProfileSection(_T("Keys"), pKBuffer, KEYBUF_SIZE, m_sIniFile);

  char* pKey = pKBuffer;
  while( *pKey ) {
    CString sKey = GetSectionKey(pKey),
            sKeys, sTok;
    ::GetPrivateProfileString(_T("Keys"), sKey, _T(""), sKeys.GetBuffer(128), 128, m_sIniFile);
    sKeys.ReleaseBuffer();
    sKeys = Trim(sKeys);
    sTok = GetTokSpace(sKeys, 0);
    if ( sTok.IsEmpty() )
      continue;
    if ( sRags.Find(sTok) >=0 ) {
      sTok = GetTokSpace(sKeys, 1);
      if ( sTok.IsEmpty() ) {
        bRet = TRUE;
        break;
      }
      sTok = GetTokSpace(sKeys, 2);
      if ( sTok.IsEmpty() || sRags.Find(sTok) >=0 ) {
        bRet = TRUE;
        break;
      }
    }
    pKey += strlen(pKey)+1;
  }
  delete pKBuffer;
  return bRet;
}

CString CFormsCache::GetByROVD() {
  return GetSVal(m_sCommonSect, _T("BYUMVS"), _T("") );
}
void CFormsCache::SetByROVD(LPCTSTR szBy) {
  SetSVal(m_sCommonSect, _T("BYUMVS"), szBy );
}
CString CFormsCache::GetToROVD() {
  return GetSVal(m_sCommonSect, _T("TOUMVS"), _T("") );
}
void CFormsCache::SetToROVD(LPCTSTR szTo) {
  SetSVal(m_sCommonSect, _T("TOUMVS"), szTo );
}

CString CFormsCache::GetByMil() {
  return GetSVal(m_sCommonSect, _T("BYMIL"), _T("") );
}
void CFormsCache::SetByMil(LPCTSTR szBy) {
  SetSVal(m_sCommonSect, _T("BYMIL"), szBy );
}
CString CFormsCache::GetToMil() {
  return GetSVal(m_sCommonSect, _T("TOMIL"), _T("") );
}
void CFormsCache::SetToMil(LPCTSTR szTo) {
  SetSVal(m_sCommonSect, _T("TOMIL"), szTo );
}
CString CFormsCache::GetByCourt() {
  return GetSVal(m_sCommonSect, _T("BYCOURT"), _T("") );
}
void CFormsCache::SetByCourt(LPCTSTR szBy) {
  SetSVal(m_sCommonSect, _T("BYCOURT"), szBy );
}
CString CFormsCache::GetToTax() {
  return GetSVal(m_sCommonSect, _T("TOTAX"), _T("") );
}
void CFormsCache::SetToTax(LPCTSTR szTo) {
  SetSVal(m_sCommonSect, _T("TOTAX"), szTo );
}

CString CFormsCache::GetNoCert() {
  return GetSVal(m_sCommonSect, _T("NOCERT"), _T("Свідоцтво не видано.") );
}
CString CFormsCache::GetBIRTH_BP_COUNTRY() {
  return GetSVal(m_sBirthSect, _T("CHILD_BP_COUNTRY"), _T("Україна") );
}
void CFormsCache::SetBIRTH_BP_COUNTRY(LPCTSTR szCountry) {
  SetSVal(m_sBirthSect, _T("CHILD_BP_COUNTRY"), szCountry );
}
UINT    CFormsCache::GetBIRTH_BP_COUNTRY_CHECK() {
  return GetIVal(m_sBirthSect, _T("CHILD_BP_COUNTRY_CHECK"), 1);
}
void CFormsCache::SetBIRTH_BP_COUNTRY_CHECK(UINT uCheck) {
  SetIVal(m_sBirthSect, _T("CHILD_BP_COUNTRY_CHECK"), uCheck);
}
CString CFormsCache::GetBIRTH_BP_REGION() {
  return GetSVal(m_sBirthSect, _T("CHILD_BP_REGION"), _T("") );
}
void CFormsCache::SetBIRTH_BP_REGION(LPCTSTR szRegion) {
  SetSVal(m_sBirthSect, _T("CHILD_BP_REGION"), szRegion );
}
UINT    CFormsCache::GetBIRTH_BP_REGION_CHECK() {
  return GetIVal(m_sBirthSect, _T("CHILD_BP_REGION_CHECK"), 1);
}
void CFormsCache::SetBIRTH_BP_REGION_CHECK(UINT uCheck) {
  SetIVal(m_sBirthSect, _T("CHILD_BP_REGION_CHECK"), uCheck);
}
CString CFormsCache::GetBIRTH_BP_DISTRICT() {
  return GetSVal(m_sBirthSect, _T("CHILD_BP_DISTRICT"), _T("") );
}
void CFormsCache::SetBIRTH_BP_DISTRICT(LPCTSTR szDistrict) {
  SetSVal(m_sBirthSect, _T("CHILD_BP_DISTRICT"), szDistrict );
}
UINT    CFormsCache::GetBIRTH_BP_DISTRICT_CHECK() {
  return GetIVal(m_sBirthSect, _T("CHILD_BP_DISTRICT_CHECK"), 1);
}
void CFormsCache::SetBIRTH_BP_DISTRICT_CHECK(UINT uCheck) {
  SetIVal(m_sBirthSect, _T("CHILD_BP_DISTRICT_CHECK"), uCheck);
}
CString CFormsCache::GetBIRTH_BP_CITY() {
  return GetSVal(m_sBirthSect, _T("CHILD_BP_CITY"), _T("") );
}
void CFormsCache::SetBIRTH_BP_CITY(LPCTSTR szCity) {
  SetSVal(m_sBirthSect, _T("CHILD_BP_CITY"), szCity );
}
UINT CFormsCache::GetBIRTH_BP_CITY_CHECK() {
  return GetIVal(m_sBirthSect, _T("CHILD_BP_CITY_CHECK"), 1);
}
void CFormsCache::SetBIRTH_BP_CITY_CHECK(UINT uCheck) {
  SetIVal(m_sBirthSect, _T("CHILD_BP_CITY_CHECK"), uCheck);
}

CString CFormsCache::GetMDN() {
  return GetSVal(m_sBirthSect, _T("МДН"), _T("Медичне свідоцтво про народження") );
}

CString CFormsCache::GetBIRTH_Seria() {
  return GetSVal(m_sBirthSect, _T("SERIA"), _T("І-НО") );
}
void CFormsCache::SetBIRTH_Seria(LPCTSTR szSeria) {
  SetSVal(m_sBirthSect, _T("SERIA"), szSeria );
}
CString CFormsCache::GetMARRIAGE_Seria() {
  return GetSVal(m_sMarriageSect, _T("SERIA"), _T("І-НО") );
}
void CFormsCache::SetMARRIAGE_Seria(LPCTSTR szSeria) {
  SetSVal(m_sMarriageSect, _T("SERIA"), szSeria );
}
CString CFormsCache::GetDIVORCE_Seria() {
  return GetSVal(m_sDivorceSect, _T("SERIA"), _T("І-НО") );
}
void CFormsCache::SetDIVORCE_Seria(LPCTSTR szSeria) {
  SetSVal(m_sDivorceSect, _T("SERIA"), szSeria );
}
CString CFormsCache::GetCHANGE_Seria() {
  return GetSVal(m_sChangeSect, _T("SERIA"), _T("І-НО") );
}
void CFormsCache::SetCHANGE_Seria(LPCTSTR szSeria) {
  SetSVal(m_sChangeSect, _T("SERIA"), szSeria );
}
CString CFormsCache::GetDEATH_Seria() {
  return GetSVal(m_sDeathSect, _T("SERIA"), _T("І-НО") );
}
void CFormsCache::SetDEATH_Seria(LPCTSTR szSeria) {
  SetSVal(m_sDeathSect, _T("SERIA"), szSeria );
}

CString CFormsCache::GetBIRTH_CNum() {
  return GetSVal(m_sBirthSect, _T("CNUM"), g_szCNume );
}
CString CFormsCache::GetMARRIAGE_CNum() {
  return GetSVal(m_sMarriageSect, _T("CNUM"), g_szCNume );
}
CString CFormsCache::GetDIVORCE_CNum() {
  return GetSVal(m_sDivorceSect, _T("CNUM"), g_szCNume );
}
CString CFormsCache::GetCHANGE_CNum() {
  return GetSVal(m_sChangeSect, _T("CNUM"), g_szCNume );
}
CString CFormsCache::GetDEATH_CNum() {
  return GetSVal(m_sDeathSect, _T("CNUM"), g_szCNume );
}

CString CFormsCache::GetRenew() {
  return GetSVal(m_sCommonSect, _T("Renew"), _T("Запис поновлено") );
}

CString CFormsCache::GetDIVORCE_NoChildren() {
  return GetSVal(m_sDivorceSect, _T("NOCHILDREN"), _T("Дітей немає.") );
}
void CFormsCache::SetDIVORCE_NoChildren(LPCTSTR szNoChildren) {
  SetSVal(m_sDivorceSect, _T("NOCHILDREN"), szNoChildren );
}

CString CFormsCache::GetDIVORCE_SingleChild() {
  return GetSVal(m_sDivorceSect, _T("SINGLECHILD"), _T("Одна дитина."));
}
void CFormsCache::SetDIVORCE_SingleChild(LPCTSTR szSingleChild) {
  SetSVal(m_sDivorceSect, _T("SINGLECHILD"), szSingleChild);
}

/************************************** : by VK at 22.07.2005 21:04:02 **\
void CFormsCache::FillChildList(CListBox& lb) {
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
void CFormsCache::FillChildList(CStringArray& sa) {
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
    if ( !sValue.IsEmpty() ) {
      sa.Add( sValue );
    }
    pKey += strlen(pKey)+1;
    dwIndex++;
  }

  delete pKBuffer;
}


/************************************** : by VK at 22.07.2005 22:52:12 **\
CString CFormsCache::GetRPChild(CListBox& lb, LPCTSTR szSection) {
  CString s;
	int nIndex = lb.GetCurSel();
	if ( nIndex != LB_ERR ) {
    CString sKey;
    sKey.Format(_T("RP%02d"), lb.GetItemData(nIndex) );
    ::GetPrivateProfileString(szSection, sKey, _T(""), s.GetBuffer(256), 256, m_sIniFile);
    s.ReleaseBuffer();
    return FindAndReplace(s, _T("\\n"), _T("\r\n"), true);
  }
  return s;
}
CString CFormsCache::GetRPChild(long ID, LPCTSTR szSect) {
  CString sKey;
  sKey.Format(_T("RP%02d"), long ID );
  ::GetPrivateProfileString(szSection, sKey, _T(""), s.GetBuffer(256), 256, m_sIniFile);
  s.ReleaseBuffer();
  return FindAndReplace(s, _T("\\n"), _T("\r\n"), true);
}

void CFormsCache::SetRPChild(CListBox& lb, LPCTSTR szSection, LPCTSTR szRP) {
	int nIndex = lb.GetCurSel();
	if ( nIndex != LB_ERR ) {
    CString sKey;
    sKey.Format(_T("RP%02d"), lb.GetItemData(nIndex) );
    CString sValue = szRP;
    sValue = FindAndReplace(sValue, _T("\r\n"), _T("\\n"), true);
    ::WritePrivateProfileString(szSection, sKey, sValue, m_sIniFile);
  }
}
\************************************** : by VK at 22.07.2005 22:52:17 **/

CString CFormsCache::GetOverByDistrict(LPCTSTR szDistr) {
  CString sRet;
  ::GetPrivateProfileString(_T("ForList"), szDistr, _T(""), sRet.GetBuffer(256), 256, m_sIniFile);
  sRet.ReleaseBuffer();
  return sRet;
}

bool CFormsCache::FillForLists(CComboBox& cb) {
  bool bFilled = false;
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
  return bFilled;
}

CString CFormsCache::GetOwner(LPCTSTR szSection) {
  CString s;
  ::GetPrivateProfileString(szSection, _T("OWN"), _T(""), s.GetBuffer(256), 256, m_sIniFile);
  s.ReleaseBuffer();
  return FindAndReplace(s, _T("\\n"), _T("\r\n"), true);
}

void CFormsCache::SetOwner(LPCTSTR szSection, LPCTSTR szOwner) {
  CString sValue = szOwner;
  sValue = FindAndReplace(sValue, _T("\r\n"), _T("\\n"), true);
  ::WritePrivateProfileString(szSection, _T("OWN"), sValue, m_sIniFile);
}

void CFormsCache::FillBanks() {
  theBanks.RemoveAll();
  for( int i(1); i < MAX_BANKS; i++ ) {
    CString sKey, sValue;
    sKey.Format(_T("%02d"), i);
    ::GetPrivateProfileString(_T("Banks"), sKey, _T(""), sValue.GetBuffer(160), 160, theApp.GetDBIniFile());
    sValue.ReleaseBuffer();
    if ( !sValue.IsEmpty() )
      theBanks.Add( sValue );
  }
  theBanks.Sort(TRUE);
}

void CFormsCache::SetNextCNum(LPCSTR szSect, CWnd* pWnd) {
  CString s;
  pWnd->GetWindowText(s);
  if ( !s.IsEmpty() ) {
    s.Format(_T("%06d"), atoi(s)+1 );
    ::WritePrivateProfileString(szSect, _T("CNUM"), s, m_sIniFile);
  }
}
void CFormsCache::SetBIRTH_CNum(CWnd* pWnd) {
  SetNextCNum(m_sBirthSect, pWnd);
}
void CFormsCache::SetMARRIAGE_CNum(CWnd* pWnd) {
  SetNextCNum(m_sMarriageSect, pWnd);
}
void CFormsCache::SetDIVORCE_CNum(CWnd* pWnd) {
  SetNextCNum(m_sDivorceSect, pWnd);
}
void CFormsCache::SetCHANGE_CNum(CWnd* pWnd) {
  SetNextCNum(m_sChangeSect, pWnd);
}
void CFormsCache::SetDEATH_CNum(CWnd* pWnd) {
  SetNextCNum(m_sDeathSect, pWnd);
}

CString CFormsCache::GetNextNum(LPCSTR szSection, int num) {
  CString sNum;
  sNum.Format(_T("%02dNUM"), num);
  return GetNumFromStr(GetSVal(szSection, sNum, _T("0") ), NULL, true);
}

void CFormsCache::SetNum(LPCSTR szSection, int num, LPCSTR szValue) {
  CString sNum;
  sNum.Format(_T("%02dNUM"), num);
  SetSVal(szSection, sNum, szValue);
}

CString CFormsCache::GetNext41Num() {
  return GetNextNum(m_sBirthSect, 41);
}
void CFormsCache::Set41Num(LPCTSTR szNum) {
  SetNum(m_sBirthSect, 41, szNum);
}

CString CFormsCache::GetNext42Num() {
  return GetNextNum(m_sBirthSect, 42);
}
void CFormsCache::Set42Num(LPCTSTR szNum) {
  SetNum(m_sBirthSect, 42, szNum);
}

CString CFormsCache::GetNext43Num() {
  return GetNextNum( m_sDeathSect, 43 );
}

void CFormsCache::Set43Num(LPCTSTR szNum) {
  SetNum(m_sDeathSect, 43, szNum);
}

UINT CFormsCache::GetRagsID() {
  return GetIVal(m_sCommonSect, _T("RID"), -1);
}
void CFormsCache::SetRagsID(UINT id) {
  SetIVal(m_sCommonSect, _T("RID"), id);
}