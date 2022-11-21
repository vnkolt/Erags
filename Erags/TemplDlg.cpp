// TemplDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "TemplDlg.h"

#include <direct.h>

#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"

#include "..\ZipArchive\ZipArchive.h"
#include "..\ZipArchive\Options.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TRANS_CLR RGB(255,0,255)

CString GetSectionKey(const char* pKey);

#define SO_NONE    0
#define SO_ASC     1
#define SO_DESC    2

int TemplSortOrder[2] = { SO_NONE, SO_NONE };

int CALLBACK TemplListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  CTemplDlg* pDlg = (CTemplDlg*)lParamSort;

  TEMPLATE t1 = pDlg->m_pCurArray->GetAt(lParam1);
  TEMPLATE t2 = pDlg->m_pCurArray->GetAt(lParam2);

  int iResult(0);

  switch(pDlg->m_nSortColumn) {
    case 0: // template name
      iResult = CyrCompare(t1.szUkrName, t2.szUkrName);
      break;
    case 1: // file name
      iResult = stricmp(t1.szFileName, t2.szFileName);
      break;
  }
  if ( TemplSortOrder[pDlg->m_nSortColumn]==SO_DESC )
    return -iResult;
  return iResult;

}


/////////////////////////////////////////////////////////////////////////////
// CTemplDlg dialog
CTemplDlg::CTemplDlg(UINT idTemplate, CWnd* pParent /*=NULL*/)
         :CDialogEx(CTemplDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CTemplDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_idTemplate = idTemplate;
  m_uForm = -1;
  m_nSortColumn = 0;
  m_Action = m_ActionImageID = 0;
  m_sTemplatePath = m_sTemplateSavedPath = theApp.m_sTemplatePath;
  m_sTemplateSavedPath += _T(".sav");
  m_pCurArray = NULL;
}

void CTemplDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTemplDlg)
  DDX_Control(pDX, IDC_TAB, m_Tab);
	DDX_Control(pDX, IDC_TEMPL_LIST, m_TmplList);
	//}}AFX_DATA_MAP
  for( int i(0); i < 8; i++ ) {
    DDX_Control(pDX, IDC_RADIO1+i, m_rbRadio[i]);
  }
}

BEGIN_MESSAGE_MAP(CTemplDlg, CDialogEx)
	//{{AFX_MSG_MAP(CTemplDlg)
	ON_BN_CLICKED(IDC_RADIO1, OnRadioSaveOpen)
	ON_BN_CLICKED(IDC_RADIO2, OnRadioOpenOnly)
	ON_BN_CLICKED(IDC_RADIO3, OnRadioRestoreOpen)
	ON_BN_CLICKED(IDC_RADIO4, OnRadioRestore)
  ON_BN_CLICKED(IDC_RADIO5, OnRadioRestoreFromZip)
	ON_BN_CLICKED(IDC_RADIO6, OnRadioSaveImportOpen)
	ON_BN_CLICKED(IDC_RADIO7, OnRadioImportOpen)
	ON_BN_CLICKED(IDC_RADIO8, OnRadioImport)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_NOTIFY(NM_CLICK, IDC_TEMPL_LIST, OnClickTemplList)
  ON_NOTIFY(LVN_COLUMNCLICK, IDC_TEMPL_LIST, OnColumnClickTemplList)
  ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

void CTemplDlg::FillTemplateArray(TemplateArray* pTArray, LPCTSTR szFilename, LPCTSTR szSection) {
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

int CTemplDlg::GetTArrayIndex(TemplateArray* pTArray, LPCTSTR szFilename) {
  for( int i(0); i < pTArray->GetSize(); i++ ) {
    TEMPLATE t = pTArray->GetAt(i);
    if ( 0==t.szFileName.CompareNoCase(szFilename) ) {
      return i;
    }
  }
  return -1;
}
void CTemplDlg::FillAllTemplates() {
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

/////////////////////////////////////////////////////////////////////////////
// CTemplDlg message handlers
BOOL CTemplDlg::OnInitDialog()  {

	CDialogEx::OnInitDialog();

  ListView_SetExtendedListViewStyle(m_TmplList.m_hWnd, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);

  m_TmplList.InsertColumn(0, _T("Назва шаблону"),      LVCFMT_LEFT, 440);
  m_TmplList.InsertColumn(1, _T("Ім'я файла шаблону"), LVCFMT_LEFT, 120);

  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    for( int i(0); i < 8; i++ ) {
      m_rbRadio[i].SetRadioImageList(&m_RadioIL);
      m_rbRadio[i].SetRadio(IDC_RADIO1, IDC_RADIO8);
    }
  }

  m_Tab.InsertItem(0, _T("Народження"));
  m_Tab.InsertItem(1, _T("Одруження"));
  m_Tab.InsertItem(2, _T("Розірвання шлюбів"));
  m_Tab.InsertItem(3, _T("Зміни"));
  m_Tab.InsertItem(4, _T("Смерті"));
  m_Tab.InsertItem(5, _T("Конверти"));
  m_Tab.InsertItem(6, _T("Усі шаблони"));

  CString szInfoFile;
  szInfoFile.Format(_T("%s\\Templates.info"), GetModulePath());
  FillTemplateArray(&m_BirthTemplates   , szInfoFile, _T("Birth"));
  FillTemplateArray(&m_MarriageTemplates, szInfoFile, _T("Marriage"));
  FillTemplateArray(&m_DivorceTemplates , szInfoFile, _T("Divorce"));
  FillTemplateArray(&m_ChangeTemplates  , szInfoFile, _T("Change"));
  FillTemplateArray(&m_DeathTemlates    , szInfoFile, _T("Death"));
  FillTemplateArray(&m_EnvelopeTemlates , szInfoFile, _T("Envelope"));
  FillTemplateArray(&m_OtherTemlates    , szInfoFile, _T("Other"));

  FillAllTemplates();
	
	// TODO: Add extra initialization here
  UINT uForm = 0;
  switch(m_idTemplate) {
    case IDD_FORM_BIRTH:    uForm = 0;  break;
    case IDD_FORM_MARRIAGE: uForm = 1;  break;
    case IDD_FORM_DIVORCE:  uForm = 2;  break;
    case IDD_FORM_CHANGE:   uForm = 3;  break;
    case IDD_FORM_DEATH:    uForm = 4;  break;
    case IDD_RLIST:         uForm = 5;  break;
  }
  CheckRadioButton(IDC_RADIO1, IDC_RADIO8, IDC_RADIO1);
  OnRadioSaveOpen();


  SetTemplatesFor(uForm);
  m_Tab.SetCurSel(uForm);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTemplDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) {
  int nItem = m_Tab.GetCurSel();
  if ( nItem >= 0 ) {
    SetTemplatesFor(nItem);
  }

	*pResult = 0;
}
void CTemplDlg::SetTemplatesFor(UINT uForm) {
  if ( m_uForm == uForm )
    return;

  GetDlgItem(IDYES)->EnableWindow(FALSE);  

  LPCTSTR szOff = NULL;
  switch(uForm) {
    case 0:  szOff = _T("Народження");       m_pCurArray = &m_BirthTemplates;     break;
    case 1:  szOff = _T("Одруження");        m_pCurArray = &m_MarriageTemplates;  break;
    case 2:  szOff = _T("Розірвання Шлюбу"); m_pCurArray = &m_DivorceTemplates;   break;
    case 3:  szOff = _T("Зміни");            m_pCurArray = &m_ChangeTemplates;    break;
    case 4:  szOff = _T("Смерті");           m_pCurArray = &m_DeathTemlates;      break;
    case 5:  szOff = _T("Конверти");         m_pCurArray = &m_EnvelopeTemlates;   break;
    case 6:  szOff = _T("Усі шаблони");      m_pCurArray = &m_AllTemlates;        break;
  }
  CString sOffTitle;
  if ( uForm <= 5 ) {
    sOffTitle.Format(_T("Шаблони для реєстрації %s."), szOff);
  }
  else {
    sOffTitle = _T("Шаблони друку конвертів.");
  }
  if (m_pCurArray) {
    m_TmplList.DeleteAllItems();
    for( int i(0); i < m_pCurArray->GetSize(); i++ ) {
      TEMPLATE t = m_pCurArray->GetAt(i);
      m_TmplList.InsertItem(i, t.szUkrName);
      m_TmplList.SetItemText(i, 1, t.szFileName);
      m_TmplList.SetItemData(i, (DWORD)i);
      if ( t.szUkrName.Find(_T("Невідомий"))>=0 ) {
        m_TmplList.SetItemTxtColor(i, 0, RGB(255,0,0));
        m_TmplList.SetItemStyle(i, 0, LIS_TXTCOLOR|LIS_BOLD);
      }
    }
  }
  m_uForm = uForm;
}
 
void CTemplDlg::OnActionRadio() {
  int nItem = m_TmplList.GetNextItem(-1, LVNI_ALL|LVNI_SELECTED);
  if ( nItem>= 0)
    GetDlgItem(IDYES)->EnableWindow(TRUE);
  if (m_ActionImageID) {
    CWnd* pWnd = GetDlgItem(IDC_ACTIMAGE);
    //CBitmap bitmap;
    m_ActionBitmap.DeleteObject();// .Detach();
    if ( m_ActionBitmap.LoadBitmap(m_ActionImageID) ) 
      pWnd->SendMessage(STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)(HBITMAP)m_ActionBitmap);
  }
}
void CTemplDlg::OnRadioSaveOpen() {
  m_Action = ACTION_SAVE_OPEN;
  m_ActionImageID = IDB_ACTIONS1;
  OnActionRadio();
}
void CTemplDlg::OnRadioOpenOnly() {
  m_Action = ACTION_OPEN_ONLY;
  m_ActionImageID = IDB_ACTIONS2;
  OnActionRadio();
}
void CTemplDlg::OnRadioRestoreOpen() {
  m_Action = ACTION_RESTORE_OPEN;
  m_ActionImageID = IDB_ACTIONS3;
  OnActionRadio();
}
void CTemplDlg::OnRadioRestore() {
  m_Action = ACTION_RESTORE;
  m_ActionImageID = IDB_ACTIONS4;
  GetDlgItem(IDYES)->EnableWindow(TRUE);
  OnActionRadio();
}
void CTemplDlg::OnRadioRestoreFromZip() {
  m_Action = ACTION_RESTORE_FROM_ZIP;
  m_ActionImageID = IDB_ACTIONS5;
  GetDlgItem(IDYES)->EnableWindow(TRUE);
  OnActionRadio();
}

void CTemplDlg::OnRadioSaveImportOpen() {
  m_Action = ACTION_SAVE_IMPORT_OPEN;
  m_ActionImageID = IDB_ACTIONS6;
  OnActionRadio();
}
void CTemplDlg::OnRadioImportOpen() {
  m_Action = ACTION_IMPORT_OPEN;
  m_ActionImageID = IDB_ACTIONS7;
  OnActionRadio();
}
void CTemplDlg::OnRadioImport() {
  m_Action = ACTION_IMPORT;
  m_ActionImageID = IDB_ACTIONS8;
  OnActionRadio();
}

bool CTemplDlg::Save(LPCTSTR szTemplate, LPCTSTR szTemplateForSave)  {
  _mkdir(m_sTemplateSavedPath);
  if( CopyFile(szTemplate, szTemplateForSave, FALSE) )
    return true;
  return false;
}
bool CTemplDlg::Open(LPCTSTR szTemplate) {
  ShellExecute(NULL, "open", szTemplate, NULL, NULL, SW_SHOW);
  return true;
}
bool CTemplDlg::Restore(LPCTSTR szTemplate, LPCTSTR szSavedTemplate) {
  if( CopyFile(szSavedTemplate, szTemplate, FALSE) )
    return true;
  return false;
}
bool CTemplDlg::RestoreFromZip(LPCTSTR szTemplate) {
  CString szTemplateFilename = GetFileName(szTemplate);
  CString szTemplatePath     = GetFilePath(szTemplate);
  CString szZipFile;
  szZipFile.Format(_T("%s\\Templates.zip"), szTemplatePath);
  if ( false==FileExists(szZipFile) ) {
    ErrorBox(_T("Архівний файл шаблонів \"%s\" відсутній."), szZipFile);
    return false;
  }
  CZipArchive za;
  COptions    ZipOptions;
  BOOL berr = 0;
	try {
    za.Open(szZipFile, CZipArchive::zipOpen, ZipOptions.m_bTdComp ? 1 : 0 );
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
    return false;
  }
  int nZiped = za.GetCount();
  WORD wIndex = (WORD)-1;
  for( WORD i = 0; i < nZiped; i++ ) {
    CZipFileHeader fh;
    za.GetFileInfo(fh, i);
    CZipString sz = fh.GetFileName();
    if ( sz.CompareNoCase(szTemplateFilename)==0 ) {
      wIndex = i;
      break;
    }
  }
  if ( wIndex == (WORD)-1 ) {
    CString s;
    s.Format(_T("Файл \"%s\" не знайдено в архіві."), szTemplate);
    AfxGetMainWnd()->MessageBox(s);
    return false;
  }
  else {
    if ( za.ExtractFile(wIndex, szTemplatePath) ) {
      CString s;
      s.Format(_T("Файл \"%s\" успішно відновлений."), szTemplate);
      AfxGetMainWnd()->MessageBox(s);
      return true;
    }
  }
  return false;
}

bool CTemplDlg::Import(LPCTSTR szTemplate, const CString& sFullTemplateName, CString& sImportFile) {
  //sFilter.Format(_T("Шаблони ЕРАГС (*.rtf)|*.rtf")
  int nItem = m_TmplList.GetNextItem(-1, LVNI_ALL|LVNI_SELECTED);
  if ( -1==nItem ) {
    return false;
  }
  CString sUkrName  = m_TmplList.GetItemText(nItem, 0);
  CString sFileName = m_TmplList.GetItemText(nItem, 1);
  CString sFilter;
  sFilter.Format(_T("%s|%s||"), sUkrName, sFileName);

  CFileDialog dlg(TRUE, _T("*.rtf"), szTemplate, OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, sFilter);
  dlg.m_ofn.lpstrTitle = _T("Імпортувати шаблон");
  if ( dlg.DoModal()==IDOK ) {
    sImportFile = dlg.GetPathName();
    if ( sFullTemplateName.CompareNoCase(sImportFile)==0 ) {
      AfxGetMainWnd()->MessageBox(_T("Не можна імпортувати з цієї папки."), _T("ЕРАГС"), MB_OK|MB_ICONERROR);
      return false;
    }
    if (FALSE==CopyFile(sImportFile, sFullTemplateName, FALSE) ) {
      DWORD dwError = GetLastError();
      ErrorBox(_T("Неможливо переписати файл шаблону \"%s\".\n")
               _T("Можливо, цей файл відкритий в іншій програмі.\n")
               _T("Системна помилка %d(0x%04X): %s."),
               sFullTemplateName, dwError, dwError, FormatError(dwError));
      return false;
    }
    return true;
  }
  return false;
}

void CTemplDlg::OnYes() {
  UpdateData(TRUE);
  CString sName, sTemplate, sTemplateSaved, sImportFile;
  int nItem = m_TmplList.GetNextItem(-1, LVNI_ALL|LVNI_SELECTED);
  if ( -1==nItem ) {
    EndDialog(IDNO);
  }
  sName = m_TmplList.GetItemText(nItem, 1);
  sTemplate.Format(_T("%s\\%s"), m_sTemplatePath, sName);
  sTemplateSaved.Format(_T("%s\\%s"), m_sTemplateSavedPath, sName);
  EndDialog(IDYES);
  bool bRet = false;
  switch(m_Action) {
    case ACTION_SAVE_OPEN:
      if ( Save(sTemplate, sTemplateSaved) )
        bRet = Open(sTemplate);
      break;
    case ACTION_OPEN_ONLY:
      bRet = Open(sTemplate);
      break;
    case ACTION_RESTORE_OPEN:
      if ( Restore(sTemplate, sTemplateSaved) )
        bRet = Open(sTemplate);
      break;
    case ACTION_RESTORE:
      bRet = Restore(sTemplate, sTemplateSaved);
      break;
    case ACTION_RESTORE_FROM_ZIP:
      bRet = RestoreFromZip(sTemplate);
      break;
    case ACTION_SAVE_IMPORT_OPEN:
      if ( Save(sTemplate, sTemplateSaved) ) {
        if ( Import(sName, sTemplate, sImportFile)) {
          bRet = Open(sTemplate);
        }
      }
      break;
    case ACTION_IMPORT_OPEN:
      if ( Import(sName, sTemplate, sImportFile) ) {
        bRet = Open(sTemplate);
      }
      break;
    case ACTION_IMPORT:
      Import(sName, sTemplate, sImportFile);
      break;
  }
}

void CTemplDlg::OnClickTemplList(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: Add your control notification handler code here
  if ( m_Action	!= ACTION_NONE )
    GetDlgItem(IDYES)->EnableWindow(TRUE);
	*pResult = 0;
}

void CTemplDlg::OnColumnClickTemplList(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

  m_nSortColumn = pNMListView->iSubItem;

  switch( TemplSortOrder[m_nSortColumn] ) {
    case SO_NONE:  TemplSortOrder[m_nSortColumn] = SO_ASC;  break;
    case SO_ASC:   TemplSortOrder[m_nSortColumn] = SO_DESC; break;
    case SO_DESC:  TemplSortOrder[m_nSortColumn] = SO_ASC;  break;
  }

  m_TmplList.SortItems(TemplListSort, (DWORD)this);
  // m_TmplList.SetSortedColumn(m_nSortColumn, SO_ASC==TemplSortOrder[m_nSortColumn]);
	*pResult = 0;
}


BOOL CTemplDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("WinWord"));
  return true;
}
