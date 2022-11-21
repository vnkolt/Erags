#if !defined(AFX_RLISTDOC_H__6543AF73_FDB0_48FB_BB5E_2A1BF78C26C1__INCLUDED_)
#define AFX_RLISTDOC_H__6543AF73_FDB0_48FB_BB5E_2A1BF78C26C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RListDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRListDoc document

class CRListDoc : public CDocument
{
protected:
	CRListDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRListDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRListDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRListDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// file menu commands
	//{{AFX_MSG(CDocument)
	afx_msg void OnFileClose();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG

	// Generated message map functions
protected:
	//{{AFX_MSG(CRListDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RLISTDOC_H__6543AF73_FDB0_48FB_BB5E_2A1BF78C26C1__INCLUDED_)
