#if !defined(AFX_WIZTREECTRL_H__C7027099_55D7_4855_89FB_87780278915D__INCLUDED_)
#define AFX_WIZTREECTRL_H__C7027099_55D7_4855_89FB_87780278915D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizTreeCtrl window

class CWizTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CWizTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizTreeCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZTREECTRL_H__C7027099_55D7_4855_89FB_87780278915D__INCLUDED_)
