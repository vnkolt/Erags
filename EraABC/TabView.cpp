// TabView.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "EraABCDoc.h"
#include "TabView.h"

#include "EraABCView.h"

#include "ABCList.h"
#include "FormBirth.h"
#include "FormChange.h"
#include "FormDeath.h"
#include "FormDivorce.h"
#include "FormMarriage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabView

IMPLEMENT_DYNCREATE(CTabView, CView)
CTabView::CTabView() {
  m_nCurTab = 0;
}

CTabView::~CTabView() {
}


BEGIN_MESSAGE_MAP(CTabView, CView)
	//{{AFX_MSG_MAP(CTabView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_COMMAND(ID_BIRTH, OnBirth)
	ON_COMMAND(ID_MARRIAGE, OnMarriage)
	ON_COMMAND(ID_DIVORCE, OnDivorce)
	ON_COMMAND(ID_CHANGE, OnChange)
	ON_COMMAND(ID_DEATH, OnDeath)
	ON_UPDATE_COMMAND_UI(ID_BIRTH, OnUpdateBirth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabView drawing
void CTabView::OnDraw(CDC* pDC) {
/************************************** : by VK at 29.01.2005 9:50:13 **\
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
\************************************** : by VK at 29.01.2005 9:50:16 **/
}

/////////////////////////////////////////////////////////////////////////////
// CTabView diagnostics
#ifdef _DEBUG
void CTabView::AssertValid() const {
	CView::AssertValid();
}
void CTabView::Dump(CDumpContext& dc) const {
	CView::Dump(dc);
}
CEraABCDoc* CTabView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEraABCDoc)));
	return (CEraABCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabView message handlers
int CTabView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
  m_pTabCtrl = new CTabCtrl();
  m_pTabCtrl->Create(WS_CHILD|WS_VISIBLE|TCS_TABS|TCS_SINGLELINE|TCS_TOOLTIPS|TCS_FLATBUTTONS|TCS_HOTTRACK, CRect(0,0,0,0), this, 0);

  CFont* pFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
  m_pTabCtrl->SetFont(pFont);

  m_ImageList.Create(24, 24, ILC_COLOR8, 5, 0);
  CBitmap bm;
  bm.LoadBitmap(IDIL_TABS);
  m_ImageList.Add(&bm, RGB(255,0,255));
  m_pTabCtrl->SetImageList(&m_ImageList);

/************************************** : by VK at 26.01.2005 0:31:52 **\
  LOGFONT lf;
  CFont* pFont = GetFont();
  pFont->GetLogFont(&lf);
  pFont->CreateFontIndirect(&lf);
  m_pTabCtrl->SetFont(pFont);
\************************************** : by VK at 26.01.2005 0:31:55 **/

	return 0;
}

void CTabView::RecalcLayout() {
  CRect rc;
  GetClientRect(rc);
  m_pTabCtrl->MoveWindow(&rc);
  m_pTabCtrl->MapWindowPoints(this,rc);
  m_pTabCtrl->AdjustRect(FALSE,rc);

  int nCurSel = m_pTabCtrl->GetCurSel();
  int nTabs = m_Tabs.GetSize();
  for( int i(0); i < nTabs; i++ ) {
    CWnd* pWnd = (CWnd*)m_Tabs.GetAt(i);
    pWnd->ShowWindow( nCurSel==i ? SW_SHOW : SW_HIDE );
  }

  HDWP hDwp = ::BeginDeferWindowPos(nTabs);
  for (i=0; i < nTabs; i++)
    ::DeferWindowPos(hDwp, ((CWnd*)(m_Tabs.GetAt(i)))->GetSafeHwnd(),HWND_TOP,rc.left,rc.top-1,rc.Width(),rc.Height()+1,0);//SWP_NOZORDER);
  ::EndDeferWindowPos(hDwp);
}
void CTabView::OnSize(UINT nType, int cx, int cy) {
	CView::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
  if ( m_pTabCtrl )
    RecalcLayout();
}

BOOL CTabView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
  if ( m_pTabCtrl && m_pTabCtrl->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo) )
    return TRUE;
	return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CTabView::OnEraseBkgnd(CDC* pDC) {
	// TODO: Add your message handler code here and/or call default
	return TRUE;//	return CView::OnEraseBkgnd(pDC);
}

CFormABC* CTabView::GetActiveForm() {
  int CurSel = m_pTabCtrl->GetCurSel();
  if ( CurSel >= 0 ) {
    CEraABCView* pActiveView = (CEraABCView*)m_Tabs.GetAt(CurSel);
    return pActiveView->GetForm();
  }
  return NULL;
}
void CTabView::SetActiveForm(int nTab/*=-1*/) {
  CEraABCView* pActiveView = NULL;
  if ( m_nCurTab != nTab && m_nCurTab >= 0 ) {
    pActiveView = (CEraABCView*)m_Tabs.GetAt(m_nCurTab);
    CFormABC* pForm = pActiveView->GetForm();
    pForm->m_tooltip.HideTooltip();
  }
  if ( nTab != -1 ) {
    m_pTabCtrl->SetCurSel(nTab);
    m_nCurTab = nTab;
  }
  else {
    m_nCurTab = m_pTabCtrl->GetCurSel();
  }
  pActiveView = (CEraABCView*)m_Tabs.GetAt(m_nCurTab);
  CFormABC* pForm = pActiveView->GetForm();
  pActiveView->SetActivePane(0, 0);
  pForm->SetFocus();
  pForm->SetFocusToFirstControl();
  if ( nTab != -1 )
    RecalcLayout();

  if ( pForm->m_pSet ) {
    CString strTitle = pForm->m_pSet->m_pDatabase->GetName();
    switch ( m_nCurTab ) {
      case 0: // Народження
        strTitle += _T(" [Народження]"); break;
      case 1: // Шлюби
        strTitle += _T(" [Шлюби]"); break;
      case 2: // Розірвання Шлюбів
        strTitle += _T(" [Розірвання Шлюбів]"); break;
      case 3: // Зміни
        strTitle += _T(" [Зміни]"); break;
      case 4: // Смерті
        strTitle += _T(" [Смерті]"); break;
    }
    CEraABCDoc* pDoc = (CEraABCDoc*)GetDocument();
    pDoc->SetTitle(strTitle);
  }

}
BOOL CTabView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
	// TODO: Add your specialized code here and/or call the base class
  NMHDR* pnmh = (LPNMHDR) lParam;
	if (TCN_SELCHANGE == pnmh->code) {
    SetActiveForm();
    RecalcLayout();
  }
	return CView::OnNotify(wParam, lParam, pResult);
}

void CTabView::OnDestroy()  {
	if ( m_pTabCtrl ) {
    if ( m_BirthView.GetSafeHwnd() )    m_BirthView.DeleteView(0, 0);
    if ( m_MarriageView.GetSafeHwnd() ) m_MarriageView.DeleteView(0, 0);
    if ( m_DivorceView.GetSafeHwnd() )  m_DivorceView.DeleteView(0, 0);
    if ( m_ChangeView.GetSafeHwnd() )   m_ChangeView.DeleteView(0, 0);
    if ( m_DeathView.GetSafeHwnd() )    m_DeathView.DeleteView(0, 0);
    m_pTabCtrl->DestroyWindow();
    delete m_pTabCtrl;
  }
	CView::OnDestroy();
	// TODO: Add your message handler code here
}

void CTabView::OnInitialUpdate() {
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
  CEraABCDoc* pDoc = GetDocument() ;
  if ( NULL==pDoc )
    return;

  CWaitCursor wc;

  if ( NULL==m_BirthView.GetSafeHwnd() ) {
    m_BirthView.CreateStatic(m_pTabCtrl, 2, 1);
    m_BirthView.CreateView(0, 0, RUNTIME_CLASS(CFormBirth), CSize(100,120), NULL);
    m_BirthView.CreateView(1, 0, RUNTIME_CLASS(CBirthList), CSize(100,100), NULL);
    m_pTabCtrl->InsertItem(0, _T("Народження"), 0);
    m_Tabs.Add(&m_BirthView); 
  }
  else {
    m_BirthView.GetForm()->CloseRecordSet();
    m_BirthView.GetForm()->SendMessage(WM_INITIALUPDATE);
  }
  m_BirthView.GetListCtrl()->Fill();
  m_BirthView.GetForm()->SetFilled();

  if ( NULL==m_MarriageView.GetSafeHwnd() ) {
    m_MarriageView.CreateStatic(m_pTabCtrl, 2, 1);
    m_MarriageView.CreateView(1, 0, RUNTIME_CLASS(CMarriageList), CSize(100,100), NULL);
    m_MarriageView.CreateView(0, 0, RUNTIME_CLASS(CFormMarriage), CSize(100,140), NULL);
    m_pTabCtrl->InsertItem(1, _T("Шлюби"), 1);
    m_Tabs.Add(&m_MarriageView); 
  }
  else {
    m_MarriageView.GetForm()->CloseRecordSet();
    m_MarriageView.GetForm()->SendMessage(WM_INITIALUPDATE);
  }
  m_MarriageView.GetListCtrl()->Fill();
  m_MarriageView.GetForm()->SetFilled();

  if ( NULL==m_DivorceView.GetSafeHwnd() ) {
    m_DivorceView.CreateStatic(m_pTabCtrl, 2, 1);
    m_DivorceView.CreateView(1, 0, RUNTIME_CLASS(CDivorceList), CSize(100,100), NULL);
    m_DivorceView.CreateView(0, 0, RUNTIME_CLASS(CFormDivorce), CSize(100,148), NULL);
    m_pTabCtrl->InsertItem(2, _T("Розірвання Шлюбів"), 2);
    m_Tabs.Add(&m_DivorceView); 
  }
  else {
    m_DivorceView.GetForm()->CloseRecordSet();
    m_DivorceView.GetForm()->SendMessage(WM_INITIALUPDATE);
  }
  m_DivorceView.GetListCtrl()->Fill();
  m_DivorceView.GetForm()->SetFilled();

  if ( NULL==m_ChangeView.GetSafeHwnd() ) {
    m_ChangeView.CreateStatic(m_pTabCtrl, 2, 1);
    m_ChangeView.CreateView(1, 0, RUNTIME_CLASS(CChangeList), CSize(100,100), NULL);
    m_ChangeView.CreateView(0, 0, RUNTIME_CLASS(CFormChange), CSize(100,140), NULL);
    m_pTabCtrl->InsertItem(3, _T("Зміни"), 3);
    m_Tabs.Add(&m_ChangeView); 
  }
  else {
    m_ChangeView.GetForm()->CloseRecordSet();
    m_ChangeView.GetForm()->SendMessage(WM_INITIALUPDATE);
  }
  m_ChangeView.GetListCtrl()->Fill();
  m_ChangeView.GetForm()->SetFilled();

  if ( NULL==m_DeathView.GetSafeHwnd() ) {
    m_DeathView.CreateStatic(m_pTabCtrl, 2, 1);
    m_DeathView.CreateView(1, 0, RUNTIME_CLASS(CDeathList), CSize(100,100), NULL);
    m_DeathView.CreateView(0, 0, RUNTIME_CLASS(CFormDeath), CSize(100,120), NULL);
    m_pTabCtrl->InsertItem(4, _T("Смерті"), 4);
    m_Tabs.Add(&m_DeathView); 
  }
  else {
    m_DeathView.GetForm()->CloseRecordSet();
    m_DeathView.GetForm()->SendMessage(WM_INITIALUPDATE);
  }
  m_DeathView.GetListCtrl()->Fill();
  m_DeathView.GetForm()->SetFilled();

  SetActiveForm();

/************************************** : by VK at 02.02.2005 21:30:06 **\
  int nCurTab = 0;
  m_pTabCtrl->SetCurSel(nCurTab);
  m_pTabCtrl->SetCurFocus(nCurTab);

  CEraABCView* pActiveView = (CEraABCView*)m_Tabs.GetAt(nCurTab);
  CFormABC* pForm = pActiveView->GetForm();
  pActiveView->SetActivePane(0, 0);
  pForm->SetFocus();
  pForm->SetFocusToFirstControl();
\************************************** : by VK at 02.02.2005 21:30:09 **/
	
}

void CTabView::OnBirth() {
  m_pTabCtrl->SetCurSel(0);
}
void CTabView::OnMarriage() {
  m_pTabCtrl->SetCurSel(1);
}
void CTabView::OnDivorce() {
  m_pTabCtrl->SetCurSel(2);
}
void CTabView::OnChange() {
  m_pTabCtrl->SetCurSel(3);
}
void CTabView::OnDeath() {
  m_pTabCtrl->SetCurSel(4);
}

void CTabView::OnUpdateBirth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}
