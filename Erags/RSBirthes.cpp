// RSBirthes.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"

#include "DataManager.h"
#include "DateFunc.h"
#include "Defaults.h"
#include "RSBirthes.h"

#include "..\Common\DaoErr.h"
#include "..\Common\CyrString.h"
#include "..\Common\MDB.h"
#include "..\Common\EraDate.h"

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


/////////////////////////////////////////////////////////////////////////////
// CRSBirthes

IMPLEMENT_DYNAMIC(CRSBirthes, CDaoRecordset)

CRSBirthes::CRSBirthes(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSBirthes)
	m_ID = 0;
	m_SEX = FALSE;
//	m_DATEREG = (DATE)0;
	m_NUMBER = 0;
	m_RENEW = 0;
	m_SURNAME = _T("");
	m_NAME = _T("");
	m_PATRONYMIC = _T("");
//	m_BIRTH_DATE = (DATE)0;
	m_BP_FLAG = FALSE;
	m_BP_COUNTRY = _T("");
	m_BP_REGION = _T("");
	m_BP_CITY = _T("");
	m_BP_DISTRICT = _T("");
	m_NKIDS = 0;
	m_BYCOUNT = 0;
	m_ALIVE_FLAG = FALSE;
	m_SOURCE_TYPE = 0;
  m_SOURCE_NDOC = _T("");
//  m_SOURCE_DATE = (DATE)0;
  m_SOURCE_BY = _T("");
	m_MEDICAL_CERTIFICATE_NUMBER = _T("");
//	m_MEDICAL_CERTIFICATE_DATE = (DATE)0;
	m_MEDICAL_CERTIFICATE_BY = _T("");
	m_FATHER_SURNAME = _T("");
	m_FATHER_NAME = _T("");
	m_FATHER_PATRONYMIC = _T("");
	m_FATHER_DOB_FLAG = FALSE;
//	m_FATHER_BIRTH_DATE = (DATE)0;
	m_FATHER_CITIZENSHIP = _T("");
	m_FATHER_COUNTRY = _T("");
	m_FATHER_REGION = _T("");
	m_FATHER_CITY = _T("");
	m_FATHER_DISTRICT = _T("");
	m_FATHER_STREET = _T("");
	m_FATHER_HOUSE = _T("");
	m_FATHER_FLAT = _T("");
	m_MOTHER_SURNAME = _T("");
	m_MOTHER_NAME = _T("");
	m_MOTHER_PATRONYMIC = _T("");
	m_MOTHER_DOB_FLAG = FALSE;
//	m_MOTHER_BIRTH_DATE = (DATE)0;
	m_MOTHER_CITIZENSHIP = _T("");
	m_MOTHER_COUNTRY = _T("");
	m_MOTHER_REGION = _T("");
	m_MOTHER_CITY = _T("");
	m_MOTHER_DISTRICT = _T("");
	m_MOTHER_STREET = _T("");
	m_MOTHER_HOUSE = _T("");
	m_MOTHER_FLAT = _T("");
  m_DECLARANT_TYPE = 0;
	m_DECLARANT_NAME = _T("");
	m_DECLARANT_ADDRESS = _T("");
	m_DECLARANT_PASSPORT_TYPE = 0;
	m_DECLARANT_PASSPORT_SERIA = _T("");
	m_DECLARANT_PASSPORT_NUMBER = _T("");
//	m_DECLARANT_PASSPORT_DATE = (DATE)0;
	m_DECLARANT_PASSPORT_BY = _T("");
	m_CERTIFICATE_SERIA = _T("");
	m_CERTIFICATE_NUMBER = _T("");
	m_NOTICE = _T("");
  m_EXTNOTES = _T("");
	m_nFields = 62;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenTable;//dbOpenDynaset;
}


CString CRSBirthes::GetDefaultDBName() {
	return theDataManager.m_strYearDBName;
}

CString CRSBirthes::GetDefaultSQL() {
	return _T("[BIRTHES]");
}

void CRSBirthes::DoFieldExchange(CDaoFieldExchange* pFX) {
  try {
	//{{AFX_FIELD_MAP(CRSBirthes)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_ID);
	DFX_Bool(pFX, _T("[SEX]"), m_SEX);
	DFX_DateTime(pFX, _T("[DATEREG]"), m_DATEREG);
	DFX_Short(pFX, _T("[NUMBER]"), m_NUMBER);
	DFX_Long(pFX, _T("[RENEW]"), m_RENEW);
	DFX_Text(pFX, _T("[SURNAME]"), m_SURNAME);
	DFX_Text(pFX, _T("[NAME]"), m_NAME);
	DFX_Text(pFX, _T("[PATRONYMIC]"), m_PATRONYMIC);
	DFX_DateTime(pFX, _T("[BIRTH_DATE]"), m_BIRTH_DATE);
	DFX_Bool(pFX, _T("[BP_FLAG]"), m_BP_FLAG);
	DFX_Text(pFX, _T("[BP_COUNTRY]"), m_BP_COUNTRY);
	DFX_Text(pFX, _T("[BP_REGION]"), m_BP_REGION);
	DFX_Text(pFX, _T("[BP_CITY]"), m_BP_CITY);
	DFX_Text(pFX, _T("[BP_DISTRICT]"), m_BP_DISTRICT);
	DFX_Byte(pFX, _T("[NKIDS]"), m_NKIDS);
	DFX_Byte(pFX, _T("[BYCOUNT]"), m_BYCOUNT);
	DFX_Bool(pFX, _T("[ALIVE_FLAG]"), m_ALIVE_FLAG);
	DFX_Text(pFX, _T("[MEDICAL_CERTIFICATE_NUMBER]"), m_MEDICAL_CERTIFICATE_NUMBER);
	DFX_DateTime(pFX, _T("[MEDICAL_CERTIFICATE_DATE]"), m_MEDICAL_CERTIFICATE_DATE);
	DFX_Text(pFX, _T("[MEDICAL_CERTIFICATE_BY]"), m_MEDICAL_CERTIFICATE_BY);
	DFX_Byte(pFX, _T("[SOURCE_TYPE]"), m_SOURCE_TYPE);
  DFX_Text(pFX, _T("[SOURCE_NDOC]"), m_SOURCE_NDOC);
	DFX_DateTime(pFX, _T("[SOURCE_DATE]"), m_SOURCE_DATE);
	DFX_Text(pFX, _T("[SOURCE_BY]"), m_SOURCE_BY);
	DFX_Text(pFX, _T("[FATHER_SURNAME]"), m_FATHER_SURNAME);
	DFX_Text(pFX, _T("[FATHER_NAME]"), m_FATHER_NAME);
	DFX_Text(pFX, _T("[FATHER_PATRONYMIC]"), m_FATHER_PATRONYMIC);
	DFX_Bool(pFX, _T("[FATHER_DOB_FLAG]"), m_FATHER_DOB_FLAG);
	DFX_DateTime(pFX, _T("[FATHER_BIRTH_DATE]"), m_FATHER_BIRTH_DATE);
	DFX_Text(pFX, _T("[FATHER_CITIZENSHIP]"), m_FATHER_CITIZENSHIP);
	DFX_Text(pFX, _T("[FATHER_COUNTRY]"), m_FATHER_COUNTRY);
	DFX_Text(pFX, _T("[FATHER_REGION]"), m_FATHER_REGION);
	DFX_Text(pFX, _T("[FATHER_CITY]"), m_FATHER_CITY);
	DFX_Text(pFX, _T("[FATHER_DISTRICT]"), m_FATHER_DISTRICT);
	DFX_Text(pFX, _T("[FATHER_STREET]"), m_FATHER_STREET);
	DFX_Text(pFX, _T("[FATHER_HOUSE]"), m_FATHER_HOUSE);
	DFX_Text(pFX, _T("[FATHER_FLAT]"), m_FATHER_FLAT);
	DFX_Text(pFX, _T("[MOTHER_SURNAME]"), m_MOTHER_SURNAME);
	DFX_Text(pFX, _T("[MOTHER_NAME]"), m_MOTHER_NAME);
	DFX_Text(pFX, _T("[MOTHER_PATRONYMIC]"), m_MOTHER_PATRONYMIC);
	DFX_Bool(pFX, _T("[MOTHER_DOB_FLAG]"), m_MOTHER_DOB_FLAG);
	DFX_DateTime(pFX, _T("[MOTHER_BIRTH_DATE]"), m_MOTHER_BIRTH_DATE);
	DFX_Text(pFX, _T("[MOTHER_CITIZENSHIP]"), m_MOTHER_CITIZENSHIP);
	DFX_Text(pFX, _T("[MOTHER_COUNTRY]"), m_MOTHER_COUNTRY);
	DFX_Text(pFX, _T("[MOTHER_REGION]"), m_MOTHER_REGION);
	DFX_Text(pFX, _T("[MOTHER_CITY]"), m_MOTHER_CITY);
	DFX_Text(pFX, _T("[MOTHER_DISTRICT]"), m_MOTHER_DISTRICT);
	DFX_Text(pFX, _T("[MOTHER_STREET]"), m_MOTHER_STREET);
	DFX_Text(pFX, _T("[MOTHER_HOUSE]"), m_MOTHER_HOUSE);
	DFX_Text(pFX, _T("[MOTHER_FLAT]"), m_MOTHER_FLAT);
	DFX_Byte(pFX, _T("[DECLARANT_TYPE]"), m_DECLARANT_TYPE);
	DFX_Text(pFX, _T("[DECLARANT_NAME]"), m_DECLARANT_NAME);
	DFX_Text(pFX, _T("[DECLARANT_ADDRESS]"), m_DECLARANT_ADDRESS);
	DFX_Byte(pFX, _T("[DECLARANT_PASSPORT_TYPE]"), m_DECLARANT_PASSPORT_TYPE);
	DFX_Text(pFX, _T("[DECLARANT_PASSPORT_SERIA]"), m_DECLARANT_PASSPORT_SERIA);
	DFX_Text(pFX, _T("[DECLARANT_PASSPORT_NUMBER]"), m_DECLARANT_PASSPORT_NUMBER);
	DFX_DateTime(pFX, _T("[DECLARANT_PASSPORT_DATE]"), m_DECLARANT_PASSPORT_DATE);
	DFX_Text(pFX, _T("[DECLARANT_PASSPORT_BY]"), m_DECLARANT_PASSPORT_BY);
	DFX_Text(pFX, _T("[CERTIFICATE_SERIA]"), m_CERTIFICATE_SERIA);
	DFX_Text(pFX, _T("[CERTIFICATE_NUMBER]"), m_CERTIFICATE_NUMBER);
	DFX_Text(pFX, _T("[NOTICE]"), m_NOTICE);
	DFX_Text(pFX, _T("[EXTNOTES]"), m_EXTNOTES);
	//}}AFX_FIELD_MAP
  }
  catch(CDaoException* e) {
    DaoError(e, NULL, pFX->m_prs, pFX->m_nField-1);
    e->Delete();
  }
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

void CRSBirthes::SetNewSurname(LPCTSTR szNewSurname, CString& szMemo) {
  MakeBracketString(szMemo, rsb_NewSurname, szNewSurname);
}
void CRSBirthes::SetNewName(LPCTSTR szNewName, CString& szMemo) {
  MakeBracketString(szMemo, rsb_NewName, szNewName);
}
void CRSBirthes::SetNewPatronymic(LPCTSTR szNewPatronymic, CString& szMemo) {
  MakeBracketString(szMemo, rsb_NewPatronymic, szNewPatronymic);
}

CString CRSBirthes::SetNewSNP(CString& sMemo,
                              const CString& sNewS,
                              const CString& sNewN,
                              const CString& sNewP,
                              const CString& sNewMotherSurname,
                              const CString& sFatherDate,
                              const CString& sMotherDate,
                              const CString& sGrg10) {
  // At firts remove military card data
/************************************** : by VK at 22.01.2004 3:58:00 **\
  CString s = GetSentence(sMemo, rsb_NewSurname, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, rsb_NewSurname, false);

  s = GetSentence(sMemo, rsb_NewName, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, rsb_NewName, false);

  s = GetSentence(sMemo, rsb_NewPatronymic, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, rsb_NewPatronymic, false);

  s = GetSentence(sMemo, rsb_NewMotherSurname, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, rsb_NewMotherSurname, false);

  s = GetSentence(sMemo, rsb_FatherDate, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, rsb_FatherDate, false);

  s = GetSentence(sMemo, rsb_MotherDate, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, rsb_MotherDate, false);
\************************************** : by VK at 22.01.2004 3:58:04 **/
  sMemo = Trim(sMemo);

  SetNewSurname(sNewS, sMemo);
  SetNewName(sNewN, sMemo);
  SetNewPatronymic(sNewP, sMemo);
  MakeBracketString(sMemo, rsb_NewMotherSurname,  sNewMotherSurname);
  MakeBracketString(sMemo, rsb_NewMotherSurname,  sNewMotherSurname);
  MakeBracketString(sMemo, rsb_FatherDate,        sFatherDate);
  MakeBracketString(sMemo, rsb_MotherDate,        sMotherDate);
  MakeBracketString(sMemo, rsb_Gr10,              sGrg10);

  return sMemo;
}

CString CRSBirthes::GetSvNeVidano() {
  CString s;
  if ( m_NOTICE.Find(g_szSvNeVidano)>=0 ) {
    s = theIniCache.GetNoCert();
  }
  return s;
}

CString CRSBirthes::GetNotices() {
  CString s, sMem;
  sMem = m_NOTICE;
  s = GetSvNeVidano();
  if ( !s.IsEmpty() ) {
    sMem = FindAndReplace(sMem, s, _T(""), true);
  }
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
COleDateTime CRSBirthes::GetPassport2ODT(LPCTSTR szMemo/*=NULL*/) {
  CString s = GetPassport2Date(szMemo);
  return ParseDate(s);
}


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
void CRSBirthes::SetVerdictOf(LPCTSTR szVerdictOf, CString& szMemo) {
  MakeBracketString(szMemo, rsb_VerdictBy, szVerdictOf);
}

COleDateTime CRSBirthes::GetVerdictDate(LPCTSTR szMemo/*=NULL*/) {
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
void CRSBirthes::SetVerdictDate(COleDateTime dtVerdictDate, CString& szMemo) {
  CString szVerdictDate = GetDateDDMMYYYY(dtVerdictDate);
  MakeBracketString(szMemo, rsb_VerdictDate, szVerdictDate);
}
CString CRSBirthes::GetVerdictNumber(LPCTSTR szMemo/*=NULL*/) {
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, rsb_VerdictNumber, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, rsb_VerdictNumber, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  return s;
}
void CRSBirthes::SetVerdictNumber(LPCTSTR szVerdictNumber, CString& szMemo) {
  MakeBracketString(szMemo, rsb_VerdictNumber, szVerdictNumber);
}
COleDateTime CRSBirthes::GetNewBirthDate(LPCTSTR szMemo/*=NULL*/) {
  COleDateTime ed;
  CString sMemo = (NULL==szMemo) ? m_EXTNOTES : szMemo;
  CString s = GetSentence(sMemo, rsb_NewBirthDate, _T("}") );
  if ( !s.IsEmpty() ) {
    s = FindAndReplace(s, rsb_NewBirthDate, g_szEmpty, true);
    s = Trim(FindAndReplace(s, _T("}"), g_szEmpty, true));
  }
  if ( s.IsEmpty() )
    ed = m_BIRTH_DATE;
  else
    ed.ParseDateTime(s);
  if ( COleDateTime::valid != ed.GetStatus() )
    ed.SetStatus( COleDateTime::null );
  return ed;
}
CString CRSBirthes::GetNewBirthDate(BOOL fStrikeOut) {
  COleDateTime odt = GetNewBirthDate();
  if ( odt==m_BIRTH_DATE ) {
    return fStrikeOut ? CString('-', 20) : GetDateDDMMYYYYr(odt);
  }
  return GetDateDDMMYYYYr(odt);
}
void CRSBirthes::SetNewBirthDate(COleDateTime dtNewBirthDate, CString& szMemo) {
  CString szDate = GetDateDDMMYYYY(dtNewBirthDate);
  MakeBracketString(szMemo, rsb_NewBirthDate, szDate);
}

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
void CRSBirthes::SetNewBirthCountry(LPCTSTR szNewCountry, CString& szMemo) {
  MakeBracketString(szMemo, rsb_NewBirthCountry, szNewCountry);
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
void CRSBirthes::SetNewBirthRegion(LPCTSTR szNewRegion, CString& szMemo) {
  MakeBracketString(szMemo, rsb_NewBirthRegion, szNewRegion);
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
void CRSBirthes::SetNewBirthCity(LPCTSTR szNewCity, CString& szMemo) {
  MakeBracketString(szMemo, rsb_NewBirthCity, szNewCity);
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
void CRSBirthes::SetNewBirthDistrict(LPCTSTR szNewDistrict, CString& szMemo) {
  MakeBracketString(szMemo, rsb_NewBirthDistrict, szNewDistrict);
}


CString CRSBirthes::SetPassport2(CString& sMemo, int nType, const CString& sSeria, const CString& sNumber, const COleDateTime& odt, const CString& sBy) {
  // At firts remove military card data

  CString s = GetSentence(sMemo, g_szP2Type, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, g_szEmpty, false);

  s = GetSentence(sMemo, g_szP2Seria, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, g_szEmpty, false);

  s = GetSentence(sMemo, g_szP2Number, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, g_szEmpty, false);

  s = GetSentence(sMemo, g_szP2Date, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, g_szEmpty, false);

  s = GetSentence(sMemo, g_szP2By, _T("}") );
  if ( !s.IsEmpty() ) 
    sMemo = FindAndReplace(sMemo, s, g_szEmpty, false);

  sMemo = Trim(sMemo);

  if ( FALSE==sSeria.IsEmpty() && FALSE==sNumber.IsEmpty() && COleDateTime::valid==odt.GetStatus() ) {
    s.Format(_T("%s %d%c %s %s%c %s %s%c %s %02d.%02d.%04d%c %s %s%c"),
              g_szP2Type, nType, C_BRACKET,
              g_szP2Seria, sSeria, C_BRACKET,
              g_szP2Number, sNumber, C_BRACKET,
              g_szP2Date, odt.GetDay(), odt.GetMonth(), odt.GetYear(), C_BRACKET,
              g_szP2By, sBy, C_BRACKET);
    sMemo += ' ';
    sMemo += s;
    sMemo = Trim(sMemo);
  }

  return sMemo;
}
