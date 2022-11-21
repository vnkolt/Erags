// EraLabel.cpp : implementation file
//

#include "stdafx.h"
#include "EraLabel.h"
#include "NewMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void DrawGradient(CDC* pDC,CRect& Rect, COLORREF StartColor,COLORREF EndColor,  BOOL bHorizontal,BOOL bUseSolid);


BEGIN_MESSAGE_MAP(CEraLabel, CStatic)
	//{{AFX_MSG_MAP(CEraLabel)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraLabel Version 1.2
//
// From now on I'll try to keep a log of fixes and enhancements...
// 
// The new feature were added due to the response of people.
// All I ask is to all you programmers out there, is if you add, fix or
// enhance this code, sent me a copy and I'll send the copy on to www.codeguru.com
//
// Happy hacking :)
// 
// New features include:
//
// A. Support for 3D Fonts
// B. Support for background transparency
// C. More comments provided
// D. If alignment is 'centered' and the window text is seperated by '\r\n'
//	  the will be centered accordingly - requested by someone @ nasa ;)
// E. Support for font rotation.
// F. Respond to System Color Change
// G. OnPaint improved performance - using Double Buffering Technique
//
// Thanks to:
// Mark McDowell	- For suggestion on 'Increasing the flexibility of "hypertext" setting...'
// Erich Ruth		- For suggestion on 'Font Rotation'
//

/////////////////////////////////////////////////////////////////////////////
// CEraLabel Version 1.3
//
// A. Added SS_LEFTNOWORDWRAP to include wordwrap
// B. Fix repainting problem 
// C. Fix SetBkColor
// D. Added SS_CENTER

// Thanks to:
// Marius						- Added styling problem.
// Azing Vondeling & Broker		- Spotting painting Problem.
// Mel Stober					- Back Color & SS_CENTER
// 
/////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::CEraLabel
//
// Description:		Default contructor
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel::CEraLabel() {
	m_crText = GetSysColor(COLOR_WINDOWTEXT);

// 1.1
	m_hBackBrush = NULL;
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);

	m_font.CreateFontIndirect(&m_lf);
	m_bTimer =			FALSE;
	m_bState =			FALSE;
	m_bTransparent =	FALSE;
	m_bLink =			TRUE;
	m_hCursor =			NULL;
	m_Type =			  Background;
	m_bFont3d =			FALSE;
	m_bNotifyParent =	FALSE;
	m_bToolTips =		FALSE;
	m_bRotation =		FALSE;
	
	m_hwndBrush = ::CreateSolidBrush(GetSysColor(COLOR_3DFACE));
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::~CEraLabel
//
// Description:		
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel::~CEraLabel() {
	// Clean up
	m_font.DeleteObject();
	::DeleteObject(m_hwndBrush);
  if ( m_hBackBrush )
	  ::DeleteObject(m_hBackBrush);
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::ReconstructFont
//
// Description:		Helper function to build font after it was changed
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
void CEraLabel::ReconstructFont() {
  m_font.DeleteObject();
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf);

	ASSERT(bCreated);
}

BOOL CEraLabel::OnEraseBkgnd(CDC* pDC) {
  CRect r;
  GetClientRect(&r);
  CWnd* pParent = GetParent();
  if ( pParent->IsKindOf(RUNTIME_CLASS(CFormView)) || pParent->IsKindOf(RUNTIME_CLASS(CPropertyPage)) ) {
    GradientEraseBkgnd(this, GetParent(), pDC, r);
  }
  else {
    //GradientEraseBkgnd(this, GetParent(), pDC, r);
    EraseBkgndForDlgControl(this, pDC, r);
  }
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::OnPaint
//
// Description:		Handles all the drawing code for the label
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			Called by Windows... not by USER
//					Probably needs tiding up a some point.
//					Different states will require this code to be reworked.
//
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////

void CEraLabel::OnPaint() {
	CPaintDC dc(this); // device context for painting
  //DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
	DWORD dwFlags = 0;

	CRect rc;
	GetClientRect(rc);
	CString strText;
	GetWindowText(strText);
	CBitmap bmp;


	///////////////////////////////////////////////////////
	//
	// Set up for double buffering...
	//
	CDC* pDCMem = &dc;
/************************************** : by VK at 04.01.2005 3:17:05 **\
  CBitmap* pOldBitmap;
	if (!m_bTransparent) {
		pDCMem = new CDC;
		pDCMem->CreateCompatibleDC(&dc);
		bmp.CreateCompatibleBitmap(&dc,rc.Width(),rc.Height());
		pOldBitmap = pDCMem->SelectObject(&bmp);
	}
	else {
		pDCMem = &dc;
	}
\************************************** : by VK at 04.01.2005 3:17:09 **/
	UINT nMode = pDCMem->SetBkMode(TRANSPARENT);


	COLORREF crText = pDCMem->SetTextColor(m_crText);
	CFont *pOldFont = pDCMem->SelectObject(&m_font);


	// Fill in backgound if not transparent
/************************************** : by VK at 04.01.2005 3:04:55 **\
	if (!m_bTransparent)
	{
		CBrush br;
		
		if (m_bState && m_Type == Background)
		{
			if (m_hBackBrush != NULL)
				br.Attach(m_hBackBrush);
			else
				br.Attach(m_hwndBrush);
		}
		else
		{
			if (m_hBackBrush != NULL)
				br.Attach(m_hBackBrush);
			else
				br.Attach(m_hwndBrush);
		}
		pDCMem->FillRect(rc,&br);
		br.Detach();
	}
\************************************** : by VK at 04.01.2005 3:04:59 **/

  pDCMem->SetBkMode(TRANSPARENT);
	
	// If the text is flashing turn the text color on
	// then to the color of the window background.

	LOGBRUSH lb;
	ZeroMemory(&lb,sizeof(lb));
	::GetObject(m_hBackBrush,sizeof(lb),&lb);


	// Something to do with flashing
	if (!m_bState && m_Type == Text)
		pDCMem->SetTextColor(lb.lbColor);


	if (!(GetStyle() & SS_LEFTNOWORDWRAP))
		dwFlags |= DT_WORDBREAK;

	if (GetStyle() & SS_LEFT)
		dwFlags = DT_LEFT;

	if (GetStyle() & SS_RIGHT)
		dwFlags = DT_RIGHT;

	if (GetStyle() & SS_CENTER)
		dwFlags = DT_CENTER;

	// If the text centered make an assumtion that
	// the will want to center verticly as well
	if (GetStyle() & SS_CENTERIMAGE) {
		// dwFlags = DT_CENTER;

		// Apply 
		if (strText.Find("\r\n") == -1) {
			dwFlags |= DT_VCENTER;

			// And because DT_VCENTER only works with single lines
			dwFlags |= DT_SINGLELINE; 
		}
	}

	//
	// 3333   DDDDD
	//     3  D    D
	//   33   D     D    E F X 
	//     3  D    D
	// 3333   DDDDD
	//
	//
	if (m_bRotation) {
		int nAlign = pDCMem->SetTextAlign (TA_BASELINE);

		CPoint pt;
		GetViewportOrgEx (pDCMem->m_hDC,&pt) ;
		SetViewportOrgEx (pDCMem->m_hDC,rc.Width() / 2, rc.Height() / 2, NULL) ;
		pDCMem->TextOut (0, 0, strText) ;
		SetViewportOrgEx (pDCMem->m_hDC,pt.x / 2, pt.y / 2, NULL) ;
		pDCMem->SetTextAlign (nAlign);
	}
	else {
		pDCMem->DrawText(strText,rc,dwFlags);
		if (m_bFont3d) {
			pDCMem->SetTextColor(RGB(255,255,255));

			if (m_3dType == Raised)
				rc.OffsetRect(-1,-1);
			else
				rc.OffsetRect(1,1);

			pDCMem->DrawText(strText,rc,dwFlags);
			m_3dType;

		}
	}

	// Restore DC's State
	pDCMem->SetBkMode(nMode);
	pDCMem->SelectObject(pOldFont);
	pDCMem->SetTextColor(crText);

/************************************** : by VK at 04.01.2005 3:17:19 **\
	if (!m_bTransparent) {
		dc.BitBlt(0,0,rc.Width(),rc.Height(),pDCMem,0,0,SRCCOPY);
    pDCMem->SelectObject(pOldBitmap);
		delete pDCMem;
  }
\************************************** : by VK at 04.01.2005 3:17:23 **/
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::OnTimer
//
// Description:		Used in conjunction with 'FLASH' functions
//
// INPUTS:          Windows API
// 
// RETURNS:         Windows API
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
void CEraLabel::OnTimer(UINT nIDEvent) {

	m_bState = !m_bState;

	InvalidateRect(NULL,TRUE);
	UpdateWindow();
	
	CStatic::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::OnSetCursor
//
// Description:		Used in conjunction with 'LINK' function
//
// INPUTS:          Windows API
// 
// RETURNS:         Windows API
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
BOOL CEraLabel::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {

	if (m_hCursor) {
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::OnLButtonDown
//
// Description:		Called when a link is click on
//
// INPUTS:          Windows API
// 
// RETURNS:         Windows API
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
void CEraLabel::OnLButtonDown(UINT nFlags, CPoint point) {

	if (m_bNotifyParent) {
		CString strLink;

		GetWindowText(strLink);
		ShellExecute(NULL,"open",strLink,NULL,NULL,SW_SHOWNORMAL);
	}
	else {
		// To use notification in parent window
		// Respond to a OnNotify in parent and disassemble the message
		//
		NMHDR nm;

		nm.hwndFrom = GetSafeHwnd();
		nm.idFrom  = GetDlgCtrlID();
		nm.code = NM_LINKCLICK;
		GetParent()->SendMessage(WM_NOTIFY,nm.idFrom,(LPARAM) &nm);
	}
		
	CStatic::OnLButtonDown(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// THE FUNCTIONS START HERE :----
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetText
//
// Description:		Short cut to set window text - caption - label
//
// INPUTS:          Text to use
// 
// RETURNS:         Reference to this
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetText(const CString& strText) {

	SetWindowText(strText);
	Invalidate(FALSE);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetTextColor
//
// Description:		Sets the text color 
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetTextColor(COLORREF crText) {

	m_crText = crText;
	RedrawWindow();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetFontBold
//
// Description:		Sets the font ot bold 
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetFontBold(BOOL bBold) {	

	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	ReconstructFont();
	RedrawWindow();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetFontUnderline
//
// Description:		Sets font underline attribue
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetFontUnderline(BOOL bSet) {	
	m_lf.lfUnderline = bSet;
	ReconstructFont();
	RedrawWindow();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetFontItalic
//
// Description:		Sets font italic attribute
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetFontItalic(BOOL bSet)
{

	m_lf.lfItalic = bSet;
	ReconstructFont();
	RedrawWindow();
	return *this;	
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetSunken
//
// Description:		Sets sunken effect on border
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetSunken(BOOL bSet) {

	if (!bSet)
		ModifyStyleEx(WS_EX_STATICEDGE,0,SWP_DRAWFRAME);
	else
		ModifyStyleEx(0,WS_EX_STATICEDGE,SWP_DRAWFRAME);
		
	return *this;	
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetBorder
//
// Description:		Toggles the border on/off
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetBorder(BOOL bSet) {

	if (!bSet)
		ModifyStyle(WS_BORDER,0,SWP_DRAWFRAME);
	else
		ModifyStyle(0,WS_BORDER,SWP_DRAWFRAME);
		
	return *this;	
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetFontSize
//
// Description:		Sets the font size
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetFontSize(int nSize) {

	CFont cf;
	LOGFONT lf;

	cf.CreatePointFont(nSize * 10, m_lf.lfFaceName);
	cf.GetLogFont(&lf);

	m_lf.lfHeight = lf.lfHeight;
	m_lf.lfWidth  = lf.lfWidth;

	RedrawWindow();

//	nSize*=-1;
//	m_lf.lfHeight = nSize;
	ReconstructFont();
	RedrawWindow();
	return *this;
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetBkColor
//
// Description:		Sets background color
//
// INPUTS:          Colorref of background color
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetBkColor(COLORREF crBkgnd) {

	if (m_hBackBrush)
		::DeleteObject(m_hBackBrush);

	m_hBackBrush = ::CreateSolidBrush(crBkgnd);

	Invalidate(FALSE);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetFontName
//
// Description:		Sets the fonts face name
//
// INPUTS:          String containing font name
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetFontName(const CString& strFont) {	

	strcpy(m_lf.lfFaceName,strFont);
	ReconstructFont();
	RedrawWindow();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::FlashText
//
// Description:		As the function states
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::FlashText(BOOL bActivate) {

	if (m_bTimer)
		KillTimer(1);

	if (bActivate) {
		m_bState = FALSE;
		
		m_bTimer = TRUE;
		
		SetTimer(1,500,NULL);

		m_Type = Text;
	}
	else
		m_Type = None; // Fix

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::FlashBackground
//
// Description:		As the function states
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::FlashBackground(BOOL bActivate) {

	if (m_bTimer)
		KillTimer(1);

	if (bActivate)
	{
		m_bState = FALSE;

		m_bTimer = TRUE;
		SetTimer(1,500,NULL);

		m_Type = Background;
	}

	return *this;
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetLink
//
// Description:		Indicates the string is a link
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
// NT ALMOND				26/08/99	1.2		Added flexbility of
//												Sending Click meessage to parent
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetLink(BOOL bLink,BOOL bNotifyParent) {

	m_bLink = bLink;
	m_bNotifyParent = bNotifyParent;

	if (bLink)
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetLinkCursor
//
// Description:		Sets the internet browers link
//
// INPUTS:          Handle of cursor
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetLinkCursor(HCURSOR hCursor) {

	m_hCursor = hCursor;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetTransparent
//
// Description:		Sets the Label window to be transpaent
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetTransparent(BOOL bSet) {

	m_bTransparent = bSet;
	InvalidateRect(NULL,TRUE);
	UpdateWindow();

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetFont3D
//
// Description:		Sets the 3D attribute of the font.
//
// INPUTS:          True or false, Raised or Sunken
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetFont3D(BOOL bSet,Type3D type) {

	m_bFont3d = bSet;
	m_3dType = type;
	RedrawWindow();

	return *this;
}

void CEraLabel::OnSysColorChange() {

	if (m_hwndBrush)
		::DeleteObject(m_hwndBrush);

	m_hwndBrush = ::CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	
	RedrawWindow();
		
}



//////////////////////////////////////////////////////////////////////////
//
// Function:		CEraLabel::SetRotationAngle
//
// Description:		Sets the 3D attribute of the font.
//
// INPUTS:          True or false, Raised or Sunken
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CEraLabel& CEraLabel::SetRotationAngle(UINT nAngle,BOOL bRotation) {
	// Arrrrh...
	// Your looking in here why the font is rotating, aren't you?
	// Well try setting the font name to 'Arial' or 'Times New Roman'
	// Make the Angle 180 and set bRotation to true.
	//
	// Font rotation _ONLY_ works with TrueType fonts...
	//
	// 
	m_lf.lfEscapement = m_lf.lfOrientation = (nAngle * 10);
	m_bRotation = bRotation;
	
	ReconstructFont();
	
	RedrawWindow();

	return *this;
}
/////////////////////////////////////////////////////////////////////////////
// CEraOnOffLabel

CEraOnOffLabel::CEraOnOffLabel() {
  m_bOn = FALSE;
  m_BrushOn.CreateSolidBrush( ::GetSysColor(COLOR_BTNFACE) );
  m_BrushOff.CreateSolidBrush( ::GetSysColor(COLOR_BTNFACE) );
  m_OnForeClr = m_OffForeClr = ::GetSysColor(COLOR_WINDOWTEXT);
  m_OnBackClr = m_OffBackClr = ::GetSysColor(COLOR_BTNFACE);
}

CEraOnOffLabel::~CEraOnOffLabel() {
}

void  CEraOnOffLabel::SetText(LPCTSTR szOnText, LPCTSTR szOffText) {
  ModifyStyle(0,SS_NOTIFY);
  m_OnText = szOnText;
  m_OffText = szOffText;
  SetWindowText( m_bOn ? m_OnText : m_OnText );
}
void  CEraOnOffLabel::SetForeColor(COLORREF	clrOn, COLORREF	clrOff) {
  m_OnForeClr = clrOn;
  m_OffForeClr = clrOff;
}
void  CEraOnOffLabel::SetBackColor(COLORREF	clrOn, COLORREF	clrOff) {
  m_OnBackClr = clrOn;
  m_OffBackClr = clrOff;
  m_BrushOn.CreateSolidBrush(m_OnBackClr);
  m_BrushOff.CreateSolidBrush(m_OffBackClr);
}

void CEraOnOffLabel::Reset() {
  SetWindowText( m_bOn ? m_OnText : m_OffText );
  InvalidateRect(NULL);
}
void CEraOnOffLabel::SetOn(BOOL bOn) {
  if ( bOn != m_bOn ) {
    m_bOn = bOn;
    Reset();
  }
}

BEGIN_MESSAGE_MAP(CEraOnOffLabel, CStatic)
	//{{AFX_MSG_MAP(CEraOnOffLabel)
  ON_WM_CTLCOLOR_REFLECT( )
  ON_WM_ERASEBKGND()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraOnOffLabel message handlers
BOOL CEraOnOffLabel::OnEraseBkgnd(CDC* pDC) {
  CRect r;
  GetClientRect(&r);
  CWnd* pParent = GetParent();
  if ( pParent->IsKindOf(RUNTIME_CLASS(CFormView)) || pParent->IsKindOf(RUNTIME_CLASS(CPropertyPage)) ) {
    GradientEraseBkgnd(this, GetParent(), pDC, r);
  }
  else {
    //GradientEraseBkgnd(this, GetParent(), pDC, r);
    EraseBkgndForDlgControl(this, pDC, r);
  }
	return TRUE;
}
HBRUSH CEraOnOffLabel::CtlColor(CDC* pDC, UINT nCtlColor) {
  CString s;
  GetWindowText(s);
  if ( m_bOn ) {
    pDC->SetTextColor( m_OnForeClr );
    pDC->SetBkColor( m_OnBackClr );
    return m_BrushOn;
  }
  pDC->SetTextColor( m_OffForeClr );
  pDC->SetBkColor( m_OffBackClr );
  return m_BrushOff;
}

void CEraOnOffLabel::OnClicked() {
  SetOn( m_bOn ^ 1 );
}


void DrawLabel(CWnd* pParentWnd, int nIDCtl, LPDRAWITEMSTRUCT lpDIS, COLORREF clrText, COLORREF clrBack, BOOL fBold, BOOL fEraseBackground) {
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
  CWnd* pWnd = pParentWnd->GetDlgItem(nIDCtl);

  ASSERT(pWnd);

	CRect rc;
	pWnd->GetClientRect(rc);
	CString strText;
	pWnd->GetWindowText(strText);
	CBitmap bmp;


	///////////////////////////////////////////////////////
	//
	// Set up for double buffering...
	//
	CDC* pDCMem = NULL;
  CBitmap* pOldBitmap;

  pDCMem = new CDC;
	pDCMem->CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	pOldBitmap = pDCMem->SelectObject(&bmp);

	UINT nMode = pDCMem->SetBkMode(TRANSPARENT);


  LOGFONT lf;
  CFont* pFont = pWnd->GetFont();
  pFont->GetLogFont(&lf);
	lf.lfWeight = fBold ? FW_BOLD : FW_NORMAL;

  CFont font;
  font.CreateFontIndirect(&lf);

	CFont *pOldFont = pDCMem->SelectObject(&font);

  if ( fEraseBackground ) {
    EraseBkgndForDlgControl(pWnd, pDCMem, rc, false);
  }
  else {
    pDCMem->FillSolidRect(rc,clrBack);
  }


 	DWORD dwFlags = 0;
  LONG lStyle = pWnd->GetStyle();
	
	if (!(lStyle & SS_LEFTNOWORDWRAP))	dwFlags |= DT_WORDBREAK;

	if (lStyle & SS_LEFT)		dwFlags = DT_LEFT;

	if (lStyle & SS_RIGHT)	dwFlags = DT_RIGHT;

	if (lStyle & SS_CENTER)	dwFlags = DT_CENTER;

	// If the text centered make an assumtion that
	// the will want to center verticly as well
	if (lStyle & SS_CENTERIMAGE) {
		// dwFlags = DT_CENTER;

		// Apply 
		if (strText.Find("\r\n") == -1) {
			dwFlags |= DT_VCENTER;

			// And because DT_VCENTER only works with single lines
			dwFlags |= DT_SINGLELINE; 
		}
	}

	//
	// 3333   DDDDD
	//     3  D    D
	//   33   D     D    E F X 
	//     3  D    D
	// 3333   DDDDD
	//
	//

	COLORREF crText = pDCMem->SetTextColor(clrText);

  if ( lStyle & WS_DISABLED )
    crText = pDCMem->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
  else
    crText = pDCMem->SetTextColor(clrText);

  pDCMem->DrawText(strText,rc,dwFlags);
  if (lStyle & WS_BORDER) {
    //rc.InflateRect(1,1,1,1);
    pDCMem->FrameRect(rc, &CBrush(GetSysColor(COLOR_3DDKSHADOW)));
  }

/************************************** : by VK at 14.12.2004 23:58:49 **\
	if (m_bFont3d) {
		pDCMem->SetTextColor(RGB(255,255,255));

		if (m_3dType == Raised)
			rc.OffsetRect(-1,-1);
		else
			rc.OffsetRect(1,1);

		pDCMem->DrawText(strText,rc,dwFlags);
	}
\************************************** : by VK at 14.12.2004 23:58:53 **/

	// Restore DC's State
	pDCMem->SetBkMode(nMode);
	pDCMem->SelectObject(pOldFont);
	pDCMem->SetTextColor(crText);

  pDC->BitBlt(0,0,rc.Width(),rc.Height(),pDCMem,0,0,SRCCOPY);
  pDCMem->SelectObject(pOldBitmap);
	delete pDCMem;
}

void DrawGradientLabel(CWnd* pParentWnd, int nIDCtl, LPDRAWITEMSTRUCT lpDIS, COLORREF clrText, COLORREF clrBackLeft, COLORREF clrBackRight, BOOL fBold, BOOL fGradient) {
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
  CWnd* pWnd = pParentWnd->GetDlgItem(nIDCtl);

  ASSERT(pWnd);

	CRect rc;
	pWnd->GetClientRect(rc);
	CString strText;
	pWnd->GetWindowText(strText);
	CBitmap bmp;


	///////////////////////////////////////////////////////
	//
	// Set up for double buffering...
	//
	CDC* pDCMem = NULL;
  CBitmap* pOldBitmap;

  pDCMem = new CDC;
	pDCMem->CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	pOldBitmap = pDCMem->SelectObject(&bmp);

	UINT nMode = pDCMem->SetBkMode(TRANSPARENT);
  COLORREF crText;
  if ( pWnd->GetStyle() & WS_DISABLED ) {
    crText = pDCMem->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
  }
  else {
    crText = pDCMem->SetTextColor(clrText);
  }

  LOGFONT lf;
  CFont* pFont = pWnd->GetFont();
  pFont->GetLogFont(&lf);
	lf.lfWeight = fBold ? FW_BOLD : FW_NORMAL;

  CFont font;
  font.CreateFontIndirect(&lf);

	CFont *pOldFont = pDCMem->SelectObject(&font);

  if ( fGradient ) {
    DrawGradient(pDCMem, rc, clrBackLeft, clrBackRight, TRUE, TRUE);
  }
  else
    pDCMem->FillSolidRect(rc,clrBackLeft);

 	DWORD dwFlags = 0;
	
	if (!(pWnd->GetStyle() & SS_LEFTNOWORDWRAP))
		dwFlags |= DT_WORDBREAK;

	if (pWnd->GetStyle() & SS_LEFT)
		dwFlags = DT_LEFT;

	if (pWnd->GetStyle() & SS_RIGHT)
		dwFlags = DT_RIGHT;

	if (pWnd->GetStyle() & SS_CENTER)
		dwFlags = DT_CENTER;

	// If the text centered make an assumtion that
	// the will want to center verticly as well
	if (pWnd->GetStyle() & SS_CENTERIMAGE) {
		// dwFlags = DT_CENTER;

		// Apply 
		if (strText.Find("\r\n") == -1) {
			dwFlags |= DT_VCENTER;

			// And because DT_VCENTER only works with single lines
			dwFlags |= DT_SINGLELINE; 
		}
	}

	//
	// 3333   DDDDD
	//     3  D    D
	//   33   D     D    E F X 
	//     3  D    D
	// 3333   DDDDD
	//
	//
  pDCMem->DrawText(strText,rc,dwFlags);
  LONG lStyle = GetWindowLong(pWnd->m_hWnd, GWL_STYLE);
  if (lStyle & WS_BORDER) {
    //rc.InflateRect(1,1,1,1);
    pDCMem->FrameRect(rc, &CBrush(GetSysColor(COLOR_3DDKSHADOW)));
  }


	// Restore DC's State
	pDCMem->SetBkMode(nMode);
	pDCMem->SelectObject(pOldFont);
	pDCMem->SetTextColor(crText);

  pDC->BitBlt(0,0,rc.Width(),rc.Height(),pDCMem,0,0,SRCCOPY);
  pDCMem->SelectObject(pOldBitmap);
	delete pDCMem;
}
