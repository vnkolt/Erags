// SearchDoc.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "SearchDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchDoc

IMPLEMENT_DYNCREATE(CSearchDoc, CDocument)
CSearchDoc::CSearchDoc() {
}

BOOL CSearchDoc::OnNewDocument() {
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CSearchDoc::~CSearchDoc() {
}


BEGIN_MESSAGE_MAP(CSearchDoc, CDocument)
	//{{AFX_MSG_MAP(CSearchDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchDoc diagnostics

#ifdef _DEBUG
void CSearchDoc::AssertValid() const {
	CDocument::AssertValid();
}

void CSearchDoc::Dump(CDumpContext& dc) const {
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSearchDoc serialization
void CSearchDoc::Serialize(CArchive& ar) {
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSearchDoc commands

BOOL CSearchDoc::OnOpenDocument(LPCTSTR lpszPathName) {
/************************************** : by VK at 20.11.2004 2:15:27 **\
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
\************************************** : by VK at 20.11.2004 2:15:31 **/
	// TODO: Add your specialized creation code here
	return TRUE;
}

void CSearchDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) {
	// TODO: Add your specialized code here and/or call the base class

  LPCSTR szCurForm = NULL;
  switch(theApp.m_nCurrentForm) {
    case ID_BIRTH:      szCurForm = _T("Пошук: Народження");         break;
    case ID_MARRIAGE:   szCurForm = _T("Пошук: Шлюби");              break;
    case ID_DIVORCE:    szCurForm = _T("Пошук: Розірвання шлюбів");  break;
    case ID_CHANGE:     szCurForm = _T("Пошук: Зміни");              break;
    case ID_DEATH:      szCurForm = _T("Пошук: Смерті");             break;
  }
	CDocument::SetPathName(szCurForm, FALSE);
}
