#if !defined(BKGNDCTRL_H_INCLUDED)
#define BKGNDCTRL_H_INCLUDED

#ifndef __CNewMenu_H_
#include "NewMenu.h"
#endif

extern COLORREF g_clrBkgnd;
extern CBrush   g_brBkgnd;

BOOL  IsIDC_STATIC(int id);
void  SetButtonSTColors(CWnd* pParent, BOOL bRepaint/*=TRUE*/);
void  DrawStatic(LPDRAWITEMSTRUCT pDIS);

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
  CMapPtrToPtr  m_Brushes;
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDialogBG)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////
// CFormViewBG
class CFormViewBG : public CFormView {
  DECLARE_DYNAMIC(CFormViewBG)
public:
  BOOL          m_fGradientFill;
  CPtrArray     m_Statics;
  CMapPtrToPtr  m_Brushes;
  
// Construction
protected:
  CFormViewBG(LPCTSTR lpszTemplateName):CFormView(lpszTemplateName){
    m_fGradientFill = TRUE;
  }
  CFormViewBG(UINT nIDTemplate):CFormView(nIDTemplate){
    m_fGradientFill = TRUE;
  }
  ~CFormViewBG();
  
  // Implementation
protected:
	virtual void OnInitialUpdate();
  // Generated message map functions
	//{{AFX_MSG(CFormViewBG)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysColorChange();
  afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS);
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
  CMapPtrToPtr  m_Brushes;

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageBG)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////
// CTabCtrlBG
class CTabCtrlBG : public CTabCtrl {
  DECLARE_DYNCREATE(CTabCtrlBG)
public:
  BOOL  m_fGradientFill;
public:
  CTabCtrlBG():CTabCtrl(){ m_fGradientFill = TRUE; }
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTabCtrlBG)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
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
class CDialogBarBG : public CDialogBar
{
  DECLARE_DYNCREATE(CDialogBarBG)
public:
  BOOL          m_fGradientFill;
  CPtrArray     m_Statics;
  CMapPtrToPtr  m_Brushes;
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
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif