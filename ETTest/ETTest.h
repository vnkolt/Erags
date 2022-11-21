// ETTest.h : main header file for the ETTEST application
//

#if !defined(AFX_ETTEST_H__08A2A00B_2911_4B8E_A781_E8C4E438035F__INCLUDED_)
#define AFX_ETTEST_H__08A2A00B_2911_4B8E_A781_E8C4E438035F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CETTestApp:
// See ETTest.cpp for the implementation of this class
//

class CETTestApp : public CWinApp
{
public:
	CETTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CETTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CETTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ETTEST_H__08A2A00B_2911_4B8E_A781_E8C4E438035F__INCLUDED_)
