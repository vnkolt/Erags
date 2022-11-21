// EraWiz.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "EraWiz.h"

#include "MasterDlg.h"

#include "SetRagsPage.h"
#include "SetGeoPlace.h"
#include "BirthPage.h"
#include "DivorcePage.h"
#include "MedicsPage.h"

#include "..\Common\CyrString.h"
#include "..\Common\DAO36.h"
#include "..\Common\MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern long g_RagsID;

/*
BOOL        g_fDebug = false;
CString     g_szEragsIni;

void DebugMessageBox(LPCTSTR szText) {
  if ( false==g_fDebug ) {
    return;
  }
  ::MessageBox(NULL, szText, _T("EraWiz"), MB_OK);
}
*/

CString GetFilePath(LPCTSTR szFileName){
CString sPath(szFileName);
  return sPath.Mid( 0, sPath.ReverseFind('\\') );
}

CString GetModulePath() {
  CString s;
  GetModuleFileName(NULL, s.GetBuffer(MAX_PATH), MAX_PATH);
  s.ReleaseBuffer();
  return GetFilePath(s);
}

BOOL FileExists(PCSTR pszFilename){
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = FindFirstFile(pszFilename, &FindFileData);

  if (INVALID_HANDLE_VALUE==hFind)
    return FALSE;
  FindClose(hFind);
  return TRUE;
}

LPCTSTR GetCertSeria() {
  struct SeriaForReg {
    LPCTSTR szRegion;
    LPCTSTR szSeria;
  };
  static SeriaForReg serias[] = { { _T("Крим")             , _T("І-АП") },
                                  { _T("Вінницька")        , _T("І-АМ") },
                                  { _T("Волинська")        , _T("І-ЕГ") },
                                  { _T("Дніпропетровська") , _T("І-КИ") },
                                  { _T("Донецька")         , _T("І-НО") },
                                  { _T("Житомирська")      , _T("І-ТП") },
                                  { _T("Закарпатська")     , _T("І-ФМ") },
                                  { _T("Запорізька")       , _T("І-ЖС") },
                                  { _T("Івано-Франківська"), _T("І-НМ") },
                                  { _T("Київська")         , _T("І-ОК") },
                                  { _T("Кіровоградська")   , _T("І-ОЛ") },
                                  { _T("Луганська")        , _T("І-ЕД") },
                                  { _T("Львівська")        , _T("І-СГ") },
                                  { _T("Миколаївська")     , _T("І-ФП") },
                                  { _T("Одеська")          , _T("І-ЖД") },
                                  { _T("Полтавська")       , _T("І-КЕ") },
                                  { _T("Рівненська")       , _T("І-ГЮ") },
                                  { _T("Сумська")          , _T("І-БП") },
                                  { _T("Тернопільська")    , _T("І-ИД") },
                                  { _T("Харківська")       , _T("І-ВЛ") },
                                  { _T("Херсонська")       , _T("І-КГ") },
                                  { _T("Хмельницька")      , _T("І-БВ") },
                                  { _T("Черкаська")        , _T("І-СР") },
                                  { _T("Чернівецька")      , _T("І-МИ") },
                                  { _T("Чернігівська")     , _T("І-ЕЛ") },
                                  { _T("Київ")             , _T("І-БК") },
                                  { _T("Севастополь")      , _T("І-АС") },
                                  { NULL                   , NULL       }
                                };
  for( int i(0); serias[i].szRegion; i++ ) {
    if ( g_szRegion.Find(serias[i].szRegion) >=0 ) {
      return serias[i].szSeria;
    }
  }
  return _T("І-НО");
}

bool IsTablePresent(CDaoDatabase* pDB, LPCTSTR pszTableName) {
  if ( pDB->IsOpen()==false )
    return false;

  CDaoTableDefInfo tdInfo;
  try {
    pDB->GetTableDefInfo(pszTableName, tdInfo);
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return false;
  }
  return true;
}

bool IsTablesIdentical(CDaoDatabase* pDB1, LPCTSTR szTable1, CDaoDatabase* pDB2, LPCTSTR szTable2) {
  bool fRet = false;
  CDaoTableDef td1(pDB1);
  CDaoTableDef td2(pDB2);
  try {
    td1.Open(szTable1);
    td2.Open(szTable2);
    short nFields = td1.GetFieldCount();
    if ( nFields == td2.GetFieldCount() ) {
      for( short i(0); i < nFields; i++ ) {
        CDaoFieldInfo fi1;
        CDaoFieldInfo fi2;
        td1.GetFieldInfo(i, fi1, AFX_DAO_PRIMARY_INFO);
        td2.GetFieldInfo(i, fi2, AFX_DAO_PRIMARY_INFO);
        if ( stricmp(fi1.m_strName, fi2.m_strName)!=0   // Если имена полей не совпадают
             || fi1.m_nType!=fi2.m_nType                // или типы не совпадают
             || fi1.m_lSize!=fi2.m_lSize                // или размеры не совпадают
             || fi1.m_lAttributes!=fi2.m_lAttributes ) {// или аттрибуты не совпадают
          break; // Уходим, таблицы разные
        }
      }
      if ( i==nFields ) {
        fRet = true; // Таблицы идентичны по полям и типам.
      }
    }
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
  if ( td1.IsOpen() ) { td1.Close(); }
  if ( td2.IsOpen() ) { td2.Close(); }
  return fRet;
}

LPCTSTR GetCityShortTypeFromCB(const CString& szCityType) {
  if ( szCityType.IsEmpty() ) {
    return _T("");
  }
  if ( szCityType==_T("місто") )
    return _T("м.");
  if ( szCityType==_T("смт") )
    return _T("смт");
  if ( szCityType==_T("селище") )
    return _T("слщ");
  return _T("село");
}

bool ClearTable(CDaoDatabase* pDB, LPCTSTR pszTableName, LPCTSTR szConnect) {
  CString sql;
  sql.Format(_T("DELETE FROM %s"), pszTableName);
  try {
    pDB->Execute(sql);
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return false;
  }
/*
  CString szDBName  = pDB->GetName();
  CString szDBNamePacked;
  szDBNamePacked.Format(_T("%s.tmp"), szDBName);

  pDB->Close();
  try {
    // CDaoWorkspace::RepairDatabase(szDBName);
    CDaoWorkspace::CompactDatabase(szDBName, szDBNamePacked, dbLangCyrillic, dbVersion30, szConnect);
    CFile::Rename(szDBNamePacked, szDBName);
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
  try {
    pDB->Open(szDBName, FALSE, FALSE, szConnect);
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
*/
  return true;
}
//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CEraWizApp

BEGIN_MESSAGE_MAP(CEraWizApp, CWinApp)
	//{{AFX_MSG_MAP(CEraWizApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraWizApp construction

CEraWizApp::CEraWizApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEraWizApp object

CEraWizApp    theApp;
CString       g_szDBPath;
CDaoDatabase  theDatabase;

UINT HashKey(LPCTSTR szKey) {
  CString sKey = szKey;
	UINT nHash = 0;
  LPCTSTR key = sKey;
	while (*key)
		nHash = (nHash<<5) + nHash + *key++;
	return nHash;
}

void WriteToDefaults(CDaoRecordset* prs, LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal) {
  CString szMapKey;
  szMapKey.Format(_T("%s_%s"), szSect, szKey);
  CString sValue = szDefVal;
  if ( prs->IsOpen() ) {
    try {
      BOOL bFound = FALSE;
      prs->SetCurrentIndex(_T("SECTION"));
      UINT hash = HashKey(szSect);
      COleVariant ovHash((long)hash, VT_I4);
      if ( prs->Seek(_T("="), &ovHash) ) {
        while ( FALSE==prs->IsEOF() ) {
          UINT hHash = (UINT)GetFieldLong(prs, _T("SECTION"));
          if ( hHash != hash) {
            break;
          }
          CString sKey = GetFieldString(prs, _T("KEY"));
          if ( sKey.CompareNoCase(szKey)==0 ) {
             prs->Edit(); 
             prs->SetFieldValue(_T("VALUE"), (LPCTSTR)sValue);
             prs->Update();
            bFound = TRUE;
            break;
          }
          prs->MoveNext();
        }
      }
      if ( FALSE==bFound ) {
        if ( FALSE==sValue.IsEmpty() && prs->CanAppend() ) {
          prs->AddNew();
          prs->SetFieldValue(_T("SECTION"), &ovHash);
          prs->SetFieldValue(_T("KEY"), szKey);
          prs->SetFieldValue(_T("VALUE"), (LPCTSTR)sValue);
          prs->Update();
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

CString ReadFromDefaults(CDaoRecordset* prs, LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal) {
  CString szMapKey;
  szMapKey.Format(_T("%s_%s"), szSect, szKey);
  CString sValue = szDefVal;
  if ( prs->IsOpen() ) {
    try {
      BOOL bFound = FALSE;
      prs->SetCurrentIndex(_T("SECTION"));
      UINT hash = HashKey(szSect);
      COleVariant ovHash((long)hash, VT_I4);
      if ( prs->Seek(_T("="), &ovHash) ) {
        while ( FALSE==prs->IsEOF() ) {
          UINT hHash = (UINT)GetFieldLong(prs, _T("SECTION"));
          if ( hHash != hash) {
            break;
          }
          CString sKey = GetFieldString(prs, _T("KEY"));
          if ( sKey.CompareNoCase(szKey)==0 ) {
            sValue = GetFieldString(prs, _T("VALUE"));
            bFound = TRUE;
            break;
          }
          prs->MoveNext();
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

void FillAbbrValues(CDaoRecordset& rs) {
  LPCTSTR szSect = _T("Abbreviations");
  WriteToDefaults(&rs, szSect, _T("ДВРАГС"), _T("державний відділ реєстрації актів цивільного стану"));
  WriteToDefaults(&rs, szSect, _T("ВРАГС"),  _T("відділ реєстрації актів цивільного стану"));
  WriteToDefaults(&rs, szSect, _T("Врагс"),  _T("відділ реєстрації актів цивільного стану"));
  WriteToDefaults(&rs, szSect, _T("врагс"),  _T("відділ реєстрації актів цивільного стану"));
  WriteToDefaults(&rs, szSect, _T("в.рагс"), _T("відділ реєстрації актів цивільного стану"));
  WriteToDefaults(&rs, szSect, _T("в/рагс"), _T("відділ реєстрації актів цивільного стану"));
  WriteToDefaults(&rs, szSect, _T("ВРАЦС"),  _T("відділ реєстрації актів цивільного стану"));
  WriteToDefaults(&rs, szSect, _T("Врацс"),  _T("відділ реєстрації актів цивільного стану"));
  WriteToDefaults(&rs, szSect, _T("врацс"),  _T("відділ реєстрації актів цивільного стану"));
  WriteToDefaults(&rs, szSect, _T("в.рацс"), _T("відділ реєстрації актів цивільного стану"));
  WriteToDefaults(&rs, szSect, _T("в/рацс"), _T("відділ реєстрації актів цивільного стану"));
  WriteToDefaults(&rs, szSect, _T("В"),      _T("виконком"));
  WriteToDefaults(&rs, szSect, _T("ВО"),     _T("виконавчий орган"));
  WriteToDefaults(&rs, szSect, _T("о"),      _T("області"));
  WriteToDefaults(&rs, szSect, _T("р"),      _T("району"));
  WriteToDefaults(&rs, szSect, _T("ср"),     _T("сільської ради"));
  WriteToDefaults(&rs, szSect, _T("с/р"),    _T("сільської ради"));
  WriteToDefaults(&rs, szSect, _T("с.р"),    _T("сільської ради"));
  WriteToDefaults(&rs, szSect, _T("с-р"),    _T("сільської ради"));
  WriteToDefaults(&rs, szSect, _T("сщр"),    _T("селищної ради"));
  WriteToDefaults(&rs, szSect, _T("мр"),     _T("міської ради"));
  WriteToDefaults(&rs, szSect, _T("м/р"),    _T("міської ради"));
  WriteToDefaults(&rs, szSect, _T("м-р"),    _T("міської ради"));
  WriteToDefaults(&rs, szSect, _T("ГУЮ"),    _T("Головного управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("Гую"),    _T("Головного управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("гую"),    _T("Головного управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("МРУЮ"),   _T("міськрайонного управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("Мрую"),   _T("міськрайонного управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("мрую"),   _T("міськрайонного управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("МУЮ"),    _T("міського управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("Мую"),    _T("міського управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("мую"),    _T("міського управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("РУЮ"),    _T("районного управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("Рую"),    _T("районного управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("рую"),    _T("районного управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("ОУЮ"),    _T("обласного управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("Оую"),    _T("обласного управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("оую"),    _T("обласного управління юстиції"));
  WriteToDefaults(&rs, szSect, _T("громадянського"), _T("цивільного"));
}
void MakeFromIni(const CString& sIniFile) {

  CDaoRecordset rs(&theDatabase);
  try {
    rs.Open(dbOpenTable, "[DEFAULTS]");
    FillAbbrValues(rs);
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return;
	}

  UINT nConverted = theApp.GetProfileInt(_T(""), _T("DefConverted"), 0);
  if ( FALSE==nConverted ) {
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
              WriteToDefaults(&rs, szSect, sKey, sValue);
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
  rs.Close();
  theApp.WriteProfileInt(_T(""), _T("DefConverted"), 1);
}
void ReadFromDefaults() {
  CDaoRecordset rs(&theDatabase);
  try {
    rs.Open(dbOpenTable, "[DEFAULTS]");
    g_szRagsName = ReadFromDefaults(&rs, _T("COMMON"), _T("RAGS"), _T(""));
    g_szRegion   = ReadFromDefaults(&rs, _T("COMMON"), _T("REGION"), _T(""));
    g_szDistrict = ReadFromDefaults(&rs, _T("COMMON"), _T("DISTRICT"), _T(""));
    g_szCity     = ReadFromDefaults(&rs, _T("COMMON"), _T("CITY"), _T(""));
    g_szRagsName = ReadFromDefaults(&rs, _T("COMMON"), _T("RAGS"), _T(""));
    g_szBoss     = ReadFromDefaults(&rs, _T("COMMON"), _T("BOSS"), _T(""));
    g_szByUMVS   = ReadFromDefaults(&rs, _T("COMMON"), _T("BYUMVS"), _T(""));
    g_szToUMVS   = ReadFromDefaults(&rs, _T("COMMON"), _T("TOUMVS"), _T(""));
    g_szByMil    = ReadFromDefaults(&rs, _T("COMMON"), _T("BYMIL"), _T(""));
    g_szToMil    = ReadFromDefaults(&rs, _T("COMMON"), _T("TOMIL"), _T(""));
    g_szToTax    = ReadFromDefaults(&rs, _T("COMMON"), _T("TOTAX"), _T(""));
    g_szByCourt  = ReadFromDefaults(&rs, _T("COMMON"), _T("BYCOURT"), _T(""));
    g_RagsID     = atol(ReadFromDefaults(&rs, _T("COMMON"), _T("RID"), _T("0")));
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return;
	}
  while ( FALSE==rs.IsEOF() ) {
    rs.MoveNext();
  }
  rs.Close();
} 
void ImportTable(LPCTSTR szTableName, CDaoDatabase* pDBDest, CDaoDatabase* pDBSource, LPCTSTR szConnect) {
  bool fDestTablePresent   = IsTablePresent(pDBDest,   szTableName);
  bool fSourceTablePresent = IsTablePresent(pDBSource, szTableName);
  if ( fSourceTablePresent && fDestTablePresent ) {
    ClearTable(pDBDest, szTableName, szConnect);
    CString szRecordset;
    szRecordset.Format(_T("[%s]"), szTableName);
    CDaoRecordset rsSrc(pDBSource);
    CDaoRecordset rsDst(pDBDest);
    rsSrc.Open(dbOpenTable, szRecordset);
    rsDst.Open(dbOpenTable, szRecordset);
    while ( !rsSrc.IsEOF() ) {
      rsDst.AddNew();
      for( int i(1); i < rsSrc.GetFieldCount(); i++ ) {
        COleVariant ovar;
        try {
          rsSrc.GetFieldValue(i, ovar);
          rsDst.SetFieldValue(i, ovar);
        }
        catch (CDaoException* e) {
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
      	}
      }
      rsDst.Update();
      rsSrc.MoveNext();
    }
  }
}

BOOL IsRecordPresent(CDaoRecordset& rs, LPCTSTR szField1, const COleVariant& ov1, LPCTSTR szField2, const COleVariant& ov2) {
  BOOL fRet = false;
  try {
    if ( false==rs.IsBOF() && false==rs.IsEOF() ) {
      COleVariant bm = rs.GetBookmark();  // Сохраняем текущую позицию в рекордсете
      rs.MoveFirst();
      while ( !rs.IsEOF()) {
        try {
          COleVariant ovar1, ovar2;
          rs.GetFieldValue(szField1, ovar1);
          rs.GetFieldValue(szField2, ovar2);
          if ( ov1==ovar1 && ov2==ovar2 ) { // Значение контрольных полей совпадают
            fRet = true;
            break;  // Больше не проверяем
          }
        }
        catch(CDaoException* e) {
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
        }
        rs.MoveNext();
      }
      rs.SetBookmark(bm); // Восстанавливаем позицию в рекордсете
    }
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
  return fRet;
}

void ImportDefaultsTable(CDaoDatabase* pDBDest, CDaoDatabase* pDBSource, LPCTSTR szConnect) {
  LPCTSTR szTableName = _T("Defaults");
  bool fDestTablePresent   = IsTablePresent(pDBDest,   szTableName);
  bool fSourceTablePresent = IsTablePresent(pDBSource, szTableName);
  if ( fSourceTablePresent && IsTablesIdentical(pDBDest, szTableName, pDBSource, szTableName) ) {
    CString szRecordset;
    szRecordset.Format(_T("[%s]"), szTableName);
    CDaoRecordset rsSrc(pDBSource);
    CDaoRecordset rsDst(pDBDest);
    rsSrc.Open(dbOpenTable, szRecordset);
    rsDst.Open(dbOpenTable, szRecordset);
    while ( !rsSrc.IsEOF() ) {
      COleVariant ovSECTION;
      COleVariant ovKEY;
      COleVariant ovVALUE;
      rsSrc.GetFieldValue(_T("SECTION"), ovSECTION);
      rsSrc.GetFieldValue(_T("KEY"),     ovKEY);
      rsSrc.GetFieldValue(_T("VALUE"),   ovVALUE);
      if ( false==IsRecordPresent(rsDst, _T("SECTION"), ovSECTION, _T("KEY"), ovKEY) ) {
        rsDst.AddNew();
        rsDst.SetFieldValue(_T("SECTION"), ovSECTION);
        rsDst.SetFieldValue(_T("KEY"),     ovKEY);
        rsDst.SetFieldValue(_T("VALUE"),   ovVALUE);
        rsDst.Update();
        rsDst.SetBookmark( rsDst.GetLastModifiedBookmark() );
      }
      rsSrc.MoveNext();
    }
  }
}

BOOL EXPORT Wizard(LPCTSTR szDBPath) {
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  // normal function body here
  CString sMsg;

  BOOL fRetVal = FALSE;

  try {
    AfxDaoInit36();
  }
  catch(...) {
    sMsg.Format(_T("Увага! Комплекс ЕРАГС використовує компоненти DAO 3.6.\n")
                _T("Будь ласка, встановіть DAO 3.6, а потім запустіть Майстер Установки ЕРАГС знов.\n")
                _T("Бібліотека DAO 3.6 поставляється разом з ПК ЕРАГС.")
                _T("Вам потрібна інсталяція ПЕ ЕРАГС версії від 31.05.2011 або більш пізньої.")
                );
    AfxMessageBox(sMsg);
    return FALSE;
  }

  if ( szDBPath ) {
    g_szDBPath = szDBPath;
  }
  else {
    g_szDBPath.Format(_T("%s\\DB"), GetModulePath());
  }

/*
  if ( g_fDebug ) {
    CString szMsg;
    szMsg.Format(_T("g_szDBPath=%s"), g_szDBPath);
    DebugMessageBox(szMsg);
  }
*/

  CString szRoot = g_szDBPath.Left(3);
  if ( szRoot.Left(2)==_T("\\\\") ) { // Don't make for network
    return TRUE;
  }

  if ( DRIVE_FIXED != GetDriveType(szRoot) ) {
    return TRUE;
  }

  CString sDBName, sDefaults;
  sDBName.Format(_T("%s\\Helpers.mdb"), g_szDBPath);
  sDefaults.Format(_T("%s\\Defaults.ini"), g_szDBPath);

/*
  if ( g_fDebug ) {
    CString szMsg;
    szMsg.Format(_T("sDBName=%s"), sDBName);
    DebugMessageBox(szMsg);
  }
*/

  BOOL dbOpened = true;

  try {
    CWaitCursor wc;
    static BYTE bPassword[] = { ~';', ~'P', ~'W', ~'D', ~'=',
                                ~'A', ~'n', ~'t', ~'o', ~'n',
                                ~'V', ~'i', ~'t', ~'a', ~'l', ~'i',~'a', ~0
                              };

    CString szPassword(' ', sizeof(bPassword));
    for( int i(0); i < sizeof(bPassword); i++ ) {
      szPassword.SetAt(i, ~bPassword[i]);
    }

    CString szConnect;
    szConnect.Format(_T("%s"), szPassword);

/*
    if ( g_fDebug ) {
      ::GetPrivateProfileString(_T("Settings"), _T("WizardConnection"), _T(""), szConnect.GetBuffer(512), 512, g_szEragsIni);
      szConnect.ReleaseBuffer();
    }
    if ( szConnect.IsEmpty() ) {
      szConnect.Format(_T("%s"), szPassword);
    }
    if ( g_fDebug ) {
      CString szMsg;
      szMsg.Format(_T("szConnect=%s"), szConnect);
      DebugMessageBox(szMsg);
    }
    if ( g_fDebug ) {
      CString szMsg;
      szMsg.Format(_T("CDaoWorkspace::GetVersion=%s, AfxGetModuleState()->m_dwVersion=0x%04x"),
                   CDaoWorkspace::GetVersion(),
                   _MFC_VER
                  );
      DebugMessageBox(szMsg);
    }

    if ( g_fDebug ) {
      DebugMessageBox(_T("Before theDatabase.Open."));
    }
*/
    try {
      theDatabase.Open(sDBName, FALSE, FALSE, szConnect);
      /*
      if ( g_fDebug ) {
        DebugMessageBox(_T("After theDatabase.Open.Success!"));
      }
      */
    }
    catch(CDaoException* e) {
      /*
      if ( g_fDebug ) {
        DebugMessageBox(_T("After theDatabase.Open.Failure!"));
      }
      */
      dbOpened = false;
      /*
      if ( g_fDebug ) {
        CString szMsg;
        szMsg.Format(_T("theDatabase.Open error=%d"), e->m_nAfxDaoError);
        DebugMessageBox(szMsg);
        e->ReportError();
      }
      */
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }

    MakeFromIni(sDefaults);
/************************************** : by VK at 22.01.2007 20:25:25 **\
    ReadFromDefaults();
\************************************** : by VK at 22.01.2007 20:25:27 **/

    CString sOldDBName;
    sOldDBName.Format(_T("%s.old"), sDBName);
    if ( FileExists(sOldDBName) ) {
      CDaoDatabase oldDatabase;
      try {
        oldDatabase.Open(sOldDBName, FALSE, FALSE, szConnect);
        try {
          ImportDefaultsTable(&theDatabase, &oldDatabase, szConnect);
        }
        catch(CDaoException* e) {
          /*
          if ( g_fDebug ) {
            CString szMsg;
            szMsg.Format(_T("ImportDefaultsTable, error=%d"), e->m_nAfxDaoError);
            DebugMessageBox(szMsg);
            e->ReportError();
          }
          */
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
        }
        try {
          ImportTable(_T("CausesOfDeath"), &theDatabase, &oldDatabase, szConnect);
        }
        catch(CDaoException* e) {
          /*
          if ( g_fDebug ) {
            CString szMsg;
            szMsg.Format(_T("ImportTable.CausesOfDeath, error=%d"), e->m_nAfxDaoError);
            DebugMessageBox(szMsg);
            e->ReportError();
          }
          */
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
        }
        try {
          ImportTable(_T("Hospitals"), &theDatabase, &oldDatabase, szConnect);
        }
        catch(CDaoException* e) {
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
        }
        try {
          ImportTable(_T("MIA"), &theDatabase, &oldDatabase, szConnect);
        }
        catch(CDaoException* e) {
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
        }
        try {
          ImportTable(_T("Streets"), &theDatabase, &oldDatabase, szConnect);
        }
        catch(CDaoException* e) {
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
        }
        oldDatabase.Close();
      }
      catch(CDaoException* e) {
        e->ReportError();
        e->Delete();
      }
    }
    ReadFromDefaults();
  }
  catch(CDaoException* e) {
    e->ReportError();
    e->Delete();
    return FALSE;
  }

  if ( dbOpened ) {
    CMasterDlg dlg;

    CSetRagsPage   RagsPage;
    CSetGeoPlace   GeoPage;
    CBirthPage     BirthPage;
    CDivorcePage   DivorcePage;
    CMedicsPage    MedicsPage;

    dlg.AddPage(&RagsPage,    CSetRagsPage::IDD);
    //dlg.AddPage(&MedicsPage,  CMedicsPage::IDD);
    dlg.AddPage(&GeoPage,     CSetGeoPlace::IDD);
    dlg.AddPage(&BirthPage,   CBirthPage::IDD);
    dlg.AddPage(&DivorcePage, CDivorcePage::IDD);
    dlg.AddPage(&MedicsPage,  CMedicsPage::IDD);

    if ( ID_WIZFINISH==dlg.DoModal() ) {
      fRetVal = TRUE;
    }

    theDatabase.Close();
  }

  AfxDaoTerm();

  return fRetVal;
}

BOOL CEraWizApp::InitInstance() {
	// TODO: Add your specialized code here and/or call the base class
  if ( theApp.m_pszAppName ) {
    free((void*)theApp.m_pszAppName);
    theApp.m_pszAppName = _tcsdup(_T("Erags"));
  }
  SetRegistryKey(_T("Vladimir Koltsov"));

/*
  g_szEragsIni.Format(_T("%s\\Erags.ini"), GetModulePath());
  g_fDebug = ::GetPrivateProfileInt(_T("Settings"), _T("DebugWizard"), 0, g_szEragsIni);


  // http://www.codeguru.com/forum/showthread.php?s=&threadid=191013&highlight=AfxGetModuleState
  // http://support.microsoft.com/default.aspx?scid=kb;EN-US;q236991

  DWORD dwAfxVersion = ::GetPrivateProfileInt(_T("Settings"), _T("AfxVersion"), 0, g_szEragsIni);

  if ( dwAfxVersion ) {
    AfxGetModuleState()->m_dwVersion = dwAfxVersion;
  }
*/
	return CWinApp::InitInstance();
}

int CEraWizApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
  AfxDaoTerm();
	return CWinApp::ExitInstance();
}
