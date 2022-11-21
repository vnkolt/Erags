#if !defined(AFX_NOTECHANGE_H__5B68BC17_936C_4574_8C43_3B7F736C5478__INCLUDED_)
#define AFX_NOTECHANGE_H__5B68BC17_936C_4574_8C43_3B7F736C5478__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NoteChange.h : header file
//

#include "DialogEx.h"
#include "..\Controls\EraControls.h"

class CFormChange;

/////////////////////////////////////////////////////////////////////////////
// CNoteChange dialog

class CNoteChange : public CDialogEx {
// Construction
public:
	CNoteChange(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNoteChange)
	enum { IDD = IDD_NOTECHANGE };
	CEraEdit	    m_Change;
	CStaticBG     m_Citizen_RV;
	CStaticBG     m_Citizen_DV;
	CEraNameEdit	m_Surname_RV;
	CEraNameEdit	m_Name_RV;
	CEraNameEdit	m_Father_RV;
	CEraNameEdit	m_Surname_DV;
	CEraNameEdit	m_Name_DV;
	CEraNameEdit	m_Father_DV;
	CListCtrl	m_listAct;
	//}}AFX_DATA

  CFormChange*  m_pForm;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoteChange)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void AddToChange(int nGraph, LPCTSTR sOld, LPCTSTR sNew);

	// Generated message map functions
	//{{AFX_MSG(CNoteChange)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
	afx_msg void OnClickActlist(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTECHANGE_H__5B68BC17_936C_4574_8C43_3B7F736C5478__INCLUDED_)
