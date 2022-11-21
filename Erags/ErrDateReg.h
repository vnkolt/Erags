#if !defined(AFX_ERRDATEREG_H__4BDC50A1_76DB_47F5_A58A_65616BF862EA__INCLUDED_)
#define AFX_ERRDATEREG_H__4BDC50A1_76DB_47F5_A58A_65616BF862EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrDateReg.h : header file
//

#include "DialogEx.h"
/////////////////////////////////////////////////////////////////////////////
// CErrDateReg dialog
class CErrDateReg : public CDialogEx {
// Construction
public:
	CErrDateReg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CErrDateReg)
	enum { IDD = IDD_ERRDATEREG };
	CStaticBG m_ErrMsg;
	//}}AFX_DATA
  int m_ErrYear;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrDateReg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CErrDateReg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRDATEREG_H__4BDC50A1_76DB_47F5_A58A_65616BF862EA__INCLUDED_)
