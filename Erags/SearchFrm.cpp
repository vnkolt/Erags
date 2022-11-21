// SearchFrm.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "SearchFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchFrm

IMPLEMENT_DYNCREATE(CSearchFrm, CFrameWnd)

CSearchFrm::CSearchFrm() {
}

CSearchFrm::~CSearchFrm() {
}


BEGIN_MESSAGE_MAP(CSearchFrm, CFrameWnd)
	//{{AFX_MSG_MAP(CSearchFrm)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchFrm message handlers
int CSearchFrm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
  CRect rect;
  AfxGetMainWnd()->GetWindowRect(&rect);
  SetWindowPos(NULL, rect.right-400, rect.top+62, 320, 500, SWP_NOZORDER|SWP_SHOWWINDOW);
	
	return 0;
}

BOOL CSearchFrm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL CSearchFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.hMenu = NULL;
	return CFrameWnd::PreCreateWindow(cs);
}
