//
// GeoView.cpp
//
#include "stdafx.h"
#include "Erags.h"
#include "MainFrm.h"
#include "DataManager.h"
#include "ChildFrm.h"

#include "AddGeoDlg.h"
#include "GeoView.h"
#include "YesNoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGeoView*   g_pGeoView     = NULL;
CImageList  g_GeoImageList;

#define RLC_NAME     0
#define RLC_TYPE     1
#define RLC_ZIP      2
#define RLC_PHONE    3
#define RLC_DIRECORY 4

int GetGeoImageIndex(const CGeoRecord* pRecord) {
  int imageIndex = 0;
  if ( pRecord->IsCountry() ) {
    if ( pRecord->m_Name==_T("Україна") )
      imageIndex = 7;
    else
      imageIndex = 0;
  }
  else if ( pRecord->IsRegion() )
    imageIndex = 1;
  else if ( pRecord->IsCity() )
    imageIndex = 2;
  else if ( pRecord->IsDistrict() )
    imageIndex = 3;
  else if ( pRecord->m_Type.Find("смт")==0 )
    imageIndex = 4;
  else if ( pRecord->m_Type==_T("с") || pRecord->m_Type==_T("с.") )
    imageIndex = 6;
  else if ( pRecord->m_Type.Find("слщ")==0 || pRecord->m_Type.Find("с-ще")==0 || pRecord->m_Type.Find("сще")==0 || pRecord->m_Type==_T("селище") )
    imageIndex = 5;
  else
    imageIndex = 6;
  return imageIndex;
}


int CALLBACK GetGeoSortCmp(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  CGeoRecord* p1 = (CGeoRecord*)lParam1;
  CGeoRecord* p2 = (CGeoRecord*)lParam2;

  int w1 = p1->GetGeoTypeWeight();
  int w2 = p2->GetGeoTypeWeight();
  if ( w1==w2 )
    return CyrCompare(p1->m_Name, p2->m_Name);
  return w1-w2;
}

/////////////////////////////////////////////////////////////////////////////
// CGeoLTree
IMPLEMENT_DYNCREATE(CGeoLTree, CTreeView)
BEGIN_MESSAGE_MAP(CGeoLTree, CTreeView)
	//{{AFX_MSG_MAP(CGeoLTree)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
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
	ON_COMMAND(IDD_ADDCOUNTRY, OnAddCountry)
	ON_COMMAND(IDD_ADDREGION, OnAddRegion)
	ON_COMMAND(IDD_ADDDISTRICT, OnAddDistrict)
	ON_COMMAND(IDD_ADDCITY, OnAddCity)
  ON_COMMAND(IDD_RENAME, OnRename)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
  ON_COMMAND(IDD_DELETE_ITEM, OnRecordDelete)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
  ON_COMMAND(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CGeoLTree::CGeoLTree() {
  m_fInitialized = false;
  m_pRecord = NULL;
  m_MenuType = GEO_MENU_TYPE_TREE;
}
CGeoLTree::~CGeoLTree() {
}
/////////////////////////////////////////////////////////////////////////////
// CGeoLTree diagnostics
#ifdef _DEBUG
void CGeoLTree::AssertValid() const {
	CTreeView::AssertValid();
}
void CGeoLTree::Dump(CDumpContext& dc) const {
	CTreeView::Dump(dc);
}
#endif //_DEBUG
void CGeoLTree::RemoveFromTree(CGeoRecord* pRecord) {
  GetTreeCtrl().DeleteItem( pRecord->m_hItem );
}
/////////////////////////////////////////////////////////////////////////////
// CGeoLTree message handlers
void CGeoLTree::OnInitialUpdate() {
	CTreeView::OnInitialUpdate();

	if ( false==m_fInitialized ) {
    m_fInitialized = true;
    CTreeCtrl& TreeCtrl = GetTreeCtrl();

    TreeCtrl.SetImageList(&g_GeoImageList, TVSIL_NORMAL);

  }
  CString strTitle = _T("Список географічних назв");
  if ( theDataManager.m_dbLists.IsOpen() ) {
    strTitle.Format(_T("%s - Список географічних назв"), theDataManager.m_dbLists.GetName());
  }
  GetDocument()->SetTitle(strTitle);
}

void CGeoLTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  if ( pNMTreeView->itemNew.state & TVIS_SELECTED ) {
    if ( m_pRecord ) {
      GetTreeCtrl().SetItemState(m_pRecord->m_hItem , 0, TVIS_SELECTED);
    }
    m_pRecord = (CGeoRecord*)pNMTreeView->itemNew.lParam;
    g_pGeoView->OnLTreeSelchanged(m_pRecord);
  }
	*pResult = 0;
}
void CGeoLTree::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) {
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if ( VK_DELETE==pTVKeyDown->wVKey ) { 
    OnRecordDelete();
  }
	*pResult = 0;
}


void CGeoLTree::OnUpdateRecordFirst(CCmdUI* pCmdUI) {
  CGeoRecord* pFirst = theGeoCache.GetFirstRecord();
  BOOL fEnable = (m_pRecord != pFirst);
	pCmdUI->Enable(fEnable);
/*
  if ( false==fEnable ) {
    SetFocus();
  }
*/
}

void CGeoLTree::OnRecordFirst() {
  CGeoRecord* pFirst = theGeoCache.GetFirstRecord();
  if ( pFirst != m_pRecord ) {
/*
    CTreeCtrl& TreeCtrl =  GetTreeCtrl();
    TreeCtrl.SetItemState(m_pRecord->m_hItem ,          0, TVIS_SELECTED|LVIS_FOCUSED);
    TreeCtrl.SetItemState(pFirst->m_hItem , TVIS_SELECTED|LVIS_FOCUSED, TVIS_SELECTED|LVIS_FOCUSED);
    TreeCtrl.EnsureVisible(pFirst->m_hItem);
    m_pRecord = pFirst;
    g_pGeoView->OnLTreeSelchanged(m_pRecord);
*/
    SendMessage(WM_KEYDOWN, VK_HOME, 0);
  }
}

void CGeoLTree::OnUpdateRecordPrev(CCmdUI* pCmdUI) {
  BOOL fEnable = false;
  if ( m_pRecord ) {
    if ( m_pRecord->m_pParent ) {
      fEnable = true;
    }
    else if ( theGeoCache.m_array.GetSize() > 0 ) {
      CGeoRecord* pFirst = (CGeoRecord*)theGeoCache.m_array.GetAt(0);
      fEnable = (pFirst && pFirst != m_pRecord);
    }
  }
	pCmdUI->Enable(fEnable);
}

void CGeoLTree::OnRecordPrev() {
  SendMessage(WM_KEYDOWN, VK_UP, 0);
/*
  if ( m_pRecord ) {
    CGeoRecord* pPrev = theGeoCache.GetPrevRecord(m_pRecord);
    if ( pPrev && pPrev != m_pRecord ) {
    //SendMessage(WM_KEYDOWN, VK_UP, 0);
      CTreeCtrl& TreeCtrl =  GetTreeCtrl();
      TreeCtrl.SetItemState(m_pRecord->m_hItem ,             0, TVIS_SELECTED);
      TreeCtrl.SetItemState(pPrev->m_hItem     , TVIS_SELECTED, TVIS_SELECTED);
      TreeCtrl.EnsureVisible(pPrev->m_hItem);
      m_pRecord = pPrev;
      g_pGeoView->OnLTreeSelchanged(m_pRecord);
    }
  }
*/
}

void CGeoLTree::OnUpdateRecordNext(CCmdUI* pCmdUI) {
  BOOL fEnable = false;
  if ( m_pRecord ) {
    CGeoRecord* pLastRecord = theGeoCache.GetLastRecord(theGeoCache.m_array);
    fEnable = (m_pRecord != pLastRecord);
  }
	pCmdUI->Enable(fEnable);
}

void CGeoLTree::OnRecordNext() {
  CGeoRecord* pOldRecord = m_pRecord;
  SendMessage(WM_KEYDOWN, VK_DOWN, 0);
  if ( m_pRecord==pOldRecord ) {
    SendMessage(WM_KEYDOWN, VK_RIGHT, 0);
  }
}

void CGeoLTree::OnUpdateRecordLast(CCmdUI* pCmdUI) {
  OnUpdateRecordNext(pCmdUI);
}

void CGeoLTree::OnRecordLast() {
  CGeoRecord* pOldRecord = m_pRecord;
  SendMessage(WM_KEYDOWN, VK_END, 0);
  if ( m_pRecord==pOldRecord ) {
    SendMessage(WM_KEYDOWN, VK_RIGHT, 0);
  }
/************************************** : by VK at 27/06/2007 03:02:03 **\
  CGeoRecord* pLastRecord = theGeoCache.GetLastRecord(theGeoCache.m_array);
  if ( pLastRecord != m_pRecord ) {
    CTreeCtrl& TreeCtrl =  GetTreeCtrl();
    TreeCtrl.SetItemState(m_pRecord->m_hItem ,               0, TVIS_SELECTED);
    TreeCtrl.SetItemState(pLastRecord->m_hItem , TVIS_SELECTED, TVIS_SELECTED);
    TreeCtrl.EnsureVisible(pLastRecord->m_hItem);
    m_pRecord = pLastRecord;
    g_pGeoView->OnLTreeSelchanged(m_pRecord);
  }
\************************************** : by VK at 27/06/2007 03:02:08 **/
}

/////////////////////////////////////////////////////////////////////////////
// CGeoRList
IMPLEMENT_DYNCREATE(CGeoRList, CListView)
BEGIN_MESSAGE_MAP(CGeoRList, CListView)
	//{{AFX_MSG_MAP(CGeoRList)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
  ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
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
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
  ON_COMMAND(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CGeoRList::CGeoRList() {
  m_fInitialized = false;
  m_pRecord = NULL;
}
CGeoRList::~CGeoRList() {
}
/////////////////////////////////////////////////////////////////////////////
// CGeoRList diagnostics
#ifdef _DEBUG
void CGeoRList::AssertValid() const {
	CListView::AssertValid();
}
void CGeoRList::Dump(CDumpContext& dc) const {
	CListView::Dump(dc);
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CGeoRList message handlers
void CGeoRList::OnInitialUpdate() {
	CListView::OnInitialUpdate();

	if ( false==m_fInitialized ) {
    m_fInitialized = true;
    CListCtrl& ListCtrl = GetListCtrl();

    CFont* pFont = ListCtrl.GetFont();
    if ( pFont ) {
      LOGFONT lf;
      pFont->GetLogFont(&lf);
      lf.lfWeight = FW_BOLD;
      m_Bold.CreateFontIndirect(&lf);
    }
    
    ListCtrl.SetImageList(&g_GeoImageList, LVSIL_SMALL);
    ListCtrl.ModifyStyle(0, LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SHAREIMAGELISTS);
    ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);
    ListCtrl.InsertColumn(RLC_NAME,     _T("Назва"),          LVCFMT_LEFT, 240);
    ListCtrl.InsertColumn(RLC_TYPE,     _T("Тип"),            LVCFMT_LEFT,  60);
    ListCtrl.InsertColumn(RLC_ZIP,      _T("Індекс"),         LVCFMT_LEFT, 100);
    ListCtrl.InsertColumn(RLC_PHONE,    _T("Телефонний код"), LVCFMT_LEFT, 100);
    ListCtrl.InsertColumn(RLC_DIRECORY, _T("Довідкова"),      LVCFMT_LEFT, 100);
  }
  CString strTitle = _T("Список географічних назв");
  if ( theDataManager.m_dbLists.IsOpen() ) {
    strTitle.Format(_T("%s - Список географічних назв"), theDataManager.m_dbLists.GetName());
  }
  GetDocument()->SetTitle(strTitle);

}
void CGeoRList::RedrawListItem(int nItem, CGeoRecord* pRecord) {
  CListCtrl& ListCtrl = GetListCtrl();
  ListCtrl.SetItem(nItem, RLC_NAME, LVIF_TEXT|LVIF_IMAGE, pRecord->m_Name, GetGeoImageIndex(pRecord), 0, 0, (LPARAM)pRecord);
  ListCtrl.SetItemText(nItem, RLC_TYPE      , pRecord->GetTypeName());
  ListCtrl.SetItemText(nItem, RLC_ZIP       , pRecord->m_ZipCode);
  ListCtrl.SetItemText(nItem, RLC_PHONE     , pRecord->m_PhoneCode);
  ListCtrl.SetItemText(nItem, RLC_DIRECORY  , pRecord->m_Directory);
  ListCtrl.SetItemData(nItem, (DWORD)pRecord);
}

void CGeoRList::FillGeoList(CGeoRecord* pParentRecord) {
  CListCtrl& ListCtrl = GetListCtrl();
  ListCtrl.DeleteAllItems();
  if ( NULL==pParentRecord )
    return;
  m_pRecord = NULL;
  for( int i(0); i < pParentRecord->m_array.GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)pParentRecord->m_array.GetAt(i);
    ListCtrl.InsertItem(i, pRecord->m_Name, GetGeoImageIndex(pRecord) );
    RedrawListItem(i, pRecord);
  }
}
void CGeoRList::RemoveFromList(CGeoRecord* pRecord) {
  LVFINDINFO fi;
  fi.flags  = LVFI_PARAM;
  fi.lParam = (LPARAM)pRecord;
  CListCtrl& ListCtrl = GetListCtrl();
  int nItem = ListCtrl.FindItem(&fi);
  if ( nItem >= 0 ) {
    ListCtrl.DeleteItem(nItem);
  }
}
void CGeoRList::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  if ( pNMListView->uNewState & LVIS_SELECTED ) {
    m_pRecord = (CGeoRecord*)pNMListView->lParam;
  }

  g_pGeoView->OnRListItemchanged((NM_LISTVIEW*)pNMHDR);
	*pResult = 0;
}
void CGeoRList::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) {
  NMLVCUSTOMDRAW* pNMLVCustomDraw = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
  CGeoRecord* pRecord = (CGeoRecord*)pNMLVCustomDraw->nmcd.lItemlParam;
  switch (pNMLVCustomDraw->nmcd.dwDrawStage) {
    case CDDS_PREPAINT:
      *pResult = CDRF_NOTIFYITEMDRAW;
      break;
    case CDDS_ITEMPREPAINT:
    case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
      if ( pRecord && pRecord->Updated() ) {
        ::SelectObject(pNMLVCustomDraw->nmcd.hdc, m_Bold);
        *pResult = CDRF_NEWFONT;
      }
      else {
        *pResult = CDRF_DODEFAULT;
      }
      break;
  }
}
void CGeoRList::OnUpdateRecordFirst(CCmdUI* pCmdUI) {
  BOOL fEnable = false;
  if ( m_pRecord && AfxIsValidAddress(m_pRecord, sizeof(void*), true) ) {
    if ( m_pRecord->m_pParent && m_pRecord->m_pParent->m_array.GetSize() > 0 ) {
      CGeoRecord* pFirst = (CGeoRecord*)m_pRecord->m_pParent->m_array.GetAt(0);
      fEnable = (pFirst != m_pRecord);
    }
  }
  pCmdUI->Enable(fEnable);
}
void CGeoRList::OnRecordFirst() {
  SendMessage(WM_KEYDOWN, VK_HOME, 0);
}
void CGeoRList::OnUpdateRecordPrev(CCmdUI* pCmdUI) {
  OnUpdateRecordFirst(pCmdUI);
}
void CGeoRList::OnRecordPrev() {
  SendMessage(WM_KEYDOWN, VK_UP, 0);
}
void CGeoRList::OnUpdateRecordNext(CCmdUI* pCmdUI) {
  OnUpdateRecordLast(pCmdUI);
}
void CGeoRList::OnRecordNext() {
  SendMessage(WM_KEYDOWN, VK_DOWN, 0);
}
void CGeoRList::OnUpdateRecordLast(CCmdUI* pCmdUI) {
  BOOL fEnable = false;
  if ( m_pRecord ) {
    if ( m_pRecord->m_pParent && m_pRecord->m_pParent->m_array.GetSize() > 0 ) {
      int nLastIndex = m_pRecord->m_pParent->m_array.GetSize()-1;
      CGeoRecord* pLast = (CGeoRecord*)m_pRecord->m_pParent->m_array.GetAt(nLastIndex);
      fEnable = (pLast != m_pRecord);
    }
  }
  pCmdUI->Enable(fEnable);
}
void CGeoRList::OnRecordLast() {
  SendMessage(WM_KEYDOWN, VK_END, 0);
}
void CGeoLTree::OnUpdateRecordNew(CCmdUI* pCmdUI) {
	pCmdUI->Enable(theApp.m_fReadOnly != TRUE);
}
void CGeoLTree::OnRecordNew() {
	// TODO: Add your command handler code here
  if ( NULL==m_pRecord ) {
    return;
  }

  CRect r;
  if ( ((CMainFrame*)AfxGetMainWnd())->GetCommandButtonRect(ID_RECORD_NEW, &r) ) {
    CPoint p(r.left, r.bottom);
  	CNewMenu menu;
    menu.LoadMenu(IDM_GEOMENU);
    CNewMenu* pPopup = (CNewMenu*)menu.GetSubMenu(0);
    if ( pPopup ) {
      pPopup = (CNewMenu*)pPopup->GetSubMenu(0);
      if ( pPopup ) {
        pPopup->SetMenuTitle(_T("Додати"), MFT_GRADIENT|MFT_SIDE_TITLE|MFT_LINE);
        pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON, p.x, p.y, this);
      }
    }
  }
/*
  CRect r;
  if ( ((CMainFrame*)AfxGetMainWnd())->GetCommandButtonRect(ID_RECORD_NEW, &r) ) {
    CPoint p(r.left, r.bottom);

	  CNewMenu menu;
    menu.LoadMenu(IDM_GEOMENU);
    CNewMenu* pPopup = (CNewMenu*)menu.GetSubMenu(1);
    if ( pPopup ) {
      CString s;
      CGeoRecord* pParent = m_pRecord->m_pParent;
      if ( pParent ) {
        s.Format(_T("Додати до \"%s\""), GetGeoPath(pParent));
        pPopup->ModifyODMenu(ID_ADD_TO_PARENT, MF_BYCOMMAND, ID_ADD_TO_PARENT|MF_STRING, s);
      }
      else {
        pPopup->DeleteMenu(ID_ADD_TO_PARENT, MF_BYCOMMAND);
      }
      s.Format(_T("Додати до \"%s\""), GetGeoPath(m_pRecord));
      pPopup->ModifyODMenu(ID_ADD_TO_CURRENT, MF_BYCOMMAND, ID_ADD_TO_CURRENT|MF_STRING, s);

      pPopup->SetMenuTitle(_T("Додати"), MFT_GRADIENT|MFT_SIDE_TITLE|MFT_LINE);
      pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON, p.x, p.y, this);
    }
  }
*/
}
void CGeoLTree::OnUpdateRecordDelete(CCmdUI* pCmdUI) {
  BOOL fEnable = false;
  if ( m_pRecord && m_pRecord->m_array.GetSize()==0 ) {
    fEnable = true;
  }
  pCmdUI->Enable(fEnable);
}
void CGeoLTree::OnRecordDelete() {
  CTreeCtrl& GeoTree = GetTreeCtrl();
  HTREEITEM hItem = GeoTree.GetSelectedItem();
  if ( hItem ) {
    CString sText;
    CString sItemText = GeoTree.GetItemText(hItem);
    if ( GeoTree.ItemHasChildren(hItem) ) {
      sText.Format(_T("Назва \"%s\" має залежні назви. Видаліть спочатку їх."), sItemText );
      AfxMessageBox(sText);
    }
    else {
      // theGeoCache.Load 
      CGeoRecord* pRecord = (CGeoRecord*)GeoTree.GetItemData(hItem);
      g_pGeoView->RemoveFromCache(pRecord);
      g_pGeoView->OnRecordDelete(pRecord, true);
      GeoTree.DeleteItem(hItem);
      m_pRecord = NULL;
    }
  }
}
void CGeoLTree::OnAddCountry() {
  g_pGeoView->OnAddCountry(m_pRecord, true);
}
void CGeoLTree::OnAddRegion() {
  g_pGeoView->OnAddRegion(m_pRecord, true);
}
void CGeoLTree::OnAddDistrict() {
  g_pGeoView->OnAddDistrict(m_pRecord, true);
}
void CGeoLTree::OnAddCity() {
  g_pGeoView->OnAddCity(m_pRecord, true);
}
void CGeoLTree::OnRename() {
  CTreeCtrl& GeoTree = GetTreeCtrl();
  HTREEITEM hItem = GeoTree.GetSelectedItem();
  if ( hItem ) {
    CGeoRecord* pRecord = (CGeoRecord*)GeoTree.GetItemData(hItem);
    GeoTree.EditLabel(hItem);
  }
}

void CGeoLTree::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: Add your control notification handler code here
  m_MenuType = GEO_MENU_TYPE_TREE;
  CPoint p;

  CTreeCtrl& TreeCtrl = GetTreeCtrl();

  GetCursorPos(&p);
  TreeCtrl.ScreenToClient(&p);
  UINT uFlags;
  HTREEITEM hItem = TreeCtrl.HitTest(p, &uFlags);
  TreeCtrl.SelectItem(hItem);

  if ( theApp.m_fReadOnly ) {
    return;
  }
  
  CNewMenu menu;
  GetCursorPos(&p);
  menu.LoadMenu(IDM_GEOMENU);
  CNewMenu* pPopup = (CNewMenu*)menu.GetSubMenu(0);
  pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON, p.x, p.y, this);
	
	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeList
IMPLEMENT_DYNCREATE(CGeoTreeList, CView)
CGeoTreeList::CGeoTreeList() {
}
CGeoTreeList::~CGeoTreeList() {
}

BEGIN_MESSAGE_MAP(CGeoTreeList, CView)
	//{{AFX_MSG_MAP(CGeoTreeList)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeList drawing
void CGeoTreeList::OnDraw(CDC* pDC) {
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeList diagnostics
#ifdef _DEBUG
void CGeoTreeList::AssertValid() const {
	CView::AssertValid();
}
void CGeoTreeList::Dump(CDumpContext& dc) const {
	CView::Dump(dc);
}
#endif //_DEBUG

CGeoLTree* CGeoTreeList::GetLTree() {
  return (CGeoLTree*)m_Splitter.GetPane(0, 0);
}
CGeoRList* CGeoTreeList::GetRList() {
  return (CGeoRList*)m_Splitter.GetPane(0, 1);
}
void CGeoRList::OnUpdateRecordNew(CCmdUI* pCmdUI) {
	pCmdUI->Enable(true);
}

void CGeoRList::OnRecordNew() {
  if ( NULL==m_pRecord ) {
    return;
  }

  CRect r;
  if ( ((CMainFrame*)AfxGetMainWnd())->GetCommandButtonRect(ID_RECORD_NEW, &r) ) {
    CPoint p(r.left, r.bottom);
  	CNewMenu menu;
    menu.LoadMenu(IDM_GEOMENU);
    CNewMenu* pPopup = (CNewMenu*)menu.GetSubMenu(0);
    if ( pPopup ) {
      pPopup = (CNewMenu*)pPopup->GetSubMenu(0);
      if ( pPopup ) {
        pPopup->SetMenuTitle(_T("Додати"), MFT_GRADIENT|MFT_SIDE_TITLE|MFT_LINE);
        pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON, p.x, p.y, this);
      }
    }
  }
}
void CGeoRList::OnUpdateRecordDelete(CCmdUI* pCmdUI) {
  BOOL fEnable = false;
  if ( m_pRecord && m_pRecord->m_array.GetSize()==0 ) {
    fEnable = true;
  }
  pCmdUI->Enable(fEnable);

}
void CGeoRList::OnRecordDelete() {
  CDWordArray selItems;
  CPtrArray   selRecords;
  CListCtrl& ListCtrl = GetListCtrl();
  POSITION pos = ListCtrl.GetFirstSelectedItemPosition();
  int WithChidren = 0;
  int WithoutChidren = 0;
  while ( pos ) {
    CGeoRecord* pRecord = NULL;
    int nItem = ListCtrl.GetNextSelectedItem(pos);
    selItems.Add((DWORD)nItem);
    pRecord = (CGeoRecord*)ListCtrl.GetItemData(nItem);
    if ( pRecord->m_array.GetSize() > 0 ) {
      WithChidren++;
    }
    else {
      WithoutChidren++;
    }
    selRecords.Add(pRecord);
  }
  if ( 0==selItems.GetSize() ) {
    return;
  }
  if ( 0==WithoutChidren ) {
    AfxMessageBox(_T("Усі визначені елементи мають підлегли елементи. Потрібно спочатку видалити їх"));
    return;
  }
  CString s, sHowMutch;
  if ( 5 < WithoutChidren && WithoutChidren < 21 ) {
    sHowMutch = _T("елементів");
  }
  else {
    switch( WithoutChidren % 10 ) {
      case 1:                   sHowMutch = _T("елемент");   break;
      case 2: case 3: case 4:   sHowMutch = _T("елементи");  break;
      default:                  sHowMutch = _T("елементів"); break;
    }
  }
  s.Format( _T("Ви дійсно бажаєте видалити %d %s?"), WithoutChidren, sHowMutch);
  if ( YNDlg(this, _T("Увага! Вилучені елементи не можна відновити."), s)) {
    int i;
    for( i= 0; i < selRecords.GetSize(); i++ ) {
      CGeoRecord* pRecord = (CGeoRecord*)selRecords.GetAt(i);
      int nItem = (int)selItems.GetAt(i);
      if ( pRecord->m_array.GetSize()==0 ) {
        ListCtrl.DeleteItem(nItem);
        g_pGeoView->OnRecordDelete(pRecord, false);
        g_pGeoView->RemoveFromCache(pRecord);
        m_pRecord = NULL;

      }
    }
    int nItems = ListCtrl.GetItemCount();
    for( i = 0; i < nItems; i++ ) {
      ListCtrl.SetItemState(i, 0, LVIS_FOCUSED|LVIS_SELECTED);
    }
  }
}
void CGeoRList::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) {
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if ( VK_DELETE==pLVKeyDow->wVKey ) { 
    OnRecordDelete();
  }
#ifdef _DEBUG
  if ( (GetKeyState(VK_CONTROL) & 0x80000000) && 'C'==pLVKeyDow->wVKey ) { 
    CString szClipText;
    if ( OpenClipboard() ) {
      HANDLE hData = GetClipboardData(CF_TEXT);
      if ( hData ) {
        LPTSTR lptstr = (LPTSTR)GlobalLock(hData);
        if (lptstr != NULL) {
          szClipText = lptstr;
          GlobalUnlock(hData);
        }
      }
      CloseClipboard();
      if ( false==szClipText.IsEmpty() ) {
        CString sLine;
        int nTok = 0;
        while ( true ) {
          sLine = GetTok(szClipText, nTok, _T("\r\n"));
          if ( sLine.IsEmpty() ) {
            break;
          }
          sLine.Replace(_T("] ["), _T("]["));
          CString sIndex, sCode, sName;
          sIndex = GetTok(sLine, 0, _T("[]"));
          sCode  = GetTok(sLine, 1, _T("[]"));
          sName  = GetTok(sLine, 2, _T("[]"));
          int nFound = sName.Find('('); 
          if ( nFound > 0 ) {
            sName = Trim(sName.Left(nFound));
          }

          CListCtrl& ListCtrl = GetListCtrl();
          LVFINDINFO fi;
          fi.flags = LVFI_STRING;
          fi.psz = sName;
          int nItem = ListCtrl.FindItem(&fi);
          if ( nItem >= 0 ) {
            CGeoRecord* pRecord = (CGeoRecord*)ListCtrl.GetItemData(nItem);
            if ( pRecord && pRecord->m_ZipCode.IsEmpty() ) {
              sCode = Trim(sCode);
              pRecord->m_ZipCode   = sIndex;
              pRecord->m_PhoneCode = sCode;
              pRecord->Update();
              RedrawListItem(nItem, pRecord);
            }
          }
          nTok++;
        }
      }
    }
  }
#endif
	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CGeoTreeList message handlers
int CGeoTreeList::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

  if ( NULL==g_GeoImageList.m_hImageList ) {
    g_GeoImageList.Create( IDIL_GEOTREE, 16, 1, RGB(255, 0, 255) );
    g_GeoImageList.Add(AfxGetApp()->LoadIcon(IDI_UKRAINE));
  }

  CCreateContext context;
  context.m_pNewViewClass = NULL;
  context.m_pCurrentDoc   = GetDocument();
  context.m_pNewDocTemplate = theApp.m_pGeoTemplate;
  context.m_pLastView     = this;
  context.m_pCurrentFrame = GetParentFrame();

  if ( m_Splitter.CreateStatic(this, 1, 2) ) {
    m_Splitter.CreateView(0, 0, RUNTIME_CLASS(CGeoLTree),   CSize(300,600), &context);
    m_Splitter.CreateView(0, 1, RUNTIME_CLASS(CGeoRList),   CSize(500,600), &context);
  }
	return 0;
}

void CGeoTreeList::OnSize(UINT nType, int cx, int cy) {
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if ( m_Splitter.GetSafeHwnd() ) {
    CRect r;
    GetClientRect(&r);
    m_Splitter.MoveWindow(&r);
    m_Splitter.RecalcLayout();
    m_Splitter.RedrawWindow(NULL);
    CGeoLTree*  pLTree = GetLTree();
    if ( pLTree )
      pLTree->RedrawWindow(NULL);
    CGeoRList* pRList = GetRList();
    if ( pRList )
      pRList->RedrawWindow(NULL);
  }
}

/////////////////////////////////////////////////////////////////////////////
// CGeoForm
IMPLEMENT_DYNCREATE(CGeoForm, CFormViewBG)

CGeoForm::CGeoForm():CFormViewBG(CGeoForm::IDD) {
	//{{AFX_DATA_INIT(CGeoForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_fInitialized = m_fModified = false;
  m_OrigialRect.SetRect(0,0,0,0);
}

CGeoForm::~CGeoForm() {
}

void CGeoForm::DoDataExchange(CDataExchange* pDX) {
	CFormViewBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeoForm)
  DDX_Control(pDX, IDC_LBL_PATH, m_LblPath);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_ALTNAME, m_AltName);
	DDX_Control(pDX, IDC_TYPE, m_Type);
	DDX_Control(pDX, IDC_ZIP_CODES, m_Zips);
	DDX_Control(pDX, IDC_CODES, m_Codes);
  DDX_Control(pDX, IDC_DIRECTORY, m_Directory);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGeoForm, CFormViewBG)
	//{{AFX_MSG_MAP(CGeoForm)
  ON_WM_SIZE()
	ON_EN_CHANGE(IDC_NAME, OnChange)
	ON_EN_KILLFOCUS(IDC_NAME, OnKillfocus)
	ON_CBN_SELENDOK(IDC_TYPE, OnSelendokType)
  ON_EN_CHANGE(IDC_ALTNAME, OnChange)
	ON_EN_KILLFOCUS(IDC_ALTNAME, OnKillfocus)
  ON_EN_CHANGE(IDC_CODES, OnChange)
  ON_EN_KILLFOCUS(IDC_CODES, OnKillfocus)
  ON_EN_CHANGE(IDC_ZIP_CODES, OnChange)
  ON_EN_KILLFOCUS(IDC_ZIP_CODES, OnKillfocus)
  ON_EN_CHANGE(IDC_DIRECTORY, OnChange)
  ON_EN_KILLFOCUS(IDC_DIRECTORY, OnKillfocus)
	ON_CBN_KILLFOCUS(IDC_TYPE, OnKillfocusType)
  ON_COMMAND(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeoForm diagnostics

#ifdef _DEBUG
void CGeoForm::AssertValid() const {
	CFormViewBG::AssertValid();
}

void CGeoForm::Dump(CDumpContext& dc) const {
	CFormViewBG::Dump(dc);
}
#endif //_DEBUG

void CGeoForm::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
  wFlags = SCALE_WIDTH;//SCALE_NONE;
/*
  switch(pWnd->GetDlgCtrlID()) {
    case IDC_LBL_NAME:
    case IDC_LBL_ALTNAME:
    case IDC_LBL_TYPE:
    case IDC_LBL_PHONE:
    case IDC_LBL_ZIP_CODE:
      wFlags = SCALE_WIDTH;
      break;
    default:
      CFormViewBG::SetScaleFlags(pWnd, wFlags);
  }
*/
}

/*
void CGeoForm::OnMoveControl(CWnd* pWnd, LPRECT lpRect, BOOL bRepaint) {
  static CRect rLblPath;
  CRect r, rc;
  GetClientRect(&rc);
  int cy = lpRect->bottom - lpRect->top;
  switch( pWnd->GetDlgCtrlID() ) {
    case IDC_LBL_PATH     :
      lpRect->left = lpRect->top = 2;
      lpRect->bottom = lpRect->left + cy;
      lpRect->right = rc.Width()-2;
      rLblPath = lpRect;
      break;
    case IDC_LBL_NAME     :
    case IDC_NAME         :
    case IDC_LBL_TYPE     :
    case IDC_TYPE         :
    case IDC_LBL_PHONE    :
    case IDC_CODES        :
      lpRect->top = rLblPath.bottom + 2;
      lpRect->bottom = lpRect->top + cy;
      break;
    case IDC_LBL_ALTNAME  :
    case IDC_ALTNAME      :
    case IDC_LBL_ZIP_CODE :
    case IDC_ZIP_CODES    :
    case IDC_LBL_DIRECTORY:
    case IDC_DIRECTORY    :
      GetDlgItem(IDC_LBL_NAME)->GetWindowRect(&r);
      ScreenToClient(&r);
      lpRect->top = r.bottom + 2;
      lpRect->bottom = lpRect->top + cy;
      break;
  }
  switch( pWnd->GetDlgCtrlID() ) {
    case IDC_NAME   :
    case IDC_TYPE   :
    case IDC_CODES  :
      {
        CWnd* pWndPrev = pWnd->GetWindow(GW_HWNDPREV);
        pWndPrev->GetWindowRect(&r);
        ScreenToClient(&r);
        lpRect->left = r.right + 2;
      }
      break;
    case IDC_ALTNAME:
    case IDC_ZIP_CODES:
    case IDC_DIRECTORY:
      {
        CWnd* pWndPrev = pWnd->GetWindow(GW_HWNDPREV);
        pWndPrev->GetWindowRect(&r);
        ScreenToClient(&r);
        lpRect->left = r.right + 2;
      }
      break;
  }
  pWnd->MoveWindow(lpRect);
}
*/
void CGeoForm::FillForm(CGeoRecord* pRecord) {
  SetRedraw(false);
  m_Name     .SetWindowText(pRecord->m_Name);
  m_AltName  .SetWindowText(pRecord->m_AltName);
  m_Zips     .SetWindowText(pRecord->m_ZipCode);
  m_Codes    .SetWindowText(pRecord->m_PhoneCode);
  m_Directory.SetWindowText(pRecord->m_Directory);
  m_LblPath  .SetWindowText(GetGeoPath(pRecord));
  //m_LblPath  .InvalidateRect(NULL);
  CString sType = pRecord->GetTypeName();
  int nItem = m_Type.FindString(-1, sType);
  if ( CB_ERR==nItem ) {
    nItem = m_Type.AddString(sType);
  }
  m_Type.SetCurSel(nItem);
  m_fModified = false;
  SetRedraw(true);
  InvalidateRect(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CGeoForm message handlers
void CGeoForm::OnInitialUpdate() {
  m_ResizableEnabled = false;
	//CFormViewBG::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
  //CRect r(0, 0, 636, 70);
  //GetClientRect(&r);
  m_ResizableEnabled = true;
  OnSize(SIZE_RESTORED, 636, 70);

  if ( theApp.m_fReadOnly ) {
    SetRedraw(false);
    CWnd* pWnd = GetWindow(GW_CHILD);
    while( pWnd ) {
      pWnd->EnableWindow(false);
      pWnd = pWnd->GetWindow(GW_HWNDNEXT);
    }
    SetRedraw(true);
    InvalidateRect(NULL);
  }

/*
  if ( false==m_fInitialized ) {
    m_fInitialized = true;
    m_fRestoredRectSaved = true;
    m_RestoredRect = CRect(0,0, 636, 70);
    //GetClientRect(&rc);
  }
*/
}

void CGeoForm::OnSize(UINT nType, int cx, int cy) {
  CRect r;
  GetClientRect(&r);
  CFormViewBG::OnSize(nType, cx, cy);
  if ( SIZE_RESTORED==nType && cx > 0 && cy > 0 && 0==m_OrigialRect.bottom ) {
    GetClientRect(&m_OrigialRect);
  }
  if ( m_ResizableEnabled && false==m_fInitialized) {
    CFormViewBG::OnInitialUpdate();
    m_fInitialized = true;
  }
}
void CGeoForm::OnSave() {
  if ( theApp.m_fReadOnly ) {
    return;
  }

  CString szName, szAltName, szType, szZips, szCodes, szDirecory;
  szName     = m_Name.GetText();
  szAltName  = m_AltName.GetText();
  szType     = m_Type.GetCurText();
  szZips     = m_Zips.GetText();
  szCodes    = m_Codes.GetText();
  szDirecory = m_Directory.GetText();
  g_pGeoView->OnSave(szName, szAltName, szType, szZips, szCodes, szDirecory);
  m_fModified = false;
}
void CGeoForm::OnChange() {
  m_fModified = true;
}
void CGeoForm::OnKillfocus() {
	// TODO: Add your control notification handler code here
  if ( m_fModified ) {
    OnSave();
  }
}
void CGeoForm::OnSelendokType() {
  m_fModified = true;
}
void CGeoForm::OnKillfocusType() {
  if ( m_fModified ) {
    OnSave();
  }
}

/////////////////////////////////////////////////////////////////////////////
// CGeoViewSplitter
void CGeoViewSplitter::RecalcLayout() {
  CRect r;
  GetClientRect(&r);
  if ( r.Height() > 80 ) {
    SetRowInfo(1, r.Height()-70, 20);
  }
  SetRowInfo(1, 70, 10);
/*
  if ( r.Height() > 80 ) {
    m_pRowInfo[0].nIdealSize = m_pRowInfo[0].nMinSize = r.Height() - 80;
    //m_pRowInfo[1].nIdealSize = m_pRowInfo[1].nMinSize = 70;
  }
*/
  CSplitterWnd::RecalcLayout();
}
void CGeoViewSplitter::TrackRowSize(int y, int row) {
  CRect r;
  GetClientRect(&r);
  if ( r.Height() > 80 ) {
    SetRowInfo(1, r.Height()-70, 20);
  }
  SetRowInfo(1, 70, 10);
  CSplitterWnd::TrackRowSize(y, row);
}

/////////////////////////////////////////////////////////////////////////////
// CGeoView
IMPLEMENT_DYNCREATE(CGeoView, CView)
BEGIN_MESSAGE_MAP(CGeoView, CView)
	//{{AFX_MSG_MAP(CGeoView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGeoView::CGeoView() {
  m_pRecord = NULL;
}
CGeoView::~CGeoView() {
  g_pGeoView = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CGeoView diagnostics
#ifdef _DEBUG
void CGeoView::AssertValid() const {
	CView::AssertValid();
}
void CGeoView::Dump(CDumpContext& dc) const {
	CView::Dump(dc);
}
#endif //_DEBUG


CGeoTreeList* CGeoView::GetTree() {
  return (CGeoTreeList*)m_Splitter.GetPane(0, 0);
}
CGeoLTree* CGeoView::GetLTree() {
  return GetTree()->GetLTree();
}
CGeoRList* CGeoView::GetRList() {
  return GetTree()->GetRList();
}
CGeoForm*  CGeoView::GetForm() {
  return (CGeoForm*)m_Splitter.GetPane(1, 0);
}
void CGeoView::OnDraw(CDC* pDC) {
}

void CGeoView::Load(CPtrArray* pArray, HTREEITEM hParent) {
  CTreeCtrl& GeoTree = GetLTree()->GetTreeCtrl();
  for( int i(0); i < pArray->GetSize(); i++ ) {
    CGeoRecord* pRecord = (CGeoRecord*)pArray->GetAt(i);
    if ( pRecord ) {
      int imageIndex = GetGeoImageIndex(pRecord);
      CString s = pRecord->m_Name;
      if ( !pRecord->m_AltName.IsEmpty() )
        s.Format(_T("%s (%s)"), pRecord->m_Name, pRecord->m_AltName);
      
      HTREEITEM hInsertAfter = TVI_LAST;
      if ( s==_T("Україна") )
        hInsertAfter = TVI_FIRST;
      HTREEITEM hItem = GeoTree.InsertItem(s, imageIndex, imageIndex, hParent, hInsertAfter);
      GeoTree.SetItemData(hItem, (DWORD)pRecord);
      pRecord->m_hItem = hItem;
      if ( pRecord->m_array.GetSize() )
        Load(&pRecord->m_array, hItem);
    }
  }
}

int CGeoView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

  g_pGeoView = this;

  CCreateContext context;
  context.m_pNewViewClass = NULL;
  context.m_pCurrentDoc   = GetDocument();
  context.m_pNewDocTemplate = theApp.m_pGeoTemplate;
  context.m_pLastView     = this;
  context.m_pCurrentFrame = GetParentFrame();

  if ( m_Splitter.CreateStatic(this, 2, 1) ) {
    m_Splitter.CreateView(0, 0, RUNTIME_CLASS(CGeoTreeList),  CSize(600,530), &context);
    m_Splitter.CreateView(1, 0, RUNTIME_CLASS(CGeoForm),      CSize(600, 70), &context);
  }

  CChildFrame* pFrame = (CChildFrame*)GetParentFrame();
  pFrame->m_pView = this;
  theApp.m_pGeoFrame = pFrame;


  CRect rc;
  GetClientRect(&rc);
  OnSize(SIZE_MAXIMIZED, rc.Width(), rc.Height());
  
	CTreeCtrl& GeoTree = GetLTree()->GetTreeCtrl();
  GeoTree.ModifyStyle(0, TVS_HASLINES|TVS_LINESATROOT|TVS_EDITLABELS|TVS_HASBUTTONS|TVS_SHOWSELALWAYS);

  CListCtrl& GeoList = GetRList()->GetListCtrl();
  GeoList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);
  //
	// Add items to the tree.
	//
  Load(&theGeoCache.m_array, TVI_ROOT);
  m_pRecord = theGeoCache.GetFirstRecord();

  GetForm()->SendMessage(WM_INITIALUPDATE, 0, 0);

  GetLTree()->SetFocus();

/*
  OnLTreeSelchanged(m_pRecord);
  CTreeCtrl& TreeCtrl = GetLTree()->GetTreeCtrl();
  HTREEITEM hItem = TreeCtrl.GetRootItem();
  TreeCtrl.SelectItem(hItem);
*/
	return 0;
}
void CGeoView::OnInitialUpdate() {
  CString strTitle = _T("Список географічних назв");
  if ( theDataManager.m_dbLists.IsOpen() ) {
    strTitle.Format(_T("%s - Список географічних назв"), theDataManager.m_dbLists.GetName());
  }
  GetDocument()->SetTitle(strTitle);
}

/*
void CGeoView::OnLTreeSelchanged(NM_TREEVIEW* pNMTreeView) {
  if ( pNMTreeView->itemNew.state & TVIS_SELECTED ) {
    CTreeCtrl& GeoTree = GetLTree()->GetTreeCtrl();
    m_pRecord = (CGeoRecord*)pNMTreeView->itemNew.lParam;
    if ( m_pRecord->GetCount() ) {
      GetRList()->FillGeoList(m_pRecord);
    }
    GetForm()->FillForm(m_pRecord);
  }
}
*/
void CGeoView::OnLTreeSelchanged(CGeoRecord* pCurrentRecord) {
  if ( pCurrentRecord ) {
    CTreeCtrl& GeoTree = GetLTree()->GetTreeCtrl();
    m_pRecord = pCurrentRecord;
    if ( m_pRecord->GetCount() ) {
      GetRList()->FillGeoList(m_pRecord);
    }
    GetForm()->FillForm(m_pRecord);
  }
}
void CGeoView::OnRListItemchanged(NM_LISTVIEW* pNMListView) {
  if ( pNMListView->uNewState & LVIS_SELECTED ) {
    m_pRecord = (CGeoRecord*)pNMListView->lParam;
    GetForm()->FillForm(m_pRecord);
  }
}
void CGeoView::OnSave(CString& szName, CString& szAltName, CString& szType, CString& szZips, CString& szCodes, CString& szDirectory) {
  if ( theApp.m_fReadOnly ) {
    return;
  }
  if ( m_pRecord ) {
    m_pRecord->m_Name      = szName;
    m_pRecord->m_AltName   = szAltName;
    m_pRecord->m_Type      = szType;
    m_pRecord->m_ZipCode   = szZips;
    m_pRecord->m_PhoneCode = szCodes;
    m_pRecord->m_Directory = szDirectory;
    m_pRecord->Update();

    CTreeCtrl& TreeCtrl = GetLTree()->GetTreeCtrl();
    TreeCtrl.SetItem(m_pRecord->m_hItem, TVIF_STATE|TVIF_TEXT, m_pRecord->GetNameWithAltName(), 0, 0, TVIS_BOLD, TVIS_BOLD, 0);

    CListCtrl& ListCtrl = GetRList()->GetListCtrl();
    LVFINDINFO fi;
    fi.flags = LVFI_PARAM;
    fi.lParam = (LPARAM)m_pRecord;
    int nItem = ListCtrl.FindItem(&fi);
    if ( nItem >=0 ) {
      GetRList()->RedrawListItem(nItem, m_pRecord);
    }
  }
}
void CGeoView::OnSize(UINT nType, int cx, int cy) {
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if ( m_Splitter.GetSafeHwnd() ) {
    CRect r;
    GetClientRect(&r);
    CGeoTreeList*  pTree = GetTree();
    CGeoForm* pForm = GetForm();
    m_Splitter.MoveWindow(&r);
    m_Splitter.SetRowInfo(1, 70, 70);
    /*
    if ( r.Height() > 140 ) {
      if ( pTree ) {
        pTree->MoveWindow(r.left, r.top, r.right, r.bottom-100);
      }
      if ( pForm ) {
        pTree->MoveWindow(r.left, r.bottom-100, r.right, r.bottom);
      }
    }
    */
    m_Splitter.RecalcLayout();
    m_Splitter.RedrawWindow(NULL);
    if ( pTree )
      pTree->RedrawWindow(NULL);
    if ( pForm )
      pForm->RedrawWindow(NULL);

/************************************** : by VK 30.08.2005 at 13:42:30 **\
    double* pBestScale;
    UINT nl;
    if(AfxGetApp()->GetProfileBinary(_T("Products"), _TEXT("BS"), (LPBYTE*)&pBestScale, &nl)) {
      CRect r;
      m_Splitter.SetColumnInfo(0, (int)(r.Width()* *pBestScale+0.5),         10);
      m_Splitter.SetColumnInfo(1, (int)(r.Width()*(1.0-*pBestScale)+0.5),    10);
      m_Splitter.RecalcLayout();
      delete pBestScale;
    }
\************************************** : by VK 30.08.2005 at 13:42:34 **/
  }
}

void CGeoView::AddToTreeAndList(CGeoRecord* pRecord) {
  int imageIndex = GetGeoImageIndex(pRecord);
  CGeoRecord* pParentRecord = pRecord->m_pParent;

  CTreeCtrl& GeoTree = GetLTree()->GetTreeCtrl();
  CListCtrl& GeoList = GetRList()->GetListCtrl();

  HTREEITEM hParentItem = NULL;
  if ( NULL==pParentRecord )
    hParentItem = TVI_ROOT;
  else {
    hParentItem = pParentRecord->m_hItem;
  }
  CString s = pRecord->GetNameWithAltName();

  HTREEITEM hNewItem = GeoTree.InsertItem(s, imageIndex, imageIndex, hParentItem);
  if ( hNewItem ) {
    GeoTree.SetItemData(hNewItem, (DWORD)pRecord);
    pRecord->m_hItem = hNewItem;
    GeoTree.SetItem(hNewItem, TVIF_STATE, NULL, 0, 0, TVIS_BOLD, TVIS_BOLD, 0);

    TVSORTCB tvSort;
    tvSort.hParent      = hParentItem; // hParent Item
    tvSort.lParam       = (LPARAM)NULL;
    tvSort.lpfnCompare  = GetGeoSortCmp;

    GeoTree.SortChildrenCB(&tvSort);
    GeoTree.EnsureVisible(hNewItem);

    if ( GeoList.GetItemCount() > 0 ) {
      CGeoRecord* pFirstRecord = (CGeoRecord*)GeoList.GetItemData(0);
      if ( pFirstRecord->m_pParent==pRecord->m_pParent ) { // the same level
        int nItem = GeoList.InsertItem(GeoList.GetItemCount(), pRecord->m_Name, GetGeoImageIndex(pRecord));
        GetRList()->RedrawListItem(nItem, pRecord);
        GeoList.EnsureVisible(nItem, FALSE);
      }
    }

/*
    HTREEITEM hSelectedItem = GeoTree.GetSelectedItem();
    if ( hSelectedItem==hParentItem ) {
      int nItem = GeoList.InsertItem(GeoList.GetItemCount(), pRecord->m_Name, GetGeoImageIndex(pRecord));
      GetRList()->RedrawListItem(nItem, pRecord);
      GeoList.EnsureVisible(nItem, FALSE);
    }
*/
  }
}
void CGeoView::OnAdd(CGeoRecord* pRecord, BOOL fFromLTree, int GeoType) {
	CAddGeoDlg dlg(this, (ERAGSGEOTYPE)GeoType);
  dlg.m_pParentGeoRecord = pRecord;
  dlg.DoModal();
  if ( dlg.m_fOk && dlg.m_pRecord ) {
    AddToTreeAndList(dlg.m_pRecord);
  }
}
void CGeoView::OnAddCountry(CGeoRecord* pRecord, BOOL fFromLTree) {
  OnAdd(pRecord, fFromLTree, GT_COUNTRY);
}
void CGeoView::OnAddRegion(CGeoRecord* pRecord, BOOL fFromLTree) {
  OnAdd(pRecord, fFromLTree, GT_REGION);
}
void CGeoView::OnAddDistrict(CGeoRecord* pRecord, BOOL fFromLTree) {
  OnAdd(pRecord, fFromLTree, GT_DISTRICT);
}
void CGeoView::OnAddCity(CGeoRecord* pRecord, BOOL fFromLTree) {
  OnAdd(pRecord, fFromLTree, GT_CITY);
}
void CGeoView::OnRecordDelete(CGeoRecord* pRecord, BOOL fFromLTree) {
  if ( fFromLTree ) {
    GetRList()->RemoveFromList(pRecord);
  }
  else {
    GetLTree()->RemoveFromTree(pRecord);
  }
}
void CGeoView::RemoveFromCache(CGeoRecord* pRecord) {
  if ( pRecord ) {
    if ( pRecord->m_pParent )
      pRecord->m_pParent->RemoveRecordFromArray( pRecord );
    else
      theGeoCache.RemoveRecordFromArray( pRecord );
  }
}

void CGeoLTree::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) {
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
  if ( pTVDispInfo->item.pszText ) {
    CTreeCtrl& GeoTree = GetTreeCtrl();
    HTREEITEM hItem = pTVDispInfo->item.hItem;
    GeoTree.SetItemText(hItem, pTVDispInfo->item.pszText);
    CGeoRecord* pRecord = (CGeoRecord*)GeoTree.GetItemData(hItem);
    CString sName, sFullName;
    int lBracket(0), rBracket(0);
    sName = pTVDispInfo->item.pszText;
    lBracket = sName.Find('(');
    rBracket = sName.Find(')');
    // Абхазія (Республіка Абхазія)
    //         9                  28
    if ( lBracket >= 0 && rBracket > lBracket ) {
      pRecord->m_Name = Trim(sName.Left(lBracket));
      pRecord->m_AltName = sName.Mid(lBracket+1,rBracket-lBracket-1);
      pRecord->m_AltName.TrimRight('(');
      pRecord->m_AltName.TrimRight(')');
    }
    else {
      pRecord->m_Name = pTVDispInfo->item.pszText;
      pRecord->m_AltName.Empty();
    }
    pRecord->Update();
    GeoTree.SetItem(m_pRecord->m_hItem, TVIF_STATE|TVIF_TEXT, pRecord->GetNameWithAltName(), 0, 0, TVIS_BOLD, TVIS_BOLD, 0);
  }
	*pResult = 0;
	
	*pResult = 0;
}

void CGeoLTree::OnHelp() {
  theApp.OnHelp(_T("Lists"), _T("#GeoList"));
}
void CGeoRList::OnHelp() {
  theApp.OnHelp(_T("Lists"), _T("#GeoList"));
}
void CGeoForm::OnHelp() {
  theApp.OnHelp(_T("Lists"), _T("#GeoList"));
}
