#if !defined(AFX_CDMENU_H__09D4CAD8_0BA2_4721_94BD_32A05F8058CB__INCLUDED_)
#define AFX_CDMENU_H__09D4CAD8_0BA2_4721_94BD_32A05F8058CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CDMenu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCDMenu dialog

class CCDMenu : public CDialog
{
// Construction
public:
	CCDMenu(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCDMenu)
	enum { IDD = IDD_MENU };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDMenu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCDMenu)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDMENU_H__09D4CAD8_0BA2_4721_94BD_32A05F8058CB__INCLUDED_)
