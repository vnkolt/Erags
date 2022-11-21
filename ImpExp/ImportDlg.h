#if !defined(AFX_IMPORTDLG_H__31BB0BDA_4260_4408_BAC2_AFC936D9017B__INCLUDED_)
#define AFX_IMPORTDLG_H__31BB0BDA_4260_4408_BAC2_AFC936D9017B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportDlg.h : header file
//
//#include "..\Controls\FileEditCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CImportDlg dialog

class CImportDlg : public CDialog
{
// Construction
public:
	CImportDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImportDlg)
	enum { IDD = IDD_IMPORT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImportDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnOpenFileDlg();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTDLG_H__31BB0BDA_4260_4408_BAC2_AFC936D9017B__INCLUDED_)
