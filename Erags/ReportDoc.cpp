// ReportDoc.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "ReportDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportDoc

IMPLEMENT_DYNCREATE(CReportDoc, CDocument)

CReportDoc::CReportDoc()
{
}

BOOL CReportDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CReportDoc::~CReportDoc()
{
}


BEGIN_MESSAGE_MAP(CReportDoc, CDocument)
	//{{AFX_MSG_MAP(CReportDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDoc diagnostics

#ifdef _DEBUG
void CReportDoc::AssertValid() const {
	CDocument::AssertValid();
}

void CReportDoc::Dump(CDumpContext& dc) const {
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportDoc serialization

void CReportDoc::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		// TODO: add storing code here
	}
	else {
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CReportDoc commands

BOOL CReportDoc::OnOpenDocument(LPCTSTR lpszPathName) {
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}

void CReportDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) {
	CDocument::SetPathName(lpszPathName, FALSE);
}

void CReportDoc::OnCloseDocument() {
	// TODO: Add your specialized code here and/or call the base class
  CString sFileName = m_strPathName;
	CDocument::OnCloseDocument();
  DeleteFileIfExist(sFileName);
}
