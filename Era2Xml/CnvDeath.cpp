//
// CnvDeath.cpp
//
#include "stdafx.h"
#include "CnvDeath.h"
#include "db.h"
#include "Helpers.h"

#include "Dictionaries.h"
#include "Geography.h"
#include "Globals.h"
#include "Helpers.h"
#include "RSDeathes.h"
#include "XmlFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL PeekAndPump();


void MakeAddressTag(CXmlFile& xml,
                    BYTE bAddressType,
                    CString& szCountry,
                    CString& szRegion,
                    CString& szDistrict,
                    LPCTSTR  szFullCity,
                    LPCTSTR  szStreet,
                    TCHAR    cStreetTypeId,
                    LPCTSTR  szHouse,
                    LPCTSTR  szFlat
                    )
{
  CString s, stmp, spaces(' ', 8);

  // AddressType - ��� ������ ( �������� �� �������� ����� ���������� ��� ���������� = 1, ����� ����������� = 2, ����� ����� = 3)
  s.Format( _T("%s<Address AddressType=\"%c\""), spaces, bAddressType);

  TCHAR cCountryType = GetCountryType(szCountry);

  // CountryType - "��� ������ (�����)" ( �������� �� �������� ������� = 1, ����� ������� = 2, ��� ������� = 3, ���� CountryType = 3, ���� �������� ����� �� ���������, ���������, �� ������ �� �������)
  stmp.Format( _T(" CountryType=\"%c\""), cCountryType);
  s += stmp;

  CString szCity = GetCity(szFullCity);
  int nRegionId  = GetRegionId(szRegion, szCity);

  // CountryName - "����� (����)" (���������, ���� CountryType = 2, ������ ��� ����� �� ���������)
  if ( '2'==cCountryType ) {
    if ( g_bWriteEmptyTags || false==szRegion.IsEmpty() ) {
      stmp.Format(_T(" CountryName=\"%s\""), Win1251ToUTF8(szRegion));
      s += stmp;
    }
  }
  // RegionId    - "����� 1" (���������, ���� CountryType = 1, ������ ��� ����� �� ���������), ���� �������� ������� �������� ������� � ������� 1 ������� ������
  if ( '1'==cCountryType ) {
    stmp.Format(_T(" RegionId=\"%d\""), nRegionId);
    s += stmp;
  }
  // RegionName  - "����� 2" (���������, ���� CountryType = 2, ������ ��� ����� �� ���������)
  if ( '2'==cCountryType ) {
    if ( g_bWriteEmptyTags || false==szRegion.IsEmpty() ) {
      stmp.Format(_T(" RegionName=\"%s\""), Win1251ToUTF8(szRegion));
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

  // SettlementName - "����������� �����"
  if ( g_bWriteEmptyTags || false==szSettlementName.IsEmpty() ) {
    stmp.Format(_T(" SettlementName=\"%s\""), Win1251ToUTF8(szSettlementName));
    s += stmp;
  }
  // SettlementTypeId - "��� ���������� ������"
  BOOL bDistrictInCity = IsDistrictInCity(szCountry, szRegion, szDistrict, szCity);
  TCHAR cSettlementTypeId = szSettlementName.IsEmpty() ? '0' : GetSettlementTypeId(szFullCity, bDistrictInCity);
  stmp.Format(_T(" SettlementTypeId=\"%c\""), cSettlementTypeId, bDistrictInCity);
  s += stmp;
  // CityDistrict - "����� ���������� ������"
  CString szCityDistrict = bDistrictInCity ? _T("") : szDistrict;
  if ( g_bWriteEmptyTags || false==szCityDistrict.IsEmpty() ) {
    stmp.Format(_T(" CityDistrict=\"%s\""), Win1251ToUTF8(szCityDistrict));
    s += stmp;
  }
  if ( szStreet && szHouse && szFlat ) {
    CString sStreet(szStreet), sHouse(szHouse), sFlat(szFlat);

    // Street - "������"
    CString szStreetTypeName, szStreetTypeToken;
    if ( 0==cStreetTypeId ) {
      ParseStreet(sStreet, szStreetTypeToken, cStreetTypeId, szStreetTypeName);
    }
    if ( sStreet.IsEmpty() ) {
      cStreetTypeId = '0';
    }
    if ( false==szStreetTypeName.IsEmpty() ) {
      sStreet.Replace(szStreetTypeName, _T(""));
    }
    if ( g_bWriteEmptyTags || false==sStreet.IsEmpty() ) {
      stmp.Format(_T(" Street=\"%s\""), Win1251ToUTF8(sStreet));
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

  } // if ( szFldStreet && szFldHouse && szFldFlat )

  s += _T(" />\r\n");
  xml.WriteString(s);

}

//
// ��� ���������
// 
void MakePersonTag(CXmlFile& xml,
                   const CString& szSurname,
                   const CString& szName,
                   const CString& szPatronymic,
                   BOOL fGender,
                   const CString& szCitizenship,
                   const CString& szBirthDate,
                   CString& szBirthCountry,
                   CString& szBirthRegion,
                   CString& szBirthDistrict,
                   CString& szFullBirthCity,
                   CString& szDeathCountry,
                   CString& szDeathRegion,
                   CString& szDeathDistrict,
                   CString& szFullDeathCity,
                   CString& szResidenceCountry,
                   CString& szResidenceRegion,
                   CString& szResidenceDistrict,
                   CString& szResidenceCity,
                   CString& szResidenceStreet,
                   CString& szResidenceHouse,
                   CString& szResidenceFlat,
                   CString& szIdNum
                   )

{
  CString s, stmp, spaces(' ', 8);
  // <Person Role="5"> <!-- �� Role - ���� ������ � �� (��� �� ��� ������, ���� ��������� = 5) -->
  s.Format(_T("      <Person Role=\"5\">\r\n"));
  xml.WriteString(s);
  // <!-- "�������" -->
  s.Format( _T("%s<Surname>%s</Surname>\r\n"), spaces, Win1251ToUTF8(szSurname) );
  xml.WriteString(s);
  // <!-- "������ ���" -->
  s.Format( _T("%s<Name>%s</Name>\r\n"), spaces, Win1251ToUTF8(szName) );
  xml.WriteString(s);
  // <!-- "�� �������" -->
  s.Format( _T("%s<Patronymic>%s</Patronymic>\r\n"), spaces, Win1251ToUTF8(szPatronymic) );
  xml.WriteString(s);
  // <!-- "����� 1" ( �������� �� �������� �׻ = 1, �ƻ = 2, ����� = 3) -->
  s.Format( _T("%s<Gender>%c</Gender>\r\n"), spaces, fGender ? '1' : '2');
  xml.WriteString(s);
  // <!-- "������������ 1" ( �������� �� �������� �����������(��) ������ = 1, ����� = 2) -->
  TCHAR cCitizenship = GetCitizenship( szCitizenship );
  s.Format( _T("%s<Citizenship>%c</Citizenship>\r\n"), spaces, cCitizenship );
  xml.WriteString(s);
  if ( cCitizenship != '1' ) { // ���� ������������ != '1' (������)
    s.Format( _T("%s<CitizenshipDescription>%s</CitizenshipDescription>\r\n"), spaces, Win1251ToUTF8(szCitizenship) );
    xml.WriteString(s);
  }
  // <!-- "�������������" -->
  if ( g_bWriteEmptyTags ) {
    s.Format( _T("%s<Nationality></Nationality>\r\n"), spaces);
    xml.WriteString(s);
  }
  // <!-- "���������������� �����" -->
  if ( g_bWriteEmptyTags ) {
    s.Format( _T("%s<Idn></Idn>\r\n"), spaces, Win1251ToUTF8(szIdNum));
    xml.WriteString(s);
  }
  // <!-- ���� ���������� -->
  if ( g_bWriteEmptyTags || false==szBirthDate.IsEmpty() ) {
    s.Format( _T("%s<BirthDate>%s</BirthDate>\r\n"), spaces, szBirthDate);
    xml.WriteString(s);
  }
  s.Format(_T("%s<Addresses>\r\n"), spaces);
  xml.WriteString(s);
  // <!-- ³������ ��� ������ ��������� -->
  {
    // AddressType - ��� ������ ( �������� �� �������� ����� ���������� ��� ���������� = 1,
    //                                                 ����� ����������� = 2,
    //                                                 ����� ����� = 3)

    MakeAddressTag(xml, '1',
                   szResidenceCountry, szResidenceRegion, szResidenceDistrict, szResidenceCity,
                   szResidenceStreet, 0, szResidenceHouse, szResidenceFlat
                  );
    MakeAddressTag(xml, '2',
                   szBirthCountry, szBirthRegion, szBirthDistrict, szFullBirthCity,
                   NULL, 0, NULL,NULL
                  );
    MakeAddressTag(xml, '3',
                   szDeathCountry, szDeathRegion, szDeathDistrict, szFullDeathCity,
                   NULL, 0, NULL,NULL
                  );
  }
  s.Format(_T("%s</Addresses>\r\n"), spaces);
  xml.WriteString(s);

  xml.WriteString(_T("      </Person>\r\n"));

}

void ConvertDeath(CDaoDatabase& db, LPCTSTR szOutFolder, LPCTSTR szFileMask, long nMaxOutRecords,
                  BOOL fPeriod, COleDateTime& odtFrom, COleDateTime& odtTill,
                  CProgressCtrl& ProgressBar, int& nCurProgressPos) {
  CRSDeathes rs(&db);

  long lRecords = 0, lRecNum = 1;

  CString s, spaces;
  CXmlFile xml;

  CMap<CString, LPCSTR, long, long> map;


  try {
    rs.Open(dbOpenTable, _T("[DEATHES]"), dbReadOnly);
    rs.SetCurrentIndex(_T("NUMBER"));
    lRecords = rs.GetRecordCount();

    if ( lRecords > 0 ) {

      if ( false==CreateXMLFile(xml, szOutFolder, szFileMask, _T("Death"), fPeriod, odtFrom, odtTill, lRecords, lRecNum, nMaxOutRecords) ) {
        // Error message here
        rs.Close();
        return;
      }
      xml.WriteString(g_szXMLHeader);
      xml.WriteString(_T("<ActRecords>\r\n"));

      BOOL bIsUALang;

      while( !rs.IsEOF() ) {
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


        xml.WriteString(_T("  <ActRecord>\r\n"));
        // Parsing DEATH record and writing to XML here

        spaces = CString(' ', 4);
        
		    COleDateTime odtDateReg;
		    GetFieldDate(rs, _T("DATEREG"), &odtDateReg);

        // <!-- ������������� ��������� �������, ����������� �������������� �� ��ֻ ��� ����� ��������� ������� -->
        xml.WriteFormat(_T("%s<ExtSystemId>%s</ExtSystemId>\r\n"), spaces, Win1251ToUTF8(g_szExtSystemId));
        // <!-- ������������� �� � �������� ������ -->
        xml.WriteFormat(_T("%s<ExtActRecordId>4%04d%lu</ExtActRecordId>\r\n"), spaces, odtDateReg.GetYear(), rs.m_ID);
        // <!-- "������� ����� �������� ���������� �����" (�������� true ��� false) -->
        bIsUALang = IsUALang(rs);
        xml.WriteFormat(_T("%s<IsUALang>%s</IsUALang>\r\n"), spaces, bIsUALang ? _T("true") : _T("false"));
        // <!-- "����, ���� �������� ��" (���� IsUALang �� �������� true, ��� ����� �� ���������) -->
        if ( false==bIsUALang ) {
          // todo
        }
        // <!-- "��� �������� ������", ��� �� ��� ������ ������ �� �������� ���� 5 -->
        xml.WriteFormat(_T("%s<Type>5</Type>\r\n"), spaces);
        // <!-- "����������" (�������� true ��� false) -->
        xml.WriteFormat(_T("%s<IsRestored>%s</IsRestored>\r\n"), spaces, rs.m_RENEW ? _T("true") : _T("false"));
        // <!-- "��������� � ��������� ������" (�������� true ��� false) -->
        BOOL bIsDelayedRegistration = false; // TODO!!!
        xml.WriteFormat(_T("%s<IsDelayedRegistration>%s</IsDelayedRegistration>\r\n"), spaces, bIsDelayedRegistration ? _T("true") : _T("false"));
        // <!-- "�� � �������� �����" (�������� true ��� false) -->
        xml.WriteFormat(_T("%s<IsMetricBook>false</IsMetricBook>\r\n"), spaces);
        // <!-- "����� ��" -->
        xml.WriteFormat(_T("%s<Number>%lu</Number>\r\n"), spaces, rs.m_NUMBER);
        // <!-- "���� ��������� ��" -->
        xml.WriteFormat(_T("%s<CompositionDate>%s</CompositionDate>\r\n"), spaces, rs.m_DATEREG);
        // <!-- ���� ���������� ��� ����� � �� -->
        xml.WriteFormat(_T("%s<Persons>\r\n"), spaces);
        {
          // <!-- ³������ ��� ��������� -->
          MakePersonTag(xml, rs.m_SURNAME, rs.m_NAME, rs.m_PATRONYMIC, rs.m_SEX,
                        rs.m_CITIZENSHIP, rs.m_BIRTH_DATE,
                        rs.m_BP_COUNTRY, rs.m_BP_REGION, rs.m_BP_DISTRICT, rs.m_BP_CITY,
                        rs.m_DP_COUNTRY, rs.m_DP_REGION, rs.m_DP_DISTRICT, rs.m_DP_CITY,
                        rs.m_RP_COUNTRY, rs.m_RP_REGION, rs.m_RP_DISTRICT, rs.m_RP_CITY,
                        rs.m_RP_STREET, rs.m_RP_HOUSE, rs.m_RP_FLAT,
                        rs.m_TAX_CODE
                       );

        }
        // <!-- ʳ���� ��������� ��� ������ ��������� -->
        // <!-- ³������ ��� �������� (���� ���� ������� �� 0 �� 9 ���) -->
        {
          CString s, stmp, spaces(' ', 8);
          CString szSurname, szName, szPatronymic, szOrganization;
          xml.WriteFormat(_T("      <Person Role=\"4\" DeclarantRole=\"\">\r\n"));

          rs.ParseDeclarantFIO(szSurname, szName, szPatronymic, szOrganization);
          // <!-- "�������" -->
          xml.WriteFormat(_T("%s<Surname>%s</Surname>\r\n"), spaces, Win1251ToUTF8(szSurname));
          // <!-- "������ ���" -->
          xml.WriteFormat(_T("%s<Name>%s</Name>\r\n"), spaces, Win1251ToUTF8(szName));
          // <!-- "�� �������" -->
          xml.WriteFormat(_T("%s<Patronymic>%s</Patronymic>\r\n"), spaces, Win1251ToUTF8(szPatronymic));

          CString szCountry, szRegion, szDistrict, szCity, szStreet, szBuild, szFlat;
          TCHAR cStreetType = '0';

          rs.ParseDeclarantAddress(szCountry, szRegion, szDistrict, szCity, cStreetType, szStreet, szBuild, szFlat);

          MakeAddressTag(xml, '1', szCountry, szRegion, szDistrict, szCity, szStreet, cStreetType, szBuild, szFlat);


          // <!-- "����������", ���� ������� �������� ����� -->
          if ( g_bWriteEmptyTags || false==szOrganization.IsEmpty() ) {
            xml.WriteFormat(_T("%s<Organization>%s</Organization>\r\n"), spaces, Win1251ToUTF8(szOrganization));
          }

          s = GetDocType(rs.m_DECLARANT_PASSPORT_TYPE);
          xml.WriteFormat(_T("%s<DocType>%s</DocType>\r\n"), spaces, s);
          
          // <!-- "���� �� �����" -->
          xml.WriteFormat(_T("%s<DocSeriaNumber>%s %s</DocSeriaNumber>\r\n"),
                          spaces, Win1251ToUTF8(rs.m_DECLARANT_PASSPORT_SERIA), Win1251ToUTF8(rs.m_DECLARANT_PASSPORT_NUMBER));

          // <!-- "��� �������" -->
          xml.WriteFormat(_T("%s<DocOrgan>%s</DocOrgan>\r\n"), spaces, Win1251ToUTF8(rs.m_DECLARANT_PASSPORT_BY));
          // <!-- "���� ������" -->
          xml.WriteFormat(_T("%s<DocDate>%s</DocDate>\r\n"), spaces, rs.m_DECLARANT_PASSPORT_DATE);
          // <!-- ʳ���� ��������� ��� ��������, �� ������� ����� -->
          xml.WriteFormat(_T("      </Person>\r\n"));

        }

        xml.WriteFormat(_T("%s</Persons>\r\n"), spaces);

        xml.WriteFormat(_T("%s<Certificates>\r\n"), spaces);
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
        xml.WriteFormat(_T("%s</Certificates>\r\n"), spaces);

        // RacsType - "��� ������ ����" ( (�������� �� �������� ����������/���� ���ѻ = 97, ����������� ����� �./��./����.��� = 98)
        xml.WriteFormat(_T("%s<RacsType>%s</RacsType>\r\n"), spaces, GetRagsType());

        // <!-- "����� ����" (�����)-->
        xml.WriteFormat(_T("%s<RacsName>%s</RacsName>\r\n"), spaces, Win1251ToUTF8(g_szRacsName));
        // <!-- "�������" -->
        if ( g_fWriteRacsDirectorName ) {
          xml.WriteFormat(_T("%s<RacsDirectorName>%s</RacsDirectorName>\r\n"), spaces, Win1251ToUTF8(g_szRacsDirectorName));
        }
        // <!-- "���������" -->
        if ( g_fWriteDeathSpecialistName ) {
          xml.WriteFormat(_T("%s<RacsSpecialistName>%s</RacsSpecialistName>\r\n"), spaces, Win1251ToUTF8(g_szSpecialistNameForDeath));
        }
        // <!-- ������ (��������)-->
        if ( g_fWriteRacsDirectorPosition ) {
          xml.WriteFormat(_T("%s<RacsDirectorPosition>%s</RacsDirectorPosition>\r\n"), spaces, Win1251ToUTF8(g_szRacsDirectorPos));
        }

        // <!-- ������ (����������)-->
        if ( g_fWriteDeathSpecialistPosition ) {
          xml.WriteFormat(_T("%s<RacsSpecialistPosition>%s</RacsSpecialistPosition>\r\n"), spaces, Win1251ToUTF8(g_szSpecialistPosForDeath));
        }

        // <!-- ʳ���� ��������� ��� ����� ����, ���� ����� �� -->

        xml.WriteFormat(_T("%s<Notes>\r\n"), spaces);
        {
          CString spaces = CString(' ', 6);
          xml.WriteFormat(_T("%s<Note Text=\"%s\" Date=\"%s\"/>\r\n"), spaces, Win1251ToUTF8(rs.GetNotices()), rs.m_DATEREG);
        }
        s.Format(_T("%s</Notes>\r\n"), spaces);
        xml.WriteString(s);
        // <!-- ʳ���� ��������� ��� ������ -->

        xml.WriteFormat(_T("%s<DeathInfo>\r\n"), spaces);
        {
          CString spaces = CString(' ', 6);

          xml.WriteFormat(_T("%s<DeathDocs>\r\n"), spaces);
          xml.WriteFormat(_T("%s<Document Name=\"%s\" Number=\"%s\" DeliveryDate=\"%s\" DeliveryOrgan=\"%s\" />\r\n"),
                          CString(' ', 6), 
                          Win1251ToUTF8(rs.m_MEDICAL_CERT_TYPE),
                          Win1251ToUTF8(rs.m_MEDICAL_CERT_NUMBER),
                          rs.m_MEDICAL_CERT_DATE,
                          Win1251ToUTF8(rs.m_MEDICAL_CERT_BY)
                         );

          xml.WriteFormat(_T("%s</DeathDocs>\r\n"), spaces);
        
          // <!-- "��������� �����" (�������� true ��� false)-->
          xml.WriteFormat(_T("%s<IsNotRecognized>%s</IsNotRecognized>\r\n"), spaces, rs.GetIsNotRecognized() );
          // <!-- "���� �����" -->
          xml.WriteFormat(_T("%s<DeathDate>%s</DeathDate>\r\n"), spaces, rs.m_DEATH_DATE);
          // <!-- ³� 1 ��� ³� 2 -->
          Duration age = rs.GetAge();
          xml.WriteFormat(_T("%s<Age>%d</Age>\r\n"), spaces, age.years);
          if ( age.years == 0 ) {
            xml.WriteFormat(_T("%s<MonthCount>%d</MonthCount>\r\n"), spaces, age.months);
            xml.WriteFormat(_T("%s<DaysCount>%d</DaysCount>\r\n"), spaces, age.days);
          }

        }
        xml.WriteFormat(_T("%s</DeathInfo>\r\n"), spaces);


        xml.WriteString(_T("  </ActRecord>\r\n"));

        {
          CString s, stmp, spaces(' ', 8);
          // <Person Role="4" DeclarantRole="">
          // DeclarantRole - "��������� �" (��� �� ��� ������: ����� ����� = 3, ��������� ����� = 10)-->
          s.Format(_T("      <Person Role=\"4\"  >\r\n"));
        }


        if ( lRecNum % nMaxOutRecords == 0) {
          xml.WriteString(_T("</ActRecords>\r\n"));
          xml.Close();
          if ( false==CreateXMLFile(xml, szOutFolder, szFileMask, _T("Death"), fPeriod, odtFrom, odtTill, lRecords, lRecNum+1, nMaxOutRecords) ) {
            // Error message here
            break;
          }
          xml.WriteString(g_szXMLHeader);
          xml.WriteString(_T("<ActRecords>\r\n"));
        }
        lRecNum++;
        rs.MoveNext();
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