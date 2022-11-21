// OODoc.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "OODoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COODoc

IMPLEMENT_DYNCREATE(COODoc, CDocument)

COODoc::COODoc()
{
}

BOOL COODoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

COODoc::~COODoc()
{
}


BEGIN_MESSAGE_MAP(COODoc, CDocument)
	//{{AFX_MSG_MAP(COODoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COODoc diagnostics

#ifdef _DEBUG
void COODoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COODoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COODoc serialization

void COODoc::Serialize(CArchive& ar)
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
// COODoc commands
