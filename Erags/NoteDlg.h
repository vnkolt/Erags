#if !defined(AFX_NOTEDLG_H__4289E201_C2C7_11D4_8EBB_008048E47427__INCLUDED_)
#define AFX_NOTEDLG_H__4289E201_C2C7_11D4_8EBB_008048E47427__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NoteDlg.h : header file
//

#include "DialogEx.h"
/////////////////////////////////////////////////////////////////////////////
// CNoteDlg dialog
class CNoteDlg : public CDialogEx {
// Construction
public:
	CNoteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNoteDlg)
	enum { IDD = IDD_NOTEDLG };
	CString	m_sNote;
	//}}AFX_DATA
  UINT  m_nPos;
  BOOL  m_fMale;
  DATE  m_d;
  COleDateTime* m_pD1;
  COleDateTime* m_pD2;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNoteDlg)
	afx_msg void OnNoteMenu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTEDLG_H__4289E201_C2C7_11D4_8EBB_008048E47427__INCLUDED_)
