//
// Monthes.cpp
//
#include "stdafx.h"
#include "..\Common\Monthes.h"

LPCTSTR  g_aszUkrMonthes[] =
 { _T("����"), _T("������"),   _T("�������"),
   _T("�����"),_T("������"),   _T("������"),
   _T("�����"), _T("������"),   _T("�������"),
   _T("������"),_T("���������"),_T("������") };

LPCTSTR GetMonth(int nIndex) {
  if( nIndex > 0 && nIndex < 13 )
    return g_aszUkrMonthes[nIndex-1];
  return _T("");
}