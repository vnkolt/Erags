#if !defined(AFX_SETTYPEPAGE_H__09B592B7_29BC_45BE_95A7_DD3DE9CBB3A9__INCLUDED_)
#define AFX_SETTYPEPAGE_H__09B592B7_29BC_45BE_95A7_DD3DE9CBB3A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetTypePage.h : header file
//

#include "NewWizPage.h"

/////////////////////////////////////////////////////////////////////////////
// CSetTypePage dialog

class CSetTypePage : public CNewWizPage
{
// Construction
public:
	CSetTypePage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetTypePage)
	enum { IDD = IDW_SETRAGSTYPE };
	CListBox	m_TypeList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetTypePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetTypePage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTYPEPAGE_H__09B592B7_29BC_45BE_95A7_DD3DE9CBB3A9__INCLUDED_)
