#if !defined(AFX_SETREGIONPAGE_H__179F3AF0_A9BC_4D6E_B0D5_EF6A93EA06D8__INCLUDED_)
#define AFX_SETREGIONPAGE_H__179F3AF0_A9BC_4D6E_B0D5_EF6A93EA06D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetRegionPage.h : header file
//

#include "NewWizPage.h"

/////////////////////////////////////////////////////////////////////////////
// CSetRegionPage dialog

class CSetRegionPage : public CNewWizPage
{
// Construction
public:
	CSetRegionPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetRegionPage)
	enum { IDD = IDW_SETREGION };
	CStatic	  m_CaptionCtrl;
	CListCtrl m_Regions;
	//}}AFX_DATA

  CImageList m_ImageList;
  CFont      m_Font;
  int        GetImage(const CString& sType);
  LPCTSTR    GetTypeName(const CString& sType);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetRegionPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetRegionPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedReglist(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETREGIONPAGE_H__179F3AF0_A9BC_4D6E_B0D5_EF6A93EA06D8__INCLUDED_)
