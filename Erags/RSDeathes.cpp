// RSDeathes.cpp : implementation file
//
#include "stdafx.h"
#include "erags.h"

#include "DataManager.h"
#include "DateFunc.h"
#include "Defaults.h"
#include "RSDeathes.h"

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

/////////////////////////////////////////////////////////////////////////////
// CRSDeathes

IMPLEMENT_DYNAMIC(CRSDeathes, CDaoRecordset)

CRSDeathes::CRSDeathes(CDaoDatabase* pdb)
           :CDaoRecordset(pdb) {
	//{{AFX_FIELD_INIT(CRSDeathes)
	m_ID = 0;
	m_SEX = FALSE;
	m_DATEREG = (DATE)0;
	m_NUMBER = 0;
	m_FLAGS = 0;
	m_RENEW = FALSE;
	m_SURNAME = _T("");
	m_NAME = _T("");
	m_PATRONYMIC = _T("");
	m_CITIZENSHIP = _T("");
	m_NATIONALITY = _T("");
	m_DOD_FLAG = FALSE;
	m_DEATH_DATE = (DATE)0;
	m_DP_COUNTRY = _T("");
	m_DP_REGION = _T("");
	m_DP_DISTRICT = _T("");
	m_DP_CITY = _T("");
	m_CAUSE_OF_DEATH = _T("");
	m_DOB_FLAG = FALSE;
	m_BIRTH_DATE = (DATE)0;
	m_BP_COUNTRY = _T("");
	m_BP_REGION = _T("");
	m_BP_DISTRICT = _T("");
	m_BP_CITY = _T("");
	m_RP_ZIPCODE = _T("");
	m_RP_COUNTRY = _T("");
	m_RP_REGION = _T("");
	m_RP_DISTRICT = _T("");
	m_RP_CITY = _T("");
	m_RP_STREET = _T("");
	m_RP_HOUSE = _T("");
	m_RP_FLAT = _T("");
	m_PASSPORT_TYPE = 0;
	m_PASSPORT_SERIA = _T("");
	m_PASSPORT_NUMBER = _T("");
	m_PASSPORT_DATE = (DATE)0;
	m_PASSPORT_BY = _T("");
	m_TAX_CODE = _T("");
	m_MEDICAL_CERT_TYPE = _T("");
	m_MEDICAL_CERT_NUMBER = _T("");
	m_MEDICAL_CERT_BY = _T("");
	m_MEDICAL_CERT_DATE = (DATE)0;
	m_DECLARANT_NAME = _T("");
	m_DECLARANT_ADDRESS = _T("");
	m_DECLARANT_PASSPORT_TYPE = 0;
	m_DECLARANT_PASSPORT_SERIA = _T("");
	m_DECLARANT_PASSPORT_NUMBER = _T("");
	m_DECLARANT_PASSPORT_DATE = (DATE)0;
	m_DECLARANT_PASSPORT_BY = _T("");
	m_CERTIFICATE_SERIA = _T("");
	m_CERTIFICATE_NUMBER = _T("");
	m_NOTICE = _T("");
	m_EXTNOTES = _T("");
	m_nFields = 53;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenTable;
}


CRSDeathes::~CRSDeathes() {
}

CString CRSDeathes::GetDefaultDBName() {
	return theDataManager.m_strYearDBName;
}

CString CRSDeathes::GetDefaultSQL() {
  return _T("[DEATHES]");
}

void CRSDeathes::DoFieldExchange(CDaoFieldExchange* pFX)
{
  try {
	//{{AFX_FIELD_MAP(CRSDeathes)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_ID);
	DFX_Bool(pFX, _T("[SEX]"), m_SEX);
	DFX_DateTime(pFX, _T("[DATEREG]"), m_DATEREG);
	DFX_Short(pFX, _T("[NUMBER]"), m_NUMBER);
	DFX_Long(pFX, _T("[FLAGS]"), m_FLAGS);
	DFX_Bool(pFX, _T("[RENEW]"), m_RENEW);
	DFX_Text(pFX, _T("[SURNAME]"), m_SURNAME);
	DFX_Text(pFX, _T("[NAME]"), m_NAME);
	DFX_Text(pFX, _T("[PATRONYMIC]"), m_PATRONYMIC);
	DFX_Text(pFX, _T("[CITIZENSHIP]"), m_CITIZENSHIP);
	DFX_Text(pFX, _T("[NATIONALITY]"), m_NATIONALITY);
	DFX_Bool(pFX, _T("[DOD_FLAG]"), m_DOD_FLAG);
	DFX_DateTime(pFX, _T("[DEATH_DATE]"), m_DEATH_DATE);
	DFX_Text(pFX, _T("[DP_COUNTRY]"), m_DP_COUNTRY);
	DFX_Text(pFX, _T("[DP_REGION]"), m_DP_REGION);
	DFX_Text(pFX, _T("[DP_DISTRICT]"), m_DP_DISTRICT);
	DFX_Text(pFX, _T("[DP_CITY]"), m_DP_CITY);
	DFX_Text(pFX, _T("[CAUSE_OF_DEATH]"), m_CAUSE_OF_DEATH);
	DFX_Bool(pFX, _T("[DOB_FLAG]"), m_DOB_FLAG);
	DFX_DateTime(pFX, _T("[BIRTH_DATE]"), m_BIRTH_DATE);
	DFX_Text(pFX, _T("[BP_COUNTRY]"), m_BP_COUNTRY);
	DFX_Text(pFX, _T("[BP_REGION]"), m_BP_REGION);
	DFX_Text(pFX, _T("[BP_DISTRICT]"), m_BP_DISTRICT);
	DFX_Text(pFX, _T("[BP_CITY]"), m_BP_CITY);
	DFX_Text(pFX, _T("[RP_ZIPCODE]"), m_RP_ZIPCODE);
	DFX_Text(pFX, _T("[RP_COUNTRY]"), m_RP_COUNTRY);
	DFX_Text(pFX, _T("[RP_REGION]"), m_RP_REGION);
	DFX_Text(pFX, _T("[RP_DISTRICT]"), m_RP_DISTRICT);
	DFX_Text(pFX, _T("[RP_CITY]"), m_RP_CITY);
	DFX_Text(pFX, _T("[RP_STREET]"), m_RP_STREET);
	DFX_Text(pFX, _T("[RP_HOUSE]"), m_RP_HOUSE);
	DFX_Text(pFX, _T("[RP_FLAT]"), m_RP_FLAT);
	DFX_Byte(pFX, _T("[PASSPORT_TYPE]"), m_PASSPORT_TYPE);
	DFX_Text(pFX, _T("[PASSPORT_SERIA]"), m_PASSPORT_SERIA);
	DFX_Text(pFX, _T("[PASSPORT_NUMBER]"), m_PASSPORT_NUMBER);
	DFX_DateTime(pFX, _T("[PASSPORT_DATE]"), m_PASSPORT_DATE);
	DFX_Text(pFX, _T("[PASSPORT_BY]"), m_PASSPORT_BY);
	DFX_Text(pFX, _T("[TAX_CODE]"), m_TAX_CODE);
	DFX_Text(pFX, _T("[MEDICAL_CERT_TYPE]"), m_MEDICAL_CERT_TYPE);
	DFX_Text(pFX, _T("[MEDICAL_CERT_NUMBER]"), m_MEDICAL_CERT_NUMBER);
	DFX_Text(pFX, _T("[MEDICAL_CERT_BY]"), m_MEDICAL_CERT_BY);
	DFX_DateTime(pFX, _T("[MEDICAL_CERT_DATE]"), m_MEDICAL_CERT_DATE);
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
  if ( m_NOTICE.Find(g_szSvNeVidano)>=0 ) {
    s = theIniCache.GetNoCert();
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
