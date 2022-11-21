// RFindFrm.h : interface of the CGlobalSearchBar class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RFINDFRM_H__F774C523_8F83_4D9D_801E_8535403E02B7__INCLUDED_)
#define AFX_RFINDFRM_H__F774C523_8F83_4D9D_801E_8535403E02B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Controls\scbarcf.h"
#include "..\Controls\MyBtnST.h"
#include "..\Controls\BkgndCtrl.h"

#define SF_BIRTHES    0x01
#define SF_FATHERS    0x02
#define SF_MARRIAGES  0x04
#define SF_DIVORCES   0x08
#define SF_CHANGES    0x10
#define SF_DEATHES    0x20
#define SF_PARTIAL    0x40

#define SF_MAX           5

#define SF_ALL        0xFFFFFFFF

class CRFindView;
class CLeftView;
class CGlobalSearchBar;

/////////////////////////////////////////////////////////////////////////////
// CRFindDlgBar dialog
class CRFindDlgBar : public CDialogBarBG {
// Construction
public:
	CRFindDlgBar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRFindDlgBar)
	enum { IDD = IDTB_RFIND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

private:
  CGlobalSearchBar*  m_pBar;
  CMyButtonST	m_btnNewSearch;
  CMyButtonST	m_btnSaveAs;
  CMyButtonST	m_btnFindPath;
  CMyButtonST	m_btnFind;

  CMyButtonST	m_btnEQU;
  CMyButtonST	m_btnPartial;

  CMyButtonST	m_btnBirh;
  CMyButtonST	m_btnMarriage;
  CMyButtonST	m_btnDivorce;
  CMyButtonST	m_btnChange;
  CMyButtonST	m_btnDeath;

  CMyButtonST	m_btnOpenRecord;

// Operations:
public:
  void  SetBkColor(BOOL bRepaint=TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRFindDlgBar)
	public:
	virtual BOOL Create(CWnd* pParentWnd);
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRFindDlgBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
  friend class CGlobalSearchBar;
};


#define CGlobalSearchBarBase CSizingControlBarCF

class CRFindSplitter : public CSplitterWnd {
	DECLARE_DYNCREATE(CRFindSplitter)
public:
	CRFindSplitter();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRFindSplitter)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRFindSplitter();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRFindSplitter)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CGlobalSearchBar : public CGlobalSearchBarBase {
	DECLARE_DYNCREATE(CGlobalSearchBar)
public:
	CGlobalSearchBar();

// Attributes
protected:
	CSplitterWnd     m_wndSplitter;
	CReBar           m_wndReBar;
	CRFindDlgBar     m_wndDlgBar;
	CPPToolTip       m_tooltip;
  BOOL             m_fNeedShowTooltip;

  CDaoDatabase*    m_pDB;
  int              m_SeekFor;
  BOOL             m_bEnableSearch;
  CString          m_sPath;

  CLeftView*       m_pLeftView;
	CRFindView*      m_pRFindView;

public:
  BOOL IsTableDef(CString sTDef);
// Operations
public:
  void ResetTitle();
  bool Match(const CString& s1, const CString& s2, const CString& s3);
  void AddToFoundList(int imlIndex,
                      long  lID,
                      const CString& strNumber,
                      const CString& strDateReg,
                      const CString& strSurName,
                      const CString& strName,
                      const CString& strPatronymic,
                      const CString& strFileName);
  void SearchBirthes();
  void SearchAffilations();
  void SearchMarriages();
  void SearchDivorces();
  void SearchChanges();
  void SearchDeathes();
  void SearchForActs(LPCTSTR szMDEFile);
  void SearchForMde(LPCTSTR szPath);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlobalSearchBar)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGlobalSearchBar();
  CLeftView*  GetLeftPane();
	CRFindView* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:  // control bar embedded members
//	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CGlobalSearchBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
  afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFind(CCmdUI* pCmdUI);
	afx_msg void OnFind();
	afx_msg void OnUpdateFindPath(CCmdUI* pCmdUI);
	afx_msg void OnFindPath();
	afx_msg void OnUpdateNewSearch(CCmdUI* pCmdUI);
  afx_msg void OnNewSearch();
	afx_msg void OnUpdateFindEqu(CCmdUI* pCmdUI);
	afx_msg void OnFindEqu();
	afx_msg void OnUpdatePartialMatching(CCmdUI* pCmdUI);
	afx_msg void OnPartialMatching();
	afx_msg void OnUpdateEnable(CCmdUI* pCmdUI);
	afx_msg void OnEnableBirthes();
	afx_msg void OnEnableFathers();
	afx_msg void OnEnableMarriages();
	afx_msg void OnEnableDivorces();
	afx_msg void OnEnableChanges();
	afx_msg void OnEnableDeathes();
	afx_msg void OnDestroy();
	afx_msg void OnFileOpen();
  afx_msg void OnUpdateGotoFoundRec(CCmdUI* pCmdUI);
  afx_msg void OnGotoFoundRec();
  afx_msg void OnUpdateWhatIsIt(CCmdUI* pCmdUI);
  afx_msg void OnWhatIsIt();
	//}}AFX_MSG
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
  afx_msg BOOL OnHelpInfo(HELPINFO*);
  afx_msg void OnHelp();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RFINDFRM_H__F774C523_8F83_4D9D_801E_8535403E02B7__INCLUDED_)
