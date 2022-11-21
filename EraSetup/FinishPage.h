#if !defined(AFX_FINISHPAGE_H__96AD70D1_5482_41AB_B74D_3B00E061850B__INCLUDED_)
#define AFX_FINISHPAGE_H__96AD70D1_5482_41AB_B74D_3B00E061850B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FinishPage.h : header file
//
#include "AutoRichEditCtrl.h"
#include "NewWizPage.h"

/////////////////////////////////////////////////////////////////////////////
// CFinishPage dialog

class CFinishPage : public CDialog
{
// Construction
public:
	CFinishPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFinishPage)
	enum { IDD = IDD_FINISH };
	CAutoRichEditCtrl	m_RichText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFinishPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFinishPage)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINISHPAGE_H__96AD70D1_5482_41AB_B74D_3B00E061850B__INCLUDED_)
