// ReportFrm.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "ReportFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CReportFrame

IMPLEMENT_DYNCREATE(CReportFrame, CMDIChildWnd)

CReportFrame::CReportFrame() {
  m_pPrevFrame = NULL;
}

CReportFrame::~CReportFrame() {
}

BEGIN_MESSAGE_MAP(CReportFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CReportFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportFrame message handlers
int CReportFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  m_pPrevFrame = ((CMainFrame*)AfxGetMainWnd())->MDIGetActive();
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}
