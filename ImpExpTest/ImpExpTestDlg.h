// ImpExpTestDlg.h : header file
//

#if !defined(AFX_IMPEXPTESTDLG_H__5C9E8CD3_4F73_4934_A6AB_AC4DA8851381__INCLUDED_)
#define AFX_IMPEXPTESTDLG_H__5C9E8CD3_4F73_4934_A6AB_AC4DA8851381__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CImpExpTestDlg dialog

class CImpExpTestDlg : public CDialog
{
// Construction
public:
	CImpExpTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CImpExpTestDlg)
	enum { IDD = IDD_IMPEXPTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImpExpTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImpExpTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPEXPTESTDLG_H__5C9E8CD3_4F73_4934_A6AB_AC4DA8851381__INCLUDED_)
