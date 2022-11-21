#ifndef __NAMES_H
#define __NAMES_H


#define RC_NV 1
#define RC_RV 2
#define RC_DV 3
#define RC_ZV 4
#define RC_OV 5
#define RC_MV 6

extern CString sEOL;

struct SVidCnv {
  LPCTSTR szNV; // Називний відмінок
  LPCTSTR szRV; // Родовий відмінок
  LPCTSTR szDV; // Давальний відмінок
  LPCTSTR szOV; // Орудний відмінок
  LPCTSTR szMV; // Місцевий відмінок
};


CString OfferSurname(LPCTSTR szSrc, BOOL bSexFrom, BOOL bSexTo);
CString OfferSurname(CWnd* pWnd, BOOL bSexFrom, BOOL bSexTo);
CString OfferName(CWnd* pWnd);

///////////////////////////////////////////////////////
// Функции-ковертеры мужских фамилий, имен и отчеств.
//
CString ManSurname_DV(LPCTSTR szFrom);
CString ManSurname_OV(LPCTSTR szFrom);
CString ManSurname_RV(LPCTSTR szFrom);
CString ManSurname_ZV(LPCTSTR szFrom);
CString ManName_DV(LPCTSTR szFrom);
CString ManName_OV(LPCTSTR szFrom);
CString ManName_RV(LPCTSTR szFrom);
CString ManName_ZV(LPCTSTR szFrom);
CString ManFather_DV(LPCTSTR szFrom);
CString ManFather_OV(LPCTSTR szFrom);
CString ManFather_RV(LPCTSTR szFrom);
CString ManFather_ZV(LPCTSTR szFrom);

#define	NC_MSURNAME_DV	100
#define	NC_WSURNAME_DV	101
#define	NC_MSURNAME_OV	110
#define	NC_WSURNAME_OV	111
#define	NC_MSURNAME_RV	120
#define	NC_WSURNAME_RV	121
#define	NC_MSURNAME_ZV	130
#define	NC_WSURNAME_ZV	131

#define	NC_MNAME_DV			200
#define	NC_WNAME_DV			201
#define	NC_MNAME_OV			210
#define	NC_WNAME_OV			211
#define	NC_MNAME_RV			220
#define	NC_WNAME_RV			221
#define	NC_MNAME_ZV			230
#define	NC_WNAME_ZV			231

#define	NC_MFATHER_DV		300
#define	NC_WFATHER_DV		301
#define	NC_MFATHER_OV		310
#define	NC_WFATHER_OV		311
#define	NC_MFATHER_RV		320
#define	NC_WFATHER_RV		321
#define	NC_MFATHER_ZV		330
#define	NC_WFATHER_ZV		331


///////////////////////////////////////////////////////
// Функции-ковертеры женских фамилий, имен и отчеств.
//
CString WomanSurname_DV(LPCTSTR szFrom);
CString WomanSurname_OV(LPCTSTR szFrom);
CString WomanSurname_RV(LPCTSTR szFrom);
CString WomanSurname_ZV(LPCTSTR szFrom);
CString WomanName_DV(LPCTSTR szFrom);
CString WomanName_OV(LPCTSTR szFrom);
CString WomanName_RV(LPCTSTR szFrom);
CString WomanName_ZV(LPCTSTR szFrom);
CString WomanFather_DV(LPCTSTR szFrom);
CString WomanFather_OV(LPCTSTR szFrom);
CString WomanFather_RV(LPCTSTR szFrom);
CString WomanFather_ZV(LPCTSTR szFrom);


CString MakeFullName(const CString& sSurName, const CString& sName, const CString& sFather, BOOL fMale, SHORT nVid);
CString MakeFromFullName(const CString& sFullName, bool bSex);

CString SVRagsC(LPCTSTR szSrc, SHORT nVid);
CString NameC(LPCTSTR szSrc, WORD wID);

#endif// __NAMES_H