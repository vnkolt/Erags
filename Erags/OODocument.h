#if !defined(AFX_OODOCUMENT_H__3917B7C2_2724_46FA_9BC1_8F43A0FECCA7__INCLUDED_)
#define AFX_OODOCUMENT_H__3917B7C2_2724_46FA_9BC1_8F43A0FECCA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OODocument.h : header file
//

#include "afxole.h"

class COOView;

/////////////////////////////////////////////////////////////////////////////
// COODocument document

class COODocument : public COleDocument
{
protected:
	COODocument();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COODocument)

// Attributes
public:
  COOView*      m_pView;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COODocument)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COODocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COODocument)
	afx_msg void OnUpdateEnabledCmd(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
  afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
  afx_msg void OnFileSaveAs();
  afx_msg void OnReturn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OODOCUMENT_H__3917B7C2_2724_46FA_9BC1_8F43A0FECCA7__INCLUDED_)
