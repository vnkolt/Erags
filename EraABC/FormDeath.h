#if !defined(AFX_FORMDEATH_H__BFC64628_C5C0_469B_A718_64A63B231B96__INCLUDED_)
#define AFX_FORMDEATH_H__BFC64628_C5C0_469B_A718_64A63B231B96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormDeath.h : header file
//

#include "FormABC.h"
#include "..\Controls\EraControls.h"

/////////////////////////////////////////////////////////////////////////////
// CFormDeath form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormDeath
class CFormDeath : public CFormABC {
protected: // create from serialization only
	CFormDeath();
	DECLARE_DYNCREATE(CFormDeath)

public:
	//{{AFX_DATA(CFormDeath)
	enum{ IDD = IDD_FORM_DEATH };
	CEraXButtonXP     m_fSex;
	CEraEdit	        m_Number;
	CEraDateEdit	    m_DateReg;
	CEraNameEdit      m_Surname;
  CEraNameComboBox  m_Name;
  CEraNameComboBox  m_Patronymic;
  CEraDateEdit	    m_DateBirth;
	//}}AFX_DATA
private:
  BOOL              m_fSexSaved;
// Operations
public:
  void SetFocusToFirstControl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormDeath)
	public:
	virtual CDaoRecordset* OnGetRecordset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:

protected:
  void OnClickSex();
  void OnSexDependences(BOOL fRefill);

// Generated message map functions
protected:
	//{{AFX_MSG(CFormDeath)
	afx_msg void OnSetfocusNumber();
	afx_msg void OnSetfocusDatereg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMDEATH_H__BFC64628_C5C0_469B_A718_64A63B231B96__INCLUDED_)
