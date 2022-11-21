#if !defined(AFX_EXPIREDDLG_H__CAFF4FFC_F019_4B17_ABF8_7B3D3B4848FC__INCLUDED_)
#define AFX_EXPIREDDLG_H__CAFF4FFC_F019_4B17_ABF8_7B3D3B4848FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExpiredDlg.h : header file
//

#include "..\Controls\Label.h"

/////////////////////////////////////////////////////////////////////////////
// CExpiredDlg dialog

class CExpiredDlg : public CDialog
{
// Construction
public:
	CExpiredDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExpiredDlg)
	enum { IDD = IDD_EXPIRED };
	CLabel m_Email;
	//}}AFX_DATA
  CFont m_Font;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpiredDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExpiredDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPIREDDLG_H__CAFF4FFC_F019_4B17_ABF8_7B3D3B4848FC__INCLUDED_)
