4//
// RList.cpp
//
#include "stdafx.h"
#include "Erags.h"
#include "DataManager.h"

#include "ChildFrm.h"
#include "Defaults.h"
#include "EnvelopeDlg.h"
#include "MainFrm.h"
#include "RList.h"
#include "RNames.h"
#include "RTFCnv.h"
#include "TemplDlg.h"
#include "Menu.h"

#include "..\Common\MDB.h"
#include "..\Common\CyrString.h"


#include <search.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static WORD ToolIdEnvelope[] = { IDR_POST,
                                 16, 15,
                                 ID_PRINT_ENVELOPE_A4_UKR,      // Envelope A4 Ukr
                                 ID_PRINT_ENVELOPE_A4_RUS,      // Envelope A4 Rus
                                 ID_PRINT_ENVELOPE_DL_UKR,      // Envelope DL Ukr
                                 ID_PRINT_ENVELOPE_DL_RUS,      // Envelope DL Rus
                                 ID_PRINT_ENVELOPE_229x162_UKR, // Envelope 229x162 Ukr
                                 ID_PRINT_ENVELOPE_229x162_RUS, // Envelope 229x162 Rus
                                 ID_PRINT_ENVELOPE_229x114_UKR, // Envelope 229x114 Ukr
                                 ID_PRINT_ENVELOPE_229x114_RUS, // Envelope 229x114 Rus
                                 ID_PRINT_ENVELOPE_162x114_UKR, // Envelope 162x114 Ukr
                                 ID_PRINT_ENVELOPE_162x114_RUS, // Envelope 162x114 Rus
                                 NULL};

CRList theRList;

int CompareRListID( const void *a, const void *b) {
   return *(long*)a - *(long*)b;
}

int RegRecCmp(const void *a1, const void *a2) {
  CRListRecord *p1 = *(CRListRecord**)a1,
               *p2 = *(CRListRecord**)a2;

  return CyrCompare(p1->m_Fullname, p2->m_Fullname);
}


/////////////////////////////////////////////////////////////////////////////
// CRListRecord
CRListRecord::CRListRecord() {
  m_hTreeItem = NULL;
}
CRListRecord::~CRListRecord() {
}
int CRListRecord::GetChildCount() {
  int nCount = 0;
  for( int i(0); i < m_array.GetSize(); i++ ) {
    nCount++;
    CRListRecord* pRecord = (CRListRecord*)m_array.GetAt(i);
    if ( pRecord ) {
      nCount += pRecord->GetChildCount();
    }
  }
  return nCount;
}
void CRListRecord::AddChild(CRListRecord* pChildRecord) {
/************************************** : by VK at 01.07.2005 2:36:26 **\
  for( int i(0); i < m_array.GetSize(); i++ ) {
    CRListRecord* pRecord = (CRListRecord*)m_array.GetAt(i);
    if ( CyrCompare(pRecord->m_Fullname, pChildRecord->m_Fullname) > 0 ) {
      m_array.InsertAt(i, pChildRecord);
      return;
    }
  }
\************************************** : by VK at 01.07.2005 2:36:30 **/
  m_array.Add( pChildRecord );
}
void CRListRecord::Update() {
  try {
    CDaoRecordset rs(&theDataManager.m_dbLists);
    rs.Open(dbOpenTable, _T("[RLIST]"));
    rs.SetCurrentIndex(_T("PrimaryKey"));
    COleVariant ovKey(m_ID);
    if ( rs.Seek(_T("="), &ovKey) && rs.CanUpdate() ) {
      rs.Edit();
      COleVariant var, vtNull;
      vtNull.ChangeType(VT_NULL);

      rs.SetFieldValue(_T("FLAGS"), COleVariant(m_Flags, VT_I4));
      if ( m_Fullname.IsEmpty() ) { var = vtNull;                           }
      else                        {var = COleVariant(m_Fullname, VT_BSTRT); }
      rs.SetFieldValue(_T("FULLNAME"), var);

      if ( m_Address.IsEmpty() )  { var = vtNull;                           }
      else                        { var = COleVariant(m_Address, VT_BSTRT); }
      rs.SetFieldValue(_T("ADDRESS"), var);

      if ( m_Phones.IsEmpty() )   { var = vtNull;                           }
      else                        { var = COleVariant(m_Phones, VT_BSTRT);  }
      rs.SetFieldValue(_T("PHONES"), var);

      if ( m_Notice.IsEmpty() )   { var = vtNull;                           }
      else                        { var = COleVariant(m_Notice, VT_BSTRT);  }
      rs.SetFieldValue(_T("NOTICE"), var);

      rs.Update();
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
  }
}
CRListRecord* CRListRecord::InsertChild(const CString& szShortname, const CString& szAddress,
                                        const CString& szPhones,  const CString& szNotice) {
  CRListRecord* pRecordNew = NULL;
  CString szChildID;
  szChildID.Format(_T("%0d01"), m_ID); // It probably will child ID
  if ( szChildID.Left(2)==_T("00") ) {
    szChildID = szChildID.Mid(2);
  }

  int idLen = szChildID.GetLength();
  CDWordArray idArray;
  for( int i(0); i < m_array.GetSize(); i++ ) {
    CRListRecord* pRecord = (CRListRecord*)m_array.GetAt(i);
    idArray.Add( (DWORD)pRecord->m_ID );
  }
  DWORD key = (DWORD)atol(szChildID);
  UINT num = idArray.GetSize();
  for(;;) {
    long* pFound = (long*)_lfind(&key, idArray.GetData(), &num, sizeof(DWORD), CompareRListID);
    if ( NULL==pFound )
      break;
    key++;
  }
  szChildID.Format(_T("%0*d"), idLen, key);
  long lChildID = atol(szChildID);
  try {
    CDaoRecordset rs(&theDataManager.m_dbLists);
    rs.Open(dbOpenTable, _T("[RLIST]"));
    if ( rs.CanAppend() ) {
      rs.AddNew();
      rs.SetFieldValue(_T("ID"),     lChildID);
      rs.SetFieldValue(_T("PARENT"), m_ID);
      if ( FALSE==szShortname.IsEmpty() )
        rs.SetFieldValue(_T("FULLNAME"), (LPCTSTR)szShortname);
      if ( FALSE==szAddress.IsEmpty() )
        rs.SetFieldValue(_T("ADDRESS"), (LPCTSTR)szAddress);
      if ( FALSE==szNotice.IsEmpty() )
        rs.SetFieldValue(_T("NOTICE"), (LPCTSTR)szNotice);
      rs.Update();
      pRecordNew = new CRListRecord();
      pRecordNew->m_ID        = lChildID;
      pRecordNew->m_ParentID  = m_ID;
      pRecordNew->m_Fullname  = szShortname;
      pRecordNew->m_Address   = szAddress;
      pRecordNew->m_Phones    = szPhones;
      pRecordNew->m_Notice    = szNotice;
      theRList.Add(pRecordNew);
      AddChild(pRecordNew);
    }
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
  }
  return pRecordNew;
}
void CRListRecord::Delete() {
  for( int i(0); i < m_array.GetSize(); i++ ) {
    CRListRecord* pChild = (CRListRecord*)m_array.GetAt(i);
    pChild->Delete();
  }
  m_array.RemoveAll();
  try {
    CString sql;
    sql.Format(_T("DELETE FROM RLIST WHERE ID=%d"), m_ID);
    theDataManager.m_dbLists.Execute(sql);
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
  }
  theRList.Delete(this);
}
int CRListRecord::GetImage() {
  if ( -1==m_ParentID )
    return RLIMAGE_ROOT;
  if ( m_ID==theApp.m_RagsID )
    return RLIMAGE_OUR;
  return m_Notice.IsEmpty() ? RLIMAGE_NOCOMMENT : RLIMAGE_COMMENT;
}
int CRListRecord::GetImage(CTreeCtrl& TreeCtrl) {
  if ( -1==m_ParentID )
    return RLIMAGE_ROOT;
  //int nImage = GetImage();
  //if ( TreeCtrl.GetItemState(m_hTreeItem, TVIS_EXPANDED)==TVIS_EXPANDED )
  //  nImage++;
  //return nImage;
  return GetImage();
}
/////////////////////////////////////////////////////////////////////////////
// CRList
CRList::CRList() {
}
CRList::~CRList() {
  Clear();
}
void CRList::Clear() {
  POSITION pos = m_map.GetStartPosition();
  while ( pos ) {
    long key;
    CRListRecord* pRecord = NULL;
    m_map.GetNextAssoc(pos, (void*&)key, (void*&)pRecord);
    delete pRecord;
  }
  m_map.RemoveAll();
}

void CRList::Sort(CPtrArray* pArray) {
  qsort( pArray->GetData(), pArray->GetSize(), sizeof(CRListRecord*), RegRecCmp);
}

void CRList::Load(CProgressCtrl* pProgressCtrl/*=NULL*/, CStatic* pStatic/*=NULL*/) {
  if ( FALSE==theDataManager.m_dbLists.IsOpen() ) {
    return;
  }
  CDaoRecordset rs(&theDataManager.m_dbLists);
  try {
    rs.Open(dbOpenTable, "[RLIST]", dbReadOnly);
    try {
      rs.SetCurrentIndex(_T("PrimaryKey"));
      rs.MoveFirst();
    }
    catch(...) {
    }
    int OldPercent = 0;
    while ( !rs.IsEOF() ) {
      CRListRecord* pRecord = new CRListRecord();
      pRecord->m_ID       = GetFieldLong  (&rs, "ID");
      pRecord->m_ParentID = GetFieldLong  (&rs, "PARENT");
      pRecord->m_Flags    = GetFieldLong  (&rs, "FLAGS");
      pRecord->m_Fullname = GetFieldString(&rs, "FULLNAME");
      pRecord->m_Address  = GetFieldString(&rs, "ADDRESS");
      pRecord->m_Phones   = GetFieldString(&rs, "PHONES");
      pRecord->m_Notice   = GetFieldString(&rs, "NOTICE");

      m_map.SetAt((void*)pRecord->m_ID, pRecord);

      CRListRecord* pParentRecord = NULL;
      if ( m_map.Lookup((void*&)pRecord->m_ParentID, (void*&)pParentRecord) ) {
        pParentRecord->AddChild(pRecord);
      }
      else {
        m_RootItems.Add(pRecord);
      }

      if ( pProgressCtrl && pStatic ) {
        int NewPercent = (int)(rs.GetPercentPosition()*10);
        if ( NewPercent != OldPercent ) {
          pProgressCtrl->SetPos(NewPercent);
          pStatic->SetWindowText(pRecord->m_Fullname);
          OldPercent = NewPercent;
          PeekAndPump();
        }
      }
      rs.MoveNext();
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
  }

  if ( m_RootItems.GetSize() > 1 )
    Sort(&m_RootItems);


  POSITION pos = m_map.GetStartPosition();
  while( pos ) {
    long key;
    CRListRecord* pRecord = NULL;
    m_map.GetNextAssoc(pos, (void*&)key, (void*&)pRecord);
    if ( pRecord->m_array.GetSize() > 1 )
      Sort(&pRecord->m_array);
  }

  long lOwnerID = theIniCache.GetRagsID();
  if ( lOwnerID != -1 ) {
    CRListRecord* pRecord = Lookup(lOwnerID);
    if ( pRecord ) {
      if ( pRecord->m_ParentID )
        pRecord = Lookup(pRecord->m_ParentID);
      if ( pRecord ) {
        if ( pRecord->m_ID > 100 && pRecord->m_ParentID )
          pRecord = Lookup(pRecord->m_ParentID);
        SetParent(pRecord);
      }
    }
  }
  
  pos = m_map.GetStartPosition();
  while( pos ) {
    CRListRecord* pRecord = NULL;
    long key;
    m_map.GetNextAssoc(pos, (void*&)key, (void*&)pRecord);
    if ( pRecord && (pRecord->m_Flags & RLFLAG_USEFLAG)==RLFLAG_USEFLAG ) {
      AddToUserMap(pRecord);
    }
  }

}
void CRList::AddToUserMap(CRListRecord* pParent) {
  m_UserMap.SetAt( (void*)pParent->m_ID, pParent );
  for( int i(0); i < pParent->m_array.GetSize(); i++ ) {
    CRListRecord* pRecord = (CRListRecord*)pParent->m_array.GetAt(i);
    AddToUserMap(pRecord);
  }
}
void CRList::RemoveFromUserMap(CRListRecord* pParent) {
  CRListRecord* pRecord = NULL;
  if ( m_UserMap.Lookup((void*&)pParent->m_ParentID, (void*&)pRecord) ) {
    for( int i(0); i < pParent->m_array.GetSize(); i++ ) {
      pRecord = (CRListRecord*)pParent->m_array.GetAt(i);
      RemoveFromUserMap(pRecord);
    }
    m_UserMap.RemoveKey((void*&)pParent->m_ParentID);
  }
}
void CRList::SetParent(CRListRecord* pParent) {
  m_UserMap.RemoveAll();
  AddToUserMap(pParent);
}
void CRList::FillRegCB(CComboBox& cb, const CString& sNewValue) {
  cb.ResetContent();  
  POSITION pos = m_UserMap.GetStartPosition();
  while ( pos ) {
    CRListRecord* pRecord = NULL;
    long ID = 0;
    m_UserMap.GetNextAssoc(pos, (void*&)ID, (void*&)pRecord);
    cb.AddString(pRecord->m_Fullname);
  }
  if ( !sNewValue.IsEmpty() ) {
    int nIndex = cb.FindString(-1, sNewValue);
    if ( CB_ERR==nIndex )
      nIndex = cb.AddString(sNewValue);
    cb.SetCurSel(nIndex);
  }
}

void CRList::Add(CRListRecord* pRecord) {
  m_map.SetAt((void*)pRecord->m_ID, pRecord);
}
void CRList::Delete(CRListRecord* pRecord) {
  RemoveFromUserMap(pRecord);
  CRListRecord* pParentRecord = Lookup(pRecord->m_ParentID);
  if ( pParentRecord ) {
    for( int i(0); i < pParentRecord->m_array.GetSize(); i++ ) {
      CRListRecord* pChildRecord = (CRListRecord*)pParentRecord->m_array.GetAt(i);
      if ( pChildRecord==pRecord ) {
        pParentRecord->m_array.RemoveAt(i);
        break;
      }
    }
  }
  m_map.RemoveKey((void*)pRecord->m_ID);
  delete pRecord;
}
CRListRecord* CRList::Lookup(long ID) {
  CRListRecord* pRecord = NULL;
  if ( m_map.Lookup((void*)ID, (void*&)pRecord) )
    return pRecord;
  return NULL;
}

CRListRecord* CRList::LookupZeroParent(long ID) {
  CRListRecord* pRecord = Lookup(ID);
  while( pRecord ) {
    if ( 0==pRecord->m_ParentID ) {
      return pRecord;
    }
    pRecord = LookupZeroParent(pRecord->m_ParentID);
  }
  return NULL;
}

CRListRecord* CRList::Lookup(const CString& szName) {
  POSITION pos = m_map.GetStartPosition();
  while ( pos ) {
    long lKey = 0;
    CRListRecord* pRecord = NULL;
    m_map.GetNextAssoc(pos, (void*&)lKey, (void*&)pRecord );
    if ( DBCompare(pRecord->m_Fullname, szName)==0 )
      return pRecord;
  }
  return NULL;
}

HTREEITEM CRList::FillTreeCtrl(CTreeCtrl& tc, long ParentID, HTREEITEM hParentItem) {
  if ( NULL==hParentItem ) {
    tc.DeleteAllItems();
  }
  CRListRecord* pRecord = Lookup(ParentID);
  if ( pRecord ) {
    #ifdef _DEBUG
    CString s;
    s.Format(_T("%s (%d,%d)"), pRecord->m_Fullname, pRecord->m_array.GetSize(), pRecord->GetChildCount());
    HTREEITEM hItem = tc.InsertItem(s, 0, 0, hParentItem);
    #else
    HTREEITEM hItem = tc.InsertItem(pRecord->m_Fullname, 0, 0, hParentItem);
    #endif
    //HTREEITEM hItem = tc.InsertItem(pRecord->m_Fullname, 0, 0, hParentItem);
    if ( hItem ) {
      tc.SetItemData(hItem, (DWORD)pRecord);
      for( int i(0); i < pRecord->m_array.GetSize(); i++ ) {
        CRListRecord* pChildRecord = (CRListRecord*)pRecord->m_array.GetAt(i);
        FillTreeCtrl(tc, pChildRecord->m_ID, hItem);
      }
      return hItem;
    }
  }
  return NULL;
}
/////////////////////////////////////////////////////////////////////////////
// CRListView dialog
void CRListView::FillParent(CRListRecord* pRecord, HTREEITEM hParent) {
  int nImage = 0;
  #ifdef _DEBUG
  CString s;
  s.Format(_T("%s (%d,%d)"), pRecord->m_Fullname, pRecord->m_array.GetSize(), pRecord->GetChildCount());
  HTREEITEM hItem = m_RTree.InsertItem(s, hParent, TVI_LAST);
  #else
  HTREEITEM hItem = m_RTree.InsertItem(pRecord->m_Fullname, hParent, TVI_LAST);
  #endif
  //HTREEITEM hItem = m_RTree.InsertItem(pRecord->m_Fullname, hParent, TVI_LAST);
  m_RTree.SetItemData(hItem, (DWORD)pRecord);
  pRecord->m_hTreeItem = hItem;
  if ( NULL==hParent ) {
    m_hMinJust = hItem;
  }
  else {
    nImage = pRecord->GetImage(m_RTree);
  }
  if ( pRecord->m_ID==theApp.m_RagsID ) {
    m_pOurRecord = pRecord;
  }
  m_RTree.SetItemImage(hItem, nImage, nImage);
  for( int i(0); i < pRecord->m_array.GetSize(); i++ ) {
    CRListRecord* pChild = (CRListRecord*)pRecord->m_array.GetAt(i);
    FillParent(pChild, hItem);
  }
}

void CRListView::Fill() {
  for( int i(0); i < theRList.m_RootItems.GetSize(); i++ ) {
    CRListRecord* pRecord = (CRListRecord*)theRList.m_RootItems.GetAt(i);
    FillParent(pRecord, NULL);
  }
}

IMPLEMENT_DYNCREATE(CRListView, CRListViewBase)
CRListView::CRListView()
           :CRListViewBase(IDD_RLIST) {
  m_fGradientFill = TRUE;
  m_hMinJust = NULL;
  m_fCanSave = m_fDoSave = m_fPrintToWord = FALSE;
  m_pCurrentRecord = m_pOurRecord = NULL;
}
CRListView::~CRListView() {
}
BOOL CRListView::IsNeedSubclassForStaticBG(CWnd* pWnd) {
  switch( pWnd->GetDlgCtrlID() ) {
    case IDC_LBL_CASE:
    case IDC_LBL_PHONES:
    case IDC_STATIC:
    case 0xFFFF:
      return TRUE;
  }
  return FALSE;
}
void CRListView::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
  switch(pWnd->GetDlgCtrlID()) {
    case IDC_LBL_NAME:
    case IDC_LBL_ADDRESS:
    case IDC_LBL_CASE:
    case IDC_LBL_PHONES:
    case IDC_LBL_NOTICE:
      wFlags = SCALE_WIDTH;
      break;
    default:
      CRListViewBase::SetScaleFlags(pWnd, wFlags);
  }
}
void CRListView::DoDataExchange(CDataExchange* pDX) {
  CRListViewBase::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CRListView)
    DDX_Control(pDX, IDC_RTREE,     m_RTree);
    DDX_Control(pDX, IDC_CHILDLIST, m_RList);
    DDX_Control(pDX, IDC_FULLREGNAME, m_Fullname);
    DDX_Control(pDX, IDC_SHORTNAME,   m_Shortname);
    DDX_Control(pDX, IDC_CASE, m_Cases);
    DDX_Control(pDX, IDC_ADDRESS, m_Address);
    DDX_Control(pDX, IDC_PHONES, m_Phones);
    DDX_Control(pDX, IDC_EMAIL, m_EMailLink);
    // DDX_Control(pDX, IDC_EMAIL_LABEL, m_EmailLabel);
    DDX_Control(pDX, IDC_NOTICE, m_Notice);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRListView, CRListViewBase)
  //{{AFX_MSG_MAP(CRListView)
  ON_WM_CREATE()
  ON_WM_DESTROY()
  ON_UPDATE_COMMAND_UI(ID_RECORD_NEW, OnUpdateRecordNew)
  ON_COMMAND(ID_RECORD_NEW, OnRecordNew)
  ON_UPDATE_COMMAND_UI(ID_RECORD_DELETE, OnUpdateRecordDelete)
  ON_COMMAND(ID_RECORD_DELETE, OnRecordDelete)
  ON_UPDATE_COMMAND_UI_RANGE(ID_PRINT_FIRST, ID_PRINT_LAST, OnUpdatePrintItem)
  ON_COMMAND_RANGE(ID_PRINT_FIRST, ID_PRINT_LAST, OnPrintItem)
  ON_UPDATE_COMMAND_UI(ID_PRINT, OnUpdatePrint)
  ON_COMMAND(ID_PRINT, OnPrint)
  ON_COMMAND(ID_WORD, OnWord)
  ON_COMMAND(ID_TEMPLATES, OnTemplates)
  ON_NOTIFY(NM_CLICK, IDC_RTREE, OnClickRTree)
  ON_NOTIFY(NM_RCLICK, IDC_RTREE, OnRClickRTree)
  ON_NOTIFY(NM_RCLICK, IDC_CHILDLIST, OnRClickChildList)
  ON_COMMAND(IDD_SET_OWNER, OnSetOwner)
	ON_CBN_SELENDOK(IDC_CASE, OnSelendokCase)
  ON_UPDATE_COMMAND_UI(ID_WORD, OnUpdatePrint)
  ON_UPDATE_COMMAND_UI(ID_TEMPLATES, OnUpdatePrint)
  ON_COMMAND(IDD_ADD_RAGS, OnRecordNew)
  ON_COMMAND(IDD_DELETE_RAGS, OnRecordDelete)
  ON_COMMAND(IDD_ADD_TO_USEMAP, OnAddToUseMap)
	ON_EN_CHANGE(IDC_SHORTNAME, OnChangeShortname)
	//}}AFX_MSG_MAP
  ON_COMMAND(ID_HELP, OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRListView message handlers
void CRListView::OnInitialUpdate()  {
  CRListViewBase::OnInitialUpdate();
  CChildFrame* pFrame = (CChildFrame*)GetParentFrame();
  pFrame->m_pView = this;
  theApp.m_pRListFrame = pFrame;

  CString strTitle = _T("Список органів реєстрації");
  if ( theDataManager.m_dbLists.IsOpen() ) {
    strTitle.Format(_T("%s - Список органів реєстрації"), theDataManager.m_dbLists.GetName());
  }
  GetDocument()->SetTitle(strTitle);
  m_Cases.SetCurSel(0);
  CRect rc;
  GetClientRect(&rc);
  OnSize(SIZE_MAXIMIZED, rc.Width(), rc.Height());

  m_RList.InsertColumn(0, _T(""), LVCFMT_LEFT, 350);

  m_EMailLink.SetURL(_T("mailto:ERAGS@UKR.NET"));

  // m_ImageList.Create(IDIL_RFOLDERS, 16, 0, 0xFFFFFF);
  m_ImageList.CreateTC(IDIL_RFOLDERS_TC, 16, 16, 0xFFFFFF);
  m_RTree.SetImageList(&m_ImageList, TVSIL_NORMAL);
  m_RList.SetImageList(&m_ImageList, LVSIL_SMALL);
  Fill();
  if ( m_hMinJust ) {
    m_RTree.Expand(m_hMinJust, TVE_EXPAND);
    m_RTree.Select(m_hMinJust, TVGN_CARET);
  }
}
int CRListView::OnCreate(LPCREATESTRUCT lpCreateStruct)  {
  if (CRListViewBase::OnCreate(lpCreateStruct) == -1)
    return -1;


  return 0;
}

void CRListView::OnDestroy() {
  theApp.m_pRListFrame = NULL;
  CRListViewBase::OnDestroy();
}

void CRListView::UpdateTreeItem(CRListRecord* pRecord) {
  m_RTree.SetItemText(pRecord->m_hTreeItem, pRecord->m_Fullname);
}
void CRListView::UpdateListItem(CRListRecord* pRecord) {
  LVFINDINFO lvFindInfo;
  lvFindInfo.flags = LVFI_PARAM;
  lvFindInfo.lParam = (LPARAM)pRecord;
  int nItem = m_RList.FindItem(&lvFindInfo);
  if ( nItem >= 0 ) {
    m_RList.SetItemText(nItem, 0, pRecord->m_Fullname);
    m_RList.SetItem(nItem, 0, LVIF_IMAGE, NULL, pRecord->GetImage(), 0, 0, NULL);
  }
}

void CRListView::DoSave() {
  if ( theApp.m_fReadOnly || false==m_fDoSave )
    return;
  m_fDoSave = false;
  if ( m_pCurrentRecord ) {
    m_pCurrentRecord->m_Fullname = m_Shortname.GetText();
    m_pCurrentRecord->m_Address  = m_Address.GetText();
    m_pCurrentRecord->m_Phones   = m_Phones.GetText();
    m_pCurrentRecord->m_Notice   = m_Notice.GetText();
    m_pCurrentRecord->Update();
    m_RTree.SetItem(m_pCurrentRecord->m_hTreeItem, TVIF_STATE, NULL, 0, 0, TVIS_BOLD, TVIS_BOLD, 0);
    UpdateTreeItem(m_pCurrentRecord);
    UpdateListItem(m_pCurrentRecord);
  }
}

void CRListView::ShowHideEmail() {
  if ( NULL==m_pCurrentRecord ) {
    return;
  }
  int nShow = SW_HIDE;
  int nFound = m_pCurrentRecord->m_Phones.Find('@');
  if ( nFound ) {
    CString s = GetTokenBefore(m_pCurrentRecord->m_Phones, nFound);
    CString sEmail;
    sEmail.Format(_T("mailto:%s"), s);
    m_EMailLink.SetWindowText(s);
    m_EMailLink.SetURL(sEmail);
    nShow = SW_SHOW;
  }
  // m_EmailLabel.ShowWindow(nShow);
  m_EMailLink.ShowWindow(nShow);
  m_EMailLink.SetVisited(false);
  m_EMailLink.InvalidateRect(NULL);

}

void CRListView::FillFromRecord(CRListRecord* pRecord) {
  if ( m_pCurrentRecord && pRecord != m_pCurrentRecord && m_fDoSave ) {
    DoSave();
  }
  m_fCanSave = false;
  CString s;
  int nCase = m_Cases.GetCurSel()+1;
  if ( nCase < RC_NV || nCase > RC_MV )
    nCase = RC_NV;
  s = SVRagsC(pRecord->m_Fullname, nCase);
  m_Fullname.SetWindowText(s);
  m_Shortname.SetWindowText(pRecord->m_Fullname);
  m_Address.SetWindowText(pRecord->m_Address);
  m_Phones.SetWindowText(pRecord->m_Phones);
  m_Notice.SetWindowText(pRecord->m_Notice);
  m_fCanSave = true;
  m_pCurrentRecord = pRecord;
  ShowHideEmail();
}
void CRListView::FillListCtrl(CRListRecord* pParentRecord) {
  CHeaderCtrl* pHdr = m_RList.GetHeaderCtrl();
  CString sHdrText;
  sHdrText.Format(_T("Відділи %s"), pParentRecord->m_Fullname);
  if ( sHdrText.Find(_T("Міністерство")) >=0 ) {
    sHdrText.Replace(_T("Міністерство"), _T("Міністерства"));
  }
  HDITEM hdItem;
  hdItem.mask = HDI_TEXT;
  hdItem.pszText = (LPTSTR)(LPCTSTR)sHdrText;
  hdItem.cchTextMax = sHdrText.GetLength();
  pHdr->SetItem(0, &hdItem);
  m_RList.DeleteAllItems();
  for( int i(0); i < pParentRecord->m_array.GetSize(); i++ ) {
    CRListRecord* pRecord = (CRListRecord*)pParentRecord->m_array.GetAt(i);
    m_RList.InsertItem(i, pRecord->m_Fullname, pRecord->GetImage());
    m_RList.SetItemData(i, (DWORD)pRecord);
  }
}
BOOL CRListView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
  NMHDR* pNMHDR = (NMHDR*)lParam;
  switch( pNMHDR->idFrom ) {
    case IDC_RTREE: {
        NMTREEVIEW* pNMTreeView = (NMTREEVIEW*)pNMHDR;
        switch ( pNMHDR->code ) {
          case TVN_SELCHANGED:
             if( pNMTreeView->itemNew.state & TVIS_SELECTED ) {
              CRListRecord* pRecord = (CRListRecord*)pNMTreeView->itemNew.lParam;
              FillFromRecord(pRecord);
              FillListCtrl(pRecord);
            }
            *pResult = 0;
            break;
          case TVN_ITEMEXPANDED: {
            CRListRecord* pRecord = (CRListRecord*)pNMTreeView->itemNew.lParam;
            if ( pRecord->m_ParentID != -1 ) {
              int nImage = pRecord->GetImage(m_RTree);
              if ( pNMTreeView->itemNew.state & TVIS_EXPANDED )
               nImage++;
              m_RTree.SetItemImage(pNMTreeView->itemNew.hItem, nImage, nImage);
            }
          }
          *pResult = 0;
          break;
        }
      }
      break;
    case IDC_CHILDLIST: {
        NMLISTVIEW* pNMLISTVIEW = (NMLISTVIEW*)pNMHDR;
        switch ( pNMHDR->code ) {
          case LVN_ITEMCHANGED:
            if ( (pNMLISTVIEW->uNewState & LVIS_FOCUSED) && pNMLISTVIEW->iItem >= 0 ) {
              CRListRecord* pRecord = (CRListRecord*)pNMLISTVIEW->lParam;
              FillFromRecord(pRecord);
            }
            break;
        }
      }
      break;
  }
  return CRListViewBase::OnNotify(wParam, lParam, pResult);
}
BOOL CRListView::OnCommand(WPARAM wParam, LPARAM lParam) {
  switch(LOWORD(wParam)) {
    case IDC_SHORTNAME:
    case IDC_ADDRESS:
    case IDC_PHONES:
    case IDC_NOTICE:
      if ( m_fCanSave && EN_CHANGE==HIWORD(wParam) ) {
        m_fDoSave = TRUE;
      }
      break;
  }
  return CRListViewBase::OnCommand(wParam, lParam);
}
void CRListView::OnUpdateRecordNew(CCmdUI* pCmdUI) {
  pCmdUI->Enable(theApp.m_fReadOnly != FALSE);
}
void CRListView::OnRecordNew() {
  if ( m_pCurrentRecord ) {
    CRListAddDlg dlg(this);
    dlg.m_pSelectedRecord = m_pCurrentRecord;

    if ( dlg.DoModal()==IDYES ) {
      CRListRecord* pRecord = dlg.m_pSelectedRecord->InsertChild(dlg.m_szShortname, dlg.m_szAddress,
                                                                 dlg.m_szPhones, dlg.m_szNotice);
      if ( pRecord ) {
        HTREEITEM hItem = m_RTree.InsertItem(pRecord->m_Fullname, dlg.m_pSelectedRecord->m_hTreeItem, TVI_LAST);
        m_RTree.SetItem(hItem, TVIF_STATE, NULL, 0, 0, TVIS_BOLD, TVIS_BOLD, 0);
        pRecord->m_hTreeItem = hItem;
        int nImage = pRecord->GetImage(m_RTree);
        m_RTree.SetItemImage(hItem, nImage, nImage);
        m_RTree.SetItemData(hItem, (DWORD)pRecord);
        pRecord->m_hTreeItem = hItem;
        if ( dlg.m_pSelectedRecord->m_hTreeItem )
          m_RTree.SortChildren(dlg.m_pSelectedRecord->m_hTreeItem);

        CRListRecord* pRTreeRecord = NULL;
        HTREEITEM hSelItem = m_RTree.GetSelectedItem();
        if ( hSelItem ) {
          pRTreeRecord = (CRListRecord*)m_RTree.GetItemData(hSelItem);
        }
        if ( dlg.m_pSelectedRecord==pRTreeRecord ) {
          FillListCtrl(pRTreeRecord);
        }
      }
    }
  }
}
void CRListView::OnUpdateRecordDelete(CCmdUI* pCmdUI) {
  if ( theApp.m_fReadOnly ) {
    pCmdUI->Enable(false);
    return;
  }
  HTREEITEM hItem = m_RTree.GetSelectedItem();
  int nItem = -1;
  POSITION pos = m_RList.GetFirstSelectedItemPosition();
  if ( pos ) {
    nItem = m_RList.GetNextSelectedItem(pos);
  }
  pCmdUI->Enable(hItem != NULL || nItem>= 0);
}
void CRListView::OnRecordDelete() {
  CRListRecord* pRTreeRecord = NULL;
  CRListRecord* pRListRecord = NULL;
  HTREEITEM hItem = m_RTree.GetSelectedItem();
  if ( hItem ) {
    pRTreeRecord = (CRListRecord*)m_RTree.GetItemData(hItem);
  }
  int nItem = -1;
  POSITION pos = m_RList.GetFirstSelectedItemPosition();
  if ( pos ) {
    nItem = m_RList.GetNextSelectedItem(pos);
    if ( nItem >= 0 ) {
      pRListRecord = (CRListRecord*)m_RList.GetItemData(nItem);
    }
  }

  if ( pRTreeRecord || pRListRecord ) {
    CRListDelDlg dlg(this);
    dlg.m_pRTreeRecord = pRTreeRecord;
    dlg.m_pRListRecord = pRListRecord;
    if ( dlg.DoModal()==IDYES && dlg.m_pRSelectedRecord ) {
      CWaitCursor wc;
      HTREEITEM hItem = dlg.m_pRSelectedRecord->m_hTreeItem;
      HTREEITEM hItemNext = NULL;
      HTREEITEM hItemPrev = NULL;
      HTREEITEM hItemRoot = NULL;
      if ( hItem ) {
        hItemNext = m_RTree.GetNextItem(hItem, TVGN_NEXT);
        hItemPrev = m_RTree.GetNextItem(hItem, TVGN_PREVIOUS);
        hItemRoot = m_RTree.GetNextItem(hItem, TVGN_ROOT);
      }
      dlg.m_pRSelectedRecord->Delete();
      if ( hItem ) {
        m_RTree.DeleteItem(hItem);
        if ( hItemNext )
          m_RTree.SelectItem(hItemNext);
        else if ( hItemPrev )
          m_RTree.SelectItem(hItemPrev);
        else if ( hItemRoot )
          m_RTree.SelectItem(hItemRoot);
      }
    }
  }
}

void CRListView::OnAddToUseMap() {
  if ( m_pCurrentRecord ) {
    if ( m_pCurrentRecord->m_Flags & RLFLAG_USEFLAG ) { // to remove
      m_pCurrentRecord->m_Flags &= ~RLFLAG_USEFLAG;
    }
    else { // to add
      m_pCurrentRecord->m_Flags |= RLFLAG_USEFLAG;
    }
    m_pCurrentRecord->Update();
    if ( m_pCurrentRecord->m_Flags & RLFLAG_USEFLAG ) {
      theRList.AddToUserMap(m_pCurrentRecord);
    }
    else {
      theRList.RemoveFromUserMap(m_pCurrentRecord);
    }
  }
}
void CRListView::OnSelendokCase() {
	// TODO: Add your control notification handler code here
  if ( m_pCurrentRecord ) {
    CString s;
    int nCase = m_Cases.GetCurSel() + 1;
    if ( nCase < RC_NV || nCase > RC_MV )
      nCase = RC_NV;
    s = SVRagsC(m_pCurrentRecord->m_Fullname, nCase);
    m_Fullname.SetWindowText(s);
  }
}

// Print support
void CRListView::OnPrintMenu() {
  CNewMenu menu, *pPopup = NULL;
  CRect r;
  menu.LoadMenu(IDR_PRINT);
  pPopup = DYNAMIC_DOWNCAST(CNewMenu,menu.GetSubMenu(CONTEXT_RLIST));
  ASSERT(pPopup);

  ((CMainFrame*)theApp.m_pMainWnd)->GetCommandButtonRect(m_fPrintToWord ? ID_WORD : ID_PRINT, &r);
  POINT p;
  p.y = r.bottom;
  p.x = r.right;

  LPCTSTR szMenuTitle = m_fPrintToWord ? _T("Експорт Документа") : _T("Конверти");

  if ( szMenuTitle )
    pPopup->SetMenuTitle(szMenuTitle, MFT_GRADIENT|MFT_SIDE_TITLE|MFT_LINE);

  pPopup->LoadToolBar(ToolIdEnvelope, RGB(192,192,192) );
  pPopup->TrackPopupMenu(TPM_RIGHTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON|TPM_VERTICAL, p.x, p.y, GetParent());
}

void CRListView::OnUpdatePrintItem(CCmdUI* pCmdUI) {
  // TODO: Add your command update UI handler code here
  pCmdUI->Enable();
  
}
void CRListView::OnUpdatePrint(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
}
void CRListView::OnPrint() {
  m_fPrintToWord = FALSE;
  OnPrintMenu();
}
void CRListView::OnWord() {
  m_fPrintToWord = TRUE;
  OnPrintMenu();
}

void CRListView::OnTemplates() {
  CTemplDlg dlg(IDD_RLIST, this);
  if ( IDYES==dlg.DoModal() ) {
  }
}

void CRListView::OnPrint(UINT nPrintID) {
  HTREEITEM hItem = m_RTree.GetSelectedItem();
  if ( NULL==hItem )
    return;

  CRListRecord* pRTreeRecord = (CRListRecord*)m_RTree.GetItemData(hItem);
  CEnvelopeDlg dlg(nPrintID, this);
  dlg.m_pRecord = pRTreeRecord;
  if ( IDYES==dlg.DoModal() ) {
    CString sTemplate, sOut;
    switch ( nPrintID ) {
      case ID_PRINT_ENVELOPE_A4_UKR:
        sTemplate.Format(IDS_ENVELOPE, theApp.m_sTemplatePath, _T("A4_Ukr") );
        sOut.Format(IDS_ENVELOPE, theApp.m_sOutPath, _T("A4_Ukr"));
        break;
      case ID_PRINT_ENVELOPE_A4_RUS:
        sTemplate.Format(IDS_ENVELOPE, theApp.m_sTemplatePath, _T("A4_Rus") );
        sOut.Format(IDS_ENVELOPE, theApp.m_sOutPath, _T("A4_Rus"));
        break;
      case ID_PRINT_ENVELOPE_DL_UKR:
        sTemplate.Format(IDS_ENVELOPE, theApp.m_sTemplatePath, _T("DL_Ukr") );
        sOut.Format(IDS_ENVELOPE, theApp.m_sOutPath, _T("DL_Ukr"));
        break;
      case ID_PRINT_ENVELOPE_DL_RUS:
        sTemplate.Format(IDS_ENVELOPE, theApp.m_sTemplatePath, _T("DL_Rus") );
        sOut.Format(IDS_ENVELOPE, theApp.m_sOutPath, _T("DL_Rus"));
        break;
      case ID_PRINT_ENVELOPE_229x114_UKR:
        sTemplate.Format(IDS_ENVELOPE, theApp.m_sTemplatePath, _T("229x114_Ukr") );
        sOut.Format(IDS_ENVELOPE, theApp.m_sOutPath, _T("229x114_Ukr"));
        break;
      case ID_PRINT_ENVELOPE_229x114_RUS:
        sTemplate.Format(IDS_ENVELOPE, theApp.m_sTemplatePath, _T("229x114_Rus") );
        sOut.Format(IDS_ENVELOPE, theApp.m_sOutPath, _T("229x114_Rus"));
        break;
      case ID_PRINT_ENVELOPE_229x162_UKR:
        sTemplate.Format(IDS_ENVELOPE, theApp.m_sTemplatePath, _T("229x162_Ukr") );
        sOut.Format(IDS_ENVELOPE, theApp.m_sOutPath, _T("229x162_Ukr"));
        break;
      case ID_PRINT_ENVELOPE_229x162_RUS:
        sTemplate.Format(IDS_ENVELOPE, theApp.m_sTemplatePath, _T("229x162_Rus") );
        sOut.Format(IDS_ENVELOPE, theApp.m_sOutPath, _T("229x162_Rus"));
        break;
      case ID_PRINT_ENVELOPE_162x114_UKR:
        sTemplate.Format(IDS_ENVELOPE, theApp.m_sTemplatePath, _T("162x114_Ukr") );
        sOut.Format(IDS_ENVELOPE, theApp.m_sOutPath, _T("162x114_Ukr"));
        break;
      case ID_PRINT_ENVELOPE_162x114_RUS:
        sTemplate.Format(IDS_ENVELOPE, theApp.m_sTemplatePath, _T("162x114_Rus") );
        sOut.Format(IDS_ENVELOPE, theApp.m_sOutPath, _T("162x114_Rus"));
        break;
    }

    MakeInOutExt(sTemplate, sOut);

    CWaitCursor wc;
    if ( ConvertEnvelope(sTemplate, sOut) ) {
      if ( m_fPrintToWord ) {
        ShellExecute(NULL, "open", sOut, NULL, NULL, SW_SHOW);
      }
      else {
        if ( MS_OFFICE==theApp.GetOffice() ) {
          theApp.m_pWordTemplate->CloseAllDocuments(FALSE);
          theApp.m_pWordTemplate->OpenDocumentFile(sOut);
        }
        else {
          theApp.m_pOOTemplate->CloseAllDocuments(FALSE);
          theApp.m_pOOTemplate->OpenDocumentFile(sOut);
        }
      }
    }
  }
}
void CRListView::OnPrintItem(UINT nID) {
  // TODO: Add your command update UI handler code here
  OnPrint(nID);
}

void CRListView::OnClickRTree(NMHDR* pNMHDR, LRESULT* pResult) {
  // TODO: Add your control notification handler code here
  CPoint p;
  GetCursorPos(&p);
  m_RTree.ScreenToClient(&p);
  UINT uFlags;
  HTREEITEM hItem = m_RTree.HitTest(p, &uFlags);
  m_RTree.SelectItem(hItem);
  *pResult = 0;
}
void CRListView::OnRClickRTree(NMHDR* pNMHDR, LRESULT* pResult) {
  // TODO: Add your control notification handler code here
  OnClickRTree(pNMHDR, pResult);
  if ( theApp.m_fReadOnly ) {
    return;
  }
  HTREEITEM hItem = m_RTree.GetSelectedItem();
  CPoint p;
  CNewMenu menu;
  GetCursorPos(&p);
  menu.LoadMenu(IDM_RLIST);
  CNewMenu* pPopup = (CNewMenu*)menu.GetSubMenu(0);
  if ( hItem ) {
    CRListRecord* pRecord = (CRListRecord* )m_RTree.GetItemData(hItem);
    if ( pRecord ) {
      pPopup->CheckMenuItem(IDD_ADD_TO_USEMAP, (pRecord->m_Flags & RLFLAG_USEFLAG) ? MF_CHECKED|MF_BYCOMMAND : MF_UNCHECKED|MF_BYCOMMAND);
    }
    if ( FALSE==g_fSuperVisor ) {
      pPopup->DeleteMenu(IDD_SET_OWNER, MF_BYCOMMAND);
      int nLastPos = pPopup->GetMenuItemCount()-1;
      pPopup->DeleteMenu(nLastPos, MF_BYPOSITION);
    }
  }
  pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON, p.x, p.y, this);
  *pResult = 0;
}
void CRListView::OnRClickChildList(NMHDR* pNMHDR, LRESULT* pResult) {
  if ( theApp.m_fReadOnly ) {
    return;
  }

  CPoint p;
  GetCursorPos(&p);
  CNewMenu menu;
  menu.LoadMenu(IDM_RLIST);
  CNewMenu* pPopup = (CNewMenu*)menu.GetSubMenu(0);
  int nItem = m_RList.GetNextItem(-1, LVNI_SELECTED);
  if ( nItem >= 0 ) {
    CRListRecord* pRecord = (CRListRecord*)m_RList.GetItemData(nItem);
    if ( pRecord ) {
      pPopup->CheckMenuItem(IDD_ADD_TO_USEMAP, (pRecord->m_Flags & RLFLAG_USEFLAG) ? MF_CHECKED|MF_BYCOMMAND : MF_UNCHECKED|MF_BYCOMMAND);
    }
  }
  pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON, p.x, p.y, this);
  *pResult = 0;
}
void CRListView::OnSetOwner() {
/************************************** : by VK at 17.07.2005 7:00:36 **\
  HTREEITEM hItem = m_RTree.GetSelectedItem();
  if ( NULL==hItem )
    return;
  CRListRecord* pRTreeRecord = (CRListRecord*)m_RTree.GetItemData(hItem);
  CRListRecord* pRListRecord = (CRListRecord*)m_RTree.GetItemData(hItem);
\************************************** : by VK at 17.07.2005 7:00:40 **/
  #ifndef _DEBUG
  if ( FALSE==g_fSuperVisor ) {
    MessageBox(_T("Ця функція недоступна для Вашого відділу."), _T("ЕРАГС"), MB_OK|MB_ICONINFORMATION);
    return;
  }
  #endif
  if ( m_pCurrentRecord ) {
    int nImage;
    theApp.m_RagsID = m_pCurrentRecord->m_ID;
    if ( m_pOurRecord ) {
      nImage = m_pOurRecord->GetImage(m_RTree);
      m_RTree.SetItemImage(m_pOurRecord->m_hTreeItem, nImage, nImage);
      UpdateListItem(m_pOurRecord);
    }
    m_pOurRecord = m_pCurrentRecord;

    theIniCache.SetRagsID(m_pOurRecord->m_ID);
    theIniCache.SetRAGS(m_pOurRecord->m_Fullname);

    CRListRecord* pParent = theRList.Lookup(m_pOurRecord->m_ParentID);
    if ( pParent ) {
      theIniCache.SetParent(pParent->m_Fullname);
      theRList.SetParent(pParent);
    }

    nImage = m_pOurRecord->GetImage(m_RTree);
    m_RTree.SetItemImage(m_pOurRecord->m_hTreeItem, nImage, nImage);
    UpdateListItem(m_pOurRecord);
  }
}
void CRListView::OnHelp() {
  theApp.OnHelp(_T("Lists"), _T("#Registars"));
}


/////////////////////////////////////////////////////////////////////////////
// CRListAddDlg dialog
CRListAddDlg::CRListAddDlg(CWnd* pParent /*=NULL*/)
             :CDialogEx(CRListAddDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CRListAddDlg)
  //}}AFX_DATA_INIT
  m_pSelectedRecord = NULL;
}

void CRListAddDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CRListAddDlg)
  DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_CHILD_OF, m_ChildOf);
  DDX_Control(pDX, IDC_BTN_UP, m_btnUp);
  DDX_Control(pDX, IDC_SHORTNAME, m_Shortname);
  DDX_Control(pDX, IDC_ADDRESS,   m_Address);
  DDX_Control(pDX, IDC_PHONES,    m_Phones);
  DDX_Control(pDX, IDC_NOTICE,    m_Notice);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRListAddDlg, CDialogEx)
  //{{AFX_MSG_MAP(CRListAddDlg)
  ON_BN_CLICKED(IDYES, OnYes)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRListAddDlg message handlers
BOOL CRListAddDlg::OnInitDialog() {
  CDialogEx::OnInitDialog();

  m_ChildOf.SetWindowText(m_pSelectedRecord->m_Fullname);
  m_btnUp.SetIcon(IDI_UP);

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

void CRListAddDlg::OnUp() {
  CRListRecord* pParentRecord = theRList.Lookup(m_pSelectedRecord->m_ParentID);
  if ( pParentRecord ) {
    m_pSelectedRecord = pParentRecord;
    m_ChildOf.SetWindowText(m_pSelectedRecord->m_Fullname);
  }
}
void CRListAddDlg::OnYes() {
  m_szShortname = m_Shortname.GetText();
  m_szAddress = m_Address.GetText();
  m_szPhones = m_Phones.GetText();
  m_szNotice = m_Notice.GetText();
  CDialogEx::OnYes();
}

BOOL CRListAddDlg::CanAdd() {
  return (FALSE==m_Shortname.GetText().IsEmpty());
}

BOOL CRListAddDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
  switch( LOWORD(wParam) ) {
    case IDC_BTN_UP:
      if ( BN_CLICKED==HIWORD(wParam) ) {
        OnUp();
      }
      break;
    case IDC_SHORTNAME:
      if ( EN_CHANGE==HIWORD(wParam) ) {
        m_btnOk.EnableWindow( CanAdd() );
      }
      break;
  }
  return CDialogEx::OnCommand(wParam, lParam);
}
/////////////////////////////////////////////////////////////////////////////
// CRListDelDlg dialog
CRListDelDlg::CRListDelDlg(CWnd* pParent /*=NULL*/)
             :CDialogEx(CRListDelDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CRListDelDlg)
  //}}AFX_DATA_INIT
  m_pRTreeRecord = m_pRTreeRecord = m_pRSelectedRecord = NULL;
}

void CRListDelDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CRListDelDlg)
  DDX_Control(pDX, IDC_WARNING, m_Warning);
  DDX_Control(pDX, IDC_LBL_OR, m_lblOr);
  DDX_Control(pDX, IDC_RADIO_TREE, m_RadioTree);
  DDX_Control(pDX, IDC_RADIO_LIST, m_RadioList);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRListDelDlg, CDialogEx)
  //{{AFX_MSG_MAP(CRListDelDlg)
  ON_BN_CLICKED(IDC_RADIO_TREE, OnRadioTree)
  ON_BN_CLICKED(IDC_RADIO_LIST, OnRadioList)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRListDelDlg message handlers
BOOL CRListDelDlg::OnInitDialog() {
  CDialogEx::OnInitDialog();

  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_RadioTree.SetRadioImageList(&m_RadioIL);  m_RadioTree.SetRadio(IDC_RADIO_TREE, IDC_RADIO_LIST);
    m_RadioList.SetRadioImageList(&m_RadioIL);  m_RadioList.SetRadio(IDC_RADIO_TREE, IDC_RADIO_LIST);
  }


  GetDlgItem(IDC_WARNING)->SetWindowText(_T("Увага!\r\n")
                                         _T("Видалені записи не підлягать відновленню!\r\n")
                                         _T("Чи дійсно Ви бажаєте видалити запис")
                                        );
  int nOrShow = 2;
  if ( NULL==m_pRTreeRecord ) {
    GetDlgItem(IDC_RADIO_TREE)->ShowWindow(SW_HIDE);
    nOrShow--;
  }
  else {
    GetDlgItem(IDC_RADIO_TREE)->SetWindowText(m_pRTreeRecord->m_Fullname);
    m_pRSelectedRecord = m_pRTreeRecord;
  }
  if ( NULL==m_pRListRecord ) {
    GetDlgItem(IDC_RADIO_LIST)->ShowWindow(SW_HIDE);
    nOrShow--;
  }
  else {
    GetDlgItem(IDC_RADIO_LIST)->SetWindowText(m_pRListRecord->m_Fullname);
    m_pRSelectedRecord = m_pRListRecord;
  }
  if ( nOrShow <= 1 ) {
    GetDlgItem(IDC_RADIO_TREE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_RADIO_LIST)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_LBL_OR)->SetWindowText( (m_pRTreeRecord!=NULL) ? m_pRTreeRecord->m_Fullname : m_pRListRecord->m_Fullname );
    m_btnOk.EnableWindow(TRUE);
  }
  else {
    m_pRSelectedRecord = NULL;
  }
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}
void CRListDelDlg::OnRadioTree() {
  m_pRSelectedRecord = m_pRTreeRecord;
  m_btnOk.EnableWindow(TRUE);
}
void CRListDelDlg::OnRadioList() {
  m_pRSelectedRecord = m_pRListRecord;
  m_btnOk.EnableWindow(TRUE);
}


void CRListView::OnChangeShortname() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CRListViewBase::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
