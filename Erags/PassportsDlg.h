#if !defined(AFX_PASSPORTSDLG_H__D898A9A6_ED11_46A4_8141_9D54DFDE0A13__INCLUDED_)
#define AFX_PASSPORTSDLG_H__D898A9A6_ED11_46A4_8141_9D54DFDE0A13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PassportsDlg.h : header file
//

#include "..\Controls\EraControls.h"
#include "..\Controls\EraMonthCalCtrl.h"
#include "DialogEx.h"

class CRSBirthes;
/////////////////////////////////////////////////////////////////////////////
// CPassportsDlg dialog

class CPassportsDlg : public CDialogEx
{
// Construction
public:
	CPassportsDlg(CRSBirthes* pSet,
                CEraEdit*           pWndMemo,
                CEraPassportButton* pWndType1,
                CEraSeriaEdit*      pWndSeria1,
                CEraEdit*           pWndNumber1,
                CEraDateEdit*       pWndDate1,
                CEraComboBox*       pWndBy1,
                CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPassportsDlg)
	enum { IDD = IDD_PASSPORTS };
  CFrameBG            m_Frame1;
  CFrameBG            m_Frame2;
	CEraPassportButton	m_Type1;
	CEraPassportButton	m_Type2;
	CEraSeriaEdit	      m_Seria1;
	CEraSeriaEdit	      m_Seria2;
	CEraEdit          	m_Number1;
	CEraEdit          	m_Number2;
	CEraDateEdit        m_Date1;
	CEraDateEdit        m_Date2;
	CEraComboBox      	m_By1;
	CEraComboBox      	m_By2;
	CEraEdit	          m_ExtNotice;
	//}}AFX_DATA

  CEraMonthCalCtrl    m_Calendar;

  CRSBirthes*   m_pSet;

  CEraEdit*           m_pWndMemo;
  CEraPassportButton* m_pWndType1;
  CEraSeriaEdit*      m_pWndSeria1;
  CEraEdit*           m_pWndNumber1;
  CEraDateEdit*       m_pWndDate1;
  CEraComboBox*       m_pWndBy1;

  COleDateTime  m_date1;
  COleDateTime  m_date2;
  CString       m_sMemo;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassportsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPassportsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAll2();
	afx_msg void OnYes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSPORTSDLG_H__D898A9A6_ED11_46A4_8141_9D54DFDE0A13__INCLUDED_)
