#if !defined(AFX_WITNESSDLG_H__8B19A682_3742_47F3_847A_A864D46A0BDF__INCLUDED_)
#define AFX_WITNESSDLG_H__8B19A682_3742_47F3_847A_A864D46A0BDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WitnessDlg.h : header file
//

#include "RSBirthes.h"

/////////////////////////////////////////////////////////////////////////////
// CWitnessDlg dialog
class CWitnessDlg : public CDialog {
// Construction
public:
	CWitnessDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWitnessDlg)
	enum { IDD = IDD_WITNESSES };
  CString	m_szTitle;
  CString	m_szGR10;

  CString	m_MedDocName;
	CString	m_MedDocNum;
	CString	m_MedDocDate;
	CString	m_MedDocBy;
	int		  m_SettlType1;

	static CString	m_Surname1;
	static CString	m_Name1;
	static CString	m_Patronymic1;
	static CString	m_Country1;
	static CString	m_Region1;
	static CString	m_District1;
	static CString	m_City1;
  static TCHAR    m_cCityType1;
	static CString	m_Street1;
  static TCHAR    m_cStreetType1;
  static CString	m_Build1;
	static CString	m_Flat1;
	static int		  m_DocType1;
	static CString	m_DocSeria1;
  static CString	m_DocNumber1;
  static CString	m_DocDate1;
	static CString	m_DocOrgan1;

	static CString	m_Surname2;
	static CString	m_Name2;
	static CString	m_Patronymic2;
	static CString	m_Country2;
	static CString	m_Region2;
	static CString	m_District2;
	static CString	m_City2;
  static TCHAR    m_cCityType2;
  static TCHAR    m_cStreetType2;
	static int		  m_SettlType2;
	static CString	m_Street2;
	static CString	m_Build2;
	static CString	m_Flat2;
	static int		  m_DocType2;
	static CString	m_DocSeria2;
	static CString	m_DocNumber2;
	static CString	m_DocDate2;
	static CString	m_DocOrgan2;

  CComboBox       m_cbCityType1;
  CComboBox       m_cbCityType2;
  CComboBox       m_cbStreetType1;
  CComboBox       m_cbStreetType2;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWitnessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  void OnOk();
	//}}AFX_VIRTUAL

// Implementation
protected:

  void SetCityType(int& SettlType, TCHAR& cCityType);

	// Generated message map functions
	//{{AFX_MSG(CWitnessDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BOOL ParseG10(CRSBirthes& rs);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WITNESSDLG_H__8B19A682_3742_47F3_847A_A864D46A0BDF__INCLUDED_)
