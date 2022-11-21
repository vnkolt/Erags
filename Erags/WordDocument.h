#if !defined(AFX_WORDDOCUMENT_H__5E602BB5_2D57_4F1B_B7B0_BB589F05A0F2__INCLUDED_)
#define AFX_WORDDOCUMENT_H__5E602BB5_2D57_4F1B_B7B0_BB589F05A0F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WordDocument.h : header file
//
#include "afxole.h"

#define WMC_INIPREVIEW     0x1000
#define WMC_SETMAGNIFIER   0x1001 // SetMagnifier(LPARAM)
#define WMC_SETPAGETOFIT   0x1002 // SetPageToFit(LPARAM)
#define WMC_SETPERCENTAGE  0x1003 // SetPercentage(LPARAM)
#define WMC_SCREENREFRESH  0x1004 // ScreenRefresh()
#define WMC_PRINT          0x1005
#define WMC_PAGE_SETUP     0x1006
#define WMC_GRIDLINES      0x1007 // LPARAM=Show(TRUE),Hide(FALSE)
#define WMC_SAVE_AS        0x1008
#define WMC_TOOLBARS       0x1009
#define WMC_GET_PAGE_COUNT 0x100A
#define WMC_BEGIN_COPY     0x100B
#define WMC_COPY_PAGE      0x100C // LAPARAM = Page Number
#define WMC_COPY_ALL       0x100D
#define WMC_END_COPY       0x100E
#define WMC_QUIT           0x100F
#define WMC_SAVE_STATE     0x2000 // LPARAM=pointer to RVState struct
#define WMC_RESTORE_STATE  0x2001 // LPARAM=pointer to RVState struct

class CWordCntrItem;
class CWordView;
/////////////////////////////////////////////////////////////////////////////
// CWordDocument document

class CWordDocument : public COleDocument
{
protected:
	CWordDocument();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CWordDocument)

// Attributes
public:
	CWordCntrItem *m_ctrl;
  CString        m_template;

// Operations
public:
  CWordView*      m_pView;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordDocument)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWordDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Implementation
public:
	virtual BOOL ReportError(SCODE sc) const;

	// Generated message map functions
protected:
	//{{AFX_MSG(CWordDocument)
	afx_msg void OnUpdateEnabledCmd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnUpdateFilePageSetup(CCmdUI* pCmdUI);
	afx_msg void OnFilePageSetup();
	afx_msg void OnReturn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDDOCUMENT_H__5E602BB5_2D57_4F1B_B7B0_BB589F05A0F2__INCLUDED_)
