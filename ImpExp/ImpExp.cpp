// ImpExp.cpp : Defines the initialization routines for the DLL.
//
#include "stdafx.h"
#include "ImpExp.h"

// �������
#include "ImportDlg.h"
#include "ImportProgessDlg.h"

#include "..\Common\CyrString.h"
#include "..\Common\DAO36.h"
#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void OnMessage(int nImage, LPCTSTR szMessage) {
  ASSERT ( g_pMessageList );
  if ( g_pMessageList ) {
    int nItem = g_pMessageList->InsertItem(g_pMessageList->GetItemCount(), szMessage, nImage);
    g_pMessageList->EnsureVisible(nItem, false);
  }
  g_pImportProgessDlg->PumpMessages();
}

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CImpExpApp

BEGIN_MESSAGE_MAP(CImpExpApp, CWinApp)
	//{{AFX_MSG_MAP(CImpExpApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImpExpApp construction
CImpExpApp::CImpExpApp() {
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CString      g_szTargetFile;    // ��� ����� ��-��������
CString      g_szSourceFile;    // ��� ����� ��-���������
CDaoDatabase g_TargetDB;        // ��-�������, � ������� ������������� ������
CDaoDatabase g_SourceDB;        // ��-��������, �� ������� ������������� ������
BOOL         g_fNoEmpty = true; // ������������� ������ �������� ������
BOOL         g_fNoExist = true; // �� ������������ ������, ������� ��� ���� � ��-��������
int          g_Year     = 0;    // ���� != 0, �� ������������� ������ ������ � �����. ����� �����������

BOOL         g_fBirth     = true;  // ��������� �� � ��������
BOOL         g_fMarriage  = true;  // ��������� �� � �����
BOOL         g_fDivorce   = true;  // ��������� �� � ����������� �����
BOOL         g_fChange    = true;  // ��������� �� � ��������
BOOL         g_fDeath     = true;  // ��������� �� � ������
BOOL         g_fNoAskMore = false; // ������������ ��� ������ �� �� ������� �������

CListCtrl*          g_pMessageList = NULL; // ListCtrl ��� ������� �����������
CProgressCtrl*	    g_pProgress    = NULL; // ProgressBar ��� �������
CStatic*	          g_pInfoBox     = NULL; // � ����� ���������� ������� ��������
CImportProgessDlg*  g_pImportProgessDlg = NULL;

CString g_szCountry, g_szRegion, g_szCity, g_szDistrict;
pOnHelpCallback    fOnHelpCallback;

void ExportWizard(LPCTSTR szSrcDB);

BOOL AfxDaInitInternal() {
  BOOL fRet = true;
  try {
    AfxDaoInit36();
  }
  catch(...) {
    fRet = false;
    AfxMessageBox(_T("�����! �������� ����� ����������� ���������� DAO 3.6.\n")
                  _T("���� �����, ��������� DAO, � ���� �������� ����� ����.")
                 );
    return 0;
  }
  return fRet;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CImpExpApp object
CImpExpApp theApp;
__declspec(dllexport) int WINAPI Import(LPCTSTR szTo, LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szCity, LPCTSTR szDistrict, pOnHelpCallback fHelpCallback)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  // normal function body here

  if ( false==AfxDaInitInternal() ) {
    return 0;
  }
  
  
  int nImportedRecords = 0;
  g_szTargetFile  = szTo;
  fOnHelpCallback = fHelpCallback;
  CImportDlg dlg;
  g_Year     = atoi(GetFileName(szTo).Left(4)); // ������ 4 ������� ������ �������� ��� �����-��������
  if ( IDOK==dlg.DoModal() ) {
    if ( CyrCompare(szTo, g_szSourceFile)==0 ) {
      ::MessageBox(NULL, _T("�� ����� ����������� � ���� � ���� ������ �����."), _T("�������"), MB_OK|MB_ICONERROR);
      return 0;
    }
    try {
      g_TargetDB.Open(szTo,        // database name
                      false,       // Exclusive
                      false,       // Read only
                      _T(";PWD=")  // szConnect
                     );

    }
    catch(CDaoException* e){
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
      CString s;
      s.Format(_T("�� ������� ������� ���� �� \"%s\"."), szTo);
      ::MessageBox(NULL, s, _T("�������"), MB_OK|MB_ICONERROR);
      AfxDaoTerm();
      return 0;
    }
    if ( g_TargetDB.IsOpen() ) {
      g_szCountry  = szCountry;
      g_szRegion   = szRegion;
      g_szCity     = szCity;
      g_szDistrict = szDistrict;
      CImportProgessDlg dlg;
      dlg.DoModal();
      nImportedRecords = dlg.m_nImportedRecords;
      g_TargetDB.Close();
    }
    AfxDaoTerm();
  }
  return nImportedRecords;
}

__declspec(dllexport) int WINAPI Export(LPCTSTR szSrcDB, pOnHelpCallback fHelpCallback)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  fOnHelpCallback = fHelpCallback;

  if ( false==AfxDaInitInternal() ) {
    return 0;
  }

  g_szSourceFile = szSrcDB;

  try {
    g_SourceDB.Open(g_szSourceFile, // database name
                    false,          // Exclusive
                    true,           // Read only
                    _T(";PWD=")  // szConnect
                   );

  }
  catch(CDaoException* e){
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    CString s;
    s.Format(_T("�� ������� ������� ���� �� \"%s\"."), g_szSourceFile);
    ::MessageBox(NULL, s, _T("�������"), MB_OK|MB_ICONERROR);
    AfxDaoTerm();
    return 0;
  }

  ExportWizard(szSrcDB);
  g_SourceDB.Close();
  // AfxDaoTerm();

  return 0;
}

int CImpExpApp::ExitInstance() {
	// TODO: Add your specialized code here and/or call the base class
	AfxDaoTerm();
	return CWinApp::ExitInstance();
}
