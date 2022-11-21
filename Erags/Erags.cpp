// Erags.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Erags.h"

#include "MainFrm.h"
#include "ChildFrm.h"

#include "BanksDlg.h"
#include "CantOpenDlg.h"
#include "DataManager.h"
#include "DBCauses.h"
#include "DBCitizenships.h"
#include "DBHospitals.h"
#include "DBMIAs.h"
#include "DBNames.h"
#include "DBStreets.h"

#include "NamesDlg.h"

#include "EragsDoc.h"
#include "EragsView.h"

#include "FormBirth.h"
#include "FormMarriage.h"
#include "FormDivorce.h"
#include "FormDeath.h"
#include "FormChange.h"
#include "GeoView.h"

#include "RList.h"
#include "RListDoc.h"

#include "RegFinder.h"

#include "SettingsDlg.h"

#include "Defaults.h"
#include "UnzipDlg.h"
#include "xMachine.h"
#include "ZipDBDlg.h"
#include "LogThread.h"

#include "..\ImpExp\ImpExpDll.h"

#include "..\Common\DAO36.h"
#include "..\Common\EraMessages.h"
#include "..\Common\FHelpers.h"
#include "..\Common\Version.h"
#include "..\Controls\NewMenu.h"
#include "..\Controls\MyFileDialog.h"
#include "..\Controls\HyperLink.h"
#include "..\Controls\ProgressBar.h"

#include <locale.h>
#include <process.h>

#include <HTMLHelp.h>

#include "OODocument.h"
#include "OOView.h"

#include "WordDocument.h"
#include "WordView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef BOOL (*EXPORT pWizard)(LPCTSTR szDBPath);
//extern "C" BOOL PASCAL EXPORT Wizard(LPCTSTR szDBPath);


COLORREF g_clrBackColor = 0xC0C0C0;
COLORREF g_clrForeColor = 0x000000;
COLORREF g_clrFocusBackColor = 0xFFFFFF;
COLORREF g_clrFocusForeColor = 0x000000;
BOOL     g_fSuperVisor  = false;

COLORREF g_clrMaleBackColor = 0x808080;
COLORREF g_clrFemaleBackColor = 0x808080;
short    g_SecurityKeysCheckedOk[4]  = { TRUE, TRUE, TRUE, TRUE};
COLORREF g_clrMaleForeColor = RGB(0x00, 0x00, 0xFF);
COLORREF g_clrFemaleForeColor = RGB(0xFF, 0x00, 0x00);
BOOL     g_fLogging = false;

HBRUSH g_hEditBrush, g_hFocusEditBrush;

#ifndef FREE_LICENCE
int     g_LKeyResult = 0;
#endif // FREE_LICENCE

extern COLORREF g_clrLeft;
extern COLORREF g_clrRight;

UINT res_IDB_HDRUP     = IDB_HDRUP;
UINT res_IDB_HDRDOWN   = IDB_HDRDOWN;

void CreateBackgroundBitmap();
BOOL IsValidRDF();

short    g_SecurityLoaded[4]  = { FALSE, FALSE, FALSE, FALSE};

LPCTSTR g_szDateFormat = _T("dd mmmm yyyy"),
        g_szDateMask = _T("dd.mm.yyyy");

WORD ToolId[] = { IDR_NEWMENU256,
                        16, 15,

                        ID_FILE_NEW,
                        ID_FILE_OPEN,
                        ID_IMPORT,
                        ID_EDIT_CUT,
                        ID_EDIT_COPY,
                        ID_EDIT_PASTE,
                        ID_FILE_PRINT,
                        ID_APP_ABOUT,
                        ID_WINDOW_NEW,
                        ID_WINDOW_CASCADE,
                        ID_WINDOW_TILE_HORZ,
                        ID_WINDOW_TILE_VERT,
                        ID_RECORD_FIRST,
                        ID_RECORD_PREV,
                        ID_RECORD_NEXT,
                        ID_RECORD_LAST,
                        ID_RECORD_NEW,
                        ID_RECORD_DELETE,
                        ID_FILE_PRINT_SETUP,
                        ID_FILE_SAVE_AS,
                        ID_APP_EXIT,
                        ID_EDIT_FIND,
                        ID_FILE_CLOSE,
                        ID_DEFAULT_HELP,
                        ID_HELP_UKR,
                        ID_HELP_RUS,
                        ID_FOLDER_TREE,
                        ID_BIRTH,
                        ID_MARRIAGE,
                        ID_DIVORCE,
                        ID_CHANGE,
                        ID_DEATH,
                        ID_GEOGRAPHY,
                        ID_MEDICS,
                        ID_REGISTRARS,
                        ID_POLICE,
                        ID_BANK,
                        ID_ZIPDB,
                        ID_TEMPLATES,
                        ID_WHAT_IS_IT,
                        NULL};

BOOL PeekAndPump() {
	static MSG msg;
	while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) {
		if (!AfxGetApp()->PumpMessage()) {
			::PostQuitMessage(0);
			return false;
		}	
	}
	return true;
}


void ProgressRoutine(int nCount, int nProcessed, void* lpData) {
  if ( nCount > 0 ) {
    CProgressBar* pBar = (CProgressBar*)lpData;
    int nPercent = (int)((((double(nProcessed)+0.5 )*100))/double(nCount));
    pBar->SetPos( nPercent );
    PeekAndPump();
  }
}

void __cdecl ErrorBox(LPCTSTR format,...) {
  CString szErr;
  va_list va;
  va_start(va, format);
  szErr.FormatV(format, va);
  va_end(va);
  AfxMessageBox(szErr, MB_OK|MB_ICONSTOP);
}

void OnHelpCallback(LPCTSTR szHelpFile) {
  theApp.OnHelp(szHelpFile);
}
/////////////////////////////////////////////////////////////////////////////
// CEragsApp
BEGIN_MESSAGE_MAP(CEragsApp, CWinApp)
	//{{AFX_MSG_MAP(CEragsApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_UPDATE_COMMAND_UI(ID_BIRTH, OnUpdateBirth)
	ON_COMMAND(ID_BIRTH, OnBirth)
	ON_UPDATE_COMMAND_UI(ID_CHANGE, OnUpdateChange)
	ON_COMMAND(ID_CHANGE, OnChange)
	ON_UPDATE_COMMAND_UI(ID_DEATH, OnUpdateDeath)
	ON_COMMAND(ID_DEATH, OnDeath)
	ON_UPDATE_COMMAND_UI(ID_DIVORCE, OnUpdateDivorce)
	ON_COMMAND(ID_DIVORCE, OnDivorce)
	ON_UPDATE_COMMAND_UI(ID_MARRIAGE, OnUpdateMarriage)
	ON_COMMAND(ID_MARRIAGE, OnMarriage)
	ON_UPDATE_COMMAND_UI(ID_MEDICS, OnUpdateMedics)
	ON_COMMAND(ID_MEDICS, OnMedics)
	ON_UPDATE_COMMAND_UI(ID_POLICE, OnUpdatePolice)
	ON_COMMAND(ID_POLICE, OnPolice)
	ON_UPDATE_COMMAND_UI(ID_REGISTRARS, OnUpdateRegistrars)
	ON_COMMAND(ID_REGISTRARS, OnRegistrars)
	ON_UPDATE_COMMAND_UI(ID_GEOGRAPHY, OnUpdateGeography)
	ON_COMMAND(ID_GEOGRAPHY, OnGeography)
	ON_UPDATE_COMMAND_UI(ID_CITIZENSHIPS, OnUpdateCitizenships)
	ON_COMMAND(ID_CITIZENSHIPS, OnCitizenships)
	ON_UPDATE_COMMAND_UI(ID_DEATHCAUSES, OnUpdateDeathcauses)
	ON_COMMAND(ID_DEATHCAUSES, OnDeathcauses)
  ON_UPDATE_COMMAND_UI(ID_NAMES, OnUpdateNames)
  ON_COMMAND(ID_NAMES, OnNames)
	ON_UPDATE_COMMAND_UI(ID_PATRONYMICS, OnUpdatePatronymics)
	ON_COMMAND(ID_PATRONYMICS, OnPatronymics)
	ON_UPDATE_COMMAND_UI(ID_STREETS, OnUpdateStreets)
	ON_COMMAND(ID_STREETS, OnStreets)
	ON_UPDATE_COMMAND_UI(ID_BANK, OnUpdateBank)
	ON_COMMAND(ID_BANK, OnBank)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
  ON_UPDATE_COMMAND_UI(ID_ZIPDB, OnUpdateZipDB)
  ON_COMMAND(ID_ZIPDB, OnZipDB)
	ON_UPDATE_COMMAND_UI(ID_UNZIP, OnUpdateUnzip)
  ON_COMMAND(ID_UNZIP, OnUnzip)
	ON_UPDATE_COMMAND_UI(ID_IMPORT, OnUpdateImport)
  ON_COMMAND(ID_IMPORT, OnImport)
	ON_UPDATE_COMMAND_UI(ID_FILE_RECENT, OnUpdateFileRecent)
	ON_COMMAND(ID_FILE_RECENT, OnFileRecent)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS, OnUpdateSettings)
	ON_COMMAND(ID_SETTINGS, OnSettings)
	ON_COMMAND(ID_HELP_CONTENT, OnHelp)
	ON_UPDATE_COMMAND_UI(ID_HELP_CONTENT, OnUpdateHelp)
	ON_UPDATE_COMMAND_UI(ID_HELP, OnUpdateHelp)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_UPDATE_COMMAND_UI(ID_HELPER, OnUpdateHelper)
	ON_COMMAND(ID_HELPER, OnHelper)
	ON_UPDATE_COMMAND_UI(ID_HELP_UKR, OnUpdateHelpUkr)
	ON_UPDATE_COMMAND_UI(ID_HELP_RUS, OnUpdateHelpRus)
	ON_COMMAND(ID_HELP_UKR, OnHelpLanguage)
	ON_COMMAND(ID_HELP_RUS, OnHelpLanguage)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
  // ON_MESSAGE(WM_EM_DOZIP, &CEragsApp::OnDoZip)
  //  ON_COMMAND_RANGE(ID_FILE_MRU_FIRST, ID_FILE_MRU_LAST, MyMRUFileHandler) 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEragsApp construction

/************************************** : by VK 24.08.2004 at 11:09:22 **\
void CodeStrings() {
  #define XSTR3(str) { str[0]^1, str[1]^2, str[2]^3, str[3] }
  #define XSTR4(str) { str[0]^1, str[1]^2, str[2]^3, str[3], str[4]  }
  #ifdef _DEBUG
    #define XSTR5TRACE(str) { if(sizeof(str)!=5) { MessageBeep(MB_ICONASTERISK); TRACE1("XSTR5: sizeof(str)=%d\n", sizeof(str));}  }
    #define XSTR5(str) { str[0]^1, str[1]^2, str[2]^3, str[3]^4, str[4]^5, str[5]^6 }; XSTR5TRACE(str)
  #else
    #define XSTR5(str) { str[0]^1, str[1]^2, str[2]^3, str[3]^4, str[4]^5, str[5]^6 };
  #endif
  TCHAR szX3[] = XSTR3("АБВ");
  TCHAR szX4[] = XSTR4("АБВГ");
//  TCHAR* szAll[] = { XSTR3("АБВ"), XSTR4("АБВГ") };
}
\************************************** : by VK 24.08.2004 at 11:09:25 **/

LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2) {
  while (p1 != NULL && *p1 != NULL) {
    LPCTSTR p = p2;
    while (p != NULL && *p != NULL) {
      if (*p1 == *p)
        return CharNext(p1);
      p = CharNext(p);
    }
    p1 = CharNext(p1);
  }
  return NULL;
}

CEragsApp::CEragsApp() {
	// TODO: add construction code here,
  m_bGeoLoaded = m_bRegLoaded = FALSE;
	// Place all significant initialization in InitInstance
  m_pBirthTemplate = m_pMarriageTemplate = 
  m_pDivorceTemplate = m_pChangeTemplate = 
  m_pDeathTemplate = m_pWordTemplate =
  m_pOOTemplate = m_pRListTemplate = m_pGeoTemplate = NULL;

  m_pRListFrame = m_pGeoFrame = NULL;

  m_pWordActive = NULL;
  m_pWordView = NULL;
  m_pOOView = NULL;

  m_pDoc = NULL;
  m_fUseHelper = m_fUkrHelp = TRUE;
  m_AccelNavigators = NULL;
	m_nCurrentForm = 0;//Undefined;
  m_fExitApp = m_fReadOnly = false;

  m_fOfficeChanged = true;
  m_nOffice = MS_OFFICE;

  m_dwOfficeInstalled = 0;

  m_RagsID = -1;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEragsApp object

CEragsApp theApp;

CDocument* CEragsApp::OpenDocument(const CString& sDatabase, int iForm) {
  CDocument* pDoc = NULL;
  switch (iForm) {
    case 1:   // Birthes
      m_nCurrentForm = ID_BIRTH;
      pDoc = m_pBirthTemplate->OpenDocumentFile(sDatabase);
      break;
    case 2:   // Marriages
      m_nCurrentForm = ID_MARRIAGE;
      pDoc = m_pMarriageTemplate->OpenDocumentFile(sDatabase);
      break;
    case 3:   // Divorces
      m_nCurrentForm = ID_DIVORCE;
      pDoc = m_pDivorceTemplate->OpenDocumentFile(sDatabase);
      break;
    case 4:   // Changes
      m_nCurrentForm = ID_CHANGE;
      pDoc = m_pChangeTemplate->OpenDocumentFile(sDatabase);
      break;
    case 5:   // Deathes
    default:
      m_nCurrentForm = ID_DEATH;
      pDoc = m_pDeathTemplate->OpenDocumentFile(sDatabase);
      break;
    //default:  pDoc = OpenDocumentFile(sDatabase);
    //  break;
  }
  return pDoc;
}

void DeleteFiles(LPCTSTR szPath) {
  CFileFind finder;
  CString sPath;
  sPath.Format(_T("%s\\*.*"), szPath);
  BOOL bWorking = finder.FindFile(sPath);
  while (bWorking) {
    bWorking = finder.FindNextFile();
    if (finder.IsDots())
         continue;
    if ( finder.IsDirectory() )
      continue;
    CString sFileName = finder.GetFilePath();
    DeleteFile(sFileName);
  }
}

void CEragsApp::CreateFont(const LOGFONT* lpLogFont) {
  m_Font.DeleteObject();
  m_Font.CreateFontIndirect(lpLogFont);
}

void CEragsApp::ResetFont() {
  CMainFrame* pMainFrame = (CMainFrame*)m_pMainWnd;
  CEraForm* pForm = NULL;
  if ( pMainFrame->m_pBirthFrame ) {
    pForm = (CEraForm*)pMainFrame->m_pBirthFrame->GetActiveView();
    if ( pForm ) pForm->SetFont();
  }
  if ( pMainFrame->m_pMarriageFrame ) {
    pForm = (CEraForm*)pMainFrame->m_pMarriageFrame->GetActiveView();
    if ( pForm ) pForm->SetFont();
  }
  if ( pMainFrame->m_pDivorceFrame ) {
    pForm = (CEraForm*)pMainFrame->m_pDivorceFrame->GetActiveView();
    if ( pForm ) pForm->SetFont();
  }
  if ( pMainFrame->m_pChangeFrame ) {
    pForm = (CEraForm*)pMainFrame->m_pChangeFrame->GetActiveView();
    if ( pForm ) pForm->SetFont();
  }
  if ( pMainFrame->m_pDeathFrame ) {
    pForm = (CEraForm*)pMainFrame->m_pDeathFrame->GetActiveView();
    if ( pForm ) pForm->SetFont();
  }
}
void CEragsApp::SaveFont() {
  if ( m_Font.m_hObject ) {
    LOGFONT lf;
    m_Font.GetLogFont(&lf);
    WriteProfileBinary(_T("Settings"), _T("Font"), (LPBYTE)&lf, sizeof(lf));
  }
}
void CEragsApp::RestoreFont() {
  LOGFONT* pLogFont = NULL;
  UINT nSize = 0;
  if(GetProfileBinary(_T("Settings"), _T("Font"), (LPBYTE*)&pLogFont, &nSize)) {
    CreateFont(pLogFont);
    delete pLogFont;
  }
}
void CEragsApp::Wizard(BOOL bRunWizard) {
  CString szHelpers, szWizardDll;
  szHelpers.Format(_T("%s\\DB\\Helpers.mdb"), GetModulePath());
  if ( FALSE==FileExists(szHelpers) ) {
    return;
  }
  if ( bRunWizard || TRUE==GetProfileInt(_T("Settings"), _T("LoadWizard"), TRUE) ) {
    szWizardDll.Format(_T("%s\\EraWiz.dll"), GetModulePath());
    SetLastError(0);
    HINSTANCE hWizard = LoadLibrary(szWizardDll);
    if ( NULL==hWizard ) {
/************************************** : by VK at 05.10.2005 22:56:40 **\
      TCHAR szBuffer[512];
      DWORD dwError = GetLastError();
      FormatMessage(  FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_HMODULE,
                      NULL,
                      dwError, 0, szBuffer, sizeof( szBuffer ), 0 );
      AfxMessageBox(szBuffer);
\************************************** : by VK at 05.10.2005 22:56:43 **/
      return;
    }
    pWizard fWizard = (pWizard)GetProcAddress(hWizard, _T("Wizard"));
    if ( fWizard ) {
      if ( (fWizard)(NULL/*szHelpers*/) ) {
        WriteProfileInt(_T("Settings"), _T("LoadWizard"), FALSE);
      }
    }
    if ( hWizard ) {
      FreeLibrary(hWizard);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////
// CEragsApp initialization
BOOL CEragsApp::PreInitInstance() {
  switch(g_Shell) {
    case Win32s:
    case WinNT3:
    case Win95:
      AfxMessageBox(_T("Програма ERAGS не підтримує цю операційну систему.\n")
                    _T("Для роботи ERAGS потрібна будь-яка із операціїних систем:\n\n")
                    _T("Windows 98, Windows Me, Windows 2000, Windows XP."));
      return FALSE;
  }
  return TRUE;
}
BOOL CEragsApp::InitInstance() {

  if ( FALSE==PreInitInstance() )
    return FALSE;

  if(!AfxOleInit()) { // Your addition starts here
    AfxMessageBox("Could not initialize COM dll");
    return FALSE;
  }                   // End of your addition

  if ( m_pMessageFilter ) {
    m_pMessageFilter->EnableBusyDialog(FALSE);
    m_pMessageFilter->EnableNotRespondingDialog(FALSE);
  }

  {
    CRegFinder msoFinder(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Office"));
    if ( msoFinder.IsOk() ) {
      if ( msoFinder.Find(_T("Word\\InstallRoot"), _T("Path"), _T("WinWord"), m_szMSWordPath) ) {
        m_dwOfficeInstalled |= OFFICE_INSTALED_MSWORD;
      }
      if ( msoFinder.Find(_T("Excel\\InstallRoot"), _T("Path"), _T("Excel"), m_szMSExcelPath) ) {
        m_dwOfficeInstalled |= OFFICE_INSTALED_MSEXCEL;
      }
    }
    CRegFinder ooFinder(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\OpenOffice.org\\OpenOffice.org"));
    if ( ooFinder.IsOk() ) {
      if ( ooFinder.Find(_T("{7C35B9AB-2CE3-4C18-BE7C-5B97EA089EB3}"), _T("INSTALLLOCATION")      , _T("\\program\\swriter"), m_szOOWriterPath) ||
           ooFinder.Find(_T("{7C35B9AB-2CE3-4C18-BE7C-5B97EA089EB3}"), _T("OFFICEINSTALLLOCATION"), _T("\\program\\swriter"), m_szOOWriterPath)
        ) {
        m_dwOfficeInstalled |= OFFICE_INSTALED_SWRITER;
      }
      if ( ooFinder.Find(_T("{7C35B9AB-2CE3-4C18-BE7C-5B97EA089EB3}"), _T("INSTALLLOCATION")      , _T("\\program\\scalc"), m_szOOCalcPath) || 
           ooFinder.Find(_T("{7C35B9AB-2CE3-4C18-BE7C-5B97EA089EB3}"), _T("OFFICEINSTALLLOCATION"), _T("\\program\\scalc"), m_szOOCalcPath)
         ) {
        m_dwOfficeInstalled |= OFFICE_INSTALED_SCALC;
      }
    }
  }

  AfxInitRichEdit();

  ::CoInitialize( NULL );

//  this->m_M
  // Replace test:


	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

  CString sMsg;

  try {
    AfxDaoInit36();
  }
  catch(...) {
    sMsg.Format(_T("Увага! Комплекс ЕРАГС використовує компоненти DAO 3.6.\n")
                _T("Будь ласка, встановіть DAO, а потім запустіть ЕРАГС знов.") );
    AfxMessageBox(sMsg);
    return FALSE;
  }

  AfxEnableControlContainer();

  //CodeStrings();

  // Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Vladimir Koltsov"));

  GetOffice();

/************************************** : by VK at 23.12.2006 9:40:22 **\
  g_fLogging = GetProfileInt(_T("Settings"), _T("MakeLogFile"), false);
  WriteProfileInt(("Settings"), _T("MakeLogFile"), true);
  OpenLog();
\************************************** : by VK at 23.12.2006 9:40:24 **/

  TCHAR szTokens[] = _T("-/");
  LPCTSTR lpszToken = FindOneOf(m_lpCmdLine, szTokens);
  BOOL bRunWizard = false; // Запускаем как мастер установки
  BOOL bSetup     = false; // Запускаем из сетапа
  while (lpszToken != NULL) {
    if (lstrcmpi(lpszToken, _T("Wizard"))==0) {
      bRunWizard = true;
    }
    else if (lstrcmpi(lpszToken, _T("Setup"))==0) {
      bSetup = true;
    }
    else if (lstrcmpi(lpszToken, _T("sv"))==0) { // super visor
      g_fSuperVisor = true;
    }
    lpszToken = FindOneOf(lpszToken, szTokens);
  }
  Wizard(bRunWizard || bSetup);
  if ( bRunWizard ) { // Если запускался мастер
    return false;     // уходим
  }
  if ( bSetup ) {           // После Setupа перезаписываем командную строку,
    m_lpCmdLine[0] = '\0';  // чтобы открыть последний файл из recent-listа.
  }

  m_fUseHelper = GetProfileInt(_T("Settings"), _T("Helper"), TRUE);
  m_fUkrHelp   = GetProfileInt(_T("Settings"), _T("UkrHelp"), TRUE);
  RestoreFont();

  char* pOldLoc = setlocale(LC_ALL, _T("Ukr"));

  g_clrBackColor = GetSysColor(COLOR_3DFACE);
  g_clrForeColor = GetSysColor(COLOR_WINDOWTEXT);
  g_clrFocusBackColor = 0xFFFFFF; // WHITE
  g_clrFocusForeColor = 0x000000; // BLACK

  g_hEditBrush = ::CreateSolidBrush(g_clrBackColor);
  g_hFocusEditBrush = ::CreateSolidBrush(g_clrFocusBackColor);

	CString s;
  m_sTemplatePath.Format(_T("%s\\Templates"), GetModulePath() );
  m_sOutPath.Format(_T("%s\\Out"), GetModulePath() );

  CreateDirectory(m_sOutPath, NULL);
  DeleteFiles(m_sOutPath);

  LoadStdProfileSettings(7);  // Load standard INI file options (including MRU)

  g_clrLeft  = GetProfileInt(_T("Colors"), _T("WindowBackgroundLeft"), GetSysColor(COLOR_BTNFACE));
  g_clrRight = GetProfileInt(_T("Colors"), _T("WindowBackgroundRight"), GetSysColor(COLOR_WINDOW));
  CreateBackgroundBitmap();

  CNewMenu::SetMenuDrawMode(CNewMenu::STYLE_MONOCHROME/*STYLE_XP_2003*/);
  CNewMenu::SetSelectDisableMode(0);  // Selection
  CNewMenu::SetXpBlending(0);         // Gloom
  CNewMenu::SetAcceleratorsDraw(1);   // AcceleratorsDraw

  time_t t = time(NULL);

  g_pMachine = (CXMachine*) AfxBeginThread(RUNTIME_CLASS(CXMachine), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
  g_pMachine->m_pMainWnd = NULL;
  g_pMachine->ResumeThread();

  m_AccelNavigators = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(IDR_NAVIGATORS));

	m_pDeathTemplate = new CNewMultiDocTemplate(IDR_MAINFRAME,
		                                       RUNTIME_CLASS(CEragsDoc),
		                                       RUNTIME_CLASS(CChildFrame),
		                                       RUNTIME_CLASS(CFormDeath));
	AddDocTemplate(m_pDeathTemplate);
  m_pDeathTemplate->m_NewMenuShared.LoadToolBar(ToolId,RGB(192,192,192)); 
  m_pDeathTemplate->LoadDocString(IDR_ERAGSTYPE);

	m_pDivorceTemplate = new CNewMultiDocTemplate(IDR_MAINFRAME,
		                                         RUNTIME_CLASS(CEragsDoc),
		                                         RUNTIME_CLASS(CChildFrame),
  	                                         RUNTIME_CLASS(CFormDivorce));

  m_pDivorceTemplate->m_NewMenuShared.LoadToolBar(ToolId,RGB(192,192,192)); 
  //m_pDivorceTemplate->LoadDocString(IDR_ERAGSTYPE);
  AddDocTemplate(m_pDivorceTemplate);
	//g_pMachine->AddCommand( new CCheckDebugger(m_pDeathTemplate, m_pDivorceTemplate) );
  g_pMachine->AddCommand( new CIsDebuggerPresent(m_pDeathTemplate, m_pDivorceTemplate) );


	m_pBirthTemplate = new CNewMultiDocTemplate(IDR_MAINFRAME,
		                                       RUNTIME_CLASS(CEragsDoc),
		                                       RUNTIME_CLASS(CChildFrame),
		                                       RUNTIME_CLASS(CFormBirth));
  m_pBirthTemplate->m_NewMenuShared.LoadToolBar(ToolId,RGB(192,192,192)); 
  //m_pBirthTemplate->LoadDocString(IDR_ERAGSTYPE);
	AddDocTemplate(m_pBirthTemplate);


	m_pMarriageTemplate = new CNewMultiDocTemplate(IDR_MAINFRAME,
		                                          RUNTIME_CLASS(CEragsDoc),
		                                          RUNTIME_CLASS(CChildFrame),
		                                          RUNTIME_CLASS(CFormMarriage));
  m_pMarriageTemplate->m_NewMenuShared.LoadToolBar(ToolId,RGB(192,192,192)); 
  //m_pMarriageTemplate->LoadDocString(IDR_ERAGSTYPE);
	AddDocTemplate(m_pMarriageTemplate);

  if ( time(NULL)-t > 8)
    g_pMachine->AddCommand( new CSetDebuggerPresent1() );

	m_pChangeTemplate = new CNewMultiDocTemplate(IDR_MAINFRAME,
		                                         RUNTIME_CLASS(CEragsDoc),
		                                         RUNTIME_CLASS(CChildFrame),
		                                         RUNTIME_CLASS(CFormChange));
  m_pChangeTemplate->m_NewMenuShared.LoadToolBar(ToolId,RGB(192,192,192)); 
  //m_pChangeTemplate->LoadDocString(IDR_ERAGSTYPE);
	AddDocTemplate(m_pChangeTemplate);

	m_pWordTemplate = new CNewMultiDocTemplate(IDR_REPORTFRAME,
		                                        RUNTIME_CLASS(CWordDocument),
		                                        RUNTIME_CLASS(CMDIChildWnd/*CReportFrame*/),
		                                        RUNTIME_CLASS(CWordView));
	m_pWordTemplate->SetContainerInfo(/*IDR_REPORTFRAME*/IDR_CNTR_INPLACE);
  AddDocTemplate(m_pWordTemplate);


	m_pOOTemplate = new CNewMultiDocTemplate(IDR_REPORTFRAME,
		                                        RUNTIME_CLASS(COODocument),
		                                        RUNTIME_CLASS(CMDIChildWnd),
		                                        RUNTIME_CLASS(COOView));
	m_pOOTemplate->SetContainerInfo(/*IDR_REPORTFRAME*/IDR_CNTR_INPLACE);
  AddDocTemplate(m_pOOTemplate);

  m_pRListTemplate = new CNewMultiDocTemplate(IDR_MAINFRAME,
		                                         RUNTIME_CLASS(CRListDoc),
		                                         RUNTIME_CLASS(CChildFrame),
		                                         RUNTIME_CLASS(CRListView));
  m_pRListTemplate->m_NewMenuShared.LoadToolBar(ToolId,RGB(192,192,192)); 
	AddDocTemplate(m_pRListTemplate);

/************************************** : by VK at 23/06/2007 16:19:03 **\
	m_pGeoTemplate = new CNewMultiDocTemplate(IDR_MAINFRAME,
		                                        RUNTIME_CLASS(CRListDoc),
		                                        RUNTIME_CLASS(CChildFrame),
		                                        RUNTIME_CLASS(CGeoListView));
\************************************** : by VK at 23/06/2007 16:19:09 **/
	m_pGeoTemplate = new CNewMultiDocTemplate(IDR_MAINFRAME,
		                                        RUNTIME_CLASS(CRListDoc),
		                                        RUNTIME_CLASS(CChildFrame),
		                                        RUNTIME_CLASS(CGeoView));

  m_pGeoTemplate->m_NewMenuShared.LoadToolBar(ToolId,RGB(192,192,192)); 
	AddDocTemplate(m_pGeoTemplate);

#ifndef FREE_LICENCE
  theRegTimer.Startup();
#endif

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;


	// This code replaces the MFC created menus with the Ownerdrawn versions 
/************************************** : by VK at 10.12.2004 23:18:55 **\
	m_pDeathTemplate->m_hMenuShared=pMainFrame->NewMenu();
  m_pBirthTemplate->m_hMenuShared = m_pDeathTemplate->m_hMenuShared;
  m_pMarriageTemplate->m_hMenuShared= m_pDeathTemplate->m_hMenuShared;
  m_pDivorceTemplate->m_hMenuShared = m_pDeathTemplate->m_hMenuShared;
  m_pChangeTemplate->m_hMenuShared= m_pDeathTemplate->m_hMenuShared;
	pMainFrame->m_hMenuDefault=pMainFrame->NewDefaultMenu();
\************************************** : by VK at 10.12.2004 23:19:00 **/
	
	// This simulates a window being opened if you don't have
	// a default window displayed at startup

//	pMainFrame->OnUpdateFrameMenu(pMainFrame->m_hMenuDefault);

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

//	pMainFrame->ShowWindow(m_nCmdShow);
//	pMainFrame->UpdateWindow();
	if (m_lpCmdLine[0] == 0) {
    CString sDatabase = GetProfileString(_T("Settings"), _T("Database") );
    if ( !sDatabase.IsEmpty() ) {
_Open:
      if ( FileExists(sDatabase) ) {
        ZipIfItsNeed(sDatabase);
        OpenDocument( sDatabase, theApp.GetDefaultForm() );
      }
      else {
        CCantOpenDlg dlg;
        dlg.m_szFilename = sDatabase;
        if ( IDYES==dlg.DoModal()) {
          switch( dlg.m_idCheckedButton ) {
            case IDC_RADIO1:  // try again
              goto _Open;
            case IDC_RADIO2:  // call open file dialog
              OnFileOpen();
              break;
            default:
              break;
          }
        }
        else
          return false;
      }
    /************************************** : by VK at 12.01.2004 23:34:20 **\
      if ( theDataManager.OpenDatabases(sDatabase) )
        theDataManager.LoadTextData();
    \************************************** : by VK at 12.01.2004 23:34:24 **/
    }
    else
      theDataManager.FindAndLoadHelpersDB();
  }

	// The main window has been initialized, so show and update it.
  pMainFrame->ShowWindow(m_nCmdShow);
  pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog {
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_sVersion;
	//}}AFX_DATA
  CFont       m_Font;
  CHyperLink  m_EMailLink;
  CHyperLink  m_WebSite;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
  m_sVersion.Format(_T("ЕРАГС версія %s."), extGetModuleVersion(NULL) );
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_VERSION, m_sVersion);
  DDX_Control(pDX, IDC_EMAILLINK, m_EMailLink);
  DDX_Control(pDX, IDC_WEBSITE, m_WebSite);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Font.CreateFont(-12, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

  GetDlgItem(IDC_VERSION)->SetFont(&m_Font);
  GetDlgItem(IDC_COPYRIGHT)->SetFont(&m_Font);
  GetDlgItem(IDC_REGINFO)->SetFont(&m_Font);

  m_EMailLink.SetURL(_T("mailto:erags@ukr.net"));
  m_WebSite.SetURL(_T("http://sites.google.com/site/pkerags"));
  //m_EMailLink.SetUnderline(CHyperLink::ulAlways);

#ifdef FREE_LICENCE
  CString s;
  s.Format(_T("Ліцензією на поточну копію ПК ЕРАГС володіє:\n%s"), theIniCache.GetRAGS());
  GetDlgItem(IDC_LICENSED_TO)->SetWindowText(s);
#else
  if ( LK_VALID_LICENCE==g_LKeyResult || LK_LICENCE_NOTEXPIRED==g_LKeyResult || IsValidRDF() ) {
    CString s;
    s.Format(_T("Ліцензією на поточну копію ПК ЕРАГС володіє:\n%s"), theIniCache.GetRAGS());
    GetDlgItem(IDC_LICENSED_TO)->SetWindowText(s);
  }
  else {
    GetDlgItem(IDC_LICENSED_TO)->SetWindowText(_T("Поточна копія ПК ЕРАГС не зареєстрована"));
  }
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// App command to run the dialog
void CEragsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CEragsApp message handlers


void CEragsApp::OnUpdateBirth(CCmdUI* pCmdUI) {
  pCmdUI->Enable( theDataManager.m_fBirthesTable);
}

void CEragsApp::OnBirth() {
  ((CMainFrame*)m_pMainWnd)->OnRegistration(ID_BIRTH);
}

void CEragsApp::OnUpdateChange(CCmdUI* pCmdUI) {
  pCmdUI->Enable( theDataManager.m_fChangesTable);
}

void CEragsApp::OnChange() {
  ((CMainFrame*)m_pMainWnd)->OnRegistration(ID_CHANGE);
}

void CEragsApp::OnUpdateDeath(CCmdUI* pCmdUI) {
  pCmdUI->Enable( theDataManager.m_fDeathesTable);
}

void CEragsApp::OnDeath() {
  ((CMainFrame*)m_pMainWnd)->OnRegistration(ID_DEATH);
}

void CEragsApp::OnUpdateDivorce(CCmdUI* pCmdUI) {
  pCmdUI->Enable( theDataManager.m_fDivorcesTable);
}

void CEragsApp::OnDivorce() {
  ((CMainFrame*)m_pMainWnd)->OnRegistration(ID_DIVORCE);
}

void CEragsApp::OnUpdateMarriage(CCmdUI* pCmdUI) {
  pCmdUI->Enable( theDataManager.m_fMarrigesTable);
}

void CEragsApp::OnMarriage() {
  ((CMainFrame*)m_pMainWnd)->OnRegistration(ID_MARRIAGE);
}

void CEragsApp::OnUpdateMedics(CCmdUI* pCmdUI) {
	pCmdUI->Enable( theDataManager.m_fHospitalsTable);
}

void CEragsApp::OnMedics() {
	CDBHospitals dlg(AfxGetMainWnd());
	dlg.DoModal();
  theDataManager.FillHospitals();
}

/************************************** : by VK at 02.04.2004 1:34:17 **\
void CEragsApp::MyMRUFileHandler(UINT i) {
   ASSERT_VALID(this);
   ASSERT(m_pRecentFileList != NULL);

   ASSERT(i >= ID_FILE_MRU_FILE1);
   ASSERT(i < ID_FILE_MRU_FILE1 + (UINT)m_pRecentFileList->GetSize());

   CString strName, strCurDir, strMessage;
   int nIndex = i - ID_FILE_MRU_FILE1;
   ASSERT((*m_pRecentFileList)[nIndex].GetLength() != 0);


  CDocument* pDoc = NULL;

  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  CFrameWnd* pForm = pMainWnd->GetActiveFrame();
  if ( pForm ) {
    m_pBirthTemplate->CloseAllDocuments(FALSE);
    m_pMarriageTemplate->CloseAllDocuments(FALSE);
    m_pDivorceTemplate->CloseAllDocuments(FALSE);
    m_pChangeTemplate->CloseAllDocuments(FALSE);
    m_pDeathTemplate->CloseAllDocuments(FALSE);
    //pDoc = pForm->GetActiveDocument();
  }

  pDoc = OpenDocumentFile((*m_pRecentFileList)[nIndex]);

  if ( pDoc ) {
  }
  else
    m_pRecentFileList->Remove(nIndex);

}
\************************************** : by VK at 02.04.2004 1:34:35 **/

void CEragsApp::OnUpdatePolice(CCmdUI* pCmdUI) {
  pCmdUI->Enable( theDataManager.m_fMIATable );	
}

void CEragsApp::OnPolice() {
  CDBMIAs dlg(AfxGetMainWnd());
	dlg.DoModal();
  theDataManager.FillMIAs();
}

void CEragsApp::OnUpdateRegistrars(CCmdUI* pCmdUI) {
  pCmdUI->Enable( theDataManager.m_fRListTable );	
}

void CEragsApp::OnRegistrars() {
	// TODO: Add your command handler code here
  if ( theRList.IsEmpty() ) {
    theRList.Load();
  }
  if ( m_pRListFrame ) {
    m_pRListFrame->ActivateFrame(SW_SHOWMAXIMIZED);
  }
  else {
    m_pRListTemplate->OpenDocumentFile(NULL, TRUE);
  }
}
void CEragsApp::OnUpdateGeography(CCmdUI* pCmdUI) {
	pCmdUI->Enable(m_bGeoLoaded);
}
void CEragsApp::OnGeography() {
  if ( m_pGeoFrame ) {
    m_pGeoFrame->ActivateFrame(SW_SHOWMAXIMIZED);
  }
  else {
    m_pGeoTemplate->OpenDocumentFile(NULL, TRUE);
  }
}

void CEragsApp::OnUpdateCitizenships(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( theDataManager.m_fCitizenshipsTable );	
}

void CEragsApp::OnCitizenships() {
  CDBCitizenships dlg(AfxGetMainWnd());
	dlg.DoModal();
  theDataManager.FillCitizenships();
}

void CEragsApp::OnUpdateDeathcauses(CCmdUI* pCmdUI) {
	pCmdUI->Enable( theDataManager.m_fCausesOfDeathTable );	
}

void CEragsApp::OnDeathcauses() {
  CDBCauses dlg(AfxGetMainWnd());

	dlg.DoModal();
  CMDIChildWnd* pFrame = ((CMainFrame*)(AfxGetMainWnd()))-> MDIGetActive();
  if ( pFrame ) {
    CEraForm* pForm = (CEraForm*)pFrame->GetActiveView();
    if ( pForm->IsKindOf(RUNTIME_CLASS(CFormDeath)) ) {
      CFormDeath* pFormDeath = (CFormDeath*)pForm;
      pFormDeath->LoadCauses();
      pFormDeath->FillCauseCmb();
    }
  }

}

void CEragsApp::OnUpdateNames(CCmdUI* pCmdUI) {
	pCmdUI->Enable(theDataManager.m_fNamesTable);
}
void CEragsApp::OnNames() {
  CNamesDlg dlg(_T("Імена"), _T("Names"), _T("NAME"), _T("Ім'я"));
  dlg.DoModal();
}

void CEragsApp::OnUpdatePatronymics(CCmdUI* pCmdUI) {
	pCmdUI->Enable( theDataManager.m_fPatronymicsTable );
}

void CEragsApp::OnPatronymics() {
  CNamesDlg dlg(_T("По батькові"), _T("Patronymics"), _T("PATRONYMIC"), _T("По батькові"));
  dlg.DoModal();
}

void CEragsApp::OnUpdateStreets(CCmdUI* pCmdUI) {
	pCmdUI->Enable( theDataManager.m_fStreetTable );
}

void CEragsApp::OnStreets() {
  CDBStreets dlg(AfxGetMainWnd());
	dlg.DoModal();
  theDataManager.FillStreets();
}

int CEragsApp::ExitInstance() {
	// TODO: Add your specialized code here and/or call the base class
  theRList.Clear();
  theDataManager.CloseDatabases();

#ifndef FREE_LICENCE
  theRegTimer.Shutdown();
#endif
  
  try {
    g_pMachine->Stop();
  }
  catch(...) { ; }
  ::CoUninitialize();

  ::DeleteObject(g_hEditBrush);
  ::DeleteObject(g_hFocusEditBrush);
  CloseLog();
  WriteProfileInt(("Settings"), _T("MakeLogFile"), false);
	return CWinApp::ExitInstance();
}
BOOL CEragsApp::PreTranslateMessage(MSG* pMsg) {
  if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST && theApp.m_AccelNavigators ) {
    CView* pView = GetGetActiveForm();
    if ( pView && pView->IsKindOf(RUNTIME_CLASS(CEraForm)) ) {
      if ( ::TranslateAccelerator(pView->m_hWnd, m_AccelNavigators, pMsg) ) {
        ((CEraForm*)pView)->m_tooltip.HideTooltip();
        return true;
      }
    }
  }
/*
  if ( WM_LBUTTONUP==pMsg->message ) {
    WORD wNotifyCode = HIWORD(pMsg->wParam); // notification code 
    WORD wID         = LOWORD(pMsg->wParam); // item, control, or accelerator identifier 
    HWND hwndCtl     = (HWND) pMsg->lParam;  // handle of control
  }
*/
  return CWinApp::PreTranslateMessage(pMsg);
}
void CEragsApp::OnUpdateBank(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
  pCmdUI->Enable(TRUE);
/************************************** : by VK at 23.09.2004 23:57:17 **\
  pCmdUI->Enable( FileExists(m_sDBIniFile) );
\************************************** : by VK at 23.09.2004 23:57:21 **/
}

void CEragsApp::OnBank() {
	// TODO: Add your command handler code here
  CBanksDlg dlg(AfxGetMainWnd());
	dlg.DoModal();
}

void CEragsApp::OnFileNew() {
	// TODO: Add your command handler code here
  CString sDBFile = GetFilePath(theApp.GetProfileString(_T("Settings"), _T("Database"), _T("")));
  if ( sDBFile.IsEmpty() ) {
    CString s;
    s.Format(_T("%s\\DB\\Helpers.mdb"), GetModulePath() );
    if ( FileExists(s) )
      sDBFile = GetFilePath(s);
  }
  if ( false==theDataManager.m_dbLists.IsOpen() ) {
    theDataManager.FindAndLoadHelpersDB();
  }
  CMyFileDialog ofd(TRUE, "*.er3", NULL, OFN_HIDEREADONLY|OFN_LONGNAMES, _T("Файли БД ЕРАГС(*.er3)|*.er3|"), AfxGetMainWnd());
  ofd.SetTitle(IDD_FILE_NEW, _T("Створити новий файл БД ЕРАГС"));
  ofd.m_ofn.lpstrInitialDir = sDBFile;
  if (IDOK==ofd.DoModal() ) {
    CString sExt;
    CString sFileName = ofd.GetPathName();
    sFileName.Replace(_T("І"), _T("I")); sFileName.Replace(_T("і"), _T("i"));
    sExt = sFileName.Right(3);
    sExt.MakeLower();
    if ( sExt != _T("er3") ) {
      sFileName += _T(".er3");
    }
    sFileName.Replace(_T(" .er3"), _T(".er3"));
    if ( FALSE==FileExists(sFileName) ) {
      CString sTemplateDB;
      sTemplateDB.Format(_T("%s\\DBTemplate.mdb"), m_sTemplatePath);
      CopyFile(sTemplateDB, sFileName, FALSE);
    }
    CloseAllDocuments(FALSE);
    OpenDocumentFile(sFileName);
  }
}
void CEragsApp::OnFileOpen() {
	// TODO: Add your command handler code here
  CString sDBFile = GetFilePath(theApp.GetProfileString(_T("Settings"), _T("Database"), _T("")));

  if ( sDBFile.IsEmpty() ) {
    sDBFile.Format(_T("%s\\DB"), GetModulePath());
    if ( false==FileExists(sDBFile) ) {
      sDBFile.Empty();
    }
  }
  
  CMyFileDialog ofd(TRUE, "*.er3", NULL, OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_LONGNAMES, _T("Файли БД ЕРАГС(*.er3)|*.er3|"), AfxGetMainWnd());
  ofd.m_ofn.lpstrInitialDir = sDBFile;
  ofd.SetTitle(0, _T("Відкрити файл бази даних"));
  if ( IDOK==ofd.DoModal() ) {
    AfxGetApp()->OpenDocumentFile(ofd.GetPathName());
  }
}

void CEragsApp::OnUpdateZipDB(CCmdUI* pCmdUI) {
	pCmdUI->Enable(g_LocalDB);
}

/*
LRESULT CEragsApp::OnDoZip(WPARAM, LPARAM) {
  CString sDatabase = theDataManager.GetYearDBName();
  theApp.m_pBirthTemplate->CloseAllDocuments(FALSE);
  theApp.m_pMarriageTemplate->CloseAllDocuments(FALSE);
  theApp.m_pDivorceTemplate->CloseAllDocuments(FALSE);
  theApp.m_pChangeTemplate->CloseAllDocuments(FALSE);
  theApp.m_pDeathTemplate->CloseAllDocuments(FALSE);
  theApp.m_pWordTemplate->CloseAllDocuments(FALSE);
  theApp.m_pOOTemplate->CloseAllDocuments(FALSE);
  theDataManager.CloseDatabases();

  AfxGetMainWnd()->InvalidateRect(NULL);
  CZipDBDlg dlg( AfxGetMainWnd() );
  dlg.DoModal();
  theDataManager.OpenDatabases(sDatabase);
  theApp.OpenDocument(sDatabase, theApp.m_nCurrentForm);
  return 0L;
}
*/

void CEragsApp::OnZipDB() {
  if ( g_LocalDB ) {
    // theApp.PostThreadMessage(WM_EM_DOZIP, 0, 0);
    AfxGetMainWnd()->PostMessage(WM_EM_DOZIP, 0, 0);
  }
}
void CEragsApp::OnUpdateUnzip(CCmdUI* pCmdUI) {
	pCmdUI->Enable(TRUE);
}
void CEragsApp::OnUnzip() {
  Unzip();
}


void CEragsApp::OnUpdateImport(CCmdUI* pCmdUI) {
  pCmdUI->Enable(theDataManager.m_dbYear.IsOpen());
}
void CEragsApp::OnImport() {
  long nImportedRecords = 0;
  nImportedRecords = Import((LPCTSTR)theDataManager.m_strYearDBName,
                                   (LPCTSTR)theIniCache.GetCOUNTRY(),
                                   (LPCTSTR)theIniCache.GetREGION(),
                                   (LPCTSTR)theIniCache.GetCITY(),
                                   (LPCTSTR)theIniCache.GetDISTRICT(),
                                   OnHelpCallback
                           );
  if ( nImportedRecords ) {
    RefreshForms(); // После импорта нужно перечитать данные в активных формах
  }

/*
  typedef void (*pOnHelpCallback)(LPCTSTR szHelpFile);
  typedef int (WINAPI* pImport)(LPCTSTR szTo, LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szCity, LPCTSTR szDistrict, pOnHelpCallback fHelpCallback);
  long nImportedRecords = 0;
  HINSTANCE hImpExp = LoadLibrary("ImpExp.dll");
  if( hImpExp ) {
    pImport fImport = (pImport)GetProcAddress(hImpExp, _T("Import"));
    if ( fImport ) {
      nImportedRecords = (fImport)((LPCTSTR)theDataManager.m_strYearDBName,
                                   (LPCTSTR)theIniCache.GetCOUNTRY(),
                                   (LPCTSTR)theIniCache.GetREGION(),
                                   (LPCTSTR)theIniCache.GetCITY(),
                                   (LPCTSTR)theIniCache.GetDISTRICT(),
                                   OnHelpCallback
                                  );
    }
    FreeLibrary(hImpExp);
  }
  if ( nImportedRecords ) {
    RefreshForms(); // После импорта нужно перечитать данные в активных формах
  }
*/
}
void CEragsApp::OnUpdateFileRecent(CCmdUI* pCmdUI) {
	pCmdUI->Enable(TRUE);
}
void CEragsApp::OnFileRecent() {
  CNewMenu menu;
  menu.LoadMenu(IDR_FILEDROPDOWN);

  CNewMenu* pPopup = DYNAMIC_DOWNCAST(CNewMenu,menu.GetSubMenu(0));
//  pPopup = menu.GetSubMenu(0);
  ASSERT(pPopup);
  POINT p;
  GetCursorPos(&p);
  HWND hWnd = WindowFromPoint(p);
  if ( hWnd ) {
    RECT r;
    ::GetWindowRect(hWnd, &r);
    p.y = r.bottom;
    GetMainWnd()->GetClientRect(&r);
    GetMainWnd()->ClientToScreen(&r);
    p.x = r.left;
  }
  pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL, p.x, p.y, GetMainWnd(), NULL);
}

void CEragsApp::OnUpdateSettings(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
}

void CEragsApp::OnSettings() {
	// TODO: Add your command handler code here
  CSettingsDlg dlg(_T("Установи"), AfxGetMainWnd(), 0);
  if ( IDOK==dlg.DoModal() ) {
    if ( dlg.m_pageThemes.m_fColorChanged ) 
      UpdateTopFrames();
  }
}

void CEragsApp::OnUpdateHelp(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
  pCmdUI->Enable(true);
}
void CEragsApp::OnHelp(LPCTSTR szHtmFileName, LPCTSTR szReference/*=_T("")*/) {
  static HINSTANCE hInst = NULL;
  typedef HWND (WINAPI *FPHH) (HWND,LPCSTR,UINT,DWORD);
  FPHH htmlHelp;
  if ( NULL==hInst ) {
    hInst = LoadLibrary("HHCTRL.OCX");
  }
  if ( hInst ) {
    (FARPROC&) htmlHelp = GetProcAddress(hInst,"HtmlHelpA");
    if ( htmlHelp ) {
      CString szHelpDirectory, szHelpPostfix;
      szHelpDirectory.Format(_T("%s\\Help"), GetModulePath());
      szHelpPostfix = GetHelpPostfix();

      CString szFileName;
      szFileName.Format(_T("%s\\Erags_%s.chm::/%s_%s.htm%s"), szHelpDirectory, szHelpPostfix, szHtmFileName, szHelpPostfix, szReference);
      htmlHelp(GetDesktopWindow(),szFileName,HH_DISPLAY_TOPIC,NULL);
    }
  }
}
void CEragsApp::OnHelp() {
  OnHelp(_T("Default"));
}

void CEragsApp::OnUpdateHelper(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
  pCmdUI->SetCheck(m_fUseHelper);
}

void CEragsApp::OnHelper() {
  m_fUseHelper = !m_fUseHelper;
  WriteProfileInt(_T("Settings"), _T("Helper"), m_fUseHelper);
  if ( m_fUseHelper ) {
    CFrameWnd* pFrame = ((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
    if ( pFrame ) {
      CEraForm* pForm = (CEraForm*)pFrame->GetActiveView();
      if ( pForm && pForm->IsKindOf(RUNTIME_CLASS(CEraForm)) ) {
        pForm->SetTooltips();
      }
    }	
  }
  CString s;
  s.Format(_T("Помічник %s"), m_fUseHelper ? _T("включено") : _T("виключено"));
  OnMessage(EM_INFO, s);
}

void CEragsApp::OnUpdateHelpUkr(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
  pCmdUI->Enable(TRUE);
  pCmdUI->SetCheck(m_fUkrHelp);
}

void CEragsApp::OnUpdateHelpRus(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
  pCmdUI->Enable(TRUE);
  pCmdUI->SetCheck(!m_fUkrHelp);
}

void CEragsApp::OnHelpLanguage() {
  m_fUkrHelp = m_fUkrHelp ? FALSE : TRUE;
  WriteProfileInt(_T("Settings"), _T("UkrHelp"), m_fUkrHelp);

  CMDIChildWnd* pFrame = ((CMainFrame*)(AfxGetMainWnd()))-> MDIGetActive();
  if ( pFrame ) {
    CEraForm* pForm = (CEraForm*)pFrame->GetActiveView();
    if ( pForm->IsKindOf(RUNTIME_CLASS(CEraForm)) ) {
      pForm->SetTooltips();
    }
  }
}

bool CEragsApp::SetDBFolder(LPCTSTR szDBFileName) {
  CString sHelpers;
  sHelpers.Format(_T("%s\\DB\\Helpers.mdb"), GetModulePath());
  if ( FileExists(sHelpers) ) {
    m_sDBFolder = GetFilePath(sHelpers);
    m_sHelpersMDB = sHelpers;
    return true;
  }

  CString sFolder = GetFilePath(szDBFileName);
  sHelpers.Format(_T("%s\\Helpers.mdb"), sFolder);
  if ( FileExists(sHelpers) ) {
    m_sDBFolder = sFolder;
    m_sHelpersMDB = sHelpers;
    return true;
  }
  if ( sFolder.ReverseFind('\\') > 0 )
    return SetDBFolder(sFolder);

  CString sMsg;
  sMsg.Format( _T("Увага!\nНемає файла \"Helpers.mdb\" у папці \"%s\".\n")
               _T("Цей файли потрібен для правильної роботи ЕРАГС.\n\n")
               _T("Вам потрібно переустановити ЕРАГС або відкрити файл БД з іншої папки."),
               GetFilePath(szDBFileName) );
  AfxMessageBox(sMsg);

  return false;
}

CDocument* CEragsApp::OpenDocumentFile(LPCTSTR lpszFileName) {
  CString sIni;
  if ( !SetDBFolder(lpszFileName) ) {
    return NULL;
  }

  CWaitCursor wc;
	ASSERT(m_pDocManager != NULL);
  m_pDocManager->CloseAllDocuments(FALSE);
  return OpenDocument(lpszFileName, theApp.GetDefaultForm());
	//return m_pDocManager->OpenDocumentFile(lpszFileName);
}

CView* CEragsApp::GetGetActiveForm() {
  CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
  if ( NULL==pMainFrm )
    return NULL;
  CFrameWnd* pFrame = pMainFrm->GetActiveFrame();
  if ( NULL==pFrame )
    return NULL;
  CView* pView = pFrame->GetActiveView();
  if ( NULL==pView )
    return NULL;
  if ( pView->IsKindOf(RUNTIME_CLASS(CFormBirth))     ||
       pView->IsKindOf(RUNTIME_CLASS(CFormMarriage))  ||
       pView->IsKindOf(RUNTIME_CLASS(CFormDivorce))   ||
       pView->IsKindOf(RUNTIME_CLASS(CFormDeath))     ||
       pView->IsKindOf(RUNTIME_CLASS(CFormChange))    ||
       pView->IsKindOf(RUNTIME_CLASS(CRListView))     ||
       pView->IsKindOf(RUNTIME_CLASS(CGeoView)) 
     )
    return pView;
  return NULL;
}

LPCTSTR CEragsApp::GetFormName(UINT FormID) {
  switch(FormID) {
    case ID_BIRTH:    return _T("Birth");
    case ID_MARRIAGE: return _T("Marriage");
    case ID_DIVORCE:  return _T("Divorce");
    case ID_CHANGE:   return _T("Change");
    case ID_DEATH:    return _T("Death");
  }
  return _T("Unknown");
}
LPCTSTR CEragsApp::GetCyrFormName(UINT FormID) {
  switch(FormID) {
    case ID_BIRTH:    return _T("Народження");
    case ID_MARRIAGE: return _T("Шлюби");
    case ID_DIVORCE:  return _T("Розірвання Шлюбів");
    case ID_CHANGE:   return _T("Зміни");
    case ID_DEATH:    return _T("Смерті");
  }
  return _T("Unknown");
}
void CEragsApp::RefreshForms() {
  CMainFrame* pMainFrame = (CMainFrame*)m_pMainWnd;
  CEraForm* pForm = NULL;
  if ( pMainFrame->m_pBirthFrame ) {
    pForm = (CEraForm*)pMainFrame->m_pBirthFrame->GetActiveView();
    if ( pForm ) pForm->Refresh();
  }
  if ( pMainFrame->m_pMarriageFrame ) {
    pForm = (CEraForm*)pMainFrame->m_pMarriageFrame->GetActiveView();
    if ( pForm ) pForm->Refresh();
  }
  if ( pMainFrame->m_pDivorceFrame ) {
    pForm = (CEraForm*)pMainFrame->m_pDivorceFrame->GetActiveView();
    if ( pForm ) pForm->Refresh();
  }
  if ( pMainFrame->m_pChangeFrame ) {
    pForm = (CEraForm*)pMainFrame->m_pChangeFrame->GetActiveView();
    if ( pForm ) pForm->Refresh();
  }
  if ( pMainFrame->m_pDeathFrame ) {
    pForm = (CEraForm*)pMainFrame->m_pDeathFrame->GetActiveView();
    if ( pForm ) pForm->Refresh();
  }
}
void CAboutDlg::OnOK() {
	// TODO: Add extra validation here
	CDialog::OnOK();
}

/************************************** : by VK at 23.02.2005 23:17:24 **\
void CEragsApp::OnFind() {

	// TODO: Add your command handler code here
  POSITION pos =	m_pRFindTemplate->GetFirstDocPosition();
  if ( pos ) {
    CRFindDoc* pDoc = (CRFindDoc*)m_pRFindTemplate->GetNextDoc(pos);
    if ( pDoc ) {
      pos = pDoc->GetFirstViewPosition();
      if ( pos ) {
        CView* pView = pDoc->GetNextView(pos);
        if ( pView )
          pView->GetParentFrame()->ActivateFrame();
      }
    }
  }
  else {
    CString sPath = GetFilePath(m_sDBIniFile);
    m_pRFindTemplate->OpenDocumentFile(sPath);
  }
}
\************************************** : by VK at 23.02.2005 23:17:28 **/

void CEragsApp::AddToRecentFileList(LPCTSTR lpszPathName) {
	// TODO: Add your specialized code here and/or call the base class
	CString sExt = CString(lpszPathName).Right(4);
  sExt.MakeLower();
  if ( sExt==_T(".er3"))
	  CWinApp::AddToRecentFileList(lpszPathName);
}

void CEragsApp::UpdateChildWindows(CWnd* pParent) {
  CWnd* pWnd = pParent->GetWindow(GW_CHILD);
  while( pWnd ) {
    pWnd->SendMessage(WM_SYSCOLORCHANGE);
    pWnd->InvalidateRect(NULL);
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
}
void CEragsApp::UpdateTopFrames() {
  WriteProfileInt(_T("Colors"), _T("WindowBackgroundLeft"),  g_clrLeft);
  WriteProfileInt(_T("Colors"), _T("WindowBackgroundRight"), g_clrRight);
  CreateBackgroundBitmap();

  DWORD pid = (DWORD)_getpid();
  CWnd* pWnd = m_pMainWnd;
  while ( pWnd ) {
    DWORD dwProcessID;
    ::GetWindowThreadProcessId(pWnd->m_hWnd, &dwProcessID);
    if ( pid==dwProcessID/* && (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)) || pWnd->IsKindOf(RUNTIME_CLASS(CDialogBarBG)))  */) {
      pWnd->SendMessage(WM_SYSCOLORCHANGE);
      pWnd->InvalidateRect(NULL);
      UpdateChildWindows(pWnd);
    }
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
  ::InvalidateRect(NULL, NULL, TRUE);
}
LPCTSTR CEragsApp::GetHelpPostfix() {
  return m_fUkrHelp ? _T("u") : _T("r");
}
UINT CEragsApp::GetDefaultForm() {
  UINT uForm = GetProfileInt(_T("Common"), _T("DefaultForm"), 5);
  if ( uForm < 1 || uForm > 5)
    uForm = 5;
  return uForm;
}
void CEragsApp::SetDefaultForm(UINT uForm) {
  if ( uForm < 1 || uForm > 5)
    uForm = 5;
  WriteProfileInt(_T("Common"), _T("DefaultForm"), uForm);
}

UINT CEragsApp::GetOffice() {
  if ( m_fOfficeChanged ) {
    m_nOffice = GetProfileInt(_T("Settings"), _T("Office"), MS_OFFICE);
    m_fOfficeChanged = false;
  }
  return m_nOffice;
}

void CEragsApp::SetOffice(UINT nOffice) {
  m_fOfficeChanged = true;
  WriteProfileInt(_T("Settings"), _T("Office"), nOffice);
}

void CEragsApp::OnMessage(int MessageType, LPCTSTR lpszFormat, ...) {
  ASSERT(AfxIsValidString(lpszFormat));

  va_list argList;
  va_start(argList, lpszFormat);

  CString s;
  s.FormatV(lpszFormat, argList);


  if ( m_pMainWnd ) {
    m_pMainWnd->SendMessage(WM_EM_MESSAGE, (WPARAM)MessageType, (LPARAM)(LPCTSTR)s);
  }

  va_end(argList);
}
