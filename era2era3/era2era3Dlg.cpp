// era2era3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "era2era3.h"
#include "era2era3Dlg.h"
#include "Registry.h"
#include "db.h"
#include "RepairDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RAGSDB_PATH_C _T("C:\\Rags\\DB")
#define RAGSDB_PATH_D _T("D:\\Rags\\DB")

BYTE JET_SIGNATURE[] = { 0x0, 0x01, 0x00, 0x00, 'S', 't', 'a', 'n', 'd', 'a', 'r', 'd', ' ', 'J', 'e', 't', ' ', 'D', 'B' };

CString   g_SourcePath;
CString   g_DestPath;

CString GetFilePath(LPCTSTR szFileName){
  CString sPath(szFileName);
  return sPath.Mid( 0, sPath.ReverseFind('\\') );
}

CString GetModulePath() {
  CString s;
  GetModuleFileName(NULL, s.GetBuffer(MAX_PATH), MAX_PATH);
  s.ReleaseBuffer();
  return GetFilePath(s);
}

CString ReplaceFileExt(LPCTSTR szPath, LPCTSTR szExt){
  CString sPath(szPath);
  int iDot;
  iDot = sPath.ReverseFind('.');
  if ( iDot > 0 ) {
    CString s;
    s  = sPath.Left(iDot+1) + szExt; 
    sPath = s;
  }
  return sPath;
}

CString Trim(LPCTSTR sz) {
  CString s = sz;
  s.TrimLeft();
  s.TrimRight();
  return s;
}

void FreeSexMap(SEXMap& map) {
  POSITION pos = map.GetStartPosition();
  while ( pos ) {
    CString sKey;
    CSexRecord* pRecord = NULL;
    map.GetNextAssoc(pos, sKey, pRecord);
    if ( pRecord )
      delete pRecord;
  }
  map.RemoveAll();
}

void Free2FieldMap(RECORDMap& map) {
  POSITION pos = map.GetStartPosition();
  while ( pos ) {
    CString sKey;
    C2FieldRecord* pRecord = NULL;
    map.GetNextAssoc(pos, sKey, pRecord);
    if ( pRecord )
      delete pRecord;
  }
  map.RemoveAll();
}

int CALLBACK BrowseCallbackProcOld(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData){
  TCHAR szDir[MAX_PATH];

  switch(uMsg) {
    case BFFM_INITIALIZED:{
      ::SetWindowText(hwnd, _T("Маршрут файлів старої БД"));
      CString s = g_SourcePath;
      if(!s.IsEmpty()){
        lstrcpy(szDir, s);
        // WParam is TRUE since you are passing a path.
        // It would be FALSE if you were passing a pidl.
        SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)szDir);
      }
      break;
    }
    case BFFM_SELCHANGED: {
      // Set the status window to the currently selected path.
      if (SHGetPathFromIDList((LPITEMIDLIST) lp ,szDir)) {
        SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);
      }
      break;
    }
    default:
      break;
  }
  return 0;
}

int CALLBACK BrowseCallbackProcNew(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData){
  TCHAR szDir[MAX_PATH];

  switch(uMsg) {
    case BFFM_INITIALIZED:{
      ::SetWindowText(hwnd, _T("Маршрут файлів нової БД"));
      CString s = g_DestPath;
      if(!s.IsEmpty()){
        lstrcpy(szDir, s);
        // WParam is TRUE since you are passing a path.
        // It would be FALSE if you were passing a pidl.
        SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)szDir);
      }
      break;
    }
    case BFFM_SELCHANGED: {
      // Set the status window to the currently selected path.
      if (SHGetPathFromIDList((LPITEMIDLIST) lp ,szDir)) {
        SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);
      }
      break;
    }
    default:
      break;
  }
  return 0;
}


bool JetFile(LPCTSTR szFileName) {
  FILE* f = fopen(szFileName, "r");
  if ( f ) {
    BYTE szSignature[sizeof(JET_SIGNATURE)];
    memset(szSignature, 0, sizeof(szSignature) );
    fread(szSignature, 1, sizeof(szSignature), f);
    fclose(f);
    if ( memcmp(szSignature, JET_SIGNATURE, sizeof(JET_SIGNATURE))==0 )
      return true;
    return true;
  }
  return false;
}

bool CheckTables(CDaoDatabase& db) {
  int nTables = db.GetTableDefCount();
  LPCTSTR szTables[4] = { _T("Акты_о_браке"), _T("Акты_о_разводе"), _T("Акты_о_рождении"), _T("Акты_о_смерти") };
  int nCount(0);
  for( int i(0); i < 4; i++ ) {
    CDaoTableDefInfo tabledefinfo;
    try {
      db.GetTableDefInfo(szTables[i], tabledefinfo);
      nCount++;
    }
    catch(CDaoException* e){
      e->Delete();
    }
  }

  return (nCount==4) ? true : false;
}

bool OpenOldDB(CDaoDatabase& db, LPCTSTR szFileName) {
  bool fRet = true;
  try {
    db.Open(szFileName, FALSE, TRUE);
  }
  catch(CDaoException* e) {
    e->Delete();
    fRet = false;
  }
  if (fRet==false ) {
    CString sPWD;
    sPWD.Format(_T(";PWD=%s"), _T("августдекабрь"));
    try {
      db.Open(szFileName, FALSE, TRUE, sPWD);
      db.Close();
    }
    catch(CDaoException* e) {
      e->Delete();
      fRet = false;
    }
  }
  return fRet;
}

bool EraFile(LPCTSTR szFileName) {
  bool fRet = true;
  CDaoDatabase db;
  try {
    db.Open(szFileName, FALSE, TRUE);
    fRet = CheckTables(db);
    db.Close();
  }
  catch(CDaoException* e) {
    e->Delete();
    fRet = false;
  }
  if ( false==fRet ) {
    CString sPWD;
    sPWD.Format(_T(";PWD=%s"), _T("августдекабрь"));
    try {
      db.Open(szFileName, FALSE, TRUE, sPWD);
      fRet = CheckTables(db);
      db.Close();
    }
    catch(CDaoException* e) {
      e->Delete();
      fRet = false;
    }
  }
  return fRet;
}

bool CheckDB(CStringArray& SourceFiles, LPCTSTR szPath) {
  int nCount = 0;
  CString sPath;
  sPath.Format(_T("%s\\*.*"), szPath);
  WIN32_FIND_DATA FindData;
  HANDLE hFind = FindFirstFile(sPath, &FindData);
  if ( hFind != INVALID_HANDLE_VALUE ) {
    BOOL bFound = TRUE;
    while ( bFound ) {
      nCount++;
      if ( FindData.cFileName[0] != '.' ) {
        if ( FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
          CString sNewPath;
          sNewPath.Format(_T("%s\\%s"), szPath, FindData.cFileName);
          CheckDB(SourceFiles, sNewPath);
        }
        else if ( FindData.dwFileAttributes & (FILE_ATTRIBUTE_NORMAL|FILE_ATTRIBUTE_ARCHIVE) ) {
          CString sFileName;
          sFileName.Format(_T("%s\\%s"), szPath, FindData.cFileName);
          if ( JetFile(sFileName) && EraFile(sFileName) )
            SourceFiles.Add(sFileName);
        }
      }
      bFound = FindNextFile(hFind, &FindData);
    }
    FindClose(hFind);
  }
  return nCount ? true : false;
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
// CEra2era3Dlg dialog

CEra2era3Dlg::CEra2era3Dlg(CWnd* pParent /*=NULL*/)
             :CDialog(CEra2era3Dlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CEra2era3Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  m_TotalRecs = m_FilePos = m_TotalPos = 0;
}

void CEra2era3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEra2era3Dlg)
	DDX_Control(pDX, IDC_PROGRESS_TOTAL, m_ProgressTotal);
	DDX_Control(pDX, IDC_PROGRESS_FILE, m_ProgressFile);
	DDX_Control(pDX, IDC_OLDFILELIST, m_oldFileList);
	DDX_Control(pDX, IDC_NEWFILELIST, m_newFileList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEra2era3Dlg, CDialog)
	//{{AFX_MSG_MAP(CEra2era3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHOOSE_OLD, OnChooseOld)
	ON_BN_CLICKED(IDC_CHOOSE_NEW, OnChooseNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEra2era3Dlg::FillFileList() {
  m_oldFileList.DeleteAllItems();
  m_newFileList.DeleteAllItems();
  m_SourceFiles.RemoveAll();
  if ( g_SourcePath.IsEmpty() ) {
    if ( CheckDB(m_SourceFiles, RAGSDB_PATH_C) )
      g_SourcePath = RAGSDB_PATH_C;
    else if ( CheckDB(m_SourceFiles, RAGSDB_PATH_D) )
      g_SourcePath = RAGSDB_PATH_D;
  }
  else
    CheckDB(m_SourceFiles, g_SourcePath);

  int nFiles = m_SourceFiles.GetSize();
  if ( nFiles ) {
    if ( g_DestPath.IsEmpty() ) {
      g_DestPath = g_SourcePath;
    }
    GetDlgItem(IDC_OLDPATH)->SetWindowText(g_SourcePath);
    for( int i(0); i < nFiles; i++ ) {
      CString sFile = m_SourceFiles[i];
      sFile.Replace(g_SourcePath, _T(""));

      m_oldFileList.InsertItem(i, _T(""));    m_oldFileList.SetItemText(i, 1, sFile );    m_oldFileList.SetCheck(i, TRUE);
      sFile = ReplaceFileExt(sFile, _T("er3"));
      m_newFileList.InsertItem(i, _T(""));    m_newFileList.SetItemText(i, 1, sFile );    m_newFileList.SetCheck(i, TRUE);

    }
  }
  GetDlgItem(IDOK)->EnableWindow( nFiles > 0 );
}
/////////////////////////////////////////////////////////////////////////////
// CEra2era3Dlg message handlers

BOOL CEra2era3Dlg::OnInitDialog()
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
  m_oldFileList.InsertColumn(0, _T("Обробляти"), LVCFMT_LEFT, 70);
  m_oldFileList.InsertColumn(1, _T("Ім'я файлу"), LVCFMT_LEFT, 240);

  m_newFileList.InsertColumn(0, _T("Переписувати"), LVCFMT_LEFT, 70);
  m_newFileList.InsertColumn(1, _T("Ім'я файлу"), LVCFMT_LEFT, 240);

  ListView_SetExtendedListViewStyle(m_oldFileList.m_hWnd,
                                    ListView_GetExtendedListViewStyle(m_oldFileList.m_hWnd) |
                                    LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);

  ListView_SetExtendedListViewStyle(m_newFileList.m_hWnd,
                                    ListView_GetExtendedListViewStyle(m_newFileList.m_hWnd) |
                                    LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);

  CString s = theRegistry.GetProfileString(_T("Settings"), _T("Database"), _T(""));
  if ( !s.IsEmpty() ) {
    g_DestPath = GetFilePath(s);
    GetDlgItem(IDC_NEWPATH)->SetWindowText(g_DestPath);
  }
  FillFileList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEra2era3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEra2era3Dlg::OnPaint() 
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
HCURSOR CEra2era3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEra2era3Dlg::OnChooseOld() {
  BROWSEINFO bi;
  TCHAR szDir[MAX_PATH];
  LPITEMIDLIST pidl;
  LPMALLOC pMalloc;

  BOOL fChanged = FALSE;

  if (SUCCEEDED(SHGetMalloc(&pMalloc))) {
    ZeroMemory(&bi,sizeof(bi));
    bi.hwndOwner = AfxGetMainWnd()->m_hWnd;
    bi.pszDisplayName = 0;
    bi.pidlRoot = 0;
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
    bi.lpfn = BrowseCallbackProcOld;

    pidl = SHBrowseForFolder(&bi);
    if(pidl){
      if(SHGetPathFromIDList(pidl,szDir)){
        if ( strcmp(g_SourcePath, szDir) ) {
          g_SourcePath = szDir;
          fChanged = TRUE;
        }
        //AfxGetMainWnd()->SetWindowText(g_SourcePath);
        //m_bEnableSearch = DoesSearchPathExist();
      }
      pMalloc->Free(pidl); pMalloc->Release();
    }
  }
  if ( fChanged )
    FillFileList();
}

void CEra2era3Dlg::OnChooseNew() {
  BROWSEINFO bi;
  TCHAR szDir[MAX_PATH];
  LPITEMIDLIST pidl;
  LPMALLOC pMalloc;

  BOOL fChanged = FALSE;

  if (SUCCEEDED(SHGetMalloc(&pMalloc))) {
    ZeroMemory(&bi,sizeof(bi));
    bi.hwndOwner = AfxGetMainWnd()->m_hWnd;
    bi.pszDisplayName = 0;
    bi.pidlRoot = 0;
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
    bi.lpfn = BrowseCallbackProcNew;

    pidl = SHBrowseForFolder(&bi);
    if(pidl){
      if(SHGetPathFromIDList(pidl,szDir)){
        if ( strcmp(g_SourcePath, szDir) ) {
          g_DestPath = szDir;
          GetDlgItem(IDC_NEWPATH)->SetWindowText(g_DestPath);
          fChanged = TRUE;
        }
        //AfxGetMainWnd()->SetWindowText(g_SourcePath);
        //m_bEnableSearch = DoesSearchPathExist();
      }
      pMalloc->Free(pidl); pMalloc->Release();
    }
  }
}

void CEra2era3Dlg::FillSexMap(SEXMap& map, CDaoDatabase& db, LPCTSTR szTableName, LPCTSTR szKeyField, LPCTSTR szValueField) {
  FreeSexMap(map);

  CString sql;
  sql.Format(_T("SELECT [%s], [%s], [Пол] FROM [%s]"), szKeyField, szValueField, szTableName);
  CDaoRecordset rs(&db);
  try {
    rs.Open(dbOpenDynaset, sql);
    while ( !rs.IsEOF() ) {
      CString sID, sName;
      sID.Format(_T("%ld"), iDBLongField(rs, 0) );
      sName = iDBStringField(rs, 1);
      bool fSex = iDBBoolField(rs, 2);
      map.SetAt(sID, new CSexRecord(sName, fSex) );
      rs.MoveNext();
    }
    rs.Close();
  }
  catch(CDaoException* e) {
    e->Delete();
  }

}

void CEra2era3Dlg::Fill2FieldMap(RECORDMap& map, CDaoDatabase& db, LPCTSTR szTableName, LPCTSTR szKeyField, LPCTSTR szField1, LPCTSTR szField2) {
  Free2FieldMap(map);
  CString sql;
  sql.Format(_T("SELECT [%s], [%s], [%s] FROM [%s]"), szKeyField, szField1, szField2, szTableName);
  CDaoRecordset rs(&db);
  try {
    rs.Open(dbOpenDynaset, sql);
    while ( !rs.IsEOF() ) {
      CString sID, sField1, sField2;
      sID.Format(_T("%ld"), iDBLongField(rs, 0) );
      sField1 = iDBStringField(rs, 1);
      sField2 = iDBStringField(rs, 2);
      map.SetAt(sID, new C2FieldRecord(sField1, sField2));
      rs.MoveNext();
    }
    rs.Close();
  }
  catch(CDaoException* e) {
    e->Delete();
  }
}

void CEra2era3Dlg::FillStringMap(CMapStringToString& map, CDaoDatabase& db, LPCTSTR szTableName, LPCTSTR szKeyField, LPCTSTR szValueField) {
  map.RemoveAll();
  CString sql;
  sql.Format(_T("SELECT [%s], [%s] FROM [%s]"), szKeyField, szValueField, szTableName);
  CDaoRecordset rs(&db);
  try {
    rs.Open(dbOpenDynaset, sql);
    while ( !rs.IsEOF() ) {
      CString sID, sValue;
      sID.Format(_T("%ld"), iDBLongField(rs, 0) );
      sValue = iDBStringField(rs, 1);
      map.SetAt(sID, sValue);
      rs.MoveNext();
    }
    rs.Close();
  }
  catch(CDaoException* e) {
    e->Delete();
  }
}


void CEra2era3Dlg::SetName(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                           LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName,
                           LPCTSTR szWhat/*=NULL*/) {
  CString sKey;
  CSexRecord* pRecord = NULL;
  sKey.Format(_T("%ld"), var.lVal);
  if ( m_Names.Lookup(sKey, pRecord) ) {
    if ( pRecord->m_Name.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("ім'я, яке вказане"), this);
      if (IDOK==dlg.DoModal() ) {
        pRecord->m_Name = dlg.m_szFieldValue;
        //m_Names.SetAt(sKey, pRecord->m_Name);
      }
    }
    if ( !pRecord->m_Name.IsEmpty() ) {
      if ( szWhat ) {
        AddToMemo(rsNew, szFieldName, szWhat, pRecord->m_Name);
      }
      else {
        try {
          rsNew.SetFieldValue(szFieldName, (LPCTSTR)pRecord->m_Name);
        }
        catch(CDaoException* e) {
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
        }
      }
    }
  }
}

void CEra2era3Dlg::SetPatronymic(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                                 LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName,
                                 LPCTSTR szWhat/*=NULL*/) {
  CString sKey;
  CSexRecord* pRecord = NULL;
  sKey.Format(_T("%ld"), var.lVal);
  if ( m_Patronymics.Lookup(sKey, pRecord) ) {
    if ( pRecord->m_Name.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("по батькові, яке вказане"), this);
      if (IDOK==dlg.DoModal() ) {
        pRecord->m_Name = dlg.m_szFieldValue;
      }
    }
    if ( !pRecord->m_Name.IsEmpty() ) {
      if ( szWhat ) {
        AddToMemo(rsNew, szFieldName, szWhat, pRecord->m_Name);
      }
      else {
        try {
          rsNew.SetFieldValue(szFieldName, (LPCTSTR)pRecord->m_Name);
        }
        catch(CDaoException* e) {
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
        }
      }
    }
  }
}

void CEra2era3Dlg::SetCountry(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                              LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {
  CString sKey;
  C2FieldRecord* pRecord;
  sKey.Format(_T("%ld"), (long)var.bVal);
  if ( m_Countries.Lookup(sKey, pRecord) ) {
    if ( pRecord->m_Value1.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву держави, яка вказана"), this);
      if (IDOK==dlg.DoModal() ) {
        pRecord->m_Value1 = dlg.m_szFieldValue;
      }
    }
    if ( !pRecord->m_Value1.IsEmpty() ) {
      try {
        rsNew.SetFieldValue(szFieldName, (LPCTSTR)pRecord->m_Value1);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

void CEra2era3Dlg::SetCitizen(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                              LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName ) {
  CString sKey;
  C2FieldRecord* pRecord;
  sKey.Format(_T("%ld"), (long)var.bVal);
  if ( m_Countries.Lookup(sKey, pRecord) ) {
    if ( pRecord->m_Value2.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("громадянство, яке вказане"), this);
      if (IDOK==dlg.DoModal() ) {
        pRecord->m_Value2 = dlg.m_szFieldValue;
      }
    }

    pRecord->m_Value2.Replace(_T("громадянин "), _T(""));
    pRecord->m_Value2.Replace(_T("громадянка "), _T(""));
    pRecord->m_Value2.Replace(_T("Громадянин "), _T(""));
    pRecord->m_Value2.Replace(_T("Громадянка "), _T(""));

    if ( !pRecord->m_Value2.IsEmpty() ) {
      try {
        rsNew.SetFieldValue(szFieldName, (LPCTSTR)pRecord->m_Value2);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

void CEra2era3Dlg::SetNation(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, BOOL fSex, COleVariant var,
                              LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName,
                              BOOL fToMemo/*=FALSE*/) {
  CString sKey;
  C2FieldRecord* pRecord;
  sKey.Format(_T("%ld"), var.lVal);
  if ( m_Nations.Lookup(sKey, pRecord) ) {
    CString s = fSex ? pRecord->m_Value1 : pRecord->m_Value2;

    if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву національності, яка вказана"), this);
      if (IDOK==dlg.DoModal() ) {
        s = dlg.m_szFieldValue;
        if ( fSex ) pRecord->m_Value1 = s;
        else        pRecord->m_Value2 = s;
      }
    }
    if ( !s.IsEmpty() ) {
      if ( fToMemo ) {
        AddToMemo(rsNew, szFieldName, szFieldDesc, s);
      }
      else {
        try {
          rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
        }
        catch(CDaoException* e) {
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
        }
      }
    }
  }
}

void CEra2era3Dlg::SetNationToMemo(CDaoRecordset& rsNew, CDaoRecordset& rsOld,
                                   int NAZ, COleDateTime& DateReg, BOOL fSex,
                                   COleVariant var, LPCTSTR szMemoFld, LPCTSTR szFieldDesc,
                                   LPCTSTR szActName) {
  CString sKey;
  C2FieldRecord* pRecord;
  sKey.Format(_T("%ld"), var.lVal);
  if ( m_Nations.Lookup(sKey, pRecord) ) {
    CString s = fSex ? pRecord->m_Value1 : pRecord->m_Value2;

    if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву національності, яка вказана"), this);
      if (IDOK==dlg.DoModal() ) {
        s = dlg.m_szFieldValue;
        if ( fSex ) pRecord->m_Value1 = s;
        else        pRecord->m_Value2 = s;
      }
    }
    if ( !s.IsEmpty() ) {
      COleVariant varMemo;
      rsNew.GetFieldValue(szMemoFld, varMemo);
      CString sMemo = V_BSTRT(&varMemo);
      CString sNat;
      sNat.Format(_T("{Національність: %s}"), s);
      if ( sMemo.Find(sNat)==-1 )
        sMemo += sNat;
      try {
        rsNew.SetFieldValue(szMemoFld, (LPCTSTR)sMemo);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

void CEra2era3Dlg::SetCity(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {
  CString sKey;
  C2FieldRecord* pRecord = NULL;
  sKey.Format(_T("%ld"), var.lVal);
  if ( m_Cities.Lookup(sKey, pRecord) ) {
    CString s;
    s.Format(_T("%s %s"), pRecord->m_Value1, pRecord->m_Value2);
    s = Trim(s);
    if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву наседенного пункту, який вказан"), this);
      if (IDOK==dlg.DoModal() ) {
        s = dlg.m_szFieldValue;
        //m_Cities .SetAt(sKey, s);
        pRecord->m_Value1 = s;
        pRecord->m_Value2.Empty();
      }
    }
    if ( !s.IsEmpty() ) {
      try {
        CDaoFieldInfo fi;
        rsNew.GetFieldInfo(szFieldName, fi);
        if ( fi.m_lSize < s.GetLength() )
          s = s.Left(fi.m_lSize);
        rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

void CEra2era3Dlg::SetDistrict(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {
  CString sKey, s;
  sKey.Format(_T("%ld"), var.lVal);
  if ( m_Districts.Lookup(sKey, s) ) {
    if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву району, який вказан"), this);
      if (IDOK==dlg.DoModal() ) {
        s = dlg.m_szFieldValue;
        m_Districts.SetAt(sKey, s);
      }
    }
    if ( !s.IsEmpty() ) {
      try {
        rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

void CEra2era3Dlg::SetRegion(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {
  CString sKey, s;
  sKey.Format(_T("%ld"), var.lVal);
  if ( m_Regions.Lookup(sKey, s) ) {
    if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву області, яка вказана"), this);
      if (IDOK==dlg.DoModal() ) {
        s = dlg.m_szFieldValue;
        m_Regions.SetAt(sKey, s);
      }
    }
    if ( !s.IsEmpty() ) {
      try {
        rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
      }
      catch(CDaoException* e) {
        e->Delete();
      }
    }
  }
}

void CEra2era3Dlg::SetStreet(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {
  CString sKey, s;
  sKey.Format(_T("%ld"), var.lVal);
  if ( m_Streets.Lookup(sKey, s) ) {
    if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву вулиці, яка вказана"), this);
      if (IDOK==dlg.DoModal() ) {
        s = dlg.m_szFieldValue;
        m_Streets.SetAt(sKey, s);
      }
    }
    if ( !s.IsEmpty() ) {
      try {
        rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

void CEra2era3Dlg::SetROVD(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {

  CString sKey, s;
  sKey.Format(_T("%ld"), var.lVal);
  if ( m_ROVDs.Lookup(sKey, s) ) {
    if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву органу внутрішніх справ в ОРУДНОМУ ВІДМІНКУ, який вказан"), this);
      if (IDOK==dlg.DoModal() ) {
        s = dlg.m_szFieldValue;
        m_ROVDs.SetAt(sKey, s);
      }
    }
    if ( !s.IsEmpty() ) {
      try {
        rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

void CEra2era3Dlg::SetRAGS(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {

  CString sKey, s;
  sKey.Format(_T("%ld"), var.lVal);
  if ( m_RAGSes.Lookup(sKey, s) ) {
    if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("СКОРОЧЕНУ назву органу руєстрації в ОРУДНОМУ ВІДМІНКУ, який вказан"), this);
      if (IDOK==dlg.DoModal() ) {
        s = dlg.m_szFieldValue;
        m_RAGSes.SetAt(sKey, s);
      }
    }
    if ( !s.IsEmpty() ) {
      try {
        rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
      }
      catch(CDaoException* e) {
        e->Delete();
      }
    }
  }
}

void CEra2era3Dlg::SetBank(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {

  CString sKey, s;
  sKey.Format(_T("%ld"), var.lVal);
  if ( m_Banks.Lookup(sKey, s) ) {
    if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву фінансової установи, яка вказана"), this);
      if (IDOK==dlg.DoModal() ) {
        s = dlg.m_szFieldValue;
        m_Banks.SetAt(sKey, s);
      }
    }
    if ( !s.IsEmpty() ) {
      try {
        rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

void CEra2era3Dlg::SetMemo(CDaoRecordset& rsNew, LPCTSTR szMemoNew, COleVariant& varMemoOld){
  try { 
    COleVariant varMemo;
    rsNew.GetFieldValue(szMemoNew, varMemo);
    CString s,
            sMemo = V_BSTRT(&varMemo),
            sVar  = V_BSTRT(&varMemoOld);
    if ( !sMemo.IsEmpty() && sVar!=sMemo && sMemo.Find(sVar)==-1) {
      s = sVar + sMemo;
      rsNew.SetFieldValue(szMemoNew, (LPCTSTR)s);
    }
    else
      rsNew.SetFieldValue(szMemoNew, varMemoOld);
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
}

void CEra2era3Dlg::AddToMemo(CDaoRecordset& rsNew, LPCTSTR szMemoFld, LPCTSTR szWhat, const CString& sValue) {
  CString sMemo = GetFieldString(&rsNew, szMemoFld);
  CString s;
  if ( sMemo.Find(sValue)==-1 ) {
    s.Format(_T(" {%s: %s}"), szWhat, sValue);
    sMemo += s;
    sMemo = Trim(sMemo);
    try {
      rsNew.SetFieldValue(szMemoFld, (LPCTSTR)sMemo);
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }
}

long CEra2era3Dlg::GetRecs(int nIndex) {
  long nTotalRecs = 0;

  CString szSourceFile = m_SourceFiles.GetAt(nIndex);
  CDaoDatabase dbIn;
  if ( OpenOldDB(dbIn, szSourceFile) ) {
    TCHAR* szTables[5]={_T("Акты_о_рождении"), _T("Акты_о_браке"), _T("Акты_о_разводе"), _T("Акты_о_перемене"), _T("Акты_о_смерти")};
    for( int i(0); i < 5; i++ ) {
      CDaoTableDef td(&dbIn);
      try {
        td.Open(szTables[i]);
        long lRecs = td.GetRecordCount();
        if ( lRecs > 0 )
          nTotalRecs += lRecs;
        td.Close();
      }
      catch(CDaoException* e) {
        e->Delete();
      }
    }
    dbIn.Close();
  }
  return nTotalRecs;
}

bool CEra2era3Dlg::IsTablePresent(CDaoDatabase& db, LPCTSTR szTable) {
  CDaoTableDefInfo tabledefinfo;
  try {
    db.GetTableDefInfo(szTable, tabledefinfo);
    return true;
  }
  catch(CDaoException* e){
    e->Delete();
  }
  return false;
}
void CEra2era3Dlg::Convert(int nIndex) {
  CString szSourceFile = m_SourceFiles.GetAt(nIndex);
  CString szDestFile;

  GetDlgItem(IDC_NEWPATH)->GetWindowText(szDestFile);
  szDestFile += m_newFileList.GetItemText(nIndex, 1);

  m_Banks.RemoveAll();
  Free2FieldMap(m_Cities);
  m_Regions.RemoveAll();
  m_Districts.RemoveAll();
  Free2FieldMap(m_Countries);
  m_Streets.RemoveAll();
  Free2FieldMap(m_Nations);
  m_RAGSes.RemoveAll();
  m_ROVDs.RemoveAll();
  m_MHospitals.RemoveAll();
  m_Hospitals.RemoveAll();

  m_oldFileList.SetItemState(nIndex, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
  m_newFileList.SetItemState(nIndex, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
  m_oldFileList.SetHotItem(nIndex);
  m_newFileList.SetHotItem(nIndex);
  m_oldFileList.EnsureVisible(nIndex, TRUE);
  m_newFileList.EnsureVisible(nIndex, TRUE);
  m_oldFileList.RedrawItems(0, nIndex);
  m_newFileList.RedrawItems(0, nIndex);

  CDaoDatabase dbIn, dbOut;
  if ( false==JetFile(szDestFile) ) {
    CString szDBTemplate;
    szDBTemplate.Format(_T("%s\\Templates\\dbTemplate.mdb"), GetModulePath() );
    CopyFile(szDBTemplate, szDestFile, TRUE);
  }
  RedrawWindow();

  m_FilePos = 0;

  try {
    dbOut.Open(szDestFile, FALSE, FALSE);
    try {
      m_ProgressFile.SetRange32(0, (int)m_RecArray.GetAt(nIndex));
      m_ProgressFile.ShowWindow(SW_SHOW);
      m_ProgressFile.SetPos(m_FilePos);

      CString s;
      s.Format(_T("Оброблюється файл бази даних %s."), szSourceFile); 
      GetDlgItem(IDC_CURRENT_FILE)->SetWindowText(s);

      if ( OpenOldDB(dbIn, szSourceFile) ) {
        FillSexMap(m_Names,       dbIn, _T("Имена"),          _T("КодИмени"),    _T("Имя")      );
        FillSexMap(m_Patronymics, dbIn, _T("Отчества"),       _T("КодОтчества"), _T("Отчество") );
        FillStringMap(m_Banks,    dbIn, _T("Банки"),          _T("Код"),         _T("Банк")     );
        Fill2FieldMap(m_Cities,   dbIn, _T("геоНП"),          _T("Код НП"),      _T("Название"),  _T("НП") );
        FillStringMap(m_Regions,  dbIn, _T("геоОбласти"),     _T("КодО"),        _T("Область")  );
        FillStringMap(m_Districts,dbIn, _T("геоРайоны"),      _T("Код Района"),  _T("Район")    );
        Fill2FieldMap(m_Countries,dbIn, _T("геоСтраны"),      _T("Код_Страны"),  _T("Страна"),      _T("Гражданство") );
        FillStringMap(m_Streets,  dbIn, _T("геоУлицы"),       _T("Код"),         _T("Улица")    );
        Fill2FieldMap(m_Nations,  dbIn, _T("Национальности"), _T("Код"),         _T("Чоловік"),     _T("Жінка") );
        FillStringMap(m_RAGSes,   dbIn, _T("РАГСы"),          _T("Код"),         _T("РАГС")     );
        FillStringMap(m_ROVDs,    dbIn, _T("РОВД"),           _T("Код"),         _T("Паспорт_выдан")     );

        FillStringMap(m_MHospitals,dbIn,_T("РодДома"),        _T("Код"),         _T("Больница") );
        FillStringMap(m_Hospitals,dbIn, _T("СвВыдано"),       _T("Код"),         _T("Больница") );

        if ( IsTablePresent(dbIn, _T("Акты_о_смерти")) )
          CopyDeath(nIndex, dbIn, dbOut);
        if ( IsTablePresent(dbIn, _T("Акты_о_рождении")) )
          CopyBirth(nIndex, dbIn, dbOut);
        if ( IsTablePresent(dbIn, _T("Акты_о_браке")) )
          CopyMarriage(nIndex, dbIn, dbOut);
        if ( IsTablePresent(dbIn, _T("Акты_о_разводе")) )
          CopyDivorce(nIndex, dbIn, dbOut);
        if ( IsTablePresent(dbIn, _T("Акты_о_перемене")) )
          CopyChange(nIndex, dbIn, dbOut);
    
        dbIn.Close();
      }
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
    dbOut.Close();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
}

void CEra2era3Dlg::OnOK() {
  int i, nFiles = m_oldFileList.GetItemCount();

  int nFilesToConvert = 0;
  m_TotalRecs = 0;

  m_RecArray.SetSize(nFiles);

  CWaitCursor wc;
  for( i=0; i < nFiles; i++ ) {
    if ( m_oldFileList.GetCheck(i) ) {
      long lRecs = GetRecs(i);
      m_RecArray.SetAt(i, (DWORD)lRecs);
      m_TotalRecs += lRecs;
      nFilesToConvert++;
    }
  }
  
  if ( nFilesToConvert && m_TotalRecs ) {
    m_ProgressTotal.SetRange32(0, m_TotalRecs);
    m_ProgressTotal.ShowWindow(SW_SHOW);
    for( i=0; i < nFiles; i++ ) {
      if ( m_oldFileList.GetCheck(i) ) {
        Convert( i );
      }
    }
  }

  FreeSexMap(m_Names);
  FreeSexMap(m_Patronymics);
  Free2FieldMap(m_Cities);
  Free2FieldMap(m_Countries);
  Free2FieldMap(m_Nations);

  if ( nFilesToConvert ) {
    LPCTSTR szThatAll = _T("Конвертування файлів бази даних закінчено.");
    GetDlgItem(IDC_CURRENT_FILE)->SetWindowText(szThatAll);
    AfxMessageBox(szThatAll);
  }

	CDialog::OnOK();
}

