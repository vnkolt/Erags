#if !defined(AFX_REPORTDOC_H__A03BD33E_B632_4FC5_9855_5A65EC9572AC__INCLUDED_)
#define AFX_REPORTDOC_H__A03BD33E_B632_4FC5_9855_5A65EC9572AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportDoc document

class CReportDoc : public CDocument
{
protected:
	CReportDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CReportDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	virtual void OnCloseDocument();
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReportDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CReportDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDOC_H__A03BD33E_B632_4FC5_9855_5A65EC9572AC__INCLUDED_)
