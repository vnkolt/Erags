// SetGeoPlace.cpp : implementation file
//

#include "stdafx.h"
#include "EraWiz.h"
#include "SetGeoPlace.h"

#include "..\Common\CyrString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString g_szRegion;
CString g_szDistrict;
CString g_szCity;
CString g_szCityType;
CString g_szBoss;
CString g_szByUMVS;
CString g_szToUMVS;
CString g_szByMil;
CString g_szToMil;
CString g_szToTax;
CString g_szByCourt;

extern CString g_szRagsName;

extern CDaoDatabase theDatabase;
void WriteToDefaults(CDaoRecordset* prs, LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal);
LPCTSTR GetCityShortTypeFromCB(const CString& szCityType);
/////////////////////////////////////////////////////////////////////////////
// CSetGeoPlace dialog


CSetGeoPlace::CSetGeoPlace(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CSetGeoPlace::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetGeoPlace)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetGeoPlace::DoDataExchange(CDataExchange* pDX)
{
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetGeoPlace)
	DDX_Control(pDX, IDC_BOSS, m_edtBoss);
	DDX_Control(pDX, IDC_TOTAX, m_edtToTax);
	DDX_Control(pDX, IDC_BYCOURT, m_edtByCourt);
	DDX_Control(pDX, IDC_TOUMVS, m_edtToUMVS);
	DDX_Control(pDX, IDC_TOMIL, m_edtToMil);
	DDX_Control(pDX, IDC_PARENT, m_edtParent);
	DDX_Control(pDX, IDC_CITY, m_edtCity);
	DDX_Control(pDX, IDC_BYUMVS, m_ByUMVS);
	DDX_Control(pDX, IDC_BYMIL, m_edtByMil);
	DDX_Control(pDX, IDC_DISTRICT, m_edtDistrict);
	DDX_Control(pDX, IDC_REGION, m_edtRegion);
	DDX_Control(pDX, IDC_CITYTYPE, m_cmbCityType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetGeoPlace, CNewWizPage)
	//{{AFX_MSG_MAP(CSetGeoPlace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetGeoPlace message handlers

BOOL CSetGeoPlace::OnInitDialog() 
{
	CNewWizPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetGeoPlace::OnSetActive() {
  if ( g_szDistrict.IsEmpty() ) {
    int nFirstDist = g_szRagsName.Find(_T("ий ВРАЦС"));
    int nMUY       = g_szRagsName.Find(_T(" МУЮ"));
    if ( nFirstDist > 0 && nMUY > nFirstDist ) {
      CString szToken = GetTokSpace(g_szRagsName, 0);
      if ( szToken != _T("Міський")) {
        g_szDistrict = szToken;
      }
    }
  }
  if ( g_szDistrict.IsEmpty() ) {
    int nOver = g_szRagsName.Find(_T(" по ")); // i.g. ВРАЦС по Вознесенському р Вознесенського МРУЮ Миколаївської о
    if ( nOver > 0 ) {
      CString szToken = GetTokSpace(g_szRagsName.Mid(nOver+4), 0);
      szToken += ' ';
      if ( szToken.Right(4)==_T("ому ")) {
        szToken.Replace(_T("ому "), _T("ий"));
        g_szDistrict = szToken;
      }
    }
  }
  
  GetDlgItem(IDC_REGION)->SetWindowText(g_szRegion);
  GetDlgItem(IDC_DISTRICT)->SetWindowText(g_szDistrict);
  GetDlgItem(IDC_CITY)->SetWindowText(g_szCity);

  if ( g_szCityType.IsEmpty() ) {
    m_cmbCityType.SetCurSel(-1);
  }
  else {
    m_cmbCityType.SelectString(0, g_szCityType);
  }

  GetDlgItem(IDC_PARENT)->SetWindowText(g_szParentRags);
  m_edtRegion.SetFocus();
  GetParent()->GetDlgItem(ID_WIZNEXT)->EnableWindow(TRUE);

  GetDlgItem(IDC_BYUMVS)->SetWindowText(g_szByUMVS);
  GetDlgItem(IDC_TOUMVS)->SetWindowText(g_szToUMVS);
  GetDlgItem(IDC_BYMIL)->SetWindowText(g_szByMil);
  GetDlgItem(IDC_TOMIL)->SetWindowText(g_szToMil);
  GetDlgItem(IDC_TOTAX)->SetWindowText(g_szToTax);
  GetDlgItem(IDC_BYCOURT)->SetWindowText(g_szByCourt);
  GetDlgItem(IDC_BOSS)->SetWindowText(g_szBoss);
}

LRESULT CSetGeoPlace::OnWizardNext() {
  GetDlgItem(IDC_REGION)->GetWindowText(g_szRegion);
  GetDlgItem(IDC_DISTRICT)->GetWindowText(g_szDistrict);
  GetDlgItem(IDC_CITY)->GetWindowText(g_szCity);

  GetDlgItem(IDC_PARENT)->GetWindowText(g_szParentRags);

  GetDlgItem(IDC_BYUMVS)->GetWindowText(g_szByUMVS);
  GetDlgItem(IDC_TOUMVS)->GetWindowText(g_szToUMVS);
  GetDlgItem(IDC_BYMIL)->GetWindowText(g_szByMil);
  GetDlgItem(IDC_TOMIL)->GetWindowText(g_szToMil);
  GetDlgItem(IDC_TOTAX)->GetWindowText(g_szToTax);
  GetDlgItem(IDC_BYCOURT)->GetWindowText(g_szByCourt);
  GetDlgItem(IDC_BOSS)->GetWindowText(g_szBoss);

  int nSel = m_cmbCityType.GetCurSel();
  if ( nSel != CB_ERR )
    m_cmbCityType.GetLBText(nSel, g_szCityType);

  if ( theDatabase.IsOpen() ) {
    CDaoRecordset rs(&theDatabase);    
    try {
      CString s;
      rs.Open(dbOpenTable, "[DEFAULTS]");
      WriteToDefaults(&rs, _T("COMMON"), _T("REGION"),    g_szRegion);
      WriteToDefaults(&rs, _T("COMMON"), _T("DISTRICT"),  g_szDistrict);

      s.Format(_T("%s %s"), g_szCity, GetCityShortTypeFromCB(g_szCityType));
      s.TrimRight();
      WriteToDefaults(&rs, _T("COMMON"), _T("CITY"),      s);

      WriteToDefaults(&rs, _T("COMMON"), _T("PARENT"),    g_szParentRags);
      WriteToDefaults(&rs, _T("COMMON"), _T("BOSS"),      g_szBoss);
      WriteToDefaults(&rs, _T("COMMON"), _T("BYUMVS"),    g_szByUMVS);
      WriteToDefaults(&rs, _T("COMMON"), _T("TOUMVS"),    g_szToUMVS);
      WriteToDefaults(&rs, _T("COMMON"), _T("BYMIL"),     g_szByMil);
      WriteToDefaults(&rs, _T("COMMON"), _T("TOMIL"),     g_szToMil);
      WriteToDefaults(&rs, _T("COMMON"), _T("TOTAX"),     g_szToTax);
      WriteToDefaults(&rs, _T("COMMON"), _T("BYCOURT"),   g_szByCourt);

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
