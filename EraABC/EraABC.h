// EraABC.h : main header file for the ERAABC application
//

#if !defined(AFX_ERAABC_H__CEB64AA0_49D6_48E8_94FA_C48762BBB901__INCLUDED_)
#define AFX_ERAABC_H__CEB64AA0_49D6_48E8_94FA_C48762BBB901__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "..\Controls\NewMenu.h"
class CEraABCDoc;

/////////////////////////////////////////////////////////////////////////////
// CEraABCApp:
// See EraABC.cpp for the implementation of this class
//

class CEraABCApp : public CWinApp
{
public:
	CEraABCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraABCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

public:
  CString             m_strDBRoot;
  CString             m_strYearDBName;
  CString             m_DocName;
  CString             m_szRagsName;
  BOOL                m_fUkrHelp;
  BOOL                m_fUseHelper;
  CDaoDatabase        m_dbYear;
  CEraABCDoc*         m_pDoc;

// Operations:
public:
  UINT       GetDefaultForm();
  LPCTSTR    GetHelpPostfix();
  CDocument* OpenDocument(const CString& sDatabase, UINT uForm);
  void       OnForm(CMDIChildWnd* pFrame, UINT uForm);
  void       OnMessage(int MessageType, LPCTSTR lpszFormat, ...);

// Implementation
	//{{AFX_MSG(CEraABCApp)
  afx_msg void OnAppAbout();
  afx_msg void OnUpdateBirth(CCmdUI* pCmdUI);
  afx_msg void OnBirth();
  afx_msg void OnUpdateMarriage(CCmdUI* pCmdUI);
  afx_msg void OnMarriage();
  afx_msg void OnUpdateDivorce(CCmdUI* pCmdUI);
  afx_msg void OnDivorce();
  afx_msg void OnUpdateChange(CCmdUI* pCmdUI);
  afx_msg void OnChange();
  afx_msg void OnUpdateDeath(CCmdUI* pCmdUI);
  afx_msg void OnDeath();
  afx_msg void OnFileNew();
  afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileRecent(CCmdUI* pCmdUI);
	afx_msg void OnFileRecent();
  afx_msg void OnUpdateHelper(CCmdUI* pCmdUI);
	afx_msg void OnHelper();
	afx_msg void OnUpdateHelpUkr(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHelpRus(CCmdUI* pCmdUI);
	afx_msg void OnHelpLanguage();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
extern CEraABCApp theApp;


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERAABC_H__CEB64AA0_49D6_48E8_94FA_C48762BBB901__INCLUDED_)
