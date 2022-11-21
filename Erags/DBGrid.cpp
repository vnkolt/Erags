// dbgrid.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "YesNoDlg.h"
#include "..\Common\CyrString.h"
#include "..\Common\DB.h"
#include "..\Common\MDB.h"

#include "DBGrid.h"
#include "DateFunc.h"

#include "..\Controls\GridCtrl\CellTypes\GridCellCheck.h"
#include "..\Controls\GridCtrl\CellTypes\GridCellCombo.h"
#include "..\Controls\GridCtrl\CellTypes\GridCellDate.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDBGrid, CGridCtrl)

int CALLBACK pfnDBGridCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  UNUSED_ALWAYS(lParamSort);

  CGridCellBase* pCell1 = (CGridCellBase*) lParam1;
  CGridCellBase* pCell2 = (CGridCellBase*) lParam2;
  if (!pCell1 || !pCell2) return 0;

  CGridCtrl* pGrid = pCell1->GetGrid();
  if ( pGrid ) {
    int iSortCol = pGrid->GetSortColumn();
    CString sText = (LPCTSTR)pGrid->GetItemData(0, iSortCol);
    if ( sText==_T("NUMBER") ) {
      return (atol(pCell1->GetText()) - atol(pCell2->GetText()));
    }
    else if ( sText==_T("DATEREG") ) {
      COleDateTime odt1, odt2;
      odt1.ParseDateTime(pCell1->GetText(), VAR_DATEVALUEONLY);
      odt2.ParseDateTime(pCell2->GetText(), VAR_DATEVALUEONLY);
      return (int)(odt1 - odt2);
    }
  }

  return CyrCompare(pCell1->GetText(), pCell2->GetText());
}



CString GetABCField(CDaoRecordset* pRS, LPCTSTR lpszFldName){
  CString sRet;
  COleVariant ovar;
  try {
    ovar = pRS->GetFieldValue(lpszFldName);
    switch(ovar.vt) {
      case VT_UI2:
        sRet.Format(_T("%d"), ovar.uiVal);
        break;
      case VT_I2:
        sRet.Format(_T("%d"), ovar.iVal);
        break;
      case VT_UI4:
        sRet.Format(_T("%d"), ovar.ulVal);
        break;
      case VT_I4:
        sRet.Format(_T("%d"), ovar.lVal);
        break;
      case VT_UINT:
        sRet.Format(_T("%d"), ovar.uintVal);
        break;
      case VT_INT:
        sRet.Format(_T("%d"), ovar.intVal);
        break;
      case VT_BOOL:
        if ( lpszFldName==_T("SEX") ) {
          sRet = ovar.boolVal ? _T("Ч") : _T("Ж");
        }
        else
          sRet = ovar.boolVal ? _T("1") : _T("0");
        break;
      case VT_BSTR:
        sRet = V_BSTRT(&ovar);
        break;
      case VT_DATE:
        sRet = GetFieldDate(pRS, lpszFldName, false);
        break;
    }
  }
  catch(CDaoException* e) {
    e->Delete();
  }
  return sRet;
}



/////////////////////////////////////////////////////////////////////////////
// CDBGrid
CDBGrid::CDBGrid() {
  m_pDB = NULL;
  SetListMode(TRUE);
  //EnableSelection(FALSE);
  m_bSortOnClick = TRUE;
  m_LastDateReg = (DATE)0;
  m_LastNumber = 0;
}

CDBGrid::~CDBGrid() {
}

void CDBGrid::SetCellFormats(int row, CDaoRecordset* pRS/*=NULL*/) {
  for( int col(1); col < GetColumnCount(); col++ ) {
    if ( dbDate==m_FieldTypes[col] ) {
      GV_ITEM gvItem;
      gvItem.row = row;
      gvItem.col = col;
      gvItem.strMask = _T("00.00.0000");
      gvItem.mask = GVIF_STRMASK;
      SetItem(&gvItem);
    }
    else if ( dbBoolean==m_FieldTypes[col] && NULL==pRS) {
      SetItemText(row, col, _T("Ч") );
    }
    if ( pRS ) {
      CDaoFieldInfo fi;
      try {
        pRS->GetFieldInfo(col, fi);
        if ( fi.m_strName==_T("DATEREG") ) {
          COleDateTime odt = iDBDateField(*pRS, col);
          if ( odt.GetStatus()==COleDateTime::valid && odt > m_LastDateReg )
            m_LastDateReg = odt;
        }
        else if ( fi.m_strName==_T("NUMBER") ) {
          short Number = iDBShortField(*pRS, col);
          if ( Number > m_LastNumber )
            m_LastNumber = Number;
        }
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG 
          e->ReportError();
        #endif
        e->Delete();
      }

      LPCTSTR szField = (LPCTSTR)GetItemData(0, col);
      CString sValue  = GetABCField(pRS, szField);
      SetItemText(row, col, sValue);
    }
    else {  // pRS==NULL
      CString sValue;
      if ( m_FieldNames[col].CompareNoCase(_T("NUMBER"))==0 ) {
        sValue.Format(_T("%d"), GetNextNumber());
      }
      else if ( m_FieldNames[col].CompareNoCase(_T("DATEREG"))==0 ) {
        sValue = GetDateDDMMYYYY(GetNextDateReg());
      }
      if ( sValue.GetLength() ) {
        SetItemText(row, col, sValue);
      }
    }
  }
}

bool CDBGrid::Load() {

  CString sql = _T("SELECT ");
  for( int col(0); col < GetColumnCount(); col++ ) {
    sql += (LPCTSTR)GetItemData(0, col);
    sql += _T(",");
  }
  sql.TrimRight(_T(","));
  sql += _T(" FROM ");
  sql += m_TableName;
  
  CDaoQueryDef qd(m_pDB);
  CDaoRecordset rs(m_pDB);

  int iRow(0);

  try {
    qd.Create(NULL,sql);
    rs.Open(&qd);

    int nColumns = GetColumnCount();

    m_FieldTypes.SetSize(nColumns);
    m_FieldNames.SetSize(nColumns);

    for( int col(0); col < GetColumnCount(); col++ ) {
      LPCTSTR szField = (LPCTSTR)GetItemData(0, col);
      CDaoFieldInfo fi;
      rs.GetFieldInfo(szField, fi);
      m_FieldTypes.SetAt(col, fi.m_nType);
      m_FieldNames.SetAt(col, fi.m_strName);
    }

    while ( !rs.IsEOF() ) {
      long lID = iDBLongField(rs, 0);

      iRow++;
      InsertRow(_T(""));

      SetCellFormats(iRow, &rs);
      SetItemData(iRow, 0, (LPARAM)lID);
      rs.MoveNext();
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return false;
  }

  SetCompareFunction(pfnDBGridCompare);

  return true;
}

bool CDBGrid::AddRow(int newRow) {
  return Insert(newRow);
}

bool CDBGrid::Insert(int newRow) {
  if ( NULL==m_pDB )
    return false;
  if ( m_TableName.IsEmpty() )
    return false;
  LPCTSTR szID = (LPCTSTR)GetItemData(0, 0); // for ID fieldname

  CString sql;
  if ( m_InsertSQL.IsEmpty() )
    return false;

  try {
    m_pDB->Execute(m_InsertSQL);
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return false;
  }

  sql.Format(_T("SELECT MAX(%s) FROM %s"), (LPCTSTR)GetItemData(0, 0), m_TableName );
  CDaoRecordset rs(m_pDB);
  try {
    rs.Open(dbOpenDynaset, sql);
    long lID = iDBLongField(rs, 0);
    SetCellFormats(newRow);
    SetItemData(newRow, 0, (LPARAM)lID);
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return false;
  }

  return true;
}

bool CDBGrid::Update(int row, int col, const CString& sData) {
  if ( NULL==m_pDB )
    return false;
  if ( m_TableName.IsEmpty() )
    return false;
  LPCTSTR szID = (LPCTSTR)GetItemData(0, 0); // for ID fieldname

  CString sql = _T("SELECT ");
  LPCTSTR szField = (LPCTSTR)GetItemData(0, col); // for other fieldnames
  sql += szField;

  CString s;
  s.Format(_T(" FROM %s WHERE %s=%lu"), m_TableName, szID, (long)(LPCTSTR)GetItemData(row, 0) );
  sql += s;

  try {
    CDaoRecordset rs(m_pDB);
    rs.Open(dbOpenDynaset, sql);

    COleVariant  ovar;
    COleDateTime odt;
    if ( szField==_T("SEX")) {
      ovar.vt = VT_BOOL;
      ovar.boolVal = (sData==_T("ч") || sData==_T("Ч")) ? AFX_OLE_TRUE : AFX_OLE_FALSE;
    }
    else
      ovar.SetString(sData, VT_BSTRT);

    CDaoFieldInfo fi;
    rs.GetFieldInfo(szField, fi);
    switch ( fi.m_nType ) {
      case dbDate:
        odt.ParseDateTime(sData);
        ovar.date = (DATE)odt;
        ovar.vt = VT_DATE;
        if ( fi.m_strName.CompareNoCase(_T("DATEREG"))==0 ) {
          if ( odt > m_LastDateReg )
            m_LastDateReg = odt;
        }
        break;
      case dbInteger:
        if ( fi.m_strName.CompareNoCase(_T("NUMBER"))==0 ) {
          short Number = (short)atoi(sData);
          if ( Number > m_LastNumber )
            m_LastNumber = Number;
        }
        break;
    }
    rs.Edit();
    rs.SetFieldValue(szField, ovar); // for other fieldnames
    rs.Update();
    rs.Close();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return false;
  }

  return true;
}

bool CDBGrid::Delete(int row) {
  if ( NULL==m_pDB )
    return false;
  if ( m_TableName.IsEmpty() )
    return false;
  LPCTSTR szID = (LPCTSTR)GetItemData(0, 0); // for ID fieldname

  CCellID curCell = GetFocusCell();

  CString sql;
  sql.Format(_T("DELETE FROM %s WHERE [%s]=%ld"), m_TableName, szID, (long)(LPCTSTR)GetItemData(row, 0));

  try {
    m_pDB->Execute(sql);
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return false;
  }

  Refresh();

  if ( IsValid(curCell)) {
    if ( curCell.row < GetRowCount() ) {
      SelectRows(curCell);
//      SetFocusCell(curCell);
      EnsureVisible(curCell);
    }
  }

  return true;
}

short CDBGrid::GetNextNumber() {
  return m_LastNumber+1;
}

COleDateTime CDBGrid::GetNextDateReg() {
  return m_LastDateReg;
}

void CDBGrid::SelectRow(int row) {
  SetFocusCell(row, 1);
  SetSelectedRange(row, 0, row, GetColumnCount()-1);
  EnsureVisible(row, 1);
}

BEGIN_MESSAGE_MAP(CDBGrid, CGridCtrl)
	//{{AFX_MSG_MAP(CDBGrid)
  ON_NOTIFY(GVN_ENDLABELEDIT, IDC_INPLACE_CONTROL, OnEndInPlaceEdit)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDBGrid::OnEditCell(int nRow, int nCol, CPoint point, UINT nChar) {
/************************************** : by VK at 05.06.2004 22:09:15 **\
  LPCTSTR szField = (LPCTSTR)GetItemData(0, nCol);
  if ( strcmp(szField, _T("SEX"))==0 ) {
    CString s = GetItemText(nRow, nCol);
    if ( s==_T("Ч") || s==_T("ч") )
      s = _T("Ж");
    else
      s = _T("Ч");
    SetItemText(nRow, nCol, s);
    //    SetCellType(nRow,nCol, RUNTIME_CLASS(CGridCellCheck));
  }
\************************************** : by VK at 05.06.2004 22:09:20 **/
  CGridCtrl::OnEditCell(nRow, nCol, point, nChar);
}

void CDBGrid::OnDelete() {
  int nSellRows = 0;
  int nFirstSelectedRow = 0;
  CDWordArray delArray;
  for( int row = GetRowCount()-1; row > GetFixedRowCount()-1; row-- ) {
    if ( IsCellSelected(row, 1) ) {
      nFirstSelectedRow = row;
      delArray.Add( (DWORD)row );
      nSellRows++;
    }
  }
  if ( nSellRows ) {
    CString s;
    CString sHowMutch;
    if ( 5 < nSellRows && nSellRows < 21 )
      sHowMutch = _T("записів");
    else {
      switch( nSellRows % 10 ) {
        case 1:                   sHowMutch = _T("запис");    break;
        case 2: case 3: case 4:   sHowMutch = _T("записи");  break;
        default:                  sHowMutch = _T("записів");  break;
      }
    }
    s.Format( _T("Ви дійсно бажаєте видалити %d %s?"), nSellRows, sHowMutch);
    if ( YNDlg(this, _T("Увага! Вилучені записи не можна відновити."), s)) {
      for( int i(0); i < delArray.GetSize(); i++ ) {
        int row = (int)delArray.GetAt(i);
        if ( Delete(row) )
          DeleteRow(row);
      }
    }
  } // if ( nSellRows )
  if ( nFirstSelectedRow ) {
    if ( nFirstSelectedRow > 1 ) {
      SetFocusCell(--nFirstSelectedRow, 1);
      EnsureVisible(nFirstSelectedRow, 1);
      SetSelectedRange(nFirstSelectedRow, 0, nFirstSelectedRow, GetColumnCount()-1);
    }
    else {
      if ( GetRowCount() > 1 ) {
        SetFocusCell(1, 1);
        SetSelectedRange(1, 0, 1, GetColumnCount()-1);
      }
    }
  }
}

void CDBGrid::OnEndInPlaceEdit(NMHDR* pNMHDR, LRESULT* pResult) {
  GV_DISPINFO *pgvDispInfo = (GV_DISPINFO *)pNMHDR;
  GV_ITEM     *pgvItem = &pgvDispInfo->item;

  CEdit* pEdit = (CEdit*)CWnd::FromHandle(pgvDispInfo->hdr.hwndFrom);
  if ( pEdit->GetModify() ) {
    CString s;
    pEdit->GetWindowText(s);
    Update(pgvItem->row, pgvItem->col, s);
    //GetOwner()->SendMessage(WM_NOTIFY, (WPARAM)pEdit->GetDlgCtrlID(),  (LPARAM)pNMHDR);
  }
  CGridCtrl::OnEndInPlaceEdit(pNMHDR, pResult);
}
/////////////////////////////////////////////////////////////////////////////
// CDBGrid message handlers

void CDBGrid::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
  if ( VK_DELETE==nChar ) {
    OnDelete();
  }
  else {
    if (VK_DOWN==nChar && IsValid(m_idCurrentCell) && m_idCurrentCell.row==GetRowCount()-1 ) {
      CString s = GetItemText(m_idCurrentCell.row, m_idCurrentCell.col);
      if ( !s.IsEmpty() ) {
        int nCol = m_idCurrentCell.col-1;
        if ( nCol <= 0 ) nCol++;
        int nRow = GetRowCount();
        InsertRow(_T(""));
        AddRow(nRow);
        EnsureVisible(nRow, nCol);
        ResetSelectedRange();
        m_idCurrentCell.row = nRow;
        m_idCurrentCell.col = nCol;
        OnEditCell(nRow, nCol, CPoint(-1,-1), VK_LBUTTON);
      }
    }
    CGridCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
  }
}

