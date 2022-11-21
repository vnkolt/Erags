// ImpExpTest.h : main header file for the IMPEXPTEST application
//

#if !defined(AFX_IMPEXPTEST_H__F2A1EE11_D06D_4BED_84ED_DF69C584D001__INCLUDED_)
#define AFX_IMPEXPTEST_H__F2A1EE11_D06D_4BED_84ED_DF69C584D001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CImpExpTestApp:
// See ImpExpTest.cpp for the implementation of this class
//

class CImpExpTestApp : public CWinApp
{
public:
	CImpExpTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImpExpTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CImpExpTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPEXPTEST_H__F2A1EE11_D06D_4BED_84ED_DF69C584D001__INCLUDED_)
