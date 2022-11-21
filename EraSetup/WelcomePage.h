#if !defined(AFX_WELCOMEPAGE_H__92F866C4_F728_4809_AF45_16FF815A8DFE__INCLUDED_)
#define AFX_WELCOMEPAGE_H__92F866C4_F728_4809_AF45_16FF815A8DFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WelcomePage.h : header file
//

#include "NewWizPage.h"

/////////////////////////////////////////////////////////////////////////////
// CWelcomePage dialog

class CWelcomePage : public CNewWizPage
{
// Construction
public:
	CWelcomePage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWelcomePage)
	enum { IDD = IDD_WELCOME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWelcomePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWelcomePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioUkr();
	afx_msg void OnRadioRus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOMEPAGE_H__92F866C4_F728_4809_AF45_16FF815A8DFE__INCLUDED_)
