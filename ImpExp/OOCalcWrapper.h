#pragma once

struct CellInfo {
};

//
// OOCalcWrapper.h
//
class COOCalcWrapper {
public:
  COOCalcWrapper();
  COOCalcWrapper(LPCTSTR szFilename);
  ~COOCalcWrapper();
// Data members:
public:
  HRESULT     hRes;
  IDispatch*  m_pDispFactory;
  IDispatch*  m_pDispDesk;
  IDispatch*  m_pDispDoc;
  IDispatch*  m_pSheets;
  //_variant_t  Sheets;
protected:
  void  Initialize();
public:
  CString     GetCellName(int row, int col);
  CString     GetRangeName(const RECT* pRect);

  HRESULT     GetUnoStruct(OLECHAR* sStructName, CComPtr<IDispatch>& pdispResult);
  void        Show(BOOL fShow);
  BOOL        Load(LPCTSTR szFilename, BOOL fHidden);
  HRESULT     GetSheet(int nIndex, CComVariant* pRet);
  int         GetSheetCount();
  HRESULT     GetNextSheet(int nIndex, CComVariant* pRet);
  HRESULT     GetCell(IDispatch* pSheet, int nRow, int nCol, CComVariant* pRet);
  HRESULT     GetCell(int nSheet, int nRow, int nCol, CComVariant* pRet);
  CString     GetCellString(IDispatch* pCell);
  HRESULT     SetCellString(IDispatch* pCell, LPCTSTR szValue);
  HRESULT     SetCellValue(IDispatch* pSheet, int nRow, int nCol, LPCTSTR szValue);
  CString     GetCellString(int nSheet, int nRow, int nCol);
  BOOL        GetRange(int nSheet, int nMinRow, int nMinCol, int nMaxRow, int nMaxCol,
                       LPCSTR szValue1, LPCSTR szValue2, 
                       int& Row1, int& Col1, int& Row2, int& Col2);
  void        CopyCells(IDispatch* pSheetFrom, const CRect& rSrc, IDispatch* pSheetTo, const CRect& rDst);
  void        CopyCells(int nSheetFrom, const CRect& rSrc, int nSheetTo, const CRect& rDst);
  void        CopyRowHeigh(int nSrcSheet, int nDstSheet, int rFrom, int rTo, int Row);
};