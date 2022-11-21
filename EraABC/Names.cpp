#include "stdafx.h"
#include "EraABC.h"

#include "..\Common\CyrString.h"

#include "Names.h"


CString OfferSurname(LPCTSTR szSrc, BOOL bSexFrom, BOOL bSexTo) {
  CString sFrom = szSrc;
  CString sOffer = szSrc;
  int iLen = sFrom.GetLength();

  sOffer = sFrom;

  if ( TRUE==bSexFrom && FALSE==bSexTo ) {  // »сходна€ фамили€ - мужска€,
                                            // предложить женскую
    if ( sFrom.Right(4)==_T("ький") )
      sOffer = sFrom.Left(iLen - 2) + _T("а");
    else {
      CString sRight2 = sFrom.Right(2);
      if ( sRight2==_T("ой") || sRight2==_T("ий") )
        sOffer = sFrom.Left(iLen - 2) + _T("а");
      else if ( sRight2==_T("ов") || sRight2==_T("ин") || sRight2==_T("≥н") || sRight2==_T("Їв") || sRight2==_T("ев"))
        sOffer = sFrom + _T("а");
    }
  }
  else if( FALSE==bSexFrom && TRUE==bSexTo ) {
    CString sRight2 = sFrom.Right(2);
    CString sRight3 = sFrom.Right(3);
    if ( sRight3==_T("ова") || sRight3==_T("ина") ||
         sRight3==_T("≥на") || sRight3==_T("Їва") ||
         sRight3==_T("ева") )
      sOffer = sFrom.Left(iLen-1);
    else if ( sRight3==_T("на€") )
      sOffer = sFrom.Left(iLen - 2) + _T("ий");
    else if ( sRight3==_T("н€€") )
      sOffer = sFrom.Left(iLen - 2) + _T("≥й");
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
  if ( s.Find(_T("¬асил")==0) )
    s = _T("¬асиль");
  else if ( s.Find(_T("ƒанил")==0) )
    s = _T("ƒанило");
  else if ( s.Find(_T("ƒмитр")==0) )
    s = _T("ƒмитро");
  else if ( s.Find(_T("√аврил")==0) )
    s = _T("√аврило");
  else if ( s.Find(_T("≤зра≥")==0) )
    s = _T("≤зра≥ль");
  else if ( s.Find(_T("≤зрае")==0) )
    s = _T("≤зраель");
  else if ( s.Find(_T("≤ллар≥он")==0) )
    s = _T("≤ллар≥он");
  else if ( s.Find(_T("≤лл")==0) )
    s = _T("≤лл€");
  else if ( s.Find(_T(" ал≥н")==0) )
    s = _T(" ал≥на");
  else if ( s.Find(_T("ћикит")==0) )
    s = _T("ћикита");
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
// ‘ункции-конверторы мужских фамилий, имен и отчеств.
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
  else if(sRight3 == _T("Їць") )
    sManSurname_DV = sLeft3 + _T("йцю");
  else if(sRight2==_T("ов") || sRight2==_T("ев") || sRight2==_T("Їв") ||
          sRight2==_T("ин") || sRight2==_T("≥н") || sRight2==_T("њн") ||
          sRight2==_T("≥в") || sRight2==_T("њв") )
    sManSurname_DV = sFrom + _T("у");
  else if(sRight2==_T("ий") || sRight2==_T("ой") )
    sManSurname_DV = sLeft2 + _T("ому");
  else if(sRight2==_T("га")  )
    sManSurname_DV = sFrom.Left(iLen-2) + _T("з≥");
  else if(sRight2==_T("ча") || sRight2==_T("ша") || sRight2==_T("жа") )
    sManSurname_DV = sLeft1 + _T("≥");
  else if(sRight2==_T("ць") )
    sManSurname_DV = sFrom.Left(iLen - 4) + _T("цю");
  else if(sRight2==_T("≥й") ){
    if(sFrom.Right(3) == _T("н≥й") )
      sManSurname_DV = sLeft2 + _T("ьому");
    else
      sManSurname_DV = sLeft1 + _T("ю");
  }
  else{
    switch(sFrom.Right(1)[0]){
      case 'о':
        sManSurname_DV = sLeft1 + _T("у");  break;
      case 'а':
        sManSurname_DV = sLeft1 + "≥";  break;
      case 'ц': case 'к': case 'н': case 'г':
      case 'ш': case 'щ': case 'з': case 'х':
      case 'ф': case 'в': case 'п': case 'р':
      case 'л': case 'д': case 'ж': case 'ч':
      case 'с': case 'м': case 'т': case 'б':
        sManSurname_DV = sFrom + _T("у");
        break;
      case '€':
        sManSurname_DV = sLeft1 + _T("≥");
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
  else if(sRight3 == _T("Їць") )
    sManSurname_OV = sLeft3 + _T("йцем");
  if(sRight2==_T("ов") || sRight2==_T("ев") || sRight2==_T("Їв") ||
     sRight2==_T("ин") || sRight2==_T("≥н") || sRight2==_T("њн") ||
     sRight2==_T("≥в") || sRight2==_T("њв") )
    sManSurname_OV = sFrom + _T("им");
  else if(sRight2==_T("ий") )
    sManSurname_OV = sLeft2 + _T("им");
  else if(sRight2==_T("ой") )
    sManSurname_OV = sLeft1 + _T("Їм");
  else if(sRight2==_T("ча") || sRight2==_T("ша") || sRight2==_T("жа") )
    sManSurname_OV = sLeft1 + _T("ою");
  else if(sRight2==_T("ко") )
    sManSurname_OV = sFrom + _T("м");
  else if(sRight2==_T("≥б") || sRight2==_T("ук") || sRight2==_T("ак") || sRight2==_T("юк") || sRight2==_T("€к") )
    sManSurname_OV = sFrom + _T("ом");
  else if(sRight2==_T("≥й") ) {
     if(sFrom.Mid(iLen - 2, 1) == _T("н") )
       sManSurname_OV = sLeft1 + _T("≥м");
     else
       sManSurname_OV = sLeft1 + _T("Їм");
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
       case '€':
         sManSurname_OV = sLeft1 + _T("ею"); break;
       case 'й':
         sManSurname_OV = sLeft1 + _T("Їм"); break;
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
    sManSurname_RV = sLeft3 + _T("ц€");
  else if(sRight3 == _T("Їць") )
    sManSurname_RV = sLeft3 + _T("йц€");
  else if(sRight2==_T("ов") || sRight2==_T("ин") || sRight2==_T("≥н") ||
          sRight2==_T("њн") || sRight2==_T("Їв") || sRight2==_T("ев") ||
          sRight2==_T("≥в") || sRight2==_T("њв") )
    sManSurname_RV = sFrom + _T("а");
  else if(sRight2==_T("ий") || sRight2==_T("ой") )
    sManSurname_RV = sLeft2 + _T("ого") ;
  else if(sRight2==_T("ча") || sRight2==_T("ша") || sRight2==_T("жа") )
    sManSurname_RV = sLeft1 + _T("≥");
  else if(sRight2==_T("≥й") ){
    if(sFrom.Right(3) == _T("н≥й") )
      sManSurname_RV = sLeft2 + _T("ього");
    else
      sManSurname_RV = sLeft1 + _T("€");
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
      case '€':
        sManSurname_RV =  sLeft1 + _T("≥");  break;
      case 'й': case 'ь':
        sManSurname_RV =  sLeft1 + _T("€");  break;
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
    sManSurname_ZV = sLeft3 + _T("ц€");
  else if(sRight3 == _T("Їць") )
    sManSurname_ZV = sLeft3 + _T("йц€");
  else if(sRight2==_T("ов") || sRight2==_T("ин") || sRight2==_T("≥н") ||
          sRight2==_T("њн") || sRight2==_T("Їв") || sRight2==_T("ев") ||
          sRight2==_T("≥в") || sRight2==_T("њв") )
    sManSurname_ZV = sFrom + _T("а");
  else if(sRight1==_T("а") )
    sManSurname_ZV = sLeft1 + _T("у");
  else if(sRight2==_T("ий") || sRight2==_T("ой") )
    sManSurname_ZV = sLeft2 + _T("ого");
  else if(sRight2==_T("ць") )
    sManSurname_ZV = sFrom.Left(iLen - 4) + _T("ц€");
  else if(sRight2==_T("≥й") ){
    if(sRight3 == _T("н≥й") )
      sManSurname_ZV = sLeft2 + _T("ього");
    else
      sManSurname_ZV = sLeft1 + _T("€");
  }
  else{
    switch(sRight1[0]){
      case 'о':
        sManSurname_ZV = sLeft1 + _T("а");  break;
      case 'а':
        sManSurname_ZV = sLeft1 + _T("≥");  break;
      case 'ц': case 'к': case 'н': case 'г':
      case 'ш': case 'щ': case 'з': case 'х':
      case 'ф': case 'в': case 'п': case 'р':
      case 'л': case 'д': case 'ж': case 'ч':
      case 'с': case 'м': case 'т': case 'б':
        sManSurname_ZV = sFrom + _T("а");
        break;
      case '€':
        sManSurname_ZV = sLeft1 + _T("ю");
        break;
      case 'ь':
        sManSurname_ZV = sLeft1 + _T("€");
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
      sManName_DV = sLeft1 + _T("≥"); break;
    case 'о':
      sManName_DV = sLeft1 + _T("у"); break;
    case 'й':
      sManName_DV = sLeft1 + _T("ю"); break;
    case '€':
      switch(sFrom.Mid(iLen - 1, 1)[0]){
        case 'у': case 'е': case 'њ': case '≥':
        case 'а': case 'о': case 'Ї': case '\'':
        case '€': case 'и': case 'ю':
          sManName_DV = sLeft1 + _T("њ"); break;
        default:
          sManName_DV = sLeft1 + _T("≥"); break;
      }
      break;
    case 'р':
      if(sFrom==_T("≤гор") || sFrom==_T("Ћазар") )
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
    case 'й': sManName_OV = sLeft1 + _T("Їм");  break;
    case '€':
      switch(sFrom.Mid(iLen - 1, 1)[0]){
        case 'у': case 'е': case 'њ': case '≥':
        case 'а': case 'о': case 'Ї': case '\'':
        case '€': case 'и': case 'ю':
          sManName_OV = sLeft1 +  _T("Їю");
      }
      break;
    case 'р':
      sRight2 = sFrom.Right(2);
      if(sFrom == _T("‘ед≥р") )
        sManName_OV = _T("‘едором");
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
    case 'й': sManName_RV = sLeft1 + "€";  break;
    case '€':
      switch(sFrom.Mid(iLen - 1, 1)[0]){
        case 'у': case 'е': case 'њ': case '≥': case 'а': case 'о':
        case 'Ї': case '€': case 'и': case 'ю': case '\'':
          sManName_RV = sLeft1 + _T("њ");  break;
        default:
          sManName_RV = sLeft1 + _T("≥");  break;
      }
      break;
    case 'р':
      if (sFrom == _T("≤гор") || sFrom == _T("Ћазар") )
        sManName_RV = sFrom + _T("€");
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
    case 'й': sManName_ZV = sLeft1 + "€";  break;
    case '€':
        sManName_ZV = sLeft1 + _T("ю");  break;
      break;
    case 'р':
      if (sFrom == _T("≤гор") || sFrom == _T("Ћазар") )
        sManName_ZV = sFrom + _T("€");
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
// ‘ункции-ковертеры женских фамилий, имен и отчеств.
//
BOOL W_as_ova(CString& sFrom) {
BOOL bRet(FALSE);
CString sRight3;
int iLen = sFrom.GetLength();
  if(iLen>3){
    sRight3 = sFrom.Right(3);
    if(sRight3==_T("ала") || sRight3==_T("дка") || sRight3==_T("тка") ||
       sRight3==_T("ова") || sRight3==_T("ина") || sRight3==_T("≥на") ||
       sRight3==_T("њна") || sRight3==_T("рна") || sRight3==_T("Їва") ||
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

  if(W_as_ova(sFrom) || W_as_ska(sFrom))
    sWomanSurname_DV = sLeft1 + _T("≥й");
  else if(sFrom.Right(4)==_T("авка") )
    sWomanSurname_DV = sFrom.Left(iLen-2) + _T("ц≥");
  else if(sRight2==_T("га")  )
    sWomanSurname_DV = sFrom.Left(iLen-2) + _T("з≥");
  else if(sRight2==_T("ба") || sRight2==_T("ва") )
    sWomanSurname_DV = sLeft1 + _T("≥");
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
    sWomanSurname_OV = sLeft1 + _T("оњ");
  if(W_as_ova(sFrom) || sFrom.Right(4)==_T("авка") || sRight2==_T("ба") ||
     sRight2==_T("ва") || sRight2==_T("га") || sRight2==_T("ка") )
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
  else if(sRight2=="€€")
    sWomanSurname_RV = sFrom.Left(iLen-2) + _T("≥й");
  else if(sRight2==_T("л€") || sRight2==_T("ча") )
    sWomanSurname_RV = sLeft1 + _T("≥");
  else if(W_as_ova(sFrom))
    sWomanSurname_RV = sLeft1 + _T("оњ");
  else if(W_as_ura(sFrom))
    sWomanSurname_RV = sLeft1 + _T("и");
  else if(W_as_ska(sFrom))
    sWomanSurname_RV = sLeft1 + _T("оњ");

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
  else if(sRight2==_T("€€") )
    sWomanSurname_ZV = sFrom.Left(iLen-2) + _T("юю");
  else if(sRight2==_T("л€") )
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

  if(sFrom==_T("ќльга") )
    sWomanName_DV = _T("ќльз≥") ;
  else if(sFrom==_T("Ћюбов") )
    sWomanName_DV = _T("Ћюбов≥") ;
  else if(sFrom==_T("ѕалажка") )
    sWomanName_DV = _T("ѕалажц≥");
  else if(sFrom==_T("—олоха") )
    sWomanName_DV = _T("—олос≥") ;
  else {
    switch(sFrom.Right(1)[0]) {
      case 'а': case 'ь':
        sWomanName_DV = sLeft1 + _T("≥"); break;
      case '€':
        switch(sFrom.Right(2)[0]){
          case 'у': case 'е': case 'њ': case '≥': case 'а':  case 'о':
          case 'Ї': case '€': case 'и':  case 'ю': case '\'': 
            sWomanName_DV = sLeft1 + _T("њ");  break;
          default:
            sWomanName_DV = sLeft1 + _T("≥");  break;
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

  if(sFrom==_T("Ћюбов") )
    sWomanName_OV = _T("Ћюбов'ю");
  else{
    switch(sFrom.Right(1)[0]){
      case 'а':
        sWomanName_OV = sLeft1 + _T("ою");  break;
      case 'ь':
        sWomanName_OV = sLeft1 +  _T("ю");  break;
      case '€':
        switch(sFrom.Mid(iLen - 1, 1)[0]){
          case 'у': case 'е': case 'њ': case '≥': case 'а':  case 'о':
          case 'Ї': case '€': case 'и':  case 'ю': case '\'': 
            sWomanName_OV = sLeft1 +  _T("Їю");  break;
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

  if(sFrom==_T("ќльга") )
    sWomanName_RV = _T("ќльз≥");
  else if(sFrom==_T("Ћюбов") )
    sWomanName_RV  = _T("Ћюбов≥");
  else {
    switch(sFrom.Right(1)[0]) {
      case 'а':
        sWomanName_RV = sLeft1 + _T("и");  break;
      case 'ь':
        sWomanName_RV = sLeft1 + _T("≥");  break;
      case '€':
        switch(sFrom.Right(2)[0]){
          case 'у': case 'е': case 'њ': case '≥': case 'а':  case 'о':
          case 'Ї': case '€': case 'и':  case 'ю': case '\'': 
            sWomanName_RV = sLeft1 + _T("њ");  break;
          default:
            sWomanName_RV = sLeft1 + _T("≥");  break;
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
    case '€':
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
    sWomanFather_DV = sFrom.Left(iLen - 1) + _T("≥");
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
