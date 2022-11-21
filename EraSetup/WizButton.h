#if !defined(AFX_WIZBUTTON_H__1F905281_8D72_46B4_9E21_85D4C58BBC6E__INCLUDED_)
#define AFX_WIZBUTTON_H__1F905281_8D72_46B4_9E21_85D4C58BBC6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizButton window

class CWizButton : public CButton
{
// Construction
public:
	CWizButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizButton)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZBUTTON_H__1F905281_8D72_46B4_9E21_85D4C58BBC6E__INCLUDED_)
