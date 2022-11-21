#if !defined(AFX_FILEEDITCTRL_H__F15965B0_B05A_11D4_B625_A1459D96AB20__INCLUDED_)
#define AFX_FILEEDITCTRL_H__F15965B0_B05A_11D4_B625_A1459D96AB20__INCLUDED_

#include "FEButton.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileEditCtrl.h : header file
//

/*  FileEditCtrl style constants.
	This control uses these optional Edit control style constants:
		One or none of - ES_LEFT (default), ES_CENTER, or ES_RIGHT.
		One or none of - ES_UPPERCASE or ES_LOWERCASE.
		ES_AUTOHSCROLL.

	This control also defines two of its own style constants:
		One or none of - FES_FILE (default) or FES_FOLDER.

	If you specify FES_FILE (the default), then clicking on the
	browse button will bring up the 'File Open' dialog.
	If you specify FES_FOLDER, then clicking on the browse button
	will bring up the SHBrowseForFolder dialog.
*/

#define FES_FILE   0x0000L
#define FES_FOLDER 0x4000L

/////////////////////////////////////////////////////////////////////////////
// CFileEditCtrl window

class CFileEditCtrl : public CWnd
{
// Construction
public:
	CFileEditCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileEditCtrl)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetNextPathName(POSITION &pos) const;
	POSITION GetStartPosition() const;
	virtual ~CFileEditCtrl();
	CEdit* GetEditControl() const;
	OPENFILENAME* GetOpenFileName() const;
	BROWSEINFO* GetBrowseInfo() const;
	int GetWindowText (LPTSTR, int) const;
	void GetWindowText (CString &) const;
	int GetWindowTextLength() const;
	void SetWindowText(LPCTSTR text);
	void SetFont (CFont *pFont, BOOL bRedraw = TRUE);

	// Generated message map functions
protected:
	BOOL FECOpenFile();
	BOOL FECBrowseForFolder();
	//{{AFX_MSG(CFileEditCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnEnable(BOOL bEnable);
	//}}AFX_MSG
	afx_msg void OnBrowse();
	DECLARE_MESSAGE_MAP()

private:
	CFileDialog *m_pcfd;
	BROWSEINFO *m_pbi;
	CEdit *m_edit;
	CFEButton *m_button;
	BOOL m_bFindFolder;
	char m_buffer[MAX_PATH];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEEDITCTRL_H__F15965B0_B05A_11D4_B625_A1459D96AB20__INCLUDED_)
