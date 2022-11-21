// FormABC.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "FormABC.h"

#include "ABCList.h"
#include "EraABCDoc.h"
#include "EraABCView.h"
#include "HelpMan.h"

#include "..\Common\MDB.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL IsFocusChild(CWnd* pParentWnd) {
  HWND hWnd = ::GetFocus();
  if ( NULL==hWnd )
    return FALSE;
  return ::IsChild(pParentWnd->m_hWnd, hWnd);
}

/////////////////////////////////////////////////////////////////////////////
// CFormABC

IMPLEMENT_DYNAMIC(CFormABC, CFormABCBase)
BEGIN_MESSAGE_MAP(CFormABC, CFormABCBase)
	//{{AFX_MSG_MAP(CFormABC)
  ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_RECORD_FIRST, OnUpdateRecordFirst)
	ON_COMMAND(ID_RECORD_FIRST, OnRecordFirst)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREV, OnUpdateRecordPrev)
	ON_COMMAND(ID_RECORD_PREV, OnRecordPrev)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateRecordNext)
	ON_COMMAND(ID_RECORD_NEXT, OnRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_LAST, OnUpdateRecordLast)
	ON_COMMAND(ID_RECORD_LAST, OnRecordLast)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEW, OnUpdateRecordNew)
	ON_COMMAND(ID_RECORD_NEW, OnRecordNew)
	ON_UPDATE_COMMAND_UI(ID_RECORD_DELETE, OnUpdateRecordDelete)
	ON_COMMAND(ID_RECORD_DELETE, OnRecordDelete)
	ON_WM_KEYDOWN()
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFormABC::CFormABC(UINT idd) : CFormABCBase(idd) {
	//{{AFX_DATA_INIT(CFormABC)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
  m_bEnabled = TRUE;
  m_fGoTo = m_fInitialized = m_fFilled = FALSE;
  m_ID = -1;
  m_fEnableRelayEvent = true;
  m_ShownCtrlId = 0;
}

CFormABC::~CFormABC() {
  CloseRecordSet();
}

void CFormABC::CloseRecordSet() {
  if ( m_pSet ) {
    if ( m_pSet->IsOpen() ) {
      SaveData();
      m_pSet->Close();
    }
    delete m_pSet;
    m_pSet = NULL;
    ClearControls();
  }
  m_fFilled = FALSE;
  m_ID = -1;
}

void CFormABC::DoDataExchange(CDataExchange* pDX, long lID) {
	CFormABCBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormABC)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
BOOL CFormABC::SaveData() {
  ASSERT_VALID(this);
  CDaoRecordset* pSet = OnGetRecordset();
  if ( NULL==pSet )
    return false;
  try {
    if (pSet->IsBOF() || pSet->IsEOF() )
      return TRUE;
    if (pSet->CanUpdate() && !pSet->IsDeleted() ) {
      pSet->Edit();
      if (!UpdateData())
        return TRUE;
      if (pSet->IsFieldDirty(NULL))
        pSet->Update();
      else
        pSet->CancelUpdate();
    }
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return false;
  }
  return true;
}


BOOL CFormABC::PreCreateWindow(CREATESTRUCT& cs) {
	return CFormABCBase::PreCreateWindow(cs);
}

void CFormABC::OnInitialUpdate() {
  if ( m_pSet )
	  CFormABCBase::OnInitialUpdate();
  else
    CFormView::OnInitialUpdate();
/************************************** : by VK at 29.01.2005 9:38:41 **\
	ResizeParentToFit();
\************************************** : by VK at 29.01.2005 9:38:43 **/
  CEraABCView* pView = static_cast<CEraABCView*>(GetParent());
  if ( m_tooltip.GetSafeHwnd()==NULL ) {
    m_tooltip.Create(this);
    SetDefaults(&m_tooltip);
    SetTooltips();
  }

}


void CFormABC::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
  switch(pWnd->GetDlgCtrlID()) {
    case IDC_CHILDFACE:     wFlags = SCALE_NONE;  break;
  }
}
void CFormABC::EnableControls(BOOL bEnable/*= TRUE*/) {
  if ( bEnable==m_bEnabled )
    return;
  CWnd* pWnd = GetWindow(GW_CHILD);
  while( pWnd ) {
    pWnd->EnableWindow(bEnable);
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
  m_bEnabled = bEnable;
}
void CFormABC::ClearControls() {
  CWnd* pWnd = GetWindow(GW_CHILD);
  while( pWnd ) {
    if ( pWnd->IsKindOf(RUNTIME_CLASS(CEdit)) ) {
      pWnd->SetWindowText(_T(""));
    }
    else if ( pWnd->IsKindOf(RUNTIME_CLASS(CComboBox)) ) {
      pWnd->SetWindowText(_T(""));
    }
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
}
void CFormABC::GoTo(long lID, BOOL fSave/*=TRUE*/) {
  if ( m_fGoTo || FALSE==m_fFilled)
    return;
  m_fGoTo = TRUE;
  if ( fSave ) {
    SaveData();
  }
  if ( m_ID!=lID ) {
    try {
      if ( m_pSet->Seek("=", &COleVariant(lID)) ) {
        m_ID = lID;
        UpdateData(FALSE);
      }
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }
  m_fGoTo = FALSE;
}
long CFormABC::RecordNew() {
  long lID = -1;
  SaveData();
  try {
    if ( m_pSet->CanAppend() ) {
      m_pSet->AddNew();
      if ( m_pSet->CanUpdate() ) {
        m_pSet->Update();
        m_pSet->SetBookmark( m_pSet->GetLastModifiedBookmark() );
        //if ( !m_pSet->IsDeleted() )
        lID = GetFieldLong(m_pSet, _T("ID"));
      }
    }
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
  m_pSet->SetBookmark( m_pSet->GetLastModifiedBookmark() );
  UpdateData(FALSE);
  EnableControls(TRUE);
  return lID;
}

bool CFormABC::SetDefaultNumber() {
  CString sNumber;
  bool bRet = true;
  CEdit* pEdit = (CEdit*)GetDlgItem(IDC_NUMBER);
  pEdit->GetWindowText(sNumber);
  CDaoRecordset* pSet = OnGetRecordset();
  if ( pSet ) {
    long lNum(0);
    COleVariant ovNumber;
    try {
      COleVariant bm = pSet->GetBookmark();
      if ( !pSet->IsBOF() ) {
        pSet->MovePrev();
        if ( !pSet->IsBOF() ) {
          pSet->GetFieldValue(_T("NUMBER"), ovNumber);
          lNum = V_UI2(&ovNumber);
        }
      }
      pSet->SetBookmark(bm);
    }
    catch(CDaoException* e) {
      e->Delete();
      bRet = false;
    }
    sNumber.Format(_T("%d"), lNum+1);
    pEdit->SetWindowText(sNumber);
    pEdit->SetSel(0, -1);
  }
  return bRet;
}
void CFormABC::SetDefaultDateReg() {
  CString sDateReg;
  if ( m_pSet ) {
    COleDateTime odt;
    try {
      COleVariant bm = m_pSet->GetBookmark();
      if ( !m_pSet->IsBOF() ) {
        m_pSet->MovePrev();
        sDateReg = GetFieldDate(m_pSet, _T("DATEREG"), false);
      }
      m_pSet->SetBookmark(bm);
    }
    catch(CDaoException* e) {
      e->Delete();
    }
    if ( !sDateReg.IsEmpty() ) {
      CEdit* pEdit = (CEdit*)GetDlgItem(IDC_DATEREG);
      pEdit->SetWindowText(sDateReg);
      pEdit->SetSel(0, -1);
    }
  }
}

void CFormABC::SetFilled() {
  m_fFilled = TRUE;
  UpdateData(FALSE);
}
/////////////////////////////////////////////////////////////////////////////
// CFormABC diagnostics
#ifdef _DEBUG
void CFormABC::AssertValid() const {
	CFormABCBase::AssertValid();
}

void CFormABC::Dump(CDumpContext& dc) const {
	CFormABCBase::Dump(dc);
}
CEraABCDoc* CFormABC::GetDocument() // non-debug version is inline
{
/************************************** : by VK at 29.01.2005 9:54:46 **\
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEraABCDoc)));
	return (CEraABCDoc*)m_pDocument;
\************************************** : by VK at 29.01.2005 9:54:49 **/
  return theApp.m_pDoc;
}
#endif //_DEBUG

CABCList* CFormABC::GetListCtrl() {
	CEraABCView* pView = static_cast<CEraABCView*>(GetParent());
  return pView->GetListCtrl();
}
/////////////////////////////////////////////////////////////////////////////
// CEraABCView database support
CDaoRecordset* CFormABC::OnGetRecordset() {
  return m_pSet;
}
void CFormABC::OnUpdateRecordFirst(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
  GetListCtrl()->OnUpdateRecordFirst(	pCmdUI );
}
void CFormABC::OnRecordFirst() {
  GetListCtrl()->OnRecordFirst();
}
void CFormABC::OnUpdateRecordPrev(CCmdUI* pCmdUI) {
  GetListCtrl()->OnUpdateRecordPrev(pCmdUI);
}
void CFormABC::OnRecordPrev() {
  GetListCtrl()->OnRecordPrev();
}
void CFormABC::OnUpdateRecordNext(CCmdUI* pCmdUI) {
  GetListCtrl()->OnUpdateRecordNext(pCmdUI);
}

void CFormABC::OnRecordNext() {
  GetListCtrl()->OnRecordNext();
}

void CFormABC::OnUpdateRecordLast(CCmdUI* pCmdUI) {
  GetListCtrl()->OnUpdateRecordLast(pCmdUI);
}
void CFormABC::OnRecordLast() {
  GetListCtrl()->OnRecordLast();
}
void CFormABC::OnUpdateRecordNew(CCmdUI* pCmdUI) {
	GetListCtrl()->OnUpdateRecordNew(pCmdUI);
}
void CFormABC::OnRecordNew() {
	GetListCtrl()->OnRecordNew();
}
void CFormABC::OnUpdateRecordDelete(CCmdUI* pCmdUI) {
	GetListCtrl()->OnUpdateRecordDelete(pCmdUI);
}
void CFormABC::OnRecordDelete() {
	GetListCtrl()->OnRecordDelete();
}

/////////////////////////////////////////////////////////////////////////////
// CFormABC message handlers
void CFormABC::OnDestroy() {
  CloseRecordSet();  
}
void CFormABC::GoToPrevRecord() {
  SaveData();
  CABCList* pList = GetListCtrl();
  if ( pList->CanGoToPrev() ) {
    OnRecordPrev();
  }
}
void CFormABC::GoToNextRecord() {
  SaveData();
  CABCList* pList = GetListCtrl();
  if ( pList->CanGoToNext() ) {
    OnRecordNext();
  }
  else
    pList->OnRecordNew();
}
void CFormABC::BeforeGoToNextRecord() {
}
BOOL CFormABC::OnCommand(WPARAM wParam, LPARAM lParam) {
	// TODO: Add your specialized code here and/or call the base class
  WORD wNotifyCode = HIWORD(wParam);
  WORD wCtrlId = LOWORD(wParam);
  CWnd* pControl = CWnd::FromHandle((HWND)lParam);

  switch(wNotifyCode) {
    case BN_SETFOCUS:
    case EN_SETFOCUS:
    case CBN_SETFOCUS:
      ScrollToControl(pControl);
      if ( theApp.m_fUseHelper && m_ShownCtrlId != wCtrlId ) {
        m_tooltip.HideTooltip();
        m_ShownCtrlId = wCtrlId;
        ShowHelpTooltipSetFocus(&m_tooltip, this, m_szFormName, pControl, wCtrlId);
        m_fEnableRelayEvent = false;
      }
      break;
    case BN_KILLFOCUS:
    case EN_KILLFOCUS:
    case CBN_KILLFOCUS:
      m_fEnableRelayEvent = true;
      break;
  }

  if ( BN_KILLFOCUS==wNotifyCode || CBN_KILLFOCUS==wNotifyCode || EN_KILLFOCUS==wNotifyCode ) {
    WORD wFirstID = 0;
    WORD wLastID = 0;
    m_tooltip.HideTooltip();

    switch((int)m_lpszTemplateName) {
      case IDD_FORM_BIRTH:
        wFirstID   = IDC_SEX;
        wLastID = IDC_PATRONYMIC;
        break;
      case IDD_FORM_MARRIAGE:
        wFirstID = IDC_NUMBER;
        wLastID = IDC_WPATRONYMIC;
        break;
      case IDD_FORM_DIVORCE:
        wFirstID = IDC_NUMBER;
        wLastID = IDC_WPATRONYMIC;
        break;
      case IDD_FORM_CHANGE:
        wFirstID = IDC_SEX;
        wLastID = IDC_NEW_PATRONYMIC;
        break;
      case IDD_FORM_DEATH:
        wFirstID = IDC_SEX;
        wLastID = IDC_PATRONYMIC;
        break;
    }
    if ( wLastID==wCtrlId && GetKeyState(VK_SHIFT)>=0 && (GetKeyState(VK_TAB)<0 ||GetKeyState(VK_RETURN)<0) ) {
      BeforeGoToNextRecord();
      GoToNextRecord();
      return FALSE;
    }
    else if ( wFirstID==wCtrlId && GetKeyState(VK_SHIFT)<0 ) {
      GoToPrevRecord();
      return FALSE;
    }
  }
  else if ( BN_CLICKED==wNotifyCode && IDC_SEX==wCtrlId) {
    BOOL bResult = CFormABCBase::OnCommand(wParam, lParam);
    OnClickSex();
    return bResult;
  }
	return CFormABCBase::OnCommand(wParam, lParam);
}

void CFormABC::SetTooltips() {
  theToolTipCache.Fill(this, m_szFormName, &m_tooltip);
}
void CFormABC::ScrollToControl(CWnd* pWnd) {
  CWnd* pFocusWnd = GetFocus();
  if ( NULL==pFocusWnd )
    return;

  BOOL fComboEdit = pFocusWnd->IsKindOf(RUNTIME_CLASS(CEdit)) && pWnd->IsKindOf(RUNTIME_CLASS(CComboBox));

  if ((pFocusWnd->m_hWnd == pWnd->m_hWnd) || fComboEdit) {
      CRect rcChild, rcParent, rcTemp;

      pWnd->GetWindowRect(&rcChild);
      GetWindowRect(&rcParent);


     //Get document size. Assume mapping mode is MM_TEXT and ViewPort
     //and Window origins have not been set so we can also assume LP==DP.
      CSize size = GetTotalSize();

      // Determine if scroll bars are visible
      // and subtract their size from the view.
      if (size.cx > rcParent.right - rcParent.left)
         rcParent.bottom -= GetSystemMetrics(SM_CYHSCROLL);
      if (size.cy > rcParent.bottom - rcParent.top)
         rcParent.right -= GetSystemMetrics(SM_CXVSCROLL);

      // Succeed only if no part of the child appears in the parent.
      rcTemp.IntersectRect(rcChild, rcParent);

      if (rcTemp != rcChild)
      {
         POINT pt;

         pt.x = GetDeviceScrollPosition().x;
         pt.y = GetDeviceScrollPosition().y;

         if (rcChild.top < rcParent.top)
         {
            TRACE("control is above the client area\n");
            pt.y -= rcParent.top - rcChild.top +
               GetSystemMetrics(SM_CXEDGE);
         }
         else if (rcChild.bottom > rcParent.bottom)
         {
            TRACE("control is below the client area\n");
            // If the control is taller than the current view
            // scroll up, sacrificing the bottom of the control.
            pt.y += min(rcChild.top - rcParent.top,
               rcChild.bottom - rcParent.bottom +
               GetSystemMetrics(SM_CYHSCROLL) +
               GetSystemMetrics(SM_CXEDGE));
         }

         if (rcChild.left < rcParent.left)
         {
            TRACE("control is left of the client area\n");
            pt.x -= rcParent.left - rcChild.left +
               GetSystemMetrics(SM_CYEDGE);
         }
         else if (rcChild.right > rcParent.right)
         {
            TRACE("control is right of the client area\n");
            // If the control is wider than the current view
            // scroll right, sacrificing the right edge of the control.
            pt.x += min(rcChild.left - rcParent.left,
               rcChild.right - rcParent.right +
               GetSystemMetrics(SM_CXVSCROLL) +
               GetSystemMetrics(SM_CYEDGE));
         }

         ScrollToPosition(pt);  //Assume mapping mode is MM_TEXT.

         SendMessage(WM_SYSCOLORCHANGE);
         InvalidateRect(NULL);
      }
  }
}

BOOL CFormABC::PreTranslateMessage(MSG* pMsg) {
	// TODO: Add your specialized code here and/or call the base class
  if ( theApp.m_fUseHelper && m_tooltip.GetSafeHwnd() && m_fEnableRelayEvent) {
    if( pMsg->hwnd==m_hWnd )
      m_tooltip.RelayEvent(pMsg);
  }
	return CFormABCBase::PreTranslateMessage(pMsg);
}

BOOL CFormABC::OnHelpInfo(HELPINFO* pHelpInfo) {
  CWnd* pFromPoint = WindowFromPoint(pHelpInfo->MousePos);
  BOOL bChild = IsChild(pFromPoint);
  if ( bChild ) {
    m_tooltip.HideTooltip();
    CWnd* pControl = GetDlgItem(pHelpInfo->iCtrlId);
    if ( pControl )
      ScrollToControl(pControl);
    ShowHelpTooltipSetFocus(&m_tooltip, this, m_szFormName, CWnd::FromHandle((HWND)pHelpInfo->hItemHandle), pHelpInfo->iCtrlId);
    m_fEnableRelayEvent = false;
    return true;
  }
  return false;
}
