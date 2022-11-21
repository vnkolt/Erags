#if !defined(AFX_YESNODLG_H__EB25F001_EC05_11D3_AC53_E311A2E21678__INCLUDED_)
#define AFX_YESNODLG_H__EB25F001_EC05_11D3_AC53_E311A2E21678__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YesNoDlg.h : header file
//

#include "DialogEx.h"

/////////////////////////////////////////////////////////////////////////////
// CYesNoDlg dialog

class CYesNoDlg : public CDialogEx
{
// Construction
public:
	CYesNoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CYesNoDlg)
	enum { IDD = IDD_YESNO };
	CString	m_sMessage;
	CString	m_sQuestion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYesNoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CYesNoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BOOL PASCAL EXPORT YNDlg(CWnd* pParent, LPCTSTR szMessage, LPCTSTR szQuestion);
BOOL PASCAL EXPORT YNDlg(CWnd* pParent, UINT uMessageID, UINT uQuestionID);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_YESNODLG_H__EB25F001_EC05_11D3_AC53_E311A2E21678__INCLUDED_)
