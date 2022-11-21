#if !defined(AFX_EMPTYTABLEDLG_H__731D7A64_F6CE_4DE0_AFA4_0883BD6B3A84__INCLUDED_)
#define AFX_EMPTYTABLEDLG_H__731D7A64_F6CE_4DE0_AFA4_0883BD6B3A84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmptyTableDlg.h : header file
//

#include "DialogEx.h"
#include "..\Controls\TCToolBar\TCImageList.h"

/////////////////////////////////////////////////////////////////////////////
// CEmptyTableDlg dialog

class CEmptyTableDlg : public CDialogEx
{
// Construction
public:
	CEmptyTableDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEmptyTableDlg)
	enum { IDD = IDD_OPEN_RECORD };
	CStaticBG   m_Info;
  CXButtonXP  m_Radio1;
  CXButtonXP  m_Radio2;
  CXButtonXP  m_Radio3;
  CXButtonXP  m_Radio4;
  CXButtonXP  m_Radio5;
	//}}AFX_DATA
  CTCImageList  m_RadioIL;
  int           m_nPrinPos;
  int           m_FormID;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmptyTableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEmptyTableDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMPTYTABLEDLG_H__731D7A64_F6CE_4DE0_AFA4_0883BD6B3A84__INCLUDED_)
