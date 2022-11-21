#if !defined(AFX_WIZCOMBOBOX_H__59F4D48E_BB0B_41C6_8C5D_D968990C8B9E__INCLUDED_)
#define AFX_WIZCOMBOBOX_H__59F4D48E_BB0B_41C6_8C5D_D968990C8B9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizComboBox window

class CWizComboBox : public CComboBox
{
// Construction
public:
	CWizComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizComboBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZCOMBOBOX_H__59F4D48E_BB0B_41C6_8C5D_D968990C8B9E__INCLUDED_)
