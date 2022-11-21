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
  map.SetAt(_T("��"),            _T("��������� ���������")                    );
  map.SetAt(_T("�����"),         _T("���� ��������� ���� ��������� �����") );
  map.SetAt(_T("�����"),         _T("���� ��������� ���� ��������� �����") );
  map.SetAt(_T("������"),        _T("���� �������� ��������� ���� ��������� �����") );
  map.SetAt(_T("���"),           _T("��������� ��������� �������")             );
  map.SetAt(_T("��������������"),_T("���������")                               );
  map.SetAt(_T("�"),             _T("��������")                                 );
  map.SetAt(_T("��"),            _T("���������� �����")                         );
  map.SetAt(_T("�.����"),        _T("���� ��������� ���� ��������� �����") );
  map.SetAt(_T("�.����"),        _T("���� ��������� ���� ��������� �����") );
  map.SetAt(_T("�/����"),        _T("���� ��������� ���� ��������� �����") );
  map.SetAt(_T("�/����"),        _T("���� ��������� ���� ��������� �����") );
  map.SetAt(_T("�-�"),           _T("����� ����")                             );
  map.SetAt(_T("�.�"),           _T("����� ����")                             );
  map.SetAt(_T("�/�"),           _T("����� ����")                             );
  map.SetAt(_T("��"),            _T("����� ����")                             );
  map.SetAt(_T("���"),           _T("������� ��������� �������")              );
  map.SetAt(_T("����"),          _T("������������� ��������� �������")        );
  map.SetAt(_T("�"),             _T("������")                                   );
  map.SetAt(_T("�-��"),          _T("������")                                   );
  map.SetAt(_T("�-��"),          _T("������")                                   );
  map.SetAt(_T("����"),          _T("��������� ���� ��������� �����")        );
  map.SetAt(_T("����"),          _T("��������� ���� ��������� �����")        );
  map.SetAt(_T("���"),           _T("��������� ��������� �������")             );
  map.SetAt(_T("�"),             _T("������")                                  );
  map.SetAt(_T("���"),           _T("������")                                  );
  map.SetAt(_T("���."),          _T("������")                                  );
  map.SetAt(_T("���"),           _T("��������� ��������� �������")             );

  map.SetAt(_T("�.�"),           _T("������� ����")                           );
  map.SetAt(_T("�/�"),           _T("������� ����")                           );
  map.SetAt(_T("�-�"),           _T("������� ����")                           );
  map.SetAt(_T("��"),            _T("������� ����")                           );
  map.SetAt(_T("���"),           _T("������� ����")                            );


  CString szRagsName;
  szRagsName.Format(_T(" %s "), sRagsName);
  if ( szRagsName.Find(_T("� �� ����")) > 0 ) {
    szRagsName.Replace(_T("� �� ����"), _T("� ��������� ��������� ����"));
  }
  else if ( szRagsName.Find(_T(" �� ����")) > 0 ) {
    szRagsName.Replace(_T(" �� ����"), _T(" ��������� ��������� ����"));
  }
  if ( szRagsName.Find(_T(" ��� ")) >= 0 ) {
    szRagsName.Replace(_T(" ��� "), _T(" ³��� ��������� ���� "));
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
  map.SetAt(_T(" �� "),         _T(" ��������� ��������� ")                   );
  map.SetAt(_T(" ����� "),      _T(" ���� ��������� ���� ��������� ����� "));
  map.SetAt(_T(" ��� "),        _T(" ��������� ��������� ������� ")            );
  map.SetAt(_T(" � "),          _T(" �������� ")                                );
  map.SetAt(_T(" � "),          _T(" �������� ")                                );
  map.SetAt(_T(" �."),          _T(" �. ")                                      );
  map.SetAt(_T(" �� "),         _T(" ����� ���� ")                            );
  map.SetAt(_T(" ��� "),        _T(" ������� ��������� ������� ")             );
  map.SetAt(_T(" ���� "),       _T(" ������������� ��������� ������� ")       );
  map.SetAt(_T(" � "),          _T(" ������ ")                                  );
  map.SetAt(_T(" ��� "),        _T(" ��������� ��������� ������� ")            );
  map.SetAt(_T(" � "),          _T(" ������ ")                                 );
  map.SetAt(_T(" ��� "),        _T(" ��������� ��������� ������� ")            );
  map.SetAt(_T(" �� "),         _T(" ������� ���� ")                          );
  map.SetAt(_T(" ��� "),        _T(" ������� ���� ")                           );

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
  if ( sRagsName.Find(_T(" �� ")) >=0 ) {
    return false;
  }
\************************************** : by VK at 22.10.2005 0:23:15 **/
  sCity = szCity;
  if ( sCity.IsEmpty() )
    return false;
  else if ( sCity.Right(2)==_T("��") ) { // �����, ������, �����
    sCity.TrimRight('�');
    sCity.TrimRight('�');
    sCity += _T("���");
  }
  else if ( sCity.Right(1)=="�" ) { // �����, ������
    sCity.TrimRight('�');
    sCity += _T("�");
  }
  else if ( sCity.Right(1)=="�" ) { // ����, �������
    sCity.TrimRight('�');
  }
  else if ( sCity.Right(1)=="�" ) { // �������
    sCity += _T("�");
  }
  else if ( sCity.Right(2)=="��" ) {// ��������
    ; // notning
  }
  else if ( sCity.Right(2)=="��" ) {// ������������
    sCity.TrimRight("��");
  }
  else if ( sCity.Right(1)=="�" ) { // ³�����
    sCity.TrimRight('�');
    sCity += _T("�");
  }
  else if ( sCity.Right(1)=="�" ) { // ��������
    sCity.TrimRight('�');
    sCity += _T("�");
  }
  else if ( sCity.Right(2)=="��" ) {// �������
    sCity.TrimRight('�');
    sCity.TrimRight('�');
    sCity += _T("���");
  }
  else {
    switch( sCity.Right(1).GetAt(0) ) {
      case '�': case '�': case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�':
        sCity += _T("�");
        break;
    }
  }

  s.Format(_T("�.%s"), sCity);
  if ( sRagsName.Find(s)>=0 )
    return true;
  

  sCity = szCity;
  if ( sCity.Right(1)=="�" )      { // �����, ������
    sCity.TrimRight('�');
    sCity += _T("��");
  }
  else if ( sCity.Right(3)==_T("���") ) { // �������
    sCity.TrimRight('�');
    sCity.TrimRight('�');
    sCity.TrimRight('�');
    sCity += _T("�����");
  }
  else if ( sCity==_T("��������") )  {// ��������
    sCity = _T("��������");
  }
  else if ( sCity.Right(1)=="�" ) { // ³�����
    sCity.TrimRight('�');
    sCity += _T("��");
  }
  else if ( sCity.Right(1)=='�' ) { // г���
    sCity += _T("����");
  }
  else  {
    switch( sCity.Right(1).GetAt(0) ) {
      case '�': case '�': case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�':
        sCity += _T("���");
        break;
    }
  }
  s.Format(_T("%s�� ������"), sCity);
  if ( sRagsName.Find(s)>=0 )
    return true;

  s.Format(_T("̳����� ����� %s���"), sCity);
  if ( sRagsName.Find(s)>=0 )
    return true;

  s.Format(_T("%s��� ���"), sCity);
  if ( sRagsName.Find(s)>=0 )
    return true;

  s.Format(_T("%s��� �������"), sCity);
  if ( sRagsName.Find(s)>=0 )
    return true;

  s.Format(_T("%s��� ���"), sCity);
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
      if ( sCity.Left(4)==sFoundCity.Left(4) && FALSE==sType.IsEmpty() && sType.GetAt(0)=='�' ) {
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
  sz1.Replace(_T("����"), _T(""));
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
  if ( sCity.Left(4)==_T("����") ) {
    nCount = 8;
  }
  else if ( sCity.Left(5)==_T("�����") ) {
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
        if ( sType.GetAt(0)=='�') {
          szType = _T("����");
        }
        else if ( sType==_T("���") || sType==_T("���.") ) {
          szType = _T("���");
        }
        else if ( sType==_T("���") || sType==_T("�-��") ) {
          szType = _T("������");
        }
        else if ( sType.GetAt(0)=='�' ) {
          szType = _T("����");
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

  if ( sRagsName.Find(_T("�����������")) >=0 ) {
    sRegion = _T("");
    g_RegionID = 0;
    GetRegionFromDB(_T("�����������"), RegionID);
    g_CityID = RegionID;
    g_szCity = _T("�����������");
    g_szCityType = _T("����");
  }
  else if ( sRagsName.Find(_T("ѳ���������")) >=0 ) {
    sRegion = _T("��������� ��������� ����");
    // g_RegionID = 11897;
    GetRegionFromDB(_T("����"), g_RegionID);
    g_szCity = _T("ѳ���������");
    // g_CityID = 11905;
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
    g_szCityType = _T("����");
  }
  else if ( sRagsName.Right(4)==_T("����") ) {
    sRegion = _T("��������� ��������� ����");
    g_RegionID = 11897;
    GetRegionFromDB(_T("����"), g_RegionID);
  }
  else if ( sRagsName.Right(5)==_T("����") || sRagsName.Right(5)==_T("���") ) {
    sRegion = _T("");
    g_RegionID = 0;
    g_CityID = 9678;
    g_szCity = _T("���");
    GetRegionFromDB(g_szCity, g_CityID);
    g_szCityType = _T("����");
  }
  else if ( IsMainCityRags(sRagsName, _T("³�����")) ) {
    sRegion = GetRegionFromDB(_T("³�������"), g_RegionID);
    g_CityID = 3;
    g_szCity = _T("³�����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
    g_szCityType = _T("����");
  }
  else if ( IsMainCityRags(sRagsName, _T("�����")) ) {
    sRegion = GetRegionFromDB(_T("���������"), g_RegionID);
    g_CityID = 3;
    g_szCity = _T("�����");
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("��������������")) ) {
    sRegion = GetRegionFromDB(_T("���������������"), g_RegionID);
    g_CityID = 2659;
    g_szCity = _T("��������������");
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("�������"))  ) {
    sRegion = GetRegionFromDB(_T("��������"), g_RegionID);
    g_CityID = 4196;
    g_szCity = _T("�������");
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("�������")) ) {
    sRegion = GetRegionFromDB(_T("�����������"), g_RegionID);
    g_szCity = _T("�������");
    g_CityID = 5473;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("�������")) ) {
    sRegion = GetRegionFromDB(_T("������������"), g_RegionID);
    g_szCity = _T("�������");
    g_CityID = 7176;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("��������")) ) {
    sRegion = GetRegionFromDB(_T("���������"), g_RegionID);
    g_szCity = _T("��������");
    g_CityID = 7800;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("�����-���������")) ) {
    sRegion = GetRegionFromDB(_T("�����-����������"), g_RegionID);
    g_szCity = _T("�����-���������");
    g_CityID = 8771;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("ʳ��������")) ) {
    sRegion = GetRegionFromDB(_T("ʳ������������"), g_RegionID);
    g_szCity = _T("ʳ��������");
    g_CityID = 10829;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("��������")) ) {
    sRegion = GetRegionFromDB(_T("���������"), g_RegionID);
    g_szCity = _T("��������");
    g_CityID = 12913;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("����")) ) {
    sRegion = GetRegionFromDB(_T("��������"), g_RegionID);
    g_szCity = _T("����");
    g_CityID = 13867;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("�������")) ) {
    sRegion = GetRegionFromDB(_T("�����������"), g_RegionID);
    g_szCity = _T("�������");
    g_CityID = 14693;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("�����")) ) {
    sRegion = GetRegionFromDB(_T("�������"), g_RegionID);
    g_szCity = _T("�����");
    g_CityID = 16763;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("�������")) ) {
    sRegion = GetRegionFromDB(_T("����������"), g_RegionID);
    g_szCity = _T("�������");
    g_CityID = 17977;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("г���")) ) {
    sRegion = GetRegionFromDB(_T("г��������"), g_RegionID);
    g_szCity = _T("г���");
    g_CityID = 19283;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("����")) ) {
    sRegion = GetRegionFromDB(_T("�������"), g_RegionID);
    g_szCity = _T("����");
    g_CityID = 20179;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("��������")) ) {
    sRegion = GetRegionFromDB(_T("������������"), g_RegionID);
    g_szCity = _T("��������");
    g_CityID = 21705;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("�����")) ) {
    sRegion = GetRegionFromDB(_T("���������"), g_RegionID);
    g_szCity = _T("�����");
    g_CityID = 22789;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("������")) ) {
    sRegion = GetRegionFromDB(_T("����������"), g_RegionID);
    g_szCity = _T("������");
    g_CityID = 24571;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("������������")) ) {
    sRegion = GetRegionFromDB(_T("�����������"), g_RegionID);
    g_szCity = _T("������������");
    g_CityID = 24702;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("�������")) ) {
    sRegion = GetRegionFromDB(_T("���������"), g_RegionID);
    g_szCity = _T("�������");
    g_CityID = 26176;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( IsMainCityRags(sRagsName, _T("�������")) ) {
    sRegion = GetRegionFromDB(_T("����������"), g_RegionID);
    g_szCity = _T("�������");
    g_CityID = 27044;
    g_szCityType = _T("����");
    GetCityFromDB(g_szCity, g_RegionID, g_CityID);
  }
  else if ( sRagsName.Right(4)==_T("� �") ) {
    s = GetTokenBefore(sRagsName, sRagsName.GetLength()-4);
    if ( FALSE==s.IsEmpty() ) {
      sRegion = GetRegionFromDB(s, g_RegionID);
    }
  }
  else if (sRagsName.Right(7)==_T("��� ���")) {
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

  s = _T(" �� ");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs-4);
    if ( g_RegionID ) {
      sCity = GetCityFromDB(s, g_RegionID, g_CityID);
      if ( FALSE==sCity.IsEmpty() ) {
        g_szCityType = _T("����");
        return sCity;
      }
    }
  }

  s = _T("�� ���� ");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs+s.GetLength()+1);
    if ( g_RegionID ) {
      sCity = GetCityFromDB(s, g_RegionID, g_CityID);
      if ( FALSE==sCity.IsEmpty() ) {
        g_szCityType = _T("����");
        return sCity;
      }
    }
  }
  s = _T("�� �.");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs+s.GetLength()+1);
    if ( g_RegionID ) {
      sCity = GetCityFromDB(s, g_RegionID, g_CityID);
      if ( FALSE==sCity.IsEmpty() ) {
        g_szCityType = _T("����");
        return sCity;
      }
    }
  }
  s = _T("��� ");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs-2);
    if ( g_RegionID ) {
      sCity = GetCityFromDB(s, g_RegionID, g_CityID);
      if ( FALSE==sCity.IsEmpty() ) {
        g_szCityType = _T("����");
        return sCity;
      }
    }
  }

  s = _T("̳����� �����");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs+s.GetLength()+1);
    if ( g_RegionID ) {
      sCity = GetCityFromDB(s, g_RegionID, g_CityID);
      if ( FALSE==sCity.IsEmpty() ) {
        g_szCityType = _T("����");
        return sCity;
      }
    }
  }

  s = _T("�� ������");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs);
    if ( g_RegionID ) {
      sCity = GetCityFromDB(s, g_RegionID, g_CityID);
      if ( FALSE==sCity.IsEmpty() ) {
        g_szCityType = _T("����");
        return sCity;
      }
    }
  }
  return sCity;
}

CString GetCityFromRagsName(const CString& sRagsName, long lParentID) {
  CString sCity;

  if ( sRagsName==_T("� �������� �� ����������� � ������������ �") ) {
    sCity = _T("����");
  }
  else {
    LPCTSTR szFind[3] = { _T(" �� "), _T(" �� "), _T(" ��� ") };
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

  if ( szDistrict.Right(3)==_T("���") ) {
    szDistrict.TrimRight(_T("���"));
  }

  try {
    CString sql;
    sql.Format(_T("SELECT ID,NAME,TYPE FROM GEOGRAPHY WHERE PARENT=%d"), ParentID);
    rs.Open(dbOpenDynaset, sql, dbReadOnly);

    while ( !rs.IsEOF() ) {
      long id                = GetFieldLong  (&rs, _T("ID"));
      CString sFoundDistrict = GetFieldString(&rs, _T("NAME"));
      CString sType          = GetFieldString(&rs, _T("TYPE"));
      if ( sFoundDistrict.Find(szDistrict)>=0 && FALSE==sType.IsEmpty() && sType.GetAt(0)=='�' ) {
        s = sFoundDistrict;
        lID = id;
        break;
      }
      else if (FALSE==sType.IsEmpty() && sType.GetAt(0)=='�') {
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
  s = _T(" ��� ");
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
  s = _T("�������� �����");
  offs = sRagsName.Find(s);
  if ( offs >= 0 ) {
    s = GetTokenBefore(sRagsName, offs+s.GetLength()+1);
    if ( g_RegionID ) {
      sDistrict = GetDistrictFromDB(s, g_RegionID, g_DistrictID);
      if ( FALSE==sDistrict.IsEmpty() )
        return sDistrict;
    }
  }
  s = _T("��� �");
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
  if ( g_szRagsName.Left(2)==_T("� ") ) {
    fEnable = true;
    uID = IDC_VYCONCOM;
  }
  else if ( g_szRagsName.Left(3)==_T("�� ") ) {
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

  if ( g_szRegion==_T("��������") ) {
    if ( sRagsName.Find(_T("� ���������� ")) >= 0 ) {
      fProcess = false;
      g_szCity = _T("�������, �. ��������");
      g_szBirthCityType = g_szCityType = _T("�");
    }
    else if ( sRagsName.Find(_T("� ����������� ��� ")) >= 0 ) {
      fProcess = false;
      g_szCity = _T("�������, �. ��������");
      g_szBirthCityType = g_szCityType = _T("���");
    }
    else if ( sRagsName.Find(_T("� ���������� ��� ")) >= 0 ) {
      fProcess = false;
      g_szCity = _T("�����, �. ����");
      g_szBirthCityType = g_szCityType = _T("���");
    }
  }

  if ( fProcess ) {
    CString sCity = GetCityFromRagsName(sRagsName);
    if ( sCity.IsEmpty() ) {
      switch(g_RagsID) {
        case 41301: // � ���������� �� �. ����������� �������� �
          sCity = _T("���������� �.����������");
          g_szCityType = _T("���");
          break;
        case 41302: // � ʳ������� ��� �. ����������� �������� � ���������� �����
          sCity = _T("ʳ���� �.����������");
          g_szCityType = _T("���");
          break;
        case 41303: // � ������������ ��� �. ����������� �������� �
          sCity = _T("������������ �.����������");
          g_szCityType = _T("���");
          break;
        case 41304: // � ����������� ��� �. ����������� �������� �
          sCity = _T("��������� �.����������");
          g_szCityType = _T("���");
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
      if ( sRagsName.Left(2)==_T("� ") || sRagsName.Left(2)==_T("� ") ) {
        CString sCity = GetCityFromRagsName(sRagsName, g_DistrictID);
        if ( FALSE==sCity.IsEmpty() ) {
          g_szCity = g_szBirthCity = sCity;
          g_szBirthCityType = g_szCityType;
        }
      }
    }
  }

  if ( g_szRegion==_T("��������") ) {
    if ( g_szCity==_T("�����������") ) {
      g_szCity=_T("�����������, �. ����������");
    }
    else if ( g_szCity==_T("�����������") ) {
      g_szCity=_T("����������, �. �����������");
    }

  }
  else if ( g_szRegion==_T("���������") ) {
    if ( g_szCity==_T("���������������") ) {
      g_szCity=_T("��������������� �. ���������");
    }
  }
  else if ( g_szRegion==_T("��������") ) {
    if ( sRagsName == _T("� ���������� ��� �.�������� �������� �") ) {
      g_szCity = _T("��������, �. ��������");
      g_szBirthCityType = g_szCityType = _T("���");
    }
    else if ( sRagsName == _T("� ����������� ��� �. ������") ) {
      g_szCity = _T("���������, �. ����");
      g_szBirthCityType = g_szCityType = _T("���");
    }
    else if ( sRagsName == _T("� ���������� ��� �. ������") ) {
      g_szCity = _T("�����, �. ����");
      g_szBirthCityType = g_szCityType = _T("���");
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
  if ( g_szRagsName.Left(3)==_T("�� ") ) {
    g_szRagsName.Delete(1);
    GetDlgItem(IDC_SHORTNAME)->SetWindowText(g_szRagsName);
    OnChangeShortname();
  }
}

void CSetRagsPage::OnOrgan() {
	// TODO: Add your control notification handler code here
  if ( g_szRagsName.Left(2)==_T("� ") ) {
    g_szRagsName.Insert(1, '�');
    GetDlgItem(IDC_SHORTNAME)->SetWindowText(g_szRagsName);
    OnChangeShortname();
  }
}
