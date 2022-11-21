#if !defined(AFX_CDIV18_H__7163606E_DF0C_479D_AE84_2576513019D3__INCLUDED_)
#define AFX_CDIV18_H__7163606E_DF0C_479D_AE84_2576513019D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Div18.h : header file
//

#include "DialogEx.h"
#include "..\Controls\EraControls.h"

/////////////////////////////////////////////////////////////////////////////
// CDiv18 dialog

class CDiv18 : public CDialogEx
{
// Construction
public:
	CDiv18(CWnd* pParent = NULL, BOOL fSex=FALSE);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDiv18)
	enum { IDD = IDD_DIVORCE_18 };
	CEraEdit	    m_ToRags;
	CEraNameEdit	m_Surname;
	CEraNameEdit	m_Name;
	CEraNameEdit	m_Patronymic;
	//}}AFX_DATA

  BOOL      m_fSex;
	CString   m_sToRags;
	CString   m_sSurname;
	CString   m_sName;
	CString   m_sPatronymic;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiv18)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDiv18)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDIV18_H__7163606E_DF0C_479D_AE84_2576513019D3__INCLUDED_)
