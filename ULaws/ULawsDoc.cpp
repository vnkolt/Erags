// This is part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
//
// ULawsDoc.cpp : implementation of the CULawsDoc class
//

#include "stdafx.h"
#include "ULaws.h"

#include "ULawsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CULawsDoc

IMPLEMENT_DYNCREATE(CULawsDoc, CDocument)

BEGIN_MESSAGE_MAP(CULawsDoc, CDocument)
	//{{AFX_MSG_MAP(CULawsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CULawsDoc construction/destruction

CULawsDoc::CULawsDoc()
{
}

CULawsDoc::~CULawsDoc()
{
}

BOOL CULawsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CULawsDoc serialization

void CULawsDoc::Serialize(CArchive& ar)
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
// CULawsDoc diagnostics

#ifdef _DEBUG
void CULawsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CULawsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CULawsDoc commands
