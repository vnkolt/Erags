#if !defined(AFX_ERAPATHPAGE_H__1C53C308_56A1_426E_A762_70FF820D29EB__INCLUDED_)
#define AFX_ERAPATHPAGE_H__1C53C308_56A1_426E_A762_70FF820D29EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EraPathPage.h : header file
//
#include "NewWizPage.h"

#include "WizButton.h"
#include "WizEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CEraPathPage dialog
class CEraPathPage : public CNewWizPage {
// Construction
public:
	CEraPathPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEraPathPage)
	enum { IDD = IDD_ERAPATH };
	CWizButton	m_SelPath;
	CWizEdit	  m_EraPath;
	CWizEdit	  m_EraGroup;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraPathPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void    ResetFreeSpace();
  LRESULT OnWizardNext();

	// Generated message map functions
	//{{AFX_MSG(CEraPathPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelpath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERAPATHPAGE_H__1C53C308_56A1_426E_A762_70FF820D29EB__INCLUDED_)
