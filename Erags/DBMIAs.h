#if !defined(AFX_DBMIAS_H__C2E42662_13BC_46AC_B7AA_1A1BDA4D82E6__INCLUDED_)
#define AFX_DBMIAS_H__C2E42662_13BC_46AC_B7AA_1A1BDA4D82E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DBMIAs.h : header file
//

#include "DBGridDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDBMIAs dialog
class CDBMIAs : public CDBGridDlg {
// Construction
public:
	CDBMIAs(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBMIAs)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBMIAs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDBMIAs)
	virtual BOOL OnInitDialog();
  afx_msg BOOL OnHelpInfo(HELPINFO*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBMIAS_H__C2E42662_13BC_46AC_B7AA_1A1BDA4D82E6__INCLUDED_)
