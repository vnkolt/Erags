#if !defined(AFX_COPY2XLDLG_H__13161BC4_0115_49E8_9705_DEC47FA9046C__INCLUDED_)
#define AFX_COPY2XLDLG_H__13161BC4_0115_49E8_9705_DEC47FA9046C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Copy2XLDlg.h : header file
//

#include "DialogEx.h"
#include "..\Controls\AutoRichEditCtrl.h"
#include "..\Controls\TCToolBar\TCImageList.h"

/////////////////////////////////////////////////////////////////////////////
// CCopy2XLDlg dialog
class CCopy2XLDlg : public CDialogEx {
// Construction
public:
	CCopy2XLDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCopy2XLDlg)
	enum { IDD = IDD_COPY2EXCEL };
  CXButtonXP    m_rbEachToEach;
  CXButtonXP    m_rbAllToOne;
	//}}AFX_DATA
  CTCImageList  m_RadioIL;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopy2XLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCopy2XLDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern BOOL g_fAllToOne;


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCopy2XLDlg_H__13161BC4_0115_49E8_9705_DEC47FA9046C__INCLUDED_)
