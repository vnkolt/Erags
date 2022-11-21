//
// Copy2Excel.cpp
//
#include "stdafx.h"
#include "ImpExp.h"
#include "..\Common\CyrString.h"
#include "..\Common\Elections.h"

#include "OOCalcWrapper.h"

#pragma warning (disable:4146)
#pragma warning (disable:4192)

#import "..\MSO\mso9.dll"    no_namespace rename("DocumentProperties", "DocumentPropertiesXL")
#import "..\MSO\vbe6ext.olb" no_namespace
#import "..\MSO\excel9.olb"  rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") no_dual_interfaces

//using namespace Excel;

enum XlSheetType
{
    xlChart = -4109,
    xlDialogSheet = -4116,
    xlExcel4IntlMacroSheet = 4,
    xlExcel4MacroSheet = 3,
    xlWorksheet = -4167
};


void ReportComError(_com_error &e) {
  CString szErr;
  szErr.Format(_T("COM error %08lx, %s."), e.Error(), e.ErrorMessage());
  AfxMessageBox(szErr);
}

CString GetColName(int col) {
  CString sCol, szCol;
  while ( col >=0 ) {
    CString s;
    s.Format(_T("%c"), 'A'+col%26);
    col -= 26;
    sCol += s;
  }
  szCol.Format(_T("%s:%s"), sCol, sCol);
  return szCol;
}

CString GetRowName(int row) {
  CString szRow;
  szRow.Format(_T("%d:%d"), row+1, row+1);
  return szRow;
}

CString GetCellName(int row, int col) {
  CString sCell, sRow, sCol;
  sRow.Format(_T("%d"), row+1);
  while ( col >=0 ) {
    CString s;
    s.Format(_T("%c"), 'A'+col%26);
    col -= 26;
    sCol += s;
  }
  sCell.Format("%s%s", sCol, sRow);

  return sCell;
}
CString GetRangeName(const RECT* pRect) {
  CString s;
  s.Format(_T("%s:%s"), GetCellName(pRect->top, pRect->left), GetCellName(pRect->bottom, pRect->right));
  return s;
}

//using namespace Excel;
Excel::_ApplicationPtr  g_pXL     = NULL;
Excel::WorkbooksPtr     g_pBooks  = NULL;
Excel::_WorkbookPtr     g_pBook   = NULL;

void CopyCells(Excel::_WorksheetPtr pSrcSheet, _bstr_t& srcRange, Excel::_WorksheetPtr pDstSheet, _bstr_t& dstRange) {
  if ( pSrcSheet==pDstSheet && srcRange==dstRange ) {
    return;
  }
  try {
    pSrcSheet->Select();
    pSrcSheet->Range[srcRange]->Select();
    pSrcSheet->Range[srcRange]->Copy();
    //pDstSheet->Range[dstRange]->PasteSpecial(Excel::xlPasteAll, Excel::xlPasteSpecialOperationNone, vtMissing, vtMissing);
    pDstSheet->Range[dstRange]->PasteSpecial(Excel::xlPasteAll, Excel::xlPasteSpecialOperationNone, false, false);
  }
  catch (_com_error &e) { 
    ReportComError(e); 
  } 
}
void CopyCellsHeigh(Excel::_WorksheetPtr pSrcSheet, _bstr_t& srcRange, Excel::_WorksheetPtr pDstSheet, _bstr_t& dstRange) {
  if ( pSrcSheet==pDstSheet && srcRange==dstRange ) {
    return;
  }
  _variant_t Heigh;
  try {
    Heigh = pSrcSheet->Range[srcRange]->RowHeight;
    pDstSheet->Range[dstRange]->RowHeight = Heigh;
  }
  catch (_com_error &e) { 
    ReportComError(e); 
  } 
}

void CopyRowHeigh(Excel::_WorksheetPtr pSrcSheet, Excel::_WorksheetPtr pDstSheet, int rFrom, int rTo, int Rows) {
/*
  if ( pSrcSheet==pDstSheet ) {
    return;
  }
*/
  for( int r(0); r < Rows; r++ ) {
    _variant_t height;
    _bstr_t bstrFrom(GetRowName(rFrom+r));
    _bstr_t bstrTo(GetRowName(rTo+r));
    try {
      height = pSrcSheet->Range[bstrFrom]->EntireRow->RowHeight;
      pDstSheet->Range[bstrTo]->EntireRow->RowHeight = height;
    }
    catch (_com_error &e) { 
      ReportComError(e); 
    } 
  }
/*
  for( int row = rFrom; row <= rTo; row++ ) {
    _variant_t height;
    _bstr_t bstrCol(GetRowName(row));
    try {
      height = pSrcSheet->Range[bstrCol]->EntireRow->RowHeight;
      pDstSheet->Range[bstrCol]->EntireRow->RowHeight = height;
    }
    catch (_com_error &e) { 
      ReportComError(e); 
    } 
  }
*/
}

void CopyColWidth(Excel::_WorksheetPtr pSrcSheet, Excel::_WorksheetPtr pDstSheet, int cFrom, int cTo) {
  if ( pSrcSheet==pDstSheet ) {
    return;
  }
  for( int col = cFrom; col <= cTo; col++ ) {
    _variant_t width;
    _bstr_t bstrCol(GetColName(col));
    try {
      width = pSrcSheet->Range[bstrCol]->EntireColumn->ColumnWidth;
      pDstSheet->Range[bstrCol]->EntireColumn->ColumnWidth = width;
    }
    catch (_com_error &e) { 
      ReportComError(e); 
    } 
  }
}

__declspec(dllexport) BOOL WINAPI BeginCopy2XL() {
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  BOOL fRet = true;
  try { 
    g_pXL.CreateInstance(L"Excel.Application"); 
    g_pXL->Visible = VARIANT_FALSE;//VARIANT_TRUE;
    g_pBooks  = g_pXL->Workbooks;
    g_pBook   = g_pBooks->Add((long)xlWorksheet);
  }
  catch (_com_error &e) { 
    fRet = false;
    ReportComError(e); 
  } 
  return fRet;
}

__declspec(dllexport) BOOL WINAPI Copy2XL(long nSheet) {
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  BOOL fRet = true;
  if ( NULL==g_pXL || NULL==g_pBooks ) {
    return false;
  }
  try { 
    Excel::_WorksheetPtr pSheet  = g_pXL->ActiveSheet;
    Excel::SheetsPtr     pSheets = g_pBook->Sheets;
    if ( pSheets->Count < nSheet ) {
      g_pXL->ScreenUpdating = VARIANT_FALSE;
      pSheet = pSheets->Add();
      g_pXL->ScreenUpdating = VARIANT_TRUE;
    }
    pSheet->Paste();
  }
  catch (_com_error &e) { 
    fRet = false;
    ReportComError(e); 
  } 
  return fRet;
}

__declspec(dllexport) void WINAPI EndCopy2XL() {
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  if ( g_pXL ) {
    g_pXL->Visible = VARIANT_TRUE;
  }
  g_pBooks = NULL;
  g_pXL    = NULL;
}

/*
__declspec(dllexport) BOOL WINAPI Copy2XL() {
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  BOOL fRet = true;
  _ApplicationPtr pXL;
  try { 
    pXL.CreateInstance(L"Excel.Application"); 
    pXL->Visible = VARIANT_TRUE;
    WorkbooksPtr pBooks  = pXL->Workbooks;
    _WorkbookPtr pBook   = pBooks->Add((long)xlWorksheet);
    _WorksheetPtr pSheet = pXL->ActiveSheet;
    pSheet->Paste();
  }
  catch (_com_error &e) { 
    fRet = false;
    ReportComError(e); 
  } 
  return fRet;
}
*/

struct KeyCell {
  int     row;
  int     col;
  LPCTSTR szName;
  CString szValue;
  KeyCell():row(0), col(0), szName(NULL){}
  KeyCell(int r, int c, LPCTSTR szN, LPCTSTR szV):row(r), col(c), szName(szN), szValue(szV) {}
};

LPCTSTR g_CommonKW[] = { "!Òåðèòîð³ÿ!", "!ïåð³îä!", NULL };

LPCTSTR g_KW[]  = { "!¹!"  ,  "!ÏðÏ!" , "!²ìÏ!" ,  "!ÏáÏ!",  "!ÄàòàÍ!",
                    "!ÄÍ!" ,  "!ÎÍ!"  , "!ÐÍ!"  ,  "!ìññí!", "!ìñ!",
                    "!âóë!",  "!òâóë!", "!íâóë!",  "!áóä!",  "!äñääììðððð!",
                    NULL
                  };

LPCTSTR FindKW(LPCTSTR szWhere, LPCTSTR* pKW) {
  for( int i(0); pKW[i]; i++ ) {
    if ( DBFind(szWhere, pKW[i]) >=0 ) {
      return pKW[i];
    }
  }
  return NULL;
}

int GetKeyCellIndex(CArray <KeyCell, KeyCell>& Keys, LPCTSTR szKW) {
  for( int i(0); i < Keys.GetSize(); i++ ) {
    KeyCell kc = Keys.GetAt(i);
    if ( DBFind(kc.szValue, szKW) >= 0 ) {
      return i;
    }
  }
  return -1;
}

CString GetKeyWord(const CString& szCell, int& nFrom) {
  CString szKeyWord;
  int nFirst = szCell.Find('!', nFrom);
  if ( nFirst >= 0 ) {
    int nSecond = szCell.Find('!', nFirst+1);
    if ( nSecond >= 1 ) {
      szKeyWord = szCell.Mid(nFirst, nSecond-nFirst+1);
      nFrom = nSecond+1;
    }
  }
  return szKeyWord;
}

#pragma warning (push)
#pragma warning (disable : 4786)
Excel::_WorksheetPtr GetNextSheet(Excel::_ApplicationPtr pXL, Excel::_WorkbookPtr pBook, long nSheet) {
  Excel::_WorksheetPtr pNextSheet;
  Excel::SheetsPtr     pSheets;

  try { 
    pSheets = pBook->Sheets;
    if ( pSheets->Count < nSheet ) {
      variant_t LastSheet((IDispatch*)pSheets->GetItem((long)(nSheet-1)));
      pNextSheet = pSheets->Add(vtMissing, LastSheet);
    }
    else {
      pNextSheet = pSheets->GetItem(nSheet);
    }
  }
  catch (_com_error &e) { 
    pNextSheet = NULL;
    ReportComError(e); 
  } 
  return pNextSheet;
}
#pragma warning (pop)


__declspec(dllexport) BOOL WINAPI E2Excel(CElections* pElections, LPCTSTR szXLS, BOOL fMultiSheet, BOOL (* pElectEncoder)(TCHAR* pDestBuf, int BufSize, LPCTSTR szKey, CElectItem* pItem, int Number), void (* ProgressRoutine)(int nCount, int nProcessed, void* lpData), void* lpData) {
  BOOL fRet = true;
  Excel::_ApplicationPtr pXL;
  Excel::WorkbooksPtr    pBooks;
  Excel::_WorkbookPtr    pBook;
  Excel::_WorksheetPtr   pSheet;
  _bstr_t bstrXLS =      szXLS;
  CString                szCell;

  TCHAR   buf[1024];

  POINT   begHdr;
  POINT   endHdr;
  int   HdrFound  = 0;
  int   OffsetRow = 0;
  int   MinTRow   = 10000, MaxTRow   = 0;
  int   MinTCol   = 10000, MaxTCol   = 0;
  long  nSheet = 1;
  CString szValue;
  CArray <KeyCell, KeyCell> CommonKeys;
  CArray <KeyCell, KeyCell> Keys;

  if ( pElections->m_Territories.GetSize() <= 0 ) {
    return false;
  }
  CTerritory* pTerritiry = (CTerritory*)pElections->m_Territories.GetAt(0);
  if ( NULL==pTerritiry ) {
    return false;
  }

  int nItems   = pElections->CalcTotalItems();
  int nCurItem = 0;

  try { 
    pXL.CreateInstance(L"Excel.Application"); 
    pBooks = pXL->Workbooks; 
    try {
      pBook = pBooks->Open(bstrXLS);//, VARIANT_FALSE, VARIANT_FALSE, 
      pSheet = pBook->Sheets->GetItem(nSheet);

#ifdef _DEBUG
      pXL->Visible = VARIANT_TRUE;
#endif
      for( int row = 0; row < 30; row++ ) {
        for( int col = 0; col < 20; col++ ) {
          szCell = GetCellName(row, col);
          VARIANT val = pSheet->Range[_bstr_t(szCell)]->Value;
          if ( VT_BSTR == val.vt ) {
            USES_CONVERSION;
            szValue = OLE2T(val.bstrVal);
            int nFind = 0;
            if ( (nFind = DBFind(szValue, _T("!ÏÇ!"))) >= 0 ) {
              begHdr.x = col; begHdr.y = row; HdrFound = 1;
              ReplaceIgnoreCase(szValue, _T("!ÏÇ!"), _T(""));
              pSheet->Range[_bstr_t(szCell)]->Value = _bstr_t(szValue);
            }
            else if ( DBFind(szValue, _T("!ÊÇ!")) >= 0 ) {
              endHdr.x = col; endHdr.y = row; HdrFound++;
              ReplaceIgnoreCase(szValue, _T("!ÊÇ!"), _T(""));
              pSheet->Range[_bstr_t(szCell)]->Value = _bstr_t(szValue);
            }
            else {
              LPCSTR szKW = FindKW(szValue, g_CommonKW);
              if ( szKW ) {
                CommonKeys.Add( KeyCell(row, col, szKW, szValue) );
              }
              else {
                int nFrom = 0;
                while ( true ) {
                  CString szKeyWord  = GetKeyWord(szValue, nFrom);
                  if ( szKeyWord.IsEmpty() ) {
                    break;
                  }
                  if ( row < MinTRow ) { MinTRow = row; }
                  if ( row > MaxTRow ) { MaxTRow = row; }
                  if ( col < MinTCol ) { MinTCol = col; }
                  if ( col > MaxTCol ) { MaxTCol = col; }
                  Keys.Add( KeyCell(row, col, szKeyWord, szValue) );
                }
              }
            }
          }
        }
      }
      if ( HdrFound < 2 ) {
        return false;
      }
      int HdrRows = endHdr.y - begHdr.y +1;
      int TabRows = MaxTRow  - MinTRow +1;
      CString szFrom, szTo;

      if ( CommonKeys.GetSize()>0 && Keys.GetSize() >0 ) {
        Excel::_WorksheetPtr pCurSheet = pSheet;
        for( int i(0); i < pElections->m_Territories.GetSize(); i++ ) {
          pSheet->Activate();
          szFrom.Format(_T("%s:%s"), GetCellName(begHdr.y           , begHdr.x), GetCellName(endHdr.y          , endHdr.x));
          szTo  .Format(_T("%s:%s"), GetCellName(begHdr.y+OffsetRow , begHdr.x), GetCellName(endHdr.y+OffsetRow, endHdr.x));
          CopyCells(pSheet, _bstr_t(szFrom), pCurSheet, _bstr_t(szTo));
          CopyRowHeigh(pSheet, pCurSheet, begHdr.y, begHdr.y+OffsetRow, HdrRows);
          CopyColWidth(pSheet, pCurSheet, begHdr.x, endHdr.x);

          CTerritory* pTerritory = (CTerritory*)pElections->m_Territories.GetAt(i);
          int kcIndex = GetKeyCellIndex(CommonKeys, "!Òåðèòîð³ÿ!");
          if ( kcIndex >= 0 ) {
            KeyCell kc = CommonKeys.GetAt(kcIndex);
            CString szValue = kc.szValue;
            ReplaceIgnoreCase(szValue, _T("!Òåðèòîð³ÿ!"), pTerritory->m_szTerritory);
            _bstr_t bstrCell = _bstr_t(GetCellName(kc.row+OffsetRow, kc.col));
            pCurSheet->Range[bstrCell]->Value = _bstr_t(szValue);
          }
          kcIndex = GetKeyCellIndex(CommonKeys, "!ïåð³îä!");
          if ( kcIndex >= 0 ) {
            KeyCell kc = CommonKeys.GetAt(kcIndex);
            CString szValue = kc.szValue;
            ReplaceIgnoreCase(szValue, _T("!ïåð³îä!"), pElections->m_szPeriod);
            _bstr_t bstrCell = _bstr_t(GetCellName(kc.row+OffsetRow, kc.col));
            pCurSheet->Range[bstrCell]->Value = _bstr_t(szValue);
          }
          for( int i(0); i < pTerritory->m_array.GetSize(); i++ ) {
            nCurItem++;
            if ( ProgressRoutine ) {
              ProgressRoutine(nItems, nCurItem, lpData);
            }
            CElectItem* pItem = (CElectItem*)pTerritory->m_array.GetAt(i);
            int cRow = MinTRow+OffsetRow;
            int cCol = MinTCol;
            szFrom.Format(_T("%s:%s"), GetCellName(MinTRow, MinTCol), GetCellName(MaxTRow, MaxTCol));
            szTo  .Format(_T("%s:%s"), GetCellName(cRow, MinTCol),    GetCellName(cRow    , MaxTCol));
            CopyCells(pSheet, _bstr_t(szFrom), pCurSheet, _bstr_t(szTo));
            CopyCellsHeigh(pSheet, _bstr_t(szFrom), pCurSheet, _bstr_t(szTo));
            for( int k(0); k < Keys.GetSize(); k++ ) {
              KeyCell kc = Keys.GetAt(k);
              szCell  = GetCellName(cRow, kc.col);
              CString szCellValue = kc.szValue;
              CString szKeyWord, szKey, szValue;
              while ( true ) {
                int nFrom = 0;
                szKeyWord = GetKeyWord(szCellValue, nFrom);
                if ( szKeyWord.IsEmpty() ) {
                  break;
                }
                szKey   = Trim(szKeyWord.Mid(1, szKeyWord.GetLength()-2));
                pElectEncoder(buf, 1024, szKey, pItem, i+1);
                ReplaceIgnoreCase(szCellValue, szKeyWord, buf);
                pCurSheet->Range[_bstr_t(szCell)]->Value = _bstr_t(szCellValue);
              }
            }
            OffsetRow += TabRows;
          } // for( int i(0); i < pTerritory->m_array.GetSize(); i++ )
          OffsetRow++;
          // System date
          pElectEncoder(buf, 1024, "ÑÄ", NULL, 0);
          szCell = GetCellName(OffsetRow+HdrRows, 1);
          pCurSheet->Range[_bstr_t(szCell)]->Value = _bstr_t(buf);
          if ( fMultiSheet ) {
            OffsetRow = 0;
            if ( ++nSheet <= pElections->m_Territories.GetSize() ) {
              pCurSheet = GetNextSheet(pXL, pBook, nSheet);
            }
          }
          else {
            OffsetRow += HdrRows + 1;
          }
        }
      }
      pBook->Save();
      pBook->Saved = VARIANT_TRUE; 
      pXL->Visible = VARIANT_TRUE;
      pBooks = NULL;
      pXL    = NULL;
      //pBooks->Close();
      //pXL->Quit();
    }
    catch (_com_error &e) { 
      ReportComError(e); 
    } 
  }
  catch (_com_error &e) { 
    fRet = false;
    ReportComError(e); 
  } 
 return true;
}

/*
void CopyCells(CComDispatchDriver& dispSheets, int nSrcSheet, _bstr_t& srcRange, int nDstSheet, _bstr_t& dstRange) {
  if ( nSrcSheet==nDstSheet && srcRange==dstRange ) {
    return;
  }
  // http://www.oooforum.org/forum/viewtopic.phtml?t=22048
  // http://www.oooforum.org/forum/viewtopic.phtml?t=67090&highlight=
  //
  HRESULT hRes;
  _variant_t varRet, varData, args[2];
  try {
    args[0].vt = VT_I4;
    args[0].intVal = nSrcSheet;
    hRes = dispSheets.InvokeN(L"getByIndex", args, 1, &varRet);
    if ( FAILED(hRes) ) {
      return;
    }
    CComDispatchDriver srcSheet(varRet.pdispVal);
    varRet.Clear();

    args[0].vt = VT_I4;
    args[0].intVal = nDstSheet;
    hRes = dispSheets.InvokeN(L"getByIndex", args, 1, &varRet);
    if ( FAILED(hRes) ) {
      return;
    }
    CComDispatchDriver dstSheet(varRet.pdispVal);
    varRet.Clear();

    args[0] = srcRange;
    hRes = srcSheet.InvokeN(L"getCellRangeByName", args, 1, &varRet);
    if ( FAILED(hRes) ) {
      return;
    }
    CComDispatchDriver srcRange(varRet.pdispVal);
    varRet.Clear();

    args[0] = dstRange;
    hRes = dstSheet.InvokeN(L"getCellRangeByName", args, 1, &varRet);
    if ( FAILED(hRes) ) {
      return;
    }
    CComDispatchDriver dstRange(varRet.pdispVal);
    varRet.Clear();

    //
    //pSrcSheet->Select();
    //pSrcSheet->Range[srcRange]->Select();
    //pSrcSheet->Range[srcRange]->Copy();
    //pDstSheet->Range[dstRange]->PasteSpecial(Excel::xlPasteAll, Excel::xlPasteSpecialOperationNone, false, false);
    //
  }
  catch (_com_error &e) { 
    ReportComError(e); 
  } 
}
*/
void CopyOOCells(CComDispatchDriver& srcSheet, const CRect& rSrc, CComDispatchDriver& dstSheet, const CRect& rDst) {
  if ( srcSheet==dstSheet && rSrc==rDst ) {
    return;
  }

  _bstr_t srcRange = _bstr_t(GetRangeName(&rSrc));
  _bstr_t dstRange = _bstr_t(GetRangeName(&rDst));
  // http://www.oooforum.org/forum/viewtopic.phtml?t=22048
  // http://www.oooforum.org/forum/viewtopic.phtml?t=67090&highlight=
  //
  HRESULT hRes;
  _variant_t varRet, varData, args[2];
  try {
    args[0] = srcRange;
    hRes = srcSheet.InvokeN(L"getCellRangeByName", args, 1, &varRet);
    if ( FAILED(hRes) ) {
      return;
    }
    CComDispatchDriver srcRange(varRet.pdispVal);
    varRet.Clear();

    args[0] = dstRange;
    hRes = dstSheet.InvokeN(L"getCellRangeByName", args, 1, &varRet);
    if ( FAILED(hRes) ) {
      return;
    }
    CComDispatchDriver dstRange(varRet.pdispVal);
    varRet.Clear();

    _variant_t oSrcCells, oDstCell;

    args[0].vt = VT_I4;
    args[0].intVal = rDst.top; // row;
    args[1].vt = VT_I4;
    args[1].intVal = rDst.left;// col;

    hRes = dstSheet.InvokeN(L"getCellByPosition", args, 2, &varRet);
    if ( FAILED(hRes) ) {
      return;
    }

    CComDispatchDriver dispCell(varRet.pdispVal);
    varRet.Clear();

    hRes = dispCell.Invoke0(L"getCellAddress", &oDstCell);
    hRes = srcRange.Invoke0(L"getRangeAddress", &oSrcCells);

    args[0] = oSrcCells;
    args[1] = oDstCell;
    hRes = dstSheet.InvokeN(L"CopyRange", args, 2, &varRet);

  }
  catch (_com_error &e) { 
    ReportComError(e); 
  } 
}

void CopyOORowHeigh(CComDispatchDriver& srcSheet, CComDispatchDriver& dstSheet, int rFrom, int rTo, int Row) {
  // http://www.oooforum.org/forum/viewtopic.phtml?t=59696
  if ( srcSheet==dstSheet && rFrom==Row ) {
    return;
  }
  HRESULT hRes;
  _variant_t varRet;
  hRes = srcSheet.Invoke0(L"GetRows", &varRet);
  CComDispatchDriver dispSrcRows(varRet.pdispVal);
  hRes = dstSheet.Invoke0(L"GetRows", &varRet);
  CComDispatchDriver dispDstRows(varRet.pdispVal);

  int Rows = rTo - rFrom + 1;

  for( int r(0); r < Rows; r++ ) {
    _variant_t args[2];
    _bstr_t bstrFrom(GetRowName(rFrom+r));
    _bstr_t bstrTo(GetRowName(rTo+r));
    try {
      //_variant_t SrcRows, DstRows;
      hRes = dispSrcRows.Invoke1(L"getByIndex", &_variant_t((long)(r+rFrom)), &varRet);
      CComDispatchDriver srcRow(varRet.pdispVal);
      hRes = dispDstRows.Invoke1(L"getByIndex", &_variant_t((long)(r+Row)), &varRet);
      CComDispatchDriver dstRow(varRet.pdispVal);
      args[0] = _bstr_t("Height");
      hRes = srcRow.InvokeN(L"getPropertyValue", args, 1, &varRet);
      args[1] = args[0];
      args[0] = varRet;
      hRes = dstRow.InvokeN(L"setPropertyValue", args, 2, &varRet);
    }
    catch (_com_error &e) { 
      ReportComError(e); 
    } 
  }
}
void SetCellValue(CComDispatchDriver& dispSheet, int row, int col, LPCTSTR szValue) {
  HRESULT hRes;
  _variant_t varRet, args[2];

  args[0].vt = VT_I4;
  args[0].intVal = row;
  args[1].vt = VT_I4;
  args[1].intVal = col;
  hRes = dispSheet.InvokeN(L"getCellByPosition", args, 2, &varRet);
  if ( FAILED(hRes) ) {
    return;
  }
  CComDispatchDriver dispCell(varRet.pdispVal);
  varRet.Clear();
  args[0] = _bstr_t(szValue);
  hRes = dispCell.InvokeN(L"setString", args, 1, &varRet);
}

__declspec(dllexport) BOOL WINAPI E2OCalc(CElections* pElections, LPCTSTR szXLS, BOOL fMultiSheet, BOOL (* pElectEncoder)(TCHAR* pDestBuf, int BufSize, LPCTSTR szKey, CElectItem* pItem, int Number), void (* ProgressRoutine)(int nCount, int nProcessed, void* lpData), void* lpData) {
  CWaitCursor wc;
  if ( pElections->m_Territories.GetSize() <= 0 ) {
    return false;
  }
  CTerritory* pTerritiry = (CTerritory*)pElections->m_Territories.GetAt(0);
  if ( NULL==pTerritiry ) {
    return false;
  }
  COOCalcWrapper ocw;

  if ( false==ocw.Load(szXLS, true) ) {
    return false;
  }
  
  HRESULT hRes;
  CComVariant cvRet;
  CArray <KeyCell, KeyCell> CommonKeys;
  CArray <KeyCell, KeyCell> Keys;

  CString szCell, szValue;
  int nItems   = pElections->CalcTotalItems();
  int nCurItem = 0;

  TCHAR  buf[1024];
  POINT  begHdr;
  POINT  endHdr;
  int    HdrFound  = 0;
  int    OffsetRow = 0;

  int    MinTRow   = 10000, MaxTRow   = 0;
  int    MinTCol   = 10000, MaxTCol   = 0;

  int nSheet = 0;

  for( int row = 0; row < 30; row++ ) {
    for( int col = 0; col < 20; col++ ) {
      hRes = ocw.GetCell(nSheet, row, col, &cvRet);
      if ( FAILED(hRes) ) {
        return false;
      }
      IDispatch* pCell = cvRet.pdispVal;
      szValue = ocw.GetCellString(pCell);
      int nFind = 0;
      if ( (nFind = DBFind(szValue, _T("!ÏÇ!"))) >= 0 ) {
        begHdr.x = col; begHdr.y = row; HdrFound = 1;
        ReplaceIgnoreCase(szValue, _T("!ÏÇ!"), _T(""));
        ocw.SetCellString(pCell, szValue);
      }
      else if ( DBFind(szValue, _T("!ÊÇ!")) >= 0 ) {
        endHdr.x = col; endHdr.y = row; HdrFound++;
        ReplaceIgnoreCase(szValue, _T("!ÊÇ!"), _T(""));
        ocw.SetCellString(pCell, szValue);
      }
      else {
        LPCSTR szKW = FindKW(szValue, g_CommonKW);
        if ( szKW ) {
          CommonKeys.Add( KeyCell(row, col, szKW, szValue) );
        }
        else {
          int nFrom = 0;
          while ( true ) {
            CString szKeyWord  = GetKeyWord(szValue, nFrom);
            if ( szKeyWord.IsEmpty() ) {
              break;
            }
            if ( row < MinTRow ) { MinTRow = row; }
            if ( row > MaxTRow ) { MaxTRow = row; }
            if ( col < MinTCol ) { MinTCol = col; }
            if ( col > MaxTCol ) { MaxTCol = col; }
            Keys.Add( KeyCell(row, col, szKeyWord, szValue) );
          }
        }
      }
    }
  }
  if ( HdrFound < 2 ) {
    return false;
  }
  int HdrRows = endHdr.y - begHdr.y +1;
  int TabRows = MaxTRow  - MinTRow +1;
  CString szFrom, szTo;

  if ( CommonKeys.GetSize()>0 && Keys.GetSize() >0 ) {
    hRes = ocw.GetSheet(nSheet, &cvRet);
    IDispatch* pSheet = cvRet.pdispVal;

    int nCurSheet = 0;
    hRes = ocw.GetSheet(nCurSheet, &cvRet);
    if ( FAILED(hRes) ) {
      return false;
    }
    IDispatch* pCurSheet = cvRet.pdispVal;

    for( int i(0); i < pElections->m_Territories.GetSize(); i++ ) {
      CRect rSrc(begHdr.x, begHdr.y          , endHdr.x, endHdr.y          );
      CRect rDst(begHdr.x, begHdr.y+OffsetRow, endHdr.x, endHdr.y+OffsetRow);
      szFrom.Format(_T("%s:%s"), GetCellName(begHdr.y           , begHdr.x), GetCellName(endHdr.y          , endHdr.x));
      szTo  .Format(_T("%s:%s"), GetCellName(begHdr.y+OffsetRow , begHdr.x), GetCellName(endHdr.y+OffsetRow, endHdr.x));
      //ocw.CopyCells(pSheet, rSrc, pCurSheet, rDst); // CopyOOCells(dispSheet, rSrc, dispCurSheet, rDst);
      ocw.CopyCells(nSheet, rSrc, nCurSheet, rDst); // CopyOOCells(dispSheet, rSrc, dispCurSheet, rDst);
      if ( fMultiSheet ) {
        ocw.CopyRowHeigh(nSheet, nCurSheet, begHdr.y, begHdr.y+OffsetRow, HdrRows);
      }
      // CopyOORowHeigh(dispSheet, dispCurSheet, begHdr.y, begHdr.y+OffsetRow, HdrRows);
      // // CopyColWidth(pSheet, pCurSheet, begHdr.x, endHdr.x);
      CTerritory* pTerritory = (CTerritory*)pElections->m_Territories.GetAt(i);
      int kcIndex = GetKeyCellIndex(CommonKeys, "!Òåðèòîð³ÿ!");
      if ( kcIndex >= 0 ) {
        KeyCell kc = CommonKeys.GetAt(kcIndex);
        CString szValue = kc.szValue;
        ReplaceIgnoreCase(szValue, _T("!Òåðèòîð³ÿ!"), pTerritory->m_szTerritory);
        //SetCellValue(dispCurSheet, kc.row+OffsetRow, kc.col, szValue);
        ocw.SetCellValue(pCurSheet, kc.row+OffsetRow, kc.col, szValue);
      }
      kcIndex = GetKeyCellIndex(CommonKeys, "!ïåð³îä!");
      if ( kcIndex >= 0 ) {
        KeyCell kc = CommonKeys.GetAt(kcIndex);
        CString szValue = kc.szValue;
        ReplaceIgnoreCase(szValue, _T("!ïåð³îä!"), pElections->m_szPeriod);
        //SetCellValue(dispCurSheet, kc.row+OffsetRow, kc.col, szValue);
        ocw.SetCellValue(pCurSheet, kc.row+OffsetRow, kc.col, szValue);
      }
      for( int i(0); i < pTerritory->m_array.GetSize(); i++ ) {
        nCurItem++;
        if ( ProgressRoutine ) {
          ProgressRoutine(nItems, nCurItem, lpData);
        }
        CElectItem* pItem = (CElectItem*)pTerritory->m_array.GetAt(i);
        int cRow = MinTRow+OffsetRow;
        int cCol = MinTCol;

        CRect rSrc(MinTCol, MinTRow, MaxTCol, MaxTRow);
        CRect rDst(MinTCol, cRow, MaxTCol, cRow);
        
        szFrom.Format(_T("%s:%s"), GetCellName(MinTRow, MinTCol), GetCellName(MaxTRow, MaxTCol));
        szTo  .Format(_T("%s:%s"), GetCellName(cRow, MinTCol),    GetCellName(cRow    , MaxTCol));
        ocw.CopyCells(nSheet, rSrc, nCurSheet, rDst); // CopyOOCells(dispSheet, rSrc, dispCurSheet, rDst);
        ocw.CopyRowHeigh(nSheet, nCurSheet, MinTRow, MaxTRow, cRow);
        // CopyOORowHeigh(dispSheet, dispCurSheet, MinTRow, MaxTRow, cRow);
        for( int k(0); k < Keys.GetSize(); k++ ) {
          KeyCell kc = Keys.GetAt(k);
          szCell  = GetCellName(cRow, kc.col);
          CString szCellValue = kc.szValue;
          CString szKeyWord, szKey, szValue;
          while ( true ) {
            int nFrom = 0;
            szKeyWord = GetKeyWord(szCellValue, nFrom);
            if ( szKeyWord.IsEmpty() ) {
              break;
            }
            szKey   = Trim(szKeyWord.Mid(1, szKeyWord.GetLength()-2));
            pElectEncoder(buf, 1024, szKey, pItem, i+1);
            ReplaceIgnoreCase(szCellValue, szKeyWord, buf);
            // SetCellValue(dispCurSheet, cRow, kc.col, szCellValue);
            ocw.SetCellValue(pCurSheet, cRow, kc.col, szCellValue);
          }
        }
        OffsetRow += TabRows;
      } // for( int i(0); i < pTerritory->m_array.GetSize(); i++ )
      OffsetRow++;
      // System date
      pElectEncoder(buf, 1024, "ÑÄ", NULL, 0);
      // SetCellValue(dispCurSheet, OffsetRow+HdrRows, 1, buf);
      ocw.SetCellValue(pCurSheet, OffsetRow+HdrRows, 1, buf);
      if ( fMultiSheet ) {
        OffsetRow = 0;
        if ( ++nCurSheet < pElections->m_Territories.GetSize() ) {
          ocw.GetNextSheet(nCurSheet, &cvRet);
          pCurSheet = cvRet.pdispVal;
        }
      }
      else {
        OffsetRow += HdrRows + 1;
      }
    }
    /*
    if ( dispCurSheet == dispSheet ) {
      dispCurSheet.p = NULL;
    }
    */
  }
  // http://www.oooforum.org/forum/viewtopic.phtml?t=22048
  // http://www.oooforum.org/forum/viewtopic.phtml?t=67090&highlight=
  // http://www.biostatisticien.eu/textes/saisie/AndrewMacro.pdf
  // http://www.oooforum.org/forum/viewtopic.phtml?p=50063

  // Show(dispDoc, true);
  ocw.Show(true);
  return true;
}
