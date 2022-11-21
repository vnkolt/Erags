// TreeEditorView.h : interface of the CGeoTreeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOTREEVIEW_H__6E51006D_1A14_11D8_9063_00409533E092__INCLUDED_)
#define AFX_GEOTREEVIEW_H__6E51006D_1A14_11D8_9063_00409533E092__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GeoTreeCtrl.h"

class CGeoTreeView : public CView
{
protected: // create from serialization only
	CGeoTreeView();
	DECLARE_DYNCREATE(CGeoTreeView)

// Attributes
public:
	CGeoTreeDoc*  GetDocument();
	CGeoTreeCtrl  m_etc;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoTreeView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGeoTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGeoTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GeoTreeView.cpp
inline CGeoTreeDoc* CGeoTreeView::GetDocument()
   { return (CGeoTreeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEOTREEVIEW_H__6E51006D_1A14_11D8_9063_00409533E092__INCLUDED_)
