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

#define BIRTH_TYPE_ACT          0 // ��� ��� ���������
#define BIRTH_TYPE_MOTHER       1 // ����� �����
#define BIRTH_TYPE_PARENTS      2 // ����� ������
#define BIRTH_TYPE_APPL         3 // �����
#define BIRTH_TYPE_APPLNUM      4 // ����� �
#define BIRTH_TYPE_AFFILIATION1 5 // ����� ��� �������� ����������
#define BIRTH_TYPE_AFFILIATION2 6 // ������ ����� ��� �������� ����������

CString GetNationality(const CString& szMemo, BOOL fFather) {
  CString szNationality, szFind;
  int nFound = -1;
  if ( fFather ) {
    szFind = _T("������������� ������:");
  }
  else {
    szFind = _T("������������� �����:");
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
// ��� ���� ��� ������
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

  // <!-- "�������" -->
  xml.WriteFormat( _T("%s<Surname>%s</Surname>\r\n"), spaces, Win1251ToUTF8(szSurname) );
  // <!-- "������ ���" -->
  xml.WriteFormat( _T("%s<Name>%s</Name>\r\n"), spaces, Win1251ToUTF8(szName) );
  // <!-- "�� �������" -->
  xml.WriteFormat( _T("%s<Patronymic>%s</Patronymic>\r\n"), spaces, Win1251ToUTF8(szPatronymic) );

  if ( szCitizenship ) {
    // <!-- "������������ 1" ( �������� �� �������� �����������(��) ������ = 1, ����� = 2) -->
    TCHAR cCitizenship = GetCitizenship( szCitizenship );
    xml.WriteFormat( _T("%s<Citizenship>%c</Citizenship>\r\n"), spaces, cCitizenship );
    if ( cCitizenship != '1' ) { // ���� ������������ != '1' (������)
      xml.WriteFormat( _T("%s<CitizenshipDescription>%s</CitizenshipDescription>\r\n"), spaces, Win1251ToUTF8(szCitizenship) );
    }

    // <!-- "�������������" -->
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

    // <!-- "���������������� �����" -->
    // <Idn></Idn> ���������� ���� ���
    if ( g_bWriteEmptyTags ) {
      xml.WriteFormat( _T("%s<Idn></Idn>\r\n"), spaces);
    }
  }

  if ( szBirthDate ) {
    // <!-- ���� ���������� -->
    CString szDate = szBirthDate;
    if ( g_bWriteEmptyTags || false==szDate.IsEmpty() ) {
      xml.WriteFormat( _T("%s<BirthDate>%s</BirthDate>\r\n"), spaces, szDate);
    }
  }

  xml.WriteFormat(_T("%s<Addresses>\r\n"), spaces);
  // <!-- ³������ ��� ������ ������ -->
  {
   /*
    <!-- ���� ��� ��� �����
    AddressType - ��� ������ ( �������� �� �������� ����� ���������� ��� ���������� = 1, ����� ����������� = 2, ����� ����� = 3)
    CountryType - "��� ������ (�����)" ( �������� �� �������� ������� = 1, ����� ������� = 2, ��� ������� = 3, ���� CountryType = 3, ���� �������� ����� �� ���������, ���������, �� ������ �� �������)
    CountryName - "����� (����)" (���������, ���� CountryType = 2, ������ ��� ����� �� ���������)
    RegionId    - "����� 1" (���������, ���� CountryType = 1, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1            
    RegionName  - "����� 2" (���������, ���� CountryType = 2, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1
    RegionTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ��������� = 2, ��� ������� = 0)
    DistrictName - "�����"
    DistrictTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ������ = 2, ��� ������� = 0)
    SettlementName - "��������� �����"
    SettlementTypeId - "��� ���������� ������" ( �������� �� �������� �̳��� = 1, 
              ������ = 2, 
              ������� = 5, 
              ������� ������� ���� = 3,
              �������� ���� = 8,
              ����� = 4,
              �ѳ������ = 6
              ��� ������� = 0)
    CityDistrict - "����� ���������� ������"
    Street - "������"
    StreetTypeId - "��� ������" ( �������� �� �������� �������� = 3,
                                  �������� = 1,
                                  ������ = 6,
                                  ������ = 2,
                                  ��������� = 5,
                                  ��������� = 4,
                                  ��� ������� = 0)
    StreetTypeName - "��� ������" �������� ��������, ���� StreetTypeId ������ �� 0, �������� ����������
    ZipCode - "�������� ������"
    BuildNumb - "����� �������"
    BuildType - "��� �����" (������� = 1, �������� = 2, ��� ������� = 0)
    BuildExtNumb - "�����" (�������, ������)
    ApartNumb - "����� ��������"
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

    // RegionId    - "����� 1" (���������, ���� CountryType = 1, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1
    if ( '1'==cCountryType ) {
      stmp.Format(_T(" RegionId=\"%d\""), nRegionId);
      s += stmp;
    }
    // RegionName  - "����� 2" (���������, ���� CountryType = 2, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1
    if ( '2'==cCountryType ) {
      if ( g_bWriteEmptyTags || false==szRegion.IsEmpty() ) {
        stmp.Format(_T(" CountryName=\"%s\""), Win1251ToUTF8(szRegion));
        s += stmp;
      }
    }
    // RegionTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ��������� = 2, ��� ������� = 0)
    stmp.Format(_T(" RegionTypeId=\"%c\""), GetRegionTypeId(szRegion, szCity));
    s += stmp;
    // DistrictName - "�����"
    CString szDistrictName;
    CString szSettlementName;
    // DistrictTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ������ = 2, ��� ������� = 0)
    TCHAR  cDistrictTypeId = GetDistrictTypeId(szCountry, szRegion, szDistrict, szCity, szDistrictName, szSettlementName);


    // DistrictName - "�����"
    if ( g_bWriteEmptyTags || false==szDistrictName.IsEmpty() ) {
      stmp.Format(_T(" DistrictName=\"%s\""), Win1251ToUTF8(szDistrictName));
      s += stmp;
    }
    stmp.Format(_T(" DistrictTypeId=\"%c\""), cDistrictTypeId);
    s += stmp;

    // SettlementName - "��������� �����"
    if ( g_bWriteEmptyTags || false==szSettlementName.IsEmpty() ) {
      stmp.Format(_T(" SettlementName=\"%s\""), Win1251ToUTF8(szSettlementName));
      s += stmp;
    }
    BOOL bDistrictInCity = IsDistrictInCity(szCountry, szRegion, szDistrict, szCity);
    TCHAR cSettlementTypeId = szSettlementName.IsEmpty() ? '0' : GetSettlementTypeId(szFullCity, bDistrictInCity);
    stmp.Format(_T(" SettlementTypeId=\"%c\""), cSettlementTypeId);
    s += stmp;
  
    // CityDistrict - "����� ���������� ������"
    CString szCityDistrict = bDistrictInCity ? _T("") : szDistrict;
    if ( g_bWriteEmptyTags || false==szCityDistrict.IsEmpty() ) {
      stmp.Format(_T(" CityDistrict=\"%s\""), Win1251ToUTF8(szCityDistrict));
      s += stmp;
    }
    // Street - "������"
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
    // StreetTypeId - "��� ������" ( �������� �� �������� �������� = 3,
    //                               �������� = 1,
    //                               ������ = 6,
    //                               ������ = 2,
    //                               ��������� = 5,
    //                               ��������� = 4,
    //                               ��� ������� = 0)
    stmp.Format(_T(" StreetTypeId=\"%c\""), cStreetTypeId);
    s += stmp;
    // StreetTypeName - "��� ������" �������� ��������, ���� StreetTypeId ������ �� 0, �������� ����������
    if ( g_bWriteEmptyTags || false==szStreetTypeName.IsEmpty() ) {
      stmp.Format(_T(" StreetTypeName=\"%s\""), Win1251ToUTF8(szStreetTypeName));
      s += stmp;
    }
    // ZipCode - "�������� ������"
    if ( g_bWriteEmptyTags ) {
      stmp = _T(" ZipCode=\"\"");
      s += stmp;
    }
    // BuildNumb - "����� �������"
    TCHAR BuildType;
    CString szBuildNumb, szBuildExtNumb;
    ParseBuildNumb(szBuild, szBuildNumb, szBuildExtNumb, BuildType);
    if ( g_bWriteEmptyTags || false==szBuildNumb.IsEmpty() ) {
      stmp.Format(_T(" BuildNumb=\"%s\""), Win1251ToUTF8(szBuildNumb));
      s += stmp;
    }
    // BuildType - "��� �����" (������� = 1, �������� = 2, ��� ������� = 0)
    stmp.Format(_T(" BuildType=\"%c\""), BuildType);
    s += stmp;
    // BuildExtNumb - "�����" (�������, ������)
    if ( g_bWriteEmptyTags || false==szBuildExtNumb.IsEmpty() ) {
      stmp.Format(_T(" BuildExtNumb=\"%s\""), Win1251ToUTF8(szBuildExtNumb));
      s += stmp;
    }
    // ApartNumb - "����� ��������"
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
// ��� �������
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

  // <!-- "�������" -->
  xml.WriteFormat( _T("%s<Surname>%s</Surname>\r\n"), spaces, Win1251ToUTF8(szSurname) );
  // <!-- "������ ���" -->
  xml.WriteFormat( _T("%s<Name>%s</Name>\r\n"), spaces, Win1251ToUTF8(szName) );
  // <!-- "�� �������" -->
  xml.WriteFormat( _T("%s<Patronymic>%s</Patronymic>\r\n"), spaces, Win1251ToUTF8(szPatronymic) );
  // <!-- "����� 1" ( �������� �� �������� �׻ = 1, �ƻ = 2, ����� = 3) -->
  xml.WriteFormat( _T("%s<Gender>%c</Gender>\r\n"), spaces, fGender ? '1' : '2');
  // <!-- ���� ���������� -->
  if ( g_bWriteEmptyTags || false==szBirthDate.IsEmpty() ) {
    xml.WriteFormat( _T("%s<BirthDate>%s</BirthDate>\r\n"), spaces, szBirthDate);
  }

  xml.WriteFormat(_T("%s<Addresses>\r\n"), spaces);
  // <!-- ³������ ��� ������ ������ -->
  {
   /*
    <!-- ���� ��� ��� �����
    AddressType - ��� ������ ( �������� �� �������� ����� ���������� ��� ���������� = 1, ����� ����������� = 2, ����� ����� = 3)
    CountryType - "��� ������ (�����)" ( �������� �� �������� ������� = 1, ����� ������� = 2, ��� ������� = 3, ���� CountryType = 3, ���� �������� ����� �� ���������, ���������, �� ������ �� �������)
    CountryName - "����� (����)" (���������, ���� CountryType = 2, ������ ��� ����� �� ���������)
    RegionId    - "����� 1" (���������, ���� CountryType = 1, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1            
    RegionName  - "����� 2" (���������, ���� CountryType = 2, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1
    RegionTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ��������� = 2, ��� ������� = 0)
    DistrictName - "�����"
    DistrictTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ������ = 2, ��� ������� = 0)
    SettlementName - "��������� �����"
    SettlementTypeId - "��� ���������� ������" ( �������� �� �������� �̳��� = 1, 
              ������ = 2, 
              ������� = 5, 
              ������� ������� ���� = 3,
              �������� ���� = 8,
              ����� = 4,
              �ѳ������ = 6
              ��� ������� = 0)
    CityDistrict - "����� ���������� ������"
    Street - "������"
    StreetTypeId - "��� ������" ( �������� �� �������� �������� = 3,
                                  �������� = 1,
                                  ������ = 6,
                                  ������ = 2,
                                  ��������� = 5,
                                  ��������� = 4,
                                  ��� ������� = 0)
    StreetTypeName - "��� ������" �������� ��������, ���� StreetTypeId ������ �� 0, �������� ����������
    ZipCode - "�������� ������"
    BuildNumb - "����� �������"
    BuildType - "��� �����" (������� = 1, �������� = 2, ��� ������� = 0)
    BuildExtNumb - "�����" (�������, ������)
    ApartNumb - "����� ��������"
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

    // RegionId    - "����� 1" (���������, ���� CountryType = 1, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1
    if ( '1'==cCountryType ) {
      stmp.Format(_T(" RegionId=\"%d\""), nRegionId);
      s += stmp;
    }
    // RegionName  - "����� 2" (���������, ���� CountryType = 2, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1
    if ( '2'==cCountryType ) {
      if ( g_bWriteEmptyTags || false==szRegion.IsEmpty() ) {
        stmp.Format(_T(" CountryName=\"%s\""), Win1251ToUTF8(szRegion));
        s += stmp;
      }
    }
    // RegionTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ��������� = 2, ��� ������� = 0)
    stmp.Format(_T(" RegionTypeId=\"%c\""), GetRegionTypeId(szRegion, szCity));
    s += stmp;
    // DistrictName - "�����"
    CString szDistrictName;
    CString szSettlementName;
    TCHAR  cDistrictTypeId = GetDistrictTypeId(szCountry, szRegion, szDistrict, szCity, szDistrictName, szSettlementName);
    if ( g_bWriteEmptyTags || false==szDistrictName.IsEmpty() ) {
      stmp.Format(_T(" DistrictName=\"%s\""), Win1251ToUTF8(szDistrictName));
      s += stmp;
    }
    // DistrictTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ������ = 2, ��� ������� = 0)
    stmp.Format(_T(" DistrictTypeId=\"%c\""), cDistrictTypeId);
    s += stmp;

    // SettlementName - "��������� �����"
    if ( g_bWriteEmptyTags || false==szSettlementName.IsEmpty() ) {
      stmp.Format(_T(" SettlementName=\"%s\""), Win1251ToUTF8(szSettlementName));
      s += stmp;
    }
    BOOL bDistrictInCity = IsDistrictInCity(szCountry, szRegion, szDistrict, szCity);
    TCHAR cSettlementTypeId = szSettlementName.IsEmpty() ? '0' : GetSettlementTypeId(szFullCity, bDistrictInCity);
    stmp.Format(_T(" SettlementTypeId=\"%c\""), cSettlementTypeId);
    s += stmp;
  
    // CityDistrict - "����� ���������� ������"
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
// ��� ����������
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

  // <!-- "�������" -->
  xml.WriteFormat( _T("%s<Surname>%s</Surname>\r\n"), spaces, Win1251ToUTF8(szSurname) );
  // <!-- "������ ���" -->
  xml.WriteFormat( _T("%s<Name>%s</Name>\r\n"), spaces, Win1251ToUTF8(szName) );
  // <!-- "�� �������" -->
  xml.WriteFormat( _T("%s<Patronymic>%s</Patronymic>\r\n"), spaces, Win1251ToUTF8(szPatronymic) );


  xml.WriteFormat(_T("%s<Addresses>\r\n"), spaces);
  // <!-- ³������ ��� ������ ������ -->
  {
   /*
    <!-- ���� ��� ��� �����
    AddressType - ��� ������ ( �������� �� �������� ����� ���������� ��� ���������� = 1, ����� ����������� = 2, ����� ����� = 3)
    CountryType - "��� ������ (�����)" ( �������� �� �������� ������� = 1, ����� ������� = 2, ��� ������� = 3, ���� CountryType = 3, ���� �������� ����� �� ���������, ���������, �� ������ �� �������)
    CountryName - "����� (����)" (���������, ���� CountryType = 2, ������ ��� ����� �� ���������)
    RegionId    - "����� 1" (���������, ���� CountryType = 1, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1            
    RegionName  - "����� 2" (���������, ���� CountryType = 2, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1
    RegionTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ��������� = 2, ��� ������� = 0)
    DistrictName - "�����"
    DistrictTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ������ = 2, ��� ������� = 0)
    SettlementName - "��������� �����"
    SettlementTypeId - "��� ���������� ������" ( �������� �� �������� �̳��� = 1, 
              ������ = 2, 
              ������� = 5, 
              ������� ������� ���� = 3,
              �������� ���� = 8,
              ����� = 4,
              �ѳ������ = 6
              ��� ������� = 0)
    CityDistrict - "����� ���������� ������"
    Street - "������"
    StreetTypeId - "��� ������" ( �������� �� �������� �������� = 3,
                                  �������� = 1,
                                  ������ = 6,
                                  ������ = 2,
                                  ��������� = 5,
                                  ��������� = 4,
                                  ��� ������� = 0)
    StreetTypeName - "��� ������" �������� ��������, ���� StreetTypeId ������ �� 0, �������� ����������
    ZipCode - "�������� ������"
    BuildNumb - "����� �������"
    BuildType - "��� �����" (������� = 1, �������� = 2, ��� ������� = 0)
    BuildExtNumb - "�����" (�������, ������)
    ApartNumb - "����� ��������"
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

    // RegionId    - "����� 1" (���������, ���� CountryType = 1, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1
    if ( '1'==cCountryType ) {
      stmp.Format(_T(" RegionId=\"%d\""), nRegionId);
      s += stmp;
    }
    // RegionName  - "����� 2" (���������, ���� CountryType = 2, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1
    if ( '2'==cCountryType ) {
      if ( g_bWriteEmptyTags || false==szRegion.IsEmpty() ) {
        stmp.Format(_T(" CountryName=\"%s\""), Win1251ToUTF8(szRegion));
        s += stmp;
      }
    }
    // RegionTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ��������� = 2, ��� ������� = 0)
    stmp.Format(_T(" RegionTypeId=\"%c\""), GetRegionTypeId(szRegion, szCity));
    s += stmp;
    // DistrictName - "�����"
    CString szDistrictName;
    CString szSettlementName;
    // DistrictTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ������ = 2, ��� ������� = 0)
    TCHAR  cDistrictTypeId = GetDistrictTypeId(szCountry, szRegion, szDistrict, szCity, szDistrictName, szSettlementName);


    // DistrictName - "�����"
    if ( g_bWriteEmptyTags || false==szDistrictName.IsEmpty() ) {
      stmp.Format(_T(" DistrictName=\"%s\""), Win1251ToUTF8(szDistrictName));
      s += stmp;
    }
    stmp.Format(_T(" DistrictTypeId=\"%c\""), cDistrictTypeId);
    s += stmp;

    // SettlementName - "��������� �����"
    if ( g_bWriteEmptyTags || false==szSettlementName.IsEmpty() ) {
      stmp.Format(_T(" SettlementName=\"%s\""), Win1251ToUTF8(szSettlementName));
      s += stmp;
    }
    BOOL bDistrictInCity = IsDistrictInCity(szCountry, szRegion, szDistrict, szCity);
    TCHAR cSettlementTypeId = szSettlementName.IsEmpty() ? '0' : GetSettlementTypeId(szCity, bDistrictInCity);
    stmp.Format(_T(" SettlementTypeId=\"%c\""), cSettlementTypeId);
    s += stmp;
  
    // CityDistrict - "����� ���������� ������"
    CString szCityDistrict = bDistrictInCity ? _T("") : szDistrict;
    if ( g_bWriteEmptyTags || false==szCityDistrict.IsEmpty() ) {
      stmp.Format(_T(" CityDistrict=\"%s\""), Win1251ToUTF8(szCityDistrict));
      s += stmp;
    }
    // Street - "������"
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
    // StreetTypeId - "��� ������" ( �������� �� �������� �������� = 3,
    //                               �������� = 1,
    //                               ������ = 6,
    //                               ������ = 2,
    //                               ��������� = 5,
    //                               ��������� = 4,
    //                               ��� ������� = 0)
    stmp.Format(_T(" StreetTypeId=\"%c\""), cStreetTypeId);
    s += stmp;
    // StreetTypeName - "��� ������" �������� ��������, ���� StreetTypeId ������ �� 0, �������� ����������
    /*
    if ( g_bWriteEmptyTags || false==szStreetTypeName.IsEmpty() ) {
      stmp.Format(_T(" StreetTypeName=\"%s\""), Win1251ToUTF8(szStreetTypeName));
      s += stmp;
    }
    */
    // BuildNumb - "����� �������"
    TCHAR BuildType;
    CString szBuildNumb, szBuildExtNumb;
    ParseBuildNumb(szBuild, szBuildNumb, szBuildExtNumb, BuildType);
    if ( g_bWriteEmptyTags || false==szBuildNumb.IsEmpty() ) {
      stmp.Format(_T(" BuildNumb=\"%s\""), Win1251ToUTF8(szBuildNumb));
      s += stmp;
    }
    // BuildType - "��� �����" (������� = 1, �������� = 2, ��� ������� = 0)
    stmp.Format(_T(" BuildType=\"%c\""), BuildType);
    s += stmp;
    // BuildExtNumb - "�����" (�������, ������)
    if ( g_bWriteEmptyTags || false==szBuildExtNumb.IsEmpty() ) {
      stmp.Format(_T(" BuildExtNumb=\"%s\""), Win1251ToUTF8(szBuildExtNumb));
      s += stmp;
    }
    // ApartNumb - "����� ��������"
    if ( g_bWriteEmptyTags || false==szApartNumb.IsEmpty() ) {
      stmp.Format(_T(" ApartNumb=\"%s\""), Win1251ToUTF8(szApartNumb));
      s += stmp;
    }

    s += _T(" />\r\n");
    xml.WriteString(s);
  }
  xml.WriteFormat(_T("%s</Addresses>\r\n"), spaces);

  // <!-- "����������" -->
  xml.WriteFormat(_T("%s<Organization></Organization>\r\n"), spaces);
  // <!-- ³������ ��� ��������, �� ������� ����� -->
  xml.WriteFormat(_T("%s<DocType>%d</DocType>\r\n"), spaces, nDocType);
  // <!-- "���� �� �����" -->
  xml.WriteFormat(_T("%s<DocSeriaNumber>%s %s</DocSeriaNumber>\r\n"),
                     spaces, Win1251ToUTF8(szDocSeria), Win1251ToUTF8(szDocNum));

  // <!-- "��� �������" -->
  xml.WriteFormat(_T("%s<DocOrgan>%s</DocOrgan>\r\n"), spaces, Win1251ToUTF8(szDocBy));
  // <!-- "���� ������" -->
  xml.WriteFormat(_T("%s<DocDate>%s</DocDate>\r\n"), spaces, szDocDate);


  xml.WriteString(_T("      </Person>\r\n"));
}

BOOL IsLegalEntity(const CString& sz) {
  CCyrString s(sz);
  s.MakeLower();
  if ( s.Find(_T("�����������"))  >= 0 ||
       s.Find(_T("����������")) >= 0 || 
       s.Find(_T("������"))       >= 0 || 
       s.Find(_T("���������"))    >= 0 || 
       s.Find(_T("����"))        >= 0 || 
       s.Find(_T("���������"))    >= 0 ) 
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
  szDeclRole = "3";  // ���� �����

  CString szDeclarant        = rs.m_DECLARANT_NAME;
  CString szDeclarantAddress = rs.m_DECLARANT_ADDRESS;

  if ( rs.IsFatherDeclarant() ) {
    szDeclRole = _T("1");    // ������
  }
  else if ( rs.IsMotherDeclarant() ) {
    szDeclRole = _T("2");  // ����
  }
  else if ( IsLegalEntity(szDeclarant) || IsLegalEntity(szDeclarantAddress) ) {
    szDeclRole = _T("10");  // �������� �����
  }

  if ( szDeclRole==_T("1") ) { // ������� - ������
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
  else if ( szDeclRole==_T("2") ) { // ������� - ����
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
  // <!-- "�������" -->
  xml.WriteFormat( _T("%s<Surname>%s</Surname>\r\n"), spaces, Win1251ToUTF8(szSurname));
  // <!-- "������ ���" -->
  xml.WriteFormat( _T("%s<Name>%s</Name>\r\n"), spaces, Win1251ToUTF8(szName) );
  // <!-- "�� �������" -->
  xml.WriteFormat( _T("%s<Patronymic>%s</Patronymic>\r\n"), spaces, Win1251ToUTF8(szPatronymic) );

  xml.WriteFormat(_T("%s<Addresses>\r\n"), spaces);
  {
    CString spaces(' ', 10);
    TCHAR cCountryType = GetCountryType(szCountry);
    s.Format( _T("%s<Address AddressType=\"1\" CountryType=\"%c\""), spaces, cCountryType);
    CString szCity     = GetCity(szFullCity);
    int nRegionId = GetRegionId(szRegion, szCity);
    // RegionId    - "����� 1" (���������, ���� CountryType = 1, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1
    if ( '1'==cCountryType ) {
      stmp.Format(_T(" RegionId=\"%d\""), nRegionId);
      s += stmp;
    }
    // RegionName  - "����� 2" (���������, ���� CountryType = 2, ������ ��� ����� �� ���������), ���� �������� �������� � ������� 1
    if ( '2'==cCountryType ) {
      if ( g_bWriteEmptyTags || false==szRegion.IsEmpty() ) {
        stmp.Format(_T(" CountryName=\"%s\""), Win1251ToUTF8(szRegion));
        s += stmp;
      }
    }
    // RegionTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ��������� = 2, ��� ������� = 0)
    stmp.Format(_T(" RegionTypeId=\"%c\""), GetRegionTypeId(szRegion, szCity));
    s += stmp;
    // DistrictName - "�����"
    CString szDistrictName;
    CString szSettlementName;
    // DistrictTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ������ = 2, ��� ������� = 0)
    TCHAR  cDistrictTypeId = GetDistrictTypeId(szCountry, szRegion, szDistrict, szCity, szDistrictName, szSettlementName);
    // DistrictName - "�����"
    if ( g_bWriteEmptyTags || false==szDistrictName.IsEmpty() ) {
      stmp.Format(_T(" DistrictName=\"%s\""), Win1251ToUTF8(szDistrictName));
      s += stmp;
    }
    stmp.Format(_T(" DistrictTypeId=\"%c\""), cDistrictTypeId);
    s += stmp;

    // SettlementName - "��������� �����"
    if ( g_bWriteEmptyTags || false==szSettlementName.IsEmpty() ) {
      stmp.Format(_T(" SettlementName=\"%s\""), Win1251ToUTF8(szSettlementName));
      s += stmp;
    }
    BOOL bDistrictInCity = IsDistrictInCity(szCountry, szRegion, szDistrict, szCity);
    TCHAR cSettlementTypeId = szSettlementName.IsEmpty() ? '0' : GetSettlementTypeId(szFullCity, bDistrictInCity);
    stmp.Format(_T(" SettlementTypeId=\"%c\""), cSettlementTypeId);
    s += stmp;
    // CityDistrict - "����� ���������� ������"
    CString szCityDistrict = bDistrictInCity ? _T("") : szDistrict;
    if ( g_bWriteEmptyTags || false==szCityDistrict.IsEmpty() ) {
      stmp.Format(_T(" CityDistrict=\"%s\""), Win1251ToUTF8(szCityDistrict));
      s += stmp;
    }
    // Street - "������"
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
    // StreetTypeId - "��� ������" ( �������� �� �������� �������� = 3,
    //                               �������� = 1,
    //                               ������ = 6,
    //                               ������ = 2,
    //                               ��������� = 5,
    //                               ��������� = 4,
    //                               ��� ������� = 0)
    stmp.Format(_T(" StreetTypeId=\"%c\""), cStreetTypeId);
    s += stmp;
    // StreetTypeName - "��� ������" �������� ��������, ���� StreetTypeId ������ �� 0, �������� ����������
    if ( g_bWriteEmptyTags || false==szStreetTypeName.IsEmpty() ) {
      stmp.Format(_T(" StreetTypeName=\"%s\""), Win1251ToUTF8(szStreetTypeName));
      s += stmp;
    }
    // ZipCode - "�������� ������"
    if ( g_bWriteEmptyTags ) {
      stmp = _T(" ZipCode=\"\"");
      s += stmp;
    }
    // BuildNumb - "����� �������"
    TCHAR BuildType;
    CString szBuild, szBuildNumb, szBuildExtNumb;
    szBuild = szHouse;
    ParseBuildNumb(szBuild, szBuildNumb, szBuildExtNumb, BuildType);
    if ( g_bWriteEmptyTags || false==szBuildNumb.IsEmpty() ) {
      stmp.Format(_T(" BuildNumb=\"%s\""), Win1251ToUTF8(szBuildNumb));
      s += stmp;
    }
    // BuildType - "��� �����" (������� = 1, �������� = 2, ��� ������� = 0)
    stmp.Format(_T(" BuildType=\"%c\""), BuildType);
    s += stmp;
    // BuildExtNumb - "�����" (�������, ������)
    if ( g_bWriteEmptyTags || false==szBuildExtNumb.IsEmpty() ) {
      stmp.Format(_T(" BuildExtNumb=\"%s\""), Win1251ToUTF8(szBuildExtNumb));
      s += stmp;
    }
    // ApartNumb - "����� ��������"
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
  if ( fBothInName || rs.AreParentsDeclarants() ) // ��������� ����� - ����, ��������� ������ - ����.
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

  LPCTSTR szArray[] = { _T("�������� �� ������."), _T("�������� �� ������."), NULL };

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

  if ( szMemo.Find(_T("�� � �������")) >= 0 ) {
    return 1; // �³������� �� ����� 126 ѳ������� ������� ������
  }

  switch(bType) {
    case BIRTH_TYPE_AFFILIATION1  :
    case BIRTH_TYPE_AFFILIATION2  :
      return 1;
    case BIRTH_TYPE_MOTHER        :
      return 3;
    case BIRTH_TYPE_APPL          :
    case BIRTH_TYPE_APPLNUM       :
      if ( szMemo.Find(_T(" �������")) > 0 || szMemo.Find(_T(" �������")) > 0 ) {
        return 5;
      }
      return 5;
  }

  return 2; // �³������� �� ����� 133 ѳ������� ������� ������ = 2
}
*/

LPCTSTR GetBirhDocName(BOOL fIsAlive) {
  if ( false==fIsAlive ) {
    return _T("�������� ��� ������������ ������");
  }
  return _T("������� �������� ��� ����������");
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
  if ( szNotice.Find(_T("³������ ��� ������")) >= 0 ) {
    if ( szNotice.Find(_T("��������"))>0 || szNotice.Find(_T("��������"))>0 ) {
      return 1; // ³������ ��� ���� ������ �� �������� ��������
    }
  }
  return 0; // ³������ ��� ������ ������ �� �� �������� ��������
}
int GetIsMotherFromDeclarant(const CString& szNotice) {
  if ( szNotice.Find(_T("³������ ��� ����")) >= 0  || szNotice.Find(_T("³������ ��� ����")) >= 0) {
    if ( szNotice.Find(_T("��������"))>0 || szNotice.Find(_T("��������"))>0 ) {
      return 1; // ³������ ��� ���� ������ �� �������� ��������
    }
  }
  return 0; // ³������ ��� ���� ������ �� �� �������� ��������
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

        // <!-- ������������� ��������� �������, ����������� �������������� �� ��ֻ ��� ����� ��������� ������� -->
        xml.WriteFormat(_T("%s<ExtSystemId>%s</ExtSystemId>\r\n"), spaces, Win1251ToUTF8(g_szExtSystemId));
        // <!-- ������������� �� � �������� ������ -->
        xml.WriteFormat(_T("%s<ExtActRecordId>1%04d%lu</ExtActRecordId>\r\n"), spaces, odtDateReg.GetYear(), rs.m_ID);
        // <!-- "������� ����� �������� ���������� �����" (�������� true ��� false) -->
        bIsUALang = IsUALang(rs);
        xml.WriteFormat(_T("%s<IsUALang>%s</IsUALang>\r\n"), spaces, bIsUALang ? _T("true") : _T("false"));
        // <!-- "����, ���� �������� ��" (���� IsUALang �� �������� true, ��� ����� �� ���������) -->
        if ( false==bIsUALang ) {
          // todo
        }
        // <!-- "��� �������� ������", ��� �� ��� ���������� ������ �� �������� ���� 3 -->
        xml.WriteFormat(_T("%s<Type>3</Type>\r\n"), spaces);
        // <!-- "����������" (�������� true ��� false) -->
        xml.WriteFormat(_T("%s<IsRestored>%s</IsRestored>\r\n"), spaces, (rs.m_RENEW & BIRTH_RENEW) ? _T("true") : _T("false"));
        // <!-- "��������� � ��������� ������" (�������� true ��� false) -->
        xml.WriteFormat(_T("%s<IsDelayedRegistration>%s</IsDelayedRegistration>\r\n"), spaces, (rs.m_RENEW & BIRTH_LONGTERM) ? _T("true") : _T("false"));
        // <!-- "�� � �������� �����" (�������� true ��� false) -->
        xml.WriteFormat(_T("%s<IsMetricBook>false</IsMetricBook>\r\n"), spaces);
        // <!-- "����� ��" -->
        xml.WriteFormat(_T("%s<Number>%lu</Number>\r\n"), spaces, GetFieldLong(rs, _T("NUMBER")));
        // <!-- "���� ��������� ��" -->
        xml.WriteFormat(_T("%s<CompositionDate>%s</CompositionDate>\r\n"), spaces, GetFieldDate(rs, _T("DATEREG")));
        // <!-- ���� ���������� ��� ����� � �� -->
        xml.WriteFormat(_T("%s<Persons>\r\n"), spaces);
        {

          CString szDeclName    = GetFieldString(rs, _T("DECLARANT_NAME"));

          // <!-- ³������ ��� ������ -->
          MakePersonTag(rs, xml, PERSON_ROLE_FATHER, NULL,
                        rs.m_FATHER_SURNAME, rs.m_FATHER_NAME, rs.m_FATHER_PATRONYMIC,
                        rs.m_FATHER_CITIZENSHIP, rs.m_FATHER_BIRTH_DATE,
                        rs.m_FATHER_COUNTRY, rs.m_FATHER_REGION, rs.m_FATHER_CITY, rs.m_FATHER_DISTRICT,
                        rs.m_FATHER_STREET, 0, rs.m_FATHER_HOUSE, rs.m_FATHER_FLAT);

          // <!-- ³������ ��� ����, �� Role - ���� ������ � �� (��� �� ��� ����������, ���� ����� = 3) -->
          MakePersonTag(rs, xml, PERSON_ROLE_MOTHER, NULL,
                        rs.m_MOTHER_SURNAME, rs.m_MOTHER_NAME, rs.m_MOTHER_PATRONYMIC,
                        rs.m_MOTHER_CITIZENSHIP, rs.m_MOTHER_BIRTH_DATE,
                        rs.m_MOTHER_COUNTRY, rs.m_MOTHER_REGION, rs.m_MOTHER_CITY, rs.m_MOTHER_DISTRICT,
                        rs.m_MOTHER_STREET, 0, rs.m_MOTHER_HOUSE, rs.m_MOTHER_FLAT);

          // <!-- ³������ ��� ������, �� Role - ���� ������ � �� (��� �� ��� ����������, ���� ������ = 1) -->
          MakePersonTag(rs, xml,
                        rs.m_SURNAME, rs.m_NAME, rs.m_PATRONYMIC, rs.m_SEX,
                        rs.m_BIRTH_DATE,
                        rs.m_BP_COUNTRY, rs.m_BP_REGION, rs.m_BP_CITY, rs.m_BP_DISTRICT
                       );

          CString szDeclarantRole = _T("3");
          BOOL fTwoDeclarants = rs.AreParentsDeclarants();

          if ( fTwoDeclarants || (rs.m_DECLARANT_TYPE==2 && rs.m_EXTNOTES.Find(_T("{�2:")) >= 0) ) {
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

        // RacsType - "��� ������ ����" ( (�������� �� �������� ����������/���� ���ѻ = 97, ����������� ����� �./��./����.��� = 98)
        s.Format(_T("%s<RacsType>%s</RacsType>\r\n"), spaces, GetRagsType());
        xml.WriteString(s);

        // <!--"����� ������ ����" (���� �������� �������� � ������� 1 -->
        s.Format(_T("%s<RacsRegion>%d</RacsRegion>\r\n"), spaces, GetRagsRegionId());
        xml.WriteString(s);

        // <!-- "����� ����" (�����)-->
        s.Format(_T("%s<RacsName>%s</RacsName>\r\n"), spaces, Win1251ToUTF8(g_szRacsName));
        xml.WriteString(s);
        // <!-- "�������" -->
        if ( g_fWriteRacsDirectorName ) {
          s.Format(_T("%s<RacsDirectorName>%s</RacsDirectorName>\r\n"), spaces, Win1251ToUTF8(g_szRacsDirectorName));
          xml.WriteString(s);
        }
        // <!-- "���������" -->
        if ( g_fWriteBirthSpecialistName ) {
          s.Format(_T("%s<RacsSpecialistName>%s</RacsSpecialistName>\r\n"), spaces, Win1251ToUTF8(g_szSpecialistNameForBirth));
          xml.WriteString(s);
        }
        // <!-- ������ (��������)-->
        if ( g_fWriteRacsDirectorPosition ) {
          s.Format(_T("%s<RacsDirectorPosition>%s</RacsDirectorPosition>\r\n"), spaces, Win1251ToUTF8(g_szRacsDirectorPos));
          xml.WriteString(s);
        }

        // <!-- ������ (����������)-->
        if ( g_fWriteBirthSpecialistPosition ) {
          s.Format(_T("%s<RacsSpecialistPosition>%s</RacsSpecialistPosition>\r\n"), spaces, Win1251ToUTF8(g_szSpecialistPosForBirth));
          xml.WriteString(s);
        }

        // <!-- ʳ���� ��������� ��� ����� ����, ���� ����� �� -->

        s.Format(_T("%s<Notes>\r\n"), spaces);
        xml.WriteString(s);
        {
          CString spaces = CString(' ', 6);
          s.Format(_T("%s<Note Text=\"%s\" Date=\"%s\"/>\r\n"), spaces, Win1251ToUTF8(GetBirhNotice(rs.m_NOTICE)), rs.m_DATEREG);
          xml.WriteString(s);
        }
        s.Format(_T("%s</Notes>\r\n"), spaces);
        xml.WriteString(s);
        // <!-- ʳ���� ��������� ��� ������ -->

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
        
          //��� ����� �������� ������� �� ���� ����������� ��������� ����������
          /*
          s.Format(_T("%s<ClauseReasonType>%d</ClauseReasonType>\r\n"), spaces, GetClauseReasonType(rs));
          xml.WriteString(s);
          */
          // <!-- "ʳ������ ���������� ���� (����� �� 0 �� 10)" -->
          xml.WriteFormat(_T("%s<NewbornCount>%d</NewbornCount>\r\n"), spaces, GetFieldByte(rs, _T("NKIDS")));
          // <!-- ������������� (IsDeadBorn = 0) �� ���������������� (IsDeadBorn = 1) -->
          xml.WriteFormat(_T("%s<IsDeadBorn>%d</IsDeadBorn>\r\n"), spaces, GetFieldByte(rs, _T("ALIVE_FLAG")) ? 0 : 1);
          // <!-- ��� �� �������� ������ ���������� � ����� (����� �� 0 �� 20) -->
          xml.WriteFormat(_T("%s<NewbornNumber>%d</NewbornNumber>\r\n"), spaces, GetFieldByte(rs, _T("BYCOUNT")));
          // <!-- ³������ ��� ����� ����� -->
          xml.WriteFormat(_T("%s<WitnessPetitionInfo>%s</WitnessPetitionInfo>\r\n"), spaces, GetWitnessPetitionInfo(rs));
          // <!-- ϳ������ ������ ��������� ��� ������ -->
          xml.WriteFormat(_T("%s<FatherReason></FatherReason>\r\n"), spaces);
          // <!-- ������ ��� ������ "³������ ������ �� �������� ��������" 
          //    0 - �� �� �������� ��������
          //    1 - �� �������� ��������-->
          xml.WriteFormat(_T("%s<IsFatherFromDeclarant>%d</IsFatherFromDeclarant>\r\n"), spaces, GetIsFatherFromDeclarant(rs.m_NOTICE));
          //  <!-- ������ ��� ����� "³������ ������ �� �������� ��������" 
          //    0 - �� �� �������� ��������
          //    1 - �� �������� ��������-->
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