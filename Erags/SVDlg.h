#if !defined(AFX_SVDLG_H__AF896DD5_EC0D_4D43_809B_934BBDDF48FF__INCLUDED_)
#define AFX_SVDLG_H__AF896DD5_EC0D_4D43_809B_934BBDDF48FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SVDlg.h : header file
//

#include "DialogEx.h"
#include "..\Controls\EraControls.h"
#include "..\Controls\CPPTooltip\PPTooltip.h"
#include "..\Controls\TCToolBar\TCImageList.h"

class CRSBirthes;
class CEraForm;

/////////////////////////////////////////////////////////////////////////////
// CSVDlg dialog

class CSVDlg : public CDialogEx {
// Construction
public:
	CSVDlg(CWnd* pParent, UINT nIDTemplate, BOOL fSex=TRUE);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSVDlg)
	enum { IDD = IDD_SVID };
	CEraEdit	        m_edtOwner;
	CEraEdit	        m_edtRegPlace;
	CEraDateEdit      m_DateCert;
	CTreeCtrl	        m_RTree;
	CEraEdit	        m_edtBoss;
  CXButtonXP        m_chkRepeat;
  CXButtonXP        m_chkAsDateReg;
	//}}AFX_DATA
  CTCImageList      m_CheckBoxIL;
  CEraForm*         m_pParentForm;
  CRSBirthes*       m_pRSBirthes;
  
  UINT              m_nIDTemplate;
  CEraNameEdit      m_MSURNAME_1;
  CEraNameEdit      m_WSURNAME_1;
  CEraNameEdit      m_MNAME_1;
  CEraNameEdit      m_WNAME_1;
  CEraNameEdit      m_MPATRONYMIC_1;
  CEraNameEdit      m_WPATRONYMIC_1;
  CEraNameEdit      m_SURNAME_TO;
  CEraNameEdit      m_NAME_TO;
  CEraNameEdit      m_PATRONYMIC_TO;
  CEraLabel         m_ToLabel;

  COleDateTime      m_DateOut;
  CString           m_szFormSect;

  CString           m_sMSurname, m_sWSurname;
  CString           m_sMName, m_sWName, m_sNewName;
  CString           m_sMPatronymic, m_sWPatronymic;
  CString           m_sSurnameTo, m_sNameTo, m_sPatronymicTo;
  BOOL              m_fSexTo;

// Свідоцтво про усиновлення
  CEraEdit          m_VerdictOf;
  CEraDateEdit      m_VerdictDate;
  COleDateTime      m_dtVerdictDate;
  CEraEdit          m_VerdictNumber;
  CEraDateEdit      m_NewBirthDate;
  COleDateTime      m_dtNewBirthDate;
  CEraNameEdit      m_NewSurname;
  CEraNameEdit      m_NewName;
  CEraNameEdit      m_NewPatronymic;
  CString           m_ExtMemo;

  CEraNameComboBox	m_cmbBirthCountry;
  CEraNameComboBox	m_cmbBirthRegion;
	CEraNameComboBox	m_cmbBirthDistrict;
	CEraNameComboBox	m_cmbBirthCity;

protected:
  BOOL       m_fNeedShowTooltip;
  CPPToolTip m_tooltip;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSVDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
  virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSVDlg)
	virtual BOOL OnInitDialog();
  afx_msg void OnAsDateReg();
	afx_msg void OnUpdateRegPlace();
	afx_msg void OnUpdateOwner();
	afx_msg void OnRepeat();
	afx_msg void OnYes();
	afx_msg void OnSelchangedRTree(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnHelpInfo(HELPINFO*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SVDLG_H__AF896DD5_EC0D_4D43_809B_934BBDDF48FF__INCLUDED_)
