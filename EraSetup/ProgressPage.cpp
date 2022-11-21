// ProgressPage.cpp : implementation file
//

#include "stdafx.h"
#include "EraSetup.h"
#include "ProgressPage.h"
#include "Shell.h"

#include <direct.h>

#include "Registry.h"

#include "..\ZipArchive\ZipArchive.h"
#include "..\ZipArchive\Options.h"

#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PROGRESS_MAX  1000

#define LC_TEMPLATE   0
#define LC_FILENAME   1

void DeleteFileTree(const CString& szFolder);

BOOL g_fSuccessful = FALSE;

CString GetSectionKey(const char* pKey) {
  CString sRet = _T("");
  while(*pKey && *pKey != '=')
    sRet += *pKey++;
  return sRet;
}

ULONG GetFolderSize(LPCTSTR szFolderPath, ULONG& ulFileCount, BOOL blnSubFolder) {
  WIN32_FIND_DATA Win32FindData;
  HFILE hFindFile;
  BOOL blnFind = TRUE;
  CString strFileName;
  CString strFolderPath(szFolderPath);
  ULONG ulFileSize = 0;
    
  if ( strFolderPath.Right(1).Compare("\\") )
      strFolderPath += "\\";
    
  hFindFile = (HFILE)FindFirstFile(strFolderPath + "*.*", &Win32FindData);
    
  while ( blnFind ) {
    strFileName.Format("%s", Win32FindData.cFileName);
        
    if ( strFileName.Compare(".")!=0 && strFileName.Compare("..")!=0 ) {
      if ( Win32FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
        if ( blnSubFolder )
          ulFileSize += GetFolderSize(strFolderPath + strFileName + "\\", ulFileCount, blnSubFolder);
      }
      else {
        ulFileSize += Win32FindData.nFileSizeLow;
        ulFileCount++;
      }
    }

    blnFind = FindNextFile((void*)hFindFile, &Win32FindData);
  }
    
  FindClose((void *)hFindFile);
  return ulFileSize;
}

TemplateArray*  g_pCurrentTemplateArray = NULL;
static int CALLBACK TempListCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
   // lParamSort contains a pointer to the list view control.
   // The lParam of an item is just its index.
  ASSERT(lParamSort!=0);
  TEMPLATE& t1 = g_pCurrentTemplateArray->GetAt((int)lParam1);
  TEMPLATE& t2 = g_pCurrentTemplateArray->GetAt((int)lParam2);
  int Ascending = (lParamSort > 0) ? 1 : -1;
  switch ( abs((int)lParamSort)-1 )  {
    case LC_TEMPLATE  : return Ascending*strcmp(t1.szUkrName , t2.szUkrName );
    case LC_FILENAME  : return Ascending*strcmp(t1.szFileName, t2.szFileName);
  }
  return 0;
}


BOOL CProgressPage::Overwrite(LPCTSTR szFileName, int& nIndex) {
  nIndex = -1;
  for( int i(0); i < m_AllTemlates.GetSize(); i++ ) {
    TEMPLATE& t = m_AllTemlates.GetAt(i);
    if ( strcmpi(t.szFileName, szFileName)==0 ) {
      nIndex = i;
      return t.fOverwrite;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////
// CProgressPage dialog
CProgressPage::CProgressPage(CWnd* pParent /*=NULL*/)
              :CNewWizPage(CProgressPage::IDD, pParent) {
	//{{AFX_DATA_INIT(CProgressPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_uTab = 0;
  m_nSortBy = LC_TEMPLATE+1;
}

void CProgressPage::DoDataExchange(CDataExchange* pDX) {
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressPage)
  DDX_Control(pDX, IDC_TAB, m_Tab);
	DDX_Control(pDX, IDC_LIST1, m_TmplList);
	DDX_Control(pDX, IDC_DESTFILENAME, m_wndDestFile);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressPage, CNewWizPage)
	//{{AFX_MSG_MAP(CProgressPage)
  ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
  ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnListColumnclick)
	ON_BN_CLICKED(IDC_SELECT_ALL, OnSelectAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CProgressPage::CopyFolderStructure(LPCTSTR szFrom, LPCTSTR szTo, ULONG& nFile) {
  CFileFind finder;
  CString sFrom;
  sFrom.Format(_T("%s\\*.*"), szFrom );

  BOOL bWorking = finder.FindFile(sFrom);
  while( bWorking ) {
    BOOL fOverwrite = TRUE;
    bWorking = finder.FindNextFile();

    if (finder.IsDots())
         continue;

    CString sFile = finder.GetFileName();
    if ( finder.IsDirectory() ) {

      CString sFromDir, sToDir;
      sFromDir.Format(_T("%s\\%s"), szFrom, sFile );
      sToDir.Format(_T("%s\\%s"), szTo, sFile );

      if ( FALSE==theApp.m_fServer ) {
        CString s = sFromDir;
        s.MakeUpper();
        if ( s.Find("\\DB")>=0 )
          continue;
      }

      _mkdir(sToDir);
      CopyFolderStructure(sFromDir, sToDir, nFile);
    }
    else {
      int nIndex = -1;
      /*
      if ( false==theApp.m_fInstallLaws && sFile.CompareNoCase("Laws.exe")==0 ) {
        continue;
      }
      */
      CString sSourceFile, sDestFile;
      sSourceFile.Format(_T("%s\\%s"), szFrom, sFile);
      sDestFile.Format(_T("%s\\%s"), szTo, sFile);

      m_wndDestFile.SetWindowText(sDestFile);
      if ( FileExists(sDestFile) )
        fOverwrite = Overwrite(sFile, nIndex);
      m_Progress.SetPos(nFile++);

      if ( FALSE==theApp.m_fServer ) {
        CString s = sSourceFile;
        s.MakeUpper();
        if ( s.Find("\\DB\\")>=0 )
          continue;
      }
      else {
        CString s = sSourceFile;
        s.MakeUpper();
        if ( s.Find("\\DB\\HELPERS.MDB")>=0 ) {
          s = sDestFile;
          if ( FileExists(sDestFile) ) {
            CString sHelperOld;
            sHelperOld.Format(_T("%s.old"), sDestFile);
            if ( FALSE==FileExists(sHelperOld) ) {
              CFile::Rename(sDestFile, sHelperOld);
            }
          }
        }
      }
  
      if ( fOverwrite ) {
        if ( nIndex >= 0 ) {
          CString szDestPath = GetFilePath(sDestFile);
          CString szDestPathUpper = szDestPath;
          szDestPathUpper.MakeUpper();
          if ( szDestPathUpper.Find(_T("\\TEMPLATES")) > 0 ) {
            CString szSavePath;
            szSavePath.Format(_T("%s.sav"), szDestPath);
            _mkdir(szSavePath);
            CString szExistingTepmlate = sDestFile;
            CString szSavedTepmlate;;
            szSavedTepmlate.Format(_T("%s\\%s"), szSavePath, GetFileName(sDestFile));

            BOOL fMove = true;
            WIN32_FIND_DATA fd1, fd2;
            if ( FileExists(szExistingTepmlate, &fd1) && FileExists(szSavedTepmlate, &fd2) ) {
              if ( fd1.nFileSizeLow == fd2.nFileSizeLow &&
                   memcmp(&fd1.ftLastWriteTime, &fd2.ftLastWriteTime, sizeof(fd1.ftLastWriteTime))==0 ) {
                fMove = false;
              }
            }
            if ( fMove ) {
              MoveFileEx(szExistingTepmlate, szSavedTepmlate, MOVEFILE_REPLACE_EXISTING);
            }
          }
        }
        CopyFile(sSourceFile, sDestFile, FALSE);
      }
      else {
        CopyFile(sSourceFile, sDestFile, TRUE );
      }
      SetFileAttributes(sDestFile, FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL );
    }
  }
}


void CProgressPage::FillTemplateArray(TemplateArray* pTArray, LPCTSTR szFilename, LPCTSTR szSection) {
  const int BUF_SIZE=0x7000;
  char* pBuffer = new char[BUF_SIZE+2];
  ::GetPrivateProfileSection(szSection, pBuffer, BUF_SIZE, szFilename);
  char* pKey = pBuffer;
  while( *pKey ) {
    TEMPLATE t;
    try {
      t.szFileName = GetSectionKey(pKey);
      ::GetPrivateProfileString(szSection, t.szFileName, _T(""), t.szUkrName.GetBuffer(128), 128, szFilename);
      t.szUkrName.ReleaseBuffer();
      pTArray->Add(t);
    }
    catch(...) {
      t.szFileName = GetSectionKey(pKey);
      t.szUkrName = _T("Помилка в файлі описання шаблонів");
    }


    pKey += strlen(pKey)+1;
  }
  delete pBuffer;
}

int CProgressPage::GetTArrayIndex(TemplateArray* pTArray, LPCTSTR szFilename) {
  for( int i(0); i < pTArray->GetSize(); i++ ) {
    TEMPLATE& t = pTArray->GetAt(i);
    if ( 0==t.szFileName.CompareNoCase(szFilename) ) {
      return i;
    }
  }
  return -1;
}
void CProgressPage::FillAllTemplates() {
  TemplateArray* pTArrays[7] = { &m_BirthTemplates , &m_MarriageTemplates, &m_DivorceTemplates,
                                 &m_ChangeTemplates, &m_DeathTemlates    , &m_EnvelopeTemlates,
                                 &m_OtherTemlates
                                };

  CString szMask;
  szMask.Format(_T("%s\\*.*"), m_sTemplatePath);
  CFileFind finder;
  BOOL bWorking = finder.FindFile(szMask);
  while (bWorking) {
    bWorking = finder.FindNextFile();
    if (finder.IsDots())
         continue;
    if ( finder.IsDirectory() )
      continue;
    CString szFilename = finder.GetFileName();
    BOOL bFound = false;
    for( int i(0); i < sizeof(pTArrays)/sizeof(pTArrays[0]); i++ ) {
      int nFound = GetTArrayIndex(pTArrays[i], szFilename);
      if ( nFound >= 0 ) {
        TEMPLATE t = pTArrays[i]->GetAt(nFound);
        m_AllTemlates.Add(t);
        bFound = true;
        break;
      }
    }
    if ( false==bFound ) {
      TEMPLATE t;
      t.szFileName = szFilename;
      t.szUkrName = _T("Невідомий файл шаблону, або файл, що не використувується поточною версією ПК ЕРАГС");
      m_AllTemlates.Add(t);
    }
  }
}

void CProgressPage::SetTemplatesFor(UINT uTab) {

  int nItems = m_TmplList.GetItemCount();
  for( int i(0); i < nItems; i++ ) {
    CString szFileName = m_TmplList.GetItemText(i, LC_FILENAME);
    int nIndex = GetTArrayIndex(&m_AllTemlates, szFileName);
    TEMPLATE t = m_AllTemlates.GetAt(nIndex);
    t.fOverwrite = m_TmplList.GetCheck(i);
    m_AllTemlates.SetAt(nIndex, t);
  }

  TemplateArray* pTArray = NULL;
  LPCTSTR szOff = NULL;
  switch(uTab) {
    case 0:  szOff = _T("Народження");       pTArray = &m_BirthTemplates;     break;
    case 1:  szOff = _T("Одруження");        pTArray = &m_MarriageTemplates;  break;
    case 2:  szOff = _T("Розірвання Шлюбу"); pTArray = &m_DivorceTemplates;   break;
    case 3:  szOff = _T("Зміни");            pTArray = &m_ChangeTemplates;    break;
    case 4:  szOff = _T("Смерті");           pTArray = &m_DeathTemlates;      break;
    case 5:  szOff = _T("Конверти");         pTArray = &m_EnvelopeTemlates;   break;
    case 6:  szOff = _T("Усі шаблони");      pTArray = &m_AllTemlates;        break;
  }
  g_pCurrentTemplateArray = pTArray;
  if (pTArray) {
    m_TmplList.DeleteAllItems();
    for( int i(0); i < pTArray->GetSize(); i++ ) {
      TEMPLATE t = pTArray->GetAt(i);
      int nItem = m_TmplList.InsertItem(i, t.szUkrName);
      m_TmplList.SetItemText(nItem, 1, t.szFileName);
      m_TmplList.SetItemData(nItem, (DWORD)i);
      int nIndex = GetTArrayIndex(&m_AllTemlates, t.szFileName);
      if ( nIndex >= 0 ) {
        t = m_AllTemlates.GetAt(nIndex);
        m_TmplList.SetCheck(i, t.fOverwrite);
      }
    }
    m_TmplList.SortItems(TempListCompareProc, (LPARAM)m_nSortBy);
  }
  m_uTab = uTab;
}

/////////////////////////////////////////////////////////////////////////////
// CProgressPage message handlers
BOOL CProgressPage::OnInitDialog() {
	CNewWizPage::OnInitDialog();

	// TODO: Add extra initialization here
  CWaitCursor wc;

  m_Tab.InsertItem(0, _T("Народження"));
  m_Tab.InsertItem(1, _T("Одруження"));
  m_Tab.InsertItem(2, _T("Розірвання шлюбів"));
  m_Tab.InsertItem(3, _T("Зміни"));
  m_Tab.InsertItem(4, _T("Смерті"));
  m_Tab.InsertItem(5, _T("Конверти"));
  m_Tab.InsertItem(6, _T("Усі шаблони"));

  CString szTeplateInfo;
  szTeplateInfo.Format(_T("%s\\Templates.info"), theApp.m_szUnzipFolder);

  m_sTemplatePath.Format(_T("%s\\Templates"), theApp.m_szUnzipFolder);

  CheckDlgButton(IDC_SAVE, true);

  FillTemplateArray(&m_BirthTemplates   , szTeplateInfo, _T("Birth"));
  FillTemplateArray(&m_MarriageTemplates, szTeplateInfo, _T("Marriage"));
  FillTemplateArray(&m_DivorceTemplates , szTeplateInfo, _T("Divorce"));
  FillTemplateArray(&m_ChangeTemplates  , szTeplateInfo, _T("Change"));
  FillTemplateArray(&m_DeathTemlates    , szTeplateInfo, _T("Death"));
  FillTemplateArray(&m_EnvelopeTemlates , szTeplateInfo, _T("Envelope"));
  FillTemplateArray(&m_OtherTemlates    , szTeplateInfo, _T("Other"));
  FillTemplateArray(&m_OverwriteTemlates, szTeplateInfo, _T("Overwrite"));

  FillAllTemplates();
  for( int i(0); i < m_AllTemlates.GetSize(); i++ ) {
    TEMPLATE t = m_AllTemlates.GetAt(i);
    int OverwriteIndex = GetTArrayIndex(&m_OverwriteTemlates, t.szFileName);
    if ( OverwriteIndex >= 0 ) {
      t.fOverwrite = t.fDefault = true;
      m_AllTemlates.SetAt(i, t);
    }
  }

  m_Progress.SetRange(0, PROGRESS_MAX);

  m_wndDestFile.ShowWindow(SW_HIDE);
  m_Progress.ShowWindow(SW_HIDE);

  m_TmplList.SetExtendedStyle(m_TmplList.GetExtendedStyle()|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES|LVS_EX_TRACKSELECT);

  m_TmplList.InsertColumn(LC_TEMPLATE, _T("Переписати шаблон") , LVCFMT_LEFT, 340);
  m_TmplList.InsertColumn(LC_FILENAME, _T("Ім'я файла")        , LVCFMT_LEFT, 120);

  SetTemplatesFor(6);
  m_Tab.SetCurSel(6);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProgressPage::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) {
  int nItem = m_Tab.GetCurSel();
  if ( nItem >= 0 ) {
    SetTemplatesFor(nItem);
  }

	*pResult = 0;
}

void CProgressPage::OnListColumnclick(NMHDR* pNMHDR, LRESULT* pResult) {
  LPNMLISTVIEW pNMListView = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
  int nSortBy = pNMListView->iSubItem + 1;
  if ( nSortBy != m_nSortBy ) {
    m_nSortBy = nSortBy;
  }
  else {
    m_nSortBy = -m_nSortBy;
  }
  m_TmplList.SortItems(TempListCompareProc, (LPARAM)m_nSortBy);
  *pResult = 0;
}

BOOL CProgressPage::OnWizardFinish() {
  CWaitCursor wc;

  theApp.m_pMainWnd->GetDlgItem(ID_WIZBACK)->EnableWindow(false);
  theApp.m_pMainWnd->GetDlgItem(ID_WIZFINISH)->EnableWindow(false);

  int nItems = m_TmplList.GetItemCount();
  for( int i(0); i < nItems; i++ ) {
    CString szFileName = m_TmplList.GetItemText(i, LC_FILENAME);
    int nIndex = GetTArrayIndex(&m_AllTemlates, szFileName);
    TEMPLATE t = m_AllTemlates.GetAt(nIndex);
    t.fOverwrite = m_TmplList.GetCheck(i);
    m_AllTemlates.SetAt(nIndex, t);
  }

  m_Progress.SetRange(0, PROGRESS_MAX);

	// TODO: Add extra initialization here
  CString szOldFolder;
  CString szSourcePath = theApp.m_szUnzipFolder;

  _mkdir( theApp.m_sEraPath );
  ULONG nFile = 1, nFiles = 0, nFolderSize = 0;

   // Удаляем старые папки помощи и помощника вместе с содержим
  szOldFolder.Format(_T("%s\\HTML"), theApp.m_sEraPath);
  DeleteFileTree(szOldFolder);
  szOldFolder.Format(_T("%s\\Help"), theApp.m_sEraPath);
  DeleteFileTree(szOldFolder);

  nFolderSize = GetFolderSize(szSourcePath, nFiles, TRUE);
  m_wndDestFile.ShowWindow(SW_SHOW);
  m_Progress.SetRange(0, (short)nFiles);
  m_Progress.ShowWindow(SW_SHOW);
  CopyFolderStructure(szSourcePath, theApp.m_sEraPath, nFile);

/*
  if ( theApp.m_fInstallLaws ) {
    CString szSourceZip, szUnzipFolder, szFilename;
    szSourceZip.Format(_T("%s\\DATA\\laws.z"), GetModulePath());
    szUnzipFolder.Format(_T("%s\\Laws"), theApp.m_sEraPath);
    CZipArchive zip;
    int nCount = 0;
    int berr = 0;
    try {
      zip.Open(szSourceZip, CZipArchive::zipOpenReadOnly);
      nCount = zip.GetCount();
      m_Progress.SetRange32(0, nCount);
      for( int i = 0; i < nCount; i++ ) {
        CZipFileHeader fh;
        zip.GetFileInfo(fh, (WORD)i);
        szFilename.Format(_T("%s\\%s"), szUnzipFolder, fh.GetFileName());
        m_wndDestFile.SetWindowText(szFilename);
        zip.ExtractFile((WORD)i, szUnzipFolder);
        m_Progress.OffsetPos(1);
      }
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
  }
*/
  CString szDesktopPath, szEragsLink, szEragsGroup, sGroupLink, sUninstallExe, sUninstallLink;
  
  // SHGetSpecialFolderPath(NULL, szDesktopPath.GetBuffer(MAX_PATH+1), CSIDL_DESKTOP, FALSE);
  SHGetSpecialFolderPath(NULL, szDesktopPath.GetBuffer(MAX_PATH+1), CSIDL_COMMON_DESKTOPDIRECTORY, FALSE);
  szDesktopPath.ReleaseBuffer();

  szEragsLink.Format(_T("%s\\%s.lnk"), szDesktopPath, theApp.m_sEraGroup);
  szEragsGroup.Format(_T("%s\\ПК ЕРАГС"), theApp.m_sEraPath);
  _mkdir(szEragsGroup);
  sGroupLink.Format(_T("%s\\Erags.exe"), theApp.m_sEraPath);

  CreateLink(szEragsGroup, szEragsLink, _T("Програмний комплекс \"ЕРАГС\""), sGroupLink, 2);
  CString sLink, sDoc;

  CString sEragsExe, sEragsLink, sEraABCExe, sEraABCLink, sEra2XmlExe, sEra2XmlLink, sHelp, sHelpLink;
  sEragsLink.Format(_T("%s\\ЕРАГС.lnk"), szEragsGroup);
  sEragsExe.Format(_T("%s\\Erags.exe"), theApp.m_sEraPath);
  CreateLink(sEragsExe, sEragsLink, _T("Erags.exe"), sEragsExe, 0);

  sEraABCLink.Format(_T("%s\\ЕраАБВ.lnk"), szEragsGroup);
  sEraABCExe.Format(_T("%s\\EraABC.exe"), theApp.m_sEraPath);
  CreateLink(sEraABCExe, sEraABCLink, _T("EraABC.exe"), sEraABCExe, 0);


  sEra2XmlLink.Format(_T("%s\\Era2Xml.lnk"), szEragsGroup);
  sEra2XmlExe.Format(_T("%s\\Era2Xml.exe"), theApp.m_sEraPath);
  CreateLink(sEra2XmlExe, sEra2XmlLink, _T("Era2Xml.exe"), sEra2XmlExe, 0);
  
  if ( theApp.m_fServer ) {
    CString sEraWiz, sEraWizLink, sWizDLL;
    sEraWizLink.Format(_T("%s\\Майстер установки.lnk"), szEragsGroup);
    sEraWiz.Format(_T("%s\\Erags.exe"), theApp.m_sEraPath);
    sWizDLL.Format(_T("%s\\EraWiz.dll"), theApp.m_sEraPath);
    CreateLink(sEraWiz, sEraWizLink, _T("Майстер установки"), sWizDLL, 0, _T("-wizard"));
  }

/*
  if ( theApp.m_fInstallLaws ) {
    CString sLawsExe, sLawsLink;
    sLawsLink.Format(_T("%s\\Юридичний довідник.lnk"), szEragsGroup);
    sLawsExe.Format(_T("%s\\Laws.exe"), theApp.m_sEraPath);
    CreateLink(sLawsExe, sLawsLink, _T("Юридичний довідник"), sLawsExe, 0);
  }
  */

  sHelp.Format(_T("%s\\Help\\Erags_r.chm"), theApp.m_sEraPath);
  sHelpLink.Format(_T("%s\\Документация на русском.lnk"), szEragsGroup);
  CreateLink(sHelp, sHelpLink, _T("Документация на русском"), NULL, 0);

  sHelp.Format(_T("%s\\Help\\Erags_u.chm"), theApp.m_sEraPath);
  sHelpLink.Format(_T("%s\\Документацiя українською.lnk"), szEragsGroup);
  CreateLink(sHelp, sHelpLink, _T("Документацiя українською"), NULL, 0);

  sEragsLink.Format(_T("%s\\ЕРАГС.lnk"), szDesktopPath);
  sEragsExe.Format(_T("%s\\Erags.exe"), theApp.m_sEraPath);
  if ( FileExists(sEragsLink) ) {
    DeleteFile(sEragsLink);
  }
  CreateLink(sEragsExe, sEragsLink, _T("Erags.exe"), sEragsExe, 0);

  sUninstallExe.Format(_T("%s\\Uninstall.exe"), theApp.m_sEraPath);
  sUninstallLink.Format(_T("%s\\Деінсталяція ПК ЕРАГС.lnk"), szEragsGroup);
  CreateLink(sUninstallExe, sUninstallLink, _T("Деінсталяція ПК ЕРАГС"), sUninstallExe, 0);

  
  CRegistry Reg;
  Reg.m_hRootKey = HKEY_LOCAL_MACHINE;

  if ( false==Reg.WriteProfileString(_T("Settings"), _T("InstallLocation"), theApp.m_sEraPath) ) {
    Reg.m_hRootKey = HKEY_CURRENT_USER;
    Reg.WriteProfileString(_T("Settings"), _T("InstallLocation"), theApp.m_sEraPath);
  }
  HKEY hUninstallKey;
  DWORD dwResult;
  dwResult = ::RegCreateKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Erags"), &hUninstallKey);
  if ( ERROR_SUCCESS == dwResult ) {
    CString s;
    s.Format(_T("%s\\Erags.exe"), theApp.m_sEraPath);
    ::RegSetValueEx(hUninstallKey, _T("DisplayIcon"), 0, REG_EXPAND_SZ, (LPBYTE)(LPCTSTR)s, s.GetLength()+1);
    ::RegSetValueEx(hUninstallKey, _T("DisplayName"), 0, REG_EXPAND_SZ, (LPBYTE)_T("ПК ЕРАГС"), 9);
    s.Format(_T("%s\\Uninstall.exe"), theApp.m_sEraPath);
    ::RegSetValueEx(hUninstallKey, _T("UninstallString"), 0, REG_EXPAND_SZ, (LPBYTE)(LPCTSTR)s, s.GetLength()+1);
    ::RegCloseKey(hUninstallKey);

  }

  ShellExecute(NULL, _T("open"), szEragsLink, NULL, NULL, SW_SHOWNORMAL);

  g_fSuccessful = TRUE;
  return TRUE;
}

/*
void CProgressPage::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if ( pNMListView->iItem >= 0 && pNMListView->uNewState != 0 ) {
    sfi[pNMListView->iItem].fNewOverwrite = m_TmplList.GetCheck(pNMListView->iItem);
  }
	*pResult = 0;
}
*/

void CProgressPage::OnSelectAll() {
	// TODO: Add your control notification handler code here
  int nChecked = IsDlgButtonChecked(IDC_SELECT_ALL);
/*
  for( int i(0); i < m_AllTemlates.GetSize(); i++ ) {
    TEMPLATE& t = m_AllTemlates.GetAt(i);
    if ( nCheck ) {
      t.fOverwrite = true;
    }
    else {
      t.fOverwrite = t.fDefault;
    }
    m_AllTemlates.SetAt(i, t);
  }

  int nItem = m_Tab.GetCurSel();
  if ( nItem >= 0 ) {
    SetTemplatesFor(nItem);
  }
*/
  if ( nChecked ) {
    int nItems = m_TmplList.GetItemCount();
    for( int i(0); i < nItems; i++ ) {
      m_TmplList.SetCheck(i, true);
    }
  }
  else {

    int nItems = m_TmplList.GetItemCount();
    for( int i(0); i < nItems; i++ ) {
      CString szFileName = m_TmplList.GetItemText(i, LC_FILENAME);
      int nIndex = GetTArrayIndex(&m_AllTemlates, szFileName);
      TEMPLATE& t = m_AllTemlates.GetAt(nIndex);
      m_TmplList.SetCheck(i, t.fDefault);
    }
  }
    
/*    
    int nItem = m_Tab.GetCurSel();
    if ( nItem >= 0 ) {
      SetTemplatesFor(nItem);
    }
*/
}
