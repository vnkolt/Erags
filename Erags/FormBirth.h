#if !defined(AFX_FORMBIRTH_H__CFC85864_E66E_4C3B_822B_7DF231FF1ED3__INCLUDED_)
#define AFX_FORMBIRTH_H__CFC85864_E66E_4C3B_822B_7DF231FF1ED3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormBirth.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormBirth DAO record view

#include "EraForm.h"
#include "RSBirthes.h"

class CFormBirth : public CEraForm {
protected:
	CFormBirth();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormBirth)

  virtual void SetFocusToFirstControl();
  virtual void SetScaleFlags(CWnd* pWnd, WORD& wFlags);

  void         BeforeLeaveSurname();
  void         BeforeLeavePatronymic();
  void         SetNewNames();
// Form Data
public:
	//{{AFX_DATA(CFormBirth)
	enum { IDD = IDD_FORM_BIRTH };
	CEraToggleButton	m_BirthPlace;
	CEraXButtonXP     m_fSex;
	CEraEdit	        m_Number;
	CEraDateEdit      m_DateReg;
	CEraNameEdit      m_Surname;
  CEraNameComboBox  m_Name;
  CEraNameComboBox  m_Patronymic;
  CEraDateEdit      m_DateBirth;
	CEraNameComboBox	m_cmbBirthCountry;
	CEraNameComboBox	m_cmbBirthRegion;
	CEraNameComboBox	m_cmbBirthDistrict;
	CEraNameComboBox	m_cmbBirthCity;
  CEraEdit          m_nKids;
  CEraEdit          m_nByCount;
	CEraOnOffLabel	  m_Alive_Flag;
  CEraEdit          m_AliveFlag;
  CEraEdit          m_MedCertNumber;
  CEraDateEdit      m_MedCertDate;
  CEraComboBox      m_MedCertPseudo;
  CEraComboBox      m_MedCertBy;
	CEraMultiStateButton	m_SourceType;
  CEraEdit          m_SourceNDoc;
  CEraDateEdit      m_SourceDate;
  CEraComboBox      m_SourceBy;
  CEraComboBox      m_FatherCitizenship;
  CEraNameEdit      m_FatherSurname;
  CEraNameComboBox  m_FatherName;
  CEraNameComboBox  m_FatherPatronymic;
  CEraDateEdit      m_FatherDate;
  CEraNameComboBox  m_FatherCountry;
  CEraNameComboBox  m_FatherRegion;
  CEraNameComboBox  m_FatherCity;
  CEraNameComboBox  m_FatherDistrict;
  CEraNameComboBox  m_FatherStreet;
  CEraEdit          m_FatherHouse;
  CEraEdit          m_FatherFlat;
  CEraComboBox      m_MotherCitizenship;
  CEraNameEdit      m_MotherSurname;
  CEraNameComboBox  m_MotherName;
  CEraNameComboBox  m_MotherPatronymic;
  CEraDateEdit      m_MotherDate;
  CEraNameComboBox  m_MotherCountry;
  CEraNameComboBox  m_MotherRegion;
  CEraNameComboBox  m_MotherCity;
  CEraNameComboBox  m_MotherDistrict;
  CEraNameComboBox  m_MotherStreet;
  CEraEdit          m_MotherHouse;
  CEraEdit          m_MotherFlat;
  CEraMultiStateButton	m_DeclarantType;
  CEraEdit              m_DeclarantName;
  CEraEdit              m_DeclarantAddress;
  CEraPassportButton    m_DeclarantPassportType;
  CEraSeriaEdit	        m_DeclarantPassportSeria;
  CEraEdit              m_DeclarantPassportNumber;
  CEraDateEdit          m_DeclarantPassportDate;
  CEraComboBox          m_DeclarantPassportBy;
	CEraButton	          m_btnDeclarantPassports;
  CEraSeriaEdit         m_CertificateSeria;
  CEraEdit              m_CertificateNumber;
  CEraNoticeEdit        m_Notice;
	CEraEdit              m_ExtNotices;
	CEraEdit              m_Flags;
	CEraOnOffLabel	      m_Decl20;
	CRSBirthes*& m_pRSet;
	//}}AFX_DATA

//  CStaticBG m_lblBirthCountry;    // IDC_BC_LABEL
  CStaticBG m_lblSourceOf;        // IDC_SOURCE_OF_LABEL
  CStaticBG m_lblSourceBy;        // IDC_SOURCE_BY_LABEL
  CStaticBG m_lblDeclarantSeria;  // IDC_LBL_DECLARANT_PSERIA
  CStaticBG m_lblDeclarantNumber; // IDC_LBL_DECLARANT_PNUMBER
  CStaticBG m_lblDeclarantPDate;  // IDC_LBL_DECLARANT_PDATE

#ifndef FREE_LICENCE
  int     m_GeoFieldsDirtyFlags;
#endif
  bool    m_fMedCertPseudoChanged;

  CString            m_SURNAME_before_save;
  CString            m_NAME_before_save;
  CString            m_PATRONYMIC_before_save;
  short              m_NUMBER_before_save;
  COleDateTime	     m_DATEREG_before_save;

  CString            m_NEW_SURNAME_before_save;
  CString            m_NEW_NAME_before_save;
  CString            m_NEW_PATRONYMIC_before_save;

// Attributes
public:
// Operations
public:
	CRSBirthes* GetRecordset();
#ifndef FREE_LICENCE
  BOOL        IsRDFFieldsDirty();
  void        SetRDFFields();
#endif
  void  OnSexDependences();
  void  OnBirthPlaceDependences();
  void  OnSourceTypeDependences();
  void  SetBPDefaults();

  void  OnBlank(const CString& szTemplate, const CString& szOut);
  void  OnPrint(UINT nPrintID);
  void  GetDecalantPassports();
  void  OnSetFocusMotherStreet();
  BOOL  IsRenew();
  BOOL  IsLongTerm();
  BOOL  IsAlive();
  BOOL  IsDeclarantIn20();
	void  OnRenew();
  void  OnLongTerm();
	void  OnAliveFlag();
  void  OnDecl20();

// Overrides
protected:
  BOOL IsNeedSubclassForStaticBG(CWnd* pWnd);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormBirth)
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
	virtual ~CFormBirth();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

  void  ShowPassportButton(BOOL bShowTwoPassportButton);

	// Generated message map functions
	//{{AFX_MSG(CFormBirth)
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg void OnRecordDelete();
	afx_msg void OnSetfocusDatereg();
	afx_msg void OnSetfocusNumber();
	afx_msg void OnSetfocusMedicalCertificateDate();
	afx_msg void OnSetfocusMedicalCertificateBy();
	afx_msg void OnSetfocusSourceDate();
	afx_msg void OnSetfocusFatherSurname();
	afx_msg void OnSetfocusFatherName();
	afx_msg void OnSetfocusDateofBirth();
	afx_msg void OnSetfocusMotherSurname();
  afx_msg void OnSetfocusDeclaranType();
	afx_msg void OnSetfocusCertificateSeria();
	afx_msg void OnSetfocusCertificateNumber();
	afx_msg void OnChangeCertificateNumber();
	afx_msg void OnSetfocusNotice();
  afx_msg void OnKillfocusSurname();
	afx_msg void OnDeclarantType();
	afx_msg void OnUpdateExtnotes(CCmdUI* pCmdUI);
	afx_msg void OnExtnotes();
	afx_msg void OnSetfocusMotherHouse();
	afx_msg void OnSetfocusMotherFlat();
	afx_msg void OnDeclarant20();
	afx_msg void OnDeclarantDlg();
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSelendokMedicalCertificatePseudunym();
  afx_msg void OnRecordNew();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
  LRESULT NotifyHyperlinkClicked(WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMBIRTH_H__CFC85864_E66E_4C3B_822B_7DF231FF1ED3__INCLUDED_)
