//
// Dictionaries.h
//

#pragma once

TCHAR GetCitizenship(LPCTSTR szCitizenship);
TCHAR GetCountryType(LPCTSTR szCountry);
int   GetRegionId(LPCTSTR szRegion, LPCTSTR szCity);
TCHAR GetRegionTypeId(LPCTSTR szRegion, LPCTSTR szCity);
TCHAR GetDistrictTypeId(const CString& szCountry, const CString& szRegion, const CString& szDistrict, const CString& szCity,
                        CString& szDistrictName, CString& szSettlementName);
TCHAR GetSettlementTypeId(LPCTSTR szCityWithType, BOOL bDistrictInCity);
void  ParseStreet(CString& szStreet, CString& szTok, TCHAR& cType, CString& szStreetTypeName);
void  ParseBuildNumb(CString& szBuild, CString& szBuildNumb, CString& szBuildExtNumb, TCHAR& BuildType);

CString MakeCountryName(LPCTSTR szCountry);

LPCTSTR GetDocType(BYTE bDocType);