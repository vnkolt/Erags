#if !defined(AFX_FILETREEVIEW_H__BD99D435_2A3F_4D0B_8ECF_E99900F5825B__INCLUDED_)
#define AFX_FILETREEVIEW_H__BD99D435_2A3F_4D0B_8ECF_E99900F5825B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileTreeView.h : header file
//

#include "FileTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CFileTreeView view

class CFileTreeView : public CView {
	DECLARE_DYNCREATE(CFileTreeView)
protected: // create from serialization only
	CFileTreeView();
public:
  CEraTreeFileCtrl m_TreeFile;
/************************************** : by VK at 27.01.2005 22:39:17 **\
	CTesttfileviewDoc* GetDocument();
\************************************** : by VK at 27.01.2005 22:39:19 **/
	//{{AFX_VIRTUAL(CFileTreeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL


public:
	virtual ~CFileTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CFileTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnToolsAllowdelete();
	afx_msg void OnUpdateToolsAllowdelete(CCmdUI* pCmdUI);
	afx_msg void OnToolsAllowopen();
	afx_msg void OnUpdateToolsAllowopen(CCmdUI* pCmdUI);
	afx_msg void OnToolsAllowrename();
	afx_msg void OnUpdateToolsAllowrename(CCmdUI* pCmdUI);
	afx_msg void OnToolsAllowsproperties();
	afx_msg void OnUpdateToolsAllowsproperties(CCmdUI* pCmdUI);
	afx_msg void OnToolsShowfiles();
	afx_msg void OnUpdateToolsShowfiles(CCmdUI* pCmdUI);
	afx_msg void OnToolsAllowdragdrop();
	afx_msg void OnUpdateToolsAllowdragdrop(CCmdUI* pCmdUI);
	afx_msg void OnToolsHidecdrom();
	afx_msg void OnUpdateToolsHidecdrom(CCmdUI* pCmdUI);
	afx_msg void OnToolsHidefixed();
	afx_msg void OnUpdateToolsHidefixed(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideramdisks();
	afx_msg void OnUpdateToolsHideramdisks(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideremovable();
	afx_msg void OnUpdateToolsHideremovable(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideremote();
	afx_msg void OnUpdateToolsHideremote(CCmdUI* pCmdUI);
	afx_msg void OnToolsFilenamemask();
	afx_msg void OnToolsHidehidden();
	afx_msg void OnUpdateToolsHidehidden(CCmdUI* pCmdUI);
	afx_msg void OnToolsHidearchive();
	afx_msg void OnUpdateToolsHidearchive(CCmdUI* pCmdUI);
	afx_msg void OnToolsHidecompressed();
	afx_msg void OnUpdateToolsHidecompressed(CCmdUI* pCmdUI);
	afx_msg void OnToolsHidesystem();
	afx_msg void OnUpdateToolsHidesystem(CCmdUI* pCmdUI);
	afx_msg void OnToolsHidetemporary();
	afx_msg void OnUpdateToolsHidetemporary(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideencrypted();
	afx_msg void OnUpdateToolsHideencrypted(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideoffline();
	afx_msg void OnUpdateToolsHideoffline(CCmdUI* pCmdUI);
	afx_msg void OnToolsHidereadonly();
	afx_msg void OnUpdateToolsHidereadonly(CCmdUI* pCmdUI);
	afx_msg void OnToolsHidereparsepoint();
	afx_msg void OnUpdateToolsHidereparsepoint(CCmdUI* pCmdUI);
	afx_msg void OnToolsHidesparse();
	afx_msg void OnUpdateToolsHidesparse(CCmdUI* pCmdUI);
	afx_msg void OnToolsAutorefresh();
	afx_msg void OnUpdateToolsAutorefresh(CCmdUI* pCmdUI);
	afx_msg void OnToolsSetrootfolder();
	afx_msg void OnDestroy();
	afx_msg void OnToolsHidenetwork();
	afx_msg void OnUpdateToolsHidenetwork(CCmdUI* pCmdUI);
	afx_msg void OnToolsShowsharedfolders();
	afx_msg void OnUpdateToolsShowsharedfolders(CCmdUI* pCmdUI);
	afx_msg void OnToolsShowallnetworkitems();
	afx_msg void OnUpdateToolsShowallnetworkitems(CCmdUI* pCmdUI);
	afx_msg void OnToolsShownetworkprinters();
	afx_msg void OnUpdateToolsShownetworkprinters(CCmdUI* pCmdUI);
	afx_msg void OnToolsShownetworkshares();
	afx_msg void OnUpdateToolsShownetworkshares(CCmdUI* pCmdUI);
	afx_msg void OnToolsShowdrivelabels();
	afx_msg void OnUpdateToolsShowdrivelabels(CCmdUI* pCmdUI);
	afx_msg void OnToolsHidemycomputer();
	afx_msg void OnUpdateToolsHidemycomputer(CCmdUI* pCmdUI);
	afx_msg void OnToolsShowrootedfolder();
	afx_msg void OnUpdateToolsShowrootedfolder(CCmdUI* pCmdUI);
	afx_msg void OnToolsSetselectedpath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETREEVIEW_H__BD99D435_2A3F_4D0B_8ECF_E99900F5825B__INCLUDED_)
