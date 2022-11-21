#include "stdafx.h"
#include "EraABC.h"

#include "..\Common\CyrString.h"

#include "Names.h"


CString OfferSurname(LPCTSTR szSrc, BOOL bSexFrom, BOOL bSexTo) {
  CString sFrom = szSrc;
  CString sOffer = szSrc;
  int iLen = sFrom.GetLength();

  sOffer = sFrom;

  if ( TRUE==bSexFrom && FALSE==bSexTo ) {  // �������� ������� - �������,
                                            // ���������� �������
    if ( sFrom.Right(4)==_T("����") )
      sOffer = sFrom.Left(iLen - 2) + _T("�");
    else {
      CString sRight2 = sFrom.Right(2);
      if ( sRight2==_T("��") || sRight2==_T("��") )
        sOffer = sFrom.Left(iLen - 2) + _T("�");
      else if ( sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��"))
        sOffer = sFrom + _T("�");
    }
  }
  else if( FALSE==bSexFrom && TRUE==bSexTo ) {
    CString sRight2 = sFrom.Right(2);
    CString sRight3 = sFrom.Right(3);
    if ( sRight3==_T("���") || sRight3==_T("���") ||
         sRight3==_T("���") || sRight3==_T("���") ||
         sRight3==_T("���") )
      sOffer = sFrom.Left(iLen-1);
    else if ( sRight3==_T("���") )
      sOffer = sFrom.Left(iLen - 2) + _T("��");
    else if ( sRight3==_T("���") )
      sOffer = sFrom.Left(iLen - 2) + _T("��");
    else if ( sFrom.Right(2)==_T("��") )
      ;
    else if ( sFrom.Right(1)==_T("�") )
      sOffer = sFrom.Left(iLen - 1) + _T("��");
  }
  return sOffer;
}

CString OfferSurname(CWnd* pWnd, BOOL bSexFrom, BOOL bSexTo) {
  CString s;
  pWnd->GetWindowText(s);
  return OfferSurname(s, bSexFrom, bSexTo);
}

CString OfferName(CWnd* pWnd) {
  CString s;
  pWnd->GetWindowText(s);
  if ( s.Find(_T("�����")==0) )
    s = _T("������");
  else if ( s.Find(_T("�����")==0) )
    s = _T("������");
  else if ( s.Find(_T("�����")==0) )
    s = _T("������");
  else if ( s.Find(_T("������")==0) )
    s = _T("�������");
  else if ( s.Find(_T("����")==0) )
    s = _T("������");
  else if ( s.Find(_T("�����")==0) )
    s = _T("�������");
  else if ( s.Find(_T("�������")==0) )
    s = _T("�������");
  else if ( s.Find(_T("���")==0) )
    s = _T("����");
  else if ( s.Find(_T("����")==0) )
    s = _T("�����");
  else if ( s.Find(_T("�����")==0) )
    s = _T("������");
  return s;
}

CString PASCAL MakeSNP(const CString& sSurname, const CString& sName, const CString& sFather) {
  CString s = Trim(sSurname);
  if ( sName.GetLength() > 0 ) {
    s += ' ';
    s += sName.GetAt(0);
    s += '.';
  }
  if ( sFather.GetLength() > 0 ) {
    s += ' ';
    s += sFather.GetAt(0);
    s += '.';
  }
  return s;
}

///////////////////////////////////////////////////////
// �������-���������� ������� �������, ���� � �������.
//
CString ManSurname_DV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<3)
    return szFrom;

  CString sManSurname_DV, sFrom(Trim(szFrom)),
          sLeft1, sLeft2, sLeft3,
          sRight2, sRight3;
  int iLen = sFrom.GetLength();
  BOOL bUppercase(FALSE);

  if (szFrom==NULL || szFrom=='\0')
    return _T("");

  if (IsCyrUpper(sFrom)) {
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  sManSurname_DV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);
  sLeft2 = sFrom.Left(iLen-2);
  sLeft3 = sFrom.Left(iLen-3);
  sRight2 = sFrom.Right(2);
  sRight3 = sFrom.Right(3);

  if(sRight3 == _T("���") )
    sManSurname_DV = sLeft3 + _T("��");
  else if(sRight3 == _T("���") )
    sManSurname_DV = sLeft3 + _T("���");
  else if(sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") ||
          sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") ||
          sRight2==_T("��") || sRight2==_T("��") )
    sManSurname_DV = sFrom + _T("�");
  else if(sRight2==_T("��") || sRight2==_T("��") )
    sManSurname_DV = sLeft2 + _T("���");
  else if(sRight2==_T("��")  )
    sManSurname_DV = sFrom.Left(iLen-2) + _T("�");
  else if(sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") )
    sManSurname_DV = sLeft1 + _T("�");
  else if(sRight2==_T("��") )
    sManSurname_DV = sFrom.Left(iLen - 4) + _T("��");
  else if(sRight2==_T("��") ){
    if(sFrom.Right(3) == _T("��") )
      sManSurname_DV = sLeft2 + _T("����");
    else
      sManSurname_DV = sLeft1 + _T("�");
  }
  else{
    switch(sFrom.Right(1)[0]){
      case '�':
        sManSurname_DV = sLeft1 + _T("�");  break;
      case '�':
        sManSurname_DV = sLeft1 + "�";  break;
      case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�':
        sManSurname_DV = sFrom + _T("�");
        break;
      case '�':
        sManSurname_DV = sLeft1 + _T("�");
        break;
      case '�':
        sManSurname_DV = sLeft1 + _T("�");
     }
  }
  if(bUppercase)
    sManSurname_DV = UpperString(sManSurname_DV);
  return sManSurname_DV;
}

CString ManSurname_OV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<3)
    return szFrom;

  CString sManSurname_OV, sFrom(Trim(szFrom)),
          sLeft1, sLeft2, sLeft3, sRight2, sRight3;
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)){
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sManSurname_OV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);
  sLeft2 = sFrom.Left(iLen-2);
  sLeft3 = sFrom.Left(iLen-3);
  sRight2 = sFrom.Right(2);
  sRight3 = sFrom.Right(3);

  
  if(sRight3 == _T("���") )
    sManSurname_OV = sLeft3 + _T("���");
  else if(sRight3 == _T("���") )
    sManSurname_OV = sLeft3 + _T("����");
  if(sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") ||
     sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") ||
     sRight2==_T("��") || sRight2==_T("��") )
    sManSurname_OV = sFrom + _T("��");
  else if(sRight2==_T("��") )
    sManSurname_OV = sLeft2 + _T("��");
  else if(sRight2==_T("��") )
    sManSurname_OV = sLeft1 + _T("��");
  else if(sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") )
    sManSurname_OV = sLeft1 + _T("��");
  else if(sRight2==_T("��") )
    sManSurname_OV = sFrom + _T("�");
  else if(sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") )
    sManSurname_OV = sFrom + _T("��");
  else if(sRight2==_T("��") ) {
     if(sFrom.Mid(iLen - 2, 1) == _T("�") )
       sManSurname_OV = sLeft1 + _T("��");
     else
       sManSurname_OV = sLeft1 + _T("��");
   }
   else {
     switch(sFrom.Right(1)[0]) {
       case  '�': case '�':
         sManSurname_OV = sLeft1 + _T("��"); break;
       case '�': case '�': case '�': case '�': case '�':
       case '�': case '�': case '�': case '�': case '�':
       case '�': case '�': case '�': case '�': case '�':
       case '�': case '�': case '�': case '�': case '�':
         sManSurname_OV = sFrom + _T("��");  break;
       case '�':
         sManSurname_OV = sLeft1 + _T("��"); break;
       case '�':
         sManSurname_OV = sLeft1 + _T("��"); break;
       case '�':
         sManSurname_OV = sLeft1 + _T("��"); break;
     }
  }
  if(bUppercase)
    sManSurname_OV = UpperString(sManSurname_OV);
  return sManSurname_OV;
}

CString ManSurname_RV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<3)
    return szFrom;

  CString sManSurname_RV, sFrom(Trim(szFrom)),
          sLeft1, sLeft2, sLeft3, sRight2, sRight3;
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)){
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sManSurname_RV = sFrom;
  sLeft1 = sFrom.Left(iLen - 1);
  sLeft2 = sFrom.Left(iLen - 2);
  sLeft3 = sFrom.Left(iLen-3);
  sRight2 = sFrom.Right(2);
  sRight3 = sFrom.Right(3);

  
  if(sRight3 == _T("���") )
    sManSurname_RV = sLeft3 + _T("��");
  else if(sRight3 == _T("���") )
    sManSurname_RV = sLeft3 + _T("���");
  else if(sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") ||
          sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") ||
          sRight2==_T("��") || sRight2==_T("��") )
    sManSurname_RV = sFrom + _T("�");
  else if(sRight2==_T("��") || sRight2==_T("��") )
    sManSurname_RV = sLeft2 + _T("���") ;
  else if(sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") )
    sManSurname_RV = sLeft1 + _T("�");
  else if(sRight2==_T("��") ){
    if(sFrom.Right(3) == _T("��") )
      sManSurname_RV = sLeft2 + _T("����");
    else
      sManSurname_RV = sLeft1 + _T("�");
  }
  else{
    switch(sFrom.Right(1)[0]){
      case '�':
        sManSurname_RV = sLeft1 + _T("�"); break;
      case '�':
        sManSurname_RV = sLeft1 + _T("�"); break;
      case '�': case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�': case '�':
        sManSurname_RV =  sFrom + _T("�"); break;
      case '�':
        sManSurname_RV =  sLeft1 + _T("�");  break;
      case '�': case '�':
        sManSurname_RV =  sLeft1 + _T("�");  break;
     }
   }
   if(bUppercase)
    sManSurname_RV = UpperString(sManSurname_RV);
   return sManSurname_RV;
}

CString ManSurname_ZV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<3)
    return szFrom;

  CString sManSurname_ZV, sFrom(Trim(szFrom)),
          sLeft1, sLeft2, sLeft3, sRight1, sRight2, sRight3;
  int iLen = sFrom.GetLength();
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)){
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  sManSurname_ZV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);
  sLeft2 = sFrom.Left(iLen-2);
  sLeft3 = sFrom.Left(iLen-3);
  sRight1 = sFrom.Right(1);
  sRight2 = sFrom.Right(2);
  sRight3 = sFrom.Right(3);
  
  if(sRight3 == _T("���") )
    sManSurname_ZV = sLeft3 + _T("��");
  else if(sRight3 == _T("���") )
    sManSurname_ZV = sLeft3 + _T("���");
  else if(sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") ||
          sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") ||
          sRight2==_T("��") || sRight2==_T("��") )
    sManSurname_ZV = sFrom + _T("�");
  else if(sRight1==_T("�") )
    sManSurname_ZV = sLeft1 + _T("�");
  else if(sRight2==_T("��") || sRight2==_T("��") )
    sManSurname_ZV = sLeft2 + _T("���");
  else if(sRight2==_T("��") )
    sManSurname_ZV = sFrom.Left(iLen - 4) + _T("��");
  else if(sRight2==_T("��") ){
    if(sRight3 == _T("��") )
      sManSurname_ZV = sLeft2 + _T("����");
    else
      sManSurname_ZV = sLeft1 + _T("�");
  }
  else{
    switch(sRight1[0]){
      case '�':
        sManSurname_ZV = sLeft1 + _T("�");  break;
      case '�':
        sManSurname_ZV = sLeft1 + _T("�");  break;
      case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�':
      case '�': case '�': case '�': case '�':
        sManSurname_ZV = sFrom + _T("�");
        break;
      case '�':
        sManSurname_ZV = sLeft1 + _T("�");
        break;
      case '�':
        sManSurname_ZV = sLeft1 + _T("�");
     }
  }
  if(bUppercase)
    sManSurname_ZV = UpperString(sManSurname_ZV);
  return sManSurname_ZV;
}


CString ManName_DV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sManName_DV, sFrom(Trim(szFrom)), sLeft1;
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)){
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sManName_DV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);


  switch(sFrom.Right(1)[0]){
    case '�':
      sManName_DV = sLeft1 + _T("�"); break;
    case '�':
      sManName_DV = sLeft1 + _T("�"); break;
    case '�':
      sManName_DV = sLeft1 + _T("�"); break;
    case '�':
      switch(sFrom.Mid(iLen - 1, 1)[0]){
        case '�': case '�': case '�': case '�':
        case '�': case '�': case '�': case '\'':
        case '�': case '�': case '�':
          sManName_DV = sLeft1 + _T("�"); break;
        default:
          sManName_DV = sLeft1 + _T("�"); break;
      }
      break;
    case '�':
      if(sFrom==_T("����") || sFrom==_T("�����") )
        sManName_DV = sFrom + "�";
      else
        sManName_DV = sFrom + "�";
      break;
    case '�':
      sManName_DV = sLeft1 + _T("�");
      break;
    case '�': case '�': case '�': case '�': case '�':
    case '�': case '�': case '�': case '�': case '�':
    case '�': case '�':  case '�': case '�': case '�':
    case '�': case '�': case '�':  case '�':
      sManName_DV = sFrom + _T("�");
      break;
  }
  if(bUppercase)
    sManName_DV = UpperString(sManName_DV);
  return sManName_DV;
}

CString ManName_OV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sManName_OV, sFrom(Trim(szFrom)), sLeft1, sRight2;
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)){
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sManName_OV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);

  switch (sFrom.Right(1)[0]){
    case '�':  sManName_OV = sLeft1 + _T("��");  break;
    case '�': sManName_OV = sFrom + _T("�");    break;
    case '�': sManName_OV = sLeft1 + _T("��");  break;
    case '�':
      switch(sFrom.Mid(iLen - 1, 1)[0]){
        case '�': case '�': case '�': case '�':
        case '�': case '�': case '�': case '\'':
        case '�': case '�': case '�':
          sManName_OV = sLeft1 +  _T("��");
      }
      break;
    case '�':
      sRight2 = sFrom.Right(2);
      if(sFrom == _T("����") )
        sManName_OV = _T("�������");
      else
        sManName_OV = sFrom + _T("��");
      break;
    case '�': case '�': case '�': case '�': case '�': case '�':
    case '�': case '�': case '�': case '�': case '�': case '�':
    case '�': case '�': case '�': case '�': case '�': case '�':
      sManName_OV  = sFrom + _T("��");
      break;
    case '�': case '�':
      sManName_OV  = sFrom + _T("��");
      break;
  }
  if(bUppercase)
    sManName_OV = UpperString(sManName_OV);
  return sManName_OV;
}

CString ManName_RV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sManName_RV, sFrom(Trim(szFrom)), sLeft1;
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)){
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }
  iLen = sFrom.GetLength();
  sManName_RV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);

  switch(sFrom.Right(1)[0]){
    case '�': sManName_RV = sLeft1 + "�";  break;
    case '�': sManName_RV = sLeft1 + "�";  break;
    case '�': sManName_RV = sLeft1 + "�";  break;
    case '�':
      switch(sFrom.Mid(iLen - 1, 1)[0]){
        case '�': case '�': case '�': case '�': case '�': case '�':
        case '�': case '�': case '�': case '�': case '\'':
          sManName_RV = sLeft1 + _T("�");  break;
        default:
          sManName_RV = sLeft1 + _T("�");  break;
      }
      break;
    case '�':
      if (sFrom == _T("����") || sFrom == _T("�����") )
        sManName_RV = sFrom + _T("�");
      else
        sManName_RV = sFrom + _T("�");
      break;
    case '�': case '�': case '�': case '�': case '�':
    case '�': case '�': case '�': case '�': case '�':
    case '�': case '�':  case '�': case '�': case '�':
    case '�': case '�': case '�':  case '�':
      sManName_RV = sFrom + _T("�");
      break;
  }
  if(bUppercase)
    sManName_RV = UpperString(sManName_RV);
  return sManName_RV;
}

CString ManName_ZV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sManName_ZV, sFrom(Trim(szFrom)), sLeft1;
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)){
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sManName_ZV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);

  switch(sFrom.Right(1)[0]) {
    case '�': sManName_ZV = sLeft1 + "�";  break;
    case '�': sManName_ZV = sLeft1 + "�";  break;
    case '�': sManName_ZV = sLeft1 + "�";  break;
    case '�':
        sManName_ZV = sLeft1 + _T("�");  break;
      break;
    case '�':
      if (sFrom == _T("����") || sFrom == _T("�����") )
        sManName_ZV = sFrom + _T("�");
      else
        sManName_ZV = sFrom + _T("�");
      break;
    case '�': case '�': case '�': case '�': case '�':
    case '�': case '�': case '�': case '�': case '�':
    case '�': case '�':  case '�': case '�': case '�':
    case '�': case '�': case '�':  case '�':
      sManName_ZV = sFrom + _T("�");
      break;
  }
  if(bUppercase)
    sManName_ZV = UpperString(sManName_ZV);
  return sManName_ZV;
}

CString ManFather_DV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sManFather_DV, sFrom(Trim(szFrom));
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)){
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }
  sManFather_DV = sFrom;
  if(sFrom.Right(1) == _T("�") )
    sManFather_DV = sFrom + _T("�");
  if(bUppercase)
    sManFather_DV = UpperString(sManFather_DV);
  return sManFather_DV;
}

CString ManFather_OV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sManFather_OV, sFrom(Trim(szFrom));
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)) {
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  sManFather_OV = sFrom;
  if(sFrom.Right(1) == _T("�") )
    sManFather_OV = sFrom + _T("��");
  if(bUppercase)
    sManFather_OV = UpperString(sManFather_OV);
  return sManFather_OV;
}

CString ManFather_RV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sManFather_RV, sFrom(Trim(szFrom));
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)){
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }
  sManFather_RV = sFrom;
  if(sFrom.Right(1) == _T("�") )
    sManFather_RV = sFrom + _T("�");
  if(bUppercase)
    sManFather_RV = UpperString(sManFather_RV);
  return sManFather_RV;
}

CString ManFather_ZV(LPCTSTR szFrom) {
  return ManFather_RV(szFrom);
}

///////////////////////////////////////////////////////
// �������-��������� ������� �������, ���� � �������.
//
BOOL W_as_ova(CString& sFrom) {
BOOL bRet(FALSE);
CString sRight3;
int iLen = sFrom.GetLength();
  if(iLen>3){
    sRight3 = sFrom.Right(3);
    if(sRight3==_T("���") || sRight3==_T("���") || sRight3==_T("���") ||
       sRight3==_T("���") || sRight3==_T("���") || sRight3==_T("���") ||
       sRight3==_T("���") || sRight3==_T("���") || sRight3==_T("���") ||
       sRight3==_T("���") || sRight3==_T("���") || sRight3==_T("���") ||
       sRight3==_T("���") )
       bRet = TRUE;
  }
  return bRet;
}

BOOL W_as_ska(CString& sFrom) {
BOOL bRet(FALSE);
CString sRight4;
int iLen = sFrom.GetLength();
  if(iLen>4){
    sRight4 = sFrom.Right(4);
    if(sRight4==_T("����") || sRight4==_T("����") || sRight4==_T("����") )
      bRet = TRUE;
  }
  return bRet;
}
BOOL W_as_ura(CString& sFrom) {
BOOL bRet(FALSE);
CString sRight2;
int iLen = sFrom.GetLength();
  if(iLen>2){
    sRight2 = sFrom.Right(2);
    if(sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") ||
       sRight2==_T("��") || sRight2==_T("��") )
      bRet = TRUE;
  }
  return bRet;
}

BOOL W_as_na(CString& sFrom) {
BOOL bRet(FALSE);
int iLen = sFrom.GetLength();
  if(iLen>2){
    if(sFrom.Right(2)==_T("��") )
      bRet = TRUE;
  }
  return bRet;
}


CString WomanSurname_DV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sWomanSurname_DV, sFrom(Trim(szFrom)), sLeft1, sRight2;
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)){
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }
  iLen = sFrom.GetLength();
  sWomanSurname_DV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);
  sRight2 = sFrom.Right(2);

  if(W_as_ova(sFrom) || W_as_ska(sFrom))
    sWomanSurname_DV = sLeft1 + _T("��");
  else if(sFrom.Right(4)==_T("����") )
    sWomanSurname_DV = sFrom.Left(iLen-2) + _T("��");
  else if(sRight2==_T("��")  )
    sWomanSurname_DV = sFrom.Left(iLen-2) + _T("�");
  else if(sRight2==_T("��") || sRight2==_T("��") )
    sWomanSurname_DV = sLeft1 + _T("�");
  if(bUppercase)
    sWomanSurname_DV = UpperString(sWomanSurname_DV);
  return sWomanSurname_DV;
}

CString WomanSurname_OV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sWomanSurname_OV, sFrom(Trim(szFrom)), sLeft1, sRight2;
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)){
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }
  iLen = sFrom.GetLength();
  sWomanSurname_OV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);
  sRight2 = sFrom.Right(2);

  if( W_as_ska(sFrom) )
    sWomanSurname_OV = sLeft1 + _T("�");
  if(W_as_ova(sFrom) || sFrom.Right(4)==_T("����") || sRight2==_T("��") ||
     sRight2==_T("��") || sRight2==_T("��") || sRight2==_T("��") )
    sWomanSurname_OV = sLeft1 + _T("��");
  if(bUppercase)
    sWomanSurname_OV = UpperString(sWomanSurname_OV);
  return sWomanSurname_OV;
}

CString WomanSurname_RV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sWomanSurname_RV, sFrom(Trim(szFrom)), sLeft1, sRight2;
  int iLen;
  BOOL bUppercase(FALSE);

  if (IsCyrUpper(sFrom)){
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }
  iLen = sFrom.GetLength();
  sWomanSurname_RV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);
  sRight2 = sFrom.Right(iLen-2);

  if(sRight2==_T("��") )
    sWomanSurname_RV = sLeft1 + _T("�");
  else if(sRight2=="��")
    sWomanSurname_RV = sFrom.Left(iLen-2) + _T("��");
  else if(sRight2==_T("��") || sRight2==_T("��") )
    sWomanSurname_RV = sLeft1 + _T("�");
  else if(W_as_ova(sFrom))
    sWomanSurname_RV = sLeft1 + _T("�");
  else if(W_as_ura(sFrom))
    sWomanSurname_RV = sLeft1 + _T("�");
  else if(W_as_ska(sFrom))
    sWomanSurname_RV = sLeft1 + _T("�");

  if (bUppercase)
    sWomanSurname_RV = UpperString(sWomanSurname_RV);
  return sWomanSurname_RV;
}

CString WomanSurname_ZV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sWomanSurname_ZV, sFrom(Trim(szFrom)), sLeft1, sRight2;
  int iLen;
  BOOL bUppercase(FALSE);

  if (IsCyrUpper(sFrom)) {
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sWomanSurname_ZV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);
  sRight2 = sFrom.Right(iLen-2);

  if(W_as_ova(sFrom) || W_as_ska(sFrom) || W_as_ura(sFrom) ||
     sRight2==_T("��") || sRight2==_T("��") )
    sWomanSurname_ZV = sLeft1 + _T("�");
  else if(sRight2==_T("��") )
    sWomanSurname_ZV = sFrom.Left(iLen-2) + _T("��");
  else if(sRight2==_T("��") )
    sWomanSurname_ZV = sLeft1 + _T("�");
  if(bUppercase)
    sWomanSurname_ZV = UpperString(sWomanSurname_ZV);
  return sWomanSurname_ZV;
}

CString WomanName_DV(LPCTSTR szFrom){

  if (szFrom==NULL || lstrlen(szFrom)<3)
    return szFrom;

  CString sWomanName_DV, sFrom(Trim(szFrom)), sLeft1;
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)) {
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sWomanName_DV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);

  if(sFrom==_T("�����") )
    sWomanName_DV = _T("����") ;
  else if(sFrom==_T("�����") )
    sWomanName_DV = _T("�����") ;
  else if(sFrom==_T("�������") )
    sWomanName_DV = _T("�������");
  else if(sFrom==_T("������") )
    sWomanName_DV = _T("�����") ;
  else {
    switch(sFrom.Right(1)[0]) {
      case '�': case '�':
        sWomanName_DV = sLeft1 + _T("�"); break;
      case '�':
        switch(sFrom.Right(2)[0]){
          case '�': case '�': case '�': case '�': case '�':  case '�':
          case '�': case '�': case '�':  case '�': case '\'': 
            sWomanName_DV = sLeft1 + _T("�");  break;
          default:
            sWomanName_DV = sLeft1 + _T("�");  break;
        }
        break;
    }
  }

  if(bUppercase)
    sWomanName_DV = UpperString(sWomanName_DV);
  return sWomanName_DV;
}

CString WomanName_OV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sWomanName_OV, sFrom(Trim(szFrom)), sLeft1;
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)) {
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sWomanName_OV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);

  if(sFrom==_T("�����") )
    sWomanName_OV = _T("�����'�");
  else{
    switch(sFrom.Right(1)[0]){
      case '�':
        sWomanName_OV = sLeft1 + _T("��");  break;
      case '�':
        sWomanName_OV = sLeft1 +  _T("�");  break;
      case '�':
        switch(sFrom.Mid(iLen - 1, 1)[0]){
          case '�': case '�': case '�': case '�': case '�':  case '�':
          case '�': case '�': case '�':  case '�': case '\'': 
            sWomanName_OV = sLeft1 +  _T("��");  break;
          default:
            sWomanName_OV = sLeft1 +  _T("��");  break;
        }
        break;
    }
  }
  if(bUppercase)
    sWomanName_OV = UpperString(sWomanName_OV);
  return sWomanName_OV;
}

CString WomanName_RV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<3)
    return szFrom;

  CString sWomanName_RV, sFrom(Trim(szFrom)), sLeft1;
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)) {
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sWomanName_RV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);

  if(sFrom==_T("�����") )
    sWomanName_RV = _T("����");
  else if(sFrom==_T("�����") )
    sWomanName_RV  = _T("�����");
  else {
    switch(sFrom.Right(1)[0]) {
      case '�':
        sWomanName_RV = sLeft1 + _T("�");  break;
      case '�':
        sWomanName_RV = sLeft1 + _T("�");  break;
      case '�':
        switch(sFrom.Right(2)[0]){
          case '�': case '�': case '�': case '�': case '�':  case '�':
          case '�': case '�': case '�':  case '�': case '\'': 
            sWomanName_RV = sLeft1 + _T("�");  break;
          default:
            sWomanName_RV = sLeft1 + _T("�");  break;
        }
        break;
    }
  }
  if(bUppercase)
    sWomanName_RV = UpperString(sWomanName_RV);
  return sWomanName_RV;
}

CString WomanName_ZV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sWomanName_ZV, sFrom(Trim(szFrom)), sLeft1;
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)) {
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }
  iLen = sFrom.GetLength();
  sWomanName_ZV = sFrom;
  sLeft1 = sFrom.Left(iLen-1);

  switch(sFrom.Right(1)[0]){
    case '�':
      sWomanName_ZV = sLeft1 + _T("�");  break;
    case '�':
      sWomanName_ZV = sLeft1 + _T("�");  break;
  }
  if(bUppercase)
    sWomanName_ZV = UpperString(sWomanName_ZV);
  return sWomanName_ZV;
}

CString WomanFather_DV(LPCTSTR szFrom){

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sWomanFather_DV, sFrom(Trim(szFrom));
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)) {
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sWomanFather_DV = sFrom;
  
  if(W_as_na(sFrom))
    sWomanFather_DV = sFrom.Left(iLen - 1) + _T("�");
  if(bUppercase)
    sWomanFather_DV = UpperString(sWomanFather_DV);
  return sWomanFather_DV;
}

CString WomanFather_OV(LPCTSTR szFrom){

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sWomanFather_OV, sFrom(szFrom);
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)) {
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sWomanFather_OV = sFrom;

  if(W_as_na(sFrom))
    sWomanFather_OV = sFrom.Left(iLen - 1) + _T("��");
  if(bUppercase)
    sWomanFather_OV = UpperString(sWomanFather_OV);
  return sWomanFather_OV;
}

CString WomanFather_RV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sWomanFather_RV, sFrom(Trim(szFrom));
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)) {
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sWomanFather_RV = sFrom;

  if(W_as_na(sFrom))
    sWomanFather_RV = sFrom.Left(iLen - 1) + _T("�");
  if(bUppercase)
    sWomanFather_RV = UpperString(sWomanFather_RV);
  return sWomanFather_RV;
}

CString WomanFather_ZV(LPCTSTR szFrom) {

  if (szFrom==NULL || lstrlen(szFrom)<2)
    return szFrom;

  CString sWomanFather_ZV, sFrom(Trim(szFrom));
  int iLen;
  BOOL bUppercase(FALSE);

  if(IsCyrUpper(sFrom)) {
    bUppercase = TRUE;
    sFrom = MakeCanonicalName(sFrom);
  }

  iLen = sFrom.GetLength();
  sWomanFather_ZV = sFrom;

  if(W_as_na(sFrom))
    sWomanFather_ZV = sFrom.Left(iLen - 1) + _T("�");
  if(bUppercase)
    sWomanFather_ZV = UpperString(sWomanFather_ZV);
  return sWomanFather_ZV;
}


CString MakeUName(LPTSTR szName){
  return UpperString(szName);
}

CString NameC(LPCTSTR szSrc, WORD wID) {
  CString s = _T("");

  switch(wID) {
    case NC_MSURNAME_DV:  s = ManSurname_DV(szSrc);    break;
    case NC_MSURNAME_OV:  s = ManSurname_OV(szSrc);    break;
    case NC_MSURNAME_RV:  s = ManSurname_RV(szSrc);    break;
    case NC_MSURNAME_ZV:  s = ManSurname_ZV(szSrc);    break;

    case NC_MNAME_DV:      s = ManName_DV(szSrc);      break;
    case NC_MNAME_OV:      s = ManName_OV(szSrc);      break;
    case NC_MNAME_RV:      s = ManName_RV(szSrc);      break;
    case NC_MNAME_ZV:      s = ManName_ZV(szSrc);      break;

    case NC_MFATHER_DV:    s = ManFather_DV(szSrc);    break;
    case NC_MFATHER_OV:    s = ManFather_OV(szSrc);    break;
    case NC_MFATHER_RV:    s = ManFather_RV(szSrc);    break;
    case NC_MFATHER_ZV:    s = ManFather_ZV(szSrc);    break;

    case NC_WSURNAME_DV:  s = WomanSurname_DV(szSrc);  break;
    case NC_WSURNAME_OV:  s = WomanSurname_OV(szSrc);  break;
    case NC_WSURNAME_RV:  s = WomanSurname_RV(szSrc);  break;
    case NC_WSURNAME_ZV:  s = WomanSurname_ZV(szSrc);  break;

    case NC_WNAME_DV:      s = WomanName_DV(szSrc);    break;
    case NC_WNAME_OV:      s = WomanName_OV(szSrc);    break;
    case NC_WNAME_RV:      s = WomanName_RV(szSrc);    break;
    case NC_WNAME_ZV:      s = WomanName_ZV(szSrc);    break;

    case NC_WFATHER_DV:    s = WomanFather_DV(szSrc);  break;
    case NC_WFATHER_OV:    s = WomanFather_OV(szSrc);  break;
    case NC_WFATHER_RV:    s = WomanFather_RV(szSrc);  break;
    case NC_WFATHER_ZV:    s = WomanFather_ZV(szSrc);  break;
  }
  return s;
}


CString MakeFullName(const CString& sSurName, const CString& sName, const CString& sFather, BOOL fMale, SHORT nVid) {
  CString sRet;
  switch( nVid ) {
    case RC_NV:
      sRet.Format(_T("%s %s %s"), sSurName, sName, sFather);
      break;
    case RC_RV:
      if ( fMale )
        sRet.Format(_T("%s %s %s"), ManSurname_RV(sSurName), ManName_RV(sName), ManFather_RV(sFather));
      else
        sRet.Format(_T("%s %s %s"), WomanSurname_RV(sSurName), WomanName_RV(sName), WomanFather_RV(sFather));
      break;
    case RC_DV:
      if ( fMale )
        sRet.Format(_T("%s %s %s"), ManSurname_DV(sSurName), ManName_DV(sName), ManFather_DV(sFather));
      else
        sRet.Format(_T("%s %s %s"), WomanSurname_DV(sSurName), WomanName_DV(sName), WomanFather_DV(sFather));
      break;
    case RC_ZV:
      if ( fMale )
        sRet.Format(_T("%s %s %s"), ManSurname_ZV(sSurName), ManName_ZV(sName), ManFather_ZV(sFather));
      else
        sRet.Format(_T("%s %s %s"), WomanSurname_ZV(sSurName), WomanName_ZV(sName), WomanFather_ZV(sFather));
      break;
    case RC_OV:
      if ( fMale )
        sRet.Format(_T("%s %s %s"), ManSurname_OV(sSurName), ManName_OV(sName), ManFather_OV(sFather));
      else
        sRet.Format(_T("%s %s %s"), WomanSurname_OV(sSurName), WomanName_OV(sName), WomanFather_OV(sFather));
      break;
  }
  sRet.Replace(_T("  "), _T(" "));
  return sRet;
}

CString MakeFromFullName(const CString& sFullName, bool bSex) {
  CString sRet;
  CString sSurName, sName, sFather;

  sSurName = GetTok(sFullName, 0, _T(" ") );
  sName    = GetTok(sFullName, 1, _T(" ") );
  sFather  = GetTok(sFullName, 2, _T(" ") );

  if ( bSex )
    sRet.Format(_T("%s %s %s"), ManSurname_RV(sSurName), ManName_RV(sName), ManFather_RV(sFather) );
  else
    sRet.Format(_T("%s %s %s"), WomanSurname_RV(sSurName), WomanName_RV(sName), WomanFather_RV(sFather) );
  return sRet;
}
