// DB.cpp : implementation file
//

#include "stdafx.h"
#include "DB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


TCHAR iDBCharField(CIRecordset& rs, int fieldNo)
{
	CString s(iDBStringField(rs,fieldNo));
	if (s.GetLength() > 0)
		return s.GetAt(0);
	return _TCHAR('\0');
}

#ifdef _SQL
  CString iDBStringField(CIRecordset& rs, int fieldNo)
	{
		CDBVariant var;
		rs.GetFieldValue((short)fieldNo,var);
		if (var.m_dwType == DBVT_NULL)
			return _T("");
		ASSERT(var.m_dwType ==  DBVT_STRING);
		CString s = *var.m_pstring;
		var.Clear();
		return s;
	}
#else
  CString iDBStringField(CIRecordset& rs, int fieldNo)
	{
		COleVariant var;
		var = rs.GetFieldValue((int)fieldNo);
		if (var.vt == VT_NULL)
			return _T("");
		CString s = V_BSTRT(&var);
		return s;
	}
#endif

#ifdef _SQL
  long iDBLongField(CIRecordset& rs, int fieldNo)
	{
		CDBVariant var;
		rs.GetFieldValue((short)fieldNo,var);
		if (var.m_dwType == DBVT_NULL)
      return 0;
		return var.m_lVal;
	}
#else
  long iDBLongField(CIRecordset& rs, int fieldNo)
	{
		COleVariant var = rs.GetFieldValue(fieldNo);
		if (var.vt == VT_NULL)
			return 0;
    switch( var.vt ) {
      case VT_I1:
			  return (long) V_I1(&var);
      case VT_UI1:
			  return (long) V_UI1(&var);
      case VT_I2 :
			  return (long) V_I2(&var);
      case VT_UI2:
        return (long) V_UI2(&var);
    }
		ASSERT(var.vt == VT_I4);
		return V_I4(&var);
	}
#endif

#ifdef _SQL
	short iDBShortField(CIRecordset& rs, int fieldNo)
	{
		CDBVariant var;
		rs.GetFieldValue((short)fieldNo,var);
		if (var.m_dwType == DBVT_NULL)
			return 0;
		return var.m_iVal;
	}
#else
	short iDBShortField(CIRecordset& rs, int fieldNo)
	{
		COleVariant var = rs.GetFieldValue(fieldNo);
		if (var.vt == VT_NULL)
			return 0;
		ASSERT(var.vt == VT_I2);
		return V_I2(&var);
	}
#endif

#ifdef _SQL
	COleDateTime iDBDateField(CIRecordset& rs, int fieldNo)
	{
		CDBVariant var;
	  COleDateTime tm;
		rs.GetFieldValue((short)fieldNo,var);
		if (var.m_dwType == DBVT_NULL) {
			tm.SetStatus(COleDateTime::null);
			return tm;
		}
		ASSERT(var.m_dwType == DBVT_DATE);
	  tm.SetDate(var.m_pdate->year,var.m_pdate->month,var.m_pdate->day);
		return tm;
	}
#else
	date_i iDBDateField(CIRecordset& rs, int fieldNo)
	{
		COleVariant var = rs.GetFieldValue(fieldNo);
		if (var.vt == VT_NULL) {
			COleDateTime tm;
			tm.SetStatus(COleDateTime::null);
			return tm;
		}
    COleDateTime tm(var);
		return tm;
	}
#endif

#ifdef _SQL
  bool iDBBoolField(CIRecordset& rs, int fieldNo)
	{
		CDBVariant var;
		rs.GetFieldValue((short)fieldNo,var);
		if (var.m_dwType == DBVT_NULL)
			return false;
		ASSERT(var.m_dwType == DBVT_BOOL);
		// fixup error in \mfc\src\dbcore.cpp GetFieldValue
		// ActualSize of data is 1, but sizeof(m_boolVal) == 4 !
		return (var.m_boolVal & 0x0F) ? true : false;
	}
#else
	bool iDBBoolField(CIRecordset& rs, int fieldNo)
	{
		COleVariant var = rs.GetFieldValue(fieldNo);
		if (var.vt == VT_NULL)
			return false;
		return V_BOOL(&var) ? true : false;
	}
#endif

#ifdef _SQL
  double iDBDoubleField(CIRecordset& rs, int fieldNo)
	{
		CDBVariant var;
		rs.GetFieldValue((short)fieldNo,var);
		if (var.m_dwType == DBVT_NULL)
			return 0.0;
		ASSERT(var.m_dwType == DBVT_DOUBLE || var.m_dwType == DBVT_SINGLE);
		if (var.m_dwType == DBVT_DOUBLE)
			return var.m_dblVal;
		else if (var.m_dwType == DBVT_SINGLE)
			return (double) var.m_fltVal;
		return 0.0;
	}
#else
  double iDBDoubleField(CIRecordset& rs, int fieldNo)
	{
		COleVariant var = rs.GetFieldValue(fieldNo);
		if (var.vt == VT_NULL)
			return 0.0;
		return V_R8(&var);
	}
#endif

#ifndef _SQL
	void iSetParamDoubleOrNull(CDaoQueryDef& qd,int fieldNo, double value)
	{
		if (value == 0.0) {
			qd.SetParamValueNull(fieldNo);
		} else {
			qd.SetParamValue(fieldNo,COleVariant((double)value));
		}
	}

	void iSetParamStringOrNull(CDaoQueryDef& qd,int fieldNo,const CString& value)
	{
		if (value.IsEmpty()) {
			qd.SetParamValueNull(fieldNo);
		} else {
			qd.SetParamValue(fieldNo,COleVariant(value,VT_BSTRT));
		}
	}

	void iSetParamLongOrNull(CDaoQueryDef& qd,int fieldNo, long value)
	{
		if (value == 0) {
			qd.SetParamValueNull(fieldNo);
		} else {
			qd.SetParamValue(fieldNo,COleVariant((long)value));
		}
	}

	void iSetParamShortOrNull(CDaoQueryDef& qd,int fieldNo, short value)
	{
		if (value == 0) {
			qd.SetParamValueNull(fieldNo);
		} else {
			qd.SetParamValue(fieldNo,COleVariant((short)value));
		}
	}

	void iSetParamDateOrNull(CDaoQueryDef& qd,int fieldNo, COleDateTime value)
	{
		if (value.GetStatus() != COleDateTime::valid) {
			qd.SetParamValueNull(fieldNo);
		} else {
			COleDateTime tm;
			tm.SetDate(value.GetYear(),value.GetMonth(),value.GetDay());
			qd.SetParamValue(fieldNo,COleVariant(tm));
		}
	}
#endif

#ifdef _SQL

const LPCTSTR szNull = _T("NULL");

CString Quote(CString& str)
{
	CString x(_T("'"));
	x += str;
	x += _T("'");
	return x;
}

CString iQuoteString(CString& str)
{
	CString arg(str);
	int pos = arg.Find(_T("'"));
	while (pos != -1) {
		arg.SetAt(pos,_T('\"'));
	}
	return Quote(arg);
}

CString iQuoteStringOrNull(CString& str)
{
	if (str.IsEmpty())
		return szNull;
	CString arg(str);
	int pos = arg.Find(_T("'"));
	while (pos != -1) {
		arg.SetAt(pos,_T('\"'));
	}
	return Quote(arg);
}

CString OleDate2Str(COleDateTime& dt)
{
  CString s;
  s.Format(_T("%04d%02d%02d"),dt.GetYear(),dt.GetMonth(),dt.GetDay());
  return s;
}

CString iQuoteDate(COleDateTime& date)
{
  return Quote(OleDate2Str(date));
}

CString iQuoteDateOrNull(COleDateTime& date)
{
  if (date.GetStatus() == COleDateTime::valid)
    return iQuoteDate(date);
  return szNull;
}

CString iParamLongOrNull(long param)
{
  if (param == 0)
    return szNull;
  CString s;
  s.Format(_T("%ld"),param);
  return s;
}

CString iParamDouble(double val)
{
  CString x;
  x.Format(_T("%.15f"),val);
  return x;
}

CString iParamDouble(double val, double precision)
{
  return iParamDouble(val);
}

CString iParamDoubleOrNull(double val)
{
  if (val == 0.0)
    return szNull;
  return iParamDouble(val);
}

CString iParamDoubleOrNull(double val, double precision)
{
  return iParamDoubleOrNull(val);
}

#endif

long iDBGetMaxID(CIDatabase* pDB, LPCTSTR szSql) {
	long id = 0;

	CIRecordset rs(pDB);
  IOpenForward(rs,szSql);
	if (!rs.IsEOF()) {
		id = iDBLongField(rs,0);  
	}
	rs.Close();
	return id;
}


/**************************************** 16.06.2001 13:29:59 by VK
bool ExecuteSQL(LPCTSTR szSQL) {

#ifdef _SQL
	CIRecordset rs(extGetDatabase());
	try {
	  extGetDatabase()->ExecuteSQL(szSQL);
  }
#else
	CDaoQueryDef qd(extGetDatabase());
	try {
	  qd.Create(NULL,szSQL);
	  qd.Execute();
	  qd.Close();
  }
#endif
	catch (CIDBException* e) {
    #ifdef _DEBUG
		  e->ReportError();
    #endif
		e->Delete();
    return false;
	}
  return true;
}
***************************************** 16.06.2001 13:30:03 by VK */
