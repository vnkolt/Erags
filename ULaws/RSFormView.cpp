//
// RSFormView.cpp
//
#include "stdafx.h"
#include "RSFormView.h"

/////////////////////////////////////////////////////////////////////////////
// CResizableFormView
IMPLEMENT_DYNAMIC(CResizableFormView, CFormView)
BEGIN_MESSAGE_MAP(CResizableFormView, CFormView)
  //{{AFX_MSG_MAP(CResizableFormView)
  ON_WM_SIZE()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CResizableFormView::CResizableFormView(LPCTSTR lpszTemplateName):CFormView(lpszTemplateName) {
  m_ResizableEnabled = m_fRestoredRectSaved = FALSE;
  memset( &m_OriginLogFont, 0, sizeof(m_OriginLogFont) );
}
CResizableFormView::CResizableFormView(UINT nIDTemplate):CFormView(nIDTemplate){
  m_ResizableEnabled = m_fRestoredRectSaved = FALSE;
  memset( &m_OriginLogFont, 0, sizeof(m_OriginLogFont) );
}
CResizableFormView::~CResizableFormView() {
}
void CResizableFormView::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
  wFlags = SCALE_ALL;
  if ( IDC_STATIC==pWnd->GetDlgCtrlID() ) {
    wFlags = SCALE_WIDTH;
  }
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
BOOL CResizableFormView::SetRect(CWnd* pWnd, const RECT* pNewRect) {
  SResizeWndInfo ri;
  if ( m_ResizeMap.Lookup(pWnd->m_hWnd, ri) ) {
    CopyRect(&ri.rect, pNewRect);
    m_ResizeMap.SetAt(pWnd->m_hWnd, ri);
  }
  return FALSE;
}
void CResizableFormView::FillChildsMap() {
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
void CResizableFormView::SetFontForChildren(CFont* pFont) {
  CWnd* pWnd = GetWindow(GW_CHILD);
  while( pWnd ) {
     SResizeWndInfo ri;
     if ( m_ResizeMap.Lookup(pWnd->m_hWnd, ri) && ri.wFlags != SCALE_NONE ) {
       pWnd->SetFont(pFont);
     }
     pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
  m_ResizableEnabled = TRUE;
}

void CResizableFormView::OnInitialUpdate() {
  CFormView::OnInitialUpdate();
  FillChildsMap();
}

/////////////////////////////////////////////////////////////////////////////
// CResizableFormView message handlers
void CResizableFormView::OnMoveControl(CWnd* pWnd, LPRECT lpRect, BOOL bRepaint/* = TRUE*/) {
  pWnd->MoveWindow(lpRect, bRepaint);
}
void CResizableFormView::OnSize(UINT nType, int cx, int cy) {
  CFormView::OnSize(nType, cx, cy);

  if ( 0==m_OriginLogFont.lfFaceName[0] ) {
    CFont* pFont = GetFont();
    if ( pFont != NULL ) {
      pFont->GetLogFont(&m_OriginLogFont);
    }
  }

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
