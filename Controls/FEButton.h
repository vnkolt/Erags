#if !defined(AFX_FEBUTTON_H__1808AFC0_B0A2_11D4_B625_A1459D96AB20__INCLUDED_)
#define AFX_FEBUTTON_H__1808AFC0_B0A2_11D4_B625_A1459D96AB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FEButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyButton window

//#define WM_BUTTONDOWN WM_USER + 101

class CFEButton : public CButton
{
// Construction
public:
	CFEButton();
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFEButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFEButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFEButton)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FEBUTTON_H__1808AFC0_B0A2_11D4_B625_A1459D96AB20__INCLUDED_)
