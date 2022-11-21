#if !defined(AFX_SEARCHFRM_H__868CB215_CD04_4495_95B1_19D06101D603__INCLUDED_)
#define AFX_SEARCHFRM_H__868CB215_CD04_4495_95B1_19D06101D603__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchFrm frame

class CSearchFrm : public CFrameWnd
{
	DECLARE_DYNCREATE(CSearchFrm)
protected:
	CSearchFrm();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchFrm)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSearchFrm();

	// Generated message map functions
	//{{AFX_MSG(CSearchFrm)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHFRM_H__868CB215_CD04_4495_95B1_19D06101D603__INCLUDED_)
