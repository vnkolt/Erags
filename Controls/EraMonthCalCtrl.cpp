// EraMonthCalCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "EraMonthCalCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEraMonthCalCtrl
CEraMonthCalCtrl::CEraMonthCalCtrl() {
}

CEraMonthCalCtrl::~CEraMonthCalCtrl() {
}


BEGIN_MESSAGE_MAP(CEraMonthCalCtrl, CMonthCalCtrl)
	//{{AFX_MSG_MAP(CEraMonthCalCtrl)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
  ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEraMonthCalCtrl::SendNotifyToOwner(UINT code) {
  CWnd* pOwner = GetOwner();
  if ( pOwner && IsWindow(pOwner->m_hWnd) ) {
    NMHDR nmhdr;
    nmhdr.hwndFrom = m_hWnd;
    nmhdr.idFrom = GetDlgCtrlID();
    nmhdr.code = code;
    pOwner->SendMessage(WM_NOTIFY, (WPARAM)nmhdr.idFrom, (LPARAM)&nmhdr);
  }
}
void CEraMonthCalCtrl::NotifyDateChange() {
  CWnd* pOwner = GetOwner();
  if ( pOwner && IsWindow(pOwner->m_hWnd) ) {
    NMDATETIMECHANGE dtc;
    if ( GetCurSel(&dtc.st) ) {
      UINT CalendareID = GetDlgCtrlID();
      dtc.nmhdr.hwndFrom = m_hWnd;
      dtc.nmhdr.idFrom   = CalendareID;
      dtc.nmhdr.code     = DTN_DATETIMECHANGE;
      dtc.dwFlags        = GDT_VALID;
      pOwner->SendMessage(WM_NOTIFY, (WPARAM)CalendareID, (LPARAM)&dtc);
    }
  }
}
void CEraMonthCalCtrl::CloseCalendar() {
  CWnd* pOwner = GetOwner();
  if ( pOwner && IsWindow(pOwner->m_hWnd) )
    pOwner->SetFocus();
  ShowWindow(SW_HIDE);
}
/////////////////////////////////////////////////////////////////////////////
// CEraMonthCalCtrl message handlers
void CEraMonthCalCtrl::OnKillFocus(CWnd* pNewWnd) {
	CMonthCalCtrl::OnKillFocus(pNewWnd);
	// TODO: Add your message handler code here
  if ( IsChild(pNewWnd) )
    return;
  SendNotifyToOwner(NM_KILLFOCUS);
  ShowWindow(SW_HIDE);
}

void CEraMonthCalCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// TODO: Add your message handler code here and/or call default
  switch(nChar) {
    case VK_RETURN:
    case VK_SPACE:
      NotifyDateChange();
      CloseCalendar();
      return;
    case VK_ESCAPE:
    case VK_F4:
    case VK_TAB:
      CloseCalendar();
      return;
  }
	CMonthCalCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CEraMonthCalCtrl::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// TODO: Add your message handler code here and/or call default
  switch(nChar) {
    case VK_DOWN:
      if ( GetKeyState(VK_MENU)<0 ) {
        ShowWindow(SW_HIDE);
        return;
      }
      break;
  }
	CMonthCalCtrl::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CEraMonthCalCtrl::OnLButtonUp(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	CMonthCalCtrl::OnLButtonUp(nFlags, point);
	NotifyDateChange();
}

BOOL CEraMonthCalCtrl::PreTranslateMessage(MSG* pMsg) {
	// TODO: Add your specialized code here and/or call the base class
  if (WM_KEYDOWN == pMsg->message && VK_ESCAPE==pMsg->wParam ) {
    CloseCalendar();
    return TRUE;
  }
	return CMonthCalCtrl::PreTranslateMessage(pMsg);
}
