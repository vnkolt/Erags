// DBListView.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "DBListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBListView

IMPLEMENT_DYNCREATE(CDBListView, CListView)

CDBListView::CDBListView()
{
}

CDBListView::~CDBListView()
{
}


BEGIN_MESSAGE_MAP(CDBListView, CListView)
	//{{AFX_MSG_MAP(CDBListView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBListView drawing

void CDBListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDBListView diagnostics

#ifdef _DEBUG
void CDBListView::AssertValid() const
{
	CListView::AssertValid();
}

void CDBListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBListView message handlers

void CDBListView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
}
