// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "Erags.h"

#include "DataManager.h"
#include "ChildFrm.h"
#include "EraForm.h"
#include "FormBirth.h"
#include "FormMarriage.h"
#include "FormDivorce.h"
#include "FormChange.h"
#include "FormDeath.h"

#include "MainFrm.h"

#include "..\Common\EraMessages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CChildFrameBase)

BEGIN_MESSAGE_MAP(CChildFrame, CChildFrameBase)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_MDIACTIVATE()
	ON_WM_SETFOCUS()
  ON_WM_SYSCOMMAND()
	ON_UPDATE_COMMAND_UI(ID_FINDIN, OnUpdateFindin)
	ON_COMMAND(ID_FINDIN, OnFindin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction
CChildFrame::CChildFrame() {
	// TODO: add member initialization code here
  m_nFormID = -1;
  m_pView = NULL;
}

CChildFrame::~CChildFrame() {
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs) {
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
  //cs.dwExStyle |= WS_EX_CONTEXTHELP;
  cs.style &= ~(WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU);

	if( !CChildFrameBase::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics
#ifdef _DEBUG
void CChildFrame::AssertValid() const {
	CChildFrameBase::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const {
	CChildFrameBase::Dump(dc);
}

#endif //_DEBUG

CString CChildFrame::GetBarStateName(LPCTSTR szBarStateName) {
  CString sBSName;
  sBSName.Format(_T("BS%s%s"), theApp.GetFormName(m_nFormID), szBarStateName);
  return sBSName;
}
BOOL CChildFrame::VerifyBarState(LPCTSTR lpszProfileName) {
  CDockState state;
  state.LoadState(lpszProfileName);

  for (int i = 0; i < state.m_arrBarInfo.GetSize(); i++) {
    CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];
    ASSERT(pInfo != NULL);
    int nDockedCount = pInfo->m_arrBarID.GetSize();
    if (nDockedCount > 0) {
      // dockbar
      for (int j = 0; j < nDockedCount; j++) {
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

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CChildFrameBase::OnCreate(lpCreateStruct) == -1)
		return -1;
  //MDIMaximize();

  ShowWindow(SW_MAXIMIZE);
	return 0;
}

BOOL CChildFrame::DestroyWindow() {
	// TODO: Add your specialized code here and/or call the base class
  CString sProfile = GetBarStateName(_T("LocSearch"));
  if ( m_LocalSearchBar.GetSafeHwnd() ) {
	  m_LocalSearchBar.SaveState(sProfile);
  }
  SaveBarState(sProfile);
	
	return CChildFrameBase::DestroyWindow();
}

void CChildFrame::OnDestroy() {
/*
  if ( m_LocalSearchBar.GetSafeHwnd() ) {
    CString sBarStateName = _T("BarState");//GetBarStateName(_T("LSBar"));
    m_LocalSearchBar.SaveState(sBarStateName);
    SaveBarState(sBarStateName);
  }
*/
/************************************** : by VK at 22.02.2005 22:33:59 **\
  if ( m_LocalSearchBar.GetSafeHwnd() )
    m_LocalSearchBar.DestroyWindow();
\************************************** : by VK at 22.02.2005 22:34:02 **/
  //CEraForm* pForm = (CEraForm*)GetActiveView();
  CEraForm* pForm = (CEraForm*)m_pView;
  if ( pForm ) {
    CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
    if ( pMainWnd ) {
      if ( pForm->IsKindOf(RUNTIME_CLASS(CFormBirth)) )
        pMainWnd->m_pBirthFrame = NULL;
      else if ( pForm->IsKindOf(RUNTIME_CLASS(CFormMarriage)) )
        pMainWnd->m_pMarriageFrame = NULL;
      else if ( pForm->IsKindOf(RUNTIME_CLASS(CFormDivorce)) )
        pMainWnd->m_pDivorceFrame = NULL;
      else if ( pForm->IsKindOf(RUNTIME_CLASS(CFormChange)) )
        pMainWnd->m_pChangeFrame = NULL;
      else if ( pForm->IsKindOf(RUNTIME_CLASS(CFormDeath)) )
        pMainWnd->m_pDeathFrame = NULL;
      else {
        CChildFrameBase::OnDestroy();
        return;
      }
    }

    if ( pForm->m_pSet &&  pForm->m_pSet->m_pDAORecordset ) {

      bool bCurrentRec = true;
      COleVariant bm;
      try {
        bm = pForm->m_pSet->GetBookmark();
      }
      catch(CDaoException* e) {
        e->Delete();
        bCurrentRec = false;
      }


      if ( bCurrentRec && pForm->m_pSet->m_pDAORecordset && pForm->m_pSet->IsOpen() ) {
        try {
          if (pForm->m_pSet->CanUpdate() )
            pForm->m_pSet->Edit();
	  	    if (!pForm->UpdateData())
     	  	  return;
          if (pForm->m_pSet->IsFieldDirty(NULL))
	    		  pForm->m_pSet->Update();
  	      else
   		    	pForm->m_pSet->CancelUpdate();
        }
        catch(CDaoException* e) {
          #ifdef _DEBUG
            e->ReportError(); // to do logstring
          #endif
          e->Delete();
        }
      }
    }
  }
	CChildFrameBase::OnDestroy();
	// TODO: Add your message handler code here
}

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) {
	CChildFrameBase::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	
	// TODO: Add your message handler code here
  ShowWindow(SW_MAXIMIZE);
  if ( FALSE==bActivate ) {
    CEraForm* pForm = (CEraForm*)GetActiveView();
    if ( pForm && pForm->IsKindOf(RUNTIME_CLASS(CEraForm)) ) {
      pForm->m_tooltip.HideTooltip();
    }
  }
//  ShowWindow(SW_MAXIMIZE);
}

void CChildFrame::OnSetFocus(CWnd* pOldWnd)
{
	if (m_pViewActive != NULL) {
    CWnd* pFocusedWnd = NULL;
    if ( m_pViewActive->IsKindOf(RUNTIME_CLASS(CEraForm)) ) {
      pFocusedWnd = ((CEraForm*)m_pViewActive)->m_pFocused;
    }
    if ( pFocusedWnd ) {
      pFocusedWnd->SetFocus();
    }
    else {
		  m_pViewActive->SetFocus();
    }
  }
	else
		CWnd::OnSetFocus(pOldWnd);
}


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) {
  return CChildFrameBase::OnCreateClient(lpcs, pContext);
	// create splitter window
/************************************** : by VK at 21.12.2004 1:49:52 **\
	if (!m_wndSplitter.CreateStatic(this, 2, 1))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CEraABCView), CSize(100, 100), pContext) ||
		  ! m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CABCList), CSize(100, 100), pContext) ) {
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
\************************************** : by VK at 21.12.2004 1:49:55 **/
	return TRUE;
}

void CChildFrame::OnSysCommand(UINT nID, LPARAM lParam) {
  switch(nID & 0xFFF0) {
    case SC_MINIMIZE:
    case SC_RESTORE:
		  return;
	}
  CChildFrameBase::OnSysCommand(nID, lParam);
}

void CChildFrame::OnUpdateFindin(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
  BOOL fEnable = true;
  if ( NULL==m_pView || false==m_pView->IsKindOf(RUNTIME_CLASS(CEraForm)) ) {
    fEnable = false;
  }
  pCmdUI->Enable( fEnable );
}

void CChildFrame::RestoreFrame() {
  //m_LocalSearchBar.ShowWindow(SW_SHOW);
  ShowControlBar(&m_LocalSearchBar, TRUE, TRUE);
  m_LocalSearchBar.OnInitialUpdate();
}

void CChildFrame::OnFindin() {
  if ( NULL==m_pView || false==m_pView->IsKindOf(RUNTIME_CLASS(CEraForm)) ) {
    return;
  }
  CString sBarStateName = GetBarStateName(_T("LocSearch"));
	// TODO: Add your command handler code here
  if ( m_LocalSearchBar.GetSafeHwnd() ) {
    if ( m_LocalSearchBar.IsWindowVisible() ) {
      SaveBarState(sBarStateName);
      m_LocalSearchBar.ShowWindow(SW_HIDE);
      ShowControlBar(&m_LocalSearchBar, FALSE, FALSE);
    }
    else {
      RestoreFrame();
    }
    RecalcLayout();
    return;
  }

  CString sBarTitle;
  sBarTitle.Format(_T("Пошук: %s, %s"), theApp.GetCyrFormName(m_nFormID), theDataManager.GetYearDBName() );

  if (!m_LocalSearchBar.Create(sBarTitle, this, 1910+m_nFormID)) {
    TRACE0("Failed to create LocalSearchBar\n");
    return;
  }
  m_LocalSearchBar.SetBarStyle(m_LocalSearchBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
  EnableDocking(CBRS_ALIGN_ANY);
  m_LocalSearchBar.EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_LocalSearchBar, AFX_IDW_DOCKBAR_RIGHT);

//  CControlBar
  if (VerifyBarState(sBarStateName)) {
    m_LocalSearchBar.LoadState(sBarStateName);
    LoadBarState(sBarStateName);
  }

  RestoreFrame();
  m_LocalSearchBar.m_pParentFrame = this;
  EnableDocking(CBRS_ALIGN_ANY);
}
