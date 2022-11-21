#if !defined(AFX_ADDRSNDLG_H__CD10DFB1_DF83_49FC_8562_3C0A6936D506__INCLUDED_)
#define AFX_ADDRSNDLG_H__CD10DFB1_DF83_49FC_8562_3C0A6936D506__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddRsnDlg.h : header file
//

#include "DialogEx.h"
#include "..\Controls\EraControls.h"


/////////////////////////////////////////////////////////////////////////////
// CAddRsnDlg dialog

class CAddRsnDlg : public CDialogEx
{
// Construction
public:
	CAddRsnDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddRsnDlg)
	enum { IDD = IDD_ADD_REASON };
	CEraEdit	m_Pseudo;
	CEraEdit	m_Reason;
	//}}AFX_DATA
	CString   m_sPseudo;
  CString   m_sReason;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddRsnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddRsnDlg)
	afx_msg void OnChangePseudo();
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDRSNDLG_H__CD10DFB1_DF83_49FC_8562_3C0A6936D506__INCLUDED_)
