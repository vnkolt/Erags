#if !defined(AFX_BIRTHSURNAMESDLG_H__61A5C8BD_9120_4A0E_B0F6_1B177CF0474D__INCLUDED_)
#define AFX_BIRTHSURNAMESDLG_H__61A5C8BD_9120_4A0E_B0F6_1B177CF0474D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BirthSurnamesDlg.h : header file
//

#include "DialogEx.h"

#include "..\Controls\EraControls.h"
#include "..\Controls\TCToolBar\TCImageList.h"

/////////////////////////////////////////////////////////////////////////////
// CBirthSurnamesDlg dialog
class CBirthSurnamesDlg : public CDialogEx {
// Construction
public:
	CBirthSurnamesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBirthSurnamesDlg)
	enum { IDD = IDD_BIRTH_NAMES };
	CEraNameEdit	m_Surname;
	CEraNameEdit	m_OldSurname;
	CEraNameEdit	m_NewSurname;
  CXButtonXP    m_btnOne;
  CXButtonXP    m_btnTwo;
	CString	m_szNewSurname;
	CString	m_szOldSurname;
	//}}AFX_DATA
  CTCImageList  m_RadioIL;
  CString       m_szSurname;
  BOOL          m_fTwoSurnames;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBirthSurnamesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBirthSurnamesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSingleSurname();
	afx_msg void OnTwoSurnames();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIRTHSURNAMESDLG_H__61A5C8BD_9120_4A0E_B0F6_1B177CF0474D__INCLUDED_)
