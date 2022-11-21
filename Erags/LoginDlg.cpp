// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "LoginDlg.h"
#include "Defaults.h"

#include "..\Common\Crypto.h"
#include "..\Common\CyrString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CUsers theUsers;

CString EncryptPassword(LPCTSTR szPassword) {
  CString sz = szPassword;
  CCrypto crypt;
  crypt.SetCryptoKey(_T("Пароль"), 6);
  crypt.SetKeyIndex(0);
  crypt.Encrypt((void*)(LPCTSTR)sz, strlen(szPassword));
  return sz;
}
CString DecryptPassword(LPCTSTR szPassword) {
  CString sz = szPassword;
  CCrypto crypt;
  crypt.SetCryptoKey(_T("Пароль"), 6);
  crypt.SetKeyIndex(0);
  crypt.Decrypt((void*)(LPCTSTR)sz, strlen(szPassword));
  return sz;
}

/////////////////////////////////////////////////////////////////////////////
// CUsers
CUsers::CUsers() {
  m_FreeIndex = -1;
}
CUsers::~CUsers() {
}
void CUsers::Load() {
  CString szKey;
  UserInfo ui;
  for( int i(0); i < MAX_USERS; i++ ) {
    szKey.Format(_T("User%02d"), i);
    CString szValue = theIniCache.GetSVal(_T("Користувач"), szKey, _T(""));
    ui.szUser     = GetBracketString(szValue, _T("Користувач:"));
    ui.szPost     = GetBracketString(szValue, _T("Посада:"));
    ui.szPassword = DecryptPassword(GetBracketString(szValue, _T("Пароль:")));
    
    if ( false==ui.szUser.IsEmpty() ) {
      m_Users.Add( ui );
    }
    else if ( m_FreeIndex==-1 ) {
      m_FreeIndex = i;
    }
  }
  if ( m_Users.GetSize()==0 ) {
    ui.szUser = theIniCache.GetBoss();
    ui.szPassword = "";
    m_Users.Add(ui);
  }
}
void CUsers::Add(LPCTSTR szUser, LPCTSTR szPost, LPCTSTR szPassword) {
  CString szKey, szValue;
  szKey.Format(_T("User%02d"), m_FreeIndex);
  UserInfo ui;
  ui.szUser = szUser;
  ui.szPost = szPost;
  ui.szPassword = szPassword;
  m_Users.Add(ui);
  szValue.Format(_T("{Користувач:%s}{Посада:%s}{Пароль:%s}"), ui.szUser, ui.szPost, EncryptPassword(szPassword));
  theIniCache.SetSVal(_T("Користувач"), szKey, szValue);
  m_FreeIndex++;
}
void CUsers::Delete(LPCTSTR szUser) {
  CString szKey;
  UserInfo ui;
  for( int i(0); i < m_Users.GetSize() ; i++ ) {
    szKey.Format(_T("User%02d"), i);
    ui = m_Users.GetAt(i);

    if ( ui.szUser==szUser ) {
      m_Users.RemoveAt(i);
      m_FreeIndex = i;
      theIniCache.SetSVal(_T("Користувач"), szKey, "");
      break;
    }
  }
}
/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog
CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Control(pDX, IDC_LOGIN, m_lstLogin);
  DDX_Text(pDX, IDC_PASSWORD, m_szPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_BN_CLICKED(IDC_SHOW_PASSWORD, OnShowPassword)
	ON_CBN_EDITCHANGE(IDC_LOGIN, OnEditchangeLogin)
	ON_CBN_SELENDOK(IDC_LOGIN, OnSelendokLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers
BOOL CLoginDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
  m_lstLogin.SetExtendedStyle(LVS_EX_FULLROWSELECT);
  m_lstLogin.InsertColumn(0, _T("ПІБ")    , LVCFMT_LEFT, 120);
  m_lstLogin.InsertColumn(1, _T("Посада") , LVCFMT_LEFT, 180);
  for( int i = 0; i < theUsers.GetCount(); i++ ) {
    UserInfo ui = theUsers.GetAt(i);
    m_lstLogin.InsertItem(i, ui.szUser);
    m_lstLogin.SetItemText(i, 1, ui.szPost);
    m_lstLogin.SetItemData(i, (DWORD)i);
  }
  m_lstLogin.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnShowPassword() {
  CEdit* pPasswordWnd = (CEdit*)GetDlgItem(IDC_PASSWORD);
  if ( IsDlgButtonChecked(IDC_SHOW_PASSWORD) ) {
    pPasswordWnd->ModifyStyle(ES_PASSWORD, 0);
    pPasswordWnd->SetPasswordChar(0);
  }
  else {
    pPasswordWnd->ModifyStyle(0, ES_PASSWORD);
    pPasswordWnd->SetPasswordChar('*');
  }
  pPasswordWnd->InvalidateRect(NULL);
  pPasswordWnd->UpdateWindow();
}

void CLoginDlg::OnEditchangeLogin() {
	// TODO: Add your control notification handler code here
	CString s;
  GetDlgItem(IDC_LOGIN)->GetWindowText(s);
  GetDlgItem(IDOK)->EnableWindow(false==s.IsEmpty());
}

void CLoginDlg::OnSelendokLogin() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDOK)->EnableWindow(true);
}

void CLoginDlg::OnOK() {
	// TODO: Add extra validation here
	UpdateData(true);

  int nItem = m_lstLogin.GetNextItem(-1, LVNI_SELECTED);

  if ( -1==nItem ) {
    AfxMessageBox(_T("Ви повинні обрати користувача зі списку."), MB_YESNO);
    return;
  }
  int nUser = m_lstLogin.GetItemData(nItem);
  UserInfo ui;
  ui = theUsers.GetAt(nUser);
  if ( ui.szPassword!=m_szPassword ) {
    if ( IDYES==AfxMessageBox(_T("Неправільный пароль. Спробувати ще раз?"), MB_YESNO) ) {
      return;
    }
    EndDialog(IDCANCEL);
  }
  theApp.m_szUser = ui.szUser;
  theApp.m_szPost = ui.szPost;
	CDialog::OnOK();
}
