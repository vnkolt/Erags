#if !defined(__FOLDERTREEBAR_H__)
#define __FOLDERTREEBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FolderTreeBar.h : header file
//

#include "..\Controls\scbarg.h"

#include "FileTreeCtrl.h"

class CEraTreeFileCtrl : public CTreeFileCtrl
{
	DECLARE_DYNCREATE(CEraTreeFileCtrl)
protected:
  void OpenEraFile(HTREEITEM hItem);
  //Just override one method for demonstration purposes
  virtual void OnSelectionChanged(NM_TREEVIEW*, const CString&);
	DECLARE_MESSAGE_MAP()
  afx_msg BOOL OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
  //{{AFX_MSG(CEraTreeFileCtrl)
	afx_msg void OnUp();
	afx_msg void OnUpdateUp(CCmdUI* pCmdUI);
  afx_msg void OnOpen();
	//{{AFX_MSG(CEraTreeFileCtrl)
};


/////////////////////////////////////////////////////////////////////////////
// CFolderTreeBar window

#ifndef baseCFolderTreeBar
#define baseCFolderTreeBar CSizingControlBarG
#endif

class CFolderTreeBar : public baseCFolderTreeBar
{
// Construction
public:
	CFolderTreeBar();

// Attributes
public:

// Operations
public:
  CString GetRootDBFolder(LPCTSTR szPath);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFolderTreeBar)
		protected:
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFolderTreeBar();

protected:
  CEraTreeFileCtrl  m_FileTree;

	// Generated message map functions
protected:
	//{{AFX_MSG(CFolderTreeBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(__FOLDERTREEBAR_H__)
