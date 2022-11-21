// EraABCDoc.cpp : implementation of the CEraABCDoc class
//

#include "stdafx.h"
#include "EraABC.h"

#include "EraABCDoc.h"

#include "IniCache.h"
#include "YesNoDlg.h"

#include "..\Common\DB.h"
#include "..\Common\EraMessages.h"
#include "..\Common\FHelpers.h"
#include "..\Common\CyrString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNameCache theNames;
CNameCache thePatronymics;

/////////////////////////////////////////////////////////////////////////////
// CNameCache
CNameCache::CNameCache() {
  m_fLoaded = FALSE;
}
CNameCache::~CNameCache() {
  m_mapM.RemoveAll();
  m_mapW.RemoveAll();
}

bool CNameCache::Load(CDaoDatabase* pDB, LPCTSTR szTableName, LPCTSTR szFieldName) {
  m_mapM.RemoveAll();
  m_mapW.RemoveAll();

  CString sql;
  sql.Format(_T("SELECT %s, SEX FROM %s ORDER BY %s"), szFieldName, szTableName, szFieldName);

  CDaoQueryDef qd(pDB);
  CDaoRecordset rs(pDB);
  try {
    qd.Create(NULL,sql);
    rs.Open(&qd);
    while ( !rs.IsEOF() ) {
      CString s  = iDBStringField(rs, 0);
      bool fMale = iDBBoolField(rs, 1);
      CCyrString sCanonical(s), sLower(s);
      sCanonical.MakeCanonical();
      sLower.MakeLower();
      if ( fMale )
        m_mapM.SetAt(sLower, sCanonical);
      else
        m_mapW.SetAt(sLower, sCanonical);
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
  m_fLoaded = TRUE;
  return true;
}

void CNameCache::FillCombo(CComboBox& cb, const CString& sFieldValue, BOOL fMale, BOOL reFill) {
  if ( reFill )
    cb.ResetContent();
  CMapStringToString* pMap = fMale ? &m_mapM : &m_mapW;
  if ( 0==cb.GetCount() ) {
    POSITION pos = pMap->GetStartPosition();
    while( pos ) {
      CCyrString sKey, sValue;
      pMap->GetNextAssoc(pos, sKey, sValue);
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
// CEraABCDoc

IMPLEMENT_DYNCREATE(CEraABCDoc, CDocument)

BEGIN_MESSAGE_MAP(CEraABCDoc, CDocument)
	//{{AFX_MSG_MAP(CEraABCDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraABCDoc construction/destruction

CEraABCDoc::CEraABCDoc() {
}

CEraABCDoc::~CEraABCDoc() {
  theApp.m_pDoc = NULL;
}

BOOL CEraABCDoc::OnNewDocument() {
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEraABCDoc serialization
void CEraABCDoc::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
	}
	else {
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEraABCDoc diagnostics
#ifdef _DEBUG
void CEraABCDoc::AssertValid() const {
	CDocument::AssertValid();
}
void CEraABCDoc::Dump(CDumpContext& dc) const {
	CDocument::Dump(dc);
}
#endif //_DEBUG

CString CEraABCDoc::GetHelperPath(LPCTSTR lpszPathName) {
  CString s = lpszPathName;
  int nSlash = s.ReverseFind('\\');
  while (nSlash != -1 ) {
    s = s.Left(nSlash);
    CString sHelperMDB;
    sHelperMDB.Format(_T("%s\\Helpers.mdb"), s);
    if ( FileExists(sHelperMDB) ) {
      return sHelperMDB;
    }
    nSlash = s.ReverseFind('\\');
  }
  s.Empty();
  return s;
}

void CEraABCDoc::FillCaches(LPCTSTR lpszPathName) {
  if ( theNames.m_fLoaded && thePatronymics.m_fLoaded )
    return;
  CString sHelperPath = GetHelperPath(lpszPathName);
  if ( FALSE==sHelperPath.IsEmpty() ) {
    CDaoDatabase db;
    static BYTE bPassword[] = { ~';', ~'P', ~'W', ~'D', ~'=',
                                ~'A', ~'n', ~'t', ~'o', ~'n',
                                ~'V', ~'i', ~'t', ~'a', ~'l', ~'i',~'a', ~0
                              };

    CString szConnect(' ', sizeof(bPassword));
    for( int i(0); i < sizeof(bPassword); i++ ) {
      szConnect.SetAt(i, ~bPassword[i]);
    }

    if ( OpenDatabase(db, sHelperPath, FALSE, TRUE, szConnect) ) {
      CIniCache ic;
      try {
        theNames.Load(&db, _T("NAMES"), _T("NAME") );
        thePatronymics.Load(&db, _T("PATRONYMICS"), _T("PATRONYMIC") );
        if ( ic.Load(db) ) {
          theApp.m_szRagsName = ic.GetRAGS();
        }
        db.Close();
      }
      catch(CDaoException* e){
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

BOOL CEraABCDoc::RepairDatabase(LPCTSTR lpszPathName) {
  try {
    CDaoWorkspace::RepairDatabase(lpszPathName);
/************************************** : by VK at 11.02.2005 23:36:59 **\
    CString sDestFileName;
    sDestFileName.Format(_T("%s.mdb"), lpszPathName, 
    CDaoWorkspace::CompactDatabase(lpszPathName, sDestFileName, dbLangCyrillic);
\************************************** : by VK at 11.02.2005 23:37:02 **/
    return TRUE;
  }
  catch(CDaoException* e){
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
  }
  return FALSE;
}
BOOL CEraABCDoc::OpenDatabase(CDaoDatabase& db, LPCTSTR lpszPathName, BOOL fExclusive, BOOL fReadOnly, LPCTSTR szConnect/*=NULL*/) {
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
    if ( !s.IsEmpty() ) {
      e->Delete();
      s += _T(" Можливо, структура файлу зруйнована.");
      if ( YNDlg(NULL, s, _T("Спробувати відновити цей файл?")) ) {
        if ( RepairDatabase(lpszPathName) ) {
          AfxMessageBox(_T("Файл бази данних було успішно відновлено."));
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
/////////////////////////////////////////////////////////////////////////////
// CEraABCDoc commands
BOOL CEraABCDoc::OnOpenDocument(LPCTSTR lpszPathName) {
/************************************** : by VK at 13.10.2004 0:18:47 **\
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
\************************************** : by VK at 13.10.2004 0:18:49 **/


	// TODO: Add your specialized creation code here
  if ( theApp.m_dbYear.IsOpen() ) {
    if ( theApp.m_dbYear.GetName()==lpszPathName )
      return TRUE;
    theApp.m_dbYear.Close();
  }

  if ( FALSE==OpenDatabase(theApp.m_dbYear, lpszPathName, FALSE, FALSE, NULL) )
    return FALSE;

/*
  theApp.OnMessage(EM_INFO, "Відкрита БД \"%s\".", lpszPathName);
*/


  FillCaches(lpszPathName);

  theApp.m_strYearDBName = lpszPathName;
  theApp.m_pDoc = this;
  theApp.WriteProfileString(_T("Settings"), _T("Database"), theApp.m_strYearDBName);

	return TRUE;
}

void CEraABCDoc::OnCloseDocument() {
	// TODO: Add your specialized code here and/or call the base class
	theApp.m_pDoc = NULL;
	CDocument::OnCloseDocument();
}
