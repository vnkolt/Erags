// EraSetupDlg.h : header file
//

#if !defined(AFX_ERASETUPDLG_H__193EA481_A6D6_4B59_9107_19D639B41CC4__INCLUDED_)
#define AFX_ERASETUPDLG_H__193EA481_A6D6_4B59_9107_19D639B41CC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEraSetupDlg dialog

class CEraSetupDlg : public CDialog
{
// Construction
public:
	CEraSetupDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEraSetupDlg)
	enum { IDD = IDD_ERASETUP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEraSetupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERASETUPDLG_H__193EA481_A6D6_4B59_9107_19D639B41CC4__INCLUDED_)
