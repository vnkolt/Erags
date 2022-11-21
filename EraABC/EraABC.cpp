// EraABC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "EraABC.h"

#include "MainFrm.h"
#include "EraABCDoc.h"
#include "TabView.h"

//#include "Utils.h"

#include "..\Controls\MyFileDialog.h"
#include "..\Common\DAO36.h"
#include "..\Common\EraMessages.h"
#include "..\Common\FHelpers.h"
#include "..\Common\Version.h"

#include <HTMLHelp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CreateBackgroundBitmap();


COLORREF g_clrBackColor = 0xC0C0C0;
COLORREF g_clrForeColor = 0x000000;
COLORREF g_clrFocusBackColor = 0xFFFFFF;
COLORREF g_clrFocusForeColor = 0x000000;

COLORREF g_clrMaleBackColor = 0x808080;
COLORREF g_clrFemaleBackColor = 0x808080;
COLORREF g_clrMaleForeColor = RGB(0x00, 0x00, 0xFF);
COLORREF g_clrFemaleForeColor = RGB(0xFF, 0x00, 0x00);

HBRUSH g_hEditBrush, g_hFocusEditBrush;

UINT res_IDB_HDRUP     = IDB_HDRUP;
UINT res_IDB_HDRDOWN   = IDB_HDRDOWN;


short    g_SecurityLoaded[4]  = { FALSE, FALSE, FALSE, FALSE};

/////////////////////////////////////////////////////////////////////////////
// CEraABCApp
BEGIN_MESSAGE_MAP(CEraABCApp, CWinApp)
  //{{AFX_MSG_MAP(CEraABCApp)
  ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
  ON_UPDATE_COMMAND_UI(ID_BIRTH, OnUpdateBirth)
  ON_COMMAND(ID_BIRTH, OnBirth)
  ON_UPDATE_COMMAND_UI(ID_MARRIAGE, OnUpdateMarriage)
  ON_COMMAND(ID_MARRIAGE, OnMarriage)
  ON_UPDATE_COMMAND_UI(ID_DIVORCE, OnUpdateDivorce)
  ON_COMMAND(ID_DIVORCE, OnDivorce)
  ON_UPDATE_COMMAND_UI(ID_CHANGE, OnUpdateChange)
  ON_COMMAND(ID_CHANGE, OnChange)
  ON_UPDATE_COMMAND_UI(ID_DEATH, OnUpdateDeath)
  ON_COMMAND(ID_DEATH, OnDeath)
  ON_COMMAND(ID_FILE_NEW, OnFileNew)
  ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
  ON_UPDATE_COMMAND_UI(ID_FILE_RECENT, OnUpdateFileRecent)
  ON_COMMAND(ID_FILE_RECENT, OnFileRecent)
  ON_UPDATE_COMMAND_UI(ID_HELPER, OnUpdateHelper)
  ON_COMMAND(ID_HELPER, OnHelper)
  ON_UPDATE_COMMAND_UI(ID_HELP_UKR, OnUpdateHelpUkr)
  ON_UPDATE_COMMAND_UI(ID_HELP_RUS, OnUpdateHelpRus)
  ON_COMMAND(ID_HELP_UKR, OnHelpLanguage)
  ON_COMMAND(ID_HELP_RUS, OnHelpLanguage)
  ON_COMMAND(ID_HELP, OnHelp)
  //}}AFX_MSG_MAP
  // Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraABCApp construction
CEraABCApp::CEraABCApp() {
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
  m_pDoc = NULL;
  m_fUkrHelp = m_fUseHelper = true;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEraABCApp object

CEraABCApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEraABCApp initialization

UINT CEraABCApp::GetDefaultForm() {
  UINT uForm = GetProfileInt(_T("Common"), _T("DefaultForm"), 5);
  if ( uForm < 1 || uForm > 5)
    uForm = 5;
  return uForm;
}
LPCTSTR CEraABCApp::GetHelpPostfix() {
  return m_fUkrHelp ? _T("u") : _T("r");
}
BOOL CEraABCApp::InitInstance()
{
  AfxEnableControlContainer();

  // Standard initialization
  // If you are not using these features and wish to reduce the size
  //  of your final executable, you should remove from the following
  //  the specific initialization routines you do not need.

#ifdef _AFXDLL
  Enable3dControls();      // Call this when using MFC in a shared DLL
#else
  Enable3dControlsStatic();  // Call this when linking to MFC statically
#endif


  try {
    AfxDaoInit36();
  }
  catch(...) {
    CString sMsg;
    sMsg.Format(_T("Увага! Комплекс ЕРАГС використовує компоненти DAO.\n")
               _T("Будь ласка, встановіть DAO, а потім запустіть ЕраАБВС знов.") );
    AfxMessageBox(sMsg);
    return FALSE;
  }


  // Change the registry key under which our settings are stored.
  // TODO: You should modify this string to be something appropriate
  // such as the name of your company or organization.
  SetRegistryKey(_T("Vladimir Koltsov"));

  LoadStdProfileSettings();  // Load standard INI file options (including MRU)

  m_strDBRoot = GetProfileString(_T("Settings"), _T("DBRoot"));
  if ( m_strDBRoot.IsEmpty() ) {
    m_strDBRoot.Format(_T("%s\\DB"), GetModulePath());
  }
  m_fUseHelper = GetProfileInt(_T("Settings"), _T("Helper"), true);
  m_fUkrHelp   = GetProfileInt(_T("Settings"), _T("UkrHelp"), true);

  g_fUseGradient = false;
  CreateBackgroundBitmap();
  CNewMenu::SetMenuDrawMode(CNewMenu::STYLE_MONOCHROME/*STYLE_XP_2003*/);
  CNewMenu::SetSelectDisableMode(0);  // Selection
  CNewMenu::SetXpBlending(0);         // Gloom
  CNewMenu::SetAcceleratorsDraw(1);   // AcceleratorsDraw
  //g_clrLeft  = RGB(224,224,224);//GetSysColor(COLOR_3DHILIGHT/*COLOR_MENU*/);

  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views.

  CSingleDocTemplate* pDocTemplate;
  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(CEraABCDoc),
    RUNTIME_CLASS(CMainFrame),       // main SDI frame window
    RUNTIME_CLASS(CTabView));
  AddDocTemplate(pDocTemplate);

  if (m_lpCmdLine[0] == '\0') {
    // create a new (empty) document
    CString sDatabase = GetProfileString(_T("Settings"), _T("Database"));
    if ( !sDatabase.IsEmpty() && FileExists(sDatabase) ) {
      OpenDocument( sDatabase, GetDefaultForm() );
    }
    else {
/************************************** : by VK 02.02.2005 at 15:34:32 **\
      CMainFrame* pMainFrame = new CMainFrame;
      if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
        return FALSE;
      m_pMainWnd = pMainFrame;
\************************************** : by VK 02.02.2005 at 15:34:37 **/
      CCommandLineInfo cmdInfo;
      ParseCommandLine(cmdInfo);
      // Dispatch commands specified on the command line
      if (!ProcessShellCommand(cmdInfo))
        return FALSE;
    }
  }
  else {
    // open an existing document
    if(!OpenDocumentFile(m_lpCmdLine))
      return FALSE;
  }

/************************************** : by VK at 28.01.2005 0:45:59 **\
  // Parse command line for standard shell commands, DDE, file open
  CCommandLineInfo cmdInfo;
  ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line
  if (!ProcessShellCommand(cmdInfo))
    return FALSE;
\************************************** : by VK at 28.01.2005 0:46:02 **/
  // The one and only window has been initialized, so show and update it.
  m_pMainWnd->ShowWindow(SW_SHOW);
  m_pMainWnd->UpdateWindow();

  //
  // To prevent Windows XP toolbar drawing bug
  //
  m_pMainWnd->InvalidateRect(NULL);

  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
  CAboutDlg();

// Dialog Data
  //{{AFX_DATA(CAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  //{{AFX_MSG(CAboutDlg)
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
  //{{AFX_MSG_MAP(CAboutDlg)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() {
  CDialog::OnInitDialog();
  
  // TODO: Add extra initialization here
  CString sVersion;
  sVersion.Format(_T("ЕрагсАБВ, версія %s"), extGetAppVersion() );
  GetDlgItem(IDC_ERABC_VERSION)->SetWindowText(sVersion);
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

// App command to run the dialog
void CEraABCApp::OnAppAbout()
{
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CEraABCApp message handlers
void CEraABCApp::OnForm(CMDIChildWnd* pFrame, UINT uForm) {
  if ( pFrame )
    pFrame->ActivateFrame();
  else
    OpenDocument(m_strYearDBName, uForm);
}
void CEraABCApp::OnUpdateBirth(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
}
void CEraABCApp::OnBirth() {
/************************************** : by VK at 26.01.2005 22:22:24 **\
  OnForm(CBirthFrame::m_pBirthFrame, 1);
\************************************** : by VK at 26.01.2005 22:22:26 **/
}
void CEraABCApp::OnUpdateMarriage(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
}
void CEraABCApp::OnMarriage() {
/************************************** : by VK at 26.01.2005 22:22:30 **\
  OnForm(CMarriageFrame::m_pMarriageFrame, 2);
\************************************** : by VK at 26.01.2005 22:22:32 **/
}
void CEraABCApp::OnUpdateDivorce(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
}
void CEraABCApp::OnDivorce() {
/************************************** : by VK at 26.01.2005 22:22:35 **\
  OnForm(CDivorceFrame::m_pDivorceFrame, 3);
\************************************** : by VK at 26.01.2005 22:22:38 **/
}
void CEraABCApp::OnUpdateChange(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
}
void CEraABCApp::OnChange() {
/************************************** : by VK at 26.01.2005 22:22:41 **\
  OnForm(CChangeFrame::m_pChangeFrame, 4);
\************************************** : by VK at 26.01.2005 22:22:44 **/
}
void CEraABCApp::OnUpdateDeath(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
}
void CEraABCApp::OnDeath() {
/************************************** : by VK at 26.01.2005 22:22:47 **\
  OnForm(CDeathFrame::m_pDeathFrame, 5);
\************************************** : by VK at 26.01.2005 22:22:50 **/
}

void CEraABCApp::OnFileNew() {
  CString sDBFile = GetFilePath(theApp.GetProfileString(_T("Settings"), _T("Database"), _T("")));
  if ( sDBFile.IsEmpty() ) {
    CString s;
    s.Format(_T("%s\\DB\\Helpers.mdb"), GetModulePath() );
    if ( FileExists(s) )
      sDBFile = GetFilePath(s);
  }
  CMyFileDialog ofd(TRUE, "*.er3", NULL, OFN_HIDEREADONLY|OFN_LONGNAMES, _T("Файли БД ЕРАГС(*.er3)|*.er3|"), AfxGetMainWnd());
  ofd.SetTitle(IDD_FILE_NEW, _T("Створити новий/Відкрити файл БД ЕРАГС"));
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
      sTemplateDB.Format(_T("%s\\Templates\\DBTemplate.mdb"), GetModulePath());
      CopyFile(sTemplateDB, sFileName, FALSE);
    }
    OpenDocumentFile(sFileName);
  }
}

void CEraABCApp::OnFileOpen() {
  // TODO: Add your command handler code here
  CString sDBFile = GetFilePath(theApp.GetProfileString(_T("Settings"), _T("Database"), _T("")));
  CMyFileDialog ofd(TRUE, "*.er3", NULL, OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_LONGNAMES, _T("Файли БД ЕРАГС(*.er3)|*.er3|"), AfxGetMainWnd());
  ofd.m_ofn.lpstrInitialDir = sDBFile;
  //ofd.m_ofn.lpstrTitle = _T("Відкрити файл бази даних");
  ofd.SetTitle(IDD_FILE_NEW, _T("Відкрити файл бази даних"));
  if ( ofd.DoModal()==IDOK ) {
    OpenDocumentFile(ofd.GetPathName());
  }
}

void CEraABCApp::OnUpdateFileRecent(CCmdUI* pCmdUI) {
  pCmdUI->Enable(TRUE);
}
void CEraABCApp::OnFileRecent() {
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

void CEraABCApp::OnUpdateHelper(CCmdUI* pCmdUI) {
  // TODO: Add your command update UI handler code here
  pCmdUI->SetCheck(m_fUseHelper);
}

void CEraABCApp::OnHelper() {
  m_fUseHelper = !m_fUseHelper;
  WriteProfileInt(_T("Settings"), _T("Helper"), m_fUseHelper);
}

void CEraABCApp::OnUpdateHelpUkr(CCmdUI* pCmdUI) {
  // TODO: Add your command update UI handler code here
  pCmdUI->Enable(TRUE);
  pCmdUI->SetCheck(m_fUkrHelp);
}

void CEraABCApp::OnUpdateHelpRus(CCmdUI* pCmdUI) {
  // TODO: Add your command update UI handler code here
  pCmdUI->Enable(TRUE);
  pCmdUI->SetCheck(!m_fUkrHelp);
}

void CEraABCApp::OnHelpLanguage() {
  m_fUkrHelp = m_fUkrHelp ? FALSE : TRUE;
  WriteProfileInt(_T("Settings"), _T("UkrHelp"), m_fUkrHelp);
/*
  CMDIChildWnd* pFrame = ((CMainFrame*)(AfxGetMainWnd()))-> MDIGetActive();
  if ( pFrame ) {
    CEraForm* pForm = (CEraForm*)pFrame->GetActiveView();
    if ( pForm->IsKindOf(RUNTIME_CLASS(CEraForm)) ) {
      pForm->SetTooltips();
    }
  }
*/
}

CDocument* CEraABCApp::OpenDocument(const CString& sDatabase, UINT uForm) {
  CDocument* pDoc = OpenDocumentFile(sDatabase);
  switch (uForm) {
    case 1:   // Birthes
      m_DocName = _T("Народження");
      break;
    case 2:   // Marriages
      m_DocName = _T("Шлюби");
      break;
    case 3:   // Divorces
      m_DocName = _T("Розірвання Шлюбів");
      break;
    case 4:   // Changes
      m_DocName = _T("Зміни");
      break;
    case 5:   // Deathes
    default:
      m_DocName = _T("Смерті");
      break;
  }
  return pDoc;
}

void CEraABCApp::OnMessage(int MessageType, LPCTSTR lpszFormat, ...) {
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

void CEraABCApp::OnHelp() {
  static HINSTANCE hHHCTRLInstance = NULL;
  typedef HWND (WINAPI *FPHH) (HWND,LPCSTR,UINT,DWORD);
  FPHH htmlHelp;
  if ( NULL==hHHCTRLInstance ) {
    hHHCTRLInstance = LoadLibrary("HHCTRL.OCX");
  }
  if ( hHHCTRLInstance ) {
    (FARPROC&) htmlHelp = GetProcAddress(hHHCTRLInstance,"HtmlHelpA");
    if ( htmlHelp ) {
      CString szHelpDirectory, szHelpPostfix;
      szHelpDirectory.Format(_T("%s\\Help"), GetModulePath());
      szHelpPostfix = theApp.GetHelpPostfix();

      CString szFileName;
      szFileName.Format(_T("%s\\Erags_%s.chm::/EraABC_%s.htm"), szHelpDirectory, szHelpPostfix, szHelpPostfix);
      HWND hHelpWnd = htmlHelp(::GetDesktopWindow(),szFileName,HH_DISPLAY_TOPIC,NULL);
      if ( hHelpWnd ) {
        ::ShowWindow(hHelpWnd, SW_MAXIMIZE);
      }
    }
  }
/************************************** : by VK at 20.01.2007 11:38:17 **\

  CString szShell;
  szShell.Format(_T("%s\\Help\\EraABC_%s.htm"), GetModulePath(), theApp.GetHelpPostfix());
  if ( FileExists(szShell) ) {
    ShellExecute(NULL, "open", szShell, NULL, NULL, SW_SHOW);
  }
  else {
    OnMessage(EM_ERROR, _T("Файл допомоги \"%s\" не існує."), szShell);
  }
\************************************** : by VK at 20.01.2007 11:38:25 **/
}