#if !defined(DB_H_INCLUDED)
#define DB_H_INCLUDED
// DB.h

#include <afxdb.h>

extern TCHAR iDBCharField(CDaoRecordset& rs, int fieldNo);
extern CString iDBStringField(CDaoRecordset& rs, int fieldNo);
extern long    iDBLongField(CDaoRecordset& rs, int fieldNo);
extern int     iDBIntField(CDaoRecordset& rs, int fieldNo);
extern short   iDBShortField(CDaoRecordset& rs, int fieldNo);
extern COleDateTime iDBDateField(CDaoRecordset& rs, int fieldNo);
extern bool    iDBBoolField(CDaoRecordset& rs, int fieldNo);
extern double  iDBDoubleField(CDaoRecordset& rs, int fieldNo);

inline void IOpenForward(CDaoRecordset& rs, LPCTSTR sql = NULL)
	{ rs.Open(dbOpenSnapshot,sql,dbForwardOnly);}

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

CString GetFieldString(CDaoRecordset* pRS, LPCTSTR lpszFldName);

#endif DB_H_INCLUDED
