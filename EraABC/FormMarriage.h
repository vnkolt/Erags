#if !defined(AFX_FORMMARRIAGE_H__EFFF953E_F54D_49D4_AF9A_EDDEF9CEDA7C__INCLUDED_)
#define AFX_FORMMARRIAGE_H__EFFF953E_F54D_49D4_AF9A_EDDEF9CEDA7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormMarriage.h : header file
//

#include "FormABC.h"
#include "..\Controls\EraControls.h"

/////////////////////////////////////////////////////////////////////////////
// CFormMarriage form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormMarriage
class CFormMarriage : public CFormABC {
protected: // create from serialization only
	CFormMarriage();
	DECLARE_DYNCREATE(CFormMarriage)

public:
	//{{AFX_DATA(CFormMarriage)
	enum{ IDD = IDD_FORM_MARRIAGE };
	CEraEdit	        m_Number;
	CEraDateEdit	    m_DateReg;
	CEraNameEdit      m_MOldSurname;
	CEraNameEdit      m_MNewSurname;
  CEraNameComboBox  m_MName;
  CEraNameComboBox  m_MPatronymic;
	CEraNameEdit      m_WOldSurname;
	CEraNameEdit      m_WNewSurname;
  CEraNameComboBox  m_WName;
  CEraNameComboBox  m_WPatronymic;
	//}}AFX_DATA

// Operations
public:
  void SetFocusToFirstControl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormMarriage)
	public:
	virtual CDaoRecordset* OnGetRecordset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFormMarriage)
	afx_msg void OnSetfocusNumber();
	afx_msg void OnSetfocusDatereg();
	afx_msg void OnSetfocusMnewSurname();
	afx_msg void OnSetfocusWnewSurname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMMARRIAGE_H__EFFF953E_F54D_49D4_AF9A_EDDEF9CEDA7C__INCLUDED_)
