// RSDeathes.cpp : implementation file
//
#include "stdafx.h"
#include "Era2Xml.h"
#include "RSDeathes.h"

#include "DateFunc.h"
#include "db.h"

#include "..\Common\DaoErr.h"
#include "..\Common\CyrString.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define O_BRACKET TCHAR('{')
#define C_BRACKET TCHAR('}')

LPCTSTR g_szDeathDate = _T("Дата смерті:");
LPCTSTR g_szBirthDate = _T("Дата народження:");
LPCTSTR g_szMCSeria   = _T("{Серія ВК:");
LPCTSTR g_szMCNumber  = _T("{Номер ВК:");
LPCTSTR g_szMCDate    = _T("{Дата видачі ВК:");
LPCTSTR g_szMCBy      = _T("{Ким видано ВК:");
extern LPCTSTR g_szEmpty;

void FillTokenArray(const char* szSrc, CStringArray& tokens, char cDelim);
BOOL FindAndRemove(CString& s, LPCTSTR szFind1, LPCTSTR szFind2=NULL, LPCTSTR szFind3=NULL);

/////////////////////////////////////////////////////////////////////////////
// CRSDeathes

IMPLEMENT_DYNAMIC(CRSDeathes, CDaoRecordset)

CRSDeathes::CRSDeathes(CDaoDatabase* pdb)
           :CDaoRecordset(pdb) {
  ClearFields();
	m_nDefaultType = dbOpenTable;
}


CRSDeathes::~CRSDeathes() {
}

void CRSDeathes::ClearFields() {
	m_ID = 0;
	m_SEX = FALSE;
	m_DATEREG.Empty();
	m_NUMBER = 0;
	m_FLAGS = 0;
	m_RENEW = FALSE;
	m_SURNAME.Empty();
	m_NAME.Empty();
	m_PATRONYMIC.Empty();
	m_CITIZENSHIP.Empty();
	m_NATIONALITY.Empty();
	m_DOD_FLAG = FALSE;
  m_DeathDate = (DATE)0;
	m_DEATH_DATE.Empty();
	m_DP_COUNTRY.Empty();
	m_DP_REGION.Empty();
	m_DP_DISTRICT.Empty();
	m_DP_CITY.Empty();
	m_CAUSE_OF_DEATH.Empty();
	m_DOB_FLAG = FALSE;
  m_BirthDate = (DATE)0;
	m_BIRTH_DATE.Empty();
	m_BP_COUNTRY.Empty();
	m_BP_REGION.Empty();
	m_BP_DISTRICT.Empty();
	m_BP_CITY.Empty();
	m_RP_ZIPCODE.Empty();
	m_RP_COUNTRY.Empty();
	m_RP_REGION.Empty();
	m_RP_DISTRICT.Empty();
	m_RP_CITY.Empty();
	m_RP_STREET.Empty();
	m_RP_HOUSE.Empty();
	m_RP_FLAT.Empty();
	m_PASSPORT_TYPE = 0;
	m_PASSPORT_SERIA.Empty();
	m_PASSPORT_NUMBER.Empty();
	m_PASSPORT_DATE.Empty();
	m_PASSPORT_BY.Empty();
	m_TAX_CODE.Empty();
	m_MEDICAL_CERT_TYPE.Empty();
	m_MEDICAL_CERT_NUMBER.Empty();
	m_MEDICAL_CERT_BY.Empty();
	m_MEDICAL_CERT_DATE.Empty();
	m_DECLARANT_NAME.Empty();
	m_DECLARANT_ADDRESS.Empty();
	m_DECLARANT_PASSPORT_TYPE = 0;
	m_DECLARANT_PASSPORT_SERIA.Empty();
	m_DECLARANT_PASSPORT_NUMBER.Empty();
	m_DECLARANT_PASSPORT_DATE.Empty();
	m_DECLARANT_PASSPORT_BY.Empty();
	m_CERTIFICATE_SERIA.Empty();
	m_CERTIFICATE_NUMBER.Empty();
	m_NOTICE.Empty();
	m_EXTNOTES.Empty();
}

void CRSDeathes::Read() {
  ClearFields();
	m_ID      = GetFieldLong (*this, _T("ID"));
  m_SEX     = GetFieldByte (*this, _T("SEX"));
  m_DATEREG = GetFieldDate (*this, _T("DATEREG"), &m_odtDateReg);
  m_NUMBER  = GetFieldShort(*this, _T("NUMBER"));
  m_FLAGS   = GetFieldLong (*this, _T("FLAGS"));
	m_RENEW   = GetFieldByte (*this, _T("RENEW"));

  m_SURNAME     = GetFieldString(*this, _T("SURNAME"));
	m_NAME        = GetFieldString(*this, _T("NAME"));
	m_PATRONYMIC  = GetFieldString(*this, _T("PATRONYMIC"));
  m_CITIZENSHIP = GetFieldString(*this, _T("CITIZENSHIP"));
  m_NATIONALITY = GetFieldString(*this, _T("NATIONALITY"));
  m_DOD_FLAG    = GetFieldByte  (*this, _T("DOD_FLAG"));
  m_DEATH_DATE  = GetFieldDate  (*this, _T("DEATH_DATE"), &m_DeathDate);
  
  m_DP_COUNTRY  = GetFieldString(*this, _T("DP_COUNTRY"));
  m_DP_REGION   = GetFieldString(*this, _T("DP_REGION"));
  m_DP_DISTRICT = GetFieldString(*this, _T("DP_DISTRICT"));
  m_DP_CITY     = GetFieldString(*this, _T("DP_CITY"));

  m_CAUSE_OF_DEATH = GetFieldString(*this, _T("CAUSE_OF_DEATH"));
  m_DOB_FLAG       = GetFieldByte  (*this, _T("DOD_FLAG"));
  m_BIRTH_DATE     = GetFieldDate  (*this, _T("BIRTH_DATE"), &m_BirthDate);
  m_BP_COUNTRY     = GetFieldString(*this, _T("BP_COUNTRY"));
  m_BP_REGION      = GetFieldString(*this, _T("BP_REGION"));
  m_BP_DISTRICT    = GetFieldString(*this, _T("BP_DISTRICT"));
  m_BP_CITY        = GetFieldString(*this, _T("BP_CITY"));

  m_RP_ZIPCODE     = GetFieldString(*this, _T("RP_ZIPCODE"));
  m_RP_COUNTRY     = GetFieldString(*this, _T("RP_COUNTRY"));
  m_RP_REGION      = GetFieldString(*this, _T("RP_REGION"));
  m_RP_DISTRICT    = GetFieldString(*this, _T("RP_DISTRICT"));
  m_RP_CITY        = GetFieldString(*this, _T("RP_CITY"));
  m_RP_STREET      = GetFieldString(*this, _T("RP_STREET"));
  m_RP_HOUSE       = GetFieldString(*this, _T("RP_HOUSE"));
  m_RP_FLAT        = GetFieldString(*this, _T("RP_FLAT"));

  m_PASSPORT_TYPE   = GetFieldByte  (*this, _T("PASSPORT_TYPE"));
  m_PASSPORT_SERIA  = GetFieldString(*this, _T("PASSPORT_SERIA"));
  m_PASSPORT_NUMBER = GetFieldString(*this, _T("PASSPORT_NUMBER"));
  m_PASSPORT_DATE   = GetFieldDate  (*this, _T("PASSPORT_DATE"));
  m_PASSPORT_BY     = GetFieldString(*this, _T("PASSPORT_BY"));
  m_TAX_CODE        = GetFieldString(*this, _T("TAX_CODE"));

  m_MEDICAL_CERT_TYPE = GetFieldString(*this, _T("MEDICAL_CERT_TYPE"));
  m_MEDICAL_CERT_TYPE.Replace(_T("№"), _T(""));
  m_MEDICAL_CERT_TYPE.TrimRight();


  m_MEDICAL_CERT_NUMBER = GetFieldString(*this, _T("MEDICAL_CERT_NUMBER"));
  m_MEDICAL_CERT_BY     = GetFieldString(*this, _T("MEDICAL_CERT_BY"));
  m_MEDICAL_CERT_DATE   = GetFieldDate  (*this, _T("MEDICAL_CERT_DATE"));

  m_DECLARANT_NAME            = GetFieldString(*this, _T("DECLARANT_NAME"));
  m_DECLARANT_ADDRESS         = GetFieldString(*this, _T("DECLARANT_ADDRESS"));
  m_DECLARANT_PASSPORT_TYPE   = GetFieldByte  (*this, _T("DECLARANT_PASSPORT_TYPE"));
  m_DECLARANT_PASSPORT_SERIA  = GetFieldString(*this, _T("DECLARANT_PASSPORT_SERIA"));
  m_DECLARANT_PASSPORT_NUMBER = GetFieldString(*this, _T("DECLARANT_PASSPORT_NUMBER"));
  m_DECLARANT_PASSPORT_DATE   = GetFieldDate  (*this, _T("DECLARANT_PASSPORT_DATE"));
  m_DECLARANT_PASSPORT_BY     = GetFieldString(*this, _T("DECLARANT_PASSPORT_BY"));

  m_CERTIFICATE_SERIA         = GetFieldString(*this, _T("CERTIFICATE_SERIA"));
  m_CERTIFICATE_NUMBER        = GetFieldString(*this, _T("CERTIFICATE_NUMBER"));

  m_NOTICE   = GetFieldString(*this, _T("NOTICE"));
  m_EXTNOTES = GetFieldString(*this, _T("EXTNOTES"));
}

CString CRSDeathes::GetDefaultSQL() {
  return _T("[DEATHES]");
}

CString CRSDeathes::MakeKey() {
  CString szKey;
  szKey.Format(_T("%d%s%s%s%s"), m_NUMBER, m_DATEREG, m_SURNAME, m_NAME, m_PATRONYMIC);
  return szKey;
}

BOOL CRSDeathes::InPeriod(COleDateTime& odtFrom, COleDateTime& odtTill) {
  return (odtFrom <= m_odtDateReg && m_odtDateReg <= odtTill);
}


/////////////////////////////////////////////////////////////////////////////
// CRSDeathes diagnostics

#ifdef _DEBUG
void CRSDeathes::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CRSDeathes::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG


CString CRSDeathes::GetSvNeVidano() {
  CString s;
  if ( m_NOTICE.Find(_T("Свідоцтво не видано."))>=0 ) {
    s = _T("Свідоцтво не видано.");
  }
  if ( m_NOTICE.Find(_T("Свідоцтво не видане."))>=0 ) {
    s = _T("Свідоцтво не видане.");
  }
  return s;
}

bool CRSDeathes::IsNoticeBirthDate() {
  return m_NOTICE.Find(g_szBirthDate, 0)==-1 ? false : true;
}
CString CRSDeathes::GetNoticeBirthDateDDMMMYYYY() {
  CString s = GetSentence(m_NOTICE, g_szBirthDate );
  s = FindAndReplace(s, g_szBirthDate, _T(""), true);
  s = FindAndReplace(s, _T("р."), _T(""), true);
  s = FindAndReplace(s, _T("року"), _T(""), true);
  return Trim(s);
}
CString CRSDeathes::GetNoticeBirthDay() {
  return GetStrDay( GetNoticeBirthDateDDMMMYYYY() );
}

CString CRSDeathes::GetNoticeBirthMonth() {
  return GetStrMonth( GetNoticeBirthDateDDMMMYYYY() );
}
CString CRSDeathes::GetNoticeBirthYear() {
  return GetStrYear( GetNoticeBirthDateDDMMMYYYY() );
}

bool CRSDeathes::IsNoticeDeathDate() {
  return m_NOTICE.Find(g_szDeathDate, 0)==-1 ? false : true;
}
CString CRSDeathes::GetNoticeDeathDateDDMMMYYYY() {
  CString s = GetSentence(m_NOTICE, g_szDeathDate );
  s = FindAndReplace(s, g_szDeathDate, _T(""), true);
  s = FindAndReplace(s, _T("р."), _T(""), true);
  s = FindAndReplace(s, _T("року"), _T(""), true);
  return Trim(s);
}

CString CRSDeathes::GetNoticeDeathDay() {
  return GetStrDay( GetNoticeDeathDateDDMMMYYYY() );
}
CString CRSDeathes::GetNoticeDeathMonth() {
  return GetStrMonth( GetNoticeDeathDateDDMMMYYYY() );
}
CString CRSDeathes::GetNoticeDeathYear() {
  return GetStrYear( GetNoticeDeathDateDDMMMYYYY() );
}

CString CRSDeathes::GetNotices() {
  CString s, sMemo;
  sMemo = m_NOTICE;
  s = GetSvNeVidano();
  if ( !s.IsEmpty() ) {
    sMemo = FindAndReplace(sMemo, s, g_szEmpty, true);
  }
  s = GetSentence(sMemo, g_szDeathDate);
  if ( !s.IsEmpty() )
    sMemo = FindAndReplace(sMemo, s, g_szEmpty, true);
  s = GetSentence(sMemo, g_szBirthDate );
  if ( !s.IsEmpty() )
  sMemo = FindAndReplace(sMemo, s, g_szEmpty, true);
  return sMemo;
}
CString CRSDeathes::GetNDov() {
  CString sMemo;
  sMemo = m_NOTICE;
  return GetNumFromStr(sMemo, _T("№"), false);
}

bool CRSDeathes::IsPassport() {
  return ( false==IsEmptyText(m_PASSPORT_SERIA) && false==IsEmptyText(m_PASSPORT_NUMBER) );
}

CString CRSDeathes::GetMilitaryCardSeria() {
  CString s = GetSentence(m_EXTNOTES, g_szMCSeria, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, g_szMCSeria, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return s;
}
CString CRSDeathes::GetMilitaryCardNumber() {
  CString s = GetSentence(m_EXTNOTES, g_szMCNumber, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, g_szMCNumber, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return s;
}

CString CRSDeathes::GetMilitaryCardDate() {
  CString s = GetSentence(m_EXTNOTES, g_szMCDate, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, g_szMCDate, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return s;
}
CString CRSDeathes::GetMilitaryCardBy() {
  CString s = GetSentence(m_EXTNOTES, g_szMCBy, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, g_szMCBy, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return s;
}

CString CRSDeathes::SetMilitaryCard(CString& sMemo, const CString& sSeria, const CString& sNumber, const COleDateTime& odt, const CString& sBy) {
  // At firts remove military card data

  CString s = GetSentence(sMemo, g_szMCSeria, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, g_szEmpty, false);

  s = GetSentence(sMemo, g_szMCNumber, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, g_szEmpty, false);

  s = GetSentence(sMemo, g_szMCDate, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, g_szEmpty, false);

  s = GetSentence(sMemo, g_szMCBy, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, g_szEmpty, false);

  sMemo = Trim(sMemo);

  if ( FALSE==sSeria.IsEmpty() && FALSE==sNumber.IsEmpty() && COleDateTime::valid==odt.GetStatus() ) {
    s.Format(_T("%s %s%c %s %s%c %s %02d.%02d.%04d%c %s %s%c"),
              g_szMCSeria, sSeria, C_BRACKET,
              g_szMCNumber, sNumber, C_BRACKET,
              g_szMCDate, odt.GetDay(), odt.GetMonth(), odt.GetYear(), C_BRACKET,
              g_szMCBy, sBy, C_BRACKET);
    sMemo += ' ';
    sMemo += s;
    sMemo = Trim(sMemo);
  }

  return sMemo;
}

LPCTSTR CRSDeathes::GetIsNotRecognized() {
  if ( m_NAME.IsEmpty() && m_PATRONYMIC.IsEmpty() && m_SURNAME.Find(_T("Невід"))>=0 ) {
    return _T("true");
  }
  return _T("false");
}

Duration CRSDeathes::GetAge() {
  return ::GetAge(m_BirthDate, m_DeathDate);
}

void CRSDeathes::ParseDeclarantFIO(CString& szSurname, CString& szName, CString& szPatronymic, CString& szOrganization) {
  szSurname    = GetTok(m_DECLARANT_NAME, 0, " ");
  szName       = GetTok(m_DECLARANT_NAME, 1, " ");
  szPatronymic = GetTok(m_DECLARANT_NAME, 2, " ");

  int nFound = m_DECLARANT_NAME.Find(szPatronymic);
  if ( nFound > 0 ) {
    nFound += szPatronymic.GetLength();
    szOrganization = m_DECLARANT_NAME.Mid(nFound);

    szOrganization.Replace(_T("Співпрацівник"), _T(""));
    szOrganization.Replace(_T("Співробітник"), _T(""));

  }
}

void CRSDeathes::ParseDeclarantAddress(CString& szCountry, CString& szRegion, CString& szDistrict, CString& szCity,
                                       TCHAR& cStreetType, CString& szStreet, CString& szBuild, CString& szFlat)
{
  szCountry = _T("Україна");

  CStringArray tokens;

  FillTokenArray(m_DECLARANT_ADDRESS, tokens, ',');

  int nTokens = tokens.GetSize();

  if ( nTokens ) {
    CString szTok;
    for( int i(0); i < nTokens; i++ ) {
      szTok = tokens[i];
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
      else if ( FindAndRemove(szTok, _T("бул."), _T("бульвар "), _T("б-р ")) ) {
        szStreet = szTok;
        cStreetType = '3';
      }
      else if ( FindAndRemove(szTok, _T("пр."), _T("проспект "), _T("пр-кт ")) ) {
        szStreet = szTok;
        cStreetType = '4';
      }
      else if ( FindAndRemove(szTok, _T("буд."), _T("б-к"),_T("будинок")) ) {
        szBuild = szTok;
      }
      else if ( FindAndRemove(szTok, _T("кв."), _T("кв-ра")) ) {
        szFlat = szTok;
      }

      if ( szBuild.IsEmpty() && szFlat.IsEmpty() ) {
        szTok = tokens[nTokens-1];
        szBuild = Trim(GetTok(szTok, 0, _T("/\\")));
        szFlat  = Trim(GetTok(szTok, 1, _T("/\\")));
      }
    }
  }

}
