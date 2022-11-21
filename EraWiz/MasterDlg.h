#if !defined(AFX_MASTERDLG_H__A612DFBB_27AF_4B90_A02C_0C3C266622FC__INCLUDED_)
#define AFX_MASTERDLG_H__A612DFBB_27AF_4B90_A02C_0C3C266622FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MasterDlg.h : header file
//

#include "NewWizDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CMasterDlg dialog

class CMasterDlg : public CNewWizDialog
{
// Construction
public:
	CMasterDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMasterDlg)
	enum { IDD = IDD_WIZARD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMasterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMasterDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MASTERDLG_H__A612DFBB_27AF_4B90_A02C_0C3C266622FC__INCLUDED_)
