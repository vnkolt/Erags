#if !defined(AFX_SEARCHDLG_H__FD92109C_72F2_47B1_B6CD_DD63E10A6F59__INCLUDED_)
#define AFX_SEARCHDLG_H__FD92109C_72F2_47B1_B6CD_DD63E10A6F59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchDlg.h : header file
//

struct FoundInfo {
  CString szFilename;
  CString szTitle;
  CString szDate;
};

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog
class CSearchDlg : public CDialog {
// Construction
public:
	CSearchDlg(CWnd* pParent = NULL);   // standard constructor
  ~CSearchDlg();

  static BOOL  Create();

// Dialog Data
	//{{AFX_DATA(CSearchDlg)
	enum { IDD = IDD_SEARCH };
	CProgressCtrl	m_Progress;
	CListCtrl	m_ResList;
	//}}AFX_DATA
private:
  BOOL        m_fResized;
  CPtrArray   m_FoundArray;

private:
  void    ClearFoundArray();
  CString FindDate(const CString& szTitle);
  BOOL  FindInTitle(const TCHAR* pBuffer, const CStringArray& Tokens, CString& szTitle, BOOL fAnyWord);
  void  Resize();
  void  InsertItem(int nItem, FoundInfo* pFound);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnInText();
	afx_msg void OnInTitle();
	afx_msg void OnAllWords();
	afx_msg void OnAnyWord();
	virtual void OnOK();
	afx_msg void OnChangeWords();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CSearchDlg* g_pSearchDlg;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHDLG_H__FD92109C_72F2_47B1_B6CD_DD63E10A6F59__INCLUDED_)
