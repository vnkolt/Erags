// RSChanges.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "RSChanges.h"

//#include "Utils.h"

#include "..\Common\DaoErr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern LPCTSTR g_szBirthDate;

/////////////////////////////////////////////////////////////////////////////
// CRSChanges

IMPLEMENT_DYNAMIC(CRSChanges, CDaoRecordset)

CRSChanges::CRSChanges(CDaoDatabase* pdb)
        	 :CDaoRecordset(pdb) {
	//{{AFX_FIELD_INIT(CRSChanges)
	m_ID = 0;
	m_NUMBER = 0;
	m_DATEREG = (DATE)0;
	m_SEX = FALSE;
	m_OLDSURNAME = _T("");
	m_NEWSURNAME = _T("");
	m_OLDNAME = _T("");
	m_NEWNAME = _T("");
	m_OLDPATRONYMIC = _T("");
	m_NEWPATRONYMIC = _T("");
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenTable;
}


CString CRSChanges::GetDefaultDBName() {
	return theApp.m_strYearDBName;
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
	DFX_Bool(pFX, _T("[SEX]"), m_SEX);
	DFX_Text(pFX, _T("[OLDSURNAME]"), m_OLDSURNAME);
	DFX_Text(pFX, _T("[NEWSURNAME]"), m_NEWSURNAME);
	DFX_Text(pFX, _T("[OLDNAME]"), m_OLDNAME);
	DFX_Text(pFX, _T("[NEWNAME]"), m_NEWNAME);
	DFX_Text(pFX, _T("[OLDPATRONYMIC]"), m_OLDPATRONYMIC);
	DFX_Text(pFX, _T("[NEWPATRONYMIC]"), m_NEWPATRONYMIC);
	//}}AFX_FIELD_MAP
  }
  catch(CDaoException* e) {
    DaoError(e, NULL, pFX->m_prs, pFX->m_nField-1);
    e->Delete();
  }
}
////////////////////////////////////////////////////////////////////////////
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
