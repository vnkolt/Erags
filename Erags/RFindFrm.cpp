// MainFrm.cpp : implementation of the CGlobalSearchBar class
//

#include "stdafx.h"
#include "Erags.h"

#include "MainFrm.h"
#include "EraForm.h"
#include "RFindFrm.h"
#include "LeftView.h"
#include "RFindView.h"

#include "HelpMan.h"
#include "RSBirthes.h"
#include "RSMarriages.h"
#include "RSDivorces.h"
#include "RSChanges.h"
#include "RSDeathes.h"

#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"
#include "..\Common\MDB.h"
#include "..\Common\Names.h"


#include "..\Controls\XBrowseForFolder.h"

#include <shlwapi.h>

void AFXAPI AfxSetWindowText(HWND hWndCtrl, LPCTSTR lpszNew);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TBTN_EQU_INDEX       10
#define TBTN_PART_INDEX      11
#define TBTN_BIRTH_INDEX     12
#define TBTN_FATHER_INDEX    13
#define TBTN_MARRIAGE_INDEX  14
#define TBTN_DIVORCE_INDEX   15
#define TBTN_CHANGE_INDEX    16
#define TBTN_DEATH_INDEX     17

LPCTSTR szTDABirth    = _T("BIRTHES");
LPCTSTR szTDAMarriage = _T("MARRIAGES");
LPCTSTR szTDADivorce  = _T("DIVORCES");
LPCTSTR szTDAChange   = _T("CHANGES");
LPCTSTR szTDADeath    = _T("DEATHES");
LPCTSTR szFlags       = _T("Flags");

LPCTSTR szPath      = _T("SearchPath");

int CALLBACK BrowseCallbackProcForSearch(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData){
TCHAR szDir[MAX_PATH];

  switch(uMsg) {
    case BFFM_INITIALIZED:{
      ::SetWindowText(hwnd, _T("Маршрут для пошуку файлів"));
      CString s = GetFilePath(theApp.GetProfileString(_T("Settings"), _T("Database")));
      if( !s.IsEmpty() ) {
        lstrcpy(szDir, s);
        // WParam is TRUE since you are passing a path.
        // It would be FALSE if you were passing a pidl.
        SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)szDir);
      }
      break;
    }
    case BFFM_SELCHANGED: {
      // Set the status window to the currently selected path.
      if (SHGetPathFromIDList((LPITEMIDLIST) lp ,szDir)) {
        SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);
      }
      break;
    }
    default:
      break;
  }
  return 0;
}

CDaoDatabase* OpenDB(LPCTSTR szFileName){
CDaoDatabase* pDB;
CString sPWD;

  pDB = new CDaoDatabase;

  try{
    sPWD = _T(";PWD=");
    //sPWD += GetPassword();
    pDB->Open(szFileName, FALSE, FALSE, sPWD);
  }
  catch(CDaoException* e){
    #ifdef _DEBUG
     e->ReportError();
    #endif
    e->Delete();
    delete pDB;
    return NULL;
  }
  return pDB;
}

void CloseDB(CDaoDatabase* pDB){
  if(pDB && pDB->IsOpen()){
    pDB->Close();
    delete pDB;
  }
}

/////////////////////////////////////////////////////////////////////////////
// CRFindDlgBar dialog
CRFindDlgBar::CRFindDlgBar() {
	//{{AFX_DATA_INIT(CMainDlgBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CRFindDlgBar::SetBkColor(BOOL bRepaint/*=TRUE*/) {
  CWnd* pWnd = GetWindow(GW_CHILD);
  while( pWnd ) {
    ((CButtonST*)pWnd)->SetColor(CButtonST::BTNST_COLOR_BK_IN, bRepaint);
    ((CButtonST*)pWnd)->SetColor(CButtonST::BTNST_COLOR_BK_OUT, bRepaint);
    ((CButtonST*)pWnd)->SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, bRepaint);
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
}

BEGIN_MESSAGE_MAP(CRFindDlgBar, CDialogBarBG)
	//{{AFX_MSG_MAP(CRFindDlgBar)
  ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRFindDlgBar message handlers
BOOL CRFindDlgBar::Create(CWnd* pParentWnd) {
	// TODO: Add your specialized code here and/or call the base class
	if (!CDialogBarBG::Create(pParentWnd, IDTB_RFIND,  CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
		return FALSE;

  m_pBar = (CGlobalSearchBar*)GetParent();

  m_btnNewSearch.SubclassDlgItem(ID_NEW_SEARCH, this);
  m_btnNewSearch.SetBitmaps(IDB_BTN_FILE_NEW, RGB(255,0,255));
  m_btnNewSearch.SetTooltipText(_T("Новий Пошук"));

  m_btnSaveAs.SubclassDlgItem(ID_FILE_SAVE, this);
  m_btnSaveAs.SetBitmaps(IDB_BTN_SAVE_AS, RGB(255,0,255), IDB_BTN_SAVE_AS_OUT, RGB(255,0,255));
  m_btnSaveAs.SetTooltipText(_T("Записати результати пошуку"));

  m_btnFindPath.SubclassDlgItem(ID_FINDPATH, this);
  m_btnFindPath.SetBitmaps(IDB_BTN_FOLDER_TREE, RGB(255,0,255));
  m_btnFindPath.SetTooltipText(_T("Маршрут Пошуку"));

  m_btnFind.SubclassDlgItem(ID_FIND, this);
  m_btnFind.SetBitmaps(IDB_BTN_FINDOUT, RGB(255,0,255), IDB_BTN_FINDOUT_OUT, RGB(255,0,255));
  m_btnFind.SetTooltipText(_T("Почати Пошук"));

  m_btnEQU.SubclassDlgItem(ID_FIND_EQU, this);
  m_btnEQU.SetBitmaps(IDB_BTN_EQU, RGB(255,0,255));
  m_btnEQU.SetTooltipText(_T("Повний збіг знайдених прізвищ"));

  m_btnPartial.SubclassDlgItem(ID_PARTIAL_MATCHING, this);
  m_btnPartial.SetBitmaps(IDB_BTN_PARTIAL, RGB(255,0,255));
  m_btnPartial.SetTooltipText(_T("Частковий знайдених прізвищ"));

  m_btnBirh.SubclassDlgItem(ID_ENABLE_BIRTHES, this);
  m_btnBirh.SetBitmaps(IDB_BTN_BIRTH, RGB(255,0,255), IDB_BTN_BIRTH_OUT, RGB(255,0,255));
  m_btnBirh.SetTooltipText(_T("Шукати АЗ про НАРОДЖЕННЯ"));

  m_btnMarriage.SubclassDlgItem(ID_ENABLE_MARRIAGES, this);
  m_btnMarriage.SetBitmaps(IDB_BTN_MARRIAGE, RGB(255,0,255), IDB_BTN_MARRIAGE_OUT, RGB(255,0,255));
  m_btnMarriage.SetTooltipText(_T("Шукати АЗ про ШЛЮБ"));

  m_btnDivorce.SubclassDlgItem(ID_ENABLE_DIVORCES, this);
  m_btnDivorce.SetBitmaps(IDB_BTN_DIVORCE, RGB(255,0,255), IDB_BTN_DIVORCE_OUT, RGB(255,0,255));
  m_btnDivorce.SetTooltipText(_T("Шукати АЗ про РОЗІРВАННЯ ШЛЮБУ"));

  m_btnChange.SubclassDlgItem(ID_ENABLE_CHANGES, this);
  m_btnChange.SetBitmaps(IDB_BTN_CHANGE, RGB(255,0,255), IDB_BTN_CHANGE_OUT, RGB(255,0,255));
  m_btnChange.SetTooltipText(_T("Шукати АЗ про ЗМІНУ"));

  m_btnDeath.SubclassDlgItem(ID_ENABLE_DEATHES, this);
  m_btnDeath.SetBitmaps(IDB_BTN_DEATH, RGB(255,0,255), IDB_BTN_DEATH_OUT, RGB(255,0,255));
  m_btnDeath.SetTooltipText(_T("Шукати АЗ про СМЕРТЬ"));

  m_btnOpenRecord.SubclassDlgItem(ID_GOTO_FOUNDREC, this);
  m_btnOpenRecord.SetBitmaps(IDB_BTN_OPEN_RECORD, RGB(255,0,255));
  m_btnOpenRecord.SetTooltipText(_T("Відкрити знайдений АЗ"));

  return TRUE;
}

LRESULT CRFindDlgBar::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM lParam) {
  OnUpdateCmdUI((CFrameWnd*)m_pBar, (BOOL)wParam);
  return 0;//m_pBar->OnIdleUpdateCmdUI(wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CRFindSplitter
IMPLEMENT_DYNCREATE(CRFindSplitter, CSplitterWnd)
BEGIN_MESSAGE_MAP(CRFindSplitter, CSplitterWnd)
	//{{AFX_MSG_MAP(CRFindSplitter)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

CRFindSplitter::CRFindSplitter() {
}
CRFindSplitter::~CRFindSplitter() {
}
/////////////////////////////////////////////////////////////////////////////
// CRFindSplitter diagnostics
#ifdef _DEBUG
void CRFindSplitter::AssertValid() const {
	CSplitterWnd::AssertValid();
}

void CRFindSplitter::Dump(CDumpContext& dc) const {
	CSplitterWnd::Dump(dc);
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CRFindSplitter message handlers
int CRFindSplitter::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CSplitterWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
	
  // TODO: Add your specialized creation code here
  return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CGlobalSearchBar

IMPLEMENT_DYNCREATE(CGlobalSearchBar, CGlobalSearchBarBase)

BEGIN_MESSAGE_MAP(CGlobalSearchBar, CGlobalSearchBarBase)
	//{{AFX_MSG_MAP(CGlobalSearchBar)
	ON_WM_CREATE()
  ON_WM_WINDOWPOSCHANGED()
  ON_WM_SIZE()
  ON_UPDATE_COMMAND_UI(ID_NEW_SEARCH, OnUpdateNewSearch)
	ON_COMMAND(ID_NEW_SEARCH, OnNewSearch)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FIND, OnUpdateFind)
	ON_COMMAND(ID_FIND, OnFind)
	ON_UPDATE_COMMAND_UI(ID_FIND_EQU, OnUpdateFindEqu)
	ON_COMMAND(ID_FINDPATH, OnFindPath)
	ON_UPDATE_COMMAND_UI(ID_FINDPATH, OnUpdateFindPath)
	ON_COMMAND(ID_FIND_EQU, OnFindEqu)
	ON_UPDATE_COMMAND_UI(ID_PARTIAL_MATCHING, OnUpdatePartialMatching)
	ON_COMMAND(ID_PARTIAL_MATCHING, OnPartialMatching)
	ON_UPDATE_COMMAND_UI(ID_ENABLE_BIRTHES, OnUpdateEnable)
	ON_COMMAND(ID_ENABLE_BIRTHES, OnEnableBirthes)
	ON_COMMAND(ID_ENABLE_FATHERS, OnEnableFathers)
	ON_COMMAND(ID_ENABLE_MARRIAGES, OnEnableMarriages)
	ON_COMMAND(ID_ENABLE_DIVORCES, OnEnableDivorces)
	ON_COMMAND(ID_ENABLE_CHANGES, OnEnableChanges)
	ON_COMMAND(ID_ENABLE_DEATHES, OnEnableDeathes)
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_ENABLE_FATHERS, OnUpdateEnable)
	ON_UPDATE_COMMAND_UI(ID_ENABLE_MARRIAGES, OnUpdateEnable)
	ON_UPDATE_COMMAND_UI(ID_ENABLE_DIVORCES, OnUpdateEnable)
	ON_UPDATE_COMMAND_UI(ID_ENABLE_CHANGES, OnUpdateEnable)
	ON_UPDATE_COMMAND_UI(ID_ENABLE_DEATHES, OnUpdateEnable)
	ON_UPDATE_COMMAND_UI(ID_GOTO_FOUNDREC, OnUpdateGotoFoundRec)
	ON_COMMAND(ID_GOTO_FOUNDREC, OnGotoFoundRec)
	ON_UPDATE_COMMAND_UI(ID_WHAT_IS_IT, OnUpdateWhatIsIt)
	ON_COMMAND(ID_GOTO_FOUNDREC, OnWhatIsIt)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
  ON_WM_HELPINFO()
  ON_COMMAND(ID_HELP, OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlobalSearchBar construction/destruction

CGlobalSearchBar::CGlobalSearchBar() {
  m_bEnableSearch = m_fNeedShowTooltip = FALSE;
  m_pLeftView = NULL;
  m_pRFindView = NULL;
}

CGlobalSearchBar::~CGlobalSearchBar() {
}

BOOL CGlobalSearchBar::IsTableDef(CString sTDef){
  if ( m_pDB && m_pDB->IsOpen() ) {
    CDaoTableDefInfo tdInfo;
    for(short i(0); i < m_pDB->GetTableDefCount(); i++){
      m_pDB->GetTableDefInfo(i, tdInfo);
      if(sTDef==tdInfo.m_strName)
        return TRUE;
    }
  }
  return FALSE;
}

void CGlobalSearchBar::ResetTitle() {
  CString sTitle;
  sTitle.Format(_T("Пошук за маршрутом %s: "), m_sPath);
  if ( (m_SeekFor & SF_PARTIAL) == 0 )
    sTitle += _T("Повний збіг");
  else
    sTitle += _T("Частковий збіг");
  if ( m_SeekFor & SF_BIRTHES )   sTitle += _T(", Народження");
  if ( m_SeekFor & SF_MARRIAGES ) sTitle += _T(", Шлюби");
  if ( m_SeekFor & SF_DIVORCES )  sTitle += _T(", Розірвання Шлюбів");
  if ( m_SeekFor & SF_CHANGES )   sTitle += _T(", Зміни");
  if ( m_SeekFor & SF_DEATHES )   sTitle += _T(", Смерті");
  SetWindowText(sTitle);
}
int CGlobalSearchBar::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CGlobalSearchBarBase::OnCreate(lpCreateStruct) == -1)
    return -1;
	
	if (!m_wndReBar.Create(this)) {
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndDlgBar.Create(this))	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}
  m_wndReBar.AddBar(&m_wndDlgBar, GetSysColor(COLOR_3DFACE), GetSysColor(COLOR_3DFACE), NULL, 0);

	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;


	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(280, 100), NULL) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRFindView), CSize(100, 100), NULL))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

  m_pLeftView  = GetLeftPane();
  m_pRFindView = GetRightPane();

//  m_pRFindView->SetDlgCtrlID(ID_FOUND_LIST);

  m_SeekFor = theApp.GetProfileInt(_T("Settings"), szFlags, SF_ALL);

  if ( m_SeekFor & SF_BIRTHES )   m_wndDlgBar.m_btnBirh.SetCheck(1);
  if ( m_SeekFor & SF_MARRIAGES ) m_wndDlgBar.m_btnMarriage.SetCheck(1);
  if ( m_SeekFor & SF_DIVORCES )  m_wndDlgBar.m_btnDivorce.SetCheck(1);
  if ( m_SeekFor & SF_CHANGES )   m_wndDlgBar.m_btnChange.SetCheck(1);
  if ( m_SeekFor & SF_DEATHES )   m_wndDlgBar.m_btnDeath.SetCheck(1);

  m_sPath = GetFilePath(theApp.GetHelperMDB());

  ResetTitle();

  m_tooltip.Create(this);
  theToolTipCache.Fill(this, _T("SearchWindow"), &m_tooltip);

	return 0;
}

void CGlobalSearchBar::OnWindowPosChanged(WINDOWPOS FAR* lpWndPos){
  CGlobalSearchBarBase::OnWindowPosChanged(lpWndPos);
  m_tooltip.HideTooltip();
}

BOOL CGlobalSearchBar::OnCreateClient(LPCREATESTRUCT /*lpcs*/,	CCreateContext* pContext) {
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(140, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRFindView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}

void CGlobalSearchBar::OnSize(UINT nType, int cx, int cy) {
  CGlobalSearchBarBase::OnSize(nType, cx, cy);
  if ( m_wndSplitter.GetSafeHwnd() ) {
    const int TOOLBAR_HEIGHT = 32;
    m_wndReBar.   MoveWindow(0, 0, cx, TOOLBAR_HEIGHT);
    m_wndSplitter.MoveWindow(0, TOOLBAR_HEIGHT, cx, cy-TOOLBAR_HEIGHT);
  }
}
BOOL CGlobalSearchBar::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CGlobalSearchBarBase::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGlobalSearchBar diagnostics

#ifdef _DEBUG
void CGlobalSearchBar::AssertValid() const {
	CGlobalSearchBarBase::AssertValid();
}

void CGlobalSearchBar::Dump(CDumpContext& dc) const {
	CGlobalSearchBarBase::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGlobalSearchBar message handlers
CLeftView* CGlobalSearchBar::GetLeftPane() {
	CWnd* pWnd = m_wndSplitter.GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	return pView;
}

CRFindView* CGlobalSearchBar::GetRightPane() {
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CRFindView* pView = DYNAMIC_DOWNCAST(CRFindView, pWnd);
	return pView;
}

void CGlobalSearchBar::OnUpdateViewStyles(CCmdUI* pCmdUI) {
	// TODO: customize or extend this code to handle choices on the
	// View menu.

	CRFindView* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void CGlobalSearchBar::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.
	CRFindView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CRFindView,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// other commands change the style on the list control
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}

bool CGlobalSearchBar::Match(const CString& s1, const CString& s2, const CString& s3) {
  CString sLookupIn1 = UpperString(s1);
  CString sLookupIn2 = UpperString(s2);
  CString sLookupIn3 = UpperString(s3);
  for( int i(0); i < m_pLeftView->m_Surnames.GetSize(); i++ ) {
    CString szSurname     = m_pLeftView->m_Surnames.GetAt(i);
    CString szName        = m_pLeftView->m_Names.GetAt(i);
    CString szPatronymic  = m_pLeftView->m_Patronymics.GetAt(i);
    if ( m_SeekFor & SF_PARTIAL ) {
      if ( FALSE==szSurname.IsEmpty() && FALSE==szName.IsEmpty() && FALSE==szPatronymic.IsEmpty() ) {     // 1 1 1
        if ( CyrInStr(sLookupIn1, szSurname) && CyrInStr(sLookupIn2, szName) && CyrInStr(sLookupIn3, szPatronymic) )
          return true;
      }
      else if ( FALSE==szSurname.IsEmpty() && FALSE==szName.IsEmpty() && szPatronymic.IsEmpty() ) {// 1 1 0
        if ( CyrInStr(sLookupIn1, szSurname) && CyrInStr(sLookupIn2, szName)  )
          return true;
      }
      if ( FALSE==szSurname.IsEmpty() && szName.IsEmpty() && FALSE==szPatronymic.IsEmpty() ) { // 1 0 1
        if ( CyrInStr(sLookupIn1, szSurname) && CyrInStr(sLookupIn3, szPatronymic) )
          return true;
      }
      else if ( FALSE==szSurname.IsEmpty() && szName.IsEmpty() && szPatronymic.IsEmpty() ) {// 1 0 0
        if ( CyrInStr(sLookupIn1, szSurname) )
          return true;
      }
      else if ( szSurname.IsEmpty() && FALSE==szName.IsEmpty() && FALSE==szPatronymic.IsEmpty() ) {// 0 1 1
        if ( CyrInStr(sLookupIn2, szName) && CyrInStr(sLookupIn3, szPatronymic) )
          return true;
      }
      else if ( szSurname.IsEmpty() && FALSE==szName.IsEmpty() && szPatronymic.IsEmpty() ) {// 0 1 0
        if ( CyrInStr(sLookupIn2, szName) )
          return true;
      }
      else if ( szSurname.IsEmpty() && szName.IsEmpty() && FALSE==szPatronymic.IsEmpty() ) {// 0 0 1
        if ( CyrInStr(sLookupIn3, szPatronymic) )
          return true;
      }
    }
    else {


      if ( FALSE==szSurname.IsEmpty() && FALSE==szName.IsEmpty() && FALSE==szPatronymic.IsEmpty() ) {     // 1 1 1
        if ( CyrStriCmp(sLookupIn1, szSurname)==0 && CyrStriCmp(sLookupIn2, szName)==0 && CyrStriCmp(sLookupIn3, szPatronymic)==0 )
          return true;
      }
      else if ( FALSE==szSurname.IsEmpty() && FALSE==szName.IsEmpty() && szPatronymic.IsEmpty() ) {// 1 1 0
        if ( CyrStriCmp(sLookupIn1, szSurname)==0 && CyrStriCmp(sLookupIn2, szName)==0  )
          return true;
      }
      if ( FALSE==szSurname.IsEmpty() && szName.IsEmpty() && FALSE==szPatronymic.IsEmpty() ) { // 1 0 1
        if ( CyrStriCmp(sLookupIn1, szSurname)==0 && CyrStriCmp(sLookupIn3, szPatronymic)==0 )
          return true;
      }
      else if ( FALSE==szSurname.IsEmpty() && szName.IsEmpty() && szPatronymic.IsEmpty() ) {// 1 0 0
        if ( CyrStriCmp(sLookupIn1, szSurname)==0 )
          return true;
      }
      else if ( szSurname.IsEmpty() && FALSE==szName.IsEmpty() && FALSE==szPatronymic.IsEmpty() ) {// 0 1 1
        if ( CyrStriCmp(sLookupIn2, szName)==0 && CyrStriCmp(sLookupIn3, szPatronymic)==0 )
          return true;
      }
      else if ( szSurname.IsEmpty() && FALSE==szName.IsEmpty() && szPatronymic.IsEmpty() ) {// 0 1 0
        if ( CyrStriCmp(sLookupIn2, szName)==0 )
          return true;
      }
      else if ( szSurname.IsEmpty() && szName.IsEmpty() && FALSE==szPatronymic.IsEmpty() ) {// 0 0 1
        if ( CyrStriCmp(sLookupIn3, szPatronymic)==0 )
          return true;
      }

    }
  }
  return false;
}

void CGlobalSearchBar::AddToFoundList(int imlIndex,
                                 long lID,
                                 const CString& strNumber,
                                 const CString& strDateReg,
                                 const CString& strSurName,
                                 const CString& strName,
                                 const CString& strPatronymic,
                                 const CString& strFileName) {
  CRFindView* pFoundView =  (CRFindView*)m_wndSplitter.GetPane(0, 1);
  if ( pFoundView ) {
    CString sFullName = MakeFIO(strSurName, strName, strPatronymic);
    pFoundView->AddToList(imlIndex, lID, strNumber, strDateReg, sFullName, strFileName);
  }
}
void CGlobalSearchBar::SearchBirthes() {
  if ( IsTableDef( CString(szTDABirth) ) ){
    CRSBirthes rs( m_pDB );
    try {
      rs.Open(dbOpenTable, szTDABirth, dbReadOnly);
      if ( rs.IsOpen() ) {
        #ifdef _DEBUG
          int i = 0;
        #endif
        while(rs.IsEOF()==FALSE){
          #ifdef _DEBUG
            TRACE1(_T("CGlobalSearchBar::SearchBirthes() = %d\n"), i++);
          #endif
          long    lID        = GetFieldLong(&rs, _T("ID"));
          CString strSurname = rs.m_SURNAME;
          CString strName    = rs.m_NAME;
          CString strFather  = rs.m_PATRONYMIC;
          CString strNumber  = GetFieldString(&rs, _T("NUMBER") );
          CString strDateReg = GetFieldDate(&rs, _T("DATEREG"), false );
          bool    fSex       = GetFieldBool(&rs, _T("SEX") );

          CString strNewSurname = rs.GetNewOrOldSurname();

          if(m_SeekFor & SF_BIRTHES) {
            if ( Match(strSurname, strName, strFather)) {
              AddToFoundList(fSex?IML_BIRTH_M:IML_BIRTH_W,
                             lID, strNumber, strDateReg,
                             strSurname, strName, strFather,
                             m_pDB->GetName());
            }
            if ( strNewSurname != strSurname && Match(strNewSurname, strName, strFather) ) {
              strName   = rs.GetNewOrOldName();
              strFather = rs.GetNewOrOldPatronymic();
              AddToFoundList(fSex?IML_BIRTH_M:IML_BIRTH_W,
                             lID, strNumber, strDateReg,
                             strNewSurname, strName, strFather,
                             m_pDB->GetName());
            }

            strSurname = rs.m_FATHER_SURNAME;
            strName    = rs.m_FATHER_NAME;
            strFather  = rs.m_FATHER_PATRONYMIC;

            if ( Match(strSurname, strName, strFather)) {
              AddToFoundList(IML_FATHER,
                             lID, strNumber, strDateReg,
                             strSurname, strName, strFather,
                             m_pDB->GetName());
            }

            strSurname = rs.m_MOTHER_SURNAME;
            strName    = rs.m_MOTHER_NAME;
            strFather  = rs.m_MOTHER_PATRONYMIC;

            if ( Match(strSurname, strName, strFather)) {
              AddToFoundList(IML_MOTHER,
                             lID, strNumber, strDateReg,
                             strSurname, strName, strFather,
                             m_pDB->GetName());
            }
            strNewSurname = rs.GetNewMotherSurname();
            if ( FALSE==strNewSurname.IsEmpty() && strNewSurname!=strSurname && Match(strNewSurname, strName, strFather)) {
              AddToFoundList(IML_MOTHER,
                             lID, strNumber, strDateReg,
                             strNewSurname, strName, strFather,
                             m_pDB->GetName());
            }
          }
          rs.MoveNext();
        }
        rs.Close();
      }
    }
    catch(CDaoException* e){
      e->Delete();
    }
  }
}

void CGlobalSearchBar::SearchAffilations() {
}

void CGlobalSearchBar::SearchMarriages() {
  if ( IsTableDef( CString(szTDAMarriage) ) ){
    CDaoRecordset rs( m_pDB );
    try {
      rs.Open(dbOpenTable, szTDAMarriage, dbReadOnly);
      if ( rs.IsOpen() ) {
        while(rs.IsEOF()==FALSE){
          long    lID          = GetFieldLong(&rs, _T("ID"));
          CString sOldMSurname = GetFieldString(&rs, _T("MOLD_SURNAME") );
          CString sNewMSurname = GetFieldString(&rs, _T("MNEW_SURNAME") );
          CString sMName       = GetFieldString(&rs, _T("MNAME") );
          CString sMFather     = GetFieldString(&rs, _T("MPATRONYMIC") );

          CString sOldWSurname = GetFieldString(&rs, _T("WOLD_SURNAME") );
          CString sNewWSurname = GetFieldString(&rs, _T("WNEW_SURNAME") );
          CString sWName       = GetFieldString(&rs, _T("WNAME") );
          CString sWFather     = GetFieldString(&rs, _T("WPATRONYMIC") );

          CString sNumber = GetFieldString(&rs,_T("NUMBER"));
          CString sDate   = GetFieldDate(&rs, _T("DATEREG"), false );

          if ( Match(sOldMSurname, sMName, sMFather)) {
            AddToFoundList(IML_MARRIAGE,
                           lID, sNumber, sDate,
                           sOldMSurname, sMName, sMFather,
                           m_pDB->GetName());
          }
          if ( !sNewMSurname.IsEmpty() && sNewMSurname!=sOldMSurname) {
            if ( Match(sNewMSurname, sMName, sMFather)) {
              AddToFoundList(IML_MARRIAGE,
                             lID, sNumber, sDate,
                             sNewMSurname, sMName, sMFather,
                             m_pDB->GetName());
            }
          }

          if ( Match(sOldWSurname, sWName, sWFather)) {
            AddToFoundList(IML_MARRIAGE,
                           lID, sNumber, sDate,
                           sOldWSurname, sWName, sWFather,
                           m_pDB->GetName());
          }
          if ( !sNewWSurname.IsEmpty() && sNewWSurname!=sOldWSurname) {
            if ( Match(sNewWSurname, sWName, sWFather)) {
              AddToFoundList(IML_MARRIAGE,
                             lID, sNumber, sDate,
                             sNewWSurname, sWName, sWFather,
                             m_pDB->GetName());
            }
          }
          rs.MoveNext();
        }
        rs.Close();
      }
    }
    catch(CDaoException* e){
      e->Delete();
    }
  }
}
void CGlobalSearchBar::SearchDivorces() {
  if ( IsTableDef( CString(szTDADivorce) ) ){
    CDaoRecordset rs( m_pDB );
    try {
      rs.Open(dbOpenTable, szTDADivorce, dbReadOnly);
      if ( rs.IsOpen() ) {
        while(rs.IsEOF()==FALSE){
          long    lID          = GetFieldLong(&rs, _T("ID"));
          CString sOldMSurname = GetFieldString(&rs, _T("MOLD_SURNAME"));
          CString sNewMSurname = GetFieldString(&rs, _T("MNEW_SURNAME"));
          CString sMName       = GetFieldString(&rs, _T("MNAME"));
          CString sMFather     = GetFieldString(&rs, _T("MPATRONYMIC"));

          CString sOldWSurname = GetFieldString(&rs, _T("WOLD_SURNAME"));
          CString sNewWSurname = GetFieldString(&rs, _T("WNEW_SURNAME"));
          CString sWName       = GetFieldString(&rs, _T("WNAME"));
          CString sWFather     = GetFieldString(&rs, _T("WPATRONYMIC"));

          CString sNumber = GetFieldString(&rs,_T("NUMBER"));
          CString sDate   = GetFieldDate(&rs, _T("DATEREG"), false);

          if ( Match(sOldMSurname, sMName, sMFather)) {
            AddToFoundList(IML_DIVORCE_M,
                           lID, sNumber, sDate,
                           sOldMSurname, sMName, sMFather,
                           m_pDB->GetName());
          }
          if ( !sNewMSurname.IsEmpty() && sNewMSurname!=sOldMSurname) {
            if ( Match(sNewMSurname, sMName, sMFather)) {
              AddToFoundList(IML_DIVORCE_M,
                             lID, sNumber, sDate,
                             sNewMSurname, sMName, sMFather,
                             m_pDB->GetName());
            }
          }

          if ( Match(sOldWSurname, sWName, sWFather)) {
            AddToFoundList(IML_DIVORCE_W,
                           lID, sNumber, sDate,
                           sOldWSurname, sWName, sWFather,
                           m_pDB->GetName());
          }
          if ( !sNewWSurname.IsEmpty() && sNewWSurname!=sOldWSurname) {
            if ( Match(sNewWSurname, sWName, sWFather)) {
              AddToFoundList(IML_DIVORCE_W,
                             lID, sNumber, sDate,
                             sNewWSurname, sWName, sWFather,
                             m_pDB->GetName());
            }
          }
          rs.MoveNext();
        }
        rs.Close();
      }
    }
    catch(CDaoException* e){
      e->Delete();
    }
  }
}

void CGlobalSearchBar::SearchChanges() {
  if ( IsTableDef( CString(szTDAChange) ) ){
    CDaoRecordset rs( m_pDB );
    try {
      rs.Open(dbOpenTable, szTDAChange, dbReadOnly);
      if ( rs.IsOpen() ) {
        while(rs.IsEOF()==FALSE){
          long    lID         = GetFieldLong(&rs, _T("ID"));
          CString sOldSurname = GetFieldString(&rs, _T("OLDSURNAME") );
          CString sNewSurname = GetFieldString(&rs, _T("NEWSURNAME") );
          CString sOldName    = GetFieldString(&rs, _T("OLDNAME") );
          CString sNewName    = GetFieldString(&rs, _T("NEWNAME") );
          CString sOldFather  = GetFieldString(&rs, _T("OLDPATRONYMIC") );
          CString sNewFather  = GetFieldString(&rs, _T("NEWPATRONYMIC") );

          if ( sNewSurname.IsEmpty() )   sNewSurname   = sOldSurname;
          if ( sNewName.IsEmpty() )      sNewName      = sOldName;
          if ( sNewFather.IsEmpty() )    sNewFather    = sOldFather;

          CString sNumber = GetFieldString(&rs,_T("NUMBER"));
          CString sDate   = GetFieldDate(&rs, _T("DATEREG"), false);

          int     imgID    = GetFieldBool(&rs, _T("SEX")) ? IML_CHANGE_M : IML_CHANGE_W;

          if ( Match(sOldSurname, sOldName, sOldFather)) {
            AddToFoundList(imgID, lID, sNumber, sDate,
                           sOldSurname, sOldName, sOldFather,
                           m_pDB->GetName());
          }

          if ( sNewSurname!=sOldSurname && Match(sNewSurname, sNewName, sNewFather)) {
            AddToFoundList(imgID, lID, sNumber, sDate,
                           sNewSurname, sNewName, sNewFather,
                           m_pDB->GetName());
          }
          rs.MoveNext();
        }
        rs.Close();
      }
    }
    catch(CDaoException* e){
      e->Delete();
    }
  }
}

void CGlobalSearchBar::SearchDeathes() {
  if ( IsTableDef( CString(szTDADeath) ) ){
    CDaoRecordset rs( m_pDB );
    try {
      rs.Open(dbOpenTable, szTDADeath, dbReadOnly);
      if ( rs.IsOpen() ) {
        while(rs.IsEOF()==FALSE){
          long    lID      = GetFieldLong(&rs, _T("ID"));
          CString sSurname = GetFieldString(&rs, _T("SURNAME"));
          CString sName    = GetFieldString(&rs, _T("NAME"));
          CString sFather  = GetFieldString(&rs, _T("PATRONYMIC"));

          CString sNumber = GetFieldString(&rs,_T("NUMBER"));
          CString sDate   = GetFieldDate(&rs, _T("DATEREG"), false);

          int     imgID    = GetFieldBool(&rs, _T("SEX")) ? IML_DEATH_M : IML_DEATH_W;

          if ( Match(sSurname, sName, sFather)) {
            AddToFoundList(imgID, lID, sNumber, sDate,
                           sSurname, sName, sFather,
                           m_pDB->GetName());
          }
          rs.MoveNext();
        }
        rs.Close();
      }
    }
    catch(CDaoException* e){
      e->Delete();
    }
  }
}

void CGlobalSearchBar::SearchForActs(LPCTSTR szMDEFile){
  m_pDB = OpenDB(szMDEFile);
  if(m_pDB && m_pDB->IsOpen()){
    #ifdef _DEBUG
    TRACE1(_T("%s\n"), szMDEFile );
    #endif
    if ( m_SeekFor & SF_BIRTHES )
      SearchBirthes();
    if ( m_SeekFor & SF_FATHERS )
      SearchAffilations();
    if (m_SeekFor & SF_MARRIAGES)
      SearchMarriages();
    if (m_SeekFor & SF_DIVORCES)
      SearchDivorces();
    if (m_SeekFor & SF_CHANGES)
      SearchChanges();
    if (m_SeekFor & SF_DEATHES)
      SearchDeathes();
    CloseDB(m_pDB);
  }
}

void CGlobalSearchBar::SearchForMde(LPCTSTR szPath){
  HANDLE hFindFile;
  BOOL bFind;
  WIN32_FIND_DATA findData;
  CString sPath = szPath; sPath += _T("\\");
  CString sMask = sPath + _T("*.*");
  CString sFileName;

  if((hFindFile = FindFirstFile(sMask, &findData)) != INVALID_HANDLE_VALUE){
    bFind = TRUE;
    while(bFind){
      if(findData.cFileName[0] != '.'){
        if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
          CString sNewPath = sPath + findData.cFileName;
          SearchForMde(sNewPath);
        }
        sFileName = sPath + findData.cFileName;
        if(sFileName.Right(3).CompareNoCase(_T("er3")) == 0) {
          SearchForActs(sFileName);
        }
      }
      bFind = FindNextFile(hFindFile, &findData);
    }
    FindClose(hFindFile);
  }
}

void CGlobalSearchBar::OnUpdateFileSave(CCmdUI* pCmdUI) {
  if ( NULL==m_pRFindView )
    pCmdUI->Enable(FALSE);
  else {
    CListCtrl& list = m_pRFindView->GetListCtrl();
    pCmdUI->Enable(list.GetItemCount() > 0);
  }
}
void CGlobalSearchBar::OnFileSave() {
  if ( NULL==m_pRFindView )
    return;
  CListCtrl& list = m_pRFindView->GetListCtrl();
  m_pRFindView->ExportToCSV();
}

void CGlobalSearchBar::OnUpdateNewSearch(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
}
void CGlobalSearchBar::OnNewSearch() {
  if ( NULL==m_pRFindView )
    return;
  CListCtrl& list = m_pRFindView->GetListCtrl();
  list.DeleteAllItems();
}
void CGlobalSearchBar::OnUpdateFind(CCmdUI* pCmdUI) {
/*
  CDocument* pDoc = GetActiveDocument( );
  if ( pDoc )
    m_sPath = pDoc->GetPathName();
  m_bEnableSearch = PathFileExists(m_sPath);
	pCmdUI->Enable(m_bEnableSearch);
*/
}

void CGlobalSearchBar::OnFind() {
  CWaitCursor wc;

  m_pLeftView = GetLeftPane();
  m_pLeftView->CreateFindArray();
  if ( m_pLeftView->m_Surnames.GetSize()==0 )
    return;

  GetRightPane()->Clear();
	SearchForMde(m_sPath);
}

void CGlobalSearchBar::OnUpdateEnable(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);

  for( int i(0); i <= SF_MAX; i++ ) {
    UINT btnID    = ID_ENABLE_BIRTHES+i;
    if ( pCmdUI->m_nID==btnID ) {
      int sFlag = 1<<i;
      int nCheck = (m_SeekFor & sFlag) ? 1 : 0; 
      CButtonST* pBtn = (CButtonST*)pCmdUI->m_pOther;
      if ( pBtn && 0==pBtn->GetCheck() )
        pCmdUI->SetCheck(nCheck);
      return;
    }
  }

/**************************************** 23.05.2002 4:10:33 by VK
  for( int i(0); i <= SF_MAX; i++ ) {
    CString sKey;
    int sFlag = 1<<i;

    UINT uCheck = (m_SeekFor & sFlag)
                ?  MF_CHECKED|MF_BYCOMMAND
                :  MF_UNCHECKED|MF_BYCOMMAND;
    int btnID    = ID_ENABLE_BIRTHES+i;
    int btnIndex = TBTN_BIRTH_INDEX+i;
    UINT nState = m_SeekFor & sFlag ? TBSTATE_CHECKED : 0;

    m_wndToolBar.SetButtonStyle(btnIndex, TBBS_CHECKBOX);
    m_wndToolBar.GetToolBarCtrl().SetState(btnID, nState);
    GetMenu()->CheckMenuItem(btnID, uCheck);
  }
***************************************** 23.05.2002 4:10:35 by VK */
}

void CGlobalSearchBar::OnEnableBirthes()    { m_SeekFor ^= SF_BIRTHES;   ResetTitle(); }
void CGlobalSearchBar::OnEnableFathers()    {	m_SeekFor ^= SF_FATHERS;   ResetTitle(); }
void CGlobalSearchBar::OnEnableMarriages()  {	m_SeekFor ^= SF_MARRIAGES; ResetTitle(); }
void CGlobalSearchBar::OnEnableDivorces()   {	m_SeekFor ^= SF_DIVORCES;  ResetTitle(); }
void CGlobalSearchBar::OnEnableChanges()    {	m_SeekFor ^= SF_CHANGES;   ResetTitle(); }
void CGlobalSearchBar::OnEnableDeathes()    {	m_SeekFor ^= SF_DEATHES;   ResetTitle(); }

void CGlobalSearchBar::OnUpdateFindEqu(CCmdUI* pCmdUI) {
  pCmdUI->Enable( (m_SeekFor & SF_PARTIAL)!=0 );
}
void CGlobalSearchBar::OnFindEqu() {
  m_SeekFor ^= SF_PARTIAL;
  ResetTitle();
}
void CGlobalSearchBar::OnUpdatePartialMatching(CCmdUI* pCmdUI) {
  pCmdUI->Enable( (m_SeekFor & SF_PARTIAL)==0 );
}
void CGlobalSearchBar::OnPartialMatching()  {	
  m_SeekFor ^= SF_PARTIAL;
  ResetTitle();
}

void CGlobalSearchBar::OnDestroy() {
  theApp.WriteProfileInt(_T("Settings"), szFlags, m_SeekFor);
	CGlobalSearchBarBase::OnDestroy();
}

void CGlobalSearchBar::OnFileOpen() {
	// TODO: Add your command handler code here
	
}

/**************************************** 23.05.2002 23:25:21 by VK
BOOL CGlobalSearchBar::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) {
  switch(nID) {
	  case ID_FILE_SAVE_AS:
      OnFileSaveAs();
      return TRUE;    
  }
	return CGlobalSearchBarBase::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
***************************************** 23.05.2002 23:25:27 by VK */

void CGlobalSearchBar::OnUpdateFindPath(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
}

void CGlobalSearchBar::OnFindPath() {
	// TODO: Add your command handler code here
  TCHAR szDir[MAX_PATH];
  if ( XBrowseForFolder(m_hWnd, m_sPath, szDir, MAX_PATH) ) {
    m_sPath = szDir;
    m_bEnableSearch = PathFileExists(m_sPath);
    ResetTitle();
  }
/*
  BROWSEINFO bi;
  TCHAR szDir[MAX_PATH];
  LPITEMIDLIST pidl;
  LPMALLOC pMalloc;
  
  if (SUCCEEDED(SHGetMalloc(&pMalloc))) {
    ZeroMemory(&bi,sizeof(bi));
    bi.hwndOwner = m_hWnd;
    bi.pszDisplayName = 0;
    bi.pidlRoot = 0;
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
    bi.lpfn = BrowseCallbackProcForSearch;

    pidl = SHBrowseForFolder(&bi);
    if(pidl){
      if(SHGetPathFromIDList(pidl,szDir)){
        m_sPath = szDir;
        //SetWindowText(_T("Маршрут пошуку: ") + m_sPath);
        theApp.WriteProfileString(_T("Settings"), szPath, szDir);
        m_bEnableSearch = PathFileExists(m_sPath);
        ResetTitle();
      }
      // In C++:
      pMalloc->Free(pidl); pMalloc->Release();
    }
  }
*/
}

void CGlobalSearchBar::OnUpdateGotoFoundRec(CCmdUI* pCmdUI) {
  if ( NULL==m_pRFindView )
    pCmdUI->Enable(FALSE);
  BOOL fEnable = FALSE;
  CListCtrl& list = m_pRFindView->GetListCtrl();
  int nItem = list.GetNextItem(-1, LVNI_FOCUSED);
  if ( nItem != -1 ) {
    fEnable = TRUE;
  }
  pCmdUI->Enable(fEnable);
}
void CGlobalSearchBar::OnGotoFoundRec() {
  if ( NULL==m_pRFindView )
    return;
  CListCtrl& list = m_pRFindView->GetListCtrl();
  int nItem = list.GetNextItem(-1, LVNI_FOCUSED);
  if ( nItem != -1 ) {
    CRFoundOb* pFoundOb = (CRFoundOb*)list.GetItemData(nItem);
    if ( pFoundOb ) {
      CString sDatabase = list.GetItemText(nItem, 4);
      theApp.m_pBirthTemplate->CloseAllDocuments(FALSE);
      theApp.m_pMarriageTemplate->CloseAllDocuments(FALSE);
      theApp.m_pDivorceTemplate->CloseAllDocuments(FALSE);
      theApp.m_pChangeTemplate->CloseAllDocuments(FALSE);
      theApp.m_pDeathTemplate->CloseAllDocuments(FALSE);
      theApp.m_pWordTemplate->CloseAllDocuments(FALSE);
      theApp.m_pOOTemplate->CloseAllDocuments(FALSE);
      theApp.OpenDocument(sDatabase, pFoundOb->m_nActType);

      CMDIChildWnd* pFrame = ((CMainFrame*)(AfxGetMainWnd()))->MDIGetActive();
      if ( pFrame ) {
        CView* pView = pFrame->GetActiveView();
        if ( pView ) {
          if ( pView->IsKindOf(RUNTIME_CLASS(CEraForm)) )
            ((CEraForm*)pView)->Find(pFoundOb->m_lID);
        }
        GetParentFrame()->ActivateFrame();
      }
    }
  }
}
void CGlobalSearchBar::OnUpdateWhatIsIt(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
}
void CGlobalSearchBar::OnWhatIsIt() {
}
BOOL CGlobalSearchBar::OnHelpInfo(HELPINFO* pHelpInfo) {
  m_tooltip.HideTooltip();
  if ( HELPINFO_WINDOW==pHelpInfo->iContextType ) {
    CWnd* pWnd = CWnd::FromHandle((HWND)pHelpInfo->hItemHandle);
    if ( pWnd ) {
      // ScrollToControl(pControl);
      m_fNeedShowTooltip = TRUE;
      ShowHelpTooltipSetFocus(&m_tooltip, pWnd->GetParent(), _T("SearchWindow"), pWnd, pHelpInfo->iCtrlId);
      // m_fEnableRelayEvent = false;
    }
  }
  return TRUE;
}
void CGlobalSearchBar::OnHelp() {
  theApp.OnHelp(_T("Search"));
}
BOOL CGlobalSearchBar::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
  switch(message) {
    case WM_PARENTNOTIFY:
      m_tooltip.HideTooltip();
      break;
    case WM_NCPAINT:
      if ( FALSE==m_fNeedShowTooltip )
        m_tooltip.HideTooltip();
      m_fNeedShowTooltip = FALSE;
      break;
  }
  return CGlobalSearchBarBase::OnWndMsg(message, wParam, lParam, pResult);
}