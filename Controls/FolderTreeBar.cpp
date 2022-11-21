// FolderTreeBar.cpp : implementation file
//

#include "stdafx.h"
#include "FolderTreeBar.h"

#include "FileTreeView.h"
#include "..\Common\FHelpers.h"

#if defined(_ERAGS)
#include "..\Erags\Erags.h"
#elif defined(_ERAABC)
#include "..\EraABC\EraABC.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CEraTreeFileCtrl, CTreeFileCtrl)
BEGIN_MESSAGE_MAP(CEraTreeFileCtrl, CTreeFileCtrl)
	//{{AFX_MSG_MAP(CEraTreeFileCtrl)
	ON_COMMAND(ID_TREEFILECTRL_UP, OnUp)
	ON_UPDATE_COMMAND_UI(ID_TREEFILECTRL_UP, OnUpdateUp)
	ON_COMMAND(ID_TREEFILECTRL_OPEN, OnOpen)
	//}}AFX_MSG_MAP
  ON_NOTIFY_REFLECT_EX(NM_DBLCLK, OnDblclk)
  ON_NOTIFY_REFLECT_EX(TVN_ENDLABELEDIT, OnEndLabelEdit)
END_MESSAGE_MAP()
void CEraTreeFileCtrl::OnUp() {
  HTREEITEM hSelItem = GetSelectedItem();
  if ( hSelItem ) {
    HTREEITEM hParentItem = GetParentItem(hSelItem);
    if ( hParentItem )
      Select(hParentItem, TVGN_CARET);
    else {
      CString sRoot = GetRootFolder();
      int nSlash = sRoot.ReverseFind('\\');
      if ( nSlash > 0 ) {
        CString sNewRoot = sRoot.Left(nSlash);
        int nLength = sNewRoot.GetLength();
        if ( nLength > 2 || (2==nLength && sNewRoot.GetAt(1)==':') ) {
          SetRootFolder(sNewRoot);
        }
      }
      else {
        SetRootFolder(_T(""));
        SetDisplayNetwork(TRUE);
        SetShowMyComputer(TRUE);
        PopulateTree();
      }
    }
  }
}
void CEraTreeFileCtrl::OnUpdateUp(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
/************************************** : by VK at 16.02.2005 2:35:59 **\
  HTREEITEM hSelItem = GetSelectedItem();
  if (hSelItem)
  {
    if (m_bAllowProperties)
    {
      CTreeFileCtrlItemInfo* pItem = (CTreeFileCtrlItemInfo*) GetItemData(hSelItem);
      ASSERT(pItem);
      if (pItem->m_bNetworkNode)
      { 
        if (pItem->m_pNetResource)
          pCmdUI->Enable(pItem->m_pNetResource->dwDisplayType == RESOURCEDISPLAYTYPE_SERVER ||
                         pItem->m_pNetResource->dwDisplayType == RESOURCEDISPLAYTYPE_SHARE);
        else
          pCmdUI->Enable(FALSE);
      }
      else
        pCmdUI->Enable(TRUE);
    }
    else
      pCmdUI->Enable(FALSE);
  }
  else
    pCmdUI->Enable(FALSE);
\************************************** : by VK at 16.02.2005 2:36:04 **/
}
void CEraTreeFileCtrl::OpenEraFile(HTREEITEM hItem) {
  if ( hItem && !HasPlusButton(hItem)) {
    CTreeFileCtrlItemInfo* pItem = (CTreeFileCtrlItemInfo*) GetItemData(hItem);
    if ( pItem->m_bFileItem ) {
      CString sFile = ItemToPath(hItem);
      #ifdef _ERAGS
      theApp.m_pWordTemplate->CloseAllDocuments(FALSE);
      #endif
      theApp.OpenDocumentFile(sFile);
    }
  }
}
void CEraTreeFileCtrl::OnOpen() {
  OpenEraFile( GetSelectedItem() );
}
void CEraTreeFileCtrl::OnSelectionChanged(NM_TREEVIEW*, const CString& sPath) {
  //For demonstration purposes, we will change the document title
/************************************** : by VK at 27.01.2005 22:18:07 **\
  CFileTreeView* pParent = (CFileTreeView*) GetParent();
  ASSERT(pParent);
  pParent->GetDocument()->SetTitle(sPath);
\************************************** : by VK at 27.01.2005 22:18:10 **/
}
BOOL CEraTreeFileCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) {
  HTREEITEM hItem = GetSelectedItem();
  CPoint pt = GetCurrentMessage()->pt;
  ScreenToClient(&pt);

	if (hItem && (hItem == HitTest(pt))) {
    OpenEraFile(hItem);
	}
  *pResult = 0;
  return FALSE;
}
BOOL CEraTreeFileCtrl::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) {
  TV_DISPINFO* pDispInfo = (TV_DISPINFO*)pNMHDR;
  if (pDispInfo->item.pszText) {
    CString sText = pDispInfo->item.pszText;
    sText.Replace(TCHAR('²'), TCHAR('I'));
    sText.Replace(TCHAR('³'), TCHAR('i'));
    strcpy(pDispInfo->item.pszText, sText);
  }
  return CTreeFileCtrl::OnEndLabelEdit(pNMHDR, pResult);
}

/////////////////////////////////////////////////////////////////////////////
// CFolderTreeBar
CFolderTreeBar::CFolderTreeBar() {
/************************************** : by VK at 02.02.2005 2:24:33 **\
  m_pFileTreeView = NULL;
\************************************** : by VK at 02.02.2005 2:24:35 **/
}

CFolderTreeBar::~CFolderTreeBar()
{
}


BEGIN_MESSAGE_MAP(CFolderTreeBar, baseCFolderTreeBar)
	//{{AFX_MSG_MAP(CFolderTreeBar)
	ON_WM_CREATE()
  ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CString CFolderTreeBar::GetRootDBFolder(LPCTSTR szPath) {
  CString sRoot = szPath;
  if ( sRoot.GetLength() <= 3 )
    return sRoot;
  CString sPath = GetFilePath(sRoot);
  CString s;
  s.Format(_T("%s\\Helpers.mdb"), sPath);
  if ( FileExists(s) )
    return GetFilePath(s);
  return GetRootDBFolder(sPath);
}
/////////////////////////////////////////////////////////////////////////////
// CFolderTreeBar message handlers
int CFolderTreeBar::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (baseCFolderTreeBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

  CString sDBPath = theApp.GetProfileString(_T("Settings"), _T("Database"));
  if ( sDBPath.GetLength()==0 ) {
    sDBPath = GetModulePath();
    CString s;
    s.Format(_T("%s\\DB"),sDBPath);
    if ( FileExists(s) ) {
      sDBPath = s;
    }
    else
      sDBPath = GetRootDBFolder(sDBPath);
  }
  else
    sDBPath = GetRootDBFolder(sDBPath);

  m_FileTree.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_TABSTOP|TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_EDITLABELS|TVS_SHOWSELALWAYS, CRect(0,0,0,0), this, IDC_FOLDER_TREE);
  m_FileTree.SetFileNameMask("*.er3");
  m_FileTree.SetShowRootedFolder(TRUE);
  m_FileTree.SetRootFolder(sDBPath);
  m_FileTree.SetShowFiles(TRUE);
  m_FileTree.PopulateTree();
  m_FileTree.SetAllowRename(TRUE);
  m_FileTree.SetAllowDelete(TRUE);

/************************************** : by VK 02.02.2005 at 14:19:16 **\
  m_FileTree.SetDisplayNetwork(TRUE);
  m_FileTree.SetShowRootedFolder(TRUE);
  m_FileTree.SetFileNameMask("*.er3");
//  m_FileTree.SetRootFolder(sDBPath);
  m_FileTree.SetShowMyComputer(TRUE);
  m_FileTree.SetShowDriveLabels(TRUE);
  m_FileTree.SetSelectedPath(sDBPath, TRUE);
//  m_FileTree.SetSelectedPath(sDBPath, TRUE);

//  m_FileTree.SetShowFiles(TRUE);
\************************************** : by VK 02.02.2005 at 14:19:19 **/

	return 0;
}

void CFolderTreeBar::OnDestroy() {
  m_FileTree.DestroyWindow();
  baseCFolderTreeBar::OnDestroy();
}
LRESULT CFolderTreeBar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
	// TODO: Add your specialized code here and/or call the base class
  if ((WM_NOTIFY == message) && (((NMHDR*)lParam)->idFrom == IDC_FOLDER_TREE)) {
    // a WM_NOTIFY coming from our tree control; use CWnd's WindowProc cause CDialogBar's will dispatch to our tree control twice
    return CWnd::WindowProc(message, wParam, lParam);
  }
	return baseCFolderTreeBar::WindowProc(message, wParam, lParam);
}
