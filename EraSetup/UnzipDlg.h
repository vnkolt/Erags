#if !defined(AFX_UNZIPDLG_H__B8DB84E2_18B1_40D4_9364_8C7862C67899__INCLUDED_)
#define AFX_UNZIPDLG_H__B8DB84E2_18B1_40D4_9364_8C7862C67899__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UnzipDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUnzipDlg dialog

class CUnzipDlg : public CDialog
{
// Construction
public:
	CUnzipDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUnzipDlg)
	enum { IDD = IDD_UNZIPDLG };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnzipDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUnzipDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNZIPDLG_H__B8DB84E2_18B1_40D4_9364_8C7862C67899__INCLUDED_)
