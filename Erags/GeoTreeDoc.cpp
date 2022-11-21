// GeoTreeDoc.cpp : implementation of the CGeoTreeDoc class
//

#include "stdafx.h"
#include "Erags.h"

#include "GeoTreeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeDoc

IMPLEMENT_DYNCREATE(CGeoTreeDoc, CDocument)

BEGIN_MESSAGE_MAP(CGeoTreeDoc, CDocument)
	//{{AFX_MSG_MAP(CGeoTreeDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeDoc construction/destruction

CGeoTreeDoc::CGeoTreeDoc()
{
}

CGeoTreeDoc::~CGeoTreeDoc()
{
}

BOOL CGeoTreeDoc::OnNewDocument()
{
	UpdateAllViews(NULL, HINT_NEW);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeDoc diagnostics

#ifdef _DEBUG
void CGeoTreeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGeoTreeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeDoc commands

// Checks if the modified flag is on. If so, it displays a warning message
// (The file was changed. Do you want to save or to discard the modifications?)
BOOL CGeoTreeDoc::SaveModified() {
	return TRUE;    // keep going
}

BOOL CGeoTreeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
/************************************** : by VK at 19.12.2004 6:05:56 **\
	if (SaveModified())
	{
		m_strFileName = lpszPathName;
		OpenFile();
	}
\************************************** : by VK at 19.12.2004 6:05:59 **/
	return TRUE;
}


