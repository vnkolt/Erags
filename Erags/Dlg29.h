#if !defined(AFX_DLG29_H__62A1A8DA_30A1_48D0_8983_29573BE1282B__INCLUDED_)
#define AFX_DLG29_H__62A1A8DA_30A1_48D0_8983_29573BE1282B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg29.h : header file
//

#include "DialogEx.h"
#include "..\Controls\EraControls.h"

class CFormChange;
/////////////////////////////////////////////////////////////////////////////
// CDlg29 dialog

class CDlg29 : public CDialogEx
{
// Construction
public:
	CDlg29(UINT PrintID, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg29)
	enum { IDD = IDD_CHANGE_29 };
  CStaticBG     m_ToLabel;
	CEraEdit	    m_To;
	CEraEdit	    m_ToRovd;
	CEraEdit	    m_PrImPb;
	CEraEdit	    m_OldPrImPb;
	CEraNameEdit  m_OldSurname;
	CEraNameEdit  m_OldPatronymic;
	CEraNameEdit  m_OldName;
	CEraEdit	    m_Number1;
	CEraEdit	    m_Number2;
	CEraEdit	    m_NewPrImPb;
	CEraDateEdit	m_Date1;
	CEraDateEdit	m_Date2;
	CEraEdit	    m_Address;
	//}}AFX_DATA

  CFormChange* m_pForm;
  UINT         m_PrintID;
  CString      m_sOldSurname, m_sNewSurname;
  CString      m_sOldName, m_sNewName;
  CString      m_sOldPatronymic, m_sNewPatronymic;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg29)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg29)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeDate1();
	afx_msg void OnChangeDate2();
	afx_msg void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG29_H__62A1A8DA_30A1_48D0_8983_29573BE1282B__INCLUDED_)
