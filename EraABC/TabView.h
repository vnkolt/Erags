#if !defined(AFX_TABVIEW_H__4832E56A_A788_45B7_A5EE_A5D711BE86FA__INCLUDED_)
#define AFX_TABVIEW_H__4832E56A_A788_45B7_A5EE_A5D711BE86FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabView.h : header file
//

#include "EraABCView.h"

/////////////////////////////////////////////////////////////////////////////
// CTabView view

class CTabView : public CView {
protected:
	CTabView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTabView)

// Attributes
private:
  CEraABCDoc*  GetDocument();

  CTabCtrl*    m_pTabCtrl;
  CEraABCView  m_BirthView;
  CEraABCView  m_MarriageView;
  CEraABCView  m_DivorceView;
  CEraABCView  m_ChangeView;
  CEraABCView  m_DeathView;

  CImageList   m_ImageList;
  CPtrArray    m_Tabs;
  int          m_nCurTab;

// Operations
public:
  CTabCtrl* GetTabCtrl() { return m_pTabCtrl; }
  CFormABC* GetActiveForm();
  void      SetActiveForm(int nTab=-1);
private:
  void      RecalcLayout();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabView)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnBirth();
	afx_msg void OnMarriage();
	afx_msg void OnDivorce();
	afx_msg void OnChange();
	afx_msg void OnDeath();
	afx_msg void OnUpdateBirth(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DemoView.cpp
inline CEraABCDoc* CTabView::GetDocument()
   { return (CEraABCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABVIEW_H__4832E56A_A788_45B7_A5EE_A5D711BE86FA__INCLUDED_)
