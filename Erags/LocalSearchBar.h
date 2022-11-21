#if !defined(AFX_LOCALSERACHBAR_H__28C161D7_27F5_4F7F_88D3_B43477344D67__INCLUDED_)
#define AFX_LOCALSERACHBAR_H__28C161D7_27F5_4F7F_88D3_B43477344D67__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ABCBar.h : header file
//
//#include "..\Controls\scbarg.h"
#include "..\Controls\scbarcf.h"

class CEraForm;
class CChildFrame;

#include "..\Controls\EraControls.h"
#include "..\Controls\BkgndCtrl.h"

struct SearchItemData {
  long          ID;
  short         Number;
  bool          Male;
  COleDateTime  DateReg;
  CString       SNP;
};

class CSearchView : public CFormViewBG {
	DECLARE_DYNCREATE(CSearchView)
public:
	CSearchView();           // protected constructor used by dynamic creation

// Form Data
public:
	//{{AFX_DATA(CSearchView)
	enum { IDD = IDD_FIND };
  CStaticBG m_lblNumber;
	CEraEdit	m_Number;
  CStaticBG m_lblPib;
	CEraEdit	m_PIB;
	CListCtrl	m_SearchList;
	//}}AFX_DATA

// Attributes
public:
  CEraForm*   m_pForm;
  CImageList  m_ImageList;
private:
  CPtrArray   m_Items;

// Operations
protected:
  void  SetItemData(int nItem, long ID, short Number, bool Male, const COleDateTime& DateReg, const CString& SNP);
public:
  BOOL  Create(CWnd* pParentWnd, CFormView* pForm);
  void  Refresh();
  static int CALLBACK ListViewCompareProc(LPARAM, LPARAM, LPARAM);

protected:
  virtual void SetScaleFlags(CWnd* pWnd, WORD& wFlags);
  virtual void FillChildsMap();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSearchView();
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

  // Generated message map functions
  //{{AFX_MSG(CSearchView)
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg void OnItemChangedSearchList(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnChangePib();
  afx_msg void OnChangeNumber();
  afx_msg void OnColumnClickSearchList(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnHelp();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CLocalSearchBar frame
//#define CLocalSearchBarBase CSizingControlBarG
#define CLocalSearchBarBase CSizingControlBarCF
class CLocalSearchBar : public CLocalSearchBarBase {
  DECLARE_DYNCREATE(CLocalSearchBar)
// Construction
public:
	CLocalSearchBar();

// Attributes
public:
  CChildFrame*  m_pParentFrame;
protected:
  CSearchView*  m_pSearchView;

// Operations
public:
  void  OnInitialUpdate();

// Overrides
// Overridables
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalSearchBar)
//	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLocalSearchBar();

	// Generated message map functions
	//{{AFX_MSG(CLocalSearchBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALSERACHBAR_H__28C161D7_27F5_4F7F_88D3_B43477344D67__INCLUDED_)
