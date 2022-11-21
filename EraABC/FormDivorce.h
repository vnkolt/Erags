#if !defined(AFX_FORMDIVORCE_H__B8BE1387_E8E4_461D_9758_4564E8F12D0A__INCLUDED_)
#define AFX_FORMDIVORCE_H__B8BE1387_E8E4_461D_9758_4564E8F12D0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormDivorce.h : header file
//

#include "FormABC.h"
#include "..\Controls\EraControls.h"

/////////////////////////////////////////////////////////////////////////////
// CFormDivorce form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormDivorce
class CFormDivorce : public CFormABC {
protected: // create from serialization only
	CFormDivorce();
	DECLARE_DYNCREATE(CFormDivorce)

public:
	//{{AFX_DATA(CFormDivorce)
	enum{ IDD = IDD_FORM_DIVORCE };
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
	//{{AFX_VIRTUAL(CFormDivorce)
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
	//{{AFX_MSG(CFormDivorce)
	afx_msg void OnSetfocusNumber();
	afx_msg void OnSetfocusDatereg();
	afx_msg void OnSetfocusMnewSurname();
	afx_msg void OnSetfocusWoldSurname();
	afx_msg void OnSetfocusWnewSurname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMDIVORCE_H__B8BE1387_E8E4_461D_9758_4564E8F12D0A__INCLUDED_)
