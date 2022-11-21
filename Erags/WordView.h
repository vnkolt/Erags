#if !defined(AFX_WORDVIEW_H__C04663A0_F352_4377_9A9D_DF948E7C2452__INCLUDED_)
#define AFX_WORDVIEW_H__C04663A0_F352_4377_9A9D_DF948E7C2452__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WordView.h : header file
//

#include "..\MSO\msword8.h"
//#include "msword9.h"

/////////////////////////////////////////////////////////////////////////////
// CWordView view

class CWordCntrItem;

class CWordView : public CView
{
protected: // create from serialization only
  CWordView();
  DECLARE_DYNCREATE(CWordView)

// Attributes
public:
  CWordDocument* GetDocument();
  // m_pSelection holds the selection to the current CXOfficeCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
  //  of objects that are not CXOfficeCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
  CWordCntrItem* m_pSelection;
  long           m_Percentage;
  long           m_PageCount;
  BOOL           m_fShowTextBoundaries;
  CDWordArray    m_CommandBars;

// Operations
public:
  void  RefreshBars(HWND hParent);
  void  RefreshMsoCommandBars();
  BOOL  WasCommandBarVisible(long lIndex);
  void  ShowCommandBars(Word::_Document* pDoc, BOOL fShow);
  BOOL  IsChecked(UINT id);
  void  CheckUncheck(UINT id, BYTE fState);
  bool  DoWordCommand(WPARAM wParam, LPARAM lParam=0);
  void  OnOnSelendOkScale();
  CWnd* GetWordWnd();

// Overrides
	// ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CWordView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	//}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CWordView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  //{{AFX_MSG(CWordView)
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnEnabledCmd(CCmdUI* pCmdUI);
	afx_msg void OnEnableExcel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnZoomIn();
	afx_msg void OnUpdateZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnZoomOut();
	afx_msg void OnGridLines();
  afx_msg void OnToolbars();
  afx_msg void OnExcel();
  afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in XOfficeView.cpp
inline CWordDocument* CWordView::GetDocument()
   { return (CWordDocument*)m_pDocument; }
#endif



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDVIEW_H__C04663A0_F352_4377_9A9D_DF948E7C2452__INCLUDED_)
