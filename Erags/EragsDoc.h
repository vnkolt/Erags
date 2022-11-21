// EragsDoc.h : interface of the CEragsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERAGSDOC_H__39BB8E28_820D_4C49_B106_86861B72A33F__INCLUDED_)
#define AFX_ERAGSDOC_H__39BB8E28_820D_4C49_B106_86861B72A33F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEragsDoc : public CDocument
{
public: // create from serialization only
	CEragsDoc();
	DECLARE_DYNCREATE(CEragsDoc)

// Attributes
public:

// Operations
public:
	virtual CFile* GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
		CFileException* pError);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEragsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnFileClose();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEragsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CEragsDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern LPCTSTR g_szDefCitizenship;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERAGSDOC_H__39BB8E28_820D_4C49_B106_86861B72A33F__INCLUDED_)
