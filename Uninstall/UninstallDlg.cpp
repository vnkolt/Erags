// UninstallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Uninstall.h"
#include "UninstallDlg.h"
#include "RegReader.h"

#include <direct.h>
#include <shlobj.h>
#include <Shlwapi.h>
#include <process.h>


#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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


// GetLinkInfo() fills the filename and path buffer with relevant information.
// 
// lpszLinkName - name of the link file passed into the function.
// 
// lpszPath     - the buffer that receives the file's path name.
// 
HRESULT GetLinkInfo(LPCTSTR lpszLinkName, LPSTR lpszPath) {
  HRESULT hres;
  IShellLink *pShLink;
  WIN32_FIND_DATA wfd;

  // Initialize the return parameters to null strings.
  *lpszPath = '\0';

  // Call CoCreateInstance to obtain the IShellLink
  // Interface pointer. This call fails if
  // CoInitialize is not called, so it is assumed that
  // CoInitialize has been called.
  hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *)&pShLink);

  if (SUCCEEDED(hres)) {
    IPersistFile *ppf;
    // The IShellLink Interface supports the IPersistFile
    // interface. Get an interface pointer to it.
    hres = pShLink->QueryInterface(IID_IPersistFile, (LPVOID *)&ppf);
    if (SUCCEEDED(hres)) {
      WORD wsz[MAX_PATH];
      // Convert the given link name string to a wide character string.
      MultiByteToWideChar(CP_ACP, 0, (LPCSTR)lpszLinkName, -1, (LPWSTR)wsz, MAX_PATH);
      // Load the file.
      hres = ppf->Load((LPCOLESTR)wsz, STGM_READ);
      if (SUCCEEDED(hres)) {
        // Get the path of the file the link points to.
        hres = pShLink->GetPath(lpszPath, MAX_PATH, &wfd, SLGP_SHORTPATH );
        // Only get the description if we successfully got the path
        // (We can't return immediately because we need to release ppf & pShLink.)
      }
      ppf->Release();
    }
    pShLink->Release();
  }
  return hres;
}

void DeleteFolders(LPCTSTR szPath/*, CStringArray& saFolders*/) {
  CString szMask;
  szMask.Format(_T("%s\\*.*"), szPath);
  CFileFind finder;
  BOOL fSearch = finder.FindFile(szMask);
  while (fSearch) {
    fSearch = finder.FindNextFile();
    if (finder.IsDots())
      continue;
    // szFile = finder.GetFileName();
    if (finder.IsDirectory()) {
      _rmdir(finder.GetFilePath());
      // saFolders.Add(finder.GetFilePath());
    }
  }
}

void FindForLink(LPCTSTR szPath, LPCTSTR szEraPath, LPCTSTR szName, CStringArray& szFound) {
  CString szMask, szFile, sEraPath(szEraPath);
  size_t nPathLen = strlen(szEraPath);
  szMask.Format(_T("%s\\*.*"), szPath);

  sEraPath.MakeUpper();

  CFileFind finder;
  BOOL fSearch = finder.FindFile(szMask);
  while (fSearch) {
    fSearch = finder.FindNextFile();
    if (finder.IsDots())
      continue;
    szFile = finder.GetFilePath();
    if (finder.IsDirectory()) {
      FindForLink(szFile, szEraPath, szName, szFound);
    }
    else if ( szFile.Right(3).CompareNoCase("lnk")==0 ) {
      CString szShortName, szExeFile;
      GetLinkInfo(szFile, szShortName.GetBuffer(MAX_PATH));
      szShortName.ReleaseBuffer();
      GetLongPathName(szShortName, szExeFile.GetBuffer(MAX_PATH+1), MAX_PATH);
      szExeFile.ReleaseBuffer();
      szExeFile.MakeUpper();
      if ( szExeFile.Find(sEraPath)==0 ) {
        szFound.Add(szFile);
      }
    }
  }
}

int CountFiles(LPCTSTR szPath) {
  int nCount = 0;
  CString szMask, szFile;
  szMask.Format(_T("%s\\*.*"), szPath);
  CFileFind finder;
  BOOL fSearch = finder.FindFile(szMask);
  while (fSearch) {
    fSearch = finder.FindNextFile();
    if (finder.IsDots())
      continue;
    szFile = finder.GetFilePath();
    if (finder.IsDirectory()) {
      nCount += CountFiles(GetFilePath(szFile));
    }
    else {
      nCount++;
    }
  }
  return nCount;
}

/////////////////////////////////////////////////////////////////////////////
// CUninstallDlg dialog

CUninstallDlg::CUninstallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUninstallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUninstallDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUninstallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUninstallDlg)
  DDX_Control(pDX, IDC_PROGRESS, m_Progress);
#ifdef _DEBUG
	DDX_Control(pDX, IDC_FILES, m_Files);
#endif
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUninstallDlg, CDialog)
	//{{AFX_MSG_MAP(CUninstallDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	// ON_NOTIFY(NM_CLICK, IDC_TREE, OnClickTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
void CUninstallDlg::FillTree(HTREEITEM hParent, LPCTSTR szPath, BOOL fCheck) {
  CString szMask, szFile;
  szMask.Format(_T("%s\\*.*"), szPath);

  CFileFind finder;

  BOOL fSearch = finder.FindFile(szMask);
  while (fSearch) {
    fSearch = finder.FindNextFile();

    if (finder.IsDots())
      continue;

    szFile = finder.GetFileName();

    HTREEITEM hItem = m_Tree.InsertItem(szFile, 0, 0, hParent);
    m_Tree.SetCheck(hItem, fCheck);
    if (finder.IsDirectory()) {
      BOOL fNewCheck = fCheck;
      CString szDir = finder.GetFilePath();
      if ( szFile.CompareNoCase(_T("DB"))==0 ) {
        fNewCheck = false;
        m_Tree.SetCheck(hItem, fNewCheck);
      }
      FillTree(hItem, szDir, fNewCheck);
    }
  }
}

void CUninstallDlg::CheckChildren(HTREEITEM hParent, BOOL fCheck) {
  HTREEITEM hItem = m_Tree.GetNextItem(hParent, TVGN_CHILD);
  while ( hItem ) {
    m_Tree.SetCheck(hItem, fCheck);
    if ( m_Tree.GetChildItem(hItem) ) {
      CheckChildren(hItem, fCheck);
    }
#ifdef _DEBUG
    CString s = m_Tree.GetItemText(hItem);
#endif
    hItem = m_Tree.GetNextItem(hItem, TVGN_NEXT);
  }
}
*/

/////////////////////////////////////////////////////////////////////////////
// CUninstallDlg message handlers

BOOL CUninstallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	// ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	// ASSERT(IDM_ABOUTBOX < 0xF000);

/*
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
*/

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
  CheckDlgButton(IDC_PROGRAMS   , BST_CHECKED);
  CheckDlgButton(IDC_TEMPLATES  , BST_CHECKED);
  CheckDlgButton(IDC_DATABASE   , BST_UNCHECKED);
  CheckDlgButton(IDC_LINKS      , BST_CHECKED);
  CheckDlgButton(IDC_REGISTRY   , BST_CHECKED);

/*
  m_Tree.ModifyStyle( TVS_CHECKBOXES, 0 );
  m_Tree.ModifyStyle( 0, TVS_CHECKBOXES );
  
  
  m_hRootFiles = m_Tree.InsertItem(_T("‘‡ÈÎË œ  ≈–¿√—"), 0, 0);
  m_hRootLinks = m_Tree.InsertItem(_T("ﬂÎËÍË Ó·Ó˜Ó„Ó ÒÚÓÎÛ"), 0, 0);
  m_hRootReg   = m_Tree.InsertItem(_T("«‡ÔËÒË Û ÒËÒÚÂÏÌÓÏÛ Â∫ÒÚ≥"), 0, 0);

  HTREEITEM hRoot = m_Tree.InsertItem(szEraPath, 0, 0, m_hRootFiles);

  m_Tree.SetCheck(m_hRootFiles, true);
  m_Tree.SetCheck(hRoot, true);
  m_Tree.SetCheck(m_hRootLinks, true);
  m_Tree.SetCheck(m_hRootReg, true);

  FillTree(hRoot, szEraPath, true);

  m_Tree.Expand(m_hRootFiles, TVE_EXPAND);
  m_Tree.Expand(hRoot       , TVE_EXPAND);
*/

  int nFound;
  CString szDocs, szDesktop;
  nFound = SHGetSpecialFolderPath(NULL, szDocs.GetBuffer(MAX_PATH+1), CSIDL_COMMON_DESKTOPDIRECTORY, false);
  szDocs.ReleaseBuffer();
  /*
  if ( nFound ) {
    nFound = szDocs.Find(':');
    if ( nFound >= 0 ) {
      nFound = szDocs.Find('\\', nFound+2);
      if ( nFound >= 0 ) {
        szDocs = szDocs.Left(nFound);
        CStringArray szFound;
        FindForLink(szDocs, _T("œ  ≈–¿√—"), szFound);
      }
    }
  }
  else {
    SHGetSpecialFolderPath(NULL, szDesktop.GetBuffer(MAX_PATH+1), CSIDL_DESKTOP, FALSE);
    szDesktop.ReleaseBuffer();
    FindForLink(szDocs, _T("œ  ≈–¿√—"), szFound);
  }
  */

#ifdef _DEBUG
  m_Files.ShowWindow(SW_SHOW);
  m_Files.InsertColumn(0, _T("‘‡ÈÎ"), LVCFMT_LEFT, 240);

  g_szERAPath = _T("E:\\Erags");
#endif

  CString szEraPath = g_szERAPath;
  SHGetSpecialFolderPath(NULL, szDesktop.GetBuffer(MAX_PATH+1), CSIDL_DESKTOP, FALSE);
  szDesktop.ReleaseBuffer();
  FindForLink(szDesktop, szEraPath, _T("œ  ≈–¿√—"), m_aLinks);

  int nFiles = m_aLinks.GetSize();
  CString s;
  for( int i = 0; i < nFiles; i++ ) {
    s = m_aLinks[i];
#ifdef _DEBUG
    m_Files.InsertItem(i, s);
#endif
  }

  GetDlgItem(IDC_TEXT)->SetWindowText(_T("¬Ë ·‡Ê‡∫ÚÂ ‚Ë‰‡ÎËÚË œ  ≈–¿√— Á ¬‡¯Ó„Ó ÍÓÏÔ'˛ÚÂ‡?"));
  
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUninstallDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
/*
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
*/
  CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUninstallDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUninstallDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
void CUninstallDlg::OnClickTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
  UINT uFlags=0;
  CPoint point = GetCurrentMessage()->pt;
  m_Tree.ScreenToClient(&point);
  HTREEITEM hItem = m_Tree.HitTest(point, &uFlags);	

  if (hItem!=NULL) {
    m_Tree.SelectItem(hItem);
    if(uFlags&TVHT_ONITEMSTATEICON) {
       BOOL fCheck = !m_Tree.GetCheck(hItem);
       CheckChildren(hItem, fCheck);
    }
  }
	*pResult = 0;
}
*/

void CUninstallDlg::FillArray(CStringArray& sa, const CString& szPath, LPCTSTR szFileMask, BOOL fFindInSubfolders) {
  CString szMask, szFile;
  szMask.Format(_T("%s\\%s"), szPath, szFileMask);
  CFileFind finder;
  BOOL fSearch = finder.FindFile(szMask);
  while (fSearch) {
    fSearch = finder.FindNextFile();
    if (finder.IsDots())
      continue;
    szFile = finder.GetFileName();
    if ( false==finder.IsDirectory()) {
      sa.Add( finder.GetFilePath() );
    }
    else if ( fFindInSubfolders ) {
      CString szDir = finder.GetFilePath();
      FillArray(sa, szDir, szFileMask, fFindInSubfolders);
    }
  }
}

void CUninstallDlg::OnOK() {
	// TODO: Add extra validation here
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
  GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

  CRegReader rr;

  CString szEraPath = rr.GetInstallLocation();

  if ( false==FileExists(szEraPath) ) {
    szEraPath = GetModulePath();
  }

  if ( false==FileExists(szEraPath) ) {
    CDialog::OnOK();
    return;
  }

  CStringArray sa;
  CString szPath;

  BOOL fPrograms  = IsDlgButtonChecked(IDC_PROGRAMS );
  BOOL fTemplates = IsDlgButtonChecked(IDC_TEMPLATES);
  BOOL fDatabases = IsDlgButtonChecked(IDC_DATABASE );
  BOOL fLinks     = IsDlgButtonChecked(IDC_LINKS    );

  BOOL fRegistry  = IsDlgButtonChecked(IDC_REGISTRY );

  szPath.Format(_T("%s\\Out"), szEraPath);
  FillArray(sa, szPath, _T("*.*"), true);

  if ( fPrograms ) {
    szPath = szEraPath;
    FillArray(sa, szPath, _T("*.*"), false);
    szPath.Format(_T("%s\\Help"), szEraPath);
    FillArray(sa, szPath, _T("*.*"), true);
    szPath.Format(_T("%s\\Downloads"), szEraPath);
    FillArray(sa, szPath, _T("*.*"), true);
  }
  if ( fTemplates ) {
    szPath.Format(_T("%s\\Templates"), szEraPath);
    FillArray(sa, szPath, _T("*.*"), true);
    szPath.Format(_T("%s\\Templates.sav"), szEraPath);
    FillArray(sa, szPath, _T("*.*"), true);
  }
  if ( fDatabases ) {
    szPath.Format(_T("%s\\DB"), szEraPath);
    FillArray(sa, szPath, _T("*.*"), true);
  }
  if ( fLinks ) {
    szPath.Format(_T("%s\\œ  ≈–¿√—"), szEraPath);
    FillArray(sa, szPath, _T("*.*"), true);
    sa.Append(m_aLinks);
  }
  if ( fRegistry ) {
    // HKEY_LOCAL_MACHINE\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Erags
    SHDeleteKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Erags"));
    // HKEY_LOCAL_MACHINE\SOFTWARE\Vladimir Koltsov\Erags
    //lResult = ::RegOpenKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Vladimir Koltsov\\Erags"), &hKey);
    SHDeleteKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Vladimir Koltsov\\Erags"));
    // HKEY_CURRENT_USER\Software\Vladimir Koltsov\Downloader
    SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Vladimir Koltsov\\Downloader"));
    // HKEY_CURRENT_USER\Software\Vladimir Koltsov\EraABC
    SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Vladimir Koltsov\\EraABC"));
    // HKEY_CURRENT_USER\Software\Vladimir Koltsov\Erags
    SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Vladimir Koltsov\\Erags"));
    // HKEY_CURRENT_USER\Software\Vladimir Koltsov\Updater
    SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Vladimir Koltsov\\Updater"));
  }
  int nFiles = sa.GetSize();
  int i;
#ifdef _DEBUG
  for( i=0; i < nFiles; i++ ) {
    m_Files.InsertItem(i, sa[i]);
  }
#endif

  m_Progress.ShowWindow(SW_SHOW);
  m_Progress.SetRange32(0, nFiles);
  for( i=0; i < nFiles; i++ ) {
    try {
      PeekAndPump();
    }
    catch(...) {
      ; // AfxMessageBox(_T("PeekAndPump()"));
    }
    if ( FileExists(sa[i]) ) {
      if ( false==DeleteFile(sa[i]) ) {
        DWORD dwError = GetLastError();
      }
    }
    try {
      m_Progress.SetPos(i);
    }
    catch(...) {
      ; //AfxMessageBox(_T("m_Progress.SetPos(i)"));
    }
  }
  // CStringArray saFolders;
  DeleteFolders(szEraPath);

  if ( fPrograms ) {
    CString szDelete, szDeleteBody, szTempPath;
    CString szExename = GetModuleFileName();
    // int nCounFiles = CountFiles(szEraPath);
    char buf[MAX_PATH];
    GetTempPath(sizeof(buf), buf);

    szDelete.Format(_T("%sDeleteRags.bat"), buf);
    szTempPath = buf;

    szDeleteBody.Format(_T("@echo off\r\n")
                        _T("cd \"%s\" >nul\r\n")
                        _T(":Repeat\r\n")
                        _T("del \"%s\" >nul\r\n")
                        _T("if exist \"%s\" goto Repeat\r\n")
                        _T("rmdir \"%s\" >nul\r\n")
                        _T("del %%0 >nul\r\n"),
                        szTempPath, szExename, szExename, szEraPath
                       );
    HANDLE hDel = CreateFile(szDelete, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
    if ( hDel != INVALID_HANDLE_VALUE ) {
      DWORD dwWritten = 0;
      WriteFile(hDel, (LPCTSTR)szDeleteBody, szDeleteBody.GetLength(), &dwWritten, NULL);
      CloseHandle(hDel);

      PROCESS_INFORMATION pi;
      STARTUPINFO         si;

      si.cb              = sizeof(STARTUPINFO);
      si.lpReserved      = NULL;
      si.lpReserved2     = NULL;
      si.cbReserved2     = 0;
      si.lpDesktop       = NULL;
      si.lpTitle         = NULL;
      si.dwFlags         = 0;
      si.dwX             = 0;
      si.dwY             = 0;
      si.dwFillAttribute = 0;
      si.wShowWindow     = SW_HIDE;
      CreateProcess(NULL, (LPTSTR)(LPCTSTR)szDelete, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
//      WinExec(szDelete, SW_HIDE);
    }


/*
    HKEY hKey;
    long lResult = ::RegOpenKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"), &hKey);
    if ( ERROR_SUCCESS!=lResult ) {
      lResult = ::RegOpenKey(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"), &hKey);
    }
    if ( ERROR_SUCCESS==lResult ) {
      szDelete.Format(_T("cmd /C del /F \"%s\\Uninstall.exe\""), szEraPath);
      ::RegSetValueEx(hKey, _T("DeleteEragsUninstall"), 0, REG_EXPAND_SZ, (LPBYTE)(LPCTSTR)szDelete, szDelete.GetLength()+1);
      if ( 1==nCounFiles )  {
        szDelete.Format(_T("cmd /C rmdir /s \"%s\""), szEraPath);
        ::RegSetValueEx(hKey, _T("DeleteEragsFolder"), 0, REG_EXPAND_SZ, (LPBYTE)(LPCTSTR)szDelete, szDelete.GetLength()+1);
      }
      ::RegCloseKey(hKey);
    }
*/
  }

//#ifdef _DEBUG
//  return;
//#endif
  // ExitThread(0);
  // TerminateProcess((HANDLE)_getpid(), 0);


	CDialog::OnOK();
}
