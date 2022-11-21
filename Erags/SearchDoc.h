#if !defined(AFX_SEARCHDOC_H__DB25588C_D5DC_42B7_8C74_F9FBA83C5459__INCLUDED_)
#define AFX_SEARCHDOC_H__DB25588C_D5DC_42B7_8C74_F9FBA83C5459__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchDoc document

class CSearchDoc : public CDocument
{
protected:
	CSearchDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSearchDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSearchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSearchDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHDOC_H__DB25588C_D5DC_42B7_8C74_F9FBA83C5459__INCLUDED_)
