#if !defined(AFX_ERALABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
#define AFX_ERALABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Label.h : header file
//

#define	NM_LINKCLICK	WM_APP + 0x200

/////////////////////////////////////////////////////////////////////////////
// CEraLabel window

class CEraLabel : public CStatic
{
// Construction
public:
	enum FlashType {None, Text, Background };
	enum Type3D { Raised, Sunken};

	CEraLabel();
	virtual CEraLabel& SetBkColor(COLORREF crBkgnd);
	virtual CEraLabel& SetTextColor(COLORREF crText);
	virtual CEraLabel& SetText(const CString& strText);
	virtual CEraLabel& SetFontBold(BOOL bBold);
	virtual CEraLabel& SetFontName(const CString& strFont);
	virtual CEraLabel& SetFontUnderline(BOOL bSet);
	virtual CEraLabel& SetFontItalic(BOOL bSet);
	virtual CEraLabel& SetFontSize(int nSize);
	virtual CEraLabel& SetSunken(BOOL bSet);
	virtual CEraLabel& SetBorder(BOOL bSet);
	virtual CEraLabel& SetTransparent(BOOL bSet);
	virtual CEraLabel& FlashText(BOOL bActivate);
	virtual CEraLabel& FlashBackground(BOOL bActivate);
	virtual CEraLabel& SetLink(BOOL bLink,BOOL bNotifyParent);
	virtual CEraLabel& SetLinkCursor(HCURSOR hCursor);
	virtual CEraLabel& SetFont3D(BOOL bSet,Type3D type=Raised);
	virtual CEraLabel& SetRotationAngle(UINT nAngle,BOOL bRotation);


// Attributes
public:
protected:
	void ReconstructFont();
	COLORREF	m_crText;
	HBRUSH		m_hwndBrush;
	HBRUSH		m_hBackBrush;
	LOGFONT		m_lf;
	CFont		m_font;
	CString		m_strText;
	BOOL		m_bState;
	BOOL		m_bTimer;
	BOOL		m_bLink;
	BOOL		m_bTransparent;
	FlashType	m_Type;
	HCURSOR		m_hCursor;
	Type3D		m_3dType;
	BOOL		m_bFont3d;
	BOOL		m_bToolTips;
	BOOL		m_bNotifyParent;
	BOOL		m_bRotation;

	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraLabel)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraLabel();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEraLabel)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSysColorChange();
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEraOnOffLabel window

class CEraOnOffLabel : public CStatic
{
// Construction
public:
	CEraOnOffLabel();

// Attributes
public:
  BOOL      m_bOn;
  CString   m_OnText, m_OffText;
  COLORREF	m_OnForeClr, m_OffForeClr;
  COLORREF	m_OnBackClr, m_OffBackClr;
  CBrush    m_BrushOn, m_BrushOff;
// Operations
public:
  void  SetText(LPCTSTR szOnText, LPCTSTR szOffText);
  void  SetForeColor(COLORREF	clrOn, COLORREF	clrOff);
  void  SetBackColor(COLORREF	clrOn, COLORREF	clrOff);

  void  Reset();
  void  SetOn(BOOL bOn);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraOnOffLabel)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraOnOffLabel();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEraOnOffLabel)
  afx_msg HBRUSH  CtlColor(CDC* pDC, UINT nCtlColor);;
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

void DrawLabel(CWnd* pParentWnd, int nIDCtl, LPDRAWITEMSTRUCT lpDIS, COLORREF clrText, COLORREF clrBack, BOOL fBold, BOOL fEraseBackground);
void DrawGradientLabel(CWnd* pParentWnd, int nIDCtl, LPDRAWITEMSTRUCT lpDIS, COLORREF clrText, COLORREF clrBackLeft, COLORREF clrBackRight, BOOL fBold, BOOL fGradient);

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERALABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
