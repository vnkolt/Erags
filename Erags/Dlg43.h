#if !defined(AFX_DLG43_H__1FA2AC8A_BAED_4B0B_84EB_1839C10952F7__INCLUDED_)
#define AFX_DLG43_H__1FA2AC8A_BAED_4B0B_84EB_1839C10952F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg43.h : header file
//

#include "DialogEx.h"
#include "..\Controls\EraControls.h"

/////////////////////////////////////////////////////////////////////////////
// CDlg43 dialog

class CDlg43 : public CDialogEx
{
// Construction
public:
	CDlg43(int nDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg43)
	enum { IDD = IDD_DLG43 };
	CEraNameEdit	m_To;
	CEraEdit	    m_Number;
  CEraNameEdit	m_About;
	//}}AFX_DATA

  int     m_nDoc;
  BOOL    m_fSex;
  static  CString m_sTo;
  static  CString m_sNumber;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg43)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg43)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG43_H__1FA2AC8A_BAED_4B0B_84EB_1839C10952F7__INCLUDED_)
