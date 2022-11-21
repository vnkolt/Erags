//
// CnvBirth.cpp
//
#include "stdafx.h"
#include "Era2Xml.h"
#include "CnvBirth.h"
#include "db.h"

#include "Dictionaries.h"
#include "Geography.h"
#include "Helpers.h"
#include "Globals.h"

#include "RSBirthes.h"
#include "XmlFile.h"
#include "WitnessDlg.h"


#include "..\Common\CyrString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL PeekAndPump();

#define PERSON_ROLE_FATHER    '2'
#define PERSON_ROLE_MOTHER    '3'
#define PERSON_ROLE_DECLARANT '4'

#define BIRTH_TYPE_ACT          0 // Акт про одруження
#define BIRTH_TYPE_MOTHER       1 // Заява матері
#define BIRTH_TYPE_PARENTS      2 // Заява батьків
#define BIRTH_TYPE_APPL         3 // Заява
#define BIRTH_TYPE_APPLNUM      4 // Заява №
#define BIRTH_TYPE_AFFILIATION1 5 // Заява про визнання батьківства
#define BIRTH_TYPE_AFFILIATION2 6 // Спільна заява про визнання батьківства

CString GetNationality(const CString& szMemo, BOOL fFather) {
  CString szNationality, szFind;
  int nFound = -1;
  if ( fFather ) {
    szFind = _T("Національність батька:");
  }
  else {
    szFind = _T("Національність матері:");
  }
  nFound = szMemo.Find(szFind);
  if ( nFound >= 0 ) {
    int nLen = szMemo.GetLength();
    nFound += szFind.GetLength();
    while ( nFound < nLen ) {
      TCHAR c = szMemo.GetAt(nFound);
      if ( c=='}' ) {
        break;
      }
      szNationality += c;
      nFound++;
    }
    szNationality.TrimLeft();
    szNationality.TrimRight();
  }
  return szNationality;
}

//
// Для отца или матери
// 
void MakePersonTag(CRSBirthes& rs,
                   CXmlFile& xml,
                   TCHAR cPersonRole,
                   LPCTSTR szDeclarantRole,
                   LPCTSTR szSurname,
                   LPCTSTR szName,
                   LPCTSTR szPatronymic,
                   LPCTSTR szCitizenship,
                   LPCTSTR szBirthDate,
                   CString& szCountry,
                   CString& szRegion,
                   CString& szFullCity,
                   CString& szDistrict,
                   CString& szStreet,
                   TCHAR cStreetTypeId,
                   CString& szBuild,
                   CString& szApartNumb
                  )
{
  CString s, stmp, spaces(' ', 8);


  if ( szDeclarantRole ) {
    xml.WriteFormat(_T("      <Person Role=\"%c\" DeclarantRole=\"%s\">\r\n"), cPersonRole, szDeclarantRole);
  }
  else {
    xml.WriteFormat(_T("      <Person Role=\"%c\">\r\n"), cPersonRole);
  }

  // <!-- "Прізвище" -->
  xml.WriteFormat( _T("%s<Surname>%s</Surname>\r\n"), spaces, Win1251ToUTF8(szSurname) );
  // <!-- "Власне ім’я" -->
  xml.WriteFormat( _T("%s<Name>%s</Name>\r\n"), spaces, Win1251ToUTF8(szName) );
  // <!-- "По батькові" -->
  xml.WriteFormat( _T("%s<Patronymic>%s</Patronymic>\r\n"), spaces, Win1251ToUTF8(szPatronymic) );

  if ( szCitizenship ) {
    // <!-- "Громадянство 1" ( значення із словника «Громадянин(ка) України» = 1, «Інше» = 2) -->
    TCHAR cCitizenship = GetCitizenship( szCitizenship );
    xml.WriteFormat( _T("%s<Citizenship>%c</Citizenship>\r\n"), spaces, cCitizenship );
    if ( cCitizenship != '1' ) { // Якщо громадянство != '1' (України)
      xml.WriteFormat( _T("%s<CitizenshipDescription>%s</CitizenshipDescription>\r\n"), spaces, Win1251ToUTF8(szCitizenship) );
    }

    // <!-- "Національність" -->
    CString szNationality;
    if ( false==rs.m_EXTNOTES.IsEmpty() ) {
      switch( cPersonRole ) {
        case PERSON_ROLE_FATHER :
          szNationality = GetNationality(rs.m_EXTNOTES, true);
          break;
        case PERSON_ROLE_MOTHER :
          szNationality = GetNationality(rs.m_EXTNOTES, false);
          break;
      }
    }
    if ( g_bWriteEmptyTags || false==szNationality.IsEmpty() ) {
      xml.WriteFormat( _T("%s<Nationality>%s</Nationality>\r\n"), spaces, szNationality);
    }

    // <!-- "Ідентифікаційний номер" -->
    // <Idn></Idn> пропускаем этот тег
    if ( g_bWriteEmptyTags ) {
      xml.WriteFormat( _T("%s<Idn></Idn>\r\n"), spaces);
    }
  }

  if ( szBirthDate ) {
    // <!-- Дата народження -->
    CString szDate = szBirthDate;
    if ( g_bWriteEmptyTags || false==szDate.IsEmpty() ) {
      xml.WriteFormat( _T("%s<BirthDate>%s</BirthDate>\r\n"), spaces, szDate);
    }
  }

  xml.WriteFormat(_T("%s<Addresses>\r\n"), spaces);
  // <!-- Відомості про адресу батька -->
  {
   /*
    <!-- опис для всіх адрес
    AddressType - тип адреси ( значення із словника «місце проживання або реєстрації» = 1, «місце народження» = 2, «місце смерті» = 3)
    CountryType - "Тип адреси (Країна)" ( значення із словника «Україна» = 1, «Інша держава» = 2, «не вказано» = 3, якщо CountryType = 3, інші атрибути можна не вказувати, вважається, що адреса не вказана)
    CountryName - "Країна (Інша)" (вказувати, якшо CountryType = 2, інакше тег можна не вказувати)
    RegionId    - "Регіон 1" (вказувати, якшо CountryType = 1, інакше тег можна не вказувати), може приймати значення з Таблиці 1            
    RegionName  - "Регіон 2" (вказувати, якшо CountryType = 2, інакше тег можна не вказувати), може приймати значення з Таблиці 1
    RegionTypeId - "Тип регіону" ( значення із словника «Місто» = 1, «Область» = 2, «не вказано» = 0)
    DistrictName - "Район"
    DistrictTypeId - "Тип району" ( значення із словника «Місто» = 1, «Район» = 2, «не вказано» = 0)
    SettlementName - "Населений пункт"
    SettlementTypeId - "Тип населеного пункту" ( значення із словника «Місто» = 1, 
              «Район» = 2, 
              «Селище» = 5, 
              «Селище міського типу» = 3,
              «Селищна рада» = 8,
              «Село» = 4,
              «Сільрада» = 6
              «не вказано» = 0)
    CityDistrict - "Район населеного пункту"
    Street - "Вулиця"
    StreetTypeId - "Тип вулиці" ( значення із словника «Бульвар» = 3,
                                  «Вулиця» = 1,
                                  «Інший» = 6,
                                  «Площа» = 2,
                                  «Провулок» = 5,
                                  «Проспект» = 4,
                                  «не вказано» = 0)
    StreetTypeName - "Тип вулиці" текстове значення, якщо StreetTypeId відмінне від 0, значення ігнорується
    ZipCode - "Поштовий індекс"
    BuildNumb - "Номер будинку"
    BuildType - "Тип будівлі" («Корпус» = 1, «Секція» = 2, «не вказано» = 0)
    BuildExtNumb - "Номер" (корпусу, секції)
    ApartNumb - "Номер квартири"
    -->
   */
    CString spaces(' ', 10);
    TCHAR cCountryType = GetCountryType(szCountry);
    s.Format( _T("%s<Address AddressType=\"1\" CountryType=\"%c\""), spaces, cCountryType);

    CString szCity     = GetCity(szFullCity);

    if ( szCountry.IsEmpty() && szFullCity.IsEmpty() ) {
      szRegion.Empty();
    }

    int nRegionId = GetRegionId(szRegion, szCity);

    // RegionId    - "Регіон 1" (вказувати, якшо CountryType = 1, інакше тег можна не вказувати), може приймати значення з Таблиці 1
    if ( '1'==cCountryType ) {
      stmp.Format(_T(" RegionId=\"%d\""), nRegionId);
      s += stmp;
    }
    // RegionName  - "Регіон 2" (вказувати, якшо CountryType = 2, інакше тег можна не вказувати), може приймати значення з Таблиці 1
    if ( '2'==cCountryType ) {
      if ( g_bWriteEmptyTags || false==szRegion.IsEmpty() ) {
        stmp.Format(_T(" CountryName=\"%s\""), Win1251ToUTF8(szRegion));
        s += stmp;
      }
    }
    // RegionTypeId - "Тип регіону" ( значення із словника «Місто» = 1, «Область» = 2, «не вказано» = 0)
    stmp.Format(_T(" RegionTypeId=\"%c\""), GetRegionTypeId(szRegion, szCity));
    s += stmp;
    // DistrictName - "Район"
    CString szDistrictName;
    CString szSettlementName;
    // DistrictTypeId - "Тип району" ( значення із словника «Місто» = 1, «Район» = 2, «не вказано» = 0)
    TCHAR  cDistrictTypeId = GetDistrictTypeId(szCountry, szRegion, szDistrict, szCity, szDistrictName, szSettlementName);


    // DistrictName - "Район"
    if ( g_bWriteEmptyTags || false==szDistrictName.IsEmpty() ) {
      stmp.Format(_T(" DistrictName=\"%s\""), Win1251ToUTF8(szDistrictName));
      s += stmp;
    }
    stmp.Format(_T(" DistrictTypeId=\"%c\""), cDistrictTypeId);
    s += stmp;

    // SettlementName - "Населений пункт"
    if ( g_bWriteEmptyTags || false==szSettlementName.IsEmpty() ) {
      stmp.Format(_T(" SettlementName=\"%s\""), Win1251ToUTF8(szSettlementName));
      s += stmp;
    }
    BOOL bDistrictInCity = IsDistrictInCity(szCountry, szRegion, szDistrict, szCity);
    TCHAR cSettlementTypeId = szSettlementName.IsEmpty() ? '0' : GetSettlementTypeId(szFullCity, bDistrictInCity);
    stmp.Format(_T(" SettlementTypeId=\"%c\""), cSettlementTypeId);
    s += stmp;
  
    // CityDistrict - "Район населеного пункту"
    CString szCityDistrict = bDistrictInCity ? _T("") : szDistrict;
    if ( g_bWriteEmptyTags || false==szCityDistrict.IsEmpty() ) {
      stmp.Format(_T(" CityDistrict=\"%s\""), Win1251ToUTF8(szCityDistrict));
      s += stmp;
    }
    // Street - "Вулиця"
    TCHAR ccStreetTypeId;
    CString szStreetTypeName, szStreetTypeToken;
    ParseStreet(szStreet, szStreetTypeToken, ccStreetTypeId, szStreetTypeName);
    if ( szStreet.IsEmpty() ) {
      cStreetTypeId = '0';
    }

    if ( cStreetTypeId==0 ) {
      cStreetTypeId = ccStreetTypeId;
    }

    if ( false==szStreetTypeName.IsEmpty() ) {
      szStreet.Replace(szStreetTypeName, _T(""));
    }
    if ( g_bWriteEmptyTags || false==szStreet.IsEmpty() ) {
      stmp.Format(_T(" Street=\"%s\""), Win1251ToUTF8(szStreet));
      s += stmp;
    }
    // StreetTypeId - "Тип вулиці" ( значення із словника «Бульвар» = 3,
    //                               «Вулиця» = 1,
    //                               «Інший» = 6,
    //                               «Площа» = 2,
    //                               «Провулок» = 5,
    //                               «Проспект» = 4,
    //                               «не вказано» = 0)
    stmp.Format(_T(" StreetTypeId=\"%c\""), cStreetTypeId);
    s += stmp;
    // StreetTypeName - "Тип вулиці" текстове значення, якщо StreetTypeId відмінне від 0, значення ігнорується
    if ( g_bWriteEmptyTags || false==szStreetTypeName.IsEmpty() ) {
      stmp.Format(_T(" StreetTypeName=\"%s\""), Win1251ToUTF8(szStreetTypeName));
      s += stmp;
    }
    // ZipCode - "Поштовий індекс"
    if ( g_bWriteEmptyTags ) {
      stmp = _T(" ZipCode=\"\"");
      s += stmp;
    }
    // BuildNumb - "Номер будинку"
    TCHAR BuildType;
    CString szBuildNumb, szBuildExtNumb;
    ParseBuildNumb(szBuild, szBuildNumb, szBuildExtNumb, BuildType);
    if ( g_bWriteEmptyTags || false==szBuildNumb.IsEmpty() ) {
      stmp.Format(_T(" BuildNumb=\"%s\""), Win1251ToUTF8(szBuildNumb));
      s += stmp;
    }
    // BuildType - "Тип будівлі" («Корпус» = 1, «Секція» = 2, «не вказано» = 0)
    stmp.Format(_T(" BuildType=\"%c\""), BuildType);
    s += stmp;
    // BuildExtNumb - "Номер" (корпусу, секції)
    if ( g_bWriteEmptyTags || false==szBuildExtNumb.IsEmpty() ) {
      stmp.Format(_T(" BuildExtNumb=\"%s\""), Win1251ToUTF8(szBuildExtNumb));
      s += stmp;
    }
    // ApartNumb - "Номер квартири"
    if ( g_bWriteEmptyTags || false==szApartNumb.IsEmpty() ) {
      stmp.Format(_T(" ApartNumb=\"%s\""), Win1251ToUTF8(szApartNumb));
      s += stmp;
    }

    s += _T(" />\r\n");
    xml.WriteString(s);
  }
  xml.WriteFormat(_T("%s</Addresses>\r\n"), spaces);

  if ( NULL==szDeclarantRole ) {
    xml.WriteString(_T("      </Person>\r\n"));
  }
}

//
// Для ребенка
// 
void MakePersonTag(CRSBirthes& rs,
                   CXmlFile& xml,
                   LPCTSTR  szSurname,
                   LPCTSTR  szName,
                   LPCTSTR  szPatronymic,
                   BOOL     fGender,
                   CString& szBirthDate,
                   CString& szCountry,
                   CString& szRegion,
                   CString& szFullCity,
                   CString& szDistrict
                   )
{
  CString s, stmp, spaces(' ', 8);
  xml.WriteFormat(_T("      <Person Role=\"1\">\r\n"));

  // <!-- "Прізвище" -->
  xml.WriteFormat( _T("%s<Surname>%s</Surname>\r\n"), spaces, Win1251ToUTF8(szSurname) );
  // <!-- "Власне ім’я" -->
  xml.WriteFormat( _T("%s<Name>%s</Name>\r\n"), spaces, Win1251ToUTF8(szName) );
  // <!-- "По батькові" -->
  xml.WriteFormat( _T("%s<Patronymic>%s</Patronymic>\r\n"), spaces, Win1251ToUTF8(szPatronymic) );
  // <!-- "Стать 1" ( значення із словника «Ч» = 1, «Ж» = 2, «Інше» = 3) -->
  xml.WriteFormat( _T("%s<Gender>%c</Gender>\r\n"), spaces, fGender ? '1' : '2');
  // <!-- Дата народження -->
  if ( g_bWriteEmptyTags || false==szBirthDate.IsEmpty() ) {
    xml.WriteFormat( _T("%s<BirthDate>%s</BirthDate>\r\n"), spaces, szBirthDate);
  }

  xml.WriteFormat(_T("%s<Addresses>\r\n"), spaces);
  // <!-- Відомості про адресу батька -->
  {
   /*
    <!-- опис для всіх адрес
    AddressType - тип адреси ( значення із словника «місце проживання або реєстрації» = 1, «місце народження» = 2, «місце смерті» = 3)
    CountryType - "Тип адреси (Країна)" ( значення із словника «Україна» = 1, «Інша держава» = 2, «не вказано» = 3, якщо CountryType = 3, інші атрибути можна не вказувати, вважається, що адреса не вказана)
    CountryName - "Країна (Інша)" (вказувати, якшо CountryType = 2, інакше тег можна не вказувати)
    RegionId    - "Регіон 1" (вказувати, якшо CountryType = 1, інакше тег можна не вказувати), може приймати значення з Таблиці 1            
    RegionName  - "Регіон 2" (вказувати, якшо CountryType = 2, інакше тег можна не вказувати), може приймати значення з Таблиці 1
    RegionTypeId - "Тип регіону" ( значення із словника «Місто» = 1, «Область» = 2, «не вказано» = 0)
    DistrictName - "Район"
    DistrictTypeId - "Тип району" ( значення із словника «Місто» = 1, «Район» = 2, «не вказано» = 0)
    SettlementName - "Населений пункт"
    SettlementTypeId - "Тип населеного пункту" ( значення із словника «Місто» = 1, 
              «Район» = 2, 
              «Селище» = 5, 
              «Селище міського типу» = 3,
              «Селищна рада» = 8,
              «Село» = 4,
              «Сільрада» = 6
              «не вказано» = 0)
    CityDistrict - "Район населеного пункту"
    Street - "Вулиця"
    StreetTypeId - "Тип вулиці" ( значення із словника «Бульвар» = 3,
                                  «Вулиця» = 1,
                                  «Інший» = 6,
                                  «Площа» = 2,
                                  «Провулок» = 5,
                                  «Проспект» = 4,
                                  «не вказано» = 0)
    StreetTypeName - "Тип вулиці" текстове значення, якщо StreetTypeId відмінне від 0, значення ігнорується
    ZipCode - "Поштовий індекс"
    BuildNumb - "Номер будинку"
    BuildType - "Тип будівлі" («Корпус» = 1, «Секція» = 2, «не вказано» = 0)
    BuildExtNumb - "Номер" (корпусу, секції)
    ApartNumb - "Номер квартири"
    -->
   */
    CString spaces(' ', 10);
    TCHAR cCountryType = GetCountryType(szCountry);
    s.Format( _T("%s<Address AddressType=\"2\" CountryType=\"%c\""), spaces, cCountryType);

    CString szCity     = GetCity(szFullCity);

    if ( szCountry.IsEmpty() && szFullCity.IsEmpty() ) {
      szCountry.Empty();
    }
    
    int nRegionId = GetRegionId(szRegion, szCity);

    // RegionId    - "Регіон 1" (вказувати, якшо CountryType = 1, інакше тег можна не вказувати), може приймати значення з Таблиці 1
    if ( '1'==cCountryType ) {
      stmp.Format(_T(" RegionId=\"%d\""), nRegionId);
      s += stmp;
    }
    // RegionName  - "Регіон 2" (вказувати, якшо CountryType = 2, інакше тег можна не вказувати), може приймати значення з Таблиці 1
    if ( '2'==cCountryType ) {
      if ( g_bWriteEmptyTags || false==szRegion.IsEmpty() ) {
        stmp.Format(_T(" CountryName=\"%s\""), Win1251ToUTF8(szRegion));
        s += stmp;
      }
    }
    // RegionTypeId - "Тип регіону" ( значення із словника «Місто» = 1, «Область» = 2, «не вказано» = 0)
    stmp.Format(_T(" RegionTypeId=\"%c\""), GetRegionTypeId(szRegion, szCity));
    s += stmp;
    // DistrictName - "Район"
    CString szDistrictName;
    CString szSettlementName;
    TCHAR  cDistrictTypeId = GetDistrictTypeId(szCountry, szRegion, szDistrict, szCity, szDistrictName, szSettlementName);
    if ( g_bWriteEmptyTags || false==szDistrictName.IsEmpty() ) {
      stmp.Format(_T(" DistrictName=\"%s\""), Win1251ToUTF8(szDistrictName));
      s += stmp;
    }
    // DistrictTypeId - "Тип району" ( значення із словника «Місто» = 1, «Район» = 2, «не вказано» = 0)
    stmp.Format(_T(" DistrictTypeId=\"%c\""), cDistrictTypeId);
    s += stmp;

    // SettlementName - "Населений пункт"
    if ( g_bWriteEmptyTags || false==szSettlementName.IsEmpty() ) {
      stmp.Format(_T(" SettlementName=\"%s\""), Win1251ToUTF8(szSettlementName));
      s += stmp;
    }
    BOOL bDistrictInCity = IsDistrictInCity(szCountry, szRegion, szDistrict, szCity);
    TCHAR cSettlementTypeId = szSettlementName.IsEmpty() ? '0' : GetSettlementTypeId(szFullCity, bDistrictInCity);
    stmp.Format(_T(" SettlementTypeId=\"%c\""), cSettlementTypeId);
    s += stmp;
  
    // CityDistrict - "Район населеного пункту"
    CString szCityDistrict = bDistrictInCity ? _T("") : szDistrict;
    if ( g_bWriteEmptyTags || false==szCityDistrict.IsEmpty() ) {
      stmp.Format(_T(" CityDistrict=\"%s\""), Win1251ToUTF8(szCityDistrict));
      s += stmp;
    }
    s += _T(" />\r\n");
    xml.WriteString(s);
  }
  s.Format(_T("%s</Addresses>\r\n"), spaces);
  xml.WriteString(s);

  xml.WriteString(_T("      </Person>\r\n"));
}


//
// Для свидетелей
// 
void MakePersonTag(/*CRSBirthes& rs,*/
                   CXmlFile& xml,
                   LPCTSTR szSurname,
                   LPCTSTR szName,
                   LPCTSTR szPatronymic,
                   CString& szCountry,
                   CString& szRegion,
                   CString& szCity,
                   TCHAR&  cSettlementTypeId,
                   CString& szDistrict,
                   CString& szStreet,
                   TCHAR&  cStreetTypeId,
                   CString& szBuild,
                   CString& szApartNumb,
                   int nDocType,
                   CString& szDocSeria,
                   CString& szDocNum,
                   CString& szDocDate,
                   CString& szDocBy
                  )
{
  CString s, stmp, spaces(' ', 8);


  xml.WriteFormat(_T("      <Person Role=\"12\">\r\n"));

  // <!-- "Прізвище" -->
  xml.WriteFormat( _T("%s<Surname>%s</Surname>\r\n"), spaces, Win1251ToUTF8(szSurname) );
  // <!-- "Власне ім’я" -->
  xml.WriteFormat( _T("%s<Name>%s</Name>\r\n"), spaces, Win1251ToUTF8(szName) );
  // <!-- "По батькові" -->
  xml.WriteFormat( _T("%s<Patronymic>%s</Patronymic>\r\n"), spaces, Win1251ToUTF8(szPatronymic) );


  xml.WriteFormat(_T("%s<Addresses>\r\n"), spaces);
  // <!-- Відомості про адресу батька -->
  {
   /*
    <!-- опис для всіх адрес
    AddressType - тип адреси ( значення із словника «місце проживання або реєстрації» = 1, «місце народження» = 2, «місце смерті» = 3)
    CountryType - "Тип адреси (Країна)" ( значення із словника «Україна» = 1, «Інша держава» = 2, «не вказано» = 3, якщо CountryType = 3, інші атрибути можна не вказувати, вважається, що адреса не вказана)
    CountryName - "Країна (Інша)" (вказувати, якшо CountryType = 2, інакше тег можна не вказувати)
    RegionId    - "Регіон 1" (вказувати, якшо CountryType = 1, інакше тег можна не вказувати), може приймати значення з Таблиці 1            
    RegionName  - "Регіон 2" (вказувати, якшо CountryType = 2, інакше тег можна не вказувати), може приймати значення з Таблиці 1
    RegionTypeId - "Тип регіону" ( значення із словника «Місто» = 1, «Область» = 2, «не вказано» = 0)
    DistrictName - "Район"
    DistrictTypeId - "Тип району" ( значення із словника «Місто» = 1, «Район» = 2, «не вказано» = 0)
    SettlementName - "Населений пункт"
    SettlementTypeId - "Тип населеного пункту" ( значення із словника «Місто» = 1, 
              «Район» = 2, 
              «Селище» = 5, 
              «Селище міського типу» = 3,
              «Селищна рада» = 8,
              «Село» = 4,
              «Сільрада» = 6
              «не вказано» = 0)
    CityDistrict - "Район населеного пункту"
    Street - "Вулиця"
    StreetTypeId - "Тип вулиці" ( значення із словника «Бульвар» = 3,
                                  «Вулиця» = 1,
                                  «Інший» = 6,
                                  «Площа» = 2,
                                  «Провулок» = 5,
                                  «Проспект» = 4,
                                  «не вказано» = 0)
    StreetTypeName - "Тип вулиці" текстове значення, якщо StreetTypeId відмінне від 0, значення ігнорується
    ZipCode - "Поштовий індекс"
    BuildNumb - "Номер будинку"
    BuildType - "Тип будівлі" («Корпус» = 1, «Секція» = 2, «не вказано» = 0)
    BuildExtNumb - "Номер" (корпусу, секції)
    ApartNumb - "Номер квартири"
    -->
   */
    CString spaces(' ', 10);
    TCHAR cCountryType = GetCountryType(szCountry);
    s.Format( _T("%s<Address AddressType=\"1\" CountryType=\"%c\""), spaces, cCountryType);

    // CString szCity     = GetCity(szFullCity);

    if ( szCountry.IsEmpty() && szCity.IsEmpty() ) {
      szRegion.Empty();
    }

    int nRegionId = GetRegionId(szRegion, szCity);

    // RegionId    - "Регіон 1" (вказувати, якшо CountryType = 1, інакше тег можна не вказувати), може приймати значення з Таблиці 1
    if ( '1'==cCountryType ) {
      stmp.Format(_T(" RegionId=\"%d\""), nRegionId);
      s += stmp;
    }
    // RegionName  - "Регіон 2" (вказувати, якшо CountryType = 2, інакше тег можна не вказувати), може приймати значення з Таблиці 1
    if ( '2'==cCountryType ) {
      if ( g_bWriteEmptyTags || false==szRegion.IsEmpty() ) {
        stmp.Format(_T(" CountryName=\"%s\""), Win1251ToUTF8(szRegion));
        s += stmp;
      }
    }
    // RegionTypeId - "Тип регіону" ( значення із словника «Місто» = 1, «Область» = 2, «не вказано» = 0)
    stmp.Format(_T(" RegionTypeId=\"%c\""), GetRegionTypeId(szRegion, szCity));
    s += stmp;
    // DistrictName - "Район"
    CString szDistrictName;
    CString szSettlementName;
    // DistrictTypeId - "Тип району" ( значення із словника «Місто» = 1, «Район» = 2, «не вказано» = 0)
    TCHAR  cDistrictTypeId = GetDistrictTypeId(szCountry, szRegion, szDistrict, szCity, szDistrictName, szSettlementName);


    // DistrictName - "Район"
    if ( g_bWriteEmptyTags || false==szDistrictName.IsEmpty() ) {
      stmp.Format(_T(" DistrictName=\"%s\""), Win1251ToUTF8(szDistrictName));
      s += stmp;
    }
    stmp.Format(_T(" DistrictTypeId=\"%c\""), cDistrictTypeId);
    s += stmp;

    // SettlementName - "Населений пункт"
    if ( g_bWriteEmptyTags || false==szSettlementName.IsEmpty() ) {
      stmp.Format(_T(" SettlementName=\"%s\""), Win1251ToUTF8(szSettlementName));
      s += stmp;
    }
    BOOL bDistrictInCity = IsDistrictInCity(szCountry, szRegion, szDistrict, szCity);
    TCHAR cSettlementTypeId = szSettlementName.IsEmpty() ? '0' : GetSettlementTypeId(szCity, bDistrictInCity);
    stmp.Format(_T(" SettlementTypeId=\"%c\""), cSettlementTypeId);
    s += stmp;
  
    // CityDistrict - "Район населеного пункту"
    CString szCityDistrict = bDistrictInCity ? _T("") : szDistrict;
    if ( g_bWriteEmptyTags || false==szCityDistrict.IsEmpty() ) {
      stmp.Format(_T(" CityDistrict=\"%s\""), Win1251ToUTF8(szCityDistrict));
      s += stmp;
    }
    // Street - "Вулиця"
    /*
    TCHAR cStreetTypeId;
    CString szStreetTypeName, szStreetTypeToken;
    ParseStreet(szStreet, szStreetTypeToken, cStreetTypeId, szStreetTypeName);
    */
    if ( szStreet.IsEmpty() ) {
      cStreetTypeId = '0';
    }
    /*
    if ( false==szStreetTypeName.IsEmpty() ) {
      szStreet.Replace(szStreetTypeName, _T(""));
    }
    */
    if ( g_bWriteEmptyTags || false==szStreet.IsEmpty() ) {
      stmp.Format(_T(" Street=\"%s\""), Win1251ToUTF8(szStreet));
      s += stmp;
    }
    // StreetTypeId - "Тип вулиці" ( значення із словника «Бульвар» = 3,
    //                               «Вулиця» = 1,
    //                               «Інший» = 6,
    //                               «Площа» = 2,
    //                               «Провулок» = 5,
    //                               «Проспект» = 4,
    //                               «не вказано» = 0)
    stmp.Format(_T(" StreetTypeId=\"%c\""), cStreetTypeId);
    s += stmp;
    // StreetTypeName - "Тип вулиці" текстове значення, якщо StreetTypeId відмінне від 0, значення ігнорується
    /*
    if ( g_bWriteEmptyTags || false==szStreetTypeName.IsEmpty() ) {
      stmp.Format(_T(" StreetTypeName=\"%s\""), Win1251ToUTF8(szStreetTypeName));
      s += stmp;
    }
    */
    // BuildNumb - "Номер будинку"
    TCHAR BuildType;
    CString szBuildNumb, szBuildExtNumb;
    ParseBuildNumb(szBuild, szBuildNumb, szBuildExtNumb, BuildType);
    if ( g_bWriteEmptyTags || false==szBuildNumb.IsEmpty() ) {
      stmp.Format(_T(" BuildNumb=\"%s\""), Win1251ToUTF8(szBuildNumb));
      s += stmp;
    }
    // BuildType - "Тип будівлі" («Корпус» = 1, «Секція» = 2, «не вказано» = 0)
    stmp.Format(_T(" BuildType=\"%c\""), BuildType);
    s += stmp;
    // BuildExtNumb - "Номер" (корпусу, секції)
    if ( g_bWriteEmptyTags || false==szBuildExtNumb.IsEmpty() ) {
      stmp.Format(_T(" BuildExtNumb=\"%s\""), Win1251ToUTF8(szBuildExtNumb));
      s += stmp;
    }
    // ApartNumb - "Номер квартири"
    if ( g_bWriteEmptyTags || false==szApartNumb.IsEmpty() ) {
      stmp.Format(_T(" ApartNumb=\"%s\""), Win1251ToUTF8(szApartNumb));
      s += stmp;
    }

    s += _T(" />\r\n");
    xml.WriteString(s);
  }
  xml.WriteFormat(_T("%s</Addresses>\r\n"), spaces);

  // <!-- "Організація" -->
  xml.WriteFormat(_T("%s<Organization></Organization>\r\n"), spaces);
  // <!-- Відомості про документ, що посвідчує особу -->
  xml.WriteFormat(_T("%s<DocType>%d</DocType>\r\n"), spaces, nDocType);
  // <!-- "Серія та номер" -->
  xml.WriteFormat(_T("%s<DocSeriaNumber>%s %s</DocSeriaNumber>\r\n"),
                     spaces, Win1251ToUTF8(szDocSeria), Win1251ToUTF8(szDocNum));

  // <!-- "Ким виданий" -->
  xml.WriteFormat(_T("%s<DocOrgan>%s</DocOrgan>\r\n"), spaces, Win1251ToUTF8(szDocBy));
  // <!-- "Дата видачі" -->
  xml.WriteFormat(_T("%s<DocDate>%s</DocDate>\r\n"), spaces, szDocDate);


  xml.WriteString(_T("      </Person>\r\n"));
}

BOOL IsLegalEntity(const CString& sz) {
  CCyrString s(sz);
  s.MakeLower();
  if ( s.Find(_T("представник"))  >= 0 ||
       s.Find(_T("свіпробітник")) >= 0 || 
       s.Find(_T("акушер"))       >= 0 || 
       s.Find(_T("працівник"))    >= 0 || 
       s.Find(_T("лікар"))        >= 0 || 
       s.Find(_T("медсестра"))    >= 0 ) 
  {
    return true;
  }
  return false;
}
//
//
//
void ParseBirthDeclarant(CRSBirthes& rs, CXmlFile& xml,
                         CString& szDeclRole,
                         CString& szDeclSurname,
                         CString& szDeclName,
                         CString& szDeclPatronymic
                        )
{
  szDeclRole = "3";  // Інша особа

  CString szDeclarant        = rs.m_DECLARANT_NAME;
  CString szDeclarantAddress = rs.m_DECLARANT_ADDRESS;

  if ( rs.IsFatherDeclarant() ) {
    szDeclRole = _T("1");    // Батько
  }
  else if ( rs.IsMotherDeclarant() ) {
    szDeclRole = _T("2");  // Мати
  }
  else if ( IsLegalEntity(szDeclarant) || IsLegalEntity(szDeclarantAddress) ) {
    szDeclRole = _T("10");  // Юридична особа
  }

  if ( szDeclRole==_T("1") ) { // Заявник - батько
    MakePersonTag(rs, xml, PERSON_ROLE_DECLARANT, szDeclRole, 
                  rs.m_FATHER_SURNAME,
                  rs.m_FATHER_NAME,
                  rs.m_FATHER_PATRONYMIC,
                  NULL, // LPCTSTR szCitizenship,
                  NULL, // LPCTSTR szBirthDate,
                  rs.m_FATHER_COUNTRY,
                  rs.m_FATHER_REGION,
                  rs.m_FATHER_CITY,
                  rs.m_FATHER_DISTRICT,
                  rs.m_FATHER_STREET,
                  0,
                  rs.m_FATHER_HOUSE,
                  rs.m_FATHER_FLAT
                 );
  }
  else if ( szDeclRole==_T("2") ) { // Заявник - мати
    MakePersonTag(rs, xml, PERSON_ROLE_DECLARANT, szDeclRole, 
                  rs.m_MOTHER_SURNAME,
                  rs.m_MOTHER_NAME,
                  rs.m_MOTHER_PATRONYMIC,
                  NULL, // LPCTSTR szCitizenship,
                  NULL, // LPCTSTR szBirthDate,
                  rs.m_MOTHER_COUNTRY,
                  rs.m_MOTHER_REGION,
                  rs.m_MOTHER_CITY,
                  rs.m_MOTHER_DISTRICT,
                  rs.m_MOTHER_STREET,
                  0,
                  rs.m_MOTHER_HOUSE,
                  rs.m_MOTHER_FLAT
                 );
  }
  else {

    CString szSurname, szName, szPatronymic, szOrganization;
    rs.ParseDeclarantFIO(szSurname, szName, szPatronymic, szOrganization);

    if ( false==rs.m_MOTHER_STREET.IsEmpty() && rs.m_DECLARANT_ADDRESS.Find(rs.m_MOTHER_STREET)>=0 &&
         false==rs.m_MOTHER_HOUSE.IsEmpty() && rs.m_DECLARANT_ADDRESS.Find(rs.m_MOTHER_HOUSE)>=0
       )
    {
      MakePersonTag(rs, xml, PERSON_ROLE_DECLARANT, szDeclRole, 
                    szSurname,
                    szName,
                    szPatronymic,
                    NULL, // LPCTSTR szCitizenship,
                    NULL, // LPCTSTR szBirthDate,
                    rs.m_MOTHER_COUNTRY,
                    rs.m_MOTHER_REGION,
                    rs.m_MOTHER_CITY,
                    rs.m_MOTHER_DISTRICT,
                    rs.m_MOTHER_STREET,
                    0,
                    rs.m_MOTHER_HOUSE,
                    rs.m_MOTHER_FLAT
                   );
    }
    else if ( false==rs.m_FATHER_STREET.IsEmpty() && rs.m_DECLARANT_ADDRESS.Find(rs.m_FATHER_STREET)>=0 &&
              false==rs.m_FATHER_HOUSE.IsEmpty() && rs.m_DECLARANT_ADDRESS.Find(rs.m_FATHER_HOUSE)>=0
            )
    {
      MakePersonTag(rs, xml, PERSON_ROLE_DECLARANT, szDeclRole, 
                    szSurname,
                    szName,
                    szPatronymic,
                    NULL, // LPCTSTR szCitizenship,
                    NULL, // LPCTSTR szBirthDate,
                    rs.m_FATHER_COUNTRY,
                    rs.m_FATHER_REGION,
                    rs.m_FATHER_CITY,
                    rs.m_FATHER_DISTRICT,
                    rs.m_FATHER_STREET,
                    0,
                    rs.m_FATHER_HOUSE,
                    rs.m_FATHER_FLAT
                   );
    }
    else {
      CString szCountry, szRegion, szDistrict, szCity, szStreet, szBuild, szFlat;
      TCHAR cStreetType = '0';

      rs.ParseDeclarantAddress(szCountry, szRegion, szDistrict, szCity, cStreetType, szStreet, szBuild, szFlat);


      MakePersonTag(rs, xml, PERSON_ROLE_DECLARANT, szDeclRole, 
                    szSurname,
                    szName,
                    szPatronymic,
                    NULL, // LPCTSTR szCitizenship,
                    NULL, // LPCTSTR szBirthDate,
                    szCountry,
                    szRegion,
                    szCity,
                    szDistrict,
                    szStreet,
                    cStreetType,
                    szBuild,
                    szFlat
                  );
    }
  }

  BYTE bDocType       = GetFieldByte  (rs, _T("DECLARANT_PASSPORT_TYPE"));
  CString szDocSeria  = GetFieldString(rs, _T("DECLARANT_PASSPORT_SERIA"));
  CString szDocNumber = GetFieldString(rs, _T("DECLARANT_PASSPORT_NUMBER"));
  CString szDocDate   = GetFieldDate  (rs, _T("DECLARANT_PASSPORT_DATE"));
  CString szDocBy     = GetFieldString(rs, _T("DECLARANT_PASSPORT_BY"));
  LPCTSTR szDocType = _T("0");

  xml.WriteString(_T("        <Organization></Organization>\r\n"));

  if ( false==szDocSeria.IsEmpty() || false==szDocNumber.IsEmpty() ) {
    szDocType = GetDocType(bDocType);
    xml.WriteFormat(_T("        <DocType>%s</DocType>\r\n"), szDocType); 
    xml.WriteFormat(_T("        <DocSeriaNumber>%s %s</DocSeriaNumber>\r\n"), Win1251ToUTF8(szDocSeria), Win1251ToUTF8(szDocNumber));
    xml.WriteFormat(_T("        <DocOrgan>%s</DocOrgan>\r\n"), Win1251ToUTF8(szDocBy));
    xml.WriteFormat(_T("        <DocDate>%s</DocDate>\r\n"), szDocDate);
  }
  else {
    xml.WriteString(_T("        <DocType>0</DocType>\r\n"));
  }

  xml.WriteString(_T("      </Person>\r\n"));
}

void MakeDeclarantPersonTag(CXmlFile& xml, TCHAR cDeclarantRole,
                            const CString& szSurname, const CString& szName, const CString& szPatronymic,
                            const CString& szCountry,
                            const CString& szRegion,
                            const CString& szFullCity,
                            const CString& szDistrict,
                            CString& szStreet, const CString& szHouse, const CString& szFlat,
                            BYTE bDocType, const CString& szDocSeria, const CString& szDocNumber, const CString& szDocDate, const CString& szDocBy
                           )
{
  CString s, stmp, spaces(' ', 8);
  xml.WriteFormat(_T("      <Person Role=\"4\" DeclarantRole=\"%c\">\r\n"), cDeclarantRole);
  // <!-- "Прізвище" -->
  xml.WriteFormat( _T("%s<Surname>%s</Surname>\r\n"), spaces, Win1251ToUTF8(szSurname));
  // <!-- "Власне ім’я" -->
  xml.WriteFormat( _T("%s<Name>%s</Name>\r\n"), spaces, Win1251ToUTF8(szName) );
  // <!-- "По батькові" -->
  xml.WriteFormat( _T("%s<Patronymic>%s</Patronymic>\r\n"), spaces, Win1251ToUTF8(szPatronymic) );

  xml.WriteFormat(_T("%s<Addresses>\r\n"), spaces);
  {
    CString spaces(' ', 10);
    TCHAR cCountryType = GetCountryType(szCountry);
    s.Format( _T("%s<Address AddressType=\"1\" CountryType=\"%c\""), spaces, cCountryType);
    CString szCity     = GetCity(szFullCity);
    int nRegionId = GetRegionId(szRegion, szCity);
    // RegionId    - "Регіон 1" (вказувати, якшо CountryType = 1, інакше тег можна не вказувати), може приймати значення з Таблиці 1
    if ( '1'==cCountryType ) {
      stmp.Format(_T(" RegionId=\"%d\""), nRegionId);
      s += stmp;
    }
    // RegionName  - "Регіон 2" (вказувати, якшо CountryType = 2, інакше тег можна не вказувати), може приймати значення з Таблиці 1
    if ( '2'==cCountryType ) {
      if ( g_bWriteEmptyTags || false==szRegion.IsEmpty() ) {
        stmp.Format(_T(" CountryName=\"%s\""), Win1251ToUTF8(szRegion));
        s += stmp;
      }
    }
    // RegionTypeId - "Тип регіону" ( значення із словника «Місто» = 1, «Область» = 2, «не вказано» = 0)
    stmp.Format(_T(" RegionTypeId=\"%c\""), GetRegionTypeId(szRegion, szCity));
    s += stmp;
    // DistrictName - "Район"
    CString szDistrictName;
    CString szSettlementName;
    // DistrictTypeId - "Тип району" ( значення із словника «Місто» = 1, «Район» = 2, «не вказано» = 0)
    TCHAR  cDistrictTypeId = GetDistrictTypeId(szCountry, szRegion, szDistrict, szCity, szDistrictName, szSettlementName);
    // DistrictName - "Район"
    if ( g_bWriteEmptyTags || false==szDistrictName.IsEmpty() ) {
      stmp.Format(_T(" DistrictName=\"%s\""), Win1251ToUTF8(szDistrictName));
      s += stmp;
    }
    stmp.Format(_T(" DistrictTypeId=\"%c\""), cDistrictTypeId);
    s += stmp;

    // SettlementName - "Населений пункт"
    if ( g_bWriteEmptyTags || false==szSettlementName.IsEmpty() ) {
      stmp.Format(_T(" SettlementName=\"%s\""), Win1251ToUTF8(szSettlementName));
      s += stmp;
    }
    BOOL bDistrictInCity = IsDistrictInCity(szCountry, szRegion, szDistrict, szCity);
    TCHAR cSettlementTypeId = szSettlementName.IsEmpty() ? '0' : GetSettlementTypeId(szFullCity, bDistrictInCity);
    stmp.Format(_T(" SettlementTypeId=\"%c\""), cSettlementTypeId);
    s += stmp;
    // CityDistrict - "Район населеного пункту"
    CString szCityDistrict = bDistrictInCity ? _T("") : szDistrict;
    if ( g_bWriteEmptyTags || false==szCityDistrict.IsEmpty() ) {
      stmp.Format(_T(" CityDistrict=\"%s\""), Win1251ToUTF8(szCityDistrict));
      s += stmp;
    }
    // Street - "Вулиця"
    TCHAR cStreetTypeId;
    CString szStreetTypeName, szStreetTypeToken;
    ParseStreet(szStreet, szStreetTypeToken, cStreetTypeId, szStreetTypeName);
    if ( szStreet.IsEmpty() ) {
      cStreetTypeId = '0';
    }
    if ( false==szStreetTypeName.IsEmpty() ) {
      szStreet.Replace(szStreetTypeName, _T(""));
    }
    if ( g_bWriteEmptyTags || false==szStreet.IsEmpty() ) {
      stmp.Format(_T(" Street=\"%s\""), Win1251ToUTF8(szStreet));
      s += stmp;
    }
    // StreetTypeId - "Тип вулиці" ( значення із словника «Бульвар» = 3,
    //                               «Вулиця» = 1,
    //                               «Інший» = 6,
    //                               «Площа» = 2,
    //                               «Провулок» = 5,
    //                               «Проспект» = 4,
    //                               «не вказано» = 0)
    stmp.Format(_T(" StreetTypeId=\"%c\""), cStreetTypeId);
    s += stmp;
    // StreetTypeName - "Тип вулиці" текстове значення, якщо StreetTypeId відмінне від 0, значення ігнорується
    if ( g_bWriteEmptyTags || false==szStreetTypeName.IsEmpty() ) {
      stmp.Format(_T(" StreetTypeName=\"%s\""), Win1251ToUTF8(szStreetTypeName));
      s += stmp;
    }
    // ZipCode - "Поштовий індекс"
    if ( g_bWriteEmptyTags ) {
      stmp = _T(" ZipCode=\"\"");
      s += stmp;
    }
    // BuildNumb - "Номер будинку"
    TCHAR BuildType;
    CString szBuild, szBuildNumb, szBuildExtNumb;
    szBuild = szHouse;
    ParseBuildNumb(szBuild, szBuildNumb, szBuildExtNumb, BuildType);
    if ( g_bWriteEmptyTags || false==szBuildNumb.IsEmpty() ) {
      stmp.Format(_T(" BuildNumb=\"%s\""), Win1251ToUTF8(szBuildNumb));
      s += stmp;
    }
    // BuildType - "Тип будівлі" («Корпус» = 1, «Секція» = 2, «не вказано» = 0)
    stmp.Format(_T(" BuildType=\"%c\""), BuildType);
    s += stmp;
    // BuildExtNumb - "Номер" (корпусу, секції)
    if ( g_bWriteEmptyTags || false==szBuildExtNumb.IsEmpty() ) {
      stmp.Format(_T(" BuildExtNumb=\"%s\""), Win1251ToUTF8(szBuildExtNumb));
      s += stmp;
    }
    // ApartNumb - "Номер квартири"
    CString szApartNumb = szFlat;
    if ( g_bWriteEmptyTags || false==szApartNumb.IsEmpty() ) {
      stmp.Format(_T(" ApartNumb=\"%s\""), Win1251ToUTF8(szApartNumb));
      s += stmp;
    }
    s += _T(" />\r\n");
    xml.WriteString(s);
  }
  xml.WriteFormat(_T("%s</Addresses>\r\n"), spaces);
  xml.WriteString(_T("      </Person>\r\n"));
}

void ParseBirthDeclarants(CRSBirthes& rs, CXmlFile& xml, BOOL fBothInName) {
  if ( fBothInName || rs.AreParentsDeclarants() ) // Заявитель слева - отец, заявитель справа - мать.
  {
    MakeDeclarantPersonTag(xml, '1',
                           rs.m_FATHER_SURNAME,
                           rs.m_FATHER_NAME,
                           rs.m_FATHER_PATRONYMIC,
                           rs.m_FATHER_COUNTRY,
                           rs.m_FATHER_REGION,
                           rs.m_FATHER_CITY,
                           rs.m_FATHER_DISTRICT,
                           rs.m_FATHER_STREET,
                           rs.m_FATHER_HOUSE,
                           rs.m_FATHER_FLAT,
                           rs.m_DECLARANT_PASSPORT_TYPE,
                           rs.m_DECLARANT_PASSPORT_SERIA,
                           rs.m_DECLARANT_PASSPORT_NUMBER,
                           rs.m_DECLARANT_PASSPORT_DATE,
                           rs.m_DECLARANT_PASSPORT_BY
                          );

    BYTE bDocType = 0;
    CString szDocType   = rs.GetPassport2Type();
    CString szDocSeria  = rs.GetPassport2Seria();
    CString szDocNumber = rs.GetPassport2Number();
    CString szDocDate   = rs.GetPassport2Date();
    CString szDocBy     = rs.GetPassport2By();
    if ( false==szDocType.IsEmpty() ) {
      bDocType = (BYTE)atoi(szDocType);
    }
    MakeDeclarantPersonTag(xml, '2',
                           rs.m_MOTHER_SURNAME,
                           rs.m_MOTHER_NAME,
                           rs.m_MOTHER_PATRONYMIC,
                           rs.m_MOTHER_COUNTRY,
                           rs.m_MOTHER_REGION,
                           rs.m_MOTHER_CITY,
                           rs.m_MOTHER_DISTRICT,
                           rs.m_MOTHER_STREET,
                           rs.m_MOTHER_HOUSE,
                           rs.m_MOTHER_FLAT,
                           bDocType,
                           szDocSeria,
                           szDocNumber,
                           szDocDate,
                           szDocBy
                          );
  }
}

CString GetBirhNotice(const CString& sNotice) {
  CString s, szNotice;
  szNotice = sNotice;

  LPCTSTR szArray[] = { _T("Свідоцтво не видано."), _T("Свідоцтво не видане."), NULL };

  for( int i(0); szArray[i]; i++ ) {
    if ( szNotice.Find(szArray[i]) > 0 ) {
      szNotice = FindAndReplace(szNotice, szArray[i], _T(""), true);
    }
  }
  return szNotice;
}

/*
int GetClauseReasonType(CDaoRecordset& rs) {
  BYTE bType = GetFieldByte(rs, _T("SOURCE_TYPE"));
  CString szMemo = GetFieldString(rs, _T("NOTICE"));

  if ( szMemo.Find(_T("не є батьком")) >= 0 ) {
    return 1; // «Відповідно до статті 126 Сімейного кодексу України»
  }

  switch(bType) {
    case BIRTH_TYPE_AFFILIATION1  :
    case BIRTH_TYPE_AFFILIATION2  :
      return 1;
    case BIRTH_TYPE_MOTHER        :
      return 3;
    case BIRTH_TYPE_APPL          :
    case BIRTH_TYPE_APPLNUM       :
      if ( szMemo.Find(_T(" опікуськ")) > 0 || szMemo.Find(_T(" піклуван")) > 0 ) {
        return 5;
      }
      return 5;
  }

  return 2; // «Відповідно до статті 133 Сімейного кодексу України» = 2
}
*/

LPCTSTR GetBirhDocName(BOOL fIsAlive) {
  if ( false==fIsAlive ) {
    return _T("Свідоцтво про перинатальну смерть");
  }
  return _T("Медичне свідоцтво про народження");
}

CString GetWitnessPetitionInfo(CDaoRecordset& rs) {
  CString s;
  return s;
}
CString GetFatherReason(CDaoRecordset& rs) {
  CString s;
  return s;
}
int GetIsFatherFromDeclarant(const CString& szNotice) {
  if ( szNotice.Find(_T("Відомості про батька")) >= 0 ) {
    if ( szNotice.Find(_T("заявника"))>0 || szNotice.Find(_T("заявниці"))>0 ) {
      return 1; // Відомості про матір внесені за вказівкою заявника
    }
  }
  return 0; // Відомості про батька внесені НЕ за вказівкою заявника
}
int GetIsMotherFromDeclarant(const CString& szNotice) {
  if ( szNotice.Find(_T("Відомості про матір")) >= 0  || szNotice.Find(_T("Відомості про мати")) >= 0) {
    if ( szNotice.Find(_T("заявника"))>0 || szNotice.Find(_T("заявниці"))>0 ) {
      return 1; // Відомості про матір внесені за вказівкою заявника
    }
  }
  return 0; // Відомості про матір внесені НЕ за вказівкою заявника
}

void ConvertBirth(CDaoDatabase& db, LPCTSTR szOutFolder, LPCTSTR szFileMask, long nMaxOutRecords,
                  BOOL fPeriod, COleDateTime& odtFrom, COleDateTime& odtTill,
                  CProgressCtrl& ProgressBar, int& nCurProgressPos) {
  CRSBirthes rs(&db);

  long lRecords = 0, lRecNum = 1;
  CString s, spaces;

  CXmlFile xml;

  CMap<CString, LPCSTR, long, long> map;

  if ( nMaxOutRecords <= 0 ) {
    nMaxOutRecords = 1;
  }

  try {
    rs.Open(dbOpenTable, _T("[BIRTHES]"), dbReadOnly);
    rs.SetCurrentIndex(_T("NUMBER"));
    lRecords = rs.GetRecordCount();

    if ( lRecords > 0 ) {

      if ( false==CreateXMLFile(xml, szOutFolder, szFileMask, _T("Birth"), fPeriod, odtFrom, odtTill, lRecords, lRecNum, nMaxOutRecords) ) {
        // Error message here
        rs.Close();
        return;
      }
      xml.WriteString(g_szXMLHeader);
      xml.WriteString(_T("<ActRecords>\r\n"));

      BOOL bIsUALang;

      while( !rs.IsEOF() ) {
        CString szDeclSurname, szDeclName, szDeclPatronymic;
        nCurProgressPos++;

        ProgressBar.SetPos(nCurProgressPos);
        PeekAndPump();

        rs.Read();

        if ( IsEmptyRecord(rs) ) {
          rs.MoveNext();
          continue;
        }

        if ( fPeriod && false==rs.InPeriod(odtFrom, odtTill) ) {
          rs.MoveNext();
          continue;
        }

        CString szKey = rs.MakeKey();
        long lVal = 0;
        if ( map.Lookup(szKey, lVal) ) {
          rs.MoveNext();
          continue;
        }
        map.SetAt(szKey, rs.m_ID);


        BOOL fIsAlive = (BOOL)GetFieldByte(rs, _T("ALIVE_FLAG"));

        xml.WriteString(_T("  <ActRecord>\r\n"));
        // Parsing BIRTH record and writing to XML here

        spaces = CString(' ', 4);

		    COleDateTime odtDateReg;
		    GetFieldDate(rs, _T("DATEREG"), &odtDateReg);

        // <!-- Ідентифікатор сторонньої системи, Визначається представниками ДП «ІЦ» для кожної сторонньої системи -->
        xml.WriteFormat(_T("%s<ExtSystemId>%s</ExtSystemId>\r\n"), spaces, Win1251ToUTF8(g_szExtSystemId));
        // <!-- Ідентифікатор АЗ в сторонній системі -->
        xml.WriteFormat(_T("%s<ExtActRecordId>1%04d%lu</ExtActRecordId>\r\n"), spaces, odtDateReg.GetYear(), rs.m_ID);
        // <!-- "Актовий запис складено українською мовою" (значення true або false) -->
        bIsUALang = IsUALang(rs);
        xml.WriteFormat(_T("%s<IsUALang>%s</IsUALang>\r\n"), spaces, bIsUALang ? _T("true") : _T("false"));
        // <!-- "Мова, якою складено АЗ" (якщо IsUALang має значення true, тег можна не вказувати) -->
        if ( false==bIsUALang ) {
          // todo
        }
        // <!-- "Вид актового запису", для АЗ про народження завжди має значення рівне 3 -->
        xml.WriteFormat(_T("%s<Type>3</Type>\r\n"), spaces);
        // <!-- "Поновлений" (значення true або false) -->
        xml.WriteFormat(_T("%s<IsRestored>%s</IsRestored>\r\n"), spaces, (rs.m_RENEW & BIRTH_RENEW) ? _T("true") : _T("false"));
        // <!-- "Реєстрація з пропуском строку" (значення true або false) -->
        xml.WriteFormat(_T("%s<IsDelayedRegistration>%s</IsDelayedRegistration>\r\n"), spaces, (rs.m_RENEW & BIRTH_LONGTERM) ? _T("true") : _T("false"));
        // <!-- "АЗ з метричної книги" (значення true або false) -->
        xml.WriteFormat(_T("%s<IsMetricBook>false</IsMetricBook>\r\n"), spaces);
        // <!-- "Номер АЗ" -->
        xml.WriteFormat(_T("%s<Number>%lu</Number>\r\n"), spaces, GetFieldLong(rs, _T("NUMBER")));
        // <!-- "Дата складання АЗ" -->
        xml.WriteFormat(_T("%s<CompositionDate>%s</CompositionDate>\r\n"), spaces, GetFieldDate(rs, _T("DATEREG")));
        // <!-- Блок інформації про людей в АЗ -->
        xml.WriteFormat(_T("%s<Persons>\r\n"), spaces);
        {

          CString szDeclName    = GetFieldString(rs, _T("DECLARANT_NAME"));

          // <!-- Відомості про батька -->
          MakePersonTag(rs, xml, PERSON_ROLE_FATHER, NULL,
                        rs.m_FATHER_SURNAME, rs.m_FATHER_NAME, rs.m_FATHER_PATRONYMIC,
                        rs.m_FATHER_CITIZENSHIP, rs.m_FATHER_BIRTH_DATE,
                        rs.m_FATHER_COUNTRY, rs.m_FATHER_REGION, rs.m_FATHER_CITY, rs.m_FATHER_DISTRICT,
                        rs.m_FATHER_STREET, 0, rs.m_FATHER_HOUSE, rs.m_FATHER_FLAT);

          // <!-- Відомості про матір, де Role - роль людини в АЗ (для АЗ про народження, роль матері = 3) -->
          MakePersonTag(rs, xml, PERSON_ROLE_MOTHER, NULL,
                        rs.m_MOTHER_SURNAME, rs.m_MOTHER_NAME, rs.m_MOTHER_PATRONYMIC,
                        rs.m_MOTHER_CITIZENSHIP, rs.m_MOTHER_BIRTH_DATE,
                        rs.m_MOTHER_COUNTRY, rs.m_MOTHER_REGION, rs.m_MOTHER_CITY, rs.m_MOTHER_DISTRICT,
                        rs.m_MOTHER_STREET, 0, rs.m_MOTHER_HOUSE, rs.m_MOTHER_FLAT);

          // <!-- Відомості про дитину, де Role - роль людини в АЗ (для АЗ про народження, роль дитини = 1) -->
          MakePersonTag(rs, xml,
                        rs.m_SURNAME, rs.m_NAME, rs.m_PATRONYMIC, rs.m_SEX,
                        rs.m_BIRTH_DATE,
                        rs.m_BP_COUNTRY, rs.m_BP_REGION, rs.m_BP_CITY, rs.m_BP_DISTRICT
                       );

          CString szDeclarantRole = _T("3");
          BOOL fTwoDeclarants = rs.AreParentsDeclarants();

          if ( fTwoDeclarants || (rs.m_DECLARANT_TYPE==2 && rs.m_EXTNOTES.Find(_T("{П2:")) >= 0) ) {
            ParseBirthDeclarants(rs, xml, fTwoDeclarants);
          }
          else {
            ParseBirthDeclarant(rs, xml, szDeclarantRole, szDeclSurname, szDeclName, szDeclPatronymic);
          }

          if ( ParseG10(rs) ) {
            MakePersonTag(xml,
                          CWitnessDlg::m_Surname1,
                          CWitnessDlg::m_Name1,
                          CWitnessDlg::m_Patronymic1,
                          CWitnessDlg::m_Country1,
                          CWitnessDlg::m_Region1,
                          CWitnessDlg::m_City1,
                          CWitnessDlg::m_cCityType1,
                          CWitnessDlg::m_District1,
                          CWitnessDlg::m_Street1,
                          CWitnessDlg::m_cStreetType1,
                          CWitnessDlg::m_Build1,
                          CWitnessDlg::m_Flat1,
                          CWitnessDlg::m_DocType1,
                          CWitnessDlg::m_DocSeria1,
                          CWitnessDlg::m_DocNumber1,
                          CWitnessDlg::m_DocDate1,
                          CWitnessDlg::m_DocOrgan1
                         );

            MakePersonTag(xml,
                          CWitnessDlg::m_Surname2,
                          CWitnessDlg::m_Name2,
                          CWitnessDlg::m_Patronymic2,
                          CWitnessDlg::m_Country2,
                          CWitnessDlg::m_Region2,
                          CWitnessDlg::m_City2,
                          CWitnessDlg::m_cCityType2,
                          CWitnessDlg::m_District2,
                          CWitnessDlg::m_Street2,
                          CWitnessDlg::m_cStreetType2,
                          CWitnessDlg::m_Build2,
                          CWitnessDlg::m_Flat2,
                          CWitnessDlg::m_DocType2,
                          CWitnessDlg::m_DocSeria2,
                          CWitnessDlg::m_DocNumber2,
                          CWitnessDlg::m_DocDate2,
                          CWitnessDlg::m_DocOrgan2
                         );
          }

        }
        // 
        s.Format(_T("%s</Persons>\r\n"), spaces);
        xml.WriteString(s);

        s.Format(_T("%s<Certificates>\r\n"), spaces);
        xml.WriteString(s);
        {
          CString spaces = CString(' ', 6);
          CString stmp;

          stmp.Format(_T("%s<Certificate"), spaces);
          s = stmp;

          stmp.Format(_T(" IsRepeat=\"false\""));
          s += stmp;

          stmp.Format(_T(" Number=\"%s\""), Win1251ToUTF8(rs.m_CERTIFICATE_NUMBER) );
          s += stmp;

          stmp.Format(_T(" Seria=\"%s\""), Win1251ToUTF8(rs.m_CERTIFICATE_SERIA) );
          s += stmp;

          /*
          stmp.Format(_T(" GivingDate=\"%s\""), GetFieldDate(rs, _T("DATEREG")) );
          s += stmp;
          */
          s += _T(" GivingDate=\"\"");

          /*
          stmp.Format(_T(" OwnerSurname=\"%s\""), Win1251ToUTF8(szDeclSurname));
          s += stmp;
          */
          s += _T(" OwnerSurname=\"\"");

          /*
          stmp.Format(_T(" OwnerName=\"%s\""), Win1251ToUTF8(szDeclName));
          s += stmp;
          */
          s += _T(" OwnerName=\"\"");

          /*
          stmp.Format(_T(" OwnerPatronymic=\"%s\""), Win1251ToUTF8(szDeclPatronymic));
          s += stmp;
          */

          /*
          stmp.Format(_T(" Status=\"1\""));  // ???
          s += stmp;
          */
          s += _T(" Status=\"1\"  ChangeDate=\"\" ChangeReason=\"\"");

          stmp.Format(_T(" RacsType=\"%s\""), GetRagsType());
          s += stmp;

          stmp.Format(_T(" RacsRegion=\"%d\""), GetRagsRegionId());
          s += stmp;

          stmp.Format(_T(" RacsName=\"%s\""), Win1251ToUTF8(g_szRacsName));
          s += stmp;

          stmp.Format(_T(" RacsDirectorName=\"%s\"/>\r\n"), Win1251ToUTF8(g_szRacsDirectorName));
          s += stmp;
          
          xml.WriteString(s);
        }
        s.Format(_T("%s</Certificates>\r\n"), spaces);
        xml.WriteString(s);

        // RacsType - "Тип органу РАЦС" ( (значення із словника «Управління/відділ РАЦС» = 97, «Виконавчий орган с./сщ./міськ.рад» = 98)
        s.Format(_T("%s<RacsType>%s</RacsType>\r\n"), spaces, GetRagsType());
        xml.WriteString(s);

        // <!--"Регіон органу РАЦС" (може приймати значення з Таблиці 1 -->
        s.Format(_T("%s<RacsRegion>%d</RacsRegion>\r\n"), spaces, GetRagsRegionId());
        xml.WriteString(s);

        // <!-- "Орган РАЦС" (назва)-->
        s.Format(_T("%s<RacsName>%s</RacsName>\r\n"), spaces, Win1251ToUTF8(g_szRacsName));
        xml.WriteString(s);
        // <!-- "Керівник" -->
        if ( g_fWriteRacsDirectorName ) {
          s.Format(_T("%s<RacsDirectorName>%s</RacsDirectorName>\r\n"), spaces, Win1251ToUTF8(g_szRacsDirectorName));
          xml.WriteString(s);
        }
        // <!-- "Спеціаліст" -->
        if ( g_fWriteBirthSpecialistName ) {
          s.Format(_T("%s<RacsSpecialistName>%s</RacsSpecialistName>\r\n"), spaces, Win1251ToUTF8(g_szSpecialistNameForBirth));
          xml.WriteString(s);
        }
        // <!-- Посада (Керівника)-->
        if ( g_fWriteRacsDirectorPosition ) {
          s.Format(_T("%s<RacsDirectorPosition>%s</RacsDirectorPosition>\r\n"), spaces, Win1251ToUTF8(g_szRacsDirectorPos));
          xml.WriteString(s);
        }

        // <!-- Посада (Спеціаліста)-->
        if ( g_fWriteBirthSpecialistPosition ) {
          s.Format(_T("%s<RacsSpecialistPosition>%s</RacsSpecialistPosition>\r\n"), spaces, Win1251ToUTF8(g_szSpecialistPosForBirth));
          xml.WriteString(s);
        }

        // <!-- Кінець відомостей про орган РАЦС, який склав АЗ -->

        s.Format(_T("%s<Notes>\r\n"), spaces);
        xml.WriteString(s);
        {
          CString spaces = CString(' ', 6);
          s.Format(_T("%s<Note Text=\"%s\" Date=\"%s\"/>\r\n"), spaces, Win1251ToUTF8(GetBirhNotice(rs.m_NOTICE)), rs.m_DATEREG);
          xml.WriteString(s);
        }
        s.Format(_T("%s</Notes>\r\n"), spaces);
        xml.WriteString(s);
        // <!-- Кінець відомостей про відмітки -->

        s.Format(_T("%s<BirthInfo>\r\n"), spaces);
        xml.WriteString(s);
        {
          CString spaces = CString(' ', 6);

          xml.WriteFormat(_T("%s<BirthDocs>\r\n"), spaces);
          xml.WriteFormat(_T("%s<Document Name=\"%s\" Number=\"%s\" DeliveryDate=\"%s\" DeliveryOrgan=\"%s\" />\r\n"),
                          CString(' ', 6), 
                          Win1251ToUTF8(rs.m_szBirhDocName),
                          Win1251ToUTF8(rs.m_MEDICAL_CERTIFICATE_NUMBER),
                          rs.m_MEDICAL_CERTIFICATE_DATE,
                          Win1251ToUTF8(rs.m_MEDICAL_CERTIFICATE_BY)
                         );
          xml.WriteFormat(_T("%s</BirthDocs>\r\n"), spaces);
        
          //Тип статті сімейного кодекса за якою проводиться реєстрація народження
          /*
          s.Format(_T("%s<ClauseReasonType>%d</ClauseReasonType>\r\n"), spaces, GetClauseReasonType(rs));
          xml.WriteString(s);
          */
          // <!-- "Кількість народжених дітей (число від 0 до 10)" -->
          xml.WriteFormat(_T("%s<NewbornCount>%d</NewbornCount>\r\n"), spaces, GetFieldByte(rs, _T("NKIDS")));
          // <!-- Живонароджена (IsDeadBorn = 0) чи мертвонароджений (IsDeadBorn = 1) -->
          xml.WriteFormat(_T("%s<IsDeadBorn>%d</IsDeadBorn>\r\n"), spaces, GetFieldByte(rs, _T("ALIVE_FLAG")) ? 0 : 1);
          // <!-- Яка за рахунком дитина народилась у матері (число від 0 до 20) -->
          xml.WriteFormat(_T("%s<NewbornNumber>%d</NewbornNumber>\r\n"), spaces, GetFieldByte(rs, _T("BYCOUNT")));
          // <!-- Відомості про заяву свідків -->
          xml.WriteFormat(_T("%s<WitnessPetitionInfo>%s</WitnessPetitionInfo>\r\n"), spaces, GetWitnessPetitionInfo(rs));
          // <!-- Підстава запису відомостей про батька -->
          xml.WriteFormat(_T("%s<FatherReason></FatherReason>\r\n"), spaces);
          // <!-- Ознака для батька "Відомості внесені за вказівкою заявника" 
          //    0 - не за вказівкою заявника
          //    1 - за вказівкою заявника-->
          xml.WriteFormat(_T("%s<IsFatherFromDeclarant>%d</IsFatherFromDeclarant>\r\n"), spaces, GetIsFatherFromDeclarant(rs.m_NOTICE));
          //  <!-- Ознака для матері "Відомості внесені за вказівкою заявника" 
          //    0 - не за вказівкою заявника
          //    1 - за вказівкою заявника-->
          xml.WriteFormat(_T("%s<IsMotherFromDeclarant>%d</IsMotherFromDeclarant>\r\n"), spaces, GetIsMotherFromDeclarant(rs.m_NOTICE));

        }
        xml.WriteFormat(_T("%s</BirthInfo>\r\n"), spaces);
        xml.WriteString(_T("  </ActRecord>\r\n"));
        
        if ( lRecNum % nMaxOutRecords == 0) {
          xml.WriteString(_T("</ActRecords>\r\n"));
          xml.Close();
          if ( false==CreateXMLFile(xml, szOutFolder, szFileMask, _T("Birth"), fPeriod, odtFrom, odtTill, lRecords, lRecNum+1, nMaxOutRecords) ) {
            // Error message here
            break;
          }
          xml.WriteString(g_szXMLHeader);
          xml.WriteString(_T("<ActRecords>\r\n"));
        }
        rs.MoveNext();
        lRecNum++;
      }
    }
    rs.Close();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
    e->ReportError();
    #endif
    e->Delete();
  }
  if ( xml.m_pStream ) {
    xml.WriteString(_T("</ActRecords>"));
    xml.Close();
  }
}