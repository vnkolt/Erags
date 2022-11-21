// EraABCView.cpp : implementation of the CEraABCView class
//

#include "stdafx.h"
#include "EraABC.h"

#include "EraABCDoc.h"
#include "EraABCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEraABCView

IMPLEMENT_DYNCREATE(CEraABCView, CSplitterWnd)

BEGIN_MESSAGE_MAP(CEraABCView, CSplitterWnd)
	//{{AFX_MSG_MAP(CEraABCView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraABCView construction/destruction
CEraABCView::CEraABCView() {
	// TODO: add construction code here
}

CEraABCView::~CEraABCView() {
}

BOOL CEraABCView::PreCreateWindow(CREATESTRUCT& cs) {
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CSplitterWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEraABCView diagnostics

#ifdef _DEBUG
void CEraABCView::AssertValid() const {
	CSplitterWnd::AssertValid();
}

void CEraABCView::Dump(CDumpContext& dc) const {
	CSplitterWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEraABCView message handlers
int CEraABCView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CSplitterWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
	
  // TODO: Add your specialized creation code here
  return 0;
}
CFormABC* CEraABCView::GetForm() {
  if ( GetDlgItem(IdFromRowCol(0, 0)) )
    return (CFormABC*)GetPane(0, 0);
  return NULL;
}
CABCList* CEraABCView::GetListCtrl() {
  return (CABCList*)GetDlgItem(IdFromRowCol(1, 0));
//  return (CABCList*)GetPane(1, 0);
}
