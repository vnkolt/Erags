// RSDeathes.cpp : implementation file
//
#include "stdafx.h"
#include "EraABC.h"

#include "RSDeathes.h"
#include "..\Common\DaoErr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	m_SURNAME = _T("");
	m_NAME = _T("");
	m_PATRONYMIC = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenTable;
}


CString CRSDeathes::GetDefaultDBName() {
	return theApp.m_strYearDBName;
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
	DFX_Text(pFX, _T("[SURNAME]"), m_SURNAME);
	DFX_Text(pFX, _T("[NAME]"), m_NAME);
	DFX_Text(pFX, _T("[PATRONYMIC]"), m_PATRONYMIC);
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
