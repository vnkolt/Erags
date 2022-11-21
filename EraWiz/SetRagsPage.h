#if !defined(AFX_SETRAGSPAGE_H__73D13B81_0ED2_4499_80F3_174924CAAA02__INCLUDED_)
#define AFX_SETRAGSPAGE_H__73D13B81_0ED2_4499_80F3_174924CAAA02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetRagsPage.h : header file
//

#define RLIMAGE_ROOT            0
#define RLIMAGE_NOCOMMENT       1
#define RLIMAGE_NOCOMMENT_EAXP  2
#define RLIMAGE_COMMENT         3
#define RLIMAGE_COMMENT_EAXP    4

#include "NewWizPage.h"
#include "UkraineMap.h"
#include "WizEdit.h"
#include "WizTreeCtrl.h"

#include "..\Controls\TCToolBar\TCImageList.h"

class CRListRecord : public CObject {
public:
  CRListRecord();
  ~CRListRecord();
public:
  CPtrArray     m_array;
  long          m_ID;
  long          m_ParentID;
  long          m_Flags;
  CString       m_Fullname;
  CString       m_Address;
  CString       m_Phones;
  CString       m_Notice;
  HTREEITEM     m_hTreeItem;
public:
  void          AddChild(CRListRecord* pChildRecord);
};

class CRList {
public:
  CRList();
  ~CRList();
// Data members:
public:
  CMapPtrToPtr    m_map;
  CPtrArray       m_RootItems;
public:
  void  Clear();
  void  Sort(CPtrArray* pArray);
  void  Load(CProgressCtrl* pProgressCtrl=NULL, CStatic* pStatic=NULL);
  BOOL  IsEmpty() { return (m_map.GetCount()==0); }
  void  Add(CRListRecord* pRecord);
  void  Delete(CRListRecord* pRecord);
  CRListRecord* Lookup(long ID);
};


/////////////////////////////////////////////////////////////////////////////
// CSetRagsPage dialog

class CSetRagsPage : public CNewWizPage
{
// Construction
public:
	CSetRagsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetRagsPage)
	enum { IDD = IDW_SETRAGS };
	CWizEdit      m_edtFullName;
	CWizEdit	    m_edtShortName;
	CUkraineMap	  m_Map;
  CStatic       m_CaptionCtrl;
  CBitmap       m_bmpEmblem;
  CStatic       m_Emblem;
	CWizTreeCtrl	m_RTree;
	//}}AFX_DATA

  CFont        m_Font;
  CTCImageList m_ImageList;
  HTREEITEM    m_hMinJust;
  HTREEITEM    m_hOurRags;
  long         m_FilledID;
  long         m_Flags;

  virtual void OnSetActive();
	virtual LRESULT OnWizardNext();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetRagsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  HTREEITEM FillParent(CRListRecord* pRecord, HTREEITEM hParent, long lFlags=0);
  void      Fill(long id=-1, long lFlags=0);

  void SetRadioButtons();
	// Generated message map functions
	//{{AFX_MSG(CSetRagsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedRtree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeShortname();
	afx_msg void OnVyconcom();
	afx_msg void OnOrgan();
	//}}AFX_MSG
  afx_msg LRESULT OnSetRagsAll(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetRagsCity(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetRagRegion(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

extern CRList theRList;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETRAGSPAGE_H__73D13B81_0ED2_4499_80F3_174924CAAA02__INCLUDED_)
