#if !defined(AFX_AGREEMENTPAGE_H__C9CCF585_C1FD_41BE_898D_1B490F4AC196__INCLUDED_)
#define AFX_AGREEMENTPAGE_H__C9CCF585_C1FD_41BE_898D_1B490F4AC196__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AgreementPage.h : header file
//
#include "NewWizPage.h"
#include "AutoRichEditCtrl.h"


/////////////////////////////////////////////////////////////////////////////
// CAgreementPage dialog

class CAgreementPage : public CNewWizPage
{
// Construction
public:
	CAgreementPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAgreementPage)
	enum { IDD = IDD_AGREEMENT };
	CAutoRichEditCtrl	m_reAgreement;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAgreementPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual LRESULT OnWizardNext();

	// Generated message map functions
	//{{AFX_MSG(CAgreementPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AGREEMENTPAGE_H__C9CCF585_C1FD_41BE_898D_1B490F4AC196__INCLUDED_)
