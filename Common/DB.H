// DB.h
#if !defined(DB_H_INCLUDED)
#define DB_H_INCLUDED

#pragma warning(disable : 4995)

#ifdef _SQL

  #define CIRecordset     CRecordset
  #define CIDatabase      CDatabase
  #define CIFieldExchange CFieldExchange
  #define IDynaset        CRecordset::dynaset
  #define IForwardOnly    CRecordset::forwardOnly

  #define IFX_Text RFX_Text
  #define IFX_Long RFX_Long
  #define IFX_Double RFX_Double
  #define IFX_Short RFX_Int
  #define IFX_DateTime RFX_Date
  #define IFX_Bool RFX_Bool

  #define short_i int
  #define date_i  CTime

  #define CIDBException CDBException

  #define DBDate2Date(x) Date2Ole(x)
  #define Date2DBDate(x) Ole2Date(x)

#else

  #define CIDatabase      CDaoDatabase
  #define CIRecordset     CDaoRecordset
  #define CIFieldExchange CDaoFieldExchange
  #define IDynaset        dbOpenDynaset
  #define IForwardOnly    dbOpenSnapshot

  #define IFX_Text DFX_Text
  #define IFX_Long DFX_Long
  #define IFX_Double DFX_Double
  #define IFX_Short DFX_Short
  #define IFX_DateTime DFX_DateTime
  #define IFX_Bool DFX_Bool

  #define short_i short
  #define date_i  COleDateTime

  #define CIDBException CDaoException

  #define DBDate2Date(x) (x)
  #define Date2DBDate(x) (x)

#endif

extern TCHAR iDBCharField(CIRecordset& rs, int fieldNo);
extern CString iDBStringField(CIRecordset& rs, int fieldNo);
extern long    iDBLongField(CIRecordset& rs, int fieldNo);
extern short   iDBShortField(CIRecordset& rs, int fieldNo);
extern short_i iDBShortField(CIRecordset& rs, int fieldNo);
extern COleDateTime iDBDateField(CIRecordset& rs, int fieldNo);
extern bool    iDBBoolField(CIRecordset& rs, int fieldNo);
extern double  iDBDoubleField(CIRecordset& rs, int fieldNo);

// Recordsets
#ifdef _SQL
  inline void IOpenForward(CIRecordset& rs, LPCTSTR sql = NULL)
	{ rs.Open(CRecordset::forwardOnly,sql,CRecordset::readOnly);}
#else
  inline void IOpenForward(CIRecordset& rs, LPCTSTR sql = NULL)
	{ rs.Open(dbOpenSnapshot,sql,dbForwardOnly);}
#endif

#ifndef _SQL
	// Parameters 
	inline void iSetParamLong(CDaoQueryDef& qd, int no, long value)
	{ qd.SetParamValue(no,COleVariant((long)value)); }
	inline void iSetParamString(CDaoQueryDef& qd, int no, LPCTSTR text)
	{ qd.SetParamValue(no,COleVariant(CString(text),VT_BSTRT)); }
	inline void iSetParamShort(CDaoQueryDef& qd, int no, short value)
	{ qd.SetParamValue(no,COleVariant((short)value)); }
	inline void iSetParamDouble(CDaoQueryDef& qd, int no, double value)
	{ qd.SetParamValue(no,COleVariant((double)value)); }
	inline void iSetParamDate(CDaoQueryDef& qd, int no, COleDateTime value)
	{ qd.SetParamValue(no,COleVariant((COleDateTime)value)); }
	inline void iSetParamBool(CDaoQueryDef& qd, int no, bool value)
	{ qd.SetParamValue(no,COleVariant((short) (value ? -1 : 0))); }

	extern void iSetParamStringOrNull(CDaoQueryDef& qd,int fieldNo,const CString& value);
	extern void iSetParamLongOrNull(CDaoQueryDef& qd,int fieldNo, long value);
	extern void iSetParamDoubleOrNull(CDaoQueryDef& qd,int fieldNo, double value);
	extern void iSetParamShortOrNull(CDaoQueryDef& qd,int fieldNo, short value);
	extern void iSetParamDateOrNull(CDaoQueryDef& qd,int fieldNo, COleDateTime value);
#endif

#ifdef _SQL
	CString iQuoteString(CString& str);
	CString iQuoteStringOrNull(CString& str);
	CString iQuoteDate(COleDateTime& date);
	CString iQuoteDateOrNull(COleDateTime& date);
	CString iParamLongOrNull(long param);
	CString iParamDouble(double val);
	CString iParamDouble(double val, double precision);
	CString iParamDoubleOrNull(double val);
	CString iParamDoubleOrNull(double val, double precision);
#endif

long iDBGetMaxID(CIDatabase* pDB, LPCTSTR szSql);
bool  ExecuteSQL(LPCTSTR szSQL);

#endif//DB_H_INCLUDED