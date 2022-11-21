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
#include "MemDC.h"


extern COLORREF g_clrLeft;
extern COLORREF g_clrRight;
extern BOOL     g_fUseGradient;

BOOL Is_IDC_STATIC(int id) {
  return (IDC_STATIC==id || 0xFFFF==id);
}
void SetButtonSTColors(CWnd* pParent, BOOL bRepaint/*=TRUE*/) {
  CWnd* pWnd = pParent->GetWindow(GW_CHILD);
  while ( pWnd ) {
    if ( pWnd->IsKindOf(RUNTIME_CLASS(CButtonST)) ) {
/************************************** : by VK 24.12.2004 at 13:14:01 **\
      ((CButtonST*)pWnd)->SetColor(CButtonST::BTNST_COLOR_BK_IN, g_clrLeft, bRepaint);
      ((CButtonST*)pWnd)->SetColor(CButtonST::BTNST_COLOR_BK_OUT, g_clrLeft, bRepaint);
      ((CButtonST*)pWnd)->SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, g_clrLeft, bRepaint);
      //((CButtonST*)pWnd)->SendMessage(WM_SYSCOLORCHANGE);
\************************************** : by VK 24.12.2004 at 13:14:09 **/
      ((CButtonST*)pWnd)->Invalidate();
    }
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
}
void SubclassStatics(CWnd* pParent, CPtrArray& array) {
  CWnd* pWnd = pParent->GetWindow(GW_CHILD); 
  int newID = 40000;
  while ( pWnd ) {
    if ( Is_IDC_STATIC(pWnd->GetDlgCtrlID()) ) {
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
/////////////////////////////////////////////////////////////////////////////
// CStaticBG
IMPLEMENT_DYNCREATE(CStaticBG, CStatic)
BEGIN_MESSAGE_MAP(CStaticBG, CStatic)
	//{{AFX_MSG_MAP(CStaticBG)
	ON_WM_ERASEBKGND()
  ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CStaticBG message handlers
BOOL CStaticBG::OnEraseBkgnd(CDC* pDC) {
  CRect r;
  GetClientRect(&r);
  CWnd* pParent = GetParent();
  if ( pParent->IsKindOf(RUNTIME_CLASS(CFormView)) || pParent->IsKindOf(RUNTIME_CLASS(CPropertyPage)) ) {
    GradientEraseBkgnd(this, GetParent(), pDC, r);
  }
  else {
    EraseBkgndForDlgControl(this, pDC, r);
  }
	return TRUE;
}

void CStaticBG::OnPaint() {
	CPaintDC dc(this); // device context for painting
/************************************** : by VK at 23.11.2005 1:13:54 **\
  CPaintDC PaintDC(this); // device context for painting
  CMemDC dc(&PaintDC);
\************************************** : by VK at 23.11.2005 1:13:57 **/
	// Where to draw text
	CRect client_rect;
	GetClientRect(client_rect);

	// Get the caption
	CString szText;
	GetWindowText(szText);

	// Get the font
	CFont *pFont, *pOldFont;
	pFont = GetFont();
  if ( pFont )
	  pOldFont = dc.SelectObject(pFont);

	// Map "Static Styles" to "Text Styles"
#define MAP_STYLE(src, dest) if(dwStyle & (src)) dwText |= (dest)
#define NMAP_STYLE(src, dest) if(!(dwStyle & (src))) dwText |= (dest)

	DWORD dwStyle = GetStyle(), dwText = 0;

	MAP_STYLE(	SS_RIGHT,			    DT_RIGHT					);
	MAP_STYLE(	SS_CENTER,			  DT_CENTER					);
	MAP_STYLE(	SS_CENTERIMAGE,	  DT_VCENTER | DT_SINGLELINE	);
	MAP_STYLE(	SS_NOPREFIX,		  DT_NOPREFIX					);
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
  if ( dwStyle & WS_DISABLED ) {
    dc.SetTextColor( GetSysColor(COLOR_GRAYTEXT) );
    dc.DrawText(szText, client_rect, dwText);
/************************************** : by VK at 18.11.2005 0:53:11 **\
    client_rect.left++;
    client_rect.top++;
    dc.SetTextColor(clr);
    dc.DrawText(szText, client_rect, dwText);
\************************************** : by VK at 18.11.2005 0:53:15 **/
  }
  else {
/************************************** : by VK at 12.11.2005 13:59:01 **\
    dc.DrawState(CPoint(client_rect.left, client_rect.top),
                 CSize(client_rect.Width(), client_rect.Height()),
                 (LPCTSTR)szText, (UINT)DSS_NORMAL, TRUE, 0, (HBRUSH)NULL);//, int nTextLen = 0, CBrush* pBrush = NULL );
\************************************** : by VK at 12.11.2005 13:59:06 **/
	  dc.DrawText(szText, client_rect, dwText);
  }


  HICON hIcon = GetIcon();
  if ( hIcon ) {
    dc.DrawIcon(client_rect.left, client_rect.top, hIcon);
  }
	// Select old font
  if ( pFont )
	  dc.SelectObject(pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// CButtonBG message handlers
IMPLEMENT_DYNCREATE(CButtonBG, CButton)
BEGIN_MESSAGE_MAP(CButtonBG, CButton)
	//{{AFX_MSG_MAP(CButtonBG)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CButtonBG message handlers
BOOL CButtonBG::OnEraseBkgnd(CDC* pDC) {
  pDC->SetBkMode(TRANSPARENT);
  CRect r;
  GetClientRect(&r);
  EraseBkgndForDlgControl(this, pDC, r);
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CDialogBG
IMPLEMENT_DYNCREATE(CDialogBG, CDialog)
BEGIN_MESSAGE_MAP(CDialogBG, CDialog)
	//{{AFX_MSG_MAP(CDialogBG)
	ON_WM_ERASEBKGND()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogBG message handlers
CDialogBG::~CDialogBG() {
  ReleaseStatics(m_Statics);
}
BOOL CDialogBG::OnInitDialog() {
  BOOL bResult = CDialog::OnInitDialog();
  if ( bResult ) {
    SubclassStatics(this, m_Statics);
  }
  return bResult;
}
BOOL CDialogBG::OnEraseBkgnd(CDC* pDC) {
  CRect r;
  GetClientRect(&r);
  GradientEraseBkgnd(pDC, r, false);
	return TRUE;
}
void CDialogBG::OnSysColorChange() {
  SetButtonSTColors(this, TRUE);
	CDialog::OnSysColorChange();
}

LRESULT CDialogBG::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
  if ( 0x128==message ) {
    return 0;
  }
	
	return CDialog::WindowProc(message, wParam, lParam);
}


/////////////////////////////////////////////////////////////////////////////
// CFormViewBG
IMPLEMENT_DYNAMIC(CFormViewBG, CFormView)
BEGIN_MESSAGE_MAP(CFormViewBG, CFormView)
	//{{AFX_MSG_MAP(CFormViewBG)
	ON_WM_ERASEBKGND()
//	ON_WM_CTLCOLOR()
	ON_WM_SYSCOLORCHANGE()
  ON_WM_DRAWITEM()
  ON_WM_SIZE()
  ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFormViewBG::~CFormViewBG() {
  ReleaseStatics(m_Statics);
}
void CFormViewBG::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
  wFlags = SCALE_ALL;
  if ( Is_IDC_STATIC(pWnd->GetDlgCtrlID()) )
    wFlags = SCALE_WIDTH;
  else if ( pWnd->IsKindOf(RUNTIME_CLASS(CEdit)) ) {
    if ( (pWnd->GetStyle() & ES_MULTILINE) == 0 )
      wFlags = SCALE_WIDTH;
  }
  else if ( pWnd->IsKindOf(RUNTIME_CLASS(CButton)) ) {
      wFlags = SCALE_NONE;
  }
  else if ( pWnd->IsKindOf(RUNTIME_CLASS(CComboBox)) ) {
    wFlags = SCALE_WIDTH;
  }
}
BOOL CFormViewBG::SetRect(CWnd* pWnd, const RECT* pNewRect) {
  SResizeWndInfo ri;
  if ( m_ResizeMap.Lookup(pWnd->m_hWnd, ri) ) {
    CopyRect(&ri.rect, pNewRect);
    m_ResizeMap.SetAt(pWnd->m_hWnd, ri);
  }
  return FALSE;
}
void CFormViewBG::FillChildsMap() {
  CWnd* pWnd = GetWindow(GW_CHILD);
  while( pWnd ) {
     SResizeWndInfo ri;
     ri.wFlags = SCALE_ALL;
     pWnd->GetWindowRect(&ri.rect);
     ScreenToClient(&ri.rect);
     SetScaleFlags(pWnd, ri.wFlags);
     m_ResizeMap.SetAt(pWnd->m_hWnd, ri);
     pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
  m_ResizableEnabled = TRUE;
}
BOOL CFormViewBG::IsNeedSubclassForStaticBG(CWnd* pWnd) {
  return Is_IDC_STATIC(pWnd->GetDlgCtrlID());
}

/////////////////////////////////////////////////////////////////////////////
// CFormViewBG message handlers
void CFormViewBG::SubclassStatics() {
  CWnd* pWnd = GetWindow(GW_CHILD); 
  int newID = 40000;
  while ( pWnd ) {
    int oldID = pWnd->GetDlgCtrlID();
    if ( IsNeedSubclassForStaticBG(pWnd) ) {
      CStaticBG* pStatic = new CStaticBG();
      if ( Is_IDC_STATIC(oldID) ) {
        pWnd->SetDlgCtrlID(newID);
        pStatic->SubclassDlgItem(newID, this);
        newID++;
      }
      else {
        pWnd->SetDlgCtrlID(oldID);
        pStatic->SubclassDlgItem(oldID, this);
      }
      m_Statics.Add( pStatic );
      newID++;
    }
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
}
void CFormViewBG::OnInitialUpdate() {
  CFormView::OnInitialUpdate(); 
  FillChildsMap();
  SubclassStatics();
}
BOOL CFormViewBG::OnEraseBkgnd(CDC* pDC) {
  if ( g_fUseGradient ) {
    CMemDC memDC(pDC);
    CRect rc;
    GetClientRect(&rc);
    //GradientEraseBkgnd(pDC, rc, false);
    GradientEraseBkgnd(&memDC, rc, false);
  }
  else {
    CRect clipRect;
    pDC->GetClipBox(&clipRect);
    pDC->FillSolidRect(&clipRect, g_clrLeft);
  }
	return TRUE;
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
void CFormViewBG::OnMoveControl(CWnd* pWnd, LPRECT lpRect, BOOL bRepaint/* = TRUE*/) {
  pWnd->MoveWindow(lpRect, bRepaint);
}
void CFormViewBG::OnSize(UINT nType, int cx, int cy) {
	CFormView::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
  if ( m_fRestoredRectSaved==FALSE && SIZE_RESTORED==nType && cx>0 && cy>0 ) {
    GetClientRect(&m_RestoredRect);
    m_fRestoredRectSaved = TRUE;
  }
  if ( m_ResizableEnabled ) {
    switch(nType) {
      case SIZE_RESTORED:
      case SIZE_MAXIMIZED:
      case SIZE_MAXSHOW: {
          CRect rcCurrent;
          GetClientRect(&rcCurrent);
          if ( rcCurrent.right > m_RestoredRect.right || rcCurrent.bottom > m_RestoredRect.bottom ) {
            double xScale = (double)rcCurrent.right/(double)m_RestoredRect.right;
            double yScale = (double)rcCurrent.bottom/(double)m_RestoredRect.bottom;
            CWnd* pWnd = GetWindow(GW_CHILD);
            SetRedraw(FALSE);
            while( pWnd ) {
              SResizeWndInfo ri;
              if ( m_ResizeMap.Lookup(pWnd->m_hWnd, ri) ) {
                CSize size(ri.rect.right-ri.rect.left, ri.rect.bottom-ri.rect.top);
                if ( xScale > 1.0 ) {
                  ri.rect.left    = (int)(ri.rect.left*xScale+0.5);
                  if ( ri.wFlags & SCALE_WIDTH )
                    ri.rect.right   = (int)(ri.rect.right*xScale+0.5);
                  else
                    ri.rect.right   = ri.rect.left + size.cx;
                }
                if ( yScale > 1.0 ) {
                  ri.rect.top     = (int)(ri.rect.top *yScale+0.5);
                  if ( ri.wFlags & SCALE_HEIGH )
                    ri.rect.bottom  = (int)(ri.rect.bottom*yScale+0.5);
                  else
                    ri.rect.bottom  = ri.rect.top + size.cy;
                }
                OnMoveControl(pWnd, &ri.rect, FALSE);
              }
              pWnd = pWnd->GetWindow(GW_HWNDNEXT);
            }
            SetRedraw(TRUE);
            InvalidateRect(NULL);
          }
        }
        break;
    }
  }
}
void CFormViewBG::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
  CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
  Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordViewBG
IMPLEMENT_DYNAMIC(CDaoRecordViewBG, CDaoRecordView)
BEGIN_MESSAGE_MAP(CDaoRecordViewBG, CDaoRecordView)
	//{{AFX_MSG_MAP(CDaoRecordViewBG)
	ON_WM_ERASEBKGND()
	ON_WM_SYSCOLORCHANGE()
  ON_WM_DRAWITEM()
  ON_WM_SIZE()
  ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDaoRecordViewBG::CDaoRecordViewBG(LPCTSTR lpszTemplateName):CDaoRecordView(lpszTemplateName) {
  m_ResizableEnabled = m_fRestoredRectSaved = FALSE;
}
CDaoRecordViewBG::CDaoRecordViewBG(UINT nIDTemplate):CDaoRecordView(nIDTemplate){
  m_ResizableEnabled = m_fRestoredRectSaved = FALSE;
}
CDaoRecordViewBG::~CDaoRecordViewBG() {
  ReleaseStatics(m_Statics);
}
void CDaoRecordViewBG::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
  wFlags = SCALE_ALL;
  if ( Is_IDC_STATIC(pWnd->GetDlgCtrlID()) )
    wFlags = SCALE_WIDTH;
  else if ( pWnd->IsKindOf(RUNTIME_CLASS(CEdit)) ) {
    if ( (pWnd->GetStyle() & ES_MULTILINE) == 0 )
      wFlags = SCALE_WIDTH;
  }
  else if ( pWnd->IsKindOf(RUNTIME_CLASS(CButton)) ) {
      wFlags = SCALE_NONE;
  }
  else if ( pWnd->IsKindOf(RUNTIME_CLASS(CComboBox)) ) {
    wFlags = SCALE_WIDTH;
  }
}
BOOL CDaoRecordViewBG::SetRect(CWnd* pWnd, const RECT* pNewRect) {
  SResizeWndInfo ri;
  if ( m_ResizeMap.Lookup(pWnd->m_hWnd, ri) ) {
    CopyRect(&ri.rect, pNewRect);
    m_ResizeMap.SetAt(pWnd->m_hWnd, ri);
  }
  return FALSE;
}
void CDaoRecordViewBG::FillChildsMap() {
  CWnd* pWnd = GetWindow(GW_CHILD);
  while( pWnd ) {
     SResizeWndInfo ri;
     ri.wFlags = SCALE_ALL;
     pWnd->GetWindowRect(&ri.rect);
     ScreenToClient(&ri.rect);
     SetScaleFlags(pWnd, ri.wFlags);
     m_ResizeMap.SetAt(pWnd->m_hWnd, ri);
     pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
  m_ResizableEnabled = TRUE;
}
BOOL CDaoRecordViewBG::IsNeedSubclassForStaticBG(CWnd* pWnd) {
  return Is_IDC_STATIC(pWnd->GetDlgCtrlID());
}
void CDaoRecordViewBG::SubclassStatics() {
  CWnd* pWnd = GetWindow(GW_CHILD); 
  int newID = 40000;
  while ( pWnd ) {
    int oldID = pWnd->GetDlgCtrlID();
    if ( IsNeedSubclassForStaticBG(pWnd) ) {
      CStaticBG* pStatic = new CStaticBG();
      if ( Is_IDC_STATIC(oldID) ) {
        pWnd->SetDlgCtrlID(newID);
        pStatic->SubclassDlgItem(newID, this);
        newID++;
      }
      else {
        pWnd->SetDlgCtrlID(oldID);
        pStatic->SubclassDlgItem(oldID, this);
      }
      m_Statics.Add( pStatic );
      newID++;
    }
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
}
void CDaoRecordViewBG::OnInitialUpdate() {
	CDaoRecordView::OnInitialUpdate();
  FillChildsMap();
  SubclassStatics();
}

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordViewBG message handlers
BOOL CDaoRecordViewBG::OnEraseBkgnd(CDC* pDC) {
  if ( g_fUseGradient ) {
    CMemDC memDC(pDC);
    CRect rc;
    GetClientRect(&rc);
    //GradientEraseBkgnd(pDC, rc, false);
    GradientEraseBkgnd(&memDC, rc, false);
  }
  else {
    CRect clipRect;
    pDC->GetClipBox(&clipRect);
    pDC->FillSolidRect(&clipRect, g_clrLeft);
  }
	return TRUE;
}
void CDaoRecordViewBG::OnSysColorChange() {
  SetButtonSTColors(this, TRUE);
	CDaoRecordView::OnSysColorChange();
}
void CDaoRecordViewBG::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS) {
  if ( ODT_BUTTON==lpDIS->CtlType ) {
    CWnd* pWnd = CWnd::FromHandle(lpDIS->hwndItem);
    if ( pWnd->IsKindOf(RUNTIME_CLASS(CButtonST)) ) {
      ((CButtonST*)pWnd)->DrawItem(lpDIS);
      return;
    }
  }
  CDaoRecordView::OnDrawItem(nIDCtl, lpDIS);
}
void CDaoRecordViewBG::OnMoveControl(CWnd* pWnd, LPRECT lpRect, BOOL bRepaint/* = TRUE*/) {
/*
  pWnd->MoveWindow(lpRect, bRepaint);
*/
  if ( pWnd->IsKindOf(RUNTIME_CLASS(CComboBox)) ) {
    CComboBox* pCombo = (CComboBox*)pWnd;
    CRect rDroppedRect;
    pCombo->GetDroppedControlRect(&rDroppedRect);
    lpRect->bottom = lpRect->top + rDroppedRect.Height();
    pWnd->MoveWindow(lpRect);
  }
  pWnd->MoveWindow(lpRect, bRepaint);
}
void CDaoRecordViewBG::OnSize(UINT nType, int cx, int cy) {
	CDaoRecordView::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
  if ( m_fRestoredRectSaved==FALSE && SIZE_RESTORED==nType && cx>0 && cy>0 ) {
    GetClientRect(&m_RestoredRect);
    m_fRestoredRectSaved = TRUE;
  }
  if ( m_ResizableEnabled ) {
    switch(nType) {
      case SIZE_RESTORED:
      case SIZE_MAXIMIZED:
      case SIZE_MAXSHOW: {
          CRect rcCurrent;
          GetClientRect(&rcCurrent);
          if ( rcCurrent.right > m_RestoredRect.right || rcCurrent.bottom > m_RestoredRect.bottom ) {
            double xScale = (double)rcCurrent.right/(double)m_RestoredRect.right;
            double yScale = (double)rcCurrent.bottom/(double)m_RestoredRect.bottom;
            CWnd* pWnd = GetWindow(GW_CHILD);
            SetRedraw(FALSE);
            while( pWnd ) {
              SResizeWndInfo ri;
              if ( m_ResizeMap.Lookup(pWnd->m_hWnd, ri) ) {
                CSize size(ri.rect.right-ri.rect.left, ri.rect.bottom-ri.rect.top);
                if ( xScale > 1.0 ) {
                  ri.rect.left    = (int)(ri.rect.left*xScale+0.5);
                  if ( ri.wFlags & SCALE_WIDTH )
                    ri.rect.right   = (int)(ri.rect.right*xScale+0.5);
                  else
                    ri.rect.right   = ri.rect.left + size.cx;
                }
                if ( yScale > 1.0 ) {
                  ri.rect.top     = (int)(ri.rect.top *yScale+0.5);
                  if ( ri.wFlags & SCALE_HEIGH )
                    ri.rect.bottom  = (int)(ri.rect.bottom*yScale+0.5);
                  else
                    ri.rect.bottom  = ri.rect.top + size.cy;
                }
                if ( pWnd->IsKindOf(RUNTIME_CLASS(CEdit)) ) {
                  // We should set correspond edit heigh
                  int nPointSize = 0;
                  int Height = 0;
                  CFont* pFont = pWnd->GetFont();
                  if ( pFont ) {
                    LOGFONT lf;
                    pFont->GetLogFont(&lf);
                    nPointSize = -(int)((lf.lfHeight*72)/96.0 - 0.5);
                    CDC* pDC = pWnd->GetDC();
                    if ( pDC ) {
                      CFont* pOldFont = pDC->SelectObject(pFont);
                      Height = pDC->GetTextExtent("Æ").cy + 8;
                      pDC->SelectObject(pOldFont);
                      pWnd->ReleaseDC(pDC);
                    }
                  }
                  if ( ri.rect.bottom - ri.rect.top < Height ) {
                    ri.rect.bottom = ri.rect.top + Height;
                  }
                }
                OnMoveControl(pWnd, &ri.rect, FALSE);
              }
              pWnd = pWnd->GetWindow(GW_HWNDNEXT);
            }
            SetRedraw(TRUE);
            InvalidateRect(NULL);
          }
        }
        break;
    }
  }
}

void CDaoRecordViewBG::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
  CDaoRecordView::OnHScroll(nSBCode, nPos, pScrollBar);
  Invalidate();
}
/////////////////////////////////////////////////////////////////////////////
// CPropertyPageBG
IMPLEMENT_DYNCREATE(CPropertyPageBG, CPropertyPage)
BEGIN_MESSAGE_MAP(CPropertyPageBG, CPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageBG)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CPropertyPageBG::~CPropertyPageBG() {
  ReleaseStatics(m_Statics);
}
/////////////////////////////////////////////////////////////////////////////
// CPropertyPageBG message handlers
BOOL CPropertyPageBG::OnInitDialog() {
  BOOL bResult = CPropertyPage::OnInitDialog();
  if ( bResult ) {
    SubclassStatics(this, m_Statics);
  }
  return bResult;
}
BOOL CPropertyPageBG::OnEraseBkgnd(CDC* pDC) {
  CRect r;
  GetClientRect(&r);
  GradientEraseBkgnd(this, GetParent(), pDC, r);
	return TRUE;
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
  CRect r;
  GetClientRect(&r);
  GradientEraseBkgnd(pDC, r);
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
  CRect r;
  GetClientRect(&r);
  GradientEraseBkgnd(this, GetParent(), pDC, r);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDialogBarBG
IMPLEMENT_DYNCREATE(CDialogBarBG, CDialogBar)
CDialogBarBG::CDialogBarBG() {
}
CDialogBarBG::~CDialogBarBG() {
  ReleaseStatics(m_Statics);
}

BEGIN_MESSAGE_MAP(CDialogBarBG, CDialogBar)
	//{{AFX_MSG_MAP(CDialogBarBG)
	ON_WM_ERASEBKGND()
  ON_WM_SYSCOLORCHANGE()
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
  CRect r;
  GetClientRect(&r);
  // GradientEraseBkgnd(this, GetParent(), pDC, r);
  GradientEraseBkgnd(pDC, r, false);
	return TRUE;
}
void CDialogBarBG::OnSysColorChange() {
  InvalidateRect(NULL);
  SetButtonSTColors(this, TRUE);
	CDialogBar::OnSysColorChange();
}
