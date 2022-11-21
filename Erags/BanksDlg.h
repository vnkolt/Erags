#if !defined(AFX_BANKSDLG_H__574D5010_AD73_4947_9F7A_C2936AC04310__INCLUDED_)
#define AFX_BANKSDLG_H__574D5010_AD73_4947_9F7A_C2936AC04310__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BanksDlg.h : header file
//
#include "DialogEx.h"
#include "..\Controls\GridCtrl\GridCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CBanksDlg dialog

class CBanksDlg : public CDialogEx
{
// Construction
public:
	CBanksDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBanksDlg)
	enum { IDD = IDD_BANKS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

  CGridCtrl m_Grid;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBanksDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBanksDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BANKSDLG_H__574D5010_AD73_4947_9F7A_C2936AC04310__INCLUDED_)
