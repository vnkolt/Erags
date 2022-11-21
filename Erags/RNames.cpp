#include "stdafx.h"

#include "..\Common\CyrString.h"
#include "..\Common\Names.h"
#include "..\Controls\EraControls.h"

#include "Defaults.h"
#include "Geography.h"
#include "RNames.h"

CString sEOL = CString(_T("\r\n"));

LPCTSTR szLongVRAGS = _T("відділ реєстрації актів громадянського стану");
LPCTSTR szLongRAGS  = _T("реєстрації актів громадянського стану");

extern int g_MaxDates;

CString GetCity(LPCTSTR szCity, bool fTypeCity=false);
CString GetShortTypeOfCity(LPCTSTR szCity) {
  CString sCity = Trim(szCity), sRet;
  if (  sCity.Right(3)==_T(" м.") || sCity.Right(2)==_T(" м") || sCity.Right(6)==_T(" місто") )
    sRet = _T("м.");
  else if (  sCity.Right(4)==_T(" слщ") || sCity.Right(5)==_T(" с-ще") || sCity.Right(5)==_T(" смт.") || sCity.Right(4)==_T(" смт") || sCity.Right(7)==_T(" селище") )
    sRet = _T("с-ще");
  else if ( sCity.Right(2)==_T(" с") || sCity.Right(3)==_T(" с.") || sCity.Right(5)==_T(" село") )
    sRet = _T("с.");
  else if ( sCity.Right(2)==_T(" х") || sCity.Right(3)==_T(" х.") || sCity.Right(4)==_T(" х-р") || sCity.Right(6)==_T(" хутір") )
    sRet = _T("х-р");
  else if (  sCity.Right(4)==_T(" ст.") || sCity.Right(7)==_T(" ст-ція") || sCity.Right(5)==_T(" с-ція") || sCity.Right(8)==_T(" станція") )
    sRet = _T("ст-ція");
  else if ( sCity.Right(5)==_T(" с-ця") || sCity.Right(6)==_T(" ст-ця") || sCity.Right(8)==_T(" станиця") )
    sRet = _T("ст-я");
  return sRet;
}

SVidCnv svTable[] = {
 // RC_NV                 RC_RV                     RC_DV                      RC_OV                      RC_MV
 // кто? що?              кого? чого?               кому? чому?                ким? чим?                  де?
 { _T("адміністрація ")   ,_T("адміністрації ")     ,_T("адміністрації ")      ,_T("адміністрацією ")     ,_T("адміністрації ")       },
 { _T("відділ ")          ,_T("відділу ")           ,_T("відділу ")            ,_T("відділом ")           ,_T("відділі ")             },
 { _T("виконком ")        ,_T("виконкому ")         ,_T("виконкому ")          ,_T("виконкомом ")         ,_T("виконкомі ")           },
 { _T("виконавчий орган "),_T("виконавчого органу "),_T("виконавчому органу ") ,_T("виконавчим органом ") ,_T("виконавчому органі ")  },
 { _T("головне ")         ,_T("головного ")         ,_T("головному ")          ,_T("головним ")           ,_T("головному ")           },
 { _T("державний ")       ,_T("державного ")        ,_T("державному ")         ,_T("державним ")          ,_T("державному ")          },
 { _T("рада ")            ,_T("ради ")              ,_T("раді ")               ,_T("радою ")              ,_T("раді ")                },
 { _T("міськрада ")       ,_T("міськради ")         ,_T("міськраді ")          ,_T("міськрадою ")         ,_T("міськраді ")           },
 { _T("райвідділ ")       ,_T("райвідділу ")        ,_T("райвідділу ")         ,_T("райвідділом ")        ,_T("райвідділі ")          },
 { _T("сільрада ")        ,_T("сільради ")          ,_T("сільраді ")           ,_T("сільрадою ")          ,_T("сільраді ")            },
 { _T("палац ")           ,_T("палацу ")            ,_T("палацу ")             ,_T("палацем ")            ,_T("палаці ")              },
 { _T("міська ")          ,_T("міської ")           ,_T("міській ")            ,_T("міською ")            ,_T("міській ")             },
 { _T("міський ")         ,_T("міського ")          ,_T("міському ")           ,_T("міським ")            ,_T("міському ")            },
 { _T("обласна ")         ,_T("обласної ")          ,_T("обласній ")           , _T("обласною ")          ,_T("обласній ")            },
 { _T("обласний ")        ,_T("обласного ")         ,_T("обласному ")          ,_T("обласним ")           ,_T("обласному ")           },
 { _T("районна ")         ,_T("районної ")          ,_T("районній ")           ,_T("районною ")           ,_T("районній ")            },
 { _T("районний ")        ,_T("районного ")         ,_T("районному ")          ,_T("районним ")           ,_T("районному ")           },
 { _T("сектор ")          ,_T("сектору ")           ,_T("сектору ")            ,_T("сектором ")           ,_T("секторі ")             },
 { _T("селищна ")         ,_T("селищної ")          ,_T("селищній ")           ,_T("селищною ")           ,_T("селищній ")            },
 { _T("селищний ")        ,_T("селищного ")         ,_T("селищному ")          ,_T("селищним ")           ,_T("селищному ")           },
 { _T("сільська ")        ,_T("сільської ")         ,_T("сільській ")          ,_T("сільською ")          ,_T("сільській ")           },
 { _T("сільський ")       ,_T("сільського ")        ,_T("сільському ")         ,_T("сільським ")          ,_T("сільському ")          },
 { NULL                   ,NULL                     ,NULL                      ,NULL                      ,NULL                       }
};

LPCTSTR GetFromSVTable(int index, int iVID) {
  switch ( iVID ) {
    case RC_RV:  return svTable[index].szRV;
    case RC_DV:  return svTable[index].szDV;
    case RC_OV:  return svTable[index].szOV;
    case RC_MV:  return svTable[index].szMV;
    default:     return svTable[index].szNV;
  }
}
CString DecodeRagsName(const CString& sRags) {
  CCyrString sDecoded;
  sDecoded.Format(_T(" %s "), sRags );
  int buf_size = sRags.GetLength()+2;
  char* pBuf = new char[buf_size];
#if _MFC_VER < 0x0800
  strcpy(pBuf, sRags);
  char* p = strtok(pBuf, " ");
#else
  strcpy_s(pBuf, buf_size, sRags);
  char *next_token = NULL;
  char* p = strtok_s(pBuf, " ", &next_token);
#endif
  while(p) {
    CString sValue;
    if ( theIniCache.LookupAbbr(p, sValue) ) {
      CString sFind, sReplace;
      sFind.Format(_T(" %s "), p );
      sReplace.Format(_T(" %s "), sValue );
      sDecoded.Replace(sFind, sReplace);
    }
#if _MFC_VER < 0x0800
    p = strtok(NULL, " ");
#else
    p = strtok_s(NULL, " ", &next_token);
#endif
  }
  delete pBuf;
  sDecoded.Trim();
/************************************** : by VK at 30.09.2005 21:15:26 **\
  sDecoded.MakeUpperFirstChar();
\************************************** : by VK at 30.09.2005 21:15:28 **/
  if ( sDecoded.Find(_T("в АР Крим")) > 0 ) {
    sDecoded.Replace(_T("в АР Крим"), _T("в Автономній Республіці Крим"));
  }
  else if ( sDecoded.Find(_T(" АР Крим")) > 0 ) {
    sDecoded.Replace(_T(" АР Крим"), _T(" Автономної Республіки Крим"));
  }
  
  return sDecoded;
}

CString DecodeRagsNameWithoutAbbr(const CString& sUpperRags) {
  CMapStringToString map;
  map.SetAt(_T("ВРАГС"),         _T("ВІДДІЛ РЕЄСТРАЦІЇ АКТІВ ЦИВІЛЬНОГО СТАНУ") );
  map.SetAt(_T("ВРАЦС"),         _T("ВІДДІЛ РЕЄСТРАЦІЇ АКТІВ ЦИВІЛЬНОГО СТАНУ") );
  map.SetAt(_T("ВДРАЦС"),        _T("ВІДДІЛ ДЕРЖАВНОЇ РЕЄСТРАЦІЇ АКТІВ ЦИВІЛЬНОГО СТАНУ") );
  map.SetAt(_T("ГРОМАДЯНСЬКОГО"),_T("ЦИВІЛЬНОГО")                               );
  map.SetAt(_T("В"),             _T("ВИКОНКОМ")                                 );
  map.SetAt(_T("ВО"),            _T("ВИКОНАВЧИЙ ОРГАН")                         );
  map.SetAt(_T("В.РАГС"),        _T("ВІДДІЛ РЕЄСТРАЦІЇ АКТІВ ЦИВІЛЬНОГО СТАНУ") );
  map.SetAt(_T("В.РАЦС"),        _T("ВІДДІЛ РЕЄСТРАЦІЇ АКТІВ ЦИВІЛЬНОГО СТАНУ") );
  map.SetAt(_T("В/РАГС"),        _T("ВІДДІЛ РЕЄСТРАЦІЇ АКТІВ ЦИВІЛЬНОГО СТАНУ") );
  map.SetAt(_T("В/РАЦС"),        _T("ВІДДІЛ РЕЄСТРАЦІЇ АКТІВ ЦИВІЛЬНОГО СТАНУ") );
  map.SetAt(_T("ДРАЦС"),         _T("ДЕРЖАВНОЇ РЕЄСТРАЦІЇ АКТІВ ЦИВІЛЬНОГО СТАНУ") );
  map.SetAt(_T("М-Р"),           _T("МІСЬКОЇ РАДИ")                             );
  map.SetAt(_T("М.Р"),           _T("МІСЬКОЇ РАДИ")                             );
  map.SetAt(_T("М/Р"),           _T("МІСЬКОЇ РАДИ")                             );
  map.SetAt(_T("МР"),            _T("МІСЬКОЇ РАДИ")                             );
  map.SetAt(_T("МУЮ"),           _T("МІСЬКОГО УПРАВЛІННЯ ЮСТИЦІЇ")              );
  map.SetAt(_T("МРУЮ"),          _T("МІСЬКРАЙОННОГО УПРАВЛІННЯ ЮСТИЦІЇ")        );
  map.SetAt(_T("Р"),             _T("РАЙОНУ")                                   );
  map.SetAt(_T("Р-НУ"),          _T("РАЙОНУ")                                   );
  map.SetAt(_T("РАГС"),          _T("РЕЄСТРАЦІЇ АКТІВ ЦИВІЛЬНОГО СТАНУ")        );
  map.SetAt(_T("РАЦС"),          _T("РЕЄСТРАЦІЇ АКТІВ ЦИВІЛЬНОГО СТАНУ")        );
  map.SetAt(_T("РУЮ"),           _T("РАЙОННОГО УПРАВЛІННЯ ЮСТИЦІЇ")             );
  map.SetAt(_T("О"),             _T("ОБЛАСТІ")                                  );
  map.SetAt(_T("ОБЛ"),           _T("ОБЛАСТІ")                                  );
  map.SetAt(_T("ОБЛ."),          _T("ОБЛАСТІ")                                  );
  map.SetAt(_T("ОУЮ"),           _T("ОБЛАСНОГО УПРАВЛІННЯ ЮСТИЦІЇ")             );

  map.SetAt(_T("С.Р"),           _T("СІЛЬСЬКОЇ РАДИ")                           );
  map.SetAt(_T("С/Р"),           _T("СІЛЬСЬКОЇ РАДИ")                           );
  map.SetAt(_T("С-Р"),           _T("СІЛЬСЬКОЇ РАДИ")                           );
  map.SetAt(_T("СР"),            _T("СІЛЬСЬКОЇ РАДИ")                           );
  map.SetAt(_T("СЩР"),           _T("СЕЛИЩНОЇ РАДИ")                            );

  CString sDecoded;
  sDecoded.Format(_T(" %s "), sUpperRags );
  char* pBuf = new char[sUpperRags.GetLength()+4];
  strcpy(pBuf, sUpperRags);

  char* p = strtok(pBuf, " ");
  while(p) {
    CString sValue;
    if ( map.Lookup(p, sValue) ) {
      CString sFind, sReplace;
      sFind.Format(_T(" %s "), p );
      sReplace.Format(_T(" %s "), sValue );
      sDecoded.Replace(sFind, sReplace);
    }
    p = strtok(NULL, " ");
  }
  delete pBuf;
  return Trim(sDecoded);

}


CString EncodeRagsName(const CString& sRags) {
  CString sEncoded;
  sEncoded.Format(_T(" %s "), sRags );
  POSITION pos = theIniCache.GetAbbrStartPosition();
  while ( pos ) {
    CString sKey, sValue;
    theIniCache.GetNextAbbr(pos, sKey, sValue);
    sEncoded.Replace(sValue, sKey);
  }
  return Trim(sEncoded);
}

CString MakeKeysForRagsName(const CString& sRags) {
  CString sKeys;
  sKeys.Format(_T(" %s "),  UpperString(DecodeRagsNameWithoutAbbr(sRags)));
  sKeys.Replace(_T(" ВІДДІЛ "), _T(" "));
  sKeys.Replace(_T(" РЕЄСТРАЦІЇ "), _T(" "));
  sKeys.Replace(_T(" АКТІВ "), _T(" "));
  sKeys.Replace(_T(" ГРОМАДЯНСЬКОГО "), _T(" "));
  sKeys.Replace(_T(" ЦИВІЛЬНОГО "), _T(" "));
  sKeys.Replace(_T(" СТАНУ "), _T(" "));
  sKeys.Replace(_T(" ОБЛАСНОГО "), _T(" "));
  sKeys.Replace(_T(" МІСЬКОГО "), _T(" "));
  sKeys.Replace(_T(" РАЙОННОГО "), _T(" "));
  sKeys.Replace(_T(" УПРАВЛІННЯ "), _T(" "));
  sKeys.Replace(_T(" ЮСТИЦІЇ "), _T(" "));

  sKeys.Replace(_T(" ВИКОНКОМ "), _T(" "));
  sKeys.Replace(_T(" ВИКОНКОМОМ "), _T(" "));
  sKeys.Replace(_T(" ВИКОНАВЧИЙ ОРГАН "), _T(" "));
  sKeys.Replace(_T(" ВИКОНАВЧИМ ОРГАНОМ "), _T(" "));
  sKeys.Replace(_T(" МР "), _T(" "));
  sKeys.Replace(_T(" МІСЬКОЇ "), _T(" "));
  sKeys.Replace(_T(" М-Р "), _T(" "));
  sKeys.Replace(_T(" М\\Р "), _T(" "));
  sKeys.Replace(_T(" М/Р "), _T(" "));
  sKeys.Replace(_T(" М.Р "), _T(" "));
  sKeys.Replace(_T(" М."), _T(" "));
  sKeys.Replace(_T(" О "), _T(" "));
  sKeys.Replace(_T(" ОБЛ "), _T(" "));
  sKeys.Replace(_T(" ОБЛ. "), _T(" "));
  sKeys.Replace(_T(" ОБЛАСТІ "), _T(" "));
  sKeys.Replace(_T(" Р "), _T(" "));
  sKeys.Replace(_T(" Р-НУ "), _T(" "));
  sKeys.Replace(_T(" РАДА "), _T(" "));
  sKeys.Replace(_T(" РАДИ "), _T(" "));
  sKeys.Replace(_T(" РАЙОНУ "), _T(" "));
  sKeys.Replace(_T(" С-Р "), _T(" "));
  sKeys.Replace(_T(" С\\Р "), _T(" "));
  sKeys.Replace(_T(" С/Р "), _T(" "));
  sKeys.Replace(_T(" С.Р "), _T(" "));
  sKeys.Replace(_T(" СЕЛИЩНОЇ "), _T(" "));
  sKeys.Replace(_T(" СІЛЬСЬКОЇ "), _T(" "));
  sKeys.Replace(_T(" СР "), _T(" "));

  sKeys.Replace(_T("ЗЬКОГО "), _T(" "));
  sKeys.Replace(_T("СЬКОГО "), _T(" "));
  sKeys.Replace(_T("ЦЬКОГО "), _T(" "));
  sKeys.Replace(_T("ЗЬКОЇ "), _T(" "));
  sKeys.Replace(_T("СЬКОЇ "), _T(" "));
  sKeys.Replace(_T("ЦЬКОЇ "), _T(" "));

  sKeys.Replace(_T("  "), _T(" "));
  return MakeCanonicalName(Trim(sKeys));
}


CString RagsFromTo(const CString& sRagsFrom, int iFrom, int iTo) {
  CString sRagsTo;
  sRagsTo = Trim(sRagsFrom);

  for( int i(0) ; NULL!=svTable[i].szNV; i++ ) {
    CCyrString sOld = CString(GetFromSVTable(i, iFrom)),
               sNew = CString(GetFromSVTable(i, iTo));
    if ( sRagsFrom.Find(sOld)!= -1 )
      sRagsTo.Replace(sOld, sNew);
    else {
      sOld.MakeUpperFirstChar();
      sNew.MakeUpperFirstChar();
      if ( sRagsFrom.Find(sOld)!= -1 ) sRagsTo.Replace(sOld, sNew);
    }
  }

  if ( (RC_NV==iTo || RC_RV==iTo || RC_DV==iTo || RC_OV==iTo || RC_MV==iTo) &&
       (RC_NV==iFrom || RC_RV==iFrom || RC_DV==iFrom || RC_OV==iFrom) ) {

    static const TCHAR* szFromTo[] = {
     // RC_NV      RC_RV        RC_DV        RC_ZN       RC_OV      RC_MV
     // кто? що?   кого? чого?  кому? чому?  кого? що?   ким? чим?
      _T("ький"), _T("ького"),  _T("ькому"),_T("ький"), _T("ьким"), _T("ькому"), 
      _T("ька"),  _T("ької"),   _T("ькій"), _T("ьку"),  _T("ькою"), _T("ькій"),
      _T("на"),   _T("ної"),    _T("ній"),  _T("ну"),   _T("ною"),  _T("ній") };

    CString sToken = GetTokSpace(sRagsTo, 0);
    for( int i(0); i < 18; i += 6 ) {
      CString sFrom = szFromTo[i+iFrom-1],
              sTo   = szFromTo[i+iTo-1],
              sRepl = sToken;
      int nLenFrom = sFrom.GetLength();
      if ( sToken.Right(nLenFrom)==sFrom )
        sRepl = sToken.Left( sToken.GetLength()-nLenFrom ) + sTo;

      if ( sToken != sRepl )
        sRagsTo.Replace(sToken, sRepl);
    }
  }
  sRagsTo = DecodeRagsName(sRagsTo);
  return sRagsTo;
}

CString MakeCanonicalRagsName(const CString &s) {
  CString sN = DecodeRagsName(s);
  return RagsFromTo(sN, RC_OV, RC_NV);
}

CString SVRagsC(LPCTSTR szSrc, int nVid) {
  CString sVRAGS = MakeCanonicalRagsName(szSrc);
  return RagsFromTo(sVRAGS, RC_NV, nVid);
}

bool PASCAL IsStreet(const CString& s) {
  if ( s.IsEmpty() )
    return false;
  int nTok = 0;
  CString sTok = GetTok(s, nTok, " .");
  while ( !sTok.IsEmpty() ) {
    if (   sTok == _T("бульвар")    // бульвар
        || sTok == _T("бул")        // бульвар
        || sTok == _T("б-р")        // бульвар
        || sTok == _T("вул")        // вулиця
        || sTok == _T("к-л")        // квартал
        || sTok == _T("кв")         // квартал
        || sTok == _T("кв-л")       // квартал
        || sTok == _T("квартал")    // квартал
        || sTok == _T("п-т")        // прошпект
        || sTok == _T("п-к")        // перевулок
        || sTok == _T("пер")        // перевулок
        || sTok == _T("перевул")    // перевулок
        || sTok == _T("перевулок")  // перевулок
        || sTok == _T("пр")         // прошпект, проїзд
        || sTok == _T("пр-д")       // проїзд
        || sTok == _T("проїзд")     // проїзд
        || sTok == _T("пр-т") )     // прошпект
      return false;
    sTok = GetTok(s, ++nTok, " .");
  }
  return true;
}


BOOL PASCAL IsDistrictInCity(LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szDistrict, LPCTSTR szCity) {
  CString sCountry(szCountry), sRegion(szRegion), sCity(szCity), sDistrict(szDistrict);
  CGeoRecord* pCountryRecord  = NULL;
  CGeoRecord* pRegionRecord   = NULL;
  CGeoRecord* pCityRecord     = NULL;
  CGeoRecord* pDistrictRecord = NULL;

  pCountryRecord = theGeoCache.GetCountry(&theGeoCache.m_array, sCountry);

  if ( pCountryRecord ) {
    if ( NULL==pRegionRecord )
      pRegionRecord = theGeoCache.GetRegion( &pCountryRecord->m_array, sRegion );
    if ( pRegionRecord ) {
      if ( NULL==pCityRecord )
        pCityRecord = theGeoCache.GetCity( &pRegionRecord->m_array, sCity );
      if ( pCityRecord ) {
        if ( NULL==pDistrictRecord )
          pDistrictRecord = theGeoCache.GetDistrict( &pCityRecord->m_array, sDistrict );
      }
      else { // city not found
        if ( NULL==pDistrictRecord )
          pDistrictRecord = theGeoCache.GetDistrict( &pRegionRecord->m_array, sDistrict );
        if ( pDistrictRecord ) { // district in region
          if ( NULL==pCityRecord )
            pCityRecord = theGeoCache.GetCity( &pDistrictRecord->m_array, sCity );
        }
      }
    }
    if ( pCountryRecord && NULL==pCityRecord ) {
      pCityRecord = theGeoCache.GetCity( &pCountryRecord->m_array, sCity );
      if ( pCityRecord && NULL==pDistrictRecord) { // City in the country, region not need
        pDistrictRecord = theGeoCache.GetDistrict( &pCityRecord->m_array, sDistrict );
      }
    }
  }

  if ( pCityRecord && theGeoCache.GetDistrict(&pCityRecord->m_array, sDistrict) )
    return TRUE;
  return FALSE;
}
CString PASCAL GetPlace(LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szDistrict, LPCTSTR szCity, BOOL fShort/*=true*/) {
  CString sCountry(szCountry), sRegion(szRegion), sCity(szCity), sDistrict(szDistrict);

  CGeoRecord* pCountryRecord  = NULL;
  CGeoRecord* pRegionRecord   = NULL;
  CGeoRecord* pCityRecord     = NULL;
  CGeoRecord* pDistrictRecord = NULL;

  pCountryRecord = theGeoCache.GetCountry(&theGeoCache.m_array, sCountry);

  if ( pCountryRecord ) {
    if ( NULL==pRegionRecord )
      pRegionRecord = theGeoCache.GetRegion( &pCountryRecord->m_array, sRegion );
    if ( pRegionRecord ) {
      if ( NULL==pCityRecord )
        pCityRecord = theGeoCache.GetCity( &pRegionRecord->m_array, sCity );
      if ( pCityRecord ) {
        if ( NULL==pDistrictRecord )
          pDistrictRecord = theGeoCache.GetDistrict( &pCityRecord->m_array, sDistrict );
      }
      else { // city not found
        if ( NULL==pDistrictRecord )
          pDistrictRecord = theGeoCache.GetDistrict( &pRegionRecord->m_array, sDistrict );
        if ( pDistrictRecord ) { // district in region
          if ( NULL==pCityRecord )
            pCityRecord = theGeoCache.GetCity( &pDistrictRecord->m_array, sCity );
        }
      }
    }
    if ( pCountryRecord && NULL==pCityRecord ) {
      pCityRecord = theGeoCache.GetCity( &pCountryRecord->m_array, sCity );
      if ( pCityRecord && NULL==pDistrictRecord) { // City in the country, region not need
        pDistrictRecord = theGeoCache.GetDistrict( &pCityRecord->m_array, sDistrict );
      }
    }
  }

  if ( pCountryRecord && !pCountryRecord->m_AltName.IsEmpty() )
    sCountry = pCountryRecord->m_AltName;

  bool fDistrictInCity = false;
  if ( pCityRecord && theGeoCache.GetDistrict(&pCityRecord->m_array, sDistrict) )
    fDistrictInCity = true;

  sCountry  = Trim(sCountry);
  sRegion   = Trim(sRegion);
  sCity     = Trim(sCity);
  sDistrict = Trim(sDistrict);

  sRegion += TCHAR(' ');
  if ( sRegion.Right(4) == _T("ька ") ) {
    sRegion += fShort ? _T("обл.") : _T("область");
  }
  else if ( sRegion.Right(4) == _T("ький ") ) {
    sRegion += _T("край");
  }

  sDistrict += TCHAR(' ');
  if ( sDistrict.Right(4) == _T("кий ") ) {
    if ( pDistrictRecord )
      sDistrict.Format(_T("%s %s"), pDistrictRecord->m_Name, fShort ? pDistrictRecord->GetShortTypeName() : _T("район"));
    else
      sDistrict += fShort ? _T("р-н") : _T("район");
  }

  if ( !sCity.IsEmpty() ) {
    if ( pCityRecord )
      sCity.Format(_T("%s %s"), pCityRecord->GetShortTypeName(), pCityRecord->m_Name);
    else {
      sCity.Format(_T("%s %s"), GetShortTypeOfCity(sCity), GetCity(sCity));
      sCity.TrimRight();
      sCity.TrimRight('.');
    }
  }

  CString s;
  if ( fDistrictInCity ) {
    s.Format(_T("%s, %s, %s, %s"), sCountry, sRegion, sCity, sDistrict);
  }
  else
    s.Format(_T("%s, %s, %s, %s"), sCountry, sRegion, sDistrict, sCity);

  s = FindAndReplace(s, _T(" ,"), _T(""), true);
  s = Trim(s); s.TrimRight(','); s.TrimLeft(',');
  s.TrimRight('/');  s.TrimRight(','); s.TrimLeft(',');
  return Trim(s);
}
CString PASCAL GetAddress(LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szCity, LPCTSTR szDistrict, LPCTSTR szStreet, LPCTSTR szHouse, LPCTSTR szFlat, BOOL fFullAddress/*=FALSE*/) {
  CString sCountry(szCountry), sRegion(szRegion), sCity(szCity), sDistrict(szDistrict),
          sStreet(szStreet), sHouse(szHouse), sFlat(szFlat);

  CGeoRecord* pCountryRecord  = NULL;
  CGeoRecord* pRegionRecord   = NULL;
  CGeoRecord* pCityRecord     = NULL;
  CGeoRecord* pDistrictRecord = NULL;

  pCountryRecord = theGeoCache.GetCountry(&theGeoCache.m_array, sCountry);

  if ( pCountryRecord ) {
    if ( NULL==pRegionRecord )
      pRegionRecord = theGeoCache.GetRegion( &pCountryRecord->m_array, sRegion );
    if ( pRegionRecord ) {
      if ( NULL==pCityRecord )
        pCityRecord = theGeoCache.GetCity( &pRegionRecord->m_array, sCity );
      if ( pCityRecord ) {
        if ( NULL==pDistrictRecord )
          pDistrictRecord = theGeoCache.GetDistrict( &pCityRecord->m_array, sDistrict );
      }
      else { // city not found
        if ( NULL==pDistrictRecord )
          pDistrictRecord = theGeoCache.GetDistrict( &pRegionRecord->m_array, sDistrict );
        if ( pDistrictRecord ) { // district in region
          if ( NULL==pCityRecord )
            pCityRecord = theGeoCache.GetCity( &pDistrictRecord->m_array, sCity );
        }
      }
    }
    if ( pCountryRecord && NULL==pCityRecord ) {
      pCityRecord = theGeoCache.GetCity( &pCountryRecord->m_array, sCity );
      if ( pCityRecord && NULL==pDistrictRecord) { // City in the country, region not need
        pDistrictRecord = theGeoCache.GetDistrict( &pCityRecord->m_array, sDistrict );
      }
    }
  }

  if ( pCountryRecord && !pCountryRecord->m_AltName.IsEmpty() )
    sCountry = pCountryRecord->m_AltName;

  bool fDistrictInCity = false;
  if ( pCityRecord && theGeoCache.GetDistrict(&pCityRecord->m_array, sDistrict) )
    fDistrictInCity = true;

  sCountry  = Trim(sCountry);
  sRegion   = Trim(sRegion);
  sCity     = Trim(sCity);
  sDistrict = Trim(sDistrict);
  sStreet   = Trim(sStreet);
  sHouse    = Trim(sHouse);
  sFlat     = Trim(sFlat);

  sRegion += TCHAR(' ');
  if ( sRegion.Right(4) == _T("ька ") ) {
    if ( pRegionRecord )
      sRegion.Format(_T("%s %s"), pRegionRecord->m_Name, pRegionRecord->GetShortTypeName());
    else
      sRegion += _T("обл.");
  }
  else if ( sRegion.Right(4) == _T("ький ") ) {
    if ( pRegionRecord )
      sRegion += Trim(pRegionRecord->m_Type);
    else
      sRegion += _T("край");
  }

  sDistrict += TCHAR(' ');
  if ( sDistrict.Right(4) == _T("кий ") ) {
    if ( pDistrictRecord )
      sDistrict.Format(_T("%s %s"), pDistrictRecord->m_Name, pDistrictRecord->GetShortTypeName());
    else
      sDistrict += _T("р-н");
  }

  if ( !sCity.IsEmpty() ) {
    if ( pCityRecord )
      sCity.Format(_T("%s %s"), pCityRecord->GetShortTypeName(), pCityRecord->m_Name);
    else {
      sCity.Format(_T("%s %s"), GetShortTypeOfCity(sCity), GetCity(sCity));
      sCity.TrimRight();
      sCity.TrimRight('.');
    }
  }

  if ( IsStreet(sStreet) )
    sStreet =  _T("вул. ") + sStreet;

/************************************** : by VK at 11.01.2004 2:38:27 **\
  CString s;
  if ( fDistrictInCity )
    s.Format(_T("%s, %s, %s, %s, %s, %s/%s"),
             sCountry, sRegion, sCity, sDistrict, sStreet, sHouse, sFlat);
  else
    s.Format(_T("%s, %s, %s, %s, %s, %s/%s"),
             sCountry, sRegion, sDistrict, sCity, sStreet, sHouse, sFlat);
\************************************** : by VK at 11.01.2004 2:38:36 **/

  CString s, sHouseFlat;
  if ( !IsEmptyText(sHouse) ) {
   if ( IsEmptyText(sFlat) || sFlat.GetAt(0)=='-' ) {
     sHouseFlat.Format(_T("буд. %s"), sHouse);
   }
   else {
     sHouseFlat.Format(_T("буд. %s, кв. %s"), sHouse, sFlat);
   }
  }

  if ( fDistrictInCity ) {
    if ( fFullAddress )
      s.Format(_T("%s, %s, %s, %s"), sCity, sDistrict, sStreet, sHouseFlat);
    else
      s.Format(_T("%s, %s, %s"), sCity, sStreet, sHouseFlat);
  }
  else
    s.Format(_T("%s, %s, %s, %s"), sDistrict, sCity, sStreet, sHouseFlat);

  if ( fFullAddress && !sCountry.IsEmpty() ) {
    CString sNewAddress;
    if ( pCityRecord && pCityRecord->IsMainCity() ) {
      sNewAddress.Format(_T("%s, %s"), sCountry, s);
    }
    else
      sNewAddress.Format(_T("%s, %s, %s"), sCountry, sRegion, s);
    s = sNewAddress;
  }

  s = FindAndReplace(s, _T(" ,"), _T(""), true);
  s = Trim(s); s.TrimRight(','); s.TrimLeft(',');
  s.TrimRight('/');  s.TrimRight(','); s.TrimLeft(',');
  return Trim(s);
}

TCHAR PASCAL GetRagsType(LPCTSTR szRagsName) {
  CCyrString sz(szRagsName);
  sz.Trim();
  sz.MakeUpper();
  if ( sz.Left(2)==_T("В ") || sz.Left(8)==_T("ВИКОНКОМ") || sz.Find(_T("ВИКОНКОМ")) >-1 || sz.Find(_T("ВИКОНАВЧИЙ")) >-1 ) {
    return TCHAR('В');
  }
  return TCHAR('Р');
}

CString GetCityFromAddress(const CString& szAddress, int nFound) {
  CString s;
  int nLength = szAddress.GetLength();
  while ( nFound < nLength ) {
    TCHAR c = szAddress[nFound++];
    if ( c==',' ) {
      break;
    }
    s += c;
  }
  s = Trim(s);
  return s;
}
CString GetDistrictFromAddress(const CString& szAddress, int nFound) {
  CString s;
  while ( nFound > 0 ) {
    TCHAR c = szAddress[nFound--];
    if ( c==',' ) {
      break;
    }
    s += c;
  }
  s.MakeReverse();
  s = Trim(s);
  return s;
}

CString PASCAL MakeAddress(CEraNameComboBox* pCountry, CEraNameComboBox* pRegion, CEraNameComboBox* pCity, CEraNameComboBox* pDistrict, CEraNameComboBox* pStreet, CEraEdit* pHouse, CEraEdit* pFlat) {
  CString sCountry, sRegion, sCity, sDistrict, sStreet, sHouse, sFlat;
  sCountry  = pCountry->GetCurText();
  sRegion   = pRegion->GetCurText();
  sCity     = pCity->GetCurText();
  sDistrict = pDistrict->GetCurText();
  sStreet   = pStreet->GetCurText();
  pHouse->GetWindowText(sHouse);
  pFlat->GetWindowText(sFlat);

  BOOL fDontEditCity = false;

/*
  Test:

  Україна            +++
  Донецька
  Ворощиловський
  Донецьк м.

  Україна            +++
  Донецька
  Совєтський
  Нижня Кринка м. Макіївки смт
  Україна, Донецька обл., Макіївка, Совєтський р-н, м. смт Нижня Кринка, квартал 'Б', буд. 02, кв. 63
  
  Україна
  Донецька
  
  Дебальцеве м. Світлодарськ

*/


  if ( sRegion.IsEmpty() && sCity.IsEmpty() && sDistrict.IsEmpty() && sStreet.IsEmpty() && sHouse.IsEmpty() && sFlat.IsEmpty() )
    return _T("");

  CGeoRecord* pCountryRecord  = (CGeoRecord*)pCountry->GetCurData();
  CGeoRecord* pRegionRecord   = (CGeoRecord*)pRegion->GetCurData();
  CGeoRecord* pCityRecord     = (CGeoRecord*)pCity->GetCurData();
  CGeoRecord* pDistrictRecord = (CGeoRecord*)pDistrict->GetCurData();

  if ( NULL==pCountryRecord )
    pCountryRecord = theGeoCache.GetCountry(&theGeoCache.m_array, sCountry);

  if ( pCountryRecord ) {
    if ( NULL==pRegionRecord )
      pRegionRecord = theGeoCache.GetRegion( &pCountryRecord->m_array, sRegion );
    if ( pRegionRecord ) {
      if ( NULL==pCityRecord )
        pCityRecord = theGeoCache.GetCity( &pRegionRecord->m_array, sCity );
      if ( pCityRecord ) {
        if ( NULL==pDistrictRecord )
          pDistrictRecord = theGeoCache.GetDistrict( &pCityRecord->m_array, sDistrict );
      }
      else { // city not found
        if ( NULL==pDistrictRecord )
          pDistrictRecord = theGeoCache.GetDistrict( &pRegionRecord->m_array, sDistrict );
        if ( pDistrictRecord ) { // district in region
          if ( NULL==pCityRecord )
            pCityRecord = theGeoCache.GetCity( &pDistrictRecord->m_array, sCity );
        }
      }
    }
    if ( pCountryRecord && NULL==pCityRecord ) {
      pCityRecord = theGeoCache.GetCity( &pCountryRecord->m_array, sCity );
      if ( pCityRecord && NULL==pDistrictRecord) { // City in the country, region not need
        pDistrictRecord = theGeoCache.GetDistrict( &pCityRecord->m_array, sDistrict );
      }
    }
  }

  if ( pCountryRecord && !pCountryRecord->m_AltName.IsEmpty() )
    sCountry = pCountryRecord->m_AltName;

  bool fDistrictInCity = false;
  if ( pCityRecord && theGeoCache.GetDistrict(&pCityRecord->m_array, sDistrict) )
    fDistrictInCity = true;

  sCountry  = Trim(sCountry);
  sRegion   = Trim(sRegion);
  sCity     = Trim(sCity);
  sDistrict = Trim(sDistrict);
  sStreet   = Trim(sStreet);
  sHouse    = Trim(sHouse);
  sFlat     = Trim(sFlat);

  sRegion += TCHAR(' ');
  if ( sRegion.Right(4) == _T("ька ") ) {
    if ( pRegionRecord )
      sRegion += pRegionRecord->GetShortTypeName();
    else
      sRegion += _T("обл.");
  }
  else if ( sRegion.Right(4) == _T("ький ") ) {
    if ( pRegionRecord )
      sRegion += pRegionRecord->GetShortTypeName();
    else
      sRegion += _T("край");
  }

  sDistrict += TCHAR(' ');
  if ( sDistrict.Right(4) == _T("кий ") ) {
    if ( pDistrictRecord )
      sDistrict += pDistrictRecord->GetShortTypeName();
    else
      sDistrict += _T("р-н");
  }

  if ( !sCity.IsEmpty() && pCityRecord ) {
    if ( false==pCityRecord->m_AltName.IsEmpty() && sCity.Find(pCityRecord->m_AltName)>=0 ) {
      sCity.Format(_T("%s %s"), pCityRecord->GetShortTypeName(), pCityRecord->m_AltName);
      // смт Нижня Кринка, м. Макіївка
      int nFound = sCity.Find(_T("м."));
      if ( nFound > 0 ) {
        CString s1 = sCity.Mid(nFound),
                s2 = sCity.Left(nFound-1);
        sCity.Format(_T("%s, %s"), Trim(s1), Trim(s2));
        fDontEditCity = true;
      }
    }
    else {
      sCity.Format(_T("%s %s"), pCityRecord->GetShortTypeName(), pCityRecord->m_Name);
      fDontEditCity = true;
    }
  }

  if ( IsStreet(sStreet) )
    sStreet =  _T("вул. ") + sStreet;

  CString s, sHouseFlat;
  if ( !IsEmptyText(sHouse) ) {
    if ( (IsEmptyText(sFlat) || sFlat.GetAt(0)=='-')  ) {
      sHouseFlat.Format(_T("буд. %s"), sHouse);
    }
    else {
      sHouseFlat.Format(_T("буд. %s, кв. %s"), sHouse, sFlat);
    }
  }

  CString sReg;
  if ( FALSE==sRegion.IsEmpty() && pCityRecord && false==pCityRecord->IsMainCity() ) {
    sReg.Format(_T("%s, "), sRegion);
  }


  if ( false==fDontEditCity && false==IsEmptyText(sCity) ) {
    int nFound1(0), nFound2(0);
    nFound1 = sCity.Find(_T("м."));
    if ( nFound1 >=0 ) {
      nFound2 = sCity.Find(_T("м."), nFound1+1);
    }
    if ( nFound2 <= nFound1 ) {
      sCity.Format(_T("%s %s"),  GetCity(sCity, true), GetCity(sCity, false) );
    }
  }

  sReg = Trim(sReg);
  sCity = Trim(sCity);
  sStreet = Trim(sStreet);
  if ( fDistrictInCity ) {
    s.Format(_T("%s, %s %s, %s, %s, %s"), sCountry, sReg, sCity, sDistrict, sStreet, sHouseFlat);
  }
  else {
    s.Format(_T("%s, %s %s, %s, %s, %s"), sCountry, sReg, sDistrict, sCity, sStreet, sHouseFlat);
  }

  int nDistrict, nCity;
  LPCTSTR szCityWord, szDistrictWord;
  szCityWord = _T(" м.");
  
  szDistrictWord = _T(" р-н");
  nDistrict = s.Find(szDistrictWord);
  if ( -1 == nDistrict ) {
    szDistrictWord = szDistrictWord;
    nDistrict = s.Find(_T(" район"));
  }

  nCity = s.Find(szCityWord);
  if ( -1 == nCity ) {
    szCityWord = _T(" місто");
    nCity = s.Find(szCityWord);
  }

  if ( nDistrict > 0 && nCity > nDistrict ) {
    CString szCity, szDistrict;
    szCity = GetCityFromAddress(s, nCity+lstrlen(szCityWord));
    szDistrict = GetDistrictFromAddress(s, nDistrict);
    szDistrict.Replace(szDistrictWord, _T(""));
    if ( pRegionRecord ) {
      CGeoRecord* pCityRecord = theGeoCache.GetCity(&pRegionRecord->m_array, szCity);
      if ( pCityRecord ) { 
        pDistrictRecord = theGeoCache.GetDistrict(&pCityRecord->m_array, szDistrict);
        if ( pDistrictRecord ) { // Это район в городе?
          szCity.Format(_T("%s %s"), Trim(szCityWord), Trim(szCity));
          szDistrict.Format(_T("%s %s"), Trim(szDistrict), Trim(szDistrictWord));
          if ( s.Find(szCity) > 0 && s.Find(szDistrict) > 0 ) {
            s.Replace(szCity, _T("CITY"));
            s.Replace(szDistrict, _T("DISTRICT"));
            s.Replace(_T("CITY"), szDistrict);
            s.Replace(_T("DISTRICT"), szCity);
          }
        }
      }
    }
  }


  for( int i(0); i < 2; i++ ) {
    s.Replace("  ", " ");
    s.Replace(", ,", ",");
    s.Replace(",,", ",");
    s = Trim(s); s.TrimRight(','); s.TrimLeft(',');
    s.TrimRight('/');
    s.TrimRight(','); s.TrimLeft(',');
  }
  return Trim(s);
}

