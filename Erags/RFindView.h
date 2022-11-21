// RFindView.h : interface of the CRFindView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RFINDVIEW_H__40382939_8675_459D_8BF7_268A60BC41BD__INCLUDED_)
#define AFX_RFINDVIEW_H__40382939_8675_459D_8BF7_268A60BC41BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxcview.h>

#define MAX_LIST_COLUMNS 256

#define IML_BIRTH_W   0
#define IML_BIRTH_M   1
#define IML_FATHER_W  2
#define IML_FATHER_M  3
#define IML_MARRIAGE  4
#define IML_DIVORCE_W 5
#define IML_DIVORCE_M 6
#define IML_CHANGE_W  7
#define IML_CHANGE_M  8
#define IML_DEATH_W   9
#define IML_DEATH_M  10
#define IML_FATHER   11
#define IML_MOTHER   12

class CRFoundOb : public CObject {
public:
  int       m_nImage;
  long      m_lID;
  int       m_nActType;
  CString   m_sActType;
  CString   m_sNumber;
  CString   m_sDateReg;
  CString   m_sFullName;
public:
  CRFoundOb(int nImage, long lID, int nActType, LPCTSTR szActType, LPCTSTR szNumber, LPCTSTR szDateReg, LPCTSTR szFullName) {
    m_nImage    = nImage;
    m_lID       = lID;
    m_nActType  = nActType;
    m_sActType  = szActType;
    m_sNumber   = szNumber;
    m_sDateReg  = szDateReg;
    m_sFullName = szFullName;
  }
};


class CRFindView : public CListView {
protected: // create from serialization only
	CRFindView();
	DECLARE_DYNCREATE(CRFindView)

// Attributes
public:
	CRFindDoc* GetDocument();
  CImageList  m_ImageList;

  CFont*   m_pPrinterFont;
  int      m_nColumns;
  CRect    m_margins;
  int      m_column_order_array[MAX_LIST_COLUMNS];
  CSize    m_column_size [MAX_LIST_COLUMNS];
  UINT     m_justify     [MAX_LIST_COLUMNS];
  UINT     m_band        [MAX_LIST_COLUMNS];
  UINT     m_total_bands;
  UINT     m_nPagesPerBand;
  UINT     m_nCurrentBand;

  int m_nPage;
  int m_nLinesPerPage;
  int m_nPageHeight;
  int m_nPageWidth;
  int m_nRowWidth;
  int m_nRowHeight;

// Operations
public:
  void  Clear();
  void  AddToList(int imlIndex,
                  long lID, const CString& sNumber, const CString& sDateReg,
                  const CString& sFullName,
                  const CString& sFileName);

// Operations
public:
  void ExportToCSV();

  virtual void PrintPageHeader(CDC* pDC);
  virtual void PrintPageFooter(CPoint point, CDC* pDC, CPrintInfo* pInfo);

protected:
  void WriteCSVHeader(CFile* pFile);
  void WriteCSVBody  (CFile* pFile);

  void OnPrintLine(CDC* pDC, int nItem, int cy);
  void OnPrint(CDC* pDC, CPrintInfo* pInfo);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRFindView)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRFindView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRFindView)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnFilePrint();
	afx_msg void OnFileSave();
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RFindView.cpp
inline CRFindDoc* CRFindView::GetDocument()
   { return (CRFindDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RFINDVIEW_H__40382939_8675_459D_8BF7_268A60BC41BD__INCLUDED_)
