// Era2Xml.h : main header file for the ERA2XML application
//

#if !defined(AFX_ERA2XML_H__E8542F69_5CB7_4AD7_8630_012DB4A23D0F__INCLUDED_)
#define AFX_ERA2XML_H__E8542F69_5CB7_4AD7_8630_012DB4A23D0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEra2XmlApp:
// See Era2Xml.cpp for the implementation of this class
//

class CEra2XmlApp : public CWinApp
{
public:
	CEra2XmlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEra2XmlApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

  CString m_szEraPath;

// Implementation

	//{{AFX_MSG(CEra2XmlApp)
	afx_msg void OnChangeBirthFrom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CEra2XmlApp theApp;
extern HINSTANCE   g_hHHCTRLInstance;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERA2XML_H__E8542F69_5CB7_4AD7_8630_012DB4A23D0F__INCLUDED_)
