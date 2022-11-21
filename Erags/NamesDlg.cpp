// NamesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "NamesDlg.h"

#include "DataManager.h"
#include "..\Common\DB.h"
#include "..\Common\DaoErr.h"
#include "..\Common\EraMessages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNamesDlg dialog
BEGIN_MESSAGE_MAP(CNamesDlg, CDialog)
	//{{AFX_MSG_MAP(CNamesDlg)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_CLICK, IDC_NAMELIST, OnClickNamelist)
	ON_NOTIFY(LVN_KEYDOWN, IDC_NAMELIST, OnKeydownNamelist)
	ON_EN_CHANGE(IDC_NAME, OnChangeName)
	ON_BN_CLICKED(ID_RECORD_NEW, OnRecordNew)
	ON_BN_CLICKED(ID_RECORD_DELETE, OnRecordDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_NAMELIST, OnDblclkNamelist)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_NAMELIST, OnEndLabelEditNamelist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_NAMELIST, OnItemchangedNamelist)
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CNamesDlg::CNamesDlg(LPCTSTR szCaption, LPCTSTR szTableName, LPCTSTR szFieldName, LPCTSTR szColumnName, CWnd* pParent /*=NULL*/)
	        :CDialog(CNamesDlg::IDD, pParent) {
  m_szCaption    = szCaption;
	m_szTableName  = szTableName;
  m_szFieldName  = szFieldName;
  m_szColumnName = szColumnName;
  m_fChangeName = false;
  //{{AFX_DATA_INIT(CNamesDlg)
	//}}AFX_DATA_INIT
}

void CNamesDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNamesDlg)
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, ID_RECORD_NEW, m_btnNew);
	DDX_Control(pDX, ID_RECORD_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_NAMELIST, m_List);
	//}}AFX_DATA_MAP
}

void CNamesDlg::AddNewRecord(const CString& s, bool fSex) {
  CDaoRecordset rs(&theDataManager.m_dbLists);
  long lID = 0;

  COleVariant ovSex;
  ovSex.vt      = VT_BOOL;
  ovSex.boolVal = fSex;

  try {
    rs.Open(dbOpenTable, m_szTableName);
    if ( rs.CanAppend() ) {
      rs.AddNew();
      rs.SetFieldValue(m_szFieldName, (LPCTSTR)s);
      rs.SetFieldValue(_T("SEX"), ovSex);
      rs.Update();
      rs.SetBookmark( rs.GetLastModifiedBookmark() ); // Необходимо для последующего чтения из rs
      lID = rs.GetFieldValue(_T("ID")).lVal;
    }
    if ( lID ) {
      int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
      if ( nItem >= 0 ) {
        nItem++;
      }
      else {
        nItem = m_List.GetItemCount();
      }
      nItem = m_List.InsertItem(nItem, s, fSex);
      m_List.SetItemText(nItem, 1, fSex ? _T("Ч") : _T("Ж"));
      m_List.SetItemData(nItem, (LPARAM)lID);
    }
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    theApp.OnMessage(EM_ERROR, FormatDaoError(e));
  }
}
void CNamesDlg::UpdateRecord(int nItem, LPCTSTR szName, bool fSex) {
  if ( NULL==szName || '\0'==szName[0] ) {
    return;
  }
  COleVariant ovSex;
  long lID = m_List.GetItemData(nItem);
  ovSex.vt = VT_BOOL;
  ovSex.boolVal = fSex;

  COleVariant ovKey(lID);
  CDaoRecordset rs(&theDataManager.m_dbLists);
  try {
    rs.Open(dbOpenTable, m_szTableName);
    rs.SetCurrentIndex("PrimaryKey");
    if ( rs.Seek(_T("="), &ovKey) ) {
      if ( rs.CanUpdate() ) {
        rs.Edit();
        rs.SetFieldValue(m_szFieldName, szName);
        rs.SetFieldValue(_T("SEX"), ovSex);
        rs.Update();
        m_List.SetItemText(nItem, 0, szName);
      }
    }
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    theApp.OnMessage(EM_ERROR, FormatDaoError(e));
  }
}

void CNamesDlg::Fill() {
  CString sql;
  sql.Format(_T("SELECT ID, %s, SEX FROM %s ORDER BY %s"),
             m_szFieldName, m_szTableName, m_szFieldName);

  CDaoQueryDef qd(&theDataManager.m_dbLists);
  CDaoRecordset rs(&theDataManager.m_dbLists);


  int iRow = 0;
  try {
    qd.Create(NULL,sql);
    rs.Open(&qd);

    while ( !rs.IsEOF() ) {
      long lID = iDBLongField(rs, 0);
      CString sName   = iDBStringField(rs, 1);
      BOOL fMale      = iDBBoolField(rs, 2);

      m_List.InsertItem (iRow, sName,  fMale);
      m_List.SetItemText(iRow, 1, fMale ? _T("Ч") : _T("Ж"));
      m_List.SetItemData(iRow, (LPARAM)lID);
      rs.MoveNext();
      iRow++;
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CNamesDlg message handlers
BOOL CNamesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);

  SetWindowText(m_szCaption);
  GetDlgItem(IDC_LABEL)->SetWindowText(m_szColumnName);


  m_List.InsertColumn(0,  m_szColumnName,  LVCFMT_LEFT, 124);
  m_List.InsertColumn(1,  _T("Стать"),              LVCFMT_LEFT, 48);
  m_ImageList.Create(IDIL_ABCSEX, 16, 0, RGB(0xFF, 0, 0xFF));
  m_List.SetImageList(&m_ImageList, LVSIL_SMALL);

  m_btnNew.SetIcon(IDI_RECORD_NEW);
  m_btnNew.SetTooltipText(_T("Додати"), true);

  m_btnDelete.SetIcon(IDI_RECORD_DELETE);
  m_btnDelete.SetTooltipText(_T("Видалити"), true);

  Fill();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNamesDlg::OnSize(UINT nType, int cx, int cy) {
	CNamesDlgBase::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
}

BOOL CNamesDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CNamesDlgBase::OnEraseBkgnd(pDC);
}
void CNamesDlg::ChangeSex() {
  int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
  if ( nItem >= 0 ) {
    CString s = m_List.GetItemText(nItem, 1);
    bool fSex;
    if ( s==_T("Ч") ) {
      s = _T("Ж"); fSex = false;
    }
    else {
      s = _T("Ч"); fSex = true;
    }
    m_List.SetItemText(nItem, 1, s);
    m_List.SetItem(nItem, 0, LVIF_IMAGE, NULL, fSex, LVIF_IMAGE, LVIF_IMAGE, 0);
    UpdateRecord(nItem, m_List.GetItemText(nItem,0), fSex);
  }
}
void CNamesDlg::OnClickNamelist(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: Add your control notification handler code here
  NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
  if ( pNMListView->iItem >= 0 ) {
    CString s = m_List.GetItemText(pNMListView->iItem, 0);
    m_Name.SetWindowText(s);
    if ( 1==pNMListView->iSubItem ) {
      ChangeSex();
    }
  }
	*pResult = 0;
}

void CNamesDlg::OnItemchangedNamelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  if ( pNMListView->iItem >= 0 && (pNMListView->uNewState & LVIS_SELECTED) ) {
    if ( false==m_fChangeName ) {
      CString s = m_List.GetItemText(pNMListView->iItem, 0);
      m_Name.SetWindowText(s);
    }
  }
	
	*pResult = 0;
}

void CNamesDlg::OnKeydownNamelist(NMHDR* pNMHDR, LRESULT* pResult) {
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
  if ( VK_SPACE==pLVKeyDow->wVKey ) {
    ChangeSex();
  }
	*pResult = 0;
}

void CNamesDlg::OnDblclkNamelist(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: Add your control notification handler code here
  NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
  int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
  if ( 0==pNMListView->iSubItem ) {
  	m_List.EditLabel(pNMListView->iItem);
  }
	*pResult = 0;
}

void CNamesDlg::OnEndLabelEditNamelist(NMHDR* pNMHDR, LRESULT* pResult) {
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here

  if ( pDispInfo->item.pszText && pDispInfo->item.cchTextMax > 0 ) {
    bool fSex = (m_List.GetItemText(pDispInfo->item.iItem, 1)==_T("Ч")) ? true : false;
    UpdateRecord(pDispInfo->item.iItem, pDispInfo->item.pszText, fSex);
  }
	
	*pResult = 0;
}

void CNamesDlg::OnChangeName() {
  m_fChangeName = true;
  CString s;
  m_Name.GetWindowText(s);
  if ( false==s.IsEmpty() ) {
    LVFINDINFO fi;
    fi.flags = LVFI_PARTIAL|LVFI_STRING;
    fi.psz   = s;
    int nItem = m_List.FindItem(&fi);
    if (nItem >= 0) {
      m_List.EnsureVisible(nItem, false);
      m_List.SetItemState(nItem, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
    }
  }
  m_fChangeName = false;
}

void CNamesDlg::OnRecordNew() {
	// TODO: Add your control notification handler code here
  CString s;
  m_Name.GetWindowText(s);
  s = Trim(s);
  if ( false==s.IsEmpty() ) {
    LVFINDINFO fi;
    fi.flags = LVFI_STRING;
    fi.psz   = s;
    int nItem = m_List.FindItem(&fi);
    if ( -1 == nItem ) {
      bool fSex = true;
      if ( s.Right(1)==_T("а") || s.Right(1)==_T("я") ) {
        fSex = false;
      }
      AddNewRecord(s, fSex);
    }
  }
}
void CNamesDlg::OnRecordDelete() {
	// TODO: Add your control notification handler code here
  int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
  if ( nItem >= 0 ) {
    long lID = (long)m_List.GetItemData(nItem);
    CDaoRecordset rs(&theDataManager.m_dbLists);
    COleVariant ovKey(lID);
    try {
      rs.Open(dbOpenTable, m_szTableName);
      rs.SetCurrentIndex("PrimaryKey");
      if ( rs.Seek(_T("="), &ovKey) ) {
        rs.Delete();
        m_List.DeleteItem(nItem);
      }
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      theApp.OnMessage(EM_ERROR, FormatDaoError(e));
    }
  }
}

BOOL CNamesDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
  if ( m_szTableName==_T("Names") ) {
    theApp.OnHelp(_T("Lists"), _T("#Names"));
  }
  else {
    theApp.OnHelp(_T("Lists"), _T("#Patronymics"));
  }
  return TRUE;
}