// EragsView.cpp : implementation of the CEragsView class
//

#include "stdafx.h"
#include "Erags.h"

#include "EragsDoc.h"
#include "EragsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEragsView

IMPLEMENT_DYNCREATE(CEragsView, CView)

BEGIN_MESSAGE_MAP(CEragsView, CView)
	//{{AFX_MSG_MAP(CEragsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEragsView construction/destruction

CEragsView::CEragsView()
{
	// TODO: add construction code here

}

CEragsView::~CEragsView()
{
}

BOOL CEragsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEragsView drawing

void CEragsView::OnDraw(CDC* pDC)
{
	CEragsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEragsView printing

BOOL CEragsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEragsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEragsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEragsView diagnostics

#ifdef _DEBUG
void CEragsView::AssertValid() const
{
	CView::AssertValid();
}

void CEragsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEragsDoc* CEragsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEragsDoc)));
	return (CEragsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEragsView message handlers
