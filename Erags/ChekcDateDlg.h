#if !defined(AFX_CHEKDATEDLG_H__3481812D_E0BF_4824_AD2B_7AFBAC4321DC__INCLUDED_)
#define AFX_CHEKDATEDLG_H__3481812D_E0BF_4824_AD2B_7AFBAC4321DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChekDateDlg.h : header file
//
#include "DialogEx.h"

class CEraDateEdit;

/////////////////////////////////////////////////////////////////////////////
// CCheckDateDlg dialog

class CCheckDateDlg : public CDialogEx
{
// Construction
public:
	CCheckDateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckDateDlg)
	enum { IDD = IDD_CHECKDATE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

  CString m_szNameBefore;
  CString m_szNameAfter;

  CString m_szToEdit1;
  CString m_szToEdit2;
  CString m_szMessage;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckDateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCheckDateDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BOOL  CheckDates(CEraDateEdit* pBefore, LPCTSTR szNameBefore,
                 CEraDateEdit* pAfter, LPCTSTR szNameAfter,
                 BOOL fBeforeDef);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHEKDATEDLG_H__3481812D_E0BF_4824_AD2B_7AFBAC4321DC__INCLUDED_)
