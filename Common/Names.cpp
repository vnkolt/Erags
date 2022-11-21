#include "stdafx.h"

#include "CyrString.h"
#include "Names.h"
#include "..\Controls\EraControls.h"


CString OfferSurname(LPCTSTR szSrc, BOOL bSexFrom, BOOL bSexTo) {
  CString sFrom = szSrc;
  CString sOffer = szSrc;
  int iLen = sFrom.GetLength();

  sOffer = sFrom;

  if ( TRUE==bSexFrom && FALSE==bSexTo ) {  // Исходная фамилия - мужская,
                                            // предложить женскую
    if ( sFrom.Right(4)==_T("ький") )
      sOffer = sFrom.Left(iLen - 2) + _T("а");
    else {
      CString sRight2 = sFrom.Right(2);
      if ( sRight2==_T("ой") || sRight2==_T("ий") )
        sOffer = sFrom.Left(iLen - 2) + _T("а");
      else if ( sRight2==_T("ов") || sRight2==_T("ин") || sRight2==_T("ін") || sRight2==_T("єв") || sRight2==_T("ев") || sRight2==_T("їв"))
        sOffer = sFrom + _T("а");
    }
  }
  else if( FALSE==bSexFrom && TRUE==bSexTo ) {
    CString sRight2 = sFrom.Right(2);
    CString sRight3 = sFrom.Right(3);
    if ( sRight3==_T("ова") || sRight3==_T("ина") ||
         sRight3==_T("іна") || sRight3==_T("єва") ||
         sRight3==_T("ева") )
      sOffer = sFrom.Left(iLen-1);
    else if ( sRight3==_T("ная") )
      sOffer = sFrom.Left(iLen - 2) + _T("ий");
    else if ( sRight3==_T("няя") )
      sOffer = sFrom.Left(iLen - 2) + _T("ій");
    else if ( sFrom.Right(2)==_T("ма") )
      ;
    else if ( sFrom.Right(1)==_T("а") )
      sOffer = sFrom.Left(iLen - 1) + _T("ий");
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
  if ( s.Find(_T("Васил")==0) )
    s = _T("Василь");
  else if ( s.Find(_T("Данил")==0) )
    s = _T("Данило");
  else if ( s.Find(_T("Дмитр")==0) )
    s = _T("Дмитро");
  else if ( s.Find(_T("Гаврил")==0) )
    s = _T("Гаврило");
  else if ( s.Find(_T("Ізраі")==0) )
    s = _T("Ізраіль");
  else if ( s.Find(_T("Ізрае")==0) )
    s = _T("Ізраель");
  else if ( s.Find(_T("Ілларіон")==0) )
    s = _T("Ілларіон");
  else if ( s.Find(_T("Ілл")==0) )
    s = _T("Ілля");
  else if ( s.Find(_T("Калін")==0) )
    s = _T("Каліна");
  else if ( s.Find(_T("Микит")==0) )
    s = _T("Микита");
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
CString PASCAL MakeFIO(CString& sSurname, CString& sName, CString& sFather){
CString sMakeFIO;
  sMakeFIO = sSurname;
  sMakeFIO += " " + sName;
  sMakeFIO += " " + sFather;
  sMakeFIO.Replace(_T("  "), _T(" "));
  sMakeFIO = Trim(sMakeFIO);
  return sMakeFIO;
}

CString PASCAL MakeFIO(LPCTSTR szSurname, LPCTSTR szName, LPCTSTR szFather){
CString sSurname(szSurname), sName(szName), sFather(szFather);
  return MakeFIO(sSurname, sName, sFather);
}

CString PASCAL MakeFIO(CEraNameEdit* pSurname, CEraNameComboBox* pName, CEraNameComboBox* pPatronymic) {
  CString sSurname, sName, sPatronymic;
  pSurname->GetWindowText(sSurname);
  sName = pName->GetCurText();
  sPatronymic = pPatronymic->GetCurText();
  return MakeFIO(sSurname, sName, sPatronymic);
}
///////////////////////////////////////////////////////
// Функции-конверторы мужских фамилий, имен и отчеств.
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

  if(sRight3 == _T("ець") )
    sManSurname_DV = sLeft3 + _T("цю");
  else if(sRight3 == _T("єць") )
    sManSurname_DV = sLeft3 + _T("йцю");
  else if(sRight2==_T("ов") || sRight2==_T("ев") || sRight2==_T("єв") ||
          sRight2==_T("ин") || sRight2==_T("ін") || sRight2==_T("їн") ||
          sRight2==_T("ів") || sRight2==_T("їв") )
    sManSurname_DV = sFrom + _T("у");
  else if(sRight2==_T("ий") || sRight2==_T("ой") )
    sManSurname_DV = sLeft2 + _T("ому");
  else if(sRight2==_T("га")  )
    sManSurname_DV = sFrom.Left(iLen-2) + _T("зі");
  else if(sRight2==_T("ча") || sRight2==_T("ша") || sRight2==_T("жа") )
    sManSurname_DV = sLeft1 + _T("і");
  else if(sRight2==_T("ць") )
    sManSurname_DV = sFrom.Left(iLen - 4) + _T("цю");
  else if(sRight2==_T("ій") ){
    if(sFrom.Right(3) == _T("ній") )
      sManSurname_DV = sLeft2 + _T("ьому");
    else
      sManSurname_DV = sLeft1 + _T("ю");
  }
  else{
    switch(sFrom.Right(1)[0]){
      case 'о':
        sManSurname_DV = sLeft1 + _T("у");  break;
      case 'а':
        sManSurname_DV = sLeft1 + "і";  break;
      case 'ц': case 'к': case 'н': case 'г':
      case 'ш': case 'щ': case 'з': case 'х':
      case 'ф': case 'в': case 'п': case 'р':
      case 'л': case 'д': case 'ж': case 'ч':
      case 'с': case 'м': case 'т': case 'б':
        sManSurname_DV = sFrom + _T("у");
        break;
      case 'я':
        sManSurname_DV = sLeft1 + _T("і");
        break;
      case 'ь':
        sManSurname_DV = sLeft1 + _T("ю");
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

  
  if(sRight3 == _T("ець") )
    sManSurname_OV = sLeft3 + _T("цем");
  else if(sRight3 == _T("єць") )
    sManSurname_OV = sLeft3 + _T("йцем");
  if(sRight2==_T("ов") || sRight2==_T("ев") || sRight2==_T("єв") ||
     sRight2==_T("ин") || sRight2==_T("ін") || sRight2==_T("їн") ||
     sRight2==_T("ів") || sRight2==_T("їв") )
    sManSurname_OV = sFrom + _T("им");
  else if(sRight2==_T("ий") )
    sManSurname_OV = sLeft2 + _T("им");
  else if(sRight2==_T("ой") )
    sManSurname_OV = sLeft1 + _T("єм");
  else if(sRight2==_T("ча") || sRight2==_T("ша") || sRight2==_T("жа") )
    sManSurname_OV = sLeft1 + _T("ою");
  else if(sRight2==_T("ко") )
    sManSurname_OV = sFrom + _T("м");
  else if(sRight2==_T("іб") || sRight2==_T("ук") || sRight2==_T("ак") || sRight2==_T("юк") || sRight2==_T("як") )
    sManSurname_OV = sFrom + _T("ом");
  else if(sRight2==_T("ій") ) {
     if(sFrom.Mid(iLen - 2, 1) == _T("н") )
       sManSurname_OV = sLeft1 + _T("ім");
     else
       sManSurname_OV = sLeft1 + _T("єм");
   }
   else {
     switch(sFrom.Right(1)[0]) {
       case  'о': case 'а':
         sManSurname_OV = sLeft1 + _T("ою"); break;
       case 'ц': case 'к': case 'н': case 'г': case 'ш':
       case 'щ': case 'з': case 'х': case 'ф': case 'в':
       case 'п': case 'р': case 'л': case 'д': case 'ж':
       case 'ч': case 'с': case 'м': case 'т': case 'б':
         sManSurname_OV = sFrom + _T("ом");  break;
       case 'я':
         sManSurname_OV = sLeft1 + _T("ею"); break;
       case 'й':
         sManSurname_OV = sLeft1 + _T("єм"); break;
       case 'ь':
         sManSurname_OV = sLeft1 + _T("ем"); break;
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

  
  if(sRight3 == _T("ець") )
    sManSurname_RV = sLeft3 + _T("ця");
  else if(sRight3 == _T("єць") )
    sManSurname_RV = sLeft3 + _T("йця");
  else if(sRight2==_T("ов") || sRight2==_T("ин") || sRight2==_T("ін") ||
          sRight2==_T("їн") || sRight2==_T("єв") || sRight2==_T("ев") ||
          sRight2==_T("ів") || sRight2==_T("їв") )
    sManSurname_RV = sFrom + _T("а");
  else if(sRight2==_T("ий") || sRight2==_T("ой") )
    sManSurname_RV = sLeft2 + _T("ого") ;
  else if(sRight2==_T("ча") || sRight2==_T("ша") || sRight2==_T("жа") )
    sManSurname_RV = sLeft1 + _T("і");
  else if(sRight2==_T("ій") ){
    if(sFrom.Right(3) == _T("ній") )
      sManSurname_RV = sLeft2 + _T("ього");
    else
      sManSurname_RV = sLeft1 + _T("я");
  }
  else{
    switch(sFrom.Right(1)[0]){
      case 'о':
        sManSurname_RV = sLeft1 + _T("а"); break;
      case 'а':
        sManSurname_RV = sLeft1 + _T("и"); break;
      case 'ц': case 'к': case 'н': case 'г': case 'ш':
      case 'щ': case 'з': case 'х': case 'ф': case 'в':
      case 'п': case 'р': case 'л': case 'д': case 'ж':
      case 'ч': case 'с': case 'м': case 'т': case 'б':
        sManSurname_RV =  sFrom + _T("а"); break;
      case 'я':
        sManSurname_RV =  sLeft1 + _T("і");  break;
      case 'й': case 'ь':
        sManSurname_RV =  sLeft1 + _T("я");  break;
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
  
  if(sRight3 == _T("ець") )
    sManSurname_ZV = sLeft3 + _T("ця");
  else if(sRight3 == _T("єць") )
    sManSurname_ZV = sLeft3 + _T("йця");
  else if(sRight2==_T("ов") || sRight2==_T("ин") || sRight2==_T("ін") ||
          sRight2==_T("їн") || sRight2==_T("єв") || sRight2==_T("ев") ||
          sRight2==_T("ів") || sRight2==_T("їв") )
    sManSurname_ZV = sFrom + _T("а");
  else if(sRight1==_T("а") )
    sManSurname_ZV = sLeft1 + _T("у");
  else if(sRight2==_T("ий") || sRight2==_T("ой") )
    sManSurname_ZV = sLeft2 + _T("ого");
  else if(sRight2==_T("ць") )
    sManSurname_ZV = sFrom.Left(iLen - 4) + _T("ця");
  else if(sRight2==_T("ій") ){
    if(sRight3 == _T("ній") )
      sManSurname_ZV = sLeft2 + _T("ього");
    else
      sManSurname_ZV = sLeft1 + _T("я");
  }
  else{
    switch(sRight1[0]){
      case 'о':
        sManSurname_ZV = sLeft1 + _T("а");  break;
      case 'а':
        sManSurname_ZV = sLeft1 + _T("і");  break;
      case 'ц': case 'к': case 'н': case 'г':
      case 'ш': case 'щ': case 'з': case 'х':
      case 'ф': case 'в': case 'п': case 'р':
      case 'л': case 'д': case 'ж': case 'ч':
      case 'с': case 'м': case 'т': case 'б':
        sManSurname_ZV = sFrom + _T("а");
        break;
      case 'я':
        sManSurname_ZV = sLeft1 + _T("ю");
        break;
      case 'ь':
        sManSurname_ZV = sLeft1 + _T("я");
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
    case 'а':
      sManName_DV = sLeft1 + _T("і"); break;
    case 'о':
      sManName_DV = sLeft1 + _T("у"); break;
    case 'й':
      sManName_DV = sLeft1 + _T("ю"); break;
    case 'я':
      switch(sFrom.Mid(iLen - 1, 1)[0]){
        case 'у': case 'е': case 'ї': case 'і':
        case 'а': case 'о': case 'є': case '\'':
        case 'я': case 'и': case 'ю':
          sManName_DV = sLeft1 + _T("ї"); break;
        default:
          sManName_DV = sLeft1 + _T("і"); break;
      }
      break;
    case 'р':
      if(sFrom==_T("Ігор") || sFrom==_T("Лазар") )
        sManName_DV = sFrom + "ю";
      else
        sManName_DV = sFrom + "у";
      break;
    case 'ь':
      sManName_DV = sLeft1 + _T("ю");
      break;
    case 'ц': case 'к': case 'н': case 'г': case 'ш':
    case 'щ': case 'з': case 'х': case 'ф': case 'в':
    case 'п': case 'л':  case 'д': case 'ж': case 'ч':
    case 'с': case 'м': case 'т':  case 'б':
      sManName_DV = sFrom + _T("у");
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
    case 'а':  sManName_OV = sLeft1 + _T("ою");  break;
    case 'о': sManName_OV = sFrom + _T("м");    break;
    case 'й': sManName_OV = sLeft1 + _T("єм");  break;
    case 'я':
      switch(sFrom.Mid(iLen - 1, 1)[0]){
        case 'у': case 'е': case 'ї': case 'і':
        case 'а': case 'о': case 'є': case '\'':
        case 'я': case 'и': case 'ю':
          sManName_OV = sLeft1 +  _T("єю");
      }
      break;
    case 'р':
      sRight2 = sFrom.Right(2);
      if(sFrom == _T("Федір") )
        sManName_OV = _T("Федором");
      else
        sManName_OV = sFrom + _T("ом");
      break;
    case 'м': case 'н': case 'к': case 'г': case 'ш': case 'щ':
    case 'з': case 'х': case 'ф': case 'в': case 'п': case 'л':
    case 'д': case 'ч': case 'с': case 'т': case 'б': case 'ь':
      sManName_OV  = sFrom + _T("ом");
      break;
    case 'ц': case 'ж':
      sManName_OV  = sFrom + _T("ем");
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
    case 'а': sManName_RV = sLeft1 + "и";  break;
    case 'о': sManName_RV = sLeft1 + "а";  break;
    case 'й': sManName_RV = sLeft1 + "я";  break;
    case 'я':
      switch(sFrom.Mid(iLen - 1, 1)[0]){
        case 'у': case 'е': case 'ї': case 'і': case 'а': case 'о':
        case 'є': case 'я': case 'и': case 'ю': case '\'':
          sManName_RV = sLeft1 + _T("ї");  break;
        default:
          sManName_RV = sLeft1 + _T("і");  break;
      }
      break;
    case 'р':
      if (sFrom == _T("Ігор") || sFrom == _T("Лазар") )
        sManName_RV = sFrom + _T("я");
      else
        sManName_RV = sFrom + _T("а");
      break;
    case 'ц': case 'к': case 'н': case 'г': case 'ш':
    case 'щ': case 'з': case 'х': case 'ф': case 'в':
    case 'п': case 'л':  case 'д': case 'ж': case 'ч':
    case 'с': case 'м': case 'т':  case 'б':
      sManName_RV = sFrom + _T("а");
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
    case 'а': sManName_ZV = sLeft1 + "у";  break;
    case 'о': sManName_ZV = sLeft1 + "а";  break;
    case 'й': sManName_ZV = sLeft1 + "я";  break;
    case 'я':
        sManName_ZV = sLeft1 + _T("ю");  break;
      break;
    case 'р':
      if (sFrom == _T("Ігор") || sFrom == _T("Лазар") )
        sManName_ZV = sFrom + _T("я");
      else
        sManName_ZV = sFrom + _T("а");
      break;
    case 'ц': case 'к': case 'н': case 'г': case 'ш':
    case 'щ': case 'з': case 'х': case 'ф': case 'в':
    case 'п': case 'л':  case 'д': case 'ж': case 'ч':
    case 'с': case 'м': case 'т':  case 'б':
      sManName_ZV = sFrom + _T("а");
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
  if(sFrom.Right(1) == _T("ч") )
    sManFather_DV = sFrom + _T("у");
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
  if(sFrom.Right(1) == _T("ч") )
    sManFather_OV = sFrom + _T("ем");
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
  if(sFrom.Right(1) == _T("ч") )
    sManFather_RV = sFrom + _T("а");
  if(bUppercase)
    sManFather_RV = UpperString(sManFather_RV);
  return sManFather_RV;
}

CString ManFather_ZV(LPCTSTR szFrom) {
  return ManFather_RV(szFrom);
}

///////////////////////////////////////////////////////
// Функции-ковертеры женских фамилий, имен и отчеств.
//
BOOL W_as_ova(CString& sFrom) {
BOOL bRet(FALSE);
CString sRight3;
int iLen = sFrom.GetLength();
  if(iLen>3){
    sRight3 = sFrom.Right(3);
    if(sRight3==_T("ала") || sRight3==_T("дка") || sRight3==_T("тка") ||
       sRight3==_T("ова") || sRight3==_T("ина") || sRight3==_T("іна") ||
       sRight3==_T("їна") || sRight3==_T("рна") || sRight3==_T("єва") ||
       sRight3==_T("ева") || sRight3==_T("жна") || sRight3==_T("чна") ||
       sRight3==_T("шна") )
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
    if(sRight4==_T("ська") || sRight4==_T("зька") || sRight4==_T("цька") )
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
    if(sRight2==_T("да") || sRight2==_T("ра") || sRight2==_T("ха") ||
       sRight2==_T("ма") || sRight2==_T("ла") )
      bRet = TRUE;
  }
  return bRet;
}

BOOL W_as_na(CString& sFrom) {
BOOL bRet(FALSE);
int iLen = sFrom.GetLength();
  if(iLen>2){
    if(sFrom.Right(2)==_T("на") )
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

  if(W_as_ova(sFrom) || W_as_ska(sFrom) || sRight2==_T("на") )
    sWomanSurname_DV = sLeft1 + _T("ій");
  else if(sFrom.Right(4)==_T("авка") )
    sWomanSurname_DV = sFrom.Left(iLen-2) + _T("ці");
  else if(sRight2==_T("га")  )
    sWomanSurname_DV = sFrom.Left(iLen-2) + _T("зі");
  else if(sRight2==_T("ба") || sRight2==_T("ва") )
    sWomanSurname_DV = sLeft1 + _T("і");
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
    sWomanSurname_OV = sLeft1 + _T("ої");
  if(W_as_ova(sFrom) || sFrom.Right(4)==_T("авка") || sRight2==_T("ба") ||
     sRight2==_T("ва") || sRight2==_T("га") || sRight2==_T("ка") || sRight2==_T("на") )
    sWomanSurname_OV = sLeft1 + _T("ою");
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

  if(sRight2==_T("ша") )
    sWomanSurname_RV = sLeft1 + _T("и");
  else if(sRight2=="яя")
    sWomanSurname_RV = sFrom.Left(iLen-2) + _T("ій");
  else if(sRight2==_T("ля") || sRight2==_T("ча") )
    sWomanSurname_RV = sLeft1 + _T("і");
  else if(W_as_ova(sFrom))
    sWomanSurname_RV = sLeft1 + _T("ої");
  else if(W_as_ura(sFrom))
    sWomanSurname_RV = sLeft1 + _T("и");
  else if(W_as_ska(sFrom))
    sWomanSurname_RV = sLeft1 + _T("ої");

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
     sRight2==_T("ша") || sRight2==_T("ча") )
    sWomanSurname_ZV = sLeft1 + _T("у");
  else if(sRight2==_T("яя") )
    sWomanSurname_ZV = sFrom.Left(iLen-2) + _T("юю");
  else if(sRight2==_T("ля") )
    sWomanSurname_ZV = sLeft1 + _T("ю");
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

  if(sFrom==_T("Ольга") )
    sWomanName_DV = _T("Ользі") ;
  else if(sFrom==_T("Любов") )
    sWomanName_DV = _T("Любові") ;
  else if(sFrom==_T("Палажка") )
    sWomanName_DV = _T("Палажці");
  else if(sFrom==_T("Солоха") )
    sWomanName_DV = _T("Солосі") ;
  else {
    switch(sFrom.Right(1)[0]) {
      case 'а': case 'ь':
        sWomanName_DV = sLeft1 + _T("і"); break;
      case 'я':
        switch(sFrom.Right(2)[0]){
          case 'у': case 'е': case 'ї': case 'і': case 'а':  case 'о':
          case 'є': case 'я': case 'и':  case 'ю': case '\'': 
            sWomanName_DV = sLeft1 + _T("ї");  break;
          default:
            sWomanName_DV = sLeft1 + _T("і");  break;
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

  if(sFrom==_T("Любов") )
    sWomanName_OV = _T("Любов'ю");
  else{
    switch(sFrom.Right(1)[0]){
      case 'а':
        sWomanName_OV = sLeft1 + _T("ою");  break;
      case 'ь':
        sWomanName_OV = sLeft1 +  _T("ю");  break;
      case 'я':
        switch(sFrom.Mid(iLen - 1, 1)[0]){
          case 'у': case 'е': case 'ї': case 'і': case 'а':  case 'о':
          case 'є': case 'я': case 'и':  case 'ю': case '\'': 
            sWomanName_OV = sLeft1 +  _T("єю");  break;
          default:
            sWomanName_OV = sLeft1 +  _T("ею");  break;
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

  if(sFrom==_T("Ольга") )
    sWomanName_RV = _T("Ользі");
  else if(sFrom==_T("Любов") )
    sWomanName_RV  = _T("Любові");
  else {
    switch(sFrom.Right(1)[0]) {
      case 'а':
        sWomanName_RV = sLeft1 + _T("и");  break;
      case 'ь':
        sWomanName_RV = sLeft1 + _T("і");  break;
      case 'я':
        switch(sFrom.Right(2)[0]){
          case 'у': case 'е': case 'ї': case 'і': case 'а':  case 'о':
          case 'є': case 'я': case 'и':  case 'ю': case '\'': 
            sWomanName_RV = sLeft1 + _T("ї");  break;
          default:
            sWomanName_RV = sLeft1 + _T("і");  break;
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
    case 'а':
      sWomanName_ZV = sLeft1 + _T("у");  break;
    case 'я':
      sWomanName_ZV = sLeft1 + _T("ю");  break;
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
    sWomanFather_DV = sFrom.Left(iLen - 1) + _T("і");
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
    sWomanFather_OV = sFrom.Left(iLen - 1) + _T("ою");
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
    sWomanFather_RV = sFrom.Left(iLen - 1) + _T("и");
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
    sWomanFather_ZV = sFrom.Left(iLen - 1) + _T("у");
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

BOOL GetMaleOrFemale(LPCTSTR szPIB) {
  CString s = Trim(szPIB);
  if ( s.Right(2)==_T("ни") || s.Right(2)==_T("на") ) 
    return FALSE;
  return TRUE;
}

void GetCanonicalPIB(LPCTSTR szPIB, CString& szSurname, CString& szName, CString& szPatronymic, BOOL fMale) {
  szSurname.Format(_T("%s "), GetTok(szPIB, 0, _T(" ")) );
  szName.Format(_T("%s "), GetTok(szPIB, 1, _T(" ")) );
  szPatronymic.Format(_T("%s "), GetTok(szPIB, 2, _T(" ")) );
  if ( fMale ) {
    if ( szSurname.Right(4)==_T("ова ") )
      szSurname.Replace(_T("ова "), _T("ов"));
    else if ( szSurname.Right(4)==_T("ого ") )
      szSurname.Replace(_T("ого "), _T("ий"));
    else if ( szSurname.Right(4)==_T("ина ") )
      szSurname.Replace(_T("ина "), _T("ин"));
    else if ( szSurname.Right(4)==_T("іна ") )
      szSurname.Replace(_T("іна "), _T("ін"));
    else if ( szSurname.Right(4)==_T("ука ") )
      szSurname.Replace(_T("ука "), _T("ук"));
    else if ( szSurname.Right(4)==_T("юка ") )
      szSurname.Replace(_T("юка "), _T("юк"));
    else if ( szSurname.Right(4)==_T("яка ") )
      szSurname.Replace(_T("яка "), _T("як"));
    else if ( szSurname.Right(3)==_T("ка ") )
      szSurname.Replace(_T("ка "), _T("ко"));
    else if ( szSurname.Right(3)==_T("ла ") )
      szSurname.Replace(_T("ла "), _T("ло"));

    if ( szName==_T("Петра ") )
      szName = _T("Петро");
    else if ( szName==_T("Марка ") )
      szName = _T("Марк");
    else if ( szName.Right(2)==_T("и ") )
      szName.Replace(_T("и "), _T("а"));
    else if ( szName.Right(3)==_T("ая ") )
      szName.Replace(_T("ая "), _T("ай"));
    else if ( szName.Right(3)==_T("ра ")   )
      szName.Replace(_T("ра "), _T("р"));
    else if ( szName.Right(3)==_T("ря ")   )
      szName.Replace(_T("ря "), _T("р"));

    if ( szPatronymic.Right(3)==_T("ча ") )
      szPatronymic.Replace(_T("ча "), _T("ч"));
  }
  else {
    if ( szSurname.Right(3)==_T("ої ") )
      szSurname.Replace(_T("ої "), _T("а"));

    if ( szName.Right(3)==_T("зі ") )
      szName.Replace(_T("зі "), _T("га"));
    else if ( szName.Right(3)==_T("ві ") )
      szName.Replace(_T("ві "), _T("в"));
    else if ( szName.Right(2)==_T("и ") )
      szName.Replace(_T("и "), _T("а"));
    else if ( szName.Right(2)==_T("ї ") )
      szName.Replace(_T("ї "), _T("я"));

    if ( szPatronymic.Right(3)==_T("ни ") )
      szPatronymic.Replace(_T("ни "), _T("на"));
  }
  szSurname.TrimRight();
  szName.TrimRight();
  szPatronymic.TrimRight();
}