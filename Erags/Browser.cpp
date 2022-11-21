// Browser.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "Browser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowser

IMPLEMENT_DYNCREATE(CBrowser, CHtmlView)

CBrowser::CBrowser() {
	//{{AFX_DATA_INIT(CBrowser)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CBrowser::~CBrowser() {
}

void CBrowser::DoDataExchange(CDataExchange* pDX) {
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBrowser)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBrowser, CHtmlView)
	//{{AFX_MSG_MAP(CBrowser)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowser diagnostics

#ifdef _DEBUG
void CBrowser::AssertValid() const {
	CHtmlView::AssertValid();
}

void CBrowser::Dump(CDumpContext& dc) const {
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBrowser message handlers
