#if !defined(AFX_TABCTRLBG_H__537FB33C_0B54_45F0_8EAB_908A05E4E655__INCLUDED_)
#define AFX_TABCTRLBG_H__537FB33C_0B54_45F0_8EAB_908A05E4E655__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabCtrlBG.h : header file
//

#include "EnTabCtrl.h"

#define CTabCtrlBGBase  CEnTabCtrl

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlBG window

class CTabCtrlBG : public CTabCtrlBGBase
{
// Construction
public:
	CTabCtrlBG();

// Attributes
public:
  BOOL  m_fGradientFill;
  BOOL  m_bFlat;
  BOOL  m_bBackColor;
  DWORD m_dwFlags;
// Operations
public:
  void  ResetStyles(DWORD dwFlags, BOOL bFlat, COLORREF clrBk);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabCtrlBG)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabCtrlBG();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabCtrlBG)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABCTRLBG_H__537FB33C_0B54_45F0_8EAB_908A05E4E655__INCLUDED_)
