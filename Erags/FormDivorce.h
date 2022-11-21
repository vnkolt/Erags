#if !defined(AFX_FORMDIVORCE_H__E2027494_B2D6_4EB6_A0A8_EABFE2B92A2D__INCLUDED_)
#define AFX_FORMDIVORCE_H__E2027494_B2D6_4EB6_A0A8_EABFE2B92A2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormDivorce.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormDivorce DAO record view
/************************************** : by VK at 26.01.2004 11:28:11 **\
#include ".\Controls\EraControls.h"
#include ".\Controls\KMComboBox.h"
\************************************** : by VK at 26.01.2004 11:28:13 **/
#include "EraForm.h"

#include "RSDivorces.h"

class CFormDivorce : public CEraForm {
protected:
	CFormDivorce();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormDivorce)

  virtual void SetFocusToFirstControl();
  virtual void SetScaleFlags(CWnd* pWnd, WORD& wFlags);
public:
  void AddRecordToNavigateBars(CListCtrl* pNameList, CListCtrl* pNumberList);

// Form Data
public:
	//{{AFX_DATA(CFormDivorce)
	enum { IDD = IDD_FORM_DIVORCE };
	CEraDateEdit       m_DateReg;
	CEraEdit    	     m_Number;
	//CEraMultiStateButton m_GroundType;
	CEraComboBox       m_Ground;
  CEraEdit	         m_GroundNumber;
  CEraDateEdit       m_GroundDate;
  CEraEdit	         m_NKids;
	CEraComboBox	     m_MarriageBy;
	CEraEdit	         m_MarriageNumber;
	CEraDateEdit       m_MarriageDate;
	CEraNameComboBox	 m_MCitizenship;
	CEraEdit	         m_MMarriageNumber;
	CEraNameEdit	     m_MOldSurname;
	CEraNameEdit	     m_MNewSurname;
	CEraNameComboBox	 m_MName;
	CEraNameComboBox	 m_MPatronymic;
	CEraDateEdit       m_MBirthDate;

  CEraNameComboBox	 m_MBirthCountry;
  CEraNameComboBox	 m_MBirthRegion;
  CEraNameComboBox	 m_MBirthDistrict;
  CEraNameComboBox	 m_MBirthCity;
  CEraPassportButton m_MPassportType;
	CEraSeriaEdit	     m_MPassportSeria;
	CEraEdit	         m_MPassportNumber;
	CEraDateEdit       m_MPassportDate;
	CEraComboBox	     m_MPassportBy;
	CEraNameComboBox	 m_MRPCountry;
	CEraNameComboBox	 m_MRPRegion;
	CEraNameComboBox	 m_MRPDistrict;
	CEraNameComboBox	 m_MRPCity;
	CEraNameComboBox	 m_MRPStreet;
	CEraEdit	         m_MRPHouse;
	CEraEdit	         m_MRPFlat;
	CEraMoneyEdit	     m_MDuty;
	CEraMoneyEdit	     m_MDuty2;
	CEraMultiStateButton m_MMoneyType;
	CEraEdit	         m_MCheckNumber;
	CEraDateEdit       m_MCheckDate;
	CEraComboBox	     m_MCheckBank;
	CEraSeriaEdit	     m_MCertificateSeria;
	CEraEdit	         m_MCertificateNumber;
	CEraNoticeEdit	   m_MNotice;
	CEraNameComboBox	 m_WCitizenship;
	CEraEdit	         m_WMarriageNumber;
	CEraNameEdit	     m_WOldSurname;
	CEraNameEdit	     m_WNewSurname;
	CEraNameComboBox	 m_WName;
	CEraNameComboBox	 m_WPatronymic;
	CEraDateEdit       m_WBirthDate;
  CEraNameComboBox	 m_WBirthCountry;
  CEraNameComboBox	 m_WBirthRegion;
  CEraNameComboBox	 m_WBirthDistrict;
  CEraNameComboBox	 m_WBirthCity;
	CEraPassportButton m_WPassportType;
	CEraSeriaEdit	     m_WPassportSeria;
	CEraEdit	         m_WPassportNumber;
	CEraDateEdit       m_WPassportDate;
	CEraComboBox	     m_WPassportBy;
	CEraNameComboBox	 m_WRPCountry;
	CEraNameComboBox	 m_WRPRegion;
	CEraNameComboBox	 m_WRPDistrict;
	CEraNameComboBox	 m_WRPCity;
	CEraNameComboBox	 m_WRPStreet;
	CEraEdit	         m_WRPHouse;
	CEraEdit	         m_WRPFlat;
	CEraMoneyEdit	     m_WDuty;
	CEraMoneyEdit	     m_WDuty2;
	CEraMultiStateButton m_WMoneyType;
	CEraEdit	         m_WCheckNumber;
	CEraDateEdit       m_WCheckDate;
	CEraComboBox	     m_WCheckBank;
	CEraSeriaEdit	     m_WCertificateSeria;
	CEraEdit	         m_WCertificateNumber;
	CEraNoticeEdit	   m_WNotice;
	CRSDivorces*&      m_pRSet;
	//}}AFX_DATA

// Attributes
public:

  CString            m_MOLD_SURNAME_before_save;
  CString            m_MNEW_SURNAME_before_save;
  CString            m_MPATRONYMIC_before_save;
  CString            m_MNAME_before_save;

  CString            m_WOLD_SURNAME_before_save;
  CString            m_WNEW_SURNAME_before_save;
  CString            m_WNAME_before_save;
  CString            m_WPATRONYMIC_before_save;

  short              m_NUMBER_before_save;
  COleDateTime	     m_DATEREG_before_save;
  int                m_GeoFieldsDirtyFlags;

// Operations
public:
	CRSDivorces* GetRecordset();

#ifndef FREE_LICENCE
  BOOL         IsRDFFieldsDirty();
  void         SetRDFFields();
#endif

  void  OnBlank(const CString& szTemplate, const CString& szOut);
  void  OnPrint(UINT nPrintID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormDivorce)
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
	virtual ~CFormDivorce();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

  CString DivReason(int nReason);
  CString DecisionCase(int nReason);
  void    OnShowHideGroundNumber();

  CString GetForUnknown(CEraNameEdit& newSN, CEraNameEdit& oldSN, CEraNameComboBox& Name, CEraNameComboBox& Patronymic, bool fMale);
  CString GetForIncapable(CEraNameEdit& newSN, CEraNameEdit& oldSN, CEraNameComboBox& Name, CEraNameComboBox& Patronymic, bool fMale);
  CString GetForDeprivationOfLiberty(CEraNameEdit& newSN, CEraNameEdit& oldSN, CEraNameComboBox& Name, CEraNameComboBox& Patronymic, bool fMale);
  void RefillGroundCombo();
  void OnKillFocusPatronymic(CEraNameEdit& wndNewSurname, CEraMoneyEdit& wndDuty);
	void OnKillfocusDuty(CEraNameEdit& wndNewSurname, CWnd& where);
	void OnSetfocusCertificateSeria(CEraSeriaEdit& wndCertificateSeria);
	void OnSetfocusCertificateNumber(CEraSeriaEdit& wndCertificateSeria, CEraEdit& wndCertificateNumber);
	void OnChangeCertificateNumber(CEraEdit& wndCertificateNumber);
	void OnBeforeGroundType();

  BOOL IsNeedSubclassForStaticBG(CWnd* pWnd);

  // Generated message map functions
	//{{AFX_MSG(CFormDivorce)
	afx_msg void OnSetfocusDatereg();
	afx_msg void OnSetfocusNumber();
	// afx_msg void OnGroundType();
	afx_msg void OnSetfocusMNewSurname();
	afx_msg void OnSetfocusWOldSurname();
	afx_msg void OnSetfocusWNewSurname();
  afx_msg void OnSetfocusGround();
  afx_msg void OnSelendokGround();
	afx_msg void OnSetfocusGroundNumber();
	afx_msg void OnRecordDelete();
	afx_msg void OnRecordNew();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
  LRESULT NotifyHyperlinkClicked(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMDIVORCE_H__E2027494_B2D6_4EB6_A0A8_EABFE2B92A2D__INCLUDED_)
