#ifndef __RNAMES_H
#define __RNAMES_H

class CEraEdit;
class CEraNameEdit;
class CEraNameComboBox;

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

CString GetShortTypeOfCity(LPCTSTR szCity);
CString DecodeRagsName(const CString& sRags);
CString DecodeRagsNameWithoutAbbr(const CString& sUpperRags);
CString EncodeRagsName(const CString& sRags);
CString MakeKeysForRagsName(const CString& sRags);

CString RagsFromTo(const CString& sRagsFrom, int iFrom, int iTo);
CString MakeCanonicalRagsName(const CString &s);
CString SVRagsC(LPCTSTR szSrc, int nVid);

bool    PASCAL IsStreet(const CString& s);

CString GetDistrictFromAddress(const CString& szAddress, int nFound);


BOOL PASCAL    IsDistrictInCity(LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szDistrict, LPCTSTR szCity);
CString PASCAL GetPlace(LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szDistrict, LPCTSTR szCity, BOOL fShort=true);
CString PASCAL GetAddress(LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szCity, LPCTSTR szDistrict, LPCTSTR szStreet, LPCTSTR szHouse, LPCTSTR szFlat, BOOL fFullAddress=FALSE);
TCHAR   PASCAL GetRagsType(LPCTSTR szRagsName);
CString PASCAL MakeAddress(CEraNameComboBox* pCountry, CEraNameComboBox* pRegion, CEraNameComboBox* pCity, CEraNameComboBox* pDistrict, CEraNameComboBox* pStreet, CEraEdit* pHouse, CEraEdit* pFlat);


CString SVRagsC(LPCTSTR szSrc, SHORT nVid);

#endif// __RNAMES_H