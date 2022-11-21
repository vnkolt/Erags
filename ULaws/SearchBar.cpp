// SearchBar.cpp : implementation file
//

#include "stdafx.h"
#include "ULaws.h"
#include "MainFrm.h"
#include "SearchBar.h"
#include "ULawsView.h"

#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"

#include "..\Controls\ProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LC_DATA   0
#define LC_TITLE  1
#define LC_FILE   2

#define FLC_NUMBER  0
#define FLC_DATE    1
#define FLC_NAME    2
#define FLC_FILE    3

CSearchBar theSearhBar;
CFoundList theFoundList;
CFoundBar* g_pFoundBar = NULL;

int CalcCountOfFiles(const CString& szMask, DWORD& MaxSize) {
  int nCount = 0;
  MaxSize = 0;
  WIN32_FIND_DATA fi;
  HANDLE hFile = FindFirstFile(szMask, &fi);
  if(hFile != INVALID_HANDLE_VALUE) {
    do {
      if((fi.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY|FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM))==0) {
        nCount++;
        if ( fi.nFileSizeLow > MaxSize ) {
          MaxSize = fi.nFileSizeLow;
        }
      }
    } while(FindNextFile(hFile, &fi));
    FindClose(hFile);
  }
  return nCount;
}

/////////////////////////////////////////////////////////////////////////////
// CFoundList
CFoundList::CFoundList() {
}
CFoundList::~CFoundList() {
  Clear();
}
void CFoundList::Clear() {
  for( int i(0); i < m_array.GetSize(); i++ ) {
    FoundInfo* pFoundInfo = (FoundInfo*)m_array.GetAt(i);
    delete pFoundInfo;
  }
  m_array.RemoveAll();
}
int CFoundList::Add(FoundInfo* pFound) {
  return m_array.Add(pFound);
}

CString GetTitle(const TCHAR* pBuffer) {
  CString szTitle;
  const char* szB = strstr(pBuffer, "name=1>");
  if ( NULL==szB ) {
     return szTitle;
  }
  const char* szE = strstr(pBuffer, "name=6");
  if ( NULL==szE ) {
    szE = strstr(pBuffer, "name=5");
  }
  if ( NULL==szE ) {
    return szTitle;
  }
  while( szB < szE ) {
    if ( IsCyrChar(*szB) ) {
      szTitle += *szB;
    }
    szB++;
  }
  return szTitle;
}

BOOL FindInTitle(const TCHAR* pBuffer, const CStringArray& Tokens, BOOL fAnyWord) {
  CString szTitle = GetTitle(pBuffer);

  if ( szTitle.IsEmpty() ) {
    return false;
  }
  int nFound = 0;
  if ( fAnyWord ) {
    for ( int i(0); i < Tokens.GetSize(); i++ ) {
      if ( szTitle.Find(Tokens.GetAt(i)) >= 0 ) {
        return true;
      }
    }
    return false;
  }
  else {
    for ( int i(0); i < Tokens.GetSize(); i++ ) {
      if ( szTitle.Find(Tokens.GetAt(i)) >= 0 )
        nFound++;
    }
  }
  return nFound==Tokens.GetSize();
}

BOOL FindInBuffer(const TCHAR* pBuffer, const CStringArray& Tokens, BOOL fAnyWord) {
  int nFound = 0;
  if ( fAnyWord ) {
    for ( int i(0); i < Tokens.GetSize(); i++ ) {
      if ( strstr(pBuffer, Tokens.GetAt(i)) >= 0 ) {
        return true;
      }
    }
    return false;
  }
  else {
    for ( int i(0); i < Tokens.GetSize(); i++ ) {
      if ( strstr(pBuffer, Tokens.GetAt(i)) >= 0 ) {
        nFound++;
      }
    }
  }
  return nFound==Tokens.GetSize();
}

CString FindDate(const CString& szTitle) {
  CString s;
  int nFound = szTitle.Find(_T("| вiд "));
  if ( nFound > 0 ) {
    s = szTitle.Mid(nFound+6, 11);
  }
  return s;
}

CString FindNumber(const CString& szTitle) {
  CString s;
  int nFound = szTitle.Find(_T("№"));
  if ( nFound > 0 ) {
    nFound++;
    while ( nFound < szTitle.GetLength() && szTitle.GetAt(nFound)==' ' ) nFound++;
    for( int i=nFound; i < szTitle.GetLength(); i++ ) {
      TCHAR c = szTitle.GetAt(i);
      if ( '('==c || '<'==c) {
        break;
      }
      s += c;
    }
  }
  return Trim(s);
}

CString GetHTMLTitle(const TCHAR* pBuffer) {
  const char* szB = strstr(pBuffer, "<TITLE>");
  if ( NULL==szB ) {
    return _T("");
  }
  szB += 7; // strlen("<TITLE>");
  const char* szE = strstr(pBuffer, "</TITLE>");
  if ( NULL==szE ) {
    return _T("");
  }
  return CString(szB, szE - szB);
}
void DoSearch(BOOL fAnyWord, BOOL fInTitle, LPCTSTR szWords) {
  CCyrString szSearch(szWords);
  szSearch.MakeLower();

  CString szMask;
  szMask.Format(_T("%s\\Laws\\*.htm"), GetModulePath());
  DWORD dwMaxSize = 0;
  int  nFiles = CalcCountOfFiles(szMask, dwMaxSize), nPos(0);

  if ( 0==nFiles ) {
    return;
  }

  CStringArray Words;
  FillTokenArray(szSearch, Words);

  TCHAR* pBuffer = new TCHAR[dwMaxSize+1];
  if ( NULL==pBuffer ) {
    return;
  }

  CString szTitle;
  int nFound = 0;

  BOOL fFoundBarVisible = false;

  CProgressBar bar(_T("Пошук документів..."), 100, nFiles, false, 0);

  WIN32_FIND_DATA fi;
  HANDLE hFile = FindFirstFile(szMask, &fi);
  if(hFile != INVALID_HANDLE_VALUE) {
    do {
      if((fi.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY|FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM))==0) {
        CString szFile;
        szFile.Format(_T("%s\\Laws\\%s"), GetModulePath(), fi.cFileName);

        nPos++;
        bar.SetPos(nPos);
        PeekAndPump();

        CFile f;
        DWORD dwRead = 0;
        if ( f.Open(szFile, CFile::modeRead | CFile::shareDenyWrite) ) {
          CString szTitle;
          if ( fInTitle ) {
            dwRead = f.ReadHuge(pBuffer, 1024*8);
            pBuffer[dwRead] = 0;
            szTitle = GetHTMLTitle(pBuffer);
            MakeLower(pBuffer);
            if ( FindInTitle(pBuffer, Words, fAnyWord) ) {
              FoundInfo* pFound = new FoundInfo;
              pFound->szTitle = szTitle;
              pFound->szFilename = szFile;
              pFound->szDate   = FindDate(szTitle);
              pFound->szNumber = FindNumber(szTitle);
              if ( false==fFoundBarVisible ) {
                fFoundBarVisible = true;
                theFoundList.Clear();
                if ( g_pFoundBar ) {
                  g_pFoundBar->Clear();
                }
                ((CMainFrame*)AfxGetMainWnd())->ShowFoundBar(true);
              }
              theFoundList.Add( pFound );
              g_pFoundBar->Add( pFound );
            }
          }
          else {
            dwRead = f.ReadHuge(pBuffer, fi.nFileSizeLow);
            pBuffer[dwRead] = 0;
            szTitle = GetHTMLTitle(pBuffer);
            MakeLower(pBuffer);
            if ( FindInBuffer(pBuffer, Words, fAnyWord) ) {
              FoundInfo* pFound = new FoundInfo;
              pFound->szTitle = szTitle;
              pFound->szFilename = szFile;
              pFound->szDate   = FindDate(szTitle);
              pFound->szNumber = FindNumber(szTitle);
              if ( false==fFoundBarVisible ) {
                fFoundBarVisible = true;
                theFoundList.Clear();
                if ( g_pFoundBar ) {
                  g_pFoundBar->Clear();
                }
                ((CMainFrame*)AfxGetMainWnd())->ShowFoundBar(true);
              }
              theFoundList.Add( pFound );
              g_pFoundBar->Add( pFound );
            }
          }
          f.Close();
        }
      }
    } while(FindNextFile(hFile, &fi));
    FindClose(hFile);
  }
  delete pBuffer;

}

/////////////////////////////////////////////////////////////////////////////
// CSearchBar dialog
IMPLEMENT_DYNCREATE(CSearchBar, CDialogBar)
CSearchBar::CSearchBar() {
}

void CSearchBar::DoDataExchange(CDataExchange* pDX) {
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSearchBar, CDialogBar)
	//{{AFX_MSG_MAP(CSearchBar)
	ON_BN_CLICKED(IDC_IN_TEXT, OnInText)
	ON_BN_CLICKED(IDC_IN_TITLE, OnInTitle)
	ON_BN_CLICKED(IDC_ALL_WORDS, OnAllWords)
	ON_BN_CLICKED(IDC_ANY_WORD, OnAnyWord)
  ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_EN_CHANGE(IDC_WORDS, OnChangeWords)
  ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CSearchBar::Create() {
  BOOL fCreate = CDialogBar::Create(AfxGetMainWnd(), IDD_SBAR, CBRS_ALIGN_ANY, IDD_SBAR);
  if ( fCreate ) {
    SetWindowText(_T("Пошук документів"));
    CheckRadioButton(IDC_IN_TITLE,  IDC_IN_TEXT, IDC_IN_TITLE);
    CheckRadioButton(IDC_ALL_WORDS, IDC_ANY_WORD, IDC_ALL_WORDS);
  }
  return fCreate;
}
/////////////////////////////////////////////////////////////////////////////
// CSearchBar message handlers
void CSearchBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler) {
  CString szWords;
  GetDlgItem(IDC_WORDS)->GetWindowText(szWords);
  szWords.TrimLeft();
  szWords.TrimRight();
	bDisableIfNoHndler = szWords.IsEmpty();
	CDialogBar::OnUpdateCmdUI(pTarget,bDisableIfNoHndler);
}
void CSearchBar::OnInText() {
	CheckRadioButton(IDC_IN_TITLE,  IDC_IN_TEXT, IDC_IN_TEXT);
}
void CSearchBar::OnInTitle() {
	CheckRadioButton(IDC_IN_TITLE,  IDC_IN_TEXT, IDC_IN_TITLE);
}

void CSearchBar::OnAllWords() {
	CheckRadioButton(IDC_ALL_WORDS, IDC_ANY_WORD, IDC_ALL_WORDS);
}

void CSearchBar::OnAnyWord() {
	CheckRadioButton(IDC_ALL_WORDS, IDC_ANY_WORD, IDC_ANY_WORD);
}

void CSearchBar::OnChangeWords() {
  CString s;
  GetDlgItem(IDC_WORDS)->GetWindowText(s);
  s.TrimLeft();
  s.TrimRight();
  CWnd* pWndOk = GetDlgItem(IDC_SEARCH);
  BOOL fEnabled = pWndOk->IsWindowEnabled();
  if ( s.IsEmpty() ) {
    if ( fEnabled ) {
      pWndOk->EnableWindow(false);
    }
  }
  else {
    if ( false==fEnabled ) {
      pWndOk->EnableWindow(true);
    }
  }
}
void CSearchBar::OnSearch() {
  BOOL fAnyWord = IDC_ANY_WORD==GetCheckedRadioButton(IDC_ALL_WORDS, IDC_ANY_WORD);
  BOOL fInTitle = IDC_IN_TITLE==GetCheckedRadioButton(IDC_IN_TITLE,  IDC_IN_TEXT);
 
  CCyrString szSearch;
  GetDlgItem(IDC_WORDS)->GetWindowText(szSearch);
  szSearch.MakeLower();
  
  DoSearch(fAnyWord, fInTitle, szSearch);
}
/////////////////////////////////////////////////////////////////////////////
// CFoundBar
BEGIN_MESSAGE_MAP(CFoundBar, baseCFoundBar)
	//{{AFX_MSG_MAP(CFoundBar)
	ON_WM_CREATE()
  ON_WM_DESTROY()
  ON_WM_SIZE()
  ON_NOTIFY(NM_CLICK, IDC_RESULTS, OnClickResults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFoundBar::CFoundBar() {
  m_nItems = 0;
}
CFoundBar::~CFoundBar() {
}

void CFoundBar::Clear() {
  m_FoundList.DeleteAllItems();
  m_nItems = 0;
}

int CFoundBar::Add(FoundInfo* pFoundInfo) {
  int nItem = m_FoundList.InsertItem(m_nItems++, pFoundInfo->szNumber);
  m_FoundList.SetItemText(nItem, FLC_DATE, pFoundInfo->szDate);
  m_FoundList.SetItemText(nItem, FLC_NAME, pFoundInfo->szTitle);
  m_FoundList.SetItemText(nItem, FLC_NAME, pFoundInfo->szTitle);
  m_FoundList.SetItemData(nItem, (DWORD)pFoundInfo);
  return nItem;
}

/////////////////////////////////////////////////////////////////////////////
// CFoundBar message handlers
int CFoundBar::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (baseCFoundBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

  if (!m_FoundList.Create(WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL, CRect(0,0,0,0), this, IDC_RESULTS))
		return -1;

  m_FoundList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

  m_FoundList.InsertColumn(FLC_NUMBER, _T("№")    , LVCFMT_LEFT,  48);
  m_FoundList.InsertColumn(FLC_DATE  , _T("Дата") , LVCFMT_LEFT,  80);
  m_FoundList.InsertColumn(FLC_NAME  , _T("Назва"), LVCFMT_LEFT, 520);

  g_pFoundBar = this;

	return 0;
}

void CFoundBar::OnDestroy() {
  baseCFoundBar::OnDestroy();
}

void CFoundBar::OnSize(UINT nType, int cx, int cy) {
  baseCFoundBar::OnSize(nType, cx, cy);
  if ( m_FoundList.GetSafeHwnd() ) {
    CRect r;
    GetClientRect(&r);
    m_FoundList.MoveWindow(&r);
  }
}
void CFoundBar::OnClickResults(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: Add your control notification handler code here
  int nItem = m_FoundList.GetNextItem(-1, LVNI_SELECTED);
  if ( nItem >= 0 ) {
    FoundInfo* pFound = (FoundInfo*)m_FoundList.GetItemData(nItem);
    g_pULawsView->GoToUrl(pFound->szFilename);
  }
	*pResult = 0;
}
