// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__A89F5032_816B_463A_82D9_BC8847EA298B__INCLUDED_)
#define AFX_MAINFRM_H__A89F5032_816B_463A_82D9_BC8847EA298B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Controls\ExtStatusControlBar.h"
#include "..\Controls\FolderTreeBar.h"
#include "..\Controls\TCToolBar\TCToolBar.h"
#include "..\Controls\NewMenuBar.h"

class CTabView;
class CFormABC;
class CExtStatusBarLabel;
class CExtStatusBarComboBox;

#define CMainFrameBase  CNewFrameWnd

class CMainFrame : public CNewFrameWnd {
	DECLARE_DYNCREATE(CMainFrame)
public:
	CMainFrame();

// Attributes
private:
  bool	          m_bShowOnce;
  CSplitterWnd    m_wndSplitter;
  CFolderTreeBar  m_FileTreeBar;
  CBitmap         m_bmNormal;
  CBitmap         m_bmHot;
  CBitmap         m_bmDisabled;
public:
  CTabView*       m_pTabView;

// Operations
public:
  BOOL      VerifyBarState(LPCTSTR lpszProfileName);
  CFormABC* GetActiveForm();
protected:
  void RestoreFrame();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	virtual CDocument* GetActiveDocument();
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
  virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
  CExtStatusControlBar   m_wndStatusBar;
  CTCToolBar             m_wndToolBar;
  CNewMenuBar            m_wndMenuBar;

  CImageList             m_MsgImageList;
  CExtStatusBarLabel*    m_pWndLabel;
  CStatic                m_wndMsgIcon;
  CExtStatusBarComboBox* m_pWndMessageBox;
  HICON*                 m_pMsgIcons;
  int                    m_nMsgIcons;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUpdateFolderTree(CCmdUI* pCmdUI);
	afx_msg void OnFolderTree();
	afx_msg void OnUpdateWhatIsIt(CCmdUI* pCmdUI);
	afx_msg void OnWhatIsIt();
  afx_msg BOOL OnHelpInfo(HELPINFO*);
	afx_msg void OnDestroy();
	afx_msg void OnBirth();
	afx_msg void OnMarriage();
	afx_msg void OnDivorce();
	afx_msg void OnChange();
	afx_msg void OnDeath();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
  afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
  afx_msg LRESULT OnSetMessageString(WPARAM wParam, LPARAM lParam);
  afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
  afx_msg void OnToggleInsert();
	//}}AFX_MSG
  LRESULT OnEmMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A89F5032_816B_463A_82D9_BC8847EA298B__INCLUDED_)
