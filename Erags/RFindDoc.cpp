// RFindDoc.cpp : implementation of the CRFindDoc class
//

#include "stdafx.h"
#include "Erags.h"

#include "RFindDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CRFindDoc

IMPLEMENT_DYNCREATE(CRFindDoc, CDocument)

BEGIN_MESSAGE_MAP(CRFindDoc, CDocument)
	//{{AFX_MSG_MAP(CRFindDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRFindDoc construction/destruction

CRFindDoc::CRFindDoc() {
	// TODO: add one-time construction code here

}

CRFindDoc::~CRFindDoc() {
}

BOOL CRFindDoc::OnNewDocument() {
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


void CRFindDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU/* = TRUE*/) {
  CDocument::SetPathName(lpszPathName, FALSE);
/************************************** : by VK at 08.07.2004 20:28:41 **\
	// store the path fully qualified
	TCHAR szFullPath[_MAX_PATH];
	AfxFullPath(szFullPath, lpszPathName);
	m_strPathName = szFullPath;
	ASSERT(!m_strPathName.IsEmpty());       // must be set to something
	m_bEmbedded = FALSE;
	ASSERT_VALID(this);

	// set the document title based on path name
	TCHAR szTitle[_MAX_FNAME];
	if (AfxGetFileTitle(szFullPath, szTitle, _MAX_FNAME) == 0)
		SetTitle(szTitle);

	ASSERT_VALID(this);
\************************************** : by VK at 08.07.2004 20:28:45 **/
}

/////////////////////////////////////////////////////////////////////////////
// CRFindDoc serialization
void CRFindDoc::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		// TODO: add storing code here
	}
	else {
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRFindDoc diagnostics

#ifdef _DEBUG
void CRFindDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRFindDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRFindDoc commands

BOOL CRFindDoc::OnOpenDocument(LPCTSTR lpszPathName) {
/************************************** : by VK at 03.07.2004 2:45:01 **\
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
\************************************** : by VK at 03.07.2004 2:45:04 **/
	// TODO: Add your specialized creation code here
  SetPathName(lpszPathName, FALSE);
  //SetTitle(lpszPathName);
	return TRUE;
}
