#if !defined(AFX_FINISHDLG_H__C497298E_4A97_4FA9_9608_0BAF1947929A__INCLUDED_)
#define AFX_FINISHDLG_H__C497298E_4A97_4FA9_9608_0BAF1947929A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FinishDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFinishDlg dialog

class CFinishDlg : public CDialog
{
// Construction
public:
	CFinishDlg(LPCTSTR szOutFolder, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFinishDlg)
	enum { IDD = IDD_FINISH };
	BOOL	m_fOpenFolder;
	BOOL	m_fCloseApp;
	//}}AFX_DATA

  CString m_szOutFolder;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFinishDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFinishDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINISHDLG_H__C497298E_4A97_4FA9_9608_0BAF1947929A__INCLUDED_)
