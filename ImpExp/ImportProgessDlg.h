#if !defined(AFX_IMPORTPROGESSDLG_H__B9836987_5458_4A8C_962E_57B47484F031__INCLUDED_)
#define AFX_IMPORTPROGESSDLG_H__B9836987_5458_4A8C_962E_57B47484F031__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportProgessDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportProgessDlg dialog

class CImportProgessDlg : public CDialog
{
// Construction
public:
	CImportProgessDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImportProgessDlg)
	enum { IDD = IDD_IMPORT_PROGESS };
	CListCtrl	m_MessageList;
	CProgressCtrl	m_Progress;
	CStatic	m_InfoBox;
	//}}AFX_DATA

private:
  CImageList  m_ImageList;
  BOOL        m_fCanClose;
public:
  long        m_nImportedRecords;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportProgessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
  void PumpMessages();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImportProgessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTPROGESSDLG_H__B9836987_5458_4A8C_962E_57B47484F031__INCLUDED_)
