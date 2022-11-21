//
// ExpByExcel.cpp
//
#include "stdafx.h"

#include "ExpByExcel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning (disable:4786)

using namespace Excel;

CExpByExcel::CExpByExcel() {
  m_pXL = NULL;
}
CExpByExcel::~CExpByExcel() {
}
void CExpByExcel::ReportComError(_com_error &e) {
}
BOOL CExpByExcel::CreateInstance() {
  BOOL fRet = true;
  try { 
    m_pXL.CreateInstance(L"Excel.Application");
  }
  catch(_com_error &e) { 
    fRet = false;
    ReportComError(e);
  } 
  return fRet;
}
WorkbooksPtr CExpByExcel::GetWorkbooks() {
  if ( m_pXL ) {
    return m_pXL->Workbooks;
  }
  return NULL;
}

_WorkbookPtr CExpByExcel::Add(WorkbooksPtr pBooks) {
  return pBooks->Add((long)xlWorksheet); 
}
_WorksheetPtr CExpByExcel::GetActiveSheet() {
  if ( m_pXL ) {
    return m_pXL->ActiveSheet;
  }
  return NULL;
}
void CExpByExcel::SetSheetName(_WorksheetPtr pSheet, LPCTSTR szName) {
  if ( NULL==pSheet || NULL==szName ) {
    return;
  }
  try { 
    // This one will fail 
    pSheet->Name = szName;
  }
  catch (_com_error &e) { 
    ReportComError(e); 
  }
  pSheet->Name = szName;
}
void CExpByExcel::Quit() {
  if ( m_pXL ) {
    m_pXL->Quit();
  }
}

