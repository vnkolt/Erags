#if !defined(AFX_FORMCHANGE_H__9E3A916F_CA26_44AD_BF21_EA3804B49097__INCLUDED_)
#define AFX_FORMCHANGE_H__9E3A916F_CA26_44AD_BF21_EA3804B49097__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormChange.h : header file
//

#include "FormABC.h"
#include "..\Controls\EraControls.h"

/////////////////////////////////////////////////////////////////////////////
// CFormChange form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormChange
class CFormChange : public CFormABC {
protected: // create from serialization only
	CFormChange();
	DECLARE_DYNCREATE(CFormChange)

public:
	//{{AFX_DATA(CFormChange)
	enum{ IDD = IDD_FORM_CHANGE };
	CEraXButtonXP     m_fSex;
	CEraEdit	        m_Number;
	CEraDateEdit	    m_DateReg;
	CEraNameEdit      m_OldSurname;
	CEraNameEdit      m_NewSurname;
  CEraNameComboBox  m_OldName;
  CEraNameComboBox  m_NewName;
  CEraNameComboBox  m_OldPatronymic;
  CEraNameComboBox  m_NewPatronymic;
	//}}AFX_DATA
private:
  BOOL  m_fSexSaved;

// Operations
public:
  void SetFocusToFirstControl();
protected:
  void OnClickSex();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormChange)
	public:
	virtual CDaoRecordset* OnGetRecordset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:

protected:
  void OnSexDependences(BOOL fRefill);
// Generated message map functions
protected:
	//{{AFX_MSG(CFormChange)
	afx_msg void OnSetfocusNumber();
	afx_msg void OnSetfocusDatereg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMCHANGE_H__9E3A916F_CA26_44AD_BF21_EA3804B49097__INCLUDED_)
