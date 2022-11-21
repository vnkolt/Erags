#if !defined(AFX_ERADOWNBTN_H__2DF47825_B2EA_4869_A707_091AA24884A2__INCLUDED_)
#define AFX_ERADOWNBTN_H__2DF47825_B2EA_4869_A707_091AA24884A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EraDownBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEraDownBtn window

class CEraDownBtn : public CButton
{
// Construction
public:
	CEraDownBtn();

// Attributes
public:
  DWORD m_dwBtnStyle;
  bool  m_fDropDown;
  bool  m_fOffByBtn;
  bool  m_fCalendarOn;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraDownBtn)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraDownBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEraDownBtn)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnClicked();
	//}}AFX_MSG
  afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERADOWNBTN_H__2DF47825_B2EA_4869_A707_091AA24884A2__INCLUDED_)
