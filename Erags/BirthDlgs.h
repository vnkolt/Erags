#if !defined(AFX_BIRTHDLS_H__F9F5996A_CAB0_4C45_B8AC_429C18AA9A4A__INCLUDED_)
#define AFX_BIRTHDLS_H__F9F5996A_CAB0_4C45_B8AC_429C18AA9A4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//
// BirthDlgs.h : header file
//

#include "DialogEx.h"
#include "..\Controls\EraControls.h"


/////////////////////////////////////////////////////////////////////////////
// CBirth08 dialog
class CBirth08 : public CDialogEx {
// Construction
public:
	CBirth08(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBirth08)
	enum { IDD = IDD_BIRTH_08 };
	CEraEdit  m_Number;
	CEraEdit  m_BabyName;
	CEraEdit  m_To;
	CEraEdit  m_Where;
	//}}AFX_DATA
  int       m_nDoc;
	CString   m_sNumber;
	CString   m_sTo;
	CString   m_sBabyName;
	CString   m_sWhere;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBirth08)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBirth08)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CBirth09 : public CDialogEx {
// Construction
public:
	CBirth09(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBirth11)
	enum { IDD = IDD_BIRTH_09 };
	CEraEdit  m_To;
	CEraEdit  m_BabyName;
	CEraEdit  m_FatherName;
	CEraEdit  m_MotherName;
	//}}AFX_DATA

  CString   m_sTo;
  CString   m_sBabyName;
	CString   m_sFatherName;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBirth11)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBirth09)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeSocProt();
	afx_msg void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CBirth11 : public CDialogEx {
// Construction
public:
	CBirth11(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBirth11)
	enum { IDD = IDD_BIRTH_11 };
	CEraEdit  m_To;
	CEraEdit  m_BabyName;
	CEraEdit  m_FatherName;
	CEraEdit  m_MotherName;
	//}}AFX_DATA

  BOOL      m_fSocProtChanged;
  CString   m_sTo;
  CString   m_sBabyName;
	CString   m_sFatherName;
	CString   m_sMotherName;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBirth11)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBirth11)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeSocProt();
	afx_msg void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CString g_Dlg08_sNumber, g_sFullBabyNameRV, g_Dlg08_sWhere;
extern CString g_sFullFatherNameRV, g_sFullMotherNameRV;


BOOL BirthDlg08(int nDoc, CWnd* pParent, short nAct, BOOL bSex, LPCTSTR szMemo, LPCTSTR szSurName, LPCTSTR szName, LPCTSTR szFather);
BOOL BirthDlg09(CWnd* pParent, BOOL bSex,
                LPCTSTR szSurName,  LPCTSTR szName,  LPCTSTR szPatronymic,
                LPCTSTR szMSurName, LPCTSTR szMName, LPCTSTR szMPatronymic
               );
BOOL BirthDlg11(CWnd* pParent, BOOL bSex,
                LPCTSTR szSurName,  LPCTSTR szName,  LPCTSTR szPatronymic,
                LPCTSTR szMSurName, LPCTSTR szMName, LPCTSTR szMPatronymic,
                LPCTSTR szWSurName, LPCTSTR szWName, LPCTSTR szWPatronymic
               );

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIRTHDLS_H__F9F5996A_CAB0_4C45_B8AC_429C18AA9A4A__INCLUDED_)
