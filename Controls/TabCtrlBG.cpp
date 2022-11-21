// TabCtrlBG.cpp : implementation file
//
#include "stdafx.h"
#include "TabCtrlBG.h"
#include "BtnST.h"
#include "NewMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern COLORREF g_clrLeft;
extern COLORREF g_clrRight;
/////////////////////////////////////////////////////////////////////////////
// CTabCtrlBG
CTabCtrlBG::CTabCtrlBG() {
  m_bBackColor = m_bFlat = m_fGradientFill = TRUE;
  ResetStyles(ETC_FLAT|ETC_COLOR|ETC_SELECTION|ETC_GRADIENT|ETC_BACKTABS, m_bFlat, g_clrLeft);
}

CTabCtrlBG::~CTabCtrlBG() {
}

BEGIN_MESSAGE_MAP(CTabCtrlBG, CTabCtrlBGBase)
	//{{AFX_MSG_MAP(CTabCtrlBG)
	ON_WM_ERASEBKGND()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CTabCtrlBG::ResetStyles(DWORD dwFlags, BOOL bFlat, COLORREF clrBk) {
  m_dwFlags = dwFlags;
  m_bFlat = bFlat;
  SetBkgndColor(clrBk);
  EnableDraw(BTC_ALL);
  SetBkgndColor(clrBk);
  EnableDraw(m_bFlat ? BTC_ALL : m_dwFlags ? BTC_TABS : BTC_NONE); 
  CEnTabCtrl::EnableCustomLook(m_dwFlags | m_bBackColor, m_dwFlags);
  if ( GetSafeHwnd() )
    Invalidate();
}
/////////////////////////////////////////////////////////////////////////////
// CTabCtrlBG message handlers
BOOL CTabCtrlBG::OnEraseBkgnd(CDC* pDC) {
	// TODO: Add your message handler code here and/or call default
  CRect clipRect;
  pDC->GetClipBox(&clipRect);
  EraseBkgndForDlgControl(this, pDC, clipRect);
	return TRUE;
}
void CTabCtrlBG::OnSysColorChange() {
	CTabCtrlBGBase::OnSysColorChange();
	// TODO: Add your message handler code here
  ResetStyles(m_dwFlags, m_bFlat, g_clrLeft);
}

/////////////////////////////////////////////////////////////////////////////
