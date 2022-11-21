#if !defined(AFX_ABCDLG_H__8CF86777_C960_4241_8D84_EC60576524AF__INCLUDED_)
#define AFX_ABCDLG_H__8CF86777_C960_4241_8D84_EC60576524AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ABCDlg.h : header file
//

#include "DialogEx.h"
#include "..\Controls\TCToolBar\TCImageList.h"

/////////////////////////////////////////////////////////////////////////////
// CABCDlg dialog
class CABCDlg : public CDialogEx {
// Construction
public:
	CABCDlg(BOOL fHideNewSurname, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CABCDlg)
	enum { IDD = IDD_ABC };
  CXButtonXP        m_CheckBox1;
  CXButtonXP        m_CheckBox2;
	//}}AFX_DATA
  CTCImageList      m_CheckBoxIL;
  BOOL              m_fHideNewSurname;
  CString           m_AfterTitle;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CABCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CABCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABCDLG_H__8CF86777_C960_4241_8D84_EC60576524AF__INCLUDED_)
