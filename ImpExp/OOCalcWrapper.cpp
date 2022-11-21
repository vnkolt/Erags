//
// OOCalcWrapper.cpp
//
#include "stdafx.h"
#include "OOCalcWrapper.h"

CComModule _Module;
BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HRESULT ExecuteFunc( IDispatch* idispUnoObject, 
					 OLECHAR* sFuncName, 
					 CComVariant* params, 
					 unsigned int count, 
					 CComVariant* pResult )
{
	if( !idispUnoObject )
		return E_FAIL;

	DISPID id;
	HRESULT hr = idispUnoObject->GetIDsOfNames( IID_NULL, &sFuncName, 1, LOCALE_USER_DEFAULT, &id);
	if( !SUCCEEDED( hr ) ) return hr;

	DISPPARAMS dispparams= { params, 0, count, 0};

	// DEBUG
	EXCEPINFO myInfo;
	return idispUnoObject->Invoke( id, IID_NULL,LOCALE_USER_DEFAULT, DISPATCH_METHOD, 
                    &dispparams, pResult, &myInfo, 0);
}

HRESULT GetIDispByFunc(IDispatch* idispUnoObject, 
                       OLECHAR* sFuncName, 
                       CComVariant* params,
					  	         unsigned int count,
					  	         CComPtr<IDispatch>& pdispResult
                      ) {
	if( !idispUnoObject )
		return E_FAIL;

	CComVariant result;
	HRESULT hr = ExecuteFunc( idispUnoObject, sFuncName, params, count, &result );
	if( !SUCCEEDED( hr ) ) return hr;

	if( result.vt != VT_DISPATCH || result.pdispVal == NULL )
		return hr;

	pdispResult = CComPtr<IDispatch>( result.pdispVal );

	return S_OK;
}

HRESULT PutPropertiesToIDisp(IDispatch* pdispObject,
                             OLECHAR** sMemberNames,
                             CComVariant* pVariant,
                             unsigned int count )
{
  for( unsigned int ind = 0; ind < count; ind++ ) {
    DISPID id;
    HRESULT hr = pdispObject->GetIDsOfNames( IID_NULL, &sMemberNames[ind], 1, LOCALE_USER_DEFAULT, &id );
    if( !SUCCEEDED( hr ) ) return hr;
    hr = CComDispatchDriver::PutProperty( pdispObject, id, &pVariant[ind] );
    if( !SUCCEEDED( hr ) ) return hr;
  }
  return S_OK;
}

COOCalcWrapper::COOCalcWrapper() {
  Initialize();
}
COOCalcWrapper::COOCalcWrapper(LPCTSTR szFilename) {
  Initialize();
  Load(szFilename, true);
}
void COOCalcWrapper::Initialize() {
  hRes = S_OK;
  m_pDispFactory = m_pDispDesk = m_pDispDoc = m_pSheets = NULL;
  //_Module.Init( ObjectMap, GetModuleHandle( NULL));
}


COOCalcWrapper::~COOCalcWrapper() {
/*
  if ( m_pSheets ) {
    m_pSheets->Release();
  }
*/
  //_Module.Term();
}


HRESULT COOCalcWrapper::GetUnoStruct( OLECHAR* sStructName, CComPtr<IDispatch>& pdispResult) {
  return GetIDispByFunc(m_pDispFactory, L"Bridge_GetStruct", &CComVariant(sStructName), 1, pdispResult );
}

void COOCalcWrapper::Show(BOOL fShow) {
  CComVariant cvArg, cvRet;
  HRESULT hRes = ExecuteFunc(m_pDispDoc, L"getCurrentController", NULL, 0, &cvRet);
  if ( FAILED(hRes) ) return;

  IDispatch*  pIDocCtrl = cvRet.pdispVal;
  hRes = ExecuteFunc(pIDocCtrl, L"getFrame", NULL, 0, &cvRet);
  if ( FAILED(hRes) ) return;

  IDispatch* pIDocFrame = cvRet.pdispVal;
  hRes = ExecuteFunc(pIDocFrame, L"getContainerWindow", NULL, 0, &cvRet);
  if ( FAILED(hRes) ) return;

  IDispatch* pIDocWindow = cvRet.pdispVal;
  cvArg.vt = VT_BOOL;
  cvArg.boolVal = fShow ? VARIANT_TRUE : VARIANT_FALSE;
  ExecuteFunc(pIDocWindow, L"setVisible", &cvArg, 1, &cvRet);
}

BOOL COOCalcWrapper::Load(LPCTSTR szFilename, BOOL fHidden) {

	IDispatchPtr starManager;
	hRes = starManager.CreateInstance(_T("com.sun.star.ServiceManager"));
  if ( FAILED(hRes) ) {
    return false;
  }
  m_pDispFactory = starManager;

	SAFEARRAY* pPropVals = SafeArrayCreateVector(VT_DISPATCH, 0, 1);

  CComPtr<IDispatch> pdispPropVal;
  hRes = GetUnoStruct( L"com.sun.star.beans.PropertyValue", pdispPropVal);

  OLECHAR*  sPropMemberNames[2] = { L"Name", L"Value" };
  CComVariant pPropVar[2];
  pPropVar[0] = CComBSTR("Hidden");
  pPropVar[1].vt = VT_BOOL;
  pPropVar[1].boolVal = fHidden ? VARIANT_TRUE : VARIANT_FALSE;
  hRes = PutPropertiesToIDisp( pdispPropVal, sPropMemberNames, pPropVar, 2 );
/*
  if( !SUCCEEDED( hRes ) ) return hRes;
*/
  _variant_t varP1(L"com.sun.star.frame.Desktop");
	_variant_t varRet;
  CComVariant  cvRet;

  hRes = ExecuteFunc(m_pDispFactory,
                     L"createInstance",
                     &CComVariant(L"com.sun.star.frame.Desktop"), 1, &cvRet);

  if ( FAILED(hRes) ) {
    return false;
  }
  CString szURL;
  szURL.Format(_T("file:///%s"), szFilename);
  szURL.Replace('\\', '/');

  m_pDispDesk = cvRet.pdispVal;

  CComVariant args[4];
  CComBSTR bstrFilename(szURL);

  long ix = 0;
  SafeArrayPutElement(pPropVals, &ix, pdispPropVal);

  args[3] = _variant_t(bstrFilename);/* _variant_t(L"private:factory/swriter");*/
	args[2] = _variant_t(L"Test");// _variant_t(L"file://c:/2.odt");  // _variant_t(L"Test");
	args[1] = _variant_t((long) 40);
	args[0].vt= VT_ARRAY | VT_DISPATCH;
	args[0].parray= pPropVals;
	//hRes = dispDesk.InvokeN(L"loadComponentFromURL", args, 4, &varRet);

  hRes = ExecuteFunc(m_pDispDesk, L"loadComponentFromURL", args, 4, &cvRet);

  if ( FAILED(hRes) ) {
    return false;
  }

  m_pDispDoc = cvRet.pdispVal;
  hRes = ExecuteFunc(m_pDispDoc, L"getSheets", args, 0, &cvRet);
  if ( FAILED(hRes) ) {
    return false;
  }
  m_pSheets = cvRet.pdispVal;
  m_pSheets->AddRef();

  return true;
}

HRESULT COOCalcWrapper::GetSheet(int nIndex, CComVariant* pRet) {
  return ExecuteFunc(m_pSheets, L"getByIndex", &CComVariant(nIndex), 1, pRet);
}
int COOCalcWrapper::GetSheetCount() {
  CComVariant cvRet;
  hRes = ExecuteFunc(m_pSheets, L"getCount", NULL, 0, &cvRet);
  if ( FAILED(hRes) ) {
    return 0;
  }
  return cvRet.iVal;
}
HRESULT COOCalcWrapper::GetNextSheet(int nIndex, CComVariant* pRet) {
  int nSheets = GetSheetCount();
  if ( nIndex >= nSheets ) {
    CComVariant args[2];
    CString szSheetName;
    szSheetName.Format(_T("Лист %d"), nSheets+1);
    args[0].vt = VT_I2;
    args[0].intVal = nSheets;
    args[1] = CComBSTR(szSheetName);
    hRes = ExecuteFunc(m_pSheets, L"insertNewByName", args, 2, pRet);
    if ( FAILED(hRes) ) {
      return hRes;
    }
    nIndex = nSheets;
  }
  return GetSheet(nIndex, pRet);
}

HRESULT COOCalcWrapper::GetCell(IDispatch* pSheet, int nRow, int nCol, CComVariant* pRet) {
  CComVariant args[2];
  args[0].vt = VT_I4;
  args[0].intVal = nRow;
  args[1].vt = VT_I4;
  args[1].intVal = nCol;
  return ExecuteFunc(pSheet, L"getCellByPosition", args, 2, pRet);
}
HRESULT COOCalcWrapper::GetCell(int nSheet, int nRow, int nCol, CComVariant* pRet) {
  hRes = GetSheet(nSheet, pRet);
  if ( FAILED(hRes) ) return hRes;
  IDispatch* pSheet = pRet->pdispVal;
  return GetCell(pSheet, nRow, nCol, pRet);
}
CString COOCalcWrapper::GetCellString(IDispatch* pCell) {
  CString s;
  CComVariant cvRet;
  hRes = ExecuteFunc(pCell, L"getType", NULL, 0, &cvRet);
  if ( FAILED(hRes) ) {
    return s;
  }
  if ( 2==cvRet.intVal ) { // text
    hRes = ExecuteFunc(pCell, L"getString", NULL, 0, &cvRet);
    USES_CONVERSION;
    s = OLE2T(cvRet.bstrVal);
  }
  return s;
}
HRESULT COOCalcWrapper::SetCellString(IDispatch* pCell, LPCTSTR szValue) {
  CComVariant cvPar, cvRet;
  cvPar.vt = VT_BSTR;
  cvPar.bstrVal = CComBSTR(szValue);
  return ExecuteFunc(pCell, L"setString", &cvPar, 1, &cvRet);
}
HRESULT COOCalcWrapper::SetCellValue(IDispatch* pSheet, int nRow, int nCol, LPCTSTR szValue) {
  CComVariant cvPar, cvRet;
  hRes = GetCell(pSheet, nRow, nCol, &cvRet);
  if ( FAILED(hRes) ) {
    return hRes;
  }
  IDispatch* pCell = cvRet.pdispVal;
  return SetCellString(pCell, szValue);
}
CString COOCalcWrapper::GetCellString(int nSheet, int nRow, int nCol) {
  CString s;
  CComVariant cvRet;
  hRes = GetCell(nSheet, nRow, nCol, &cvRet);
  if ( FAILED(hRes) ) {
    return s;
  }
  IDispatch* pCell = cvRet.pdispVal;
  hRes = ExecuteFunc(pCell, L"getType", NULL, 0, &cvRet);
  if ( FAILED(hRes) ) {
    return s;
  }
  if ( 2==cvRet.intVal ) { // text
    hRes = ExecuteFunc(pCell, L"getString", NULL, 0, &cvRet);
    USES_CONVERSION;
    s = OLE2T(cvRet.bstrVal);
  }
  return s;
}

BOOL COOCalcWrapper::GetRange(int nSheet, int nMinRow, int nMinCol, int nMaxRow, int nMaxCol,
                              LPCSTR szValue1, LPCSTR szValue2,
                              int& Row1, int& Col1, int& Row2, int& Col2) {
  _variant_t arg;
  _variant_t varRet;
  CComDispatchDriver dispSheets(m_pSheets);
  hRes = dispSheets.InvokeN(L"getByIndex", &arg, 1, &varRet);
  if ( FAILED(hRes) ) {
    return false;
  }
  CComDispatchDriver dispSheet(varRet.pdispVal);
  varRet.Clear();

  for( int row = nMinRow; row <= nMaxRow; row++ ) {
    for( int col = nMinCol; col <= nMaxCol; col++ ) {
      _variant_t args[2];
      args[0].vt = VT_I4;
      args[0].intVal = row;
      args[1].vt = VT_I4;
      args[1].intVal = col;
      hRes = dispSheet.InvokeN(L"getCellByPosition", args, 2, &varRet);
      if ( FAILED(hRes) ) {
        return false;
      }
      CComDispatchDriver dispCell(varRet.pdispVal);
      varRet.Clear();
      hRes = dispCell.Invoke0(L"getType", &varRet);
      switch( varRet.intVal ) {
        case 0: // empty value
          break;
        case 1: // number
          break;
        case 2: // text
          hRes = dispCell.Invoke0(L"getString", &varRet);
          {
            CString szValue;
            USES_CONVERSION;
            szValue = OLE2T(varRet.bstrVal);
            if ( szValue==szValue1 ) {
              Row1 = row;
              Col1 = col;
            }
            if ( szValue==szValue2 ) {
              Row2 = row;
              Col2 = col;
            }
          }
          break;
        case 3: // formula
          break;
      }
    }
  }
  return true;
}

CString COOCalcWrapper::GetCellName(int row, int col) {
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
CString COOCalcWrapper::GetRangeName(const RECT* pRect) {
  CString s;
  s.Format(_T("%s:%s"), GetCellName(pRect->top, pRect->left), GetCellName(pRect->bottom, pRect->right));
  return s;
}

void COOCalcWrapper::CopyCells(IDispatch* pSrcSheet, const CRect& rSrc, IDispatch* pDstSheet, const CRect& rDst) {
  CComVariant args[2], cvRet, oSrcCells, oDstCell;
  args[0] = CComBSTR(GetRangeName(&rSrc));

  hRes = ExecuteFunc(pSrcSheet, L"getCellRangeByName", args, 1, &cvRet);
  if ( FAILED(hRes) ) return;
  IDispatch* pSrcRange = cvRet.pdispVal;

  args[0].vt = VT_I4;
  args[0].intVal = rDst.top; // row;
  args[1].vt = VT_I4;
  args[1].intVal = rDst.left;// col;

  hRes = ExecuteFunc(pDstSheet, L"getCellByPosition", args, 2, &cvRet);
  if ( FAILED(hRes) ) return;
  IDispatch* pDispCells = cvRet.pdispVal;

  hRes = ExecuteFunc(pDispCells, L"getCellAddress", NULL, 0, &oDstCell);
  if ( FAILED(hRes) ) return;

  hRes = ExecuteFunc(pSrcRange, L"getRangeAddress", NULL, 0, &oSrcCells);
  if ( FAILED(hRes) ) return;

  args[0] = oSrcCells;
  args[1] = oDstCell;
  hRes = ExecuteFunc(pDstSheet, L"CopyRange", args, 2, &cvRet);
}
void COOCalcWrapper::CopyCells(int nSheetFrom, const CRect& rSrc, int nSheetTo, const CRect& rDst) {
  if ( nSheetFrom==nSheetTo && rSrc==rDst ) {
    return;
  }
  CComVariant cvRet;
  hRes = GetSheet(nSheetFrom, &cvRet);
  if ( FAILED(hRes) ) return;
  IDispatch* pSrcSheet = cvRet.pdispVal;

  hRes = GetSheet(nSheetTo, &cvRet);
  if ( FAILED(hRes) ) return;
  IDispatch* pDstSheet = cvRet.pdispVal;

  CopyCells(pSrcSheet, rSrc, pDstSheet, rDst);
}

void COOCalcWrapper::CopyRowHeigh(int nSrcSheet, int nDstSheet, int rFrom, int rTo, int Row) {
  if ( nSrcSheet==nDstSheet && rFrom==Row ) {
    return;
  }

  CComVariant cvRet;
  hRes = GetSheet(nSrcSheet, &cvRet);
  if ( FAILED(hRes) ) return;
  IDispatch* pSrcSheet = cvRet.pdispVal;

  hRes = GetSheet(nDstSheet, &cvRet);
  if ( FAILED(hRes) ) return;
  IDispatch* pDstSheet = cvRet.pdispVal;

  hRes = ExecuteFunc(pSrcSheet, L"GetRows", NULL, 0, &cvRet);
  if ( FAILED(hRes) ) return;
  IDispatch* pSrcRows = cvRet.pdispVal;

  hRes = ExecuteFunc(pDstSheet, L"GetRows", NULL, 0, &cvRet);
  if ( FAILED(hRes) ) return;
  IDispatch* pDstRows = cvRet.pdispVal;

  int Rows = rTo - rFrom + 1;

  for( int r(0); r < Rows; r++ ) {
    CComVariant args[2];
    try {
      hRes = ExecuteFunc(pSrcRows, L"getByIndex", &CComVariant((long)(r+rFrom)), 1, &cvRet);
      if ( FAILED(hRes) ) break;
      IDispatch* pSrcRow = cvRet.pdispVal;

      hRes = ExecuteFunc(pDstRows, L"getByIndex", &CComVariant((long)(r+Row)), 1, &cvRet);
      if ( FAILED(hRes) ) break;
      IDispatch* pDstRow = cvRet.pdispVal;
      args[0] = L"Height";

      hRes = ExecuteFunc(pSrcRow, L"getPropertyValue", args, 1, &cvRet);
      if ( FAILED(hRes) ) break;
      args[1] = args[0];
      args[0] = cvRet;
      hRes = ExecuteFunc(pDstRow, L"setPropertyValue", args, 2, &cvRet);
      if ( FAILED(hRes) ) break;
    }
    catch (_com_error &e) { 
      // ReportComError(e); 
    } 
  }

}
