#if !defined(AFX_DBCITIZENSHIPS_H__14FFA486_0A0B_41B8_AE93_5B0D0FFFC4CF__INCLUDED_)
#define AFX_DBCITIZENSHIPS_H__14FFA486_0A0B_41B8_AE93_5B0D0FFFC4CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBCitizenships.h : header file
//

#include "DBGridDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDBCitizenships dialog
class CDBCitizenships : public CDBGridDlg {
// Construction
public:
	CDBCitizenships(CWnd* pParent = NULL);   // standard constructor

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBCitizenships)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDBCitizenships)
	virtual BOOL OnInitDialog();
  afx_msg BOOL OnHelpInfo(HELPINFO*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBCITIZENSHIPS_H__14FFA486_0A0B_41B8_AE93_5B0D0FFFC4CF__INCLUDED_)
