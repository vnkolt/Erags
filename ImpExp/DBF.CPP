// DBF.cpp : implementation file
//

#include "stdafx.h"
#include "DBF.h"

#include "ScriptObject.h"
#include "SafeArrayHelper.h"

#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"

#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CDBFField::Create(LPCTSTR szFName, UCHAR ucFType, BYTE bFLen, BYTE bFDec){
  memset(this, 0, sizeof(CDBFField));
  lstrcpyn((LPTSTR)fieldname, szFName, 11);
  ty = ucFType;
  fl = bFLen;
  nd = bFDec;
}

CDBF::CDBF(){
}
CDBF::~CDBF(){
  Close();
}
void CDBF::Close(){
  if(cFile.m_hFile!=(UINT)CFile::hFileNull){
    long lRecs, lLOF;
    lLOF = cFile.GetLength() ;
    lRecs = (lLOF - dbfHeader.hl) / dbfHeader.rl;
    if(lRecs != dbfHeader.nRecs){
      dbfHeader.nRecs = lRecs;
      cFile.SeekToBegin();
      cFile.Write(&dbfHeader, sizeof(dbfHeader));
    }
    cFile.Close();
  }
}

BOOL CDBF::Create(LPCTSTR lpszFileName, int nFields, CDBFField* dbfFields) {
  if(cFile.Open(lpszFileName, CFile::modeCreate | CFile::modeWrite)) {
    int i;
    UCHAR c;
    COleDateTime dt;
    dt = COleDateTime::GetCurrentTime();

    memset(&dbfHeader, 0, sizeof(dbfHeader));

    dbfHeader.id = 3;
    dbfHeader.yy = (BYTE)(dt.GetYear() % 100);
    dbfHeader.mm = (BYTE)(dt.GetMonth());
    dbfHeader.dd = (BYTE)(dt.GetDay());
    dbfHeader.nRecs = 0;
    dbfHeader.hl = (SHORT)(nFields * sizeof(CDBFField) + sizeof(dbfHeader) + 1);
    dbfHeader.rl = 1;

    for(i=0; i < nFields; i++)
      dbfHeader.rl += (SHORT)(dbfFields[i].fl);

    cFile.Write(&dbfHeader, sizeof(dbfHeader));

    for(i=0; i < nFields; i++)
      cFile.Write(&dbfFields[i], sizeof(CDBFField));

    c = 0x0D;
    cFile.Write(&c, 1);
    
    return true;
  }
  return false;
}

/*
  "D_FORM  ,D, 8,0,"
  "D_PERIOD,N, 4,0,"
  "C_OKPO  ,C, 8,0,"
  "REG     ,C,42,0,"
  "DIST    ,C,55,0,"
  "POL     ,N, 1,0,"
  "FULLNAME,C,30,0,"
  "NAME    ,C,15,0,"
  "FULLOT  ,C,20,0,"
  "TIN     ,C,10,0,"
  "D_ROG   ,D, 8,0,"
  "D_REEST ,D, 8,0 "

*/
BOOL CDBF::Create(LPCTSTR lpszFileName, LPCTSTR szFieldsInfo, char* pErrBuf) {
  CStringArray szTokens;
  CString szToken;
  int nTok = 0;
  for ( ;; ) {
    szToken = GetTok(szFieldsInfo, nTok++, " ,");
    if ( szToken.IsEmpty() ) {
      break;
    }
    szTokens.Add(szToken);
  }
  if ( szTokens.GetSize() == 0 ) {
    return false;
  }
  if ( szTokens.GetSize()%4 != 0 ) { // массив должен быть кратен 4
    return false;
  }


  CStringArray Names;  // Имена полей ("D_FORM", "D_PERIOD", etc)
  CByteArray   Types;  // Типы полей  ("C", "N", "D")
  CByteArray   Lens;   // Длины полей ( от 1 до 255)
  CByteArray   Decs;   // Кол-во десятичных точек
  int nFields = szTokens.GetSize() / 4;
  for( int i(0); i < nFields; i++ ) {
    CString sName, sType, sLen, sDec;
    sName = szTokens[i*4];      // NAME
    if ( sName.GetLength() > 11 ) {
      sprintf(pErrBuf, _T("Помилка в імені поля \"%s\": довжина імені поля не повинна бути більш за 11 символів."), sName);
      return false;
    }
    Names.Add(sName);
    sType = szTokens[i*4 + 1];      // TYPE
    if ( sType.GetLength() != 1 || (sType[0] != 'C' && sType[0] != 'D' && sType[0] != 'N') ) {
      sprintf(pErrBuf, _T("Неправильний тип поля \"%s\": тип поля може бути лише 'C', 'D' або 'N'."), sName);
      return false;
    }
    Types.Add( BYTE(sType.GetAt(0)) );
    sLen = szTokens[i*4 + 2];      // LEN
    int nLen = atoi(sLen);
    if ( nLen <= 0 || nLen > 255 ) {
      sprintf(pErrBuf, _T("Неправильна довжина поля \"%s\": довжина може бути від 1 до 255."), sName);
      return false;
    }
    Lens.Add((BYTE)nLen);
    sDec = szTokens[i*4 + 3];      // DECIMALS
    int nDec = atoi(sDec);
    if ( nDec < 0 || nDec > nLen ) {
      sprintf(pErrBuf, _T("Неправильна кількість цифр після коми для поля \"%s\": це число може бути від 0 до %d."), sName, sLen);
      return false;
    }
    if ( nDec > 0 && sType != _T("N") ) {
      sprintf(pErrBuf, _T("Помилка в полі %s: кількість цифр після коми може бути встановлена тільки для поля числовиго типу."), sName);
      return false;
    }
    Decs.Add((BYTE)nDec);
  }

  CDBFField* pFields = new CDBFField[nFields];
  for( i = 0; i < nFields; i++ ) {
    pFields[i].Create(Names[i], Types[i], Lens[i], Decs[i]);
  }

  BOOL fRet = Create(lpszFileName, nFields, pFields);

  delete pFields;

  return fRet;
}

BOOL CDBF::AddRec(CDBFField* pDBFFields, CString* psFields, int nFields) {
  BOOL fRet = false;
  if(cFile.m_hFile!=(UINT)CFile::hFileNull){
    CString sRec = _T(" "); // delete flag
    for(int i(0); i < nFields; i++){
      CString sFld, sEmpty(' ', pDBFFields[i].fl);
      int iLen = psFields[i].GetLength();
      if(iLen >= pDBFFields[i].fl)
        sFld = psFields[i].Left(pDBFFields[i].fl);
      else
        sFld = psFields[i] + sEmpty.Left(pDBFFields[i].fl - iLen);
      sRec += sFld;
    }
    cFile.SeekToEnd();
    cFile.Write(LPCTSTR(sRec), dbfHeader.rl);
    fRet = true;
  }
  return fRet;
}

BOOL CDBF::AddRec(LPCSTR szRecord) {
  BOOL fRet = false;
  int nLen = (int)dbfHeader.rl;
  char* pRecord = new char[nLen];
  memset(pRecord, ' ', nLen);
  if ( szRecord ) {
    int nMax = strlen(pRecord);
    if ( nMax > nLen ) {
      nMax = nLen;
    }
    memcpy(pRecord, szRecord, nMax);
  }
  cFile.SeekToEnd();
  cFile.Write(pRecord, dbfHeader.rl);
  delete pRecord;
  return fRet;
}

CString CDBF::MakeDBFDate(COleDateTime& odt){
  CString sRet;
  sRet = _T("        ");
  if(odt.m_status == COleDateTime::valid){
    sRet.Format(_T("%04u%02u%02u"),
                 odt.GetYear(),
                 odt.GetMonth(),
                 odt.GetDay() );
  }
  return sRet;
}

CString CDBF::MakeDBFCDate() {
  COleDateTime odt = COleDateTime::GetCurrentTime();
  return MakeDBFDate(odt);
}

//
//
//
CDBF*           g_pDBF       = NULL;
CScriptObject*  g_pScriptObj = NULL;

BOOL IsMethodPresent(LPCTSTR szName) {
	int nCount = g_pScriptObj->GetMethodsCount();
	for(int i(0); i < nCount; i++) {
		CString strFunc = g_pScriptObj->GetNameAt(i);
    if ( strFunc.CompareNoCase(szName)==0 ) {
      return true;
    }
	}
  return false;
}
_declspec(dllexport) BOOL WINAPI CreateDBF(CDaoRecordset* pSet, LPCSTR szOKPO, LPCSTR szDBFile, LPCTSTR szVBScript, char* pErrBuf/* 1024 bytes*/) {
  // ASSERT ( pError != NULL );
  if ( g_pDBF ) {
    delete g_pDBF;
  }
  if ( g_pScriptObj ) {
    delete g_pScriptObj;
  }
  if ( false==FileExists(szVBScript) ) {
    sprintf(pErrBuf, _T("Помилка: не існує файла \"%s\"."), szVBScript);
    return false;
  }

  g_pScriptObj = new CScriptObject();
  g_pScriptObj->SetLanguage(_T("VBScript"));

  BOOL fOk = true;

  if ( false==g_pScriptObj->LoadScript(szVBScript) ) {
    sprintf(pErrBuf, _T("Помилка під час спроби завантажити код із файла \"%s\":\n%s"),
            szVBScript, g_pScriptObj->GetErrorString()
           );
    fOk = false;
  }
  else if ( false==IsMethodPresent(_T("Initialize")) ) {
    sprintf(pErrBuf, _T("Помилка: у файлі \"%s\" відсутня обов'язкова функція \"%s\"."), szVBScript, _T("Initialize"));
    fOk = false;
  }
  else if ( false==IsMethodPresent(_T("GetDBFFields")) ) {
    sprintf(pErrBuf, _T("Помилка: у файлі \"%s\" відсутня обов'язкова функція \"%s\"."), szVBScript, _T("GetDBFFields"));
    fOk = false;
  }
  else if ( false==IsMethodPresent(_T("OnRecord")) ) {
    sprintf(pErrBuf, _T("Помилка: у файлі \"%s\" відсутня обов'язкова функція \"%s\"."), szVBScript, _T("OnRecord"));
    fOk = false;
  }
  if ( false==fOk ) {
    delete g_pScriptObj;
    g_pScriptObj = NULL;
    return false;
  }
  CString szRSFieldNames;

  int nFields = pSet->GetFieldCount();
  for( int i(0); i < nFields; i++ ) {
    CDaoFieldInfo fi;
    pSet->GetFieldInfo(i, fi);
    if ( false==szRSFieldNames.IsEmpty() ) {
      szRSFieldNames += TCHAR(1);
    }
    szRSFieldNames += fi.m_strName;
  }

  _variant_t par1, par2;
  _variant_t varRet;

  CString    szDBFieldInfo;
  CSafeArrayHelper sfHelper;

  try {
    sfHelper.Create(VT_VARIANT, 1, 0, 2);	// VBS-function "Initialize" should receive 2 parameters

    par1 = _bstr_t(szRSFieldNames);
    par2 = _bstr_t(szOKPO);

    sfHelper.PutElement(0, (void*)&par1);	// parameter1 -> index 0
    sfHelper.PutElement(1, (void*)&par2);	// parameter1 -> index 0

    LPSAFEARRAY sa =  sfHelper.GetArray();

    if (g_pScriptObj->RunProcedure(_T("Initialize"), &sa, &varRet)) {
      szDBFieldInfo = (LPCTSTR)_bstr_t(varRet);
      if ( szDBFieldInfo.CompareNoCase(_T("Ok")) != 0 ) {
        sprintf(pErrBuf, _T("Помилка при спробі виконати функцію \"%s\" у файлі %s:\n%s"),
                szVBScript, _T("Initialize"), szDBFieldInfo);
        fOk = false;
      }
      else {
        sfHelper.Destroy();
        sfHelper.Create(VT_VARIANT, 1, 0, 0);	// VBS-function "GetDBFFields" has not parameters
        sa = sfHelper.GetArray();
        if (g_pScriptObj->RunProcedure(_T("GetDBFFields"), &sa, &varRet)) {
          szDBFieldInfo = (LPCTSTR)_bstr_t(varRet);
          if ( szDBFieldInfo.IsEmpty() ) {
            sprintf(pErrBuf, _T("Функція %s у файлі %s повинна повертати строку з інформацією про DBF-файл, що будується."),
                    _T("GetDBFFields"), szVBScript);
            fOk = false;
          }
        }
        else {
          sprintf(pErrBuf, _T("Помилка при спробі виконати функцію \"%s\" у файлі %s:\n%s"),
                  szVBScript, _T("GetDBFFields"), szDBFieldInfo);
          fOk = false;
        }
      }
    }
    else {
      sprintf(pErrBuf, _T("Помилка при спробі виконати функцію \"%s\" у файлі %s:\n%s"),
              szVBScript, _T("Initialize"), g_pScriptObj->GetErrorString());
      fOk = false;
    }
  }
  catch(...) {
    fOk = false;
  }


  if ( false==fOk ) {
    delete g_pScriptObj;
    g_pScriptObj = NULL;
    return false;
  }

  g_pDBF = new CDBF();
  if ( false==g_pDBF->Create(szDBFile, szDBFieldInfo, pErrBuf) ) {
    delete g_pScriptObj;
    g_pScriptObj = NULL;
    delete g_pDBF;
    g_pDBF = NULL;
    fOk = false;
  }

  return fOk;
}

_variant_t varRet;

_declspec(dllexport) BOOL WINAPI OnDBFRecord(CDaoRecordset* pSet) {
  if ( NULL==g_pDBF || NULL==g_pScriptObj ) {
    return false;
  }

  CString szRecord, szRet;

  int nFields = pSet->GetFieldCount();
  for( int i(0); i < nFields; i++ ) {
    CString     szValue;
    COleVariant varValue;
    CDaoFieldInfo fi;
    pSet->GetFieldInfo(i, fi);
    pSet->GetFieldValue(i, varValue);
    switch( fi.m_nType ) {
      case dbBoolean  : szValue = varValue.boolVal ? "1" : "0";
        break;
      case dbByte     : szValue.Format(_T("%u"), varValue.bVal);
        break;
      case dbInteger  : szValue.Format(_T("%u"), varValue.intVal);
        break;
      case dbLong     : szValue.Format(_T("%u"), varValue.lVal);
        break;
      case dbCurrency :
        {
          COleCurrency uah(varValue);
          szValue.Format(_T("%d,%02d"), (int)uah.m_cur.int64/10000, (int)(uah.m_cur.int64%10000)/100);
        }
        break;
      case dbSingle   : szValue.Format(_T("%.4f"), varValue.fltVal);
        break;
      case dbDouble   : szValue.Format(_T("%.4f"), varValue.dblVal);
        break;
      case dbDate     :
        {
          COleDateTime dt(varValue);
          if ( dt.GetStatus()==COleDateTime::valid && dt.m_dt != (DATE)0 ) {
            szValue.Format(_T("%4d%02d%02d"), dt.GetYear(), dt.GetMonth(), dt.GetDay());
          }
        }
        break;
      case dbText  : case dbMemo  : szValue = V_BSTRT(&varValue);
        break;
      default:
        szValue = _T("?");
        break;
    }
    if ( szValue.IsEmpty() ) {
      szValue = _T(" ");
    }
    if ( false==szRecord.IsEmpty() ) {
      szRecord += TCHAR(1);
    }
    szRecord += szValue;
  }

  BOOL fOk = false;

  try {
    _variant_t par = _bstr_t(szRecord);
    CSafeArrayHelper sfHelper;
    sfHelper.Create(VT_VARIANT, 1, 0, 1);	// VBS-function "OnRecord" should receive 1 parameter
    sfHelper.PutElement(0, (void*)&par);	// parameter1 -> index 0
    // TRACE1("%s\n", szRecord);
    LPSAFEARRAY sa =  sfHelper.GetArray();
    if (g_pScriptObj->RunProcedure(_T("OnRecord"), &sa, &varRet)) {
      szRet = (LPCTSTR)_bstr_t(varRet);
      fOk = true;
    }
    // TRACE1("%s\n", szRecord);
  }
  catch(...) {
  }

  if ( fOk ) {
    g_pDBF->AddRec(szRet);
  }

  return true;
}

_declspec(dllexport) BOOL WINAPI CloseDBF() {
  if ( NULL==g_pDBF || NULL==g_pScriptObj ) {
    return false;
  }
  g_pDBF->Close();
  delete g_pDBF;
  g_pDBF = NULL;
  delete g_pScriptObj;
  g_pScriptObj = NULL;
  return true;
}