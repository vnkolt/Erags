#if !defined(AFX_BLANKSDLG_H__AE45FD73_4713_46CC_A89E_36920F41F7DA__INCLUDED_)
#define AFX_BLANKSDLG_H__AE45FD73_4713_46CC_A89E_36920F41F7DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BlanksDlg.h : header file
//

#include "DialogEx.h"

#include "..\Controls\EraControls.h"
#include "..\Controls\TCToolBar\TCImageList.h"

/////////////////////////////////////////////////////////////////////////////
// CBlanksDlg dialog
class CBlanksDlg : public CDialogEx {
// Construction
public:
	CBlanksDlg(const COleDateTime& odt, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBlanksDlg)
	enum { IDD = IDD_BLANKS };
  CFrameBG      m_Frame1;
	CListBox	    m_MonList;
	CXButtonXP    m_chkPeriod;
	CEraDateEdit	m_Till;
	CEraDateEdit	m_From;
  CXButtonXP    m_chkBirth;
  CXButtonXP    m_chkMarriage;
  CXButtonXP    m_chkDeath;
	//}}AFX_DATA

  CTCImageList        m_CheckBoxIL;
  BOOL                m_bCheckPeriod;
  COleDateTime        m_odt;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlanksDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBlanksDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnSelchangeMonlist();
  afx_msg void OnPeriod();
  afx_msg void OnYes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLANKSDLG_H__AE45FD73_4713_46CC_A89E_36920F41F7DA__INCLUDED_)
