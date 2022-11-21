#if !defined(AFX_DBGRIDDLG_H__2A0D99C6_89F5_4161_92F2_17300BC748FD__INCLUDED_)
#define AFX_DBGRIDDLG_H__2A0D99C6_89F5_4161_92F2_17300BC748FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBGridDlg.h : header file
//
#include "DBGrid.h"
#include "..\Controls\BkgndCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDBGridView dialog
#define CDBGridViewBase CFormViewBG
class CDBGridView : public CDBGridViewBase {
// Construction
public:
	CDBGridView(CWnd* pParent = NULL, UINT id=IDD_DBGRID);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBGridView)
	enum { IDD = IDD_DBGRID };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
  CDBGrid         m_Grid;
	//CDBGridToolBar	m_toolBar;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBGridView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Operations
public:
  BOOL  Create(UINT uID);
// Implementation
protected:
  virtual ~CDBGridView();
public:

	// Generated message map functions
	//{{AFX_MSG(CDBGridView)
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBGRIDDLG_H__2A0D99C6_89F5_4161_92F2_17300BC748FD__INCLUDED_)
