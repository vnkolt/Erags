#if !defined(AFX_OODOC_H__FF53CC7D_99C1_4C00_99DA_5037672C6647__INCLUDED_)
#define AFX_OODOC_H__FF53CC7D_99C1_4C00_99DA_5037672C6647__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OODoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COODoc document

class COODoc : public CDocument
{
protected:
	COODoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COODoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COODoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COODoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COODoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OODOC_H__FF53CC7D_99C1_4C00_99DA_5037672C6647__INCLUDED_)
