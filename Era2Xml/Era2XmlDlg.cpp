// Era2XmlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Era2Xml.h"
#include "Era2XmlDlg.h"
#include "MyFileDialog.h"
#include "db.h"

#include "CnvBirth.h"
#include "CnvDeath.h"
#include "Globals.h"
#include "Helpers.h"
#include "FinishDlg.h"
#include "Registry.h"

#include "..\Common\FHelpers.h"

#include <direct.h>
#include <HTMLHelp.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_FILE_SELECT       2001
#define IDC_FOLDER_SELECT     2002
#define IDC_OUTFOLDER_SELECT  2003

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

CString GetSpecialFolder(int nFolderID) {
   // Allocate a pointer to an Item ID list
   LPITEMIDLIST pidl;

   // Get a pointer to an item ID list that
   // represents the path of a special folder
   HRESULT hr = SHGetSpecialFolderLocation(NULL, nFolderID, &pidl);

   // Convert the item ID list's binary
   // representation into a file system path
   char szPath[_MAX_PATH];
   BOOL f = SHGetPathFromIDList(pidl, szPath);

   // Allocate a pointer to an IMalloc interface
   LPMALLOC pMalloc;

   // Get the address of our task allocator's IMalloc interface
   hr = SHGetMalloc(&pMalloc);

   // Free the item ID list allocated by SHGetSpecialFolderLocation
   pMalloc->Free(pidl);

   // Free our task allocator
   pMalloc->Release();

   // Work with the special folder's path (contained in szPath)
   return CString(szPath);
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEra2XmlDlg dialog

CEra2XmlDlg::CEra2XmlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEra2XmlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEra2XmlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  m_fGeoCacheLoaded = false;
}

void CEra2XmlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEra2XmlDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_INFO, m_InfoText);
	DDX_Control(pDX, IDC_FILES, m_Files);
  DDX_Control(pDX, IDC_RAGS, m_Rags);
  DDX_Control(pDX, IDC_BOSS, m_Boss);
  DDX_Control(pDX, IDC_BOSS_POS, m_BossPosition);
  DDX_Control(pDX, IDC_BIRTH_SPEC, m_BirthSpecialist);
  DDX_Control(pDX, IDC_BIRTH_SPEC_POS, m_BirthSpecialistPos);
  DDX_Control(pDX, IDC_DEATH_SPEC, m_DeathSpecialist);
  DDX_Control(pDX, IDC_DEATH_SPEC_POS, m_DeathSpecialistPos);
  DDX_Control(pDX, IDC_BIRTH_FROM, m_BirthFrom);
  DDX_Control(pDX, IDC_BIRTH_TILL, m_BirthTill);
  DDX_Control(pDX, IDC_DEATH_FROM, m_DeathFrom);
  DDX_Control(pDX, IDC_DEATH_TILL, m_DeathTill);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEra2XmlDlg, CDialog)
	//{{AFX_MSG_MAP(CEra2XmlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_CONVERT, OnConvert)
	ON_BN_CLICKED(IDC_ADDFILE, OnAddFile)
	ON_BN_CLICKED(IDC_DELFILE, OnDelFile)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FILES, OnItemchangedFiles)
	ON_BN_CLICKED(IDC_BIRTH_FROM_CHECK, OnBirthFromCheck)
	ON_BN_CLICKED(IDC_DEATH_FROM_CHECK, OnDeathFromCheck)
  ON_COMMAND(ID_HELP, OnHelp)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTNHELP, OnHelp)
	ON_EN_SETFOCUS(IDC_DEATH_FROM, OnSetfocusDeathFrom)
  ON_EN_SETFOCUS(IDC_DEATH_TILL, OnSetfocusDeathTill)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEra2XmlDlg message handlers

BOOL CEra2XmlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
  CRect r;
/*
  GetDlgItem(IDC_FILE_SELECT_FRAME)->GetWindowRect(&r);
  ScreenToClient(&r);
  m_FileEdit.MoveWindow(&r);


  GetDlgItem(IDC_FOLDER_SELECT_FRAME)->GetWindowRect(&r);
  ScreenToClient(&r);
  m_FolderEdit.MoveWindow(&r);
*/

  GetDlgItem(IDC_OUTFOLDER_SELECT_FRAME)->GetWindowRect(&r);
  ScreenToClient(&r);
  m_OutFolder.MoveWindow(&r);


	CFont *pFont = GetFont();
	// m_FileEdit.SetFont(pFont, false);
  // m_FolderEdit.SetFont(pFont, false);
  m_OutFolder.SetFont(pFont, false);

  /*
  OPENFILENAME *ofn = m_FileEdit.GetOpenFileName();
	ofn->lpstrFilter = _T("Файли ПК ЕРАГС (*.er3)\0*.er3\0All Files (*.*)\0*.*\0");
	ofn->Flags |= OFN_ALLOWMULTISELECT;

  CEdit* pEdit = m_FileEdit.GetEditControl();
  pEdit->ModifyStyle(0, ES_READONLY);
  */

/*
	BROWSEINFO *bi = m_FolderEdit.GetBrowseInfo();
	bi->lpszTitle = _T("Оберіть файлову папку з файлами ПК ЕРАГС");
*/

  BROWSEINFO *bi = m_OutFolder.GetBrowseInfo();
  bi->lpszTitle = _T("Оберіть файлову папку для xml-файлів");


  m_Files.GetWindowRect(&r);
  m_Files.InsertColumn(0, _T("Файли для конвертування"), LVCFMT_LEFT, r.Width()-4);

  m_Files.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

  CheckDlgButton(IDC_BIRTH, BST_CHECKED);
  CheckDlgButton(IDC_DEATH, BST_CHECKED);

  CString s, szPFFolder;
  szPFFolder = GetSpecialFolder(0x0026/*CSIDL_PROGRAM_FILES*/);
  s.Format(_T("%s\\Era2Xml"),  szPFFolder.Left(2));
  m_OutFolder.SetWindowText(s);

  GetDlgItem(IDC_XMLRECORDS)->SetWindowText(_T("100"));


  m_Rags.SetWindowText(g_szRacsName);
  m_Boss.SetWindowText(g_szRacsDirectorName);
  m_BossPosition.SetWindowText(g_szRacsDirectorPos);

  m_BirthSpecialist.SetWindowText(g_szSpecialistNameForBirth);
  m_BirthSpecialistPos.SetWindowText(g_szSpecialistPosForBirth);
  m_DeathSpecialist.SetWindowText(g_szSpecialistNameForDeath);
  m_DeathSpecialistPos.SetWindowText(g_szSpecialistPosForDeath);

  CheckDlgButton(IDC_RAGS_EMPTY, g_fWriteRacsName ? BST_UNCHECKED : BST_CHECKED);
  CheckDlgButton(IDC_BOSS_EMPTY, g_fWriteRacsDirectorName ? BST_UNCHECKED : BST_CHECKED);
  CheckDlgButton(IDC_BOSS_POS_EMPTY, g_fWriteRacsDirectorPosition ? BST_UNCHECKED : BST_CHECKED);
  CheckDlgButton(IDC_BIRTH_SPEC_EMPTY, g_fWriteBirthSpecialistName ? BST_UNCHECKED : BST_CHECKED);
  CheckDlgButton(IDC_BIRTH_SPEC_POS_EMPTY, g_fWriteBirthSpecialistPosition ? BST_UNCHECKED : BST_CHECKED);
  CheckDlgButton(IDC_DEATH_SPEC_EMPTY, g_fWriteDeathSpecialistName ? BST_UNCHECKED : BST_CHECKED);
  CheckDlgButton(IDC_DEATH_SPEC_POS_EMPTY, g_fWriteDeathSpecialistPosition ? BST_UNCHECKED : BST_CHECKED);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEra2XmlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEra2XmlDlg::OnPaint() 
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
HCURSOR CEra2XmlDlg::OnQueryDragIcon() {
	return (HCURSOR) m_hIcon;
}

int CEra2XmlDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
  // m_FileEdit.CreateEx(WS_EX_CLIENTEDGE, NULL,"",WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_TABSTOP|ES_AUTOHSCROLL, CRect (10,10,300,30),this, IDC_FILE_SELECT);
  // m_FolderEdit.CreateEx(WS_EX_CLIENTEDGE, NULL,"",WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_TABSTOP|ES_AUTOHSCROLL|FES_FOLDER, CRect (10,40,300,60),this, IDC_FOLDER_SELECT);
  m_OutFolder.CreateEx(WS_EX_CLIENTEDGE, NULL,"",WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_TABSTOP|ES_AUTOHSCROLL|FES_FOLDER, CRect (10,40,300,60),this, IDC_OUTFOLDER_SELECT);

  /*
  CEdit* pEdit = m_FileEdit.GetEditControl();
  pEdit->ModifyStyle(0, ES_READONLY);
  */
	
	return 0;
}

void CEra2XmlDlg::AddToFilelist(LPCTSTR szFilename) {
  LVFINDINFO fi;
  fi.flags = LVFI_STRING;
  fi.psz   = szFilename;

  int nItem = m_Files.FindItem(&fi);
  if ( nItem >= 0 ) {
    return;
  }
  GetDlgItem(IDC_CONVERT)->EnableWindow(true);
  nItem = m_Files.GetItemCount();
  m_Files.InsertItem(nItem, szFilename);
  PeekAndPump();
}

void CEra2XmlDlg::LoadGeoCache() {
  m_Progress.SetRange(0, 1000);
  m_Progress.ShowWindow(SW_SHOW);
  
  LoadCaches(&m_Progress, &m_InfoText);
  m_Progress.ShowWindow(SW_HIDE);
  m_InfoText.SetWindowText(_T(""));
}

/*
void CEra2XmlDlg::OnSearch(LPCTSTR szPath) {
  CString szMask, szText;
  szMask.Format(_T("%s\\*.*"), szPath);
  szMask.Replace(_T("\\\\"), _T("\\"));

  szText.Format(_T("Сканується папка \"%s\""), szPath);
  m_InfoText.SetWindowText(szText);

  CFileFind finder;
  BOOL fSearch = finder.FindFile(szMask);
  while (fSearch) {
    PeekAndPump();
    fSearch = finder.FindNextFile();
    if (finder.IsDots()) {
      continue;
    }
    CString szFilename = finder.GetFilePath();
    if (finder.IsDirectory()) {
      OnSearch(szFilename);
    }
    else {
      if ( szFilename.Right(4).CompareNoCase(_T(".er3"))==0 ) {
        AddToFilelist(szFilename);
      }
    }
  }

}

void CEra2XmlDlg::OnSearch() {
	// TODO: Add your control notification handler code here
  TCHAR szDrives[MAX_PATH];
  DWORD dwLength = GetLogicalDriveStrings(sizeof(szDrives), szDrives);
  if ( 0==dwLength ) {
    return;
  }
  TCHAR* p = szDrives;
  CStringArray aFixedDrives;
  while ( *p ) {
    if ( GetDriveType(p)==DRIVE_FIXED ) {
      aFixedDrives.Add(p);
    }
    p += strlen(p)+1;
  }
  int nDrives = aFixedDrives.GetSize();
  CWaitCursor wc;
  for( int i(0); i < nDrives; i++ ) {
    OnSearch( aFixedDrives.GetAt(i) );
  }
  m_InfoText.SetWindowText(_T(""));
}
*/


bool OpenDB(CDaoDatabase& db, LPCTSTR szFileName) {
  bool fRet = true;
  try {
    db.Open(szFileName, FALSE, TRUE);
  }
  catch(CDaoException* e) {
    e->Delete();
    fRet = false;
  }
  return fRet;
}

void CEra2XmlDlg::OnConvert() {


  BOOL fBirth = IsDlgButtonChecked(IDC_BIRTH);
  BOOL fDeath = IsDlgButtonChecked(IDC_DEATH);

  if ( false==fBirth && false==fDeath ) {
    return;
  }

  BOOL fBirthPeriod = IsDlgButtonChecked(IDC_BIRTH_FROM_CHECK);
  BOOL fDeathPeriod = IsDlgButtonChecked(IDC_DEATH_FROM_CHECK);

  COleDateTime odtBirthFrom, odtBirthTill, odtDeathFrom, odtDeathTill;

/*
  m_BirthFrom.GetTime(odtBirthFrom);
  m_BirthTill.GetTime(odtBirthTill);
  m_DeathFrom.GetTime(odtDeathFrom);
  m_DeathTill.GetTime(odtDeathTill);
*/
  odtBirthFrom = m_BirthFrom.GetDate();
  odtBirthTill = m_BirthTill.GetDate();
  odtDeathFrom = m_DeathFrom.GetDate();
  odtDeathTill = m_DeathTill.GetDate();

  if ( fBirthPeriod ) {
    if ( odtBirthFrom.GetStatus() != COleDateTime::valid || odtBirthTill.GetStatus() != COleDateTime::valid ) {
      AfxMessageBox(_T("Неправильний період для даних про народження."), MB_OK);
      return;
    }
    else if ( odtBirthFrom >= odtBirthTill ) {
      AfxMessageBox(_T("Неправильний період для даних про народження."), MB_OK);
      return;
    }
  }

  if ( fDeathPeriod ) {
    if ( odtDeathFrom.GetStatus() != COleDateTime::valid || odtDeathTill.GetStatus() != COleDateTime::valid ) {
      AfxMessageBox(_T("Неправильний період для даних про смерь."), MB_OK);
      return;
    }
    else if ( odtDeathFrom >= odtDeathTill ) {
      AfxMessageBox(_T("Неправильний період для даних про смерь."), MB_OK);
      return;
    }
  }


  if ( false==m_fGeoCacheLoaded ) {
    LoadGeoCache();
    m_fGeoCacheLoaded = true;
  }
  
  int nFiles = m_Files.GetItemCount();
  if ( nFiles < 1 ) {
    GetDlgItem(IDC_CONVERT)->EnableWindow(false);
    return;
  }


  CString szOutFolder;
  m_OutFolder.GetWindowText(szOutFolder);

  _mkdir(szOutFolder);

  if ( false==FileExists(szOutFolder) ) {
    return;
  }

  CString szMaxOutRecords;
  GetDlgItem(IDC_XMLRECORDS)->GetWindowText(szMaxOutRecords);

  long lMaxXmlRecords = atol(szMaxOutRecords);

  if ( lMaxXmlRecords < 1 ) {
    return;
  }

  long nRecords = 0;
  int i;

  CDaoDatabase db;
  // Считаем количество записей, которое нужно обработать
  for( i = 0; i < nFiles; i++ ) {
    CString szDatabase = m_Files.GetItemText(i, 0);
    if ( OpenDB(db, szDatabase) ) {
      if ( fBirth ) {
        nRecords += GetRecordCount(db, _T("BIRTHES"));
      }
      if ( fDeath ) {
        nRecords += GetRecordCount(db, _T("DEATHES"));
      }
      db.Close();
    }
  }

  // Включаем ProgressBar
  int nCurPos = 0;
  m_Progress.SetRange32(0, nRecords);
  m_Progress.ShowWindow(SW_SHOW);

  // Обработка (конвертирование таблиц в xml-файлы
  for( i = 0; i < nFiles; i++ ) {
    CString szDatabase = m_Files.GetItemText(i, 0);
    CString szFileMask = GetFileName(szDatabase);
    if ( OpenDB(db, szDatabase) ) {
      if ( fBirth ) {
        ConvertBirth(db, szOutFolder, szFileMask, lMaxXmlRecords,
                     fBirthPeriod, odtBirthFrom, odtBirthTill,
                     m_Progress, nCurPos
                    );
      }
      if ( fDeath ) {
        ConvertDeath(db, szOutFolder, szFileMask, lMaxXmlRecords,
                     fDeathPeriod, odtDeathFrom, odtDeathTill,
                     m_Progress, nCurPos
                    );
      }
      db.Close();
    }
  }

  // Выключаем ProgressBar
  m_Progress.ShowWindow(SW_HIDE);

  CFinishDlg dlg(szOutFolder, this);

  if ( dlg.DoModal()==IDOK ) {
    if ( dlg.m_fCloseApp ) {
      ShellExecute(NULL, _T("open"), szOutFolder, NULL, NULL, SW_SHOWNORMAL);
      PostMessage(WM_CLOSE);
    }
  }

}

BOOL CEra2XmlDlg::DestroyWindow() {
	// TODO: Add your specialized code here and/or call the base class
	theIniCache.Close();
  CloseHelperDB();
	return CDialog::DestroyWindow();
}

void CEra2XmlDlg::OnAddFile() 
{
	// TODO: Add your control notification handler code here
  CMyFileDialog ofd(TRUE, "*.er3", NULL, OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_LONGNAMES, _T("Файли БД ЕРАГС(*.er3)|*.er3|"), this);
  ofd.SetTitle(0, _T("Оберіть файл, який потрібно конвертувати"));
  if ( IDOK==ofd.DoModal() ) {
    AddToFilelist(ofd.GetPathName());
  }
}

void CEra2XmlDlg::OnDelFile() {
	// TODO: Add your control notification handler code here
	POSITION pos = m_Files.GetFirstSelectedItemPosition();
  while ( pos ) {
    int nItem = m_Files.GetNextSelectedItem(pos);
    if ( nItem >= 0 ) {
      m_Files.DeleteItem(nItem);
    }
  }

  if ( m_Files.GetItemCount()==0 ) {
    GetDlgItem(IDC_CONVERT)->EnableWindow(false);
  }

}

void CEra2XmlDlg::OnItemchangedFiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  if ( pNMListView->iItem >=0 && (pNMListView->uNewState & LVIS_SELECTED) ) {
    GetDlgItem(IDC_DELFILE)->EnableWindow(true);
  }
  else {
    GetDlgItem(IDC_DELFILE)->EnableWindow(false);
  }
	*pResult = 0;
}

LPCTSTR CEra2XmlDlg::GetHelpPostfix() {
  CRegistry r(_T("Erags"));
  UINT fUkrHelp = r.GetProfileInt(_T("Settings"), _T("UkrHelp"), true);
  return fUkrHelp ? _T("u") : _T("r");
}

void CEra2XmlDlg::OnBirthFromCheck() {
	// TODO: Add your control notification handler code here
  BOOL fCheck = IsDlgButtonChecked(IDC_BIRTH_FROM_CHECK);
  m_BirthFrom.EnableWindow( fCheck );
  m_BirthTill.EnableWindow( fCheck );
}

void CEra2XmlDlg::OnDeathFromCheck() {
	// TODO: Add your control notification handler code here
  BOOL fCheck = IsDlgButtonChecked(IDC_DEATH_FROM_CHECK);
  m_DeathFrom.EnableWindow( fCheck );
  m_DeathTill.EnableWindow( fCheck );
}

void CEra2XmlDlg::OnSetfocusDeathFrom() {
	// TODO: Add your control notification handler code here
  if ( m_DeathFrom.GetText().IsEmpty() ) {
    COleDateTime odt = m_BirthFrom.GetDate();
    if ( odt.GetStatus()==COleDateTime::valid ) {
      m_DeathFrom.SetDate( odt );
    }
  }
}

void CEra2XmlDlg::OnSetfocusDeathTill() {
	// TODO: Add your control notification handler code here
  if ( m_DeathTill.GetText().IsEmpty() ) {
    COleDateTime odt = m_BirthTill.GetDate();
    if ( odt.GetStatus()==COleDateTime::valid ) {
      m_DeathTill.SetDate( odt );
    }
  }
}

void CEra2XmlDlg::OnHelp() {
  typedef HWND (WINAPI *FPHH) (HWND,LPCSTR,UINT,DWORD);
  FPHH htmlHelp;
  if ( NULL==g_hHHCTRLInstance ) {
    g_hHHCTRLInstance = LoadLibrary("HHCTRL.OCX");
  }
  if ( g_hHHCTRLInstance ) {
    (FARPROC&) htmlHelp = GetProcAddress(g_hHHCTRLInstance,"HtmlHelpA");
    if ( htmlHelp ) {
      CString szHelpDirectory, szHelpPostfix;
      szHelpDirectory.Format(_T("%s\\Help"), GetModulePath());

      szHelpPostfix = GetHelpPostfix();

      CString szFileName;
      szFileName.Format(_T("%s\\Erags_%s.chm::/Era2Xml_%s.htm"), szHelpDirectory, szHelpPostfix, szHelpPostfix);
      HWND hHelpWnd = htmlHelp(GetDesktopWindow()->m_hWnd,szFileName, HH_DISPLAY_TOPIC, NULL);
      if ( hHelpWnd ) {
        ::ShowWindow(hHelpWnd, SW_MAXIMIZE);
      }
    }
  }
}

void CEra2XmlDlg::OnClose() {
	// TODO: Add your message handler code here and/or call default
  m_Rags.GetWindowText(g_szRacsName);
  theIniCache.SetRacsName(g_szRacsName);
  theIniCache.SetWriteRacsName( IsDlgButtonChecked(IDC_RAGS_EMPTY)==0 );
  
  m_Boss.GetWindowText(g_szRacsDirectorName);
  theIniCache.SetRacsDirectorName(g_szRacsDirectorName);
  theIniCache.SetWriteRacsDirectorName( IsDlgButtonChecked(IDC_BOSS_EMPTY)==0 );

  m_BossPosition.GetWindowText(g_szRacsDirectorPos);
  theIniCache.SetRacsDirectorPosition(g_szRacsDirectorPos);
  theIniCache.SetWriteRacsDirectorPosition( IsDlgButtonChecked(IDC_BOSS_POS_EMPTY)==0 );

  m_BirthSpecialist.GetWindowText(g_szSpecialistNameForBirth);
  theIniCache.SetSpecialistNameForBirth(g_szSpecialistNameForBirth);
  theIniCache.SetWriteBirthSpecialistName( IsDlgButtonChecked(IDC_BIRTH_SPEC_EMPTY)==0 );

  m_BirthSpecialistPos.GetWindowText(g_szSpecialistPosForBirth);
  theIniCache.SetSpecialistPosForBirth(g_szSpecialistPosForBirth);
  theIniCache.SetWriteBirthSpecialistPosition( IsDlgButtonChecked(IDC_BIRTH_SPEC_POS_EMPTY)==0 );

  m_DeathSpecialist.GetWindowText(g_szSpecialistNameForDeath);
  theIniCache.SetSpecialistNameForDeath(g_szSpecialistNameForDeath);
  theIniCache.SetWriteDeathSpecialistName( IsDlgButtonChecked(IDC_DEATH_SPEC_EMPTY)==0 );

  m_DeathSpecialistPos.GetWindowText(g_szSpecialistPosForDeath);
  theIniCache.SetSpecialistPosForDeath(g_szSpecialistPosForDeath);
  theIniCache.SetWriteDeathSpecialistPosition( IsDlgButtonChecked(IDC_DEATH_SPEC_POS_EMPTY)==0 );

  CDialog::OnClose();
}

