// EraForm.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "EraForm.h"

#include "ChildFrm.h"
#include "EmptyTableDlg.h"
#include "Geography.h"
#include "Defaults.h"
#include "HelpMan.h"
#include "MainFrm.h"
#include "Menu.h"
#include "YesNoDlg.h"

#include "FormBirth.h"
#include "FormMarriage.h"
#include "FormDivorce.h"
#include "FormDeath.h"
#include "FormChange.h"

#include "RegDlg.h"
#include "TemplDlg.h"

#include "xMachine.h"

#include "..\Common\DaoErr.h"
#include "..\Common\EraMessages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_OUTNMENU   ID_PRINT_LAST

extern BOOL dm_fNewBirth;
extern BOOL dm_fNewMarrige;
extern BOOL dm_fNewDivorce;
extern BOOL dm_fNewChange;
extern BOOL dm_fNewDeath;

void OnDocShell(LPCTSTR szFilename, BOOL fExport);

BOOL IsFocusChild(CWnd* pParentWnd) {
  HWND hWnd = ::GetFocus();
  if ( NULL==hWnd )
    return FALSE;
  return ::IsChild(pParentWnd->m_hWnd, hWnd);
}

static WORD ToolIdBirth[] = { IDR_PRINTMENU,
                              16, 15,
                              ID_PRINT_BIRTH_ACT,           // Актовий &запис про народження
                              ID_PRINT_BIRTH_CERTIFICATE,   // &Свідоцтво про народження
                              ID_OUTNMENU,
                              ID_OUTNMENU,
                              ID_PRINT_ADOPTION_CERTIFICATE,// Свідоцтво про &усиновлення
                              ID_OUTNMENU,                // Certificate with red check
                              ID_PRINT_BIRTH_FORTAX,      // List 1
                              ID_OUTNMENU,
                              ID_PRINT_BIRTH_8,
                              ID_PRINT_BIRTH_9,
                              ID_PRINT_DEATH_CHILDREN,
                              ID_OUTNMENU,
                              ID_PRINT_BIRTH_ABC,
                              ID_OUTNMENU,
                              NULL};


static WORD ToolIdMarriage[] = { IDR_PRINTMENU,
                              16, 15,
                              ID_PRINT_MARRIAGE_ACT,      // Act
                              ID_OUTNMENU,
                              ID_OUTNMENU,
                              ID_PRINT_MARRIAGE_CERIFICATE,
                              ID_OUTNMENU,
                              ID_OUTNMENU,
                              ID_OUTNMENU,
                              ID_OUTNMENU,
                              ID_OUTNMENU,
                              ID_PRINT_BLANK_REGISTER,
                              ID_OUTNMENU,
                              ID_PRINT_CHANGE_ELECTIONS,
                              ID_PRINT_MARRIAGE_ABC,
                              ID_OUTNMENU,
                              NULL};

static WORD ToolIdDivorce[] = { IDR_PRINT_DIVORCE,
                              16, 15,
                              ID_PRINT_DIVORCE_ACT,      // Act
                              ID_PRINT_DIVORCE_CERIFICATE1,
                              ID_PRINT_DIVORCE_CERIFICATE2,
                              ID_PRINT_DIVORCE_18_1,
                              ID_PRINT_DIVORCE_18_2,
                              ID_PRINT_DIVORCE_16,
                              ID_PRINT_DIVORCE_23,
                              ID_PRINT_DIVORCE_ABC,
                              NULL};


static WORD ToolIdChange[] = { IDR_PRINTMENU,
                              16, 15,
                              ID_PRINT_CHANGE_ACT,      // Act
                              ID_PRINT_CHANGE_CERIFICATE,
                              ID_OUTNMENU,
                              ID_OUTNMENU,
                              ID_OUTNMENU,
                              ID_OUTNMENU,
                              ID_OUTNMENU,
                              ID_PRINT_CHANGE_27,
                              ID_OUTNMENU,
                              ID_OUTNMENU,
                              ID_OUTNMENU,
                              ID_PRINT_CHANGE_30,
                              ID_PRINT_CHANGE_ABC,
                              NULL};

static WORD ToolIdDeath[] = { IDR_PRINTMENU,
                              16, 15,
                              ID_PRINT_DEATH_ACT,         // Act
                              ID_PRINT_DEATH_CERIFICATE,  // Death Certificate
                              ID_OUTNMENU,                // Birth Certificate
                              ID_OUTNMENU,                // Marriage Certificate
                              ID_OUTNMENU,                // Certificate with red check
                              ID_PRINT_DEATH_FORTAX,      // List 1
                              ID_PRINT_DEATH_FORTAX_13,   // List 2
                              ID_PRINT_DEATH_FORSOCPROT,  // List 2
                              ID_PRINT_DEATH_DOV,
                              ID_PRINT_DEATH_DOV43,       // Paper with blue lines
                              ID_PRINT_DEATH_CHILDREN,    // Paper with pen
                              ID_PRINT_BLANK_REGISTER,
                              ID_PRINT_DEATH_ABC,
                              ID_PRINT_DEATH_PASSPORTS,
                              NULL};

/////////////////////////////////////////////////////////////////////////////
// CEraForm

IMPLEMENT_DYNAMIC(CEraForm, CDaoRecordViewBG)

CEraForm::CEraForm(UINT nIDTemplate)
         :CDaoRecordViewBG( nIDTemplate ) {
  //{{AFX_DATA_INIT(CEraForm)
  //}}AFX_DATA_INIT
  m_idTemplate = nIDTemplate;
  m_bEnabled = TRUE;
  m_fEnableRelayEvent = true;
  m_pSet = NULL;
  m_nPrinPos = CONTEXT_UNKNWOWN;
  m_ShownCtrlId = 0;
  m_fNewRecord = FALSE;
  m_LastCtrlId = 0;
  m_ID = -1;
  m_fPrintToWord = FALSE;
  m_fUpdateNavigateBars = TRUE;
  m_pFocused = NULL;
}

CEraForm::~CEraForm() {
}

int CEraForm::GetFormID() {
  switch(m_nPrinPos) {
    case CONTEXT_BIRTH:     return ID_BIRTH;
    case CONTEXT_MARRIAGE:  return ID_MARRIAGE;
    case CONTEXT_DIVORCE:   return ID_DIVORCE;
    case CONTEXT_CHANGE:    return ID_CHANGE;
    case CONTEXT_DEATH:     return ID_DEATH;
  }
  return ID_UNKNOWN;
}
void CEraForm::ResetControls() {
	CWnd* pWnd = GetWindow(GW_CHILD);
  while(pWnd){
    if ( pWnd->IsKindOf(RUNTIME_CLASS(CComboBox)) ) {
      ((CComboBox*)pWnd)->SetCurSel(-1);
    }
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
}

bool CEraForm::RecordNew() {
  bool bOk = true;
  ResetControls();
  m_fNewRecord = TRUE;
  try {
    if ( m_pSet->CanAppend() ) {
      m_pSet->AddNew();
      if ( m_pSet->CanUpdate() ) {
        m_pSet->Update();
        m_pSet->SetBookmark( m_pSet->GetLastModifiedBookmark() );
      }
    }
  }
  catch (CDaoException* e) {
    e->Delete();
    bOk = false;
  }
  if ( bOk )
    SetFocusToFirstControl();
  return bOk;
}
void CEraForm::EmptyTable() {
  if ( theApp.m_fReadOnly ) {
    EnableForm(false);
    return;
  }
  if ( m_pSet && m_pSet->IsEOF() && m_pSet->IsBOF() ) {
    EnableForm(false);
    m_tooltip.HideTooltip();
    bool fMakeNewRecord = false;
    switch( GetFormID() ) {
      case ID_BIRTH     : if ( dm_fNewBirth )   { fMakeNewRecord = true; dm_fNewBirth   = FALSE; }
        break;
      case ID_MARRIAGE  : if ( dm_fNewMarrige ) { fMakeNewRecord = true; dm_fNewMarrige = FALSE; }
        break;
      case ID_DIVORCE   : if ( dm_fNewDivorce ) { fMakeNewRecord = true; dm_fNewDivorce = FALSE; }
        break;
      case ID_CHANGE    : if ( dm_fNewChange )  { fMakeNewRecord = true; dm_fNewChange  = FALSE; }
        break;
      case ID_DEATH     : if ( dm_fNewDeath  )  { fMakeNewRecord = true; dm_fNewDeath   = FALSE; }
        break;
    }
    if ( fMakeNewRecord ) {
      OnRecordNew();
      return;
    }
    CEmptyTableDlg dlg(this);
    dlg.m_nPrinPos = m_nPrinPos;
    if ( IDYES==dlg.DoModal() && dlg.m_FormID != ID_UNKNOWN ) {
      if ( GetFormID()==dlg.m_FormID ) {
        OnRecordNew();
      }
      else {
        AfxGetMainWnd()->PostMessage(WM_COMMAND, MAKEWPARAM(dlg.m_FormID, 0), 0);
      }
    }
  }
}
void CEraForm::SetFont() {
  SendMessageToDescendants(WM_SETFONT, (WPARAM)(HFONT)theApp.m_Font, MAKELPARAM(1, 0), true, true);
  CWnd::SetFont(&theApp.m_Font, true);
  CRect r;
  GetClientRect(&r);
  OnSize(SIZE_RESTORED, r.Width(), r.Height());
}
void CEraForm::EnableForm(BOOL bEnable) {
  if ( m_bEnabled==bEnable )
    return;
  if ( FALSE==m_bEnabled )
    AfxGetMainWnd()->SetFocus();

  SetRedraw(FALSE);
  CWnd* pWnd = GetWindow(GW_CHILD);
  while( pWnd ) {
    pWnd->EnableWindow(bEnable);
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
  m_bEnabled = bEnable;
  SetRedraw(TRUE);
  InvalidateRect(NULL);
}
void CEraForm::Refresh() {
  if ( m_pSet && m_pSet->IsOpen() ) {
    m_pSet->Close(); 
    delete m_pSet;
    m_pSet = NULL;
    OnGetRecordset(); // Необходимо перечитать рекордсет после импорта данных
    if ( false==(m_pSet->IsEOF() && m_pSet->IsBOF()) ) { // Есть данные?
      m_pSet->MoveLast();
      EnableForm(true);   // разрешаем редактирование
      UpdateData(false);  // и заполняем форму данными.
      CEraForm::OnMove(ID_RECORD_LAST);
    }
  }
}
void CEraForm::DoDataExchange(CDataExchange* pDX) {
  CDaoRecordViewBG::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CEraForm)
    // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEraForm, CDaoRecordViewBG)
  //{{AFX_MSG_MAP(CEraForm)
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
  ON_UPDATE_COMMAND_UI(ID_PRINT, OnUpdatePrint)
  ON_COMMAND(ID_PRINT, OnPrint)
  ON_COMMAND(ID_WORD, OnWord)
  ON_COMMAND(ID_TEMPLATES, OnTemplates)
  ON_UPDATE_COMMAND_UI(ID_WORD, OnUpdatePrint)
  ON_UPDATE_COMMAND_UI(ID_TEMPLATES, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI_RANGE(ID_PRINT_FIRST, ID_PRINT_LAST, OnUpdatePrintItem)
  ON_COMMAND_RANGE(ID_PRINT_FIRST, ID_PRINT_LAST, OnPrintItem)
  ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
  ON_COMMAND(ID_HELP, OnHelp)
  ON_WM_HELPINFO()
  ON_MESSAGE(WM_EM_HIDE_TOOLTIPS, OnHideTooltips)
  ON_MESSAGE(WM_EM_SHOW_TOOLTIPS, OnShowTooltips)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraForm diagnostics

#ifdef _DEBUG
void CEraForm::AssertValid() const {
  CDaoRecordViewBG::AssertValid();
}

void CEraForm::Dump(CDumpContext& dc) const {
  CDaoRecordViewBG::Dump(dc);
}
#endif //_DEBUG

void  CEraForm::SetBookMarks() {
  CDaoRecordset* pRecordset = OnGetRecordset();
  // recordset must be allocated already
  ASSERT(pRecordset != NULL);
  if (!pRecordset->IsEOF())  {
    // Determine recordset properties for move button enabling
    if (pRecordset->CanBookmark()) {
      // Get the bookmark of the first record
      m_varBookmarkCurrent = pRecordset->GetBookmark();
      if ( CDaoRecordViewBG::IsOnFirstRecord() )
        m_varBookmarkFirst = m_varBookmarkCurrent;
      if ( CDaoRecordViewBG::IsOnLastRecord() )
        m_varBookmarkLast = m_varBookmarkCurrent;
    }

    // Enable forward scrolling buttons
    m_nStatus |= AFX_DAOVIEW_SCROLL_NEXT;

    // Enable backward scrolling buttons if possible
    if (pRecordset->CanScroll()) {
      m_nStatus |= AFX_DAOVIEW_SCROLL_LAST;
      m_nStatus |= AFX_DAOVIEW_SCROLL_BACKWARD;
    }
    else {
      m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
      m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
    }
  }
}

void  CEraForm::SetDefaultDateReg(UINT idForm) {
  if ( FALSE==m_bEnabled )
    return;
  CString s;
  GetDlgItem(IDC_DATEREG)->GetWindowText(s);
  if ( s.IsEmpty() ) {
    SYSTEMTIME st;
    GetLocalTime(&st);
    s.Format(_T("%02d.%02d.%04d"), st.wDay, st.wMonth, st.wYear);
    GetDlgItem(IDC_DATEREG)->SetWindowText(s);
  }
}

bool CEraForm::SetDefaultNumber(short& Number) {
  CString sNumber;
  bool bRet = true;
  CEdit* pEdit = (CEdit*)GetDlgItem(IDC_NUMBER);
  pEdit->GetWindowText(sNumber);
  CDaoRecordset* pSet = OnGetRecordset();
  if ( pSet ) {
    long lNum;
    COleVariant ovNumber;
    try {
      COleVariant bm = pSet->GetBookmark();
      pSet->MoveLast();
      pSet->GetFieldValue(_T("NUMBER"), ovNumber);
      lNum = V_UI2(&ovNumber);
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

/////////////////////////////////////////////////////////////////////////////
// CEraForm message handlers
CDaoRecordset* CEraForm::OnGetRecordset() {
  return NULL;
}

BOOL CEraForm::OnMove(UINT nIDMoveCommand) {
  ASSERT_VALID(this);

  CDaoRecordset* pSet = OnGetRecordset();
  ResetDaoError();
  try {
    if (pSet->CanUpdate()) {
      pSet->Edit();
      if (!UpdateData())
        return TRUE;

      if (pSet->IsFieldDirty(NULL)) {
        #ifndef FREE_LICENCE
        BOOL fRDFFieldsDirty = IsRDFFieldsDirty();
        #endif // FREE_LICENCE
        pSet->Update();
        #ifndef FREE_LICENCE
        if ( fRDFFieldsDirty ) {
          SetRDFFields();
        }
        #endif // FREE_LICENCE
      }
      else {
        pSet->CancelUpdate();
      }
    }
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
    e->ReportError();
    #endif
    e->Delete();
    return FALSE;
  }
  if ( IsDaoError() ) {
    return FALSE;
  }

  BOOL bBookmarkable = pSet->CanBookmark();
  BOOL bScrollable = pSet->CanScroll();

  switch (nIDMoveCommand) {
    case ID_RECORD_PREV:
      pSet->MovePrev();

      if (!pSet->IsBOF()) {
        if (bBookmarkable)
          m_varBookmarkCurrent = pSet->GetBookmark();

        // Enable forward scrolling
        m_nStatus |= AFX_DAOVIEW_SCROLL_NEXT;

        if (bScrollable) {
          m_nStatus |= AFX_DAOVIEW_SCROLL_LAST;

          if (IsOnFirstRecord())
            // Disable backward scrolling
            m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
          else
            m_nStatus |= AFX_DAOVIEW_SCROLL_BACKWARD;
        }
        else {
          m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
          m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
        }
        break;
      }
      // Fall through to reset to first record

    case ID_RECORD_FIRST:
      pSet->MoveFirst();

      // backward scrolling never allowed after movefirst
      m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;

      if (pSet->IsEOF()) {
        // Empty recordset, disable forward too
        m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;
        m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
      }
      else {
        if (bBookmarkable) {
          m_varBookmarkCurrent = pSet->GetBookmark();
          m_varBookmarkFirst = m_varBookmarkCurrent;
        }

        // Enable forward scrolling
        m_nStatus |= AFX_DAOVIEW_SCROLL_NEXT;

        if (bScrollable)
          m_nStatus |= AFX_DAOVIEW_SCROLL_LAST;
        else
          m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
      }
      break;

    case ID_RECORD_NEXT:
      pSet->MoveNext();

      if (!pSet->IsEOF()) {
        if (bBookmarkable)
          m_varBookmarkCurrent = pSet->GetBookmark();

        if (IsOnLastRecord()) {
          // Disable forward scrolling
          m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;
          m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
        }
        else {
          m_nStatus |= AFX_DAOVIEW_SCROLL_NEXT;
          m_nStatus |= AFX_DAOVIEW_SCROLL_LAST;
        }

        if (bScrollable)
          m_nStatus |= AFX_DAOVIEW_SCROLL_BACKWARD;
        else {
          m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
          m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
        }
        break;
      }

      // Can't fall through to move last
      if (!bScrollable) {
        // At the end of forward only recordset
        m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;
        m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
        m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
        break;
      }

      // Fall through to reset to last record

    case ID_RECORD_LAST:
      pSet->MoveLast();

      // forward scrolling never allowed after movelast
      m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;
      m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;

      if (pSet->IsBOF()) {
        // Empty recordset, disable backward too
        m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
      }
      else {
        if (bBookmarkable) {
          m_varBookmarkCurrent = pSet->GetBookmark();
          m_varBookmarkLast = m_varBookmarkCurrent;
        }

        // Enable backward scrolling
        if (bBookmarkable)
          m_nStatus |= AFX_DAOVIEW_SCROLL_BACKWARD;
        else
          m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
      }
      break;

    default:
      // Unexpected case value
      //ASSERT(FALSE);
      break;
  }

  m_fNewRecord = FALSE;

  // Show results of move operation
  UpdateData(FALSE);
  return TRUE;
}

void CEraForm::SetTooltips() {
//  if ( theApp.m_fUseHelper )
    theToolTipCache.Fill(this, m_szFormName, &m_tooltip);
}
void CEraForm::ScrollToControl(CWnd* pWnd) {
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

BOOL CEraForm::PreCreateWindow(CREATESTRUCT& cs) {
	if( !CDaoRecordViewBG::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}
void CEraForm::OnInitialUpdate() {
  m_pParentFrame = (CChildFrame*)GetParentFrame();
  ASSERT(m_pParentFrame);
  m_pParentFrame->m_pView = this;


  if ( m_tooltip.GetSafeHwnd()==NULL ) {
    m_tooltip.Create(this);
    SetDefaults(&m_tooltip);
    SetTooltips();
  }

  g_pMachine->AddCommand( new CIsDebuggerAttached(&m_tooltip, m_pParentFrame) );

  CDaoRecordViewBG::OnInitialUpdate();

  if ( NULL==theApp.m_Font.m_hObject ) {
    CFont* pFont = GetFont();
    if ( pFont ) {
      LOGFONT lf;
      pFont->GetLogFont(&lf);
      theApp.CreateFont(&lf);
      theApp.SaveFont();
    }
  }
  SetFont();
  /*
  CRect rc;
  GetClientRect(&rc);
  OnSize(SIZE_MAXIMIZED, rc.Width(), rc.Height());
  */

}

void CEraForm::OnUpdateRecordFirst(CCmdUI* pCmdUI) {
  CDaoRecordViewBG::OnUpdateRecordFirst(pCmdUI);
}

void CEraForm::OnRecordFirst() {
  //CDaoRecordViewBG::OnMove(ID_RECORD_FIRST);
  OnMove(ID_RECORD_FIRST);
}

void CEraForm::OnUpdateRecordPrev(CCmdUI* pCmdUI) {
  CDaoRecordViewBG::OnUpdateRecordPrev(pCmdUI);
}
void CEraForm::OnRecordPrev() {
  //CDaoRecordViewBG::OnMove(ID_RECORD_PREV);
  OnMove(ID_RECORD_PREV);
}
void CEraForm::OnUpdateRecordNext(CCmdUI* pCmdUI) {
  CDaoRecordViewBG::OnUpdateRecordNext(pCmdUI);
}
void CEraForm::OnRecordNext() {
  //CDaoRecordViewBG::OnMove(ID_RECORD_NEXT);
  OnMove(ID_RECORD_NEXT);
}
void CEraForm::OnUpdateRecordLast(CCmdUI* pCmdUI) {
  CDaoRecordViewBG::OnUpdateRecordLast(pCmdUI);
}
void CEraForm::OnRecordLast() {
  //CDaoRecordViewBG::OnMove(ID_RECORD_LAST);
  OnMove(ID_RECORD_LAST);
}

void CEraForm::Find(long lID) {
  if ( m_ID==lID )
    return;
  OnMove(0);
  CDaoRecordset* pSet = OnGetRecordset();
  try {
    bool bFound = false;
    COleVariant ovKey(lID);
    COleVariant bm = pSet->GetBookmark();
    CString sOldIndex = pSet->GetCurrentIndex();
    pSet->SetCurrentIndex("PrimaryKey");
    if ( pSet->Seek(_T("="), &ovKey) ) {
      bm = pSet->GetBookmark();
      bFound = true;
      m_ID = lID;
    }
    if ( bFound ) {
      pSet->SetCurrentIndex(sOldIndex);
    }
    pSet->SetBookmark(bm);
    if ( !sOldIndex.IsEmpty() ) {
      pSet->SetCurrentIndex(sOldIndex);
      pSet->SetBookmark(bm);
      pSet->Move(0);
    }
    UpdateData(FALSE);
    OnMove(0);
  }
  catch(CDaoException* e) {
    e->Delete();
  }
}
void CEraForm::OnUpdateRecordNew(CCmdUI* pCmdUI) {
  BOOL fEnable = false;
  if ( false==theApp.m_fReadOnly && m_pSet && m_pSet->m_pDAORecordset && m_pSet->IsOpen() )
    fEnable = true;
  pCmdUI->Enable(fEnable);
}

void CEraForm::OnRecordNew() {
  if ( m_pSet ) {
    if ( !(m_pSet->IsEOF() || m_pSet->IsBOF()) ) {
      // m_pSet->Move(0);
      OnMove(0);
    }
    RecordNew();
//    m_pSet->Update();
    m_pSet->SetBookmark( m_pSet->GetLastModifiedBookmark() );
    UpdateData(FALSE);
    m_pSet->Move(0);
    SetBookMarks();

    EnableForm(TRUE);
    OnMove(0);
    m_fNewRecord = TRUE;
#ifndef FREE_LICENCE
    theRegTimer.Next();
#endif
  }
}

void CEraForm::OnUpdateRecordDelete(CCmdUI* pCmdUI) {
  if ( m_pSet->m_pDAORecordset )
    pCmdUI->Enable(( m_pSet!=NULL) & !m_pSet->IsDeleted());
  else
    pCmdUI->Enable( FALSE );
}

void CEraForm::OnRecordDelete() {
  if ( NULL==m_pSet )
    return;

  if ( m_pSet->IsDeleted() )
    return;

  if ( YNDlg(this, IDS_DELETE_CASE, IDS_DELETE_QUESTION) ) {
    try {
      m_pSet->Delete();
      m_pSet->MoveNext();
      if ( m_pSet->IsEOF() ) {
        m_pSet->MovePrev();
        if ( m_pSet->IsBOF() )
          EnableForm(FALSE);
      }
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
    if ( m_pSet->IsBOF() )
      m_pSet->SetFieldNull(NULL);
    UpdateData(FALSE);
  }
  SetBookMarks();
}

void CEraForm::OnUpdatePrint(CCmdUI* pCmdUI) {
  pCmdUI->Enable( m_pSet->m_pDAORecordset != NULL /*&& m_bEnabled*/);
}

/*
void CEraForm::OnBlanksMenu(UINT nPrintID) {
  CNewMenu menu, *pPopup = NULL;
  CRect r;
  menu.LoadMenu(IDR_PRINT);
  pPopup = DYNAMIC_DOWNCAST(CNewMenu,menu.GetSubMenu(CONTEXT_BIRTH_BLANKS));
  ASSERT(pPopup);

  ((CMainFrame*)theApp.m_pMainWnd)->GetCommandButtonRect(m_fPrintToWord ? ID_WORD : ID_PRINT, &r);
  POINT p;
  p.y = r.bottom;
  p.x = r.right;

  LPCTSTR szMenuTitle = m_fPrintToWord ? _T("Експорт Документа") : _T("Перегляд/Друк Документа");

  if ( szMenuTitle )
    pPopup->SetMenuTitle(szMenuTitle, MFT_GRADIENT|MFT_SIDE_TITLE|MFT_LINE);

  int nCmd = pPopup->TrackPopupMenu(TPM_RETURNCMD|TPM_RIGHTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON|TPM_VERTICAL, p.x, p.y, GetParent());
  if ( nCmd ) {
    CString szBlank, sID;
    pPopup->GetMenuString(nCmd, szBlank, MF_BYCOMMAND);
    int nIndex = szBlank.FindOneOf("0123456789");
    if ( nIndex >= 0 ) {
      char c = 0;
      while ( true ) {
        c = szBlank.GetAt(nIndex++);
        if ( '.'==c || IsDigit(c) ) { sID += c; }
        else                        { break;    }
      }
      if ( sID.GetLength() ) {
        CString szOut;
        if ( sID.GetAt(1)=='.' ) sID.Insert(0, '0');
        szBlank.Format(_T("%s\\Blank_%s.rtf"), theApp.m_sTemplatePath, sID);
        szOut.Format(_T("%s\\Blank_%s.rtf"), theApp.m_sOutPath, sID);
        OnBlank(szBlank, szOut);
      }
    }
  }
}
*/
void CEraForm::OnBlankItem() {
  CString szIn, szOut, szID;
  int nIndex = m_szPrintItem.FindOneOf("0123456789");
  if ( nIndex >= 0 ) {
    char c = 0;
    while ( true ) {
      c = m_szPrintItem.GetAt(nIndex++);
      if ( '.'==c || IsDigit(c) ) { szID += c; }
      else                        { break;    }
    }
    if ( szID.GetLength() ) {
      if ( szID.GetAt(1)=='.' ) szID.Insert(0, '0');
      szIn.Format (_T("%s\\Blank_%s.rtf"), theApp.m_sTemplatePath, szID);
      szOut.Format(_T("%s\\Blank_%s.rtf"), theApp.m_sOutPath, szID);
      OnBlank(szIn, szOut);
    }
  }
}
void CEraForm::OnPrintMenu() {
  CNewMenu menu, *pPopup = NULL;
  CRect r;
  menu.LoadMenu(IDR_PRINT);
  pPopup = DYNAMIC_DOWNCAST(CNewMenu,menu.GetSubMenu(m_nPrinPos));
  ASSERT(pPopup);

  ((CMainFrame*)theApp.m_pMainWnd)->GetCommandButtonRect(m_fPrintToWord ? ID_WORD : ID_PRINT, &r);
  POINT p;
  p.y = r.bottom;
  p.x = r.right;

  WORD* pToolId = NULL;

  switch(m_nPrinPos) {
    case CONTEXT_BIRTH       : pToolId = ToolIdBirth;     break;
    case CONTEXT_MARRIAGE    : pToolId = ToolIdMarriage;  break;
    case CONTEXT_DIVORCE     : pToolId = ToolIdDivorce;   break;
    case CONTEXT_CHANGE      : pToolId = ToolIdChange;    break;
    case CONTEXT_DEATH       : pToolId = ToolIdDeath;     break;
  }

  LPCTSTR szMenuTitle = m_fPrintToWord ? _T("Експорт Документа") : _T("Перегляд/Друк Документа");

  if ( szMenuTitle )
    pPopup->SetMenuTitle(szMenuTitle, MFT_GRADIENT|MFT_SIDE_TITLE|MFT_LINE);

  if ( pToolId )
    pPopup->LoadToolBar(pToolId, RGB(192,192,192) );

  int nCmd = pPopup->TrackPopupMenu(TPM_RETURNCMD|TPM_RIGHTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON|TPM_VERTICAL, p.x, p.y, GetParent());
  if ( nCmd ) {
    pPopup->GetMenuString(nCmd, m_szPrintItem, MF_BYCOMMAND);
    OnPrint(nCmd);
  }
}

void CEraForm::OnRTFShell(LPCTSTR szFilename) {
  OnDocShell(szFilename, m_fPrintToWord);
/*
  if ( m_fPrintToWord ) {
    ShellExecute(NULL, "open", szFilename, NULL, NULL, SW_SHOW);
  }
  else {
    if ( theApp.IsMsOffice() ) {
      theApp.m_pWordTemplate->CloseAllDocuments(false);
      theApp.m_pWordTemplate->OpenDocumentFile(szFilename);
    }
    else {
      theApp.m_pOOTemplate->CloseAllDocuments(false);
      theApp.m_pOOTemplate->OpenDocumentFile(szFilename);
    }
  }
*/
}

void CEraForm::OnPrint() {
  m_fPrintToWord = FALSE;
  OnPrintMenu();
}
void CEraForm::OnWord() {
  m_fPrintToWord = TRUE;
  OnPrintMenu();
}

void CEraForm::OnTemplates() {
  CTemplDlg dlg(m_idTemplate, this);
  if ( IDYES==dlg.DoModal() ) {
  }
}

void CEraForm::OnSetfocusCountry(CEraNameComboBox& cmbCountry) {
  if ( cmbCountry.IsEmpty() ) {
    CString s = cmbCountry.GetDefault();
    if ( !s.IsEmpty() )
      cmbCountry.SelectString(-1, s );
    else
      cmbCountry.SetCurSel(-1);
  }
}

void CEraForm::OnSetfocusRegion(CEraNameComboBox& cmbCountry, CEraNameComboBox& cmbRegion, CEraNameComboBox& cmbCity) {
  BOOL fRegionEmpty = cmbRegion.IsEmpty();
  BOOL fCityEmpty   = cmbCity.IsEmpty();
  if ( fRegionEmpty && fCityEmpty ) {
    if ( cmbCountry.IsCurDefault() ) {
      cmbRegion.SetDefault(theIniCache.GetREGION());
      theGeoCache.FillRegionCB(cmbRegion, cmbCountry, theIniCache.GetREGION());
    }
    else {
      cmbRegion.SetDefault(_T(""));
      theGeoCache.FillRegionCB(cmbRegion, cmbCountry, _T("") );
    }
  }
  else if ( fCityEmpty ) {
    theGeoCache.FillRegionCB(cmbRegion, cmbCountry, cmbRegion.GetCurText() );
  }
}

void CEraForm::OnSetfocusDistrict(CEraNameComboBox& cmbRegion, CEraNameComboBox& cmbDistrict) {
  if ( cmbDistrict.IsEmpty() ) {
    if ( cmbRegion.IsCurDefault() ) {
       cmbDistrict.SetDefault(theIniCache.GetDISTRICT());
       theGeoCache.FillDistrictCB(cmbDistrict, cmbRegion, theIniCache.GetDISTRICT());
    }
    else {
      cmbDistrict.SetDefault(_T(""));
      theGeoCache.FillDistrictCB(cmbDistrict, cmbRegion, _T("") );
    }
  }
  else {
    theGeoCache.FillDistrictCB(cmbDistrict, cmbRegion, cmbDistrict.GetCurText() );
  }
}

void CEraForm::OnSetfocusCity(CEraNameComboBox& cmbCountry, CEraNameComboBox& cmbRegion, CEraNameComboBox& cmbDistrict, CEraNameComboBox& cmbCity) {
  if ( cmbCity.IsEmpty() ) {
    if ( cmbRegion.IsCurDefault() || cmbDistrict.IsCurDefault() ) {
       cmbCity.SetDefault(theIniCache.GetCITY());
       theGeoCache.FillCityCB(cmbCity, cmbRegion, cmbDistrict, theIniCache.GetCITY());
    }
    else {
      if ( cmbRegion.IsEmpty() ) {
        theGeoCache.FillCityCBByCountryCities(cmbCity, cmbCountry, cmbCity.GetCurText() );
      }
      else {
        cmbCity.SetDefault(_T(""));
        theGeoCache.FillCityCB(cmbCity, cmbRegion, cmbDistrict, _T("") );
      }
    }
  }
  else {
    if ( cmbRegion.IsEmpty() ) {
      theGeoCache.FillCityCBByCountryCities(cmbCity, cmbCountry, cmbCity.GetCurText() );
    }
    else {
      theGeoCache.FillCityCB(cmbCity, cmbRegion, cmbDistrict, cmbCity.GetCurText() );
    }
  }
}

void CEraForm::OnSetfocusPassportBy(CEraSeriaEdit& PassportSeria, CEraEdit& PassportNumber, CEraComboBox& cmbPassportBy) {
  if ( cmbPassportBy.IsEmpty() ) {
    if ( false==PassportSeria.IsEmpty() || false==PassportNumber.IsEmpty() ) {
      cmbPassportBy.UpdateByDefault();
    }
  }
}

BOOL CEraForm::PreTranslateMessage(MSG* pMsg) {
	// TODO: Add your specialized code here and/or call the base class
  if ( theApp.m_fUseHelper && m_tooltip.GetSafeHwnd() && m_fEnableRelayEvent) {
    if( pMsg->hwnd==m_hWnd )
      m_tooltip.RelayEvent(pMsg);
  }
	return CDaoRecordViewBG::PreTranslateMessage(pMsg);
}

void CEraForm::HideTooltip() {
//  m_tooltip.HideTooltip();
}
void CEraForm::OnHelp() {
  LPCTSTR szHtmFileName = NULL;
  CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
  CChildFrame* pFrame = (CChildFrame*)GetParentFrame();
  if ( IsKindOf(RUNTIME_CLASS(CFormBirth)) ) {
    szHtmFileName = _T("RegBirth");
  }
  else if ( IsKindOf(RUNTIME_CLASS(CFormMarriage)) ) {
    szHtmFileName = _T("RegMarriage");
  }
  else if ( IsKindOf(RUNTIME_CLASS(CFormDivorce)) ) {
    szHtmFileName = _T("RegDivorce");
  }
  else if ( IsKindOf(RUNTIME_CLASS(CFormChange)) ) {
    szHtmFileName = _T("RegChange");
  }
  else if ( IsKindOf(RUNTIME_CLASS(CFormDeath)) ) {
    szHtmFileName = _T("RegDeath");
  }
  if ( pMainFrame->m_GlobalSearchBar.GetSafeHwnd() && pMainFrame->m_GlobalSearchBar.IsWindowVisible() ) {
    szHtmFileName = _T("Search");
  }
  if ( pFrame && pFrame->m_LocalSearchBar.GetSafeHwnd() && pFrame->m_LocalSearchBar.IsWindowVisible() ) {
    szHtmFileName = _T("Search");
  }
  if ( szHtmFileName ) {
    theApp.OnHelp(szHtmFileName);
  }
}
BOOL CEraForm::OnHelpInfo(HELPINFO* pHelpInfo) {
  CWnd* pFromPoint = WindowFromPoint(pHelpInfo->MousePos);
  BOOL bChild = IsChild(pFromPoint);
  if ( bChild ) {
    m_tooltip.HideTooltip();
    CWnd* pControl = GetDlgItem(pHelpInfo->iCtrlId);
    if ( pControl )
      ScrollToControl(pControl);
    ShowHelpTooltipSetFocus(&m_tooltip, this, m_szFormName, CWnd::FromHandle((HWND)pHelpInfo->hItemHandle), pHelpInfo->iCtrlId);
    m_fEnableRelayEvent = false;
    return TRUE;
  }
  else {
    CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
    if ( pMainFrame->m_GlobalSearchBar.GetSafeHwnd() ) {
      bChild = pMainFrame->m_GlobalSearchBar.IsChild(pFromPoint);
      if ( bChild ) {
        return pMainFrame->m_GlobalSearchBar.SendMessage(WM_HELP, 0, (LPARAM)pHelpInfo);
      }
    }
  }
  return FALSE;
  //return CDaoRecordViewBG::OnHelpInfo(pHelpInfo);
}

void CEraForm::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) {
	// TODO: Add your specialized code here and/or call the base class
  if ( pActivateView==this ) {
    if ( bActivate ) {
      if ( IsKindOf(RUNTIME_CLASS(CFormBirth)) ) {
        theApp.m_nCurrentForm = ((CChildFrame*)GetParentFrame())->m_nFormID = ID_BIRTH;
      }
      else if ( IsKindOf(RUNTIME_CLASS(CFormMarriage)) ) {
        theApp.m_nCurrentForm = ((CChildFrame*)GetParentFrame())->m_nFormID = ID_MARRIAGE;
      }
      else if ( IsKindOf(RUNTIME_CLASS(CFormDivorce)) ) {
        theApp.m_nCurrentForm = ((CChildFrame*)GetParentFrame())->m_nFormID = ID_DIVORCE;
      }
      else if ( IsKindOf(RUNTIME_CLASS(CFormChange)) ) {
        theApp.m_nCurrentForm = ((CChildFrame*)GetParentFrame())->m_nFormID = ID_CHANGE;
      }
      else if ( IsKindOf(RUNTIME_CLASS(CFormDeath)) ) {
        theApp.m_nCurrentForm = ((CChildFrame*)GetParentFrame())->m_nFormID = ID_DEATH;
      }
      m_pParentFrame->MDIMaximize();
    }
    else {
    }
  }
	CDaoRecordViewBG::OnActivateView(bActivate, pActivateView, pDeactiveView);

}

HBRUSH CEraForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	HBRUSH hbr = CDaoRecordViewBG::OnCtlColor(pDC, pWnd, nCtlColor);
  ScrollToControl(pWnd);
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CEraForm::OnUpdatePrintItem(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
  pCmdUI->Enable();
	
}
void CEraForm::OnPrintItem(UINT nID) {
	// TODO: Add your command update UI handler code here
  OnPrint(nID);
}
void CEraForm::OnShowWindow( BOOL bShow, UINT nStatus ) {
  CDaoRecordViewBG::OnShowWindow(bShow, nStatus);
}
LRESULT CEraForm::OnHideTooltips(WPARAM, LPARAM) {
  HideTooltip();
  return (LRESULT)0;
}
LRESULT CEraForm::OnShowTooltips(WPARAM, LPARAM) {
  if ( theApp.m_fUseHelper ) {
    m_ShownCtrlId = 0;
    CWnd* pFocus = GetFocus();
    if ( pFocus ) {
      WORD wCtrlId = pFocus->GetDlgCtrlID();
      int nCode = 0;
      if ( pFocus->IsKindOf(RUNTIME_CLASS(CButton)) )
        nCode = BN_SETFOCUS;
      else if ( pFocus->IsKindOf(RUNTIME_CLASS(CEdit)) )
        nCode = EN_SETFOCUS;
      else if ( pFocus->IsKindOf(RUNTIME_CLASS(CComboBox)) )
        nCode = CBN_SETFOCUS;
      SendMessage(WM_COMMAND, MAKEWPARAM(wCtrlId, nCode), (LPARAM)pFocus->m_hWnd);
    }
  }
  return (LRESULT)0;
}

#ifndef FREE_LICENCE
void CEraForm::RegDlgCmd() {
  m_tooltip.HideTooltip();
  int nDates = theIniCache.CalcDates();
  CString szLKey;
  LIC_KEY lc;
  BOOL fValidLKey = theIniCache.IsValidLKey(&lc, &szLKey);
  CRegDlg dlg;
  dlg.m_nDates = nDates;
  dlg.m_RTF_ID = IDR_RTF2;
  if ( fValidLKey ) {
    dlg.m_pValidLC = &lc;
    dlg.m_szValidRegCode = szLKey;
  }
  dlg.DoModal();
}
#endif