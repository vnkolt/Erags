// EraPathPage.cpp : implementation file
//

#include "stdafx.h"
#include "EraSetup.h"
#include "EraPathPage.h"
#include "Registry.h"

#include "..\Common\FHelpers.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString GetErags() {
  return theRegistry.GetProfileString(_T("Erags"), _T("EraPath"), _T("C:\\Erags"));
}

DWORD GetFreeSpaceMB(LPCTSTR lpRootPathName) {
  DWORD SectorsPerCluster;
  DWORD BytesPerSector;
  DWORD NumberOfFreeClusters;
  DWORD TotalNumberOfClusters;
  if ( GetDiskFreeSpace(lpRootPathName,        // pointer to root path
                        &SectorsPerCluster,    // pointer to sectors per cluster
                        &BytesPerSector,       // pointer to bytes per sector
                        &NumberOfFreeClusters, // pointer to number of free clusters
                        &TotalNumberOfClusters // pointer to total number of clusters
                       )) {
    return MulDiv(SectorsPerCluster * BytesPerSector, NumberOfFreeClusters, 1024*1024);
  }
  return 0;
}


int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM lpData){
TCHAR szDir[MAX_PATH];

  switch(uMsg) {
    case BFFM_INITIALIZED:{
      ::SetWindowText(hwnd, _T("Оберіть папку для ПК ЕРАГС"));
      CString s = GetErags();
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
/////////////////////////////////////////////////////////////////////////////
// CEraPathPage dialog
CEraPathPage::CEraPathPage(CWnd* pParent /*=NULL*/)
          	:CNewWizPage(CEraPathPage::IDD, pParent) {
	//{{AFX_DATA_INIT(CEraPathPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CEraPathPage::DoDataExchange(CDataExchange* pDX) {
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEraPathPage)
	DDX_Text(pDX, IDC_ERAPATH, theApp.m_sEraPath);
	DDX_Text(pDX, IDC_ERAGROUP, theApp.m_sEraGroup);
	DDX_Control(pDX, IDC_SELPATH, m_SelPath);
	DDX_Control(pDX, IDC_ERAPATH, m_EraPath);
	DDX_Control(pDX, IDC_ERAGROUP, m_EraGroup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEraPathPage, CNewWizPage)
	//{{AFX_MSG_MAP(CEraPathPage)
	ON_BN_CLICKED(IDC_SELPATH, OnSelpath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraPathPage message handlers
void CEraPathPage::OnSelpath() {
  BROWSEINFO bi;
  TCHAR szDir[MAX_PATH];
  LPITEMIDLIST pidl;
  LPMALLOC pMalloc;

  if (SUCCEEDED(SHGetMalloc(&pMalloc))) {
    ZeroMemory(&bi,sizeof(bi));
    bi.hwndOwner = this->m_hWnd;
    bi.pszDisplayName = 0;
    bi.pidlRoot = 0;
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
    bi.lParam = (LPARAM)this;
    bi.lpfn = BrowseCallbackProc;

    pidl = SHBrowseForFolder(&bi);
    if ( pidl ) {
      if ( SHGetPathFromIDList(pidl,szDir) ) {
        theApp.m_sEraPath = szDir;
        GetDlgItem(IDC_ERAPATH)->SetWindowText(theApp.m_sEraPath);
        ResetFreeSpace();
      }
      // In C++:`
      pMalloc->Free(pidl); pMalloc->Release();
    }
  }
}
LRESULT CEraPathPage::OnWizardNext() {
  if ( IDC_RADIO1==GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2) )
    theApp.m_fServer = true;
  else
    theApp.m_fServer = false;

/*
  theApp.m_fInstallLaws = (IsDlgButtonChecked(IDC_CHECK_LAWS) != 0);
*/

  m_EraPath.GetWindowText(theApp.m_sEraPath);
  m_EraGroup.GetWindowText(theApp.m_sEraGroup);
  return 0;
}

void CEraPathPage::ResetFreeSpace() {
  DWORD dwFreeSpace = GetFreeSpaceMB(theApp.m_sEraPath.Left(3));
  CString szFreeSpace;
  szFreeSpace.Format("На жорсткому диску %c: %d Mb вільного простору",
                     theApp.m_sEraPath.GetAt(0), dwFreeSpace);
  GetDlgItem(IDC_FREE_SPACE)->SetWindowText(szFreeSpace);
}
BOOL CEraPathPage::OnInitDialog() {
	CNewWizPage::OnInitDialog();

/*
  CString szLaws;
  szLaws.Format(_T("%s\\DATA\\laws.z"), GetModulePath());
  if ( false==FileExists(szLaws) ) {
    GetDlgItem(IDC_CHECK_LAWS)->ShowWindow(SW_HIDE);
  }
*/
	
	// TODO: Add extra initialization here
  if ( theApp.m_fServer )
    CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
  else
    CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);

  ResetFreeSpace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

