#if !defined(BKGNDCTRL_H_INCLUDED)
#define BKGNDCTRL_H_INCLUDED

// BkgndCtrl.h


#ifndef __CNewMenu_H_
#include "NewMenu.h"
#endif

#include "TabCtrlBG.h"

#pragma warning(disable : 4995)

void  SetButtonSTColors(CWnd* pParent, BOOL bRepaint/*=TRUE*/);

////////////////////////////////////////////////////////////////////////////
// CStaticBG
class CStaticBG : public CStatic {
  DECLARE_DYNCREATE(CStaticBG)
public:
  BOOL  m_fGradientFill;
public:
  CStaticBG() {
    m_fGradientFill = TRUE;
  }
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStaticBG)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////
// CButtonBG
class CButtonBG : public CButton {
  DECLARE_DYNCREATE(CButtonBG)
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CButtonBG)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////
// CDialogBG
class CDialogBG : public CDialog {
  DECLARE_DYNCREATE(CDialogBG)
public:
  BOOL  m_fGradientFill;
public:
  CDialogBG(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL):CDialog(lpszTemplateName, pParentWnd){
    m_fGradientFill = TRUE;
  }
  CDialogBG(UINT nIDTemplate, CWnd* pParentWnd = NULL ):CDialog(nIDTemplate, pParentWnd){
    m_fGradientFill = TRUE;
  }
  CDialogBG():CDialog(){
    m_fGradientFill = TRUE;
  }
  ~CDialogBG();
  CPtrArray     m_Statics;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogBG)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDialogBG)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#define SCALE_NONE  0     // 00000000
#define SCALE_WIDTH 1     // 00000001
#define SCALE_HEIGH 2     // 00000010
#define SCALE_ALL   3     // 00000011

struct SResizeWndInfo {
  RECT  rect;
  WORD  wFlags;
};

typedef CMap<HWND, HWND, SResizeWndInfo, SResizeWndInfo>  ResizeMap;

////////////////////////////////////////////////////////////////////////////
// CFormViewBG
class CFormViewBG : public CFormView {
  DECLARE_DYNAMIC(CFormViewBG)
public:
  BOOL          m_fGradientFill;
  CPtrArray     m_Statics;

  BOOL        m_fRestoredRectSaved;
  BOOL        m_ResizableEnabled;
  CRect       m_RestoredRect;
  ResizeMap   m_ResizeMap;
  
// Construction
protected:
  CFormViewBG(LPCTSTR lpszTemplateName):CFormView(lpszTemplateName){
    m_fGradientFill = TRUE;
    m_ResizableEnabled = m_fRestoredRectSaved = FALSE;
  }
  CFormViewBG(UINT nIDTemplate):CFormView(nIDTemplate){
    m_fGradientFill = TRUE;
    m_ResizableEnabled = m_fRestoredRectSaved = FALSE;
  }
  ~CFormViewBG();

  virtual void SetScaleFlags(CWnd* pWnd, WORD& wFlags);
  virtual void OnMoveControl(CWnd* pWnd, LPRECT lpRect, BOOL bRepaint = TRUE);
  BOOL         SetRect(CWnd* pWnd, const RECT* pNewRect);
  void         FillChildsMap();
  virtual BOOL IsNeedSubclassForStaticBG(CWnd* pWnd);
  virtual void SubclassStatics();

  
  // Implementation
protected:
	virtual void OnInitialUpdate();
  // Generated message map functions
	//{{AFX_MSG(CFormViewBG)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysColorChange();
  afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS);
	afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


////////////////////////////////////////////////////////////////////////////
// CDaoRecordViewBG
class CDaoRecordViewBG : public CDaoRecordView {
  DECLARE_DYNAMIC(CDaoRecordViewBG)
// Construction
protected:
  CDaoRecordViewBG(LPCTSTR lpszTemplateName);
  CDaoRecordViewBG(UINT nIDTemplate);
  ~CDaoRecordViewBG();

// Attributes
protected:
  BOOL        m_fRestoredRectSaved;
  BOOL        m_ResizableEnabled;
  CRect       m_RestoredRect;
  ResizeMap   m_ResizeMap;

  CPtrArray     m_Statics;

// Operations
protected:
  virtual void SetScaleFlags(CWnd* pWnd, WORD& wFlags);
  virtual void OnMoveControl(CWnd* pWnd, LPRECT lpRect, BOOL bRepaint = TRUE);
  virtual void SubclassStatics();
  virtual BOOL IsNeedSubclassForStaticBG(CWnd* pWnd);

  BOOL         SetRect(CWnd* pWnd, const RECT* pNewRect);
  void         FillChildsMap();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoRecordViewBG)
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDaoRecordViewBG)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysColorChange();
  afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS);
	afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////
// CPropertyPageBG
class CPropertyPageBG : public CPropertyPage {
  DECLARE_DYNCREATE(CPropertyPageBG)
public:
  BOOL  m_fGradientFill;
public:
  CPropertyPageBG():CPropertyPage(){
    m_fGradientFill = TRUE;
  }
  CPropertyPageBG(UINT nIDTemplate, UINT nIDCaption = 0):CPropertyPage(nIDTemplate, nIDCaption){
    m_fGradientFill = TRUE;
  }
  CPropertyPageBG(LPCTSTR lpszTemplateName, UINT nIDCaption = 0):CPropertyPage(lpszTemplateName, nIDCaption){
    m_fGradientFill = TRUE;
  }
  ~CPropertyPageBG();

  CPtrArray     m_Statics;

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageBG)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////
// CPropertySheetBG
class CPropertySheetBG : public CPropertySheet {
  DECLARE_DYNCREATE(CPropertySheetBG)
public:
  BOOL  m_fGradientFill;
public:
  CPropertySheetBG():CPropertySheet() { m_fGradientFill = TRUE; }
  CPropertySheetBG(UINT nIDCaption, CWnd *pParentWnd = NULL, UINT iSelectPage = 0 )
                   :CPropertySheet(nIDCaption, pParentWnd, iSelectPage){ m_fGradientFill = TRUE; }
  CPropertySheetBG( LPCTSTR pszCaption, CWnd *pParentWnd = NULL, UINT iSelectPage = 0)
                   :CPropertySheet(pszCaption, pParentWnd, iSelectPage){ m_fGradientFill = TRUE; }

public:
  CTabCtrlBG  m_TabCtrl;
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertySheetBG)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



////////////////////////////////////////////////////////////////////////////
// CReBarBG
class CReBarBG : public CReBar {
  DECLARE_DYNCREATE(CReBarBG)
public:
  BOOL  m_fGradientFill;
public:
  CReBarBG() { m_fGradientFill = TRUE; }
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CReBarBG)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDialogBarBG
class CDialogBarBG : public CDialogBar {
  DECLARE_DYNCREATE(CDialogBarBG)
public:
  CPtrArray     m_Statics;
public:
  CDialogBarBG();
  ~CDialogBarBG();
	virtual BOOL Create(CWnd* pParentWnd, LPCTSTR lpszTemplateName, UINT nStyle, UINT nID);
	virtual BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);

  virtual void SetColors(BOOL bRepaint=TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogBarBG)
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogBarBG)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif