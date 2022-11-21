#if !defined(AFX_BROWSER_H__21701576_7C6C_47FD_A29A_93FD6228A8B6__INCLUDED_)
#define AFX_BROWSER_H__21701576_7C6C_47FD_A29A_93FD6228A8B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Browser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBrowser html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CBrowser : public CHtmlView
{
protected:
	CBrowser();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBrowser)

// html Data
public:
	//{{AFX_DATA(CBrowser)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBrowser();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CBrowser)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSER_H__21701576_7C6C_47FD_A29A_93FD6228A8B6__INCLUDED_)
