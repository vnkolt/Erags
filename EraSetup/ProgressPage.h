#if !defined(AFX_PROGRESSPAGE_H__CE6FE58C_412B_487F_8A23_2B9404DED6AA__INCLUDED_)
#define AFX_PROGRESSPAGE_H__CE6FE58C_412B_487F_8A23_2B9404DED6AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressPage.h : header file
//
#include "NewWizPage.h"

#include <Afxtempl.h>

struct TEMPLATE {
  CString szUkrName;
  CString szFileName;
  BOOL    fOverwrite;
  BOOL    fDefault;
  TEMPLATE() { fOverwrite = false; fDefault = false; }
};

typedef CArray<TEMPLATE, TEMPLATE&> TemplateArray;


/////////////////////////////////////////////////////////////////////////////
// CProgressPage dialog
class CProgressPage : public CNewWizPage {
// Construction
public:
	CProgressPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgressPage)
	enum { IDD = IDD_PROGRESS };
  CTabCtrl      m_Tab;
	CListCtrl	    m_TmplList;
	CStatic	      m_wndDestFile;
	CProgressCtrl	m_Progress;
	//}}AFX_DATA

  int               m_nSortBy;
  UINT              m_uTab;
  CString           m_sTemplatePath;
  TemplateArray     m_BirthTemplates;
  TemplateArray     m_MarriageTemplates;
  TemplateArray     m_DivorceTemplates;
  TemplateArray     m_ChangeTemplates;
  TemplateArray     m_DeathTemlates;
  TemplateArray     m_EnvelopeTemlates;
  TemplateArray     m_OtherTemlates;
  TemplateArray     m_OverwriteTemlates;
  TemplateArray     m_AllTemlates;

private:
  BOOL Overwrite(LPCTSTR szFileName, int& nIndex);
  void FillTemplateArray(TemplateArray* pTArray, LPCTSTR szFilename, LPCTSTR szSection);
  int  GetTArrayIndex(TemplateArray* pTArray, LPCTSTR szFilename);
  void FillAllTemplates();
  void SetTemplatesFor(UINT uTab);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
 	virtual BOOL OnWizardFinish();
  void CopyFolderStructure(LPCTSTR szFrom, LPCTSTR szTo, ULONG& nFile);

	// Generated message map functions
	//{{AFX_MSG(CProgressPage)
	virtual BOOL OnInitDialog();
  afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnListColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelectAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSPAGE_H__CE6FE58C_412B_487F_8A23_2B9404DED6AA__INCLUDED_)
