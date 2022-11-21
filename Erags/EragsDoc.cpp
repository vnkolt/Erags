// EragsDoc.cpp : implementation of the CEragsDoc class
//

#include "stdafx.h"
#include "Erags.h"

#include "EragsDoc.h"
#include "DataManager.h"
#include "MainFrm.h"
#include "Defaults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CEragsDoc

IMPLEMENT_DYNCREATE(CEragsDoc, CDocument)

BEGIN_MESSAGE_MAP(CEragsDoc, CDocument)
	//{{AFX_MSG_MAP(CEragsDoc)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEragsDoc construction/destruction
CEragsDoc::CEragsDoc() {
}

CEragsDoc::~CEragsDoc() {
}

CFile* CEragsDoc::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags, CFileException* pError) {
  nOpenFlags &= ~CFile::shareDenyWrite;
  return CDocument::GetFile(lpszFileName, nOpenFlags, pError);
}

BOOL CEragsDoc::OnNewDocument() {
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEragsDoc serialization
void CEragsDoc::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		// TODO: add storing code here
	}
	else {
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEragsDoc diagnostics

#ifdef _DEBUG
void CEragsDoc::AssertValid() const {
	CDocument::AssertValid();
}

void CEragsDoc::Dump(CDumpContext& dc) const {
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEragsDoc commands
BOOL CEragsDoc::OnOpenDocument(LPCTSTR lpszPathName) {
/************************************** : by VK at 12.01.2004 23:07:34 **\
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
\************************************** : by VK at 12.01.2004 23:07:36 **/
  theApp.m_pDoc = this;
  CWaitCursor wc;

  if ( !theApp.SetDBFolder(lpszPathName) )
    return FALSE;

  if ( theDataManager.GetYearDBName()==lpszPathName )
    return TRUE;

	// TODO: Add your specialized creation code here
  if ( theDataManager.SetYearDBName(lpszPathName)==false )
    return FALSE;

  if ( theDataManager.OpenDatabases(lpszPathName)==false )
    return FALSE;


  theDataManager.LoadTextData();
  SetTitle(lpszPathName);

//  ((CMainFrame*)AfxGetMainWnd())->EnablePreviewBar(false);

	return TRUE;
}

void CEragsDoc::OnFileClose() {
}
void CEragsDoc::OnFileSave() {
}
void CEragsDoc::OnFileSaveAs() {
}
