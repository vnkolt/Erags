//
// Export.cpp
//
#include "stdafx.h"
#include "Export.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
// CExportColumn
CExportColumn::CExportColumn() {
  m_ColumnType = VT_EMPTY;
}
CExportColumn::~CExportColumn() {
}
void CExportColumn::SetColumn(VARTYPE ColumnType, LPCTSTR szColumnDBName, LPCTSTR szColumnAltName/*=NULL*/) {
  m_ColumnType      = ColumnType;
  m_szColumnDBName  = szColumnDBName;
  m_szColumnAltName = szColumnAltName;
}

//
// CExportCell
CExportCell::CExportCell() {
}
CExportCell::CExportCell(const COleVariant& var) {
  SetData(var);
}
CExportCell::~CExportCell() {
}
void CExportCell::SetData(const COleVariant& var) {
  m_data = var;
}

//
// CExportRow
CExportRow::CExportRow(int nColumns) {
  m_Cells.SetSize(nColumns);
  for( int i(0); i < nColumns; i++ ) {
    m_Cells.SetAt(i, new CExportCell() );
  }
}
CExportRow::~CExportRow() {
  for( int i(0); i < m_Cells.GetSize(); i++ ) {
    CExportCell* pCell = (CExportCell*)m_Cells.GetAt(i);
    delete pCell;
  }
  m_Cells.RemoveAll();
}
void CExportRow::SetAt(int nCol, const COleVariant& vt) {
  CExportCell* pCell = (CExportCell*)m_Cells.GetAt(nCol);
  pCell->SetData(vt);
}
COleVariant CExportRow::GetAt(int nCol) {
  CExportCell* pCell = (CExportCell*)m_Cells.GetAt(nCol);
  return pCell->GetData();
}
void CExportRow::DeleteCell(int nCol) {
  CExportCell* pCell = (CExportCell*)m_Cells.GetAt(nCol);
  if ( pCell ) {
    m_Cells.RemoveAt(nCol);
    delete pCell;
  }
}
//
// CExportTable
CExportTable::CExportTable(int nCols) {
  m_Columns.SetSize(nCols);
}
CExportTable::~CExportTable() {
  // free rows
  int i;
  for( i=0; i < m_Rows.GetSize(); i++ ) {
    CExportRow* pRow = (CExportRow*)m_Rows.GetAt(i);
    delete pRow;
  }
  m_Rows.RemoveAll();
  // free columns
  for( i = 0; i < m_Columns.GetSize(); i++ ) {
    CExportColumn* pColumn = (CExportColumn*)m_Columns.GetAt(i);
    delete pColumn;
  }
  m_Columns.RemoveAll();
}

void CExportTable::DeleteColumn(int nCol) {
  CExportColumn* pColumn = (CExportColumn*)m_Columns.GetAt(nCol);
  if ( pColumn ) {
    m_Columns.RemoveAt(nCol);
    delete pColumn;
  }
  for( int r = 0; r < m_Rows.GetSize(); r++ ) {
    CExportRow* pRow = (CExportRow*)m_Rows.GetAt(r);
    if ( pRow ) {
      pRow->DeleteCell(nCol);
    }
  }
}
void CExportTable::DeleteColumn(LPCTSTR szColumnName) {
  for( int i(0); i < m_Columns.GetSize(); i++ ) {
    CExportColumn* pColumn = (CExportColumn*)m_Columns.GetAt(i);
    if ( pColumn->GetDBName()==szColumnName ) {
      DeleteColumn(i);
      break;
    }
  }
}
int CExportTable::AddRow() {
  return m_Rows.Add( new CExportRow(m_Columns.GetSize()) );
}
void CExportTable::SetColumn(int nCol, VARTYPE ColumnType, LPCTSTR szColumnDBName, LPCTSTR szColumnAltName/*=NULL*/) {
  CExportColumn* pColumn = (CExportColumn*)m_Columns.GetAt(nCol);
  if ( NULL==pColumn ) {
    pColumn = new CExportColumn();
    m_Columns.SetAt(nCol, pColumn);
  }
  pColumn->SetColumn(ColumnType, szColumnDBName, szColumnAltName);
}
void CExportTable::SetData(int nCol, int nRow, const COleVariant& var) {
  CExportRow* pRow = (CExportRow*)m_Rows.GetAt(nRow);
  pRow->SetAt(nCol, var);
}
const CString& CExportTable::GetColumnName(int nCol) {
  CExportColumn* pColumn = (CExportColumn*)m_Columns.GetAt(nCol);
  return pColumn->GetDBName();
}
const CString& CExportTable::GetColumnAltName(int nCol) {
  CExportColumn* pColumn = (CExportColumn*)m_Columns.GetAt(nCol);
  return pColumn->GetAltName();
}
COleVariant CExportTable::GetCellData(int nCol, int nRow) {
  CExportRow* pRow = (CExportRow*)m_Rows.GetAt(nRow);
  return pRow->GetAt(nCol);
}