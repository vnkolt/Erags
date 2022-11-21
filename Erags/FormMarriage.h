#if !defined(AFX_FORMMARRIAGE_H__4E354A75_6424_4085_A7DE_E6A192E8E91A__INCLUDED_)
#define AFX_FORMMARRIAGE_H__4E354A75_6424_4085_A7DE_E6A192E8E91A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormMarriage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormMarriage DAO record view
#include "..\Controls\EraControls.h"

#include "EraForm.h"
#include "RSMarriages.h"

class CFormMarriage : public CEraForm {
protected:
	CFormMarriage();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormMarriage)

public:
  void AddRecordToNavigateBars(CListCtrl* pNameList, CListCtrl* pNumberList);
  void SetFocusToFirstControl();
  void SetScaleFlags(CWnd* pWnd, WORD& wFlags);

// Form Data
public:
	//{{AFX_DATA(CFormMarriage)
	enum { IDD = IDD_FORM_MARRIAGE };
  CStaticBG           m_MActLabel;
  CStaticBG           m_WActLabel;
  CStaticBG           m_MDateLabel;
  CStaticBG           m_WDateLabel;
  CStaticBG           m_MByLabel;
  CStaticBG           m_WByLabel;
	CEraDateEdit        m_DateReg;
	CEraEdit    	      m_Number;
	CEraNameComboBox	  m_MCitizenship;
	CEraNameComboBox	  m_WCitizenship;
	CEraNameEdit	      m_MOldSurname;
	CEraNameEdit        m_WOldSurname;
	CEraNameEdit        m_MNewSurname;
	CEraNameEdit        m_WNewSurname;
	CEraNameComboBox	  m_MName;
	CEraNameComboBox	  m_MPatronymic;
	CEraNameComboBox	  m_WName;
	CEraNameComboBox	  m_WPatronymic;
	CEraDateEdit        m_MBirthDate;
	CEraDateEdit        m_WBirthDate;
	CEraNameComboBox	  m_MBirth_Country;
	CEraNameComboBox	  m_WBirth_Country;
	CEraNameComboBox    m_MBirth_Region;
	CEraNameComboBox    m_WBirth_Region;
	CEraNameComboBox    m_MBirth_District;
	CEraNameComboBox    m_WBirth_District;
	CEraNameComboBox    m_MBirth_City;
	CEraNameComboBox    m_WBirth_City;
	CEraNameComboBox	  m_MRP_Country;
	CEraNameComboBox	  m_WRP_Country;
	CEraNameComboBox    m_MRP_Region;
	CEraNameComboBox    m_WRP_Region;
	CEraNameComboBox    m_MRP_District;
	CEraNameComboBox    m_WRP_District;
	CEraNameComboBox    m_MRP_City;
	CEraNameComboBox    m_WRP_City;
	CEraNameComboBox	  m_MRP_Street;
	CEraNameComboBox	  m_WRP_Street;
	CEraEdit	          m_MRP_House;
	CEraEdit	          m_WRP_House;
	CEraEdit	          m_MRP_Flat;
	CEraEdit	          m_WRP_Flat;
	CEraPassportButton  m_MPassport_Type;
	CEraPassportButton  m_WPassport_Type;
	CEraSeriaEdit     	m_MPassport_Seria;
	CEraSeriaEdit     	m_WPassport_Seria;
	CEraEdit	          m_MPassport_Number;
	CEraEdit	          m_WPassport_Number;
	CEraComboBox	      m_MPassport_By;
	CEraComboBox	      m_WPassport_By;
	CEraDateEdit        m_MPassportDate;
	CEraDateEdit        m_WPassportDate;
	CEraMultiStateButton  m_MFamily_Status;
	CEraMultiStateButton  m_WFamily_Status;
	CEraEdit	          m_MAct_Number;
	CEraEdit	          m_WAct_Number;
	CEraDateEdit        m_MActDate;
	CEraDateEdit        m_WActDate;
	CEraComboBox	      m_MAct_By;
	CEraComboBox	      m_WAct_By;
	CEraSeriaEdit       m_Certificate_Seria;
	CEraEdit	          m_Certificate_Number;
  CEraNoticeEdit      m_Notice;
	CEraNoticeEdit      m_MNotice;
	CEraNoticeEdit      m_WNotice;
	CRSMarriages*&      m_pRSet;
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
	CRSMarriages* GetRecordset();
  BOOL          IsRDFFieldsDirty();
  void          SetRDFFields();
  void          OnBlank(const CString& szTemplate, const CString& szOut);
  void          OnPrint(UINT nPrintID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormMarriage)
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
	virtual ~CFormMarriage();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

  void  OnFamilyStatusDependences(CEraMultiStateButton& msFamily_Status,
                                  UINT id_NACT_LABEL, UINT id_ACT_NUMBER,
                                  UINT id_DATE_LABEL, UINT id_ACT_DATE,
                                  UINT id_BY_LABEL,  UINT id_ACT_BY,
                                  CEraNoticeEdit& NoticeWnd,
                                  BOOL fSet=false);

	// Generated message map functions
	//{{AFX_MSG(CFormMarriage)
	afx_msg void OnSetfocusDatereg();
	afx_msg void OnSetfocusNumber();
	afx_msg void OnSetfocusMNewSurname();
	afx_msg void OnSetfocusWNewSurname();
	afx_msg void OnSetfocusCertificateSeria();
	afx_msg void OnSetfocusCertificateNumber();
	afx_msg void OnChangeCertificateNumber();
  afx_msg void OnSetfocusNotice();
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

#endif // !defined(AFX_FORMMARRIAGE_H__4E354A75_6424_4085_A7DE_E6A192E8E91A__INCLUDED_)
