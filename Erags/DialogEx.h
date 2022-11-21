#if !defined(AFX_DIALOGEX_H__653B9141_3FA6_11D3_AC51_EA76109A7558__INCLUDED_)
#define AFX_DIALOGEX_H__653B9141_3FA6_11D3_AC51_EA76109A7558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogEx.h : header file
//

#include "..\Controls\XButtonXP.h"
//#include "..\Controls\BtnST.h"
#include "..\Controls\BkgndCtrl.h"

class CDlgToolBar : public CToolBar {   
// Construction
public:
	CDlgToolBar();
   
// Implementation
public:   
	virtual ~CDlgToolBar();

protected:                
	// Generated message map functions
	//{{AFX_MSG(CDlgToolBar)
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};        


/////////////////////////////////////////////////////////////////////////////
// CDialogEx dialog
#define CDialogExBase CDialogBG
class CDialogEx : public CDialogExBase
{
// Construction
public:
	CDialogEx(UINT nIDTemplate, CWnd* pParentWnd = NULL);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogEx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont	m_Font;
  BOOL        m_fYes;
  BOOL        m_fNo;
	CXButtonXP	m_btnOk;
	CXButtonXP	m_btnCancel;
// Implementation
protected:
  void         PumpMessages();
  virtual void LoadBitmaps();
  virtual void OnYes();
  virtual void OnNo();

	// Generated message map functions
	//{{AFX_MSG(CDialogEx)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGEX_H__653B9141_3FA6_11D3_AC51_EA76109A7558__INCLUDED_)
