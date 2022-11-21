// ETTestDlg.h : header file
//

#if !defined(AFX_ETTESTDLG_H__AB997C36_9EEA_4F23_A94E_848664670E03__INCLUDED_)
#define AFX_ETTESTDLG_H__AB997C36_9EEA_4F23_A94E_848664670E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CETTestDlg dialog

class CETTestDlg : public CDialog
{
// Construction
public:
	CETTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CETTestDlg)
	enum { IDD = IDD_ETTEST_DIALOG };
	CListCtrl	m_List;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CETTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CETTestDlg)
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

#endif // !defined(AFX_ETTESTDLG_H__AB997C36_9EEA_4F23_A94E_848664670E03__INCLUDED_)
