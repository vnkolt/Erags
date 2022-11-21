// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__BFE37A8F_FFB6_4F87_BDC9_86A94E5725CD__INCLUDED_)
#define AFX_CHILDFRM_H__BFE37A8F_FFB6_4F87_BDC9_86A94E5725CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Controls\NewMenu.h"
#include "LocalSearchBar.h"

#define CChildFrameBase CNewMDIChildWnd

class CChildFrame : public CChildFrameBase {
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:
  int             m_nFormID;
  //CFormView*      m_pForm;
  CView*          m_pView;
  CLocalSearchBar m_LocalSearchBar;
protected:
  CString GetBarStateName(LPCTSTR szBarStateName);
  BOOL    VerifyBarState(LPCTSTR lpszProfileName);
  void    RestoreFrame();
// Operations
public:
/*
  void  SaveBarState(LPCTSTR szBarStateName);
  void  LoadBarState(LPCTSTR szBarStateName);
*/

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
  virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnUpdateFindin(CCmdUI* pCmdUI);
	afx_msg void OnFindin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__BFE37A8F_FFB6_4F87_BDC9_86A94E5725CD__INCLUDED_)
