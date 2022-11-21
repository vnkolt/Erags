// DBGridDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DBGridView.h"

/////////////////////////////////////////////////////////////////////////////
// CDBGridView dialog


CDBGridView::CDBGridView:CDBGridViewBase(CDBGridView::IDD) {
	//{{AFX_DATA_INIT(CDBGridView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
CDBGridView::~CDBGridView() {
}

void CDBGridView::DoDataExchange(CDataExchange* pDX) {
	CDBGridViewBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBGridView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
  DDX_GridControl(pDX, IDC_GRID, m_Grid);
}

BEGIN_MESSAGE_MAP(CDBGridView, CDBGridViewBase)
	//{{AFX_MSG_MAP(CDBGridView)
	ON_UPDATE_COMMAND_UI(ID_RECORD_EDIT, OnUpdateRecordEdit)
	ON_COMMAND(ID_RECORD_EDIT, OnRecordEdit)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEW, OnUpdateRecordNew)
	ON_COMMAND(ID_RECORD_NEW, OnRecordNew)
	ON_UPDATE_COMMAND_UI(ID_RECORD_DELETE, OnUpdateRecordDelete)
	ON_COMMAND(ID_RECORD_DELETE, OnRecordDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDBGridView::Create(UINT uID) {
  BOOL bRet = CDBGridViewBase::Create(NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), AfxGetMainWnd(), uID, NULL);
  if ( bRet )
    ShowWindow(SW_MAXIMIZE);
  return bRet;
}

/////////////////////////////////////////////////////////////////////////////
// CDBGridView message handlers
void CDBGridView::OnInitialUpdate() {
  CDBGridViewBase::OnInitialUpdate();
}

void CDBGridView::OnSize(UINT nType, int cx, int cy)  {
	CDBGridViewBase::OnSize(nType, cx, cy);
}
BOOL CDBGridView::OnEraseBkgnd(CDC* pDC) {
	// TODO: Add your message handler code here and/or call default
	CRect r, rList;
  pDC->GetClipBox(&r);
  m_SearchList.GetWindowRect(&rList);
  ScreenToClient(&rList);
  r.bottom = rList.top;
  GradientEraseBkgnd(this, GetParent(), pDC, r);
	return TRUE;
}
