#if !defined(AFX_RAGSINFODLG_H__6BB8AD74_AF50_41AB_97CF_BED5FE7594CE__INCLUDED_)
#define AFX_RAGSINFODLG_H__6BB8AD74_AF50_41AB_97CF_BED5FE7594CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RagsInfoDlg.h : header file
//
#include "DialogEx.h"
/////////////////////////////////////////////////////////////////////////////
// CRagsInfoDlg dialog

class CRagsInfoDlg : public CDialogEx
{
// Construction
public:
	CRagsInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRagsInfoDlg)
	enum { IDD = IDD_REGKEYS };
	CTreeCtrl	m_RTree;
	CString	m_szCity;
	CString	m_szDistrict;
	CString	m_szRegion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRagsInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRagsInfoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAGSINFODLG_H__6BB8AD74_AF50_41AB_97CF_BED5FE7594CE__INCLUDED_)
