//
// Monthes.cpp
//
#include "stdafx.h"
#include "..\Common\Monthes.h"

LPCTSTR  g_aszUkrMonthes[] =
 { _T("січня"), _T("лютого"),   _T("березня"),
   _T("квітня"),_T("травня"),   _T("червня"),
   _T("липня"), _T("серпня"),   _T("вересня"),
   _T("жовтня"),_T("листопада"),_T("грудня") };

LPCTSTR GetMonth(int nIndex) {
  if( nIndex > 0 && nIndex < 13 )
    return g_aszUkrMonthes[nIndex-1];
  return _T("");
}