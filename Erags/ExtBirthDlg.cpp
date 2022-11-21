// ExtBirthDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "ExtBirthDlg.h"

#include "Caches.h"
#include "Defaults.h"

#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtBirthDlg dialog


CExtBirthDlg::CExtBirthDlg(CWnd* pParent /*=NULL*/)
             :CDialogEx(CExtBirthDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CExtBirthDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_pSet = NULL;
  m_fSex = FALSE;
}


void CExtBirthDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtBirthDlg)
	DDX_Control(pDX, IDC_FRAME1, m_Frame1);
	DDX_Control(pDX, IDC_FRAME2, m_Frame2);
	DDX_Control(pDX, IDC_FRAME3, m_Frame3);
	DDX_Control(pDX, IDC_GR10, m_chkGr10);
  DDX_Control(pDX, IDC_GRSVID, m_chkWitnesses);
	DDX_Control(pDX, IDC_NEWSURNAME, m_edtNewSurname);
	DDX_Control(pDX, IDC_COMBO_NEWNAME, m_cmbNewName);
	DDX_Control(pDX, IDC_COMBO_NEWPATRONYMIC, m_cmbNewPatronymic);
	DDX_Control(pDX, IDC_NEWFATHERDATE, m_edtFatherDate);
	DDX_Control(pDX, IDC_NEWMOTHERDATE, m_edtMotherDate);
	DDX_Control(pDX, IDC_NEWMOTHERSURNAME, m_edtNewMotherSurname);
	DDX_Control(pDX, IDC_GR10TEXT, m_edtGr10);
	DDX_Control(pDX, IDC_MEMO, m_edtMemo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExtBirthDlg, CDialogEx)
	//{{AFX_MSG_MAP(CExtBirthDlg)
	ON_EN_CHANGE(IDC_NEWSURNAME, OnChangeAll)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_BN_CLICKED(IDC_GR10, OnGr10)
  ON_EN_UPDATE(IDC_NEWSURNAME, OnChangeAll)
	ON_CBN_SELCHANGE(IDC_COMBO_NEWNAME, OnChangeAll)
	ON_CBN_SELCHANGE(IDC_COMBO_NEWPATRONYMIC, OnChangeAll)
	ON_EN_CHANGE(IDC_NEWFATHERDATE, OnChangeAll)
	ON_EN_CHANGE(IDC_NEWMOTHERDATE, OnChangeAll)
	ON_EN_CHANGE(IDC_NEWMOTHERSURNAME, OnChangeAll)
  ON_EN_CHANGE(IDC_GR10TEXT, OnChangeAll)
	ON_BN_CLICKED(IDC_GRSVID, OnGrSvid)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtBirthDlg message handlers
BOOL CExtBirthDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

  ASSERT( m_pSet != NULL );

  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_chkGr10.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkWitnesses.SetCheckBoxImageList(&m_CheckBoxIL);
  }
	
	// TODO: Add extra initialization here
  CString s;
  s = m_pSet->GetNewSurname(m_sMemo);
  m_edtNewSurname.SetWindowText(s);
  if ( m_fSex ) {
    theMNames.FillCombo( m_cmbNewName, m_pSet->GetNewName(m_sMemo), false );
    theMPatronymics.FillCombo( m_cmbNewPatronymic, m_pSet->GetNewPatronymic(m_sMemo), false );
  }
  else {
    theWNames.FillCombo( m_cmbNewName, m_pSet->GetNewName(m_sMemo), false );
    theWPatronymics.FillCombo( m_cmbNewPatronymic, m_pSet->GetNewPatronymic(m_sMemo), false );
  }
  m_edtMemo.SetWindowText( m_sMemo );

  m_edtNewMotherSurname.SetWindowText( m_pSet->GetNewMotherSurname() );
  m_edtFatherDate.SetWindowText( m_pSet->GetFatherDate() );
  m_edtMotherDate.SetWindowText( m_pSet->GetMotherDate() );

  if ( m_sGr10 != m_sNewGr10 ) {
    if ( !m_sNewGr10.IsEmpty() ) {
      m_chkGr10.SetCheck(1);
      m_edtGr10.SetWindowText(m_sNewGr10);
    }
    else {
      m_chkGr10.SetCheck(1);
      m_edtGr10.SetWindowText(m_sGr10);
    }
  }
  else {
    m_chkGr10.SetCheck(0);
  }
  if ( 0==m_chkGr10.GetCheck() ) {
    m_chkWitnesses.EnableWindow(false);
  }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CExtBirthDlg::OnChangeAll() {
  CString s = m_pSet->SetNewSNP( m_edtMemo.GetText(),
                                 m_edtNewSurname.GetText(),
                                 m_cmbNewName.GetCurText(),
                                 m_cmbNewPatronymic.GetCurText(),
                                 m_edtNewMotherSurname.GetText(),
                                 m_edtFatherDate.GetText(),
                                 m_edtMotherDate.GetText(),
                                 m_edtGr10.GetText() );
  m_edtMemo.SetWindowText(s);
}

void CExtBirthDlg::OnYes() {
	if ( UpdateData(TRUE) ) {
    m_sMemo = m_edtMemo.GetText();
  }
  EndDialog(IDYES);
}

BOOL CExtBirthDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
  WORD wNotifyCode = HIWORD(wParam);
  WORD wCtrlId = LOWORD(wParam);
	switch( wCtrlId ) {
    case IDC_COMBO_NEWNAME:
    case IDC_COMBO_NEWPATRONYMIC:
      if ( CBN_SELCHANGE==wNotifyCode || CBN_EDITCHANGE==wNotifyCode )
        OnChangeAll();
      break;
  }
	return CDialogEx::OnCommand(wParam, lParam);
}


void CExtBirthDlg::OnGr10() { 
  if ( m_chkGr10.GetCheck() ) {
    m_chkWitnesses.EnableWindow(true);
    if ( !m_sNewGr10.IsEmpty() )
      m_edtGr10.SetWindowText(m_sNewGr10);
    else {
      m_edtGr10.SetWindowText(m_sGr10);
    }
  }
  else {
    CString sGr10;
    m_sMemo = m_edtMemo.GetText();
    sGr10 = GetFullBracketString(m_sMemo, _T("Г10:"));
    if ( false==sGr10.IsEmpty() ) {
      m_sMemo.Replace(sGr10, _T(""));
      m_sMemo = Trim(m_sMemo);
      m_edtMemo.SetWindowText(m_sMemo);
    }
    m_edtGr10.SetWindowText(_T(""));
    m_chkWitnesses.EnableWindow(false);
  }
}

void CExtBirthDlg::OnGrSvid() {
	// TODO: Add your control notification handler code here
	CString sMemo;
  m_edtGr10.GetWindowText(sMemo);
  int nFind = sMemo.Find(_T("Свідки:"));
  if ( nFind >=0 )
    sMemo = sMemo.Left(nFind);
  else {
    CString s;
    s.Format(_T(" Свідки: , паспорт № , виданий %s, зареєстрований за адресою: %s;")
                   _T("  , паспорт № , виданий %s, зареєстрований за адресою: %s;"),
             theIniCache.GetByROVD(), theIniCache.GetCITY(),
             theIniCache.GetByROVD(), theIniCache.GetCITY() );
    sMemo += s;

  }
  m_edtGr10.SetWindowText(sMemo);
}

BOOL CExtBirthDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("RegBirth2"));
  return true;
}
