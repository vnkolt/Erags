//
// BkgndCtrl.cpp
// 
#include "stdafx.h"
#include "BtnST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "BkgndCtrl.h"
#include "NewMenu.h"


COLORREF g_clrBkgnd;
CBrush   g_brBkgnd;

void SetButtonSTColors(CWnd* pParent, BOOL bRepaint/*=TRUE*/) {
  CWnd* pWnd = pParent->GetWindow(GW_CHILD);
  while ( pWnd ) {
    if ( pWnd->IsKindOf(RUNTIME_CLASS(CButtonST)) ) {
/************************************** : by VK 24.12.2004 at 13:14:01 **\
      ((CButtonST*)pWnd)->SetColor(CButtonST::BTNST_COLOR_BK_IN, g_clrBkgnd, bRepaint);
      ((CButtonST*)pWnd)->SetColor(CButtonST::BTNST_COLOR_BK_OUT, g_clrBkgnd, bRepaint);
      ((CButtonST*)pWnd)->SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, g_clrBkgnd, bRepaint);
      //((CButtonST*)pWnd)->SendMessage(WM_SYSCOLORCHANGE);
\************************************** : by VK 24.12.2004 at 13:14:09 **/
      ((CButtonST*)pWnd)->Invalidate();
    }
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
}

void SubclassStatics(CWnd* pParent, CPtrArray& array) {
  CWnd* pWnd = pParent->GetWindow(GW_CHILD); 
  int newID = IDC_STATIC+2000;
  while ( pWnd ) {
    if ( IDC_STATIC==pWnd->GetDlgCtrlID() ) {
      pWnd->SetDlgCtrlID(newID);
      CStaticBG* pStatic = new CStaticBG();
      pStatic->SubclassDlgItem(newID, pParent);
      array.Add( pStatic );
      newID++;
    }
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
}
void ReleaseStatics(CPtrArray& array) {
  for( int i(0); i < array.GetSize(); i++ ) {
    CStaticBG* pStatic = (CStaticBG*)array.GetAt(i);
    delete pStatic;
  }
}
void CreateBrushes(CWnd* pParent, CMapPtrToPtr& Brushes) {
  CWnd*   pWnd  = pParent->GetWindow(GW_CHILD);
  CDC*    pDC   = pParent->GetDC();
  CBrush* pMenuBrush = GetMenuBarBrush();

  CRect rcParent;
  pParent->GetClientRect(&rcParent);

  CDC tempDC;
  tempDC.CreateCompatibleDC(pDC);
  CBitmap tempBitmap;
  tempBitmap.CreateCompatibleBitmap(pDC, rcParent.Width(), rcParent.Height());
  CBitmap* pOldBitmap = tempDC.SelectObject(&tempBitmap);
  tempDC.FillRect(&rcParent, pMenuBrush);

  while ( pWnd ) {
    if ( pWnd->GetDlgCtrlID() != IDC_STATIC ) {
      CRect rWnd;
      pWnd->GetWindowRect(&rWnd);
      pParent->ScreenToClient(&rWnd);

      CDC memDC;
      memDC.CreateCompatibleDC(pDC);
      CBitmap bitmap;
      bitmap.CreateCompatibleBitmap(pDC, rWnd.Width(), rWnd.Height());
      CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
      memDC.BitBlt(0,0, rWnd.Width(), rWnd.Height(), &tempDC, rWnd.left, rWnd.top, SRCCOPY);
      memDC.SelectObject(pOldBitmap);

      CBrush* pNewBrush = new CBrush();
      pNewBrush->CreatePatternBrush(&bitmap);
      Brushes.SetAt((void*)pWnd->GetDlgCtrlID(), pNewBrush);

      pWnd = pWnd->GetWindow(GW_HWNDNEXT);
    }
  }
  tempDC.SelectObject(pOldBitmap);
  pParent->ReleaseDC(pDC);
}
void ReleaseBrushes(CMapPtrToPtr& Brushes) {
  POSITION pos = Brushes.GetStartPosition();
  while ( pos ) {
    CBrush* pBrush = NULL;
    void* key;
    Brushes.GetNextAssoc(pos, key, (void*&)pBrush);
    if ( pBrush ) {
      pBrush->DeleteObject();
      delete pBrush;
    }
  }
  Brushes.RemoveAll();
}
/////////////////////////////////////////////////////////////////////////////
// CDialogBG
IMPLEMENT_DYNCREATE(CStaticBG, CStatic)
BEGIN_MESSAGE_MAP(CStaticBG, CStatic)
	//{{AFX_MSG_MAP(CStaticBG)
	ON_WM_ERASEBKGND()
  ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CDialogBG::~CDialogBG() {
  ReleaseStatics(m_Statics);
  ReleaseBrushes(m_Brushes);
}
/////////////////////////////////////////////////////////////////////////////
// CStaticBG message handlers
BOOL CStaticBG::OnEraseBkgnd(CDC* pDC) {
  if ( m_fGradientFill ) {
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    CBrush*pBrush = GetMenuBarBrush();
    CRect rc, rBrush;
    GetClientRect(&rc);
    GetWindowRect(&rBrush);
    GetParent()->ScreenToClient(&rBrush);
    CBrush* pOldBrush = memDC.SelectObject(pBrush);
    pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, rBrush.left, rBrush.top, SRCCOPY);
    memDC.SelectObject(pOldBrush);
    //::SetBrushOrgEx(pDC->m_hDC, rBrush.left, rBrush.top, NULL);
    //pDC->SetBrushOrg(rBrush.left, rBrush.top);
    //pDC->FillRect(rc,pBrush);
  }
  else {
    CRect clipRect;
    pDC->GetClipBox(&clipRect);
    pDC->FillSolidRect(&clipRect, g_clrBkgnd);
  }
	return TRUE;
}
void CStaticBG::OnPaint() {
//  Default();
	CPaintDC dc(this); // device context for painting

	// Where to draw text
	CRect client_rect;
	GetClientRect(client_rect);

	// Get the caption
	CString szText;
	GetWindowText(szText);

	// Get the font
	CFont *pFont, *pOldFont;
	pFont = GetFont();
	pOldFont = dc.SelectObject(pFont);

	// Map "Static Styles" to "Text Styles"
#define MAP_STYLE(src, dest) if(dwStyle & (src)) dwText |= (dest)
#define NMAP_STYLE(src, dest) if(!(dwStyle & (src))) dwText |= (dest)

	DWORD dwStyle = GetStyle(), dwText = 0;

	MAP_STYLE(	SS_RIGHT,			DT_RIGHT					);
	MAP_STYLE(	SS_CENTER,			DT_CENTER					);
	MAP_STYLE(	SS_CENTERIMAGE,		DT_VCENTER | DT_SINGLELINE	);
	MAP_STYLE(	SS_NOPREFIX,		DT_NOPREFIX					);
	MAP_STYLE(	SS_WORDELLIPSIS,	DT_WORD_ELLIPSIS			);
	MAP_STYLE(	SS_ENDELLIPSIS,		DT_END_ELLIPSIS				);
	MAP_STYLE(	SS_PATHELLIPSIS,	DT_PATH_ELLIPSIS			);

	NMAP_STYLE(	SS_LEFTNOWORDWRAP |
				SS_CENTERIMAGE |
				SS_WORDELLIPSIS |
				SS_ENDELLIPSIS |
				SS_PATHELLIPSIS,	DT_WORDBREAK				);

	// Set transparent background
	dc.SetBkMode(TRANSPARENT);

	// Draw the text
	dc.DrawText(szText, client_rect, dwText);

	// Select old font
	dc.SelectObject(pOldFont);
}


/////////////////////////////////////////////////////////////////////////////
// CDialogBG
IMPLEMENT_DYNCREATE(CDialogBG, CDialog)
BEGIN_MESSAGE_MAP(CDialogBG, CDialog)
	//{{AFX_MSG_MAP(CDialogBG)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogBG message handlers
BOOL CDialogBG::OnInitDialog() {
  BOOL bResult = CDialog::OnInitDialog();
  if ( bResult ) {
    SubclassStatics(this, m_Statics);
    if ( g_Shell >= WinXP ) {
      CreateBrushes(this, m_Brushes);
    }
  }
  return bResult;
}
BOOL CDialogBG::OnEraseBkgnd(CDC* pDC) {
  if ( m_fGradientFill ) {
    CBrush*pBrush = GetMenuBarBrush();
    CRect rc;
    GetClientRect(&rc);
    pDC->FillRect(rc,pBrush);
  }
  else {
    CRect clipRect;
    pDC->GetClipBox(&clipRect);
    pDC->FillSolidRect(&clipRect, g_clrBkgnd);
  }
	return TRUE;
}
HBRUSH CDialogBG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
  switch (nCtlColor) {
    case CTLCOLOR_BTN    :
    case CTLCOLOR_STATIC :  {
        pDC->SetBkMode(TRANSPARENT);
        CBrush* pBrush = NULL;
        m_Brushes.Lookup((void*)pWnd->GetDlgCtrlID(), (void*&)pBrush);
        if ( pBrush )
          return (HBRUSH)pBrush->m_hObject;
      }
      return (HBRUSH)GetMenuBarBrush()->m_hObject;
  }
/*
	
	switch (nCtlColor) {
    case CTLCOLOR_BTN    :
    case CTLCOLOR_STATIC : {
      CRect r;
      pWnd->GetWindowRect(&r);
      ScreenToClient(&r);
      pDC->SetBrushOrg(r.left, r.right);
      pDC->SetBkMode(TRANSPARENT);
      return (HBRUSH)GetMenuBarBrush()->m_hObject;
    }
    //return g_brBkgnd;
  }
*/
  return hbr;
}
void CDialogBG::OnSysColorChange() {
  SetButtonSTColors(this, TRUE);
	CDialog::OnSysColorChange();
}

/////////////////////////////////////////////////////////////////////////////
// CFormViewBG
IMPLEMENT_DYNAMIC(CFormViewBG, CFormView)
BEGIN_MESSAGE_MAP(CFormViewBG, CFormView)
	//{{AFX_MSG_MAP(CFormViewBG)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_SYSCOLORCHANGE()
  ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFormViewBG::~CFormViewBG() {
  ReleaseStatics(m_Statics);
  ReleaseBrushes(m_Brushes);
}
/////////////////////////////////////////////////////////////////////////////
// CFormViewBG message handlers
void CFormViewBG::OnInitialUpdate() {
  CFormView::OnInitialUpdate();
  if ( m_Statics.GetSize()==0 ) {
    SubclassStatics(this, m_Statics);
    if ( g_Shell >= WinXP ) {
      CreateBrushes(this, m_Brushes);
    }
  }
}
BOOL CFormViewBG::OnEraseBkgnd(CDC* pDC) {
  if ( m_fGradientFill ) {
    CBrush*pBrush = GetMenuBarBrush();
    CRect rc;
    GetClientRect(&rc);
    pDC->FillRect(rc,pBrush);
  }
  else {
    CRect clipRect;
    pDC->GetClipBox(&clipRect);
    pDC->FillSolidRect(&clipRect, g_clrBkgnd);
  }
	return TRUE;
}
HBRUSH CFormViewBG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
  switch (nCtlColor) {
    case CTLCOLOR_BTN    :
    case CTLCOLOR_STATIC :  {
        pDC->SetBkMode(TRANSPARENT);
        CBrush* pBrush = NULL;
        m_Brushes.Lookup((void*)pWnd->GetDlgCtrlID(), (void*&)pBrush);
        if ( pBrush )
          return (HBRUSH)pBrush->m_hObject;
      }
      return (HBRUSH)GetMenuBarBrush()->m_hObject;
  }
  return hbr;
}
void CFormViewBG::OnSysColorChange() {
  SetButtonSTColors(this, TRUE);
	CFormView::OnSysColorChange();
}
void CFormViewBG::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS) {
  if ( ODT_BUTTON==lpDIS->CtlType ) {
    CWnd* pWnd = CWnd::FromHandle(lpDIS->hwndItem);
    if ( pWnd->IsKindOf(RUNTIME_CLASS(CButtonST)) ) {
      ((CButtonST*)pWnd)->DrawItem(lpDIS);
      return;
    }
  }
  CFormView::OnDrawItem(nIDCtl, lpDIS);
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageBG
IMPLEMENT_DYNCREATE(CPropertyPageBG, CPropertyPage)
BEGIN_MESSAGE_MAP(CPropertyPageBG, CPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageBG)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CPropertyPageBG::~CPropertyPageBG() {
  ReleaseStatics(m_Statics);
  ReleaseBrushes(m_Brushes);
}
/////////////////////////////////////////////////////////////////////////////
// CPropertyPageBG message handlers
HBRUSH CPropertyPageBG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
  HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
  switch (nCtlColor) {
    case CTLCOLOR_BTN    :
    case CTLCOLOR_STATIC :  {
        pDC->SetBkMode(TRANSPARENT);
        CBrush* pBrush = NULL;
        m_Brushes.Lookup((void*)pWnd->GetDlgCtrlID(), (void*&)pBrush);
        if ( pBrush )
          return (HBRUSH)pBrush->m_hObject;
      }
      return (HBRUSH)GetMenuBarBrush()->m_hObject;
/*
    case CTLCOLOR_STATIC : {
      //CRect r;
      //pWnd->GetWindowRect(&r);
      //ScreenToClient(&r);
      //SetBrushOrgEx(pDC->m_hDC, r.left, r.right, NULL);
      pDC->SetBkMode(TRANSPARENT);
      return (HBRUSH)GetMenuBarBrush()->m_hObject;
    }
*/
    case CTLCOLOR_DLG    :
      return (HBRUSH)GetMenuBarBrush()->m_hObject;
  }
  return hbr;
}
BOOL CPropertyPageBG::OnEraseBkgnd(CDC* pDC) {
  if ( m_fGradientFill ) {
    CBrush*pBrush = GetMenuBarBrush();
    CRect rc;
    GetClientRect(&rc);
    pDC->FillRect(rc,pBrush);
  }
  else {
    CRect clipRect;
    pDC->GetClipBox(&clipRect);
    pDC->FillSolidRect(&clipRect, g_clrBkgnd);
  }
	return TRUE;
}
BOOL CPropertyPageBG::OnInitDialog() {
  BOOL bResult = CPropertyPage::OnInitDialog();
  if ( bResult ) {
    SubclassStatics(this, m_Statics);
    if ( g_Shell >= WinXP ) {
      CreateBrushes(this, m_Brushes);
    }
  }
  return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetBG
IMPLEMENT_DYNCREATE(CPropertySheetBG, CPropertySheet)
BEGIN_MESSAGE_MAP(CPropertySheetBG, CPropertySheet)
	//{{AFX_MSG_MAP(CPropertySheetBG)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CPropertySheetBG message handlers
BOOL CPropertySheetBG::OnInitDialog() {
  BOOL bResult = CPropertySheet::OnInitDialog();
  CTabCtrl* pTab = GetTabControl();
  if (pTab==NULL) {
    return FALSE;
  }	
  HWND hWnd = pTab->Detach();
  m_TabCtrl.SubclassWindow(hWnd);
  return bResult;
}
BOOL CPropertySheetBG::OnEraseBkgnd(CDC* pDC) {
  if ( m_fGradientFill ) {
    CBrush*pBrush = GetMenuBarBrush();
    CRect rc;
    GetClientRect(&rc);
    pDC->FillRect(rc,pBrush);
  }
  else {
    CRect clipRect;
    pDC->GetClipBox(&clipRect);
    pDC->FillSolidRect(&clipRect, g_clrBkgnd);
  }
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlBG
IMPLEMENT_DYNCREATE(CTabCtrlBG, CTabCtrl)
BEGIN_MESSAGE_MAP(CTabCtrlBG, CTabCtrl)
	//{{AFX_MSG_MAP(CTabCtrlBG)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CTabCtrlBG message handlers
BOOL CTabCtrlBG::OnEraseBkgnd(CDC* pDC) {
  if ( m_fGradientFill ) {
    CBrush*pBrush = GetMenuBarBrush();
    CRect rc;
    GetClientRect(&rc);
    pDC->FillRect(rc,pBrush);
  }
  else {
    CRect clipRect;
    pDC->GetClipBox(&clipRect);
    pDC->FillSolidRect(&clipRect, g_clrBkgnd);
  }
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CReBarBG
IMPLEMENT_DYNCREATE(CReBarBG, CReBar)
BEGIN_MESSAGE_MAP(CReBarBG, CReBar)
	//{{AFX_MSG_MAP(CReBarBG)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CReBarBG message handlers
BOOL CReBarBG::OnEraseBkgnd(CDC* pDC) {
  if ( m_fGradientFill ) {
    CBrush*pBrush = GetMenuBarBrush();
    CRect rClipBox;
    pDC->GetClipBox(&rClipBox);
    pDC->FillRect(&rClipBox,pBrush);
  }
  else {
    CRect clipRect;
    pDC->GetClipBox(&clipRect);
    pDC->FillSolidRect(&clipRect, g_clrBkgnd);
  }
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDialogBarBG
IMPLEMENT_DYNCREATE(CDialogBarBG, CDialogBar)
CDialogBarBG::CDialogBarBG() {
  m_fGradientFill = TRUE;
}
CDialogBarBG::~CDialogBarBG() {
  ReleaseStatics(m_Statics);
  ReleaseBrushes(m_Brushes);
}

BEGIN_MESSAGE_MAP(CDialogBarBG, CDialogBar)
	//{{AFX_MSG_MAP(CDialogBarBG)
	ON_WM_SYSCOLORCHANGE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDialogBarBG::SetColors(BOOL bRepaint/*=TRUE*/) {
  SetButtonSTColors(this, TRUE);
}
/////////////////////////////////////////////////////////////////////////////
// CDialogBarBG message handlers
BOOL CDialogBarBG::Create(CWnd* pParentWnd, LPCTSTR lpszTemplateName, UINT nStyle, UINT nID) {
  BOOL bResult = CDialogBar::Create(pParentWnd, lpszTemplateName, nStyle, nID);
  if ( bResult ) {
    SubclassStatics(this, m_Statics);
  }
  return bResult;
}
BOOL CDialogBarBG::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID) {
  BOOL bResult = CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);
  if ( bResult ) {
    SubclassStatics(this, m_Statics);
  }
  return bResult;
}
BOOL CDialogBarBG::OnEraseBkgnd(CDC* pDC) {
  if ( m_fGradientFill ) {
    CBrush*pBrush = GetMenuBarBrush();
    CRect rClipBox;
    pDC->GetClipBox(&rClipBox);
    pDC->FillRect(&rClipBox,pBrush);
    //SetColors(TRUE);
  }
  else {
    CRect clipRect;
    pDC->GetClipBox(&clipRect);
    pDC->FillSolidRect(&clipRect, g_clrBkgnd);
  }
	return TRUE;
}
HBRUSH CDialogBarBG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	HBRUSH hbr = CDialogBar::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Change any attributes of the DC here
/*
  if ( CTLCOLOR_STATIC==nCtlColor || CTLCOLOR_BTN==nCtlColor ) {
    pDC->SetBkMode(TRANSPARENT);
    return (HBRUSH)GetMenuBarBrush()->m_hObject;
    //return g_brBkgnd;
  }
*/
  switch (nCtlColor) {
    case CTLCOLOR_BTN    :
    case CTLCOLOR_STATIC :  {
        pDC->SetBkMode(TRANSPARENT);
        CBrush* pBrush = NULL;
        m_Brushes.Lookup((void*)pWnd->GetDlgCtrlID(), (void*&)pBrush);
        if ( pBrush )
          return (HBRUSH)pBrush->m_hObject;
      }
      return (HBRUSH)GetMenuBarBrush()->m_hObject;
  }

	// TODO: Return a different brush if the default is not desired
	return hbr;
}
void CDialogBarBG::SetColors(BOOL bRepaint/*=TRUE*/) {
  SetButtonSTColors(this, TRUE);
  if ( g_Shell >= WinXP ) {
    ReleaseBrushes(m_Brushes);
    CreateBrushes(this, m_Brushes);
  }
	CDialogBar::OnSysColorChange();
}
