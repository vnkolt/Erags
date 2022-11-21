// Uninstall.h : main header file for the UNINSTALL application
//

#if !defined(AFX_UNINSTALL_H__E8B66562_27E7_4632_ABAF_BF6486419F9B__INCLUDED_)
#define AFX_UNINSTALL_H__E8B66562_27E7_4632_ABAF_BF6486419F9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUninstallApp:
// See Uninstall.cpp for the implementation of this class
//

class CUninstallApp : public CWinApp
{
public:
	CUninstallApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUninstallApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUninstallApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNINSTALL_H__E8B66562_27E7_4632_ABAF_BF6486419F9B__INCLUDED_)
