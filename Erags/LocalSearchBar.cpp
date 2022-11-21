// LocalSearchBar.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "LocalSearchBar.h"

#include "DataManager.h"
#include "ChildFrm.h"
#include "EraForm.h"
#include "RSBirthes.h"
#include "RSChanges.h"
#include "RSDeathes.h"
#include "RSDivorces.h"
#include "RSMarriages.h"

#include "..\Common\DB.h"
#include "..\Common\MDB.h"
#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SC_NUMBER   0
#define SC_DATEREG  1
#define SC_FULLNAME 2

/////////////////////////////////////////////////////////////////////////////
// CSearchView
IMPLEMENT_DYNCREATE(CSearchView, CFormViewBG)

CSearchView::CSearchView():CFormViewBG(CSearchView::IDD) {
	//{{AFX_DATA_INIT(CSearchView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_pForm = NULL;
}

CSearchView::~CSearchView() {
  for( int i(0); i < m_Items.GetSize(); i++) {
    SearchItemData* pData = (SearchItemData*)m_Items.GetAt(i);
    if ( pData )
      delete pData;
  }
  m_Items.RemoveAll();
}
void CSearchView::DoDataExchange(CDataExchange* pDX) {
	CFormViewBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchView)
  DDX_Control(pDX, IDC_LBL_NUMBER, m_lblNumber);
  DDX_Control(pDX, IDC_LBL_PIB, m_lblPib);
	DDX_Control(pDX, IDC_PIB, m_PIB);
	DDX_Control(pDX, IDC_NUMBER, m_Number);
	DDX_Control(pDX, IDC_SEARCHLIST, m_SearchList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSearchView, CFormViewBG)
	//{{AFX_MSG_MAP(CSearchView)
 	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SEARCHLIST, OnItemChangedSearchList)
	ON_EN_CHANGE(IDC_PIB, OnChangePib)
	ON_EN_CHANGE(IDC_NUMBER, OnChangeNumber)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_SEARCHLIST, OnColumnClickSearchList)
  ON_WM_SIZE()
  ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
  ON_COMMAND(ID_HELP, OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchView diagnostics

#ifdef _DEBUG
void CSearchView::AssertValid() const {
	CFormViewBG::AssertValid();
}
void CSearchView::Dump(CDumpContext& dc) const {
	CFormViewBG::Dump(dc);
}
#endif //_DEBUG

BOOL CSearchView::Create(CWnd* pParentWnd, CFormView* pForm) {
  if ( FALSE==pForm->IsKindOf( RUNTIME_CLASS(CEraForm)) ) {
    return FALSE;
  }
  m_pForm = (CEraForm*)pForm;
  BOOL bRet = CFormViewBG::Create(NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), pParentWnd, 230665+m_pForm->m_idTemplate, NULL);
  if ( bRet )
    ShowWindow(SW_MAXIMIZE);
  return bRet;
}
void CSearchView::SetItemData(int nItem, long ID, short Number, bool Male, const COleDateTime& DateReg, const CString& SNP) {
  SearchItemData* pData = new SearchItemData;
  pData->ID      = ID;
  pData->Number  = Number;
  pData->Male    = Male;
  pData->DateReg = DateReg;
  pData->SNP     = SNP;
  m_Items.Add(pData);
  m_SearchList.SetItemData(nItem, (DWORD)pData);
}

void CSearchView::Refresh() {
  CWaitCursor wc;
  CDaoRecordset rs(&theDataManager.m_dbYear);
  CString sql;
  m_SearchList.DeleteAllItems();

  switch(theApp.m_nCurrentForm) {
    case ID_BIRTH:
      sql = _T("SELECT ID, NUMBER, SEX, DATEREG, SURNAME, NAME, PATRONYMIC, EXTNOTES FROM BIRTHES ORDER BY NUMBER");
      break;
    case ID_MARRIAGE:
      sql = _T("SELECT ID, NUMBER, DATEREG, MOLD_SURNAME, MNEW_SURNAME, MNAME, MPATRONYMIC, WOLD_SURNAME, WNEW_SURNAME, WNAME, WPATRONYMIC FROM MARRIAGES ORDER BY NUMBER");
      break;
    case ID_DIVORCE:
      sql = _T("SELECT ID, NUMBER, DATEREG, MOLD_SURNAME, MNEW_SURNAME, MNAME, MPATRONYMIC, WOLD_SURNAME, WNEW_SURNAME, WNAME, WPATRONYMIC FROM DIVORCES ORDER BY NUMBER");
      break;
    case ID_CHANGE:
      sql = _T("SELECT ID, NUMBER, DATEREG, SEX, OLDSURNAME, NEWSURNAME, OLDNAME, NEWNAME, OLDPATRONYMIC, NEWPATRONYMIC FROM CHANGES ORDER BY NUMBER");
       break;
    case ID_DEATH:
      sql = _T("SELECT ID, NUMBER, DATEREG, SEX, SURNAME, NAME, PATRONYMIC FROM DEATHES ORDER BY NUMBER");
       break;
  }
  try {
    CString sSurname, sNewSurname, sName, sNewName, sPatronymic, sNewPatronymic, sFullName, sMemo;
    int nItem = 0;
    rs.Open( dbOpenDynaset, sql, dbReadOnly);
    while ( FALSE==rs.IsEOF() ) {
      bool   fMale         = true;
      long   lID           = GetFieldLong(&rs, _T("ID"));
      short  Number        = GetFieldShort(&rs,  _T("NUMBER"));
      COleDateTime DateReg = GetFieldOleDateTime(&rs, _T("DATEREG"));
      CString sNumber  = GetFieldString(&rs, _T("NUMBER"));
      CString sDateReg = GetFieldDate(&rs, _T("DATEREG"), false);
      m_SearchList.InsertItem(nItem, sNumber );
      m_SearchList.SetItemText(nItem, SC_DATEREG, sDateReg);
      //m_SearchList.SetItemData(nItem, lID);
      switch(theApp.m_nCurrentForm) {
        case ID_BIRTH:
          fMale       = GetFieldBool(&rs, _T("SEX") );
          sSurname    = GetFieldString(&rs, _T("SURNAME"));
          sName       = GetFieldString(&rs, _T("NAME"));
          sPatronymic = GetFieldString(&rs, _T("PATRONYMIC"));
          sFullName   = MakeSNP( sSurname, sName, sPatronymic);
          m_SearchList.SetItemText(nItem, SC_FULLNAME, sFullName );
          m_SearchList.SetItem(nItem, 0, LVIF_IMAGE, NULL, fMale ? 1 : 0,  0, 0, lID);
          SetItemData(nItem, lID, Number, fMale, DateReg, sFullName);

          sMemo = GetFieldString(&rs, _T("EXTNOTES"));
          if ( FALSE==sMemo.IsEmpty() ) {
            sNewSurname    = CRSBirthes::GetNewSurnameFromMemo(sMemo, sSurname);
            sNewName       = CRSBirthes::GetNewNameFromMemo(sMemo, sName);
            sNewPatronymic = CRSBirthes::GetNewPatronymicFromMemo(sMemo, sPatronymic);
            if ( sSurname != sNewSurname || sName != sNewName || sPatronymic != sNewPatronymic ) {
              nItem++;
              sFullName   = MakeSNP(sNewSurname, sNewName, sNewPatronymic);
              m_SearchList.InsertItem(nItem, sNumber );
              m_SearchList.SetItemText(nItem, SC_DATEREG, sDateReg);
              m_SearchList.SetItemText(nItem, SC_FULLNAME, sFullName);
              m_SearchList.SetItem(nItem, 0, LVIF_IMAGE, NULL, fMale ? 1 : 0,  0, 0, lID);
              //m_SearchList.SetItemData(nItem, lID);
              SetItemData(nItem, lID, Number, fMale, DateReg, sFullName);
            }
          }
          break;
        case ID_MARRIAGE:
        case ID_DIVORCE:
          fMale = true;
          sSurname    = GetFieldString(&rs, _T("MOLD_SURNAME"));
          sName       = GetFieldString(&rs, _T("MNAME"));
          sPatronymic = GetFieldString(&rs, _T("MPATRONYMIC"));
          sFullName   = MakeSNP( sSurname, sName, sPatronymic);
          SetItemData(nItem, lID, Number, fMale, DateReg, sFullName);
          m_SearchList.SetItemText(nItem, SC_FULLNAME, sFullName );
          m_SearchList.SetItem(nItem, 0, LVIF_IMAGE, NULL, fMale ? 1 : 0,  0, 0, lID);
          sNewSurname = GetFieldString(&rs, _T("MNEW_SURNAME"));
          if ( FALSE==sNewSurname.IsEmpty() && sNewSurname != sSurname ) {
            sFullName   = MakeSNP(sNewSurname, sName, sPatronymic);
            nItem++;
            m_SearchList.InsertItem(nItem, sNumber );
            m_SearchList.SetItemText(nItem, SC_DATEREG, sDateReg);
            m_SearchList.SetItemText(nItem, SC_FULLNAME, sFullName);
            m_SearchList.SetItem(nItem, 0, LVIF_IMAGE, NULL, fMale ? 1 : 0,  0, 0, lID);
            //m_SearchList.SetItemData(nItem, lID);
            SetItemData(nItem, lID, Number, fMale, DateReg, sFullName);
          }
          nItem++;
          m_SearchList.InsertItem(nItem, sNumber );
          m_SearchList.SetItemText(nItem, SC_DATEREG, sDateReg);
          //m_SearchList.SetItemData(nItem, lID);
          fMale = false;
          sSurname    = GetFieldString(&rs, _T("WOLD_SURNAME"));
          sName       = GetFieldString(&rs, _T("WNAME"));
          sPatronymic = GetFieldString(&rs, _T("WPATRONYMIC"));
          sFullName   = MakeSNP( sSurname, sName, sPatronymic);
          m_SearchList.SetItemText(nItem, SC_FULLNAME, sFullName);
          m_SearchList.SetItem(nItem, 0, LVIF_IMAGE, NULL, fMale ? 1 : 0,  0, 0, lID);
          SetItemData(nItem, lID, Number, fMale, DateReg, sFullName);
          sNewSurname = GetFieldString(&rs, _T("WNEW_SURNAME"));
          if ( FALSE==sNewSurname.IsEmpty() && sNewSurname != sSurname ) {
            sFullName   = MakeSNP(sNewSurname, sName, sPatronymic);
            nItem++;
            m_SearchList.InsertItem(nItem, sNumber);
            m_SearchList.SetItemText(nItem, SC_DATEREG, sDateReg);
            m_SearchList.SetItemText(nItem, SC_FULLNAME, sFullName);
            //m_SearchList.SetItemData(nItem, lID);
            m_SearchList.SetItem(nItem, 0, LVIF_IMAGE, NULL, fMale ? 1 : 0,  0, 0, lID);
            SetItemData(nItem, lID, Number, fMale, DateReg, sFullName);
          }
          break;
        case ID_CHANGE:
          fMale = GetFieldBool(&rs, _T("SEX") );
          sSurname    = GetFieldString(&rs, _T("OLDSURNAME"));
          sName       = GetFieldString(&rs, _T("OLDNAME"));
          sPatronymic = GetFieldString(&rs, _T("OLDPATRONYMIC"));
          sFullName = MakeSNP(sSurname, sSurname, sPatronymic);
          m_SearchList.SetItemText(nItem, SC_FULLNAME, sFullName );
          m_SearchList.SetItem(nItem, 0, LVIF_IMAGE, NULL, fMale ? 1 : 0,  0, 0, lID);
          SetItemData(nItem, lID, Number, fMale, DateReg, sFullName);
          nItem++;
          m_SearchList.InsertItem(nItem, sNumber);
          m_SearchList.SetItemText(nItem, SC_DATEREG, sDateReg);
          sNewSurname    = GetFieldString(&rs, _T("NEWSURNAME"));
          sNewName       = GetFieldString(&rs, _T("NEWNAME"));
          sNewPatronymic = GetFieldString(&rs, _T("NEWPATRONYMIC"));
          sFullName = MakeSNP(sNewSurname, sNewName, sNewPatronymic);
          m_SearchList.SetItemText(nItem, SC_FULLNAME, sFullName );
          m_SearchList.SetItem(nItem, 0, LVIF_IMAGE, NULL, fMale ? 1 : 0,  0, 0, lID);
          //m_SearchList.SetItemData(nItem, lID);
          SetItemData(nItem, lID, Number, fMale, DateReg, sFullName);
          break;
        case ID_DEATH:
          fMale = GetFieldBool(&rs, _T("SEX") );
          sFullName = MakeSNP( GetFieldString(&rs, _T("SURNAME")), GetFieldString(&rs, _T("NAME")), GetFieldString(&rs, _T("PATRONYMIC")));
          m_SearchList.SetItemText(nItem, SC_FULLNAME, sFullName );
          m_SearchList.SetItem(nItem, 0, LVIF_IMAGE, NULL, fMale ? 1 : 0,  0, 0, lID);
          SetItemData(nItem, lID, Number, fMale, DateReg, sFullName);
          break;
      }
      rs.MoveNext();
      nItem++;
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return;
  }
}
/////////////////////////////////////////////////////////////////////////////
// CSearchView message handlers
void CSearchView::OnInitialUpdate()  {
	CFormViewBG::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
  if ( NULL==m_ImageList.GetSafeHandle() ) {
    m_SearchList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    m_ImageList.Create(IDB_IMLIST, 16, 0, RGB(0xFF, 0, 0xFF));
    m_SearchList.SetImageList(&m_ImageList, LVSIL_SMALL);

    m_SearchList.InsertColumn(SC_NUMBER,   _T(" № "),        LVCFMT_RIGHT, 48);
    m_SearchList.InsertColumn(SC_DATEREG,  _T(" Дата "),     LVCFMT_RIGHT, 68);
    m_SearchList.InsertColumn(SC_FULLNAME, _T(" Прізвище "), LVCFMT_LEFT, 104);

    CRect r;
    GetClientRect(&r);
    OnSize(SIZE_RESTORED, r.Width(), r.Height());
  }
  Refresh();
  GetParentFrame()->SetActiveView(this);
  SetActiveWindow();
  m_Number.SetFocus();
}
void CSearchView::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
  wFlags = SCALE_NONE;
}
void CSearchView::FillChildsMap() {
  m_ResizableEnabled = FALSE;
}
void CSearchView::OnSize(UINT nType, int cx, int cy)  {
	CFormViewBG::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
  if ( m_SearchList.GetSafeHwnd() && m_PIB.GetSafeHwnd() ) {
    CRect r;
    GetClientRect(&r);
    m_lblNumber.MoveWindow(8, 4, 34, 16, TRUE);
    m_Number.MoveWindow(51, 2, 45, 20, TRUE);
    m_lblPib.MoveWindow(102, 4, 24, 16, TRUE);
    m_PIB.MoveWindow(132, 2, 94, 20, TRUE);
    r.top = 28;
    m_SearchList.MoveWindow(&r, TRUE);
/************************************** : by VK at 22.11.2005 23:36:53 **\
    CRect r, rc;
    m_PIB.GetClientRect(&r);
    rc.top += r.bottom+8;
    m_SearchList.MoveWindow(&rc, TRUE);
\************************************** : by VK at 22.11.2005 23:36:56 **/
  }
}

BOOL CSearchView::OnEraseBkgnd(CDC* pDC) {
	// TODO: Add your message handler code here and/or call default
	CRect r, rList;
  pDC->GetClipBox(&r);
  m_SearchList.GetWindowRect(&rList);
  ScreenToClient(&rList);
  r.bottom = rList.top;
  GradientEraseBkgnd(this, GetParent(), pDC, r);
	return TRUE;
}
void CSearchView::OnItemChangedSearchList(NMHDR* pNMHDR, LRESULT* pResult) {

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  if ( pNMListView->iItem >= 0 && (pNMListView->uNewState & LVIS_FOCUSED) ) {
    int nFocusedItem = pNMListView->iItem;
    SearchItemData* pData = (SearchItemData*)m_SearchList.GetItemData(nFocusedItem);
    //long lID = (long)m_SearchList.GetItemData(nFocusedItem);
    m_pForm->Find(pData->ID);
  }
	*pResult = 0;
}

void CSearchView::OnChangePib() {
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormViewBG::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

  CString s;
  int nCount = m_SearchList.GetItemCount();
  GetDlgItem(IDC_PIB)->GetWindowText(s);
  s = Trim(s);

  if ( FALSE==s.IsEmpty() ) {
    CString sFullName;
    for( int i(0); i < nCount; i++ ) {
      sFullName = m_SearchList.GetItemText(i, SC_FULLNAME);
      int n = _strnicoll(s, sFullName, s.GetLength() );
      if ( 0==n ) {
        m_SearchList.EnsureVisible(i, TRUE);
        m_SearchList.SetItem(i, 0, LVIF_STATE, NULL, 0,  LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED, 0);
        break;
      }
    }
  }
}

void CSearchView::OnChangeNumber() {
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormViewBG::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

  CString s;
  int nCount = m_SearchList.GetItemCount();
  GetDlgItem(IDC_NUMBER)->GetWindowText(s);
  s = Trim(s);

  if ( FALSE==s.IsEmpty() ) {
    CString sNumber;
    for( int i(0); i < nCount; i++ ) {
      sNumber = m_SearchList.GetItemText(i, SC_NUMBER);
      int n = _strnicoll(s, sNumber, s.GetLength() );
      if ( 0==n ) {
        m_SearchList.EnsureVisible(i, TRUE);
        m_SearchList.SetItem(i, 0, LVIF_STATE, NULL, 0,  LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED, 0);
        break;
      }
    }
  }
}

void CSearchView::OnColumnClickSearchList(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  m_SearchList.SortItems(ListViewCompareProc, pNMListView->iSubItem);
	*pResult = 0;
}
int CALLBACK CSearchView::ListViewCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  int iResult(0);

	SearchItemData *pData1 = (SearchItemData*)lParam1;
	SearchItemData *pData2 = (SearchItemData*)lParam2;
  switch(lParamSort) {
    case SC_NUMBER:
      iResult = pData1->Number-pData2->Number;
      break;
    case SC_DATEREG:
      iResult = pData1->DateReg-pData2->DateReg;
      break;
    case SC_FULLNAME:
      iResult = CyrCompare(pData1->SNP, pData2->SNP);
      break;
  }
  return iResult;
}
void CSearchView::OnHelp() {
  theApp.OnHelp(_T("Search"));
}
/////////////////////////////////////////////////////////////////////////////
// CLocalSearchBar
IMPLEMENT_DYNCREATE(CLocalSearchBar, CLocalSearchBarBase)
CLocalSearchBar::CLocalSearchBar() {
  m_szMinHorz = CSize(33, 32);
  m_szMinVert = CSize(33, 32);
  m_szMinFloat = CSize(37, 32);
  m_szHorz = CSize(200, 200);
  m_szVert = CSize(258, 494);
  m_szFloat = CSize(254, 532);
  m_bTracking = FALSE;
  m_bKeepSize = FALSE;
  m_bParentSizing = FALSE;
  m_cxEdge = 5;
  m_bDragShowContent = FALSE;
  m_nDockBarID = 0;
  m_dwSCBStyle = 0;
  m_pParentFrame = NULL;
}

CLocalSearchBar::~CLocalSearchBar() {
/************************************** : by VK at 22.02.2005 22:43:08 **\
  if ( m_pSearchView ) {
    m_pSearchView->DestroyWindow();
    //delete m_pSearchView;
  }
\************************************** : by VK at 22.02.2005 22:43:10 **/
}

BEGIN_MESSAGE_MAP(CLocalSearchBar, CLocalSearchBarBase)
	//{{AFX_MSG_MAP(CLocalSearchBar)
	ON_WM_CREATE()
  ON_WM_WINDOWPOSCHANGED()
  ON_WM_SIZE()
  ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalSearchBar message handlers
int CLocalSearchBar::OnCreate(LPCREATESTRUCT lpCreateStruct) {
//  lpCreateStruct->style &= ~(WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
	if (CLocalSearchBarBase::OnCreate(lpCreateStruct) == -1)
		return -1;

  SetSCBStyle(GetSCBStyle() | SCBS_SIZECHILD);

  CChildFrame* pFrame = (CChildFrame*)GetParent();
	// TODO: Add your specialized creation code here
  m_pSearchView = new CSearchView();
  m_pSearchView->Create(this, (CFormView*)pFrame->m_pView);

	return 0;
}
void CLocalSearchBar::OnWindowPosChanged(WINDOWPOS* lpwndpos) {
  CLocalSearchBarBase::OnWindowPosChanged(lpwndpos);
  if ( lpwndpos->flags & SWP_HIDEWINDOW ) {
    if ( m_pParentFrame && IsWindow(m_pParentFrame->m_hWnd) ) {
      //m_pParentFrame->MDIActivate();
      m_pParentFrame->ActivateFrame(SW_SHOWMAXIMIZED);
      m_pParentFrame->SetActiveView(m_pParentFrame->m_pView);
    }
  }
}
void CLocalSearchBar::OnInitialUpdate() {
  if ( m_pSearchView && m_pSearchView->GetSafeHwnd() ) {
    m_pSearchView->SendMessage(WM_INITIALUPDATE);
  }
}

void CLocalSearchBar::OnSize(UINT nType, int cx, int cy)  {
	CLocalSearchBarBase::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
  if ( m_pSearchView && m_pSearchView->GetSafeHwnd() ) {
    CRect r;
    GetClientRect(&r);
    m_pSearchView->MoveWindow(&r, TRUE);
    //m_pSearchView->ShowWindow(SW_MAXIMIZE);
  }
}

void CLocalSearchBar::OnDestroy() {
  // TODO: Add your message handler code here
  CLocalSearchBarBase::OnDestroy();
  if ( m_pSearchView && m_pSearchView->GetSafeHwnd() )
    m_pSearchView->DestroyWindow();
}
