#if !defined(AFX_WIZEDIT_H__38FF1A81_C2B8_472C_AB66_A477801E0564__INCLUDED_)
#define AFX_WIZEDIT_H__38FF1A81_C2B8_472C_AB66_A477801E0564__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizEdit window

class CWizEdit : public CEdit
{
// Construction
public:
	CWizEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizEdit)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZEDIT_H__38FF1A81_C2B8_472C_AB66_A477801E0564__INCLUDED_)
