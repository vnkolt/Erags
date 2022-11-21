#if !defined(AFX_DLG27_H__ECA00B62_5714_45B9_8AAC_439CFC687777__INCLUDED_)
#define AFX_DLG27_H__ECA00B62_5714_45B9_8AAC_439CFC687777__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg27.h : header file
//

#include "DialogEx.h"
#include "..\Controls\EraControls.h"

/////////////////////////////////////////////////////////////////////////////
// CDlg27 dialog
class CDlg27 : public CDialogEx {
// Construction
public:
	CDlg27(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg27)
	enum { IDD = IDD_CHANGE_27 };
	CEraNameEdit	m_OldSurname;
	CEraComboBox	m_OldPatronymic;
	CEraComboBox	m_OldName;
	CEraNameEdit	m_NewSurname;
	CEraComboBox	m_NewPatronymic;
	CEraComboBox	m_NewName;
	CEraEdit	    m_Address;
	//}}AFX_DATA

	CString       m_sOldSurname;
	CString       m_sOldPatronymic;
	CString       m_sOldName;
	CString       m_sNewSurname;
	CString       m_sNewPatronymic;
	CString       m_sNewName;
	CString       m_sAddress;
  BOOL          m_fSex;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg27)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg27)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
  BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG27_H__ECA00B62_5714_45B9_8AAC_439CFC687777__INCLUDED_)
