#if !defined(AFX_DIVORCEPAGE_H__D6FD43ED_60E0_4A65_A4F6_634A2439BFD5__INCLUDED_)
#define AFX_DIVORCEPAGE_H__D6FD43ED_60E0_4A65_A4F6_634A2439BFD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DivorcePage.h : header file
//

#include "NewWizPage.h"
#include "WizEdit.h"
#include "WizComboBox.h"


/////////////////////////////////////////////////////////////////////////////
// CDivorcePage dialog

class CDivorcePage : public CNewWizPage
{
// Construction
public:
	CDivorcePage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDivorcePage)
	enum { IDD = IDW_DIVORCE };
	CWizEdit	m_edtSeriaDeath;
	CWizEdit	m_edtSeriaChange;
	CWizEdit	m_edtSeriaDivorce;
	CWizEdit	m_edtSingleChild;
	CWizEdit	m_edtNoChildren;
	//}}AFX_DATA

  CFont       m_Font;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDivorcePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

  virtual LRESULT OnWizardNext();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDivorcePage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIVORCEPAGE_H__D6FD43ED_60E0_4A65_A4F6_634A2439BFD5__INCLUDED_)
