#if !defined(AFX_STREETS_H__C2E42662_13BC_46AC_B7AA_1A1BDA4D82E6__INCLUDED_)
#define AFX_STREETS_H__C2E42662_13BC_46AC_B7AA_1A1BDA4D82E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBStreets.h : header file
//

#include "DBGridDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CDBStreets dialog
class CDBStreets : public CDBGridDlg {
// Construction
public:
	CDBStreets(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBStreets)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBStreets)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDBStreets)
	virtual BOOL OnInitDialog();
  afx_msg BOOL OnHelpInfo(HELPINFO*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STREETS_H__C2E42662_13BC_46AC_B7AA_1A1BDA4D82E6__INCLUDED_)
