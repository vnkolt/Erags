#if !defined(AFX_SETDEFDLG_H__607A0D86_9E04_441A_AFB3_6BB1EE570D90__INCLUDED_)
#define AFX_SETDEFDLG_H__607A0D86_9E04_441A_AFB3_6BB1EE570D90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDefDlg.h : header file
//
#include "DialogEx.h"
#include "..\Controls\TCToolBar\TCImageList.h"

/////////////////////////////////////////////////////////////////////////////
// CSetDefDlg dialog
class CSetDefDlg : public CDialogEx {
// Construction
public:
	CSetDefDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetDefDlg)
	enum { IDD = IDD_SETDEFVAL };
	BOOL	m_DontShow;
  CXButtonXP        m_CheckBox;
	//}}AFX_DATA

  CTCImageList      m_CheckBoxIL;
  CString m_Text;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetDefDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetDefDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDontShow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

int CallSetDefDlg(CWnd* pParent, LPCTSTR szSection, LPCTSTR szShowValue, LPCTSTR szYesNoValue, LPCTSTR szMsg);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETDEFDLG_H__607A0D86_9E04_441A_AFB3_6BB1EE570D90__INCLUDED_)
