// ZipDBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"

#include "DataManager.h"
#include "ZipDBDlg.h"
#include "YesNoDlg.h"

#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"
#include "..\Common\MDB.h"
#include "..\ZipArchive\ZipPlatform.h"
#include "..\ZipArchive\ZipArchive.h"
#include "..\ZipArchive\Options.h"

#include "..\Controls\ProgressBar.h"
#include "..\Controls\ShellType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FLC_FILENAME  0
#define FLC_DATETIME  1
#define FLC_SIZE      2
#define FLC_NOTICE    3

#define IML_PROCESS 0
#define IML_OK      1
#define IML_ERROR   2
#define IML_ZIPPED  3

#if !defined(PROGRESS_CONTINUE)
#define PROGRESS_CONTINUE   0
#endif


typedef
DWORD
(WINAPI *LPPROGRESS_ROUTINE)(
    LARGE_INTEGER TotalFileSize,
    LARGE_INTEGER TotalBytesTransferred,
    LARGE_INTEGER StreamSize,
    LARGE_INTEGER StreamBytesTransferred,
    DWORD dwStreamNumber,
    DWORD dwCallbackReason,
    HANDLE hSourceFile,
    HANDLE hDestinationFile,
    LPVOID lpData OPTIONAL
    );

typedef WINBASEAPI BOOL (WINAPI *FCopyFileEx)
                        (IN LPCSTR lpExistingFileName,
                         IN LPCSTR lpNewFileName,
                         IN LPPROGRESS_ROUTINE lpProgressRoutine OPTIONAL,
                         IN LPVOID lpData OPTIONAL,
                         IN LPBOOL pbCancel OPTIONAL,
                         IN DWORD dwCopyFlags
                        );


/*
LARGE_INTEGER g_TotalSize   = {0};
LARGE_INTEGER g_Transferred = {0};
*/

DWORD CALLBACK CopyProgressRoutine(LARGE_INTEGER TotalFileSize, LARGE_INTEGER TotalBytesTransferred,
                                   LARGE_INTEGER StreamSize, LARGE_INTEGER StreamBytesTransferred,
                                   DWORD dwStreamNumber, DWORD dwCallbackReason,
                                   HANDLE hSourceFile, HANDLE hDestinationFile, LPVOID lpData
                                  )
{
  CWaitCursor wc;
  double nPercent = 0;
  if ( TotalFileSize.QuadPart ) {
    nPercent = (double(TotalBytesTransferred.QuadPart*100))/((double)TotalFileSize.QuadPart);
  }
  //LARGE_INTEGER Transferred;
  //Transferred.QuadPart = g_Transferred.QuadPart+TotalBytesTransferred.QuadPart;
  //double nPercent = (double(Transferred.QuadPart*100))/((double)TotalFileSize);
  /*
  if ( TotalFileSize.QuadPart==TotalBytesTransferred.QuadPart ) {
    g_Transferred.QuadPart += TotalBytesTransferred.QuadPart;
  }
  */
  CProgressBar* pBar = (CProgressBar*)lpData;
  pBar->SetPos( (int)nPercent );
  PeekAndPump();
  return PROGRESS_CONTINUE;
}


int GetIndexOf(DWORD dwValue, const CDWordArray* pArray) {
  for( int i(0); i < pArray->GetSize(); i++ ) {
    if ( dwValue==pArray->GetAt(i) )
      return i;
  }
  return -1;
}
CZipFileInfo::CZipFileInfo() {
  m_dwLength = 0;
  m_fIsReadOnly =  FALSE;
  m_fDoZip = TRUE;
  m_ZipIndex = (WORD)-1;
}

/************************************** : by VK at 26.11.2005 2:30:41 **\
CString AddRTFString(LPCTSTR sz, BOOL fPar, BOOL fBold, BOOL fRed) {
  CString s;
  if ( fPar )  s += _T("\\par ");
  if ( fBold ) s += _T("\\b ");
  if ( fRed )  s += _T("\\cf1 ");
  while ( *sz ) {
    if ( (unsigned char)*sz > 128 ) {
      CString sChar;
      sChar.Format(_T("\\\'%02x"), (unsigned char)*sz);
      s += sChar;
      sz++;
      continue;
    }
    else if ( *sz == '\\' ) {
      s += '\\';
    }
    s += *sz++;
  }
  if ( fRed )  s += _T("\\cf0 ");
  if ( fBold ) s += _T("\\b0 ");
  s += _T("\r\n");
  return s;
}
\************************************** : by VK at 26.11.2005 2:30:45 **/

/////////////////////////////////////////////////////////////////////////////
// CZipDBDlg dialog
CZipDBDlg::CZipDBDlg(CWnd* pParent /*=NULL*/)
        	:CDialogEx(CZipDBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZipDBDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_fYesButton = FALSE;
}


void CZipDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZipDBDlg)
	DDX_Control(pDX, IDC_FILELIST, m_FileList);
	DDX_Control(pDX, IDC_INFO, m_Info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZipDBDlg, CDialogEx)
	//{{AFX_MSG_MAP(CZipDBDlg)
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CZipDBDlg::SetCurrentItem(int nItem) {
  m_FileList.EnsureVisible(nItem, TRUE);
  m_FileList.SetItemState(nItem, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
}
void CZipDBDlg::PrepareFileList(LPCTSTR szRoot, LPCTSTR szPath) {
  CFileFind finder;
  CString sPath;
  sPath.Format(_T("%s\\*.*"), szPath);
  BOOL bWorking = finder.FindFile(sPath);
  while (bWorking) {
    bWorking = finder.FindNextFile();
    if (finder.IsDots())
         continue;
    if ( finder.IsDirectory() )  {
      CString sNewPath = finder.GetFilePath();
      PrepareFileList(szRoot, sNewPath);
      continue;
    }
    CString szExt = finder.GetFileName().Right(4);
    if ( 0==szExt.CompareNoCase(".er3") || 0==szExt.CompareNoCase(".mdb") ) {
      CZipFileInfo zfi;
      CString szFileName = finder.GetFilePath();
      if ( !ZipPlatform::GetFileModTime(szFileName, zfi.m_ftModiTime) )
        zfi.m_ftModiTime = time(NULL);
      zfi.m_ftModiTime &= 0xFFFFFFFE;
      zfi.m_szFileName  = szFileName.Mid(strlen(szRoot));
      zfi.m_dwLength    = finder.GetLength();
      zfi.m_fIsReadOnly = finder.IsReadOnly();
      int nItem = m_Files.Add(zfi);
      m_FileList.InsertItem(nItem, zfi.m_szFileName, IML_PROCESS);
      //SetCurrentItem(nItem);
      CString s;
      CTime t(zfi.m_ftModiTime);
      s.Format(_T("%04d.%02d.%02d/%02d:%02d:%02d"),
                   t.GetYear(), t.GetMonth(), t.GetDay(),
                   t.GetHour(), t.GetMinute(), t.GetSecond() );
      m_FileList.SetItemText(nItem, FLC_DATETIME, s);
  		s.Format(_T("%d"), zfi.m_dwLength);
		  m_FileList.SetItemText(nItem, FLC_SIZE, s);
    }
  }
}
void CZipDBDlg::SetDoZip(CZipFileHeader* pZipFileHeader, WORD wZipIndex) {
  CCyrString szZipFile = pZipFileHeader->GetFileName();
  szZipFile.MakeUpper();
  for( int i(0); i < m_Files.GetSize(); i++ ) {
    CZipFileInfo fi = m_Files.GetAt(i);
    CCyrString sDskFileName = fi.m_szFileName;
    sDskFileName.MakeUpper();
    if ( szZipFile==sDskFileName ) {
      fi.m_ZipIndex = wZipIndex;
      if ( fi.m_ftModiTime <= pZipFileHeader->GetTime() ) {
        fi.m_fDoZip = FALSE;
        CString s;
        s.Format(_T("Файл \"%s\" не змінювався після останньої архівації."), fi.m_szFileName);
        AddToLog(s, TRUE, TRUE, FALSE);
        m_FileList.SetItem(i, 0, LVIF_IMAGE, NULL, IML_OK, 0, 0, 0);
  		  m_FileList.SetItemText(i, FLC_NOTICE, _T("Не змінювався після останньої архівації."));
      }
      m_Files.SetAt(i, fi);
    }
  }
}

void CopyRecord(CDaoRecordset& rsDest, CDaoRecordset& rsSrc, CStringArray& FieldsSrc, COleVariant* pOV=NULL) {
  CArray <COleVariant, COleVariant&> values;
  values.SetSize(FieldsSrc.GetSize());

  try {
    for ( int i(0); i < FieldsSrc.GetSize(); i++ ) {
      CString szField = FieldsSrc.GetAt(i);
      if ( szField==_T("ID") )
        continue;
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

  if ( rsDest.CanAppend() ) {
    BOOL fAdded = true;
    try {
      rsDest.AddNew();
    }
    catch(CDaoException* e) {
      fAdded = false;
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
    if ( fAdded ) {
      for ( int i = 0; i < FieldsSrc.GetSize(); i++ ) {
        CString szField = FieldsSrc.GetAt(i);
        COleVariant ov;
        if ( szField==_T("ID") ) {
          if ( NULL==pOV )
            continue;
          else
            ov = *pOV;
        }
        else {
          ov = values.GetAt(i);
        }
        if ( IsFieldPresent(rsDest, szField) ) {
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
      }
      rsDest.Update();
    }
  }
}

void CompactDatabaseTable(CDaoDatabase& dbDest, CDaoDatabase& dbSrc, LPCTSTR szTableName, CDWordArray* pOldIDs=NULL, CDWordArray* pNewIDs=NULL, BOOL bSetID=false) {
  CDaoRecordset rsDest(&dbDest);
  CDaoRecordset rsSrc (&dbSrc);
  CStringArray Fields;
  try {
    rsDest.Open(dbOpenTable, szTableName);
    /*
    for (short i(0); i < rsDest.GetFieldCount(); i++ ) {
      CDaoFieldInfo fi;
      rsDest.GetFieldInfo(i, fi, AFX_DAO_PRIMARY_INFO);
      FieldsDest.Add(fi.m_strName);
    }
    */
    rsSrc.Open(dbOpenTable, szTableName, dbReadOnly);

    for ( short i(0); i < rsSrc.GetFieldCount(); i++ ) {
      CDaoFieldInfo fi;
      rsSrc.GetFieldInfo(i, fi, AFX_DAO_PRIMARY_INFO);
      if ( IsFieldPresent(rsDest, fi.m_strName) ) {
        Fields.Add(fi.m_strName);
      }
    }

    while ( false==rsSrc.IsEOF() ) {
      try {
        COleVariant ov;
        BOOL fEmpty = false;
        rsSrc.GetFieldValue(_T("NUMBER"), ov);
        fEmpty = (0==ov.iVal);
        if ( fEmpty && stricmp(szTableName, _T("MARRIAGES"))==0) {
          CString szMOld = Trim(GetFieldString(&rsSrc, _T("MOLD_SURNAME")));
          CString szWOld = Trim(GetFieldString(&rsSrc, _T("WOLD_SURNAME")));
          if ( false==szMOld.IsEmpty() || false==szWOld.IsEmpty() ) {
            fEmpty = false;
          }
        }

        if ( false==fEmpty ) {
          rsSrc.GetFieldValue(_T("ID"), ov);
          if ( bSetID ) {
            if ( pOldIDs && pNewIDs && pOldIDs->GetSize()==pNewIDs->GetSize() ) {
              int idIndex = GetIndexOf((DWORD)ov.lVal, pOldIDs);
              if ( idIndex != -1 )
                ov.lVal = (long)pNewIDs->GetAt(idIndex);
            }
            CopyRecord(rsDest, rsSrc, Fields, &ov);
          }
          else {
            CopyRecord(rsDest, rsSrc, Fields);
            if ( pOldIDs && pNewIDs) {
              pOldIDs->Add( ov.lVal );
              rsDest.SetBookmark(rsDest.GetLastModifiedBookmark());
              rsDest.GetFieldValue(_T("ID"), ov);
              pNewIDs->Add( ov.lVal );
            }
          }
        }
      }
      catch(CDaoException* e){
        #ifdef _DEBUG
        e->ReportError();
        #endif
        e->Delete();
      }
      rsSrc.MoveNext();
    }
    rsSrc.Close();
    rsDest.Close();
  }
  catch(CDaoException* e){
    #ifdef _DEBUG
     e->ReportError();
    #endif
    e->Delete();
  }
}
void MyCompactDatabase(LPCTSTR szFileName) {
  CString szTemplate, szNewFileName;
  szTemplate.Format(_T("%s\\DBTemplate.mdb"), theApp.m_sTemplatePath);
  szNewFileName = SetFileExt(szFileName, _T("mdb"));
  if ( CopyFile(szTemplate, szNewFileName, false) ) {
    CDaoDatabase dbSrc;
    CDaoDatabase dbDest;
    try {
      CDWordArray oldIDs, newIDs;
      dbSrc.Open(szFileName, true, false);
      dbDest.Open(szNewFileName, true, false);
      CompactDatabaseTable(dbDest, dbSrc, _T("BIRTHES"));
      CompactDatabaseTable(dbDest, dbSrc, _T("CHANGES"), &oldIDs, &newIDs);
      CompactDatabaseTable(dbDest, dbSrc, _T("CHANGESDEP"), &oldIDs, &newIDs, true);
      CompactDatabaseTable(dbDest, dbSrc, _T("DEATHES"));
      CompactDatabaseTable(dbDest, dbSrc, _T("DIVORCES"));
      CompactDatabaseTable(dbDest, dbSrc, _T("MARRIAGES"));
      dbDest.Close();
      dbSrc.Close();
    }
    catch(CDaoException* e){
      #ifdef _DEBUG
       e->ReportError();
      #endif
      e->Delete();
    }
    if ( dbSrc.IsOpen() )
      dbSrc.Close();
    if ( dbDest.IsOpen() )
      dbDest.Close();
    if ( CopyFile(szNewFileName, szFileName, false) ) {
      DeleteFile(szNewFileName);
    }
  }
}
int CZipDBDlg::Pack(LPCTSTR szFileName, int nItem) {
  CString szConnect;
  CString szExt = GetFileExt(szFileName);
  BOOL fCompactOk = FALSE;
  if ( szExt.CompareNoCase("mdb")==0 ) {
    static BYTE bPassword[] = { ~';', ~'P', ~'W', ~'D', ~'=',
                                ~'A', ~'n', ~'t', ~'o', ~'n',
                                ~'V', ~'i', ~'t', ~'a', ~'l', ~'i',~'a', ~0
                              };

    szConnect = CString(' ', sizeof(bPassword));
    for( int i(0); i < sizeof(bPassword); i++ ) {
      szConnect.SetAt(i, ~bPassword[i]);
    }
  }
  else if ( szExt.CompareNoCase("er3")==0 ) {
    //szConnect = _T(";PWD=");
    szConnect = _T("");
  }
  CString szLog;
  CDaoDatabase db;
  try {
    db.Open(szFileName, TRUE, TRUE, szConnect);
  }
  catch(CDaoException* e){
    #ifdef _DEBUG
     e->ReportError();
    #endif
    e->Delete();
    szLog.Format(_T("Не вдалося відкрити файл \"%s\", можливо він використовуються іншею програмою."), szFileName);
    AddToLog(szLog, TRUE, FALSE, TRUE);
    m_FileList.SetItem(nItem, 0, LVIF_IMAGE, NULL, IML_ERROR, 0, 0, 0);
    m_FileList.SetItemText(nItem, FLC_NOTICE, _T("Не вдалося відкрити, можливо використовуються іншею програмою."));
    return PACK_CANT_OPEN;
  }
  db.Close();
  CString szTmpFile = szFileName;
  szTmpFile += _T(".old");
  CopyFile(szFileName, szTmpFile, FALSE);

  CString szPackedFileName = szFileName;
  szPackedFileName += _T(".cdb");
  if ( FileExists(szPackedFileName) ) {
    DeleteFile(szPackedFileName);
  }
  try {
    szLog.Format(_T("Пакується файл %s..."), szFileName);
    AddToLog(szLog, TRUE, FALSE, FALSE);
    if ( szExt.CompareNoCase("er3")==0 ) {
      MyCompactDatabase(szFileName);
    }
    CDaoWorkspace::CompactDatabase(szFileName, szPackedFileName, dbLangCyrillic, dbVersion30, szConnect);
    fCompactOk = TRUE;
  }
  catch(CDaoException* e){
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    m_FileList.SetItem(nItem, 0, LVIF_IMAGE, NULL, IML_ERROR, 0, 0, 0);
  }
  if ( fCompactOk ) {
    DeleteFile(szTmpFile);
    DeleteFile(szFileName);
    ::MoveFile(szPackedFileName, szFileName);
  }
  else {
    CopyFile(szTmpFile, szFileName, FALSE);
  }
  return PACK_OK;
}
void CZipDBDlg::AddToLog(LPCTSTR sz, BOOL fPar/*=FALSE*/, BOOL fBold/*=FALSE*/, BOOL fRed/*=FALSE*/) {
  m_Info.SetWindowText(sz);
  m_Info.Invalidate();
  PumpMessages();
}


void DeleteFilesFromArchive(CZipArchive& za, int nIndex) {
  CZipFileHeader fh;
  za.GetFileInfo(fh, (WORD)nIndex);

  CString szFile = fh.GetFileName();
  
  CZipWordArray szDelArray;
  int nZiped = za.GetCount();
  for( int i = 0; i < nZiped; i++ ) {
    CZipFileHeader fh;
    za.GetFileInfo(fh, (WORD)i);
    CString szZipFile = fh.GetFileName();
    if ( szZipFile==szFile ) {
      szDelArray.Add( (WORD)i );
    }
  }
  if ( szDelArray.GetSize() ) {
    za.DeleteFiles(szDelArray);
  }
}

BOOL CZipDBDlg::DoZip() {
  CWaitCursor wc;
  int i;

  theDataManager.CloseDatabases();

  for( i = 0; i < m_Files.GetSize(); i++ ) {
    CZipFileInfo zfi = m_Files.GetAt(i);
    AddToLog(zfi.m_szFileName, TRUE, FALSE, FALSE);
  }
  CString szZipArchive, szZipArchiveOld;
  szZipArchive.Format(_T("%seradb.zip"), m_szDBPath);
  szZipArchiveOld = szZipArchive + _T(".old");
  int openMode = CZipArchive::zipCreate;
  if ( FileExists(szZipArchive) ) {
    CWaitCursor wc;
    BOOL fCopied = false;
    if ( g_Shell >= WinNT4 ) {
      HINSTANCE hInst = NULL;
      hInst = LoadLibrary("kernel32.dll");
      if ( hInst ) {
        FCopyFileEx CopyFileEx;
        (FARPROC&)CopyFileEx = GetProcAddress(hInst,"CopyFileExA");
        if ( CopyFileEx ) {
          BOOL bCancel = false;
          // memset(&g_TotalSize, 0, sizeof(g_TotalSize));
          // memset(&g_Transferred, 0, sizeof(g_Transferred));
          CProgressBar bar(_T("Створюється резервна копія архівного файлу..."), 80, 100, true, 2);
          CopyFileEx(szZipArchive, szZipArchiveOld, CopyProgressRoutine, &bar, &bCancel, 0);
          fCopied = true;
        }
        FreeLibrary(hInst);
      }
    }
    if ( false==fCopied ) {
      CopyFile(szZipArchive, szZipArchiveOld, false);
    }
    openMode = CZipArchive::zipOpen;
  }
  CZipArchive za;
  COptions    ZipOptions;
  BOOL berr = 0;

	try {
    za.Open(szZipArchive, openMode, ZipOptions.m_bTdComp ? 1 : 0 );
		berr = 0;
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
	// thrown in the STL version
	catch (CZipException e)	{
		if (e.m_iCause == CZipException::cdirNotFound)
			berr = -1;
		else
			berr = 1;
	}
	catch(...) {
		berr = 1;
	}
  if ( berr != 0 ) {
    za.Close(true);
    return FALSE;
  }
  int nZiped = za.GetCount();
  for( i = 0; i < nZiped; i++ ) {
    CZipFileHeader fh;
    za.GetFileInfo(fh, (WORD)i);
    SetDoZip(&fh, (WORD)i);
  }
  CProgressBar bar(_T("Архівуються файли бази даних..."), 80, m_Files.GetSize(), true, 2);
  for( i = 0 ; i < m_Files.GetSize(); i++ ) {
    bar.StepIt();
    CZipFileInfo zfi = m_Files.GetAt(i);
    if ( zfi.m_fDoZip ) {
      CString szFileName;
      szFileName.Format(_T("%s%s"), m_szDBPath, zfi.m_szFileName);
      SetCurrentItem(i);
      if ( PACK_OK==Pack(szFileName, i) ) {
        if ( zfi.m_ZipIndex != (WORD)-1 ) {
          DeleteFilesFromArchive(za, zfi.m_ZipIndex);
        }
        /************************************** : by VK 28.2.2008 at 1:50:04 PM **\
        if ( zfi.m_ZipIndex != (WORD)-1 )
          za.DeleteFile(zfi.m_ZipIndex);
        \************************************** : by VK 28.2.2008 at 1:50:07 PM **/
        bool fZip = za.AddNewFile(szFileName, zfi.m_szFileName);
        m_FileList.SetItem(i, 0, LVIF_IMAGE, NULL, fZip ? IML_ZIPPED : IML_ERROR, 0, 0, 0);
        m_FileList.SetItemText(i, FLC_NOTICE, fZip ? _T("Успішно заархівований") : _T("Помилка під час архівації") );
        m_FileList.RedrawItems(i, i);
      }
      PeekAndPump();
    }
  } 
  za.Close(false);
  DeleteFile(szZipArchiveOld);
  COleDateTime odt = COleDateTime::GetCurrentTime();
  theApp.WriteProfileBinary(_T("Settings"), "LADate", (LPBYTE)&odt.m_dt, sizeof(odt.m_dt));
  AddToLog(_T("Архівацію закінчено."));
  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CZipDBDlg message handlers
BOOL CZipDBDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  m_FileList.InsertColumn(FLC_FILENAME, _T("Ім'я файлу"), LVCFMT_LEFT, 280);
  m_FileList.InsertColumn(FLC_DATETIME, _T("Дата/час"),   LVCFMT_LEFT, 120);
  m_FileList.InsertColumn(FLC_SIZE,     _T("Розмір"),     LVCFMT_LEFT,  60);
  m_FileList.InsertColumn(FLC_NOTICE,   _T("Примітка"),   LVCFMT_LEFT, 120);

  m_FileList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
  m_ImageList.Create(IDIL_ZIP, 16, 0, RGB(0xFF, 0, 0xFF));
  m_FileList.SetImageList(&m_ImageList, LVSIL_SMALL);

/*
  HRSRC hrsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(IDRTF_EMPTY), "RTF");
  if ( NULL==hrsrc )
    return FALSE;
  
  HGLOBAL hGlobal = ::LoadResource(AfxGetResourceHandle(), hrsrc);
  LPVOID pData = ::LockResource(hGlobal);
  if ( NULL==pData )
    return FALSE;
*/
  CenterWindow();
  RedrawWindow();
  CWaitCursor wc;

  m_szDBPath.Format(_T("%s\\DB\\"), GetModulePath());
/*
  m_szEmptyRTF = (LPCTSTR)pData;
*/
  AddToLog(_T("Готується список файлів до архівування...") );
  PrepareFileList(m_szDBPath, m_szDBPath);
  AddToLog(_T("Список файлів до архівування побудовано...") );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CZipDBDlg::OnYes() {
  if ( FALSE==m_fYesButton ) {
    CRect r1, r2;
    m_btnOk.GetWindowRect(&r1);
    m_btnCancel.GetWindowRect(&r2);
    int xOffset = r2.right - r1.right;
    ScreenToClient(&r1);
    r1.OffsetRect(xOffset, 0);
    SetWindowText(_T("Архівується база даних ПК ЕРАГС"));
    m_btnCancel.ShowWindow(SW_HIDE);
    m_btnOk.MoveWindow(r1.left, r1.top, r1.Width(), r1.Height());
    m_btnOk.EnableWindow(false);
    DoZip();
    m_fYesButton = true;
    m_btnOk.EnableWindow(true);
    m_btnOk.SetWindowText(_T("Закрити"));
  }
  else {
    EndDialog(IDYES);
  }
}

BOOL CZipDBDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
	// TODO: Add your message handler code here and/or call default
  theApp.OnHelp(_T("Zip"));
	return TRUE;
	//return CDialog::OnHelpInfo(pHelpInfo);
}


void ZipIfItsNeed(const CString& szDatabase) {
  COleDateTime odt = COleDateTime::GetCurrentTime();
  if ( szDatabase.GetLength() < 2) {
    return;
  }
  CString szRoot = szDatabase.Left(3);
  if ( szRoot.Left(2)==_T("\\\\") ) { // Don't make it for network
    return;
  }

  if ( DRIVE_FIXED != GetDriveType(szRoot) ) {
    return;
  }

  int nDays = -1;

  DATE* pLADate = NULL;
  UINT nl;
  if ( theApp.GetProfileBinary(_TEXT("Settings"), _TEXT("LADate"), (LPBYTE*)&pLADate, &nl)) {
    COleDateTime laDate(*pLADate);
    COleDateTimeSpan ts = odt - laDate;
    nDays = (int)ts.GetTotalDays();
    delete pLADate;
    if ( 0==nDays ) {
      return;
    }
  }
  int ZipType = theApp.GetProfileInt(_T("Settings"), _T("ZipType"), 1);
  if ( ZipType < 0 || ZipType > 7 ) {
    ZipType = 7;
  }
  switch( ZipType ) {
    case 0  : // Не архивировать
      return;
    case 1  : // Архивировать в понедельник
      if ( 2 == odt.GetDayOfWeek() ) {
        break;
      }
      return;
    case 2  : // Архивировать во вторник
      if ( 3 == odt.GetDayOfWeek() ) {
        break;
      }
      return;
    case 3  : // Архивировать в среду
      if ( 4 == odt.GetDayOfWeek() ) {
        break;
      }
      return;
    case 4  : // Архивировать в четверг
      if ( 5 == odt.GetDayOfWeek() ) {
        break;
      }
      return;
    case 5  : // Архивировать в пятницу
      if ( 6 == odt.GetDayOfWeek() ) {
        break;
      }
      return;
    case 6  : // Архивировать в субботу
      if ( 7 == odt.GetDayOfWeek() ) {
        break;
      }
      return;
    case 7  : // Архивировать каждый день
    default :
      break;
  }
/*
  if ( nDays != -1 ) {
    if ( 0 < nDays && nDays < 7 ) {
      return;
    }
  }
*/
  CString szDays, szMsg;
  if ( 5 < nDays && nDays < 21 ) {
    szDays = _T("днів");
  }
  else {
    switch( nDays % 10 ) {
      case 1:                 szDays = _T("день"); break;
      case 2: case 3: case 4: szDays = _T("дні");  break;
      default:                szDays = _T("днів"); break;
    }
  }
  if ( -1 == nDays ) {
    szMsg = _T("Увага! База даних ще не архівувалась.");
  }
  else {
    szMsg.Format( _T("Увага! База даних не архівувалась %d %s."), nDays, szDays);
  }
  if ( YNDlg(NULL, szMsg, _T("Заархівувати базу даних зараз?")) ) {
    CZipDBDlg dlg(NULL);
    dlg.DoModal();
  }
}