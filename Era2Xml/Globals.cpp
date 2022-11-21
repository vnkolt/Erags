//
// Globals.cpp
//
#include "stdafx.h"
#include "Globals.h"

#include "db.h"
#include "Geography.h"
#include "Helpers.h"
#include "MyFileDialog.h"
#include "Registry.h"

#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR g_szEmpty = _T("");


CIniCache    theIniCache;
CDaoDatabase theHelperDB;
BOOL         g_fHelpersDBOpened = false;

CString      g_szRacsName;
CString      g_szRacsDirectorName;
CString      g_szRacsDirectorPos;
CString      g_szSpecialistNameForBirth;
CString      g_szSpecialistPosForBirth;
CString      g_szSpecialistNameForDeath;
CString      g_szSpecialistPosForDeath;


BOOL         g_fWriteRacsName               = false;
BOOL         g_fWriteRacsDirectorName       = false;
BOOL         g_fWriteRacsDirectorPosition   = false;

BOOL         g_fWriteBirthSpecialistName     = false;
BOOL         g_fWriteBirthSpecialistPosition = false;
BOOL         g_fWriteDeathSpecialistName     = false;
BOOL         g_fWriteDeathSpecialistPosition = false;


bool OpenHelpersDB(const CString& szMDBFilename) {
  static BYTE bPassword[] = { ~';', ~'P', ~'W', ~'D', ~'=',
                              ~'A', ~'n', ~'t', ~'o', ~'n',
                              ~'V', ~'i', ~'t', ~'a', ~'l', ~'i',~'a', ~0
                            };

  if ( g_fHelpersDBOpened ) {
    return true;
  }

  CString szConnect(' ', sizeof(bPassword));
  for( int i(0); i < sizeof(bPassword); i++ ) {
    szConnect.SetAt(i, ~bPassword[i]);
  }
  try {

    theHelperDB.Open(szMDBFilename,   // database name
                     false,           // Exclusive
                     true,            // Read only,
                     szConnect        // szConnect
                    );
    g_fHelpersDBOpened = true;
  }
  catch(CDaoException* e){
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return false;
  }
  return true;
}

BOOL LoadMDBValues() {
_Open:
  if ( FileExists(g_szHelpersMDB) && OpenHelpersDB(g_szHelpersMDB) ) {
    theIniCache.Load(theHelperDB);
    return true;
  }
  CMyFileDialog ofd(TRUE, "Helpers.mdb", NULL, OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_LONGNAMES, _T("Службовий файл БД ЕРАГС(Helpers.mdb)|Helpers.mdb|"), NULL);
  ofd.SetTitle(0, _T("Вкажіть службовий файл ПК ЕРАГС"));
  if ( IDOK==ofd.DoModal() ) {
    g_szHelpersMDB = ofd.GetPathName();
    goto _Open;
  }

  return false;
}

/////////////////////////////////////////////////////////////////////////////
// CIniCache class members
CIniCache::CIniCache() {
  m_fLoaded = false;
  m_prs = NULL;
  m_szCommonSect   = _T("COMMON");
  m_szAbbrSect     = _T("Abbreviations");
/*
  m_szBirthSect    = _T("BIRTH_FORM");
  m_szMarriageSect = _T("MARRIAGE_FORM");
  m_szDivorceSect  = _T("DIVORCE_FORM");
  m_szChangeSect   = _T("CHANGE_FORM");
  m_szDeathSect    = _T("DEATH_FORM");
*/
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

void CIniCache::FillAbbrCache() {
  m_AbbrMap.RemoveAll();


  if ( IsOpen() ) {
    try {
      m_prs->SetCurrentIndex(_T("SECTION"));
      UINT hash = HashKey(m_szAbbrSect);
      COleVariant ovHash((long)hash, VT_I4);
      if ( m_prs->Seek(_T("="), &ovHash) ) {
        while ( FALSE==m_prs->IsEOF() ) {
          UINT hHash = (UINT)GetFieldLong(*m_prs, _T("SECTION"));
          if ( hHash != hash) {
            break;
          }
          CString sKey   = GetFieldString(*m_prs, _T("KEY"));
          CString sValue = GetFieldString(*m_prs, _T("VALUE"));

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

  m_AbbrMap.SetAt(_T("ВРАГС") , _T("відділ реєстрації актів цивільного стану"));
  m_AbbrMap.SetAt(_T("Врагс") , _T("відділ реєстрації актів цивільного стану"));
  m_AbbrMap.SetAt(_T("врагс") , _T("відділ реєстрації актів цивільного стану"));
  m_AbbrMap.SetAt(_T("в.рагс"), _T("відділ реєстрації актів цивільного стану"));
  m_AbbrMap.SetAt(_T("в/рагс"), _T("відділ реєстрації актів цивільного стану"));
  m_AbbrMap.SetAt(_T("ВРАЦС") , _T("відділ реєстрації актів цивільного стану"));
  m_AbbrMap.SetAt(_T("Врацс") , _T("відділ реєстрації актів цивільного стану"));
  m_AbbrMap.SetAt(_T("врацс") , _T("відділ реєстрації актів цивільного стану"));
  m_AbbrMap.SetAt(_T("в.рацс"), _T("відділ реєстрації актів цивільного стану"));
  m_AbbrMap.SetAt(_T("в/рацс"), _T("відділ реєстрації актів цивільного стану"));
  m_AbbrMap.SetAt(_T("В")     , _T("виконком"));
  m_AbbrMap.SetAt(_T("о")     , _T("області"));
  m_AbbrMap.SetAt(_T("р")     , _T("району"));
  m_AbbrMap.SetAt(_T("ср")    , _T("сільської ради"));
  m_AbbrMap.SetAt(_T("с/р")   , _T("сільської ради"));
  m_AbbrMap.SetAt(_T("с.р")   , _T("сільської ради"));
  m_AbbrMap.SetAt(_T("с-р")   , _T("сільської ради"));
  m_AbbrMap.SetAt(_T("сщр")   , _T("селищної ради"));
  m_AbbrMap.SetAt(_T("мр")    , _T("міської ради"));
  m_AbbrMap.SetAt(_T("м/р")   , _T("міської ради"));
  m_AbbrMap.SetAt(_T("м-р")   , _T("міської ради"));
  m_AbbrMap.SetAt(_T("ГУЮ")   , _T("Головного управління юстиції"));
  m_AbbrMap.SetAt(_T("Гую")   , _T("Головного управління юстиції"));
  m_AbbrMap.SetAt(_T("гую")   , _T("Головного управління юстиції"));
  m_AbbrMap.SetAt(_T("МРУЮ")  , _T("міськрайонного управління юстиції"));
  m_AbbrMap.SetAt(_T("Мрую")  , _T("міськрайонного управління юстиції"));
  m_AbbrMap.SetAt(_T("мрую")  , _T("міськрайонного управління юстиції"));
  m_AbbrMap.SetAt(_T("МУЮ")   , _T("міського управління юстиції"));
  m_AbbrMap.SetAt(_T("Мую")   , _T("міського управління юстиції"));
  m_AbbrMap.SetAt(_T("мую")   , _T("міського управління юстиції"));
  m_AbbrMap.SetAt(_T("РУЮ")   , _T("районного управління юстиції"));
  m_AbbrMap.SetAt(_T("Рую")   , _T("районного управління юстиції"));
  m_AbbrMap.SetAt(_T("рую")   , _T("районного управління юстиції"));
  m_AbbrMap.SetAt(_T("ОУЮ")   , _T("обласного управління юстиції"));
  m_AbbrMap.SetAt(_T("Оую")   , _T("обласного управління юстиції"));
  m_AbbrMap.SetAt(_T("оую")   , _T("обласного управління юстиції"));
  m_AbbrMap.SetAt(_T("ВДРАЦС"), _T("відділ державної реєстрації актів цивільного стану"));
  m_AbbrMap.SetAt(_T("ВДРАГС"), _T("відділ державної реєстрації актів громадянського стану"));
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


CString CIniCache::GetPrivateProfileString(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal) {
  CString szMapKey;
  szMapKey.Format(_T("%s_%s"), szSect, szKey);
  CString sValue;
  if ( m_keys.Lookup(szMapKey, sValue) ) {
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
          UINT hHash = (UINT)GetFieldLong(*m_prs, _T("SECTION"));
          if ( hHash != hash) {
            break;
          }
          CString sKey = GetFieldString(*m_prs, _T("KEY"));
          if ( sKey.CompareNoCase(szKey)==0 ) {
            sValue = GetFieldString(*m_prs, _T("VALUE"));
            bFound = TRUE;
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
  if ( false==sValue.IsEmpty() ) {
    m_keys.SetAt(szMapKey, sValue);
  }
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
          UINT hHash = (UINT)GetFieldLong(*m_prs, _T("SECTION"));
          if ( hHash != hash) {
            break;
          }
          CString sKey = GetFieldString(*m_prs, _T("KEY"));
          if ( sKey.CompareNoCase(szKey)==0 ) {
            sValue = GetFieldString(*m_prs, _T("VALUE"));
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

CString CIniCache::GetSVal(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal) {
  return GetPrivateProfileString(szSect, szKey, szDefVal);
}

UINT CIniCache::GetIVal(LPCTSTR szSect, LPCTSTR szKey, UINT iDefVal) {
  return GetPrivateProfileInt(szSect, szKey, iDefVal);
}

BOOL CIniCache::Load(CDaoDatabase& db) {

  if ( m_fLoaded ) {
    return true;
  }

  if ( Open(db) ) {
    FillAbbrCache();
    
    g_szRacsName                = GetRacsName();
    g_szRacsDirectorName        = GetRacsDirectorName();
    g_szRacsDirectorPos         = GetRacsDirectorPosition();
    g_szSpecialistNameForBirth  = GetSpecialistNameForBirth();
    g_szSpecialistPosForBirth   = GetSpecialistPosForBirth();
    g_szSpecialistNameForDeath  = GetSpecialistNameForDeath();
    g_szSpecialistPosForDeath   = GetSpecialistPosForDeath();

    
    g_fWriteRacsName                = GetWriteRacsName();
    g_fWriteRacsDirectorName        = GetWriteRacsDirectorName();
    g_fWriteRacsDirectorPosition    = GetWriteRacsDirectorPosition();

    g_fWriteBirthSpecialistName     = GetWriteBirthSpecialistName();
    g_fWriteBirthSpecialistPosition = GetWriteBirthSpecialistPosition();

    g_fWriteDeathSpecialistName     = GetWriteDeathSpecialistName();
    g_fWriteDeathSpecialistPosition = GetWriteDeathSpecialistPosition();

    m_fLoaded = true;
    return true;
	}
  return false;
}

CString CIniCache::GetCOUNTRY() {  
  return GetSVal(m_szCommonSect, _T("COUNTRY"), _T("Україна") );
}
CString CIniCache::GetREGION() {
  return GetSVal(m_szCommonSect, _T("REGION"), _T("") );
}
CString CIniCache::GetCITY() {
  return GetSVal(m_szCommonSect, _T("CITY"), _T("") );
}
CString CIniCache::GetDISTRICT() {
  return GetSVal(m_szCommonSect, _T("DISTRICT"), _T("") );
}
CString CIniCache::GetRAGS() {
  return GetSVal(m_szCommonSect, _T("RAGS"), _T("") );
}

CString CIniCache::GetRagsFullName() {
  CString sRags = GetRAGS();
  CString sDecoded;
  sDecoded.Format(_T(" %s "), sRags );
  int buf_size = sRags.GetLength()+2;
  char* pBuf = new char[buf_size];
#if _MFC_VER < 0x0800
  strcpy(pBuf, sRags);
  char* p = strtok(pBuf, " ");
#else
  strcpy_s(pBuf, buf_size, sRags);
  char *next_token = NULL;
  char* p = strtok_s(pBuf, " ", &next_token);
#endif
  while(p) {
    CString sValue;
    if ( LookupAbbr(p, sValue) ) {
      CString sFind, sReplace;
      sFind.Format(_T(" %s "), p );
      sReplace.Format(_T(" %s "), sValue );
      sDecoded.Replace(sFind, sReplace);
    }
#if _MFC_VER < 0x0800
    p = strtok(NULL, " ");
#else
    p = strtok_s(NULL, " ", &next_token);
#endif
  }
  delete pBuf;
  sDecoded.TrimLeft();
  sDecoded.TrimRight();
  return sDecoded;
}

CString CIniCache::GetRacsName() {
  CRegistry r(_T("Era2Xml"));
  CString s = r.GetProfileString(_T("Settings"), _T("RacsName"), _T(""));
  if ( s.IsEmpty() ) {
    s = GetRagsFullName();
  }
  return s;
}

void CIniCache::SetRacsName(LPCTSTR szName) {
  CRegistry r(_T("Era2Xml"));
  r.WriteProfileString(_T("Settings"), _T("RacsName"), szName);
}

CString CIniCache::GetRacsDirectorName() {
  CRegistry r(_T("Era2Xml"));
  CString s = r.GetProfileString(_T("Settings"), _T("RacsDirectorName"), _T(""));
  if ( s.IsEmpty() ) {
    s = GetSVal(m_szCommonSect, _T("BOSS"), _T(""));
  }
  return s;
}

void CIniCache::SetRacsDirectorName(LPCTSTR szName) {
  CRegistry r(_T("Era2Xml"));
  r.WriteProfileString(_T("Settings"), _T("RacsDirectorName"), szName);
}

CString CIniCache::GetRacsDirectorPosition() {
  CRegistry r(_T("Era2Xml"));
  CString s = r.GetProfileString(_T("Settings"), _T("RacsDirectorPosition"), _T(""));
  return s;
}
void CIniCache::SetRacsDirectorPosition(LPCTSTR szPosition) {
  CRegistry r(_T("Era2Xml"));
  r.WriteProfileString(_T("Settings"), _T("RacsDirectorPosition"), szPosition);
}

CString CIniCache::GetSpecialistNameForBirth() {
  CRegistry r(_T("Era2Xml"));
  CString s = r.GetProfileString(_T("Settings"), _T("SpecialistNameForBirth"), _T(""));
  if ( s.IsEmpty() ) {
    s = GetPIBPO();
  }
  return s;
}
void CIniCache::SetSpecialistNameForBirth(LPCTSTR szName) {
  CRegistry r(_T("Era2Xml"));
  r.WriteProfileString(_T("Settings"), _T("SpecialistNameForBirth"), szName);
}

CString CIniCache::GetSpecialistPosForBirth() {
  CRegistry r(_T("Era2Xml"));
  CString s = r.GetProfileString(_T("Settings"), _T("SpecialistPosForBirth"), _T(""));
  if ( s.IsEmpty() ) {
    s = GetPosada();
  }
  return s;
}
void CIniCache::SetSpecialistPosForBirth(LPCTSTR szPosition) {
  CRegistry r(_T("Era2Xml"));
  r.WriteProfileString(_T("Settings"), _T("SpecialistPosForBirth"), szPosition);
}

CString CIniCache::GetSpecialistNameForDeath() {
  CRegistry r(_T("Era2Xml"));
  CString s = r.GetProfileString(_T("Settings"), _T("SpecialistNameForDeath"), _T(""));
  if ( s.IsEmpty() ) {
    s = GetPIBPO();
  }
  return s;
}
void CIniCache::SetSpecialistNameForDeath(LPCTSTR szName) {
  CRegistry r(_T("Era2Xml"));
  r.WriteProfileString(_T("Settings"), _T("SpecialistNameForDeath"), szName);
}

CString CIniCache::GetSpecialistPosForDeath() {
  CRegistry r(_T("Era2Xml"));
  CString s = r.GetProfileString(_T("Settings"), _T("SpecialistPosForDeath"), _T(""));
  if ( s.IsEmpty() ) {
    s = GetPosada();
  }
  return s;
}
void CIniCache::SetSpecialistPosForDeath(LPCTSTR szPosition) {
  CRegistry r(_T("Era2Xml"));
  r.WriteProfileString(_T("Settings"), _T("SpecialistPosForDeath"), szPosition);
}

BOOL CIniCache::GetBool(LPCTSTR szValueName, BOOL fDefault/*=false*/) {
  CRegistry r(_T("Era2Xml"));
  return r.GetProfileInt(_T("Settings"), szValueName, fDefault);
}
void CIniCache::SetBool(LPCTSTR szValueName, BOOL fBool) {
  CRegistry r(_T("Era2Xml"));
  r.WriteProfileInt(_T("Settings"), szValueName, fBool);
}

BOOL CIniCache::GetWriteRacsName() {
  return GetBool(_T("WriteRacsName"), true);
}

void CIniCache::SetWriteRacsName(BOOL fWrite) {
  SetBool(_T("WriteRacsName"), fWrite);
}

BOOL CIniCache::GetWriteRacsDirectorName() {
  return GetBool(_T("WriteRacsDirectorName"), true);
}
void CIniCache::SetWriteRacsDirectorName(BOOL fWrite) {
  SetBool(_T("WriteRacsDirectorName"), fWrite);
}
BOOL CIniCache::GetWriteRacsDirectorPosition() {
  return GetBool(_T("WriteRacsDirectorPosition"));
}
void CIniCache::SetWriteRacsDirectorPosition(BOOL fWrite) {
  SetBool(_T("WriteRacsDirectorPosition"), fWrite);
}
BOOL CIniCache::GetWriteBirthSpecialistName() {
  return GetBool(_T("WriteBirthSpecialistName"));
}
void CIniCache::SetWriteBirthSpecialistName(BOOL fWrite) {
  SetBool(_T("WriteBirthSpecialistName"), fWrite);
}
BOOL CIniCache::GetWriteBirthSpecialistPosition() {
  return GetBool(_T("WriteBirthSpecialistPosition"));
}
void CIniCache::SetWriteBirthSpecialistPosition(BOOL fWrite) {
  SetBool(_T("WriteBirthSpecialistPosition"), fWrite);
}
BOOL CIniCache::GetWriteDeathSpecialistName() {
  return GetBool(_T("WriteDeathSpecialistName"));
}
void CIniCache::SetWriteDeathSpecialistName(BOOL fWrite) {
  SetBool(_T("WriteDeathSpecialistName"), fWrite);
}
BOOL CIniCache::GetWriteDeathSpecialistPosition() {
  return GetBool(_T("WriteDeathSpecialistPosition"));
}
void CIniCache::SetWriteDeathSpecialistPosition(BOOL fWrite) {
  SetBool(_T("WriteDeathSpecialistPosition"), fWrite);
}


CString CIniCache::GetPosada() {
  return GetSVal(m_szCommonSect, _T("Posada"), _T("") );
}

CString CIniCache::GetPIBPO() {
  return GetSVal(m_szCommonSect, _T("PIBPO"), _T("") );
}

CString CIniCache::GetParent() {
  return GetSVal(m_szCommonSect, _T("PARENT"), _T("") );
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


BOOL LoadCaches(CProgressCtrl* pProgressCtrl, CStatic* pStatic) {

  if ( FileExists(g_szHelpersMDB) ) {
    if ( OpenHelpersDB(g_szHelpersMDB) ) {
      theIniCache.Load(theHelperDB);

      theGeoCache.Load(theHelperDB, pProgressCtrl, pStatic);
      // theHelperDB.Close();
      return true;
    }
  }

  return false;
}

void CloseHelperDB() {
  if ( theHelperDB.IsOpen() ) {
    theHelperDB.Close();
  }
}