// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__6C6A03C5_54F9_4C15_9429_6635A78FEBC3__INCLUDED_)
#define AFX_MAINFRM_H__6C6A03C5_54F9_4C15_9429_6635A78FEBC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Controls\ExtStatusControlBar.h"
#include "..\Controls\CPPTooltip\PPTooltip.h"
#include "..\Controls\NewMenuBar.h"
#include "..\Controls\NewToolBar.h"
#include "..\Controls\NewStatusBar.h"

#include "..\Controls\BtnST.h"
#include "..\Controls\FolderTreeBar.h"

#include "..\Controls\TCToolBar\TCToolBar.h"

#include "MainDlgBar.h"
#include "RFindFrm.h"

class CExtStatusBarLabel;

void RemoveForID(CListCtrl* pList, long lParam);

class CEraToolBar : public CToolBar {
	DECLARE_DYNAMIC(CEraToolBar)
public:
  CEraToolBar();

// Data members:
public:
  LPCTSTR    m_szName;
	CPPToolTip m_tooltip;
  void       SetTooltips();
  void       HideTooltip();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraToolBar)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CEraToolBar();

	//{{AFX_MSG(CEraToolBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
  afx_msg BOOL OnHelpInfo(HELPINFO*);
};

class CPreviewBar : public CEraToolBar {
public:
  CComboBox m_cmbScale;
public:
  CPreviewBar();

  CFont m_Font;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewBar)
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CPreviewBar();

	// Generated message map functions
public:

	//{{AFX_MSG(CPreviewBar)
	//}}AFX_MSG
	afx_msg void OnSelendOkScale();

	DECLARE_MESSAGE_MAP()
};

#define CMainFrameBase  CNewMDIFrameWnd

class CMainFrame : public CMainFrameBase {
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
  CFrameWnd*    m_pBirthFrame;
  CFrameWnd*    m_pMarriageFrame;
  CFrameWnd*    m_pDivorceFrame;
  CFrameWnd*    m_pDeathFrame;
  CFrameWnd*    m_pChangeFrame;
  BOOL          m_bDragHelp;

  CFolderTreeBar     m_FileTreeBar;
  CGlobalSearchBar   m_GlobalSearchBar;

protected:
  bool	        m_bShowOnce;

// Operations
private:
  BOOL VerifyBarState(LPCTSTR lpszProfileName);
public:
	void OnRegistration(UINT nCmdID);

  void      EnablePreviewBar(bool fEnable);
  BOOL      GetCommandButtonRect(UINT idBtn, RECT* pRect);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
  void    DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
public:
  CExtStatusControlBar   m_wndStatusBar;
  CImageList             m_MsgImageList;
  CExtStatusBarLabel*    m_pWndLabel;
  CStatic                m_wndMsgIcon;
  HICON*                 m_pMsgIcons;
  int                    m_nMsgIcons;


  CPreviewBar    m_wndPreviewBar;
  CTCToolBar     m_wndBrowserBar;
  CPPToolTip     m_tooltip;
  CNewMenuBar    m_wndMenuBar;
  CNewMenu       m_SysMenu;
//  CNewToolBar    m_wndToolBar;
	CReBarBG       m_wndReBar;
	CMainDlgBar    m_wndDlgBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnClose();
	afx_msg void OnDestroy();
  afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUpdateFolderTree(CCmdUI* pCmdUI);
	afx_msg void OnFolderTree();
	afx_msg void OnFind();
  afx_msg void OnNames();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnUpdateWhatIsIt(CCmdUI* pCmdUI);
	afx_msg void OnWhatIsIt();
	afx_msg void OnUpdateRegistration(CCmdUI* pCmdUI);
#ifndef FREE_LICENCE
	afx_msg void OnRegDlg();
#endif

  afx_msg void OnRegBirth();
  afx_msg void OnRegMarriage();
  afx_msg void OnRegDivorce();
  afx_msg void OnRegChange();
  afx_msg void OnRegChaned();
  afx_msg void OnRegDeath();
  
  afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
  afx_msg LRESULT OnSetMessageString(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysColorChange();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
#if _MSC_VER < 1300
  afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
#else
  afx_msg void OnActivateApp(BOOL bActive, DWORD hTask);
#endif
	//}}AFX_MSG
  LRESULT OnDisplayChanged(WPARAM wParam, LPARAM lParam);
  LRESULT OnEmMessage(WPARAM wParam, LPARAM lParam);
  afx_msg void OnToggleInsert();
  afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
  afx_msg void OnUpdateFind(CCmdUI* pCmdUI);
  afx_msg BOOL OnHelpInfo(HELPINFO*);
  afx_msg LRESULT OnDoZip(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__6C6A03C5_54F9_4C15_9429_6635A78FEBC3__INCLUDED_)
