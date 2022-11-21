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

  if ( sz==_T("УКРАЇНА") || sz==_T("УКРАЇНИ") || sz==_T("УКРАЇНСЬКЕ") ||
       sz==_T("УКРАИНА") || sz==_T("УКРАИНИ") || sz==_T("УКРАИНСЬКОЕ")) {
    return '1';
  }
  return '2';
}

TCHAR GetCountryType(LPCTSTR szCountry) {
  CString sz = UpperString(szCountry);
  sz.TrimLeft();
  sz.TrimRight();

  if ( sz==_T("УКРАЇНА") || sz==_T("УКРАИНА") ) {
    return '1';
  }
  return '2';
}

int GetRegionId(LPCTSTR szRegion, LPCTSTR szCity) { // call it only if CountryType = '1' (Україна)
  CString sReg = UpperString(szRegion);
  sReg.TrimLeft();
  sReg.TrimRight();

  CString sCit = UpperString(szCity);
  sCit.TrimLeft();
  sCit.TrimRight();

  if ( sReg.Find(_T("КРИМ"))>=0 || sReg.Find(_T("КРЫМ"))>=0 ) return 1; // Автономна Республіка Крим
  if ( sReg.Find(_T("ВІН"))==0  || sReg.Find(_T("ВИН"))==0  ) return 2; // Вінницька обл.
  if ( sReg.Find(_T("ВОЛ"))==0 )                              return 3; // Волинська обл.
  if ( sReg.Find(_T("ДНІП"))==0 || sReg.Find(_T("ДНЕП"))==0 ) return 4; // Дніпропетровська обл.
  if ( sReg.Find(_T("ДОН"))==0 )                              return 5; // Донецька обл.
  if ( sReg.Find(_T("ДОН"))==0 )                              return 6; // Житомирська обл.
  if ( sReg.Find(_T("ЗАК"))==0 )                              return 7; // Закарпатська обл.
  if ( sReg.Find(_T("ЗАП"))==0 )                              return 8; // Запорізька обл.
  if ( sReg.Find(_T("ІВА"))==0 || sReg.Find(_T("ИВА"))==0 )   return 9; // Івано-Франківська обл.
  if ( sReg.Find(_T("КИЇ"))==0 || sReg.Find(_T("КИЄ"))==0 || sReg.Find(_T("КИЕ"))==0 ) return 10; // Київська обл.
  if ( sReg.Find(_T("КІР"))==0 || sReg.Find(_T("КИР"))==0 )   return 11;// Кіровоградська обл.
  if ( sReg.Find(_T("ЛУГ"))==0 )                              return 12;// Луганська обл.
  if ( sReg.Find(_T("ЛЬВ"))==0 )                              return 13;// Львівська обл.
  if ( sReg.Find(_T("МИК"))==0 || sReg.Find(_T("НИК"))==0 )   return 14;// Миколаївська обл.
  if ( sReg.Find(_T("ОДЕ"))==0 )                              return 15;// Одеська обл.
  if ( sReg.Find(_T("ПОЛ"))==0 )                              return 16;// Полтавська обл.
  if ( sReg.Find(_T("РІВ"))==0 || sReg.Find(_T("РОВ"))==0 )   return 17;// Рівненська обл.
  if ( sReg.Find(_T("СУМ"))==0 )                              return 18;// Сумська обл.
  if ( sReg.Find(_T("ТЕР"))==0 )                              return 19;// Тернопільська обл.
  if ( sReg.Find(_T("ХАР"))==0 )                              return 20;// Харківська обл.
  if ( sReg.Find(_T("ХЕР"))==0 )                              return 21;// Херсонська обл.
  if ( sReg.Find(_T("ХМЕ"))==0 )                              return 22;// Хмельницька обл.
  if ( sReg.Find(_T("ЧЕРК"))==0 )                             return 23;// Черкаська обл.
  if ( sReg.Find(_T("ЧЕРНІВ"))==0 || sReg.Find(_T("ЧЕРНОВ"))==0) return 24;// Чернівецька обл.
  if ( sReg.Find(_T("ЧЕРНІГ"))==0 || sReg.Find(_T("ЧЕРНИГ"))==0) return 25;// Чернігівська обл.

  if ( sReg.IsEmpty() ) {
    if ( sCit.Find(_T("КИЇВ"))==0 || sCit.Find(_T("КИЇВ"))==0 || sCit.Find(_T("КИЇВ"))==0 ) { // 26 - м. Київ
      return 26;
    }
    if ( sCit.Find(_T("Севас"))==0 ) { // 27 - м. Севастополь
      return 27;
    }
  }

  return 0;
}

// RegionTypeId - "Тип регіону" ( значення із словника «Місто» = 1, «Область» = 2, «не вказано» = 0)
TCHAR GetRegionTypeId(LPCTSTR szRegion, LPCTSTR szCity) {
  CString sReg = UpperString(szRegion);
  sReg.TrimLeft();
  sReg.TrimRight();

  CString sCit = UpperString(szCity);
  sCit.TrimLeft();
  sCit.TrimRight();
  if ( sReg.IsEmpty() && sCit.IsEmpty() ) {
    return '0'; // Не вказано
  }

  switch( GetRegionId(szRegion, szCity) ) {
    case 26:  // м. Київ
    case 27:  // м. Севастополь
      return '1';
  }
  return '2';
}

CString MakeCountryName(LPCTSTR szCountry) {
  CString s;
  s.Format(_T(" CountryName=\"%s\""), szCountry);
  return s;
}


// DistrictTypeId - "Тип району" ( значення із словника «Місто» = 1, «Район» = 2, «не вказано» = 0)
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
  if ( pMainCity ) { // Областной центр?
    return '0';
  }
  CGeoRecord* pRegion = theGeoCache.GetRegion(&pCountry->m_array, sRegion);
  if ( NULL==pRegion ) { // Регион не указан?
    return '0';
  }
  CGeoRecord* pSubCity = NULL;
  CGeoRecord* pCity = theGeoCache.GetCity(&pRegion->m_array, sCity, &pSubCity);
  if ( pCity ) { // Город областного подчинения?
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
  if ( pDistrict ) { // Район в области или в городе?
    if ( pCity ) {   // Город подчинен району в другом городе ( Область: Донецька, район: Пролетарський, місто: Моспіне)
      szDistrictName = pCity->m_Name;
      szSettlementName = szCity;
      return '1';
    }
    szDistrictName = szDistrict;
    szSettlementName = szCity;
    return '2';
  }
  

  return '0'; // не вказано
}

/*
 SettlementTypeId - "Тип населеного пункту" ( значення із словника «Місто» = 1, 
                                              «Район» = 2, 
                                              «Селище» = 5, 
                                              «Селище міського типу» = 3,
                                              «Селищна рада» = 8,
                                              «Село» = 4,
                                              «Сільрада» = 6
                                              «не вказано» = 0)
*/
TCHAR GetSettlementTypeId(LPCTSTR szCityWithType, BOOL bDistrictInCity) {
  CCyrString szCity = szCityWithType;

  if ( bDistrictInCity ) {
    return '2'; // Район
  }
 
  if ( szCity.IsEmpty() ) {
    return '0'; // не вказано
  }
  int nSpace = szCity.ReverseFind(' ');
  if ( nSpace == -1 ) {
    return '0'; // не вказано
  }
  CString szType = szCity.Mid(nSpace+1);
  
  szType.MakeUpper();

  if ( szType==_T("М") || szType==_T("М.") ) {
    return '1'; // Місто
  }
  if ( szType==_T("СМТ") || szType==_T("СМТ.") ) {
    return '3'; // Селище міського типу
  }
  if ( szType==_T("С") || szType==_T("С.") || szType==_T("СЕЛО")) {
    return '4'; // Село
  }
  if ( szType==_T("СЛЩ") || szType==_T("СЛЩ.") || szType==_T("СЩ") || szType==_T("СЕЛ-ЩЕ") || szType==_T("С-ЩЕ") || szType==_T("СЕЛИЩЕ") ) {
    return '5'; // Селище
  }
  if ( szType==_T("СР") || szType==_T("СР.") || szType==_T("СІЛЬРАДА")) {
    return '6'; // Сільрада
  }

  return '0'; // не вказано
}

/*  StreetTypeId - "Тип вулиці" ( значення із словника
                                 «Вулиця» = 1,
                                 «Площа» = 2,
                                 «Бульвар» = 3,
                                 «Проспект» = 4,
                                 «Провулок» = 5,
                                 «Інший» = 6,
                                 «не вказано» = 0)

*/
void ParseStreet(CString& szStreet, CString& szTok, TCHAR& cType, CString& szStreetTypeName) {
  if ( szStreet.IsEmpty() ) {
    return;
  }

  struct SType { LPCTSTR szName; TCHAR cType; };

  static SType STypes[] =
  {
    { _T("вул "), '1' }, { _T("вул."), '1' }, { _T("вулиця "),'1'}, { _T("в-ця "),'1'},

    { _T("площа "),'2'}, { _T("пл."),   '2'}, { _T("пл-ща "),'2'}, { _T("пл-а "),'2'},

    { _T("б-р "),  '3' },{ _T("бул "), '3' }, { _T("бул."), '3' }, { _T("бульвар "), '3' },

    { _T("пс "), '4'  }, { _T("пс."), '4' },  { _T("пр "), '4'  },    { _T("пр."), '4' },
    { _T("пр-т "), '4'}, { _T("просп "),'4'}, { _T("просп."),'4'},    { _T("проспект "),'4'}, 
    { _T("прошп "),'4'}, { _T("прошп."),'4'}, { _T("прошпект "),'4'}, { _T("пр-кт "),'4'},

    { _T("провулок "), '5'}, { _T("пров."), '5'},   { _T("пров-к "), '5'},
    { _T("пр-к "),     '5'}, { _T("п-к ") , '5'},
    { _T("пер."),      '5'}, { _T("перевул."),'5'}, { _T("перевулок "),'5'},

    { _T("квартал"),  'к' }, { _T("кв-л"), 'к' }, { _T("кв."), 'к' }, { _T("кв "), 'к' },  { _T(" кв"), 'к' }, 

    { _T("куток "),   'у' }, { _T("кут "),  'у' }, { _T("кут."),'у' },

    { _T("мікрорайон"),'м'}, { _T("м-н "),  'м' }, { _T("мрн "),'м' }, { _T("м-район"),'м' }, { _T("мікрор-н"),'м' },

    { _T("проїзд"),    'п'}, { _T("пр-д"),  'п'},  { _T("пр-зд"),'п'}

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
    case 'к':
      cType = '6';
      szStreetTypeName = _T("квартал");
      break;
    case 'у':
      cType = '6';
      szStreetTypeName = _T("куток");
      break;
    case 'м':
      cType = '6';
      szStreetTypeName = _T("мікрорайон");
      break;
    case 'п':
      cType = '6';
      szStreetTypeName = _T("проїзд");
      break;
    case '1': case '2': case '3': case '4': case '5':
      cType = cStreetType;
      break;
    default :
      cType = cStreetType;
      szStreetTypeName = _T("вулиця");
      break;
  }
  // return szStreetTypeName;
/*
  cType = '0';
  CString szType = _T("вулиця");
  int nTok = 0;
  CString sTok = GetTok(szStreet, nTok, " .");
  while ( !sTok.IsEmpty() ) {
    if (  0==DBCompare(sTok,_T("бульвар")) || 0==DBCompare(sTok,_T("бул")) || 0==DBCompare(sTok,_T("б-р")) )    { // бульвар
      szTok = sTok;
      cType = '3';    // Бульвар
      return _T("бульвар");
    }    // бульвар
    else if ( 0==DBCompare(sTok,_T("вул")) || 0==DBCompare(sTok,_T("вулиця")) ) { // вулиця
      szTok = sTok;
      cType = '1';    // Вулиця
      return _T("вулиця");
    }
    else if ( 0==DBCompare(sTok,_T("пс")) || 0==DBCompare(sTok,_T("пр")) || 0==DBCompare(sTok,_T("пр-т")) || 0==DBCompare(sTok,_T("прос")) || 0==DBCompare(sTok,_T("просп")) || 0==DBCompare(sTok,_T("проспект")) ) {                    // проспект
      szTok = sTok;
      cType = '4'; // Проспект
      return _T("проспект");
    }
    else if ( 0==DBCompare(sTok,_T("прошп")) || 0==DBCompare(sTok,_T("прошпект")) ) { // прошпект
      szTok = sTok;
      cType = '4'; // Проспект
      return _T("прошпект");
    }
    else if ( 0==DBCompare(sTok,_T("пров")) || 0==DBCompare(sTok,_T("п-к")) || 0==DBCompare(sTok,_T("провулок")) ) { // провулок
      szTok = sTok;
      cType = '5'; // Провулок
      return _T("провулок");
    }
    else if ( 0==DBCompare(sTok,_T("пeр")) || 0==DBCompare(sTok,_T("перевул")) || 0==DBCompare(sTok,_T("перевулок")) )  { // перевулок
      szTok = sTok;
      cType = '5'; // Провулок
      return _T("перевулок");
    }
    else if ( 0==DBCompare(sTok,_T("пл")) || 0==DBCompare(sTok,_T("площа")) ) {       // площа
      szTok = sTok;
      cType = '2';    // Площа
      return _T("площа");
    }
    else if ( 0==DBCompare(sTok,_T("кут")) || 0==DBCompare(sTok,_T("куток")) ) {      // куток
      szTok = sTok;
      cType = '6'; // Інший
      szStreetTypeName = _T("куток");
      return _T("куток");
    }
    else if ( 0==DBCompare(sTok,_T("к-л")) || 0==DBCompare(sTok,_T("кв")) || 0==DBCompare(sTok,_T("кв.")) || 0==DBCompare(sTok,_T("кв-л")) || 0==DBCompare(sTok,_T("квартал")) ) { // квартал
      szTok = sTok;
      cType = '6'; // Інший
      szStreetTypeName = _T("квартал");
      return _T("квартал");
    }
    else if ( 0==DBCompare(sTok,_T("м-н")) || 0==DBCompare(sTok,_T("мрн")) || 0==DBCompare(sTok,_T("м-район")) || 0==DBCompare(sTok,_T("мікрорайон")) ) { // мікрорайон
      szTok = sTok;
      cType = '6'; // Інший
      szStreetTypeName = _T("мікрорайон");
      return _T("мікрорайон");
    }
    else if ( 0==DBCompare(sTok,_T("пр-д")) || 0==DBCompare(sTok,_T("пр-зд")) || 0==DBCompare(sTok,_T("проїзд")) ) {    // проїзд
      szTok = sTok;
      cType = '6'; // Інший
      szStreetTypeName = _T("проїзд");
      return _T("проїзд");
    }
    sTok = GetTok(szStreet, ++nTok, " .");
  }
  return _T("вулиця");
*/
}

// BuildNumb - "Номер будинку"
// BuildType - "Тип будівлі" («Корпус» = 1, «Секція» = 2, «не вказано» = 0)
// BuildExtNumb - "Номер" (корпусу, секції)
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

      static BuildTypes btypes[] = { {'0', "блок"   }, {'0', "бл" }, {'0', "б-к" },
                                     {'1', "корпус" }, {'1', "кор"}, {'1', "крп" },  {'1', "к-c" },
                                     {'2', "секція" }, {'2', "сек"}, {'2', "скт" },  {'2', "с-я" },
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
   0=паспорт,
   1=загальногромадянський закордонний паспорт
   2=свідоцтво про народження
   3=тимчасова посвідка на проживання
 
   Returns:
          <!-- "Тип документа" ( значення із словника «Паспорт громадянина України» = 1,
              «Свідоцтво про народження» = 10,
              «Дипломатичний паспорт України» = 2,
              «Свідоцтво про належність до громадянства України» = 3,
              «Посвідчення особи моряка» = 4,
              «Посвідчення особи на повернення в Україну» = 5,
              «Посвідчення члена екіпажу» = 6,
              «Службовий паспорт України» = 9,
              «Тимчасове посвідчення громадянина України» = 7,
              «Інший документ» = 8,
              якщо DocType має значення 0, вважається, що документ не вказано) -->
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