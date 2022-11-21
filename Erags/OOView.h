#if !defined(AFX_OOVIEW_H__24F11F65_502E_4D82_B7BD_26ED209DBB6D__INCLUDED_)
#define AFX_OOVIEW_H__24F11F65_502E_4D82_B7BD_26ED209DBB6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OOView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COOView html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class COOView : public CHtmlView
{
protected:
	COOView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COOView)

// html Data
public:
	//{{AFX_DATA(COOView)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
protected:
  CString m_szURL;

// Operations
protected:
  BOOL    GetOpenOfficePath(HKEY hKey, const CString& szKey, CString& szPath);
  BOOL    MakeSourcePage(LPCSTR szOOFilename);
  HWND    FindSaltSubFrame(HWND hParent);
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COOView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(COOView)
	afx_msg void OnDestroy();
  afx_msg void OnUpdateEnabledCmd(CCmdUI* pCmdUI);
  afx_msg void OnFileSaveAs();
	afx_msg void OnFilePrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  friend class COODocument;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OOVIEW_H__24F11F65_502E_4D82_B7BD_26ED209DBB6D__INCLUDED_)
