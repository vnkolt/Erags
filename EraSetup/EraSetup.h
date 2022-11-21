// EraSetup.h : main header file for the ERASETUP application
//

#if !defined(AFX_ERASETUP_H__0253166C_5F9F_48DE_AA7D_E97C6E681712__INCLUDED_)
#define AFX_ERASETUP_H__0253166C_5F9F_48DE_AA7D_E97C6E681712__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define CLR_BK  RGB(0xF4,0xF4,0xF0)

/////////////////////////////////////////////////////////////////////////////
// CEraSetupApp:
// See EraSetup.cpp for the implementation of this class
//
class CEraSetupApp : public CWinApp {
public:
	CEraSetupApp();

  BOOL  PreInitInstance();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraSetupApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

  BOOL      m_fServer;
  // BOOL      m_fInstallLaws;
  CString   m_sEraPath;
  CString   m_sEraGroup;
  CString   m_szSourceZip;
  CString   m_szUnzipFolder;
  int       m_HelpLang;

  CFont     m_Font;

// Implementation

	//{{AFX_MSG(CEraSetupApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CEraSetupApp theApp;
extern HINSTANCE    g_hHHCTRLInstance;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERASETUP_H__0253166C_5F9F_48DE_AA7D_E97C6E681712__INCLUDED_)
