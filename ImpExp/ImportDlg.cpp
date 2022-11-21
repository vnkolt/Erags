// ImportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImpExp.h"
#include "ImportDlg.h"
#include "MyFileDialog.h"

#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportDlg dialog


CImportDlg::CImportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportDlg, CDialog)
	//{{AFX_MSG_MAP(CImportDlg)
	ON_BN_CLICKED(IDC_OPEN_FILE_DLG, OnOpenFileDlg)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportDlg message handlers
BOOL CImportDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  CString s;
  s.Format(_T("Імпорт даних у файл %s"), g_szTargetFile);
  SetWindowText(s);

  if ( g_Year ) {
    s.Format(_T("Робити імпорт даних тільки за %d рік"), g_Year);
    GetDlgItem(IDC_FORYEAR)->SetWindowText(s);
    CheckDlgButton(IDC_FORYEAR, 1); // По умолчанию только за соответствующий год
  }
  else {
    GetDlgItem(IDC_FORYEAR)->ShowWindow(SW_HIDE);
  }

  CheckDlgButton(IDC_NOEMPY,  1); // По умолчанию только непустые записи
  CheckDlgButton(IDC_NOEXIST, 1); // По умолчанию не импотировать записи, которые уже есть
  CheckDlgButton(IDC_IMPORT_BIRTH, 1);
  CheckDlgButton(IDC_IMPORT_MARRIAGE, 1);
  CheckDlgButton(IDC_IMPORT_DIVORCE, 1);
  CheckDlgButton(IDC_IMPORT_DEATH, 1);
  CheckDlgButton(IDC_IMPORT_CHANGE, 1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImportDlg::OnOpenFileDlg() {
	// TODO: Add your control notification handler code here
  CMyFileDialog ofd(TRUE, "*.er3", NULL, OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_LONGNAMES, _T("Файли БД ЕРАГС(*.er3,*.era)|*.er3;*.era|"), AfxGetMainWnd());
  ofd.SetTitle(0, _T("Оберіть файл, з якого потрібно робити імпорт даних"));
  if ( IDOK==ofd.DoModal() ) {
    GetDlgItem(IDC_SOURCE_FILE)->SetWindowText(ofd.GetPathName());
    if ( g_Year ) { // Если только год присутствует в имени файла
      GetDlgItem(IDC_FORYEAR)->EnableWindow();
    }
    GetDlgItem(IDC_NOEMPY)         ->EnableWindow();
    GetDlgItem(IDC_NOEXIST)        ->EnableWindow();
    GetDlgItem(IDC_IMPORT_BIRTH)   ->EnableWindow();
    GetDlgItem(IDC_IMPORT_MARRIAGE)->EnableWindow();
    GetDlgItem(IDC_IMPORT_DIVORCE) ->EnableWindow();
    GetDlgItem(IDC_IMPORT_CHANGE)  ->EnableWindow();
    GetDlgItem(IDC_IMPORT_DEATH)   ->EnableWindow();
    GetDlgItem(IDOK)               ->EnableWindow();
  }
}

void CImportDlg::OnOK() {
	// TODO: Add extra validation here
  GetDlgItem(IDC_SOURCE_FILE)->GetWindowText(g_szSourceFile); // Сохряним в глобальной переменной
  if ( g_Year ) { // Если только год присутствует в имени файла
    if ( false==IsDlgButtonChecked(IDC_FORYEAR) ) { // Хотят имортировать записи с любым годом регистрации?
      g_Year = 0;
    }
  }
  g_fNoEmpty  = IsDlgButtonChecked(IDC_NOEMPY);
  g_fNoExist  = IsDlgButtonChecked(IDC_NOEXIST);
  g_fBirth    = IsDlgButtonChecked(IDC_IMPORT_BIRTH);
  g_fMarriage = IsDlgButtonChecked(IDC_IMPORT_MARRIAGE);
  g_fDivorce  = IsDlgButtonChecked(IDC_IMPORT_DIVORCE);
  g_fChange   = IsDlgButtonChecked(IDC_IMPORT_CHANGE);
  g_fDeath    = IsDlgButtonChecked(IDC_IMPORT_DEATH);
	CDialog::OnOK();
}

BOOL CImportDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
	// TODO: Add your message handler code here and/or call default
  if ( fOnHelpCallback ) {
    fOnHelpCallback(_T("Import"));
  }
	return TRUE;
	//return CDialog::OnHelpInfo(pHelpInfo);
}
