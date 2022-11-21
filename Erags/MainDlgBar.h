#if !defined(AFX_MAINDLGBAR_H__5796C940_8843_4063_8AF5_5ED3D9075705__INCLUDED_)
#define AFX_MAINDLGBAR_H__5796C940_8843_4063_8AF5_5ED3D9075705__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainDlgBar.h : header file
//

#include "..\Controls\MyBtnST.h"
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

  CMyButtonST	m_btnFolderTree;
  CMyButtonST	m_btnFileNew;
  CMyButtonST	m_btnFileOpen;
  CMyButtonST	m_btnFileRecent;

  CMyButtonST	m_btnBirth;
  CMyButtonST	m_btnMarriage;
  CMyButtonST	m_btnDivorce;
  CMyButtonST	m_btnChange;
  CMyButtonST	m_btnDeath;
  CMyButtonST	m_btnExtNotes;
  CMyButtonST	m_btnGeography;
  CMyButtonST	m_btnRedCross;
  CMyButtonST	m_btnCityHall;
  CMyButtonST	m_btnUkraine;
  CMyButtonST	m_btnUAH;

  CMyButtonST	m_btnFirst;
  CMyButtonST	m_btnPrev;
  CMyButtonST	m_btnNext;
  CMyButtonST	m_btnLast;
  CMyButtonST	m_btnNew;
  CMyButtonST	m_btnDelete;

  CMyButtonST	m_btnFindIn;
  CMyButtonST	m_btnFindOut;

  CMyButtonST	m_btnPrint;
  CMyButtonST	m_btnWord;
  CMyButtonST	m_btnTemplates;

  CMyButtonST	m_btnHelp;

// Operations:
public:
  void  SetBkColor(BOOL bRepaint=TRUE);
  void  SetOfficeButtons();

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
