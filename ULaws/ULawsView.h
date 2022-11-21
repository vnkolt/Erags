// This is part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
//
// ULawsView.h : interface of the CULawsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ULAWSVIEW_H__47FF4085_CE1B_11D0_BEB6_00C04FC99F83__INCLUDED_)
#define AFX_ULAWSVIEW_H__47FF4085_CE1B_11D0_BEB6_00C04FC99F83__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CULawsDoc;

class CULawsView : public CHtmlView
{
protected: // create from serialization only
	CULawsView();
	DECLARE_DYNCREATE(CULawsView)

// Attributes
public:
	CULawsDoc* GetDocument();

// Operations
public:
  void GoHome();
  void GoToUrl(LPCTSTR lpszUrl);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CULawsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL
	void OnTitleChange(LPCTSTR lpszText);
	void OnDocumentComplete(LPCTSTR lpszUrl);
	void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags,
		LPCTSTR lpszTargetFrameName, CByteArray& baPostedData,
		LPCTSTR lpszHeaders, BOOL* pbCancel);

// Implementation
public:
	virtual ~CULawsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CULawsView)
	afx_msg void OnGoBack();
	afx_msg void OnGoForward();
//  afx_msg void OnSearch();
	afx_msg void OnGoGoogle();
  afx_msg void OnGoYandex();
  afx_msg void OnGoMeta();
	afx_msg void OnGoStartPage();
	afx_msg void OnViewStop();
	afx_msg void OnViewRefresh();
	afx_msg void OnHelpWebTutorial();
	afx_msg void OnHelpOnlineSupport();
	afx_msg void OnHelpMicrosoftOnTheWebFreeStuff();
	afx_msg void OnHelpMicrosoftOnTheWebFrequentlyAskedQuestions();
	afx_msg void OnHelpMicrosoftOnTheWebGetFasterInternetAccess();
	afx_msg void OnHelpMicrosoftOnTheWebMicrosoftHomePage();
	afx_msg void OnHelpMicrosoftOnTheWebSearchTheWeb();
	afx_msg void OnHelpMicrosoftOnTheWebSendFeedback();
	afx_msg void OnHelpMicrosoftOnTheWebInternetStartPage();
	afx_msg void OnHelpMicrosoftOnTheWebBestOfTheWeb();
	afx_msg void OnViewFontsLargest();
	afx_msg void OnViewFontsLarge();
	afx_msg void OnViewFontsMedium();
	afx_msg void OnViewFontsSmall();
	afx_msg void OnViewFontsSmallest();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CULawsView* g_pULawsView;

#ifndef _DEBUG  // debug version in ULawsView.cpp
inline CULawsDoc* CULawsView::GetDocument()
   { return (CULawsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ULAWSVIEW_H__47FF4085_CE1B_11D0_BEB6_00C04FC99F83__INCLUDED_)
