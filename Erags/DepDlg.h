#if !defined(AFX_DEPDLG_H__C5F8B6AF_1AF1_45D6_99F7_B84F6574301E__INCLUDED_)
#define AFX_DEPDLG_H__C5F8B6AF_1AF1_45D6_99F7_B84F6574301E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DepDlg.h : header file
//

#include "DialogEx.h"
#include "..\Controls\EraControls.h"

#define MAX_DEPROWS 12

class   CFormChange;


/////////////////////////////////////////////////////////////////////////////
// CDepDlg dialog
class CDepDlg : public CDialogEx {
// Construction
public:
	CDepDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDepDlg)
	enum { IDD = IDD_DEPENDENCES };
	//}}AFX_DATA
	CEraComboBox	m_Type[MAX_DEPROWS];
	CEraEdit	    m_Number[MAX_DEPROWS];
	CEraDateEdit	m_Date[MAX_DEPROWS];
	CEraComboBox	m_Rags[MAX_DEPROWS];
	CEraNameEdit	m_Who[MAX_DEPROWS];

  CFormChange*      m_pForm;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDepDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
  void  UpdateWho( int nIndex );

	// Generated message map functions
	//{{AFX_MSG(CDepDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEPDLG_H__C5F8B6AF_1AF1_45D6_99F7_B84F6574301E__INCLUDED_)
