// EraDownBtn.cpp : implementation file
//
#include "stdafx.h"
#include "EraDownBtn.h"
#include "VisualStylesXP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEraDownBtn

CEraDownBtn::CEraDownBtn() {
  m_dwBtnStyle = DFCS_SCROLLDOWN;
  m_fDropDown = false;
  m_fOffByBtn = false;
  m_fCalendarOn = false;
}

CEraDownBtn::~CEraDownBtn() {
}


BEGIN_MESSAGE_MAP(CEraDownBtn, CButton)
	//{{AFX_MSG_MAP(CEraDownBtn)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraDownBtn message handlers
void CEraDownBtn::OnPaint() {
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
  CRect rc;
	GetClientRect(&rc);

  HTHEME hTheme = NULL;
  BOOL bThemeActive = g_xpStyle.UseVisualStyles();
  if ( bThemeActive )
    hTheme = g_xpStyle.OpenThemeData( m_hWnd, L"COMBOBOX" );

  if ( hTheme ) {
    int nDropBtnThemeStyle = CBXS_NORMAL;
    if ( m_dwBtnStyle & DFCS_FLAT )
      nDropBtnThemeStyle = CBXS_HOT;
    if ( m_dwBtnStyle & DFCS_PUSHED )
      nDropBtnThemeStyle = CBXS_PRESSED;
		  g_xpStyle.DrawThemeBackground( hTheme, dc.m_hDC, CP_DROPDOWNBUTTON, nDropBtnThemeStyle, &rc, NULL);
  }
  else {
    dc.DrawFrameControl(rc, DFC_SCROLL, m_dwBtnStyle);
  }
	// Do not call CButton::OnPaint() for painting messages
}

void CEraDownBtn::OnLButtonDown(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
  CRect rc;
  GetClientRect(&rc);
  DWORD dwOldBtnStyle = m_dwBtnStyle;
  if ( rc.PtInRect(point) ) {
    //SetCursor( ::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)) );
    m_dwBtnStyle = DFCS_SCROLLDOWN|DFCS_PUSHED|DFCS_FLAT;
    m_fDropDown = true;
//    SetFocus();
    if ( GetCapture() != this )
      SetCapture();	
  }
  if ( dwOldBtnStyle != m_dwBtnStyle )
    InvalidateRect(NULL);
	CButton::OnLButtonDown(nFlags, point);
}

void CEraDownBtn::OnLButtonUp(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	// TODO: Add your message handler code here and/or call default
  if ( GetCapture() == this )
    ReleaseCapture();	
  DWORD dwOldBtnStyle = m_dwBtnStyle;
	m_dwBtnStyle = DFCS_SCROLLDOWN;
  bool fShowCalendar = false;
  if ( m_fOffByBtn ) {
    m_fOffByBtn = false;
//    HideCalendar();
    if ( dwOldBtnStyle != m_dwBtnStyle )
      InvalidateRect(NULL);
    m_fDropDown = false;
    m_fCalendarOn = false;
    return;
  }

  CRect rc;
  GetClientRect(&rc);
  if ( m_fDropDown && rc.PtInRect(point) ) {
    //m_fCalendarOn = false;
    fShowCalendar = true;
  }
  m_fDropDown = false;
  if ( dwOldBtnStyle != m_dwBtnStyle )
    InvalidateRect(NULL);
  if ( fShowCalendar )
    OnClicked();
	CButton::OnLButtonUp(nFlags, point);
}

void CEraDownBtn::OnMouseMove(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
  CRect rc;
  GetClientRect(&rc);
  if ( rc.PtInRect(point) ) {
    TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(tme);
    tme.dwFlags = TME_LEAVE;
    tme.hwndTrack = m_hWnd;
    _TrackMouseEvent(&tme);
  }
  DWORD dwOldBtnStyle = m_dwBtnStyle;
  if ( rc.PtInRect(point) ) {
    SetCursor( ::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)) );
    if ( m_fDropDown && (MK_LBUTTON & nFlags) )
      m_dwBtnStyle = DFCS_SCROLLDOWN|DFCS_PUSHED|DFCS_FLAT;
    else
      m_dwBtnStyle = DFCS_SCROLLDOWN;
    m_dwBtnStyle |= DFCS_FLAT;
  }
  else {
      m_dwBtnStyle = DFCS_SCROLLDOWN;
  }
  if ( dwOldBtnStyle != m_dwBtnStyle )
    InvalidateRect(NULL);
	CButton::OnMouseMove(nFlags, point);
}
LRESULT CEraDownBtn::OnMouseLeave(WPARAM wParam, LPARAM lParam) {
  CPoint point;
  GetCursorPos(&point);
  ScreenToClient(&point);
  OnMouseMove(0, point);
  return 0L;
}
void CEraDownBtn::OnClicked() {
	// TODO: Add your control notification handler code here
  NMHDR nmhdr;
  nmhdr.hwndFrom = m_hWnd;
  nmhdr.idFrom = GetDlgCtrlID();
  nmhdr.code   = NM_CLICK;
  GetParent()->SendMessage(WM_NOTIFY, (WPARAM)nmhdr.idFrom, (LPARAM)&nmhdr);
}
