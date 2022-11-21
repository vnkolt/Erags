//
// ExtNotice.cpp
//
#include "stdafx.h"
#include "Erags.h"
#include "ExtNotice.h"

#include "..\Common\CyrString.h"
#include "..\Common\MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void SetChangedBy(CDaoRecordset* pRS, CString& szExtNotice) {
  if ( false==pRS->IsFieldDirty(NULL) ) {
    return;
  }
  CString s;
  SYSTEMTIME st;
  GetLocalTime(&st);
  s.Format(_T("%02d:%02d:%02d %02d.%02d.%04d"),
           st.wHour, st.wMinute, st.wSecond,
           st.wDay, st.wMonth, st.wYear);
  MakeBracketString(szExtNotice, _T("Змінено:"), s);
  if ( false==theApp.m_szUser.IsEmpty() ) {
    MakeBracketString(szExtNotice, _T("Спеціаліст:"), theApp.m_szUser);
    MakeBracketString(szExtNotice, _T("Посада:"), theApp.m_szPost);
  }
}

CString GetSpecPost(CDaoRecordset* pRS) {
  return GetBracketString(GetFieldString(pRS, _T("EXTNOTES")), _T("Посада:"));
}
CString GetSpecName(CDaoRecordset* pRS) {
  return GetBracketString(GetFieldString(pRS, _T("EXTNOTES")), _T("Спеціаліст:"));
}
