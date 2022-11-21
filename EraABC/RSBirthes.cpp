// RSBirthes.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"

#include "RSBirthes.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSBirthes

IMPLEMENT_DYNAMIC(CRSBirthes, CDaoRecordset)

CRSBirthes::CRSBirthes(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSBirthes)
	m_ID = 0;
	m_SEX = FALSE;
	m_DATEREG = (DATE)0;
	m_NUMBER = 0;
	m_SURNAME = _T("");
	m_NAME = _T("");
	m_PATRONYMIC = _T("");
	m_ALIVE_FLAG = FALSE;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenTable;//dbOpenDynaset;
}


CString CRSBirthes::GetDefaultDBName() {
	return theApp.m_strYearDBName;
}

CString CRSBirthes::GetDefaultSQL() {
	return _T("[BIRTHES]");
}

void CRSBirthes::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSBirthes)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_ID);
	DFX_Bool(pFX, _T("[SEX]"), m_SEX);
	DFX_DateTime(pFX, _T("[DATEREG]"), m_DATEREG);
	DFX_Short(pFX, _T("[NUMBER]"), m_NUMBER);
	DFX_Text(pFX, _T("[SURNAME]"), m_SURNAME);
	DFX_Text(pFX, _T("[NAME]"), m_NAME);
	DFX_Text(pFX, _T("[PATRONYMIC]"), m_PATRONYMIC);
	DFX_Bool(pFX, _T("[ALIVE_FLAG]"), m_ALIVE_FLAG);
	//}}AFX_FIELD_MAP
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


