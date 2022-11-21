#if !defined(AFX_ERABUTTON_H__1459A493_5443_433C_B9FC_CD48B9B4017D__INCLUDED_)
#define AFX_ERABUTTON_H__1459A493_5443_433C_B9FC_CD48B9B4017D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EraButton.h : header file
//

extern COLORREF g_clrBackColor;
extern COLORREF g_clrForeColor;
extern COLORREF g_clrFocusBackColor;
extern COLORREF g_clrFocusForeColor;

extern COLORREF g_clrMaleBackColor;
extern COLORREF g_clrFemaleBackColor;
extern COLORREF g_clrMaleForeColor;
extern COLORREF g_clrFemaleForeColor;

extern HBRUSH g_hEditBrush, g_hFocusEditBrush;

extern LPCTSTR g_szDateFormat, g_szDateMask;

/////////////////////////////////////////////////////////////////////////////
// CEraButton window
class CEraButton : public CButton
{
// Construction
public:
	CEraButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraButton)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEraButton)
  afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CEraBitmapButton window
class CEraBitmapButton : public CBitmapButton {
  DECLARE_DYNAMIC(CEraBitmapButton)
public:
  CEraBitmapButton();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraButton)
	protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	// Generated message map functions
protected:
	//{{AFX_MSG(CEraBitmapButton)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CEraToggleButton window

class CEraToggleButton : public CEraButton {
// Construction
public:
	CEraToggleButton();

// Attributes
public:
  CString   m_strOnText, m_strOffText;
  COLORREF  m_clrForeOn, m_clrForeOff;
  COLORREF  m_clrBackOn, m_clrBackOff;
  COLORREF  m_clrFocusForeOn, m_clrFocusForeOff;
  COLORREF  m_clrFocusBackOn, m_clrFocusBackOff;

  BOOL      m_bOn, m_bFocusFore, m_bFocusBack;
  CFont     m_Font;

// Operations
public:
  BOOL  IsOn() { return m_bOn; }
  void  SetFont(LPCTSTR szFontName, LONG lfHeight, LONG lfWeight, BYTE lfItalic=FALSE);
  void  SetText(LPCTSTR szOnText, LPCTSTR szOffText);
  void  SetBackColor(COLORREF clrOn, COLORREF clrOff, bool bForFocus=false);
  void  SetForeColor(COLORREF clrOn, COLORREF clrOff, bool bForFocus=false);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraToggleButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraToggleButton();

	// Generated message map functions
protected:
  
	//{{AFX_MSG(CEraToggleButton)
	afx_msg void OnClicked();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
  afx_msg LRESULT OnGetCheck(WPARAM, LPARAM);
  afx_msg LRESULT OnSetCheck(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
};

/************************************** : by VK at 21.05.2005 12:00:58 **\
class CEraMultiStateButton : public CEraButton {
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
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
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
\************************************** : by VK at 21.05.2005 12:01:07 **/

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERABUTTON_H__1459A493_5443_433C_B9FC_CD48B9B4017D__INCLUDED_)
