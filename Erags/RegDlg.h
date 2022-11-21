#if !defined(AFX_REGDLG_H__823458B2_899E_4CB8_9744_A40A9103EA8F__INCLUDED_)
#define AFX_REGDLG_H__823458B2_899E_4CB8_9744_A40A9103EA8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegDlg.h : header file
//

#ifndef FREE_LICENCE

#include "..\Controls\AutoRichEditCtrl.h"
#include "Defaults.h"
#include "DialogEx.h"

struct LIC_KEY;

#pragma pack(push, pack_recent_save, 1)

struct ValidOwner {
  DWORD  RagsHash;
  time_t FirstStartDate;
  DWORD  TotalRecords;
  DWORD  dwValidGeoRecords;
  DWORD  dwInvalidGeoRecors;
  DWORD  dwValidRagsRecords;
  DWORD  dwVyconcom;
};

struct ValidationInfo {
  DWORD   RagsNameHash; // hash value of full unpacked RAGS name
  BYTE    RagsType;     // 'О' - ВРАЦС, 'В' - виконком
  BYTE    FoundInRDF;
  CString szRegion;
  CString szCity;
  CString szDistrict;
  CString szRagsKeys;
  CString szCityKeys;
  CString szDistrictKeys;
};

#define OVER_BY_REGION      0xFF

extern ValidOwner     g_ValidOwner;
extern ValidationInfo g_ValidationInfo;

#pragma pack(pop, pack_recent_save)

#define RFI_OK   0
#define RFI_NEW  1

#ifndef FREE_LICENCE
void SaveGeoValidation();
void SaveGeoValidation(const CString& szRegion, const CString& szDistrict, const CString& szCity, BOOL fWrite);

void SaveDateValidation(const COleDateTime& sd, const COleDateTime& pDate);
void SaveDateValidation(const COleDateTime* pDate1, const COleDateTime* pDate2=NULL, const COleDateTime* pDate3=NULL);

#endif // #FREE_LICENCE

/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog
class CRegDlg : public CDialogEx {
// Construction
public:
	CRegDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegDlg)
	enum { IDD = IDD_REGISTRATION };
	CAutoRichEditCtrl	m_InfoText;
  CDateTimeCtrl	    m_StartDate;
  CComboBox         m_cmbPeriod;
	CString	          m_key[6];
  CXButtonXP	      m_btnLater;
	//}}AFX_DATA

  CBrush    m_Brush;
  CFont     m_Font;
  int       m_nDates;
  UINT      m_RTF_ID;
  LIC_KEY*  m_pValidLC;
  CString   m_szValidRegCode;
#ifdef _DEBUG
  CString   m_szRealLicKey;
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

private:
  LK_VALUE CheckNewLicKey(LPCTSTR szLicKey);
// Implementation
protected:

  CString GetNewRegCode();
  void OnReinit();
  void OnChangeKey(UINT idKey);

#ifdef _DEBUG
  void MakeKey();
#endif
  
  // Generated message map functions
	//{{AFX_MSG(CRegDlg)
	virtual BOOL OnInitDialog();
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
	afx_msg void OnChangeKey1();
	afx_msg void OnChangeKey2();
	afx_msg void OnChangeKey3();
	afx_msg void OnChangeKey4();
	afx_msg void OnChangeKey5();
	afx_msg void OnChangeKey6();
  afx_msg void OnYes();
  afx_msg void OnRegLater();
  afx_msg void OnStartDateChange(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnSelendokPeriod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void  InitValidationInfo();

#endif // FREE_LICENCE


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGDLG_H__823458B2_899E_4CB8_9744_A40A9103EA8F__INCLUDED_)
