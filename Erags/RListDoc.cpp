// RListDoc.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "RListDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRListDoc

IMPLEMENT_DYNCREATE(CRListDoc, CDocument)

CRListDoc::CRListDoc()
{
}

BOOL CRListDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CRListDoc::~CRListDoc()
{
}


BEGIN_MESSAGE_MAP(CRListDoc, CDocument)
	//{{AFX_MSG_MAP(CRListDoc)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRListDoc diagnostics

#ifdef _DEBUG
void CRListDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRListDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRListDoc serialization

void CRListDoc::Serialize(CArchive& ar)
{
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
// CRListDoc commands
void CRListDoc::OnFileClose() {
}
void CRListDoc::OnFileSave() {
}
void CRListDoc::OnFileSaveAs() {
}
