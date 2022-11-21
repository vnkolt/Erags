
// UpdaterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Updater.h"
#include "UpdaterDlg.h"

#include "MD5.h"
#include "RegWriter.h"

#include "..\ZipArchive\ZipArchive.h"
#include "..\ZipArchive\Options.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define LC_NAME     0
#define LC_DATETIME 1
#define LC_SIZE     2

typedef CArray<CDaoFieldInfo, CDaoFieldInfo&> FeildsArray;

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

BOOL IsFileName(const CString& s) {
  CString szFilename;
  szFilename.Format(_T("%s\\%s"), theApp.m_szDownloadsPath, s);
  if ( FileExists(szFilename) ) {
    return true;
  }
  return false;
}
BOOL IsDigits(const CString& s) {
  int nLen = s.GetLength();
  for( int i(0); i < nLen; i++ ) {
    if ( 0==isdigit(s[i]) ) {
      return false;
    }
  }
  return true;
}
BOOL IsHex(const CString& s) {
  int nLen = s.GetLength();
  for( int i(0); i < nLen; i++ ) {
    if ( 0==isxdigit(s[i]) ) {
      return false;
    }
  }
  return true;
}

BOOL IsURL(const CString& s) {
  CString sz = s;
  sz.MakeLower();
  if ( sz.Left(7) != _T("http://") ) {
    return false;
  }
  return true;
}

BOOL IsValidTokens(const CString& s) {
  int nPos = 0;
  CString szToken;
  szToken = s.Tokenize(_T(" \t"), nPos);
  // Filename
  if ( szToken.IsEmpty() || false==IsFileName(szToken) ) {
    return false;
  }
  // DateTime
  szToken = s.Tokenize(_T(" \t"), nPos);
  if ( szToken.GetLength() != 14 || false==IsDigits(szToken) ) {
    return false;
  }
  // Filesize
  szToken = s.Tokenize(_T(" \t"), nPos);
  if ( szToken.IsEmpty() || false==IsDigits(szToken) ) {
    return false;
  }
  // MD5
  szToken = s.Tokenize(_T(" \t"), nPos);
  if ( szToken.GetLength() != 32 || false==IsHex(szToken) ) {
    return false;
  }
  // URL
  szToken = s.Tokenize(_T(" \t"), nPos);
  if ( szToken.IsEmpty() || false==IsURL(szToken) ) {
    return false;
  }
  return true;
}

void FillArray(FIArray& fiArray, LPCTSTR szFileInfo) {
  CStdioFile f;
  if ( false==f.Open(szFileInfo, CFile::modeRead) ) {
    return;
  }
  CString s;
  while ( f.ReadString(s) ) {
    s.Trim();
    if ( false==s.IsEmpty() && IsValidTokens(s) ) {
      CString szTime;
      SFileInfo fi;
      int nPos = 0;

      fi.szFilename    = s.Tokenize(_T(" \t"), nPos);
      // fi.lUnixFileTime = atol(s.Tokenize(_T(" \t"), nPos));
      szTime           = s.Tokenize(_T(" \t"), nPos);
      if ( szTime.GetLength()==14 ) {
        SYSTEMTIME st;
        memset(&st, 0, sizeof(st));
        st.wYear   = atoi(szTime.Mid(0,4));
        st.wMonth  = atoi(szTime.Mid(4,2));
        st.wDay    = atoi(szTime.Mid(6,2));
        st.wHour   = atoi(szTime.Mid(8,2));
        st.wMinute = atoi(szTime.Mid(10,2));
        st.wSecond = atoi(szTime.Mid(12,2));
        SystemTimeToFileTime(&st, &fi.ft);
        /*
        //               YYYY                    MM                  DD
        odt.SetDateTime( atoi(s.Mid(0,4)), atoi(s.Mid(4,2)), atoi(s.Mid(6,2)), 
        //                 hh                    mm                  ss
                         atoi(s.Mid(8,2)), atoi(s.Mid(10,2)), atoi(s.Mid(12,2))
                       );
        if ( odt.GetStatus()==COleDateTime::valid ) {
        }
        */

      }

      if ( nPos >= 0 ) fi.dwFilesize = atol(s.Tokenize(_T(" \t"), nPos));
      if ( nPos >= 0 ) fi.szMD5      = s.Tokenize(_T(" \t"), nPos);
      fiArray.Add(fi);
    }
  }

  f.Close();
}

BOOL IsTablePresent(CDaoDatabase& db, LPCTSTR szTableName) {
  if ( db.IsOpen()==false )
    return false;

  CDaoTableDefInfo tdInfo;
  short nTables = db.GetTableDefCount();
  try {
    for( short i(0); i < nTables; i++ ) {
      db.GetTableDefInfo(i, tdInfo);
      if ( tdInfo.m_strName.CompareNoCase(szTableName)==0 ) {
        return true;
      }
    }
  }
  catch ( CDaoException* e ) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
  return false;
}


// CUpdaterDlg dialog
CUpdaterDlg::CUpdaterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdaterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  m_dwTotalSize = 0;
  m_fEnableClose = false;
}

void CUpdaterDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_FILES, m_FileList);
  DDX_Control(pDX, IDC_PROGRESS, m_Progress);
}

BEGIN_MESSAGE_MAP(CUpdaterDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CUpdaterDlg::FillList() {
  int nSize = m_Files.GetSize();
  for( int i(0); i < nSize; i++ ) {
    SFileInfo& fi = m_Files.GetAt(i);
    CString s;
    COleDateTime odt( fi.ft );
    m_FileList.InsertItem(i, fi.szFilename);
    s.Format(_T("%02d.%02d.%04d %02d:%02d:%02d"),
             odt.GetDay(), odt.GetMonth(), odt.GetYear(),
             odt.GetHour(), odt.GetMinute(), odt.GetSecond()
             );
    m_FileList.SetItemText(i, LC_DATETIME, s);

    s.Format(_T("%lu"), fi.dwFilesize);
    m_FileList.SetItemText(i, LC_SIZE, s);

    m_dwTotalSize += fi.dwFilesize;
  }
}

void CUpdaterDlg::Unpack(LPCTSTR szFilename) {
  CZipArchive za;
  COptions    zoptions;
  za.Open(szFilename, CZipArchive::zipOpen, zoptions.m_bTdComp ? 1 : 0 );
  CZipFileHeader fh;
  int iCount = za.GetCount();
  for (int i = 0; i < iCount; i++) {
    CString szExctractPath;
    za.GetFileInfo(fh, (WORD)i);
    CString szFilename = (LPCTSTR)fh.GetFileName();
    BOOL fSuccess = za.ExtractFile(i, theApp.m_szEraPath, true);
  }
}

void CopyRecord(CDaoRecordset& rsDest, CDaoRecordset& rsSrc, CStringArray& FieldsSrc) {

  CArray <COleVariant, COleVariant&> values;
  values.SetSize(FieldsSrc.GetSize());

  try {
    for ( int i(0); i < FieldsSrc.GetSize(); i++ ) {
      CString szField = FieldsSrc.GetAt(i);
      COleVariant ov;
      try {
        rsSrc.GetFieldValue(szField, ov);
        values.SetAt(i, ov);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
  catch(CDaoException* e){
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return;
  }

  rsDest.AddNew();
  for ( int i = 0; i < FieldsSrc.GetSize(); i++ ) {
    CString szField = FieldsSrc.GetAt(i);
    COleVariant ov;
    ov = values.GetAt(i);
    try {
      rsDest.SetFieldValue(szField, ov);
    }
    catch(CDaoException* e){
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }
  rsDest.Update();
}

void CUpdaterDlg::ReplaceTable(CDaoDatabase& dbOld, CDaoDatabase& dbNew, LPCTSTR szTableName) {
  if ( IsTablePresent(dbOld, szTableName) ) {
    dbOld.DeleteTableDef(szTableName);
  }
  CDaoRecordset rsNew(&dbNew);
  rsNew.Open(dbOpenTable, szTableName);
  FeildsArray Fields;
  CStringArray FieldNames;
  int nFields = rsNew.GetFieldCount();
  int i;
  for( i=0; i < nFields; i++ ) {
    CDaoFieldInfo fi;
    rsNew.GetFieldInfo(i, fi, AFX_DAO_SECONDARY_INFO/*AFX_DAO_PRIMARY_INFO*/);
    FieldNames.Add(fi.m_strName);
    Fields.Add(fi);
  }
  CDaoTableDef tdOld(&dbOld);
  tdOld.Create(szTableName);
  for( i=0; i < nFields; i++ ) {
    CDaoFieldInfo& fi = Fields[i];
    tdOld.CreateField(fi.m_strName, fi.m_nType, fi.m_lSize, fi.m_lAttributes);
  }
  tdOld.Append();
  CDaoRecordset rsOld(&dbOld);
  rsOld.Open(dbOpenTable, szTableName);
  while ( false==rsNew.IsEOF() ) {
    CopyRecord(rsOld, rsNew, FieldNames);
    rsNew.MoveNext();
  }

  // CDaoTableDef tdNew(&dbOld);
  // tdNew.Open(szTableName);
  rsOld.Close();
  int nIndexes = rsNew.GetIndexCount();
  for( i = 0; i < nIndexes; i++ ) {
    CDaoIndexInfo indexinfo;
    rsNew.GetIndexInfo(i, indexinfo, AFX_DAO_SECONDARY_INFO);
    try {
      tdOld.CreateIndex(indexinfo);
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }

  rsNew.Close();
}

void CUpdaterDlg::UpdateHelpers(LPCTSTR szFilename) {
  CZipArchive za;
  COptions    zoptions;
  int berr = 0;
  do {
    try {
      za.Open(szFilename, CZipArchive::zipOpen, zoptions.m_bTdComp ? 1 : 0 );
      CZipFileHeader fh;
      int iCount = za.GetCount();
      for (int i = 0; i < iCount; i++) {
        CString szExctractPath;
        za.GetFileInfo(fh, (WORD)i);
        CString szFilename = (LPCTSTR)fh.GetFileName();
        BOOL fSuccess = za.ExtractFile(i, theApp.m_szDownloadsPath, false);
      }
      za.Close();
    }
    catch (CZipException* e) {
      if (e->m_iCause == CZipException::cdirNotFound)
	      berr = -1;
		  else
			  berr = 1;
			e->Delete();
    }
    catch (CException* e) {
	    e->Delete();
		  berr = 1;
    }
  } while (berr == -1);
  CString szNewHelpers;
  CString szOldHelpers;
  szNewHelpers.Format(_T("%s\\Helpers.mdb"), theApp.m_szDownloadsPath);
  szOldHelpers.Format(_T("%s\\DB\\Helpers.mdb"), theApp.m_szEraPath);
  if ( false==FileExists(szOldHelpers) ) {
    return;
  }
  if ( false==FileExists(szNewHelpers) ) {
    return;
  }

  static BYTE bPassword[] = { ~';', ~'P', ~'W', ~'D', ~'=',
                              ~'A', ~'n', ~'t', ~'o', ~'n',
                              ~'V', ~'i', ~'t', ~'a', ~'l', ~'i',~'a', ~0
                            };

  CString szConnect(' ', sizeof(bPassword));
  for( int i(0); i < sizeof(bPassword); i++ ) {
    szConnect.SetAt(i, ~bPassword[i]);
  }

  CDaoDatabase dbOld;
  CDaoDatabase dbNew;
  BOOL fOpened = true;

  try {
    dbOld.Open(szOldHelpers, true, false, szConnect);
  }
  catch(CDaoException* e) {
    fOpened = false;
    e->Delete();
  }
  if ( false==fOpened ) {
    return;
  }

  try {
    dbNew.Open(szNewHelpers, true, false, szConnect);
  }
  catch(CDaoException* e){
    fOpened = false;
    e->Delete();
  }

  if ( false==fOpened ) {
    return;
  }

  ReplaceTable(dbOld, dbNew, _T("Translator"));
  ReplaceTable(dbOld, dbNew, _T("RList"));
  ReplaceTable(dbOld, dbNew, _T("Geography"));

  dbNew.Close();
  dbOld.Close();

  BOOL fCompactOk = false;
  CString szPackedFileName;
  szPackedFileName.Format(_T("%s.pack"), szOldHelpers);

  try {
    CDaoWorkspace::CompactDatabase(szOldHelpers, szPackedFileName, dbLangCyrillic, dbVersion30, szConnect);
    fCompactOk = true;
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
  if ( fCompactOk ) {
    DeleteFile(szOldHelpers);
    ::MoveFile(szPackedFileName, szOldHelpers);
    DeleteFile(szFilename);
  }

}

void CUpdaterDlg::Copy(LPCTSTR szSource, FILETIME& ft) {
  CString szDest, szSrc;
  szSrc.Format(_T("%s\\%s"), theApp.m_szDownloadsPath, szSource);
  if ( _stricmp(szSource, _T("TEMPLATES.ZIP"))==0 ) {
    szDest.Format(_T("%s\\Templates\\%s"), theApp.m_szEraPath, szSource);
  }
  else {
    szDest.Format(_T("%s\\%s"), theApp.m_szEraPath, szSource);
  }
_try_again:
  if ( false==::CopyFile(szSrc, szDest, false) ) {
    CString szMsg;
    szMsg.Format(_T("Помилка при спробі переписати файл \"%s\".\r\n")
                 _T("Можливо, цей файл використовую інша програма. Закрийтё її і спробуйте ще раз."), 
                 szDest);
    if ( IDRETRY==AfxMessageBox(szMsg, MB_RETRYCANCEL) ) {
      goto _try_again;
    }
  }
}

void CUpdaterDlg::Update() {
  int nSize = m_Files.GetSize();
  DWORD dwTotalSize = 0;
  for( int i(0); i < nSize; i++ ) {
    BOOL fCheck = false;
    SFileInfo& fi = m_Files.GetAt(i);
    CString szFilename, szMD5;
    szFilename.Format(_T("%s\\%s"), theApp.m_szDownloadsPath, fi.szFilename);

    dwTotalSize += fi.dwFilesize;

    WIN32_FIND_DATA fd;
    if ( false==FileExists(szFilename, &fd) ) {
      continue;
    }
    if ( fd.nFileSizeLow != fi.dwFilesize ) {
      continue;
    }
    if ( false==CalcMD5(szFilename, szMD5) ) {
      continue;
    }
    if ( szMD5.CompareNoCase(fi.szMD5) != 0 ) {
      continue;
    }
    CString szUpperFilename = fi.szFilename;
    szUpperFilename.MakeUpper();

    CString szSource;
    szSource.Format(_T("%s\\%s"), theApp.m_szDownloadsPath, fi.szFilename);

    if ( szUpperFilename.Right(4)==_T(".ZIP") && szUpperFilename!=_T("TEMPLATES.ZIP") ) {
      if ( szUpperFilename==_T("HELPERS.ZIP") ) {
        UpdateHelpers(szSource);
      }
      else {
        Unpack(szSource);
      }
    }
    else {
      Copy(fi.szFilename, fi.ft);
    }
    m_Progress.SetPos(dwTotalSize);
    m_FileList.SetCheck(i, true);
    PeekAndPump();
  }
}

// CUpdaterDlg message handlers
BOOL CUpdaterDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
  ListView_SetExtendedListViewStyle(m_FileList.m_hWnd, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
  m_FileList.InsertColumn(LC_NAME     , _T("Ім'я файлу")    , LVCFMT_LEFT , 260);
  m_FileList.InsertColumn(LC_DATETIME , _T("Дата/Час")      , LVCFMT_LEFT , 120);
  m_FileList.InsertColumn(LC_SIZE     , _T("Розмір (байт)") , LVCFMT_RIGHT, 100);

  FillArray(m_Files, theApp.m_szNewFileInfo);
  FillList();
  CenterWindow();
  ShowWindow(SW_SHOW);
  m_Progress.SetRange32(0, m_dwTotalSize);
  Update();

  CRegWriter rw1(HKEY_CURRENT_USER);
  if ( rw1.OpenKey() ) {
    rw1.SetLastUpdated();
    rw1.CloseKey();
  }
  CRegWriter rw2(HKEY_LOCAL_MACHINE);
  if ( rw2.OpenKey() ) {
    rw2.SetLastUpdated();
    rw2.CloseKey();
  }

  m_fEnableClose = true;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUpdaterDlg::OnSysCommand(UINT nID, LPARAM lParam) {
  CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUpdaterDlg::OnPaint() {
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUpdaterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

