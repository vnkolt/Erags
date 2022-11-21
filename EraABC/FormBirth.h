#if !defined(AFX_FORMBIRTH_H__4F430A04_7384_4851_8829_76169AAFACB0__INCLUDED_)
#define AFX_FORMBIRTH_H__4F430A04_7384_4851_8829_76169AAFACB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormBirth.h : header file
//
#include "FormABC.h"
#include "..\Controls\EraControls.h"

/////////////////////////////////////////////////////////////////////////////
// CFormBirth form view
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFormBirth : public CFormABC
{
protected:
	CFormBirth();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormBirth)

// Form Data
public:
	//{{AFX_DATA(CFormBirth)
	enum { IDD = IDD_FORM_BIRTH };
  CEraXButtonXP         m_fSex;
  CEraEdit	            m_Number;
  CEraDateEdit	        m_DateReg;
  CEraNameEdit          m_Surname;
  CEraNameComboBox      m_Name;
  CEraNameComboBox      m_Patronymic;
  CEraDateEdit	        m_DateBirth;
	CEraMultiStateButton	m_Alive_Flag;
	//}}AFX_DATA
  CBitmap           m_bmBoy;
  CBitmap           m_bmGirl;
  CBitmap           m_bmStillbornBoy;
  CBitmap           m_bmStillbornGirl;
  CStatic           m_Face;
  BOOL              m_fSexSaved;

// Attributes
public:

// Operations
protected:
  void SetFocusToFirstControl();
  void OnSexDependences(BOOL fRefill);
  void OnClickSex();
  void BeforeGoToNextRecord();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormBirth)
	public:
	virtual CDaoRecordset* OnGetRecordset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFormBirth();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFormBirth)
	afx_msg void OnSetfocusNumber();
	afx_msg void OnSetfocusDatereg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMBIRTH_H__4F430A04_7384_4851_8829_76169AAFACB0__INCLUDED_)
