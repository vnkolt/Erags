// Era2XmlDlg.h : header file
//

#if !defined(AFX_ERA2XMLDLG_H__BE4DBA42_73DB_4B86_82E3_53C67E6A0AF8__INCLUDED_)
#define AFX_ERA2XMLDLG_H__BE4DBA42_73DB_4B86_82E3_53C67E6A0AF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\Controls\BkgndCtrl.h"
#include "..\Controls\EraControls.h"
#include "..\Controls\FileEditCtrl.h"



/////////////////////////////////////////////////////////////////////////////
// CEra2XmlDlg dialog

class CEra2XmlDlg : public CDialog
{
// Construction
public:
	CEra2XmlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEra2XmlDlg)
	enum { IDD = IDD_ERA2XML_DIALOG };
	CProgressCtrl	m_Progress;
	CStatic	m_InfoText;
  CFileEditCtrl	m_OutFolder;
	CListCtrl	    m_Files;
  CEraDateEdit  m_BirthFrom;
  CEraDateEdit  m_BirthTill;
  CEraDateEdit  m_DeathFrom;
  CEraDateEdit  m_DeathTill;
  
  CEdit         m_Rags;
  CEdit         m_Boss;
  CEdit         m_BossPosition;
  CEdit         m_BirthSpecialist;
  CEdit         m_BirthSpecialistPos;
  CEdit         m_DeathSpecialist;
  CEdit         m_DeathSpecialistPos;
	//}}AFX_DATA
  BOOL          m_fGeoCacheLoaded;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEra2XmlDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

private:
  void    AddToFilelist(LPCTSTR szFilename);
  void    LoadGeoCache();
  LPCTSTR GetHelpPostfix();
  // void  OnSearch(LPCTSTR szPath);
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEra2XmlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnConvert();
	afx_msg void OnAddFile();
	afx_msg void OnDelFile();
	afx_msg void OnItemchangedFiles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBirthFromCheck();
	afx_msg void OnDeathFromCheck();
  afx_msg void OnHelp();
	afx_msg void OnClose();
	afx_msg void OnSetfocusDeathFrom();
  afx_msg void OnSetfocusDeathTill();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERA2XMLDLG_H__BE4DBA42_73DB_4B86_82E3_53C67E6A0AF8__INCLUDED_)
