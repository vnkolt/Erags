#if !defined(AFX_DIV23_H__2BA3BC85_4F1D_4705_8086_9450DEBE6E00__INCLUDED_)
#define AFX_DIV23_H__2BA3BC85_4F1D_4705_8086_9450DEBE6E00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Div23.h : header file
//

#include "DialogEx.h"
#include "..\Controls\EraControls.h"

/////////////////////////////////////////////////////////////////////////////
// CDiv23 dialog

class CDiv23 : public CDialogEx {
// Construction
public:
	CDiv23(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDiv23)
	enum { IDD = IDD_DIVORCE_23 };
	CEraEdit	    m_TORAGS;
	CEraNameEdit	m_MSURNAME;
	CEraNameEdit	m_MPATRONYMIC;
	CEraNameEdit	m_MNAME;
	CEraNameEdit	m_WSURNAME;
	CEraNameEdit	m_WPATRONYMIC;
	CEraNameEdit	m_WNAME;
	//}}AFX_DATA

  CString       m_sToRags;
	CString       m_sMSurname;
	CString       m_sMPatronymic;
	CString       m_sMName;
	CString       m_sWSurname;
	CString       m_sWPatronymic;
	CString       m_sWName;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiv23)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDiv23)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIV23_H__2BA3BC85_4F1D_4705_8086_9450DEBE6E00__INCLUDED_)
