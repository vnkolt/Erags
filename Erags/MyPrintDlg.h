#if !defined(AFX_MYPRINTDLG_H__B8533D0A_EA1A_4E9E_B99A_70D19E56A530__INCLUDED_)
#define AFX_MYPRINTDLG_H__B8533D0A_EA1A_4E9E_B99A_70D19E56A530__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyPrintDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyPrintDlg dialog

class CMyPrintDlg : public CPrintDialog
{
	DECLARE_DYNAMIC(CMyPrintDlg)

public:
	CMyPrintDlg(BOOL bPrintSetupOnly,
		// TRUE for Print Setup, FALSE for Print Dialog
		DWORD dwFlags = PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS
			| PD_HIDEPRINTTOFILE | PD_NOSELECTION,
		CWnd* pParentWnd = NULL);

// Implementation
protected:
	virtual void OnOK();

protected:
	//{{AFX_MSG(CMyPrintDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPRINTDLG_H__B8533D0A_EA1A_4E9E_B99A_70D19E56A530__INCLUDED_)
