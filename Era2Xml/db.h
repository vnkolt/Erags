//
// db.h
//

#pragma once

#define BIRTH_G10         0x0001   // Const �_�10 = 1  ' ����� 10 {�10: }
#define BIRTH_RENEW       0x0002   // Const �_��� = 2  ' ���������� ��
#define BIRTH_LONGTERM    0x0004   // Const �_��� = 4  ' � ��������� ������
#define BIRTH_NOINLIST    0x0008   // Const �_��� = 8  ' �� � ������ ��������������
#define BIRTH_DECL20      0x0010

long GetRecordCount(CDaoDatabase& db, LPCTSTR szTablename);

BOOL IsFieldPresent(CDaoRecordset& rs, LPCTSTR szFieldName);

LONG    GetFieldLong(CDaoRecordset& rs, LPCTSTR lpszFldName);
SHORT   GetFieldShort(CDaoRecordset& rs, LPCTSTR lpszFldName);
BYTE    GetFieldByte(CDaoRecordset& rs, LPCTSTR lpszFldName);
CString GetFieldString(CDaoRecordset& rs, LPCTSTR lpszFldName);
CString GetFieldDate(CDaoRecordset& rs, LPCTSTR lpszFldName, COleDateTime* pDate = NULL);


BOOL    IsUALang(CDaoRecordset& rs);
