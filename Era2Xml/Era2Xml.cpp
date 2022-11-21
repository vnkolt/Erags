// Era2Xml.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Era2Xml.h"
#include "Era2XmlDlg.h"

#include "Helpers.h"
#include "Globals.h"

#include "..\Common\DAO36.h"

// #include "..\Controls\BkgndCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COLORREF g_clrBackColor = 0xC0C0C0;
COLORREF g_clrForeColor = 0x000000;
COLORREF g_clrFocusBackColor = 0xFFFFFF;
COLORREF g_clrFocusForeColor = 0x000000;

COLORREF g_clrMaleBackColor = 0x808080;
COLORREF g_clrFemaleBackColor = 0x808080;
COLORREF g_clrMaleForeColor = RGB(0x00, 0x00, 0xFF);
COLORREF g_clrFemaleForeColor = RGB(0xFF, 0x00, 0x00);

// void CreateBackgroundBitmap();


WORD ToolId[] = { IDR_NEWMENU256,
                  16, 15,
                  ID_EDIT_CUT,
                  ID_EDIT_COPY,
                  ID_EDIT_PASTE,
                  NULL};


HINSTANCE    g_hHHCTRLInstance = NULL;
/////////////////////////////////////////////////////////////////////////////
// CEra2XmlApp

BEGIN_MESSAGE_MAP(CEra2XmlApp, CWinApp)
	//{{AFX_MSG_MAP(CEra2XmlApp)
	ON_EN_CHANGE(IDC_BIRTH_FROM, OnChangeBirthFrom)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEra2XmlApp construction

CEra2XmlApp::CEra2XmlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEra2XmlApp object

CEra2XmlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEra2XmlApp initialization

BOOL CEra2XmlApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

  CString sMsg;

  try {
    AfxDaoInit36();
  }
  catch(...) {
    sMsg.Format(_T("Увага! Комплекс ЕРАГС використовує компоненти DAO 3.6.\n")
                _T("Будь ласка, встановіть DAO 3.6, а потім запустіть Era2Xml знов.\n")
                _T("Бібліотека DAO 3.6 поставляється разом з ПК ЕРАГС.")
                _T("Вам потрібна інсталяція ПЕ ЕРАГС версії від 31.05.2011 або більш пізньої.")
                );
    AfxMessageBox(sMsg);
    return FALSE;
  }


  // g_fUseGradient = true;
  // CreateBackgroundBitmap();

  LoadIniValues();
  if ( false==LoadMDBValues() ) {
    return false;
  }

	CEra2XmlDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
    return true;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
    return false;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return false;
}

int CEra2XmlApp::ExitInstance() {
	// TODO: Add your specialized code here and/or call the base class
  if ( g_hHHCTRLInstance ) {
    FreeLibrary(g_hHHCTRLInstance);
  }
	
	return CWinApp::ExitInstance();
}

void CEra2XmlApp::OnChangeBirthFrom() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CWinApp::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
