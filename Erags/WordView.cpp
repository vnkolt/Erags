// WordView.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"

#include "MainFrm.h"
#include "WordDocument.h"
#include "WordCntrItem.h"
#include "WordView.h"
#include "WordTypes.h"
#include "Copy2XLDlg.h"

#include "..\MSO\msoEra.h"
#include "..\ImpExp\ImpExpDll.h"

#include "VBEExt1.h"

#include <atlconv.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define EWM_ERAGS_BAR_NOTIFY (WM_USER+0x101)
//#define EWM_DOWORD_COMMAND   (WM_USER+0x102)

#define CMD_FILE_SAVE_AS   300
#define CMD_PRINT          301
#define CMD_PAGE_SETUP     302
#define CMD_PAGE_MAGNIFIER 303
#define CMD_ONE_PAGE       304
#define CMD_SEVERAL_PAGES  305
#define CMD_SCALE          306
#define CMD_EDIT           307
#define CMD_ON_OFF_WBARS   308
#define CMD_RETURN         309

long aPercentage[] = { 10, 25, 50, 75, 100, 150, 200, 500 };
long NextPercentage(long Percentage) {
  int nCount = sizeof(aPercentage)/sizeof(aPercentage[0]);
  for( int i(0); i < nCount; i++ )
    if ( aPercentage[i] > Percentage )
      return aPercentage[i];
  return aPercentage[nCount-1];
}
long PrevPercentage(long Percentage) {
  int nCount = sizeof(aPercentage)/sizeof(aPercentage[0]);
  for( int i = nCount-1; i >= 0; i-- )
    if ( aPercentage[i] < Percentage )
      return aPercentage[i];
  return aPercentage[0];
}

/////////////////////////////////////////////////////////////////////////////
// CWordView

IMPLEMENT_DYNCREATE(CWordView, CView)

BEGIN_MESSAGE_MAP(CWordView, CView)
  //{{AFX_MSG_MAP(CWordView)
  ON_WM_DESTROY()
  ON_WM_SETFOCUS()
  ON_WM_SIZE()
  ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
  ON_UPDATE_COMMAND_UI(ID_ZOOM_IN, OnUpdateZoomIn)
  ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
  ON_UPDATE_COMMAND_UI(ID_ZOOM_OUT, OnUpdateZoomOut)
  ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
/************************************** : by VK at 23.01.2007 23:01:16 **\
  ON_UPDATE_COMMAND_UI(ID_GRIDLINES,OnEnabledCmd)
  ON_COMMAND(ID_GRIDLINES, OnGridLines)
\************************************** : by VK at 23.01.2007 23:01:18 **/
  ON_UPDATE_COMMAND_UI(ID_TOOLBARS, OnEnabledCmd)
  ON_COMMAND(ID_TOOLBARS, OnToolbars)
  ON_UPDATE_COMMAND_UI(ID_EXCEL, OnEnableExcel)
  ON_COMMAND(ID_EXCEL, OnExcel)
  ON_COMMAND(ID_HELP, OnHelp)
  //}}AFX_MSG_MAP
  // Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordView construction/destruction

CWordView::CWordView()
{
  m_pSelection = NULL;
  // TODO: add construction code here
  m_Percentage = m_PageCount = 0;
  m_fShowTextBoundaries = FALSE;
}

CWordView::~CWordView() {
  theApp.m_pWordView = NULL;
}

BOOL CWordView::PreCreateWindow(CREATESTRUCT& cs)
{
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs

  return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWordView drawing

void CWordView::OnDraw(CDC* pDC)
{
  CWordDocument* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  // TODO: add draw code for native data here
}

CWnd* CWordView::GetWordWnd() {
  return GetWindow(GW_CHILD);
}

void CWordView::RefreshBars(HWND hParent) {
  HWND hWnd = ::GetWindow(hParent, GW_CHILD);
  while ( hWnd ) {
    //::InvalidateRect(hWnd, NULL, TRUE);
    ::ShowWindow(hWnd, SW_HIDE);
    hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
  }
}
void CWordView::RefreshMsoCommandBars() {
// 97: MsoCommandBarDock (Caption: MsoDockTop)
//
  HWND hWndMain = AfxGetMainWnd()->m_hWnd; 
  HWND hWnd = ::FindWindowEx(hWndMain, NULL, _T("MsoCommandBarDock"), NULL);
  while ( hWnd ) {
    RefreshBars(hWnd);
    ::ShowWindow(hWnd, SW_HIDE);
    hWnd = ::FindWindowEx(hWndMain, hWnd, _T("MsoCommandBarDock"), NULL);
  }
}
BOOL CWordView::WasCommandBarVisible(long lIndex) {
  for( int i(0); i < m_CommandBars.GetSize(); i++ ) {
    if ( m_CommandBars.GetAt(i)==(DWORD)lIndex ) {
      return TRUE;
    }
  }
  return FALSE;
}
void CWordView::ShowCommandBars(Word::_Document* pDoc, BOOL fShow) {
  if ( FALSE==fShow ) {
    m_CommandBars.RemoveAll();
  }
  try {
    CommandBars cmdBars(pDoc->GetCommandBars());
    long nBars = cmdBars.GetCount();
    for( long i(1); i <= nBars; i++ ) {
      COleVariant ovIndex(i, VT_I4);
      try {
        LPDISPATCH lpDisp = cmdBars.GetItem(ovIndex);
        CommandBar cb(lpDisp);
        CString sName = cb.GetName();
        if ( FALSE==fShow ) {
          if ( cb.GetVisible() ) {
            cb.SetVisible(FALSE);
            //cb.SetEnabled(FALSE);
            m_CommandBars.Add( (DWORD)i );
            cb.Reset();
          }
        }
        else if ( WasCommandBarVisible(i) ) {
          //cb.SetEnabled(TRUE);
          cb.SetVisible(TRUE);
        }
      }
      catch(CException* e) {
        e->Delete();
      }
    }
  }
  catch(CException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
}
bool CWordView::DoWordCommand(WPARAM wParam, LPARAM lParam/*=0*/) {
  if ( NULL==m_pSelection )
    return false;

  LPUNKNOWN lpUnk = m_pSelection->m_lpObject;

  if ( NULL==lpUnk ) {
    return false;
  }

  LPDISPATCH pDoc;
  LPDISPATCH pApp;
  HRESULT hRes = lpUnk->QueryInterface(IID_IDispatch, (void**)&pDoc);
  if ( FAILED(hRes) )
    return false;

  try {
    Word::_Document     doc(pDoc);
    pApp = doc.GetApplication();
    Word::_Application app(pApp);
    Word::Window window(app.GetActiveWindow());
    Word::View view(window.GetView());
    Word::Zoom zoom(view.GetZoom());
    Word::System system(app.GetSystem());

    m_Percentage = zoom.GetPercentage();

    switch(wParam) {
      case WMC_INIPREVIEW:
        doc.SetGrammarChecked(TRUE);
        doc.SetSpellingChecked(TRUE);
        doc.SetShowGrammaticalErrors(FALSE);
        doc.SetShowSpellingErrors(FALSE);
        ShowCommandBars(&doc, FALSE);
        //RefreshMsoCommandBars();
        GetParentFrame()->RecalcLayout(TRUE);
        window.SetDisplayRulers(FALSE);
        //zoom.SetPercentage(50);
        //view.SetTableGridlines(FALSE);
        m_fShowTextBoundaries = view.GetShowTextBoundaries();
        view.SetShowTextBoundaries(TRUE);
        zoom.SetPageFit(wdPageFitBestFit);
        doc.SetSaved(TRUE);
        doc.Activate();
        OnSetFocus(this);
        view.SetTableGridlines(TRUE);
/************************************** : by VK at 23.01.2007 23:01:37 **\
        CheckUncheck(ID_GRIDLINES, TBSTATE_CHECKED);
\************************************** : by VK at 23.01.2007 23:01:41 **/
        CheckUncheck(ID_TOOLBARS, 0);
//        InvalidateRect(NULL);
        //RefreshMsoCommandBars();
        app.ScreenRefresh();
        break;
/************************************** : by VK at 23.01.2007 23:01:57 **\
      case WMC_GRIDLINES:
        view.SetTableGridlines((BOOL)lParam);
        break;
\************************************** : by VK at 23.01.2007 23:02:01 **/
      case WMC_SETPERCENTAGE:
        zoom.SetPercentage(lParam);
        m_Percentage = zoom.GetPercentage();
        break;
      case WMC_SETPAGETOFIT:
        zoom.SetPageFit(lParam);
        break;
      case WMC_SCREENREFRESH: 
        app.ScreenRefresh();
        break;
      case WMC_SAVE_AS:
        m_pSelection->ExecCommand(OLECMDID_SAVEAS, OLECMDEXECOPT_PROMPTUSER);
        break;
      case WMC_PRINT:
        m_pSelection->ExecCommand(OLECMDID_PRINT, OLECMDEXECOPT_PROMPTUSER);
/************************************** : by VK at 07.08.2005 19:41:56 **\
        ExecWB(OLECMDID_PRINT, OLECMDEXECOPT_PROMPTUSER, NULL, NULL);
        try {
          Dialogs dlgs(app.GetDialogs());
          Dialog dlg(dlgs.Item(wdDialogFilePrint));
          COleVariant ov((long)30000);
          long lRet = dlg.Show(&ov);
          if ( -1==lRet )
            dlg.Execute();
        }
        catch(CException* e) {
          e->Delete();
        }
\************************************** : by VK at 07.08.2005 19:42:01 **/
        break;
      case WMC_PAGE_SETUP: {
          try {
            Word::Dialogs dlgs(app.GetDialogs());
            Word::Dialog dlg(dlgs.Item(wdDialogFilePageSetup/*wdDialogFileDocumentLayout*/));
            COleVariant ov;
            long lRet = dlg.Show(&ov);
            if ( -1==lRet )
              dlg.Execute();
          }
          catch(CException* e) {
            e->Delete();
          }
        }
      break;
/************************************** : by VK at 23.01.2007 23:02:13 **\
      case WMC_EDIT:
        view.SetTableGridlines(TRUE);
        break;
\************************************** : by VK at 23.01.2007 23:02:17 **/
      case WMC_TOOLBARS:
        ShowCommandBars(&doc, (BOOL)lParam);
        break;
      case WMC_GET_PAGE_COUNT :
        {
          _variant_t What((long)wdGoToPage), Which((long)wdGoToLast), Count((long)1), Name("");
           Word::Selection selection(app.GetSelection());
           selection.GoTo(&What, &Which, &Count, &Name);

           LPDISPATCH pDispatch = doc.GetBuiltInDocumentProperties();
           // this pDispatch will be released by the smart pointer, so use FALSE  
           COleDispatchDriver properties(pDispatch, FALSE);
           _variant_t property((long)(wdPropertyPages));
           _variant_t result;

           // The Item method is the default member for the collection object
           properties.InvokeHelper(DISPID_VALUE, 
                                   DISPATCH_METHOD | DISPATCH_PROPERTYGET, 
                                   VT_VARIANT,
                                   reinterpret_cast<void*>(&result),
                                   reinterpret_cast<BYTE*>(VTS_VARIANT),
                                   &property);
           // pDispatch will be extracted from variant Result
           COleDispatchDriver doc_property(result);
           // The Value property is the default member for the Item object
           doc_property.GetProperty(DISPID_VALUE, VT_I4, &m_PageCount);
           // The page count is now in PageCount
        }
        break;
      case WMC_BEGIN_COPY:
        app.SetScreenUpdating(false);
        break;
      case WMC_END_COPY  :
        {
          _variant_t What((long)wdGoToPage), Which((long)wdGoToFirst), Count((long)1), Name("1");
          Word::Selection selection(app.GetSelection());
          selection.GoTo(&What, &Which, &Count, &Name);
          app.SetScreenUpdating(true);
        }
        break;
      case WMC_COPY_PAGE :
        {
          CString szPage;
          szPage.Format(_T("%d"), lParam);
          _variant_t What((long)wdGoToPage), Which((long)wdGoToNext), Count((long)1), Name(szPage);
          _variant_t PageBreak("\\Page");
          Word::Selection selection(app.GetSelection());
          selection.GoTo(&What, &Which, &Count, &Name);
          Word::Bookmarks bookmarks(doc.GetBookmarks());
          LPDISPATCH pDispatch = bookmarks.Item(&PageBreak);
          Word::Bookmark bookmark(pDispatch);
          bookmark.Select();
          selection.Copy();
        }
        break;
      case WMC_COPY_ALL  :
        {
          doc.Select();
          Word::Selection selection(app.GetSelection());
          selection.Copy();
        }
        break;
      case WMC_QUIT:
/************************************** : by VK at 23.01.2007 23:02:24 **\
        view.SetTableGridlines(FALSE);
\************************************** : by VK at 23.01.2007 23:02:27 **/
        view.SetShowTextBoundaries(m_fShowTextBoundaries);
        //ShowCommandBars(&doc, TRUE);
        doc.SetSaved(TRUE);
        break;
    }
  }
  catch(CException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return false;
  }

//  pApp->Release();
//  pDoc->Release();
  return true;
}


BOOL CWordView::IsChecked(UINT id) {
  CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
  CToolBarCtrl& tb = pMainFrm->m_wndPreviewBar.GetToolBarCtrl();
  return tb.IsButtonChecked(id);
}
void CWordView::CheckUncheck(UINT id, BYTE fState) {
  CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
  CToolBarCtrl& tb = pMainFrm->m_wndPreviewBar.GetToolBarCtrl();
  tb.SetState(id, fState);
}

void CWordView::OnInitialUpdate()
{
  CView::OnInitialUpdate();

  theApp.m_pWordView = this;

  ((CMainFrame*)AfxGetMainWnd())->EnablePreviewBar(true);

  // TODO: remove this code when final selection model code is written
  m_pSelection = GetDocument()->m_ctrl;

  DoWordCommand(WMC_INIPREVIEW);
  if ( m_pSelection ) {
    m_pSelection->DoVerb(OLEIVERB_SHOW, this);
  }

}

/////////////////////////////////////////////////////////////////////////////
// CWordView printing
void CWordView::OnDestroy() {
  // Deactivate the item on destruction; this is important
  // when a splitter view is being used.
   theApp.m_pWordView = NULL;
   CView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
    pActiveItem->Deactivate();
    ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   ((CMainFrame*)AfxGetMainWnd())->EnablePreviewBar(false);
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands
BOOL CWordView::IsSelected(const CObject* pDocItem) const {
  // The implementation below is adequate if your selection consists of
  //  only CWordCntrItem objects.  To handle different selection
  //  mechanisms, the implementation here should be replaced.

  // TODO: implement this function that tests for a selected OLE client item

  return pDocItem == m_pSelection;
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CWordView::OnCancelEditCntr() {
  // Close any in-place active item on this view.
  COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
  if (pActiveItem != NULL) {
    pActiveItem->Close();
  }
  ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CWordView::OnSetFocus(CWnd* pOldWnd) {
  COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
  if (pActiveItem != NULL && pActiveItem->GetItemState() == COleClientItem::activeUIState) {
    // need to set focus to this item if it is in the same view
    CWnd* pWnd = pActiveItem->GetInPlaceWindow();
    if (pWnd != NULL)  {
      pWnd->SetFocus();   // don't call the base class
      return;
    }
  }

  CView::OnSetFocus(pOldWnd);
}

void CWordView::OnSize(UINT nType, int cx, int cy) {
  CView::OnSize(nType, cx, cy);
  COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
  if (pActiveItem != NULL)
    pActiveItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
// CWordView diagnostics

#ifdef _DEBUG
void CWordView::AssertValid() const {
  CView::AssertValid();
}

void CWordView::Dump(CDumpContext& dc) const {
  CView::Dump(dc);
}

CWordDocument* CWordView::GetDocument() // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWordDocument)));
  return (CWordDocument*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWordView message handlers
void CWordView::OnOnSelendOkScale() {
  CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
  int nIndex = pMainFrm->m_wndPreviewBar.m_cmbScale.GetCurSel();
  if ( CB_ERR==nIndex )
    return;
  CString s;
  pMainFrm->m_wndPreviewBar.m_cmbScale.GetLBText(nIndex, s);
  if ( s.IsEmpty() )
    return;
  if ( s==_T("Вікно") ) {
    DoWordCommand(WMC_SETPAGETOFIT, wdPageFitFullPage);
  }
  else {
    int scale = atoi(s);
    DoWordCommand(WMC_SETPERCENTAGE, scale);
  }
  DoWordCommand(WMC_SCREENREFRESH);
}

void CWordView::OnEnabledCmd(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
}

void CWordView::OnEnableExcel(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
}

void CWordView::OnGridLines() {
  DoWordCommand(WMC_GRIDLINES, IsChecked(ID_GRIDLINES) );
  DoWordCommand(WMC_SCREENREFRESH);
}
void CWordView::OnToolbars() {
  BOOL fToolBarOn = IsChecked(ID_TOOLBARS);
  DoWordCommand(WMC_TOOLBARS, fToolBarOn );
}
void CWordView::OnExcel() {
  BOOL fCopyAll = true;

  DoWordCommand(WMC_GET_PAGE_COUNT);
  if ( m_PageCount > 1 ) {
    CCopy2XLDlg dlg(this);
    if ( IDYES != dlg.DoModal() ) {
      return;
    }
    fCopyAll = g_fAllToOne;
  }

  CWaitCursor wc;

  DoWordCommand(WMC_BEGIN_COPY);

  BeginCopy2XL();
  if ( fCopyAll ) {
    DoWordCommand(WMC_COPY_ALL);
    Copy2XL(1);
  }
  else {
    for( UINT i(0); i < m_PageCount; i++ ) {
      long nSheet = (i+1);
      DoWordCommand(WMC_COPY_PAGE, (LPARAM)nSheet);
      Copy2XL(nSheet);
    }
  }
  EndCopy2XL();
  DoWordCommand(WMC_END_COPY);

/*
  typedef BOOL (WINAPI* pBeginCopy2XL)();
  typedef BOOL (WINAPI* pCopy2XL)(long nSheet);
  typedef void (WINAPI* pEndCopy2XL)();
  BOOL fCopyAll = true;

  DoWordCommand(WMC_GET_PAGE_COUNT);
  if ( m_PageCount > 1 ) {
    CCopy2XLDlg dlg(this);
    if ( IDYES != dlg.DoModal() ) {
      return;
    }
    fCopyAll = g_fAllToOne;
  }

  HINSTANCE hImpExp = LoadLibrary("ImpExp.dll");
  if( hImpExp ) {
    CWaitCursor wc;
    pBeginCopy2XL fBeginCopy2XL = (pBeginCopy2XL)GetProcAddress(hImpExp, _T("BeginCopy2XL"));
    pCopy2XL      fCopy2XL      = (pCopy2XL)GetProcAddress(hImpExp, _T("Copy2XL"));
    pEndCopy2XL   fEndCopy2XL   = (pEndCopy2XL)GetProcAddress(hImpExp, _T("EndCopy2XL"));

    DoWordCommand(WMC_BEGIN_COPY);

    if ( fBeginCopy2XL && fCopy2XL && fEndCopy2XL ) {
      fBeginCopy2XL();
      if ( fCopyAll ) {
        DoWordCommand(WMC_COPY_ALL);
        fCopy2XL(1);
      }
      else {
        for( UINT i(0); i < m_PageCount; i++ ) {
          long nSheet = (i+1);
          DoWordCommand(WMC_COPY_PAGE, (LPARAM)nSheet);
          fCopy2XL(nSheet);
        }
      }
      fEndCopy2XL();
    }
    DoWordCommand(WMC_END_COPY);
    FreeLibrary(hImpExp);
  }
*/
}
void CWordView::OnUpdateZoomIn(CCmdUI* pCmdUI) {
  pCmdUI->Enable( m_Percentage < 200 );
}
void CWordView::OnZoomIn() {
  DoWordCommand(WMC_SETPERCENTAGE, NextPercentage(m_Percentage));
}
void CWordView::OnUpdateZoomOut(CCmdUI* pCmdUI) {
  pCmdUI->Enable( m_Percentage > 10 );
}
void CWordView::OnZoomOut() {
  DoWordCommand(WMC_SETPERCENTAGE, PrevPercentage(m_Percentage));
}

void CWordView::OnHelp() {
  theApp.OnHelp(_T("PrintDocs"));
}