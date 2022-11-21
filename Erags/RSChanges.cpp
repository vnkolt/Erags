// RSChanges.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "DataManager.h"
#include "RSChanges.h"

#include "..\Common\DaoErr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern LPCTSTR g_szBirthDate;

/////////////////////////////////////////////////////////////////////////////
// CRSChanges
CString CRSChanges::GetTypeName(BYTE bType) {
  CString s;
  switch(bType){
    case BYTE('Н'): case BYTE('н'):
      s = _T("народження");
      break;
    case BYTE('В'): case BYTE('в'):
      s = _T("встановлення батьківства");
      break;
    case BYTE('Ш'): case BYTE('ш'):
      s = _T("шлюб");
      break;
    case BYTE('Р'): case BYTE('р'):
      s = _T("розірвання шлюбу");
      break;
    case BYTE('З'): case BYTE('з'):
      s = _T("зміну імені");
      break;
    case BYTE('П'): case BYTE('п'):
      s = _T("переміну прізвища, імені, по батькові");
      break;
  }
  return s;
}

IMPLEMENT_DYNAMIC(CRSChanges, CDaoRecordset)

CRSChanges::CRSChanges(CDaoDatabase* pdb)
        	 :CDaoRecordset(pdb) {
	//{{AFX_FIELD_INIT(CRSChanges)
	m_ID = 0;
	m_NUMBER = 0;
	m_DATEREG = (DATE)0;
	m_FLAGS = 0;
	m_SEX = FALSE;
	m_OLDSURNAME = _T("");
	m_NEWSURNAME = _T("");
	m_OLDNAME = _T("");
	m_NEWNAME = _T("");
	m_OLDPATRONYMIC = _T("");
	m_NEWPATRONYMIC = _T("");
	m_BIRTH_DATE = (DATE)0;
	m_BIRTH_COUNTRY = _T("");
	m_BIRTH_REGION = _T("");
	m_BIRTH_DISTRICT = _T("");
	m_BIRTH_CITY = _T("");
	m_BIRTHACT_NUMBER = 0;
	m_BIRTHACT_DATE = (DATE)0;
	m_BIRTHACT_BY = _T("");
	m_CITIZENSHIP = _T("");
	m_COUNTRY = _T("");
	m_REGION = _T("");
	m_DISTRICT = _T("");
	m_CITY = _T("");
	m_STREET = _T("");
	m_HOUSE = _T("");
	m_FLAT = _T("");
  m_DUTY = COleCurrency(0, 0);
	m_CHECKNUM = _T("");
	m_CHECKDATE = (DATE)0;
	m_CHECKBANK = _T("");
 	m_PASSPORT_TYPE = 0;
	m_PASSPORT_SERIA = _T("");
	m_PASSPORT_NUMBER = _T("");
	m_PASSPORT_DATE = (DATE)0;
	m_PASSPORT_BY = _T("");
	m_CERTIFICATE_SERIA = _T("");
	m_CERTIFICATE_NUMBER = _T("");
	m_NOTICE = _T("");
  m_EXTNOTES = _T("");
	m_nFields = 40;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenTable;
}


CString CRSChanges::GetDefaultDBName() {
	return theDataManager.m_strYearDBName;
}

CString CRSChanges::GetDefaultSQL() {
	return _T("[CHANGES]");
}

void CRSChanges::DoFieldExchange(CDaoFieldExchange* pFX) {
  try {
	//{{AFX_FIELD_MAP(CRSChanges)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_ID);
	DFX_Short(pFX, _T("[NUMBER]"), m_NUMBER);
	DFX_DateTime(pFX, _T("[DATEREG]"), m_DATEREG);
	DFX_Long(pFX, _T("[FLAGS]"), m_FLAGS);
	DFX_Bool(pFX, _T("[SEX]"), m_SEX);
	DFX_Text(pFX, _T("[OLDSURNAME]"), m_OLDSURNAME);
	DFX_Text(pFX, _T("[NEWSURNAME]"), m_NEWSURNAME);
	DFX_Text(pFX, _T("[OLDNAME]"), m_OLDNAME);
	DFX_Text(pFX, _T("[NEWNAME]"), m_NEWNAME);
	DFX_Text(pFX, _T("[OLDPATRONYMIC]"), m_OLDPATRONYMIC);
	DFX_Text(pFX, _T("[NEWPATRONYMIC]"), m_NEWPATRONYMIC);
	DFX_DateTime(pFX, _T("[BIRTH_DATE]"), m_BIRTH_DATE);
	DFX_Text(pFX, _T("[BIRTH_COUNTRY]"), m_BIRTH_COUNTRY);
	DFX_Text(pFX, _T("[BIRTH_REGION]"), m_BIRTH_REGION);
	DFX_Text(pFX, _T("[BIRTH_DISTRICT]"), m_BIRTH_DISTRICT);
	DFX_Text(pFX, _T("[BIRTH_CITY]"), m_BIRTH_CITY);
	DFX_Short(pFX, _T("[BIRTHACT_NUMBER]"), m_BIRTHACT_NUMBER);
	DFX_DateTime(pFX, _T("[BIRTHACT_DATE]"), m_BIRTHACT_DATE);
	DFX_Text(pFX, _T("[BIRTHACT_BY]"), m_BIRTHACT_BY);
	DFX_Text(pFX, _T("[CITIZENSHIP]"), m_CITIZENSHIP);
	DFX_Text(pFX, _T("[COUNTRY]"), m_COUNTRY);
	DFX_Text(pFX, _T("[REGION]"), m_REGION);
	DFX_Text(pFX, _T("[DISTRICT]"), m_DISTRICT);
	DFX_Text(pFX, _T("[CITY]"), m_CITY);
	DFX_Text(pFX, _T("[STREET]"), m_STREET);
	DFX_Text(pFX, _T("[HOUSE]"), m_HOUSE);
	DFX_Text(pFX, _T("[FLAT]"), m_FLAT);
  DFX_Currency(pFX, _T("[DUTY]"), m_DUTY);
	DFX_Text(pFX, _T("[CHECKNUM]"), m_CHECKNUM);
	DFX_DateTime(pFX, _T("[CHECKDATE]"), m_CHECKDATE);
	DFX_Text(pFX, _T("[CHECKBANK]"), m_CHECKBANK);
	DFX_Byte(pFX, _T("[PASSPORT_TYPE]"), m_PASSPORT_TYPE);
	DFX_Text(pFX, _T("[PASSPORT_SERIA]"), m_PASSPORT_SERIA);
	DFX_Text(pFX, _T("[PASSPORT_NUMBER]"), m_PASSPORT_NUMBER);
	DFX_DateTime(pFX, _T("[PASSPORT_DATE]"), m_PASSPORT_DATE);
	DFX_Text(pFX, _T("[PASSPORT_BY]"), m_PASSPORT_BY);
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

bool CRSChanges::IsNoticeBirthDate() {
  return m_NOTICE.Find(g_szBirthDate, 0)==-1 ? false : true;
}
CString CRSChanges::GetNoticeBirthDateDDMMMYYYY() {
  CString s = GetSentence(m_NOTICE, g_szBirthDate );
  s = FindAndReplace(s, g_szBirthDate, _T(""), true);
  s = FindAndReplace(s, _T("р."), _T(""), true);
  s = FindAndReplace(s, _T("року"), _T(""), true);
  return Trim(s);
}

CString CRSChanges::GetNotices() {
  CString s, sMemo;
  sMemo = m_NOTICE;
  s = GetSentence(sMemo, g_szBirthDate );
  if ( !s.IsEmpty() )
    sMemo = FindAndReplace(sMemo, s, _T(""), true);
  return sMemo;
}

LPCTSTR CRSChanges::GetNewSurnameOrLine() {
  if ( m_NEWSURNAME.IsEmpty()==FALSE && m_OLDSURNAME != m_NEWSURNAME )
    return m_NEWSURNAME;
  return _T("----------"); 
}
CString CRSChanges::GetNewOrOldSurname() {
  if ( m_NEWSURNAME.IsEmpty()==FALSE && m_OLDSURNAME != m_NEWSURNAME )
    return m_NEWSURNAME;
  return m_OLDSURNAME;
}

LPCTSTR CRSChanges::GetNewNameOrLine() {
  if ( m_NEWNAME.IsEmpty()==FALSE && m_OLDNAME != m_NEWNAME )
    return m_NEWNAME;
  return _T("----------"); 
}
CString CRSChanges::GetNewOrOldName() {
  if ( m_NEWNAME.IsEmpty()==FALSE && m_OLDNAME != m_NEWNAME )
    return m_NEWNAME;
  return m_OLDNAME;
}
LPCTSTR CRSChanges::GetNewPatronymicOrLine() {
  if ( m_NEWPATRONYMIC.IsEmpty()==FALSE && m_OLDPATRONYMIC != m_NEWPATRONYMIC )
    return m_NEWPATRONYMIC;
  return _T("----------"); 
}
CString CRSChanges::GetNewOrOldPatronymic() {
  if ( m_NEWPATRONYMIC.IsEmpty()==FALSE && m_OLDPATRONYMIC != m_NEWPATRONYMIC )
    return m_NEWPATRONYMIC;
  return m_OLDPATRONYMIC; 
}

void CRSChanges::Delete() {
  long ID = m_ID;
  CString sql;
  try {
    CDaoRecordset::Delete();
    sql.Format(_T("DELETE FROM CHANGESDEP WHERE ID=%ld"), ID);
    m_pDatabase->Execute(sql);
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
}

/////////////////////////////////////////////////////////////////////////////
// CRSChanges diagnostics

#ifdef _DEBUG
void CRSChanges::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CRSChanges::Dump(CDumpContext& dc) const {
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
