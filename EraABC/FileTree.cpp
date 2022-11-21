// FileTree.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "FileTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileTree

IMPLEMENT_DYNCREATE(CFileTree, CTreeView)

CFileTree::CFileTree() {
}

CFileTree::~CFileTree() {
}


BEGIN_MESSAGE_MAP(CFileTree, CTreeView)
	//{{AFX_MSG_MAP(CFileTree)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTree drawing
void CFileTree::OnDraw(CDC* pDC) {
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CFileTree diagnostics
#ifdef _DEBUG
void CFileTree::AssertValid() const {
	CTreeView::AssertValid();
}

void CFileTree::Dump(CDumpContext& dc) const {
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileTree message handlers
int CFileTree::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
  //CTreeCtrl& tree = GetTreeCtrl();
  //tree.InsertItem(
	
	return 0;
}
