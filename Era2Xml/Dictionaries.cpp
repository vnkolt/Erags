//
// Dictionaries.cpp
//
#include "stdafx.h"
#include "Dictionaries.h"
#include "Geography.h"

#include "..\Common\CyrString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


TCHAR GetCitizenship(LPCTSTR szCitizenship) {
  CString sz = UpperString(szCitizenship);
  sz.TrimLeft();
  sz.TrimRight();

  if ( sz==_T("�������") || sz==_T("�������") || sz==_T("����������") ||
       sz==_T("�������") || sz==_T("�������") || sz==_T("�����������")) {
    return '1';
  }
  return '2';
}

TCHAR GetCountryType(LPCTSTR szCountry) {
  CString sz = UpperString(szCountry);
  sz.TrimLeft();
  sz.TrimRight();

  if ( sz==_T("�������") || sz==_T("�������") ) {
    return '1';
  }
  return '2';
}

int GetRegionId(LPCTSTR szRegion, LPCTSTR szCity) { // call it only if CountryType = '1' (������)
  CString sReg = UpperString(szRegion);
  sReg.TrimLeft();
  sReg.TrimRight();

  CString sCit = UpperString(szCity);
  sCit.TrimLeft();
  sCit.TrimRight();

  if ( sReg.Find(_T("����"))>=0 || sReg.Find(_T("����"))>=0 ) return 1; // ��������� ��������� ����
  if ( sReg.Find(_T("²�"))==0  || sReg.Find(_T("���"))==0  ) return 2; // ³������� ���.
  if ( sReg.Find(_T("���"))==0 )                              return 3; // ��������� ���.
  if ( sReg.Find(_T("�Ͳ�"))==0 || sReg.Find(_T("����"))==0 ) return 4; // ��������������� ���.
  if ( sReg.Find(_T("���"))==0 )                              return 5; // �������� ���.
  if ( sReg.Find(_T("���"))==0 )                              return 6; // ����������� ���.
  if ( sReg.Find(_T("���"))==0 )                              return 7; // ������������ ���.
  if ( sReg.Find(_T("���"))==0 )                              return 8; // ��������� ���.
  if ( sReg.Find(_T("���"))==0 || sReg.Find(_T("���"))==0 )   return 9; // �����-���������� ���.
  if ( sReg.Find(_T("�ȯ"))==0 || sReg.Find(_T("�Ȫ"))==0 || sReg.Find(_T("���"))==0 ) return 10; // ������� ���.
  if ( sReg.Find(_T("ʲ�"))==0 || sReg.Find(_T("���"))==0 )   return 11;// ʳ������������ ���.
  if ( sReg.Find(_T("���"))==0 )                              return 12;// ��������� ���.
  if ( sReg.Find(_T("���"))==0 )                              return 13;// �������� ���.
  if ( sReg.Find(_T("���"))==0 || sReg.Find(_T("���"))==0 )   return 14;// ����������� ���.
  if ( sReg.Find(_T("���"))==0 )                              return 15;// ������� ���.
  if ( sReg.Find(_T("���"))==0 )                              return 16;// ���������� ���.
  if ( sReg.Find(_T("в�"))==0 || sReg.Find(_T("���"))==0 )   return 17;// г�������� ���.
  if ( sReg.Find(_T("���"))==0 )                              return 18;// ������� ���.
  if ( sReg.Find(_T("���"))==0 )                              return 19;// ������������ ���.
  if ( sReg.Find(_T("���"))==0 )                              return 20;// ��������� ���.
  if ( sReg.Find(_T("���"))==0 )                              return 21;// ���������� ���.
  if ( sReg.Find(_T("���"))==0 )                              return 22;// ����������� ���.
  if ( sReg.Find(_T("����"))==0 )                             return 23;// ��������� ���.
  if ( sReg.Find(_T("���Ͳ�"))==0 || sReg.Find(_T("������"))==0) return 24;// ���������� ���.
  if ( sReg.Find(_T("���Ͳ�"))==0 || sReg.Find(_T("������"))==0) return 25;// ���������� ���.

  if ( sReg.IsEmpty() ) {
    if ( sCit.Find(_T("�ȯ�"))==0 || sCit.Find(_T("�ȯ�"))==0 || sCit.Find(_T("�ȯ�"))==0 ) { // 26 - �. ���
      return 26;
    }
    if ( sCit.Find(_T("�����"))==0 ) { // 27 - �. �����������
      return 27;
    }
  }

  return 0;
}

// RegionTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ��������� = 2, ��� ������� = 0)
TCHAR GetRegionTypeId(LPCTSTR szRegion, LPCTSTR szCity) {
  CString sReg = UpperString(szRegion);
  sReg.TrimLeft();
  sReg.TrimRight();

  CString sCit = UpperString(szCity);
  sCit.TrimLeft();
  sCit.TrimRight();
  if ( sReg.IsEmpty() && sCit.IsEmpty() ) {
    return '0'; // �� �������
  }

  switch( GetRegionId(szRegion, szCity) ) {
    case 26:  // �. ���
    case 27:  // �. �����������
      return '1';
  }
  return '2';
}

CString MakeCountryName(LPCTSTR szCountry) {
  CString s;
  s.Format(_T(" CountryName=\"%s\""), szCountry);
  return s;
}


// DistrictTypeId - "��� ������" ( �������� �� �������� �̳��� = 1, ������ = 2, ��� ������� = 0)
TCHAR GetDistrictTypeId(const CString& szCountry,
                        const CString& szRegion,
                        const CString& szDistrict,
                        const CString& szCity,
                        CString& szDistrictName,
                        CString& szSettlementName)
{
  CCyrString sCountry(szCountry), sRegion(szRegion), sDistrict(szDistrict), sCity(szCity);

  CGeoRecord* pCountry = theGeoCache.GetCountry(sCountry);
  if ( NULL==pCountry ) {
    return '0';
  }
  CGeoRecord* pMainCity = theGeoCache.GetCity(&pCountry->m_array, sCity, NULL);
  if ( pMainCity ) { // ��������� �����?
    return '0';
  }
  CGeoRecord* pRegion = theGeoCache.GetRegion(&pCountry->m_array, sRegion);
  if ( NULL==pRegion ) { // ������ �� ������?
    return '0';
  }
  CGeoRecord* pSubCity = NULL;
  CGeoRecord* pCity = theGeoCache.GetCity(&pRegion->m_array, sCity, &pSubCity);
  if ( pCity ) { // ����� ���������� ����������?
    if ( pSubCity ) {
      szDistrictName   = pCity->m_Name;
      szSettlementName = pSubCity->m_Name;
      return '1';
    }
    szDistrictName = sCity;
    // szSettlementName = (false==szDistrict.IsEmpty()) ? szDistrict : szCity;
    if ( false==szDistrict.IsEmpty() ) {
      szSettlementName = szDistrict;
    }
    return '1';
  }
  CGeoRecord* pDistrict = theGeoCache.GetDistrict(&pRegion->m_array, szDistrict, &pCity);
  if ( pDistrict ) { // ����� � ������� ��� � ������?
    if ( pCity ) {   // ����� �������� ������ � ������ ������ ( �������: ��������, �����: �������������, ����: ������)
      szDistrictName = pCity->m_Name;
      szSettlementName = szCity;
      return '1';
    }
    szDistrictName = szDistrict;
    szSettlementName = szCity;
    return '2';
  }
  

  return '0'; // �� �������
}

/*
 SettlementTypeId - "��� ���������� ������" ( �������� �� �������� �̳��� = 1, 
                                              ������ = 2, 
                                              ������� = 5, 
                                              ������� ������� ���� = 3,
                                              �������� ���� = 8,
                                              ����� = 4,
                                              �ѳ������ = 6
                                              ��� ������� = 0)
*/
TCHAR GetSettlementTypeId(LPCTSTR szCityWithType, BOOL bDistrictInCity) {
  CCyrString szCity = szCityWithType;

  if ( bDistrictInCity ) {
    return '2'; // �����
  }
 
  if ( szCity.IsEmpty() ) {
    return '0'; // �� �������
  }
  int nSpace = szCity.ReverseFind(' ');
  if ( nSpace == -1 ) {
    return '0'; // �� �������
  }
  CString szType = szCity.Mid(nSpace+1);
  
  szType.MakeUpper();

  if ( szType==_T("�") || szType==_T("�.") ) {
    return '1'; // ̳���
  }
  if ( szType==_T("���") || szType==_T("���.") ) {
    return '3'; // ������ ������� ����
  }
  if ( szType==_T("�") || szType==_T("�.") || szType==_T("����")) {
    return '4'; // ����
  }
  if ( szType==_T("���") || szType==_T("���.") || szType==_T("��") || szType==_T("���-��") || szType==_T("�-��") || szType==_T("������") ) {
    return '5'; // ������
  }
  if ( szType==_T("��") || szType==_T("��.") || szType==_T("Ѳ������")) {
    return '6'; // ѳ������
  }

  return '0'; // �� �������
}

/*  StreetTypeId - "��� ������" ( �������� �� ��������
                                 �������� = 1,
                                 ������ = 2,
                                 �������� = 3,
                                 ��������� = 4,
                                 ��������� = 5,
                                 ������ = 6,
                                 ��� ������� = 0)

*/
void ParseStreet(CString& szStreet, CString& szTok, TCHAR& cType, CString& szStreetTypeName) {
  if ( szStreet.IsEmpty() ) {
    return;
  }

  struct SType { LPCTSTR szName; TCHAR cType; };

  static SType STypes[] =
  {
    { _T("��� "), '1' }, { _T("���."), '1' }, { _T("������ "),'1'}, { _T("�-�� "),'1'},

    { _T("����� "),'2'}, { _T("��."),   '2'}, { _T("��-�� "),'2'}, { _T("��-� "),'2'},

    { _T("�-� "),  '3' },{ _T("��� "), '3' }, { _T("���."), '3' }, { _T("������� "), '3' },

    { _T("�� "), '4'  }, { _T("��."), '4' },  { _T("�� "), '4'  },    { _T("��."), '4' },
    { _T("��-� "), '4'}, { _T("����� "),'4'}, { _T("�����."),'4'},    { _T("�������� "),'4'}, 
    { _T("����� "),'4'}, { _T("�����."),'4'}, { _T("�������� "),'4'}, { _T("��-�� "),'4'},

    { _T("�������� "), '5'}, { _T("����."), '5'},   { _T("����-� "), '5'},
    { _T("��-� "),     '5'}, { _T("�-� ") , '5'},
    { _T("���."),      '5'}, { _T("�������."),'5'}, { _T("��������� "),'5'},

    { _T("�������"),  '�' }, { _T("��-�"), '�' }, { _T("��."), '�' }, { _T("�� "), '�' },  { _T(" ��"), '�' }, 

    { _T("����� "),   '�' }, { _T("��� "),  '�' }, { _T("���."),'�' },

    { _T("���������"),'�'}, { _T("�-� "),  '�' }, { _T("��� "),'�' }, { _T("�-�����"),'�' }, { _T("�����-�"),'�' },

    { _T("�����"),    '�'}, { _T("��-�"),  '�'},  { _T("��-��"),'�'}

  };
  int nCounts = sizeof(STypes)/sizeof(STypes[0]);
  TCHAR cStreetType = '1';

  for( int i(0); i < nCounts; i++ ) {
    CString s = STypes[i].szName;
    if ( szStreet.Find(s) >= 0 ) {
      cStreetType = STypes[i].cType;
      szStreet.Replace(s, _T(""));
      break;
    }
    s.SetAt(0, CyrUpper(s[0]));
    if ( szStreet.Find(s) >= 0 ) {
      cStreetType = STypes[i].cType;
      szStreet.Replace(s, _T(""));
      break;
    }
  }
  szStreet.TrimLeft();
  szStreet.TrimRight();
  switch( cStreetType ) {
    case '�':
      cType = '6';
      szStreetTypeName = _T("�������");
      break;
    case '�':
      cType = '6';
      szStreetTypeName = _T("�����");
      break;
    case '�':
      cType = '6';
      szStreetTypeName = _T("���������");
      break;
    case '�':
      cType = '6';
      szStreetTypeName = _T("�����");
      break;
    case '1': case '2': case '3': case '4': case '5':
      cType = cStreetType;
      break;
    default :
      cType = cStreetType;
      szStreetTypeName = _T("������");
      break;
  }
  // return szStreetTypeName;
/*
  cType = '0';
  CString szType = _T("������");
  int nTok = 0;
  CString sTok = GetTok(szStreet, nTok, " .");
  while ( !sTok.IsEmpty() ) {
    if (  0==DBCompare(sTok,_T("�������")) || 0==DBCompare(sTok,_T("���")) || 0==DBCompare(sTok,_T("�-�")) )    { // �������
      szTok = sTok;
      cType = '3';    // �������
      return _T("�������");
    }    // �������
    else if ( 0==DBCompare(sTok,_T("���")) || 0==DBCompare(sTok,_T("������")) ) { // ������
      szTok = sTok;
      cType = '1';    // ������
      return _T("������");
    }
    else if ( 0==DBCompare(sTok,_T("��")) || 0==DBCompare(sTok,_T("��")) || 0==DBCompare(sTok,_T("��-�")) || 0==DBCompare(sTok,_T("����")) || 0==DBCompare(sTok,_T("�����")) || 0==DBCompare(sTok,_T("��������")) ) {                    // ��������
      szTok = sTok;
      cType = '4'; // ��������
      return _T("��������");
    }
    else if ( 0==DBCompare(sTok,_T("�����")) || 0==DBCompare(sTok,_T("��������")) ) { // ��������
      szTok = sTok;
      cType = '4'; // ��������
      return _T("��������");
    }
    else if ( 0==DBCompare(sTok,_T("����")) || 0==DBCompare(sTok,_T("�-�")) || 0==DBCompare(sTok,_T("��������")) ) { // ��������
      szTok = sTok;
      cType = '5'; // ��������
      return _T("��������");
    }
    else if ( 0==DBCompare(sTok,_T("�e�")) || 0==DBCompare(sTok,_T("�������")) || 0==DBCompare(sTok,_T("���������")) )  { // ���������
      szTok = sTok;
      cType = '5'; // ��������
      return _T("���������");
    }
    else if ( 0==DBCompare(sTok,_T("��")) || 0==DBCompare(sTok,_T("�����")) ) {       // �����
      szTok = sTok;
      cType = '2';    // �����
      return _T("�����");
    }
    else if ( 0==DBCompare(sTok,_T("���")) || 0==DBCompare(sTok,_T("�����")) ) {      // �����
      szTok = sTok;
      cType = '6'; // �����
      szStreetTypeName = _T("�����");
      return _T("�����");
    }
    else if ( 0==DBCompare(sTok,_T("�-�")) || 0==DBCompare(sTok,_T("��")) || 0==DBCompare(sTok,_T("��.")) || 0==DBCompare(sTok,_T("��-�")) || 0==DBCompare(sTok,_T("�������")) ) { // �������
      szTok = sTok;
      cType = '6'; // �����
      szStreetTypeName = _T("�������");
      return _T("�������");
    }
    else if ( 0==DBCompare(sTok,_T("�-�")) || 0==DBCompare(sTok,_T("���")) || 0==DBCompare(sTok,_T("�-�����")) || 0==DBCompare(sTok,_T("���������")) ) { // ���������
      szTok = sTok;
      cType = '6'; // �����
      szStreetTypeName = _T("���������");
      return _T("���������");
    }
    else if ( 0==DBCompare(sTok,_T("��-�")) || 0==DBCompare(sTok,_T("��-��")) || 0==DBCompare(sTok,_T("�����")) ) {    // �����
      szTok = sTok;
      cType = '6'; // �����
      szStreetTypeName = _T("�����");
      return _T("�����");
    }
    sTok = GetTok(szStreet, ++nTok, " .");
  }
  return _T("������");
*/
}

// BuildNumb - "����� �������"
// BuildType - "��� �����" (������� = 1, �������� = 2, ��� ������� = 0)
// BuildExtNumb - "�����" (�������, ������)
void ParseBuildNumb(CString& szBuild, CString& szBuildNumb, CString& szBuildExtNumb, TCHAR& BuildType) {
  CStringArray tokens;
  tokens.Add( GetTok(szBuild, 0, ",\\/") );
  tokens.Add( GetTok(szBuild, 1, ",\\/") );

  BuildType = '0';

  if ( tokens.GetAt(1).IsEmpty() ) {
    szBuildNumb = szBuild;
    szBuildExtNumb.Empty();
  }
  else {
    for( int i(0); i < 2; i++ ) {
      struct BuildTypes {
        TCHAR   cType;
        LPCTSTR szName;
      };

      static BuildTypes btypes[] = { {'0', "����"   }, {'0', "��" }, {'0', "�-�" },
                                     {'1', "������" }, {'1', "���"}, {'1', "���" },  {'1', "�-c" },
                                     {'2', "������" }, {'2', "���"}, {'2', "���" },  {'2', "�-�" },
                                     { 0, NULL }
                                   };
      CString sTok = tokens[i];
      for ( int j(0); btypes[j].szName; j++ ) {
        if ( sTok.Find(btypes[j].szName) >= 0 ) {
          if ( 0==i ) {
            szBuildExtNumb = tokens[0];
            szBuildNumb    = tokens[1];
            BuildType = btypes[j].cType;
          }
          else {
            szBuildNumb    = tokens[0];
            szBuildExtNumb = tokens[1];
            BuildType = btypes[j].cType;
          }
          return;
        }
      }
    }
    szBuildNumb    = tokens[0];
    szBuildExtNumb = tokens[1];
  }
}

/*
   Input:
   0=�������,
   1=��������������������� ����������� �������
   2=�������� ��� ����������
   3=��������� ������� �� ����������
 
   Returns:
          <!-- "��� ���������" ( �������� �� �������� �������� ����������� ������ = 1,
              ��������� ��� ����������� = 10,
              �������������� ������� ������ = 2,
              ��������� ��� ��������� �� ������������ ������ = 3,
              ����������� ����� ������ = 4,
              ����������� ����� �� ���������� � ������ = 5,
              ����������� ����� ������ = 6,
              ���������� ������� ������ = 9,
              ���������� ���������� ����������� ������ = 7,
              ������ �������� = 8,
              ���� DocType �� �������� 0, ���������, �� �������� �� �������) -->
*/
LPCTSTR GetDocType(BYTE bDocType) {
  switch(bDocType) {
    case 0: return _T("1");
    case 1: return _T("3");
    case 2: return _T("10");
    case 3: return _T("7");
  }
  return _T("8");
}