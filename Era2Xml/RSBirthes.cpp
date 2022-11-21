// RSBirthes.cpp : implementation file
//

#include "stdafx.h"
#include "Era2Xml.h"

#include "RSBirthes.h"
#include "Globals.h"

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

const char* rsb_NewSurname      = _T("Нове прізвище:");
const char* rsb_NewName         = _T("Нове ім'я:");
const char* rsb_NewPatronymic   = _T("Нове по батькові:");
const char* rsb_NewMotherSurname= _T("Нове прізвище матері:");
const char* rsb_FatherDate      = _T("Дата народження батька:");
const char* rsb_MotherDate      = _T("Дата народження матері:");
const char* rsb_Gr10            = _T("Г10:");
const char* rsb_VerdictBy       = _T("На підставі рішення:");
const char* rsb_VerdictDate     = _T("Дата прийняття рішення:");
const char* rsb_VerdictNumber   = _T("Номер рішення:");
const char* rsb_NewBirthDate    = _T("Дата народження після усиновлення:");

const char* rsb_NewBirthCountry  = _T("Нова держава народження:");
const char* rsb_NewBirthRegion   = _T("Нова область народження:");
const char* rsb_NewBirthCity     = _T("Нове місто народження:");
const char* rsb_NewBirthDistrict = _T("Нове район народження:");

LPCTSTR g_szP2Type   = _T("{П2:");
LPCTSTR g_szP2Seria  = _T("{Серія П2:");
LPCTSTR g_szP2Number = _T("{Номер П2:");
LPCTSTR g_szP2Date   = _T("{Дата видачі П2:");
LPCTSTR g_szP2By     = _T("{Ким видано П2:");
LPCTSTR g_szGR10     = _T("{Г10:");

extern LPCTSTR g_szEmpty;


void FillTokenArray(const char* szSrc, CStringArray& tokens, char cDelim);
BOOL FindAndRemove(CString& s, LPCTSTR szFind1, LPCTSTR szFind2=NULL, LPCTSTR szFind3=NULL);

/////////////////////////////////////////////////////////////////////////////
// CRSBirthes

IMPLEMENT_DYNAMIC(CRSBirthes, CDaoRecordset)

CRSBirthes::CRSBirthes(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
  ClearFields();
	m_nDefaultType = dbOpenTable;//dbOpenDynaset;
}

void CRSBirthes::ClearFields() {
	m_ID = 0;
	m_SEX = FALSE;
  m_DATEREG.Empty();
	m_NUMBER = 0;
	m_RENEW = 0;
	m_SURNAME.Empty();
	m_NAME.Empty();
	m_PATRONYMIC.Empty();
  m_BIRTH_DATE.Empty();
	m_BP_FLAG = FALSE;
	m_BP_COUNTRY.Empty();
	m_BP_REGION.Empty();
	m_BP_CITY.Empty();
	m_BP_DISTRICT.Empty();
	m_NKIDS = 0;
	m_BYCOUNT = 0;
	m_ALIVE_FLAG = FALSE;
	m_SOURCE_TYPE = 0;
  m_SOURCE_NDOC.Empty();
  m_SOURCE_DATE.Empty();
  m_SOURCE_BY.Empty();
	m_MEDICAL_CERTIFICATE_NUMBER.Empty();
	m_MEDICAL_CERTIFICATE_DATE.Empty();
	m_MEDICAL_CERTIFICATE_BY.Empty();
	m_FATHER_SURNAME.Empty();
	m_FATHER_NAME.Empty();
	m_FATHER_PATRONYMIC.Empty();
	m_FATHER_DOB_FLAG = FALSE;
	m_FATHER_BIRTH_DATE.Empty();
	m_FATHER_CITIZENSHIP.Empty();
	m_FATHER_COUNTRY.Empty();
	m_FATHER_REGION.Empty();
	m_FATHER_CITY.Empty();
	m_FATHER_DISTRICT.Empty();
	m_FATHER_STREET.Empty();
	m_FATHER_HOUSE.Empty();
	m_FATHER_FLAT.Empty();
	m_MOTHER_SURNAME.Empty();
	m_MOTHER_NAME.Empty();
	m_MOTHER_PATRONYMIC.Empty();
	m_MOTHER_DOB_FLAG = FALSE;
	m_MOTHER_BIRTH_DATE.Empty();
	m_MOTHER_CITIZENSHIP.Empty();
	m_MOTHER_COUNTRY.Empty();
	m_MOTHER_REGION.Empty();
	m_MOTHER_CITY.Empty();
	m_MOTHER_DISTRICT.Empty();
	m_MOTHER_STREET.Empty();
	m_MOTHER_HOUSE.Empty();
	m_MOTHER_FLAT.Empty();
  m_DECLARANT_TYPE = 0;
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

  m_szBirhDocName.Empty();

}

CString CRSBirthes::GetDefaultSQL() {
	return _T("[BIRTHES]");
}

void CRSBirthes::Read() {
  ClearFields();
  m_ID      = GetFieldLong (*this, _T("ID"));
  m_NUMBER  = GetFieldShort(*this, _T("NUMBER"));
	m_SEX     = GetFieldByte (*this, _T("SEX"));
  m_DATEREG = GetFieldDate (*this, _T("DATEREG"), &m_odtDateReg);
  m_RENEW   = GetFieldLong (*this, _T("RENEW"));

  m_SURNAME     = GetFieldString (*this, _T("SURNAME"));
	m_NAME        = GetFieldString (*this, _T("NAME"));
	m_PATRONYMIC  = GetFieldString (*this, _T("PATRONYMIC"));
	m_BIRTH_DATE  = GetFieldDate   (*this, _T("BIRTH_DATE"));

	m_BP_FLAG     = GetFieldByte   (*this, _T("BP_FLAG"));
	m_BP_COUNTRY  = GetFieldString (*this, _T("BP_COUNTRY"));
	m_BP_REGION   = GetFieldString (*this, _T("BP_REGION"));
	m_BP_CITY     = GetFieldString (*this, _T("BP_CITY"));
	m_BP_DISTRICT = GetFieldString (*this, _T("BP_DISTRICT"));

	m_NKIDS       = GetFieldByte   (*this, _T("NKIDS"));
	m_BYCOUNT     = GetFieldByte   (*this, _T("BYCOUNT"));
	m_ALIVE_FLAG  = GetFieldByte   (*this, _T("ALIVE_FLAG"));
	m_SOURCE_TYPE = GetFieldByte   (*this, _T("SOURCE_TYPE"));
  m_SOURCE_NDOC = GetFieldString (*this, _T("SOURCE_NDOC"));
  m_SOURCE_DATE = GetFieldDate   (*this, _T("SOURCE_DATE"));
  m_SOURCE_BY   = GetFieldString (*this, _T("SOURCE_BY"));
	m_MEDICAL_CERTIFICATE_NUMBER = GetFieldString (*this, _T("MEDICAL_CERTIFICATE_NUMBER"));

  m_FATHER_SURNAME     = GetFieldString (*this, _T("FATHER_SURNAME"));
	m_FATHER_NAME        = GetFieldString (*this, _T("FATHER_NAME"));
	m_FATHER_PATRONYMIC  = GetFieldString (*this, _T("FATHER_PATRONYMIC"));
	m_FATHER_DOB_FLAG    = GetFieldByte   (*this, _T("FATHER_DOB_FLAG"));
	m_FATHER_BIRTH_DATE  = GetFieldDate   (*this, _T("FATHER_BIRTH_DATE"));
	m_FATHER_CITIZENSHIP = GetFieldString (*this, _T("FATHER_CITIZENSHIP"));
	m_FATHER_COUNTRY     = GetFieldString (*this, _T("FATHER_COUNTRY"));
	m_FATHER_REGION      = GetFieldString (*this, _T("FATHER_REGION"));
	m_FATHER_CITY        = GetFieldString (*this, _T("FATHER_CITY"));
	m_FATHER_DISTRICT    = GetFieldString (*this, _T("FATHER_DISTRICT"));
	m_FATHER_STREET      = GetFieldString (*this, _T("FATHER_STREET"));
	m_FATHER_HOUSE       = GetFieldString (*this, _T("FATHER_HOUSE"));
	m_FATHER_FLAT        = GetFieldString (*this, _T("FATHER_FLAT"));

  m_MOTHER_SURNAME     = GetFieldString (*this, _T("MOTHER_SURNAME"));
	m_MOTHER_NAME        = GetFieldString (*this, _T("MOTHER_NAME"));
	m_MOTHER_PATRONYMIC  = GetFieldString (*this, _T("MOTHER_PATRONYMIC"));
	m_MOTHER_DOB_FLAG    = GetFieldByte   (*this, _T("MOTHER_DOB_FLAG"));
	m_MOTHER_BIRTH_DATE  = GetFieldDate   (*this, _T("MOTHER_BIRTH_DATE"));
	m_MOTHER_CITIZENSHIP = GetFieldString (*this, _T("MOTHER_CITIZENSHIP"));
	m_MOTHER_COUNTRY     = GetFieldString (*this, _T("MOTHER_COUNTRY"));
	m_MOTHER_REGION      = GetFieldString (*this, _T("MOTHER_REGION"));
	m_MOTHER_CITY        = GetFieldString (*this, _T("MOTHER_CITY"));
	m_MOTHER_DISTRICT    = GetFieldString (*this, _T("MOTHER_DISTRICT"));
	m_MOTHER_STREET      = GetFieldString (*this, _T("MOTHER_STREET"));
	m_MOTHER_HOUSE       = GetFieldString (*this, _T("MOTHER_HOUSE"));
	m_MOTHER_FLAT        = GetFieldString (*this, _T("MOTHER_FLAT"));

  m_DECLARANT_TYPE            = GetFieldByte   (*this, _T("DECLARANT_TYPE"));
	m_DECLARANT_NAME            = GetFieldString (*this, _T("DECLARANT_NAME"));
	m_DECLARANT_ADDRESS         = GetFieldString (*this, _T("DECLARANT_ADDRESS"));
	m_DECLARANT_PASSPORT_TYPE   = GetFieldByte   (*this, _T("DECLARANT_PASSPORT_TYPE"));
	m_DECLARANT_PASSPORT_SERIA  = GetFieldString (*this, _T("DECLARANT_PASSPORT_SERIA"));
	m_DECLARANT_PASSPORT_NUMBER = GetFieldString (*this, _T("DECLARANT_PASSPORT_NUMBER"));
	m_DECLARANT_PASSPORT_DATE   = GetFieldDate   (*this, _T("DECLARANT_PASSPORT_DATE"));
	m_DECLARANT_PASSPORT_BY     = GetFieldString (*this, _T("DECLARANT_PASSPORT_BY"));
	m_CERTIFICATE_SERIA         = GetFieldString (*this, _T("CERTIFICATE_SERIA"));
	m_CERTIFICATE_NUMBER        = GetFieldString (*this, _T("CERTIFICATE_NUMBER"));
	m_NOTICE                    = GetFieldString (*this, _T("NOTICE"));
  m_EXTNOTES                  = GetFieldString (*this, _T("EXTNOTES"));

  m_szBirhDocName = m_ALIVE_FLAG ? _T("Медичне свідоцтво про народження") : _T("Свідоцтво про перинатальну смерть");

}

CString CRSBirthes::MakeKey() {
  CString szKey;
  szKey.Format(_T("%d%s%s%s%s"), m_NUMBER, m_DATEREG, m_SURNAME, m_NAME, m_PATRONYMIC);
  return szKey;
}
BOOL CRSBirthes::InPeriod(COleDateTime& odtFrom, COleDateTime& odtTill) {
  return (odtFrom <= m_odtDateReg && m_odtDateReg <= odtTill);
}


/////////////////////////////////////////////////////////////////////////////
// CRSBirthes diagnostics

#ifdef _DEBUG
void CRSBirthes::AssertValid() const {
	CDaoRecordset::AssertValid();
}

void CRSBirthes::Dump(CDumpContext& dc) const {
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG

CString CRSBirthes::GetNewSurname(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  return GetBracketString(sMemo, rsb_NewSurname);
}
CString CRSBirthes::GetNewSurnameFromMemo(const CString& sMemo, const CString& sOldSurname) {
  CString sRet = GetBracketString(sMemo, rsb_NewSurname);
  if ( sRet.IsEmpty() )
    sRet = sOldSurname;
  return sRet;
}
CString CRSBirthes::GetNewOrOldSurname() {
  CString s = GetNewSurname();
  if ( s.IsEmpty() )
    s = m_SURNAME;
  return s;
}
CString CRSBirthes::GetNewName(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString sNewName = GetBracketString(sMemo, rsb_NewName);
  if ( sNewName==m_NAME )
    return g_szEmpty;
  return sNewName;
}
CString CRSBirthes::GetNewNameFromMemo(const CString& sMemo, const CString& sOldName) {
  CString sRet = GetBracketString(sMemo, rsb_NewName);
  if ( sRet.IsEmpty() )
    sRet = sOldName;
  return sRet;
}
CString CRSBirthes::GetNewOrOldName() {
  CString s = GetNewName();
  if ( s.IsEmpty() )
    s = m_NAME;
  return s;
}
CString CRSBirthes::GetNewPatronymic(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString sNewPatronymic = GetBracketString(sMemo, rsb_NewPatronymic);
  if ( sNewPatronymic==m_PATRONYMIC )
    return g_szEmpty;
  return sNewPatronymic;
}
CString CRSBirthes::GetNewPatronymicFromMemo(const CString& sMemo, const CString& sOldPatronymic) {
  CString sRet = GetBracketString(sMemo, rsb_NewPatronymic);
  if ( sRet.IsEmpty() )
    sRet = sOldPatronymic;
  return sRet;
}

CString CRSBirthes::GetNewOrOldPatronymic() {
  CString s = GetNewPatronymic();
  if ( s.IsEmpty() )
    s = m_PATRONYMIC;
  return s;
}
CString CRSBirthes::GetNewMotherSurname(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString sNewSurname = GetBracketString(sMemo, rsb_NewMotherSurname);;
  if ( sNewSurname==m_MOTHER_SURNAME )
    return g_szEmpty;
  return sNewSurname;
}
CString CRSBirthes::GetFatherDate(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  return GetBracketString(sMemo, rsb_FatherDate);
}
CString CRSBirthes::GetMotherDate(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  return GetBracketString(sMemo, rsb_MotherDate);
}


CString CRSBirthes::GetNotices() {
  CString s, sMem;
  sMem = m_NOTICE;
/*
  s = GetSvNeVidano();
  if ( !s.IsEmpty() ) {
    sMem = FindAndReplace(sMem, s, _T(""), true);
  }
*/
  return sMem;
}

CString CRSBirthes::GetNDov() {
  CString sMemo;
  sMemo = m_NOTICE;
  return GetNumFromStr(sMemo, _T("№"), false);
}

int CRSBirthes::GetPassport2Type(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, g_szP2Type, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, g_szP2Type, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return atoi(s);
}
CString CRSBirthes::GetPassport2Seria(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, g_szP2Seria, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, g_szP2Seria, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return s;
}
CString CRSBirthes::GetPassport2Number(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, g_szP2Number, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, g_szP2Number, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return s;
}
CString CRSBirthes::GetPassport2Date(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, g_szP2Date, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, g_szP2Date, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return s;
}
/*
COleDateTime CRSBirthes::GetPassport2ODT(LPCTSTR szMemo) {
  CString s = GetPassport2Date(szMemo);
  return ParseDate(s);
}
*/


CString CRSBirthes::GetPassport2By(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, g_szP2By, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, g_szP2By, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return s;
}

CString CRSBirthes::GetGr10(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, g_szGR10, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, g_szGR10, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return s;
}
CString CRSBirthes::GetVerdictOf(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, rsb_VerdictBy, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, rsb_VerdictBy, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return s;
}

/*
COleDateTime CRSBirthes::GetVerdictDate(LPCTSTR szMemo) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, rsb_VerdictDate, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, rsb_VerdictDate, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  COleDateTime ed = ParseDate(s);
  if ( COleDateTime::valid != ed.GetStatus() )
    ed.SetStatus( COleDateTime::null );
  return ed;
}

CString CRSBirthes::GetVerdictNumber(LPCTSTR szMemo) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, rsb_VerdictNumber, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, rsb_VerdictNumber, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return s;
}
*/


CString CRSBirthes::GetNewBirthCountry(BOOL fStrikeOut, LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, rsb_NewBirthCountry, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, rsb_NewBirthCountry, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  if ( s.IsEmpty() )
    s = m_BP_COUNTRY;
  if ( fStrikeOut && s==m_BP_COUNTRY ) 
    s = CString('-', 20);
  return s;
}
CString CRSBirthes::GetNewBirthRegion(BOOL fStrikeOut, LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, rsb_NewBirthRegion, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, rsb_NewBirthRegion, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  if ( s.IsEmpty() )
    s = m_BP_REGION;
  if ( fStrikeOut && s==m_BP_REGION )
    s = CString('-', 20);
  return s;
}

CString CRSBirthes::GetNewBirthCity(BOOL fStrikeOut, LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, rsb_NewBirthCity, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, rsb_NewBirthCity, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  if ( s.IsEmpty() )
    s = m_BP_CITY;
  if ( fStrikeOut && s==m_BP_CITY )
    s = CString('-', 20);
  return s;
}

CString CRSBirthes::GetNewBirthDistrict(BOOL fStrikeOut, LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, rsb_NewBirthDistrict, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, rsb_NewBirthDistrict, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  if ( s.IsEmpty() )
    s = m_BP_DISTRICT;

  if ( fStrikeOut && s==m_BP_DISTRICT )
    s = CString('-', 20);
  return s;
}


BOOL CRSBirthes::IsFatherDeclarant() {
  return (m_DECLARANT_NAME.Find(m_FATHER_SURNAME)    >=0 &&
          m_DECLARANT_NAME.Find(m_FATHER_NAME)       >=0 &&
          m_DECLARANT_NAME.Find(m_FATHER_PATRONYMIC) >=0
         );
}
BOOL CRSBirthes::IsMotherDeclarant() {
  return (m_DECLARANT_NAME.Find(m_MOTHER_SURNAME)    >=0 &&
          m_DECLARANT_NAME.Find(m_MOTHER_NAME)       >=0 &&
          m_DECLARANT_NAME.Find(m_MOTHER_PATRONYMIC) >=0
         );
}


BOOL CRSBirthes::AreParentsDeclarants() {
 if ( m_DECLARANT_NAME.Find(m_FATHER_SURNAME)    >=0 &&
      m_DECLARANT_NAME.Find(m_FATHER_NAME)       >=0 &&
      m_DECLARANT_NAME.Find(m_FATHER_PATRONYMIC) >=0 
    )
 {
   if ( m_DECLARANT_ADDRESS.Find(m_MOTHER_SURNAME)    >=0 &&
        m_DECLARANT_ADDRESS.Find(m_MOTHER_NAME)       >=0 &&
        m_DECLARANT_ADDRESS.Find(m_MOTHER_PATRONYMIC) >=0
      )
   {
     return true;
   }
   if ( m_DECLARANT_NAME.Find(m_MOTHER_SURNAME)    >=0 &&
        m_DECLARANT_NAME.Find(m_MOTHER_NAME)       >=0 &&
        m_DECLARANT_NAME.Find(m_MOTHER_PATRONYMIC) >=0
      )
   {
     return true;
   }
 }
 return false;
}

void CRSBirthes::ParseDeclarantFIO(CString& szSurname, CString& szName, CString& szPatronymic, CString& szOrganization) {
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

void CRSBirthes::ParseDeclarantAddress(CString& szCountry, CString& szRegion, CString& szDistrict, CString& szCity,
                                       TCHAR& cStreetType, CString& szStreet, CString& szBuild, CString& szFlat)
{
  szCountry = _T("Україна");

  CStringArray tokens;

  FillTokenArray(m_DECLARANT_ADDRESS, tokens, ',');

  int nTokens = tokens.GetSize();

  if ( nTokens > 1 ) {
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
  else {
    int nFound = m_DECLARANT_ADDRESS.Find(_T("м."));
    if ( nFound >=0 ) {
      nFound += 2;
      szCity = GetTok(m_DECLARANT_ADDRESS.Mid(nFound), 0, _T(" "));
    }
    nFound = m_DECLARANT_ADDRESS.Find(_T("вул."));
    if ( nFound >=0 ) {
      nFound += 4;
      szStreet = GetTok(m_DECLARANT_ADDRESS.Mid(nFound), 0, _T(" "));
      cStreetType = '1'; // вулиця
    }
    nFound = m_DECLARANT_ADDRESS.Find(_T("пл."));
    if ( nFound >=0 ) {
      nFound += 3;
      szStreet = GetTok(m_DECLARANT_ADDRESS.Mid(nFound), 0, _T(" "));
      cStreetType = '2'; // площа
    }
    nFound = m_DECLARANT_ADDRESS.Find(_T("пр."));
    if ( nFound >=0 ) {
      nFound += 3;
      szStreet = GetTok(m_DECLARANT_ADDRESS.Mid(nFound), 0, _T(" "));
      cStreetType = '4'; // проспект
    }

    nFound = m_DECLARANT_ADDRESS.Find(_T("б."));
    if ( nFound >=0 ) {
      nFound += 2;
      szBuild = GetTok(m_DECLARANT_ADDRESS.Mid(nFound), 0, _T(" "));
    }
    nFound = m_DECLARANT_ADDRESS.Find(_T("кв."));
    if ( nFound >=0 ) {
      nFound += 3;
      szFlat = GetTok(m_DECLARANT_ADDRESS.Mid(nFound), 0, _T(" "));
    }
    nFound = m_DECLARANT_ADDRESS.Find(_T("кв-ра"));
    if ( nFound >=0 ) {
      nFound += 5;
      szFlat = GetTok(m_DECLARANT_ADDRESS.Mid(nFound), 0, _T(" "));
    }
  }

}
