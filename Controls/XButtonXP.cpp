// XButtonXP.cpp  Version 1.2
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// Description:
//     XButtonXP implements CXButtonXP, an ownerdraw button that is XP
//     theme-aware and may be used as a pushbutton or a toggle button.
//     An icon and/or text may be displayed on the button.  Please see
//     my article at www.codeproject.com.
//
//     This code is based partially on Ewan Ward's article
//     "Native Win32 Theme aware Owner-draw Controls without MFC"
//     http://www.codeproject.com/buttonctrl/nativewin32xpthemes.asp
//
// History
//     Version 1.2 - 2005 April 20
//     - Fixed bug with hot state, reported by ksk
//     - Added SetDrawToolbar() and GetDrawToolbar(), suggested by Dominik Reichl
//
//     Version 1.1 - 2005 March 30
//     - Fixed bug in drawing toggle button, reported by Dominik Reichl
//     - Added SetToggleState()
//     - Removed #include "XButtonXPTest.h"
//
//     Version 1.0 - 2005 March 22
//     - Initial public release
//
// Public APIs:
//          NAME                              DESCRIPTION
//     ------------------   -------------------------------------------------
//     GetToggle()          Returns TRUE if button is a toggle button
//     SetToggle()          Sets button to toggle state (TRUE) or to
//                          pushbutton state (FALSE)
//     GetToggleState()     Returns TRUE if button is toggled (down)
//     SetToggleState()     Set toggle state to pushed (TRUE) or
//                          unpushed (FALSE)
//     GetDrawToolbar()     Returns TRUE if button is drawn with tolobar theme
//     SetDrawToolbar()     Draw button with toolbar theme (TRUE) or button
//                          theme (FALSE)
//     EnableTheming()      Enables theming (TRUE)
//     IsThemed()           Returns TRUE if button is themed;  this is more
//                          than just EnableTheming() setting - see code
//     SetIcon()            Set icon for display on button
//     SetIconAlignment()   Set icon alignment
//
// License:
//     This software is released into the public domain.  You are free to use
//     it in any way you like, except that you may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XButtonXP.h"
#include "MemDC.h"

#include "NewMenu.h"

extern COLORREF g_clrBackColor;
extern COLORREF g_clrForeColor;
extern COLORREF g_clrFocusBackColor;
extern COLORREF g_clrFocusForeColor;

extern COLORREF g_clrMaleBackColor;
extern COLORREF g_clrFemaleBackColor;
extern COLORREF g_clrMaleForeColor;
extern COLORREF g_clrFemaleForeColor;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void AFXAPI DDX_MSButton(CDataExchange* pDX, int nIDC, CEraMultiStateButton& rControl, BYTE& byte) {
  DDX_Control(pDX, nIDC, (CWnd&)rControl);
  if (!pDX->m_bSaveAndValidate)
    rControl.SetIndex( (int)byte );
  else
    byte = (BYTE)rControl.GetIndex();

  if ( rControl.GetSafeHwnd() )
    rControl.InvalidateRect(NULL);
}

void AFXAPI DDX_MSButton(CDataExchange* pDX, int nIDC, CEraMultiStateButton& rControl, BOOL& bFlag) {
  DDX_Control(pDX, nIDC, (CWnd&)rControl);
  if (!pDX->m_bSaveAndValidate)
    rControl.SetIndex( (int)bFlag );
  else
    bFlag = (BOOL)rControl.GetIndex();

  if ( rControl.GetSafeHwnd() )
    rControl.InvalidateRect(NULL);
}

///////////////////////////////////////////////////////////////////////////////
// various defines that are needed
#ifndef ODS_NOFOCUSRECT
#define ODS_NOFOCUSRECT     0x0200		// from WinUser.h
#endif

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)    ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)    ((int)(short)HIWORD(lp))
#endif

#ifndef WM_THEMECHANGED
#define WM_THEMECHANGED     0x031A
#endif


/////////////////////////////////////////////////////////////////////////////
// CFrameBG
IMPLEMENT_DYNCREATE(CFrameBG, CStatic)
CFrameBG::CFrameBG() {
  m_bFirstTime = TRUE;
	m_hTheme     = NULL;
}
CFrameBG::~CFrameBG() {
	if (m_hTheme)
		g_xpStyle.CloseThemeData(m_hTheme);
	m_hTheme = NULL;
}

BOOL CFrameBG::IsThemed() {
	return (m_hTheme && g_xpStyle.IsAppThemed());
}

BEGIN_MESSAGE_MAP(CFrameBG, CStatic)
	//{{AFX_MSG_MAP(CFrameBG)
	ON_WM_ERASEBKGND()
  ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CFrameBG message handlers
BOOL CFrameBG::OnEraseBkgnd(CDC* pDC) {
/************************************** : by VK at 12.11.2005 10:23:58 **\
  CRect r;
  GetClientRect(&r);
  CWnd* pParent = GetParent();
  if ( pParent->IsKindOf(RUNTIME_CLASS(CFormView)) ) {
    GradientEraseBkgnd(this, pParent, pDC, r);
  }
\************************************** : by VK at 12.11.2005 10:24:01 **/
	return TRUE;
}

void CFrameBG::OnPaint() {
//  Default();

	if (m_bFirstTime) {
		// open theme for Button
		m_bFirstTime = FALSE;

		if (g_xpStyle.IsThemeLibAvailable()) {
			if (m_hTheme)
				g_xpStyle.CloseThemeData(m_hTheme);
			m_hTheme = NULL;
  		m_hTheme = g_xpStyle.OpenThemeData(m_hWnd, L"Button");
		}
	}

	CPaintDC dc(this); // device context for painting
//  CMemDC memDC(&dc);
  CFont *pFont = GetParent()->GetFont();
	if (pFont)
		dc.SelectObject(pFont);
    
  dc.SetBkMode(TRANSPARENT);

	// Where to draw text
	CRect rc;
	GetClientRect(rc);

	// Get the caption
	CString s, szText;
	GetWindowText(s);
  szText.Format(_T(" %s "), s);
  
  CSize size = dc.GetTextExtent(szText);
  CRect rcFrame = rc;
  rcFrame.top += size.cy/2;
	if (IsThemed()) {
    //CRect rcExclude = rcFrame;
    //rcExclude.InflateRect(4,4);
    //memDC.ExcludeClipRect(&rcExclude);
    g_xpStyle.DrawThemeBackground(m_hTheme, dc.m_hDC, BP_GROUPBOX, GBS_NORMAL|DFCS_TRANSPARENT, &rcFrame, NULL);
  }
  else {
    dc.DrawEdge(&rcFrame, EDGE_ETCHED, BF_RECT | BF_ADJUST);
  }
  CRect rcText = rc;
  rcText.left  += size.cy/2;
  rcText.right  = rcText.left + size.cx;
  rcText.bottom = rc.top + size.cy;

  if ( GetParent()->IsKindOf(RUNTIME_CLASS(CPropertyPage)) ) {
    GradientEraseBkgnd(this, GetParent(), &dc, rcText);
  }
  else {
    EraseBkgndForDlgControl(this, &dc, rcText, false);
  }
/************************************** : by VK at 12.11.2005 22:04:25 **\
  CRect rcParentText = rcText;
  ClientToScreen(&rcParentText);
  GetParent()->ScreenToClient(&rcParentText);
  GetParent()->InvalidateRect(&rcParentText);
\************************************** : by VK at 12.11.2005 22:04:28 **/

//  EraseBkgndForDlgControl(this, &dc, rcText, true);

  dc.DrawState(CPoint(rcText.left, rcText.top), CSize(rcText.Width(), rcText.Height()),
                 (LPCTSTR)szText, (UINT)DSS_NORMAL, TRUE, 0, (HBRUSH)NULL);//, int nTextLen = 0, CBrush* pBrush = NULL );

}

///////////////////////////////////////////////////////////////////////////////
// Message map
BEGIN_MESSAGE_MAP(CXButtonXP, COddButton)
	//{{AFX_MSG_MAP(CXButtonXP)
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
  ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
  ON_MESSAGE(BM_GETCHECK, OnGetCheck)
  ON_MESSAGE(BM_SETCHECK, OnSetCheck)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// ctor
CXButtonXP::CXButtonXP() {
	m_hTheme           = NULL;
	m_bMouseOverButton = FALSE;
	m_bFirstTime       = m_fDestroyIcons = TRUE;
	m_hIcon            = NULL;
  memset(m_hIcons, 0, sizeof(m_hIcons));
  m_nIDIconOn = m_nIDIconOff = 0;
  m_iaOn = m_iaOff = LEFT;
	m_eIconAlignment   = LEFT;
	m_bIsToggle        = FALSE;
	m_bToggled         = FALSE;
	m_bLButtonDown     = FALSE;
	m_bSent            = FALSE;
	m_bEnableTheming   = TRUE;
	m_bDrawToolbar     = FALSE;
  m_fClickDown       = FALSE;
  m_fRadio = m_fCheckBox = m_bOn = m_bFocusFore = m_bFocusBack = FALSE;
  m_fReturnAsTab = FALSE;

  m_clrForeOn = m_clrForeOff = GetSysColor(COLOR_BTNTEXT);
  m_clrBackOn = m_clrBackOff = GetSysColor(COLOR_3DFACE);
  m_FirstID = m_LastID = 0;
}

///////////////////////////////////////////////////////////////////////////////
// dtor
CXButtonXP::~CXButtonXP()
{
	if (m_hTheme)
		g_xpStyle.CloseThemeData(m_hTheme);
	m_hTheme = NULL;

	if (m_hIcon)
		DestroyIcon(m_hIcon);
	m_hIcon = NULL;
  if ( m_fDestroyIcons ) {
    for( int i(0); i < 8; i++ ) {
      if ( m_hIcons[i] )
        DestroyIcon(m_hIcons[i]);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// IsThemed
BOOL CXButtonXP::IsThemed()
{
	BOOL bAppThemed = g_xpStyle.IsAppThemed();	// user can disable theming
													// for app by right-clicking
													// on exe, then clicking on
													// Properties | Compatibility |
													// Disable visual themes
	return (m_hTheme && m_bEnableTheming && bAppThemed);
}

///////////////////////////////////////////////////////////////////////////////
// SetIcon - from resource id
void CXButtonXP::SetIcon(UINT nIDResource, ICON_ALIGNMENT ia /*= LEFT*/)
{
	TRACE(_T("in CXButtonXP::SetIcon UINT\n"));

	HICON hIcon = (HICON) LoadImage(AfxGetInstanceHandle(),
								MAKEINTRESOURCE(nIDResource),
								IMAGE_ICON,
								0,
								0,
								0);

	SetIcon(hIcon, ia);

	TRACE(_T("m_hIcon=%X\n"), m_hIcon);
}

///////////////////////////////////////////////////////////////////////////////
// SetIcon - from HICON
void CXButtonXP::SetIcon(HICON hIcon, ICON_ALIGNMENT ia /*= LEFT*/) {
	TRACE(_T("in CXButtonXP::SetIcon HICON\n"));

	if (m_hIcon)
		DestroyIcon(m_hIcon);

	m_hIcon = hIcon;
	TRACE(_T("m_hIcon=%X\n"), m_hIcon);

	m_eIconAlignment = ia;

	RedrawWindow();
}

void CXButtonXP::ResetIcons() {
  if ( m_bOn && m_nIDIconOn ) {
    SetIcon(m_nIDIconOn, m_iaOn);
  }
  else if ( FALSE==m_bOn && m_nIDIconOff ) {
    SetIcon(m_nIDIconOff, m_iaOff);
  }
  else {
    InvalidateRect(NULL);
  }
}
void CXButtonXP::SetIcons(UINT nIDIconOn, UINT nIDIconOff, ICON_ALIGNMENT iaOn, ICON_ALIGNMENT iaOff) {
  m_nIDIconOn = nIDIconOn;
  m_nIDIconOff = nIDIconOff;
  m_iaOn = iaOn;
  m_iaOff = iaOff;
  ResetIcons();
}

void CXButtonXP::SetImageList(CImageList* pImageList) {
  for( int i(0); i < 7; i++ ) {
    m_hIcons[i] = pImageList->ExtractIcon(i);
  }
}
void CXButtonXP::SetRadioImageList(CImageList* pImageList) {
  m_fRadio = TRUE;
  SetImageList(pImageList);
}
void CXButtonXP::SetCheckBoxImageList(CImageList* pImageList) {
  m_fCheckBox = TRUE;
  SetImageList(pImageList);
}

void CXButtonXP::SetText(LPCTSTR szOnText, LPCTSTR szOffText) {
  m_strOnText = szOnText;
  m_strOffText = szOffText;
  if ( GetSafeHwnd() ) {
    InvalidateRect(NULL);
  }
}

void CXButtonXP::SetBackColor(COLORREF clrOn, COLORREF clrOff, bool bForFocus/*=false*/) {
  if ( bForFocus ) {
    m_bFocusBack = true;
    m_clrFocusBackOn = clrOn;
    m_clrFocusBackOff = clrOff;
  }
  else {
    m_clrBackOn = clrOn;
    m_clrBackOff = clrOff;
  }
}

void CXButtonXP::SetForeColor(COLORREF clrOn, COLORREF clrOff, bool bForFocus/*=false*/) {
  if ( bForFocus ) {
    m_bFocusFore = true;
    m_clrFocusForeOn = clrOn;
    m_clrFocusForeOff = clrOff;
  }
  else {
    m_clrForeOn = clrOn;
    m_clrForeOff = clrOff;
  }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// PRIVATE FUNCTIONS & MESSAGE HANDLERS
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// PrepareImageRect
void CXButtonXP::PrepareImageRect(BOOL bHasText,
								  RECT& rectItem,
								  RECT& rectText,
								  BOOL bIsPressed,
								  DWORD dwWidth,
								  DWORD dwHeight,
								  RECT& rectImage)
{
	CopyRect(&rectImage, &rectItem);

	if (bHasText)
	{
		// image must be placed just inside the focus rect
		int nTextWidth = rectText.right - rectText.left;
		if (m_eIconAlignment == RIGHT)
		{
			rectText.right = nTextWidth - dwWidth - dwWidth/2;
			rectText.left  = dwWidth/2;
			rectImage.left = rectItem.right - dwWidth - dwWidth/2;
		}
		else	// icon is on the left
		{
			rectText.right = nTextWidth - dwWidth/2;
			rectText.left  = 2 * dwWidth;
			rectImage.left = dwWidth/2;
		}
	}
	else	// no text
	{
		// center image horizontally
		int nImageWidth = rectImage.right - rectImage.left;
		rectImage.left += ((nImageWidth - dwWidth)/2);
	}

	// center image vertically
	int nImageHeight = rectImage.bottom - rectImage.top;
	rectImage.top += ((nImageHeight - dwHeight)/2);

	// if button is pressed then press image also
	if (bIsPressed && !IsThemed())
		OffsetRect(&rectImage, 1, 1);
}

///////////////////////////////////////////////////////////////////////////////
// DrawIcon
void CXButtonXP::DrawIcon(CDC *pDC, HICON hIcon,
						  BOOL bHasText,
						  RECT& rectItem,		// from LPDRAWITEMSTRUCT
						  RECT& rectText,
						  BOOL bIsPressed,
						  BOOL bIsDisabled)
{
	if (hIcon)
	{
		// first get size of icon

		DWORD dwWidth = 32;		// assume 32x32
		DWORD dwHeight = 32;
		ICONINFO iconinfo;

		if (GetIconInfo(hIcon, &iconinfo))
		{
			CBitmap* pBitmap = CBitmap::FromHandle(iconinfo.hbmColor);
			if (pBitmap)
			{
				BITMAP bm;
				pBitmap->GetBitmap(&bm);
				dwWidth = bm.bmWidth;
				dwHeight = bm.bmHeight;
			}
      // by VK
      if ( iconinfo.hbmMask  )  ::DeleteObject(iconinfo.hbmMask);
      if ( iconinfo.hbmColor )  ::DeleteObject(iconinfo.hbmColor);
      // by VK
		}

		RECT rectImage;

		PrepareImageRect(bHasText, rectItem, rectText, bIsPressed, dwWidth, dwHeight, rectImage);

		pDC->DrawState(CPoint(rectImage.left, rectImage.top),
					   CSize(rectImage.right - rectImage.left, rectImage.bottom - rectImage.top),
					   hIcon,
					   (bIsDisabled ? DSS_DISABLED : DSS_NORMAL) | DST_ICON,
					   (CBrush *) NULL);
	}
}

///////////////////////////////////////////////////////////////////////////////
// OnMouseMove
void CXButtonXP::OnMouseMove(UINT nFlags, CPoint point) {
	// check to see if mouse is over button

	CPoint pt(point);
	ClientToScreen(&pt);

	CRect rect;
	GetWindowRect(&rect);

	BOOL bMouseOverButton = m_bMouseOverButton;

	if (rect.PtInRect(pt))
	{
		m_bMouseOverButton = TRUE;

    TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(tme);
    tme.dwFlags = TME_LEAVE;
    tme.hwndTrack = m_hWnd;
    _TrackMouseEvent(&tme);
/************************************** : by VK at 20.05.2005 23:27:34 **\    
    SetCapture();					// +++HD 2005.04.20
\************************************** : by VK at 20.05.2005 23:27:37 **/
	}
	else
	{
		m_bMouseOverButton = FALSE;
/************************************** : by VK at 20.05.2005 23:27:41 **\
    ReleaseCapture();				// +++HD 2005.04.20
\************************************** : by VK at 20.05.2005 23:27:43 **/
	}

	if (bMouseOverButton != m_bMouseOverButton)
		InvalidateRect(NULL);

	TRACE(_T("in CXButtonXP::OnMouseMove:  m_bMouseOverButton=%d\n"), m_bMouseOverButton);

	COddButton::OnMouseMove(nFlags, point);
}
LRESULT CXButtonXP::OnMouseLeave(WPARAM wParam, LPARAM lParam) {
  CPoint point;
  GetCursorPos(&point);
  ScreenToClient(&point);
  OnMouseMove(0, point);
  return 0L;
}

void CXButtonXP::EraseBkgnd(CDC* pDC, CRect& rect, BOOL bFocus) {
  if ( bFocus ) {
    COLORREF clrBk = 0xFFFFFF;
    pDC->FillSolidRect(&rect, clrBk);
  }
  else {
    CWnd* pParent = GetParent();
    if ( !pParent->IsKindOf(RUNTIME_CLASS(CDialog)) ) {
      pParent = GetParentFrame();
    }
    //GradientEraseBkgnd(this, pParent, pDC, rect);
    if ( !pParent->IsKindOf(RUNTIME_CLASS(CPropertyPage)) ) {
      EraseBkgndForDlgControl(this, pDC, rect);
    }
    else {
      EraseBkgndForDlgControl(this, pDC, rect, true);
    }
  }
}
///////////////////////////////////////////////////////////////////////////////
// OnEraseBkgnd - to prevent flicker
BOOL CXButtonXP::OnEraseBkgnd(CDC* pDC) {
	return TRUE;
}

static int PropId = 0;

///////////////////////////////////////////////////////////////////////////////
// DrawItem
void CXButtonXP::DrawItem(LPDRAWITEMSTRUCT lpDIS) {
	if (m_bFirstTime) {
		// open theme for Button

		m_bFirstTime = FALSE;

		if (g_xpStyle.IsThemeLibAvailable())
		{
			if (m_hTheme)
				g_xpStyle.CloseThemeData(m_hTheme);
			m_hTheme = NULL;

			if (m_bDrawToolbar)
				m_hTheme = g_xpStyle.OpenThemeData(m_hWnd, L"Toolbar");	// +++HD 2005.04.20
			else
				m_hTheme = g_xpStyle.OpenThemeData(m_hWnd, L"Button");
		}
	}

	CDC *pDC = CDC::FromHandle(lpDIS->hDC);

	CMemDC memDC(pDC);

	CFont *pFont = GetParent()->GetFont();

	if (pFont)
		memDC.SelectObject(pFont);

	// button state

	BOOL bIsPressed     = lpDIS->itemState & ODS_SELECTED;

  COLORREF clrBk   = GetSysColor(COLOR_3DFACE),
           clrText = GetSysColor(COLOR_BTNTEXT);

	// get the button's title
	CString strTitle = _T("");
  if ( FALSE==m_strOnText.IsEmpty() && FALSE==m_strOffText.IsEmpty() ) {
    if ( m_bOn ) {  // button is checked
      strTitle = m_strOnText;
      clrBk    = m_clrBackOn;
      clrText  = m_clrForeOn;
    }
    else {
      strTitle = m_strOffText;
      clrBk    = m_clrBackOff;
      clrText  = m_clrForeOff;
    }
  }
  else {
	  GetWindowText(strTitle);
  }
/************************************** : by VK at 21.05.2005 1:10:20 **\
  if (lpDIS->itemState & (ODS_FOCUS|ODS_SELECTED)) {
    fFocus = TRUE;
    if ( m_bFocusFore )
      clrText =  m_bOn ? m_clrFocusForeOn : m_clrFocusForeOff;
    if ( m_bFocusBack )
      clrBk = m_bOn ? m_clrFocusBackOn : m_clrFocusBackOff;
    else
      clrBk = clrFocus;
  }
\************************************** : by VK at 21.05.2005 1:10:23 **/
	BOOL bHasText = !strTitle.IsEmpty();

/************************************** : by VK at 21.05.2005 0:21:45 **\
	if (m_bIsToggle) {
		if (m_bLButtonDown && !m_bMouseOverButton) {
			// left mb is down outside button
			bIsPressed = !m_bToggled;
		}
		else {
			bIsPressed = m_bToggled;
		}
	}
\************************************** : by VK at 21.05.2005 0:21:48 **/
	BOOL bIsFocused     = lpDIS->itemState & ODS_FOCUS;
	BOOL bIsDisabled    = lpDIS->itemState & ODS_DISABLED;
	BOOL bDrawFocusRect = !(lpDIS->itemState & ODS_NOFOCUSRECT);

  if ( bIsFocused ) {
    if ( m_bFocusFore )
      clrText =  m_bOn ? m_clrFocusForeOn : m_clrFocusForeOff;
    if ( m_bFocusBack )
      clrBk = m_bOn ? m_clrFocusBackOn : m_clrFocusBackOff;
    else
      clrBk = 0xFFFFFF;
  }

	CRect itemRect = lpDIS->rcItem;

	memDC.SetBkMode(TRANSPARENT);

	DWORD part = BP_PUSHBUTTON;

	if (IsThemed())
	{
		DWORD state = bIsPressed ? PBS_PRESSED : PBS_NORMAL;

		if (state == PBS_NORMAL)
		{
			if (bIsFocused)
				state = PBS_DEFAULTED;
			if (m_bMouseOverButton)
				state = PBS_HOT;
		}
    g_xpStyle.DrawThemeBackground(m_hTheme, memDC.m_hDC, part, state, &itemRect, NULL);

    InflateRect(&itemRect, -4, -4);
    EraseBkgnd(&memDC, itemRect, bIsFocused);
    InflateRect(&itemRect, 4, 4);

    if ( bIsFocused ) { 
      //CBrush brBackground(clrBk);
      InflateRect(&itemRect, -4, -4);
      memDC.FillSolidRect(&itemRect, clrBk);
      InflateRect(&itemRect, 4, 4);
    }
  }
	else
	{
		if (bIsFocused)
		{
      if (!m_bIsToggle || !bIsPressed)
			{
				CBrush brush(RGB(0,0,0));
				memDC.FrameRect(&itemRect, &brush);
			}
			InflateRect(&itemRect, -1, -1);

			CBrush brBackground(clrBk);
			memDC.FillRect(&itemRect, &brBackground);
    }

		if (m_bIsToggle)
		{
			// draw the traditional pushbutton edge using DrawEdge
			if (bIsPressed)
			{
				memDC.DrawEdge(&itemRect, EDGE_SUNKEN, BF_RECT | BF_MIDDLE | BF_SOFT);
			}
			else
			{
				memDC.DrawEdge(&itemRect, EDGE_RAISED, BF_RECT | BF_MIDDLE | BF_SOFT);
			}
    }
		else
		{
/************************************** : by VK at 20.05.2005 22:02:19 **\
      CBrush brBackground(GetSysColor(COLOR_BTNFACE));
	  	memDC.FillRect(&itemRect, &brBackground);
\************************************** : by VK at 20.05.2005 22:02:22 **/

      // draw pressed button
			if (bIsPressed)
			{
        CBrush brBtnShadow(GetSysColor(COLOR_BTNSHADOW));
				memDC.FrameRect(&itemRect, &brBtnShadow);
			}
			else	// ...else draw non pressed button
			{
        UINT uState = DFCS_BUTTONPUSH | (m_bMouseOverButton ? DFCS_HOT : 0) | ((bIsPressed) ? DFCS_PUSHED : 0);
        memDC.DrawFrameControl(&itemRect, DFC_BUTTON, uState);
			}
		}

    InflateRect(&itemRect, -2, -2);
    EraseBkgnd(&memDC, itemRect, bIsFocused);
    InflateRect(&itemRect, 2, 2);

  }

	UINT uTextAlignment = DT_LEFT;
	if (m_hIcon == NULL)
		uTextAlignment = DT_CENTER;
	uTextAlignment |= DT_SINGLELINE | DT_VCENTER | DT_WORDBREAK;

	RECT captionRect = lpDIS->rcItem;

	// draw the icon
  if ( m_fRadio || m_fCheckBox ) {
    int nIndex = 1; // Normal
    if ( bIsDisabled ) nIndex = 0;
    else {
      nIndex = GetCheck()*3 + 1;
      if ( m_bMouseOverButton ) nIndex++;
      if ( bIsPressed ) nIndex++;
    }
    DrawIcon(&memDC, m_hIcons[nIndex], bHasText, lpDIS->rcItem, captionRect, FALSE, FALSE);
  }
  else {
	  DrawIcon(&memDC, m_hIcon, bHasText, lpDIS->rcItem, captionRect, bIsPressed, bIsDisabled);
  }

	// write the button title (if any)
	if (bHasText)
	{
		// draw the button's title -
		// if button is pressed then "press" title also
		if (bIsPressed && !IsThemed())
			OffsetRect(&captionRect, 1, 1);

		// center text
		RECT centerRect = captionRect;
		if (m_hIcon)
			memDC.DrawText(strTitle, -1, &captionRect, uTextAlignment | DT_CALCRECT);

		LONG captionRectHeight = captionRect.bottom - captionRect.top;
		LONG centerRectHeight  = centerRect.bottom  - centerRect.top;
		OffsetRect(&captionRect, 0, (centerRectHeight - captionRectHeight)/2);

		if (IsThemed())
		{
/************************************** : by VK at 21.05.2005 1:19:17 **\
      g_xpStyle.DrawThemeText(m_hTheme, memDC.m_hDC, part, PBS_NORMAL, strTitle, uTextAlignment, 0, &captionRect);
\************************************** : by VK at 21.05.2005 1:19:21 **/
			memDC.SetBkColor(clrBk/*::GetSysColor(COLOR_BTNFACE)*/);
      if ( bIsDisabled ) {
        memDC.SetTextColor(GetSysColor(COLOR_GRAYTEXT));
      }
      else {
        memDC.SetTextColor(clrText/*::GetSysColor(COLOR_BTNTEXT)*/);
      }
			memDC.DrawText(strTitle, -1, &captionRect, uTextAlignment);
		}
		else
		{
			memDC.SetBkMode(TRANSPARENT);

			if ( bIsDisabled ) {
				OffsetRect(&captionRect, 1, 1);
				memDC.SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
				memDC.DrawText(strTitle, -1, &captionRect, uTextAlignment);
				OffsetRect(&captionRect, -1, -1);
				memDC.SetTextColor(::GetSysColor(COLOR_3DSHADOW));
				memDC.DrawText(strTitle, -1, &captionRect, uTextAlignment);
			}
			else
			{
				memDC.SetTextColor(clrText/*::GetSysColor(COLOR_BTNTEXT)*/);
				memDC.SetBkColor(clrBk/*::GetSysColor(COLOR_BTNFACE)*/);
				memDC.DrawText(strTitle, -1, &captionRect, uTextAlignment);
			}
		}
	}

	// draw the focus rect
	if (bIsFocused && bDrawFocusRect)
	{
		RECT focusRect = itemRect;
		InflateRect(&focusRect, -3, -3);
		memDC.DrawFocusRect(&focusRect);
	}
}

BOOL CXButtonXP::PreTranslateMessage(MSG* pMsg) {
	InitToolTip();
	m_ToolTip.RelayEvent(pMsg);

  if ( m_fReturnAsTab ) {
  	if ( pMsg->message==WM_KEYDOWN && VK_RETURN==pMsg->wParam) {
      pMsg->wParam = VK_TAB;
    }
  }
	return CButton::PreTranslateMessage(pMsg);
}
///////////////////////////////////////////////////////////////////////////////
// DefWindowProc
LRESULT CXButtonXP::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// catch WM_KEYDOWN so we can avoid intefering with TAB key
		case WM_GETDLGCODE:
		{
			if (lParam)
			{
				MSG *pMsg = (MSG *) lParam;
				if (pMsg && (pMsg->message == WM_KEYDOWN) ) {
          switch( pMsg->wParam ) {
            case VK_TAB:
            case VK_ESCAPE:
            case VK_LEFT:
            case VK_UP:
            case VK_RIGHT:
            case VK_DOWN:
					    // don't interfere with tab processing
				    	return 0;
          }
				}
			}
			return DLGC_WANTALLKEYS;	// we want all keys except TAB key
		}
		break;

    case WM_KEYDOWN:
      m_fClickDown = FALSE;
      if ( (wParam == VK_SPACE) || (wParam == VK_RETURN && FALSE==m_fReturnAsTab) )
        m_fClickDown = TRUE;
      break;

		// handle RETURN and SPACE - simulate a button click
    case WM_KEYUP://WM_CHAR:
		{
			if ( m_fClickDown && ((wParam == VK_SPACE) || (wParam == VK_RETURN && FALSE==m_fReturnAsTab)) )
			{
        m_fClickDown = FALSE;
				if (m_bIsToggle)
				{
          m_bToggled = !m_bToggled;
					InvalidateRect(NULL);
				}
				else
				{
          if ( FALSE==m_fRadio ) {
					  SendMessage(BM_SETSTATE, 1);
					  m_bSent = TRUE;
          }
				}
        if (wParam == VK_RETURN && FALSE==m_fReturnAsTab )
				{
					CWnd* pParent = GetParent();
					if (pParent != NULL)
					{
						::SendMessage(pParent->m_hWnd, WM_COMMAND,
							(BN_CLICKED<<16) | this->GetDlgCtrlID(),
							(LPARAM)this->m_hWnd);
					}
				}
			}
		}
		break;

    case WM_LBUTTONUP:
		{
			m_bLButtonDown = FALSE;
			if (m_bSent)
			{
				SendMessage(BM_SETSTATE, 0);
				m_bSent = FALSE;

				CWnd* pParent = GetParent();
				if (pParent != NULL)
				{
					::SendMessage(pParent->m_hWnd, WM_COMMAND,
						(BN_CLICKED<<16) | this->GetDlgCtrlID(),
						(LPARAM)this->m_hWnd);
				}
			}

			if (m_bIsToggle)
			{
				// if button is toggled and mouse button is released
				// outside of button, ignore the mouse click and restore
				// button state
				CPoint point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				ClientToScreen(&point);
				CRect rectButton;
				GetWindowRect(&rectButton);

				if (!rectButton.PtInRect(point))
				{
					m_bToggled = !m_bToggled;
					InvalidateRect(NULL);
				}
			}
		}
		break;

		case WM_LBUTTONDOWN:
		{
			m_bLButtonDown = TRUE;
			if (m_bIsToggle)
			{
				m_bToggled = !m_bToggled;
				InvalidateRect(NULL);
			}
		}
		break;

		case WM_LBUTTONDBLCLK:
		{
			if (m_bIsToggle)
			{
				// for toggle buttons, treat doubleclick as singleclick
				SendMessage(BM_SETSTATE, m_bToggled);
			}
			else
			{
				SendMessage(BM_SETSTATE, 1);
				m_bSent = TRUE;
			}
			return 0;
		}

		case WM_THEMECHANGED:
		{
			if (IsThemed()) {
				if (m_hTheme) {
					// when user changes themes, close current theme and re-open
					g_xpStyle.CloseThemeData(m_hTheme);
					m_hTheme = NULL;
					m_bFirstTime = TRUE;
				}
			}
		}
		break;
	}

	return COddButton::DefWindowProc(message, wParam, lParam);
}
void CXButtonXP::OnSetFocus(CWnd* pOldWnd) {
	COddButton::OnSetFocus(pOldWnd);
	InvalidateRect(NULL);
  CWnd* pParent = GetParent();
  if ( pParent )
    pParent->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_SETFOCUS), (LPARAM)m_hWnd);
}

void CXButtonXP::OnKillFocus(CWnd* pNewWnd) {
	COddButton::OnKillFocus(pNewWnd);
	InvalidateRect(NULL);
}
void CXButtonXP::OnClicked() {
	// TODO: Add your control notification handler code here
  if ( m_fRadio || m_fCheckBox ) {
    if ( m_fRadio ) {
      GetParent()->CheckRadioButton(m_FirstID, m_LastID, GetDlgCtrlID());
    }
    else {
      m_bOn ^= 1;
      SetCheck( m_bOn );
    }
/************************************** : by VK at 31.12.2006 0:56:04 **\
		GetParent()->SendMessage(WM_COMMAND, (BN_CLICKED<<16) | this->GetDlgCtrlID(), (LPARAM)NULL);
\************************************** : by VK at 31.12.2006 0:56:09 **/
  }
  else {
    m_bOn ^= 1;
    SetCheck( m_bOn );
    ResetIcons();
  }
	GetParent()->SendMessage(WM_COMMAND, (BN_CLICKED<<16) | this->GetDlgCtrlID(), (LPARAM)NULL/*this->m_hWnd*/);
}
LRESULT CXButtonXP::OnGetCheck(WPARAM, LPARAM) {
  return (LRESULT)( m_bOn ? BST_CHECKED : BST_UNCHECKED);
}

LRESULT CXButtonXP::OnSetCheck(WPARAM wParam, LPARAM) {
  if ( wParam==(WPARAM)BST_CHECKED)
    m_bOn = TRUE;
  else
    m_bOn = FALSE;
  ResetIcons();
  return (LRESULT)0;
}
void CXButtonXP::InitToolTip() {
  if (m_ToolTip.m_hWnd == NULL)	{
		// Create ToolTip control
		m_ToolTip.Create(this, 0);
		// Create inactive
		m_ToolTip.Activate(FALSE);
		// Enable multiline
		m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 400);
		//m_ToolTip.SendMessage(TTM_SETTITLE, TTI_INFO, (LPARAM)_T("Title"));
	} // if
} // End of InitToolTip

// This function sets the text to show in the button tooltip.
//
// Parameters:
//		[IN]	nText
//				ID number of the string resource containing the text to show.
//		[IN]	bActivate
//				If TRUE the tooltip will be created active.
//
void CXButtonXP::SetTooltipText(int nText, BOOL bActivate)
{
	CString sText;

	// Load string resource
	sText.LoadString(nText);
	// If string resource is not empty
	if (sText.IsEmpty() == FALSE) SetTooltipText((LPCTSTR)sText, bActivate);
} // End of SetTooltipText

// This function sets the text to show in the button tooltip.
//
// Parameters:
//		[IN]	lpszText
//				Pointer to a null-terminated string containing the text to show.
//		[IN]	bActivate
//				If TRUE the tooltip will be created active.
//
void CXButtonXP::SetTooltipText(LPCTSTR lpszText, BOOL bActivate)
{
	// We cannot accept NULL pointer
	if (lpszText == NULL) return;

	// Initialize ToolTip
	InitToolTip();

	// If there is no tooltip defined then add it
	if (m_ToolTip.GetToolCount() == 0)
	{
		CRect rectBtn; 
		GetClientRect(rectBtn);
		m_ToolTip.AddTool(this, lpszText, rectBtn, 1);
	} // if

	// Set text for tooltip
	m_ToolTip.UpdateTipText(lpszText, this, 1);
	m_ToolTip.Activate(bActivate);
} // End of SetTooltipText

// This function enables or disables the button tooltip.
//
// Parameters:
//		[IN]	bActivate
//				If TRUE the tooltip will be activated.
//
void CXButtonXP::ActivateTooltip(BOOL bActivate) {
	// If there is no tooltip then do nothing
	if (m_ToolTip.GetToolCount() == 0) return;

	// Activate tooltip
	m_ToolTip.Activate(bActivate);
} // End of EnableTooltip

/////////////////////////////////////////////////////////////////////////////
// CEraMultiStateButton
BEGIN_MESSAGE_MAP(CEraMultiStateButton, CXButtonXP)
	//{{AFX_MSG_MAP(CEraMultiStateButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CEraMultiStateButton::CEraMultiStateButton() {
  m_clrFore = GetSysColor(COLOR_BTNTEXT);
  m_clrBack = GetSysColor(COLOR_3DFACE);
  m_nCurrentState = 0;
}

CEraMultiStateButton::~CEraMultiStateButton() {
  m_StateNames.RemoveAll();
}

void CEraMultiStateButton::SetIndex(int nIndex) {
  BOOL fRedraw = FALSE;
  m_nCurrentState = nIndex; 
  if ( nIndex < m_StateNames.GetSize() ) {
    m_strOnText = m_strOffText = m_StateNames.GetAt(nIndex);
    fRedraw = TRUE;
  }
  if ( nIndex < m_StateNames.GetSize() ) {
    COLORREF clr = m_ForeColors.GetAt(nIndex);
    SetForeColor( clr, clr );
    fRedraw = TRUE;
  }
  if ( fRedraw )
    InvalidateRect(NULL);
}
int CEraMultiStateButton::GetIndex() {
  return m_nCurrentState;
}

void CEraMultiStateButton::AddState(int nIndex, LPCTSTR szName) {
  m_StateNames.SetAtGrow(nIndex, szName);
  m_ForeColors.SetAtGrow(nIndex, (DWORD)m_clrFore) ;
}

void CEraMultiStateButton::AddColorState(int nIndex, COLORREF clr, LPCTSTR szName) {
  m_StateNames.SetAtGrow(nIndex, szName);
  m_ForeColors.SetAtGrow(nIndex, (DWORD)clr) ;
}
void CEraMultiStateButton::OnClicked() {
  if ( ++m_nCurrentState == m_StateNames.GetSize() )
    m_nCurrentState = 0;
  SetIndex(m_nCurrentState);
//  InvalidateRect(NULL);
/************************************** : by VK at 18.01.2004 17:25:56 **\
  CWnd* pParent = GetParent();
  if ( pParent )
    pParent->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
\************************************** : by VK at 18.01.2004 17:25:59 **/
}

/////////////////////////////////////////////////////////////////////////////
// CEraPassportButton
CEraPassportButton::CEraPassportButton() {
  AddState(0, _T("ïàñïîðò") );
  AddState(1, _T("ÇÇÏ") );
  AddState(2, _T("Ñâ. í-íÿ") );
  AddState(3, _T("ÒÏÏ") );
}

/////////////////////////////////////////////////////////////////////////////
// CEraMWPassportButton
CEraMWPassportButton::CEraMWPassportButton() {
  AddColorState(0, g_clrMaleForeColor, _T("ïàñïîðò") );
  AddColorState(1, g_clrMaleForeColor, _T("ÇÇÏ") );
  AddColorState(2, g_clrMaleForeColor, _T("Ñâ. í-íÿ") );
  AddColorState(3, g_clrMaleForeColor, _T("ÒÏÏ") );

  AddColorState(4, g_clrFemaleForeColor, _T("ïàñïîðò") );
  AddColorState(5, g_clrFemaleForeColor, _T("ÇÇÏ") );
  AddColorState(6, g_clrFemaleForeColor, _T("Ñâ. í-íÿ") );
  AddColorState(7, g_clrFemaleForeColor, _T("ÒÏÏ") );
}



