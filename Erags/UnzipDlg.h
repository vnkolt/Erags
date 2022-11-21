#if !defined(AFX_UNZIPDLG_H__F65E4159_0DB9_49A5_AFB4_D0D3784D20D1__INCLUDED_)
#define AFX_UNZIPDLG_H__F65E4159_0DB9_49A5_AFB4_D0D3784D20D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UnzipDlg.h : header file
//

#include "DialogEx.h"
#include "..\ZipArchive\ZipArchive.h"
#include "..\ZipArchive\Options.h"
#include "..\Controls\TextProgressCtrl.h"
#include "..\Controls\ListViewCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CUnzipDlg dialog
class CUnzipDlg : public CDialogEx {
// Construction
public:
	CUnzipDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUnzipDlg)
	enum { IDD = IDD_UNZIPDLG };
	CTextProgressCtrl m_progress;
	CListCtrlEx       m_files;
	//}}AFX_DATA

  CImageList  m_listImageList;
  CImageList  m_hdrImageList;
  bool        m_bCommentModified;
  bool        m_bAfterException;
  CString     m_szComment;
  CZipArchive m_zip;
  COptions    m_options;
  CString     m_szZip;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnzipDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  int   GetIconIndex(const CString& sFilename);
  void  ArchiveClose();
  void  ArchiveOpen();
  void  DisplayLabel();
  void  Redisplay();

	// Generated message map functions
	//{{AFX_MSG(CUnzipDlg)
	virtual BOOL OnInitDialog();
  virtual void OnYes();
	afx_msg void OnColumnclickZipList(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnHelpInfo(HELPINFO*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void  Unzip();

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNZIPDLG_H__F65E4159_0DB9_49A5_AFB4_D0D3784D20D1__INCLUDED_)
