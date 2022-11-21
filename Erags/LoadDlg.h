#if !defined(AFX_LOADDLG_H__9590A259_9712_4BE8_8BD9_A3D87798A90D__INCLUDED_)
#define AFX_LOADDLG_H__9590A259_9712_4BE8_8BD9_A3D87798A90D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoadDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoadDlg dialog

class CLoadDlg : public CDialog
{
// Construction
public:
	CLoadDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoadDlg)
	enum { IDD = IDD_DBLOAD };
	CStatic	m_Description;
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
  void  LoadGeoTree();
  void  LoadRegistrars();

	// Generated message map functions
	//{{AFX_MSG(CLoadDlg)
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADDLG_H__9590A259_9712_4BE8_8BD9_A3D87798A90D__INCLUDED_)
