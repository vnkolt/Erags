// RFindDoc.h : interface of the CRFindDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RFINDDOC_H__F1A398E2_DDE4_496D_AF50_D4138DD9C4E4__INCLUDED_)
#define AFX_RFINDDOC_H__F1A398E2_DDE4_496D_AF50_D4138DD9C4E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRFindDoc : public CDocument
{
protected: // create from serialization only
	CRFindDoc();
	DECLARE_DYNCREATE(CRFindDoc)

// Data members
public:
  CString m_sPath;
// Attributes
public:
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRFindDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRFindDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRFindDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RFINDDOC_H__F1A398E2_DDE4_496D_AF50_D4138DD9C4E4__INCLUDED_)
