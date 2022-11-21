// ABCList.cpp : implementation of the CABCList class
//

#include "stdafx.h"
#include "EraABC.h"

#include "EraABCDoc.h"
#include "EraABCView.h"
#include "ABCList.h"
#include "FormABC.h"

#include "DateFunc.h"
#include "rsBirthes.h"
#include "rsMarriages.h"
#include "rsDivorces.h"
#include "rsChanges.h"
#include "rsDeathes.h"

#include "YesNoDlg.h"

#include "..\Common\CyrString.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern COLORREF g_clrMaleForeColor;
extern COLORREF g_clrFemaleForeColor;


int CALLBACK CompareABCProcBirth(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  int iResult(0);
  CBirthList* pABCList = (CBirthList*)lParamSort;
  ABCItemDataBirth* pData1 = (ABCItemDataBirth*)lParam1;
  ABCItemDataBirth* pData2 = (ABCItemDataBirth*)lParam2;
  switch( pABCList->m_SortColumn ) {
    case BC_SEX:
      iResult = (pData1->m_fMale - pData2->m_fMale);
      return (SO_ASC==pABCList->m_SortOrder[BC_SEX]) ? iResult : -iResult;
    case BC_NUMBER:
      iResult = (pData1->m_Number - pData2->m_Number);
      return (SO_ASC==pABCList->m_SortOrder[BC_NUMBER]) ? iResult : -iResult;
    case BC_DATEREG:
      iResult = (int)(pData1->m_DateReg - pData2->m_DateReg);
      return (SO_ASC==pABCList->m_SortOrder[BC_DATEREG]) ? iResult : -iResult;
    case BC_SURNAME:
      iResult = CyrCompare(pData1->m_Surname, pData2->m_Surname);
      return (SO_ASC==pABCList->m_SortOrder[BC_SURNAME]) ? iResult : -iResult;
      break;
    case BC_NAME:
      iResult = CyrCompare(pData1->m_Name, pData2->m_Name);
      return (SO_ASC==pABCList->m_SortOrder[BC_NAME]) ? iResult : -iResult;
    case BC_PATRONYMIC:
      iResult = CyrCompare(pData1->m_Patronymic, pData2->m_Patronymic);
      return (SO_ASC==pABCList->m_SortOrder[BC_PATRONYMIC]) ? iResult : -iResult;
  }
  return iResult;
}
int CALLBACK CompareABCProcMarriage(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  int iResult(0);
  CMarriageList* pABCList = (CMarriageList*)lParamSort;
  ABCItemDataMarriage* pData1 = (ABCItemDataMarriage*)lParam1;
  ABCItemDataMarriage* pData2 = (ABCItemDataMarriage*)lParam2;
  switch( pABCList->m_SortColumn ) {
    case MC_NUMBER:
      iResult = (pData1->m_Number - pData2->m_Number);
      return (SO_ASC==pABCList->m_SortOrder[MC_NUMBER]) ? iResult : -iResult;
    case MC_DATEREG:
      iResult = (int)(pData1->m_DateReg - pData2->m_DateReg);
      return (SO_ASC==pABCList->m_SortOrder[MC_DATEREG]) ? iResult : -iResult;
    case MC_MOLD_SURNAME:
      iResult = CyrCompare(pData1->m_MOldSurname, pData2->m_MOldSurname);
      return (SO_ASC==pABCList->m_SortOrder[MC_MOLD_SURNAME]) ? iResult : -iResult;
    case MC_MNEW_SURNAME:
      iResult = CyrCompare(pData1->m_MNewSurname, pData2->m_MNewSurname);
      return (SO_ASC==pABCList->m_SortOrder[MC_MNEW_SURNAME]) ? iResult : -iResult;
    case MC_MNAME:
      iResult = CyrCompare(pData1->m_MName, pData2->m_MName);
      return (SO_ASC==pABCList->m_SortOrder[MC_MNAME]) ? iResult : -iResult;
    case MC_MPATRONYMIC:
      iResult = CyrCompare(pData1->m_MPatronymic, pData2->m_MPatronymic);
      return (SO_ASC==pABCList->m_SortOrder[MC_MPATRONYMIC]) ? iResult : -iResult;
    case MC_WOLD_SURNAME:
      iResult = CyrCompare(pData1->m_WOldSurname, pData2->m_WOldSurname);
      return (SO_ASC==pABCList->m_SortOrder[MC_WOLD_SURNAME]) ? iResult : -iResult;
    case MC_WNEW_SURNAME:
      iResult = CyrCompare(pData1->m_WNewSurname, pData2->m_WNewSurname);
      return (SO_ASC==pABCList->m_SortOrder[MC_WNEW_SURNAME]) ? iResult : -iResult;
    case MC_WNAME:
      iResult = CyrCompare(pData1->m_WName, pData2->m_WName);
      return (SO_ASC==pABCList->m_SortOrder[MC_WNAME]) ? iResult : -iResult;
    case MC_WPATRONYMIC:
      iResult = CyrCompare(pData1->m_WPatronymic, pData2->m_WPatronymic);
      return (SO_ASC==pABCList->m_SortOrder[MC_WPATRONYMIC]) ? iResult : -iResult;
  }
  return iResult;
}
int CALLBACK CompareABCProcDivorce(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  int iResult(0);
  CDivorceList* pABCList = (CDivorceList*)lParamSort;
  ABCItemDataDivorce* pData1 = (ABCItemDataDivorce*)lParam1;
  ABCItemDataDivorce* pData2 = (ABCItemDataDivorce*)lParam2;
  switch( pABCList->m_SortColumn ) {
    case DIVC_NUMBER:
      iResult = (pData1->m_Number - pData2->m_Number);
      return (SO_ASC==pABCList->m_SortOrder[DIVC_NUMBER]) ? iResult : -iResult;
    case DIVC_DATEREG:
      iResult = (int)(pData1->m_DateReg - pData2->m_DateReg);
      return (SO_ASC==pABCList->m_SortOrder[DIVC_DATEREG]) ? iResult : -iResult;
    case DIVC_MOLD_SURNAME:
      iResult = CyrCompare(pData1->m_MOldSurname, pData2->m_MOldSurname);
      return (SO_ASC==pABCList->m_SortOrder[DIVC_MOLD_SURNAME]) ? iResult : -iResult;
    case DIVC_MNEW_SURNAME:
      iResult = CyrCompare(pData1->m_MNewSurname, pData2->m_MNewSurname);
      return (SO_ASC==pABCList->m_SortOrder[DIVC_MNEW_SURNAME]) ? iResult : -iResult;
    case DIVC_MNAME:
      iResult = CyrCompare(pData1->m_MName, pData2->m_MName);
      return (SO_ASC==pABCList->m_SortOrder[DIVC_MNAME]) ? iResult : -iResult;
    case DIVC_MPATRONYMIC:
      iResult = CyrCompare(pData1->m_MPatronymic, pData2->m_MPatronymic);
      return (SO_ASC==pABCList->m_SortOrder[DIVC_MPATRONYMIC]) ? iResult : -iResult;
    case DIVC_WOLD_SURNAME:
      iResult = CyrCompare(pData1->m_WOldSurname, pData2->m_WOldSurname);
      return (SO_ASC==pABCList->m_SortOrder[DIVC_WOLD_SURNAME]) ? iResult : -iResult;
    case DIVC_WNEW_SURNAME:
      iResult = CyrCompare(pData1->m_WNewSurname, pData2->m_WNewSurname);
      return (SO_ASC==pABCList->m_SortOrder[DIVC_WNEW_SURNAME]) ? iResult : -iResult;
    case DIVC_WNAME:
      iResult = CyrCompare(pData1->m_WName, pData2->m_WName);
      return (SO_ASC==pABCList->m_SortOrder[DIVC_WNAME]) ? iResult : -iResult;
    case DIVC_WPATRONYMIC:
      iResult = CyrCompare(pData1->m_WPatronymic, pData2->m_WPatronymic);
      return (SO_ASC==pABCList->m_SortOrder[DIVC_WPATRONYMIC]) ? iResult : -iResult;
  }
  return iResult;
}
int CALLBACK CompareABCProcChange(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  int iResult(0);
  CChangeList* pABCList = (CChangeList*)lParamSort;
  ABCItemDataChange* pData1 = (ABCItemDataChange*)lParam1;
  ABCItemDataChange* pData2 = (ABCItemDataChange*)lParam2;
  switch( pABCList->m_SortColumn ) {
    case CC_SEX:
      iResult = (pData1->m_fMale - pData2->m_fMale);
      return (SO_ASC==pABCList->m_SortOrder[CC_SEX]) ? iResult : -iResult;
    case CC_NUMBER:
      iResult = (pData1->m_Number - pData2->m_Number);
      return (SO_ASC==pABCList->m_SortOrder[CC_NUMBER]) ? iResult : -iResult;
    case CC_DATEREG:
      iResult = (int)(pData1->m_DateReg - pData2->m_DateReg);
      return (SO_ASC==pABCList->m_SortOrder[CC_DATEREG]) ? iResult : -iResult;
    case CC_OLDSURNAME:
      iResult = CyrCompare(pData1->m_OldSurname, pData2->m_OldSurname);
      return (SO_ASC==pABCList->m_SortOrder[CC_OLDSURNAME]) ? iResult : -iResult;
    case CC_NEWSURNAME:
      iResult = CyrCompare(pData1->m_NewSurname, pData2->m_NewSurname);
      return (SO_ASC==pABCList->m_SortOrder[CC_NEWSURNAME]) ? iResult : -iResult;
    case CC_OLDNAME:
      iResult = CyrCompare(pData1->m_OldName, pData2->m_OldName);
      return (SO_ASC==pABCList->m_SortOrder[CC_OLDNAME]) ? iResult : -iResult;
    case CC_NEWNAME:
      iResult = CyrCompare(pData1->m_NewName, pData2->m_NewName);
      return (SO_ASC==pABCList->m_SortOrder[CC_NEWNAME]) ? iResult : -iResult;
    case CC_OLDPATRONYMIC:
      iResult = CyrCompare(pData1->m_OldPatronymic, pData2->m_OldPatronymic);
      return (SO_ASC==pABCList->m_SortOrder[CC_OLDPATRONYMIC]) ? iResult : -iResult;
    case CC_NEWPATRONYMIC:
      iResult = CyrCompare(pData1->m_NewPatronymic, pData2->m_NewPatronymic);
      return (SO_ASC==pABCList->m_SortOrder[CC_NEWPATRONYMIC]) ? iResult : -iResult;
  }
  return iResult;
}
int CALLBACK CompareABCProcDeath(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  int iResult(0);
  CDeathList* pABCList = (CDeathList*)lParamSort;
  ABCItemDataDeath* pData1 = (ABCItemDataDeath*)lParam1;
  ABCItemDataDeath* pData2 = (ABCItemDataDeath*)lParam2;
  switch( pABCList->m_SortColumn ) {
    case   DC_SEX         : // 0
      iResult = (pData1->m_fMale - pData2->m_fMale);
      return (SO_ASC==pABCList->m_SortOrder[DC_SEX]) ? iResult : -iResult;
    case   DC_NUMBER      : // 1
      iResult = (pData1->m_Number - pData2->m_Number);
      return (SO_ASC==pABCList->m_SortOrder[DC_NUMBER]) ? iResult : -iResult;
    case   DC_DATEREG     : // 2
      iResult = (int)(pData1->m_DateReg - pData2->m_DateReg);
      return (SO_ASC==pABCList->m_SortOrder[DC_DATEREG]) ? iResult : -iResult;
    case   DC_SURNAME     : // 3
      iResult = CyrCompare(pData1->m_Surname, pData2->m_Surname);
      return (SO_ASC==pABCList->m_SortOrder[DC_SURNAME]) ? iResult : -iResult;
    case   DC_NAME        : // 4
      iResult = CyrCompare(pData1->m_Name, pData2->m_Name);
      return (SO_ASC==pABCList->m_SortOrder[DC_NAME]) ? iResult : -iResult;
    case   DC_PATRONYMIC  : // 5
      iResult = CyrCompare(pData1->m_Patronymic, pData2->m_Patronymic);
      return (SO_ASC==pABCList->m_SortOrder[DC_PATRONYMIC]) ? iResult : -iResult;
  }
  return iResult;
}

BOOL MoveFirst(CDaoRecordset* pSet) {
  try {
    if ( pSet->IsBOF() && pSet->IsEOF() )
      return FALSE;
    pSet->MoveFirst();
  }
  catch(CDaoException* e) {
    e->Delete();
    return FALSE;
  }
  return TRUE;
}
BOOL MoveLast(CDaoRecordset* pSet) {
  try {
    if ( pSet->IsBOF() && pSet->IsEOF() )
      return FALSE;
      pSet->MoveLast();
  }
  catch(CDaoException* e) {
    e->Delete();
    return FALSE;
  }
  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CABCList
IMPLEMENT_DYNCREATE(CABCList, CListView)
BEGIN_MESSAGE_MAP(CABCList, CListView)
	//{{AFX_MSG_MAP(CABCList)
  ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
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
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
  ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteItem)
  ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CABCList construction/destruction
CABCList::CABCList() {
  m_SortColumn = -1;
  m_FocusedItem = -1;
  m_FocusedID = -1;
  m_fInitialized = FALSE;
}
CABCList::~CABCList() {
/************************************** : by VK at 25.12.2004 12:50:03 **\
  POSITION pos = m_Items.GetStartPosition();
  while( pos ) {
    long lID;
    ABCItemData* pData;
    m_Items.GetNextAssoc(pos, lID, pData);
    if ( pData )
      delete pData;
  }
\************************************** : by VK at 25.12.2004 12:50:06 **/
}
BOOL CABCList::PreCreateWindow(CREATESTRUCT& cs) {
  cs.style |= LVS_REPORT|LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

int CABCList::UpdateData(long ID) {
  CListCtrl& list = GetListCtrl();

  ABCItemData* pItemData = NULL;
  if ( FALSE==m_Items.Lookup(ID, pItemData) )
    return -1;

  if ( pItemData->m_fDeleted )
    return -1;

  LVFINDINFO fi;
  memset(&fi, 0, sizeof(fi));
  fi.flags = LVFI_PARAM;
  fi.lParam = (LPARAM)pItemData;
  int nItem = list.FindItem(&fi);
  if ( nItem != -1 ) {
    FillRow(nItem);
    list.RedrawItems(nItem, nItem);
    list.EnsureVisible(nItem, TRUE);
  }
  return nItem;
}
void CABCList::GoTo(long ID) {
  int nItem = UpdateData(ID);
  if ( nItem != -1 ) {
    if ( m_FocusedItem != -1 )
      GetListCtrl().SetItemState(m_FocusedItem, 0, LVIS_FOCUSED|LVIS_SELECTED);
    GetListCtrl().SetItemState(nItem, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
  }
}
CFormABC* CABCList::GetABCForm() {
  CEraABCView* pView = (CEraABCView*)GetParent();
  if ( pView )
    return pView->GetForm();
  return NULL;
}
void CABCList::Fill() {
  CWaitCursor wc;
  CListCtrl& list = GetListCtrl();
  list.DeleteAllItems();

  CFormABC* pForm = GetABCForm();
  if ( NULL==pForm )
    return;
  CDaoRecordset* pSet = pForm->m_pSet;
  if ( NULL==pSet )
    return;
  if ( !pSet->IsOpen() )
    return;
  if ( pSet->IsBOF() && pSet->IsEOF() )
    return;

  m_SortColumn = -1;
  m_FocusedItem = -1;
  m_FocusedID = -1;

  int nItem = -1;
  long lastID = -1;
  COleVariant bm;
  try {
    list.DeleteAllItems();
    MoveFirst(pSet);
    while ( !pSet->IsEOF() ) {
      if ( !pSet->IsDeleted() ) {
        nItem++;
        nItem = list.InsertItem(nItem, "");
        FillRow(nItem);
        COleVariant varID = pSet->GetFieldValue(0);
        lastID = varID.lVal;
        bm = pSet->GetBookmark();
      }
      pSet->MoveNext();
    }
    pSet->MoveLast();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }


  if ( nItem >= 0 ) {
    //list.SetFocus();
    pSet->SetBookmark(bm);
    list.EnsureVisible(nItem, FALSE);
    list.SetItemState(nItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
    if ( lastID != -1 ) {
      pForm->GoTo(lastID, FALSE);
    }
  }
}
void CABCList::ClearSelection() {
	CListCtrl& list = GetListCtrl();
  POSITION pos = list.GetFirstSelectedItemPosition();
  CDWordArray aSelItems;
  while( pos ) {
    int nItem = list.GetNextSelectedItem(pos);
    aSelItems.Add( (DWORD)nItem);
  }
  int nSellRows = aSelItems.GetSize();  
  for( int i = nSellRows-1; i >=0 ; i-- ) {
    int nItem = (int)aSelItems.GetAt(i);
    list.SetItemState(nItem, 0, LVIS_SELECTED|LVIS_FOCUSED);
  }
}
/////////////////////////////////////////////////////////////////////////////
// CABCList drawing
void CABCList::OnDraw(CDC* pDC) {
/************************************** : by VK at 21.12.2004 2:03:43 **\
	CEraABCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
\************************************** : by VK at 21.12.2004 2:03:46 **/
}

void CABCList::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  if ( pNMListView->iItem >= 0 && (pNMListView->uNewState & LVIS_FOCUSED) ) {
    m_FocusedItem = pNMListView->iItem;
    ABCItemData* pItemData = (ABCItemData*)GetListCtrl().GetItemData(m_FocusedItem);
    CFormABC* pForm = GetABCForm();
    if ( pForm && m_FocusedID != pItemData->m_ID && FALSE==pItemData->m_fDeleted ) {
      CListCtrl& list = GetListCtrl();
      int nTopIndex = GetListCtrl().GetTopIndex();
      m_FocusedID = pItemData->m_ID;
      pForm->GoTo(m_FocusedID);
      list.EnsureVisible(nTopIndex, TRUE);
      list.EnsureVisible(pNMListView->iItem, FALSE);
    }
  }
	*pResult = 0;
}

void CABCList::OnUpdateRecordFirst(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
  BOOL fEnable = TRUE;
  CListCtrl& list = GetListCtrl();
  if ( list.GetItemCount() <=0 ) {
    fEnable  = FALSE;
  }
  else {
    if ( list.GetItemState(0, LVIS_FOCUSED)==LVIS_FOCUSED )
      fEnable  = FALSE;
  }
  pCmdUI->Enable(fEnable);
}

void CABCList::OnRecordFirst() {
	CListCtrl& list = GetListCtrl();
  if ( list.GetItemCount() > 0 ) {
    int oldItem = m_FocusedItem;
    if ( oldItem != -1 )
      list.SetItemState(oldItem, 0, LVIS_FOCUSED|LVIS_SELECTED);
    list.SetItemState(0, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
    list.EnsureVisible(0, FALSE);
    list.RedrawItems(oldItem, oldItem);
    list.RedrawItems(0, 0);
  }
}

BOOL CABCList::CanGoToPrev() {
  BOOL fEnable = TRUE;
  CListCtrl& list = GetListCtrl();
  if ( list.GetItemCount() <=0 ) {
    fEnable  = FALSE;
  }
  else {
    if ( list.GetItemState(0, LVIS_FOCUSED)==LVIS_FOCUSED )
      fEnable  = FALSE;
  }
  return fEnable;
}
void CABCList::OnUpdateRecordPrev(CCmdUI* pCmdUI) {
  pCmdUI->Enable(CanGoToPrev());
}

void CABCList::OnRecordPrev() {
	CListCtrl& list = GetListCtrl();
  if ( list.GetItemCount() > 0 && m_FocusedItem > 0) {
    int oldItem = m_FocusedItem;
    int newItem = m_FocusedItem-1;
    if ( oldItem != -1 )
      list.SetItemState(oldItem, 0, LVIS_FOCUSED|LVIS_SELECTED);
    list.SetItemState(newItem, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
    list.EnsureVisible(newItem, FALSE);
    list.RedrawItems(oldItem, oldItem);
    list.RedrawItems(newItem, 0);
  }
}

BOOL CABCList::CanGoToNext() {
  BOOL fEnable = TRUE;
  CListCtrl& list = GetListCtrl();
  int nCount = list.GetItemCount();
  if ( nCount <= 0 || m_FocusedItem==nCount-1) {
    fEnable  = FALSE;
  }
  else {
    if ( list.GetItemState(nCount-1, LVIS_FOCUSED)==LVIS_FOCUSED)
      fEnable  = FALSE;
  }
  return fEnable;
}
void CABCList::OnUpdateRecordNext(CCmdUI* pCmdUI) {
  pCmdUI->Enable(CanGoToNext());
}

void CABCList::OnRecordNext() {
	CListCtrl& list = GetListCtrl();
  int nCount = list.GetItemCount();
  if ( nCount > 0 && m_FocusedItem < nCount-1) {
    int oldItem = m_FocusedItem;
    int newItem = m_FocusedItem+1;
    if ( oldItem != -1 )
      list.SetItemState(oldItem, 0, LVIS_FOCUSED|LVIS_SELECTED);
    list.SetItemState(newItem, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
    list.EnsureVisible(newItem, FALSE);
    list.RedrawItems(oldItem, oldItem);
    list.RedrawItems(newItem, 0);
  }
}

void CABCList::OnUpdateRecordLast(CCmdUI* pCmdUI) {
  BOOL fEnable = TRUE;
  CListCtrl& list = GetListCtrl();
  int nCount = list.GetItemCount();
  if ( nCount <= 0 ) {
    fEnable  = FALSE;
  }
  else {
    if ( list.GetItemState(nCount-1, LVIS_FOCUSED)==LVIS_FOCUSED )
      fEnable  = FALSE;
  }
  pCmdUI->Enable(fEnable);
}

void CABCList::OnRecordLast() {
	CListCtrl& list = GetListCtrl();
  int nCount = list.GetItemCount();
  if ( nCount > 0 && m_FocusedItem < nCount-1) {
    int oldItem = m_FocusedItem;
    int newItem = nCount-1;
    if ( oldItem != -1 )
      list.SetItemState(oldItem, 0, LVIS_FOCUSED|LVIS_SELECTED);
    list.SetItemState(newItem, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
    list.EnsureVisible(newItem, FALSE);
    list.RedrawItems(oldItem, oldItem);
    list.RedrawItems(newItem, 0);
  }
}

void CABCList::OnUpdateRecordNew(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CABCList::OnRecordNew() {
  CFormABC* pForm = GetABCForm();
  long lID = pForm->RecordNew();
  if ( lID >-1 ) {
    CListCtrl& list = GetListCtrl();
    int nItem = list.GetItemCount();
    nItem = list.InsertItem(nItem, "");
    ClearSelection();
    FillRow(nItem);
    list.SetItemState(nItem, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
    list.EnsureVisible(nItem, FALSE);
    list.RedrawItems(nItem, nItem);
    pForm->SetFocusToFirstControl();
  }
}
void CABCList::OnUpdateRecordDelete(CCmdUI* pCmdUI) {
	pCmdUI->Enable(m_FocusedItem != -1);
}

void CABCList::OnRecordDelete() {
	CListCtrl& list = GetListCtrl();
  POSITION pos = list.GetFirstSelectedItemPosition();
  CDWordArray aSelItems; // Массив помеченных записей
  while( pos ) {
    int nItem = list.GetNextSelectedItem(pos);
    aSelItems.Add( (DWORD)nItem);
  }
  int nSellRows = aSelItems.GetSize();
  if ( nSellRows ) {
    CString s;
    CString sHowMutch;
    if ( 5 < nSellRows && nSellRows < 21 ) { // Так получается...
      sHowMutch = _T("записів");
    }
    else {
      switch( nSellRows % 10 ) { // Пытаемся правильно склонять числительные на ридній мові
        case 1:                   sHowMutch = _T("запис");   break;
        case 2: case 3: case 4:   sHowMutch = _T("записи");  break;
        default:                  sHowMutch = _T("записів"); break;
      }
    }
    s.Format( _T("Ви дійсно бажаєте видалити %d %s?"), nSellRows, sHowMutch);
    if ( YNDlg(this, _T("Видалені записи не можна відновити."), s)) {
      CFormABC* pForm = GetABCForm();
      CDaoRecordset* pSet = pForm->m_pSet;
      pForm->SaveData(); // На всякий случай сохраняем текущую запись.

      int nFirstSelected = (int)aSelItems.GetAt(0);
      for( int i = nSellRows-1; i >=0 ; i-- ) {
        int nItem = (int)aSelItems.GetAt(i);
        ABCItemData* pItemData = (ABCItemData*)list.GetItemData(nItem);
        pItemData->m_fDeleted = true;
        try {
          if ( pSet->Seek("=", &COleVariant(pItemData->m_ID), 1) ) {
            if ( !pSet->IsDeleted() ) {
              pSet->Delete();
            }
          }
        }
        catch(CDaoException* e) {
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
        }
        list.DeleteItem( nItem );
      }
      int nCount = list.GetItemCount();
      int nCurItem = nFirstSelected;
      if ( nCurItem==nCount )
        nCurItem--;
      if ( nCount>0 && nCurItem >=0 && nCurItem < nCount ) {
        ABCItemData* pItemData = (ABCItemData*)list.GetItemData(nCurItem);
        list.SetItemState(nCurItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
        list.EnsureVisible(nCurItem, FALSE);
        pForm->GoTo(pItemData->m_ID, FALSE);
      }
      else {
        m_FocusedItem = -1;
      }
    }
  }
  CFormABC* pForm = GetABCForm();
  if ( pForm ) {
    pForm->EnableControls(list.GetItemCount() > 0);
  }
}

void CABCList::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) {
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
  if ( VK_DELETE==pLVKeyDown->wVKey ) {
    OnRecordDelete();
  }
	*pResult = 0;
}

int CABCList::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CABCListBase::OnCreate(lpCreateStruct) == -1)
    return -1;

  CHeaderCtrl* pHeaderCtrl = GetListCtrl().GetHeaderCtrl();
  if ( pHeaderCtrl ) {
    HWND hWnd = pHeaderCtrl->Detach();
    m_wndHeader.SubclassWindow(hWnd);
  }

  // TODO: Add your specialized creation code here
  return 0;
}
void CABCList::OnInitialUpdate() {
  CListCtrl& list = GetListCtrl();
  ListView_SetExtendedListViewStyle(list.m_hWnd, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE|LVS_EX_HEADERDRAGDROP);
  CABCListBase::OnInitialUpdate();
}
void CABCList::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  CListCtrl& list = GetListCtrl();
  m_SortColumn = pNMListView->iSubItem;
  switch( m_SortOrder[m_SortColumn] ) {
    case SO_NONE:  m_SortOrder[m_SortColumn] = SO_ASC;  break;
    case SO_ASC:   m_SortOrder[m_SortColumn] = SO_DESC; break;
    case SO_DESC:  m_SortOrder[m_SortColumn] = SO_ASC;  break;
  }
  if ( IsKindOf(RUNTIME_CLASS(CBirthList)) ) {
    list.SortItems(CompareABCProcBirth, (DWORD)this);	
  }
  else if ( IsKindOf(RUNTIME_CLASS(CMarriageList)) ) {
    list.SortItems(CompareABCProcMarriage, (DWORD)this);	
  }
  else if ( IsKindOf(RUNTIME_CLASS(CDivorceList)) ) {
    list.SortItems(CompareABCProcDivorce, (DWORD)this);	
  }
  else if ( IsKindOf(RUNTIME_CLASS(CChangeList)) ) {
    list.SortItems(CompareABCProcChange, (DWORD)this);	
  }
  else if ( IsKindOf(RUNTIME_CLASS(CDeathList)) ) {
    list.SortItems(CompareABCProcDeath, (DWORD)this);	
  }
/************************************** : by VK at 10.02.2005 0:41:24 **\
  CABCListBase::OnColumnclick(pNMHDR, pResult);
\************************************** : by VK at 10.02.2005 0:41:27 **/
  m_wndHeader.SetSortColumn(m_SortColumn, m_SortOrder[m_SortColumn]==SO_ASC);
  if ( list.GetItemCount() )
    list.EnsureVisible(0, TRUE);
/************************************** : by VK at 08.01.2005 9:03:51 **\
  //EnableSortIcon(TRUE, m_SortColumn+1);
  CHeaderCtrl* pHdr = list.GetHeaderCtrl();
  int nCount = pHdr->GetItemCount();
  for( int i(0); i < nCount; i++ ) {
    HDITEM hdrItem;
    hdrItem.mask = HDI_FORMAT;
    pHdr->SetItem(m_SortColumn, 
  }
\************************************** : by VK at 08.01.2005 9:03:55 **/
	*pResult = 0;
}
void CABCList::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  ABCItemData* pItemData = (ABCItemData*)GetListCtrl().GetItemData(pNMListView->iItem);
  if ( pItemData ) {
    m_Items.RemoveKey(pItemData->m_ID);
    delete pItemData;
  }
	*pResult = 0;
}
void CABCList::OnSetFocus(CWnd* pOldWnd) {
  CEraABCView* pView = static_cast<CEraABCView*>(GetParent());
  if ( pView ) {
    CFormABC* pForm = pView->GetForm();
    if ( pForm )
      pForm->m_tooltip.HideTooltip();
  }
  CABCListBase::OnSetFocus(pOldWnd);
}
/////////////////////////////////////////////////////////////////////////////
// CABCList diagnostics
#ifdef _DEBUG
void CABCList::AssertValid() const {
	CListView::AssertValid();
}
void CABCList::Dump(CDumpContext& dc) const {
	CListView::Dump(dc);
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CABCList message handlers
int CABCList::GetItemCount() {
  return GetListCtrl().GetItemCount();
}

/////////////////////////////////////////////////////////////////////////////
// CBirthList
IMPLEMENT_DYNCREATE(CBirthList, CABCList)
BEGIN_MESSAGE_MAP(CBirthList, CABCList)
	//{{AFX_MSG_MAP(CBirthList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
void CBirthList::FillRow(int nItem) {
  CFormABC* pForm = GetABCForm();
  if ( NULL==pForm )
    return;
  CRSBirthes* pSet = (CRSBirthes*)pForm->m_pSet;
  if ( NULL==pSet )
    return;

  if ( pSet->IsBOF() && pSet->IsEOF() )
    return;
  CListCtrl& list = GetListCtrl();
  CString s;
  if ( !pSet->IsFieldNull(&pSet->m_NUMBER) )
    s.Format(_T("%d"), pSet->m_NUMBER);

  list.SetItem(nItem, BC_SEX, LVIF_IMAGE, NULL, pSet->m_SEX, 0, 0, 0);
  list.SetItemText(nItem, BC_NUMBER, s);
  list.SetItemText(nItem, BC_DATEREG, GetDateDDMMYYYY(pSet->m_DATEREG));
  list.SetItemText(nItem, BC_SURNAME, pSet->m_SURNAME);
  list.SetItemText(nItem, BC_NAME,    pSet->m_NAME);
  list.SetItemText(nItem, BC_PATRONYMIC,    pSet->m_PATRONYMIC);

  ABCItemDataBirth* pItemData = NULL;
  if ( m_Items.Lookup(pSet->m_ID, (ABCItemData*&)pItemData) ) {
    pItemData->Reset(pSet->m_ID, pSet->m_NUMBER, pSet->m_DATEREG, pSet->m_SEX, pSet->m_SURNAME, pSet->m_NAME, pSet->m_PATRONYMIC);
  }
  else {
    pItemData = new ABCItemDataBirth(pSet->m_ID, pSet->m_NUMBER, pSet->m_DATEREG, pSet->m_SEX, pSet->m_SURNAME, pSet->m_NAME, pSet->m_PATRONYMIC);
    m_Items.SetAt(pSet->m_ID, (ABCItemData*&)pItemData);
  }
  list.SetItemData(nItem, (DWORD)pItemData);
}
void CBirthList::OnInitialUpdate() {
	CABCList::OnInitialUpdate();
  if ( FALSE==m_fInitialized ) {
    m_fInitialized = TRUE;
    m_SortOrder.SetSize(BC_TOTAL);
    CListCtrl& list = GetListCtrl();

    m_SexImageList.Create(IDIL_ABCSEX, 16, 0, RGB(0xFF, 0, 0xFF));
    list.SetImageList(&m_SexImageList, LVSIL_SMALL);

    list.InsertColumn(BC_SEX,         _T("Стать"),        LVCFMT_LEFT, 68);
    list.InsertColumn(BC_NUMBER,      _T("№"),            LVCFMT_LEFT, 40);
    list.InsertColumn(BC_DATEREG,     _T(" Дата "),       LVCFMT_LEFT, 80);
    list.InsertColumn(BC_SURNAME,     _T("Прізвище"),     LVCFMT_LEFT, 92);
    list.InsertColumn(BC_NAME,        _T("Ім'я"),         LVCFMT_LEFT, 92);
    list.InsertColumn(BC_PATRONYMIC,  _T("По батькові"),  LVCFMT_LEFT, 92);

/************************************** : by VK at 10.02.2005 0:41:38 **\
    EnableSortIcon();
    ColorSortColumn();
    KeepLabelLeft();
\************************************** : by VK at 10.02.2005 0:41:41 **/
  }
}

/////////////////////////////////////////////////////////////////////////////
// CMarriageList
IMPLEMENT_DYNCREATE(CMarriageList, CABCList)
BEGIN_MESSAGE_MAP(CMarriageList, CABCList)
	//{{AFX_MSG_MAP(CMarriageList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
void CMarriageList::FillRow(int nItem) {
  CFormABC* pForm = GetABCForm();
  if ( NULL==pForm )
    return;
  CRSMarriages* pSet = (CRSMarriages*)pForm->m_pSet;
  if ( NULL==pSet )
    return;
  if ( pSet->IsBOF() && pSet->IsEOF() )
    return;

  CString s;
  CListCtrl& list = GetListCtrl();
  if ( !pSet->IsFieldNull(&pSet->m_NUMBER) )
    s.Format(_T("%d"), pSet->m_NUMBER);
  list.SetItemText(nItem, MC_NUMBER, s);
  list.SetItemText(nItem, MC_DATEREG,      GetDateDDMMYYYY(pSet->m_DATEREG));
  list.SetItemText(nItem, MC_MOLD_SURNAME, pSet->m_MOLD_SURNAME);
  list.SetItemText(nItem, MC_MNEW_SURNAME, pSet->m_MNEW_SURNAME);
  list.SetItemText(nItem, MC_MNAME,        pSet->m_MNAME);
  list.SetItemText(nItem, MC_MPATRONYMIC,  pSet->m_MPATRONYMIC);
  list.SetItemText(nItem, MC_WOLD_SURNAME, pSet->m_WOLD_SURNAME);
  list.SetItemText(nItem, MC_WNEW_SURNAME, pSet->m_WNEW_SURNAME);
  list.SetItemText(nItem, MC_WNAME,        pSet->m_WNAME);
  list.SetItemText(nItem, MC_WPATRONYMIC,  pSet->m_WPATRONYMIC);

  ABCItemDataMarriage* pItemData = NULL;
  if ( m_Items.Lookup(pSet->m_ID, (ABCItemData*&)pItemData) ) {
    pItemData->Reset(pSet->m_ID, pSet->m_NUMBER, pSet->m_DATEREG,
                     pSet->m_MOLD_SURNAME, pSet->m_MNEW_SURNAME, pSet->m_MNAME, pSet->m_MPATRONYMIC,
                     pSet->m_WOLD_SURNAME, pSet->m_WNEW_SURNAME, pSet->m_WNAME, pSet->m_WPATRONYMIC
                    );
  }
  else {
    pItemData = new ABCItemDataMarriage(pSet->m_ID, pSet->m_NUMBER, pSet->m_DATEREG,
                                        pSet->m_MOLD_SURNAME, pSet->m_MNEW_SURNAME, pSet->m_MNAME, pSet->m_MPATRONYMIC,
                                        pSet->m_WOLD_SURNAME, pSet->m_WNEW_SURNAME, pSet->m_WNAME, pSet->m_WPATRONYMIC
                                        );
    m_Items.SetAt(pSet->m_ID, (ABCItemData*&)pItemData);
  }
  list.SetItemData(nItem, (DWORD)pItemData);
  
}
void CMarriageList::OnInitialUpdate() {
	CABCList::OnInitialUpdate();
  if ( FALSE==m_fInitialized ) {
    m_fInitialized = TRUE;
    m_SortOrder.SetSize(MC_TOTAL);
    CListCtrl& list = GetListCtrl();
    list.InsertColumn(MC_NUMBER,       _T("№"),             LVCFMT_LEFT, 40);
    list.InsertColumn(MC_DATEREG,      _T(" Дата "),        LVCFMT_LEFT, 72);
    list.InsertColumn(MC_MOLD_SURNAME, _T("Прізвище C"),    LVCFMT_LEFT, 96);
    list.InsertColumn(MC_MNEW_SURNAME, _T("Прізвище Н"),    LVCFMT_LEFT, 96);
    list.InsertColumn(MC_MNAME,        _T("Ім'я"),          LVCFMT_LEFT, 80);
    list.InsertColumn(MC_MPATRONYMIC,  _T("По батькові"),   LVCFMT_LEFT, 96);
    list.InsertColumn(MC_WOLD_SURNAME, _T("Прізвище С"),    LVCFMT_LEFT, 96);
    list.InsertColumn(MC_WNEW_SURNAME, _T("Прізвище Н"),    LVCFMT_LEFT, 96);
    list.InsertColumn(MC_WNAME,        _T("Ім'я"),          LVCFMT_LEFT, 80);
    list.InsertColumn(MC_WPATRONYMIC,  _T("По батькові"),   LVCFMT_LEFT, 96);

    HDITEM hdItem;
    hdItem.mask = HDI_LPARAM;
    hdItem.lParam = 0;

    m_wndHeader.SetItem(MC_NUMBER,       &hdItem);
    m_wndHeader.SetItem(MC_DATEREG,      &hdItem);

    hdItem.lParam = (LPARAM)g_clrMaleForeColor;
    m_wndHeader.SetItem(MC_MOLD_SURNAME, &hdItem);
    m_wndHeader.SetItem(MC_MNEW_SURNAME, &hdItem);
    m_wndHeader.SetItem(MC_MNAME,        &hdItem);
    m_wndHeader.SetItem(MC_MPATRONYMIC,  &hdItem);

    hdItem.lParam = (LPARAM)g_clrFemaleForeColor;
    m_wndHeader.SetItem(MC_WOLD_SURNAME, &hdItem);
    m_wndHeader.SetItem(MC_WNEW_SURNAME, &hdItem);
    m_wndHeader.SetItem(MC_WNAME,        &hdItem);
    m_wndHeader.SetItem(MC_WPATRONYMIC,  &hdItem);

/************************************** : by VK at 10.02.2005 0:41:56 **\
    EnableSortIcon();
    ColorSortColumn();
    KeepLabelLeft();
\************************************** : by VK at 10.02.2005 0:41:59 **/
  }

/************************************** : by VK at 08.01.2005 9:09:47 **\
  CHeaderCtrl* pHeaderCtrl = list.GetHeaderCtrl();

  HD_ITEM hdItem;
  pHeaderCtrl->GetItem(MC_MOLD_SURNAME, &hdItem);
  hdItem.mask = HDI_IMAGE | HDI_FORMAT;
  hdItem.fmt = HDF_LEFT | HDF_IMAGE | HDF_STRING;
  hdItem.iImage = IMI_MAN;        pHeaderCtrl->SetItem(MC_MOLD_SURNAME, &hdItem);
  hdItem.iImage = IMI_MMARRIAGE;  pHeaderCtrl->SetItem(MC_MNEW_SURNAME, &hdItem);
  hdItem.iImage = IMI_MAN;        pHeaderCtrl->SetItem(MC_MNAME,        &hdItem);
  hdItem.iImage = IMI_MAN;        pHeaderCtrl->SetItem(MC_MPATRONYMIC,  &hdItem);

  hdItem.iImage = IMI_WOMAN;      pHeaderCtrl->SetItem(MC_WOLD_SURNAME, &hdItem);
  hdItem.iImage = IMI_WMARRIAGE;  pHeaderCtrl->SetItem(MC_WNEW_SURNAME, &hdItem);
  hdItem.iImage = IMI_WOMAN;      pHeaderCtrl->SetItem(MC_WNAME,        &hdItem);
  hdItem.iImage = IMI_WOMAN;      pHeaderCtrl->SetItem(MC_WPATRONYMIC,  &hdItem);
\************************************** : by VK at 08.01.2005 9:09:51 **/
}

/////////////////////////////////////////////////////////////////////////////
// CDivorceList
IMPLEMENT_DYNCREATE(CDivorceList, CABCList)
BEGIN_MESSAGE_MAP(CDivorceList, CABCList)
	//{{AFX_MSG_MAP(CDivorceList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
void CDivorceList::FillRow(int nItem) {
  CFormABC* pForm = GetABCForm();
  if ( NULL==pForm )
    return;

  CRSDivorces* pSet = (CRSDivorces*)pForm->m_pSet;
  if ( NULL==pSet )
    return;
  if ( pSet->IsBOF() && pSet->IsEOF() )
    return;
  CString s;
  CListCtrl& list = GetListCtrl();
  if ( !pSet->IsFieldNull(&pSet->m_NUMBER) )
    s.Format(_T("%d"), pSet->m_NUMBER);
  list.SetItemText(nItem, DIVC_NUMBER, s);
  list.SetItemText(nItem, DIVC_DATEREG,      GetDateDDMMYYYY(pSet->m_DATEREG));
  list.SetItemText(nItem, DIVC_MOLD_SURNAME, pSet->m_MOLD_SURNAME);
  list.SetItemText(nItem, DIVC_MNEW_SURNAME, pSet->m_MNEW_SURNAME);
  list.SetItemText(nItem, DIVC_MNAME,        pSet->m_MNAME);
  list.SetItemText(nItem, DIVC_MPATRONYMIC,  pSet->m_MPATRONYMIC);
  list.SetItemText(nItem, DIVC_WOLD_SURNAME, pSet->m_WOLD_SURNAME);
  list.SetItemText(nItem, DIVC_WNEW_SURNAME, pSet->m_WNEW_SURNAME);
  list.SetItemText(nItem, DIVC_WNAME,        pSet->m_WNAME);
  list.SetItemText(nItem, DIVC_WPATRONYMIC,  pSet->m_WPATRONYMIC);

  ABCItemDataDivorce* pItemData = NULL;
  if ( m_Items.Lookup(pSet->m_ID, (ABCItemData*&)pItemData) ) {
    pItemData->Reset(pSet->m_ID, pSet->m_NUMBER, pSet->m_DATEREG,
                     pSet->m_MOLD_SURNAME, pSet->m_MNEW_SURNAME, pSet->m_MNAME, pSet->m_MPATRONYMIC,
                     pSet->m_WOLD_SURNAME, pSet->m_WNEW_SURNAME, pSet->m_WNAME, pSet->m_WPATRONYMIC
                    );
  }
  else {
    pItemData = new ABCItemDataDivorce(pSet->m_ID, pSet->m_NUMBER, pSet->m_DATEREG,
                                       pSet->m_MOLD_SURNAME, pSet->m_MNEW_SURNAME, pSet->m_MNAME, pSet->m_MPATRONYMIC,
                                       pSet->m_WOLD_SURNAME, pSet->m_WNEW_SURNAME, pSet->m_WNAME, pSet->m_WPATRONYMIC
                                      );
    m_Items.SetAt(pSet->m_ID, (ABCItemData*&)pItemData);
  }
  list.SetItemData(nItem, (DWORD)pItemData);
}
void CDivorceList::OnInitialUpdate() {
	CABCList::OnInitialUpdate();
  if ( FALSE==m_fInitialized ) {
    m_fInitialized = TRUE;
    m_SortOrder.SetSize(DIVC_TOTAL);
    CListCtrl& list = GetListCtrl();
    list.InsertColumn(DIVC_NUMBER,       _T("№"),           LVCFMT_LEFT, 40);
    list.InsertColumn(DIVC_DATEREG,      _T(" Дата "),      LVCFMT_LEFT, 72);
    list.InsertColumn(DIVC_MOLD_SURNAME, _T("Прізвище С"),  LVCFMT_LEFT, 96);
    list.InsertColumn(DIVC_MNEW_SURNAME, _T("Прізвище Н"),  LVCFMT_LEFT, 96);
    list.InsertColumn(DIVC_MNAME,        _T("Ім'я"),        LVCFMT_LEFT, 80);
    list.InsertColumn(DIVC_MPATRONYMIC,  _T("По батькові"), LVCFMT_LEFT, 96);
    list.InsertColumn(DIVC_WOLD_SURNAME, _T("Прізвище С"),  LVCFMT_LEFT, 96);
    list.InsertColumn(DIVC_WNEW_SURNAME, _T("Прізвище Н"),  LVCFMT_LEFT, 96);
    list.InsertColumn(DIVC_WNAME,        _T("Ім'я"),        LVCFMT_LEFT, 80);
    list.InsertColumn(DIVC_WPATRONYMIC,  _T("По батькові"), LVCFMT_LEFT, 96);

    HDITEM hdItem;
    hdItem.mask = HDI_LPARAM;
    hdItem.lParam = 0;

    m_wndHeader.SetItem(DIVC_NUMBER,     &hdItem);
    m_wndHeader.SetItem(DIVC_DATEREG,    &hdItem);

    hdItem.lParam = (LPARAM)g_clrMaleForeColor;
    m_wndHeader.SetItem(DIVC_MOLD_SURNAME, &hdItem);
    m_wndHeader.SetItem(DIVC_MNEW_SURNAME, &hdItem);
    m_wndHeader.SetItem(DIVC_MNAME,        &hdItem);
    m_wndHeader.SetItem(DIVC_MPATRONYMIC,  &hdItem);

    hdItem.lParam = (LPARAM)g_clrFemaleForeColor;
    m_wndHeader.SetItem(DIVC_WOLD_SURNAME, &hdItem);
    m_wndHeader.SetItem(DIVC_WNEW_SURNAME, &hdItem);
    m_wndHeader.SetItem(DIVC_WNAME,        &hdItem);
    m_wndHeader.SetItem(DIVC_WPATRONYMIC,  &hdItem);

/************************************** : by VK at 08.01.2005 9:10:10 **\
  CHeaderCtrl* pHeaderCtrl = list.GetHeaderCtrl();

  HD_ITEM hdItem;
  pHeaderCtrl->GetItem(DIVC_MOLD_SURNAME, &hdItem);
  hdItem.mask = HDI_IMAGE | HDI_FORMAT;
  hdItem.fmt = HDF_LEFT | HDF_IMAGE | HDF_STRING;
  hdItem.iImage = IMI_MAN;        pHeaderCtrl->SetItem(DIVC_MOLD_SURNAME, &hdItem);
  hdItem.iImage = IMI_MMARRIAGE;  pHeaderCtrl->SetItem(DIVC_MNEW_SURNAME, &hdItem);
  hdItem.iImage = IMI_MAN;        pHeaderCtrl->SetItem(DIVC_MNAME,        &hdItem);
  hdItem.iImage = IMI_MAN;        pHeaderCtrl->SetItem(DIVC_MPATRONYMIC,  &hdItem);

  hdItem.iImage = IMI_WOMAN;      pHeaderCtrl->SetItem(DIVC_WOLD_SURNAME, &hdItem);
  hdItem.iImage = IMI_WMARRIAGE;  pHeaderCtrl->SetItem(DIVC_WNEW_SURNAME, &hdItem);
  hdItem.iImage = IMI_WOMAN;      pHeaderCtrl->SetItem(DIVC_WNAME,        &hdItem);
  hdItem.iImage = IMI_WOMAN;      pHeaderCtrl->SetItem(DIVC_WPATRONYMIC,  &hdItem);
\************************************** : by VK at 08.01.2005 9:10:14 **/

/************************************** : by VK at 10.02.2005 0:42:06 **\
    EnableSortIcon();
    ColorSortColumn();
    KeepLabelLeft();
\************************************** : by VK at 10.02.2005 0:42:09 **/
  }
}

/////////////////////////////////////////////////////////////////////////////
// CChangeList
IMPLEMENT_DYNCREATE(CChangeList, CABCList)
BEGIN_MESSAGE_MAP(CChangeList, CABCList)
	//{{AFX_MSG_MAP(CChangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
void CChangeList::FillRow(int nItem) {
  CFormABC* pForm = GetABCForm();
  if ( NULL==pForm )
    return;
  CRSChanges* pSet = (CRSChanges*)pForm->m_pSet;
  if ( NULL==pSet )
    return;
  if ( pSet->IsBOF() && pSet->IsEOF() )
    return;
  CString s;
  CListCtrl& list = GetListCtrl();
  if ( !pSet->IsFieldNull(&pSet->m_NUMBER) )
    s.Format(_T("%d"), pSet->m_NUMBER);

  list.SetItem(nItem, CC_SEX, LVIF_IMAGE, NULL, pSet->m_SEX, 0, 0, 0);
  list.SetItemText(nItem, CC_NUMBER, s);
  list.SetItemText(nItem, CC_DATEREG,      GetDateDDMMYYYY(pSet->m_DATEREG));
  list.SetItemText(nItem, CC_OLDSURNAME,   pSet->m_OLDSURNAME);
  list.SetItemText(nItem, CC_NEWSURNAME,   pSet->m_NEWSURNAME);
  list.SetItemText(nItem, CC_OLDNAME,      pSet->m_OLDNAME);
  list.SetItemText(nItem, CC_NEWNAME,      pSet->m_NEWNAME);
  list.SetItemText(nItem, CC_OLDPATRONYMIC,  pSet->m_OLDPATRONYMIC);
  list.SetItemText(nItem, CC_NEWPATRONYMIC,  pSet->m_NEWPATRONYMIC);

  ABCItemDataChange* pItemData = NULL;
  if ( m_Items.Lookup(pSet->m_ID, (ABCItemData*&)pItemData) ) {
    pItemData->Reset(pSet->m_ID, pSet->m_NUMBER, pSet->m_DATEREG, pSet->m_SEX,
                     pSet->m_OLDSURNAME, pSet->m_NEWSURNAME,
                     pSet->m_OLDNAME, pSet->m_NEWNAME,
                     pSet->m_OLDPATRONYMIC, pSet->m_OLDPATRONYMIC
                    );

  }
  else {
    pItemData = new ABCItemDataChange(pSet->m_ID, pSet->m_NUMBER, pSet->m_DATEREG, pSet->m_SEX,
                                      pSet->m_OLDSURNAME, pSet->m_NEWSURNAME,
                                      pSet->m_OLDNAME, pSet->m_NEWNAME,
                                      pSet->m_OLDPATRONYMIC, pSet->m_OLDPATRONYMIC
                                     );
    m_Items.SetAt(pSet->m_ID, (ABCItemData*&)pItemData);
  }
  list.SetItemData(nItem, (DWORD)pItemData);
}
void CChangeList::OnInitialUpdate() {
	CABCList::OnInitialUpdate();
  if ( FALSE==m_fInitialized ) {
    m_fInitialized = TRUE;
    m_SortOrder.SetSize(CC_TOTAL);
    CListCtrl& list = GetListCtrl();

    m_SexImageList.Create(IDIL_ABCSEX, 16, 0, RGB(0xFF, 0, 0xFF));
    list.SetImageList(&m_SexImageList, LVSIL_SMALL);

    list.InsertColumn(CC_SEX,           _T("Стать"),              LVCFMT_LEFT, 68);
    list.InsertColumn(CC_NUMBER,        _T("№"),                  LVCFMT_LEFT, 40);
    list.InsertColumn(CC_DATEREG,       _T(" Дата "),             LVCFMT_LEFT, 80);
    list.InsertColumn(CC_OLDSURNAME,    _T("Старе Пр-ще"),        LVCFMT_LEFT, 92);
    list.InsertColumn(CC_NEWSURNAME,    _T("Нове Пр-ще"),         LVCFMT_LEFT, 92);
    list.InsertColumn(CC_OLDNAME,       _T("Старе Ім'я"),         LVCFMT_LEFT, 92);
    list.InsertColumn(CC_NEWNAME,       _T("Нове Ім'я"),          LVCFMT_LEFT, 92);
    list.InsertColumn(CC_OLDPATRONYMIC, _T("Старе По батькові"),  LVCFMT_LEFT, 92);
    list.InsertColumn(CC_NEWPATRONYMIC, _T("Нове По батькові"),   LVCFMT_LEFT, 92);

/************************************** : by VK at 10.02.2005 0:42:12 **\
    EnableSortIcon();
    ColorSortColumn();
    KeepLabelLeft();
\************************************** : by VK at 10.02.2005 0:42:14 **/
  }

}

/////////////////////////////////////////////////////////////////////////////
// CDeathList
IMPLEMENT_DYNCREATE(CDeathList, CABCList)
BEGIN_MESSAGE_MAP(CDeathList, CABCList)
	//{{AFX_MSG_MAP(CDeathList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
void CDeathList::FillRow(int nItem) {
  CFormABC* pForm = GetABCForm();
  CString s;
  CRSDeathes* pSet = (CRSDeathes*)pForm->m_pSet;
  CListCtrl& list = GetListCtrl();
  if ( !pSet->IsFieldNull(&pSet->m_NUMBER) )
    s.Format(_T("%d"), pSet->m_NUMBER);
  list.SetItem(nItem, DC_SEX, LVIF_IMAGE, NULL, pSet->m_SEX, 0, 0, 0);
  list.SetItemText(nItem, DC_NUMBER, s);
  list.SetItemText(nItem, DC_DATEREG, GetDateDDMMYYYY(pSet->m_DATEREG));
  list.SetItemText(nItem, DC_SURNAME, pSet->m_SURNAME);
  list.SetItemText(nItem, DC_NAME,    pSet->m_NAME);
  list.SetItemText(nItem, DC_PATRONYMIC,    pSet->m_PATRONYMIC);

  ABCItemDataDeath* pItemData = NULL;
  if ( m_Items.Lookup(pSet->m_ID, (ABCItemData*&)pItemData) ) {
    pItemData->Reset(pSet->m_ID, pSet->m_NUMBER, pSet->m_DATEREG, pSet->m_SEX, pSet->m_SURNAME, pSet->m_NAME, pSet->m_PATRONYMIC);
  }
  else {
    pItemData = new ABCItemDataDeath(pSet->m_ID, pSet->m_NUMBER, pSet->m_DATEREG, pSet->m_SEX, pSet->m_SURNAME, pSet->m_NAME, pSet->m_PATRONYMIC);
  }
  m_Items.SetAt(pSet->m_ID, (ABCItemData*&)pItemData);
  list.SetItemData(nItem, (DWORD)pItemData);

}
void CDeathList::OnInitialUpdate() {
	CABCList::OnInitialUpdate();
  if ( FALSE==m_fInitialized ) {
    m_fInitialized = TRUE;
    m_SortOrder.SetSize(DC_TOTAL);
    CListCtrl& list = GetListCtrl();

    list.InsertColumn(DC_SEX,         _T("Стать"),        LVCFMT_LEFT, 68);
    list.InsertColumn(DC_NUMBER,      _T(" № "),          LVCFMT_LEFT, 40);
    list.InsertColumn(DC_DATEREG,     _T(" Дата "),       LVCFMT_LEFT, 80);
    list.InsertColumn(DC_SURNAME,     _T("Прізвище"),     LVCFMT_LEFT, 92);
    list.InsertColumn(DC_NAME,        _T("Ім'я"),         LVCFMT_LEFT, 92);
    list.InsertColumn(DC_PATRONYMIC,  _T("По батькові"),  LVCFMT_LEFT, 92);

    m_SexImageList.Create(IDIL_ABCSEX, 16, 0, RGB(0xFF, 0, 0xFF));
    list.SetImageList(&m_SexImageList, LVSIL_SMALL);

/************************************** : by VK at 10.02.2005 0:42:17 **\
    EnableSortIcon();
    ColorSortColumn();
    KeepLabelLeft();
\************************************** : by VK at 10.02.2005 0:42:20 **/
  }

}

