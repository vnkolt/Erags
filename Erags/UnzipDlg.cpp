// UnzipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "UnzipDlg.h"

#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"
#include "..\Controls\BrowseForFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ZLC_FILENAME  0
#define ZLC_TIME      1
#define ZLC_SIZE      2
#define ZLC_RATIO     3
/************************************** : by VK at 08.10.2005 3:11:44 **\
#define ZLC_CRC       4
#define ZLC_ATTR      5
\************************************** : by VK at 08.10.2005 3:11:47 **/
#define ZLC_COMMENT   4

#define SO_NONE    0
#define SO_ASC     1
#define SO_DESC    2

int ZipSortOrder[ZLC_COMMENT+1];

CZipArchive* g_pzip = NULL;
int CALLBACK ZipSortResults(LPARAM lParam1,
                            LPARAM lParam2,
                            LPARAM lParamSort) {
  if ( NULL==g_pzip )
    return NULL;
  CZipFileHeader fh1, fh2;
  g_pzip->GetFileInfo(fh1, (WORD)lParam1);
  g_pzip->GetFileInfo(fh2, (WORD)lParam2);
  int iResult(0);
  switch(lParamSort) {
    case ZLC_FILENAME:
      iResult = CyrCompare((LPCTSTR)fh1.GetFileName(), (LPCTSTR)fh2.GetFileName());
      break;
    case ZLC_TIME: {
        CTime t1 = fh1.GetTime();
        CTime t2 = fh2.GetTime();
        if ( t1 < t2 ) iResult = -1;
        else if ( t1 > t2 ) iResult = 1;
      }
      break;
    case ZLC_SIZE:
      iResult = fh1.m_uUncomprSize - fh2.m_uUncomprSize;
  }
  if ( ZipSortOrder[lParamSort]==SO_DESC )
    return -iResult;
  return iResult;
}


/////////////////////////////////////////////////////////////////////////////
// CUnzipDlg dialog
CUnzipDlg::CUnzipDlg(CWnd* pParent /*=NULL*/)
	        :CDialogEx(CUnzipDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CUnzipDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_bCommentModified = m_bAfterException = false;
}

void CUnzipDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnzipDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Control(pDX, IDC_ZIPLIST, m_files);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUnzipDlg, CDialogEx)
	//{{AFX_MSG_MAP(CUnzipDlg)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_ZIPLIST, OnColumnclickZipList)
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CUnzipDlg::GetIconIndex(const CString& sFilename) {
  //Retreive the icon index for a specified file/folder
  CString sExt = GetFileExt(sFilename);
  sExt.MakeLower();
  if ( sExt=="er3" ) {
    return 2;
  }
  else if ( sExt=="mdb" ) {
    return 1;
  }
  return 0;
}
void CUnzipDlg::ArchiveOpen() {
/************************************** : by VK at 08.10.2005 2:54:24 **\
	if (!GetFileName(sz, true))
		return;
\************************************** : by VK at 08.10.2005 2:54:29 **/
	ArchiveClose();
	int berr = 0;
	do 
	{
		try
		{
			m_zip.Open(m_szZip, CZipArchive::zipOpen, m_options.m_bTdComp ? 1 : 0 );
			berr = 0;
		}
		catch (CZipException* e)
		{
			if (e->m_iCause == CZipException::cdirNotFound)
				berr = -1;
			else
				berr = 1;
			e->Delete();
		}
		catch (CException* e)
		{
			e->Delete();
			berr = 1;
			
		}
		// thrown in the STL version
		catch (CZipException e)
		{
			if (e.m_iCause == CZipException::cdirNotFound)
				berr = -1;
			else
				berr = 1;

		}
		catch(...) 
		{
			berr = 1;
		}
		if (berr == -1)
		{
			if (AfxMessageBox(_T("The central directory was not found. If you're opening a multi-disk archive, make sure you have inserted the last disk. Retry?"), MB_ICONSTOP|MB_YESNO) == IDNO)
				berr = 1;
			else
				m_zip.Close(true);
		}

		if (berr == 1)
		{
			AfxMessageBox(_T("Open failed"), MB_ICONSTOP);
			return;
		}

	} while (berr == -1);
	m_bCommentModified = false;
	m_szComment = m_zip.GetGlobalComment();
	UpdateData(FALSE);
/************************************** : by VK at 08.10.2005 3:00:26 **\
	if (!m_zip.GetSpanMode())
		GetDlgItem(IDC_EDIT1)->EnableWindow();
\************************************** : by VK at 08.10.2005 3:00:29 **/
  g_pzip = &m_zip;
	Redisplay();
}
void CUnzipDlg::ArchiveClose() {
  if (m_bCommentModified) {
		UpdateData();
		m_zip.SetGlobalComment(m_szComment);
		m_bCommentModified = false;
	}
	bool berr = false;
	try
	{
		m_zip.Close(m_bAfterException);	
	}
	catch (CException* e)
	{
		e->Delete();
		berr = true;
	}
	catch(...) // thrown in the STL version
	{
		berr = true;		
	}
	if (berr)
		AfxMessageBox(_T("Close failed"), MB_ICONSTOP);
/************************************** : by VK at 08.10.2005 2:57:25 **\
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	m_szComment.Empty();
\************************************** : by VK at 08.10.2005 2:57:32 **/
	UpdateData(FALSE);
	Redisplay();
	if (m_bAfterException)
		m_bAfterException = false;
  g_pzip = NULL;
}

void CUnzipDlg::DisplayLabel() {
	SetWindowText(m_zip.IsClosed(false) ? _T("Zip") : (LPCTSTR)m_zip.GetArchivePath());
}
void CUnzipDlg::Redisplay() {
	DisplayLabel();
	m_files.DeleteAllItems();
	int iCount = m_zip.GetCount();
	m_progress.Init(iCount);	
	for (int i = 0; i < iCount; i++)
	{
		CZipFileHeader fh;
		m_zip.GetFileInfo(fh, (WORD)i);
		int iItem = m_files.GetItemCount();
		CString sz = (LPCTSTR)fh.GetFileName();
		if (fh.IsEncrypted())
			sz.Insert(0, _T("(*) "));
		int nImage = GetIconIndex(sz);
    m_files.InsertItem(iItem, sz, nImage);
/************************************** : by VK 30.09.2005 at 15:45:39 **\
		m_files.SetItemText(iItem, 1, m_zip.IsFileDirectory((WORD)i) ? _T("YES") : _T("NO"));
\************************************** : by VK 30.09.2005 at 15:45:43 **/
		sz.Format(_T("%d"), fh.m_uUncomprSize);
		m_files.SetItemText(iItem, ZLC_SIZE, sz);
		CTime t(fh.GetTime());
    sz.Format(_T("%04d.%02d.%02d/%02d:%02d:%02d"),
              t.GetYear(), t.GetMonth(), t.GetDay(),
              t.GetHour(), t.GetMinute(), t.GetSecond() );
		m_files.SetItemText(iItem, ZLC_TIME, sz);

		sz.Format(_T("%d%%"), fh.m_uUncomprSize ? fh.m_uComprSize * 100 / fh.m_uUncomprSize : 0);
		m_files.SetItemText(iItem, ZLC_RATIO, sz);
/************************************** : by VK at 08.10.2005 3:11:30 **\
		sz.Format(_T("%lu"), fh.m_uCrc32);
		m_files.SetItemText(iItem, ZLC_CRC, sz);

		DWORD uAttr = fh.GetOriginalAttributes();
		sz = uAttr & FILE_ATTRIBUTE_READONLY ? _T('r') : _T('-');
		sz += uAttr & FILE_ATTRIBUTE_ARCHIVE ? _T('a') : _T('-');
		sz += uAttr & FILE_ATTRIBUTE_HIDDEN ? _T('h') : _T('-');
		sz += uAttr & FILE_ATTRIBUTE_SYSTEM ? _T('s') : _T('-');
		m_files.SetItemText(iItem, ZLC_ATTR, sz);
\************************************** : by VK at 08.10.2005 3:11:37 **/
		CString szComment = (LPCTSTR)fh.GetComment();
		sz = (szComment.GetLength() > 1024) ? szComment.Left(1024) +_T("...") : szComment;
		m_files.SetItemText(iItem, ZLC_COMMENT, sz);
    m_files.SetItemData(iItem, (DWORD)i);
		m_progress.SetPos(i + 1);
		m_progress.RedrawWindow();

	}
	//m_files.UpdateColumnWidths();
	m_progress.Hide();
}
/////////////////////////////////////////////////////////////////////////////
// CUnzipDlg message handlers
BOOL CUnzipDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  m_files.SetExtendedStyle(LVS_EX_FULLROWSELECT);

  m_listImageList.Create(IDIL_ZIPFILES, 16, 0, RGB(0xFF, 0, 0xFF));
  memset(&ZipSortOrder, 0, sizeof(ZipSortOrder));

/************************************** : by VK at 25.10.2005 22:45:41 **\
  CHeaderCtrl* pHeaderCtrl = m_files.GetHeaderCtrl();
  if ( pHeaderCtrl ) {
    m_hdrImageList.Create(IDIL_ZIPSORT, 16, 0, RGB(0xFF, 0, 0xFF));
    pHeaderCtrl->SetImageList(&m_hdrImageList);
  }
\************************************** : by VK at 25.10.2005 22:45:48 **/
  m_files.SetImageList( &m_listImageList, LVSIL_SMALL);

	m_files.InsertColumn(ZLC_FILENAME,  _T("Ім'я файлу"), LVCFMT_LEFT, 280 );
	m_files.InsertColumn(ZLC_SIZE,      _T("Розмір")    , LVCFMT_LEFT,  60 );
	m_files.InsertColumn(ZLC_TIME,      _T("Дата/Час")  , LVCFMT_LEFT, 120 );

  m_files.EnableSortIcon(true, ZLC_FILENAME);
  m_files.EnableSortIcon(true, ZLC_TIME);
  m_files.EnableSortIcon(true, ZLC_SIZE);
	m_files.InsertColumn(ZLC_RATIO,     _T("КЖ")        , LVCFMT_LEFT,  60 );
/************************************** : by VK at 08.10.2005 3:11:57 **\
	m_files.InsertColumn(ZLC_CRC,       _T("CRC")       , LVCFMT_LEFT,  60 );
	m_files.InsertColumn(ZLC_ATTR,      _T("Атр")       , LVCFMT_LEFT,  40 );
\************************************** : by VK at 08.10.2005 3:12:00 **/
	m_files.InsertColumn(ZLC_COMMENT,   _T("Примітка")  , LVCFMT_LEFT, 200 );

  if ( FileExists(m_szZip) ) {
    ArchiveOpen();
  }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUnzipDlg::OnColumnclickZipList(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  int nSortColumn = pNMListView->iSubItem;

  switch( ZipSortOrder[nSortColumn] ) {
    case SO_NONE:  ZipSortOrder[nSortColumn] = SO_ASC;  break;
    case SO_ASC:   ZipSortOrder[nSortColumn] = SO_DESC; break;
    case SO_DESC:  ZipSortOrder[nSortColumn] = SO_ASC;  break;
  }

  switch(pNMListView->iSubItem) {
    case ZLC_FILENAME:
    case ZLC_TIME:
    case ZLC_SIZE:
      m_files.SortItems(ZipSortResults, (DWORD)pNMListView->iSubItem);
  }
/************************************** : by VK at 10.10.2005 7:30:55 **\
  CHeaderCtrl* pHeaderCtrl = m_files.GetHeaderCtrl();
  if ( pHeaderCtrl ) {
    HDITEM hdItem;
    ZeroMemory(&hdItem, sizeof(hdItem));
    hdItem.mask = HDI_IMAGE;
    int nCols = pHeaderCtrl->GetItemCount();
    for( int i(0); i < nCols; i++ ) {
      pHeaderCtrl->GetItem(i, &hdItem);
      hdItem.fmt = hdItem.fmt & HDF_JUSTIFYMASK | HDF_IMAGE | HDF_STRING | HDF_BITMAP_ON_RIGHT;
      hdItem.iImage = 0;
      if ( i==pNMListView->iSubItem ) {
        hdItem.iImage = ZipSortOrder[nSortColumn];
      }
      pHeaderCtrl->SetItem(i, &hdItem);
    }
  }
\************************************** : by VK at 10.10.2005 7:30:59 **/
	*pResult = 0;
}

void CUnzipDlg::OnYes() {
  int nItem = m_files.GetNextItem(-1, LVNI_SELECTED);
  if ( nItem >= 0 ) {
/************************************** : by VK at 26.11.2005 10:07:06 **\
    CBrowseForFolder bf;
    bf.hWndOwner = m_hWnd;
    bf.strTitle = _T("Папка для разархівації");
    bf.strStartupDir = GetFilePath(m_szZip);
  	if ( bf.GetFolder(sz) ) {
\************************************** : by VK at 26.11.2005 10:07:08 **/
	  CString sz = GetFilePath(m_szZip);
    WORD wZipItem = (WORD)m_files.GetItemData(nItem);
    if ( m_zip.ExtractFile(wZipItem, sz, true) ) {
      CZipFileHeader fh;
		  m_zip.GetFileInfo(fh, (WORD)wZipItem);
      sz.Format(_T("Файл \"%s\\%s\" успішно відновлений."),
                GetFilePath(m_szZip), (LPCTSTR)fh.GetFileName());
      AfxGetMainWnd()->MessageBox(sz);
    }
  }
  EndDialog(IDYES);
}

BOOL CUnzipDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
	// TODO: Add your message handler code here and/or call default
  theApp.OnHelp(_T("Zip"));
	return TRUE;
	//return CDialog::OnHelpInfo(pHelpInfo);
}


void Unzip() {
  CUnzipDlg dlg(AfxGetMainWnd());
  dlg.m_szZip.Format(_T("%s\\DB\\eradb.zip"), GetModulePath() );
  if ( FileExists(dlg.m_szZip) ) {
    dlg.DoModal();
  }
}
