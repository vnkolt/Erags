// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ULaws.h"
#include "SearchDlg.h"

#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LC_DATA   0
#define LC_TITLE  1
#define LC_FILE   2

CSearchDlg* g_pSearchDlg = NULL;

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
// CSearchDlg dialog


CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_fResized = false;
}

CSearchDlg::~CSearchDlg() {
  ClearFoundArray();
}

void CSearchDlg::ClearFoundArray() {
  for( int i(0); i < m_FoundArray.GetSize(); i++ ) {
    FoundInfo* pInfo = (FoundInfo*)m_FoundArray.GetAt(i);
    delete pInfo;
  }
  m_FoundArray.RemoveAll();
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_RESULTS, m_ResList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchDlg)
	ON_BN_CLICKED(IDC_IN_TEXT, OnInText)
	ON_BN_CLICKED(IDC_IN_TITLE, OnInTitle)
	ON_BN_CLICKED(IDC_ALL_WORDS, OnAllWords)
	ON_BN_CLICKED(IDC_ANY_WORD, OnAnyWord)
	ON_EN_CHANGE(IDC_WORDS, OnChangeWords)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSearchDlg::Create() {
  if ( NULL==g_pSearchDlg ) {
    g_pSearchDlg = new CSearchDlg(AfxGetMainWnd());
    return g_pSearchDlg->CDialog::Create(CSearchDlg::IDD);
  }
  return false;
}

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg message handlers
BOOL CSearchDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  CheckRadioButton(IDC_IN_TITLE,  IDC_IN_TEXT, IDC_IN_TEXT);
  CheckRadioButton(IDC_ALL_WORDS, IDC_ANY_WORD, IDC_ALL_WORDS);

  m_ResList.InsertColumn(LC_DATA,  _T("Дата"),    LVCFMT_LEFT,  64);
  m_ResList.InsertColumn(LC_TITLE, _T("Назва"),   LVCFMT_LEFT, 240);

  g_pSearchDlg = this;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CSearchDlg::OnInText() {
	CheckRadioButton(IDC_IN_TITLE,  IDC_IN_TEXT, IDC_IN_TEXT);
}
void CSearchDlg::OnInTitle() {
	CheckRadioButton(IDC_IN_TITLE,  IDC_IN_TEXT, IDC_IN_TITLE);
}

void CSearchDlg::OnAllWords() {
	CheckRadioButton(IDC_ALL_WORDS, IDC_ANY_WORD, IDC_ALL_WORDS);
}

void CSearchDlg::OnAnyWord() {
	CheckRadioButton(IDC_ALL_WORDS, IDC_ANY_WORD, IDC_ANY_WORD);
}

void CSearchDlg::OnChangeWords() {
  CString s;
  GetDlgItem(IDC_WORDS)->GetWindowText(s);
  s.TrimLeft();
  s.TrimRight();
  CWnd* pWndOk = GetDlgItem(IDOK);
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

CString CSearchDlg::FindDate(const CString& szTitle) {
  CString s;
  int nFound = szTitle.Find(_T("| вiд "));
  if ( nFound > 0 ) {
    s = szTitle.Mid(nFound+6, 11);
  }
  return s;
}
BOOL CSearchDlg::FindInTitle(const TCHAR* pBuffer, const CStringArray& Tokens, CString& szTitle, BOOL fAnyWord) {
  const char* szB = strstr(pBuffer, "<TITLE>");
  if ( NULL==szB )
    return false;
  szB += 7; // strlen("<TITLE>");
  const char* szE = strstr(pBuffer, "</TITLE>");
  if ( NULL==szE )
    return false;
  CString sz(szB, szE - szB);
  szTitle = sz;
  int nFound = 0;
  if ( fAnyWord ) {
    for ( int i(0); i < Tokens.GetSize(); i++ ) {
      if ( sz.Find(Tokens.GetAt(i)) >= 0 )
        return true;
    }
    return false;
  }
  else {
    for ( int i(0); i < Tokens.GetSize(); i++ ) {
      if ( sz.Find(Tokens.GetAt(i)) >= 0 )
        nFound++;
    }
  }
  return nFound==Tokens.GetSize();
}

void CSearchDlg::Resize() {
  CRect r;
  GetWindowRect(&r);
  int heigh = r.Height()/2, okTop;
  r.InflateRect(0, heigh);
  SetWindowPos(NULL, r.left, r.top, r.Width(), r.Height(), SWP_NOZORDER|SWP_SHOWWINDOW|SWP_NOMOVE);
  CWnd* pWndOk = GetDlgItem(IDOK);
  pWndOk->GetWindowRect(&r);
  heigh *= 2;
  r.top += heigh;
  r.bottom += heigh;
  ScreenToClient(&r);
  okTop = r.top;
  pWndOk->MoveWindow(&r);
  m_Progress.GetWindowRect(&r);
  ScreenToClient(&r);
  r.top += r.Height() + 4;
  r.bottom = okTop - 8;
  m_ResList.MoveWindow(&r);
  m_ResList.ShowWindow(SW_SHOW);
  m_ResList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);
}

void CSearchDlg::InsertItem(int nItem, FoundInfo* pFound) {
  m_ResList.InsertItem(nItem, pFound->szDate);
  m_ResList.SetItemText(nItem, LC_TITLE, pFound->szTitle);
  m_ResList.SetItemData(nItem, (LPARAM)pFound);
}
void CSearchDlg::OnOK() {
	// TODO: Add extra validation here
  UpdateData(true);
  BOOL fAnyWord = IDC_ANY_WORD==GetCheckedRadioButton(IDC_ALL_WORDS, IDC_ANY_WORD);
  BOOL fInTitle = IDC_IN_TITLE==GetCheckedRadioButton(IDC_IN_TITLE,  IDC_IN_TEXT);

  CCyrString szSearch;
  GetDlgItem(IDC_WORDS)->GetWindowText(szSearch);
  szSearch.MakeLower();

  CString szMask;
  szMask.Format(_T("%s\\Laws\\*.htm"), GetModulePath());
  DWORD dwMaxSize = 0;
  int nFiles = CalcCountOfFiles(szMask, dwMaxSize), nPos(0);

  if ( 0==nFiles ) {
    return;
  }
  m_Progress.SetRange32(0, nFiles);
  m_Progress.ShowWindow(SW_SHOW);

  CStringArray Words;
  FillTokenArray(szSearch, Words);

  TCHAR* pBuffer = new TCHAR[dwMaxSize+1];
  if ( NULL==pBuffer ) {
    return;
  }
  if ( false==m_fResized ) {
    m_fResized = true;
    Resize();
  }
  ClearFoundArray();
  m_ResList.DeleteAllItems();

  CString szTitle;
  int nFound = 0;

  WIN32_FIND_DATA fi;
  HANDLE hFile = FindFirstFile(szMask, &fi);
  if(hFile != INVALID_HANDLE_VALUE) {
    do {
      if((fi.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY|FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM))==0) {
        CString szFile;
        szFile.Format(_T("%s\\Laws\\%s"), GetModulePath(), fi.cFileName);
        //dwCount++;
        CFile f;
        DWORD dwRead = 0;
        if ( f.Open(szFile, CFile::modeRead) ) {
          if ( fInTitle ) {
            dwRead = f.ReadHuge(pBuffer, 1024);
            pBuffer[dwRead] = 0;
            if ( FindInTitle(pBuffer, Words, szTitle, fAnyWord) ) {
              FoundInfo* pFound = new FoundInfo;
              pFound->szTitle = szTitle;
              pFound->szFilename = szFile;
              pFound->szDate = FindDate(szTitle);
              m_FoundArray.Add( pFound );
              InsertItem(nFound++, pFound);
            }
          }
          else {
            dwRead = f.ReadHuge(pBuffer, fi.nFileSizeLow);
            pBuffer[dwRead] = 0;
          }
          f.Close();
          MakeUpper(pBuffer);
        }
        nPos++;
      }
      m_Progress.SetPos(nPos);
    } while(FindNextFile(hFile, &fi));
    FindClose(hFile);
  }
  delete pBuffer;
}

void CSearchDlg::OnDestroy()  {
  static BOOL fInside = false;
  if ( fInside ) {
    return;
  }
  fInside = true;
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
  if ( g_pSearchDlg ) {
    g_pSearchDlg->DestroyWindow();
    delete g_pSearchDlg;
    g_pSearchDlg = NULL;	
  }
  fInside = false;
}
