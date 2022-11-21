// WitnessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Era2Xml.h"
#include "WitnessDlg.h"

#include "..\Common\CyrString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString	CWitnessDlg::m_Surname1;
CString	CWitnessDlg::m_Name1;
CString	CWitnessDlg::m_Patronymic1;
CString	CWitnessDlg::m_Country1;
CString	CWitnessDlg::m_Region1;
CString	CWitnessDlg::m_District1;
CString	CWitnessDlg::m_City1;
TCHAR   CWitnessDlg::m_cCityType1;
CString	CWitnessDlg::m_Street1;
TCHAR   CWitnessDlg::m_cStreetType1;
CString	CWitnessDlg::m_Build1;
CString	CWitnessDlg::m_Flat1;
int		  CWitnessDlg::m_DocType1;
CString	CWitnessDlg::m_DocSeria1;
CString	CWitnessDlg::m_DocNumber1;
CString	CWitnessDlg::m_DocDate1;
CString	CWitnessDlg::m_DocOrgan1;

CString	CWitnessDlg::m_Surname2;
CString	CWitnessDlg::m_Name2;
CString	CWitnessDlg::m_Patronymic2;
CString	CWitnessDlg::m_Country2;
CString	CWitnessDlg::m_Region2;
CString	CWitnessDlg::m_District2;
CString	CWitnessDlg::m_City2;
TCHAR   CWitnessDlg::m_cCityType2;
int		  CWitnessDlg::m_SettlType2;
CString	CWitnessDlg::m_Street2;
TCHAR   CWitnessDlg::m_cStreetType2;
CString	CWitnessDlg::m_Build2;
CString	CWitnessDlg::m_Flat2;
int		  CWitnessDlg::m_DocType2;
CString	CWitnessDlg::m_DocSeria2;
CString	CWitnessDlg::m_DocNumber2;
CString	CWitnessDlg::m_DocDate2;
CString	CWitnessDlg::m_DocOrgan2;


void FillTokenArray(const char* szSrc, CStringArray& tokens, char cDelim) {
  CString s(szSrc), sToken;
  for( int i(0); i < s.GetLength(); i++ ) {
    TCHAR c = s[i];
    if ( c==cDelim ) {
      if ( FALSE==sToken.IsEmpty() ) {
        tokens.Add( sToken );
        sToken.Empty();
        continue;
      }
      tokens.Add( CString(c) );
    }
    else {
      sToken += c;
    }
  }
  if ( FALSE==sToken.IsEmpty() ) {
    tokens.Add( sToken );
  }
}

BOOL FindAndRemove(CString& s, LPCTSTR szFind1, LPCTSTR szFind2=NULL, LPCTSTR szFind3=NULL) {
  BOOL fRet = false;
  if ( s.Find(szFind1) >= 0 ) {
    s.Replace(szFind1, _T(""));
    fRet = true;
  }
  else if ( szFind2 && s.Find(szFind2) >= 0 ) {
    s.Replace(szFind2, _T(""));
    fRet = true;
  }
  else if ( szFind3 && s.Find(szFind3) >= 0 ) {
    s.Replace(szFind3, _T(""));
    fRet = true;
  }
  if ( fRet ) {
    s.TrimLeft();
    s.TrimRight();
  }
  return fRet;
}


CString GetDateFromS(const CString& s) {
  CString szDate;
  int nLen = s.GetLength();
  for( int i(0); i < nLen - 9; i++ ) {
    szDate = s.Mid(i, 10);
    if ( szDate.GetLength()==10 &&
         isdigit(szDate[0]) && isdigit(szDate[1]) && szDate[2]=='.' &&  // dd.
         isdigit(szDate[3]) && isdigit(szDate[4]) && szDate[5]=='.' &&  // mm.
         isdigit(szDate[6]) && isdigit(szDate[7]) && isdigit(szDate[8])  && isdigit(szDate[9]) // yyyy
       )
    {
      return szDate;
    }
  }
  szDate.Empty();
  return szDate;
}
void GetPassport(CString& s, CString& szSeria, CString& szNum, CString& szDate, CString& szOrgan) {
  s.Replace(_T("№"), _T(""));
  szSeria = GetTok(s, 0, _T(", "));
  szNum   = GetTok(s, 1, _T(", "));
  szDate  = GetDateFromS(s);
  if ( false==szDate.IsEmpty() ) {
    int nFound = s.Find(szDate);
    if ( nFound >=0 ) {
      nFound += szDate.GetLength()+1;
      szOrgan = GetTok(s.Mid(nFound), 0, _T(",;"));
    }
  }
  // szNum.Replace(_T("№"), _T(""));
}

/////////////////////////////////////////////////////////////////////////////
// CWitnessDlg dialog


CWitnessDlg::CWitnessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWitnessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWitnessDlg)
	m_Build1 = _T("");
	m_Build2 = _T("");
	m_City1 = _T("");
	m_City2 = _T("");
	m_Country1 = _T("");
	m_Country2 = _T("");
	m_District1 = _T("");
	m_District2 = _T("");
	m_DocDate1 = _T("");
	m_DocDate2 = _T("");
	m_DocNumber1 = _T("");
	m_DocNumber2 = _T("");
	m_DocOrgan1 = _T("");
	m_DocOrgan2 = _T("");
	m_DocSeria1 = _T("");
	m_DocSeria2 = _T("");
	m_DocType1 = 0;
	m_DocType2 = 0;
	m_Flat1 = _T("");
	m_Flat2 = _T("");
	m_MedDocBy = _T("");
	m_MedDocDate = _T("");
	m_MedDocName = _T("");
	m_MedDocNum = _T("");
	m_Name1 = _T("");
	m_Name2 = _T("");
	m_Patronymic1 = _T("");
	m_Patronymic2 = _T("");
	m_Region1 = _T("");
	m_Region2 = _T("");
	m_SettlType1 = -1;
	m_SettlType2 = -1;
	m_Street1 = _T("");
	m_Street2 = _T("");
	m_Surname1 = _T("");
	m_Surname2 = _T("");
  m_cStreetType1 = '1';
  m_cStreetType2 = '1';
  m_cCityType1 = '1';
  m_cCityType2 = '1';
	//}}AFX_DATA_INIT
}


void CWitnessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWitnessDlg)
	DDX_Text(pDX, IDC_BUILD1, m_Build1);
	DDX_Text(pDX, IDC_BUILD2, m_Build2);
	DDX_Text(pDX, IDC_CITY1, m_City1);
	DDX_Text(pDX, IDC_CITY2, m_City2);
	DDX_Text(pDX, IDC_COUNTRY1, m_Country1);
	DDX_Text(pDX, IDC_COUNTRY2, m_Country2);
	DDX_Text(pDX, IDC_DISTRICT1, m_District1);
	DDX_Text(pDX, IDC_DISTRICT2, m_District2);
	DDX_Text(pDX, IDC_DOC_DATE1, m_DocDate1);
	DDX_Text(pDX, IDC_DOC_DATE2, m_DocDate2);
	DDX_Text(pDX, IDC_DOC_NUMBER1, m_DocNumber1);
	DDX_Text(pDX, IDC_DOC_NUMBER2, m_DocNumber2);
	DDX_CBString(pDX, IDC_DOC_ORGAN1, m_DocOrgan1);
	DDX_CBString(pDX, IDC_DOC_ORGAN2, m_DocOrgan2);
	DDX_Text(pDX, IDC_DOC_SERIA1, m_DocSeria1);
	DDX_Text(pDX, IDC_DOC_SERIA2, m_DocSeria2);
	DDX_CBIndex(pDX, IDC_DOCTYPE1, m_DocType1);
	DDX_CBIndex(pDX, IDC_DOCTYPE2, m_DocType2);
	DDX_Text(pDX, IDC_FLAT1, m_Flat1);
	DDX_Text(pDX, IDC_FLAT2, m_Flat2);
	DDX_Text(pDX, IDC_MEDDOCBY, m_MedDocBy);
	DDX_Text(pDX, IDC_MEDDOCDATE, m_MedDocDate);
	DDX_Text(pDX, IDC_MEDDOCNAME, m_MedDocName);
	DDX_Text(pDX, IDC_MEDDOCNUM, m_MedDocNum);
	DDX_Text(pDX, IDC_NAME1, m_Name1);
	DDX_Text(pDX, IDC_NAME2, m_Name2);
	DDX_Text(pDX, IDC_PATRONYMIC1, m_Patronymic1);
	DDX_Text(pDX, IDC_PATRONYMIC2, m_Patronymic2);
	DDX_Text(pDX, IDC_REGION1, m_Region1);
	DDX_Text(pDX, IDC_REGION2, m_Region2);
	DDX_CBIndex(pDX, IDC_SETTLEMENT_TYPE1, m_SettlType1);
	DDX_CBIndex(pDX, IDC_SETTLEMENT_TYPE2, m_SettlType2);
	DDX_Text(pDX, IDC_STREET1, m_Street1);
	DDX_Text(pDX, IDC_STREET2, m_Street2);
	DDX_Text(pDX, IDC_SURNAME1, m_Surname1);
	DDX_Text(pDX, IDC_SURNAME2, m_Surname2);
  DDX_Control(pDX, IDC_SETTLEMENT_TYPE1, m_cbCityType1);
  DDX_Control(pDX, IDC_SETTLEMENT_TYPE2, m_cbCityType2);
  DDX_Control(pDX, IDC_STREET_TYPE1, m_cbStreetType1);
  DDX_Control(pDX, IDC_STREET_TYPE2, m_cbStreetType2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWitnessDlg, CDialog)
	//{{AFX_MSG_MAP(CWitnessDlg)
  ON_BN_CLICKED(IDOK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CWitnessDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  SetWindowText(m_szTitle);
  GetDlgItem(IDC_GR10)->SetWindowText(m_szGR10);

  m_cbCityType1.SetCurSel(0);
  m_cbCityType2.SetCurSel(0);

  m_cbStreetType1.SetCurSel(m_cStreetType1-'1');
  m_cbStreetType2.SetCurSel(m_cStreetType2-'1');
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWitnessDlg::SetCityType(int& SettlType, TCHAR& cCityType) {
  switch( SettlType ) {
    case 0: // місто
      cCityType = '1';
      break;
    case 1: // село
      cCityType = '4';
      break;
    case 2: // селище
      cCityType = '5';
      break;
    case 3: // смт
      cCityType = '3';
      break;
  }
}
void CWitnessDlg::OnOk() {
  UpdateData(true);

  m_cStreetType1 = m_cbStreetType1.GetCurSel() + '1';
  m_cStreetType2 = m_cbStreetType2.GetCurSel() + '1';

  SetCityType(m_SettlType1, m_cCityType1);
  SetCityType(m_SettlType2, m_cCityType2);


  EndDialog(IDOK);
}

void FillWitness(const CString& szSource,
                 CString& szSurname, CString& szName, CString& szPatronymic,
                 CString& szDocSeria, CString& szDocNum, CString& szDocDate, CString& szDocOrgan,
                 CString& szCountry, CString& szRegion, CString& szDistrict, CString& szCity,
                 CString& szStreet, TCHAR& cStreetType, CString& szBuild, CString& szFlat
                )
{
  szSurname    = GetTok(szSource, 0, _T(", "));
  szName       = GetTok(szSource, 1, _T(", "));
  szPatronymic = GetTok(szSource, 2, _T(", "));

  int nFound = szSource.Find(_T("паспорт"));
  if ( nFound >= 0 ) {
    GetPassport(szSource.Mid(nFound+7), szDocSeria, szDocNum, szDocDate, szDocOrgan);
  }
  nFound = szSource.Find(_T("адрес"));
  if ( nFound >= 0 ) {
    nFound += 6;
    while ( szSource[nFound] != ' ' && szSource[nFound] != ':' ) nFound++;

    if ( szSource[nFound]==':' ) nFound++;

    CString szAddr = Trim(szSource.Mid(nFound));

    CStringArray tokens;
    FillTokenArray(szAddr, tokens, ',');

    int nTokens = tokens.GetSize();
    for( int i(0); i < nTokens; i++ ) {
      CString szTok = Trim(tokens.GetAt(i));

      if ( FindAndRemove(szTok, _T("м."), _T("місто ")) ) {
        szCity = szTok;
      }
      else if ( FindAndRemove(szTok, _T("обл."), _T("область")) ) {
        szRegion = szTok;
      }
      else if ( FindAndRemove(szTok, _T("вул."), _T("вулиця ")) ) {
        szStreet = szTok;
        cStreetType = '1';
      }
      else if ( FindAndRemove(szTok, _T("пл."), _T("площа ")) ) {
        szStreet = szTok;
        cStreetType = '2';
      }
      else if ( FindAndRemove(szTok, _T("буд."), _T("б-к"),_T("будинок")) ) {
        szBuild = szTok;
      }
      else if ( FindAndRemove(szTok, _T("кв."), _T("кв-ра")) ) {
        szFlat = szTok;
      }

    }

  }


}

/////////////////////////////////////////////////////////////////////////////
// CWitnessDlg message handlers
BOOL ParseG10(CRSBirthes& rs) {
  CString sg10 = rs.GetGr10();
  if ( sg10.IsEmpty() ) {
    return false;
  }
  CString s, szMedDocName, szMedDocNum, szMedDocDate, szMedDocBy;

  int nSvid = sg10.Find(_T("Свідки"));
  if ( -1==nSvid ) {
    nSvid = sg10.Find(_T("свідки"));
  }
  if ( -1==nSvid ) {
    return false;
  }

  int nFound = sg10.Find(_T("видане "));
  if ( -1==nFound ) {
    nFound = sg10.Find(_T("видана "));
  }
  if ( nFound > 0 ) {
    s = Trim(sg10.Mid(nFound + 7, nSvid - nFound - 7));
    s.Replace(_T("р."), _T(""));
    szMedDocDate = GetDateFromS(s);
    if ( false==szMedDocDate.IsEmpty() ) {
      szMedDocBy = s;
      szMedDocBy.Replace(szMedDocDate, _T(""));
      szMedDocBy.TrimRight();
    }

    szMedDocName = sg10.Left(nFound);
    szMedDocName.Replace(_T("№"), _T(""));
    szMedDocName.TrimRight();
    nFound = szMedDocName.FindOneOf(_T("0123456789"));
    while ( nFound >= 0 ) {
      TCHAR c = szMedDocName[nFound];
      if ( isdigit(c) || c=='-' || c=='/' ) {
        szMedDocNum += c;
      }
      else {
        break;
      }
      nFound++;
    }
    szMedDocName.Replace(szMedDocNum, _T(""));
    szMedDocName = FindAndReplace(szMedDocName, _T("  "), _T(" "), true);
  }

  CString szSvidki = sg10.Mid(nSvid + 7);
  CString szSvid1  = GetTok(szSvidki, 0, _T(";"));
  CString szSvid2  = GetTok(szSvidki, 1, _T(";"));

  CWitnessDlg dlg(theApp.m_pMainWnd);

  dlg.m_szGR10      = sg10;
  dlg.m_MedDocName  = szMedDocName;
  dlg.m_MedDocNum   = szMedDocNum;
  dlg.m_MedDocDate  = szMedDocDate;
  dlg.m_MedDocBy    = szMedDocBy;

  FillWitness(szSvid1, dlg.m_Surname1, dlg.m_Name1, dlg.m_Patronymic1, 
              dlg.m_DocSeria1, dlg.m_DocNumber1, dlg.m_DocDate1, dlg.m_DocOrgan1,
              dlg.m_Country1, dlg.m_Region1, dlg.m_District1, dlg.m_City1,
              dlg.m_Street1, dlg.m_cStreetType1, dlg.m_Build1, dlg.m_Flat1
             );
  
  FillWitness(szSvid2, dlg.m_Surname2, dlg.m_Name2, dlg.m_Patronymic2, 
              dlg.m_DocSeria2, dlg.m_DocNumber2, dlg.m_DocDate2, dlg.m_DocOrgan2,
              dlg.m_Country2, dlg.m_Region2, dlg.m_District2, dlg.m_City2,
              dlg.m_Street2, dlg.m_cStreetType2, dlg.m_Build2, dlg.m_Flat2
             );

  dlg.m_szTitle.Format(_T("Уточніть дані про свідків, А/З про народження № %d від %s"),  rs.m_NUMBER, rs.m_DATEREG);
  
  if ( dlg.DoModal() == IDOK ) {
    rs.m_szBirhDocName              = dlg.m_MedDocName;
    rs.m_MEDICAL_CERTIFICATE_NUMBER = dlg.m_MedDocNum;
    rs.m_MEDICAL_CERTIFICATE_DATE   = dlg.m_MedDocDate;
    rs.m_MEDICAL_CERTIFICATE_BY     = dlg.m_MedDocBy;

    switch( dlg.m_DocType1 ) {
      case 0: dlg.m_DocType1 = 1; break;
    }

    switch( dlg.m_DocType2 ) {
      case 0: dlg.m_DocType2 = 1; break;
    }

    return true;
  }

  return false;
}

