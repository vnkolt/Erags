// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "SettingsDlg.h"
#include "MainFrm.h"

#include "Defaults.h"
// #include "LoginDlg.h"
#include "RNames.h"
#include "RTFCnv.h"

#include "..\Common\FHelpers.h"
#include "..\Controls\XFontDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define   BTN_BITMAP_WIDTH  56
#define   BTN_BITMAP_HEIGHT 20

/*
#define   CLR_STANDART_LEFT     RGB(212,208,200)
#define   CLR_STANDART_RIGHT    RGB(255,255,255)
*/
#define   CLR_STANDART_LEFT     RGB(236,233,216)
#define   CLR_STANDART_RIGHT    RGB(236,233,216)


#define   CLR_SILVER_LEFT       RGB(0xF4,0xF4,0xF0)
#define   CLR_SILVER_RIGHT      RGB(0xF4,0xF4,0xF0)

#define   CLR_SUMMER_LEFT       RGB( 92,252, 67)
#define   CLR_SUMMER_RIGHT      RGB(255,255,  0)

#define   CLR_REVOLUTION_LEFT   RGB(252,173, 91)
#define   CLR_REVOLUTION_RIGHT  RGB(255,255,255)

#define   CLR_MARINE_LEFT       RGB(175,238,238)
#define   CLR_MARINE_RIGHT      RGB(255,255,255)

#define   CLR_TRANQUIL_LEFT     RGB(192,228,250)
#define   CLR_TRANQUIL_RIGHT    RGB(255,255,255)

#define   CLR_ALPINE_LEFT       RGB(192,214,254)
#define   CLR_ALPINE_RIGHT      RGB(255,255,255)

#define                         TRANS_CLR RGB(255,0,255)

#define FONT_HEIGHT -18

#define MAX_ROWS  128 // need more
extern COLORREF g_clrLeft;
extern COLORREF g_clrRight;
extern BOOL     g_fUseGradient;

// IDS_IN can be: IDS_BIRTH_IN, IDS_MARRIAGE_IN, IDS_DIVORCE_IN, IDS_CHANGE_IN, IDS_DEATH_IN
void OverwriteActTemplate(int IDS_IN, int nPages) {
  CString sDestFile, sSrcFile, sPages, sMsg, sTemlType;
  switch(IDS_IN) {
    case IDS_BIRTH_IN:    sTemlType = _T("НАРОДЖЕННЯ");       break;
    case IDS_MARRIAGE_IN: sTemlType = _T("ШЛЮБ");             break;
    case IDS_DIVORCE_IN:  sTemlType = _T("РОЗІРВАННЯ ШЛЮБУ"); break;
    case IDS_CHANGE_IN:   sTemlType = _T("ЗМІНУ ІМЕНІ");      break;
    case IDS_DEATH_IN:    sTemlType = _T("СМЕРТЬ");           break;
    default:
      ASSERT(FALSE);
  }
  sDestFile.Format(IDS_IN, theApp.m_sTemplatePath, _T("Act") );
  sSrcFile = sDestFile;
  if ( nPages == 3 ) {
    sPages = _T("_1B");
  }
  else {
    sPages.Format(_T("_%d"), nPages);
  }
  int nDot = sDestFile.ReverseFind('.');
  sSrcFile.Insert(nDot, sPages);

  MakeInOutExt(sSrcFile, sDestFile);

  if ( FALSE==FileExists(sSrcFile) ) {
    sMsg.Format(_T("Помилка підчас виконання операції копіювання шаблону.\n")
                _T("Відсутній файл шаблону \"%s\"."), sSrcFile);
    MessageBox(AfxGetMainWnd()->m_hWnd, sMsg, _T("ЕРАГС"), MB_OK|MB_ICONSTOP);
    return;
  }
  if ( FALSE==CopyFile(sSrcFile, sDestFile, FALSE) ) {
    sMsg.Format(_T("Помилка підчас виконання операції копіювання шаблону.\n")
                _T("Не вдалося переписати файл шаблону \"%s\"."), sDestFile);
    MessageBox(AfxGetMainWnd()->m_hWnd, sMsg, _T("ЕРАГС"), MB_OK|MB_ICONSTOP);
    return;
  }
  sMsg.Format(_T("Файл шаблону \"%s\" переписано.\n")
              _T("Рекомендується перевірити новий шаблон для АЗ про %s."), sDestFile, sTemlType);
  MessageBox(AfxGetMainWnd()->m_hWnd, sMsg, _T("ЕРАГС"), MB_OK|MB_ICONINFORMATION);
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageCommon property page
IMPLEMENT_DYNCREATE(CPropertyPageCommon, CPropertyPageBG)
CPropertyPageCommon::CPropertyPageCommon()
                    :CPropertyPageBG(CPropertyPageCommon::IDD) {
	//{{AFX_DATA_INIT(CPropertyPageCommon)
	//}}AFX_DATA_INIT
}

CPropertyPageCommon::~CPropertyPageCommon() {
}

void CPropertyPageCommon::DoDataExchange(CDataExchange* pDX) {
	CPropertyPageBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageCommon)
  DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_FRAME2, m_Frame2);
	DDX_Control(pDX, IDC_COUNTRY, m_Country);
	DDX_Control(pDX, IDC_REGION, m_Region);
	DDX_Control(pDX, IDC_DISTRICT, m_District);
	DDX_Control(pDX, IDC_CITY, m_City);
	DDX_Control(pDX, IDC_RAGS, m_Rags);
  // DDX_Control(pDX, IDC_OKPO, m_OKPO);
	DDX_Control(pDX, IDC_PARENT, m_Parent);
	DDX_Control(pDX, IDC_BOSS, m_Boss);
  DDX_Control(pDX, IDC_POSADA, m_Posada);
  DDX_Control(pDX, IDC_PIBPO, m_PIBPO);
	DDX_Control(pDX, IDC_BYUMVS, m_ByUMVS);
	DDX_Control(pDX, IDC_TOUMVS, m_ToUMVS);
	DDX_Control(pDX, IDC_BYMIL, m_ByMil);
	DDX_Control(pDX, IDC_TOMIL, m_ToMil);
	DDX_Control(pDX, IDC_BYCOURT, m_ByCourt);
	DDX_Control(pDX, IDC_TOTAX, m_ToTax);
  DDX_Control(pDX, IDC_TOSOCPROT, m_ToSocProt);
	DDX_Control(pDX, IDC_RADIO_BIRTHES, m_rbBirthes);
	DDX_Control(pDX, IDC_RADIO_MARRIAGES, m_rbMarriges);
	DDX_Control(pDX, IDC_RADIO_DIVORCES, m_rbDivorces);
	DDX_Control(pDX, IDC_RADIO_CHANGES, m_rbChanges);
	DDX_Control(pDX, IDC_RADIO_DEATHES, m_rbDeathes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyPageCommon, CPropertyPageBG)
	//{{AFX_MSG_MAP(CPropertyPageCommon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CPropertyPageCommon::SetRadio(UINT uForm) {
  int btn[5] = {IDC_RADIO_BIRTHES, IDC_RADIO_MARRIAGES, IDC_RADIO_DIVORCES, IDC_RADIO_CHANGES, IDC_RADIO_DEATHES};
  CheckRadioButton(IDC_RADIO_BIRTHES, IDC_RADIO_DEATHES, btn[uForm-1]);

}
UINT CPropertyPageCommon::GetRadio() {
  int nCheckedBtnId = GetCheckedRadioButton(IDC_RADIO_BIRTHES, IDC_RADIO_DEATHES);
  if ( nCheckedBtnId )
    return ( nCheckedBtnId - IDC_RADIO_BIRTHES + 1);
  return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CPropertyPageCommon message handlers;
BOOL CPropertyPageCommon::OnInitDialog() {

	CPropertyPageBG::OnInitDialog();

  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_rbBirthes .SetRadioImageList(&m_RadioIL); m_rbBirthes .SetRadio(IDC_RADIO_BIRTHES, IDC_RADIO_DEATHES);
    m_rbMarriges.SetRadioImageList(&m_RadioIL); m_rbMarriges.SetRadio(IDC_RADIO_BIRTHES, IDC_RADIO_DEATHES);
    m_rbDivorces.SetRadioImageList(&m_RadioIL); m_rbDivorces.SetRadio(IDC_RADIO_BIRTHES, IDC_RADIO_DEATHES);
    m_rbChanges .SetRadioImageList(&m_RadioIL); m_rbChanges .SetRadio(IDC_RADIO_BIRTHES, IDC_RADIO_DEATHES);
    m_rbDeathes .SetRadioImageList(&m_RadioIL); m_rbDeathes .SetRadio(IDC_RADIO_BIRTHES, IDC_RADIO_DEATHES);
  }

	// TODO: Add extra initialization here
  m_Country.SetWindowText( theIniCache.GetCOUNTRY() );
  m_Region.SetWindowText( theIniCache.GetREGION() );
  m_District.SetWindowText( theIniCache.GetDISTRICT() );
  m_City.SetWindowText( theIniCache.GetCITY() );
  m_Rags.SetWindowText( theIniCache.GetRAGS() );
  // m_OKPO.SetWindowText( theIniCache.GetOKPO() );
  m_Parent.SetWindowText( theIniCache.GetParent() );

  m_Boss.SetWindowText( theIniCache.GetBoss() );
  m_Posada.SetWindowText( theIniCache.GetPosada() );
  m_PIBPO.SetWindowText( theIniCache.GetPIBPO() );
  
  m_ByUMVS.SetWindowText( theIniCache.GetByROVD() );
  m_ToUMVS.SetWindowText( theIniCache.GetToROVD() );
  m_ByMil.SetWindowText( theIniCache.GetByMil() );
  m_ToMil.SetWindowText( theIniCache.GetToMil() );
  m_ByCourt.SetWindowText( theIniCache.GetByCourt() );
  m_ToTax.SetWindowText( theIniCache.GetToTax() );
  m_ToSocProt.SetWindowText( theIniCache.GetToSocProt() );

  UINT uForm = theApp.GetDefaultForm();
  SetRadio(uForm);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CPropertyPageCommon::OnOK() {
	// TODO: Add your specialized code here and/or call the base class
	UpdateData( TRUE );
/*
  theIniCache.SetCOUNTRY( m_Country.GetText() );
  theIniCache.SetREGION(  m_Region.GetText() );
  theIniCache.SetDISTRICT( m_District.GetText() );
  theIniCache.SetCITY( m_City.GetText() );
*/
  theIniCache.SetRAGS( m_Rags.GetText() );
  // theIniCache.SetOKPO( m_OKPO.GetText() );

  theIniCache.SetBoss  ( m_Boss.GetText() );
  theIniCache.SetPosada( m_Posada.GetText() );
  theIniCache.SetPIBPO( m_PIBPO.GetText() );
  
  theIniCache.SetParent( m_Parent.GetText() );
  theIniCache.SetByROVD( m_ByUMVS.GetText() );
  theIniCache.SetToROVD( m_ToUMVS.GetText() );
  theIniCache.SetByMil( m_ByMil.GetText() );
  theIniCache.SetToMil( m_ToMil.GetText() );
  theIniCache.SetByCourt( m_ByCourt.GetText() );
  theIniCache.SetToTax( m_ToTax.GetText() );
  theIniCache.SetToSocProt( m_ToSocProt.GetText() );

  UINT uForm  = GetRadio();
  theApp.SetDefaultForm(uForm);

	CPropertyPageBG::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageBirth property page
IMPLEMENT_DYNCREATE(CPropertyPageBirth, CPropertyPageBG)
CPropertyPageBirth::CPropertyPageBirth()
                   :CPropertyPageBG(CPropertyPageBirth::IDD) {
	//{{AFX_DATA_INIT(CPropertyPageBirth)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropertyPageBirth::~CPropertyPageBirth() {
}

void CPropertyPageBirth::DoDataExchange(CDataExchange* pDX) {
	CPropertyPageBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageBirth)
  DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_FRAME2, m_Frame2);
  DDX_Control(pDX, IDC_FRAME3, m_Frame3);
  DDX_Control(pDX, IDC_FRAME4, m_Frame4);
	DDX_Control(pDX, IDC_SERIA, m_Seria);
	DDX_Control(pDX, IDC_REGION, m_Region);
	DDX_Control(pDX, IDC_DISTRICT, m_District);
	DDX_Control(pDX, IDC_COUNTRY, m_Country);
	DDX_Control(pDX, IDC_CITY, m_City);
	DDX_Control(pDX, IDC_ONE_PAGE, m_rbOnePage);
	DDX_Control(pDX, IDC_TWO_PAGE, m_rbTwoPages);
  DDX_Control(pDX, IDC_ONE_PAGE_B, m_rbOnePageB);
  DDX_Control(pDX, IDC_ACT, m_ActImage);
	DDX_Control(pDX, IDC_CHILD_BP_REGION_CHECK, m_chkRegion);
	DDX_Control(pDX, IDC_CHILD_BP_DISTRICT_CHECK, m_chkDistrict);
	DDX_Control(pDX, IDC_CHILD_BP_COUNTRY_CHECK, m_chkCountry);
	DDX_Control(pDX, IDC_CHILD_BP_CITY_CHECK, m_chkCity);
	DDX_Control(pDX, IDC_CITIZENSHIP_ACT, m_chkCitizenshipAct);
	DDX_Control(pDX, IDC_CITIZENSHIP_CERTS, m_chkCitizenshipCert);
	DDX_Control(pDX, IDC_CITIZENSHIP_OTHER, m_chkDistrictOther);
  DDX_Control(pDX, IDC_DEFNOTICE, m_DefNotice);
  DDX_Control(pDX, IDC_DEFNOTICE2, m_DefNotice2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyPageBirth, CPropertyPageBG)
	//{{AFX_MSG_MAP(CPropertyPageBirth)
  ON_BN_CLICKED(IDC_ONE_PAGE,  OnOnePage)
  ON_BN_CLICKED(IDC_TWO_PAGE,  OnTwoPage)
  ON_BN_CLICKED(IDC_ONE_PAGE_B,OnOnePageB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageBirth message handlers
BOOL CPropertyPageBirth::OnInitDialog() {
	CPropertyPageBG::OnInitDialog();

  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_chkCountry.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkRegion.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkDistrict.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkCity.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkCitizenshipAct.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkCitizenshipCert.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkDistrictOther.SetCheckBoxImageList(&m_CheckBoxIL);
  }
  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_rbOnePage .SetRadioImageList(&m_RadioIL); m_rbOnePage .SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
    m_rbTwoPages.SetRadioImageList(&m_RadioIL); m_rbTwoPages.SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
    m_rbOnePageB.SetRadioImageList(&m_RadioIL); m_rbOnePageB.SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
  }
	
	m_Country.SetWindowText( theIniCache.GetBIRTH_BP_COUNTRY() );
  m_chkCountry.SetCheck( theIniCache.GetBIRTH_BP_COUNTRY_CHECK() );

  m_Region.SetWindowText( theIniCache.GetBIRTH_BP_REGION() );
  m_chkRegion.SetCheck( theIniCache.GetBIRTH_BP_REGION_CHECK() );

  m_District.SetWindowText( theIniCache.GetBIRTH_BP_DISTRICT() );
  m_chkDistrict.SetCheck( theIniCache.GetBIRTH_BP_DISTRICT_CHECK() );

  m_City.SetWindowText( theIniCache.GetBIRTH_BP_CITY() );
  m_chkCity.SetCheck( theIniCache.GetBIRTH_BP_CITY_CHECK() );

  m_Seria.SetWindowText( theIniCache.GetBIRTH_Seria() );

  UINT nID;
  switch( theIniCache.GetBIRTH_NActPages() ) {
    case 3 : nID = IDC_ONE_PAGE_B; OnOnePageB(); break;
    case 2 : nID = IDC_TWO_PAGE;   OnTwoPage();  break;
    default: nID = IDC_ONE_PAGE;   OnOnePage();  break;
  }
  CheckRadioButton(IDC_ONE_PAGE, IDC_ONE_PAGE_B, nID);

  UINT nPrintCitizen = theIniCache.GetPrintCitizenBIRTH();
  m_chkCitizenshipAct.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_ACT)==PRINT_CITIZENSHIP_ACT);
  m_chkCitizenshipCert.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_CERT)==PRINT_CITIZENSHIP_CERT);
  m_chkDistrictOther.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_OTHER)==PRINT_CITIZENSHIP_OTHER);

  m_DefNotice.SetWindowText( theIniCache.GetBIRTH_DefNotice() );
  m_DefNotice2.SetWindowText( theIniCache.GetBIRTH_DefNotice2() );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageBirth::OnOnePage() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTA1);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageBirth::OnTwoPage() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTA2);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageBirth::OnOnePageB() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTB);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageBirth::OnOK() {
	// TODO: Add your specialized code here and/or call the base class
  UpdateData(TRUE);

	theIniCache.SetBIRTH_BP_COUNTRY( m_Country.GetText() );
  theIniCache.SetBIRTH_BP_COUNTRY_CHECK( m_chkCountry.GetCheck() );

  theIniCache.SetBIRTH_BP_REGION( m_Region.GetText() );
  theIniCache.SetBIRTH_BP_REGION_CHECK( m_chkRegion.GetCheck() );

  theIniCache.SetBIRTH_BP_DISTRICT( m_District.GetText() );
  theIniCache.SetBIRTH_BP_DISTRICT_CHECK( m_chkDistrict.GetCheck() );

  theIniCache.SetBIRTH_BP_CITY( m_City.GetText() );
  theIniCache.SetBIRTH_BP_CITY_CHECK( m_chkCity.GetCheck() );

  theIniCache.SetBIRTH_Seria( m_Seria.GetText() );

  int nActPages = 1 + GetCheckedRadioButton(IDC_ONE_PAGE, IDC_ONE_PAGE_B) - IDC_ONE_PAGE;
  if ( theIniCache.GetBIRTH_NActPages() != nActPages ) {
    theIniCache.SetBIRTH_NActPages(nActPages);
    OverwriteActTemplate(IDS_BIRTH_IN, nActPages);
  }

  UINT nPrintCitizen = 0;
  if ( m_chkCitizenshipAct.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_ACT;
  if ( m_chkCitizenshipCert.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_CERT;
  if ( m_chkDistrictOther.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_OTHER;
  theIniCache.SetPrintCitizenBIRTH(nPrintCitizen);

  theIniCache.SetBIRTH_DefNotice(m_DefNotice.GetText());
  theIniCache.SetBIRTH_DefNotice2(m_DefNotice2.GetText());


	CPropertyPageBG::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageMarriage property page
IMPLEMENT_DYNCREATE(CPropertyPageMarriage, CPropertyPageBG)

CPropertyPageMarriage::CPropertyPageMarriage() : CPropertyPageBG(CPropertyPageMarriage::IDD) {
	//{{AFX_DATA_INIT(CPropertyPageMarriage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropertyPageMarriage::~CPropertyPageMarriage() {
}

void CPropertyPageMarriage::DoDataExchange(CDataExchange* pDX) {
	CPropertyPageBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageMarriage)
  DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_FRAME2, m_Frame2);
  DDX_Control(pDX, IDC_FRAME3, m_Frame3);
	DDX_Control(pDX, IDC_ONE_PAGE, m_rbOnePage);
	DDX_Control(pDX, IDC_TWO_PAGE, m_rbTwoPages);
  DDX_Control(pDX, IDC_ONE_PAGE_B, m_rbOnePageB);
  DDX_Control(pDX, IDC_ACT, m_ActImage);
	DDX_Control(pDX, IDC_SERIA, m_Seria);
  DDX_Control(pDX, IDC_DEFNOTICE, m_DefNotice);
	DDX_Control(pDX, IDC_CITIZENSHIP_ACT, m_chkCitizenshipAct);
	DDX_Control(pDX, IDC_CITIZENSHIP_CERTS, m_chkCitizenshipCert);
	DDX_Control(pDX, IDC_CITIZENSHIP_OTHER, m_chkDistrictOther);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyPageMarriage, CPropertyPageBG)
	//{{AFX_MSG_MAP(CPropertyPageMarriage)
  ON_BN_CLICKED(IDC_ONE_PAGE,  OnOnePage)
  ON_BN_CLICKED(IDC_TWO_PAGE,  OnTwoPage)
  ON_BN_CLICKED(IDC_ONE_PAGE_B,OnOnePageB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageMarriage message handlers
BOOL CPropertyPageMarriage::OnInitDialog() {
	CPropertyPageBG::OnInitDialog();

  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_chkCitizenshipAct.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkCitizenshipCert.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkDistrictOther.SetCheckBoxImageList(&m_CheckBoxIL);
  }
  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_rbOnePage .SetRadioImageList(&m_RadioIL); m_rbOnePage .SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
    m_rbTwoPages.SetRadioImageList(&m_RadioIL); m_rbTwoPages.SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
    m_rbOnePageB.SetRadioImageList(&m_RadioIL); m_rbOnePageB.SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
  }

	m_Seria.SetWindowText( theIniCache.GetMARRIAGE_Seria() );
  UINT nID;
  switch( theIniCache.GetMARRIAGE_NActPages() ) {
    case 3 : nID = IDC_ONE_PAGE_B; OnOnePageB(); break;
    case 2 : nID = IDC_TWO_PAGE;   OnTwoPage();  break;
    default: nID = IDC_ONE_PAGE;   OnOnePage();  break;
  }
  CheckRadioButton(IDC_ONE_PAGE, IDC_ONE_PAGE_B, nID);

  UINT nPrintCitizen = theIniCache.GetPrintCitizenMARRIAGE();
  m_chkCitizenshipAct.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_ACT)==PRINT_CITIZENSHIP_ACT);
  m_chkCitizenshipCert.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_CERT)==PRINT_CITIZENSHIP_CERT);
  m_chkDistrictOther.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_OTHER)==PRINT_CITIZENSHIP_OTHER);

  m_DefNotice.SetWindowText( theIniCache.GetMARRIAGE_DefNotice() );


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageMarriage::OnOnePage() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTA1);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageMarriage::OnTwoPage() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTA2);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageMarriage::OnOnePageB() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTB);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageMarriage::OnOK() {
	UpdateData(TRUE);
  theIniCache.SetMARRIAGE_Seria( m_Seria.GetText() );
  int nActPages = 1 + GetCheckedRadioButton(IDC_ONE_PAGE, IDC_ONE_PAGE_B) - IDC_ONE_PAGE;
	CPropertyPageBG::OnOK();
  if ( theIniCache.GetMARRIAGE_NActPages() != nActPages ) {
    theIniCache.SetMARRIAGE_NActPages(nActPages);
    OverwriteActTemplate(IDS_MARRIAGE_IN, nActPages);
  }
  UINT nPrintCitizen = 0;
  if ( m_chkCitizenshipAct.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_ACT;
  if ( m_chkCitizenshipCert.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_CERT;
  if ( m_chkDistrictOther.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_OTHER;
  theIniCache.SetPrintCitizenMARRIAGE(nPrintCitizen);

  theIniCache.SetMARRIAGE_DefNotice(m_DefNotice.GetText());

	CPropertyPageBG::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageChange property page

IMPLEMENT_DYNCREATE(CPropertyPageChange, CPropertyPageBG)

CPropertyPageChange::CPropertyPageChange() : CPropertyPageBG(CPropertyPageChange::IDD) {
	//{{AFX_DATA_INIT(CPropertyPageChange)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropertyPageChange::~CPropertyPageChange() {
}

void CPropertyPageChange::DoDataExchange(CDataExchange* pDX) {
	CPropertyPageBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageChange)
  DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_FRAME2, m_Frame2);
	DDX_Control(pDX, IDC_ONE_PAGE, m_rbOnePage);
	DDX_Control(pDX, IDC_TWO_PAGE, m_rbTwoPages);
  DDX_Control(pDX, IDC_ONE_PAGE_B, m_rbOnePageB);
  DDX_Control(pDX, IDC_ACT, m_ActImage);
	DDX_Control(pDX, IDC_SERIA, m_Seria);
	DDX_Control(pDX, IDC_CITIZENSHIP_ACT, m_chkCitizenshipAct);
	DDX_Control(pDX, IDC_CITIZENSHIP_CERTS, m_chkCitizenshipCert);
	DDX_Control(pDX, IDC_CITIZENSHIP_OTHER, m_chkDistrictOther);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyPageChange, CPropertyPageBG)
	//{{AFX_MSG_MAP(CPropertyPageChange)
  ON_BN_CLICKED(IDC_ONE_PAGE,  OnOnePage)
  ON_BN_CLICKED(IDC_TWO_PAGE,  OnTwoPage)
  ON_BN_CLICKED(IDC_ONE_PAGE_B,OnOnePageB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageChange message handlers
BOOL CPropertyPageChange::OnInitDialog() {
	CPropertyPageBG::OnInitDialog();

  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_chkCitizenshipAct.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkCitizenshipCert.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkDistrictOther.SetCheckBoxImageList(&m_CheckBoxIL);
  }
  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_rbOnePage .SetRadioImageList(&m_RadioIL); m_rbOnePage .SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
    m_rbTwoPages.SetRadioImageList(&m_RadioIL); m_rbTwoPages.SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
    m_rbOnePageB.SetRadioImageList(&m_RadioIL); m_rbOnePageB.SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
  }
	
	m_Seria.SetWindowText( theIniCache.GetCHANGE_Seria() );

  UINT nID;
  switch( theIniCache.GetCHANGE_NActPages() ) {
    case 3 : nID = IDC_ONE_PAGE_B; OnOnePageB(); break;
    case 2 : nID = IDC_TWO_PAGE;   OnTwoPage();  break;
    default: nID = IDC_ONE_PAGE;   OnOnePage();  break;
  }
  CheckRadioButton(IDC_ONE_PAGE, IDC_ONE_PAGE_B, nID);

  UINT nPrintCitizen = theIniCache.GetPrintCitizenCHANGE();
  m_chkCitizenshipAct.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_ACT)==PRINT_CITIZENSHIP_ACT);
  m_chkCitizenshipCert.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_CERT)==PRINT_CITIZENSHIP_CERT);
  m_chkDistrictOther.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_OTHER)==PRINT_CITIZENSHIP_OTHER);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageChange::OnOnePage() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTA1);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageChange::OnTwoPage() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTA2);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageChange::OnOnePageB() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTB);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageChange::OnOK() {
	UpdateData( TRUE );
  theIniCache.SetCHANGE_Seria( m_Seria.GetText() );
  int nActPages = 1 + GetCheckedRadioButton(IDC_ONE_PAGE, IDC_ONE_PAGE_B) - IDC_ONE_PAGE;
  if ( theIniCache.GetCHANGE_NActPages() != nActPages ) {
    theIniCache.SetCHANGE_NActPages(nActPages);
    OverwriteActTemplate(IDS_CHANGE_IN, nActPages);
  }
  UINT nPrintCitizen = 0;
  if ( m_chkCitizenshipAct.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_ACT;
  if ( m_chkCitizenshipCert.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_CERT;
  if ( m_chkDistrictOther.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_OTHER;
  theIniCache.SetPrintCitizenCHANGE(nPrintCitizen);
	CPropertyPageBG::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageDeath property page

IMPLEMENT_DYNCREATE(CPropertyPageDeath, CPropertyPageBG)

CPropertyPageDeath::CPropertyPageDeath() : CPropertyPageBG(CPropertyPageDeath::IDD) {
	//{{AFX_DATA_INIT(CPropertyPageDeath)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropertyPageDeath::~CPropertyPageDeath() {
}

void CPropertyPageDeath::DoDataExchange(CDataExchange* pDX) {
	CPropertyPageBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageDeath)
  DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_FRAME2, m_Frame2);
  DDX_Control(pDX, IDC_FRAME3, m_Frame3);
	DDX_Control(pDX, IDC_ONE_PAGE, m_rbOnePage);
	DDX_Control(pDX, IDC_TWO_PAGE, m_rbTwoPages);
  DDX_Control(pDX, IDC_ONE_PAGE_B, m_rbOnePageB);
  DDX_Control(pDX, IDC_ACT, m_ActImage);
	DDX_Control(pDX, IDC_SERIA, m_Seria);
	DDX_Control(pDX, IDC_CITIZENSHIP_ACT, m_chkCitizenshipAct);
	DDX_Control(pDX, IDC_CITIZENSHIP_CERTS, m_chkCitizenshipCert);
	DDX_Control(pDX, IDC_CITIZENSHIP_OTHER, m_chkDistrictOther);
  DDX_Control(pDX, IDC_DEFNOTICE, m_DefNotice);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyPageDeath, CPropertyPageBG)
	//{{AFX_MSG_MAP(CPropertyPageDeath)
  ON_BN_CLICKED(IDC_ONE_PAGE,  OnOnePage)
  ON_BN_CLICKED(IDC_TWO_PAGE,  OnTwoPage)
  ON_BN_CLICKED(IDC_ONE_PAGE_B,OnOnePageB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageDeath message handlers
BOOL CPropertyPageDeath::OnInitDialog() {
	CPropertyPageBG::OnInitDialog();

  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_chkCitizenshipAct.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkCitizenshipCert.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkDistrictOther.SetCheckBoxImageList(&m_CheckBoxIL);
  }
  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_rbOnePage .SetRadioImageList(&m_RadioIL); m_rbOnePage .SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
    m_rbTwoPages.SetRadioImageList(&m_RadioIL); m_rbTwoPages.SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
    m_rbOnePageB.SetRadioImageList(&m_RadioIL); m_rbOnePageB.SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
  }

	m_Seria.SetWindowText( theIniCache.GetDEATH_Seria() );

  UINT nID;
  switch( theIniCache.GetDEATH_NActPages() ) {
    case 3 : nID = IDC_ONE_PAGE_B; OnOnePageB(); break;
    case 2 : nID = IDC_TWO_PAGE;   OnTwoPage();  break;
    default: nID = IDC_ONE_PAGE;   OnOnePage();  break;
  }
  CheckRadioButton(IDC_ONE_PAGE, IDC_ONE_PAGE_B, nID);

  UINT nPrintCitizen = theIniCache.GetPrintCitizenDEATH();
  m_chkCitizenshipAct.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_ACT)==PRINT_CITIZENSHIP_ACT);
  m_chkCitizenshipCert.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_CERT)==PRINT_CITIZENSHIP_CERT);
  m_chkDistrictOther.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_OTHER)==PRINT_CITIZENSHIP_OTHER);

  m_DefNotice.SetWindowText( theIniCache.GetDEATH_DefNotice() );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageDeath::OnOnePage() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTA1);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageDeath::OnTwoPage() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTA2);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageDeath::OnOnePageB() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTB);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageDeath::OnOK() {
	// TODO: Add your specialized code here and/or call the base class
  UpdateData( TRUE );
  theIniCache.SetDEATH_Seria( m_Seria.GetText() );
  int nActPages = 1 + GetCheckedRadioButton(IDC_ONE_PAGE, IDC_ONE_PAGE_B) - IDC_ONE_PAGE;
  if ( theIniCache.GetDEATH_NActPages() != nActPages ) {
    theIniCache.SetDEATH_NActPages(nActPages);
    OverwriteActTemplate(IDS_DEATH_IN, nActPages);
  }
  UINT nPrintCitizen = 0;
  if ( m_chkCitizenshipAct.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_ACT;
  if ( m_chkCitizenshipCert.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_CERT;
  if ( m_chkDistrictOther.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_OTHER;
  theIniCache.SetPrintCitizenDEATH(nPrintCitizen);

  theIniCache.SetDEATH_DefNotice(m_DefNotice.GetText());

	CPropertyPageBG::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageDivorce property page
IMPLEMENT_DYNCREATE(CPropertyPageDivorce, CPropertyPageBG)
CPropertyPageDivorce::CPropertyPageDivorce() : CPropertyPageBG(CPropertyPageDivorce::IDD) {
	//{{AFX_DATA_INIT(CPropertyPageDivorce)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropertyPageDivorce::~CPropertyPageDivorce() {
}

void CPropertyPageDivorce::DoDataExchange(CDataExchange* pDX) {
	CPropertyPageBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageDivorce)
	DDX_Control(pDX, IDC_FRAME1, m_Frame1);
	DDX_Control(pDX, IDC_FRAME2, m_Frame2);
	DDX_Control(pDX, IDC_FRAME3, m_Frame3);
	DDX_Control(pDX, IDC_FRAME4, m_Frame4);
	DDX_Control(pDX, IDC_ONE_PAGE, m_rbOnePage);
	DDX_Control(pDX, IDC_TWO_PAGE, m_rbTwoPages);
  DDX_Control(pDX, IDC_ONE_PAGE_B, m_rbOnePageB);
  DDX_Control(pDX, IDC_ACT, m_ActImage);
	DDX_Control(pDX, IDC_NOCHILDREN, m_NoChildren);
  DDX_Control(pDX, IDC_SINGLECHILD, m_SingleChild);
	DDX_Control(pDX, IDC_SERIA, m_Seria);
	DDX_Control(pDX, IDC_CITIZENSHIP_ACT, m_chkCitizenshipAct);
	DDX_Control(pDX, IDC_CITIZENSHIP_CERTS, m_chkCitizenshipCert);
	DDX_Control(pDX, IDC_CITIZENSHIP_OTHER, m_chkDistrictOther);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyPageDivorce, CPropertyPageBG)
	//{{AFX_MSG_MAP(CPropertyPageDivorce)
  ON_BN_CLICKED(IDC_ONE_PAGE,  OnOnePage)
  ON_BN_CLICKED(IDC_TWO_PAGE,  OnTwoPage)
  ON_BN_CLICKED(IDC_ONE_PAGE_B,OnOnePageB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageDivorce message handlers
BOOL CPropertyPageDivorce::OnInitDialog() {
	CPropertyPageBG::OnInitDialog();

  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_chkCitizenshipAct.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkCitizenshipCert.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkDistrictOther.SetCheckBoxImageList(&m_CheckBoxIL);
  }
  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_rbOnePage .SetRadioImageList(&m_RadioIL); m_rbOnePage .SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
    m_rbTwoPages.SetRadioImageList(&m_RadioIL); m_rbTwoPages.SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
    m_rbOnePageB.SetRadioImageList(&m_RadioIL); m_rbOnePageB.SetRadio(IDC_ONE_PAGE, IDC_ONE_PAGE_B);
  }

	m_Seria.SetWindowText( theIniCache.GetDIVORCE_Seria() );
  m_NoChildren.SetWindowText( theIniCache.GetDIVORCE_NoChildren() );
  m_SingleChild.SetWindowText( theIniCache.GetDIVORCE_SingleChild() );

  UINT nID;
  switch( theIniCache.GetDIVORCE_NActPages() ) {
    case 3 : nID = IDC_ONE_PAGE_B; OnOnePageB(); break;
    case 2 : nID = IDC_TWO_PAGE;   OnTwoPage();  break;
    default: nID = IDC_ONE_PAGE;   OnOnePage();  break;
  }
  CheckRadioButton(IDC_ONE_PAGE, IDC_ONE_PAGE_B, nID);


  UINT nPrintCitizen = theIniCache.GetPrintCitizenDIVORCE();
  m_chkCitizenshipAct.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_ACT)==PRINT_CITIZENSHIP_ACT);
  m_chkCitizenshipCert.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_CERT)==PRINT_CITIZENSHIP_CERT);
  m_chkDistrictOther.SetCheck( (nPrintCitizen & PRINT_CITIZENSHIP_OTHER)==PRINT_CITIZENSHIP_OTHER);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPropertyPageDivorce::OnOnePage() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTA1);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageDivorce::OnTwoPage() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTA2);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageDivorce::OnOnePageB() {
  m_ActBitmap.DeleteObject();
  m_ActBitmap.LoadBitmap(IDB_ACTB);
  m_ActImage.SetBitmap(m_ActBitmap);
}

void CPropertyPageDivorce::OnOK() {
  UpdateData( TRUE );
  theIniCache.SetDIVORCE_Seria( m_Seria.GetText() );
  theIniCache.SetDIVORCE_NoChildren( m_NoChildren.GetText() );
  int nActPages = 1 + GetCheckedRadioButton(IDC_ONE_PAGE, IDC_ONE_PAGE_B) - IDC_ONE_PAGE;
  if ( theIniCache.GetDIVORCE_NActPages() != nActPages ) {
    theIniCache.SetDIVORCE_NActPages(nActPages);
    OverwriteActTemplate(IDS_DIVORCE_IN, nActPages);
  }
  UINT nPrintCitizen = 0;
  if ( m_chkCitizenshipAct.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_ACT;
  if ( m_chkCitizenshipCert.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_CERT;
  if ( m_chkDistrictOther.GetCheck() )
    nPrintCitizen |= PRINT_CITIZENSHIP_OTHER;
  theIniCache.SetPrintCitizenDIVORCE(nPrintCitizen);

	CPropertyPageBG::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageThemes
IMPLEMENT_DYNCREATE(CPropertyPageThemes, CPropertyPageBG)
CPropertyPageThemes::CPropertyPageThemes() : CPropertyPageBG(CPropertyPageThemes::IDD) {
	//{{AFX_DATA_INIT(CPropertyPageThemes)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_clrLeft       = g_clrLeft;
  m_clrRight      = g_clrRight;
  m_fUseGradient  = g_clrLeft != g_clrRight;
  m_fColorChanged = m_fFontChanged = false;
  m_fUseGradientSaved = m_fUseGradient;
}

CPropertyPageThemes::~CPropertyPageThemes() {
}
void CPropertyPageThemes::DoDataExchange(CDataExchange* pDX) {
	CPropertyPageBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageThemes)
  DDX_Control(pDX, IDC_FRAME1,          m_Frame1);
  DDX_Control(pDX, IDC_FRAME2,          m_Frame2);
  DDX_Control(pDX, IDC_CHECK_USEGRADIENT, m_chkGradient);
  DDX_Control(pDX, IDC_RADIO_STANDART,  m_rbStandart);
  DDX_Control(pDX, IDC_RADIO_SILVER,    m_rdSilver);
  DDX_Control(pDX, IDC_RADIO_SUMMER,    m_rdSummer);
  DDX_Control(pDX, IDC_RADIO_REVOLUTION,m_rdRevolution);
  DDX_Control(pDX, IDC_RADIO_TRANQUIL,  m_rdTranquil);
  DDX_Control(pDX, IDC_RADIO_ALPINE,    m_rdAlpine);
  DDX_Control(pDX, IDC_CLRPICKER_LEFT,  m_ColourBoxLeft);
  DDX_Control(pDX, IDC_CLRPICKER_RIGHT, m_ColourBoxRight);
	//}}AFX_DATA_MAP
  DDX_ColourPicker(pDX, IDC_CLRPICKER_LEFT,  m_clrLeft);
  DDX_ColourPicker(pDX, IDC_CLRPICKER_RIGHT, m_clrRight);
}


BEGIN_MESSAGE_MAP(CPropertyPageThemes, CPropertyPageBG)
	//{{AFX_MSG_MAP(CPropertyPageThemes)
	ON_BN_CLICKED(IDC_RADIO_STANDART, OnRadioStandart)
	ON_BN_CLICKED(IDC_RADIO_SILVER, OnRadioSilver)
	ON_BN_CLICKED(IDC_RADIO_ALPINE, OnRadioAlpine)
	ON_BN_CLICKED(IDC_RADIO_REVOLUTION, OnRadioRevolution)
	ON_BN_CLICKED(IDC_RADIO_SUMMER, OnRadioSummer)
	ON_BN_CLICKED(IDC_RADIO_TRANQUIL, OnRadioTranquil)
	ON_BN_CLICKED(IDC_CLRPICKER_LEFT,  OnColourPicker)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_CHECK_USEGRADIENT, OnCheckUseGradient)
	ON_BN_CLICKED(IDC_CLRPICKER_RIGHT, OnColourPicker)
	ON_BN_CLICKED(IDC_FONT, OnFont)
	//}}AFX_MSG_MAP
  ON_MESSAGE(CPN_SELENDOK,  OnSelEndOK)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageThemes message handlers
void CPropertyPageThemes::OnRadioAlpine() {
  m_clrLeft  = CLR_ALPINE_LEFT;
  m_clrRight = CLR_ALPINE_RIGHT;
  OnCheckUseGradient();
}

void CPropertyPageThemes::OnRadioRevolution() {
  m_clrLeft  = CLR_REVOLUTION_LEFT;
  m_clrRight = CLR_REVOLUTION_RIGHT;
  OnCheckUseGradient();
}
void CPropertyPageThemes::OnRadioStandart() {
  m_clrLeft  = CLR_STANDART_LEFT;
  m_clrRight = CLR_STANDART_RIGHT;
  OnCheckUseGradient();
}
void CPropertyPageThemes::OnRadioSilver() {
  m_clrLeft  = CLR_SILVER_LEFT;
  m_clrRight = CLR_SILVER_RIGHT;
  OnCheckUseGradient();
}
void CPropertyPageThemes::OnRadioSummer() {
  m_clrLeft  = CLR_SUMMER_LEFT;
  m_clrRight = CLR_SUMMER_RIGHT;
  OnCheckUseGradient();
}
void CPropertyPageThemes::OnRadioTranquil() {
  m_clrLeft  = CLR_TRANQUIL_LEFT;
  m_clrRight = CLR_TRANQUIL_RIGHT;
  OnCheckUseGradient();
}
void CPropertyPageThemes::OnColourPicker() {
	// TODO: Add your control notification handler code here
}

LONG CPropertyPageThemes::OnSelEndOK(UINT lParam, LONG wParam) {
  //GetDlgItem(IDC_STYLE_USER)->InvalidateRect(NULL);
  UpdateData(TRUE);
  OnCheckUseGradient();
  return TRUE;
}

void CPropertyPageThemes::OnFont() {
  CFont* pFont = GetFont();
  if ( pFont ) {
    LOGFONT lf;
    theApp.m_Font.GetLogFont(&lf);
    // pFont->GetLogFont(&lf);
    // lf.lfCharSet = RUSSIAN_CHARSET;
    lf.lfItalic = false;
    CXFontDialog dlg(&lf, CF_SCREENFONTS|CF_LIMITSIZE);
    //CFontDialog dlg(&lf); // , CF_SCREENFONTS|CF_LIMITSIZE);
    //CFontDialog dlg; // , CF_SCREENFONTS|CF_LIMITSIZE);
    dlg.m_cf.Flags &= ~CF_EFFECTS;		// remove the Effects controls
    dlg.m_cf.Flags |= CF_TTONLY;
    dlg.m_cf.Flags |= CF_SCREENFONTS|CF_LIMITSIZE;
    dlg.m_cf.nSizeMin = 6;
    dlg.m_cf.nSizeMax = 16;
    dlg.SetFontFilter(XCF_SHOW_ALL_EXCEPT_SYMBOL);
    if ( IDOK==dlg.DoModal() ) {
      //int nPointSize = -lf.lfHeight*72/GetDeviceCaps(hdcCur,LOGPIXELSY);
      int nPointSize = -(int)((lf.lfHeight*72)/96.0 - 0.5);
      CString s;
      dlg.GetCurrentFont(&lf);

      m_Font.DeleteObject();
      m_Font.CreateFontIndirect(&lf);
      m_fFontChanged = true;
      ShowSamplesBox(&lf);
    }
  }
}

void CPropertyPageThemes::OnOK() {
	// TODO: Add your specialized code here and/or call the base class
  UpdateData(TRUE);
  if ( m_fUseGradient != m_fUseGradientSaved )
    m_fColorChanged = TRUE;
  if ( g_clrLeft != m_clrLeft ) {
    g_clrLeft       = m_clrLeft;
    m_fColorChanged = TRUE;
  }
  COLORREF clrRight = m_fUseGradient ? m_clrRight : m_clrLeft;
  if ( g_clrRight != clrRight ) {
    g_clrRight      = clrRight;
    m_fColorChanged = TRUE;
  }
  g_fUseGradient  = m_fUseGradient;
  if ( m_fFontChanged ) {
    LOGFONT lf;
    m_Font.GetLogFont(&lf);
    theApp.CreateFont(&lf);
    theApp.SaveFont();
    theApp.ResetFont();
  }
	CPropertyPageBG::OnOK();
}

void CPropertyPageThemes::OnCheckUseGradient() {
	// TODO: Add your control notification handler code here
  m_fUseGradient = IsDlgButtonChecked(IDC_CHECK_USEGRADIENT);
  CWnd* pWnd = GetWindow(GW_CHILD);
  while( pWnd ) {
    pWnd->InvalidateRect(NULL, TRUE);
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
  UpdateData(FALSE);
}


void CPropertyPageThemes::ShowSamplesBox(LOGFONT* pLogFont) {
  CString s;
  int nPointSize = -(int)((pLogFont->lfHeight*72)/96.0 - 0.5);
  s.Format(_T("%s, %d"), pLogFont->lfFaceName, nPointSize);
  CWnd* pWnd = GetDlgItem(IDC_STATIC_FONT_SAMPLE);
  pWnd->SetFont(&m_Font);
  pWnd->SetWindowText(s);
}
BOOL CPropertyPageThemes::OnInitDialog() {
	CPropertyPageBG::OnInitDialog();

	// TODO: Add extra initialization here
  CheckDlgButton(IDC_CHECK_USEGRADIENT, m_fUseGradient);

  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_chkGradient.SetCheckBoxImageList(&m_CheckBoxIL);
  }
  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_rbStandart  .SetRadioImageList(&m_RadioIL); m_rbStandart  .SetRadio(IDC_RADIO_STANDART, IDC_RADIO_ALPINE);
    m_rdSilver    .SetRadioImageList(&m_RadioIL); m_rdSilver    .SetRadio(IDC_RADIO_STANDART, IDC_RADIO_ALPINE);
    m_rdSummer    .SetRadioImageList(&m_RadioIL); m_rdSummer    .SetRadio(IDC_RADIO_STANDART, IDC_RADIO_ALPINE);
    m_rdRevolution.SetRadioImageList(&m_RadioIL); m_rdRevolution.SetRadio(IDC_RADIO_STANDART, IDC_RADIO_ALPINE);
    m_rdTranquil  .SetRadioImageList(&m_RadioIL); m_rdTranquil  .SetRadio(IDC_RADIO_STANDART, IDC_RADIO_ALPINE);
    m_rdAlpine    .SetRadioImageList(&m_RadioIL); m_rdAlpine    .SetRadio(IDC_RADIO_STANDART, IDC_RADIO_ALPINE);
  }

  GetDlgItem(IDC_STYLE_STANDART)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);
  GetDlgItem(IDC_STYLE_SILVER)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);
  GetDlgItem(IDC_STYLE_SUMMER)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);
  GetDlgItem(IDC_STYLE_REVOLUTION)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);
  GetDlgItem(IDC_STYLE_TRANQUIL)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);
  GetDlgItem(IDC_STYLE_ALPINE)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);
  GetDlgItem(IDC_STYLE_USER)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);


	// create font for sample
  LOGFONT lf;
  if ( theApp.m_Font.m_hObject ) {
    theApp.m_Font.GetLogFont(&lf);
  }
  else {
	  CFont *pFont = GetFont();
	  pFont->GetLogFont(&lf);
  }
  m_Font.CreateFontIndirect(&lf);
  ShowSamplesBox(&lf);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageThemes::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS) {
	// TODO: Add your message handler code here and/or call default
  COLORREF clrLeft(0), clrRight(0);
	switch(nIDCtl) {
    case IDC_STYLE_STANDART:
      clrLeft  = CLR_STANDART_LEFT;
      clrRight = CLR_STANDART_RIGHT;
      break;
    case IDC_STYLE_SILVER:
      clrLeft  = CLR_SILVER_LEFT;
      clrRight = CLR_SILVER_RIGHT;
      break;
    case IDC_STYLE_SUMMER:
      clrLeft  = CLR_SUMMER_LEFT;
      clrRight = CLR_SUMMER_RIGHT;
      break;
    case IDC_STYLE_REVOLUTION:
      clrLeft  = CLR_REVOLUTION_LEFT;
      clrRight = CLR_REVOLUTION_RIGHT;
      break;
    case IDC_STYLE_TRANQUIL:
      clrLeft  = CLR_TRANQUIL_LEFT;
      clrRight = CLR_TRANQUIL_RIGHT;
      break;
    case IDC_STYLE_ALPINE:
      clrLeft  = CLR_ALPINE_LEFT;
      clrRight = CLR_ALPINE_RIGHT;
      break;
    case IDC_STYLE_USER:
      clrLeft  = m_clrLeft;
      clrRight = m_clrRight;
      break;
  }
  if ( clrLeft || clrRight ) {
    DrawGradientLabel(this, nIDCtl, lpDIS, ::GetSysColor(COLOR_BTNTEXT),  clrLeft, clrRight, TRUE, m_fUseGradient);
    return;
  }

	CPropertyPageBG::OnDrawItem(nIDCtl, lpDIS);
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageArchive
IMPLEMENT_DYNCREATE(CPropertyPageArchive, CPropertyPageBG)
CPropertyPageArchive::CPropertyPageArchive() : CPropertyPageBG(CPropertyPageArchive::IDD) {
	//{{AFX_DATA_INIT(CPropertyPageArchive)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_nCheck = 0;
}

CPropertyPageArchive::~CPropertyPageArchive() {
}
void CPropertyPageArchive::DoDataExchange(CDataExchange* pDX) {
	CPropertyPageBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageArchive)
  DDX_Control(pDX, IDC_FRAME1,    m_Frame1);
  DDX_Control(pDX, IDC_NEVER,     m_rbNever);
  DDX_Control(pDX, IDC_MONDAY,    m_rbMonday);
  DDX_Control(pDX, IDC_TUESDAY,   m_rbTuesday);
  DDX_Control(pDX, IDC_WEDNESDAY, m_rbWednesday);
  DDX_Control(pDX, IDC_THURSDAY,  m_rbThursday);
  DDX_Control(pDX, IDC_FRIDAY,    m_rbFriday);
  DDX_Control(pDX, IDC_SATURDAY,  m_rbSaturday);
  DDX_Control(pDX, IDC_EVERYDAY,  m_rbEveryday);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyPageArchive, CPropertyPageBG)
	//{{AFX_MSG_MAP(CPropertyPageArchive)
	ON_BN_CLICKED(IDC_NEVER,     OnRadioNever)
	ON_BN_CLICKED(IDC_MONDAY,    OnRadioMonday)
	ON_BN_CLICKED(IDC_TUESDAY,   OnRadioTuesday)
	ON_BN_CLICKED(IDC_WEDNESDAY, OnRadioWednesday)
	ON_BN_CLICKED(IDC_THURSDAY,  OnRadioThursday)
	ON_BN_CLICKED(IDC_FRIDAY,    OnRadioFriday)
	ON_BN_CLICKED(IDC_SATURDAY,  OnRadioSaturday)
	ON_BN_CLICKED(IDC_EVERYDAY,  OnRadioEveryday)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageArchive message handlers
void CPropertyPageArchive::OnRadio() {
  CheckRadioButton(IDC_NEVER, IDC_EVERYDAY, IDC_NEVER+m_nCheck);
}
void CPropertyPageArchive::OnRadioNever()     { m_nCheck = 0; OnRadio(); }
void CPropertyPageArchive::OnRadioMonday()    { m_nCheck = 1; OnRadio(); }
void CPropertyPageArchive::OnRadioTuesday()   { m_nCheck = 2; OnRadio(); }
void CPropertyPageArchive::OnRadioWednesday() { m_nCheck = 3; OnRadio(); }
void CPropertyPageArchive::OnRadioThursday()  { m_nCheck = 4; OnRadio(); }
void CPropertyPageArchive::OnRadioFriday()    { m_nCheck = 5; OnRadio(); }
void CPropertyPageArchive::OnRadioSaturday()  { m_nCheck = 6; OnRadio(); }
void CPropertyPageArchive::OnRadioEveryday()  { m_nCheck = 7; OnRadio(); }


void CPropertyPageArchive::OnOK() {
	// TODO: Add your specialized code here and/or call the base class
  UpdateData(TRUE);
  theApp.WriteProfileInt(_T("Settings"), _T("ZipType"), m_nCheck);
	CPropertyPageBG::OnOK();
}
BOOL CPropertyPageArchive::OnInitDialog() {
	CPropertyPageBG::OnInitDialog();

  m_nCheck = theApp.GetProfileInt(_T("Settings"), _T("ZipType"), 1);
  if ( m_nCheck < 0 || m_nCheck > 7 ) {
    m_nCheck = 1;
  }
	// TODO: Add extra initialization here
  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_rbNever    .SetRadioImageList(&m_RadioIL); m_rbNever    .SetRadio(IDC_NEVER, IDC_EVERYDAY);
    m_rbMonday   .SetRadioImageList(&m_RadioIL); m_rbMonday   .SetRadio(IDC_NEVER, IDC_EVERYDAY);
    m_rbTuesday  .SetRadioImageList(&m_RadioIL); m_rbTuesday  .SetRadio(IDC_NEVER, IDC_EVERYDAY);
    m_rbWednesday.SetRadioImageList(&m_RadioIL); m_rbWednesday.SetRadio(IDC_NEVER, IDC_EVERYDAY);
    m_rbThursday .SetRadioImageList(&m_RadioIL); m_rbThursday .SetRadio(IDC_NEVER, IDC_EVERYDAY);
    m_rbFriday   .SetRadioImageList(&m_RadioIL); m_rbFriday   .SetRadio(IDC_NEVER, IDC_EVERYDAY);
    m_rbSaturday .SetRadioImageList(&m_RadioIL); m_rbSaturday .SetRadio(IDC_NEVER, IDC_EVERYDAY);
    m_rbEveryday .SetRadioImageList(&m_RadioIL); m_rbEveryday .SetRadio(IDC_NEVER, IDC_EVERYDAY);
  }
  CheckRadioButton(IDC_NEVER, IDC_EVERYDAY, IDC_NEVER+m_nCheck);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageOffice
IMPLEMENT_DYNCREATE(CPropertyPageOffice, CPropertyPageBG)
CPropertyPageOffice::CPropertyPageOffice() : CPropertyPageBG(CPropertyPageOffice::IDD) {
	//{{AFX_DATA_INIT(CPropertyPageOffice)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
CPropertyPageOffice::~CPropertyPageOffice() {
}

void CPropertyPageOffice::DoDataExchange(CDataExchange* pDX) {
	CPropertyPageBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageOffice)
  DDX_Control(pDX, IDC_MSOFFICE,   m_rdMSOffice);
  DDX_Control(pDX, IDC_OPENOFFICE, m_rdOpenOffice);
  DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_UNDERLINE, m_rdUnderline);
  DDX_Control(pDX, IDC_PRINTSINGLE, m_rdPrintSingle);
  DDX_Control(pDX, IDC_CITYTYPE, m_SampleImage);
  //}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CPropertyPageOffice, CPropertyPageBG)
	//{{AFX_MSG_MAP(CPropertyPageOffice)
  ON_BN_CLICKED(IDC_UNDERLINE,    OnRadioUnderline)
  ON_BN_CLICKED(IDC_PRINTSINGLE,  OnRadioPrintSingle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPropertyPageOffice::OnInitDialog() {
	CPropertyPageBG::OnInitDialog();

  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_rdMSOffice   .SetRadioImageList(&m_RadioIL); m_rdMSOffice   .SetRadio(IDC_MSOFFICE, IDC_OPENOFFICE);
    m_rdOpenOffice .SetRadioImageList(&m_RadioIL); m_rdOpenOffice .SetRadio(IDC_MSOFFICE, IDC_OPENOFFICE);
    m_rdUnderline  .SetRadioImageList(&m_RadioIL); m_rdUnderline  .SetRadio(IDC_UNDERLINE, IDC_PRINTSINGLE);
    m_rdPrintSingle.SetRadioImageList(&m_RadioIL); m_rdPrintSingle.SetRadio(IDC_UNDERLINE, IDC_PRINTSINGLE);
  }

  UINT nOffice = theApp.GetOffice();
  if ( MS_OFFICE==nOffice ) {
    CheckRadioButton(IDC_MSOFFICE, IDC_OPENOFFICE, IDC_MSOFFICE);
  }
  else {
    CheckRadioButton(IDC_MSOFFICE, IDC_OPENOFFICE, IDC_OPENOFFICE);
  }

  if ( theIniCache.GetCityUnderline() ) {
    CheckRadioButton(IDC_UNDERLINE, IDC_PRINTSINGLE, IDC_UNDERLINE);
  }
  else {
    CheckRadioButton(IDC_UNDERLINE, IDC_PRINTSINGLE, IDC_PRINTSINGLE);
    OnRadioPrintSingle();
  }

  CString szInfo = _T("Інформація про OpenOffice.org:\r\n\r\n");
  if ( theApp.m_dwOfficeInstalled & OFFICE_INSTALED_SWRITER) {
    szInfo += _T("OpenOffice.org Writer інстальований на цьому комп'ютері\r\n");
    szInfo += theApp.m_szOOWriterPath;
    szInfo += _T("\r\n");
  }
  if ( theApp.m_dwOfficeInstalled & OFFICE_INSTALED_MSEXCEL ) {
    szInfo += _T("OpenOffice.org Calc інстальований на цьому комп'ютері\r\n");
    szInfo += theApp.m_szOOCalcPath;
    szInfo += _T("\r\n");
  }
  if ( (theApp.m_dwOfficeInstalled & (OFFICE_INSTALED_SWRITER|OFFICE_INSTALED_SCALC))==0) {
    szInfo += _T("OpenOffice.org відсутній на цьому комп'ютері\r\n");
  }
  GetDlgItem(IDC_OOINFO)->SetWindowText(szInfo);

  szInfo = _T("Інформація про Microsoft Office:\r\n\r\n");
  if ( theApp.m_dwOfficeInstalled & OFFICE_INSTALED_MSWORD ) {
    szInfo += _T("Microsoft Word інстальований на цьому комп'ютері\r\n");
    szInfo += theApp.m_szMSWordPath;
    szInfo += _T("\r\n");
  }
  if ( theApp.m_dwOfficeInstalled & OFFICE_INSTALED_MSEXCEL ) {
    szInfo += _T("Microsoft Excel інстальований на цьому комп'ютері\r\n");
    szInfo += theApp.m_szMSExcelPath;
    szInfo += _T("\r\n");
  }
  if ( (theApp.m_dwOfficeInstalled & (OFFICE_INSTALED_MSWORD|OFFICE_INSTALED_MSEXCEL))==0) {
    szInfo += _T("Microsoft Office відсутній на цьому комп'ютері\r\n");
  }
  GetDlgItem(IDC_MSOINFO)->SetWindowText(szInfo);

  return true;
}

void CPropertyPageOffice::OnRadioUnderline() {
  m_bmpSample.DeleteObject();
  m_bmpSample.LoadBitmap( IDB_CITYTYPE1 );
  m_SampleImage.SetBitmap(m_bmpSample);
}

void CPropertyPageOffice::OnRadioPrintSingle() {
  m_bmpSample.DeleteObject();
  m_bmpSample.LoadBitmap( IDB_CITYTYPE2 );
  m_SampleImage.SetBitmap(m_bmpSample);
}

void CPropertyPageOffice::OnOK() {
	// TODO: Add your specialized code here and/or call the base class
  UpdateData(TRUE);

  int nCheckedBtnId = GetCheckedRadioButton(IDC_MSOFFICE, IDC_OPENOFFICE);
  if ( IDC_MSOFFICE==nCheckedBtnId ) {
    theApp.SetOffice(MS_OFFICE);
  }
  else {
    theApp.SetOffice(OPEN_OFFICE);
  }
  ((CMainFrame*)AfxGetMainWnd())->m_wndDlgBar.SetOfficeButtons();


  nCheckedBtnId = GetCheckedRadioButton(IDC_UNDERLINE, IDC_PRINTSINGLE);

  theIniCache.SetCityUnderline( nCheckedBtnId==IDC_UNDERLINE );


	CPropertyPageBG::OnOK();
}

/*
/////////////////////////////////////////////////////////////////////////////
// CPropertyPageUsers
IMPLEMENT_DYNCREATE(CPropertyPageUsers, CPropertyPageBG)
CPropertyPageUsers::CPropertyPageUsers() : CPropertyPageBG(CPropertyPageUsers::IDD) {
	//{{AFX_DATA_INIT(CPropertyPageUsers)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_nCurUser = -1;
}
CPropertyPageUsers::~CPropertyPageUsers() {
}

void CPropertyPageUsers::DoDataExchange(CDataExchange* pDX) {
	CPropertyPageBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageUsers)
  DDX_Control(pDX, IDC_USERS,  m_Users);
  DDX_Control(pDX, IDC_USER, m_User);
  DDX_Control(pDX, IDC_POST, m_Post);
  DDX_Control(pDX, IDC_PASSWORD1, m_Password1);
  DDX_Control(pDX, IDC_PASSWORD2, m_Password2);
  DDX_Control(pDX, IDC_ADDNEW, m_btnAddNew);
  DDX_Control(pDX, IDC_DELETE, m_btnDelete);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CPropertyPageUsers, CPropertyPageBG)
	//{{AFX_MSG_MAP(CPropertyPageUsers)
  ON_NOTIFY(LVN_ITEMCHANGED, IDC_USERS, OnItemChangedUsers)
  ON_EN_CHANGE(IDC_PASSWORD1, OnChange)
  ON_EN_CHANGE(IDC_PASSWORD2, OnChange)
  ON_BN_CLICKED(IDC_ADDNEW, OnAddNew)
  ON_BN_CLICKED(IDC_DELETE, OnDelete)
  ON_BN_CLICKED(IDC_SHOW_PASSWORD, OnShowPassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPropertyPageUsers::OnInitDialog() {
	CPropertyPageBG::OnInitDialog();

  m_Users.SetExtendedStyle(LVS_EX_FULLROWSELECT);
  m_Users.InsertColumn(0, _T("ПІБ")   , LVCFMT_LEFT, 200);
  m_Users.InsertColumn(1, _T("Посада"), LVCFMT_LEFT, 200);

  for( int i(0); i < theUsers.GetCount(); i++ ) {
    UserInfo ui = theUsers.GetAt(i);
    m_Users.InsertItem(i, ui.szUser);
    m_Users.SetItemText(i, 1, ui.szPost);
    m_Users.SetItemData(i, (DWORD)i);
  }
  m_btnAddNew.EnableWindow(false);

  return true;
}

void CPropertyPageUsers::OnItemChangedUsers(NMHDR* pNMHDR, LRESULT* pResult) {
  NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  BOOL fEnable = (pNMListView->iItem >= 0 && (pNMListView->uNewState & LVIS_FOCUSED));
  if ( fEnable ) {
    m_nCurUser = pNMListView->iItem;
  }
  else {
    m_nCurUser = -1;
  }
  m_btnDelete.EnableWindow(fEnable);
	*pResult = 0;
}
void CPropertyPageUsers::OnChange() {
  BOOL fEnable = false;
  CString szUser, szPassword1, szPassword2;
  m_User.GetWindowText(szUser);
  m_Password1.GetWindowText(szPassword1);
  m_Password2.GetWindowText(szPassword2);
  if ( false==szUser.IsEmpty() && false==szPassword1.IsEmpty() && szPassword1==szPassword2 ) {
    fEnable = true;
  }
  m_btnAddNew.EnableWindow(fEnable);
}
void CPropertyPageUsers::OnOK() {
	// TODO: Add your specialized code here and/or call the base class
  UpdateData(TRUE);
	CPropertyPageBG::OnOK();
}
void CPropertyPageUsers::OnAddNew() {
  CString szUser, szPost, szPassword;
  m_User.GetWindowText(szUser);
  m_Post.GetWindowText(szPost);
  m_Password1.GetWindowText(szPassword);
  theUsers.Add(szUser, szPost, szPassword);
  int nItem = m_Users.InsertItem(m_Users.GetItemCount(), szUser);
  m_Users.SetItemText(nItem, 1, szPost);
}
void CPropertyPageUsers::OnDelete() {
  if ( m_nCurUser >= 0 ) {
    CString szUser;
    m_Users.SetFocus();
    szUser = m_Users.GetItemText(m_nCurUser, 0);
    m_Users.DeleteItem(m_nCurUser);
    theUsers.Delete(szUser);
    m_nCurUser = -1;
  }
}

void CPropertyPageUsers::OnShowPassword() {
  CEdit* pPassword1 = (CEdit*)GetDlgItem(IDC_PASSWORD1);
  CEdit* pPassword2 = (CEdit*)GetDlgItem(IDC_PASSWORD2);
  if ( IsDlgButtonChecked(IDC_SHOW_PASSWORD) ) {
    pPassword1->ModifyStyle(ES_PASSWORD, 0);
    pPassword1->SetPasswordChar(0);
    pPassword2->ModifyStyle(ES_PASSWORD, 0);
    pPassword2->SetPasswordChar(0);
  }
  else {
    pPassword1->ModifyStyle(0, ES_PASSWORD);
    pPassword1->SetPasswordChar('*');
    pPassword2->ModifyStyle(0, ES_PASSWORD);
    pPassword2->SetPasswordChar('*');
  }
  pPassword1->InvalidateRect(NULL);
  pPassword1->UpdateWindow();
  pPassword2->InvalidateRect(NULL);
  pPassword2->UpdateWindow();
}
*/

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageStamps
IMPLEMENT_DYNCREATE(CPropertyPageStamps, CPropertyPageBG)
CPropertyPageStamps::CPropertyPageStamps() : CPropertyPageBG(CPropertyPageStamps::IDD) {
	//{{AFX_DATA_INIT(CPropertyPageStamps)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
CPropertyPageStamps::~CPropertyPageStamps() {
}

void CPropertyPageStamps::DoDataExchange(CDataExchange* pDX) {
	CPropertyPageBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageStamps)
  DDX_Control(pDX, IDC_FRAME1,  m_Frame1);
  DDX_Control(pDX, IDC_CHECK1,  m_btnCheck1);
  DDX_Control(pDX, IDC_EDIT1,   m_Edit1);
  DDX_Control(pDX, IDC_FRAME2,  m_Frame2);
  DDX_Control(pDX, IDC_CHECK2,  m_btnCheck2);
  DDX_Control(pDX, IDC_EDIT2,   m_Edit2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPropertyPageStamps, CPropertyPageBG)
	//{{AFX_MSG_MAP(CPropertyPageStamps)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPropertyPageStamps::OnInitDialog() {
	CPropertyPageBG::OnInitDialog();

  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_btnCheck1.SetCheckBoxImageList(&m_CheckBoxIL);
    m_btnCheck2.SetCheckBoxImageList(&m_CheckBoxIL);
  }

  m_Edit1.SetWindowText(theIniCache.GetStamp1());
  m_Edit2.SetWindowText(theIniCache.GetStamp2());

  m_btnCheck1.SetCheck( theIniCache.GetUseStamp1() );
  m_btnCheck2.SetCheck( theIniCache.GetUseStamp2() );
  

  return true;
}
void CPropertyPageStamps::OnOK() {
	// TODO: Add your specialized code here and/or call the base class
  UpdateData(TRUE);

  theIniCache.SetUseStamp1( m_btnCheck1.GetCheck() );
  theIniCache.SetUseStamp2( m_btnCheck2.GetCheck() );

  theIniCache.SetStamp1( m_Edit1.GetText() );
  theIniCache.SetStamp2( m_Edit2.GetText() );
  
  CPropertyPageBG::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg
IMPLEMENT_DYNAMIC(CSettingsDlg, CPropertySheetBG)

CSettingsDlg::CSettingsDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
             :CPropertySheetBG(pszCaption, pParentWnd, iSelectPage) {
  m_fYes = m_fNo = false;
  AddPage( &m_pageCommon );
  AddPage( &m_pageBirth );
  AddPage( &m_pageMarriage );
  AddPage( &m_pageDivorce );
  AddPage( &m_pageChange );
  AddPage( &m_pageDeath );
  AddPage( &m_pageThemes );
  AddPage( &m_pageArchive );
  AddPage( &m_pageOffice );
/*
  AddPage( &m_pageUsers );
*/
  AddPage( &m_pageStamps );

  m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

CSettingsDlg::~CSettingsDlg() {
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CPropertySheetBG)
	//{{AFX_MSG_MAP(CSettingsDlg)
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg message handlers
BOOL CSettingsDlg::OnInitDialog() {
	BOOL bResult = CPropertySheetBG::OnInitDialog();
	
	// TODO: Add your specialized code here

  CWnd* pOk = GetDlgItem(IDOK);
  if ( pOk ) {
    m_btnOk.SubclassWindow(pOk->m_hWnd);
    m_btnOk.SetIcon(IDI_YES);
    pOk->SetWindowText(_T("Так"));
    pOk->SetWindowPos(NULL, 0, 0, BTN_BITMAP_WIDTH+4, BTN_BITMAP_HEIGHT+4, SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);
  }
  CWnd* pCancel = GetDlgItem(IDCANCEL);
  if ( pCancel ) {
    m_btnCancel.SubclassWindow(pCancel->m_hWnd);
    m_btnCancel.SetIcon(IDI_NO);
    pCancel->SetWindowText(_T("Ні"));
    pCancel->SetWindowPos(NULL, 0, 0, BTN_BITMAP_WIDTH+4, BTN_BITMAP_HEIGHT+4, SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);
  }
  //m_ImageList.Create(24, 24, ILC_MASK, 9, 0);
  m_ImageList.Create(24, 24, ILC_MASK|ILC_COLOR8, 11, 0);
  m_ImageList.Add(theApp.LoadIcon(IDI_COMMON_SETTINGS));
  m_ImageList.Add(theApp.LoadIcon(IDI_SETBIRTH));
  m_ImageList.Add(theApp.LoadIcon(IDI_SETMARRIAGE));
  m_ImageList.Add(theApp.LoadIcon(IDI_SETDIVORCE));
  m_ImageList.Add(theApp.LoadIcon(IDI_SETCHANGE));
  m_ImageList.Add(theApp.LoadIcon(IDI_SETDEATH));
  m_ImageList.Add(theApp.LoadIcon(IDI_SETCOLORS));
  m_ImageList.Add(theApp.LoadIcon(IDI_SETZIP));
  m_ImageList.Add(theApp.LoadIcon(IDI_SETOFFICE));
  m_ImageList.Add(theApp.LoadIcon(IDI_STAMP));
  // m_ImageList.Add(theApp.LoadIcon(IDI_USERS));

  CTabCtrl* pTabCtrl = GetTabControl();
  pTabCtrl->SetImageList(&m_ImageList);
  TCITEM tcItem;
  tcItem.mask = TCIF_IMAGE;
  for( int i(0); i < 11; i++) {
    tcItem.iImage = i;
    pTabCtrl->SetItem(i, &tcItem);
  }

  SetActivePage(0);

	return bResult;
}

BOOL CSettingsDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
/*
  m_tooltip.HideTooltip();
  if ( HELPINFO_WINDOW==pHelpInfo->iContextType ) {
    CWnd* pWnd = CWnd::FromHandle((HWND)pHelpInfo->hItemHandle);
    if ( pWnd ) {
      m_fNeedShowTooltip = true;
      ShowHelpTooltipSetFocus(&m_tooltip, pWnd->GetParent(), _T("SetDlg"), pWnd, pHelpInfo->iCtrlId);
    }
  }
*/
  theApp.OnHelp(_T("SetDlg"));
  return TRUE;
}

void CSettingsDlg::OnYes() {
	//UpdateData();
  Default();
  CPropertySheetBG::EndDialog(IDOK);
}
void CSettingsDlg::OnNo() {
	CPropertySheetBG::EndDialog(IDCANCEL);
}
BOOL CSettingsDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
	// TODO: Add your specialized code here and/or call the base class
  if ( BN_SETFOCUS==HIWORD(wParam) ) {
    return TRUE;
  }
  if ( BN_CLICKED==HIWORD(wParam) ) {
    switch(LOWORD(wParam)) {
      case IDOK:
        if ( FALSE==m_fYes ) {
          CPropertySheetBG::OnCommand(wParam, lParam);
          m_fYes = TRUE;
          OnYes();
          m_fYes = FALSE;
        }
        return TRUE;
      case IDCANCEL:
        if ( FALSE==m_fNo ) {
          CPropertySheetBG::OnCommand(wParam, lParam);
          m_fNo = TRUE;
          OnNo();
          m_fNo = FALSE;
        }
        return TRUE;
      case IDHELP:
        theApp.OnHelp(_T("SetDlg"));
        return TRUE;
    }
  }
	return CPropertySheetBG::OnCommand(wParam, lParam);
}
