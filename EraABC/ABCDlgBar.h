#if !defined(AFX_ABCDLGBAR_H__6F04CC0D_6CDD_4688_8818_58BF46B4889D__INCLUDED_)
#define AFX_ABCDLGBAR_H__6F04CC0D_6CDD_4688_8818_58BF46B4889D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ABCDlgBar.h : header file
//

#include "..\Controls\BtnST.h"

/////////////////////////////////////////////////////////////////////////////
// CABCDlgBar dialog

class CABCDlgBar : public CDialogBar
{
// Construction
public:
	CABCDlgBar();   // standard constructor

  BOOL Create(CWnd* pParentWnd);

// Dialog Data
	//{{AFX_DATA(CABCDlgBar)
	enum { IDD = IDR_MAINFRAME };
	CButtonST	m_btnFileNew;
	CButtonST	m_btnFileOpen;
	CButtonST	m_btnBirth;
	CButtonST	m_btnMarriage;
  CButtonST	m_btnDivorce;
  CButtonST	m_btnChange;
  CButtonST	m_btnDeath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CABCDlgBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CABCDlgBar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABCDLGBAR_H__6F04CC0D_6CDD_4688_8818_58BF46B4889D__INCLUDED_)
