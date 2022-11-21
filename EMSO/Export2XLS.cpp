// Export2XLS.cpp : Defines the initialization routines for the DLL.
//
#include "stdafx.h"
#include "EMSO.h"

#include "..\Common\Export.h"
#include "..\Common\CyrString.h"

#include <Atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning (disable:4192) 
#pragma warning (disable:4146)

#import "..\MSO\mso9.dll"    no_namespace rename("DocumentProperties", "DocumentPropertiesXL")    
#import "..\MSO\vbe6ext.olb" no_namespace    
#import "..\MSO\excel9.olb"  rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") no_dual_interfaces 

void ReportComError(_com_error &e) { 
/*
    _tprintf(_T("Oops - hit an error!\n")); 
    _tprintf(_T("\a\tCode = %08lx\n"), e.Error()); 
    _tprintf(_T("\a\tCode meaning = %s\n"), e.ErrorMessage()); 
    _bstr_t bstrSource(e.Source()); 
    _bstr_t bstrDescription(e.Description()); 
    _tprintf(_T("\a\tSource = %s\n"), (LPCTSTR) bstrSource); 
    _tprintf(_T("\a\tDescription = %s\n"), (LPCTSTR) bstrDescription); 
*/
} 


BSTR GetCellName(unsigned row, unsigned col) {
  CString s, szCol;
  if ( col <= 26 ) {
    szCol.Format("%c", 'A' + col);
  }
  else {
    szCol.Format("%c%c", 'A' + col%26, 'A'+ col/26);
  }
  s.Format("%s%d", szCol, row+1);
  return A2WBSTR(s);
}

using namespace Excel;
_ApplicationPtr g_pXL    = NULL;
WorkbooksPtr    g_pBooks = NULL;
_WorkbookPtr    g_pBook  = NULL;
_WorksheetPtr   g_pSheet = NULL;
CPtrArray       g_Sheets;


_WorksheetPtr FindSheet(LPCTSTR szSheetName)  {
  for( int i(0); i < g_Sheets.GetSize(); i++ ) {
    //_WorksheetPtr pSheet = (_WorksheetPtr)g_Sheets.GetAt(i);
  }
  return NULL;
}

__declspec(dllexport) BOOL WINAPI BeginExp2XLS() {
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  BOOL fRet = true;
  try { 
    g_pXL.CreateInstance(L"Excel.Application"); 
    g_pXL->Visible = VARIANT_TRUE;
    g_pBooks = g_pXL->Workbooks;
    g_pBook  = g_pBooks->Add((long)xlWorksheet);
    g_pSheet = g_pXL->ActiveSheet;
  }
  catch(_com_error &e) { 
    fRet = false;
    ReportComError(e); 
  }
  return fRet;

}

__declspec(dllexport) BOOL WINAPI Exp2XLS(LPCTSTR szSheetName, CStringArray* pHeader, CExportTable* pET) {
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  if ( NULL==g_pXL || NULL==g_pBooks || NULL==g_pBook || NULL==g_pSheet ) {
    return false;
  }
  for( int i(0); i < pHeader->GetSize(); i++ ) {
    CString s = pHeader->GetAt(i);
    CString szRange = GetSentence(s, "[", "]");
    CString szValue = GetSentence(s, "<", ">");
  }
  return true;
}
/*
  CExportTable et(3);

  et.SetColumn(0, VT_I2,   _T("Int1"),  _T("Целое 1"));
  et.SetColumn(1, VT_DATE, _T("Date2"), _T("Дата 2"));
  et.SetColumn(2, VT_BSTR, _T("BStr3"), _T("Строка 3"));
  et.AddRow();
  et.AddRow();
  et.AddRow();
  for( int r(0); r < et.GetRowCount(); r++ ) {
    COleDateTime dt = COleDateTime::GetCurrentTime() + COleDateTimeSpan(r+1, 0, 0, 0);
    CString s;
    s.Format(_T("Строка %d"), r+1);
    et.SetData(0, r, COleVariant((short)(r+1), VT_I2));
    et.SetData(1, r, dt);
    et.SetData(2, r, COleVariant(s));
  }

  try { 
    pXL.CreateInstance(L"Excel.Application"); 
    pXL->Visible = VARIANT_TRUE;
    WorkbooksPtr pBooks = pXL->Workbooks;
    _WorkbookPtr pBook  = pBooks->Add((long)xlWorksheet);
    _WorksheetPtr pSheet = pXL->ActiveSheet;

    pSheet->Name = "Первый лист";
    for( int c(0); c < 3; c++ ) {
      //CString szColumnName = et.GetColumnAltName(c);
      BSTR bstrCellName = GetCellName(0,c);
      BSTR bstrColumnName  = A2WBSTR(et.GetColumnAltName(c));
      pSheet->Range[bstrCellName]->Value = bstrColumnName;
      pSheet->Range[bstrCellName]->Font->Bold = VARIANT_TRUE;
      ::SysFreeString(bstrCellName);
      ::SysFreeString(bstrColumnName);
      for( int r(0); r < et.GetRowCount(); r++ ) {
        COleVariant v = et.GetCellData(c, r);
        bstrCellName = GetCellName(r+1,c);
        pSheet->Range[bstrCellName]->Value = v;
        ::SysFreeString(bstrCellName);
      }
    }

    pBook->Saved = VARIANT_TRUE;
    pXL->Quit(); 
    //pSheet->Range[_variant_t((short)1, VT_I2), _variant_t((short)1,VT_I2)]->Value = "Company A";
    //for( int r(0); r < 3; r++ ) {
    //}
  }
  catch(_com_error &e) { 
    dump_com_error(e); 
  } 
  return 0;
 */ 

__declspec(dllexport) void WINAPI EndExp2XLS(CStringArray* pHeader, CExportTable* pET) {
  return;
}
