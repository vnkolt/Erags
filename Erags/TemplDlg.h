#if !defined(AFX_TEMPLDLG_H__7373983E_B805_4E6E_BE34_25B1C0727D0F__INCLUDED_)
#define AFX_TEMPLDLG_H__7373983E_B805_4E6E_BE34_25B1C0727D0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TemplDlg.h : header file
//


#include "DialogEx.h"
#include "..\Controls\BtnST.h"
#include "..\Controls\ListCtrlStyled.h"
#include "..\Controls\XButtonXP.h"
#include "..\Controls\TCToolBar\TCImageList.h"


/*
  Current Forms:
*/
#define ACTION_NONE             0
#define ACTION_SAVE_OPEN        1
#define ACTION_OPEN_ONLY        2
#define ACTION_RESTORE_OPEN     3
#define ACTION_RESTORE          4
#define ACTION_RESTORE_FROM_ZIP 5
#define ACTION_SAVE_IMPORT_OPEN 6
#define ACTION_IMPORT_OPEN      7
#define ACTION_IMPORT           8

struct TEMPLATE {
  CString szUkrName;
  CString szFileName;
};

typedef CArray<TEMPLATE, TEMPLATE&> TemplateArray;

/////////////////////////////////////////////////////////////////////////////
// CTemplDlg dialog
class CTemplDlg : public CDialogEx {
// Construction
public:
	CTemplDlg(UINT idTemplate, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTemplDlg)
	enum { IDD = IDD_TEMPLATES };
  CTabCtrl          m_Tab;
	CListCtrlStyled   m_TmplList;
  CXButtonXP        m_rbRadio[8];
	//}}AFX_DATA
  UINT m_idTemplate;
  UINT m_uForm;
  UINT m_Action;
  UINT m_ActionImageID;

  TemplateArray     m_BirthTemplates;
  TemplateArray     m_MarriageTemplates;
  TemplateArray     m_DivorceTemplates;
  TemplateArray     m_ChangeTemplates;
  TemplateArray     m_DeathTemlates;
  TemplateArray     m_EnvelopeTemlates;
  TemplateArray     m_OtherTemlates;
  TemplateArray     m_AllTemlates;

  TemplateArray*    m_pCurArray;
  int               m_nSortColumn;

  CString m_sTemplatePath;
  CString m_sTemplateSavedPath;
  CTCImageList  m_RadioIL;
  CBitmap m_ActionBitmap;

  void  SetTemplatesFor(UINT uForm);

private:
  void FillTemplateArray(TemplateArray* pTArray, LPCTSTR szFilename, LPCTSTR szSection);
  int  GetTArrayIndex(TemplateArray* pTArray, LPCTSTR szFilename);
  void FillAllTemplates();
  bool Save(LPCTSTR szTemplate, LPCTSTR szTemplateForSave);
  bool Open(LPCTSTR szTemplate);
  bool Restore(LPCTSTR szTemplate, LPCTSTR szSavedTemplate);
  bool RestoreFromZip(LPCTSTR szTemplate);
  bool Import(LPCTSTR szTemplate, const CString& sFullTemplateName, CString& sImportFile);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemplDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void OnActionRadio();

	// Generated message map functions
	//{{AFX_MSG(CTemplDlg)
	virtual BOOL OnInitDialog();
  afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioSaveOpen();
	afx_msg void OnRadioOpenOnly();
	afx_msg void OnRadioRestoreOpen();
	afx_msg void OnRadioRestore();
  afx_msg void OnRadioRestoreFromZip();
	afx_msg void OnRadioSaveImportOpen();
	afx_msg void OnRadioImportOpen();
	afx_msg void OnRadioImport();
	afx_msg void OnYes();
	afx_msg void OnClickTemplList(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnColumnClickTemplList(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPLDLG_H__7373983E_B805_4E6E_BE34_25B1C0727D0F__INCLUDED_)
