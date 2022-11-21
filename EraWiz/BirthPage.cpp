// BirthPage.cpp : implementation file
//

#include "stdafx.h"
#include "EraWiz.h"
#include "BirthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString g_szBirthCountry;
CString g_szBirthRegion;
CString g_szBirthDistrict;
CString g_szBirthCity;
CString g_szBirthCityType;

UINT g_BirthCountryCheck;
UINT g_BirthRegionCheck;
UINT g_BirthDistrictCheck;
UINT g_BirthCityCheck;

extern CDaoDatabase theDatabase;

CString ReadFromDefaults(CDaoRecordset* prs, LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal);
void WriteToDefaults(CDaoRecordset* prs, LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal);
LPCTSTR GetCityShortTypeFromCB(const CString& szCityType);
/////////////////////////////////////////////////////////////////////////////
// CBirthPage dialog


CBirthPage::CBirthPage(CWnd* pParent /*=NULL*/)
	         :CNewWizPage(CBirthPage::IDD, pParent) {
	//{{AFX_DATA_INIT(CBirthPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBirthPage::DoDataExchange(CDataExchange* pDX)
{
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBirthPage)
	DDX_Control(pDX, IDC_SERIA_MARRIAGE, m_edtSeriaMarriage);
	DDX_Control(pDX, IDC_SERIA_BIRTH, m_edtSeriaBirth);
	DDX_Control(pDX, IDC_TITLE1, m_Title1);
	DDX_Control(pDX, IDC_TITLE2, m_Title2);
	DDX_Control(pDX, IDC_CHILD_BP_COUNTRY_CHECK, m_chkCountry);
	DDX_Control(pDX, IDC_CHILD_BP_REGION_CHECK, m_chkRegion);
	DDX_Control(pDX, IDC_CHILD_BP_DISTRICT_CHECK, m_chkDistrict);
	DDX_Control(pDX, IDC_CHILD_BP_CITY_CHECK, m_chkCity);
	DDX_Control(pDX, IDC_CITYTYPE2, m_cmbCityType);
	DDX_Control(pDX, IDC_COUNTRY2, m_BirthCountry);
	DDX_Control(pDX, IDC_REGION2,  m_BirthRegion);
	DDX_Control(pDX, IDC_DISTRICT2, m_BirthDistrict);
	DDX_Control(pDX, IDC_CITY2, m_BirthCity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBirthPage, CNewWizPage)
	//{{AFX_MSG_MAP(CBirthPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBirthPage message handlers

BOOL CBirthPage::OnInitDialog() 
{
	CNewWizPage::OnInitDialog();
	
	// TODO: Add extra initialization here


	m_Font.CreateFont(-12, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	m_Title1.SetFont(&m_Font, TRUE);
	m_Title2.SetFont(&m_Font, TRUE);

  LPCTSTR szSeria = GetCertSeria();

  if ( theDatabase.IsOpen() ) {
    CDaoRecordset rs(&theDatabase); 
    try {
      CString s;
      rs.Open(dbOpenTable, "[DEFAULTS]");
      s = ReadFromDefaults(&rs, _T("BIRTH_FORM"), _T("SERIA"), szSeria);
      m_edtSeriaBirth.SetWindowText(s);

      s = ReadFromDefaults(&rs, _T("MARRIAGE_FORM"), _T("SERIA"), szSeria);
      m_edtSeriaMarriage.SetWindowText(s);

      rs.Close();
    }
    catch (CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
  	}
  }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBirthPage::OnSetActive() {
	m_BirthCountry.SetWindowText(_T("Україна"));
  CheckDlgButton(IDC_CHILD_BP_COUNTRY_CHECK, 1);
	m_BirthRegion.SetWindowText(g_szRegion);
  if ( FALSE==g_szRegion.IsEmpty() )
    CheckDlgButton(IDC_CHILD_BP_REGION_CHECK, 1);

	m_BirthDistrict.SetWindowText(g_szDistrict);
  if ( FALSE==g_szDistrict.IsEmpty() )
    CheckDlgButton(IDC_CHILD_BP_DISTRICT_CHECK, 1);

	m_BirthCity.SetWindowText(g_szCity);
  if ( FALSE==g_szCity.IsEmpty() )
    CheckDlgButton(IDC_CHILD_BP_CITY_CHECK, 1);
	
  if ( FALSE==g_szCityType.IsEmpty() ) {
    m_cmbCityType.SelectString(0, g_szCityType);
  }
  SetFocus();
}

LRESULT CBirthPage::OnWizardNext() {
  g_BirthCountryCheck  = IsDlgButtonChecked(IDC_CHILD_BP_COUNTRY_CHECK);
  g_BirthRegionCheck   = IsDlgButtonChecked(IDC_CHILD_BP_REGION_CHECK);
  g_BirthDistrictCheck = IsDlgButtonChecked(IDC_CHILD_BP_DISTRICT_CHECK);
  g_BirthCityCheck     = IsDlgButtonChecked(IDC_CHILD_BP_CITY_CHECK);

  m_BirthCountry.GetWindowText(g_szBirthCountry);
  m_BirthRegion.GetWindowText(g_szBirthRegion);
  m_BirthDistrict.GetWindowText(g_szBirthDistrict);
  m_BirthCity.GetWindowText(g_szBirthCity);

  int nSel = m_cmbCityType.GetCurSel();
  if ( nSel != CB_ERR )
    m_cmbCityType.GetLBText(nSel, g_szBirthCityType);

  if ( theDatabase.IsOpen() ) {
    CDaoRecordset rs(&theDatabase); 
    try {
      CString s;
      rs.Open(dbOpenTable, "[DEFAULTS]");

      WriteToDefaults(&rs, _T("BIRTH_FORM"), _T("CHILD_BP_COUNTRY"),   g_szBirthCountry);
      s.Format(_T("%d"), g_BirthRegionCheck);
      WriteToDefaults(&rs, _T("BIRTH_FORM"), _T("CHILD_BP_COUNTRY_CHECK"),   s);

      WriteToDefaults(&rs, _T("BIRTH_FORM"), _T("CHILD_BP_REGION"),    g_szBirthRegion);
      s.Format(_T("%d"), g_BirthRegionCheck);
      WriteToDefaults(&rs, _T("BIRTH_FORM"), _T("CHILD_BP_REGION_CHECK"),    s);

      WriteToDefaults(&rs, _T("BIRTH_FORM"), _T("CHILD_BP_DISTRICT"),  g_szBirthDistrict);
      s.Format(_T("%d"), g_BirthDistrictCheck);
      WriteToDefaults(&rs, _T("BIRTH_FORM"), _T("CHILD_BP_DISTRICT_CHECK"),    s);

      s.Format(_T("%s %s"), g_szBirthCity, GetCityShortTypeFromCB(g_szBirthCityType));
      s.TrimRight();
      WriteToDefaults(&rs, _T("BIRTH_FORM"), _T("CHILD_BP_CITY"),          s);
      s.Format(_T("%d"), g_BirthCityCheck);
      WriteToDefaults(&rs, _T("BIRTH_FORM"), _T("CHILD_BP_CITY_CHECK"),    s);

      m_edtSeriaBirth.GetWindowText(s);
      WriteToDefaults(&rs, _T("BIRTH_FORM"), _T("SERIA"),    s);

      m_edtSeriaMarriage.GetWindowText(s);
      WriteToDefaults(&rs, _T("MARRIAGE_FORM"), _T("SERIA"),    s);

      rs.Close();
    }
    catch (CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
  	}
  }
  
  return CNewWizPage::OnWizardNext();
}

