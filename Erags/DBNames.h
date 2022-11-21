#if !defined(AFX_NAMESS_H__C2E72613_13BC_46AC_B7AA_1A1BDA4D82E6__INCLUDED_)
#define AFX_NAMESS_H__C2E72613_13BC_46AC_B7AA_1A1BDA4D82E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBStreets.h : header file
//

#include "DBGridDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CDBNames dialog
class CDBNames : public CDBGridDlg {
// Construction
public:
	CDBNames(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBNames)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

  LPCTSTR m_szFieldName;
  CString m_sTitle;
  LPCTSTR m_szColumnName;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBNames)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  BOOL  Load(LPCTSTR szTableName, LPCTSTR szField);

	// Generated message map functions
	//{{AFX_MSG(CDBNames)
	virtual BOOL OnInitDialog();
  afx_msg BOOL OnHelpInfo(HELPINFO*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAMESS_H__C2E72613_13BC_46AC_B7AA_1A1BDA4D82E6__INCLUDED_)
