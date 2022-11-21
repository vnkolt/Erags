// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Erags.h"

#include "MainFrm.h"
#include "DataManager.h"
#include "ChildFrm.h"
#include "EraForm.h"

#include "HelpMan.h"


#include "WordDocument.h"
#include "WordView.h"
#include "ZipDBDlg.h"

#include "..\Common\CyrString.h"
#include "..\Common\EraMessages.h"
#include "..\Common\EraMessages.h"

#include "..\Controls\ExtLabel.h"
#include "..\Controls\ExtStatusBarComboBox.h"

#include <atlconv.h>
#if _MFC_VER < 0x0800
//#include <afximpl.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TBCB_STYLES (CBS_DROPDOWN|CBS_SORT|WS_VISIBLE|WS_TABSTOP|CBS_OWNERDRAWFIXED|CBS_AUTOHSCROLL|WS_VSCROLL|CBS_HASSTRINGS|CBS_NOINTEGRALHEIGHT)

void CreateBackgroundBitmap();

AFX_STATIC BOOL AFXAPI _AfxRegisterWithIcon(WNDCLASS* pWndCls, LPCTSTR lpszClassName, UINT nIDIcon);



#define EWM_CHECK_WORD_CLIENT (WM_USER+0x101)
#define FOLDER_TREE_ID        332306
#define GLOBAL_SEARCH_BAR_ID  332307
#define NAMELIST_BAR_ID       332308

extern WORD ToolId[];
extern BOOL g_fOverwrite;

static const LOGFONT logFontPages =
{
/*LONG lfHeight*/8,
/*LONG lfWidth*/0,
/*LONG lfEscapement*/0,
/*LONG lfOrientation*/0,
/*LONG lfWeight*/FW_NORMAL,
/*BYTE lfItalic*/FALSE,
/*BYTE lfUnderline*/FALSE,
/*BYTE lfStrikeOut*/FALSE,
/*BYTE lfCharSet*/ANSI_CHARSET,
/*BYTE lfOutPrecision*/0,
/*BYTE lfClipPrecision*/0,
/*BYTE lfQuality*/DEFAULT_QUALITY,
/*BYTE lfPitchAndFamily*/DEFAULT_PITCH,
/*CHAR lfFaceName[LF_FACESIZE]*/_T("MS Sans Serif")
};

static int CALLBACK CompareFuncSurname(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  CListCtrl* pNameList = (CListCtrl*)lParamSort;
  int nItem1, nItem2;
  if ( lParam1==lParam2 )
    return 0;

  LV_FINDINFO fInfo;

  fInfo.flags = LVFI_PARAM;
  fInfo.lParam = lParam1;
  nItem1 = pNameList->FindItem(&fInfo);

  fInfo.flags = LVFI_PARAM;
  fInfo.lParam = lParam2;
  nItem2 = pNameList->FindItem(&fInfo);

  CString s1 = pNameList->GetItemText(nItem1, 0);
  CString s2 = pNameList->GetItemText(nItem2, 0);
  return s1.Collate(s2);
}

static int CALLBACK CompareFuncNumber(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  CListCtrl* pNameList = (CListCtrl*)lParamSort;
  int nItem1, nItem2;

  LV_FINDINFO fInfo;
  fInfo.flags = LVFI_PARAM;

  fInfo.lParam = lParam1;
  nItem1 = pNameList->FindItem(&fInfo);

  fInfo.lParam = lParam2;
  nItem2 = pNameList->FindItem(&fInfo);

  CString s1 = pNameList->GetItemText(nItem1, 0);
  CString s2 = pNameList->GetItemText(nItem2, 0);
  return (atoi(s1) - atoi(s2));
}

void RemoveForID(CListCtrl* pList, long lID) {
  LV_FINDINFO fInfo;
  fInfo.flags = LVFI_PARAM;
  fInfo.lParam = (LPARAM)lID;
  int nItem = pList->FindItem(&fInfo, -1);
  while( nItem != -1 ) {
    pList->DeleteItem(nItem);
    nItem = pList->FindItem(&fInfo, -1);
  }
}

/////////////////////////////////////////////////////////////////////////////
// CEraToolBar
IMPLEMENT_DYNAMIC(CEraToolBar, CToolBar)
BEGIN_MESSAGE_MAP(CEraToolBar, CToolBar)
	//{{AFX_MSG_MAP(CEraToolBar)
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CEraToolBar::CEraToolBar() {
}
CEraToolBar::~CEraToolBar() {
}
void CEraToolBar::SetTooltips() {
/************************************** : by VK at 24.09.2004 22:14:05 **\
  m_tooltip.Create(this);
  SetDefaults(&m_tooltip);
  theToolTipCache.FillForToolBar(this, m_szName, &m_tooltip);
\************************************** : by VK at 24.09.2004 22:14:08 **/
}

BOOL CEraToolBar::OnHelpInfo(HELPINFO* pHelpInfo) {
/************************************** : by VK at 24.09.2004 22:14:15 **\
  int nButtons  = GetToolBarCtrl().GetButtonCount();
  CPoint p = pHelpInfo->MousePos;
  ScreenToClient(&p);
  for( int i(0); i < nButtons; i++ ) {
    CRect rect;
    GetItemRect(i, &rect);
    if ( rect.PtInRect(p) )
      break;
  }
  if ( i < nButtons ) {
    ShowHelpTooltip(&m_tooltip, this, m_szName, GetItemID(i));
  }
\************************************** : by VK at 24.09.2004 22:14:21 **/
  return TRUE;
//  return CToolBar::OnHelpInfo(pHelpInfo);
}

void CEraToolBar::HideTooltip() {
  m_tooltip.HideTooltip();
}

BOOL CEraToolBar::PreTranslateMessage(MSG* pMsg) {
/************************************** : by VK at 24.09.2004 1:39:10 **\
  if ( pMsg->hwnd==m_hWnd ) {
    m_tooltip.RelayEvent(pMsg);
    switch(pMsg->message) {
      case WM_SETCURSOR:
      case WM_HELP:
        {
          int i(0);
          i++;
        }
        break;
    }
  }
\************************************** : by VK at 24.09.2004 1:39:14 **/
  return CToolBar::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// CPreviewBar
CPreviewBar::CPreviewBar() {
  m_szName = _T("PreviewBar");
}

CPreviewBar::~CPreviewBar() {
}

BEGIN_MESSAGE_MAP(CPreviewBar, CToolBar)
	//{{AFX_MSG_MAP(CPreviewBar)
	//}}AFX_MSG_MAP
//	ON_CBN_SELENDOK(ID_CMB_SCALE,OnSelendOkScale)
  ON_CBN_SELCHANGE(ID_CMB_SCALE,OnSelendOkScale)
END_MESSAGE_MAP()

BOOL CPreviewBar::OnCommand(WPARAM wParam, LPARAM lParam) {
	return CToolBar::OnCommand(wParam, lParam);
}

void CPreviewBar::OnSelendOkScale() {
  int nIndex = m_cmbScale.GetCurSel();
  if ( CB_ERR==nIndex )
    return;

  if ( theApp.m_pWordView ) {
    theApp.m_pWordView->OnOnSelendOkScale();
  }
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMainFrameBase)

BEGIN_MESSAGE_MAP(CMainFrame, CMainFrameBase)
	// ON_COMMAND(IDR_PRINT, OnRegistration)
  ON_COMMAND(ID_BIRTH, OnRegBirth)
  ON_COMMAND(ID_MARRIAGE, OnRegMarriage)
  ON_COMMAND(ID_DIVORCE, OnRegDivorce)
  ON_COMMAND(ID_CHANGE, OnRegChange)
  ON_COMMAND(ID_DEATH, OnRegDeath)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
  ON_WM_SHOWWINDOW()
  ON_UPDATE_COMMAND_UI(ID_FOLDER_TREE, OnUpdateFolderTree)
  ON_COMMAND(ID_FOLDER_TREE, OnFolderTree)
	ON_COMMAND(ID_FIND, OnFind)
  ON_COMMAND(ID_NAMES, OnNames)
	ON_WM_MEASUREITEM()
	ON_WM_INITMENU()
	ON_UPDATE_COMMAND_UI(ID_WHAT_IS_IT, OnUpdateWhatIsIt)
	ON_COMMAND(ID_WHAT_IS_IT, OnWhatIsIt)
	ON_UPDATE_COMMAND_UI(ID_REGISTRATION, OnUpdateRegistration)
#ifndef FREE_LICENCE
	ON_COMMAND(ID_REGISTRATION, OnRegDlg)
#endif
	ON_WM_ENTERIDLE()
	ON_WM_SIZE()
  ON_WM_SYSCOMMAND()
	ON_WM_MENUSELECT()
  ON_MESSAGE(WM_SETMESSAGESTRING, OnSetMessageString)
	ON_WM_SYSCOLORCHANGE()
	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
  ON_WM_ACTIVATEAPP()
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_DISPLAYCHANGE, OnDisplayChanged)
  ON_MESSAGE(WM_EM_MESSAGE, OnEmMessage)
  ON_MESSAGE(WM_SETMESSAGESTRING, OnSetMessageString)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateInsert)
  ON_COMMAND(ID_TOGGLE_INSERT, OnToggleInsert)
  ON_WM_HELPINFO()
  ON_MESSAGE(WM_EM_DOZIP, OnDoZip)
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
CMainFrame::CMainFrame() {
	// TODO: add member initialization code here
  m_pBirthFrame = m_pMarriageFrame =
  m_pDivorceFrame = m_pDeathFrame =
  m_pChangeFrame = NULL;
  m_bDragHelp = FALSE;
/*
  m_rtfBitmapIndex = 0;
*/
  m_bShowOnce = false;
  m_pWndLabel = NULL;
  m_pMsgIcons = NULL;
  m_nMsgIcons = 0;

}

CMainFrame::~CMainFrame() {
/*
  m_bmNormal.DeleteObject();
  m_bmHot.DeleteObject();
  m_bmDisabled.DeleteObject();
*/
  if ( m_pMsgIcons ) {
    for( int i(0); i < m_nMsgIcons; i++ ) {
      ::DestroyIcon(m_pMsgIcons[i]);
    }
    delete m_pMsgIcons;
  }
}

void CMainFrame::DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf) {
	CRect rect;
	DWORD dw;
	UINT n;

	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout();
	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(Bar,n,&rect);
}

void CMainFrame::EnablePreviewBar(bool fEnable) {
  if ( fEnable ) {
    m_wndMenuBar.ShowWindow(SW_HIDE);
    m_wndReBar.ShowWindow(SW_HIDE);
    m_wndPreviewBar.ShowWindow(SW_SHOW);
    if ( false==theApp.IsMsOffice() ) {
      m_wndPreviewBar.m_cmbScale.EnableWindow(false);
    }
  }
  else {
    m_wndPreviewBar.ShowWindow(SW_HIDE);
    m_wndMenuBar.ShowWindow(SW_SHOW);
    m_wndReBar.ShowWindow(SW_SHOW);
  }
  RecalcLayout(TRUE);
}

BOOL CMainFrame::GetCommandButtonRect(UINT idBtn, RECT* pRect) {
  CWnd* pWnd = m_wndDlgBar.GetDlgItem(idBtn);
  if ( pWnd ) {
    pWnd->GetWindowRect(pRect);
    return TRUE;
  }
  return FALSE;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CMainFrameBase::OnCreate(lpCreateStruct) == -1)
		return -1;

/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
  CBitmap Toolbars;
  if ( Toolbars.LoadBitmap(IDTB_TOOLBARS) ) {
    BITMAP bmp;
    Toolbars.GetBitmap(&bmp);
    CreateBitmapFromAnotherBitmap(m_bmDisabled, bmp.bmWidth, bmp.bmHeight/3, Toolbars,  0, 0);
    CreateBitmapFromAnotherBitmap(m_bmNormal  , bmp.bmWidth, bmp.bmHeight/3, Toolbars,  0,22);
    CreateBitmapFromAnotherBitmap(m_bmHot     , bmp.bmWidth, bmp.bmHeight/3, Toolbars,  0,44);

    m_wndToolBar.SetTCToolBar(TB_SETIMAGELIST        , m_bmNormal  , 22, RGB(255,0,255));
    m_wndToolBar.SetTCToolBar(TB_SETHOTIMAGELIST     , m_bmHot     , 22, RGB(255,0,255));
    m_wndToolBar.SetTCToolBar(TB_SETDISABLEDIMAGELIST, m_bmDisabled, 22, RGB(255,0,255));
  }
*/

	if (!m_wndPreviewBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
  		!m_wndPreviewBar.LoadToolBar(IDR_REPORTFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

  CRect rect;
  m_wndPreviewBar.SetButtonInfo(2, ID_CMB_SCALE, TBBS_SEPARATOR, 40);

	m_wndPreviewBar.GetItemRect(2, &rect);
  rect.top = 0; rect.bottom = rect.top + 200;
  rect.right += 40;

  if (FALSE==m_wndPreviewBar.m_cmbScale.Create(
			CBS_DROPDOWNLIST|WS_VISIBLE|WS_TABSTOP,
			rect, &m_wndPreviewBar, ID_CMB_SCALE))
	{
		TRACE0("Failed to create combo-box\n");
		return FALSE;
	}
  m_wndPreviewBar.m_Font.CreateFontIndirect(&logFontPages);
  m_wndPreviewBar.m_cmbScale.SetFont(&m_wndPreviewBar.m_Font);

  CToolBarCtrl& tbCtrl = m_wndPreviewBar.GetToolBarCtrl();
  TBBUTTONINFO tbi;

  tbi.dwMask= TBIF_SIZE;
  tbi.cbSize= sizeof(TBBUTTONINFO);

	tbCtrl.GetButtonInfo(ID_CMB_SCALE, &tbi);
  tbi.cx = rect.Width();
  tbCtrl.SetButtonInfo(ID_CMB_SCALE, &tbi);

  m_wndPreviewBar.GetItemRect(3, &rect);

/************************************** : by VK at 23.01.2007 23:04:15 **\
  m_wndPreviewBar.SetButtonStyle( tbCtrl.CommandToIndex(ID_GRIDLINES), TBBS_CHECKBOX );
\************************************** : by VK at 23.01.2007 23:04:18 **/
  m_wndPreviewBar.SetButtonStyle( tbCtrl.CommandToIndex(ID_TOOLBARS),  TBBS_CHECKBOX );

  m_wndPreviewBar.m_cmbScale.AddString(_T("500%"));
  m_wndPreviewBar.m_cmbScale.AddString(_T("200%"));
  m_wndPreviewBar.m_cmbScale.AddString(_T("150%"));
  m_wndPreviewBar.m_cmbScale.AddString(_T("100%"));
  m_wndPreviewBar.m_cmbScale.AddString(_T("75%"));
  m_wndPreviewBar.m_cmbScale.AddString(_T("50%"));
  m_wndPreviewBar.m_cmbScale.AddString(_T("25%"));
  m_wndPreviewBar.m_cmbScale.AddString(_T("10%"));
  m_wndPreviewBar.m_cmbScale.AddString(_T("Â³êíî"));

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

  if (!m_wndMenuBar.Create(this,WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|CBRS_GRIPPER)) {
    TRACE0("Failed to create menu bar\n");
    return -1;      // fail to create
  }
  m_DefaultNewMenu.LoadToolBar(ToolId,RGB(192,192,192)); 


	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable

  m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
  m_wndPreviewBar.EnableDocking(CBRS_ALIGN_ANY);

//	EnableDocking(CBRS_ALIGN_ANY);
////  DockControlBar(&m_wndMenuBar);

	if (!m_wndReBar.Create(this, RBS_BANDBORDERS, WS_CHILD|WS_VISIBLE|/*WS_CLIPSIBLINGS|WS_CLIPCHILDREN|*/CBRS_TOP)) {
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndDlgBar.Create(this))	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}
  m_wndReBar.AddBar(&m_wndDlgBar, GetSysColor(COLOR_3DFACE), GetSysColor(COLOR_3DFACE), NULL, 0);

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
  if (!m_pWndLabel->Create(_T("ÅÐÀÃÑ"), WS_CHILD|WS_VISIBLE|WS_TABSTOP|SS_CENTER,
			                     CRect(0,0,0,0), &m_wndStatusBar, 0)) {
    TRACE(_T("Failed to create label control.\n"));
		return -1;
  }
			
  m_pWndLabel->SetFont(CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT)));
  m_wndStatusBar.AddPane(IDS_PANE_LABEL,0);
  nIndex = m_wndStatusBar.CommandToIndex(IDS_PANE_LABEL);
  m_wndStatusBar.SetPaneWidth(nIndex, 60);
  m_wndStatusBar.AddPaneControl(m_pWndLabel, IDS_PANE_LABEL, true);

/************************************** : by VK at 17.12.2004 23:53:31 **\
  //The Help item it will be right aligned
  MENUITEMINFO info;
  ZeroMemory(&info,sizeof(info));
  info.cbSize = sizeof(info);
  info.fMask = MIIM_TYPE;
  GetMenuItemInfo(m_DefaultNewMenu.m_hMenu,5,true,&info);
  info.fType |= MF_HELP; 
  SetMenuItemInfo(m_DefaultNewMenu.m_hMenu,5,true,&info);
\************************************** : by VK at 17.12.2004 23:53:37 **/
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) {
/*
  if ( NULL==cs.lpszClass ) {
  	WNDCLASS wndcls;
	  memset(&wndcls, 0, sizeof(WNDCLASS));   // start with NULL defaults
    wndcls.lpfnWndProc = (WNDPROC)::DefWindowProc;
	  wndcls.hInstance = AfxGetInstanceHandle();
	  wndcls.hCursor = afxData.hcurArrow;

	  wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	  wndcls.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    if ( _AfxRegisterWithIcon(&wndcls, _T("EragsMainWnd"), AFX_IDI_STD_FRAME) ) {
      cs.lpszClass = _T("EragsMainWnd");
    }
  }
*/

  cs.style &= ~WS_CLIPSIBLINGS;
  cs.style |= WS_CLIPCHILDREN;
  cs.dwExStyle |= WS_EX_CONTEXTHELP;

/************************************** : by VK at 19.11.2005 13:50:43 **\
  if ( m_SysMenu.m_hMenu ) {
    cs.hMenu = m_SysMenu;
  }
\************************************** : by VK at 19.11.2005 13:50:45 **/
  if( !CMainFrameBase::PreCreateWindow(cs) )
    return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

  return TRUE;
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) {
//  m_tooltip.RelayEvent(pMsg);
  if ( pMsg->message==WM_KEYDOWN ) {
    if ( 'P'==pMsg->wParam && GetKeyState(VK_CONTROL)<0 && theApp.m_pWordView ) {
      theApp.m_pWordView->DoWordCommand(WMC_PRINT, 0);
    }
  }
  return CMainFrameBase::PreTranslateMessage(pMsg);
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
void CMainFrame::OnRegistration(UINT nCmdID) {
/************************************** : by VK at 05.06.2005 16:14:34 **\
	if (nCmdID == theApp.m_nCurrentForm) {
		return;  // already selected
  }
\************************************** : by VK at 05.06.2005 16:14:36 **/

  CEraForm* pForm;

  switch(nCmdID) {
		case ID_BIRTH:
      if ( m_pBirthFrame ) {
        pForm = (CEraForm*)m_pBirthFrame->GetActiveView();
        m_pBirthFrame->ActivateFrame(SW_SHOWMAXIMIZED);
        /************************************** : by VK at 04.12.2004 4:51:23 **\
        pForm->FillNavigateBars();
        \************************************** : by VK at 04.12.2004 4:51:26 **/
      }
      else
        theApp.m_pBirthTemplate->OpenDocumentFile(NULL, TRUE);
			break;
		case ID_MARRIAGE:
      if ( m_pMarriageFrame ) {
        pForm = (CEraForm*)m_pMarriageFrame->GetActiveView();
        m_pMarriageFrame->ActivateFrame(SW_SHOWMAXIMIZED);
        /************************************** : by VK at 04.12.2004 4:51:29 **\
        pForm->FillNavigateBars();
        \************************************** : by VK at 04.12.2004 4:51:32 **/
      }
      else
        theApp.m_pMarriageTemplate->OpenDocumentFile(NULL, TRUE);
			break;
    case ID_DIVORCE:
      if ( m_pDivorceFrame ) {
        pForm = (CEraForm*)m_pDivorceFrame->GetActiveView();
        m_pDivorceFrame->ActivateFrame(SW_SHOWMAXIMIZED);
        /************************************** : by VK at 04.12.2004 4:51:35 **\
        pForm->FillNavigateBars();
        \************************************** : by VK at 04.12.2004 4:51:37 **/
      }
      else
        theApp.m_pDivorceTemplate->OpenDocumentFile(NULL, TRUE);
			break;
    case ID_CHANGE:
      if ( m_pChangeFrame ) {
        pForm = (CEraForm*)m_pChangeFrame->GetActiveView();
        m_pChangeFrame->ActivateFrame(SW_SHOWMAXIMIZED);
        /************************************** : by VK at 04.12.2004 4:51:42 **\
        pForm->FillNavigateBars();
        \************************************** : by VK at 04.12.2004 4:51:44 **/
      }
      else
        theApp.m_pChangeTemplate->OpenDocumentFile(NULL, TRUE);
      break;
    case ID_DEATH:
      if ( m_pDeathFrame ) {
        pForm = (CEraForm*)m_pDeathFrame->GetActiveView();
        m_pDeathFrame->ActivateFrame(SW_SHOWMAXIMIZED);
        /************************************** : by VK at 04.12.2004 4:51:16 **\
        pForm->FillNavigateBars();
        \************************************** : by VK at 04.12.2004 4:51:18 **/
      }
      else
        theApp.m_pDeathTemplate->OpenDocumentFile(NULL, TRUE);
			break;
		default:
			//ASSERT(0);
			return;
  }
  theApp.m_nCurrentForm = nCmdID;

}
void CMainFrame::OnRegBirth() {
  OnRegistration(ID_BIRTH);
}
void CMainFrame::OnRegMarriage() {
  OnRegistration(ID_MARRIAGE);
}
void CMainFrame::OnRegDivorce() {
  OnRegistration(ID_DIVORCE);
}
void CMainFrame::OnRegChange() {
  OnRegistration(ID_CHANGE);
}
void CMainFrame::OnRegDeath() {
  OnRegistration(ID_DEATH);
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
  if ( m_GlobalSearchBar.GetSafeHwnd() ) {
    CString sProfile(_T("GlobalSearch"));
	  m_GlobalSearchBar.SaveState(sProfile);
    SaveBarState(sProfile);
  }
  return CMainFrameBase::DestroyWindow();
}

void CMainFrame::OnClose() {
	// TODO: Add your message handler code here and/or call default
  POSITION pos = theApp.m_pWordTemplate->GetFirstDocPosition();
  if ( pos ) {
    theApp.m_pWordTemplate->CloseAllDocuments(FALSE);
    return;
  }
  pos = theApp.m_pOOTemplate->GetFirstDocPosition();
  if ( pos ) {
    theApp.m_pOOTemplate->CloseAllDocuments(FALSE);
    return;
  }
	CMainFrameBase::OnClose();
}

void CMainFrame::OnDestroy()  {
  theApp.m_fExitApp = TRUE;	
  WINDOWPLACEMENT wp;
  if ( GetWindowPlacement(&wp) ) {
    AfxGetApp()->WriteProfileBinary(_TEXT("MainFrame"), _TEXT("WP"), (LPBYTE)&wp, sizeof(wp));
/************************************** : by VK at 13.01.2005 0:29:17 **\
  	CRect r = wndpl.rcNormalPosition;
    theApp.m_Config.SetMainWndRect(r);
    theApp.m_Config.SetMainWndShowFlag(wndpl.showCmd);
\************************************** : by VK at 13.01.2005 0:29:20 **/
  }
	CMainFrameBase::OnDestroy();
	
	// TODO: Add your message handler code here
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) {
	CNewMDIFrameWnd::OnShowWindow(bShow, nStatus);
	
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

void CMainFrame::OnUpdateFolderTree(CCmdUI* pCmdUI) {
	pCmdUI->Enable(TRUE);
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
void CMainFrame::OnFolderTree() {
  if ( m_FileTreeBar.GetSafeHwnd() ) {
    if ( m_FileTreeBar.IsWindowVisible() ) {
      SaveBarState(_T("FolderTree"));
      ShowControlBar(&m_FileTreeBar, FALSE, FALSE); // Hide
    }
    else {
      ShowControlBar(&m_FileTreeBar, TRUE, FALSE); // Show
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

  EnablePreviewBar(false);
}

void CMainFrame::OnUpdateFind(CCmdUI* pCmdUI) {
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnFind() {
	// TODO: Add your command handler code here
  CString sBarStateName = _T("GlobalSearch");
  if ( m_GlobalSearchBar.GetSafeHwnd() ) {
    if ( m_GlobalSearchBar.IsWindowVisible() ) {
      SaveBarState(sBarStateName);
      ShowControlBar(&m_GlobalSearchBar, FALSE, FALSE); // Hide
    }
    else {
      ShowControlBar(&m_GlobalSearchBar, TRUE, FALSE);  // Show
    }
    RecalcLayout();
    return;
  }

  CString sBarTitle;
  //sBarTitle.Format(_T("Ïîøóê ïî âñ³é ÁÄ: %s"), theDataManager.GetYearDBName );
  sBarTitle  = _T("Ïîøóê ïî âñ³é ÁÄ");

  if (!m_GlobalSearchBar.Create(sBarTitle, this, GLOBAL_SEARCH_BAR_ID)) {
    TRACE0("Failed to create GlobalSearchBar.\n");
    return;
  }

  m_GlobalSearchBar.SetBarStyle(m_GlobalSearchBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
  EnableDocking(CBRS_ALIGN_ANY);
  m_GlobalSearchBar.EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_GlobalSearchBar, AFX_IDW_DOCKBAR_RIGHT);

  if (VerifyBarState(sBarStateName)) {
    m_GlobalSearchBar.LoadState(sBarStateName);
    LoadBarState(sBarStateName);
  }

  m_GlobalSearchBar.OnInitialUpdate();
  ShowControlBar(&m_GlobalSearchBar, TRUE, FALSE);  // Show

}

void CMainFrame::OnNames() {
/************************************** : by VK at 03.01.2007 19:37:45 **\
  if ( NULL==m_pNamesBar ) {
    m_pNamesBar = new CNameEditBar(_T("NAMES"), _T("NAME"), _T("²ì'ÿ"));
  }
  CString sBarStateName = _T("NameList");
  if ( m_pNamesBar->GetSafeHwnd() ) {
    if ( m_pNamesBar->IsWindowVisible() ) {
      SaveBarState(sBarStateName);
      ShowControlBar(m_pNamesBar, FALSE, FALSE); // Hide
    }
    else {
      ShowControlBar(m_pNamesBar, TRUE, FALSE);  // Show
    }
    RecalcLayout();
    return;
  }

  CString sBarTitle;
  sBarTitle  = _T("Ñïèñîê ³ìåí");

  if (!m_pNamesBar->Create(sBarTitle, this, NAMELIST_BAR_ID)) {
    TRACE0("Failed to create NamesBar.\n");
    return;
  }

  m_pNamesBar->SetBarStyle(m_pNamesBar->GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
  EnableDocking(CBRS_ALIGN_ANY);
  m_pNamesBar->EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(m_pNamesBar, AFX_IDW_DOCKBAR_LEFT);

  if (VerifyBarState(sBarStateName)) {
    m_pNamesBar->LoadState(sBarStateName);
    LoadBarState(sBarStateName);
  }

  m_pNamesBar->OnInitialUpdate();
  ShowControlBar(m_pNamesBar, TRUE, FALSE);  // Show
\************************************** : by VK at 03.01.2007 19:37:50 **/
}
void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
/************************************** : by VK at 24.05.2006 5:56:38 **\
  if(!CNewMenu::OnMeasureItem(GetCurrentMessage())) {
    CMainFrameBase::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
  }
\************************************** : by VK at 24.05.2006 5:56:42 **/
}

void CMainFrame::OnInitMenu(CMenu* pMenu) {
	CMainFrameBase::OnInitMenu(pMenu);
	// TODO: Add your message handler code here

/************************************** : by VK at 13.01.2004 3:48:35 **\
  CMenu* pFileMenu = pMenu->GetSubMenu(0);
  if ( m_FileMenu.m_hMenu==NULL ) {
    m_FileMenu.Attach(pMenu->m_hMenu);
    m_FileMenu.ModifyMenu(ID_FILE_OPEN, MF_BYPOSITION|MF_OWNERDRAW|MF_STRING, ID_FILE_OPEN, "File");
  }
\************************************** : by VK at 13.01.2004 3:48:37 **/
}

/************************************** : by VK at 11.12.2004 0:10:58 **\
HMENU CMainFrame::NewMenu() {
	// Load the menu from the resources
	m_doc_menu.LoadMenu(IDR_MAINFRAME);
	
	// Use ModifyODMenu to add a bitmap to a menu options.The first parameter
	// is the menu option text string.If it's NULL, keep the current text
	// string.The second option is the ID of the menu option, or the menu
	// option text (use this for adding bitmaps to popup options) to change.
	// The third option is the resource ID of the bitmap.This can also be a
	// toolbar ID in which case the class searches the toolbar for the
	// appropriate bitmap.Only Bitmap and Toolbar resources are supported.

  m_doc_menu.ModifyODMenu(NULL,ID_FILE_NEW,     IDB_NEW);
  m_doc_menu.ModifyODMenu(NULL,ID_RECORD_FIRST, IDB_NEW);
  m_doc_menu.ModifyODMenu(NULL,ID_RECORD_PREV,  IDB_NEW);
  m_doc_menu.ModifyODMenu(NULL,ID_RECORD_NEXT,  IDB_NEW);
  m_doc_menu.ModifyODMenu(NULL,ID_RECORD_LAST,  IDB_NEW);
  m_doc_menu.ModifyODMenu(NULL,ID_RECORD_NEW,   IDB_NEW);
  m_doc_menu.ModifyODMenu(NULL,ID_RECORD_DELETE,IDB_NEW);


	// Another method for adding bitmaps to menu options is through the
	// LoadToolbars member function.This method allows you to add all
	// the bitmaps in a toolbar object to menu options (if they exist).
	// The first function parameter is an array of toolbar id's.
	// The second is the number of toolbar id's. There is also a
	// function called LoadToolbar that just takes an id.

	m_doc_menu.LoadToolbar(IDR_MAINFRAME);
	return(m_doc_menu.Detach());
}

HMENU CMainFrame::NewDefaultMenu() {
	static UINT toolbars[]= { IDR_MAINFRAME};

	m_default_menu.LoadMenu(IDR_MAINFRAME);
	m_default_menu.LoadToolbars(toolbars,1);
	return(m_default_menu.Detach());
}
\************************************** : by VK at 11.12.2004 0:11:02 **/

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
  CFrameWnd* pFrame = GetActiveFrame();
  if ( pFrame ) {
    CEraForm* pForm = (CEraForm*)pFrame->GetActiveView();
    if ( pForm && pForm->IsKindOf(RUNTIME_CLASS(CEraForm)) ) {
      pForm->m_tooltip.HideTooltip();
    }
  }	
	return CMainFrameBase::OnCommand(wParam, lParam);
}

void CMainFrame::OnUpdateWhatIsIt(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
}

void CMainFrame::OnWhatIsIt() {
	// TODO: Add your command handler code here
  // m_bDragHelp = TRUE;
  POINT p;
  GetCursorPos(&p);
  PostMessage(WM_SYSCOMMAND, (WPARAM)SC_CONTEXTHELP, MAKELPARAM(p.x, p.y));
}
void CMainFrame::OnUpdateRegistration(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
  BOOL fEnable = false;
  CFrameWnd* pFrame = GetActiveFrame();
  if ( pFrame ) {
    CView* pView = pFrame->GetActiveView();
    if ( pView && pView->IsKindOf(RUNTIME_CLASS(CEraForm)) ) {
      fEnable = true;
    }
  }
  pCmdUI->Enable(fEnable);
}

#ifndef FREE_LICENCE
void CMainFrame::OnRegDlg() {
  CFrameWnd* pFrame = GetActiveFrame();
  if ( pFrame ) {
    CEraForm* pForm = (CEraForm*)pFrame->GetActiveView();
    if ( pForm && pForm->IsKindOf(RUNTIME_CLASS(CEraForm)) ) {
      pForm->RegDlgCmd();
    }
  }
}
#endif // FREE_LICENCE

BOOL CMainFrame::OnHelpInfo(HELPINFO* pHelpInfo) {
  CEraForm* pForm = NULL;
  switch(theApp.m_nCurrentForm) {
    case ID_BIRTH:
      if ( m_pBirthFrame )
        pForm = (CEraForm*)m_pBirthFrame->GetActiveView();
      break;
    case ID_MARRIAGE:
      if ( m_pMarriageFrame )
        pForm = (CEraForm*)m_pMarriageFrame->GetActiveView();
      break;
    case ID_DIVORCE:
      if ( m_pDivorceFrame )
        pForm = (CEraForm*)m_pDivorceFrame->GetActiveView();
      break;
    case ID_CHANGE:
      if ( m_pChangeFrame )
        pForm = (CEraForm*)m_pChangeFrame->GetActiveView();
      break;
    case ID_DEATH:
      if ( m_pDeathFrame )
        pForm = (CEraForm*)m_pDeathFrame->GetActiveView();
      break;
  }
  return CMainFrameBase::OnHelpInfo(pHelpInfo);
}

void CMainFrame::OnEnterIdle(UINT nWhy, CWnd* pWho) 
{
  m_tooltip.OnEnterIdle(nWhy, pWho);
/************************************** : by VK at 25.05.2004 0:03:57 **\
	CMainFrameBase::OnEnterIdle(nWhy, pWho);
	
	// TODO: Add your message handler code here
\************************************** : by VK at 25.05.2004 0:04:00 **/
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) {
	CMainFrameBase::OnSize(nType, cx, cy);

  if ( NULL==theApp.m_pWordView ) {
    CView* pView = theApp.GetGetActiveForm();
    if ( pView ) {
      CChildFrame* pFrame = (CChildFrame*)pView->GetParentFrame();
      if ( pFrame ) {
        pFrame->m_pView->SendMessage(WM_EM_HIDE_TOOLTIPS);
        pFrame->MDIMaximize();
        pFrame->m_pView->SendMessage(WM_EM_SHOW_TOOLTIPS);
      }
    }
  }
	// TODO: Add your message handler code here
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam) {
  CMainFrameBase::OnSysCommand(nID, lParam);
/************************************** : by VK at 19.11.2005 13:29:23 **\
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
\************************************** : by VK at 19.11.2005 13:29:26 **/
}

void CMainFrame::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) {
	CMainFrameBase::OnMenuSelect(nItemID, nFlags, hSysMenu);
  if ( 0==(MF_SYSMENU & nFlags) ) {
    SendMessage(WM_SETMESSAGESTRING, nItemID);
  }
}
LRESULT CMainFrame::OnSetMessageString(WPARAM wParam, LPARAM lParam) {
  if ( m_pMsgIcons ) {
    m_wndMsgIcon.SetIcon( m_pMsgIcons[EM_INFO] );
  }
  return CMainFrameBase::OnSetMessageString(wParam, lParam);
}

LRESULT CMainFrame::OnEmMessage(WPARAM wParam, LPARAM lParam) {
  if ( m_pMsgIcons && 0 <= wParam && wParam < m_nMsgIcons ) {
    SendMessage(WM_SETMESSAGESTRING, 0, lParam);
    m_wndMsgIcon.SetIcon( m_pMsgIcons[wParam] );
  }
  return 0L;
}

void CMainFrame::OnSysColorChange() {
	CMainFrameBase::OnSysColorChange();
	// TODO: Add your message handler code here
	m_wndDlgBar.SetColors(TRUE);
}

LRESULT CMainFrame::OnDisplayChanged(WPARAM wParam, LPARAM lParam) {
  CreateBackgroundBitmap();
  return 0L;
}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) {
	// TODO: Add your message handler code here and/or call default
	CRect r;
  GetClientRect(&r);
  pDC->FillSolidRect(&r, 0x808080);

	return TRUE;//CMainFrameBase::OnEraseBkgnd(pDC);
}

#if _MSC_VER < 1300
void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask)
#else
void CMainFrame::OnActivateApp(BOOL bActive, DWORD hTask)
#endif
{
  if ( bActive && IsWindowVisible() ) {
    SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_DRAWFRAME|SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
  }
}

LRESULT CMainFrame::OnDoZip(WPARAM, LPARAM) {
  CString sDatabase = theDataManager.GetYearDBName();
  theApp.m_pBirthTemplate->CloseAllDocuments(FALSE);
  theApp.m_pMarriageTemplate->CloseAllDocuments(FALSE);
  theApp.m_pDivorceTemplate->CloseAllDocuments(FALSE);
  theApp.m_pChangeTemplate->CloseAllDocuments(FALSE);
  theApp.m_pDeathTemplate->CloseAllDocuments(FALSE);
  theApp.m_pWordTemplate->CloseAllDocuments(FALSE);
  theApp.m_pOOTemplate->CloseAllDocuments(FALSE);
  theDataManager.CloseDatabases();

  AfxGetMainWnd()->InvalidateRect(NULL);
  CZipDBDlg dlg( AfxGetMainWnd() );
  dlg.DoModal();
  theDataManager.OpenDatabases(sDatabase);
  theApp.OpenDocument(sDatabase, theApp.m_nCurrentForm);
  return 0L;
}
