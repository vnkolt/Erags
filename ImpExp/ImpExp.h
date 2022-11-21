// ImpExp.h : main header file for the IMPEXP DLL
//

#if !defined(AFX_IMPEXP_H__A38A91AA_6809_4D26_843C_B000CDFD65D8__INCLUDED_)
#define AFX_IMPEXP_H__A38A91AA_6809_4D26_843C_B000CDFD65D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

enum MesssageType { MT_INFO=0, MT_WARNING=1, MT_ERROR=2,
                    MT_GIRL=3, MT_BOY=4,
                    MT_MARRIAGE = 5,
                    MT_DIVORCE  = 6,
                    MT_WCHANGE  = 7, // �������/�������
                    MT_MCHANGE  = 8, // �������/�������
                    MT_WDEATH   = 9, // ������/�������
                    MT_MDEATH  = 10  // ������/�������
                  };

class CImportProgessDlg;
typedef void (*pOnHelpCallback)(LPCTSTR szHelpFile);
/////////////////////////////////////////////////////////////////////////////
// CImpExpApp
// See ImpExp.cpp for the implementation of this class
//

class CImpExpApp : public CWinApp
{
public:
	CImpExpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImpExpApp)
	public:
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CImpExpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CImpExpApp theApp;

extern CString      g_szTargetFile; // ��� ����� ��-��������
extern CString      g_szSourceFile; // ��� ����� ��-���������
extern CDaoDatabase g_TargetDB;     // ��-�������, � ������� ������������� ������
extern CDaoDatabase g_SourceDB;     // ��-��������, �� ������� ������������� ������
extern BOOL         g_fNoEmpty;     // ������������� ������ �������� ������
extern BOOL         g_fNoExist;     // �� ������������ ������, ������ ��� ���� � ��-��������
extern int          g_Year;         // ���� != 0, �� ������������� ������ ������ � �����. ����� �����������

extern BOOL         g_fBirth;
extern BOOL         g_fMarriage;
extern BOOL         g_fDivorce;
extern BOOL         g_fChange;
extern BOOL         g_fDeath;

extern BOOL         g_fNoAskMore;

extern CListCtrl*	        g_pMessageList;
extern CProgressCtrl*	    g_pProgress;
extern CStatic*	          g_pInfoBox;
extern CImportProgessDlg* g_pImportProgessDlg;
extern CString g_szCountry, g_szRegion, g_szCity, g_szDistrict;
extern pOnHelpCallback    fOnHelpCallback;


void OnMessage(int nImage, LPCTSTR szMessage);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPEXP_H__A38A91AA_6809_4D26_843C_B000CDFD65D8__INCLUDED_)
