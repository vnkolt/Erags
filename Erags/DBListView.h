#if !defined(AFX_DBLISTVIEW_H__17633F31_087C_4CD8_AFEF_AD0B24128E4B__INCLUDED_)
#define AFX_DBLISTVIEW_H__17633F31_087C_4CD8_AFEF_AD0B24128E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBListView view

class CDBListView : public CListView
{
protected:
	CDBListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDBListView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDBListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDBListView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBLISTVIEW_H__17633F31_087C_4CD8_AFEF_AD0B24128E4B__INCLUDED_)
