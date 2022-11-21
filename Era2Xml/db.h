//
// db.h
//

#pragma once

#define BIRTH_G10         0x0001   // Const к_Г10 = 1  ' Графа 10 {Г10: }
#define BIRTH_RENEW       0x0002   // Const к_ПАЗ = 2  ' Поновлений АЗ
#define BIRTH_LONGTERM    0x0004   // Const к_ЗПС = 4  ' З пропуском строку
#define BIRTH_NOINLIST    0x0008   // Const к_МСН = 8  ' Не в списку новонароджених
#define BIRTH_DECL20      0x0010

long GetRecordCount(CDaoDatabase& db, LPCTSTR szTablename);

BOOL IsFieldPresent(CDaoRecordset& rs, LPCTSTR szFieldName);

LONG    GetFieldLong(CDaoRecordset& rs, LPCTSTR lpszFldName);
SHORT   GetFieldShort(CDaoRecordset& rs, LPCTSTR lpszFldName);
BYTE    GetFieldByte(CDaoRecordset& rs, LPCTSTR lpszFldName);
CString GetFieldString(CDaoRecordset& rs, LPCTSTR lpszFldName);
CString GetFieldDate(CDaoRecordset& rs, LPCTSTR lpszFldName, COleDateTime* pDate = NULL);


BOOL    IsUALang(CDaoRecordset& rs);
