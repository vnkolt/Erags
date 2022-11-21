#if !defined(AFX_EXTSTATUSBARCOMBOBOX_H__6791D685_8621_4608_8937_77206970221D__INCLUDED_)
#define AFX_EXTSTATUSBARCOMBOBOX_H__6791D685_8621_4608_8937_77206970221D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtStatusBarComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtStatusBarComboBox window

class CExtStatusBarComboBox : public CComboBoxEx
{
// Construction
public:
	CExtStatusBarComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtStatusBarComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExtStatusBarComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExtStatusBarComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

  virtual void PostNcDestroy(){
    delete this;
  }

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTSTATUSBARCOMBOBOX_H__6791D685_8621_4608_8937_77206970221D__INCLUDED_)
