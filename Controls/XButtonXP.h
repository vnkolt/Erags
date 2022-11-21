// XButtonXP.h  Version 1.2
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// This software is released into the public domain.  You are free to use
// it in any way you like, except that you may not sell this source code.
//
// This software is provided "as is" with no expressed or implied warranty.
// I accept no liability for any damage or loss of business that this
// software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef  XBUTTONXP_H 
#define  XBUTTONXP_H 

/************************************** : by VK at 18.05.2005 22:58:18 **\
#include "uxtheme.h"
\************************************** : by VK at 18.05.2005 22:58:21 **/

#include "OddButton.h"
#include "VisualStylesXP.h"


////////////////////////////////////////////////////////////////////////////
// CFrameBG
class CFrameBG : public CStatic {
  DECLARE_DYNCREATE(CFrameBG)

public:
  CFrameBG();
  ~CFrameBG();

  BOOL      IsThemed();
	HTHEME		   m_hTheme;
  BOOL         m_bFirstTime;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFrameBG)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CXButtonXP window
class CXButtonXP : public COddButton
{
// Construction
public:
	CXButtonXP();
	virtual ~CXButtonXP();

// Attributes
public:
	enum ICON_ALIGNMENT
	{
		CENTER = 0,
		LEFT,
		RIGHT
	};

	void SetIconAlignment(ICON_ALIGNMENT ia) 
	{ 
		m_eIconAlignment = ia; 
		RedrawWindow();
	}
	BOOL GetToggle() { return m_bIsToggle; }
	void SetToggle(BOOL bIsToggle) 
	{ 
		m_bIsToggle = bIsToggle;
		m_bToggled  = FALSE;
		RedrawWindow();
	}
	BOOL GetToggleState() { return m_bToggled; }
	void SetToggleState(BOOL bToggled) { m_bToggled = bToggled; RedrawWindow(); }
	void EnableTheming(BOOL bEnable) 
	{ 
		m_bEnableTheming = bEnable; 
		if (m_bEnableTheming)
		{
			TRACE(_T("Theming will be enabled only on XP and only ")
				  _T("if the app is themed with a manifest file.\n"));
		}
		RedrawWindow();
	}
	BOOL IsThemed();
	BOOL GetDrawToolbar() { return m_bDrawToolbar; }
	void SetDrawToolbar(BOOL bDrawToolbar) 
	{ 
		m_bDrawToolbar = bDrawToolbar; 
		m_bFirstTime = TRUE;	// force OpenThemeData() call
		RedrawWindow();
	}


// Operations
public:
	void SetIcon(UINT nIDResource, ICON_ALIGNMENT ia = LEFT);
	void SetIcon(HICON hIcon, ICON_ALIGNMENT ia = LEFT);
  void ResetIcons();
  void SetIcons(UINT nIDIconOn, UINT nIDIconOff, ICON_ALIGNMENT iaOn = LEFT, ICON_ALIGNMENT iaOff = LEFT);

  void SetImageList(CImageList* pImageList);
  void SetRadioImageList(CImageList* pImageList);
  void SetCheckBoxImageList(CImageList* pImageList);
  void  SetRadio(UINT idFirst, UINT idLast) {
    m_FirstID = idFirst; m_LastID = idLast;
  }

  BOOL  IsOn() { return m_bOn; }
  void  SetFont(LPCTSTR szFontName, LONG lfHeight, LONG lfWeight, BYTE lfItalic=FALSE);
  void  SetText(LPCTSTR szOnText, LPCTSTR szOffText);
  void  SetBackColor(COLORREF clrOn, COLORREF clrOff, bool bForFocus=false);
  void  SetForeColor(COLORREF clrOn, COLORREF clrOff, bool bForFocus=false);
  
  void  InitToolTip();
  void  SetTooltipText(int nText, BOOL bActivate);
  void  SetTooltipText(LPCTSTR lpszText, BOOL bActivate);
  void  ActivateTooltip(BOOL bActivate);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXButtonXP)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DrawIcon(CDC *pDC, HICON hIcon,
				  BOOL bHasText, 
				  RECT& rectItem, 
				  RECT& rectText, 
				  BOOL bIsPressed, 
				  BOOL bIsDisabled);

	void PrepareImageRect(BOOL bHasText, 
						  RECT& rectItem, 
						  RECT& rectText, 
						  BOOL bIsPressed, 
						  DWORD dwWidth, 
						  DWORD dwHeight, 
						  RECT& rectImage);


  CString   m_strOnText, m_strOffText;
  COLORREF  m_clrForeOn, m_clrForeOff;
  COLORREF  m_clrBackOn, m_clrBackOff;
  COLORREF  m_clrFocusForeOn, m_clrFocusForeOff;
  COLORREF  m_clrFocusBackOn, m_clrFocusBackOff;

  CToolTipCtrl m_ToolTip;			// Tooltip

  BOOL      m_fReturnAsTab;
  BOOL      m_bOn, m_fRadio, m_fCheckBox, m_bFocusFore, m_bFocusBack;
  CFont     m_Font;

	BOOL			m_bFirstTime, m_fDestroyIcons;
	BOOL			m_bMouseOverButton;
	HTHEME		m_hTheme;
	HICON			m_hIcon;
  HICON			m_hIcons[8];
  UINT            m_nIDIconOn, m_nIDIconOff;
  ICON_ALIGNMENT  m_iaOn, m_iaOff;
  UINT      m_FirstID, m_LastID;

	ICON_ALIGNMENT	m_eIconAlignment;
	BOOL			m_bToggled;
	BOOL			m_bIsToggle;
	BOOL			m_bLButtonDown;
	BOOL			m_bSent;
	BOOL			m_bEnableTheming;
	BOOL			m_bDrawToolbar;
  BOOL			m_fClickDown;

	void      EraseBkgnd(CDC* pDC, CRect& rect, BOOL bFocus);

	// Generated message map functions
	//{{AFX_MSG(CXButtonXP)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClicked();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
  afx_msg LRESULT OnGetCheck(WPARAM, LPARAM);
  afx_msg LRESULT OnSetCheck(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
};

class CEraXButtonXP : public CXButtonXP {
public:
  CEraXButtonXP() { m_fReturnAsTab = TRUE; }
};

class CEraMultiStateButton : public CEraXButtonXP {
// Attrinutes
private:
  CStringArray  m_StateNames;
  CDWordArray   m_ForeColors;
public:
  COLORREF  m_clrFore, m_clrBack;
  int       m_nCurrentState;
// Construction
public:
	CEraMultiStateButton();
// Operation:
  void  AddState(int nIndex, LPCTSTR szName);
  void  AddColorState(int nIndex, COLORREF clr, LPCTSTR szName);

  void SetIndex(int nIndex);
  int  GetIndex();

// Implementation
public:
	virtual ~CEraMultiStateButton();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraMultiStateButton)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
  
	//{{AFX_MSG(CEraMultiStateButton)
	afx_msg void OnClicked();
//	afx_msg void OnSetFocus(CWnd* pOldWnd);
//	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

class CEraPassportButton : public CEraMultiStateButton {
public:
  CEraPassportButton();
};

class CEraMWPassportButton : public CEraMultiStateButton {
public:
  CEraMWPassportButton();
};



void AFXAPI DDX_MSButton(CDataExchange* pDX, int nIDC, CEraMultiStateButton& rControl, BYTE& byte);
void AFXAPI DDX_MSButton(CDataExchange* pDX, int nIDC, CEraMultiStateButton& rControl, BOOL& bFlag);


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // XBUTTONXP_H 
