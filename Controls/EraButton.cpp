// EraButton.cpp : implementation file
//
#include "stdafx.h"
#include "EraButton.h"
#include "NewMenu.h"

void SendKeys(BYTE bKey, BYTE bShiftKey);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/************************************** : by VK at 21.05.2005 12:05:00 **\
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
\************************************** : by VK at 21.05.2005 12:05:03 **/

/////////////////////////////////////////////////////////////////////////////
// CEraButton

CEraButton::CEraButton() {
}

CEraButton::~CEraButton() {
}


BEGIN_MESSAGE_MAP(CEraButton, CButton)
	//{{AFX_MSG_MAP(CEraButton)
//  ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraButton message handlers
BOOL CEraButton::PreTranslateMessage(MSG* pMsg) {
	if ( pMsg->message==WM_KEYDOWN && VK_RETURN==pMsg->wParam) {
    pMsg->wParam = VK_TAB;
  }
	return CButton::PreTranslateMessage(pMsg);
}

BOOL CEraButton::OnEraseBkgnd(CDC * pDC) {
  if (this!=GetFocus() ) {
    CRect r;
    GetClientRect(&r);
    EraseBkgndForDlgControl(this, pDC, r);
    return TRUE;
  }
  return CButton::OnEraseBkgnd(pDC);
}
void CEraButton::OnSetFocus(CWnd* pOldWnd) {
	CButton::OnSetFocus(pOldWnd);
	InvalidateRect(NULL);
  CWnd* pParent = GetParent();
  if ( pParent )
    pParent->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_SETFOCUS), (LPARAM)m_hWnd);
}

void CEraButton::OnKillFocus(CWnd* pNewWnd) {
	CButton::OnKillFocus(pNewWnd);
	InvalidateRect(NULL);
}

void CEraButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) {
  COLORREF clrBk, clrText;

  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
  CRect rText = lpDIS->rcItem;

  rText.DeflateRect(2, 2, 2, 2);

  CString strText; GetWindowText(strText);

  BOOL fFocus;

  if (lpDIS->itemState & (ODS_FOCUS|ODS_SELECTED)) {
    clrText =  g_clrFocusForeColor;
    clrBk = g_clrFocusBackColor;
    fFocus = TRUE;
  }
  else {
    clrText =  g_clrForeColor;
    clrBk = g_clrBackColor;
    fFocus = FALSE;
  }
 
  pDC->SetBkColor(clrBk);
  if ( IsWindowEnabled() )
    pDC->SetTextColor(clrText);
  else
    pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));

  if ( fFocus )
    pDC->FillSolidRect(rText, clrBk);
  else {
    OnEraseBkgnd(pDC);
  }

  if (lpDIS->itemState & ODS_SELECTED)
    rText.DeflateRect(1, 1);
  pDC->DrawText(strText, rText, DT_CENTER|DT_VCENTER);

  UINT nEdge = BDR_RAISEDOUTER|BDR_RAISEDINNER;
  pDC->DrawEdge(&lpDIS->rcItem, nEdge, BF_RECT);
  if (lpDIS->itemState & ODS_FOCUS) {
    rText.DeflateRect(1, 1, 1, 1);
    pDC->DrawFocusRect(&rText);
  }
}

/////////////////////////////////////////////////////////////////////////////
// CEraBitmapButton
IMPLEMENT_DYNAMIC(CEraBitmapButton, CBitmapButton)
BEGIN_MESSAGE_MAP(CEraBitmapButton, CBitmapButton)
	//{{AFX_MSG_MAP(CEraBitmapButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CEraBitmapButton::CEraBitmapButton() {
}

BOOL CEraBitmapButton::PreTranslateMessage(MSG* pMsg) {
  if ( pMsg->message==WM_KEYDOWN ) {
    if ( pMsg->wParam==VK_RETURN ) {
      pMsg->wParam = VK_TAB;
    }
  }
  return CBitmapButton::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// CEraToggleButton
CEraToggleButton::CEraToggleButton() {
  m_clrForeOn = m_clrForeOff = GetSysColor(COLOR_BTNTEXT);
  m_clrBackOn = m_clrBackOff = GetSysColor(COLOR_3DFACE);
  m_bOn = m_bFocusFore = m_bFocusBack = FALSE;
}

CEraToggleButton::~CEraToggleButton() {
}

void CEraToggleButton::SetFont(LPCTSTR szFontName, LONG lfHeight, LONG lfWeight, BYTE lfItalic) {
  LOGFONT lf;
	CFont* pFont = GetFont();
	if(pFont && pFont->GetLogFont(&lf)) {
    m_Font.DeleteObject();
	  lf.lfHeight = lfHeight;
	  lf.lfWeight = lfWeight;
    lf.lfItalic = lfItalic;
    lf.lfCharSet = RUSSIAN_CHARSET;

		strcpy(lf.lfFaceName, szFontName);
		m_Font.CreateFontIndirect(&lf);
    if ( m_hWnd )
      CWnd::SetFont(&m_Font);
  }
}

void CEraToggleButton::SetText(LPCTSTR szOnText, LPCTSTR szOffText) {
  m_strOnText = szOnText;
  m_strOffText = szOffText;
}

void CEraToggleButton::SetBackColor(COLORREF clrOn, COLORREF clrOff, bool bForFocus/*=false*/) {
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

void CEraToggleButton::SetForeColor(COLORREF clrOn, COLORREF clrOff, bool bForFocus/*=false*/) {
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

BEGIN_MESSAGE_MAP(CEraToggleButton, CEraButton)
	//{{AFX_MSG_MAP(CEraToggleButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
  ON_MESSAGE(BM_GETCHECK, OnGetCheck)
  ON_MESSAGE(BM_SETCHECK, OnSetCheck)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraToggleButton message handlers
void CEraToggleButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) {
  if ( m_strOffText.IsEmpty() ) {
    GetWindowText(m_strOffText);
    m_strOnText = m_strOffText;
    //m_strOnText += _T(" v°"); // \/^ |
  }
  CBrush brYellow;
  CBrush brGray;
  COLORREF  clrHi = GetSysColor(COLOR_HIGHLIGHT),
            clrHiText = GetSysColor(COLOR_HIGHLIGHTTEXT),
            clr3DLight = GetSysColor(COLOR_BTNHILIGHT),
            clr3DShadow = GetSysColor(COLOR_BTNSHADOW),
            clrFocus = 0xFFFFFF,
            clrBk, clrText;

  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
  CRect rText = lpDIS->rcItem;

  rText.DeflateRect(2, 2, 2, 2);

  CString strText;

  BOOL fFocus(FALSE);

  if ( m_bOn ) {  // button is checked
    strText = m_strOnText;
    clrBk = m_clrBackOn;
    clrText = m_clrForeOn;
  }
  else {
    strText = m_strOffText;
    clrBk = m_clrBackOff;
    clrText = m_clrForeOff;
  }
  if (lpDIS->itemState & (ODS_FOCUS|ODS_SELECTED)) {
    fFocus = TRUE;
    if ( m_bFocusFore )
      clrText =  m_bOn ? m_clrFocusForeOn : m_clrFocusForeOff;
    if ( m_bFocusBack )
      clrBk = m_bOn ? m_clrFocusBackOn : m_clrFocusBackOff;
    else
      clrBk = clrFocus;
  }
  //pOldFont = pDC->SelectObject(pFont);
 
  pDC->SetBkColor(clrBk);
  if ( IsWindowEnabled() )
    pDC->SetTextColor(clrText);
  else
    pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));

  //pDC->SetTextAlign(TA_CENTER);
  pDC->SetBkMode(TRANSPARENT);
  if ( fFocus )
    pDC->FillSolidRect(rText, clrBk);
  else
    OnEraseBkgnd(pDC);
    
  pDC->DrawText(strText, rText, DT_CENTER|DT_VCENTER);
  //pDC->ExtTextOut(rText.left+2, rText.top+2, ETO_CLIPPED|ETO_OPAQUE, &rText, strText, strText.GetLength(), NULL);

  UINT nEdge = m_bOn ? BDR_SUNKENINNER|BDR_SUNKENOUTER
                     : BDR_RAISEDOUTER|BDR_RAISEDINNER;
  pDC->DrawEdge(&lpDIS->rcItem, nEdge, BF_RECT);

  if (lpDIS->itemState & ODS_FOCUS) {
    rText.DeflateRect(1, 1, 1, 1);
    pDC->DrawFocusRect(&rText);
  }
  //else
  //  pDC->Draw3dRect(&lpDIS->rcItem, clr3DLight, clr3DShadow);
}

void CEraToggleButton::OnClicked() {
	// TODO: Add your control notification handler code here
  m_bOn ^= 1;
  SetCheck( m_bOn );
  InvalidateRect(NULL);
}
LRESULT CEraToggleButton::OnGetCheck(WPARAM, LPARAM) {
  return (LRESULT)( m_bOn ? BST_CHECKED : BST_UNCHECKED);
}

LRESULT CEraToggleButton::OnSetCheck(WPARAM wParam, LPARAM) {
  if ( wParam==(WPARAM)BST_CHECKED)
    m_bOn = TRUE;
  else
    m_bOn = FALSE;
  InvalidateRect(NULL);
  return (LRESULT)0;
}

void CEraToggleButton::OnSetFocus(CWnd* pOldWnd) {
  GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_SETFOCUS), (LPARAM)m_hWnd);
	CEraButton::OnSetFocus(pOldWnd);
	InvalidateRect(NULL);
}

void CEraToggleButton::OnKillFocus(CWnd* pNewWnd) {
  GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_KILLFOCUS), (LPARAM)m_hWnd);
	CEraButton::OnKillFocus(pNewWnd);
	InvalidateRect(NULL);
}


/************************************** : by VK at 21.05.2005 12:04:00 **\

/////////////////////////////////////////////////////////////////////////////
// CEraMultiStateButton
BEGIN_MESSAGE_MAP(CEraMultiStateButton, CEraButton)
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
  m_nCurrentState = nIndex; 
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
/////////////////////////////////////////////////////////////////////////////
// CEraMultiStateButton message handlers
void CEraMultiStateButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) {
  CBrush brYellow;
  CBrush brGray;
  COLORREF  clrHi = GetSysColor(COLOR_HIGHLIGHT),
            clrHiText = GetSysColor(COLOR_HIGHLIGHTTEXT),
            clr3DLight = GetSysColor(COLOR_BTNHILIGHT),
            clr3DShadow = GetSysColor(COLOR_BTNSHADOW),
            clrFocus = 0xFFFFFF,
            clrBk = m_clrBack,
            clrText = m_clrFore;

  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
  CRect rText = lpDIS->rcItem;

  rText.DeflateRect(2, 2, 2, 2);

  if ( m_StateNames.GetSize()==0 ) {
    m_StateNames.Add("");
  }
  if ( m_nCurrentState >= m_StateNames.GetSize() )
    m_nCurrentState = 0;
  CString strText = m_StateNames.GetAt(m_nCurrentState);

  clrText = (COLORREF)m_ForeColors.GetAt(m_nCurrentState);

  BOOL fFocus(FALSE);

  if (lpDIS->itemState & (ODS_FOCUS|ODS_SELECTED)) {
    clrBk = clrFocus;
    fFocus = TRUE;
  }
  else {
    fFocus = FALSE;
  }
  if ( fFocus )
    pDC->FillSolidRect(rText, clrBk);
  else {
    OnEraseBkgnd(pDC);
  }

  //pOldFont = pDC->SelectObject(pFont);
 
  pDC->SetBkColor(clrBk);
  if ( IsWindowEnabled() )
    pDC->SetTextColor(clrText);
  else
    pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));

  pDC->SetBkMode(TRANSPARENT);
  pDC->DrawText(strText, rText, DT_CENTER|DT_VCENTER);

  pDC->DrawEdge(&lpDIS->rcItem, BDR_RAISEDINNER, BF_RECT);
  if (lpDIS->itemState & ODS_FOCUS) {
    CRect r = lpDIS->rcItem;
    r.DeflateRect(1, 1, 1, 1);
    pDC->DrawFocusRect(&r);
  }
}

void CEraMultiStateButton::OnClicked() {
  if ( ++m_nCurrentState == m_StateNames.GetSize() )
    m_nCurrentState = 0;
  InvalidateRect(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CEraPassportButton
CEraPassportButton::CEraPassportButton() {
  AddState(0, _T("паспорт") );
  AddState(1, _T("ЗЗП") );
  AddState(2, _T("Св. н-ня") );
  AddState(3, _T("ТПП") );
}

/////////////////////////////////////////////////////////////////////////////
// CEraMWPassportButton
CEraMWPassportButton::CEraMWPassportButton() {
  AddColorState(0, g_clrMaleForeColor, _T("паспорт") );
  AddColorState(1, g_clrMaleForeColor, _T("ЗЗП") );
  AddColorState(2, g_clrMaleForeColor, _T("Св. н-ня") );
  AddColorState(3, g_clrMaleForeColor, _T("ТПП") );

  AddColorState(4, g_clrFemaleForeColor, _T("паспорт") );
  AddColorState(5, g_clrFemaleForeColor, _T("ЗЗП") );
  AddColorState(6, g_clrFemaleForeColor, _T("Св. н-ня") );
  AddColorState(7, g_clrFemaleForeColor, _T("ТПП") );
}

\************************************** : by VK at 21.05.2005 12:04:11 **/