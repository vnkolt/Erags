// EraABCView.h : interface of the CEraABCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERAABCVIEW_H__0074241B_59EE_48E5_B5E6_E5B6A6E608FE__INCLUDED_)
#define AFX_ERAABCVIEW_H__0074241B_59EE_48E5_B5E6_E5B6A6E608FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define ABC_BIRTH_VIEW_ID      (int)('Birt')
#define ABC_MARRIAGE_VIEW_ID   (int)('Marr')
#define ABC_DIVORCE_VIEW_ID    (int)('Divo')
#define ABC_CHANGE_VIEW_ID     (int)('Chan')
#define ABC_DEATH_VIEW_ID      (int)('Deat')

class CABCList;
class CFormABC;

class CEraABCView : public CSplitterWnd {
	DECLARE_DYNCREATE(CEraABCView)
public:
	CEraABCView();

// Operations
public:
  CABCList* GetListCtrl();
  CFormABC* GetForm();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraABCView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraABCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEraABCView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERAABCVIEW_H__0074241B_59EE_48E5_B5E6_E5B6A6E608FE__INCLUDED_)
