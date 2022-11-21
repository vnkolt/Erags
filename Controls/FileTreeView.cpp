// FileTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"

#include "FileTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define REG_STR_SECTION1 _T("Settings")
#define REG_STR_ENTRY1_1 _T("Last Path")
#define REG_STR_ENTRY1_2 _T("Expanded")

IMPLEMENT_DYNCREATE(CABCTreeFileCtrl, CTreeFileCtrl)
BEGIN_MESSAGE_MAP(CABCTreeFileCtrl, CTreeFileCtrl)
	//{{AFX_MSG_MAP(CABCTreeFileCtrl)
	//}}AFX_MSG_MAP
  ON_NOTIFY_REFLECT_EX(NM_DBLCLK, OnDblclk)
END_MESSAGE_MAP()
void CABCTreeFileCtrl::OnSelectionChanged(NM_TREEVIEW*, const CString& sPath) {
  //For demonstration purposes, we will change the document title
/************************************** : by VK at 27.01.2005 22:18:07 **\
  CFileTreeView* pParent = (CFileTreeView*) GetParent();
  ASSERT(pParent);
  pParent->GetDocument()->SetTitle(sPath);
\************************************** : by VK at 27.01.2005 22:18:10 **/
}
BOOL CABCTreeFileCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) {
  HTREEITEM hItem = GetSelectedItem();
  CPoint pt = GetCurrentMessage()->pt;
  ScreenToClient(&pt);

	if (hItem && (hItem == HitTest(pt))) {
		if (!HasPlusButton(hItem)) {
      CString sFile = ItemToPath(hItem);
      //theApp.OpenEraFile(sFile);
      //theApp.OpenDocument(
      theApp.OpenDocumentFile(sFile);
    }
	}
  *pResult = 0;
  return FALSE;
}

IMPLEMENT_DYNCREATE(CFileTreeView, CView)

BEGIN_MESSAGE_MAP(CFileTreeView, CView)
	//{{AFX_MSG_MAP(CFileTreeView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_TOOLS_ALLOWDELETE, OnToolsAllowdelete)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ALLOWDELETE, OnUpdateToolsAllowdelete)
	ON_COMMAND(ID_TOOLS_ALLOWOPEN, OnToolsAllowopen)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ALLOWOPEN, OnUpdateToolsAllowopen)
	ON_COMMAND(ID_TOOLS_ALLOWRENAME, OnToolsAllowrename)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ALLOWRENAME, OnUpdateToolsAllowrename)
	ON_COMMAND(ID_TOOLS_ALLOWSPROPERTIES, OnToolsAllowsproperties)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ALLOWSPROPERTIES, OnUpdateToolsAllowsproperties)
	ON_COMMAND(ID_TOOLS_SHOWFILES, OnToolsShowfiles)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWFILES, OnUpdateToolsShowfiles)
	ON_COMMAND(ID_TOOLS_ALLOWDRAGDROP, OnToolsAllowdragdrop)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ALLOWDRAGDROP, OnUpdateToolsAllowdragdrop)
	ON_COMMAND(ID_TOOLS_HIDECDROM, OnToolsHidecdrom)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDECDROM, OnUpdateToolsHidecdrom)
	ON_COMMAND(ID_TOOLS_HIDEFIXED, OnToolsHidefixed)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEFIXED, OnUpdateToolsHidefixed)
	ON_COMMAND(ID_TOOLS_HIDERAMDISKS, OnToolsHideramdisks)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDERAMDISKS, OnUpdateToolsHideramdisks)
	ON_COMMAND(ID_TOOLS_HIDEREMOVABLE, OnToolsHideremovable)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEREMOVABLE, OnUpdateToolsHideremovable)
	ON_COMMAND(ID_TOOLS_HIDEREMOTE, OnToolsHideremote)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEREMOTE, OnUpdateToolsHideremote)
	ON_COMMAND(ID_TOOLS_FILENAMEMASK, OnToolsFilenamemask)
	ON_COMMAND(ID_TOOLS_HIDEHIDDEN, OnToolsHidehidden)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEHIDDEN, OnUpdateToolsHidehidden)
	ON_COMMAND(ID_TOOLS_HIDEARCHIVE, OnToolsHidearchive)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEARCHIVE, OnUpdateToolsHidearchive)
	ON_COMMAND(ID_TOOLS_HIDECOMPRESSED, OnToolsHidecompressed)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDECOMPRESSED, OnUpdateToolsHidecompressed)
	ON_COMMAND(ID_TOOLS_HIDESYSTEM, OnToolsHidesystem)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDESYSTEM, OnUpdateToolsHidesystem)
	ON_COMMAND(ID_TOOLS_HIDETEMPORARY, OnToolsHidetemporary)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDETEMPORARY, OnUpdateToolsHidetemporary)
	ON_COMMAND(ID_TOOLS_HIDEENCRYPTED, OnToolsHideencrypted)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEENCRYPTED, OnUpdateToolsHideencrypted)
	ON_COMMAND(ID_TOOLS_HIDEOFFLINE, OnToolsHideoffline)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEOFFLINE, OnUpdateToolsHideoffline)
	ON_COMMAND(ID_TOOLS_HIDEREADONLY, OnToolsHidereadonly)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEREADONLY, OnUpdateToolsHidereadonly)
	ON_COMMAND(ID_TOOLS_HIDEREPARSEPOINT, OnToolsHidereparsepoint)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEREPARSEPOINT, OnUpdateToolsHidereparsepoint)
	ON_COMMAND(ID_TOOLS_HIDESPARSE, OnToolsHidesparse)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDESPARSE, OnUpdateToolsHidesparse)
	ON_COMMAND(ID_TOOLS_AUTOREFRESH, OnToolsAutorefresh)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_AUTOREFRESH, OnUpdateToolsAutorefresh)
	ON_COMMAND(ID_TOOLS_SETROOTFOLDER, OnToolsSetrootfolder)
	ON_WM_DESTROY()
	ON_COMMAND(ID_TOOLS_HIDENETWORK, OnToolsHidenetwork)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDENETWORK, OnUpdateToolsHidenetwork)
	ON_COMMAND(ID_TOOLS_SHOWSHAREDFOLDERS, OnToolsShowsharedfolders)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWSHAREDFOLDERS, OnUpdateToolsShowsharedfolders)
	ON_COMMAND(ID_TOOLS_SHOWALLNETWORKITEMS, OnToolsShowallnetworkitems)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWALLNETWORKITEMS, OnUpdateToolsShowallnetworkitems)
	ON_COMMAND(ID_TOOLS_SHOWNETWORKPRINTERS, OnToolsShownetworkprinters)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWNETWORKPRINTERS, OnUpdateToolsShownetworkprinters)
	ON_COMMAND(ID_TOOLS_SHOWNETWORKSHARES, OnToolsShownetworkshares)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWNETWORKSHARES, OnUpdateToolsShownetworkshares)
	ON_COMMAND(ID_TOOLS_SHOWDRIVELABELS, OnToolsShowdrivelabels)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWDRIVELABELS, OnUpdateToolsShowdrivelabels)
	ON_COMMAND(ID_TOOLS_HIDEMYCOMPUTER, OnToolsHidemycomputer)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEMYCOMPUTER, OnUpdateToolsHidemycomputer)
	ON_COMMAND(ID_TOOLS_SHOWROOTEDFOLDER, OnToolsShowrootedfolder)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWROOTEDFOLDER, OnUpdateToolsShowrootedfolder)
	ON_COMMAND(ID_TOOLS_SETSELECTEDPATH, OnToolsSetselectedpath)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()


CFileTreeView::CFileTreeView()
{
}

CFileTreeView::~CFileTreeView()
{
}

BOOL CFileTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CFileTreeView::OnDraw(CDC* /*pDC*/)
{
/************************************** : by VK at 27.01.2005 22:38:52 **\
	CTesttfileviewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
\************************************** : by VK at 27.01.2005 22:38:54 **/
}

BOOL CFileTreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CFileTreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CFileTreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CFileTreeView::AssertValid() const
{
	CView::AssertValid();
}

void CFileTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

/************************************** : by VK at 27.01.2005 22:39:01 **\
CTesttfileviewDoc* CFileTreeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTesttfileviewDoc)));
	return (CTesttfileviewDoc*)m_pDocument;
  return NULL;
}
\************************************** : by VK at 27.01.2005 22:39:03 **/
#endif //_DEBUG

int CFileTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
  //Create the tree view
  CRect r;
  if (!m_TreeFile.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_EDITLABELS | TVS_SHOWSELALWAYS, r, this, 100))
    return -1;
    
   m_TreeFile.SetAllowRename(TRUE);

	return 0;
}

void CFileTreeView::OnSize(UINT nType, int cx, int cy) 
{
  //Let the parent class do its thing
	CView::OnSize(nType, cx, cy);

  //Let the tree control occupy all the space of the client area
  CRect rClient;  
  GetClientRect(&rClient);
  m_TreeFile.MoveWindow(rClient);
}


void CFileTreeView::OnSetFocus(CWnd* pOldWnd) 
{
  //Let the parent class do its thing
	CView::OnSetFocus(pOldWnd);
	
  m_TreeFile.SetFocus();
}

void CFileTreeView::OnToolsAllowdelete() 
{
  m_TreeFile.SetAllowDelete(!m_TreeFile.GetAllowDelete());	
}

void CFileTreeView::OnUpdateToolsAllowdelete(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetAllowDelete());	
}

void CFileTreeView::OnToolsAllowopen() 
{
  m_TreeFile.SetAllowOpen(!m_TreeFile.GetAllowOpen());		
}

void CFileTreeView::OnUpdateToolsAllowopen(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetAllowOpen());		
}

void CFileTreeView::OnToolsAllowrename() 
{
  m_TreeFile.SetAllowRename(!m_TreeFile.GetAllowRename());			
}

void CFileTreeView::OnUpdateToolsAllowrename(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetAllowRename());		
}

void CFileTreeView::OnToolsAllowsproperties() 
{
  m_TreeFile.SetAllowProperties(!m_TreeFile.GetAllowProperties());			
}

void CFileTreeView::OnUpdateToolsAllowsproperties(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetAllowProperties());		
}

void CFileTreeView::OnToolsShowfiles() 
{
  m_TreeFile.SetShowFiles(!m_TreeFile.GetShowFiles());			
}

void CFileTreeView::OnUpdateToolsShowfiles(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetShowFiles());		
}

void CFileTreeView::OnInitialUpdate() 
{
  //Let the parent class do its thing
	CView::OnInitialUpdate();

  //Set the selected path in the tree control	
  CWinApp* pApp = AfxGetApp();
  CString sSelPath = pApp->GetProfileString(REG_STR_SECTION1, REG_STR_ENTRY1_1, _T("C:\\"));
  m_TreeFile.SetRootFolder(theApp.m_strDBRoot);
  m_TreeFile.SetShowRootedFolder(TRUE);
  m_TreeFile.SetShowFiles(TRUE);
  m_TreeFile.SetFileNameMask(_T("*.er3"));
  //m_TreeFile.SetDriveHideFlags(m_TreeFile.GetDriveHideFlags() & ~DRIVE_ATTRIBUTE_CDROM);
  //CString sSelPath = theApp.m_strDBRoot;
  BOOL bExpanded = pApp->GetProfileInt(REG_STR_SECTION1, REG_STR_ENTRY1_2, FALSE);
  m_TreeFile.SetSelectedPath(sSelPath, bExpanded);
  m_TreeFile.PopulateTree();
}

void CFileTreeView::OnToolsAllowdragdrop() 
{
	m_TreeFile.SetAllowDragDrop(!m_TreeFile.GetAllowDragDrop());		
}

void CFileTreeView::OnUpdateToolsAllowdragdrop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetAllowDragDrop());		
}

BOOL CFileTreeView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
  //Give the control first crack
  if (m_TreeFile.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    return TRUE;	
	return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CFileTreeView::OnToolsHidecdrom() 
{
  if (m_TreeFile.GetDriveHideFlags() & DRIVE_ATTRIBUTE_CDROM)
	  m_TreeFile.SetDriveHideFlags(m_TreeFile.GetDriveHideFlags() & ~DRIVE_ATTRIBUTE_CDROM);
	else
    m_TreeFile.SetDriveHideFlags(m_TreeFile.GetDriveHideFlags() | DRIVE_ATTRIBUTE_CDROM);
}

void CFileTreeView::OnUpdateToolsHidecdrom(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetDriveHideFlags() & DRIVE_ATTRIBUTE_CDROM);
}

void CFileTreeView::OnToolsHidefixed() 
{
  if (m_TreeFile.GetDriveHideFlags() & DRIVE_ATTRIBUTE_FIXED)
	  m_TreeFile.SetDriveHideFlags(m_TreeFile.GetDriveHideFlags() & ~DRIVE_ATTRIBUTE_FIXED);
	else
    m_TreeFile.SetDriveHideFlags(m_TreeFile.GetDriveHideFlags() | DRIVE_ATTRIBUTE_FIXED);
}

void CFileTreeView::OnUpdateToolsHidefixed(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetDriveHideFlags() & DRIVE_ATTRIBUTE_FIXED);
}

void CFileTreeView::OnToolsHideramdisks() 
{
  if (m_TreeFile.GetDriveHideFlags() & DRIVE_ATTRIBUTE_RAMDISK)
	  m_TreeFile.SetDriveHideFlags(m_TreeFile.GetDriveHideFlags() & ~DRIVE_ATTRIBUTE_RAMDISK);
	else
    m_TreeFile.SetDriveHideFlags(m_TreeFile.GetDriveHideFlags() | DRIVE_ATTRIBUTE_RAMDISK);
}

void CFileTreeView::OnUpdateToolsHideramdisks(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetDriveHideFlags() & DRIVE_ATTRIBUTE_RAMDISK);
}

void CFileTreeView::OnToolsHideremovable() 
{
  if (m_TreeFile.GetDriveHideFlags() & DRIVE_ATTRIBUTE_REMOVABLE)
	  m_TreeFile.SetDriveHideFlags(m_TreeFile.GetDriveHideFlags() & ~DRIVE_ATTRIBUTE_REMOVABLE);
	else
    m_TreeFile.SetDriveHideFlags(m_TreeFile.GetDriveHideFlags() | DRIVE_ATTRIBUTE_REMOVABLE);
}

void CFileTreeView::OnUpdateToolsHideremovable(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetDriveHideFlags() & DRIVE_ATTRIBUTE_REMOVABLE);
}

void CFileTreeView::OnToolsHideremote() 
{
  if (m_TreeFile.GetDriveHideFlags() & DRIVE_ATTRIBUTE_REMOTE)
	  m_TreeFile.SetDriveHideFlags(m_TreeFile.GetDriveHideFlags() & ~DRIVE_ATTRIBUTE_REMOTE);
	else
    m_TreeFile.SetDriveHideFlags(m_TreeFile.GetDriveHideFlags() | DRIVE_ATTRIBUTE_REMOTE);
}

void CFileTreeView::OnUpdateToolsHideremote(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetDriveHideFlags() & DRIVE_ATTRIBUTE_REMOTE);
}

void CFileTreeView::OnToolsFilenamemask() 
{
/************************************** : by VK at 27.01.2005 22:50:43 **\
  CFilenameMaskDlg dlg;
  dlg.m_sMask = m_TreeFile.GetFileNameMask();
  if (dlg.DoModal() == IDOK)
    m_TreeFile.SetFileNameMask(dlg.m_sMask);
\************************************** : by VK at 27.01.2005 22:50:46 **/
}

void CFileTreeView::OnToolsHidehidden() 
{
  if (m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_HIDDEN)
	  m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() & ~FILE_ATTRIBUTE_HIDDEN);
	else
    m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() | FILE_ATTRIBUTE_HIDDEN);
}

void CFileTreeView::OnUpdateToolsHidehidden(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_HIDDEN);
}

void CFileTreeView::OnToolsHidearchive() 
{
  if (m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_ARCHIVE)
	  m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() & ~FILE_ATTRIBUTE_ARCHIVE);
	else
    m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() | FILE_ATTRIBUTE_ARCHIVE);
}

void CFileTreeView::OnUpdateToolsHidearchive(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_ARCHIVE);
}

void CFileTreeView::OnToolsHidecompressed() 
{
  if (m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_COMPRESSED)
	  m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() & ~FILE_ATTRIBUTE_COMPRESSED);
	else
    m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() | FILE_ATTRIBUTE_COMPRESSED);
}

void CFileTreeView::OnUpdateToolsHidecompressed(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_COMPRESSED);
}

void CFileTreeView::OnToolsHidesystem() 
{
  if (m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_SYSTEM)
	  m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() & ~FILE_ATTRIBUTE_SYSTEM);
	else
    m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() | FILE_ATTRIBUTE_SYSTEM);
}

void CFileTreeView::OnUpdateToolsHidesystem(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_SYSTEM);
}

void CFileTreeView::OnToolsHidetemporary() 
{
  if (m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_TEMPORARY)
	  m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() & ~FILE_ATTRIBUTE_TEMPORARY);
	else
    m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() | FILE_ATTRIBUTE_TEMPORARY);
}

void CFileTreeView::OnUpdateToolsHidetemporary(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_TEMPORARY);
}

void CFileTreeView::OnToolsHideencrypted() 
{
  if (m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_ENCRYPTED)
	  m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() & ~FILE_ATTRIBUTE_ENCRYPTED);
	else
    m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() | FILE_ATTRIBUTE_ENCRYPTED);
}

void CFileTreeView::OnUpdateToolsHideencrypted(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_ENCRYPTED);
}

void CFileTreeView::OnToolsHideoffline() 
{
  if (m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_OFFLINE)
	  m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() & ~FILE_ATTRIBUTE_OFFLINE);
	else
    m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() | FILE_ATTRIBUTE_OFFLINE);
}

void CFileTreeView::OnUpdateToolsHideoffline(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_OFFLINE);
}

void CFileTreeView::OnToolsHidereadonly() 
{
  if (m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_READONLY)
	  m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() & ~FILE_ATTRIBUTE_READONLY);
	else
    m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() | FILE_ATTRIBUTE_READONLY);
}

void CFileTreeView::OnUpdateToolsHidereadonly(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_READONLY);
}

void CFileTreeView::OnToolsHidereparsepoint() 
{
  if (m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_REPARSE_POINT)
	  m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() & ~FILE_ATTRIBUTE_REPARSE_POINT);
	else
    m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() | FILE_ATTRIBUTE_REPARSE_POINT);
}

void CFileTreeView::OnUpdateToolsHidereparsepoint(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_REPARSE_POINT);
}

void CFileTreeView::OnToolsHidesparse() 
{
  if (m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_SPARSE_FILE)
	  m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() & ~FILE_ATTRIBUTE_SPARSE_FILE);
	else
    m_TreeFile.SetFileHideFlags(m_TreeFile.GetFileHideFlags() | FILE_ATTRIBUTE_SPARSE_FILE);
}

void CFileTreeView::OnUpdateToolsHidesparse(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TreeFile.GetFileHideFlags() & FILE_ATTRIBUTE_SPARSE_FILE);
}

void CFileTreeView::OnToolsAutorefresh() 
{
	m_TreeFile.SetAutoRefresh(!m_TreeFile.GetAutoRefresh());
}

void CFileTreeView::OnUpdateToolsAutorefresh(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_TreeFile.GetAutoRefresh());	
}

void CFileTreeView::OnToolsHidenetwork() 
{
  m_TreeFile.SetDisplayNetwork(!m_TreeFile.GetDisplayNetwork());	
}

void CFileTreeView::OnUpdateToolsHidenetwork(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!m_TreeFile.GetDisplayNetwork());
}

void CFileTreeView::OnToolsShowsharedfolders() 
{
  m_TreeFile.SetUsingDifferentIconForSharedFolders(!m_TreeFile.GetUsingDifferentIconForSharedFolders());	
}

void CFileTreeView::OnUpdateToolsShowsharedfolders(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_TreeFile.GetUsingDifferentIconForSharedFolders());
}

void CFileTreeView::OnToolsSetrootfolder() 
{
/************************************** : by VK at 27.01.2005 22:50:53 **\
  CRootFolderDlg dlg;
  dlg.m_sFolder = m_TreeFile.GetRootFolder();
  if (dlg.DoModal() == IDOK)
    m_TreeFile.SetRootFolder(dlg.m_sFolder);
\************************************** : by VK at 27.01.2005 22:50:56 **/
}

void CFileTreeView::OnDestroy() 
{
  //Remember the selected path, ready for the next time around
  CString sSelPath = m_TreeFile.GetSelectedPath();
  CWinApp* pApp = AfxGetApp();
  pApp->WriteProfileString(REG_STR_SECTION1, REG_STR_ENTRY1_1, sSelPath);
  BOOL bExpanded = m_TreeFile.IsExpanded(m_TreeFile.PathToItem(sSelPath));
  pApp->WriteProfileInt(REG_STR_SECTION1, REG_STR_ENTRY1_2, bExpanded);

  //Let the parent class do its thing
  m_TreeFile.DestroyWindow();
	CView::OnDestroy();
}

void CFileTreeView::OnToolsShowallnetworkitems() 
{
  m_TreeFile.SetNetworkItemTypes(RESOURCETYPE_ANY);
}

void CFileTreeView::OnUpdateToolsShowallnetworkitems(CCmdUI* pCmdUI) 
{
	DWORD dwTypes = m_TreeFile.GetNetworkItemTypes();
	pCmdUI->SetCheck(dwTypes == RESOURCETYPE_ANY);
}

void CFileTreeView::OnToolsShownetworkprinters() 
{
	m_TreeFile.SetNetworkItemTypes(RESOURCETYPE_PRINT);
}

void CFileTreeView::OnUpdateToolsShownetworkprinters(CCmdUI* pCmdUI) 
{
	DWORD dwTypes = m_TreeFile.GetNetworkItemTypes();
	pCmdUI->SetCheck(dwTypes == RESOURCETYPE_PRINT);
}

void CFileTreeView::OnToolsShownetworkshares() 
{
	m_TreeFile.SetNetworkItemTypes(RESOURCETYPE_DISK);
}

void CFileTreeView::OnUpdateToolsShownetworkshares(CCmdUI* pCmdUI) 
{
	DWORD dwTypes = m_TreeFile.GetNetworkItemTypes();
	pCmdUI->SetCheck(dwTypes & RESOURCETYPE_DISK);
}

void CFileTreeView::OnToolsShowdrivelabels() 
{
  m_TreeFile.SetShowDriveLabels(!m_TreeFile.GetShowDriveLabels());		
}

void CFileTreeView::OnUpdateToolsShowdrivelabels(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_TreeFile.GetShowDriveLabels());
}

void CFileTreeView::OnToolsHidemycomputer() 
{
	m_TreeFile.SetShowMyComputer(!m_TreeFile.GetShowMyComputer());
}

void CFileTreeView::OnUpdateToolsHidemycomputer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!m_TreeFile.GetShowMyComputer());
}

void CFileTreeView::OnToolsShowrootedfolder() 
{
	m_TreeFile.SetShowRootedFolder(!m_TreeFile.GetShowRootedFolder());
}

void CFileTreeView::OnUpdateToolsShowrootedfolder(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_TreeFile.GetShowRootedFolder());
}

void CFileTreeView::OnToolsSetselectedpath() 
{
/************************************** : by VK at 27.01.2005 22:51:02 **\
  CSelectedPathDlg dlg;
  dlg.m_sPath = m_TreeFile.GetSelectedPath();
  if (dlg.DoModal() == IDOK)
    m_TreeFile.SetSelectedPath(dlg.m_sPath);
\************************************** : by VK at 27.01.2005 22:51:05 **/
}

