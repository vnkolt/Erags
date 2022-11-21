#if !defined(AFX_CANTOPENDLG_H__9583A0BB_1BA5_4B70_9741_9C5EF1D8F125__INCLUDED_)
#define AFX_CANTOPENDLG_H__9583A0BB_1BA5_4B70_9741_9C5EF1D8F125__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CantOpenDlg.h : header file
//
#include "DialogEx.h"
#include "..\Controls\AutoRichEditCtrl.h"
#include "..\Controls\TCToolBar\TCImageList.h"

/////////////////////////////////////////////////////////////////////////////
// CCantOpenDlg dialog
class CCantOpenDlg : public CDialogEx {
// Construction
public:
	CCantOpenDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCantOpenDlg)
	enum { IDD = IDD_CANT_OPEN };
	//CAutoRichEditCtrl	m_InfoText;
  CEdit         m_InfoText;
  CXButtonXP    m_Radio1;
  CXButtonXP    m_Radio2;
  CXButtonXP    m_Radio3;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
  CTCImageList  m_RadioIL;
  UINT          m_idCheckedButton;
  CString       m_szFilename;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCantOpenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCantOpenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CANTOPENDLG_H__9583A0BB_1BA5_4B70_9741_9C5EF1D8F125__INCLUDED_)
