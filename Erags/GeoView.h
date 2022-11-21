#if !defined(GEOVIEW_H_INCLUDED)
#define GEOVIEW_H_INCLUDED

//
// GeoView.h
//
#include "..\Controls\BkgndCtrl.h"
#include <afxcview.h>

/////////////////////////////////////////////////////////////////////////////
// CGeoLTree
class CGeoLTree : public CTreeView {
protected: // create from serialization only
	CGeoLTree();
  DECLARE_DYNCREATE(CGeoLTree)

  BOOL        m_fInitialized;
  CGeoRecord* m_pRecord;
  int         m_MenuType;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoLTree)
	public:
	//virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CGeoLTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
  void  RemoveFromTree(CGeoRecord* pRecord);

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGeoLTree)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnRecordFirst();
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	afx_msg void OnRecordPrev();
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnRecordNext();
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnRecordLast();
	afx_msg void OnUpdateRecordNew(CCmdUI* pCmdUI);
	afx_msg void OnRecordNew();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg void OnRecordDelete();
  afx_msg void OnAddCountry();
	afx_msg void OnAddRegion();
  afx_msg void OnAddDistrict();
	afx_msg void OnAddCity();
  afx_msg void OnRename();
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGeoRList
class CGeoRList : public CListView {
protected: // create from serialization only
	CGeoRList();
  DECLARE_DYNCREATE(CGeoRList)

  BOOL        m_fInitialized;
  CFont       m_Bold;
  CGeoRecord* m_pRecord;
// Operations
public:
  void RedrawListItem(int nItem, CGeoRecord* pRecord);
  void FillGeoList(CGeoRecord* pParentRecord);
  void RemoveFromList(CGeoRecord* pRecord);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoRList)
	public:
	//virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL
// Implementation
	virtual ~CGeoRList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGeoRList)
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnCustomDraw (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnRecordFirst();
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	afx_msg void OnRecordPrev();
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnRecordNext();
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnRecordLast();
	afx_msg void OnUpdateRecordNew(CCmdUI* pCmdUI);
	afx_msg void OnRecordNew();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg void OnRecordDelete();
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CGeoTreeList view
class CGeoTreeList : public CView {
protected:
	CGeoTreeList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGeoTreeList)

// Attributes
private:
  CSplitterWnd  m_Splitter;
  int           m_MenuType;

// Operations
private:
  CGeoLTree*   GetLTree();
  CGeoRList*   GetRList();
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoTreeList)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGeoTreeList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGeoTreeList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  friend class CGeoView;
};


/////////////////////////////////////////////////////////////////////////////
// CGeoForm form view
class CGeoForm : public CFormViewBG {
protected:
	CGeoForm();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGeoForm)

// Form Data
public:
	//{{AFX_DATA(CGeoForm)
	enum { IDD = IDD_GEOFORM };
  CStaticBG     m_LblPath;
	CEraEdit	    m_Name;
	CEraEdit	    m_AltName;
	CEraComboBox	m_Type;
	CEraEdit	    m_Zips;
	CEraEdit	    m_Codes;
  CEraEdit	    m_Directory;
	//}}AFX_DATA

// Attributes
private:
  BOOL          m_fInitialized;
  BOOL          m_fModified;
  CRect         m_OrigialRect;
public:

// Operations
public:
  void         FillForm(CGeoRecord* pRecord);
protected:
  virtual void SetScaleFlags(CWnd* pWnd, WORD& wFlags);
  //virtual void OnMoveControl(CWnd* pWnd, LPRECT lpRect, BOOL bRepaint = TRUE);
private:
  void         OnSave();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoForm)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGeoForm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CGeoForm)
  afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChange();
	afx_msg void OnKillfocus();
	afx_msg void OnSelendokType();
	afx_msg void OnKillfocusType();
  afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CGeoViewSplitter : public CSplitterWnd {
public:
  virtual void RecalcLayout();    // call after changing sizes
protected:
  virtual void TrackRowSize(int y, int row);
};
/////////////////////////////////////////////////////////////////////////////
// CGeoView view
class CGeoView : public CView {
protected:
	CGeoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGeoView)

// Attributes
private:
  //CGeoViewSplitter  m_Splitter;
  CSplitterWnd      m_Splitter;
  CGeoRecord*       m_pRecord;

// Operations
private:
  CGeoTreeList*   GetTree();
  CGeoLTree*      GetLTree();
  CGeoRList*      GetRList();
  CGeoForm*       GetForm();
  void            Load(CPtrArray* pArray, HTREEITEM hParent);
public:
  void OnLTreeSelchanged(CGeoRecord* pCurrentRecord);
  void OnRListItemchanged(NM_LISTVIEW* pNMListView);
  void OnSave(CString& szName, CString& szAltName, CString& szType, CString& szZips, CString& szCodes, CString& szDirectory);

  void AddToTreeAndList(CGeoRecord* pRecord);
  void OnAdd(CGeoRecord* pRecord, BOOL fFromLTree, int GeoType);
  void OnAddCountry(CGeoRecord* pRecord, BOOL fFromLTree);
	void OnAddRegion(CGeoRecord* pRecord, BOOL fFromLTree);
  void OnAddDistrict(CGeoRecord* pRecord, BOOL fFromLTree);
	void OnAddCity(CGeoRecord* pRecord, BOOL fFromLTree);
  void OnRecordDelete(CGeoRecord* pRecord, BOOL fFromLTree);

  void RemoveFromCache(CGeoRecord* pRecord);

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
  virtual void OnInitialUpdate();
	//virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGeoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGeoView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

#endif // GEOVIEW_H_INCLUDED
