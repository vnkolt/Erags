//
// DataManager.cpp
//
#include "stdafx.h"
#include "Erags.h"
#include "DataManager.h"
#include "DBHospitals.h"
#include "Caches.h"
#include "Geography.h"
#include "LoadDlg.h"
#include "Defaults.h"
#include "MainFrm.h"
#include "RegDlg.h"
#include "YesNoDlg.h"
#include "xMachine.h"

// #include "LoginDlg.h"
#include "LogThread.h"

#include "..\Common\DB.h"
#include "..\Common\FHelpers.h"
#include "..\Common\MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL g_LocalDB      = true;
BOOL dm_fNewBirth   = false;
BOOL dm_fNewMarrige = false;
BOOL dm_fNewDivorce = false;
BOOL dm_fNewChange  = false;
BOOL dm_fNewDeath   = false;

CDataManager theDataManager;

bool SetProperty(CDaoDatabase* pListsDBName, LPCTSTR szPropertyName, BYTE* pValue, int nSize);

LPCTSTR g_szDefCitizenship = _T("України");

CString GetSectionKey(const char* pKey) {
  CString sRet = _T("");
  while(*pKey && *pKey != '=')
    sRet += *pKey++;
  return sRet;
}

int GetYearFromDB(LPCTSTR szDBName) {
  if ( NULL==szDBName || 0==szDBName[0] )
    return -1;
  try {
    CString sYear;
    sYear.Format(_T("%d"), atoi(GetFileName(szDBName)));
    return atoi(sYear);
  }
  catch(...) {
    Log(_T("Нераспознанная ошибка."), _T("GetYearFromDB"));
  }
  return -1;
}

/////////////////////////////////////////////////////////////////////////////
// CFByP
int FByPACompare(const void *a1, const void *a2) {
  CFByP *p1 = *(CFByP**)a1,
        *p2 = *(CFByP**)a2;
  int iLen1 = p1->m_sKey.GetLength(),
      iLen2 = p2->m_sKey.GetLength();
  if ( iLen1 != iLen2 )
    return iLen2-iLen1;
  return p1->m_sKey.Compare(p2->m_sKey);
}

CFByP::CFByP(LPCTSTR szKey, LPCTSTR szName) {
  m_sKey = szKey;
  m_sName = szName;
}

/////////////////////////////////////////////////////////////////////////////
// CFByPArray
CFByPArray::CFByPArray() {
}
CFByPArray::~CFByPArray() {
  Clear();
}

void CFByPArray::Clear() {
  for( int i(0); i < m_array.GetSize(); i++ ) {
    CFByP* pFByP = (CFByP*)m_array.GetAt(i);
    if ( pFByP )
      delete pFByP;
  }
  m_array.RemoveAll();
}

CFByP* CFByPArray::Find(LPCTSTR szKey, LPCTSTR szName) {
  CString sKey  = szKey,
          sName = szName;
  for( int i(0); i < m_array.GetSize(); i++ ) {
    CFByP* p = (CFByP*)m_array.GetAt(i);
    if ( p->m_sKey==sKey )
      return p;
  }
  return NULL;
}

CString CFByPArray::OfferDefault(const CString&  sPatronymic) {
  CString s;
  int nLen = sPatronymic.GetLength();
  if ( sPatronymic.Find(_T("Васил")) == 0) 
    s = _T("Василь");
  else if ( sPatronymic.Find(_T("Данил")) == 0)
    s = _T("Данило");
  else if ( sPatronymic.Find(_T("Дмитр")) == 0)
    s = _T("Дмитро");
  else if ( sPatronymic.Find(_T("Гаврил")) == 0)
    s = _T("Гаврило");
  else if ( sPatronymic.Find(_T("Ізраі")) == 0)
    s = _T("Ізраіль");
  else if ( sPatronymic.Find(_T("Ізрае")) == 0)
    s = _T("Ізраель");
  else if ( sPatronymic.Find(_T("Ілларіон")) == 0)
    s = _T("Ілларіон");
  else if ( sPatronymic.Find(_T("Ілл")) == 0)
    s = _T("Ілля");
  else if ( sPatronymic.Find(_T("Калін")) == 0)
    s = _T("Каліна");
  else if ( sPatronymic.Find(_T("Кирил")) == 0)
    s = _T("Кирило");
  else if ( sPatronymic.Find(_T("Микит")) == 0)
    s = _T("Микита");
  else if ( sPatronymic.Find(_T("Микол")) == 0)
    s = _T("Микола");
  else if ( sPatronymic.Find(_T("Михайл")) == 0)
    s = _T("Михайло");
  else if ( sPatronymic.Find(_T("Павл")) == 0)
    s = _T("Павло");
  else if ( sPatronymic.Find(_T("Петр")) == 0)
    s = _T("Петро");
  else if ( sPatronymic.Right(5)==_T("іївна") )
    s = sPatronymic.Left(nLen-4) + _T("й");
  else
    s = sPatronymic.Left(nLen-4);
  return s;
}

CFByP* CFByPArray::Offer(const CString&  sPatronymic) {
  for( int i(0); i < m_array.GetSize(); i++ ) {
    CFByP* p = (CFByP*)m_array.GetAt(i);
    if ( sPatronymic.Find(p->m_sKey)==0 )
      return p;
  }
  return NULL;
}

void CFByPArray::Add(LPCTSTR szKey, LPCTSTR szName) {
  if ( Find(szKey, szName)==NULL ) {
    CFByP* p = new CFByP(szKey, szName);
    m_array.Add( p );
  }
}

void CFByPArray::Sort() {
  if ( m_array.GetSize() ) {
    qsort( m_array.GetData(), m_array.GetSize(), sizeof(CFByP*), FByPACompare);
  }
}

void CFByPArray::Load(LPCTSTR szFileName) {
  bool bOk(false);
  const int KEYBUF_SIZE = 0x4000;
  TCHAR* pKBuffer = new TCHAR[KEYBUF_SIZE];
  ::GetPrivateProfileSection(_T("FNames"), pKBuffer, KEYBUF_SIZE, szFileName);
  char* pKey = pKBuffer;
  while( *pKey ) {
    CString sValue;
    CString sKey = GetSectionKey(pKey);
    ::GetPrivateProfileString(_T("FNames"), sKey, _T(""), sValue.GetBuffer(128), 128, szFileName);
    sValue.ReleaseBuffer();
    Add(sKey, sValue);
    pKey += strlen(pKey)+1;
    bOk = true;
  }
  if ( bOk )
    m_sFileName = szFileName;
  delete pKBuffer;
}
void CFByPArray::Save() {
  if ( !m_sFileName.IsEmpty() ) {
    for( int i(0); i < m_array.GetSize(); i++ ) {
      CFByP* p = (CFByP*)m_array.GetAt(i);
      ::WritePrivateProfileString(_T("FNames"), p->m_sKey, p->m_sName, m_sFileName );
    }
  }
}


void DisplayDaoException(CDaoException* e){
CString strMsg;

  if (e->m_pErrorInfo!=NULL){
    strMsg.Format(_T("%s   (%d)\n\n")
                  _T("Would you like to see help?"),
                  (LPCTSTR)e->m_pErrorInfo->m_strDescription,
                  e->m_pErrorInfo->m_lErrorCode);

    if (strMsg.Find(_T("password")) != -1)
      return;
    if ( IDYES==MessageBox(AfxGetMainWnd()->m_hWnd, strMsg, _T("ЕРАГС"), MB_YESNO|MB_ICONQUESTION) ) {
        WinHelp(GetDesktopWindow(),
                e->m_pErrorInfo->m_strHelpFile,
                HELP_CONTEXT,
                e->m_pErrorInfo->m_lHelpContext);
    }
  }
  else{
    strMsg.Format(_T("ERROR:CDaoException\n\n")
                  _T("SCODE_CODE      =%d\n")
                  _T("SCODE_FACILITY  =%d\n")
                  _T("SCODE_SEVERITY  =%d\n")
                  _T("ResultFromScode =%d\n"),
                  SCODE_CODE      (e->m_scode),
                  SCODE_FACILITY  (e->m_scode),
                  SCODE_SEVERITY  (e->m_scode),
                  ResultFromScode (e->m_scode));
    MessageBox(AfxGetMainWnd()->m_hWnd, strMsg, _T("ЕРАГС"), MB_OK|MB_ICONSTOP);
  }
}

/////////////////////////////////////////////////////////////////////////////
// CDataManager

CDataManager::CDataManager() {
  m_fCashFilled = FALSE;
  Init();
}

CDataManager::~CDataManager() {
  CloseDatabases();
}

void CDataManager::Init() {
  m_Year = -1;  // Invalid year
  m_fBirthesTable = m_fMarrigesTable =
  m_fDivorcesTable = m_fChangesTable = 
  m_fDeathesTable = m_fStreetTable = FALSE;

  m_fCausesOfDeathTable = m_fCitizenshipsTable =
  m_fGeographyTable = m_fHospitalsTable =
  m_fMIATable = m_fNamesTable = m_fPatronymicsTable =
  m_fRListTable = FALSE;
}

bool CDataManager::SetYearDBName(LPCTSTR pszFileName) {
  if( !FileExists(pszFileName) )
    return false;
  m_strYearDBName = pszFileName;
  return true;
}
CString CDataManager::GetYearDBName() {
  return m_strYearDBName;
}

bool CDataManager::SetListsDBName(LPCTSTR pszFileName) {
  //m_strListsDBName.Format(_T("%s\\Helpers.mdb"), GetFilePath(pszFileName));
  m_strListsDBName = theApp.GetHelperMDB();
  if( !FileExists(m_strListsDBName) )
    return false;
  return true;
}
CString CDataManager::GetListsDBName() {
  return m_strListsDBName;
}

bool CDataManager::OpenDatabases(LPCTSTR szYearDBName/*=NULL*/) {
  bool bRet(false);
/*
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if ( pMainWnd && pMainWnd->m_wndStatusBar.GetSafeHwnd() )
    pMainWnd->m_wndStatusBar.SetPaneText(0, _T("Завантажується база даних") );
*/
  CWaitCursor wc;

  CloseYearDB();
  m_strTables.RemoveAll();
  if ( OpenYearDB(szYearDBName) ) {
    //m_strDBFolder = GetDBFolder(m_strYearDBName);
    CString sDBPath = GetFilePath(m_strYearDBName);
    theApp.WriteProfileString(_T("Settings"), _T("Database"), m_strYearDBName);

    m_fBirthesTable  = IsTablePresent(_T("BIRTHES"));
    m_fMarrigesTable = IsTablePresent(_T("MARRIAGES"));
    m_fDivorcesTable = IsTablePresent(_T("DIVORCES"));
    m_fChangesTable  = IsTablePresent(_T("CHANGES"));
    m_fDeathesTable  = IsTablePresent(_T("DEATHES"));

    bRet = true;
    if ( FALSE==IsHelperOpened() ) {
      SetListsDBName(m_strYearDBName);
      if ( OpenHelpersDB() ) {
        bRet = true;
      }
      else {
        CloseDatabases();
        return false;
      }
    }
  }
/*
  if ( pMainWnd && pMainWnd->m_wndStatusBar.GetSafeHwnd() )
    pMainWnd->m_wndStatusBar.SetPaneText(0, _T("") );
*/
  return bRet;
}

void CDataManager::CloseHelpersDB() {
  if ( m_dbLists.IsOpen() ) {
    theIniCache.Close();
    m_dbLists.Close();
  }
}
void CDataManager::CloseYearDB() {
  if ( m_dbYear.IsOpen() ) {
    m_dbYear.Close();
    m_strYearDBName.Empty();
  }
}
void CDataManager::CloseDatabases() {
  CloseYearDB();
  CloseHelpersDB();
}
BOOL CDataManager::IsHelperOpened() {
  return m_dbLists.IsOpen();
}
void CDataManager::LoadTextData() {
  CString sDBPath = GetFilePath(m_strYearDBName);
  CString s;

  s.Format(_T("%s\\fnames.txt"), sDBPath);
  m_FByPArray.Load(s);
  m_FByPArray.Sort();
//  m_FByPArray.Save();

  FillCaches();
}

bool CDataManager::IsTableInArray(LPCTSTR pszTableName) {
  for ( int i(0); i < m_strTables.GetSize(); i++ ) {
    CString s = m_strTables.GetAt(i);
    if ( s.CompareNoCase(pszTableName)==0 )
      return true;
  }
  return false;
}

bool CDataManager::IsTablePresent(LPCTSTR pszTableName) {
  if ( m_dbYear.IsOpen()==false )
    return false;

  if ( IsTableInArray(pszTableName) )
    return true;

  CDaoTableDefInfo tdInfo;
  try {
    m_dbYear.GetTableDefInfo(pszTableName, tdInfo);
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      // e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return false;
  }
  m_strTables.Add( CString(pszTableName) );
  return true;
}

bool CDataManager::IsFieldPresent(CDaoTableDef& td, LPCTSTR szFieldName) {
  CDaoFieldInfo fieldinfo;
/*
  short nFields td.GetFieldCount();
  for( short i(0); i < nFields; i++ ) {
  }
*/
  try {  
    td.GetFieldInfo(szFieldName, fieldinfo, AFX_DAO_PRIMARY_INFO);
  }
  catch(...) {
    return false;
  }
  return true;
}

bool CDataManager::IsHelperTablePresent(LPCTSTR pszTableName) {
  if ( m_dbLists.IsOpen()==false )
    return false;

  CDaoTableDefInfo tdInfo;
  try {
    m_dbLists.GetTableDefInfo(pszTableName, tdInfo);
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return false;
  }

  return true;
}

void CDataManager::ResizeTextField(CDaoTableDef& td, CDaoFieldInfo& fieldinfo, int newSize) {
  CString szSQL1, szSQL2, szSQL3;
  CString szTable = td.GetName();
  CString szField = fieldinfo.m_strName;
  szSQL1.Format(_T("ALTER TABLE %s ADD COLUMN tmp%s TEXT (%d) NULL"), szTable, szField, newSize);
  szSQL2.Format(_T("UPDATE %s SET tmp%s = %s"), szTable, szField, szField);
  szSQL3.Format(_T("ALTER TABLE %s DROP COLUMN %s"), szTable, szField);

  try { m_dbYear.Execute(szSQL1); } catch(...) {}
  try { m_dbYear.Execute(szSQL2); } catch(...) {}
  try { m_dbYear.Execute(szSQL3); } catch(...) {}
  try {
    fieldinfo.m_lSize = newSize;
    td.CreateField(fieldinfo);
  }
  catch(CDaoException* e){
    #ifdef _DEBUG
    e->ReportError(); // to do logstring
    #endif
    e->Delete();
  }

  szSQL1.Format(_T("UPDATE %s SET %s = tmp%s"), szTable, szField, szField);
  szSQL2.Format(_T("ALTER TABLE %s DROP COLUMN tmp%s"), szTable, szField);
  try { m_dbYear.Execute(szSQL1); } catch(...) {}
  try { m_dbYear.Execute(szSQL2); } catch(...) {}
}

BOOL CDataManager::CreateTextField(CDaoTableDef& td, LPCTSTR szFieldName, LPCTSTR szTableName, long FieldSize, long ordinal, BOOL fMemo) {
  if ( IsFieldPresent(td, szFieldName) ) {
    return false;
  }
  BOOL fRet = true;
  CDaoFieldInfo fieldinfo;
  fieldinfo.m_strName = szFieldName;
  fieldinfo.m_nType   = fMemo ? dbMemo : dbText;
  fieldinfo.m_lSize   = fMemo ? 0      :FieldSize;
  fieldinfo.m_lAttributes = dbVariableField|dbUpdatableField;
  fieldinfo.m_nOrdinalPosition = ordinal;
  fieldinfo.m_bRequired = 0;
  fieldinfo.m_bAllowZeroLength = 0;
  fieldinfo.m_lCollatingOrder = 1049;
  fieldinfo.m_strForeignName = _T("");
  fieldinfo.m_strSourceField = szFieldName;
  fieldinfo.m_strSourceTable = szTableName;
  fieldinfo.m_strValidationRule = _T("");
  fieldinfo.m_strValidationText = _T("");
  fieldinfo.m_strDefaultValue = _T("");
  try {
    td.CreateField(fieldinfo);
    // td.GetFieldInfo(szFieldName, fieldinfo);
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
       e->ReportError(); // to do logstring
    #endif
    e->Delete();
    fRet = false;
  }
  return fRet;
}
void CDataManager::ModifyDatabase() {
  CDaoTableDef td(&m_dbYear);

  try {
    td.Open( _T("DIVORCES") );
    CDaoFieldInfo fieldinfo;
    LPCTSTR szModiField = NULL;

    td.GetFieldInfo(_T("MCHECK_BANK"), fieldinfo, AFX_DAO_ALL_INFO);
    if ( fieldinfo.m_lSize < 80 ) {
      ResizeTextField(td, fieldinfo, 80);
    }

    td.GetFieldInfo(_T("WCHECK_BANK"), fieldinfo, AFX_DAO_ALL_INFO);
    if ( fieldinfo.m_lSize < 80 ) {
      ResizeTextField(td, fieldinfo, 80);
    }

    if ( CreateTextField(td, _T("MBIRTH_CITY"),_T("DIVORCES"), 32, 19) ) {
      CreateTextField(td, _T("MBIRTH_DISTRICT") , _T("DIVORCES"), 32, 19);
      CreateTextField(td, _T("MBIRTH_COUNTRY"),      _T("DIVORCES"), 32, 19);
      CreateTextField(td, _T("MBIRTH_REGION"),    _T("DIVORCES"), 32, 19);

      CreateTextField(td, _T("WBIRTH_CITY")     ,  _T("DIVORCES"), 32, 47);
      CreateTextField(td, _T("WBIRTH_DISTRICT") ,  _T("DIVORCES"), 32, 47);
      CreateTextField(td, _T("WBIRTH_COUNTRY")  ,  _T("DIVORCES"), 32, 47);
      CreateTextField(td, _T("WBIRTH_REGION")   ,  _T("DIVORCES"), 32, 47);
    }
    CreateTextField(td, _T("EXTNOTES"),_T("DIVORCES"), 0, 77);

    td.Close();

    td.Open( _T("MARRIAGES") );
    CreateTextField(td, _T("EXTNOTES"),_T("MARRIAGES"), 0, 61);
    td.Close();

    td.Open( _T("CHANGES") );
    if ( false==IsFieldPresent(td, _T("PASSPORT_TYPE")) ) {
      CDaoFieldInfo fieldinfo;
      fieldinfo.m_strName = _T("PASSPORT_TYPE");
      fieldinfo.m_nType   = dbByte;
      fieldinfo.m_lSize   = 1;
      fieldinfo.m_lAttributes = dbFixedField;// | dbUpdatableField;
      fieldinfo.m_nOrdinalPosition = 30;
      fieldinfo.m_bRequired = 0;
      fieldinfo.m_bAllowZeroLength = 0;
      fieldinfo.m_lCollatingOrder = 1049;
      fieldinfo.m_strForeignName = _T("");
      fieldinfo.m_strSourceField = _T("PASSPORT_TYPE");
      fieldinfo.m_strSourceTable = _T("CHANGES");
      fieldinfo.m_strValidationRule = _T("");
      fieldinfo.m_strValidationText = _T("");
      fieldinfo.m_strDefaultValue = _T("0");
      td.CreateField(fieldinfo);
    }
    if ( false==IsFieldPresent(td, _T("DUTY")) ) {
      CDaoFieldInfo fieldinfo;
      fieldinfo.m_strName = _T("DUTY");
      fieldinfo.m_nType   = dbCurrency;
      fieldinfo.m_lSize   = 8;
      fieldinfo.m_lAttributes = dbFixedField;// | dbUpdatableField;
      fieldinfo.m_nOrdinalPosition = 28;
      fieldinfo.m_bRequired = 0;
      fieldinfo.m_bAllowZeroLength = 0;
      fieldinfo.m_lCollatingOrder = 1049;
      fieldinfo.m_strForeignName = _T("");
      fieldinfo.m_strSourceField = _T("DUTY");
      fieldinfo.m_strSourceTable = _T("CHANGES");
      fieldinfo.m_strValidationRule = _T("");
      fieldinfo.m_strValidationText = _T("");
      fieldinfo.m_strDefaultValue = _T("0");
      td.CreateField(fieldinfo);
    }
    CreateTextField(td, _T("EXTNOTES"),_T("CHANGES"), 0, 40);
    td.Close();

    td.Open( _T("CHANGESDEP") );
    if ( false==IsFieldPresent(td, _T("PERSON")) ) {
      CDaoFieldInfo fieldinfo;
      fieldinfo.m_strName = _T("PERSON");
      fieldinfo.m_nType   = dbMemo;
      fieldinfo.m_lSize   = 0;
      fieldinfo.m_lAttributes = dbVariableField;
      fieldinfo.m_nOrdinalPosition = 30;
      fieldinfo.m_bRequired = 0;
      fieldinfo.m_bAllowZeroLength = 0;
      fieldinfo.m_lCollatingOrder = 1049;
      fieldinfo.m_strForeignName = _T("");
      fieldinfo.m_strSourceField = _T("PERSON");
      fieldinfo.m_strSourceTable = _T("CHANGESDEP");
      fieldinfo.m_strValidationRule = _T("");
      fieldinfo.m_strValidationText = _T("");
      fieldinfo.m_strDefaultValue = _T("");
      td.CreateField(fieldinfo);
    }
    td.Close();

  }
  catch(CDaoException* e){
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    LogDBError(e, _T("ModifyDatabase"));
    e->Delete();
    return;
  }
}

BOOL CDataManager::RepairDatabase(LPCTSTR lpszPathName) {
  try {
    CDaoWorkspace::RepairDatabase(lpszPathName);
    return TRUE;
  }
  catch(CDaoException* e){
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    LogDBError(e, _T("RepairDatabase"));
    e->Delete();
  }
  return FALSE;
}

BOOL CDataManager::OpenDatabase(CDaoDatabase& db, LPCTSTR lpszPathName, BOOL fExclusive, BOOL fReadOnly, LPCTSTR szConnect/*=NULL*/) {
  CString sConnect;
  if ( NULL==szConnect )
    sConnect = _T(";PWD=");
  else
    sConnect = szConnect;
_try_open:
  try {
    db.Open( lpszPathName, // database name
             fExclusive,   // Exclusive
             fReadOnly,    // Read only,
             sConnect      // szConnect
           );
  }
  catch(CDaoException* e) {
    CString s;
    switch(e->m_pErrorInfo->m_lErrorCode) {
      case 3049:  //	Can't open database <name>. It may not be a database that your application recognizes, or the file may be corrupt.
        s.Format(_T("Не вдалося відкрити файл бази даних \"%s\"."), lpszPathName);
        break;
      case 3343:  //  Unrecognized database format <filename>.
        s.Format(_T("Невідомий формат файлу бази даних \"%s\"."), lpszPathName);
        break;
    }
    LogDBError(e, _T("CDataManager::OpenDatabase"));
    if ( !s.IsEmpty() ) {
      e->Delete();
      s += _T(" Можливо, структура файлу зруйнована.");
      if ( YNDlg(NULL, s, _T("Спробувати відновити цей файл?")) ) {
        if ( RepairDatabase(lpszPathName) ) {
          AfxMessageBox(_T("Файл бази даних було успішно відновлено."));
          goto _try_open;
        }
        AfxMessageBox(_T("Вибачте, файл бази не вдалося відновити."));
      }
      return FALSE;
    }
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return FALSE;
  }
  return TRUE;
}

bool CDataManager::OpenYearDB(LPCTSTR szYearDBName/*=NULL*/) {
  if ( NULL==szYearDBName && m_strYearDBName.IsEmpty() )
    return false;
  if ( szYearDBName!=NULL && m_strYearDBName==szYearDBName && m_dbYear.IsOpen() )
    return true;
  else if ( szYearDBName!=NULL )
    m_strYearDBName = szYearDBName;
  try {
    OpenDatabase(m_dbYear,        // database
                 m_strYearDBName, // database name
                 FALSE,           // Exclusive
                 FALSE,           // Read only,
                 _T(";PWD=")      // szConnect
                );

    dm_fNewBirth   = dm_fNewMarrige = dm_fNewDivorce = 
    dm_fNewChange  = dm_fNewDeath   = FALSE;

  }
  catch(CDaoException* e){
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    LogDBError(e, _T("OpenYearDB"));
    e->Delete();
    return false;
  }
  m_Year = GetYearFromDB(m_strYearDBName);
  ModifyDatabase();
  return true;
}
bool CDataManager::OpenHelpersDB() {
  static BYTE bPassword[] = { ~';', ~'P', ~'W', ~'D', ~'=',
                              ~'A', ~'n', ~'t', ~'o', ~'n',
                              ~'V', ~'i', ~'t', ~'a', ~'l', ~'i',~'a', ~0
                            };

  CString szRoot = m_strListsDBName.Left(3);
  g_LocalDB = true;
  if ( szRoot.Left(2)==_T("\\\\") ) {
    g_LocalDB = false;
  }
  else if ( DRIVE_FIXED != GetDriveType(szRoot) ) {
    g_LocalDB = false;
  }
#ifdef _DEBUG
  int driveType = GetDriveType(szRoot);
#endif

  CString szConnect(' ', sizeof(bPassword));
  for( int i(0); i < sizeof(bPassword); i++ ) {
    szConnect.SetAt(i, ~bPassword[i]);
  }
  try {

    OpenDatabase(m_dbLists,       // database
                 m_strListsDBName,// database name
                 FALSE,           // Exclusive
                 FALSE,           // Read only,
                 szConnect        // szConnect
                );
   
    m_fCausesOfDeathTable = IsHelperTablePresent(_T("CausesOfDeath"));
    m_fCitizenshipsTable  = IsHelperTablePresent(_T("Citizenships"));
    m_fGeographyTable     = IsHelperTablePresent(_T("Geography"));
    m_fHospitalsTable     = IsHelperTablePresent(_T("Hospitals"));
    m_fMIATable           = IsHelperTablePresent(_T("MIA"));
    m_fNamesTable         = IsHelperTablePresent(_T("Names"));
    m_fPatronymicsTable   = IsHelperTablePresent(_T("Patronymics"));
    m_fRListTable         = IsHelperTablePresent(_T("RList"));
    m_fStreetTable        = IsHelperTablePresent(_T("Streets"));
  }
  catch(CDaoException* e){
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    LogDBError(e, _T("OpenHelpersDB"));
    e->Delete();
    return false;
  }
  return true;
}

void CDataManager::FillMNames() {
  theMNames.Load(_T("NAMES"), _T("NAME"), TRUE);
}
void CDataManager::FillWNames() {
  theWNames.Load(_T("NAMES"), _T("NAME"), FALSE);
}

void CDataManager::FillMPatronymics() {
  theMPatronymics.Load(_T("PATRONYMICS"), ("PATRONYMIC"), TRUE);
}

void CDataManager::FillWPatronymics() {
  theWPatronymics.Load(_T("PATRONYMICS"), ("PATRONYMIC"), FALSE);
}

void CDataManager::FillCitizenships() {
  theCitizenships.Load();
}
void CDataManager::FillMIAs() {
  theMIAs.Load( _T("SELECT NAME FROM MIA") );
}

void CDataManager::FillHospitals() {
  theHospitals.Load();
}

void CDataManager::FillStreets() {
  theStreets.Load( _T("SELECT STREET FROM STREETS") );
}

#ifdef _GEO
void MakeZips() {
  CDaoRecordset rs(&theDataManager.m_dbLists);
  CGeoRecord* pUkraine = theGeoCache.GetCountry("Україна");
  CGeoRecord* pRegion   = NULL;
  CGeoRecord* pDistrict = NULL;
  try {
    rs.Open(dbOpenDynaset, _T("SELECT ZIP1,ZIP2,ZIP3 FROM Zips"), dbReadOnly);
    while( !rs.IsEOF() ) {
      CGeoRecord* pCity     = NULL;
      BOOL fUpdated = false;
      CString szRegDistrict = GetFieldString(&rs, "ZIP1");
      CString szCity        = GetFieldString(&rs, "ZIP2");
      CString szZip         = GetFieldString(&rs, "ZIP3");

      if ( szZip=="22100-22108" ) {
        int i = 0;
        int j = i++;
      }

      if ( szRegDistrict=="о") {
        pRegion = theGeoCache.GetRegion(&pUkraine->m_array, szCity);
        if ( pRegion && false==szZip.IsEmpty() ) {
          pRegion->m_ZipCode = szZip;
          pRegion->Update();
          fUpdated = true;
        }
      }
      else {
        CString szRegion   = GetTok(szRegDistrict, 0, ",");
        CString szDistrict = GetTok(szRegDistrict, 1, ",");
        if ( NULL==pRegion || pRegion->m_Name != szRegion ) {
          pRegion = theGeoCache.GetRegion(&pUkraine->m_array, szRegion);
        }
        if ( pRegion ) {
          if ( szDistrict.IsEmpty() ) {
            pDistrict = NULL;
          }
          else if ( NULL==pDistrict || pDistrict->m_Name != szDistrict ) {
            pDistrict = theGeoCache.GetDistrict(&pRegion->m_array, szDistrict);
          }
          if ( pDistrict ) {
            char typeLetter = 0;
            if ( szCity.Right(2)==" с" || szCity.Right(2)==" м" ) {
              typeLetter = szCity.Right(1).GetAt(0);
            }
            pCity = theGeoCache.GetCity(&pDistrict->m_array, szCity, typeLetter);
            if ( NULL==pCity ) { pCity = theGeoCache.GetCity(&pRegion->m_array, szCity, typeLetter); }
          }
          else {
            char typeLetter = 0;
            if ( szCity.Right(2)==" с" || szCity.Right(2)==" м" ) {
              typeLetter = szCity.Right(1).GetAt(0);
            }
            pCity = theGeoCache.GetCity(&pRegion->m_array, szCity, typeLetter);
          }
          if ( pCity ) {
            pCity->m_ZipCode = szZip;
            pCity->Update();
            fUpdated = true;
          }
        }
      }
      if ( false==fUpdated ) {
        TRACE3("%s,%s,%s\n",szRegDistrict, szCity, szZip);
      }
      rs.MoveNext();
    }
  }
  catch (CDaoException* e) {
    e->ReportError();
    e->Delete();
	}
}
#endif
void CDataManager::FillCaches() {
  if ( m_fCashFilled )
    return;

  theIniCache.Load();
  theApp.m_RagsID = theIniCache.GetRagsID();

/*
  theUsers.Load();

  if ( theUsers.GetCount() > 1 ) {
    CLoginDlg dlg;
    if ( IDOK != dlg.DoModal() ) {
      AfxMessageBox(_T("Користувача не визначено.\nРедагувати або додавати записи заборонено."), MB_OK);
      theApp.m_fReadOnly = true;
    }
  }
*/

  CLoadDlg dlg;
  dlg.DoModal();

#ifndef FREE_LICENCE
  try {
    InitValidationInfo();
  }
  catch(...) {
    Log(_T("Нераспознанная ошибка"), _T("FillCaches 1"));
  }
#endif

  try {
    FillMNames();
    FillWNames();
    FillMPatronymics();
    FillWPatronymics();
    FillCitizenships();
    FillMIAs();
    theHospitals.Load();
    FillStreets();
  }
  catch(...) {
    Log(_T("Нераспознанная ошибка"), _T("FillCaches 2"));
  }
  #ifdef _GEO
    MakeZips();
  #endif

  m_fCashFilled = TRUE;
}

bool CDataManager::FindAndLoadHelpersDB() {
  if ( m_strListsDBName.IsEmpty() ) {
    m_strListsDBName.Format(_T("%s\\DB\\Helpers.mdb"), GetModulePath());
  }
  if ( false==FileExists(m_strListsDBName) )
    return false;
  if ( OpenHelpersDB() ) {
    FillCaches();

    return true;
  }
  return false;
}