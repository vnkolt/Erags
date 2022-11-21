#if !defined(AFX_FORMCHANGE_H__C60934D1_7C5A_4D58_8F6C_ED08ECD3B920__INCLUDED_)
#define AFX_FORMCHANGE_H__C60934D1_7C5A_4D58_8F6C_ED08ECD3B920__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormChange.h : header file
//

#include "EraForm.h"

/////////////////////////////////////////////////////////////////////////////
// CFormChange DAO record view

#include "RSChanges.h"

class CFormChange : public CEraForm {
protected:
	CFormChange();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormChange)

  virtual void SetFocusToFirstControl();
  virtual void SetScaleFlags(CWnd* pWnd, WORD& wFlags);

// Form Data
public:
	//{{AFX_DATA(CFormChange)
	enum { IDD = IDD_FORM_CHANGE };
  CEraXButtonXP      m_fSex;
  CEraComboBox       m_cmbCitizenship;
  CEraDateEdit       m_DateReg;
  CEraEdit           m_Number;
  CEraNameEdit       m_OldSurname;
  CEraNameEdit       m_NewSurname;
  CEraNameComboBox   m_OldName;
  CEraNameComboBox   m_NewName;
  CEraNameComboBox   m_OldPatronymic;
  CEraNameComboBox   m_NewPatronymic;
  CEraDateEdit       m_BirthDate;
  CEraNameComboBox   m_cmbBirthCountry;
  CEraNameComboBox   m_cmbBirthRegion;
  CEraNameComboBox   m_cmbBirthDistrict;
  CEraNameComboBox   m_cmbBirthCity;
  CEraNameComboBox   m_cmbRPCountry;
  CEraNameComboBox   m_cmbRPRegion;
  CEraNameComboBox   m_cmbRPDistrict;
  CEraNameComboBox   m_cmbRPCity;
  CEraNameComboBox   m_cmbRPStreet;
  CEraEdit           m_RPHouse;
  CEraEdit           m_RPFlat;
	CEraEdit	         m_BirthActNumber;
	CEraDateEdit       m_BirthActDate;
	CEraMoneyEdit	     m_Duty;
	CEraEdit	         m_CheckNumber;
	CEraDateEdit       m_CheckDate;
	CEraComboBox	     m_CheckBank;
	CEraPassportButton m_PassportType;
	CEraSeriaEdit	     m_PassportSeria;
	CEraEdit	         m_PassportNumber;
	CEraDateEdit       m_PassportDate;
	CEraComboBox	     m_PassportBy;
  CEraEdit           m_CertificateSeria;
  CEraMaskEdit       m_CertificateNumber;
  CEraNoticeEdit     m_Notice;
	CRSChanges*&       m_pRSet;
	//}}AFX_DATA

// Attributes
public:

  CString            m_OLDSURNAME_before_save;
  CString            m_OLDNAME_before_save;
  CString            m_OLDPATRONYMIC_before_save;
  CString            m_NEWSURNAME_before_save;
  CString            m_NEWNAME_before_save;
  CString            m_NEWPATRONYMIC_before_save;
  short              m_NUMBER_before_save;
  COleDateTime	     m_DATEREG_before_save;

// Operations
public:
	CRSChanges* GetRecordset();
#ifndef FREE_LICENCE
  BOOL        IsRDFFieldsDirty();
  void        SetRDFFields();
#endif // #FREE_LICENCE
  void        SelectIfNotEmpty(CEraNameComboBox& cb, const CString& sValue);
  void        OnSexDependences();

  void  OnBlank(const CString& szTemplate, const CString& szOut);
  void  OnPrint(UINT nPrintID);

protected:
  BOOL IsNeedSubclassForStaticBG(CWnd* pWnd);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormChange)
		// NOTE - the ClassWizard will add and remove member functions here.
	public:
	virtual CDaoRecordset* OnGetRecordset();
  virtual BOOL OnMove(UINT nIDMoveCommand);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
  virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFormChange();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFormChange)
  afx_msg void OnSetfocusDatereg();
  afx_msg void OnSetfocusNumber();
	afx_msg void OnSetfocusNewSurname();
	afx_msg void OnSetfocusNewName();
	afx_msg void OnSetfocusNewPatronymic();
	afx_msg void OnSetfocusCertificateSeria();
	afx_msg void OnSetfocusCertificateNumber();
  afx_msg void OnChangeCertificateNumber();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
  LRESULT NotifyHyperlinkClicked(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMCHANGE_H__C60934D1_7C5A_4D58_8F6C_ED08ECD3B920__INCLUDED_)
