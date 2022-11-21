// Dlg29.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "Dlg29.h"

#include "DateFunc.h"
#include "Defaults.h"
#include "FormChange.h"
#include "RNames.h"
#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_Declarant;
extern CString g_ChangeAddr;
extern CString g_ChangePrImPb, g_ChangePrImPbRV;
extern CString g_OldPrImPb, g_NewPrImPb;
extern CString g_DVisn, g_DDozv, g_NVisn, g_NDozv;
extern CString  g_szSurname_DV, g_szName_DV, g_szPatronymic_DV;

/////////////////////////////////////////////////////////////////////////////
// CDlg29 dialog
CDlg29::CDlg29(UINT PrintID, CWnd* pParent /*=NULL*/)
	     :CDialogEx(CDlg29::IDD, pParent) {
	//{{AFX_DATA_INIT(CDlg29)
	//}}AFX_DATA_INIT
  m_PrintID = PrintID;
  m_pForm = (CFormChange*)pParent;
}


void CDlg29::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg29)
  DDX_Control(pDX, IDC_TO_LABEL, m_ToLabel);
	DDX_Control(pDX, IDC_TOMIL, m_To);
	DDX_Control(pDX, IDC_TOROVD, m_ToRovd);
	DDX_Control(pDX, IDC_PRIMPB, m_PrImPb);
	DDX_Control(pDX, IDC_OLPRIMPB, m_OldPrImPb);
	DDX_Control(pDX, IDC_OLDSURNAME, m_OldSurname);
	DDX_Control(pDX, IDC_OLDPATRONYMIC, m_OldPatronymic);
	DDX_Control(pDX, IDC_OLDNAME, m_OldName);
	DDX_Control(pDX, IDC_NUMBER2, m_Number2);
	DDX_Control(pDX, IDC_NUMBER1, m_Number1);
	DDX_Control(pDX, IDC_NEWPRIMPB, m_NewPrImPb);
	DDX_Control(pDX, IDC_DATE2, m_Date2);
	DDX_Control(pDX, IDC_DATE1, m_Date1);
	DDX_Control(pDX, IDC_ADDRESS, m_Address);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg29, CDialogEx)
	//{{AFX_MSG_MAP(CDlg29)
	ON_EN_CHANGE(IDC_DATE1, OnChangeDate1)
	ON_EN_CHANGE(IDC_DATE2, OnChangeDate2)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg29 message handlers
BOOL CDlg29::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO: Add extra initialization here
  CString sToLabel;
  switch(m_PrintID) {
    case ID_PRINT_CHANGE_29:
      sToLabel = _T("До (назва районного (міського) військового комісаріату)");
      m_To.SetWindowText(theIniCache.GetToMil());
      break;
    case ID_PRINT_CHANGE_30: sToLabel = _T("До паспортної служби (назва органу внутрішніх справ)");
      m_To.SetWindowText(theIniCache.GetToROVD());
      break;
  }
  GetDlgItem(IDC_TO_LABEL)->SetWindowText(sToLabel);

  m_ToRovd.SetWindowText(theIniCache.GetToROVD());

  m_Date1.SetDate(COleDateTime::GetCurrentTime());
  m_Date2.SetDate(COleDateTime::GetCurrentTime());

  m_sOldSurname    = m_pForm->m_OldSurname.GetText();
  m_sNewSurname    = m_pForm->m_NewSurname.GetText();
  m_sOldName       = m_pForm->m_OldName.GetCurText();
  m_sNewName       = m_pForm->m_NewName.GetCurText();
  m_sOldPatronymic = m_pForm->m_OldPatronymic.GetCurText();
  m_sNewPatronymic = m_pForm->m_NewPatronymic.GetCurText();

  if ( m_pForm->m_fSex.IsOn() ) {
    m_OldSurname.SetWindowText( ManSurname_DV(m_sOldSurname) );
    m_OldName.SetWindowText( ManName_DV(m_sOldName) );
    m_OldPatronymic.SetWindowText( ManFather_DV(m_sOldPatronymic) );
  }
  else {
    m_OldSurname.SetWindowText( WomanSurname_DV(m_sOldSurname) );
    m_OldName.SetWindowText( WomanName_DV(m_sOldName) );
    m_OldPatronymic.SetWindowText( WomanFather_DV(m_sOldPatronymic) );
  }
  m_Address.SetWindowText( MakeAddress(&m_pForm->m_cmbRPCountry, &m_pForm->m_cmbRPRegion, &m_pForm->m_cmbRPCity, &m_pForm->m_cmbRPDistrict, &m_pForm->m_cmbRPStreet, &m_pForm->m_RPHouse, &m_pForm->m_RPFlat));

  CString s, sOldPrImPb, sNewPrImPb;

  if ( m_sOldSurname != m_sNewSurname ) {
    s = _T("прізвища");
    sOldPrImPb = m_sOldSurname;
    sNewPrImPb = m_sNewSurname;
  }
  if ( m_sOldName != m_sNewName ) {
    if ( !s.IsEmpty() ) {
      s += _T(", ");
      sOldPrImPb += _T(", ");
      sNewPrImPb += _T(", ");
    }
    s += _T("імені");
    sOldPrImPb += m_sOldName;
    sNewPrImPb += m_sNewName;
  }
  if ( m_sOldPatronymic != m_sNewPatronymic ) {
    if ( !s.IsEmpty() ) { s += _T(", ");
      sOldPrImPb += _T(", ");
      sNewPrImPb += _T(", ");
    }
    s += _T("по батькові");
    sOldPrImPb += m_sOldPatronymic;
    sNewPrImPb += m_sNewPatronymic;
  }
  m_PrImPb.SetWindowText(s);
  m_OldPrImPb.SetWindowText(sOldPrImPb);
  m_NewPrImPb.SetWindowText(sNewPrImPb);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg29::OnChangeDate1() {
  COleDateTime odt = m_Date1.GetDate();
  CString s;
  if ( COleDateTime::valid==odt.GetStatus() && (DATE)odt !=(DATE)0) {
    s = GetDateDDMMMYYYYr(odt);
  }
  GetDlgItem(IDC_FULLDATE1)->SetWindowText(s);
}

void CDlg29::OnChangeDate2() {
  COleDateTime odt = m_Date2.GetDate();
  CString s;
  if ( COleDateTime::valid==odt.GetStatus() && (DATE)odt!=(DATE)0) {
    s = GetDateDDMMMYYYYr(odt);
  }
  GetDlgItem(IDC_FULLDATE2)->SetWindowText(s);
}

void CDlg29::OnYes() {
	// TODO: Add your control notification handler code here
  UpdateData(TRUE);
  m_Address.GetWindowText(g_ChangeAddr);

  g_Declarant = MakeFIO(m_sOldSurname, m_sOldName, m_sOldPatronymic);
  g_OldPrImPb.Empty();
  g_NewPrImPb.Empty();
  g_ChangePrImPb.Empty();
  g_ChangePrImPbRV.Empty();

  if ( m_sOldSurname != m_sNewSurname ) {
    g_ChangePrImPb = _T("прізвище");
    g_ChangePrImPbRV = _T("прізвища");
    g_OldPrImPb = m_sOldSurname;
    g_NewPrImPb = m_sNewSurname;
  }
  if ( m_sOldName != m_sNewName ) {
    if ( !g_ChangePrImPb.IsEmpty() ) {
      g_ChangePrImPb += _T(", ");
      g_ChangePrImPbRV += _T(", ");
      g_OldPrImPb += _T(", ");
      g_NewPrImPb += _T(", ");
    }
    g_ChangePrImPb += _T("ім'я");
    g_ChangePrImPbRV += _T("імені");
    g_OldPrImPb += m_sOldName;
    g_NewPrImPb += m_sNewName;
  }
  if ( m_sOldPatronymic != m_sNewPatronymic ) {
    if ( !g_ChangePrImPb.IsEmpty() ) {
      g_ChangePrImPb += _T(", ");
      g_ChangePrImPbRV += _T(", ");
      g_OldPrImPb += _T(", ");
      g_NewPrImPb += _T(", ");
    }
    g_ChangePrImPb += _T("по батькові");
    g_ChangePrImPbRV += _T("по батькові");
    g_OldPrImPb += m_sOldPatronymic;
    g_NewPrImPb += m_sNewPatronymic;
  }
  g_DVisn = GetDateDDMMMYYYYr(m_Date1.GetDate());
  g_DDozv = GetDateDDMMMYYYYr(m_Date2.GetDate());
  m_Number1.GetWindowText(g_NVisn);
  m_Number2.GetWindowText(g_NDozv);

  g_szSurname_DV      = m_OldSurname.GetText();
  g_szName_DV         = m_OldName.GetText();
  g_szPatronymic_DV   = m_OldPatronymic.GetText();

	EndDialog(IDYES);
	
}

BOOL CDlg29::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintDocs"), _T("#PrintRefs"));
  return true;
}
