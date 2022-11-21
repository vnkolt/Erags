// UninstallDlg.h : header file
//

#if !defined(AFX_UNINSTALLDLG_H__4E337450_C5A0_4A87_9101_8A068F5461DC__INCLUDED_)
#define AFX_UNINSTALLDLG_H__4E337450_C5A0_4A87_9101_8A068F5461DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUninstallDlg dialog

class CUninstallDlg : public CDialog
{
// Construction
public:
	CUninstallDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUninstallDlg)
	enum { IDD = IDD_UNINSTALL_DIALOG };
  CProgressCtrl m_Progress;
	//CTreeCtrl	m_Tree;
	//}}AFX_DATA
#ifdef _DEBUG
	CListCtrl	m_Files;
#endif

  // HTREEITEM m_hRootFiles;
  // HTREEITEM m_hRootLinks;
  // HTREEITEM m_hRootReg;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUninstallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

private:
    // void FillTree(HTREEITEM hParent, LPCTSTR szPath, BOOL fCheck);
    // void CheckChildren(HTREEITEM hParent, BOOL fCheck);

// Implementation
protected:
  CStringArray m_aLinks;
	HICON        m_hIcon;

  void  FillArray(CStringArray& sa, const CString& szPath, LPCTSTR szFileMask, BOOL fFindInSubfolders);

	// Generated message map functions
	//{{AFX_MSG(CUninstallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickTree(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CString g_szERAPath;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNINSTALLDLG_H__4E337450_C5A0_4A87_9101_8A068F5461DC__INCLUDED_)
