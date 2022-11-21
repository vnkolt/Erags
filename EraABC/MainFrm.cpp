// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "EraABC.h"

#include "MainFrm.h"
#include "HelpMan.h"
#include "FormABC.h"
#include "TabView.h"

#include "..\Controls\FileTreeView.h"
#include "..\Controls\ExtLabel.h"
#include "..\Controls\ExtStatusBarComboBox.h"
#include "..\Common\EraMessages.h"


//#include "..\Controls\CPPTooltip\PPTooltip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FOLDER_TREE_ID  332306

extern BOOL g_fOverwrite;

WORD ToolId[] = { IDR_NEWMENU256,
                  16, 15,

                  ID_FILE_NEW,
                  ID_FILE_OPEN,
                  ID_FOLDER_TREE,

                  ID_EDIT_CUT,
                  ID_EDIT_COPY,
                  ID_EDIT_PASTE,
                  ID_FILE_PRINT,

                  ID_APP_ABOUT,

                  ID_WINDOW_NEW,
                  ID_WINDOW_CASCADE,
                  ID_WINDOW_TILE_HORZ,
                  ID_WINDOW_TILE_VERT,

                  ID_RECORD_FIRST,
                  ID_RECORD_PREV,
                  ID_RECORD_NEXT,
                  ID_RECORD_LAST,
                  ID_RECORD_NEW,
                  ID_RECORD_DELETE,

                  ID_APP_EXIT,
                  ID_DEFAULT_HELP,
                  ID_HELP_UKR,
                  ID_HELP_RUS,
                  ID_BIRTH,
                  ID_MARRIAGE,
                  ID_DIVORCE,
                  ID_CHANGE,
                  ID_DEATH,
                  0xFFFF/*ID_ZIPDB*/,
                  ID_WHAT_IS_IT,
                  NULL};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CMainFrameBase)

BEGIN_MESSAGE_MAP(CMainFrame, CMainFrameBase)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
  ON_UPDATE_COMMAND_UI(ID_FOLDER_TREE, OnUpdateFolderTree)
	ON_COMMAND(ID_FOLDER_TREE, OnFolderTree)
  ON_UPDATE_COMMAND_UI(ID_WHAT_IS_IT, OnUpdateWhatIsIt)
	ON_COMMAND(ID_WHAT_IS_IT, OnWhatIsIt)
  ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_COMMAND(ID_BIRTH,    OnBirth)
	ON_COMMAND(ID_MARRIAGE, OnMarriage)
	ON_COMMAND(ID_DIVORCE,  OnDivorce)
	ON_COMMAND(ID_CHANGE,   OnChange)
	ON_COMMAND(ID_DEATH,    OnDeath)
	ON_WM_MEASUREITEM()
  ON_WM_MENUSELECT()
  ON_MESSAGE(WM_SETMESSAGESTRING, OnSetMessageString)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateInsert)
  ON_COMMAND(ID_TOGGLE_INSERT, OnToggleInsert)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_EM_MESSAGE, OnEmMessage)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_OVR,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame():m_bShowOnce(false), m_pTabView(NULL) {
	// TODO: add member initialization code here
  m_pWndLabel = NULL;
  m_pWndMessageBox = NULL;
  m_pMsgIcons = NULL;
  m_nMsgIcons = 0;
}

CMainFrame::~CMainFrame() {
  m_bmNormal.DeleteObject();
  m_bmHot.DeleteObject();
  m_bmDisabled.DeleteObject();
  if ( m_pMsgIcons ) {
    for( int i(0); i < m_nMsgIcons; i++ ) {
      ::DestroyIcon(m_pMsgIcons[i]);
    }
    delete m_pMsgIcons;
  }
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) {
	if( !CMainFrameBase::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CMainFrameBase::OnCreate(lpCreateStruct) == -1)
		return -1;

  if (!m_wndMenuBar.Create(this,WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|CBRS_GRIPPER))
  {
    TRACE0("Failed to create menu bar\n");
    return -1;      // fail to create
  }

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
//	m_wndToolBar.LoadTCToolBar(32, IDTB_TOOLBAR_NORMAL, IDTB_TOOLBAR_HOT, IDTB_TOOLBAR_DISABLED, RGB(255,0,255));

    CBitmap Toolbars;
    if ( Toolbars.LoadBitmap(IDTB_TOOLBARS) ) {
      BITMAP bmp;
      Toolbars.GetBitmap(&bmp);
      CreateBitmapFromAnotherBitmap(m_bmDisabled, bmp.bmWidth, bmp.bmHeight/3, Toolbars,  0, 0);
      CreateBitmapFromAnotherBitmap(m_bmNormal  , bmp.bmWidth, bmp.bmHeight/3, Toolbars,  0,32);
      CreateBitmapFromAnotherBitmap(m_bmHot     , bmp.bmWidth, bmp.bmHeight/3, Toolbars,  0,64);

      m_wndToolBar.SetTCToolBar(TB_SETIMAGELIST        , m_bmNormal  , 32, RGB(255,0,255));
      m_wndToolBar.SetTCToolBar(TB_SETHOTIMAGELIST     , m_bmHot     , 32, RGB(255,0,255));
      m_wndToolBar.SetTCToolBar(TB_SETDISABLEDIMAGELIST, m_bmDisabled, 32, RGB(255,0,255));
  }

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
  m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);
  //DockControlBar(&m_wndMenuBar);

//  m_wndStatusBar.RemovePane(0);
  m_wndStatusBar.GetStatusBarCtrl().SetMinHeight(26);

  int nIndex = 0;

  m_MsgImageList.Create(IDIL_MESSAGES, 16, 0,RGB(255,255,255));
  m_nMsgIcons = m_MsgImageList.GetImageCount();
  m_pMsgIcons = new HICON[m_nMsgIcons];
  for( int i(0); i < m_nMsgIcons; i++ ) {
    m_pMsgIcons[i] = m_MsgImageList.ExtractIcon(i);
  }

  // message icon
  if (!m_wndMsgIcon.Create(_T(""), WS_CHILD|WS_VISIBLE|WS_TABSTOP|SS_CENTER|SS_ICON|SS_CENTERIMAGE|SS_REALSIZEIMAGE,
			                     CRect(0,0,0,0), &m_wndStatusBar, 0)) {
    TRACE(_T("Failed to create label control.\n"));
		return -1;
  }
  m_wndStatusBar.AddPane(IDS_PANE_ICON,0);
  nIndex = m_wndStatusBar.CommandToIndex(IDS_PANE_ICON);
  m_wndStatusBar.SetPaneWidth(nIndex, 20);
  m_wndStatusBar.AddPaneControl(&m_wndMsgIcon, IDS_PANE_ICON, true);
			
  // label

  m_pWndLabel = new CExtStatusBarLabel;
  if (!m_pWndLabel->Create(_T("ÅðàÀÁÂ"), WS_CHILD|WS_VISIBLE|WS_TABSTOP|SS_CENTER,
			                     CRect(0,0,0,0), &m_wndStatusBar, 0)) {
    TRACE(_T("Failed to create label control.\n"));
		return -1;
  }
			

  m_pWndLabel->SetFont(CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT)));
  m_wndStatusBar.AddPane(IDS_PANE_LABEL,0);
  nIndex = m_wndStatusBar.CommandToIndex(IDS_PANE_LABEL);
  m_wndStatusBar.SetPaneWidth(nIndex, 80);
  m_wndStatusBar.AddPaneControl(m_pWndLabel, IDS_PANE_LABEL, true);


/*
  //The Help item it will be right aligned
  MENUITEMINFO info;
  ZeroMemory(&info,sizeof(info));
  info.cbSize = sizeof(info);
  info.fMask = MIIM_TYPE;
  GetMenuItemInfo(m_DefaultNewMenu.m_hMenu,3,true,&info);
  info.fType |= MF_HELP; 
  SetMenuItemInfo(m_DefaultNewMenu.m_hMenu,3,true,&info);
*/

//  m_wndMenuBar.SetMenu(&m_DefaultNewMenu);
  m_DefaultNewMenu.LoadToolBar(ToolId,RGB(192,192,192));

  theApp.m_pMainWnd = this;

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) {
	// TODO: Add your specialized code here and/or call the base class
  BOOL fOk = CMainFrameBase::OnCreateClient(lpcs, pContext);
  if ( fOk ) {
    m_pTabView = (CTabView*)GetWindow(GW_CHILD);
  }
	return fOk;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMainFrameBase::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMainFrameBase::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) {
	// TODO: Add your message handler code here
	CMainFrameBase::OnShowWindow(bShow, nStatus);
  if(!m_bShowOnce && bShow && !IsWindowVisible()) {
    m_bShowOnce = true;
    WINDOWPLACEMENT *lwp;
    UINT nl;
    if(AfxGetApp()->GetProfileBinary(_TEXT("MainFrame"), _TEXT("WP"), (LPBYTE*)&lwp, &nl)) {
      SetWindowPlacement(lwp);
      delete [] lwp;
    }
  }
}

void CMainFrame::OnUpdateInsert(CCmdUI* pCmdUI) {
	pCmdUI->Enable(g_fOverwrite);
}

void CMainFrame::OnToggleInsert(){
	g_fOverwrite = !g_fOverwrite;
  CWnd* pWnd = GetFocus();
  if ( pWnd ) {
    if ( pWnd->IsKindOf(RUNTIME_CLASS(CEdit)) ) {
/************************************** : by VK at 15.01.2004 0:40:16 **\
      if ( theApp.m_bInsert )
        ::CreateCaret(pWnd->m_hWnd, NULL,  1, 16);
      else
        ::CreateCaret(pWnd->m_hWnd, NULL,  4, 16);
      ::ShowCaret(pWnd->m_hWnd);
\************************************** : by VK at 15.01.2004 0:40:19 **/
    }
    pWnd->SendMessage(WM_KEYDOWN, (WPARAM)VK_INSERT, (LPARAM)1);
  }
}

BOOL CMainFrame::DestroyWindow() {
	// TODO: Add your specialized code here and/or call the base class
  if ( m_FileTreeBar.GetSafeHwnd() ) {
    CString sProfile(_T("FolderTree"));
	  m_FileTreeBar.SaveState(sProfile);
    SaveBarState(sProfile);
  }

  WINDOWPLACEMENT wp;
  GetWindowPlacement(&wp);
  AfxGetApp()->WriteProfileBinary(_TEXT("MainFrame"), _TEXT("WP"), (LPBYTE)&wp, sizeof(wp));
  return CMainFrameBase::DestroyWindow();
}

CDocument* CMainFrame::GetActiveDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	return (CDocument*)theApp.m_pDoc;
/************************************** : by VK at 29.01.2005 9:57:46 **\
	return CMainFrameBase::GetActiveDocument();
\************************************** : by VK at 29.01.2005 9:57:49 **/
}

void CMainFrame::OnUpdateFolderTree(CCmdUI* pCmdUI) {
	pCmdUI->Enable(true);
}
void CMainFrame::RestoreFrame() {
  m_FileTreeBar.ShowWindow(SW_SHOW);
  CRect rect;
  GetWindowRect(&rect);
  rect.left++;
  MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());
  rect.left--;
  MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());
}
void CMainFrame::OnFolderTree() {
  if ( m_FileTreeBar.GetSafeHwnd() ) {
    if ( m_FileTreeBar.IsWindowVisible() ) {
      SaveBarState(_T("FolderTree"));
      ShowControlBar(&m_FileTreeBar, false, false); // Hide the bar
    }
    else {
      ShowControlBar(&m_FileTreeBar, true, false);  // Show the bar
    }
    RecalcLayout();
    return;
  }

  if (!m_FileTreeBar.Create(_T("Äåðåâî ÁÄ ÅÐÀÃÑ"), this, FOLDER_TREE_ID)) {
    TRACE0("Failed to create mybar\n");
    return;
  }

  m_FileTreeBar.SetBarStyle(m_FileTreeBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
  EnableDocking(CBRS_ALIGN_ANY);
  m_FileTreeBar.EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_FileTreeBar, AFX_IDW_DOCKBAR_LEFT);

  CString sProfile(_T("FolderTree"));
  if (VerifyBarState(sProfile)) {
    m_FileTreeBar.LoadState(sProfile);
    LoadBarState(sProfile);
    ShowControlBar(&m_FileTreeBar, TRUE, FALSE); // Show
  }

}
void CMainFrame::OnUpdateWhatIsIt(CCmdUI* pCmdUI) {
  pCmdUI->Enable(true);
}
void CMainFrame::OnWhatIsIt() {
  POINT p;
  GetCursorPos(&p);
  PostMessage(WM_SYSCOMMAND, (WPARAM)SC_CONTEXTHELP, MAKELPARAM(p.x, p.y));
}
BOOL CMainFrame::OnHelpInfo(HELPINFO* pHelpInfo) {
  return CMainFrameBase::OnHelpInfo(pHelpInfo);
}
void CMainFrame::OnDestroy() {
/************************************** : by VK at 02.02.2005 1:24:25 **\
  if ( m_FileTreeBar.GetSafeHwnd() ) {
    m_FileTreeBar.DestroyWindow();
  }
\************************************** : by VK at 02.02.2005 1:24:27 **/
	CMainFrameBase::OnDestroy();
}

BOOL CMainFrame::VerifyBarState(LPCTSTR lpszProfileName) {
    CDockState state;
    state.LoadState(lpszProfileName);

    for (int i = 0; i < state.m_arrBarInfo.GetSize(); i++)
    {
        CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];
        ASSERT(pInfo != NULL);
        int nDockedCount = pInfo->m_arrBarID.GetSize();
        if (nDockedCount > 0)
        {
            // dockbar
            for (int j = 0; j < nDockedCount; j++)
            {
                UINT nID = (UINT) pInfo->m_arrBarID[j];
                if (nID == 0) continue; // row separator
                if (nID > 0xFFFF)
                    nID &= 0xFFFF; // placeholder - get the ID
                if (GetControlBar(nID) == NULL)
                    return FALSE;
            }
        }
        
        if (!pInfo->m_bFloating) // floating dockbars can be created later
            if (GetControlBar(pInfo->m_nBarID) == NULL)
                return FALSE; // invalid bar ID
    }

    return TRUE;
}

CFormABC* CMainFrame::GetActiveForm() {
  return m_pTabView->GetActiveForm();
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) {
	// TODO: Add your specialized code here and/or call the base class
  CFormABC* pForm = GetActiveForm();
  if ( pForm ) {
    pForm->m_tooltip.HideTooltip();
  }	
	return CMainFrameBase::OnCommand(wParam, lParam);
}

void CMainFrame::OnBirth() {
  m_pTabView->SetActiveForm(0);
}
void CMainFrame::OnMarriage() {
  m_pTabView->SetActiveForm(1);
}
void CMainFrame::OnDivorce() {
  m_pTabView->SetActiveForm(2);
}
void CMainFrame::OnChange() {
  m_pTabView->SetActiveForm(3);
}
void CMainFrame::OnDeath() {
  m_pTabView->SetActiveForm(4);
}

void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) {
	// TODO: Add your message handler code here and/or call default
/************************************** : by VK at 24.05.2006 5:56:38 **\
  if(!CNewMenu::OnMeasureItem(GetCurrentMessage())) {
    CMainFrameBase::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
  }
\************************************** : by VK at 24.05.2006 5:56:42 **/
}
void CMainFrame::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) {
	CMainFrameBase::OnMenuSelect(nItemID, nFlags, hSysMenu);
  if ( 0==(MF_SYSMENU & nFlags) ) {
    SendMessage(WM_SETMESSAGESTRING, nItemID);
  }
}

LRESULT CMainFrame::OnSetMessageString(WPARAM wParam, LPARAM lParam) {
  LRESULT lRes = CMainFrameBase::OnSetMessageString(wParam, lParam);
  if ( m_pMsgIcons ) {
    m_wndMsgIcon.SetIcon( m_pMsgIcons[EM_INFO] );
  }
  return lRes;// CMainFrameBase::OnSetMessageString(wParam, lParam);
}
LRESULT CMainFrame::OnEmMessage(WPARAM wParam, LPARAM lParam) {
  if ( m_pMsgIcons && 0 <= wParam && wParam < m_nMsgIcons ) {
    SendMessage(WM_SETMESSAGESTRING, 0, lParam);
    m_wndMsgIcon.SetIcon( m_pMsgIcons[wParam] );
  }
  return 0L;
}

