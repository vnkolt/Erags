// era2era3.h : main header file for the ERA2ERA3 application
//

#if !defined(AFX_ERA2ERA3_H__777DBDA4_4F8F_4B8D_9D89_DC5B97963A3D__INCLUDED_)
#define AFX_ERA2ERA3_H__777DBDA4_4F8F_4B8D_9D89_DC5B97963A3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

extern BOOL g_fNoAskMore;


/////////////////////////////////////////////////////////////////////////////
// CEra2era3App:
// See era2era3.cpp for the implementation of this class
//

class CEra2era3App : public CWinApp
{
public:
	CEra2era3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEra2era3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEra2era3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERA2ERA3_H__777DBDA4_4F8F_4B8D_9D89_DC5B97963A3D__INCLUDED_)
