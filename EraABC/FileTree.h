#if !defined(AFX_FILETREE_H__31FDA77D_0659_41B9_B90F_C41960C9436E__INCLUDED_)
#define AFX_FILETREE_H__31FDA77D_0659_41B9_B90F_C41960C9436E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileTree.h : header file
//

#include <afxcview.h>

/////////////////////////////////////////////////////////////////////////////
// CFileTree view
class CFileTree : public CTreeView {
protected:
	CFileTree();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFileTree)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTree)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFileTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CFileTree)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETREE_H__31FDA77D_0659_41B9_B90F_C41960C9436E__INCLUDED_)
