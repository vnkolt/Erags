#if !defined(AFX_FORMDEATH_H__146D0B26_DB58_4F3F_9770_6AA211A51773__INCLUDED_)
#define AFX_FORMDEATH_H__146D0B26_DB58_4F3F_9770_6AA211A51773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormDeath.h : header file
//

#include "EraForm.h"
/////////////////////////////////////////////////////////////////////////////
// CFormDeath DAO record view

#include "rsDeathes.h"

class CFormDeath : public CEraForm {
protected:
  CFormDeath();           // protected constructor used by dynamic creation
  DECLARE_DYNCREATE(CFormDeath)

  virtual void SetScaleFlags(CWnd* pWnd, WORD& wFlags);
  virtual void SetFocusToFirstControl();

// Form Data
public:
  //{{AFX_DATA(CFormDeath)
  enum { IDD = IDD_FORM_DEATH };
  CEraXButtonXP      m_fSex;
  CEraComboBox       m_cmbCitizenship;
  CEraDateEdit       m_DateReg;
  CEraEdit           m_Number;
  CEraNameEdit       m_Surname;
  CEraNameComboBox   m_Name;
  CEraNameComboBox   m_Patronymic;
  CEraDateEdit       m_DeathDate;
  CEraNameComboBox   m_cmbDeathCountry;
  CEraNameComboBox   m_cmbDeathRegion;
  CEraNameComboBox   m_cmbDeathDistrict;
  CEraNameComboBox   m_cmbDeathCity;
  CKMComboBox        m_cmbReasonPseudo;
  //CMultiColumnComboBox m_cmbReasonPseudo;
  CEraEdit           m_Reason;
  CEraComboBox       m_cmbMidicalCertType;
  CEraEdit           m_MedicalCertNumber;
  CEraDateEdit       m_MedicalCertDate;
  CEraComboBox       m_cmbMedicalCertByPseudo;
  CEraComboBox       m_cmbMedicalCertBy;
  CEraDateEdit       m_BirthDate;
  CEraNameComboBox   m_cmbBirthCountry;
  CEraNameComboBox   m_cmbBirthRegion;
  CEraNameComboBox   m_cmbBirthDistrict;
  CEraNameComboBox   m_cmbBirthCity;
  CEraEdit           m_RPIndex;
  CEraNameComboBox   m_cmbRPCountry;
  CEraNameComboBox   m_cmbRPRegion;
  CEraNameComboBox   m_cmbRPDistrict;
  CEraNameComboBox   m_cmbRPCity;
  CEraNameComboBox   m_cmbRPStreet;
  CEraEdit           m_RPHouse;
  CEraEdit           m_RPFlat;
  CEraMaskEdit       m_IN;
  CEraPassportButton m_PassportType;
  CEraSeriaEdit      m_PassportSeria;
  CEraEdit           m_PassportNumber;
  CEraDateEdit       m_PassportDate;
  CEraComboBox       m_cmbPassportBy;
  CEraEdit           m_DeclarantName;
  CEraEdit           m_DeclarantAddress;
  CEraPassportButton m_DeclarantPassportType;
  CEraSeriaEdit      m_DeclarantPassportSeria;
  CEraEdit           m_DeclarantPassportNumber;
  CEraDateEdit       m_DeclarantPassportDate;
  CEraComboBox       m_cmbDeclarantPassportBy;
  CEraEdit           m_CertificateSeria;
  CEraEdit           m_CertificateNumber;
  CEraNoticeEdit     m_Notice;
  CRSDeathes*&       m_pRSet;
  //}}AFX_DATA

  CStaticBG          m_lblAge;  // IDC_LBL_AGE

  CString            m_SURNAME_before_save;
  CString            m_NAME_before_save;
  CString            m_PATRONYMIC_before_save;
  short              m_NUMBER_before_save;
  COleDateTime	     m_DATEREG_before_save;

// Attributes
public:
  CMapStringToString  m_CausesCache;
  bool                m_fSetfocusDeclarantName;
  CString             m_sReasonSaved;

// Operations
public:
  CRSDeathes* GetRecordset();
  BOOL        IsRDFFieldsDirty();
  void        SetRDFFields();
  void  OnSexDependences();

  bool  LoadCauses();
  void  FillCauseCmb();
  void  OnBlank(const CString& szTemplate, const CString& szOut);
  void  OnPrint(UINT nPrintID);

private:
  void    DDX_Passport(CDataExchange* pDX);
  BOOL    IsMilitary();
  CString GetMilitaryInfo();

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CFormDeath)
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
  virtual ~CFormDeath();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  // Generated message map functions
  //{{AFX_MSG(CFormDeath)
  afx_msg void OnSetfocusDatereg();
  afx_msg void OnSetfocusNumber();
  afx_msg void OnSetfocusDeathDate();
  afx_msg void OnUpdateBirthDate();
  afx_msg void OnSetfocusReasonPseudo();
  afx_msg void OnSelendokReasonPseudo();
  afx_msg void OnSetfocusMedicalCertDate();
  afx_msg void OnSelendokMedicalCertByPseudo();
  afx_msg void OnSelchangeMedicalCertByPseudo();
  afx_msg void OnSetfocusDeclarantName();
  afx_msg void OnKillfocusDeclarantName();
  afx_msg void OnSetfocusDeclarantAddress();
  afx_msg void OnSetfocusCertificateSeria();
  afx_msg void OnSetfocusCertificateNumber();
  afx_msg void OnChangeCertificateNumber();
  afx_msg void OnSetfocusNotice();
  afx_msg void OnSetfocusReason();
	afx_msg void OnKillfocusReason();
  afx_msg void OnDestroy();
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
  LRESULT NotifyHyperlinkClicked(WPARAM wParam, LPARAM lParam);
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMDEATH_H__146D0B26_DB58_4F3F_9770_6AA211A51773__INCLUDED_)
