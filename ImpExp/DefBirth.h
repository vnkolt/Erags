#if !defined(AFX_DEFBIRTH_H__F5EB60FC_97A4_4611_954A_54C2830032AD__INCLUDED_)
#define AFX_DEFBIRTH_H__F5EB60FC_97A4_4611_954A_54C2830032AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DefBirth.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDefBirth dialog
class CDefBirth : public CDialog
{
// Construction
public:
	CDefBirth(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDefBirth)
	enum { IDD = IDD_DEFBIRTH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDefBirth)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDefBirth)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CString sCHILD_BP_COUNTRY;
extern CString sCHILD_BP_REGION;
extern CString sCHILD_BP_DISTRICT;
extern CString sCHILD_BP_CITY;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEFBIRTH_H__F5EB60FC_97A4_4611_954A_54C2830032AD__INCLUDED_)
