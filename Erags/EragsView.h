// EragsView.h : interface of the CEragsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERAGSVIEW_H__E8C71CC2_03B0_4972_A094_ACCE0F4B6BA3__INCLUDED_)
#define AFX_ERAGSVIEW_H__E8C71CC2_03B0_4972_A094_ACCE0F4B6BA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEragsView : public CView
{
protected: // create from serialization only
	CEragsView();
	DECLARE_DYNCREATE(CEragsView)

// Attributes
public:
	CEragsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEragsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEragsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEragsView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in EragsView.cpp
inline CEragsDoc* CEragsView::GetDocument()
   { return (CEragsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERAGSVIEW_H__E8C71CC2_03B0_4972_A094_ACCE0F4B6BA3__INCLUDED_)
