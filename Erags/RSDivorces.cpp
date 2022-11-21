// RSDivorces.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "DataManager.h"

#include "RSDivorces.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "..\Common\DaoErr.h"

/////////////////////////////////////////////////////////////////////////////
// CRSDivorces

IMPLEMENT_DYNAMIC(CRSDivorces, CDaoRecordset)

CRSDivorces::CRSDivorces(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSDivorces)
	m_ID = 0;
	m_DATEREG = (DATE)0;
	m_NUMBER = 0;
	m_FLAGS = 0;
	m_MARRIAGE_BY = _T("");
	m_MARRIAGE_NUMBER = 0;
	m_MARRIAGE_DATE = (DATE)0;
	m_GROUND_TYPE = 0;
	m_GROUND = _T("");
  m_GROUND_NUMBER = _T("");
  m_GROUND_DATE = (DATE)0;
  m_NKIDS = 0;
	m_MMARRIAGE_NUMBER = 0;
	m_MOLD_SURNAME = _T("");
	m_MNEW_SURNAME = _T("");
	m_MNAME = _T("");
	m_MPATRONYMIC = _T("");
	m_MBIRTH_DATE = (DATE)0;
  m_MBIRTH_COUNTRY = _T("");
  m_MBIRTH_REGION = _T("");
  m_MBIRTH_DISTRICT = _T("");
  m_MBIRTH_CITY = _T("");
	m_MCITIZENSHIP = _T("");
	m_MRP_COUNTRY = _T("");
	m_MRP_REGION = _T("");
	m_MRP_DISTRICT = _T("");
	m_MRP_CITY = _T("");
	m_MRP_STREET = _T("");
	m_MRP_HOUSE = _T("");
	m_MRP_FLAT = _T("");
	m_MPASSPORT_TYPE = 0;
	m_MPASSPORT_SERIA = _T("");
	m_MPASSPORT_NUMBER = _T("");
	m_MPASSPORT_DATE = (DATE)0;
	m_MPASSPORT_BY = _T("");
  m_MDUTY = COleCurrency(0, 0);
  m_MDUTY2 = COleCurrency(0, 0);
	m_MMONEY_TYPE = 0;
	m_MCHECK_NUMBER = _T("");
	m_MCHECK_DATE = (DATE)0;
	m_MCHECK_BANK = _T("");
	m_MCERTIFICATE_SERIA = _T("");
	m_MCERTIFICATE_NUMBER = _T("");
	m_MNOTICE = _T("");
	m_WMARRIAGE_NUMBER = 0;
	m_WOLD_SURNAME = _T("");
	m_WNEW_SURNAME = _T("");
	m_WNAME = _T("");
	m_WPATRONYMIC = _T("");
	m_WBIRTH_DATE = (DATE)0;
  m_WBIRTH_COUNTRY = _T("");
  m_WBIRTH_REGION = _T("");
  m_WBIRTH_DISTRICT = _T("");
  m_WBIRTH_CITY = _T("");
	m_WCITIZENSHIP = _T("");
	m_WRP_COUNTRY = _T("");
	m_WRP_REGION = _T("");
	m_WRP_DISTRICT = _T("");
	m_WRP_CITY = _T("");
	m_WRP_STREET = _T("");
	m_WRP_HOUSE = _T("");
	m_WRP_FLAT = _T("");
	m_WPASSPORT_TYPE = 0;
	m_WPASSPORT_SERIA = _T("");
	m_WPASSPORT_NUMBER = _T("");
	m_WPASSPORT_DATE = (DATE)0;
	m_WPASSPORT_BY = _T("");
  m_WDUTY = COleCurrency(0, 0);
  m_WDUTY2 = COleCurrency(0, 0);
	m_WMONEY_TYPE = 0;
	m_WCHECK_NUMBER = _T("");
	m_WCHECK_DATE = (DATE)0;
	m_WCHECK_BANK = _T("");
	m_WCERTIFICATE_SERIA = _T("");
	m_WCERTIFICATE_NUMBER = _T("");
	m_WNOTICE = _T("");
  m_EXTNOTES = _T("");
	m_nFields = 77;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenTable;
}


CString CRSDivorces::GetDefaultDBName() {
	return theDataManager.m_strYearDBName;
}

CString CRSDivorces::GetDefaultSQL()
{
	return _T("[DIVORCES]");
}

void CRSDivorces::DoFieldExchange(CDaoFieldExchange* pFX) {
  try {
	//{{AFX_FIELD_MAP(CRSDivorces)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_ID);
	DFX_DateTime(pFX, _T("[DATEREG]"), m_DATEREG);
	DFX_Short(pFX, _T("[NUMBER]"), m_NUMBER);
	DFX_Long(pFX, _T("[FLAGS]"), m_FLAGS);
	DFX_Text(pFX, _T("[MARRIAGE_BY]"), m_MARRIAGE_BY);
	DFX_Short(pFX, _T("[MARRIAGE_NUMBER]"), m_MARRIAGE_NUMBER);
	DFX_DateTime(pFX, _T("[MARRIAGE_DATE]"), m_MARRIAGE_DATE);
	DFX_Byte(pFX, _T("[GROUND_TYPE]"), m_GROUND_TYPE);
	DFX_Text(pFX, _T("[GROUND]"), m_GROUND);
	DFX_Text(pFX, _T("[GROUND_NUMBER]"), m_GROUND_NUMBER);
	DFX_DateTime(pFX, _T("[GROUND_DATE]"), m_GROUND_DATE);
	DFX_Byte(pFX, _T("[NKIDS]"), m_NKIDS);
	DFX_Byte(pFX, _T("[MMARRIAGE_NUMBER]"), m_MMARRIAGE_NUMBER);
	DFX_Text(pFX, _T("[MOLD_SURNAME]"), m_MOLD_SURNAME);
	DFX_Text(pFX, _T("[MNEW_SURNAME]"), m_MNEW_SURNAME);
	DFX_Text(pFX, _T("[MNAME]"), m_MNAME);
	DFX_Text(pFX, _T("[MPATRONYMIC]"), m_MPATRONYMIC);
	DFX_DateTime(pFX, _T("[MBIRTH_DATE]"), m_MBIRTH_DATE);
  DFX_Text(pFX, _T("[MBIRTH_COUNTRY]"), m_MBIRTH_COUNTRY);
  DFX_Text(pFX, _T("[MBIRTH_REGION]"), m_MBIRTH_REGION);
  DFX_Text(pFX, _T("[MBIRTH_DISTRICT]"), m_MBIRTH_DISTRICT);
  DFX_Text(pFX, _T("[MBIRTH_CITY]"), m_MBIRTH_CITY);
	DFX_Text(pFX, _T("[MCITIZENSHIP]"), m_MCITIZENSHIP);
	DFX_Text(pFX, _T("[MRP_COUNTRY]"), m_MRP_COUNTRY);
	DFX_Text(pFX, _T("[MRP_REGION]"), m_MRP_REGION);
	DFX_Text(pFX, _T("[MRP_DISTRICT]"), m_MRP_DISTRICT);
	DFX_Text(pFX, _T("[MRP_CITY]"), m_MRP_CITY);
	DFX_Text(pFX, _T("[MRP_STREET]"), m_MRP_STREET);
	DFX_Text(pFX, _T("[MRP_HOUSE]"), m_MRP_HOUSE);
	DFX_Text(pFX, _T("[MRP_FLAT]"), m_MRP_FLAT);
	DFX_Byte(pFX, _T("[MPASSPORT_TYPE]"), m_MPASSPORT_TYPE);
	DFX_Text(pFX, _T("[MPASSPORT_SERIA]"), m_MPASSPORT_SERIA);
	DFX_Text(pFX, _T("[MPASSPORT_NUMBER]"), m_MPASSPORT_NUMBER);
	DFX_DateTime(pFX, _T("[MPASSPORT_DATE]"), m_MPASSPORT_DATE);
	DFX_Text(pFX, _T("[MPASSPORT_BY]"), m_MPASSPORT_BY);
	DFX_Currency(pFX, _T("[MDUTY]"), m_MDUTY);
	DFX_Currency(pFX, _T("[MDUTY2]"), m_MDUTY2);
	DFX_Byte(pFX, _T("[MMONEY_TYPE]"), m_MMONEY_TYPE);
	DFX_Text(pFX, _T("[MCHECK_NUMBER]"), m_MCHECK_NUMBER);
	DFX_DateTime(pFX, _T("[MCHECK_DATE]"), m_MCHECK_DATE);
	DFX_Text(pFX, _T("[MCHECK_BANK]"), m_MCHECK_BANK);
	DFX_Text(pFX, _T("[MCERTIFICATE_SERIA]"), m_MCERTIFICATE_SERIA);
	DFX_Text(pFX, _T("[MCERTIFICATE_NUMBER]"), m_MCERTIFICATE_NUMBER);
	DFX_Text(pFX, _T("[MNOTICE]"), m_MNOTICE);
	DFX_Byte(pFX, _T("[WMARRIAGE_NUMBER]"), m_WMARRIAGE_NUMBER);
	DFX_Text(pFX, _T("[WOLD_SURNAME]"), m_WOLD_SURNAME);
	DFX_Text(pFX, _T("[WNEW_SURNAME]"), m_WNEW_SURNAME);
	DFX_Text(pFX, _T("[WNAME]"), m_WNAME);
	DFX_Text(pFX, _T("[WPATRONYMIC]"), m_WPATRONYMIC);
	DFX_DateTime(pFX, _T("[WBIRTH_DATE]"), m_WBIRTH_DATE);
  DFX_Text(pFX, _T("[WBIRTH_COUNTRY]"), m_WBIRTH_COUNTRY);
  DFX_Text(pFX, _T("[WBIRTH_REGION]"), m_WBIRTH_REGION);
  DFX_Text(pFX, _T("[WBIRTH_DISTRICT]"), m_WBIRTH_DISTRICT);
  DFX_Text(pFX, _T("[WBIRTH_CITY]"), m_WBIRTH_CITY);
	DFX_Text(pFX, _T("[WCITIZENSHIP]"), m_WCITIZENSHIP);
	DFX_Text(pFX, _T("[WRP_COUNTRY]"), m_WRP_COUNTRY);
	DFX_Text(pFX, _T("[WRP_REGION]"), m_WRP_REGION);
	DFX_Text(pFX, _T("[WRP_DISTRICT]"), m_WRP_DISTRICT);
	DFX_Text(pFX, _T("[WRP_CITY]"), m_WRP_CITY);
	DFX_Text(pFX, _T("[WRP_STREET]"), m_WRP_STREET);
	DFX_Text(pFX, _T("[WRP_HOUSE]"), m_WRP_HOUSE);
	DFX_Text(pFX, _T("[WRP_FLAT]"), m_WRP_FLAT);
	DFX_Byte(pFX, _T("[WPASSPORT_TYPE]"), m_WPASSPORT_TYPE);
	DFX_Text(pFX, _T("[WPASSPORT_SERIA]"), m_WPASSPORT_SERIA);
	DFX_Text(pFX, _T("[WPASSPORT_NUMBER]"), m_WPASSPORT_NUMBER);
	DFX_DateTime(pFX, _T("[WPASSPORT_DATE]"), m_WPASSPORT_DATE);
	DFX_Text(pFX, _T("[WPASSPORT_BY]"), m_WPASSPORT_BY);
	DFX_Currency(pFX, _T("[WDUTY]"), m_WDUTY);
	DFX_Currency(pFX, _T("[WDUTY2]"), m_WDUTY2);
	DFX_Byte(pFX, _T("[WMONEY_TYPE]"), m_WMONEY_TYPE);
	DFX_Text(pFX, _T("[WCHECK_NUMBER]"), m_WCHECK_NUMBER);
	DFX_DateTime(pFX, _T("[WCHECK_DATE]"), m_WCHECK_DATE);
	DFX_Text(pFX, _T("[WCHECK_BANK]"), m_WCHECK_BANK);
	DFX_Text(pFX, _T("[WCERTIFICATE_SERIA]"), m_WCERTIFICATE_SERIA);
	DFX_Text(pFX, _T("[WCERTIFICATE_NUMBER]"), m_WCERTIFICATE_NUMBER);
	DFX_Text(pFX, _T("[WNOTICE]"), m_WNOTICE);
	DFX_Text(pFX, _T("[EXTNOTES]"), m_EXTNOTES);
	//}}AFX_FIELD_MAP
  }
  catch(CDaoException* e) {
    DaoError(e, NULL, pFX->m_prs, pFX->m_nField-1);
    e->Delete();
  }
}

/////////////////////////////////////////////////////////////////////////////
// CRSDivorces diagnostics

#ifdef _DEBUG
void CRSDivorces::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CRSDivorces::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
