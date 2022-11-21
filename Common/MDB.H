#if !defined(MDB_H_INCLUDED)
#define MDB_H_INCLUDED

#pragma warning(disable : 4995)

BOOL    IsTablePresent(CDaoDatabase& db, LPCTSTR szTableName);
BOOL    IsFieldPresent(CDaoRecordset& rs, LPCTSTR szFieldName);
long    GetRecordCount(CDaoDatabase& db, LPCTSTR szTableName);

LONG    GetFieldLong(CDaoRecordset* pRS, LPCTSTR lpszFldName);
SHORT   GetFieldShort(CDaoRecordset* pRS, LPCTSTR lpszFldName);
BYTE    GetFieldByte(CDaoRecordset* pRS, LPCTSTR lpszFldName);

CString GetFieldString(CDaoRecordset* pRS, LPCTSTR lpszFldName);
bool    GetFieldBool(CDaoRecordset* pRS, LPCTSTR lpszFldName);
COleDateTime GetFieldOleDateTime(CDaoRecordset* pRS, LPCTSTR lpszFldName);
CString      GetFieldDate(CDaoRecordset* pRS, LPCTSTR lpszFldName, bool fFullDate=false);

LONG    GetIDField(CDaoRecordset* pRS);

CString GetNumFromStr(CDaoRecordset* pSet, LPCTSTR szFieldName, LPCTSTR szWhat, bool fAdd=true);


#endif// MDB_H_INCLUDED