#if !defined(AFX_MAINDLGBAR_H__5796C940_8843_4063_8AF5_5ED3D9075705__INCLUDED_)
#define AFX_MAINDLGBAR_H__5796C940_8843_4063_8AF5_5ED3D9075705__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainDlgBar.h : header file
//

#include "..\Controls\BtnST.h"
#include "..\Controls\BkgndCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CMainDlgBar dialog
class CMainDlgBar : public CDialogBarBG {
// Construction
public:
	CMainDlgBar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDlgBar)
	enum { IDD = IDTB_MAIN_TOOLBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

  CButtonST	m_btnFolderTree;
  CButtonST	m_btnFileNew;
  CButtonST	m_btnFileOpen;
  CButtonST	m_btnFileRecent;

  CButtonST	m_btnFirst;
  CButtonST	m_btnPrev;
  CButtonST	m_btnNext;
  CButtonST	m_btnLast;
  CButtonST	m_btnNew;
  CButtonST	m_btnDelete;

  CButtonST	m_btnHelp;

// Operations:
public:
  void  SetBkColor(BOOL bRepaint=TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlgBar)
	public:
	virtual BOOL Create(CWnd* pParentWnd);
	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainDlgBar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLGBAR_H__5796C940_8843_4063_8AF5_5ED3D9075705__INCLUDED_)
