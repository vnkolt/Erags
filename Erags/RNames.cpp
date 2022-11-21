#include "stdafx.h"

#include "..\Common\CyrString.h"
#include "..\Common\Names.h"
#include "..\Controls\EraControls.h"

#include "Defaults.h"
#include "Geography.h"
#include "RNames.h"

CString sEOL = CString(_T("\r\n"));

LPCTSTR szLongVRAGS = _T("���� ��������� ���� �������������� �����");
LPCTSTR szLongRAGS  = _T("��������� ���� �������������� �����");

extern int g_MaxDates;

CString GetCity(LPCTSTR szCity, bool fTypeCity=false);
CString GetShortTypeOfCity(LPCTSTR szCity) {
  CString sCity = Trim(szCity), sRet;
  if (  sCity.Right(3)==_T(" �.") || sCity.Right(2)==_T(" �") || sCity.Right(6)==_T(" ����") )
    sRet = _T("�.");
  else if (  sCity.Right(4)==_T(" ���") || sCity.Right(5)==_T(" �-��") || sCity.Right(5)==_T(" ���.") || sCity.Right(4)==_T(" ���") || sCity.Right(7)==_T(" ������") )
    sRet = _T("�-��");
  else if ( sCity.Right(2)==_T(" �") || sCity.Right(3)==_T(" �.") || sCity.Right(5)==_T(" ����") )
    sRet = _T("�.");
  else if ( sCity.Right(2)==_T(" �") || sCity.Right(3)==_T(" �.") || sCity.Right(4)==_T(" �-�") || sCity.Right(6)==_T(" ����") )
    sRet = _T("�-�");
  else if (  sCity.Right(4)==_T(" ��.") || sCity.Right(7)==_T(" ��-���") || sCity.Right(5)==_T(" �-���") || sCity.Right(8)==_T(" �������") )
    sRet = _T("��-���");
  else if ( sCity.Right(5)==_T(" �-��") || sCity.Right(6)==_T(" ��-��") || sCity.Right(8)==_T(" �������") )
    sRet = _T("��-�");
  return sRet;
}

SVidCnv svTable[] = {
 // RC_NV                 RC_RV                     RC_DV                      RC_OV                      RC_MV
 // ���? ��?              ����? ����?               ����? ����?                ���? ���?                  ��?
 { _T("����������� ")   ,_T("����������� ")     ,_T("����������� ")      ,_T("������������ ")     ,_T("����������� ")       },
 { _T("���� ")          ,_T("����� ")           ,_T("����� ")            ,_T("������ ")           ,_T("���� ")             },
 { _T("�������� ")        ,_T("��������� ")         ,_T("��������� ")          ,_T("���������� ")         ,_T("�������� ")           },
 { _T("���������� ����� "),_T("����������� ������ "),_T("����������� ������ ") ,_T("���������� ������� ") ,_T("����������� ����� ")  },
 { _T("������� ")         ,_T("��������� ")         ,_T("��������� ")          ,_T("�������� ")           ,_T("��������� ")           },
 { _T("��������� ")       ,_T("���������� ")        ,_T("���������� ")         ,_T("��������� ")          ,_T("���������� ")          },
 { _T("���� ")            ,_T("���� ")              ,_T("��� ")               ,_T("����� ")              ,_T("��� ")                },
 { _T("�������� ")       ,_T("�������� ")         ,_T("������� ")          ,_T("��������� ")         ,_T("������� ")           },
 { _T("������� ")       ,_T("�������� ")        ,_T("�������� ")         ,_T("��������� ")        ,_T("������� ")          },
 { _T("������� ")        ,_T("������� ")          ,_T("������ ")           ,_T("�������� ")          ,_T("������ ")            },
 { _T("����� ")           ,_T("������ ")            ,_T("������ ")             ,_T("������� ")            ,_T("������ ")              },
 { _T("����� ")          ,_T("����� ")           ,_T("����� ")            ,_T("������ ")            ,_T("����� ")             },
 { _T("������ ")         ,_T("������� ")          ,_T("������� ")           ,_T("������ ")            ,_T("������� ")            },
 { _T("������� ")         ,_T("������� ")          ,_T("������� ")           , _T("�������� ")          ,_T("������� ")            },
 { _T("�������� ")        ,_T("��������� ")         ,_T("��������� ")          ,_T("�������� ")           ,_T("��������� ")           },
 { _T("������� ")         ,_T("������� ")          ,_T("������� ")           ,_T("�������� ")           ,_T("������� ")            },
 { _T("�������� ")        ,_T("��������� ")         ,_T("��������� ")          ,_T("�������� ")           ,_T("��������� ")           },
 { _T("������ ")          ,_T("������� ")           ,_T("������� ")            ,_T("�������� ")           ,_T("������ ")             },
 { _T("������� ")         ,_T("������� ")          ,_T("������� ")           ,_T("�������� ")           ,_T("������� ")            },
 { _T("�������� ")        ,_T("��������� ")         ,_T("��������� ")          ,_T("�������� ")           ,_T("��������� ")           },
 { _T("������� ")        ,_T("������� ")         ,_T("������� ")          ,_T("�������� ")          ,_T("������� ")           },
 { _T("�������� ")       ,_T("��������� ")        ,_T("��������� ")         ,_T("�������� ")          ,_T("��������� ")          },
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
  if ( sDecoded.Find(_T("� �� ����")) > 0 ) {
    sDecoded.Replace(_T("� �� ����"), _T("� ��������� ��������� ����"));
  }
  else if ( sDecoded.Find(_T(" �� ����")) > 0 ) {
    sDecoded.Replace(_T(" �� ����"), _T(" ��������� ��������� ����"));
  }
  
  return sDecoded;
}

CString DecodeRagsNameWithoutAbbr(const CString& sUpperRags) {
  CMapStringToString map;
  map.SetAt(_T("�����"),         _T("²�Ĳ� �Ū����ֲ� ��Ҳ� ��²������ �����") );
  map.SetAt(_T("�����"),         _T("²�Ĳ� �Ū����ֲ� ��Ҳ� ��²������ �����") );
  map.SetAt(_T("������"),        _T("²�Ĳ� �������ί �Ū����ֲ� ��Ҳ� ��²������ �����") );
  map.SetAt(_T("��������������"),_T("��²������")                               );
  map.SetAt(_T("�"),             _T("��������")                                 );
  map.SetAt(_T("��"),            _T("���������� �����")                         );
  map.SetAt(_T("�.����"),        _T("²�Ĳ� �Ū����ֲ� ��Ҳ� ��²������ �����") );
  map.SetAt(_T("�.����"),        _T("²�Ĳ� �Ū����ֲ� ��Ҳ� ��²������ �����") );
  map.SetAt(_T("�/����"),        _T("²�Ĳ� �Ū����ֲ� ��Ҳ� ��²������ �����") );
  map.SetAt(_T("�/����"),        _T("²�Ĳ� �Ū����ֲ� ��Ҳ� ��²������ �����") );
  map.SetAt(_T("�����"),         _T("�������ί �Ū����ֲ� ��Ҳ� ��²������ �����") );
  map.SetAt(_T("�-�"),           _T("̲���ί ����")                             );
  map.SetAt(_T("�.�"),           _T("̲���ί ����")                             );
  map.SetAt(_T("�/�"),           _T("̲���ί ����")                             );
  map.SetAt(_T("��"),            _T("̲���ί ����")                             );
  map.SetAt(_T("���"),           _T("̲������ �����˲��� ����ֲ�")              );
  map.SetAt(_T("����"),          _T("̲������������ �����˲��� ����ֲ�")        );
  map.SetAt(_T("�"),             _T("������")                                   );
  map.SetAt(_T("�-��"),          _T("������")                                   );
  map.SetAt(_T("����"),          _T("�Ū����ֲ� ��Ҳ� ��²������ �����")        );
  map.SetAt(_T("����"),          _T("�Ū����ֲ� ��Ҳ� ��²������ �����")        );
  map.SetAt(_T("���"),           _T("��������� �����˲��� ����ֲ�")             );
  map.SetAt(_T("�"),             _T("�����Ҳ")                                  );
  map.SetAt(_T("���"),           _T("�����Ҳ")                                  );
  map.SetAt(_T("���."),          _T("�����Ҳ")                                  );
  map.SetAt(_T("���"),           _T("��������� �����˲��� ����ֲ�")             );

  map.SetAt(_T("�.�"),           _T("Ѳ�����ί ����")                           );
  map.SetAt(_T("�/�"),           _T("Ѳ�����ί ����")                           );
  map.SetAt(_T("�-�"),           _T("Ѳ�����ί ����")                           );
  map.SetAt(_T("��"),            _T("Ѳ�����ί ����")                           );
  map.SetAt(_T("���"),           _T("������ί ����")                            );

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
  sKeys.Replace(_T(" ²�Ĳ� "), _T(" "));
  sKeys.Replace(_T(" �Ū����ֲ� "), _T(" "));
  sKeys.Replace(_T(" ��Ҳ� "), _T(" "));
  sKeys.Replace(_T(" �������������� "), _T(" "));
  sKeys.Replace(_T(" ��²������ "), _T(" "));
  sKeys.Replace(_T(" ����� "), _T(" "));
  sKeys.Replace(_T(" ��������� "), _T(" "));
  sKeys.Replace(_T(" ̲������ "), _T(" "));
  sKeys.Replace(_T(" ��������� "), _T(" "));
  sKeys.Replace(_T(" �����˲��� "), _T(" "));
  sKeys.Replace(_T(" ����ֲ� "), _T(" "));

  sKeys.Replace(_T(" �������� "), _T(" "));
  sKeys.Replace(_T(" ���������� "), _T(" "));
  sKeys.Replace(_T(" ���������� ����� "), _T(" "));
  sKeys.Replace(_T(" ���������� ������� "), _T(" "));
  sKeys.Replace(_T(" �� "), _T(" "));
  sKeys.Replace(_T(" ̲���ί "), _T(" "));
  sKeys.Replace(_T(" �-� "), _T(" "));
  sKeys.Replace(_T(" �\\� "), _T(" "));
  sKeys.Replace(_T(" �/� "), _T(" "));
  sKeys.Replace(_T(" �.� "), _T(" "));
  sKeys.Replace(_T(" �."), _T(" "));
  sKeys.Replace(_T(" � "), _T(" "));
  sKeys.Replace(_T(" ��� "), _T(" "));
  sKeys.Replace(_T(" ���. "), _T(" "));
  sKeys.Replace(_T(" �����Ҳ "), _T(" "));
  sKeys.Replace(_T(" � "), _T(" "));
  sKeys.Replace(_T(" �-�� "), _T(" "));
  sKeys.Replace(_T(" ���� "), _T(" "));
  sKeys.Replace(_T(" ���� "), _T(" "));
  sKeys.Replace(_T(" ������ "), _T(" "));
  sKeys.Replace(_T(" �-� "), _T(" "));
  sKeys.Replace(_T(" �\\� "), _T(" "));
  sKeys.Replace(_T(" �/� "), _T(" "));
  sKeys.Replace(_T(" �.� "), _T(" "));
  sKeys.Replace(_T(" ������ί "), _T(" "));
  sKeys.Replace(_T(" Ѳ�����ί "), _T(" "));
  sKeys.Replace(_T(" �� "), _T(" "));

  sKeys.Replace(_T("������ "), _T(" "));
  sKeys.Replace(_T("������ "), _T(" "));
  sKeys.Replace(_T("������ "), _T(" "));
  sKeys.Replace(_T("���ί "), _T(" "));
  sKeys.Replace(_T("���ί "), _T(" "));
  sKeys.Replace(_T("���ί "), _T(" "));

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
     // ���? ��?   ����? ����?  ����? ����?  ����? ��?   ���? ���?
      _T("����"), _T("�����"),  _T("�����"),_T("����"), _T("����"), _T("�����"), 
      _T("���"),  _T("���"),   _T("���"), _T("���"),  _T("����"), _T("���"),
      _T("��"),   _T("��"),    _T("��"),  _T("��"),   _T("���"),  _T("��") };

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
    if (   sTok == _T("�������")    // �������
        || sTok == _T("���")        // �������
        || sTok == _T("�-�")        // �������
        || sTok == _T("���")        // ������
        || sTok == _T("�-�")        // �������
        || sTok == _T("��")         // �������
        || sTok == _T("��-�")       // �������
        || sTok == _T("�������")    // �������
        || sTok == _T("�-�")        // ��������
        || sTok == _T("�-�")        // ���������
        || sTok == _T("���")        // ���������
        || sTok == _T("�������")    // ���������
        || sTok == _T("���������")  // ���������
        || sTok == _T("��")         // ��������, �����
        || sTok == _T("��-�")       // �����
        || sTok == _T("�����")     // �����
        || sTok == _T("��-�") )     // ��������
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
  if ( sRegion.Right(4) == _T("��� ") ) {
    sRegion += fShort ? _T("���.") : _T("�������");
  }
  else if ( sRegion.Right(4) == _T("���� ") ) {
    sRegion += _T("����");
  }

  sDistrict += TCHAR(' ');
  if ( sDistrict.Right(4) == _T("��� ") ) {
    if ( pDistrictRecord )
      sDistrict.Format(_T("%s %s"), pDistrictRecord->m_Name, fShort ? pDistrictRecord->GetShortTypeName() : _T("�����"));
    else
      sDistrict += fShort ? _T("�-�") : _T("�����");
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
  if ( sRegion.Right(4) == _T("��� ") ) {
    if ( pRegionRecord )
      sRegion.Format(_T("%s %s"), pRegionRecord->m_Name, pRegionRecord->GetShortTypeName());
    else
      sRegion += _T("���.");
  }
  else if ( sRegion.Right(4) == _T("���� ") ) {
    if ( pRegionRecord )
      sRegion += Trim(pRegionRecord->m_Type);
    else
      sRegion += _T("����");
  }

  sDistrict += TCHAR(' ');
  if ( sDistrict.Right(4) == _T("��� ") ) {
    if ( pDistrictRecord )
      sDistrict.Format(_T("%s %s"), pDistrictRecord->m_Name, pDistrictRecord->GetShortTypeName());
    else
      sDistrict += _T("�-�");
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
    sStreet =  _T("���. ") + sStreet;

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
     sHouseFlat.Format(_T("���. %s"), sHouse);
   }
   else {
     sHouseFlat.Format(_T("���. %s, ��. %s"), sHouse, sFlat);
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
  if ( sz.Left(2)==_T("� ") || sz.Left(8)==_T("��������") || sz.Find(_T("��������")) >-1 || sz.Find(_T("����������")) >-1 ) {
    return TCHAR('�');
  }
  return TCHAR('�');
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

  ������            +++
  ��������
  ��������������
  ������� �.

  ������            +++
  ��������
  ���������
  ����� ������ �. ��곿��� ���
  ������, �������� ���., ��곿���, ��������� �-�, �. ��� ����� ������, ������� '�', ���. 02, ��. 63
  
  ������
  ��������
  
  ���������� �. �����������

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
  if ( sRegion.Right(4) == _T("��� ") ) {
    if ( pRegionRecord )
      sRegion += pRegionRecord->GetShortTypeName();
    else
      sRegion += _T("���.");
  }
  else if ( sRegion.Right(4) == _T("���� ") ) {
    if ( pRegionRecord )
      sRegion += pRegionRecord->GetShortTypeName();
    else
      sRegion += _T("����");
  }

  sDistrict += TCHAR(' ');
  if ( sDistrict.Right(4) == _T("��� ") ) {
    if ( pDistrictRecord )
      sDistrict += pDistrictRecord->GetShortTypeName();
    else
      sDistrict += _T("�-�");
  }

  if ( !sCity.IsEmpty() && pCityRecord ) {
    if ( false==pCityRecord->m_AltName.IsEmpty() && sCity.Find(pCityRecord->m_AltName)>=0 ) {
      sCity.Format(_T("%s %s"), pCityRecord->GetShortTypeName(), pCityRecord->m_AltName);
      // ��� ����� ������, �. ��곿���
      int nFound = sCity.Find(_T("�."));
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
    sStreet =  _T("���. ") + sStreet;

  CString s, sHouseFlat;
  if ( !IsEmptyText(sHouse) ) {
    if ( (IsEmptyText(sFlat) || sFlat.GetAt(0)=='-')  ) {
      sHouseFlat.Format(_T("���. %s"), sHouse);
    }
    else {
      sHouseFlat.Format(_T("���. %s, ��. %s"), sHouse, sFlat);
    }
  }

  CString sReg;
  if ( FALSE==sRegion.IsEmpty() && pCityRecord && false==pCityRecord->IsMainCity() ) {
    sReg.Format(_T("%s, "), sRegion);
  }


  if ( false==fDontEditCity && false==IsEmptyText(sCity) ) {
    int nFound1(0), nFound2(0);
    nFound1 = sCity.Find(_T("�."));
    if ( nFound1 >=0 ) {
      nFound2 = sCity.Find(_T("�."), nFound1+1);
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
  szCityWord = _T(" �.");
  
  szDistrictWord = _T(" �-�");
  nDistrict = s.Find(szDistrictWord);
  if ( -1 == nDistrict ) {
    szDistrictWord = szDistrictWord;
    nDistrict = s.Find(_T(" �����"));
  }

  nCity = s.Find(szCityWord);
  if ( -1 == nCity ) {
    szCityWord = _T(" ����");
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
        if ( pDistrictRecord ) { // ��� ����� � ������?
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

