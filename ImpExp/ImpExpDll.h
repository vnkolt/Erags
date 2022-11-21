#if !defined(_IMPEXPDLL_H_INCLUDED)
#define _IMPEXPDLL_H_INCLUDED

class CElectItem;
class CElections;
class CDaoRecordset;

typedef void (*pOnHelpCallback)(LPCTSTR szHelpFile);

int  WINAPI Import(LPCTSTR szTo, LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szCity, LPCTSTR szDistrict, pOnHelpCallback fHelpCallback);


BOOL WINAPI BeginCopy2XL();
BOOL WINAPI Copy2XL(long nSheet);
void WINAPI EndCopy2XL();

BOOL WINAPI CreateDBF(CDaoRecordset* pSet, LPCSTR szOKPO, LPCSTR szDBFile, LPCTSTR szVBScript, char* pErrBuf/* 1024 bytes*/);
BOOL WINAPI OnDBFRecord(CDaoRecordset* pSet);
BOOL WINAPI CloseDBF();

BOOL WINAPI E2Excel(CElections*, LPCTSTR szXLS, BOOL fMultiSheet, BOOL (* pElectEncoder)(TCHAR* pDestBuf, int BufSize, LPCTSTR szKey, CElectItem* pItem, int Number), void (* ProgressRoutineProc)(int nCount, int nProcessed, void* lpData), void* lpData);
BOOL WINAPI E2OCalc(CElections*, LPCTSTR szXLS, BOOL fMultiSheet, BOOL (* pElectEncoder)(TCHAR* pDestBuf, int BufSize, LPCTSTR szKey, CElectItem* pItem, int Number), void (* ProgressRoutineProc)(int nCount, int nProcessed, void* lpData), void* lpData);

#endif