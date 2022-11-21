// RSChangesDep.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "DataManager.h"
#include "RSChangesDep.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "..\Common\DaoErr.h"

/////////////////////////////////////////////////////////////////////////////
// CRSChangesDep

IMPLEMENT_DYNAMIC(CRSChangesDep, CDaoRecordset)

CRSChangesDep::CRSChangesDep(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSChangesDep)
	m_ID = 0;
	m_TYPE = 0;
	m_NUMBER = 0;
	m_DATEREG = (DATE)0;
	m_REGISTRAR = _T("");
  m_PERSON = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenTable;
}


CString CRSChangesDep::GetDefaultDBName() {
	return theDataManager.m_strYearDBName;
}

CString CRSChangesDep::GetDefaultSQL() {
	return _T("[CHANGESDEP]");
}

void CRSChangesDep::DoFieldExchange(CDaoFieldExchange* pFX)
{
  try {
	//{{AFX_FIELD_MAP(CRSChangesDep)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_ID);
	DFX_Byte(pFX, _T("[TYPE]"), m_TYPE);
	DFX_Short(pFX, _T("[NUMBER]"), m_NUMBER);
	DFX_DateTime(pFX, _T("[DATEREG]"), m_DATEREG);
	DFX_Text(pFX, _T("[REGISTRAR]"), m_REGISTRAR);
	DFX_Text(pFX, _T("[PERSON]"), m_PERSON);
	//}}AFX_FIELD_MAP
  }
  catch(CDaoException* e) {
    DaoError(e, NULL, pFX->m_prs, pFX->m_nField-1);
    e->Delete();
  }
}

/////////////////////////////////////////////////////////////////////////////
// CRSChangesDep diagnostics

#ifdef _DEBUG
void CRSChangesDep::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CRSChangesDep::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
