#if !defined(AFX_MEDICSPAGE_H__42BF8E1C_35B9_436D_93B2_7E196265C6F3__INCLUDED_)
#define AFX_MEDICSPAGE_H__42BF8E1C_35B9_436D_93B2_7E196265C6F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedicsPage.h : header file
//

#include "NewWizPage.h"
#include "WizEdit.h"
#include "WizComboBox.h"

#define MAX_MEDCONTROLS 11

/////////////////////////////////////////////////////////////////////////////
// CMedicsPage dialog

class CMedicsPage : public CNewWizPage
{
// Construction
public:
	CMedicsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMedicsPage)
	enum { IDD = IDW_SETMEDICS };
	CWizEdit	m_Pseudo[MAX_MEDCONTROLS];
	CWizEdit	m_Hospital[MAX_MEDCONTROLS];
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedicsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  virtual void OnSetActive();
  virtual LRESULT OnWizardNext();
  virtual BOOL OnWizardFinish();

	// Generated message map functions
	//{{AFX_MSG(CMedicsPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDICSPAGE_H__42BF8E1C_35B9_436D_93B2_7E196265C6F3__INCLUDED_)
