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

#include "xMachine.h"
#include "YesNoDlg.h"

#include "..\Common\Crypto.h"
#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"
#include "..\Common\MDB.h"

#include "..\ZipArchive\ZLIB\zlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef FREE_LICENCE
CString        g_szLastLDate;
long           g_nDaysRemaining = 0;
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

#ifndef FREE_LICENCE
CRegTimer theRegTimer;
/////////////////////////////////////////////////////////////////////////////
// CRegTimer class members
CRegTimer::CRegTimer() {
}
CString CRegTimer::GetSubkey1() {
  CString s;
                          /* Software\Microsoft\Ole */
  static BYTE szKey[] = { BYTE('S'<<1), BYTE('o'<<1), BYTE('f'<<1), BYTE('t'<<1), BYTE('w'<<1), BYTE('a'<<1), BYTE('r'<<1), BYTE('e'<<1), BYTE('\\'<<1),
                          BYTE('M'<<1), BYTE('i'<<1), BYTE('c'<<1), BYTE('r'<<1), BYTE('o'<<1), BYTE('s'<<1), BYTE('o'<<1), BYTE('f'<<1), BYTE('t'<<1), BYTE('\\'<<1),
                          BYTE('O'<<1), BYTE('l'<<1), BYTE('e'<<1) };
  for( int i(0); i < sizeof(szKey); i++ )
    s += (TCHAR)(szKey[i]>>1);
  return s;
}

CString CRegTimer::GetValueName1() {
  CString s;              /* DefaultProperties */
  static BYTE szKey[] = { 'D'^0x08, 'e'^0x09, 'f'^0x0A, 'a'^0x0B, 'u'^0x0C, 'l'^0x0D, 't'^0x0E,
                          'P'^0x0F, 'r'^0x10, 'o'^0x11, 'p'^0x12, 'e'^0x13, 'r'^0x14, 't'^0x15, 'i'^0x16, 'e'^0x17, 's'^0x18 };
  BYTE xorByte = 0x08;
  for( int i(0); i < sizeof(szKey); i++ )
    s += (TCHAR)(szKey[i]^xorByte++);
  return s;
}

void CRegTimer::PrepareForWriting(RegTimerData& dest) {
  BYTE* p = (BYTE*)&m_rtd.cbShutdownCount;
  int n = sizeof(dest) - sizeof(dest.cbCheckSum) - sizeof(dest.cbSize);
  dest.cbSize = sizeof(dest);
  dest.cbCheckSum = 0;
  for( int i(0); i < n; i++ ) {
    dest.cbCheckSum += *p;
    p++;
  }
  EncryptData(dest);
}

void CRegTimer::EncryptData(RegTimerData& dest) {
  CCrypto crypt;    // vnk@ukr.net Vladimir.Koltsov@gmail.com
  crypt.SetCryptoKey("vnk@ukr.net", 10);
  crypt.Encrypt(&dest, sizeof(dest));
}

void CRegTimer::DecryptData(RegTimerData& dest) {
  CCrypto crypt;    // vnk@ukr.net Vladimir.Koltsov@gmail.com
  crypt.SetCryptoKey("vnk@ukr.net", 10);
  crypt.Decrypt(&dest, sizeof(dest));
}

uint32 CRegTimer::GetLastTime() {
  char s[32];
  SYSTEMTIME st;
  GetLocalTime(&st);
#ifdef _STRCPY_S
  sprintf_s(s, sizeof(s), "%02d%02d%02d%03d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#else
  sprintf(s, "%02d%02d%02d%03d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#endif
  return (uint32)atol(s);
}
uint32 CRegTimer::GetLastDate() {
  char s[32];
  SYSTEMTIME st;
  GetLocalTime(&st);
#ifdef _STRCPY_S
  sprintf_s(s, sizeof(s), "%04d%02d%02d", st.wYear, st.wMonth, st.wDay);
#else
  sprintf(s, "%04d%02d%02d", st.wYear, st.wMonth, st.wDay);
#endif
  return (uint32)atol(s);
}

COleDateTime CRegTimer::GetDate(uint32 u32) {
  CString s;
  s.Format(_T("%08d"), u32);
  COleDateTime odt;
  odt.SetDate( atoi(s.Mid(0, 4)), atoi(s.Mid(4,2)), atoi(s.Mid(6,2)));
  return odt;
}

BOOL CRegTimer::IsValid(const RegTimerData& rtd) {
  if ( rtd.cbSize != sizeof(rtd) ) {
    return false;
  }
  int n = sizeof(rtd) - sizeof(rtd.cbCheckSum) - sizeof(rtd.cbSize);
  BYTE* p = (BYTE*)&rtd.cbShutdownCount;
  uint16 cbCheckSum = 0;
  for( int i(0); i < n; i++ ) {
    cbCheckSum += *p;
    p++;
  }
  if ( cbCheckSum != rtd.cbCheckSum ) {
    return false;
  }

  COleDateTime odtFirst = GetDate(rtd.FirstWorkedDate);
  if ( odtFirst.GetStatus() != COleDateTime::valid ) {
    return false;
  }
  if ( odtFirst.GetYear() < 2010 ) {
    return false;
  }
  COleDateTime odtLast = GetDate(rtd.LastWorkedDate);
  if ( odtLast.GetStatus() != COleDateTime::valid ) {
    return false;
  }

  return true;
}

BOOL CRegTimer::ReadGobalData(RegTimerData& dest) {
  BOOL fRet = false;
  LONG lRes;
  HKEY hKey;

  lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, GetSubkey1(), 0L, KEY_ALL_ACCESS, &hKey);
  if ( ERROR_SUCCESS==lRes ) { 
    DWORD dwType = REG_BINARY;
    DWORD dwSize = sizeof(dest);
    lRes = ::RegQueryValueEx(hKey, GetValueName1(), NULL, &dwType, (BYTE*)&dest, &dwSize);
    ::RegCloseKey(hKey);
    if ( ERROR_SUCCESS==lRes ) { 
      DecryptData(dest);
      fRet = true;
    }
  }
  
  return fRet;
}

void CRegTimer::WriteGlobalData() {
  RegTimerData rtd;
  memcpy(&rtd, &m_rtd, sizeof(rtd));
  PrepareForWriting(rtd);

  LONG lRes;
  HKEY hKey;

  lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, GetSubkey1(), 0L, KEY_ALL_ACCESS, &hKey);
  if ( ERROR_SUCCESS!=lRes ) {  // A key does not exist. We should create the key.
    lRes = ::RegCreateKey(HKEY_LOCAL_MACHINE, GetSubkey1(), &hKey); 
  }
  if ( lRes==ERROR_SUCCESS ) {
    ::RegSetValueEx(hKey, GetValueName1(), NULL, REG_BINARY, (BYTE*)&rtd, sizeof(rtd));
    ::RegCloseKey(hKey);
  }
}


BOOL CRegTimer::ReadLocalData(RegTimerData& dest) {
  BOOL fRet = false;
  RegTimerData* pRTData = NULL;
  UINT nl;
  if ( theApp.GetProfileBinary(_T("Settings"), _T("RTInfo"), (LPBYTE*)&pRTData, &nl)) {
    if ( sizeof(dest)==nl ) {
      memcpy(&dest, pRTData, sizeof(dest));
      DecryptData(dest);
      fRet = true;
    }
    delete pRTData;
  }
  return fRet;
}

void CRegTimer::WriteLocalData() {
  RegTimerData rtd;
  memcpy(&rtd, &m_rtd, sizeof(rtd));
  PrepareForWriting(rtd);

  theApp.WriteProfileBinary(_T("Settings"), _T("RTInfo"), (LPBYTE)&rtd, sizeof(rtd));
}

void CRegTimer::Initialize() {
  m_rtd.FirstWorkedDate = m_rtd.LastWorkedDate = GetLastDate();
  m_rtd.LastWorkedTime = GetLastTime();
}

void CRegTimer::Normalize(RegTimerData& rtd) {
  if ( rtd.cbShutdownCount > m_rtd.cbShutdownCount ) {
    m_rtd.cbShutdownCount = rtd.cbShutdownCount;
  }
  if ( rtd.cbWorkedDays > m_rtd.cbWorkedDays ) {
    m_rtd.cbWorkedDays = rtd.cbWorkedDays;
  }
  if ( rtd.FirstWorkedDate > m_rtd.FirstWorkedDate ) {
    m_rtd.FirstWorkedDate = rtd.FirstWorkedDate;
  }
  if ( rtd.LastWorkedDate < m_rtd.LastWorkedDate ) {
    m_rtd.LastWorkedDate = rtd.LastWorkedDate;
  }
  if ( rtd.OverSysDates > m_rtd.OverSysDates ) {
    m_rtd.OverSysDates = rtd.OverSysDates;
  }
/*
  if ( rtd.FutureDates > m_rtd.FutureDates ) {
    m_rtd.FutureDates = rtd.FutureDates;
  }
*/
  /*
  if ( rtd.LastWorkedTime > m_rtd.LastWorkedTime ) {
    m_rtd.LastWorkedTime = rtd.LastWorkedTime;
  }
  */
}

BOOL CRegTimer::ReadMax() {
  RegTimerData rtdGlobal;
  RegTimerData rtdLocal;

  Initialize();

  if ( ReadGobalData(rtdGlobal) ) {
    Normalize(rtdGlobal);
  }

  if ( ReadLocalData(rtdLocal) ) {
    Normalize(rtdGlobal);
  }
  return true;
}

void CRegTimer::Write() {
  WriteGlobalData();
  WriteLocalData();
}

void CRegTimer::Next() {
  uint32 LastWorkedTime = GetLastTime();
  if ( LastWorkedTime > m_rtd.LastWorkedTime ) {
    m_rtd.LastWorkedTime = LastWorkedTime;
    Write();
  }
}
void CRegTimer::Startup() {
  uint32 t = GetLastTime();
  ReadMax();
  if ( t < m_rtd.LastWorkedTime ) {
    m_rtd.cbWorkedDays++;
    Write();
  }
}

void CRegTimer::Shutdown() {
  uint32 d = GetLastDate();
  if ( d > m_rtd.LastWorkedDate ) {
    m_rtd.LastWorkedDate = d;
  }
  uint32 t = GetLastTime();
  if ( t > m_rtd.LastWorkedTime ) {
    m_rtd.LastWorkedTime = t;
  }
  m_rtd.cbShutdownCount++;
  Write();
}

void CRegTimer::Reinit(COleDateTime* pStartDate) {
  Initialize();
  if ( pStartDate ) {
    CString s;
    s.Format(_T("%04d%02d%02d"), pStartDate->GetYear(), pStartDate->GetMonth(), pStartDate->GetDay());
    m_rtd.FirstWorkedDate = m_rtd.LastWorkedDate = atol(s);
  }
  Write();
}

CString CRegTimer::GetMaxDate() {
  long lWorkedDays = m_rtd.cbWorkedDays;
  long lWeeks      = lWorkedDays / 5;
  long lTotalDays  = lWorkedDays + lWeeks*2;

  CString s;
  COleDateTime LastWD1 = GetDate(m_rtd.FirstWorkedDate);
  COleDateTime LastWD2 = GetDate(m_rtd.LastWorkedDate);
  LastWD1 += COleDateTimeSpan(lTotalDays, 0, 0, 0);
  COleDateTime* odt = ( LastWD1 > LastWD2 ) ? &LastWD1 : &LastWD2;
  s.Format(_T("%04d%02d%02d"), odt->GetYear(), odt->GetMonth(), odt->GetDay());
  return s;
}

//BOOL Expired(COleDateTi

#endif // FREE_LICENCE

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

#ifndef FREE_LICENCE
  m_fLimitedLicence = false;
#endif

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

// commented at 2008.01.19

#ifndef FREE_LICENCE
  g_LKeyResult = IsValidLKey();
#endif // FREE_LICENCE
/*
  if ( FALSE==g_fValidLKey ) {
    int nDates = CalcDates();
    if ( nDates > 100 ) {
    }
  }
*/
   
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
  m_AbbrMap.SetAt(_T("ВО"), _T("виконавчий орган"));
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

BOOL CIniCache::GetCityUnderline() {
  return GetIVal(m_szCommonSect, _T("UnderlineCity"), true);
}
void CIniCache::SetCityUnderline(BOOL fUnderline) {
  SetIVal(m_szCommonSect, _T("UnderlineCity"), fUnderline);
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
  return Trim(GetCity(GetCITY()));
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
CString CIniCache::GetOKPO() {
  return GetSVal(m_szCommonSect, _T("OKPO"), _T("00000000") );
}
void CIniCache::SetOKPO(LPCTSTR szOKPO) {
  SetSVal(m_szCommonSect, _T("OKPO"), szOKPO);
}
CString CIniCache::GetBoss() {
  return GetSVal(m_szCommonSect, _T("BOSS"), _T("") );
}
void CIniCache::SetBoss(LPCTSTR szBoss) {
  SetSVal(m_szCommonSect, _T("BOSS"), szBoss);
}

CString CIniCache::GetPosada() {
  return GetSVal(m_szCommonSect, _T("Posada"), _T("") );
}
void CIniCache::SetPosada(LPCTSTR szPosada) {
  SetSVal(m_szCommonSect, _T("Posada"), szPosada);
}

CString CIniCache::GetPIBPO() {
  return GetSVal(m_szCommonSect, _T("PIBPO"), _T("") );
}
void CIniCache::SetPIBPO(LPCTSTR szPIBPO) {
  SetSVal(m_szCommonSect, _T("PIBPO"), szPIBPO);
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
  if ( szRags.Find(_T("Виконавчий орган") )==0 )
    return TRUE;
  if ( szRags.Find(_T("Виконавчий Орган") )==0 )
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

CString CIniCache::GetDefStamp() {
  CString s;
  s.Format( _T("Міністерство юстиції України\r\n%s"), GetStringPart(DecodeRagsName(GetRAGS()), 0) );
  return s;
}

UINT CIniCache::GetUseStamp1() {
  return GetIVal(m_szCommonSect, _T("UseStamp1"), 0);
}

void CIniCache::SetUseStamp1(UINT fUse) {
  SetIVal(m_szCommonSect, _T("UseStamp1"), fUse);
}

CString CIniCache::GetStamp1() {
  return GetSVal(m_szCommonSect, _T("Stamp1"), GetDefStamp());
}

void CIniCache::SetStamp1(LPCTSTR szStamp) {
  SetSVal(m_szCommonSect, _T("Stamp1"), szStamp);
}

UINT CIniCache::GetUseStamp2() {
  return GetIVal(m_szCommonSect, _T("UseStamp2"), 0);
}

void CIniCache::SetUseStamp2(UINT fUse) {
  SetIVal(m_szCommonSect, _T("UseStamp2"), fUse);
}

CString CIniCache::GetStamp2() {
  return GetSVal(m_szCommonSect, _T("Stamp2"), GetDefStamp());
}
void CIniCache::SetStamp2(LPCTSTR szStamp) {
  SetSVal(m_szCommonSect, _T("Stamp2"), szStamp);
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
CString CIniCache::GetToSocProt() {
  return GetSVal(m_szCommonSect, _T("SOCPROT"), _T("") );
}
void CIniCache::SetToSocProt(LPCTSTR szTo) {
  SetSVal(m_szCommonSect, _T("SOCPROT"), szTo );
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

UINT CIniCache::GetMakeTVKXLS() {
  return GetIVal(m_szCommonSect, _T("TVKXLS"), 1);
}
void CIniCache::SetMakeTVKXLS(UINT uCheck) {
  SetIVal(m_szCommonSect, _T("TVKXLS"), uCheck);
}

UINT CIniCache::GetTVKDash() {
  return GetIVal(m_szCommonSect, _T("TVKDash"), 1);
}
void CIniCache::SetTVKDash(UINT uCheck) {
  SetIVal(m_szCommonSect, _T("TVKDash"), uCheck);
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

CString CIniCache::GetBIRTH_DefNotice() {
  return GetSVal(m_szBirthSect, _T("DefNotice"),
                 _T("Внесено до Державного реєстру актів цивільного стану громадян                          року за номером\r\n")
                 _T("Видана довідка № !№! від !дата! на отримання допомоги у зв'язку з народженням дитини.")
                );
}

void CIniCache::SetBIRTH_DefNotice(LPCTSTR szDefNotice) {
  SetSVal(m_szBirthSect, _T("DefNotice"), szDefNotice);
}

CString CIniCache::GetBIRTH_DefNotice2() {
  return GetSVal(m_szBirthSect, _T("DefNotice2"), _T("Видана довідка № !№! від !дата! в управління праці та соціального захисту населення."));
}
void CIniCache::SetBIRTH_DefNotice2(LPCTSTR szDefNotice) {
  SetSVal(m_szBirthSect, _T("DefNotice2"), szDefNotice);
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

CString CIniCache::GetMARRIAGE_DefNotice() {
  return GetSVal(m_szMarriageSect, _T("DefNotice"),
                 _T("Внесено до Державного реєстру актів цивільного стану громадян                          року за номером\r\n")
                 _T("Направлення на медичне обстеження отримали")
                );
}

void CIniCache::SetMARRIAGE_DefNotice(LPCTSTR szDefNotice) {
  SetSVal(m_szMarriageSect, _T("DefNotice"), szDefNotice);
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

CString CIniCache::GetDEATH_DefNotice() {
  return GetSVal(m_szDeathSect, _T("DefNotice"),
                 _T("Внесено до державного реєстру актів цивільного стану громадян                          року за номером\r\n")
                 _T("Видана довідка № !№! від !дата! для отримання допомоги на поховання.")
                );
}

void CIniCache::SetDEATH_DefNotice(LPCTSTR szDefNotice) {
  SetSVal(m_szDeathSect, _T("DefNotice"), szDefNotice);
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

#ifndef FREE_LICENCE

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


CString CIniCache::GetXorForNewReg() {
  CString s, szComputerName;
  DWORD dwName = 30;
  GetComputerName(szComputerName.GetBuffer(MAX_COMPUTERNAME_LENGTH + 1), &dwName);
  szComputerName.ReleaseBuffer();
  szComputerName.MakeUpper();

  uLong adler = adler32(0L, Z_NULL, 0);
  adler = adler32(adler, (const Bytef *)(LPCTSTR)szComputerName, szComputerName.GetLength());
  s.Format("%lu", adler);
  return s;
}

CString CIniCache::GetNewRegCode() {
  CString s, szRet, szPwd;
  szPwd = Pad(GetXorForNewReg(), '0', 8);

  if ( theApp.m_RagsID <= 0 ) {
    theApp.m_RagsID = theIniCache.GetRagsID();
  }

  if ( theApp.m_RagsID <= 0 ) {
    return s;
  }

  CString szRagID;
  szRagID.Format(_T("%lu"), theApp.m_RagsID);
  CString szRags     = MakeKeysForRagsName(GetRAGS());
  CString szRDC;
  szRDC.Format(_T("%s, %s, %s"),
               Trim(GetREGION()),
               Trim(GetDISTRICT()),
               Trim(GetCITY_())
              );

  szRet = szPwd;                                      // 8

  // ID
  uLong adler = adler32(0L, Z_NULL, 0);
  adler = adler32(adler, (const Bytef *)(LPCTSTR)szRagID, szRagID.GetLength());
  s.Format("%lu", adler);
  szRet += RegCrypt(szPwd, Pad(s, '0', 8), true);    // 16

  // RAGS
  adler = adler32(0L, Z_NULL, 0);
  adler = adler32(adler, (const Bytef *)(LPCTSTR)szRags, szRags.GetLength());
  s.Format("%lu", adler);
  szRet += RegCrypt(szPwd, Pad(s, '0', 8), true);    // 24

  // REGION, DISTRICT, CITY
  adler = adler32(0L, Z_NULL, 0);
  adler = adler32(adler, (const Bytef *)(LPCTSTR)szRDC, szRDC.GetLength());
  s.Format("%lu", adler);
  szRet += RegCrypt(szPwd, Pad(s, '0', 8), true);    // 32

/*
  #ifdef _DEBUG
    szRet = _T("4869-3552-0640-6652-6504-6690-2880-3500");
  #endif
*/

  return szRet;
}

void RunWizard() {
  CString szCommandLine;

  szCommandLine.Format(_T("\"%s\" -wizard"), GetModuleFileName());

  TCHAR szExe[MAX_PATH*2];
  strncpy(szExe, szCommandLine, sizeof(szExe)-1);
  PROCESS_INFORMATION pi;
  STARTUPINFO         si;

  si.cb              = sizeof(STARTUPINFO);
  si.lpReserved      = NULL;
  si.lpReserved2     = NULL;
  si.cbReserved2     = 0;
  si.lpDesktop       = NULL;
  si.lpTitle         = NULL;
  si.dwFlags         = 0;
  si.dwX             = 0;
  si.dwY             = 0;
  si.dwFillAttribute = 0;
  si.wShowWindow     = SW_SHOW;

  CreateProcess(NULL,
                szExe,
                NULL,
                NULL,
                TRUE,
                NORMAL_PRIORITY_CLASS,
                NULL,
                NULL,
                &si,
                &pi);
}


LK_VALUE CIniCache::IsValidDigitLKey(const CString& szLKey) {
  CString szRC  = GetNewRegCode();

  if ( szRC.IsEmpty() ) {
    static BOOL fCalled = false;
    if ( fCalled ) {
      return LK_INVALID_LICENCE;
    }
    fCalled = true;
    if ( YNDlg(NULL, _T("Ваш виконком або орган реєстрації не визначений.\n")
                     _T("Потрібно визначити за допомогою Майстера Установки."),
                     _T("Запустити Майстер Установки?")) )
    {
      RunWizard();
      ExitProcess(0);
    }
    return LK_INVALID_LICENCE;
  }

  CString szPwd = szRC.Left(8);
  CString szRagsID = RegCrypt(szPwd, szRC.Mid( 8, 8), false);
  CString szRags   = RegCrypt(szPwd, szRC.Mid(16, 8), false);
  CString szRDC    = RegCrypt(szPwd, szRC.Mid(24, 8), false);

  CString s, szNewPwd;
  uLong adler = adler = adler32(0L, Z_NULL, 0);
  adler = adler32(adler, (const Bytef *)(LPCTSTR)szRC, szRC.GetLength());
  s.Format(_T("%lu"), adler);
  szNewPwd = Pad(s, '0', 8);

  s.Format(_T("%s%s%s%s%s"), szNewPwd,
           RegCrypt(szNewPwd, szRagsID, true),
           RegCrypt(szNewPwd, szRags,   true),
           RegCrypt(szNewPwd, szRDC,    true),
           szRagsID.Left(4)
          );
  s.MakeReverse();
  if ( s==szLKey ) {
    return LK_VALID_LICENCE;
  }

  CString szLstDate = GetLastDate(_T("LD"));
  CString szMaxDate = GetMaxSysDate();
  if ( szLstDate.GetLength()==8 && szMaxDate.GetLength()==8 ) {
    // CString szLstDateYYYYMMDD = szLstDate.Mid(1, 8);
    // CString szMaxDateYYYYMMDD = szMaxDate.Mid(1, 8);
    if ( szMaxDate < szLstDate ) {
      return LK_LICENCE_EXPIRED;
    }
    CString szNewLKey;
    szLstDate = GetLastDate(_T("LD"), false);
    for( int i = 0; i < 6; i++ ) {
      CString s1 = s.Mid(i*6, 6);
      szNewLKey += AddToLSection(s1, szLstDate[i*2], szLstDate[i*2+1], (i % 2)==0);
    }
    if ( szNewLKey==szLKey ) {
      m_fLimitedLicence = true;
      CString szLstDateLong = GetLastDate(_T("LD"), false);
      int nDays = atoi(szLstDateLong.Right(3));
      COleDateTime odt;
      odt.SetDateTime( atol(szLstDate.Mid(1,4)), atol(szLstDate.Mid(5,2)), atol(szLstDate.Mid(7,2)), 0, 0, 0);
      COleDateTimeSpan ods(nDays, 0, 0, 0);

      odt += ods;

      //g_szLastLDate = szLstDate; // szLstDateYYYYMMDD;
      COleDateTime odtNow = COleDateTime::GetCurrentTime();
      if ( odtNow > odt ) {
        return LK_LICENCE_EXPIRED;
      }
      
      // odt.SetDateTime( atol(g_szLastLDate.Mid(0,4)), atol(g_szLastLDate.Mid(4,2)), atol(g_szLastLDate.Mid(6,2)), 0, 0, 0);
      COleDateTimeSpan odts = odt - odtNow;
      g_nDaysRemaining = (long)odts.GetDays();

  /*
      CString s;
      s.Format(_T("LK_LICENCE_NOTEXPIRED, szLstDate=%s, odt=%04d%02d%02d, g_nDaysRemaining=%d"),
               szLstDate, odt.GetYear(), odt.GetMonth(), odt.GetDay(), g_nDaysRemaining);
      AfxMessageBox(s);

  */

      return LK_LICENCE_NOTEXPIRED;
    }
  }
  return LK_INVALID_LICENCE;
}

LK_VALUE CIniCache::IsValidLKey(LIC_KEY* pLC/*=NULL*/, CString* pszLKey/*=NULL*/) {
  CString szLKey = GetLKey();
  if ( szLKey.GetLength() != sizeof(LIC_KEY)*2 )
    return LK_INVALID_LICENCE;

  if ( IsDigit(szLKey) ) {
    return IsValidDigitLKey(szLKey);
  }

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
      return LK_VALID_LICENCE;
    }
  }
  return LK_INVALID_LICENCE;
}
CString CIniCache::GetDateCountStr() {
  CString s  = GetSVal(_T("DATES"), _T("DC"), _T(""));
  if ( s.GetLength() != 16 ) {
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
    sDate.MakeUpper();
    HexStringToBin(sDate, 2, &nDates, sizeof(nDates));
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


CString CIniCache::GetMaxSysDate() {
  BOOL fSave = false;
  CString szMax, szSaveMaxDate;
  COleDateTime odt = COleDateTime::GetCurrentTime();
  szMax.Format(_T("%04d%02d%02d"), odt.GetYear(), odt.GetMonth(), odt.GetDay());


  szSaveMaxDate = GetSVal(_T("DATES"), _T("MAXSD"), _T(""));

  if ( szSaveMaxDate.GetLength() != 8 ) {
    SetLastDate(szMax, _T("MAXSD"));
  }
  else {
    if ( szSaveMaxDate > szMax ) {
      szMax = szSaveMaxDate;
      fSave = true;
    }
    CString szSRegMax = theRegTimer.GetMaxDate();
    if ( szSRegMax > szMax ) {
      szMax = szSRegMax;
      fSave = true;
    }
  }
  if ( fSave ) {
    SetLastDate(szMax, _T("MAXSD"));
  }

  return szMax;
}

CString CIniCache::GetLastDate(LPCTSTR szKey, BOOL fShort /*= true*/) {
  CString szDate;
  CString szEncryptHex = GetSVal(_T("DATES"), szKey, _T(""));
  if ( szEncryptHex.GetLength()==48 ) {
    CString szHexDate;
    BYTE baDecryptBin[48];
    HexStringToBin(szEncryptHex, szEncryptHex.GetLength(), baDecryptBin, 24);
    CCrypto Decrypt;
    Decrypt.SetCryptoKey("vnk@ukr.net", 10);
    Decrypt.Decrypt(baDecryptBin, 24);
    memcpy(szHexDate.GetBuffer(24), baDecryptBin, 24);
    szHexDate.ReleaseBuffer();
    HexStringToBin(szHexDate, szHexDate.GetLength(), szDate.GetBuffer(12), 12);
    szDate.ReleaseBuffer();

    if ( fShort ) {
      if ( szDate.GetLength()==12 ) {
        szDate = szDate.Mid(1, 8);
      }
    }
  }
  return szDate;
}
void CIniCache::SetLastDate(const CString& szLDate, LPCTSTR szKey) {
  SetSVal(_T("DATES"), szKey, szLDate);
}

void CIniCache::SetDateCount(const COleDateTime& odt) {
  CString s = GetDateCountStr();
  if ( odt.GetStatus()==COleDateTime::valid) {
    BYTE nDates = 0;
    int dow = odt.GetDayOfWeek() - 1;
    CString sDate = s.Mid(dow*2, 2);
    HexStringToBin(sDate, s.GetLength(), &nDates, sizeof(nDates));
/*
#ifdef _STRCPY_S
    sscanf_s(sDate, "%02X", &nDates);
#else
    sscanf(sDate, "%02X", &nDates);
#endif
*/
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
    BYTE nDates = 0;
    CString sDate = s.Mid(i*2, 2);
    HexStringToBin(sDate, s.GetLength(), &nDates, sizeof(nDates));
/*
#ifdef _STRCPY_S
    sscanf_s(sDate, "%02X", &nDates);
#else
    sscanf(sDate, "%02X", &nDates);
#endif
*/
    nCount += nDates;
  }
  return nCount;
}
#endif // FREE_LICENCE

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
