#if !defined(AFX_SETREGIONDLG_H__4F83C76C_BF41_4B08_B713_8CD195BAE167__INCLUDED_)
#define AFX_SETREGIONDLG_H__4F83C76C_BF41_4B08_B713_8CD195BAE167__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetRegionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetRegionDlg dialog

class CSetRegionDlg : public CDialog
{
// Construction
public:
	CSetRegionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetRegionDlg)
	enum { IDD = IDW_SETREGION };
	CListBox	m_Regions;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetRegionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetRegionDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETREGIONDLG_H__4F83C76C_BF41_4B08_B713_8CD195BAE167__INCLUDED_)
