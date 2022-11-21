// DB.cpp : implementation file
//
#include "stdafx.h"


#include "DB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


TCHAR iDBCharField(CDaoRecordset& rs, int fieldNo)
{
	CString s(iDBStringField(rs,fieldNo));
	if (s.GetLength() > 0)
		return s.GetAt(0);
	return _TCHAR('\0');
}

CString iDBStringField(CDaoRecordset& rs, int fieldNo) {
  COleVariant var;
  var = rs.GetFieldValue((int)fieldNo);
  if (var.vt == VT_NULL)
    return _T("");
  CString s = V_BSTRT(&var);
  return s;
}

long iDBLongField(CDaoRecordset& rs, int fieldNo) {
  COleVariant var = rs.GetFieldValue(fieldNo);
	if (var.vt == VT_NULL)
	  return 0;
  if (var.vt == VT_I2)
	  return (long) V_I2(&var);
  if (var.vt == VT_I4)
    return V_I4(&var);
  if (var.vt == VT_UI1)
    return (long)var.bVal;
  return V_I4(&var);
}

int iDBIntField(CDaoRecordset& rs, int fieldNo) {
  COleVariant var = rs.GetFieldValue(fieldNo);
	if (var.vt == VT_NULL)
	  return 0;
  ASSERT(var.vt == VT_I2);
  return V_I2(&var);
}


short iDBShortField(CDaoRecordset& rs, int fieldNo) {
  return (short) iDBIntField(rs,fieldNo);
}

COleDateTime iDBDateField(CDaoRecordset& rs, int fieldNo) {
  COleVariant var = rs.GetFieldValue(fieldNo);
	if (var.vt == VT_NULL) {
	  COleDateTime tm;
		tm.SetStatus(COleDateTime::null);
		return tm;
  }
  COleDateTime tm(var);
	return tm;
}

bool iDBBoolField(CDaoRecordset& rs, int fieldNo) {
  COleVariant var = rs.GetFieldValue(fieldNo);
	if (var.vt == VT_NULL)
	  return false;
  return V_BOOL(&var) ? true : false;
}

double iDBDoubleField(CDaoRecordset& rs, int fieldNo) {
  COleVariant var = rs.GetFieldValue(fieldNo);
	if (var.vt == VT_NULL)
	  return 0.0;
  return V_R8(&var);
}

void iSetParamDoubleOrNull(CDaoQueryDef& qd,int fieldNo, double value) {
  if (value == 0.0) {
	  qd.SetParamValueNull(fieldNo);
  }
  else {
    qd.SetParamValue(fieldNo,COleVariant((double)value));
  }
}

void iSetParamStringOrNull(CDaoQueryDef& qd,int fieldNo,const CString& value) {
  if (value.IsEmpty()) {
    qd.SetParamValueNull(fieldNo);
  }
  else {
	  qd.SetParamValue(fieldNo,COleVariant(value,VT_BSTRT));
  }
}

void iSetParamLongOrNull(CDaoQueryDef& qd,int fieldNo, long value) {
  if (value == 0) {
	  qd.SetParamValueNull(fieldNo);
  }
  else {
    qd.SetParamValue(fieldNo,COleVariant((long)value));
  }
}

void iSetParamShortOrNull(CDaoQueryDef& qd,int fieldNo, short value) {
  if (value == 0) {
	  qd.SetParamValueNull(fieldNo);
  }
  else {
    qd.SetParamValue(fieldNo,COleVariant((short)value));
  }
}

void iSetParamDateOrNull(CDaoQueryDef& qd,int fieldNo, COleDateTime value) {
  if (value.GetStatus() != COleDateTime::valid) {
	  qd.SetParamValueNull(fieldNo);
  }
  else {
	  COleDateTime tm;
		tm.SetDate(value.GetYear(),value.GetMonth(),value.GetDay());
		qd.SetParamValue(fieldNo,COleVariant(tm));
  }
}

CString GetFieldString(CDaoRecordset* pRS, LPCTSTR lpszFldName) {
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
      case VT_BSTR:
        sRet = V_BSTRT(&ovar);
        break;
      case VT_I1:
      case VT_UI1:
        sRet.Format(_T("%c"), ovar.bVal);
        break;
    }
  }
  catch(CDaoException* e) {
    e->Delete();
  }
  return sRet;
}
