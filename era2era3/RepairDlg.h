#if !defined(AFX_REPAIRDLG_H__E1569767_EEFE_43C1_B4A9_E4895F8F42BD__INCLUDED_)
#define AFX_REPAIRDLG_H__E1569767_EEFE_43C1_B4A9_E4895F8F42BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RepairDlg.h : header file
//
#include "..\Controls\BkgndCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CRepairDlg dialog

class CRepairDlg : public CDialogBG
{
// Construction
public:
	CRepairDlg(LPCTSTR szFieldName, LPCTSTR szActName,
             int nAct, COleDateTime DateReg,
             LPCTSTR szNameOf, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRepairDlg)
	enum { IDD = IDD_REPAIR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

  CString       m_szFieldName, m_szActName;
  int           m_nAct;
  COleDateTime  m_DateReg;
  CString       m_NameOf;
  CString       m_szFieldValue; 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRepairDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRepairDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeWhat();
	afx_msg void OnNomore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPAIRDLG_H__E1569767_EEFE_43C1_B4A9_E4895F8F42BD__INCLUDED_)
