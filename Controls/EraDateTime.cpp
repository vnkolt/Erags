// EraDateTime.cpp : implementation file
//

#include "stdafx.h"
#include "EraDateTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern COLORREF g_clrBackColor;
void SendKeys(BYTE bKey, BYTE bCtrKey, BYTE bShiftKey=0);
/////////////////////////////////////////////////////////////////////////////
// DDX for mask control
void AFXAPI DDX_OleDate(CDataExchange* pDX, int nIDC, CEraDateTime& rControl, COleDateTime& Date) {
  DDX_Control(pDX, nIDC, (CWnd&)rControl);
  if (pDX->m_bSaveAndValidate)
    rControl.GetTime(Date);
  else
    rControl.SetTime(Date);
}
void AFXAPI DDX_DateField(CDataExchange* pDX, int nIDC, CEraDateTime& rControl, COleDateTime& Date, CDaoRecordset* pSet) {
  DDX_Control(pDX, nIDC, (CWnd&)rControl);
  if (pDX->m_bSaveAndValidate) {  // From control to field
    rControl.GetTime(Date);
    //DDX_FieldText(pDX, nIDC, Date, pSet);
  }
  else {                          // From field to control
    //DDX_FieldText(pDX, nIDC, Date, pSet);
    rControl.SetTime(Date);
  }
}

/////////////////////////////////////////////////////////////////////////////
// CEraDateTime
CEraDateTime::CEraDateTime() {
  m_bFocus = FALSE;
}
CEraDateTime::~CEraDateTime() {
}

BEGIN_MESSAGE_MAP(CEraDateTime, CDateTimeCtrl)
	//{{AFX_MSG_MAP(CEraDateTime)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(DTN_DATETIMECHANGE, OnDatetimeChange)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraDateTime message handlers
void CEraDateTime::OnSetFocus(CWnd* pOldWnd) {
	CDateTimeCtrl::OnSetFocus(pOldWnd);
  m_bFocus = TRUE;
  SetFormat(_T("dd.MM.yyyy"));
  InvalidateRect(NULL);
}
void CEraDateTime::OnKillFocus(CWnd* pNewWnd){
	CDateTimeCtrl::OnKillFocus(pNewWnd);
  m_bFocus = FALSE;
  SetFormat(_T("dd MMMM yyyy"));
  InvalidateRect(NULL);
}
BOOL CEraDateTime::OnEraseBkgnd(CDC* pDC) {
  if(FALSE==m_bFocus) {
    CRect rClip;
    pDC->GetClipBox(&rClip);
    pDC->FillSolidRect(&rClip, g_clrBackColor);
    return TRUE;
  }
  else
    return CDateTimeCtrl::OnEraseBkgnd(pDC);
}

int CEraDateTime::OnCreate(LPCREATESTRUCT lpCreateStruct)  {
	if (CDateTimeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
  SetFormat(_T("dd MMMM yyyy"));
  InvalidateRect(NULL);
	return 0;
}

void CEraDateTime::SetDate(COleDateTime& Date) {
  SetTime(Date);
}

COleDateTime CEraDateTime::GetDate() {
  COleDateTime odt;
  GetTime(odt);
  return odt;
}

CString CEraDateTime::GetDDMMYYYY() {
  CString s;
  COleDateTime odt = GetDate();
  if ( COleDateTime::valid==odt.GetStatus() && odt.m_dt != (DATE)0 )
    s.Format(_T("%02d.%02d.%04d"), odt.GetDay(), odt.GetMonth(), odt.GetYear() );
  return s;
}


BOOL CEraDateTime::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch ( pMsg->message ) {
    case WM_KEYDOWN:
      if ( VK_RETURN==pMsg->wParam && GetKeyState(VK_CONTROL)>=0 ) {
        pMsg->wParam = VK_TAB;
      }
      break;
  }
	return CDateTimeCtrl::PreTranslateMessage(pMsg);
}

void CEraDateTime::OnDatetimeChange(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: Add your control notification handler code here
  SendKeys(VK_RIGHT, 0);
	*pResult = 0;
}

void CEraDateTime::OnPaint() {
	CPaintDC dc(this); // device context for painting

  COleDateTime odt;
  GetTime(odt);
	
	// TODO: Add your message handler code here
  if ( GetFocus()==this ) {
    CDateTimeCtrl::DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
  }
  else {
    if ( odt.GetYear() > 1800 && odt.GetStatus()==COleDateTime::valid )
      CDateTimeCtrl::DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
  }
	// Do not call CDateTimeCtrl::OnPaint() for painting messages
}
