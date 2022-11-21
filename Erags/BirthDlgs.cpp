// BirthDlgs.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "BirthDlgs.h"

#include "Defaults.h"
#include "RNames.h"

#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString g_Dlg08_sNumber, g_sFullBabyNameRV, g_Dlg08_sWhere;
CString g_sFullFatherNameRV, g_sFullMotherNameRV;
extern  CString g_RagsTo;

/////////////////////////////////////////////////////////////////////////////
// CBirth08 dialog
CBirth08::CBirth08(CWnd* pParent /*=NULL*/)
       :CDialogEx(CBirth08::IDD, pParent) {
  m_nDoc = 4;
	//{{AFX_DATA_INIT(CBirth08)
	m_sNumber = _T("");
	m_sBabyName = _T("");
	m_sTo = _T("");
	m_sWhere = _T("до відділу соцзахисту населення ");
	//}}AFX_DATA_INIT
}

void CBirth08::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBirth08)
	DDX_Control(pDX, IDC_D8_NUMBER, m_Number);
	DDX_Control(pDX, IDC_D8_BABY, m_BabyName);
	DDX_Control(pDX, IDC_D8_TO, m_To);
	DDX_Control(pDX, IDC_D8_WHERE, m_Where);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBirth08, CDialogEx)
	//{{AFX_MSG_MAP(CBirth08)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBirth08 message handlers
BOOL CBirth08::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	if ( m_nDoc==46 ) {
    GetDlgItem(IDC_DOCTO)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_D8_TO)->ShowWindow(SW_SHOW);
  }

  m_Number.SetWindowText(m_sNumber);
  m_BabyName.SetWindowText(m_sBabyName);
  m_Number.SetFocus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBirth08::OnYes() {
	// TODO: Add your control notification handler code here
  UpdateData(TRUE);
  m_BabyName.GetWindowText(m_sBabyName);
  m_Number.GetWindowText(m_sNumber);
  m_Where.GetWindowText(m_sWhere);
  m_To.GetWindowText(m_sTo);
  EndDialog(IDYES);
}
BOOL CBirth08::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintDocs"), _T("#PrintRefs"));
  return true;
}


BOOL BirthDlg08(int nDoc, CWnd* pParent, short nAct, BOOL bSex, LPCTSTR szMemo, LPCTSTR szSurName, LPCTSTR szName, LPCTSTR szFather) {

  int   iDlg;
  // long nIniAct, nIniNum, nRealNum;
	CBirth08 dlg(pParent);

  dlg.m_nDoc = nDoc;

	if ( bSex ) {
    dlg.m_sBabyName = MakeFIO((LPCTSTR)ManSurname_RV(szSurName),
                              (LPCTSTR)ManName_RV(szName),
                              (LPCTSTR)ManFather_RV(szFather));
  }
  else {
    dlg.m_sBabyName = MakeFIO((LPCTSTR)WomanSurname_RV(szSurName),
                              (LPCTSTR)WomanName_RV(szName),
                              (LPCTSTR)WomanFather_RV(szFather));
  }

  dlg.m_sNumber = GetNumFromStr(szMemo, _T("населення "), false );


	iDlg = dlg.DoModal();
	if (iDlg==IDYES) {
    g_Dlg08_sNumber   = dlg.m_sNumber;
    g_sFullBabyNameRV = dlg.m_sBabyName;
    g_Dlg08_sWhere    = dlg.m_sWhere;
	}
	return (iDlg==IDYES || iDlg==IDOK);
}

/////////////////////////////////////////////////////////////////////////////
// CBirth09 dialog
CBirth09::CBirth09(CWnd* pParent /*=NULL*/)
       :CDialogEx(CBirth09::IDD, pParent) {
	//{{AFX_DATA_INIT(CBirth08)
	//}}AFX_DATA_INIT
}

void CBirth09::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBirth11)
	DDX_Control(pDX, IDC_TORAGS, m_To);
	DDX_Control(pDX, IDC_CHILDPIB, m_BabyName);
	DDX_Control(pDX, IDC_FATHERPIB, m_FatherName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBirth09, CDialogEx)
	//{{AFX_MSG_MAP(CBirth09)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBirth09 message handlers
BOOL CBirth09::OnInitDialog() {
	CDialogEx::OnInitDialog();

  m_To.SetWindowText(theIniCache.GetParent());
  m_BabyName.SetWindowText(m_sBabyName);
  m_FatherName.SetWindowText(m_sFatherName);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBirth09::OnYes() {
	// TODO: Add your control notification handler code here
  UpdateData(TRUE);
  m_To.GetWindowText(m_sTo);
  m_BabyName.GetWindowText(m_sBabyName);
  m_FatherName.GetWindowText(m_sFatherName);

  EndDialog(IDYES);
}

BOOL CBirth09::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintDocs"), _T("#PrintRefs"));
  return true;
}



BOOL BirthDlg09(CWnd* pParent, BOOL bSex,
                LPCTSTR szSurName,  LPCTSTR szName,  LPCTSTR szPatronymic,
                LPCTSTR szMSurName, LPCTSTR szMName, LPCTSTR szMPatronymic
               ) {
  
  CBirth09 dlg(pParent);

	if ( bSex ) {
    dlg.m_sBabyName = MakeFIO((LPCTSTR)ManSurname_RV(szSurName),
                              (LPCTSTR)ManName_RV(szName),
                              (LPCTSTR)ManFather_RV(szPatronymic));
  }
  else {
    dlg.m_sBabyName = MakeFIO((LPCTSTR)WomanSurname_RV(szSurName),
                              (LPCTSTR)WomanName_RV(szName),
                              (LPCTSTR)WomanFather_RV(szPatronymic));
  }

  dlg.m_sFatherName = MakeFIO((LPCTSTR)ManSurname_RV(szMSurName),
                              (LPCTSTR)ManName_RV(szMName),
                              (LPCTSTR)ManFather_RV(szMPatronymic)
                             );
  int iDlg = dlg.DoModal();
	if (iDlg==IDYES) {
    g_sFullBabyNameRV   = dlg.m_sBabyName;
    g_RagsTo            = SVRagsC(dlg.m_sTo, RC_RV);
    g_sFullFatherNameRV = dlg.m_sFatherName;
	}
	return (iDlg==IDYES || iDlg==IDOK);
}

/////////////////////////////////////////////////////////////////////////////
// CBirth11 dialog
CBirth11::CBirth11(CWnd* pParent /*=NULL*/)
       :CDialogEx(CBirth11::IDD, pParent) {
	//{{AFX_DATA_INIT(CBirth08)
	//}}AFX_DATA_INIT
  m_fSocProtChanged = false;
}

void CBirth11::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBirth11)
	DDX_Control(pDX, IDC_TOSOCPROT, m_To);
	DDX_Control(pDX, IDC_CHILDPIB, m_BabyName);
	DDX_Control(pDX, IDC_FATHERPIB, m_FatherName);
	DDX_Control(pDX, IDC_MOTHERPIB, m_MotherName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBirth11, CDialogEx)
	//{{AFX_MSG_MAP(CBirth11)
  ON_EN_CHANGE(IDC_TOSOCPROT, OnChangeSocProt)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBirth11 message handlers
BOOL CBirth11::OnInitDialog() {
	CDialogEx::OnInitDialog();

  m_To.SetWindowText(theIniCache.GetToSocProt());	
  m_BabyName.SetWindowText(m_sBabyName);
  m_FatherName.SetWindowText(m_sFatherName);
  m_MotherName.SetWindowText(m_sMotherName);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBirth11::OnChangeSocProt() {
  m_fSocProtChanged = true;
}
void CBirth11::OnYes() {
	// TODO: Add your control notification handler code here
  UpdateData(TRUE);
  m_To.GetWindowText(m_sTo);
  m_BabyName.GetWindowText(m_sBabyName);
  m_FatherName.GetWindowText(m_sFatherName);
  m_MotherName.GetWindowText(m_sMotherName);

  if ( m_fSocProtChanged ) {
    theIniCache.SetToSocProt(m_sTo);
  }

  EndDialog(IDYES);
}
BOOL CBirth11::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintDocs"), _T("#PrintRefs"));
  return true;
}



BOOL BirthDlg11(CWnd* pParent, BOOL bSex,
                LPCTSTR szSurName,  LPCTSTR szName,  LPCTSTR szPatronymic,
                LPCTSTR szMSurName, LPCTSTR szMName, LPCTSTR szMPatronymic,
                LPCTSTR szWSurName, LPCTSTR szWName, LPCTSTR szWPatronymic
               ) {
  
  CBirth11 dlg(pParent);

	if ( bSex ) {
    dlg.m_sBabyName = MakeFIO((LPCTSTR)ManSurname_RV(szSurName),
                              (LPCTSTR)ManName_RV(szName),
                              (LPCTSTR)ManFather_RV(szPatronymic));
  }
  else {
    dlg.m_sBabyName = MakeFIO((LPCTSTR)WomanSurname_RV(szSurName),
                              (LPCTSTR)WomanName_RV(szName),
                              (LPCTSTR)WomanFather_RV(szPatronymic));
  }

  dlg.m_sFatherName = MakeFIO((LPCTSTR)ManSurname_RV(szMSurName),
                              (LPCTSTR)ManName_RV(szMName),
                              (LPCTSTR)ManFather_RV(szMPatronymic)
                             );
  dlg.m_sMotherName = MakeFIO((LPCTSTR)WomanSurname_RV(szWSurName),
                              (LPCTSTR)WomanName_RV(szWName),
                              (LPCTSTR)WomanFather_RV(szWPatronymic)
                             );
  int iDlg = dlg.DoModal();
	if (iDlg==IDYES) {
    g_sFullBabyNameRV   = dlg.m_sBabyName;
    g_Dlg08_sWhere      = dlg.m_sTo;
    g_sFullFatherNameRV = dlg.m_sFatherName;
    g_sFullMotherNameRV = dlg.m_sMotherName;
	}
	return (iDlg==IDYES || iDlg==IDOK);
}

