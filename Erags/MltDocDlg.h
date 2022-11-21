#if !defined(AFX_MLTDOCDLG_H__6207FDBB_E76E_4033_BB6D_E94AA38FBE5A__INCLUDED_)
#define AFX_MLTDOCDLG_H__6207FDBB_E76E_4033_BB6D_E94AA38FBE5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MltDocDlg.h : header file
//

#include "..\Controls\EraControls.h"
#include "DialogEx.h"
#include "..\Controls\TCToolBar\TCImageList.h"

class CRSDeathes;
/////////////////////////////////////////////////////////////////////////////
// CMltDocDlg dialog

class CMltDocDlg : public CDialogEx
{
// Construction
public:
	CMltDocDlg(CRSDeathes* pSet, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMltDocDlg)
	enum { IDD = IDD_MILITARY };
	CEraEdit	    m_Seria;
	CEraEdit	    m_Number;
	CEraDateEdit	m_Date;
	CEraEdit	    m_By;
	CEraEdit	    m_ExtNotice;
    CXButtonXP      m_chkNoData;
	//}}AFX_DATA

  CTCImageList      m_CheckBoxIL;
  CRSDeathes*       m_pSet;
  COleDateTime      m_odt;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMltDocDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void  EnableControls();

	// Generated message map functions
	//{{AFX_MSG(CMltDocDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNodata();
	afx_msg void OnYes();
  afx_msg void OnSetAll();
	afx_msg void OnSetfocusMiloffice();
	//}}AFX_MSG
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MLTDOCDLG_H__6207FDBB_E76E_4033_BB6D_E94AA38FBE5A__INCLUDED_)
