// GeoTreeView.cpp : implementation of the CGeoTreeView class
//

#include "stdafx.h"
#include "Erags.h"

#include "GeoTreeDoc.h"
#include "GeoTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeView

IMPLEMENT_DYNCREATE(CGeoTreeView, CView)

BEGIN_MESSAGE_MAP(CGeoTreeView, CView)
	//{{AFX_MSG_MAP(CGeoTreeView)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeView construction/destruction

CGeoTreeView::CGeoTreeView()
{
	// TODO: add construction code here

}

CGeoTreeView::~CGeoTreeView()
{
}

BOOL CGeoTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeView drawing

void CGeoTreeView::OnDraw(CDC* pDC)
{
	CGeoTreeDoc* pDoc = (CGeoTreeDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeView diagnostics

#ifdef _DEBUG
void CGeoTreeView::AssertValid() const
{
	CView::AssertValid();
}

void CGeoTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGeoTreeDoc* CGeoTreeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeoTreeDoc)));
	return (CGeoTreeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeView message handlers

void CGeoTreeView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	m_etc.SetLimitText(100);
	m_etc.InitializeImageList();
}

void CGeoTreeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (m_etc.m_pted == NULL)
		m_etc.m_pted = (CGeoTreeDoc*)GetDocument();

	switch(lHint)
	{
	case HINT_NEW:
		m_etc.DeleteAllItems();	
		break;
	case HINT_LOAD_DIRECTORY:
		m_etc.DeleteAllItems();	
		m_etc.OnLoadEntireTree(FF_DIRECTORY_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_LOAD_TREE_TYPE:
		m_etc.DeleteAllItems();	
		m_etc.OnLoadEntireTree(FF_TREE_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_LOAD_IDENT_TYPE:
		m_etc.DeleteAllItems();	
		m_etc.OnLoadEntireTree(FF_INDENT_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_LOAD_CSV_TYPE:
		m_etc.DeleteAllItems();	
		m_etc.OnLoadEntireTree(FF_CSV_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_SAVE_TREE_TYPE:
		m_etc.OnSaveEntireTree(FF_TREE_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_SAVE_IDENT_TYPE:
		m_etc.OnSaveEntireTree(FF_INDENT_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_SAVE_CSV_TYPE:
		m_etc.OnSaveEntireTree(FF_CSV_TYPE, m_etc.m_pted->m_tt);
		break;
	}
}

int CGeoTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//Create the tree view
	CRect r;
	DWORD newstyle = TVS_SHOWSELALWAYS | TVS_EDITLABELS | TVS_HASBUTTONS | 
		TVS_LINESATROOT | TVS_HASLINES;
	if (!m_etc.Create(WS_VISIBLE | WS_CHILD | newstyle, r, this, 100))
		return -1;	      
	return 0;
}

void CGeoTreeView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	m_etc.SetFocus();
}

void CGeoTreeView::OnSize(UINT nType, int cx, int cy) 
{
	//Let the tree control occupy all the space of the client area
	CRect r;  
	GetClientRect(&r);
	m_etc.MoveWindow(r);
}
