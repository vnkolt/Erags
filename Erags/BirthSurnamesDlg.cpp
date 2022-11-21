// BirthSurnamesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "BirthSurnamesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBirthSurnamesDlg dialog
CBirthSurnamesDlg::CBirthSurnamesDlg(CWnd* pParent /*=NULL*/)
                	:CDialogEx(CBirthSurnamesDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CBirthSurnamesDlg)
	m_szNewSurname = _T("");
	m_szOldSurname = _T("");
	//}}AFX_DATA_INIT
}

void CBirthSurnamesDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBirthSurnamesDlg)
	DDX_Control(pDX, IDC_SURNAME, m_Surname);
	DDX_Text(pDX, IDC_SURNAME,    m_szSurname);
	DDX_Control(pDX, IDC_OLDSURNAME, m_OldSurname);
	DDX_Text(pDX, IDC_OLDSURNAME, m_szOldSurname);
	DDX_Control(pDX, IDC_NEWSURNAME, m_NewSurname);
	DDX_Text(pDX, IDC_NEWSURNAME, m_szNewSurname);
  DDX_Control(pDX, IDC_TWO_SURNAMES, m_btnOne);
  DDX_Control(pDX, IDC_SINGLE_SURNAME, m_btnTwo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBirthSurnamesDlg, CDialogEx)
	//{{AFX_MSG_MAP(CBirthSurnamesDlg)
	ON_BN_CLICKED(IDC_SINGLE_SURNAME, OnSingleSurname)
	ON_BN_CLICKED(IDC_TWO_SURNAMES, OnTwoSurnames)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBirthSurnamesDlg message handlers
BOOL CBirthSurnamesDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_btnOne.SetRadioImageList(&m_RadioIL);
    m_btnOne.SetRadio(IDC_TWO_SURNAMES, IDC_SINGLE_SURNAME);

    m_btnTwo.SetRadioImageList(&m_RadioIL);
    m_btnTwo.SetRadio(IDC_TWO_SURNAMES, IDC_SINGLE_SURNAME);
  }
  CheckDlgButton(IDC_TWO_SURNAMES, 1);
  m_fTwoSurnames = true;
  CString s = GetTokSpace(m_szSurname, 0);
  m_OldSurname.SetWindowText(s);

  s = GetTokSpace(m_szSurname, 1);
  s.Replace("(", "");
  s.Replace(")", "");
  m_NewSurname.SetWindowText(s);

  m_Surname.SetWindowText(m_szSurname);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBirthSurnamesDlg::OnSingleSurname() {
	// TODO: Add your control notification handler code here
  m_fTwoSurnames = false;
  m_OldSurname.EnableWindow(false);
  m_NewSurname.EnableWindow(false);
  m_Surname.EnableWindow(true);
}
void CBirthSurnamesDlg::OnTwoSurnames() {
	// TODO: Add your control notification handler code here
  m_fTwoSurnames = true;
  m_OldSurname.EnableWindow(true);
  m_NewSurname.EnableWindow(true);
  m_Surname.EnableWindow(false);
}
