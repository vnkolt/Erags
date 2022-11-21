// EMSO.h : main header file for the EMSO DLL
//

#if !defined(AFX_EMSO_H__25C464ED_70DA_4D31_ABF6_C1A1F3F19215__INCLUDED_)
#define AFX_EMSO_H__25C464ED_70DA_4D31_ABF6_C1A1F3F19215__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEMSOApp
// See EMSO.cpp for the implementation of this class
//

class CEMSOApp : public CWinApp
{
public:
	CEMSOApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEMSOApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEMSOApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMSO_H__25C464ED_70DA_4D31_ABF6_C1A1F3F19215__INCLUDED_)
