// SetRagsPage.cpp : implementation file
//

#include "stdafx.h"
#include "EraWiz.h"
#include "SetRagsPage.h"
#include "LoadDlg.h"

#include <math.h>

#include "..\Common\CyrString.h"
#include "..\Common\MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRList theRList;

CString g_szRagsName;
CString g_szFullRagsName;
long    g_RegionID;
long    g_DistrictID;
long    g_CityID;
long    g_RagsID = 0;
CString g_szParentRags;

extern CDaoDatabase theDatabase;
void WriteToDefaults(CDaoRecordset* prs, LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal);

CString DecodeRagsNameWithoutAbbr(const CString& sRagsName) {
  CMapStringToString map;
  map.SetAt(_T("АР"),            _T("Автономної Республіки")                    );
  map.SetAt(_T("ВРАГС"),         _T("відділ реєстрації актів цивільного стану") );
  map.SetAt(_T("ВРАЦС"),         _T("відділ реєстрації актів цивільного стану") );
  map.SetAt(_T("ВДРАЦС"),        _T("відділ державної реєстрації актів цивільного стану") );
  map.SetAt(_T("ГУЮ"),           _T("Головного управління юстиції")             );
  map.SetAt(_T("ГРОМАДЯНСЬКОГО"),_T("цивільного")                               );
  map.SetAt(_T("В"),             _T("виконком")                                 );
  map.SetAt(_T("ВО"),            _T("виконавчий орган")                         );
  map.SetAt(_T("В.РАГС"),        _T("відділ реєстрації актів цивільного стану") );
  map.SetAt(_T("В.РАЦС"),        _T("відділ реєстрації актів цивільного стану") );
  map.SetAt(_T("В/РАГС"),        _T("відділ реєстрації актів цивільного стану") );
  map.SetAt(_T("В/РАЦС"),        _T("відділ реєстрації актів цивільного стану") );
  map.SetAt(_T("М-Р"),           _T("міської ради")                             );
  map.SetAt(_T("М.Р"),           _T("міської ради")                             );
  map.SetAt(_T("М/Р"),           _T("міської ради")                             );
  map.SetAt(_T("МР"),            _T("міської ради")                             );
  map.SetAt(_T("МУЮ"),           _T("міського управління юстиції")              );
  map.SetAt(_T("МРУЮ"),          _T("міськрайонного управління юстиції")        );
  map.SetAt(_T("Р"),             _T("району")                                   );
  map.SetAt(_T("Р-НУ"),          _T("району")                                   );
  map.SetAt(_T("р-ну"),          _T("району")                                   );
  map.SetAt(_T("РАГС"),          _T("реєстрації актів цивільного стану")        );
  map.SetAt(_T("РАЦС"),          _T("реєстрації актів цивільного стану")        );
  map.SetAt(_T("РУЮ"),           _T("районного управління юстиції")             );
  map.SetAt(_T("О"),             _T("області")                                  );
  map.SetAt(_T("ОБЛ"),           _T("області")                                  );
  map.SetAt(_T("ОБЛ."),          _T("області")                                  );
  map.SetAt(_T("ОУЮ"),           _T("обласного управління юстиції")             );

  map.SetAt(_T("С.Р"),           _T("сільської ради")                           );
  map.SetAt(_T("С/Р"),           _T("сільської ради")                           );
  map.SetAt(_T("С-Р"),           _T("сільської ради")                           );
  map.SetAt(_T("СР"),            _T("сільської ради")                           );
  map.SetAt(_T("СЩР"),           _T("селищної ради")                            );


  CString szRagsName;
  szRagsName.Format(_T(" %s "), sRagsName);
  if ( szRagsName.Find(_T("в АР Крим")) > 0 ) {
    szRagsName.Replace(_T("в АР Крим"), _T("в Автономній Республіці Крим"));
  }
  else if ( szRagsName.Find(_T(" АР Крим")) > 0 ) {
    szRagsName.Replace(_T(" АР Крим"), _T(" Автономної Республіки Крим"));
  }
  if ( szRagsName.Find(_T(" ВРА ")) >= 0 ) {
    szRagsName.Replace(_T(" ВРА "), _T(" Відділ реєстрації актів "));
  }

  CString sDecoded;
  sDecoded.Format(_T(" %s "), szRagsName );
  char* pBuf = new char[szRagsName.GetLength()+4];
  strcpy(pBuf, szRagsName);

  char* p = strtok(pBuf, " ");
  while(p) {
    CString sKey = UpperString(p);
    CString sValue;
    if ( map.Lookup(sKey, sValue) ) {
      CString sFind, sReplace;
      sFind.Format(_T(" %s "), p );
      sReplace.Format(_T(" %s "), sValue );
      sDecoded.Replace(sFind, sReplace);
    }
    else {
    }
    p = strtok(NULL, " ");
  }
  delete pBuf;
  szRagsName = Trim(sDecoded);
  if ( szRagsName.GetLength() ) {
    szRagsName.SetAt( 0, CyrUpper(szRagsName.GetAt(0)) );
  }
  return szRagsName;
}

/*
CString CompactRagsName(const CString& sRagsName) {
  CMapStringToString map;
  map.SetAt(_T(" АР "),         _T(" Автономної Республіки ")                   );
  map.SetAt(_T(" ВРАЦС "),      _T(" відділ реєстрації актів цивільного стану "));
  map.SetAt(_T(" ГУЮ "),        _T(" Головного управління юстиції ")            );
  map.SetAt(_T(" В "),          _T(" виконком ")                                );
  map.SetAt(_T(" В "),          _T(" Виконком ")                                );
  map.SetAt(_T(" м."),          _T(" м. ")                                      );
  map.SetAt(_T(" мр "),         _T(" міської ради ")                            );
  map.SetAt(_T(" МУЮ "),        _T(" міського управління юстиції ")             );
  map.SetAt(_T(" МРУЮ "),       _T(" міськрайонного управління юстиції ")       );
  map.SetAt(_T(" р "),          _T(" району ")                                  );
  map.SetAt(_T(" РУЮ "),        _T(" районного управління юстиції ")            );
  map.SetAt(_T(" о "),          _T(" області ")                                 );
  map.SetAt(_T(" ОУЮ "),        _T(" обласного управління юстиції ")            );
  map.SetAt(_T(" ср "),         _T(" сільської ради ")                          );
  map.SetAt(_T(" сщр "),        _T(" селищної ради ")                           );

  CString sEncoded;
  sEncoded.Format(_T(" %s "), sRagsName );

  POSITION pos = map.GetStartPosition();
  while( pos ) {
    CString sKey, sValue;
    map.GetNextAssoc(pos, sKey, sValue);
    if ( sEncoded.Find(sValue)>=0 ) {
      sEncoded.Replace(sValue, sKey);
    }
  }

  return Trim(sEncoded);
}
*/

bool IsMainCityRags(const CString& sRagsName, LPCTSTR szCity) {
  CString s, sCity;

/************************************** : by VK at 22.10.2005 0:23:13 **\
  if ( sRagsName.Find(_T(" мр ")) >=0 ) {
    return false;
  }
\************************************** : by VK at 22.10.2005 0:23:15 **/
  sCity = szCity;
  if ( sCity.IsEmpty() )
    return false;
  else if ( sCity.Right(2)==_T("ів") ) { // Харків, Глухів, Львов
    sCity.TrimRight('в');
    sCity.TrimRight('і');
    sCity += _T("ова");
  }
  else if ( sCity.Right(1)=="а" ) { // Одеса, Потава
    sCity.TrimRight('а');
    sCity += _T("и");
  }
  else if ( sCity.Right(1)=="и" ) { // Суми, Черкаси
    sCity.TrimRight('и');
  }
  else if ( sCity.Right(1)=="і" ) { // Чернівці
    sCity += _T("в");
  }
  else if ( sCity.Right(2)=="жя" ) {// Запоріжжя
    ; // notning
  }
  else if ( sCity.Right(2)=="ий" ) {// Хмельницький
    sCity.TrimRight("ий");
  }
  else if ( sCity.Right(1)=="я" ) { // Вінниця
    sCity.TrimRight('я');
    sCity += _T("і");
  }
  else if ( sCity.Right(1)=="ь" ) { // Тернопіль
    sCity.TrimRight('ь');
    sCity += _T("я");
  }
  else if ( sCity.Right(2)=="їв" ) {// Миколаїв
    sCity.TrimRight('в');
    sCity.TrimRight('ї');
    sCity += _T("єва");
  }
  else {
    switch( sCity.Right(1).GetAt(0) ) {
      case 'б': case 'в': case 'д': case 'г': case 'ж': case 'з':
      case 'к': case 'л': case 'м': case 'н': case 'п': case 'р':
      case 'с': case 'т': case 'ф': case 'х': case 'ц': case 'ч': case 'ш': case 'щ':
        sCity += _T("а");
        break;
    }
  }

  s.Format(_T("м.%s"), sCity);
  if ( sRagsName.Find(s)>=0 )
    return true;
  

  sCity = szCity;
  if ( sCity.Right(1)=="а" )      { // Одеса, Потава
    sCity.TrimRight('а');
    sCity += _T("ьк");
  }
  else if ( sCity.Right(3)==_T("вці") ) { // Чернівці
    sCity.TrimRight('і');
    sCity.TrimRight('ц');
    sCity.TrimRight('в');
    sCity += _T("вецьк");
  }
  else if ( sCity==_T("Запоріжжя") )  {// Запоріжжя
    sCity = _T("Запорізьк");
  }
  else if ( sCity.Right(1)=="я" ) { // Вінниця
    sCity.TrimRight('я');
    sCity += _T("ьк");
  }
  else if ( sCity.Right(1)=='е' ) { // Рівне
    sCity += _T("нськ");
  }
  else  {
    switch( sCity.Right(1).GetAt(0) ) {
      case 'б': case 'в': case 'д': case 'г': case 'ж': case 'з':
      case 'к': case 'л': case 'м': case 'н': case 'п': case 'р':
      case 'с': case 'т': case 'ф': case 'х': case 'ц': case 'ч': case 'ш': case 'щ':
        sCity += _T("ськ");
        break;
    }
  }
  s.Format(_T("%sий міський"), sCity);
  if ( sRagsName.Find(s)>=0 )
    return true;

  s.Format(_T("Міський ВРАЦС %sого"), sCity);
  if ( sRagsName.Find(s)>=0 )
    return true;

  s.Format(_T("%sого МУЮ"), sCity);
  if ( sRagsName.Find(s)>=0 )
    return true;

  s.Format(_T("%sого міського"), sCity);
  if ( sRagsName.Find(s)>=0 )
    return true;

  s.Format(_T("%sого ОУЮ"), sCity);
  if ( sRagsName.Find(s)>=0 )
    return true;

  return false;
}



CString GetRegionFromDB(const CString& sRegion, long& lID) {
  CString s;
  CDaoRecordset rs(&theDatabase);
  try {
    rs.Open(dbOpenDynaset, _T("SELECT ID,NAME FROM GEOGRAPHY WHERE PARENT=1"), dbReadOnly);
    while ( !rs.IsEOF() ) {
      long id              = GetFieldLong  (&rs, _T("ID"));
      CString sFoundRegion = GetFieldString(&rs, _T("NAME"));
      if ( sRegion.Left(4)==sFoundRegion.Left(4) ) {
        s = sFoundRegion;
        lID = id;
        break;
      }
      rs.MoveNext();
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
	}
  return s;
}

CString GetCityFromDB(const CString& sCity, long ParentID, long& lID) {
  CString s;
  CDaoRecordset rs(&theDatabase);
  try {
    CString sql;
    sql.Format(_T("SELECT ID,NAME,TYPE FROM GEOGRAPHY WHERE PARENT=%d"), ParentID);
    rs.Open(dbOpenDynaset, sql, dbReadOnly);


    CDWordArray parents;
    while ( !rs.IsEOF() ) {
      long id            = GetFieldLong  (&rs, _T("ID"));
      CString sFoundCity = GetFieldString(&rs, _T("NAME"));
      CString sType      = GetFieldString(&rs, _T("TYPE"));
      if ( sCity.Left(4)==sFoundCity.Left(4) && FALSE==sType.IsEmpty() && sType.GetAt(0)=='м' ) {
        s = sFoundCity;
        lID = id;
        break;
      }
      parents.Add ( id );
      rs.MoveNext();
    }
    rs.Close();

    if ( s.IsEmpty() ) {
      for( int i(0); i < parents.GetSize(); i++ ) {
        s = GetCityFromDB(sCity, (long)parents.GetAt(i), lID);
        if ( FALSE==s.IsEmpty() )
          break;
      }
    }
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
	}
  return s;
}

int CompareCityNames(const CString& s1, const CString& s2) {
  int nCount = 0;
  CCyrString sz1(s1), sz2(s2);
  sz1.Replace(_T("ської"), _T(""));
  sz1.Replace(" ", "");
  sz1.Replace("-", "");
  sz2.Replace(" ", "");
  sz2.Replace("-", "");
  sz1.MakeLower();
  sz2.MakeLower();


  int nLen1 = sz1.GetLength();
  int nLen2 = sz2.GetLength();
  int nMinLen = min(nLen1, nLen2);
  int p = 10;
  for( int i(0); i < nMinLen; i++ ) {
    if ( sz1[i]==sz2[i] ) {
      nCount++;
      if ( p > 0 ) {
        nCount += (int)pow(2, p);
      }
    }
    p--;
  }
  return nCount;
}

CString GetCityFromDB(const CString& sCity, long ParentID, long& lID, CString& szType) {
  CString s;
  CDaoRecordset rs(&theDatabase);


  int nCount = 4;
  if ( sCity.Left(4)==_T("Ново") ) {
    nCount = 8;
  }
  else if ( sCity.Left(5)==_T("Старо") ) {
    nCount = 9;
  }

  int  nEqualLetters = 0;

  try {
    CString sql;
    sql.Format(_T("SELECT ID,NAME,TYPE FROM GEOGRAPHY WHERE PARENT=%d"), ParentID);
    rs.Open(dbOpenDynaset, sql, dbReadOnly);

    while ( !rs.IsEOF() ) {
      long id            = GetFieldLong  (&rs, _T("ID"));
      CString sFoundCity = GetFieldString(&rs, _T("NAME"));
      CString sType      = GetFieldString(&rs, _T("TYPE"));

      int nCompareRes = CompareCityNames(sCity, sFoundCity);

      if ( nCompareRes > nEqualLetters ) {
        nEqualLetters = nCompareRes;
        s = sFoundCity;
        lID = id;
        if ( sType.GetAt(0)=='м') {
          szType = _T("місто");
        }
        else if ( sType==_T("смт") || sType==_T("смт.") ) {
          szType = _T("смт");
        }
        else if ( sType==_T("слщ") || sType==_T("с-ще") ) {
          szType = _T("селище");
        }
        else if ( sType.GetAt(0)=='с' ) {
          szType = _T("село");
        }
      }
      rs.MoveNext();
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
	}
  return s;
}

CString GetRegionFromRagsName(const CString& sRagsName) {
  CString sRegion, s;
  g_RegionID = g_CityID = 0;
  g_szCity = g_szBirthCity = g_szCityType = g_szBirthCityType = _T("");

  long RegionID = 0;

  if ( sRagsName.Find(_T("Севастополя")) >=0 ) {
    sRegion = _T("");
    g_RegionID = 0;
    GetRegionFromDB(_T("Севастополя"), RegionID);
    g_CityID = RegionID;
    g_szCity = _T("Севастополь");
    g_szCityType = _T("місто");
  }
  else if ( sRagsName.Find(_T("Сімферополя")) >=0 ) {
    sRegion = _T("Автономна Республіка Крим");
    // g_RegionID = 11897;
    GetRegionFromDB(_T("Крим"), g_RegionID);
    g_szCity = _T("Сімферополь");
    // g_CityID = 11905;
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
    g_szCityType = _T("місто");
  }
  else if ( sRagsName.Right(4)==_T("Крим") ) {
    sRegion = _T("Автономна Республіка Крим");
    g_RegionID = 11897;
    GetRegionFromDB(_T("Крим"), g_RegionID);
  }
  else if ( sRagsName.Right(5)==_T("Києва") || sRagsName.Right(5)==_T("Києві") ) {
    sRegion = _T("");
    g_RegionID = 0;
    g_CityID = 9678;
    g_szCity = _T("Київ");
    GetRegionFromDB(g_szCity, g_CityID);
    g_szCityType = _T("місто");
  }
  else if ( IsMainCityRags(sRagsName, _T("Вінниця")) ) {
    sRegion = GetRegionFromDB(_T("Вінницька"), g_RegionID);
    g_CityID = 3;
    g_szCity = _T("Вінниця");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
    g_szCityType = _T("місто");
  }
  else if ( IsMainCityRags(sRagsName, _T("Луцьк")) ) {
    sRegion = GetRegionFromDB(_T("Волинська"), g_RegionID);
    g_CityID = 3;
    g_szCity = _T("Луцьк");
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Дніпропетровськ")) ) {
    sRegion = GetRegionFromDB(_T("Дніпропетровська"), g_RegionID);
    g_CityID = 2659;
    g_szCity = _T("Дніпропетровськ");
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Донецьк"))  ) {
    sRegion = GetRegionFromDB(_T("Донецька"), g_RegionID);
    g_CityID = 4196;
    g_szCity = _T("Донецьк");
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Житомир")) ) {
    sRegion = GetRegionFromDB(_T("Житомирська"), g_RegionID);
    g_szCity = _T("Житомир");
    g_CityID = 5473;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Ужгород")) ) {
    sRegion = GetRegionFromDB(_T("Закарпатська"), g_RegionID);
    g_szCity = _T("Ужгород");
    g_CityID = 7176;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Запоріжжя")) ) {
    sRegion = GetRegionFromDB(_T("Запорізька"), g_RegionID);
    g_szCity = _T("Запоріжжя");
    g_CityID = 7800;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Івано-Франківськ")) ) {
    sRegion = GetRegionFromDB(_T("Івано-Франківська"), g_RegionID);
    g_szCity = _T("Івано-Франківськ");
    g_CityID = 8771;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Кіровоград")) ) {
    sRegion = GetRegionFromDB(_T("Кіровоградська"), g_RegionID);
    g_szCity = _T("Кіровоград");
    g_CityID = 10829;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Луганськ")) ) {
    sRegion = GetRegionFromDB(_T("Луганська"), g_RegionID);
    g_szCity = _T("Луганськ");
    g_CityID = 12913;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Львів")) ) {
    sRegion = GetRegionFromDB(_T("Львівська"), g_RegionID);
    g_szCity = _T("Львів");
    g_CityID = 13867;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Миколаїв")) ) {
    sRegion = GetRegionFromDB(_T("Миколаївська"), g_RegionID);
    g_szCity = _T("Миколаїв");
    g_CityID = 14693;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Одеса")) ) {
    sRegion = GetRegionFromDB(_T("Одеська"), g_RegionID);
    g_szCity = _T("Одеса");
    g_CityID = 16763;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Полтава")) ) {
    sRegion = GetRegionFromDB(_T("Полтавська"), g_RegionID);
    g_szCity = _T("Полтава");
    g_CityID = 17977;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Рівне")) ) {
    sRegion = GetRegionFromDB(_T("Рівненська"), g_RegionID);
    g_szCity = _T("Рівне");
    g_CityID = 19283;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Суми")) ) {
    sRegion = GetRegionFromDB(_T("Сумська"), g_RegionID);
    g_szCity = _T("Суми");
    g_CityID = 20179;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Тернопіль")) ) {
    sRegion = GetRegionFromDB(_T("Тернопільська"), g_RegionID);
    g_szCity = _T("Тернопіль");
    g_CityID = 21705;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Харків")) ) {
    sRegion = GetRegionFromDB(_T("Харківська"), g_RegionID);
    g_szCity = _T("Харків");
    g_CityID = 22789;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Херсон")) ) {
    sRegion = GetRegionFromDB(_T("Херсонська"), g_RegionID);
    g_szCity = _T("Херсон");
    g_CityID = 24571;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Хмельницький")) ) {
    sRegion = GetRegionFromDB(_T("Хмельницька"), g_RegionID);
    g_szCity = _T("Хмельницький");
    g_CityID = 24702;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Черкаси")) ) {
    sRegion = GetRegionFromDB(_T("Черкаська"), g_RegionID);
    g_szCity = _T("Черкаси");
    g_CityID = 26176;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("Чернівці")) ) {
    sRegion = GetRegionFromDB(_T("Чернівецька"), g_RegionID);
    g_szCity = _T("Чернівці");
    g_CityID = 27044;
    g_szCityType = _T("місто");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( sRagsName.Right(4)==_T("ої о") ) {
    s = GetTokenBefore(sRagsName, sRagsName.GetLength()-4);
    if ( FALSE==s.IsEmpty() ) {
      sRegion = GetRegionFromDB(s, g_RegionID);
    }
  }
  else if (sRagsName.Right(7)==_T("ого ОУЮ")) {
    s = GetTokenBefore(sRagsName, sRagsName.GetLength()-7);
    if ( FALSE==s.IsEmpty() ) {
      sRegion = GetRegionFromDB(s, g_RegionID);
    }
  }

  return sRegion;
}


CString GetCityFromRagsName(const CString& sRagsName) {
  CString sCity, s;
  int offs = 0;

  s = _T(" мр ");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs-4);
    if ( g_RegionID ) {
      sCity = GetCityFromDB(s, g_RegionID, g_CityID);
      if ( FALSE==sCity.IsEmpty() ) {
        g_szCityType = _T("місто");
        return sCity;
      }
    }
  }

  s = _T("по місту ");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs+s.GetLength()+1);
    if ( g_RegionID ) {
      sCity = GetCityFromDB(s, g_RegionID, g_CityID);
      if ( FALSE==sCity.IsEmpty() ) {
        g_szCityType = _T("місто");
        return sCity;
      }
    }
  }
  s = _T("по м.");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs+s.GetLength()+1);
    if ( g_RegionID ) {
      sCity = GetCityFromDB(s, g_RegionID, g_CityID);
      if ( FALSE==sCity.IsEmpty() ) {
        g_szCityType = _T("місто");
        return sCity;
      }
    }
  }
  s = _T("МУЮ ");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs-2);
    if ( g_RegionID ) {
      sCity = GetCityFromDB(s, g_RegionID, g_CityID);
      if ( FALSE==sCity.IsEmpty() ) {
        g_szCityType = _T("місто");
        return sCity;
      }
    }
  }

  s = _T("Міський ВРАЦС");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs+s.GetLength()+1);
    if ( g_RegionID ) {
      sCity = GetCityFromDB(s, g_RegionID, g_CityID);
      if ( FALSE==sCity.IsEmpty() ) {
        g_szCityType = _T("місто");
        return sCity;
      }
    }
  }

  s = _T("ий міський");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs);
    if ( g_RegionID ) {
      sCity = GetCityFromDB(s, g_RegionID, g_CityID);
      if ( FALSE==sCity.IsEmpty() ) {
        g_szCityType = _T("місто");
        return sCity;
      }
    }
  }
  return sCity;
}

CString GetCityFromRagsName(const CString& sRagsName, long lParentID) {
  CString sCity;

  if ( sRagsName==_T("В Лугівської ср Рахівського р Закарпатської о") ) {
    sCity = _T("Луги");
  }
  else {
    LPCTSTR szFind[3] = { _T(" мр "), _T(" ср "), _T(" сщр ") };
    for( int i(0); i < 3; i++ ) {
      CString s = szFind[i];
      int offs = sRagsName.Find(s);
      if ( offs >= 0 ) {
        s = GetTokenBefore(sRagsName, offs-2);
        sCity = GetCityFromDB(s, lParentID, g_CityID, g_szCityType);
        if ( FALSE==sCity.IsEmpty() ) {
          return sCity;
        }
      }
    }
  }
  return sCity;
}


CString GetDistrictFromDB(const CString& sDistrict, long ParentID, long& lID) {
  CString s, szDistrict = sDistrict;
  CDaoRecordset rs(&theDatabase);
  CDWordArray daCities;

  if ( szDistrict.Right(3)==_T("ого") ) {
    szDistrict.TrimRight(_T("ого"));
  }

  try {
    CString sql;
    sql.Format(_T("SELECT ID,NAME,TYPE FROM GEOGRAPHY WHERE PARENT=%d"), ParentID);
    rs.Open(dbOpenDynaset, sql, dbReadOnly);

    while ( !rs.IsEOF() ) {
      long id                = GetFieldLong  (&rs, _T("ID"));
      CString sFoundDistrict = GetFieldString(&rs, _T("NAME"));
      CString sType          = GetFieldString(&rs, _T("TYPE"));
      if ( sFoundDistrict.Find(szDistrict)>=0 && FALSE==sType.IsEmpty() && sType.GetAt(0)=='р' ) {
        s = sFoundDistrict;
        lID = id;
        break;
      }
      else if (FALSE==sType.IsEmpty() && sType.GetAt(0)=='м') {
        daCities.Add( (DWORD)id );
      }
      rs.MoveNext();
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
	}
  if ( s.IsEmpty() && daCities.GetSize() ) {
    for( int i(0); i < daCities.GetSize(); i++ ) {
      s = GetDistrictFromDB(sDistrict, (long)daCities.GetAt(i), lID);
      if ( FALSE==s.IsEmpty() )
        break;
    }
  }
  return s;
}

CString GetDistrictFromRagsName(const CString& sRagsName) {
  CString sDistrict, s;
  int offs = 0;
  s = _T(" РУЮ ");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs-2);
    if ( g_RegionID || g_CityID ) {
      if ( g_CityID ) {
        sDistrict = GetDistrictFromDB(s, g_CityID, g_DistrictID);
      }
      if ( sDistrict.IsEmpty() && g_RegionID ) {
        sDistrict = GetDistrictFromDB(s, g_RegionID, g_DistrictID);
      }
      if ( FALSE==sDistrict.IsEmpty() )
        return sDistrict;
    }
  }
  s = _T("Районний ВРАЦС");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs+s.GetLength()+1);
    if ( g_RegionID ) {
      sDistrict = GetDistrictFromDB(s, g_RegionID, g_DistrictID);
      if ( FALSE==sDistrict.IsEmpty() )
        return sDistrict;
    }
  }
  s = _T("ого р");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs );
    if ( g_RegionID ) {
      sDistrict = GetDistrictFromDB(s, g_RegionID, g_DistrictID);
      if ( FALSE==sDistrict.IsEmpty() )
        return sDistrict;
    }
  }

  return sDistrict;
}

int RegRecCmp(const void *a1, const void *a2) {
  CRListRecord *p1 = *(CRListRecord**)a1,
               *p2 = *(CRListRecord**)a2;

  return CyrCompare(p1->m_Fullname, p2->m_Fullname);
}

/////////////////////////////////////////////////////////////////////////////
// CRListRecord
CRListRecord::CRListRecord() {
  m_hTreeItem = NULL;
}
CRListRecord::~CRListRecord() {
}
void CRListRecord::AddChild(CRListRecord* pChildRecord) {
/************************************** : by VK at 01.07.2005 2:36:26 **\
  for( int i(0); i < m_array.GetSize(); i++ ) {
    CRListRecord* pRecord = (CRListRecord*)m_array.GetAt(i);
    if ( CyrCompare(pRecord->m_Fullname, pChildRecord->m_Fullname) > 0 ) {
      m_array.InsertAt(i, pChildRecord);
      return;
    }
  }
\************************************** : by VK at 01.07.2005 2:36:30 **/
  m_array.Add( pChildRecord );
}

/////////////////////////////////////////////////////////////////////////////
// CRList
CRList::CRList() {
}
CRList::~CRList() {
  Clear();
}
void CRList::Clear() {
  POSITION pos = m_map.GetStartPosition();
  while ( pos ) {
    long key;
    CRListRecord* pRecord = NULL;
    m_map.GetNextAssoc(pos, (void*&)key, (void*&)pRecord);
    delete pRecord;
  }
  m_map.RemoveAll();
}

void CRList::Sort(CPtrArray* pArray) {
  qsort( pArray->GetData(), pArray->GetSize(), sizeof(CRListRecord*), RegRecCmp);
}

void CRList::Load(CProgressCtrl* pProgressCtrl/*=NULL*/, CStatic* pStatic/*=NULL*/) {
  if ( FALSE==theDatabase.IsOpen() ) {
    return;
  }
  CDaoRecordset rs(&theDatabase);
  try {
    rs.Open(dbOpenTable, "[RLIST]", dbReadOnly);
    try {
      rs.SetCurrentIndex(_T("PrimaryKey"));
      rs.MoveFirst();
    }
    catch(...) {
    }
    int OldPercent = 0;
    while ( !rs.IsEOF() ) {
      CRListRecord* pRecord = new CRListRecord();
      pRecord->m_ID       = GetFieldLong  (&rs, "ID");
      pRecord->m_ParentID = GetFieldLong  (&rs, "PARENT");
      pRecord->m_Flags    = GetFieldLong  (&rs, "FLAGS");
      pRecord->m_Fullname = GetFieldString(&rs, "FULLNAME");
      pRecord->m_Address  = GetFieldString(&rs, "ADDRESS");
      pRecord->m_Phones   = GetFieldString(&rs, "PHONES");
      pRecord->m_Notice   = GetFieldString(&rs, "NOTICE");

      m_map.SetAt((void*)pRecord->m_ID, pRecord);

      CRListRecord* pParentRecord = NULL;
      if ( m_map.Lookup((void*&)pRecord->m_ParentID, (void*&)pParentRecord) ) {
        pParentRecord->AddChild(pRecord);
      }
      else {
        m_RootItems.Add(pRecord);
      }

      if ( pProgressCtrl && pStatic ) {
        int NewPercent = (int)(rs.GetPercentPosition()*10);
        if ( NewPercent != OldPercent ) {
          pProgressCtrl->SetPos(NewPercent);
          pStatic->SetWindowText(pRecord->m_Fullname);
          OldPercent = NewPercent;
        }
      }
      rs.MoveNext();
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
	}

  if ( m_RootItems.GetSize() > 1 )
    Sort(&m_RootItems);


  POSITION pos = m_map.GetStartPosition();
  while( pos ) {
    long key;
    CRListRecord* pRecord = NULL;
    m_map.GetNextAssoc(pos, (void*&)key, (void*&)pRecord);
    if ( pRecord->m_array.GetSize() > 1 )
      Sort(&pRecord->m_array);
  }

/************************************** : by VK at 01.07.2005 2:48:34 **\
  POSITION pos = m_map.GetStartPosition();
  while ( pos ) {
    long key;
    CRListRecord* pRecord = NULL;
    m_map.GetNextAssoc(pos, (void*&)key, (void*&)pRecord);
    if ( pRecord ) {
      CRListRecord* pParentRecord = NULL;
      if ( m_map.Lookup((void*&)pRecord->m_ParentID, (void*&)pParentRecord) ) {
        pParentRecord->AddChild(pRecord);
      }
      else {
        m_RootItems.Add(pRecord);
      }
    }
  }
\************************************** : by VK at 01.07.2005 2:48:38 **/
}
void CRList::Add(CRListRecord* pRecord) {
  m_map.SetAt((void*)pRecord->m_ID, pRecord);
}
void CRList::Delete(CRListRecord* pRecord) {
  m_map.RemoveKey((void*)pRecord->m_ID);
  delete pRecord;
  
}
CRListRecord* CRList::Lookup(long ID) {
  CRListRecord* pRecord = NULL;
  if ( m_map.Lookup((void*)ID, (void*&)pRecord) )
    return pRecord;
  return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CSetRagsPage dialog
CSetRagsPage::CSetRagsPage(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CSetRagsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetRagsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_hMinJust = m_hOurRags = NULL;
  m_FilledID = -2;
  m_Flags = 0;
}

void CSetRagsPage::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetRagsPage)
	DDX_Control(pDX, IDC_FULLNAME, m_edtFullName);
	DDX_Control(pDX, IDC_SHORTNAME, m_edtShortName);
	DDX_Control(pDX, IDC_MAP, m_Map);
	DDX_Control(pDX, ST_CAPTION, m_CaptionCtrl);
  DDX_Control(pDX, IDC_EMBLEM, m_Emblem);
	DDX_Control(pDX, IDC_RTREE, m_RTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetRagsPage, CNewWizPage)
	//{{AFX_MSG_MAP(CSetRagsPage)
	ON_NOTIFY(TVN_SELCHANGED, IDC_RTREE, OnSelchangedRtree)
	ON_EN_CHANGE(IDC_SHORTNAME, OnChangeShortname)
	ON_BN_CLICKED(IDC_VYCONCOM, OnVyconcom)
	ON_BN_CLICKED(IDC_ORGAN, OnOrgan)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_SETRAGSLIST_ALL, OnSetRagsAll)
  ON_MESSAGE(WM_SETRAGSLIST_CITY, OnSetRagsCity)
  ON_MESSAGE(WM_SETRAGSLIST_REGION, OnSetRagRegion)
END_MESSAGE_MAP()

HTREEITEM CSetRagsPage::FillParent(CRListRecord* pRecord, HTREEITEM hParent, long lFlags/*=0*/) {
  int nImage = 0;
  HTREEITEM hItem = m_RTree.InsertItem(pRecord->m_Fullname, hParent, TVI_LAST);
  m_RTree.SetItemData(hItem, (DWORD)pRecord);
  pRecord->m_hTreeItem = hItem;
  if ( g_RagsID > 0 && pRecord->m_ID==g_RagsID ) {
    m_hOurRags = hItem;
  }
  if ( NULL==hParent ) {
    m_hMinJust = hItem;
  }
  else {
    //nImage = pRecord->m_Notice.IsEmpty() ? RLIMAGE_NOCOMMENT : RLIMAGE_COMMENT;
    nImage = RLIMAGE_NOCOMMENT;
  }
  m_RTree.SetItemImage(hItem, nImage, nImage);
  for( int i(0); i < pRecord->m_array.GetSize(); i++ ) {
    CRListRecord* pChild = (CRListRecord*)pRecord->m_array.GetAt(i);
    if ( lFlags ) {
      if ( pChild->m_Flags & lFlags )
        FillParent(pChild, hItem);
    }
    else
      FillParent(pChild, hItem);
  }
  GetDlgItem(IDC_FULLNAME)->SetWindowText("");
  GetDlgItem(IDC_SHORTNAME)->SetWindowText("");
  return hItem;
}

void CSetRagsPage::Fill(long id/*=-1*/, long lFlags/*=0*/) {
  if ( m_FilledID==id && m_Flags==lFlags)
    return;
  CWaitCursor wc;
  m_RTree.DeleteAllItems();
  if ( -1==id ) {
    for( int i(0); i < theRList.m_RootItems.GetSize(); i++ ) {
      CRListRecord* pRecord = (CRListRecord*)theRList.m_RootItems.GetAt(i);
      if ( pRecord->m_ParentID==id )
        FillParent(pRecord, NULL);
    }
  }
  else {
    CRListRecord* pParentRecord = NULL;
    theRList.m_map.Lookup((void*&)id, (void*&)pParentRecord);
    if ( pParentRecord ) {
      HTREEITEM hItem = FillParent(pParentRecord, NULL, lFlags);
      if ( hItem )
        m_RTree.Expand(hItem, TVE_EXPAND);
    }
  }

  if ( -1==id ) {
    if ( m_hMinJust ) {
      m_RTree.Expand(m_hMinJust, TVE_EXPAND);
      //m_RTree.Select(m_hMinJust, TVGN_CARET);
    }
  }

  m_FilledID = id;
  m_Flags = lFlags;

  if ( g_RagsID > 0 && m_hOurRags ) {
    m_RTree.EnsureVisible(m_hOurRags);
    //m_RTree.SetItemState(m_hOurRags, TVIS_SELECTED, TVIS_SELECTED);
    m_RTree.SelectItem(m_hOurRags);
  }

}
/////////////////////////////////////////////////////////////////////////////
// CSetRagsPage message handlers
BOOL CSetRagsPage::OnInitDialog() 
{
	CNewWizPage::OnInitDialog();

	m_Font.CreateFont(-12, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	m_CaptionCtrl.SetFont(&m_Font, TRUE);
  GetParent()->GetDlgItem(ID_WIZNEXT)->EnableWindow(FALSE);
	
	// TODO: Add extra initialization here
  // m_ImageList.Create(IDIL_RFOLDERS, 16, 0, 0xFFFFFF);
  m_ImageList.CreateTC(IDIL_RFOLDERS_TC, 16, 16, 0xFFFFFF);
  m_RTree.SetImageList(&m_ImageList, TVSIL_NORMAL);

  if ( theRList.IsEmpty() ) {
    //theRList.Load();
    CLoadDlg dlg(NULL);
    dlg.DoModal();
  }

  // m_Emblem.ModifyStyle( SS_ETCHEDFRAME, SS_BITMAP );

  SetFocus();
  Fill();
  m_RTree.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CSetRagsPage::OnSetRagsAll(WPARAM wParam, LPARAM lParam) {
  Fill( -1 );
  return (LRESULT)0;
}
LRESULT CSetRagsPage::OnSetRagsCity(WPARAM wParam, LPARAM lParam) {
  UKRREGION* pRegion = (UKRREGION*)lParam;
  if ( pRegion ) {
    Fill( pRegion->m_RListRegionID, 1 );
    UINT uImageID = pRegion->CityEmblemID;
    m_bmpEmblem.DeleteObject();
    m_bmpEmblem.LoadBitmap( uImageID );
    m_Emblem.SetBitmap( m_bmpEmblem );
  }
  return (LRESULT)0;
}
LRESULT CSetRagsPage::OnSetRagRegion(WPARAM wParam, LPARAM lParam) {
  UKRREGION* pRegion = (UKRREGION*)lParam;
  if ( pRegion ) {
    Fill( pRegion->m_RListRegionID );
    UINT uImageID = pRegion->RegionEmblemID;
    m_bmpEmblem.DeleteObject();
    m_bmpEmblem.LoadBitmap( uImageID );
    m_Emblem.SetBitmap( m_bmpEmblem );
  }
  return (LRESULT)0;
}

void CSetRagsPage::OnSelchangedRtree(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if ( pNMTreeView && pNMTreeView->itemNew.hItem ) {
    CRListRecord* pRecord = (CRListRecord*)m_RTree.GetItemData(pNMTreeView->itemNew.hItem);
    if ( pRecord && pRecord->m_ID != 0) {
      g_RagsID = pRecord->m_ID;
      CCyrString s = DecodeRagsNameWithoutAbbr(pRecord->m_Fullname);
      s.MakeUpperFirstChar();
      g_szFullRagsName = s;
      GetDlgItem(IDC_FULLNAME)->SetWindowText(g_szFullRagsName);
      GetDlgItem(IDC_SHORTNAME)->SetWindowText(pRecord->m_Fullname);
      g_szRagsName = pRecord->m_Fullname;

      HTREEITEM hParent = m_RTree.GetParentItem(pNMTreeView->itemNew.hItem);
      if ( hParent ) {
        g_szParentRags = m_RTree.GetItemText(hParent);
      }
      OnChangeShortname();
      SetRadioButtons();
    }
    else {
      g_szRagsName.Empty();
      GetDlgItem(IDC_SHORTNAME)->SetWindowText(g_szRagsName);
    }
  }
	*pResult = 0;
}

void CSetRagsPage::SetRadioButtons() {
  BOOL fEnable = false;
  UINT uID = 0;
  if ( g_szRagsName.Left(2)==_T("В ") ) {
    fEnable = true;
    uID = IDC_VYCONCOM;
  }
  else if ( g_szRagsName.Left(3)==_T("ВО ") ) {
    fEnable = true;
    uID = IDC_ORGAN;
  }
  GetDlgItem(IDC_VYCONCOM)->EnableWindow(fEnable);
  GetDlgItem(IDC_ORGAN)   ->EnableWindow(fEnable);
  if ( uID ) {
    CheckRadioButton(IDC_VYCONCOM, IDC_ORGAN, uID);
  }
}

void CSetRagsPage::OnChangeShortname()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CNewWizPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
  if ( false==g_szRagsName.IsEmpty() ) {
    GetDlgItem(IDC_SHORTNAME)->GetWindowText(g_szRagsName);
    g_szFullRagsName = DecodeRagsNameWithoutAbbr(g_szRagsName);
    GetDlgItem(IDC_FULLNAME)->SetWindowText(g_szFullRagsName);
  }

  GetParent()->GetDlgItem(ID_WIZNEXT)->EnableWindow( FALSE==g_szRagsName.IsEmpty() );
}

void CSetRagsPage::OnSetActive() {
  SetFocus();
  m_RTree.SetFocus();
}
LRESULT CSetRagsPage::OnWizardNext() {
  CWaitCursor wc;
  g_szRegion   = g_szBirthRegion =
  g_szCity     = g_szBirthCity   =
  g_szDistrict = g_szBirthDistrict = _T("");
  CString sRagsName = g_szRagsName; //CompactRagsName(g_szFullRagsName);
  CString sRegion = GetRegionFromRagsName(sRagsName);
  g_szRegion = g_szBirthRegion = sRegion;

  BOOL fProcess = true;

  if ( g_szRegion==_T("Львівська") ) {
    if ( sRagsName.Find(_T("В Стебницької ")) >= 0 ) {
      fProcess = false;
      g_szCity = _T("Стебник, м. Дрогобич");
      g_szBirthCityType = g_szCityType = _T("м");
    }
    else if ( sRagsName.Find(_T("В Брюховицької сщр ")) >= 0 ) {
      fProcess = false;
      g_szCity = _T("Стебник, м. Дрогобич");
      g_szBirthCityType = g_szCityType = _T("смт");
    }
    else if ( sRagsName.Find(_T("В Рудненської сщр ")) >= 0 ) {
      fProcess = false;
      g_szCity = _T("Редне, м. Львів");
      g_szBirthCityType = g_szCityType = _T("смт");
    }
  }

  if ( fProcess ) {
    CString sCity = GetCityFromRagsName(sRagsName);
    if ( sCity.IsEmpty() ) {
      switch(g_RagsID) {
        case 41301: // В Артемівської мр м. Дзержинська Донецької о
          sCity = _T("Артемівське м.Дзержинськ");
          g_szCityType = _T("смт");
          break;
        case 41302: // В Кіровської сщр м. Дзержинська Донецької о Виконавчий орган
          sCity = _T("Кірове м.Дзержинськ");
          g_szCityType = _T("смт");
          break;
        case 41303: // В Новгородської сщр м. Дзержинська Донецької о
          sCity = _T("Новгородське м.Дзержинськ");
          g_szCityType = _T("смт");
          break;
        case 41304: // В Щербинівської сщр м. Дзержинська Донецької о
          sCity = _T("Щербинівка м.Дзержинськ");
          g_szCityType = _T("смт");
          break;
      }
    }
    if ( FALSE==sCity.IsEmpty() ) {
      g_szCity = g_szBirthCity = sCity;
      g_szBirthCityType = g_szCityType;
    }

 
    if ( FALSE==g_szCity.IsEmpty() ) {
      g_szBirthCity = g_szCity;
      g_szBirthCityType = g_szCityType;
    }
    g_szDistrict = g_szBirthDistrict = GetDistrictFromRagsName(sRagsName);
    if ( g_szCity.IsEmpty() && g_DistrictID ) {
      if ( sRagsName.Left(2)==_T("В ") || sRagsName.Left(2)==_T("в ") ) {
        CString sCity = GetCityFromRagsName(sRagsName, g_DistrictID);
        if ( FALSE==sCity.IsEmpty() ) {
          g_szCity = g_szBirthCity = sCity;
          g_szBirthCityType = g_szCityType;
        }
      }
    }
  }

  if ( g_szRegion==_T("Донецька") ) {
    if ( g_szCity==_T("Миронівський") ) {
      g_szCity=_T("Миронівський, м. Дебальцеве");
    }
    else if ( g_szCity==_T("Світлодарськ") ) {
      g_szCity=_T("Дебальцеве, м. Світлодарськ");
    }

  }
  else if ( g_szRegion==_T("Луганська") ) {
    if ( g_szCity==_T("Молодогвардійськ") ) {
      g_szCity=_T("Молодогвардійськ м. Краснодон");
    }
  }
  else if ( g_szRegion==_T("Львівська") ) {
    if ( sRagsName == _T("В Східницької сщр м.Бореслав Львівської о") ) {
      g_szCity = _T("Східниця, м. Бореслав");
      g_szBirthCityType = g_szCityType = _T("смт");
    }
    else if ( sRagsName == _T("В Брюховицької сщр м. Львова") ) {
      g_szCity = _T("Брюховичі, м. Львів");
      g_szBirthCityType = g_szCityType = _T("смт");
    }
    else if ( sRagsName == _T("В Рудненської сщр м. Львова") ) {
      g_szCity = _T("Рудне, м. Львів");
      g_szBirthCityType = g_szCityType = _T("смт");
    }
  }

  CString s;
  if ( theDatabase.IsOpen() ) {
    CDaoRecordset rs(&theDatabase);
    try {
      CString s;
      rs.Open(dbOpenTable, "[DEFAULTS]");
      s.Format(_T("%lu"), g_RagsID);
      WriteToDefaults(&rs, _T("COMMON"), _T("RID"),      s);
      WriteToDefaults(&rs, _T("COMMON"), _T("RAGS"),     g_szRagsName);
      WriteToDefaults(&rs, _T("COMMON"), _T("PARENT"),   g_szParentRags);
      rs.Close();
    }
    catch (CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
  	}
  }

  return CNewWizPage::OnWizardNext();
}


void CSetRagsPage::OnVyconcom() {
	// TODO: Add your control notification handler code here
  if ( g_szRagsName.Left(3)==_T("ВО ") ) {
    g_szRagsName.Delete(1);
    GetDlgItem(IDC_SHORTNAME)->SetWindowText(g_szRagsName);
    OnChangeShortname();
  }
}

void CSetRagsPage::OnOrgan() {
	// TODO: Add your control notification handler code here
  if ( g_szRagsName.Left(2)==_T("В ") ) {
    g_szRagsName.Insert(1, 'О');
    GetDlgItem(IDC_SHORTNAME)->SetWindowText(g_szRagsName);
    OnChangeShortname();
  }
}
