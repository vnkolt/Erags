#if !defined(AFX_DBGRIDDLG_H__2A0D99C6_89F5_4161_92F2_17300BC748FD__INCLUDED_)
#define AFX_DBGRIDDLG_H__2A0D99C6_89F5_4161_92F2_17300BC748FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBGridDlg.h : header file
//

#include ".\DBGrid.h"
#include "..\Controls\BkgndCtrl.h"

class CDBGridToolBar : public CToolBar {   
// Construction
public:
	CDBGridToolBar();
   
// Implementation
public:   
	virtual ~CDBGridToolBar();

protected:                
	// Generated message map functions
	//{{AFX_MSG(CDBGridToolBar)
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};        


/////////////////////////////////////////////////////////////////////////////
// CDBGridDlg dialog

class CDBGridDlg : public CDialogBG {
// Construction
public:
	CDBGridDlg(CWnd* pParent = NULL, UINT id=IDD_DBGRID);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBGridDlg)
	enum { IDD = IDD_DBGRID };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
  CDBGrid         m_Grid;
	CDBGridToolBar	m_toolBar;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBGridDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDBGridDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateRecordEdit(CCmdUI* pCmdUI);
	afx_msg void OnRecordEdit();
	afx_msg void OnUpdateRecordNew(CCmdUI* pCmdUI);
	afx_msg void OnRecordNew();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg void OnRecordDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBGRIDDLG_H__2A0D99C6_89F5_4161_92F2_17300BC748FD__INCLUDED_)
