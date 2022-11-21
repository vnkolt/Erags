#if !defined(AFX_SEARCHBAR_H__9E500F4A_C9FC_4DF8_90BB_819DAB79342D__INCLUDED_)
#define AFX_SEARCHBAR_H__9E500F4A_C9FC_4DF8_90BB_819DAB79342D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchBar.h : header file
//


#include "..\Controls\scbarg.h"

struct FoundInfo {
  CString szFilename;
  CString szTitle;
  CString szDate;
  CString szNumber;
};

class CFoundList {
public:
  CFoundList();
  ~CFoundList();
protected:
  CPtrArray m_array;
public:
  void  Clear();
  int   Add(FoundInfo* pFound);
};
extern CFoundList theFoundList;


/////////////////////////////////////////////////////////////////////////////
// CSearchBar dialog

class CSearchBar : public CDialogBar {
	DECLARE_DYNCREATE(CSearchBar)
// Construction
public:
	CSearchBar();   // standard constructor

  BOOL  Create();

// Dialog Data
	//{{AFX_DATA(CSearchBar)
	enum { IDD = IDD_SBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
  virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchBar)
	afx_msg void OnInText();
	afx_msg void OnInTitle();
	afx_msg void OnAllWords();
	afx_msg void OnAnyWord();
	afx_msg void OnChangeWords();
  afx_msg void OnSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



#ifndef baseCFoundBar
#define baseCFoundBar CSizingControlBarG
#endif

/////////////////////////////////////////////////////////////////////////////
// CFoundBar
class CFoundBar : public baseCFoundBar {
// Construction
public:
	CFoundBar();

// Attributes
protected:
	CListCtrl m_FoundList;
  int       m_nItems;

// Operations
public:
  void  Clear();
  int   Add(FoundInfo* pFoundInfo);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFoundBar)
//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFoundBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFoundBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnDestroy();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnClickResults(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CSearchBar theSearhBar;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHBAR_H__9E500F4A_C9FC_4DF8_90BB_819DAB79342D__INCLUDED_)
