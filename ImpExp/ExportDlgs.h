#if !defined(EXPORTSLGS_H_INCLUDED)
#define EXPORTSLGS_H_INCLUDED

//
// ExportDlgs.h
//

#include "..\Controls\NewWizDialog.h"
#include "..\Controls\NewWizPage.h"

/////////////////////////////////////////////////////////////////////////////
// CExpTypesPage dialog
class CExpTypesPage : public CNewWizPage {
// Construction
public:
	CExpTypesPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExpTypesPage)
	enum { IDD = IDD_EXPORT_TYPES };
	BOOL	m_XLS;
	BOOL	m_RTF;
	BOOL	m_HTM;
	BOOL	m_Birth;
	BOOL	m_Marriage;
	BOOL	m_Divorce;
	BOOL	m_Change;
	BOOL	m_Death;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpTypesPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExpTypesPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CExpBirth dialog
class CExpBirth : public CNewWizPage {
// Construction
public:
	CExpBirth(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExpBirth)
	enum { IDD = IDD_EXP_BIRTH };
	CListCtrl	m_NoList;
	CListCtrl	m_DoList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpBirth)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

  virtual LRESULT OnWizardNext();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExpBirth)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedNoExport(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedDoExport(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAdd();
	afx_msg void OnSub();
	afx_msg void OnSubAll();
	afx_msg void OnAddAll();
	afx_msg void OnDeltaposSortSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CExpProgressDlg dialog
class CExpProgressDlg : public CNewWizPage {
// Construction
public:
	CExpProgressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExpProgressDlg)
	enum { IDD = IDD_EXPORT_PROGRESS };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExpProgressDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CExportWizardDlg dialog
class CExportWizardDlg : public CNewWizDialog {
// Construction
public:
	CExportWizardDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExportWizardDlg)
	enum { IDD = IDD_EXPORT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
  CBrush  m_Brush;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExportWizardDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMasterDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


void ExportWizard(LPCTSTR szSrcDB);

#endif // EXPORTSLGS_H_INCLUDED
