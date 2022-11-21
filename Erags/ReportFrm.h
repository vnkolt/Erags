#if !defined(AFX_REPORTFRM_H__ADA715C8_8CE8_4AB0_8976_9C145758122B__INCLUDED_)
#define AFX_REPORTFRM_H__ADA715C8_8CE8_4AB0_8976_9C145758122B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportFrm.h : header file
//

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CReportFrame frame

class CReportFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CReportFrame)
protected:
	CReportFrame();           // protected constructor used by dynamic creation

// Attributes
public:
  CMDIChildWnd* m_pPrevFrame;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CReportFrame();

	// Generated message map functions
	//{{AFX_MSG(CReportFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTFRM_H__ADA715C8_8CE8_4AB0_8976_9C145758122B__INCLUDED_)
