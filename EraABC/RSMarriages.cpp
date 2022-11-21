// RSMarriages.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "RSMarriages.h"

#include "..\Common\DaoErr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSMarriages

IMPLEMENT_DYNAMIC(CRSMarriages, CDaoRecordset)

CRSMarriages::CRSMarriages(CDaoDatabase* pdb)
             :CDaoRecordset(pdb) {
	//{{AFX_FIELD_INIT(CRSMarriages)
	m_ID = 0;
	m_DATEREG = (DATE)0;
	m_NUMBER = 0;
	m_MOLD_SURNAME = _T("");
	m_MNEW_SURNAME = _T("");
	m_MNAME = _T("");
	m_MPATRONYMIC = _T("");
	m_WOLD_SURNAME = _T("");
	m_WNEW_SURNAME = _T("");
	m_WNAME = _T("");
	m_WPATRONYMIC = _T("");
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenTable;
}


CString CRSMarriages::GetDefaultDBName() {
	return theApp.m_strYearDBName;
}

CString CRSMarriages::GetDefaultSQL()
{
	return _T("[MARRIAGES]");
}

void CRSMarriages::DoFieldExchange(CDaoFieldExchange* pFX)
{
  try {
	//{{AFX_FIELD_MAP(CRSMarriages)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_ID);
	DFX_DateTime(pFX, _T("[DATEREG]"), m_DATEREG);
	DFX_Short(pFX, _T("[NUMBER]"), m_NUMBER);
	DFX_Text(pFX, _T("[MOLD_SURNAME]"), m_MOLD_SURNAME);
	DFX_Text(pFX, _T("[MNEW_SURNAME]"), m_MNEW_SURNAME);
	DFX_Text(pFX, _T("[MNAME]"), m_MNAME);
	DFX_Text(pFX, _T("[MPATRONYMIC]"), m_MPATRONYMIC);
	DFX_Text(pFX, _T("[WOLD_SURNAME]"), m_WOLD_SURNAME);
	DFX_Text(pFX, _T("[WNEW_SURNAME]"), m_WNEW_SURNAME);
	DFX_Text(pFX, _T("[WNAME]"), m_WNAME);
	DFX_Text(pFX, _T("[WPATRONYMIC]"), m_WPATRONYMIC);
	//}}AFX_FIELD_MAP
  }
  catch(CDaoException* e) {
    DaoError(e, NULL, pFX->m_prs, pFX->m_nField-1);
    e->Delete();
  }
}

/////////////////////////////////////////////////////////////////////////////
// CRSMarriages diagnostics

#ifdef _DEBUG
void CRSMarriages::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CRSMarriages::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
