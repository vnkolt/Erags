#if !defined(AFX_FSTATUSDLG_H__AC79E33D_6733_432B_AB06_CACC7410DE37__INCLUDED_)
#define AFX_FSTATUSDLG_H__AC79E33D_6733_432B_AB06_CACC7410DE37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FStatusDlg.h : header file
//

#include "..\Controls\EraControls.h"
#include "DialogEx.h"
#include "..\Controls\TCToolBar\TCImageList.h"

/////////////////////////////////////////////////////////////////////////////
// CFStatusDlg dialog

class CFStatusDlg : public CDialogEx {
// Construction
public:
	CFStatusDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFStatusDlg)
	enum { IDD = IDD_FSTATUS };
  CFrameBG            m_Frame1;
  CFrameBG            m_Frame2;
  CFrameBG            m_Frame3;
  CFrameBG            m_Frame4;
  CFrameBG            m_Frame5;
	CEraDateEdit	      m_DateV;
	CEraEdit    	      m_NDov;
	CEraEdit	          m_Rags;
	CEraDateEdit	      m_DFrom;
	CEraDateEdit	      m_DTill;
	CEraNameEdit	      m_FullName1;
	CEraNameEdit	      m_FullName2;
	CXButtonXP          m_Sex;
	CXButtonXP          m_Citizen;
	CXButtonXP          m_Unmarried;
	CEraDateEdit	      m_DBirth;
	CEraEdit	          m_BPlace;
	CEraPassportButton	m_PassportType;
	CEraSeriaEdit     	m_PassportSeria;
	CEraEdit	          m_PassportNumber;
	CEraDateEdit	      m_PassportDate;
	CEraComboBox      	m_PassportBy;
	//}}AFX_DATA

  CTCImageList        m_CheckBoxIL;
  static  COleDateTime  m_odt;
  static  CString       m_szNumber;
  static  CString       m_szRags;
  static  COleDateTime  m_odtFrom;
  static  COleDateTime  m_odtTill;
  static  BOOL          m_fSex;
	static  CString       m_szFullName1;
	static  BOOL          m_fCitizen;
	static  CString       m_szFullName2;
	static  BOOL          m_fUnmarried;
	static  COleDateTime  m_odtBirth;
	static  CString       m_szBPlace;
	static  BYTE          m_bPassportType;
	static  CString       m_szPassportSeria;
	static  CString       m_szPassportNumber;
	static  COleDateTime  m_odtPassportDate;
	static  CString       m_szPassportBy;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFStatusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFStatusDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSex();
	afx_msg void OnChangeFullname1();
	afx_msg void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSTATUSDLG_H__AC79E33D_6733_432B_AB06_CACC7410DE37__INCLUDED_)
