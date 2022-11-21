//
// RTFCnv.cpp
//
#include "stdafx.h"
#include "Erags.h"

#include "..\Common\CyrString.h"
#include "..\Common\MDB.h"
#include "..\Common\Monthes.h"

#include "Caches.h"
#include "Geography.h"
#include "DataManager.h"
#include "DateFunc.h"
#include "Defaults.h"
#include "Dlg43.h"
#include "BirthDlgs.h"
#include "ElectDlg.h"
#include "ExtNotice.h"

#include "rsBirthes.h"
#include "rsMarriages.h"
#include "rsDivorces.h"
#include "rsDeathes.h"
#include "rsChanges.h"
#include "NoteChange.h"
#include "RegDlg.h"
#include "RNames.h"
#include "RTFCnv.h"
#include "LogThread.h"

#include "Keywords.h"
#include "xCnv.h"

#include "..\Common\Elections.h"
#include "..\Common\FHelpers.h"
#include "..\Common\Names.h"

#include "..\ImpExp\ImpExpDll.h"

#include "..\Controls\ProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define O_BRACKET TCHAR('{')
#define C_BRACKET TCHAR('}')
#define KEY_CHAR  TCHAR('!')

#define MAKELCID_UKR  MAKELCID(MAKELANGID(LANG_UKRAINIAN, SUBLANG_DEFAULT), SORT_DEFAULT)

struct FindStrItem {
  LPCTSTR szCyr1;
  LPCTSTR szEng;
  LPCTSTR szCyr2;
};

struct GetStrItem {
  FindStrItem strB;
  FindStrItem strE;
};


/*
LPCTSTR g_szTitle       = _T("!Title!");
LPCTSTR g_szEndTitle    = _T("!EndTitle!");
LPCTSTR g_szTable       = _T("!Table!");
LPCTSTR g_szEndTable    = _T("!EndTable!");
LPCTSTR g_szFootnote    = _T("!Footnote!");
LPCTSTR g_szEndFootnote = _T("!EndFootnote!");
*/

LPCTSTR g_szNewString = _T("{\\par }");
LPCTSTR g_szNewPage   = _T("{\\par \\page \\par }");
LPCTSTR g_szEmpty     = _T("");

CString g_sTmpBoss;
CString g_szMR_1, g_szMR_2, g_szMR_3;
CString g_szOR_1, g_szOR_2, g_szOR_3;
COleDateTime g_DateCert;
COleVariant ov_DeathBM; // bookmark for CRSDeathes recordset
BOOL        g_fSecondCert = false; // повторное свидетельство
BOOL        g_fStrikeOut  = false; // Прочерк, якщо дата або місце народження не змінилися
BOOL        g_fMakeXLS    = false;
BOOL        g_fMakeDBF    = false;
CString     g_szVBScript;
CString     g_szDBFile;

BOOL        g_fEmptyDash  = false;

CString g_sMSurname_OV, g_sWSurname_OV;
CString g_sMName_OV, g_sWName_OV;
CString g_sMPatronymic_OV, g_sWPatronymic_OV;
CString g_SurnameTo, g_NameTo, g_PatronymicTo;
CString g_RagsTo, g_RagsWhere;
BOOL    g_fDivorceDocSex = TRUE;

CString  g_szSurname_RV, g_szName_RV, g_szPatronymic_RV;

// for Marriage_38.7.7.rtf
CString  g_szSurnameM_RV, g_szNameM_RV, g_szPatronymicM_RV;
CString  g_szSurnameW_RV, g_szNameW_RV, g_szPatronymicW_RV;
CString  g_szNewSurnameM, g_szNewSurnameW;
CString  g_szRagsMarriage, g_szRagsDivorce;
CString  g_MarriageNum, g_DivorceNum;
COleDateTime g_MarriageDR, g_DivorceDR;

CString  g_szSurname_DV, g_szName_DV, g_szPatronymic_DV;
CString  g_szChanges, g_szChangeAct, g_szChangeDate, g_szChangeNumber;

CString g_Declarant;
CString g_ChangeAddr;
CString g_ChangePrImPb, g_ChangePrImPbRV;
CString g_OldPrImPb, g_NewPrImPb;
CString g_DVisn, g_DDozv, g_NVisn, g_NDozv;
BOOL    g_fNewSurnamesABC  = TRUE;
BOOL    g_fNewPageForLetter = TRUE;
BOOL    g_fAdoption = FALSE;

COleCurrency  g_ocZero(0, 0);

PRINTDOCTYPE g_nDocType       = DOCTYPE_UNKNOWN;
UINT         g_nPrintCitizen  = 0;

int g_nTotalRecs  = 0;
int g_nTotalPages = 0;

extern COleDateTime  g_RegDate;
extern SHORT         g_iMonth;
extern COleDateTime  g_odtFrom;
extern COleDateTime  g_odtTill;
extern DWORD         g_dwPrintBlanks;

extern CString g_Dlg08_sNumber, g_sFullBabyNameRV, g_Dlg08_sWhere;

CString g_TableBody;

class CMargins {
  public:
    int   m_paperw, m_paperh;
    int   m_margl, m_margt, m_margr, m_margb;
    void  Init() {
      m_paperw = 12240;
      m_paperh = 15840;
      m_margl = m_margr = 1800;
      m_margt = m_margb = 1440;
    }
    int Calc(LPCTSTR szMargin) {
      const char* p = szMargin;
      while( *p && !IsDigit(*p) ) p++;
      if ( IsDigit(*p) )
        return atoi(p);
      return 0;
    }
    void SetW(LPCTSTR szMargin) { m_paperw = Calc(szMargin); }
    void SetH(LPCTSTR szMargin) { m_paperh = Calc(szMargin); }
    void SetL(LPCTSTR szMargin) { m_margl = Calc(szMargin);  }
    void SetT(LPCTSTR szMargin) { m_margt = Calc(szMargin);  }
    void SetR(LPCTSTR szMargin) { m_margr = Calc(szMargin);  }
    void SetB(LPCTSTR szMargin) { m_margb = Calc(szMargin);  }
    void FindMargin(const CString& sMargin);
};

void CMargins::FindMargin(const CString& sMargin) {
  if ( !sMargin.IsEmpty() ) {
    if ( sMargin.Find("paperw") > -1 ) {
      SetW(sMargin);
    }
    else if ( sMargin.Find("paperh") > -1 ) {
      SetH(sMargin);
    }
    else if ( sMargin.Find("margl") > -1 ) {
      SetL(sMargin);
    }
    else if ( sMargin.Find("margt") > -1 ) {
      SetT(sMargin);
    }
    else if ( sMargin.Find("margr") > -1 ) {
      SetR(sMargin);
    }
    else if ( sMargin.Find("margb") > -1 ) {
      SetB(sMargin);
    }
  }
}

CMargins  theMargins;

void OnDocShell(LPCTSTR szFilename, BOOL fExport) {
  if ( fExport ) {
    CString s;
    if ( theApp.IsMsOffice() && false==theApp.m_szMSWordPath.IsEmpty() ) {
      // AfxMessageBox(theApp.m_szMSWordPath);
      s.Format(_T("\"%s\" \"%s\""), theApp.m_szMSWordPath, szFilename);
      // AfxMessageBox(s);
    }
    else if ( false==theApp.m_szOOWriterPath.IsEmpty() ) {
      // AfxMessageBox(theApp.m_szOOWriterPath);
      s.Format(_T("\"%s\" \"%s\""), theApp.m_szOOWriterPath, szFilename);
      // AfxMessageBox(s);
    }
    if ( false==s.IsEmpty() ) {
      // AfxMessageBox("WinExec(s, SW_SHOW)");
      WinExec(s, SW_SHOW);
    }
    else {
      // AfxMessageBox("ShellExecute(NULL, \"open\", szFilename, NULL, NULL, SW_SHOW)");
      ShellExecute(NULL, "open", szFilename, NULL, NULL, SW_SHOW);
    }
  }
  else {
    if ( theApp.IsMsOffice() ) {
      theApp.m_pWordTemplate->CloseAllDocuments(false);
      theApp.m_pWordTemplate->OpenDocumentFile(szFilename);
    }
    else {
      theApp.m_pOOTemplate->CloseAllDocuments(false);
      theApp.m_pOOTemplate->OpenDocumentFile(szFilename);
    }
  }
}

CString ReplaceEOL(LPCTSTR sz) {
  CString s(sz);
  if ( CNV_RTF==g_ConvertType ) {
    s.Replace(_T("\r\n"), _T("\\par\r\n"));
  }
/*
  else {
    s.Replace(_T("\r\n"), _T("<text:p text:style-name=\"P6\"/>\r\n"));
  }
*/
  return s;
}

BOOL IsValidDateReg(COleDateTime& DateReg) {
  if ( DateReg.GetStatus()!=COleDateTime::valid ) 
    return FALSE;
  if ( (DATE)DateReg==(DATE)0)
    return FALSE;
  if ( DateReg.GetYear()==theDataManager.m_Year )
    return TRUE;
  return FALSE;
}

CString UkrMonth(COleDateTime& odt) {
  CString s;
  if ( odt.GetStatus()==COleDateTime::valid ) {
    s.LoadString(IDS_UM01+odt.GetMonth()-1);
    s = LowerString(s);
  }
  return s;
}

BOOL DecJanFeb() {
  if ( g_odtFrom.GetMonth()==12 && g_odtFrom.GetDay()==1     &&
       g_odtTill.GetMonth()==2  && LastDayInMonth(g_odtTill) &&
       g_odtFrom.GetYear() == g_odtTill.GetYear()-1          &&
       g_odtTill.GetYear()==COleDateTime::GetCurrentTime().GetYear()
     )
  {
    return true;
  }
  return false;
}
BOOL MarAprMay() {
  if ( g_odtFrom.GetMonth()==3 && g_odtFrom.GetDay()==1  &&
       g_odtTill.GetMonth()==5 && g_odtTill.GetDay()==31 &&
       g_odtFrom.GetYear() == g_odtTill.GetYear()        &&
       g_odtTill.GetYear()==COleDateTime::GetCurrentTime().GetYear()
     )
  {
    return true;
  }
  return false;
}
BOOL JunJulAug() {
  if ( g_odtFrom.GetMonth()==6 && g_odtFrom.GetDay()==1  &&
       g_odtTill.GetMonth()==8 && g_odtTill.GetDay()==31 &&
       g_odtFrom.GetYear() == g_odtTill.GetYear()        &&
       g_odtTill.GetYear()==COleDateTime::GetCurrentTime().GetYear()
     )
  {
    return true;
  }
  return false;
}

BOOL SepOctNov() {
  if ( g_odtFrom.GetMonth()==9 && g_odtFrom.GetDay()==1  &&
       g_odtTill.GetMonth()==1 && g_odtTill.GetDay()==30 &&
       g_odtFrom.GetYear() == g_odtTill.GetYear()        &&
       g_odtTill.GetYear()==COleDateTime::GetCurrentTime().GetYear()
     )
  {
    return true;
  }
  return false;
}

CString GetPeriod() {
  CString s;
  if ( DecJanFeb() ) {
    s = _T("грудень попереднього року, січень та лютий поточного року");
  }
  else if ( MarAprMay() ) {
    s = _T("березень, квітень, травень поточного року");
  }
  else if ( JunJulAug() ) {
    s = _T("червень, липень, серпень поточного року");
  }
  else if ( SepOctNov() ) {
    s = _T("вересень, жовтень, листопад поточного року");
  }
  else if ( g_odtFrom.GetDay()==1 &&
            g_odtFrom.GetMonth()==g_odtTill.GetMonth() && 
            g_odtFrom.GetYear()==g_odtTill.GetYear() &&
            LastDayInMonth(g_odtTill) ) { // the same year, the same month, from 1 to LDM
    s.Format(_T("%s %04d р."), UkrMonth(g_odtFrom), g_odtFrom.GetYear());
  }
  else if ( g_odtFrom.GetYear()==g_odtTill.GetYear() ) {
    s.Format(_T("перід з \\'93%02d\\'94 %s до \\'93%02d\\'94 %s %04d р."),
                g_odtFrom.GetDay(), GetMonth(g_odtFrom.GetMonth()),
                g_odtTill.GetDay(), GetMonth(g_odtTill.GetMonth()),
                g_odtFrom.GetYear());
  }
  else {
    s.Format(_T("перід з %02d.%02d.%04d р. до %02d.%02d.%04d р."),
                g_odtFrom.GetDay(), g_odtFrom.GetMonth(), g_odtFrom.GetYear(),
                g_odtTill.GetDay(), g_odtTill.GetMonth(), g_odtTill.GetYear()
             );
  }
  return s;
}
/************************************** : by VK at 28.05.2004 21:49:54 **\
ГРН = ((uah).m_cur).int64/10000
КОП = (((uah).m_cur).int64%10000)/100
\************************************** : by VK at 28.05.2004 21:49:56 **/
CString UAH(COleCurrency& uah) {
  CString s;
  if ( COleCurrency::valid==uah.GetStatus() ) {
    s.Format(_T("%d,%02d"), (int)uah.m_cur.int64/10000, (int)(uah.m_cur.int64%10000)/100);
  }
  return s;
}

CString DDMMMRRRRR(CDaoRecordset* pSet, LPCTSTR lpszFldName, const CString sDDMMMRRRRR) {
  CString s = GetFieldDate(pSet, lpszFldName, true);
  CString sKey = sDDMMMRRRRR;
  sKey.Replace(_T("ДДМММРРРР"), _T("") );
  s += sKey;
  return s;
}

CString DDMMRRRRR(CDaoRecordset* pSet, LPCTSTR lpszFldName, const CString sDDMMRRRRR) {
  CString s = GetFieldDate(pSet, lpszFldName, false);
  CString sKey = sDDMMRRRRR;
  sKey.Replace(_T("ДДММРРРР"), _T("") );
  s += sKey;
  return s;
}

CString MakeUnderline(LPCTSTR sz) {
  CString s;
  if ( CNV_RTF==g_ConvertType ) { // RTF
    s.Format(_T("{\\ul %s}"), sz);
  }
  else {
    s.Format(_T("<text:span text:style-name=\"Underline\">%s</text:span>"), sz);
  }
  return s;
}

CString TypeOfCity(LPCTSTR szCity) {
  CString sCity = Trim(szCity), sRet;
  if (  sCity.Right(3)==_T(" м.") || sCity.Right(2)==_T(" м") || sCity.Right(6)==_T(" місто") )
    sRet = _T("місто");
  else if (  sCity.Right(4)==_T(" слщ") || sCity.Right(5)==_T(" с-ще") || sCity.Right(5)==_T(" смт.") || sCity.Right(4)==_T(" смт") || sCity.Right(7)==_T(" селище") )
    sRet = _T("селище");
  else if ( sCity.Right(2)==_T(" с") || sCity.Right(3)==_T(" с.") || sCity.Right(5)==_T(" село") )
    sRet = _T("село");
  else if ( sCity.Right(2)==_T(" х") || sCity.Right(3)==_T(" х.") || sCity.Right(4)==_T(" х-р") || sCity.Right(6)==_T(" хутір") )
    sRet = _T("хутір");
  else if (  sCity.Right(4)==_T(" ст.") || sCity.Right(7)==_T(" ст-ція") || sCity.Right(5)==_T(" с-ція") || sCity.Right(8)==_T(" станція") )
    sRet = _T("станція");
  else if ( sCity.Right(5)==_T(" с-ця") || sCity.Right(6)==_T(" ст-ця") || sCity.Right(8)==_T(" станиця") )
    sRet = _T("станиця");

  if ( DOCTYPE_ACT == g_nDocType && theIniCache.GetCityUnderline() ) {
    CString szAllTypes  = _T("місто, селище, (село)");
    CString szUnderline = MakeUnderline(sRet);
    szAllTypes.Replace(sRet, szUnderline);
    sRet = szAllTypes;
  }
  return sRet;
}
CString GetCity(LPCTSTR szCity, bool fTypeCity/*=false*/) {

  CString sCity = Trim(szCity);
  CString sType = TypeOfCity(sCity);
  int trimLen = 0;
  if ( !sType.IsEmpty() ) {
    trimLen = sCity.ReverseFind(' ');
  }
  if ( fTypeCity ) return sCity.Right(sCity.GetLength()-trimLen);
  return sCity.Mid(0, trimLen);
}

LPCTSTR TypeOfStreet(LPCTSTR szStreet, CString& szTok) {
  if ( NULL==szStreet || 0==szStreet[0] ) {
    return _T("");
  }
  CString szType = _T("вулиця");
  int nTok = 0;
  CString sTok = GetTok(szStreet, nTok, " .");
  while ( !sTok.IsEmpty() ) {
    if (  0==DBCompare(sTok,_T("бульвар")) || 0==DBCompare(sTok,_T("бул")) || 0==DBCompare(sTok,_T("б-р")) )    { // бульвар
      szTok = sTok;
      return _T("бульвар");
    }    // бульвар
    else if ( 0==DBCompare(sTok,_T("вул")) || 0==DBCompare(sTok,_T("вулиця")) ) { // вулиця
      szTok = sTok;
      return _T("вулиця");
    }
    else if ( 0==DBCompare(sTok,_T("к-л")) || 0==DBCompare(sTok,_T("кв")) || 0==DBCompare(sTok,_T("кв-л")) || 0==DBCompare(sTok,_T("квартал")) ) { // квартал
      szTok = sTok;
      return _T("квартал");
    }
    else if ( 0==DBCompare(sTok,_T("пс")) || 0==DBCompare(sTok,_T("пр")) || 0==DBCompare(sTok,_T("пр-т")) || 0==DBCompare(sTok,_T("прос")) || 0==DBCompare(sTok,_T("просп")) || 0==DBCompare(sTok,_T("проспект")) ) {                    // проспект
      szTok = sTok;
      return _T("проспект");
    }
    else if ( 0==DBCompare(sTok,_T("прошп")) || 0==DBCompare(sTok,_T("прошпект")) ) { // прошпект
      szTok = sTok;
      return _T("прошпект");
    }
    else if ( 0==DBCompare(sTok,_T("пров")) || 0==DBCompare(sTok,_T("п-к")) || 0==DBCompare(sTok,_T("провулок")) ) { // провулок
      szTok = sTok;
      return _T("провулок");
    }
    else if ( 0==DBCompare(sTok,_T("пeр")) || 0==DBCompare(sTok,_T("перевул")) || 0==DBCompare(sTok,_T("перевулок")) )  { // перевулок
      szTok = sTok;
      return _T("перевулок");
    }
    else if ( 0==DBCompare(sTok,_T("пр-д")) || 0==DBCompare(sTok,_T("пр-зд")) || 0==DBCompare(sTok,_T("проїзд")) ) {    // проїзд
      szTok = sTok;
      return _T("проїзд");
    }
    else if ( 0==DBCompare(sTok,_T("пл")) || 0==DBCompare(sTok,_T("площа")) ) {       // площа
      szTok = sTok;
      return _T("площа");
    }
    else if ( 0==DBCompare(sTok,_T("кут")) || 0==DBCompare(sTok,_T("куток")) ) {      // куток
      szTok = sTok;
      return _T("куток");
    }
    sTok = GetTok(szStreet, ++nTok, " .");
  }
  return _T("вулиця");
}


void ParseBuilding(const CString& szHouse, CString& szBuilding, CString& szSect) {
  CString sHouse = szHouse;
  sHouse.TrimLeft(); sHouse.TrimRight();
  CStringArray tokens;
  tokens.Add( GetTok(sHouse, 0, ",\\/") );
  tokens.Add( GetTok(sHouse, 1, ",\\/") );

  if ( tokens.GetAt(1).IsEmpty() ) {
    szBuilding = szHouse;
    szSect.Empty();
  }
  else {
    for( int i(0); i < 2; i++ ) {
      static LPCSTR szKeys[] = { "блок",   "бл",  "б-к",
                                 "корпус", "кор", "крп",  "к-c",
                                 "секція", "сек", "скт",  "с-я",
                                 NULL 
                               };
      CString sTok = tokens[i];
      for ( int j(0); szKeys[j]; j++ ) {
        if ( sTok.Find(szKeys[j]) >= 0 ) {
          if ( 0==i ) {
            szSect     = tokens[0];
            szBuilding = tokens[1];
          }
          else {
            szBuilding = tokens[0];
            szSect     = tokens[1];
          }
          return;
        }
      }
    }
    szBuilding = tokens[0];
    szSect     = tokens[1];
  }
}

CString PassportName(BYTE bType, BOOL bShortName) {
  CString sRet;
  switch(bType) {
    case 1:
      sRet = bShortName ? _T("ЗЗП") : _T("загальногромадянський закардонний паспорт");
      break;
    case 2:
      sRet = bShortName ? _T("СН") : _T("свідоцтво про народження");
      break;
    case 3:
      sRet = bShortName ? _T("ТПП") : _T("тимчасова посвідка на проживання");
      break;
    default:
      sRet = _T("паспорт");
  }
  return sRet;
}

CString PassportNameBy(BYTE bType) {
  CString sRet;
  switch(bType) {
    case 1:
      sRet = _T("загальногромадянського закардонного паспорта");
      break;
    case 2:
      sRet = _T("свідоцтва про народження");
      break;
    case 3:
      sRet = _T("тимчасової посвідки на проживання");
      break;
    default:
      sRet = _T("паспорта");
  }
  return sRet;
}

/* before 23.01.2011
CString GetPassport(BYTE bType, const CString& sSeria, const CString& sNumber, const COleDateTime& odtDate, const CString& sBy) {
  CString sRet;
  if ( !sNumber.IsEmpty() ) {
    sRet = PassportName(bType, false);
    sRet += ' ';
    sRet += Trim(sSeria);
    if ( sNumber != _T("0") ) {
      sRet += _T(" № "); sRet += sNumber; sRet += _T(" видан");
      switch(bType) {
        case 2: sRet += _T("е"); break;
        case 3: sRet += _T("а"); break;
        default: sRet += _T("ий"); break;
      }
    }
    if ( COleDateTime::valid == odtDate.GetStatus() ) {
      CString sDate = GetDateDDMMMYYYYroku(odtDate);
      sRet += ' ';
      sRet += sDate;
    }
    if ( !sBy.IsEmpty() ) {
      sRet += ' ';
      sRet += sBy;
    }
  }
  return sRet;
}
*/

// after 23.01.2011
CString GetPassport(BYTE bType, const CString& sSeria, const CString& sNumber, const COleDateTime& odtDate, const CString& sBy) {
  CString sRet;
  if ( !sNumber.IsEmpty() ) {
    sRet = PassportName(bType, false);
    sRet += ' ';
    sRet += Trim(sSeria);
    if ( sNumber != _T("0") ) {
      sRet += ' ';
      sRet += sNumber;
      /*
      switch(bType) {
        case 2: sRet += _T("е"); break;
        case 3: sRet += _T("а"); break;
        default: sRet += _T("ий"); break;
      }
      */
    }
    if ( !sBy.IsEmpty() ) {
      sRet += _T(", ");
      sRet += sBy;
    }
    if ( COleDateTime::valid == odtDate.GetStatus() ) {
      CString sDate = GetDateDDMMYYYYr(odtDate, true);
      sRet += ' ';
      sRet += sDate;
    }
  }
  return sRet;
}


CString ByCount(BYTE bCount) {
 CString s;
 const char* szCnt[] = 
 {"перша", "друга", "третя", "четверта", "п'ята", "шоста", "сьома",
  "восьма", "дев'ята", "десятя", "одинадцятя", "дванадцята", "тринадцята",
  "чотирнадцята", "п'ятнадцята", "шістнадцята",  "сімнадцята",
  "вісімнадцята", "дев'ятнадцята", "двадцята" };
  if (0 < bCount && bCount < 21 )
    s = szCnt[bCount-1];
  else {
    if ( bCount < 100 )
      s.Format(_T("%d-а"), bCount );
  }
  return s;
}

CString GetNKids(BYTE nKids) {
  CString s;
  switch(nKids) {
    case 1:  s = _T("одне");      break;
    case 2:  s = _T("двоє");      break;
    case 3:  s = _T("троє");      break;
    case 4:  s = _T("четверо");   break;
    case 5:  s = _T("п'ятеро");   break;
    case 6:  s = _T("шестеро");   break;
    case 7:  s = _T("семеро");    break;
    case 8:  s = _T("восьмеро");  break;
    case 9:  s = _T("дев'ятеро"); break;
    case 10: s = _T("деcятеро");  break;
    default: s.Format(_T("%d"), nKids); break;
  }
  return s;
}

CString MedSv(CRSBirthes* pSet) {
  CString sMedSv, s;
  if ( false==pSet->m_MEDICAL_CERTIFICATE_BY.IsEmpty() ) {
    if ( pSet->m_ALIVE_FLAG ) {
      sMedSv = theIniCache.GetMDN();
    }
    else {
      sMedSv = _T("Свідоцтво про перинатальну смерть ");
    }
    if ( !IsEmptyText(pSet->m_MEDICAL_CERTIFICATE_NUMBER) ) {
      s.Format(_T(" № %s "), Trim(pSet->m_MEDICAL_CERTIFICATE_NUMBER) );
      sMedSv += s;
    }
    if ( COleDateTime::valid==pSet->m_MEDICAL_CERTIFICATE_DATE.GetStatus() ) {
      s.Format(_T(" від %s"), GetDateDDMMYYYYr(pSet->m_MEDICAL_CERTIFICATE_DATE) );
      sMedSv += s;
    }
    if ( sMedSv.Find(_T("овідка")) >= 0 )
      sMedSv += _T(" видана ");
    else
      sMedSv += _T(" видане ");
    sMedSv += pSet->m_MEDICAL_CERTIFICATE_BY;

    sMedSv = Trim(sMedSv);
    if ( !sMedSv.IsEmpty() )
      sMedSv += '.';
  }

  return sMedSv;
}

CString GetBirthDoc(CRSBirthes* pSet) {
  CString s, s10, sMedSv;
  s10 = GetBracketString(pSet->m_EXTNOTES, _T("Г10:") );
  if ( !s10.IsEmpty() )
    s = Trim(s10);
  else {
    s = MedSv(pSet);
  }
  return s;
}

CString GetDeathDoc(CRSDeathes* pSet) {
  CString sRet;
  CString sDocType = Trim(pSet->m_MEDICAL_CERT_TYPE);
  if ( sDocType==_T("Рішення суду") ) {
    CString sFound;
    int nFound = pSet->m_NOTICE.Find(_T("{РС:"));
    if ( nFound > -1 )
      sFound = _T("{РС:");
    else {
      nFound = pSet->m_NOTICE.Find(_T("{ГР11:"));
      if ( nFound > -1 )
        sFound = _T("{ГР11:");
    }
    if ( !sFound.IsEmpty() ) {
      sRet = GetBracketString(pSet->m_NOTICE, sFound);
    }
  }
  else {
    sRet.Format(_T("%s № %s від %s, %s"),
                pSet->m_MEDICAL_CERT_TYPE, pSet->m_MEDICAL_CERT_NUMBER,
                GetDateDDMMYYYYr(pSet->m_MEDICAL_CERT_DATE, true), pSet->m_MEDICAL_CERT_BY);
    sRet.Replace(_T("№ №"), _T("№"));
  }
  return sRet;
}

CString GetFatherSource(CRSBirthes* pSet) {
  CString s, s17, sEnd;
  switch(pSet->m_SOURCE_TYPE) {
    case BIRTH_TYPE_ACT:
      s17 = _T("Актовий запис про шлюб");
      sEnd = SVRagsC(pSet->m_SOURCE_BY, RC_OV);
      break;
    case BIRTH_TYPE_MOTHER:
      s17 = _T("Заява матері");
      break;
    case BIRTH_TYPE_PARENTS:
      s17 = _T("Заява батьків");
      break;
    case BIRTH_TYPE_APPL:
      s17 = _T("");//_T("Заява");
      break;
    case BIRTH_TYPE_APPLNUM:
      s17 = _T("Заява №");
      break;
    case BIRTH_TYPE_AFFILIATION1:
      s17 = _T("Заява батька про визнання батьківства");
      break;
    case BIRTH_TYPE_AFFILIATION2:
      s17 = _T("Спільна заява батьків про визнання батьківства");
      break;
  }
  if ( !IsEmptyText(pSet->m_SOURCE_NDOC) ) {
    s17.TrimRight('№');
    s.Format(_T(" № %s"), pSet->m_SOURCE_NDOC);
    s17 += s;
  }
  if ( COleDateTime::valid==pSet->m_SOURCE_DATE.GetStatus() ) {
    s.Format(_T(" від %s"), GetDateDDMMYYYYr( pSet->m_SOURCE_DATE ) );
    s17 += s;
  }
  if ( !sEnd.IsEmpty() ) {
    s17 += _T(" складений ");
    s17 += sEnd;
  }
  return s17;
}

LPCTSTR GetFamilyStatus(BYTE bStatus, BOOL fSex) {
  switch(bStatus) {
    case 1: return fSex ? _T("розлучений") : _T("розлучена");
    case 2: return fSex ? _T("вдівець")    : _T("вдова");
  }
  return fSex ? _T("у шлюбі не перебував") : _T("у шлюбі не перебувала");
}

CString GetFamilyStatusUnderline(BYTE bStatus, BOOL fSex) {
  static LPCTSTR aszStatusM[3] = { _T("у шлюбі не перебував,") , _T("вдівець,"), _T("розлучений") };
  static LPCTSTR aszStatusW[3] = { _T("у шлюбі не перебувала,"), _T("вдова,")  , _T("розлучена")  };
  static BYTE states[3]        = { 0, 2, 1 };
  CString s;
  for( int i(0); i < 3; i++ ) {
    LPCTSTR sz = fSex ? aszStatusM[i] : aszStatusW[i];
    if ( bStatus==states[i] ) {
      s += MakeUnderline(sz);
    }
    else {
      s += sz;
    }
    if ( i < 2 ) {
      s += _T("  ");
    }
  }
  return s;
}


CString GetState(BOOL fSex, BYTE bStatus, short Number, const COleDateTime& odt, LPCTSTR szBy) {
  CString s;
  if ( COleDateTime::valid==odt.GetStatus() ) {
    switch ( bStatus ) {
      case 1:
        s.Format(_T(" Актовий запис про розірвання шлюбу № %d від %02d.%02d.%04d р. складений %s. "),
                 Number, odt.GetDay(), odt.GetMonth(), odt.GetYear(), SVRagsC(szBy, RC_OV));
        break;
      case 2:
        s.Format(_T(" Актовий запис про смерть № %d від %02d.%02d.%04d р. складений %s. "),
                 Number, odt.GetDay(), odt.GetMonth(), odt.GetYear(), SVRagsC(szBy, RC_OV));
        break;
    }
  }
  if ( false==s.IsEmpty() ) {
    s.Insert(0, fSex ? _T("Наречений:") : _T("Наречена:"));
  }
  return s;
}

CString GetDate(COleDateTime odt, const CString& sMemField, LPCTSTR szCheckStr) {
  CString s, sFullBS;
  sFullBS = GetFullBracketString(sMemField, szCheckStr);
  if ( !sFullBS.IsEmpty() ) { // Yes, it's special date string
    s = GetBracketString(sMemField, szCheckStr);
  }
  else {
    if ( COleDateTime::valid==odt.GetStatus() && odt.m_dt != (DATE)NULL)
      s.Format(_T("%02d %s %04d року"), odt.GetDay(), GetMonth(odt.GetMonth()), odt.GetYear() );
  }
  return s;
}

CString GetCitizenship(BOOL bSex, const CString& szCitizenship, BOOL& bFirst) {
  CString s;
  bFirst = true;
  if ( szCitizenship.Find("без громадянства")>=0 ) {
    s = szCitizenship;
  }
  else {
    CString sValue = Trim(theCitizenships.GetValue(szCitizenship));
    if ( FALSE==sValue.IsEmpty() ) { // found in Citizenship cache
      ; // bFirst = false;
    }
    else {
      sValue = szCitizenship;
    }
    if ( !sValue.IsEmpty() ) {
      if ( IsCyrChar(sValue.GetAt(0)) ) {
        if ( 0==g_nPrintCitizen ) {
          s = sValue;
        }
        else {
          BOOL fPrint = FALSE;
          switch (g_nDocType ) {
            case DOCTYPE_ACT:   if ( g_nPrintCitizen & PRINT_CITIZENSHIP_ACT  ) fPrint = TRUE; break;
            case DOCTYPE_CERT:  if ( g_nPrintCitizen & PRINT_CITIZENSHIP_CERT ) fPrint = TRUE; break;
            case DOCTYPE_OTHER: if ( g_nPrintCitizen & PRINT_CITIZENSHIP_OTHER) fPrint = TRUE; break;
          }
          if ( fPrint )
	          s.Format(_T("громадян%s %s"), bSex ? _T("ин") : _T("ка"), sValue);
          else
            s = sValue;
        }
      }
      else
        s = sValue;
    }
  }
  return s;
}

CString GetRegion(const CString& sRegion, bool fShort) {
  CString s = sRegion;
  if ( s.Right(3)==_T("ька") )
    s += fShort ? _T(" обл.") : _T(" область");
  else if ( s.Right(3)==_T("кий") )
    s += fShort ? _T(" кр.") : _T(" край");
  return s;
}

CString GetDistrict(const CString& sDistrict, bool fShort) {
  CString s = sDistrict;
  if ( s.Right(2)==_T("ий") )
    s += fShort ? _T(" р-н") : _T(" район");
  return s;
}

CString GetBirthPlaceForDivorce(CRSDivorces* pSet, BOOL fMale) {
  CString s;
  CString sCnt = GetFieldString(pSet, fMale ? _T("MBIRTH_COUNTRY")  : _T("WBIRTH_COUNTRY") ),
          sRgn = GetFieldString(pSet, fMale ? _T("MBIRTH_REGION")   : _T("WBIRTH_REGION") ),
          sDst = GetFieldString(pSet, fMale ? _T("MBIRTH_DISTRICT") : _T("WBIRTH_DISTRICT") ),
          sCty = GetFieldString(pSet, fMale ? _T("MBIRTH_CITY")     : _T("WBIRTH_CITY") );

  if ( false==sCnt.IsEmpty() || false==sRgn.IsEmpty() || false==sDst.IsEmpty() || false==sCty.IsEmpty() ) {
    s.Format(_T("Місце народження: %s"), GetPlace(sCnt, sRgn, sDst, sCty, false));
  }
  return s;
}

CString GetCash(COleCurrency& dMNew, COleCurrency& dMOld) {
  CString s;
  if ( COleCurrency::valid==dMOld.GetStatus() && dMOld > g_ocZero &&
       COleCurrency::valid==dMNew.GetStatus() && dMNew  > g_ocZero ) {
    s.Format(_T("сплачено %s грн."), dMNew.Format(LOCALE_NOUSEROVERRIDE) );
  }
  return s;
}

bool GetBoolFreeUp(COleCurrency& dMNew) {
  if ( COleCurrency::valid==dMNew.GetStatus() && dMNew==g_ocZero )
    return true;
  return false;
}

CString GetFreeUp(BOOL bSex, COleCurrency& dMNew) {
  CString s;
  if ( COleCurrency::valid==dMNew.GetStatus() && dMNew==g_ocZero )
    s.Format(_T("від сплати держмита звільнен%s"), bSex ? _T("ий") : _T("а") );
  return s;
}
CString GetTax(BOOL bSex, BYTE	bMoneyType, COleCurrency& dMNew, COleCurrency& dMOld, bool bFree) {
  CString s, sMoneyType;
  if ( GetBoolFreeUp(dMNew) )
    return s;
  switch (bMoneyType) {
    case 1:     sMoneyType = _T("крб.");  break;
    case 2:     sMoneyType = _T("р.");    break;
    case 0:
    default:    sMoneyType = _T("грн.");  break;
  }
  if ( COleCurrency::null==dMNew.GetStatus() ) {
    if ( COleCurrency::valid==dMOld.GetStatus() && dMOld > g_ocZero && sMoneyType != _T("грн.") )
      s.Format(_T("%s %s"), UAH(dMOld), sMoneyType);
  }
  else {
/************************************** : by VK at 03.02.2004 4:36:36 **\
    if ( SumScript() ) {
      GetTax = MoneyS(String(1024, 0), 1024, CCur(dMoney))
    }
    else
\************************************** : by VK at 03.02.2004 4:36:46 **/
    s.Format(_T("%s грн."), UAH(dMNew) );
    if ( COleCurrency::valid==dMOld.GetStatus() && dMOld > g_ocZero && sMoneyType != _T("грн.") ) {
      s.Format(_T("%s %s"), UAH(dMOld), sMoneyType);
    }

  }
  return s;
}

BOOL IsSlyVyconcom(FILE* fIn) {
  BOOL fRet = false;
  TCHAR* szRada = _T(" \\'f0\\'e0\\'e4\\'e0");
  TCHAR* szRadu = _T(" \\'f0\\'e0\\'e4\\'e8");
  long lSize = 0;
  fseek(fIn, 0, SEEK_END);
  lSize = ftell(fIn);
  fseek(fIn, 0, SEEK_SET);
  TCHAR* lpBuf = new TCHAR[lSize+1];
  fread(lpBuf, 1, lSize, fIn);
  lpBuf[0] = 0;
  if ( strstr(lpBuf, szRadu)==0 || strstr(lpBuf, szRada)==0 ) {
    fRet = true;
  }
  delete lpBuf;
  return fRet;
}

CString EncodeRTFKey(LPCTSTR szRTFKey) {
  CString s;
  CString sHexChar;
  while ( *szRTFKey ) {
    if ( strncmp(szRTFKey, "\\\'",2)==0 ) {
      szRTFKey += 2;
      if ( isalnum(*szRTFKey) ) {
        int byte(0);
        sHexChar  = *szRTFKey++;
        sHexChar += *szRTFKey++;
        sscanf(sHexChar, "%x", &byte);
        s += (TCHAR)byte;
        continue;
      }
    }
    if ( *szRTFKey != KEY_CHAR && *szRTFKey != '\n' && *szRTFKey != '\r')
      s += *szRTFKey;
    szRTFKey++;
  }
  return s;
}

int GetSpaces(CString& sKey) {
  CString spaces;
  int trim = 0;
  while( true ) {
    TCHAR c = sKey.GetAt(trim);
    if ( IsDigit(c) || ' '==c ) {
      spaces += c;
      trim++;
    }
    else
      break;
  }
  sKey = sKey.Mid(trim);
  return atoi(spaces);
}

CString Decode1234(int digit) {
  TCHAR* words[4] = { _T("першому"), _T("другому"), _T("третьому"), _T("четвертому") };
  CString s, sRet;
  digit--;
  for(int i(0); i < 4; i++ ) {
    if ( digit==i ) {
      sRet = words[i];
      break;
    }
  }
  return sRet;

}

CString GetNumMarriageStr(BYTE bNumMarriage, const CString& sSurname) {
  CString s;
  if ( !sSurname.IsEmpty() ) {
    switch( bNumMarriage ) {
      case 1: s = _T("першому");    break;
      case 2: s = _T("другому");    break;
      case 3: s = _T("третьому");   break;
      case 4: s = _T("четвертому"); break;
    }
  }
  return s;
}

CString GetNumMarriage(BYTE bNumMarriage, LPCTSTR szOldSurname) {
  CString sSurname = Trim(szOldSurname);
  int ndigit = 0;
  if ( bNumMarriage && !sSurname.IsEmpty() ) {
    ndigit = (int)(bNumMarriage);
  }
  return Decode1234(ndigit);
}

// ODT:
// <text:span text:style-name="Underline">текст</text:span>
//
// <style:style style:name="Underline" style:family="text"><style:text-properties style:text-underline-style="solid" style:text-underline-width="auto" style:text-underline-color="font-color"/></style:style>
//
//
//
// RTF: {\ul текст}
CString GetNumMarriage2(BYTE bNumMarriage) {
  CString s, sRet;
  int ndigit = 0;
  if ( bNumMarriage ) {
    ndigit = (int)(bNumMarriage);
  }
  if ( ndigit ) {
    ndigit = (int)(bNumMarriage);
    for ( int i = 1; i <= 4; i++ ) {
      if ( i==ndigit ) {
        if ( CNV_RTF==g_ConvertType ) { // RTF
          s.Format(_T("{\\ul %s}"), Decode1234(i));
        }
        else {
          s.Format(_T("<text:span text:style-name=\"Underline\">%s</text:span>"), Decode1234(i));
        }
      }
      else {
        s = Decode1234(i);
      }
      sRet += s;
      sRet += ' ';
    }
  }
  sRet.TrimRight();
  return sRet;
}

CString GetLiveOrDead(BOOL fLive) {
  static LPCTSTR sz[2] = { _T("Живонароджена"), _T("мертвонароджена") };
  CString s;
  if ( CNV_RTF==g_ConvertType ) { // RTF
    if ( fLive ) {
      s.Format(_T("{\\ul %s} чи %s"), sz[0], sz[1]);
    }
    else {
      s.Format(_T("%s чи {\\ul %s}"), sz[0], sz[1]);
    }
  }
  else {
    if ( fLive ) {
      s.Format(_T("<text:span text:style-name=\"Underline\">%s</text:span> чи %s"), sz[0], sz[1]);
    }
    else {
      s.Format(_T("%s чи <text:span text:style-name=\"Underline\">%s</text:span>"), sz[0], sz[1]);
    }
  }
  return s;
}

CString TrimRow(const CString& sRow) {
  CString s = sRow;
  while ( s.GetLength() ) {
    if ( s.Right(6) == _T("\\row }") ) {
      break;
    }
    else if ( s.Right(5) == _T("\\row ") ) {
      break;
    }
    s.TrimRight( s.Right(1) );
  }
  while ( s.GetLength() ) {
    if ( s.Left(5) == _T("\\pard") ) {
      break;
    }
    s.TrimLeft( s.Left(1) );
  }
  return s;
}

bool IsCommonSect(CDaoRecordset* pSet, const CString& sUpperKey, CString& sValue, BOOL& bConvert, BOOL& bFirst, BOOL* pOwnerFound) {
  if (      sUpperKey==_T("МР_1") ) { // Місце реєстрації: строка 1
    sValue = g_szMR_1;
  }
  else if ( sUpperKey==_T("МР_2") ) { // Місце реєстрації: строка 2
    sValue = g_szMR_2;
  }
  else if ( sUpperKey==_T("МР_3") ) { // Місце реєстрації: строка 3
    sValue = g_szMR_3;
  }
  else if ( sUpperKey==_T("ОР_1") ) { // Орган, що видав: строка 1
    if ( pOwnerFound ) {
      *pOwnerFound = true;
    }
    sValue = g_szOR_1;
  }
  else if ( sUpperKey==_T("ОР_2") ) { // Орган, що видав: строка 2
    sValue = g_szOR_2;
  }
  else if ( sUpperKey==_T("ОР_3") ) { // Орган, що видав: строка 3
    sValue = g_szOR_3;
  }
  else if ( sUpperKey==_T("ДВРР") ) { // Дата видачі свідоцтва: РР - рік
    if ( COleDateTime::valid == g_DateCert.GetStatus())
      sValue.Format(_T("%02d"), g_DateCert.GetYear() % 100 );
  }
  else if ( sUpperKey==_T("ДВРРРР")) {// Дата видачі свідоцтва: РРРР - століття+рік
    if ( COleDateTime::valid == g_DateCert.GetStatus())
      sValue.Format(_T("%04d"), g_DateCert.GetYear() );
  }
  else if ( sUpperKey==_T("ДВМММ") ) {// Дата видачі свідоцтва: МММ - місяця
    if ( COleDateTime::valid == g_DateCert.GetStatus())
      sValue = GetByMonth(g_DateCert);
  }
  else if ( sUpperKey==_T("ДВЧЧ") ) { // Дата видачі свідоцтва: ЧЧ - число
    if ( COleDateTime::valid == g_DateCert.GetStatus())
      sValue.Format(_T("%02d"), g_DateCert.GetDay() );
  }
  else if ( sUpperKey==_T("ЄДРПОУ") ){ // ЄДРПОУ відділу
    sValue = theIniCache.GetOKPO();
  }
  else if ( sUpperKey==_T("КЕРІВНИК")) {// Керівник відділу
    if ( g_sTmpBoss.IsEmpty() )
      g_sTmpBoss = theIniCache.GetBoss();
    sValue = g_sTmpBoss;
    bConvert = true;
  }
  else if ( sUpperKey==_T("СПЕЦІАЛІСТ")) {// Спеціаліст
    sValue = theApp.m_szUser;
    bConvert = true;
  }
  else if ( sUpperKey==_T("ЗАЯВНИК") && pSet ) { // ПІБ заявника
    sValue = GetFieldString(pSet, _T("DECLARANT_NAME") );
  }
  else if ( sUpperKey==_T("СД")) {      // Системная дата
    sValue = GetDateDDMMYYYYr( COleDateTime::GetCurrentTime() );
  }
  else if ( sUpperKey==_T("НОВС_РВ")) { // Назва органу внутрішніх справ у родовому відмінку
    sValue = theIniCache.GetToROVD();
    bFirst = true;
  }
  else if ( sUpperKey==_T("НВК_РВ")) {  // Назва військового комісаріату у родовому відмінку
    sValue = theIniCache.GetToMil();
    bFirst = true;
  }
  else if ( sUpperKey==_T("НДПО_РВ") ){ // Назва державного податкового органу у родовому відмінку
    sValue = theIniCache.GetToTax();
    bFirst = true;
  }
  else if ( sUpperKey==_T("НДОСЗН_РВ") || sUpperKey==_T("ОСЗН_РВ")) {// Назва державного органу соцзахисту населення у родовому відмінку
    sValue = theIniCache.GetToSocProt();
    bFirst = true;
  }
  else if ( sUpperKey==_T("НВРАГС") || sUpperKey==_T("НВРАЦС")) {  // Назва відділу РАГС
    sValue = DecodeRagsName(theIniCache.GetRAGS());
    bFirst = true;
  }
  else if ( sUpperKey==_T("НВРАЦС_ДВ") ) {  // Назва відділу РАГС в давальному відмінку
    sValue = SVRagsC(theIniCache.GetRAGS(), RC_DV);
    bFirst = true;
  }
  else if ( sUpperKey==_T("НВРАГС_ОВ") || sUpperKey==_T("НВРАЦС_ОВ") || sUpperKey==_T("НВРАГСОВ")) {  // Назва відділу РАГС в орудному відмінку
    sValue = SVRagsC(theIniCache.GetRAGS(), RC_OV);
    bFirst = true;
  }
  else if ( sUpperKey==_T("НВРАГС_РВ") || sUpperKey==_T("НВРАГСРВ")) {  // Назва відділу РАГС в родовому відмінку
    sValue = SVRagsC(theIniCache.GetRAGS(), RC_RV);
    bFirst = true;
  }
  else if ( sUpperKey==_T("НВРАГС_МВ") || sUpperKey==_T("НВРАЦС_МВ") || sUpperKey==_T("НВРАГСМВ") ) {  // Назва відділу РАГС в місцевому відмінку
    sValue = SVRagsC(theIniCache.GetRAGS(), RC_MV);
    bFirst = true;
  }
  else if ( sUpperKey==_T("ДО ВІДДІЛУ")) {  // Назва відділу РАГС в орудному відмінку
    sValue = g_RagsTo;
    bFirst = true;
  }
  else if ( sUpperKey==_T("У ВІДДІЛІ")) {  // Назва відділу РАГС в орудному відмінку
    sValue = g_RagsWhere;
    bFirst = true;
  }

  else if ( sUpperKey==_T("ГРОМАДЯН") || sUpperKey==_T("ДОКУМЕНТІВ")) {// Кількість громадян
    sValue.Format(_T("%d"), g_nTotalRecs);
  }
  else if ( sUpperKey==_T("АРКУШІВ")) { // Кількість аркушів
    sValue.Format(_T("%d"), g_nTotalPages);
  }
  else if ( (sUpperKey==_T("ПОВТОРНЕ") || sUpperKey==_T("ПОВТОРНО")) && g_fSecondCert ) { // Повторне
    sValue = sUpperKey;
    bConvert = true;
  }
  else if ( sUpperKey==_T("ЗЧЧ") ) {
    sValue.Format(_T("%02d"), g_odtFrom.GetDay() );
  }
  else if ( sUpperKey==_T("ЗМММ") ) {
    sValue.Format( _T("%s"), GetMonth(g_odtFrom.GetMonth()) );
  }
  else if ( sUpperKey==_T("ДЧЧ") ) {
    sValue.Format(_T("%02d"), g_odtTill.GetDay() );
  }
  else if ( sUpperKey==_T("ДМММ") ) {
    sValue.Format( _T("%s"), GetMonth(g_odtTill.GetMonth()) );
  }
  else if ( sUpperKey==_T("ДРРРР") ) {
    sValue.Format(_T("%04d"), g_odtTill.GetYear() );
  }
  else if ( sUpperKey==_T("ПЕРІОД") ) {
    sValue = GetPeriod();
  }
  else
    return false;
  return true;
}

void IsCommonSect(const Keyword* pKeyword, CDaoRecordset* pSet, const CString& sUpperKey, CString& sValue, BOOL& bConvert, BOOL& bFirst, BOOL* pOwnerFound) {
  switch( pKeyword->id ) {
    case IDKW_MR_1        :   // МР_1   Місце реєстрації: строка 1
      sValue = g_szMR_1;
      break;
    case IDKW_MR_2        :   // МР_2   Місце реєстрації: строка 2
      sValue = g_szMR_2;
      break;
    case IDKW_MR_3        :   // МР_3   Місце реєстрації: строка 3
      sValue = g_szMR_3;
      break;
    case IDKW_OR_1        :   // ОР_1   Орган, що видав: строка 1
      if ( pOwnerFound ) {
        *pOwnerFound = true;
      }
      sValue = g_szOR_1;
      break;
    case IDKW_OR_2        :   // ОР_2   Орган, що видав: строка 2
      sValue = g_szOR_2;
      break;
    case IDKW_OR_3        :   // ОР_3   Орган, що видав: строка 3
      sValue = g_szOR_3;
      break;
    case IDKW_DVRR        :   // ДВРР   Дата видачі свідоцтва: РР - рік
      if ( COleDateTime::valid == g_DateCert.GetStatus())
        sValue.Format(_T("%02d"), g_DateCert.GetYear() % 100 );
      break;
    case IDKW_DVRRRR      :   // ДВРРРР Дата видачі свідоцтва: РРРР - століття+рік
      if ( COleDateTime::valid == g_DateCert.GetStatus())
        sValue.Format(_T("%04d"), g_DateCert.GetYear() );
      break;
    case IDKW_DVMMM       :   // ДВЧЧ   Дата видачі свідоцтва: МММ - місяця
      if ( COleDateTime::valid == g_DateCert.GetStatus())
        sValue = GetByMonth(g_DateCert);
      break;
    case IDKW_DV44        :   // ДВЧЧ   Дата видачі свідоцтва: ЧЧ - число
      if ( COleDateTime::valid == g_DateCert.GetStatus())
        sValue.Format(_T("%02d"), g_DateCert.GetDay() );
      break;
    case IDKW_OKPO        :   // ОКПО   ЄДРПОУ відділу
    case IDKW_EDRPOU      :   // ЄДРПОУ ЄДРПОУ відділу
      sValue = theIniCache.GetOKPO();
      break;
    case IDKW_KERIVNYK    :   // КЕРІВНИК Керівник відділу
      if ( g_sTmpBoss.IsEmpty() )
        g_sTmpBoss = theIniCache.GetBoss();
      sValue = g_sTmpBoss;
      bConvert = true;
      break;
    case IDKW_PIB_PO      :   // ПІБ посадової особи
      sValue = theIniCache.GetPIBPO();
      break;
    case IDKW_POSADA      :
      if ( pSet ) {
        sValue = GetSpecPost(pSet);
      }
      if ( sValue.IsEmpty() ) {
        sValue = theIniCache.GetPosada();
      }
      break;
    case IDKW_SPECIALIST  :
      if ( pSet )
        sValue = GetSpecName(pSet);
      bConvert = true;
      break;
    case IDKW_ZAYAVNYK    :   // ЗАЯВНИК  ПІБ заявника
      if ( pSet ) {
        sValue = GetFieldString(pSet, _T("DECLARANT_NAME") );
      }
      break;
    case IDKW_SD          : // СД     Системная дата
      sValue = GetDateDDMMYYYYr( COleDateTime::GetCurrentTime() );
      break;
    case IDKW_NOVS_RV     : // НОВС_РВ  Назва органу внутрішніх справ у родовому відмінку
      sValue = theIniCache.GetToROVD();
      bFirst = true;
      break;
    case IDKW_NVK_RV      : // НВК_РВ   Назва військового комісаріату у родовому відмінку
      sValue = theIniCache.GetToMil();
      bFirst = true;
      break;
    case IDKW_NDPO_RV     : // НДПО_РВ  Назва державного податкового органу у родовому відмінку
      sValue = theIniCache.GetToTax();
      bFirst = true;
      break;
    case IDKW_NDOSZN_RV   : // НДОСЗН_РВ  Назва державного органу соцзахисту населення у родовому відмінку
    case IDKW_OSZN_RV     : // ОСЗН_РВ    Назва державного органу соцзахисту населення у родовому відмінку
      sValue = theIniCache.GetToSocProt();
      bFirst = true;
      break;
    case IDKW_NVRAGS      : // НВРАГС     Назва відділу РАГС
    case IDKW_NVRACS      : // НВРАЦС     Назва відділу РАГС
      sValue = DecodeRagsName(theIniCache.GetRAGS());
      bFirst = true;
      break;
    case IDKW_NVRACS_DV   : // НВРАЦС_ДВ  Назва відділу РАГС в давальному відмінку
      sValue = SVRagsC(theIniCache.GetRAGS(), RC_DV);
      bFirst = true;
      break;
    case IDKW_NVRAGS_OV   : // НВРАГС_ОВ  Назва відділу РАГС в орудному відмінку
    case IDKW_NVRACS_OV   : // НВРАЦС_ОВ  Назва відділу РАГС в орудному відмінку
    case IDKW_NVRAGSOV    : // НВРАГСОВ   Назва відділу РАГС в орудному відмінку
      sValue = SVRagsC(theIniCache.GetRAGS(), RC_OV);
      bFirst = true;
      break;
    case IDKW_NVRAGS_RV   : // НВРАГС_РВ  Назва відділу РАГС в родовому відмінку
    case IDKW_NVRAGSRV    : // НВРАГСРВ   Назва відділу РАГС в родовому відмінку
      sValue = SVRagsC(theIniCache.GetRAGS(), RC_RV);
      bFirst = true;
      break;
    case IDKW_NVRAGS_MV   : // НВРАГС_МВ   Назва відділу РАГС в місцевому відмінку
    case IDKW_NVRACS_MV   : // НВРАЦС_МВ   Назва відділу РАГС в місцевому відмінку
    case IDKW_NVRAGSMV    : // НВРАГСМВ    Назва відділу РАГС в місцевому відмінку
      sValue = SVRagsC(theIniCache.GetRAGS(), RC_MV);
      bFirst = true;
      break;
    case IDKW_DO_VIDDILU  : // ДО ВІДДІЛУ  Назва відділу РАГС в орудному відмінку
      sValue = g_RagsTo;
      bFirst = true;
      break;
    case IDKW_U_VIDDILI   : // У ВІДДІЛІ   Назва відділу РАГС в орудному відмінку
      sValue = g_RagsWhere;
      bFirst = true;
      break;
    case IDKW_GROMADYAN   : // ГРОМАДЯН    Кількість громадян
    case IDKW_DOCUMENTIV  : // ДОКУМЕНТІВ  Кількість громадян
      sValue.Format(_T("%d"), g_nTotalRecs);
      break;
    case IDKW_ARKUSHIV    : // АРКУШІВ     Кількість аркушів
      sValue.Format(_T("%d"), g_nTotalPages);
      break;
    case IDKW_POVTORNE    : // ПОВТОРНЕ
    case IDKW_POVTORNO    : // ПОВТОРНО
      if ( g_fSecondCert ) {
        sValue = sUpperKey;
        bConvert = true;
      }
      break;
    case IDKW_Z44         : // ЗЧЧ
      sValue.Format(_T("%02d"), g_odtFrom.GetDay() );
      break;
    case IDKW_ZMMM        : // ЗМММ
      sValue.Format( _T("%s"), GetMonth(g_odtFrom.GetMonth()) );
      break;
    case IDKW_D44         : // ДЧЧ
      sValue.Format(_T("%02d"), g_odtTill.GetDay() );
      break;
    case IDKW_DMMM        : // ДМММ
      sValue.Format( _T("%s"), GetMonth(g_odtTill.GetMonth()) );
      break;
    case IDKW_DRRRR       : // ДРРРР
      sValue.Format(_T("%04d"), g_odtTill.GetYear() );
      break;
    case IDKW_PERIOD      : // ПЕРІОД
      sValue = GetPeriod();
      break;

    case IDKW_STAMP1          : // ШТАМП1
      if ( theIniCache.GetUseStamp1() ) {
        sValue = ReplaceEOL(theIniCache.GetStamp1());
      }
      break;
    case IDKW_STAMP2          : // ШТАМП2
      if ( theIniCache.GetUseStamp2() ) {
        sValue = ReplaceEOL(theIniCache.GetStamp2());
      }
      break;
    default:
      TRACE1(_T("Unknown keyword \"%s\"."),pKeyword->szKeyword);
      break;
  }
}


struct KWData {
  CDaoRecordset* pSet;
  int            Number;
  int            nPage;
  int            nScan;
  BOOL           fOwnerFound;
};

void OnBirthKeyword(LPCTSTR szKeyword, CString& szReplace, DWORD dwData) {
  KWData* pData = (KWData*)dwData;

  CRSBirthes* pSet = (CRSBirthes*)pData->pSet;

  CString s, sKey(szKeyword);

  CString sTrimKey = Trim(sKey);
  CString sUpperKey = UpperString(sTrimKey);
  CString sLowerKey = LowerString(sTrimKey);
  BOOL bConvert = false;
  BOOL bFirst = false;
  int  nBeforeSpaces = 0;

  const Keyword* pKeyword = theKeywords.Lookup(sUpperKey);

  if ( pKeyword ) {
    switch( pKeyword->id ) {
      case IDKW_NAZ       : // НАЗ        Номер актового запису
        szReplace = GetFieldString(pSet, _T("NUMBER"));
        return;
      case IDKW_DDMMMRRRR : // ДДМММРРРР  Дата реєстрації: ДД МММ РРРР
        szReplace = GetFieldDate(pSet, _T("DATEREG"), true);
        return;
      case IDKW_DDMMRRRR  : // ДДММРРРР   Дата реєстрації: ДД.ММ.РРРР
        szReplace = GetFieldDate(pSet, _T("DATEREG"), false);
        return;
      case IDKW_PAZ       : // ПАЗ      Поновлений актовий запис
        if ( pSet->m_RENEW & BIRTH_RENEW )
          szReplace = theIniCache.GetRenew();
        return;
      case IDKW_ZPS       : // ЗПС      Реєстрація з пропуском строку
        if ( pSet->m_RENEW & BIRTH_LONGTERM )
          szReplace = _T("Реєстрація з пропуском строку");
        return;
      case IDKW_RRRR      : // РРРР     Дата реєстрації, рік: рррр
        szReplace = GetYear(pSet->m_DATEREG);
        return;
      case IDKW_RR        : // РР       Дата реєстрації, рік: рр
        szReplace = GetYear(pSet->m_DATEREG, false);
        return;
      case IDKW_MMM       : // МММ      Дата реєстрації: місяця
        szReplace = GetByMonth(pSet->m_DATEREG);
        return;
      case IDKW_44        : // ЧЧ       Дата реєстрації, число
        szReplace = GetDay(pSet->m_DATEREG);
        return;
      case IDKW_PRN       : // ПРН      Прізвище новонародженого
        szReplace = pSet->GetNewSurname();
        if ( szReplace.IsEmpty() )
          szReplace = pSet->m_SURNAME;
        bConvert = true;
        return;
      case IDKW_STPRN     : // СТПРН    Старе прізвище новонародженого
        szReplace = pSet->GetNewSurname();
        if ( !szReplace.IsEmpty() ) {
          if ( szReplace == pSet->m_SURNAME )
            szReplace.Empty();
          else
            szReplace = pSet->m_SURNAME;
        }
        if ( g_fAdoption && szReplace.IsEmpty() ) {
          szReplace = pSet->m_SURNAME;
        }
        bConvert = true;
        break;
      case IDKW_IMN       : // ІМН      Ім'я новонародженого
        szReplace = pSet->GetNewName();
        if ( szReplace.IsEmpty() )
          szReplace = pSet->m_NAME;
        else
          nBeforeSpaces = 2;
        bConvert = true;
        break;
      case IDKW_STIMN     : // СТІМН    Старе ім'я новонародженого
        szReplace = pSet->GetNewName();
        if ( !szReplace.IsEmpty())
          szReplace = pSet->m_NAME;
        if ( g_fAdoption && szReplace.IsEmpty() ) {
          szReplace = pSet->m_NAME;
        }
        bConvert = true;
        break;
      case IDKW_PBN       : // ПБН      По батькові новонародженого
        szReplace = pSet->GetNewPatronymic();
        if ( szReplace.IsEmpty() )
          szReplace = pSet->m_PATRONYMIC;
        bConvert = true;
        break;
      case IDKW_STPBN     : // СТПБН    Старе по батькові новонародженого
        szReplace = pSet->GetNewPatronymic();
        if ( !szReplace.IsEmpty() )
          szReplace = pSet->m_PATRONYMIC;
        if ( g_fAdoption && szReplace.IsEmpty() ) {
          szReplace = pSet->m_PATRONYMIC;
        }
        bConvert = true;
        break;
      case IDKW_STAT      : // СТАТЬ      Стать новонародженого
        szReplace = ( pSet->m_SEX ) ?  _T("чоловіча") : _T("жіноча");
        return;
      case IDKW_MW        : // ЧЖ         "Ч" або "Ж"
        szReplace = pSet->m_SEX ? _T("Ч") : _T("Ж");
        return;
      case IDKW_DATAN     : // ДАТАН      Дата народження
        szReplace = GetFieldDate(pSet, _T("BIRTH_DATE"), true);
        return;
      case IDKW_DN44      : // ДНЧЧ       Дата народження: чч (дд)
        if ( COleDateTime::valid == pSet->m_BIRTH_DATE.GetStatus())
          szReplace.Format(_T("%02d"), pSet->m_BIRTH_DATE.GetDay() );
        return;
      case IDKW_DNMM      : // ДНММ       Дата народження: мм
        if ( COleDateTime::valid == pSet->m_BIRTH_DATE.GetStatus())
          szReplace.Format(_T("%02d"), pSet->m_BIRTH_DATE.GetMonth() );
        return;
      case IDKW_DNMMM     : // ДНМММ      Дата народження: ммм
        szReplace = GetByMonth(pSet->m_BIRTH_DATE);
        return;
      case IDKW_DNRRRR    : // ДНРРРР     Дата народження: рррр
        if ( COleDateTime::valid == g_DateCert.GetStatus())
          szReplace.Format(_T("%04d"), pSet->m_BIRTH_DATE.GetYear() );
        return;
      case IDKW_DNDDMMRRRR: // ДНДДММРРРР Дата народження: дд.мм.рррр
        szReplace = GetFieldDate(pSet, _T("BIRTH_DATE"), false);
        return;
      case IDKW_4MPROPYSOM: // ЧМПРОПИСОМ Дата народження: число та місяць прописом
        szReplace = strDayMonth(pSet->m_BIRTH_DATE);
        return;
      case IDKW_RPROPYSOM : // РПРОПИСОМ  Дата народження: рік прописом
        szReplace = strYear(pSet->m_BIRTH_DATE);
        return;
      case IDKW_PIBN      : // ПІБН       ПІБ новонародженого
        szReplace = MakeFIO(pSet->m_SURNAME, pSet->m_NAME, pSet->m_PATRONYMIC);
        bConvert = true;
        break;
      case IDKW_PIBN_RV : case IDKW_PIBD_RV:  // Прізвище, ім'я, по батькові новонародженого у родовому відмінку
        szReplace = g_sFullBabyNameRV;
        bConvert = true;
        break;
      case IDKW_DATADOV   : // Дата довідки про народження
        szReplace = GetDateFromStr(pSet->m_NOTICE);
        return;
      case IDKW_NDN8      : // Довідка 08
        szReplace = g_Dlg08_sNumber;
        return;
      case IDKW_NDN9      : // Довідка 09
        szReplace = pSet->GetNDov();
        return;
      case IDKW_DO        : // Довідка 08
        szReplace = g_Dlg08_sWhere;
        return;
      case IDKW_NARODYVSYA: // народився/народилась
        szReplace = pSet->m_SEX ? _T("народився") : _T("народилась");
        return;
      case IDKW_NSUDU     : // Назва суда (свідоцтво про усиновлення)
        szReplace = pSet->GetVerdictOf();
        return;
      case IDKW_DPR       : // Дата прийняття рішення (свідоцтво про усиновлення)
        szReplace = GetDateDDMMYYYY(pSet->GetVerdictDate());
        return;
      case IDKW_NRS       : // Номер рішення суду (свідоцтво про усиновлення)
        s = pSet->GetVerdictNumber();
        if ( FALSE==s.IsEmpty() && s.Find('№')==-1 )
          szReplace.Format(_T("№ %s"), s);
        else
          szReplace = s;
        return;
      case IDKW_NDN       : // НДН  Нова дата народження
        szReplace = pSet->GetNewBirthDate(g_fStrikeOut);
        return;
      case IDKW_MND       : // МНД  Місце народження: Держава
        szReplace = GetFieldString(pSet, _T("BP_COUNTRY"));
        return;
      case IDKW_NMND      : // НМНД Нове місце народження: Держава
        szReplace = pSet->GetNewBirthCountry(g_fStrikeOut);
        return;
      case IDKW_MNO       : // МНО  Місце народження: Область
        szReplace = GetFieldString(pSet, _T("BP_REGION"));
        return;
      case IDKW_NMNO      : // НМНО Нове місце народження: Область
        szReplace = pSet->GetNewBirthRegion(g_fStrikeOut);
        return;
      case IDKW_MNOBL     : // МНОБЛ Місце народження: Область + область
        szReplace = GetRegion(GetFieldString(pSet, _T("BP_REGION")), false);
        return;
      case IDKW_NMNOBL    : // НМНОБЛ Нове місце народження: Область + область
        szReplace = GetRegion(pSet->GetNewBirthRegion(g_fStrikeOut), false);
        return;
      case IDKW_MNOBL_    : // МНОБЛ. Місце народження: Область + обл.
        szReplace = GetRegion(GetFieldString(pSet, _T("BP_REGION")), true);
        return;
      case IDKW_NMNOBL_   : // НМНОБЛ. Нове місце народження (Область + обл.) або прочерк
        szReplace = GetRegion(pSet->GetNewBirthRegion(g_fStrikeOut), true);
        return;
      case IDKW_MNR       : // МНР  Нове місце народження (Район) або прочерк
        szReplace = GetFieldString(pSet, _T("BP_DISTRICT"));
        return;
      case IDKW_NMNR      : // НМНР  Місце народження: Район
        szReplace = pSet->GetNewBirthDistrict(g_fStrikeOut);
        return;
      case IDKW_MNRAYON   : // МНРАЙОН Місце народження: Район + район
        szReplace = GetDistrict(GetFieldString(pSet, _T("BP_DISTRICT")), false);
        return;
      case IDKW_NMNRAYON  : // НМНРАЙОН Нове місце народження: (Район + район) або прочерк
        szReplace = GetDistrict(pSet->GetNewBirthDistrict(g_fStrikeOut), false);
        return;
      case IDKW_MNR_N     : // МНР-Н Місце народження: Район + р-н
        szReplace = GetDistrict(GetFieldString(pSet, _T("BP_DISTRICT")), true);
        return;
      case IDKW_NMNR_N    : // НМНР-Н Нове місце народження: (Район + р-н) або прочерк
        szReplace = GetDistrict(pSet->GetNewBirthDistrict(g_fStrikeOut), true);
        return;
      case IDKW_MSS       : // МСС Місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_BP_CITY);
        return;
      case IDKW_NMSS      : // НМСС Нове місто (село, селище) - тип НП або прочерк
        szReplace = TypeOfCity(pSet->GetNewBirthCity(g_fStrikeOut));
        return;
      case IDKW_MNM       : // МНМ  Місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_BP_CITY);
        return;
      case IDKW_NMNM      : // НМНМ  Нове місто (село, селище) - назва НП або прочерк
        szReplace = GetCity(pSet->GetNewBirthCity(g_fStrikeOut));
        return;
      case IDKW_DITEY     : // ДІТЕЙ Скількі народилося дітей
        szReplace = GetNKids(pSet->m_NKIDS);
        return;
      case IDKW_ALIVE     : // ЖЧМ "живонароджена" або "мертвонароджена"
        szReplace = pSet->m_ALIVE_FLAG ? _T("живонароджена") : _T("мертвонароджена");
        return;
      case IDK_LIVE_OR_NO :
        szReplace = GetLiveOrDead(pSet->m_ALIVE_FLAG);
        return;
      case IDKW_ZA_RAHUNKOM:// ЗА РАХУНКОМ
        szReplace = ByCount( pSet->m_BYCOUNT );
        return;
      case IDKW_DOCUMENT  : // Документ
        szReplace = GetBirthDoc(pSet);
        bFirst = true;
        break;
      case IDKW_PRB       : // ПРБ  Прізвище батька
        szReplace = pSet->m_FATHER_SURNAME;
        bConvert = true;
        break;
      case IDKW_PRM       : // ПРМ  Прізвище матері
        szReplace = Trim(pSet->GetNewMotherSurname());
        if ( szReplace.IsEmpty() )
          szReplace = pSet->m_MOTHER_SURNAME;
        else
          nBeforeSpaces = 2;
        bConvert = true;
        break;
      case IDKW_STPRM     : // СТПРМ  Старе прізвище матері
        szReplace = Trim(pSet->GetNewMotherSurname());
        if ( !szReplace.IsEmpty() )
          szReplace = pSet->m_MOTHER_SURNAME;
        bConvert = true;
        break;
      case IDKW_IMB       : // ІМБ  Ім'я батька
        szReplace = pSet->m_FATHER_NAME;
        bConvert = true;
        break;
      case IDKW_IMM       : // ІММ  Ім'я матері
        szReplace = pSet->m_MOTHER_NAME;
        bConvert = true;
        break;
      case IDKW_PBB       : // ПББ  По батькові батька
        szReplace = pSet->m_FATHER_PATRONYMIC;
        bConvert = true;
        break;
      case IDKW_PBM       : // ПБМ  По батькові матері
        szReplace = pSet->m_MOTHER_PATRONYMIC;
        bConvert = true;
        break;
      case IDKW_PIBB_RV   : // ПІББ_РВ  ПІБ батька у родовому відмінку
        szReplace = g_sFullFatherNameRV;
        bConvert = true;
        break;
      case IDKW_PIBM_RV   : // ПІБМ_РВ  ПІБ матері у родовому відмінку
        szReplace = g_sFullMotherNameRV;
        bConvert = true;
        break;
      case IDKW_DATANB    : // ДАТАНБ Дата народження батька
        szReplace = GetDate(pSet->m_FATHER_BIRTH_DATE, pSet->m_EXTNOTES, _T("Дата народження батька:"));
        return;
      case IDKW_DATANM    : // ДАТАНМ Дата народження матері
        szReplace = GetDate(pSet->m_MOTHER_BIRTH_DATE, pSet->m_EXTNOTES, _T("Дата народження матері:"));
        return;
      case IDKW_GROMADYANSTVOB  : // ГРОМАДЯНСТВОБ Громадянство батька
        szReplace = GetCitizenship(TRUE, pSet->m_FATHER_CITIZENSHIP, bFirst);
        break;
      case IDKW_GROMADYANSTVOM  : // ГРОМАДЯНСТВОМ Громадянство батька
        szReplace = GetCitizenship(FALSE, pSet->m_MOTHER_CITIZENSHIP, bFirst);
        break;
      case IDKW_MPBD      : // МПБД     Місце проживання батька: Держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_FATHER_COUNTRY);
        return;
      case IDKW_MPBO      : // МПБО     Місце проживання батька: Область
        szReplace = pSet->m_FATHER_REGION;
        return;
      case IDKW_MPBOBL    : // МПБОБЛ   Місце проживання батька: Область + область
        szReplace = GetRegion(pSet->m_FATHER_REGION, false);
        return;
      case IDKW_MPBOBL_   : // МПБОБЛ.  Місце проживання батька: Область + обл.
        szReplace = GetRegion(pSet->m_FATHER_REGION, true);
        return;
      case IDKW_MPBR      : // МПБР     Місце проживання батька: Район
        szReplace = pSet->m_FATHER_DISTRICT;
        return;
      case IDKW_MPBR_N    : // МПБР-Н   Місце проживання батька: Район + р-н
        szReplace = GetDistrict(pSet->m_FATHER_DISTRICT, true);
        return;
      case IDKW_MPBRAYON  : // МПБРАЙОН Місце проживання батька: Район + район
        szReplace = GetDistrict(pSet->m_FATHER_DISTRICT, false);
        return;
      case IDKW_MSSB      : // МССБ     Місце проживання батька: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_FATHER_CITY);
        return;
      case IDKW_MPBM      : // МПБМ     Місце проживання батька: місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_FATHER_CITY);
        return;
      case IDKW_VULB      : // ВУЛБ     Місце проживання батька: вулиця
        szReplace = pSet->m_FATHER_STREET;
        return;
      case IDKW_BUDB      : // БУДБ     Місце проживання батька: будинок
        szReplace = pSet->m_FATHER_HOUSE;
        return;
      case IDKW_KVB       : // КВБ      Місце проживання батька: квартира
        szReplace = pSet->m_FATHER_FLAT;
        return;
      case IDKW_MPMD      : // МПМД     Місце проживання матері: Держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_MOTHER_COUNTRY);
        return;
      case IDKW_MPMO      : // МПМО     Місце проживання матері: Область
        szReplace = pSet->m_MOTHER_REGION;
        return;
      case IDKW_MPMOBL    : // МПМОБЛ   Місце проживання матері: Область + область
        szReplace = GetRegion(pSet->m_MOTHER_REGION, false);
        return;
      case IDKW_MPMOBL_   : // МПМОБЛ.  Місце проживання матері: Область + обл.
        szReplace = GetRegion(pSet->m_MOTHER_REGION, true);
        return;
      case IDKW_MPMR      : // МПМР     Місце проживання матері: Район
        szReplace = pSet->m_MOTHER_DISTRICT;
        return;
      case IDKW_MPMR_N    : // МПМР-Н   Місце проживання матері: Район + р-н
        szReplace = GetDistrict(pSet->m_MOTHER_DISTRICT, true);
        return;
      case IDKW_MPMRAYON  : // МПМРАЙОН Місце проживання матері: Район + район
        szReplace = GetDistrict(pSet->m_MOTHER_DISTRICT, false);
        return;
      case IDKW_MSSM      : // МССМ     Місце проживання матері: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_MOTHER_CITY);
        return;
      case IDKW_MPMM      : // МПММ     Місце проживання матері: місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_MOTHER_CITY);
        return;
      case IDKW_VULM      : // ВУЛМ     Місце проживання матері: вулиця
        szReplace = pSet->m_MOTHER_STREET;
        return;
      case IDKW_BUDM      : // БУДМ     Місце проживання матері: будинок
        szReplace = pSet->m_MOTHER_HOUSE;
        return;
      case IDKW_KVM       : // КВМ      Місце проживання матері: квартира
        szReplace = pSet->m_MOTHER_FLAT;
        return;
      case IDKW_PIDSTAVA  : // ПІДСТАВА Підстава запису відомостей про батька
        szReplace = GetFatherSource(pSet);
        return;
      case IDKW_PIBZ      : // ПІБЗ     Прізвище, ім'я, по батькові заявника
        szReplace = pSet->m_DECLARANT_NAME;
        return;
      case IDKW_ADRZ      : // АДРЗ     Адреса заявника
        szReplace = pSet->m_DECLARANT_ADDRESS;
        return;
      case IDKW_PASZ      : // ПАСЗ     Паспорт заявника
        if ( pSet->m_DECLARANT_TYPE !=2 && pSet->IsDeclarantIn20()==FALSE )
          szReplace = GetPassport(pSet->m_DECLARANT_PASSPORT_TYPE, pSet->m_DECLARANT_PASSPORT_SERIA, pSet->m_DECLARANT_PASSPORT_NUMBER, pSet->m_DECLARANT_PASSPORT_DATE, pSet->m_DECLARANT_PASSPORT_BY);
        return;
      case IDKW_PASZ1     : // ПАСЗ1    Паспорт заявника 1
        if ( pSet->m_DECLARANT_TYPE == 2 )
          szReplace = GetPassport(pSet->m_DECLARANT_PASSPORT_TYPE, pSet->m_DECLARANT_PASSPORT_SERIA, pSet->m_DECLARANT_PASSPORT_NUMBER, pSet->m_DECLARANT_PASSPORT_DATE, pSet->m_DECLARANT_PASSPORT_BY);
        return;
      case IDKW_PASZ2     : // ПАСЗ2    Паспорт заявника 2
        if ( pSet->m_DECLARANT_TYPE == 2 )
          szReplace = GetPassport(pSet->GetPassport2Type(), pSet->GetPassport2Seria(), pSet->GetPassport2Number(), pSet->GetPassport2ODT(), pSet->GetPassport2By());
        return;
      case IDKW_SS        : // СС       Серія свідоцтва
        szReplace = pSet->m_CERTIFICATE_SERIA;
        return;
      case IDKW_NS        : // НС       Номер свідоцтва
        szReplace = pSet->m_CERTIFICATE_NUMBER;
        return;
      case IDKW_SSNS      : // ССНС     Серія свідоцтва + № + Номер свідоцтва
        if ( false==pSet->m_CERTIFICATE_SERIA.IsEmpty() && false==pSet->m_CERTIFICATE_NUMBER.IsEmpty() ) {
          szReplace.Format(_T("серія %s № %s"), pSet->m_CERTIFICATE_SERIA, pSet->m_CERTIFICATE_NUMBER);
        }
        return;
      case IDKW_SNV       : // СНВ      Свідоцтва не видано
        szReplace = pSet->GetSvNeVidano();
        return;
      case IDKW_POMITKY   : // ПОМІТКИ
        szReplace = ReplaceEOL(pSet->GetNotices());
        return;
      case IDKW_PIBZDV    : // ПІБЗДВ   ПІБ заявника у давальному відмінку
        szReplace = CDlg43::m_sTo;
        bConvert = true;
        break;
      case IDKW_N41: case IDKW_N42: // №41 або №42
        szReplace = CDlg43::m_sNumber;
        return;
      case IDKW_ADRM      : // АДРМ     Адреса матері новонародженого
        szReplace = GetAddress(pSet->m_MOTHER_COUNTRY, pSet->m_MOTHER_REGION, pSet->m_MOTHER_CITY,  pSet->m_MOTHER_DISTRICT,  pSet->m_MOTHER_STREET,  pSet->m_MOTHER_HOUSE, pSet->m_MOTHER_FLAT);
        return;
      case IDKW_ARKUSH    : // АРКУШ
        szReplace.Format(_T("АРКУШ %d"), pData->nPage);
        return;
      case IDKW_N         : // №
        szReplace.Format(_T("%d"), pData->Number);
        return;
      default:
        IsCommonSect(pKeyword, pSet, sUpperKey, szReplace, bConvert, bFirst, &pData->fOwnerFound);
        break;
    }
  }
  else if ( sUpperKey.Left(9)==_T("ДДМММРРРР") ) {      // Дата реєстрації
    szReplace = sUpperKey.Left(9) + sTrimKey.Mid(9);
    szReplace = DDMMMRRRRR(pSet, _T("DATEREG"), szReplace);
  }
  else if ( sUpperKey.Left(8)==_T("ДДММРРРР") ) {      // Дата реєстрації: дд.мм.рррр
    szReplace = sUpperKey.Left(8) + sTrimKey.Mid(8);
    szReplace = DDMMRRRRR(pSet, _T("DATEREG"), szReplace);
  }
  else if ( sUpperKey.Left(11)==_T("ДНДДММРРРР") ) {      // Дата народження: дд.мм.рррр
    szReplace = sUpperKey.Mid(2, 8) + sTrimKey.Mid(10);
    szReplace = DDMMRRRRR(pSet, _T("BIRTH_DATE"), szReplace);
  }
  else if ( sUpperKey.Left(5)==_T("ДАТАН") ) {            // Дата народження
    // szReplace = GetFieldDate(pSet, _T("BIRTH_DATE"), true);
    szReplace = DDMMMRRRRR(pSet, _T("BIRTH_DATE"), sTrimKey.Mid(5));
  }

  if ( false==szReplace.IsEmpty() ) {
    if ( bFirst ) {
      if ( IsCyrUpper(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt( 0, CyrUpper(szReplace.GetAt(0)) );
      }
      else if ( IsCyrLower(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt( 0, CyrLower(szReplace.GetAt(0)) );
      }
    }
    if ( bConvert ) {
      if ( sKey==sUpperKey )
        szReplace = UpperString(szReplace);
      else
        szReplace = MakeCanonicalName(szReplace);
    }
    if ( sTrimKey != sKey ) {
      sKey.Replace(sTrimKey, szReplace);
      szReplace = sKey;
    }
  }
}

void OnMarriageKeyword(LPCTSTR szKeyword, CString& szReplace, DWORD dwData) {
  KWData* pData = (KWData*)dwData;

  CRSMarriages* pSet = (CRSMarriages*)pData->pSet;

  CString sKey(szKeyword);
  CString sTrimKey = Trim(sKey);
  CString sUpperKey = UpperString(sTrimKey);
  CString sLowerKey = LowerString(sTrimKey);
  BOOL bConvert = false;
  BOOL bFirst = false;

  const Keyword* pKeyword = theKeywords.Lookup(sUpperKey);
  if ( pKeyword ) {
    switch( pKeyword->id ) {
      case IDKW_NAZ       : // НАЗ        Номер актового запису
        szReplace = GetFieldString(pSet, _T("NUMBER"));
        return;
      case IDKW_RR        : // РР         Дата реєстрації, рік: рр
        szReplace = GetYear(pSet->m_DATEREG, false);
        return;
      case IDKW_RRRR      : // РРРР       Дата реєстрації, рік: рррр
        szReplace = GetYear(pSet->m_DATEREG);
        return;
      case IDKW_MMM       : // МММ        Дата реєстрації, рік: місяця
        szReplace = GetByMonth(pSet->m_DATEREG);
        return;
      case IDKW_44        : // ЧЧ         Дата реєстрації, число
        szReplace = GetDay(pSet->m_DATEREG);
        return;
      case IDKW_4MPROPYSOM: // ЧМПРОПИСОМ Дата реєстрації: число та місяць смерті прописом
        szReplace = strDayMonth(pSet->m_DATEREG);
        return;
      case IDKW_RPROPYSOM : // РПРОПИСОМ  Дата реєстрації: рік прописом
        szReplace = strYear(pSet->m_DATEREG);
        return;
      case IDKW_PRMN      : // ПРЧН   Прізвище чоловіка ПІСЛЯ реєстрації шлюбу
        szReplace = pSet->m_MNEW_SURNAME;
        bConvert = true;
        break;
      case IDKW_PRMS      : // ПРЧС   Прізвище чоловіка ДО реєстрації шлюбу
        szReplace = pSet->m_MOLD_SURNAME;
        bConvert = true;
        break;
      case IDKW_PRWN      : // ПРЖН   Прізвище жінки ПІСЛЯ реєстрації шлюбу
        szReplace = pSet->m_WNEW_SURNAME;
        bConvert = true;
        break;
      case IDKW_PRWS      : // ПРЖС   Прізвище жінки ДО реєстрації шлюбу
        szReplace = pSet->m_WOLD_SURNAME;
        bConvert = true;
        break;
      case IDKW_IM4       : // ІМЧ    Ім'я чоловіка
        szReplace = pSet->m_MNAME;
        bConvert = true;
        break;
      case IDKW_IMZ       : // ІМЖ    Ім'я жінки
        szReplace = pSet->m_WNAME;
        bConvert = true;
        break;
      case IDKW_PB4       : // ПБЧ    По батькові чоловіка
        szReplace = pSet->m_MPATRONYMIC;
        bConvert = true;
        break;
      case IDKW_PBZ       : // ПБЖ    По батькові жінки
        szReplace = pSet->m_WPATRONYMIC;
        bConvert = true;
        break;
      case IDKW_DATAN4    : // ДАТАНЧ Дата народження чоловіка
        szReplace = GetDate(pSet->m_MBIRTH_DATE, pSet->m_MNOTICE, _T("Дата народження:"));
        return;
      case IDKW_DATANZ    : // ДАТАНЖ Дата народження жінки
        szReplace = GetDate(pSet->m_WBIRTH_DATE, pSet->m_WNOTICE, _T("Дата народження:"));
        return;
      case IDKW_4N4       : // ЧНЧ    Дата народження чоловіка: число
        if ( COleDateTime::valid == pSet->m_MBIRTH_DATE.GetStatus())
          szReplace.Format(_T("%02d"), pSet->m_MBIRTH_DATE.GetDay() );
        return;
      case IDKW_4NZ       : // ЧНЖ    Дата народження жінки: число
        if ( COleDateTime::valid == pSet->m_WBIRTH_DATE.GetStatus())
          szReplace.Format(_T("%02d"), pSet->m_WBIRTH_DATE.GetDay() );
        return;
      case IDKW_MN4       : // МНЧ    Дата народження чоловіка: місяць
        szReplace = GetByMonth(pSet->m_MBIRTH_DATE);
        return;
      case IDKW_MNZ       : // МНЖ    Дата народження жінки: місяць
        szReplace = GetByMonth(pSet->m_WBIRTH_DATE);
        return;
      case IDKW_RN4       : // РНЧ    Дата народження чоловіка: рік  РР (78)
        szReplace = GetYear(pSet->m_MBIRTH_DATE, false);
        return;
      case IDKW_RN4S      : // РНЧС   Дата народження чоловіка: рік ССРР (1978)
        szReplace = GetYear(pSet->m_MBIRTH_DATE);
        return;
      case IDKW_RNZ       : // РНЖ        Дата народження жінки: рік РР (82)
        szReplace = GetYear(pSet->m_WBIRTH_DATE, false);
        return;
      case IDKW_RNZS      : // РНЖС       Дата народження жінки: рік  ССРР  (1982)
        szReplace = GetYear(pSet->m_WBIRTH_DATE);
        return;
      case IDKW_MN4D      : // МНЧД       Місце народження чоловіка: Держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_MBIRTH_COUNTRY);
        return;
      case IDKW_MNZD      : // МНЖД       Місце народження жінки: Держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_WBIRTH_COUNTRY);
        return;
      case IDKW_MN4O      : // МНЧО       Місце народження чоловіка: Oбласть
        szReplace = pSet->m_MBIRTH_REGION;
        return;
      case IDKW_MN4OBL    : // МНЧОБЛ     Місце народження чоловіка: Oбласть+область
      case IDKW_MN4OBLAST : // МНЧОБЛАСТЬ Місце народження чоловіка: Oбласть+область
        szReplace = GetRegion(pSet->m_MBIRTH_REGION, false);
        return;
      case IDKW_MN4OBL_   : // МНЧОБЛ.    Місце народження чоловіка: Oбласть+обл.
        szReplace = GetRegion(pSet->m_MBIRTH_REGION, true);
        return;
      case IDKW_MNZO      : // МНЖО       Місце народження жінки: Область
        szReplace = pSet->m_WBIRTH_REGION;
        return;
      case IDKW_MNZOBL    : // МНЖОБЛ     Місце народження жінки: Область + область
      case IDKW_MNZOBLAST : // МНЖОБЛАСТЬ Місце народження жінки: Область + область
        szReplace = GetRegion(pSet->m_WBIRTH_REGION, false);
        return;
      case IDKW_MNZOBL_   : // МНЖОБЛ.    Місце народження жінки: Область + обл.
        szReplace = GetRegion(pSet->m_WBIRTH_REGION, true);
        return;
      case IDKW_MN4R      : // МНЧР       Місце народження чоловіка: Район
        szReplace = pSet->m_MBIRTH_DISTRICT;
        return;
      case IDKW_MN4R_N    : // МНЧР-Н     Місце народження чоловіка: Район + р-н
        szReplace = GetDistrict(pSet->m_MBIRTH_DISTRICT, true);
        return;
      case IDKW_MN4RAYON  : // МНЧРАЙОН   Місце народження чоловіка: Район + район
        szReplace = GetDistrict(pSet->m_MBIRTH_DISTRICT, false);
        return;
      case IDKW_MNZR      : // МНЖР       Місце народження жінки: Район
        szReplace = pSet->m_WBIRTH_DISTRICT;
        return;
      case IDKW_MNZR_N    : // МНЖР-Н     Місце народження жінки: Район + р-н
        szReplace = GetDistrict(pSet->m_WBIRTH_DISTRICT, true);
        return;
      case IDKW_MNZRAYON  : // МНЖРАЙОН   Місце народження жінки: Район + район
        szReplace = GetDistrict(pSet->m_WBIRTH_DISTRICT, false);
        return;
      case IDKW_MN4M      : // МНЧМ       Місце народження чоловіка: місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_MBIRTH_CITY);
        return;
      case IDKW_MN4MSS    : // МНЧМСС     Місце народження чоловіка: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_MBIRTH_CITY);
        return;
      case IDKW_MNZM      : // МНЖМ       Місце народження жінки: місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_WBIRTH_CITY);
        return;
      case IDKW_MNZMSS    : // МНЖМСС     Місце народження жінки: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_WBIRTH_CITY);
        return;
      case IDKW_GROMADYANSTVO4  : // ГРОМАДЯНСТВОЧ  Громадянство чоловіка
        szReplace = GetCitizenship(true, pSet->m_MCITIZENSHIP, bFirst);
        break;
      case IDKW_GROMADYANSTVOZ  : // ГРОМАДЯНСТВОЖ  Громадянство жінки
        szReplace = GetCitizenship(false, pSet->m_WCITIZENSHIP, bFirst);
        break;
      case IDKW_MP4D            : // МПЧД       Місце проживання чоловіка: Держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_MRP_COUNTRY);
        return;
      case IDKW_MP4M            : // МПЧМ       Місце проживання чоловіка: місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_MRP_CITY);
        return;
      case IDKW_MP4MSS          : // МПЧМСС     Місце проживання чоловіка: місто (село, селище)  - тип НП
        szReplace = TypeOfCity(pSet->m_MRP_CITY);
        return;
      case IDKW_MP4O            : // МПЧО       Місце проживання чоловіка: Область
        szReplace = pSet->m_MRP_REGION;
        return;
      case IDKW_MP4OBL          : // МПЧОБЛ     Місце проживання чоловіка: Область + область
      case IDKW_MP4OBLAST       : // МПЧОБЛАСТЬ Місце проживання чоловіка: Область + область
        szReplace = GetRegion(pSet->m_MRP_REGION, false);
        return;
      case IDKW_MP4OBL_         : // МПЧОБЛ.    Місце проживання чоловіка: Область + обл.
        szReplace = GetRegion(pSet->m_MRP_REGION, true);
        return;
      case IDKW_MP4R            : // МПЧР       Місце проживання чоловіка: Район
        szReplace = pSet->m_MRP_DISTRICT;
        return;
      case IDKW_MP4R_N          : // МПЧР-Н     Місце проживання чоловіка: Район + р-н
        szReplace = GetDistrict(pSet->m_MRP_DISTRICT, false);
        return;
      case IDKW_MP4RAYON        : // МПЧРАЙОН   Місце проживання чоловіка: Район + район
        szReplace = GetDistrict(pSet->m_MRP_DISTRICT, true);
        return;
      case IDKW_MPZD            : // МПЖД       Місце проживання жінки: держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_WRP_COUNTRY);
        return;
      case IDKW_MPZM            : // МПЖМ       Місце проживання жінки: місто (село, селище) - назва НА
        szReplace = GetCity(pSet->m_WRP_CITY);
        return;
      case IDKW_MPZMSS          : // МПЖМСС     Місце проживання жінки: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_WRP_CITY);
        return;
      case IDKW_MPZO            : // МПЖО       Місце проживання жінки: Область
        szReplace = pSet->m_WRP_REGION;
        return;
      case IDKW_MPZOBL          : // МПЖОБЛ     Місце проживання жінки: Область + область
      case IDKW_MPZOBLAST       : // МПЖОБЛАСТЬ Місце проживання жінки: Область + область
        szReplace = GetRegion(pSet->m_WRP_REGION, false);
        return;
      case IDKW_MPZOBL_         : // МПЖОБЛ.    Місце проживання жінки: Область + обл.
        szReplace = GetRegion(pSet->m_WRP_REGION, true);
        return;
      case IDKW_MPZR            : // МПЖР       Місце проживання жінки: Район
        szReplace = pSet->m_WRP_DISTRICT;
        return;
      case IDKW_MPZR_N          : // МПЖР-Н     Місце проживання жінки: Район + р-н
        szReplace = GetDistrict(pSet->m_WRP_DISTRICT, true);
        return;
      case IDKW_MPZRAYON        : // МПЖРАЙОН   Місце проживання жінки: Район + район
        szReplace = GetDistrict(pSet->m_WRP_DISTRICT, false);
        return;
      case IDKW_VUL4            : // ВУЛЧ       Місце проживання чоловіка: вулиця
        szReplace = pSet->m_MRP_STREET;
        return;
      case IDKW_VULZ            : // ВУЛЖ       Місце проживання жінки: вулиця
        szReplace = pSet->m_WRP_STREET;
        return;
      case IDKW_BUD4            : // БУДЧ       Місце проживання чоловіка: будинок
        szReplace = pSet->m_MRP_HOUSE;
        return;
      case IDKW_BUDZ            : // БУДЖ       Місце проживання жінки: будинок
        szReplace = pSet->m_WRP_HOUSE;
        return;
      case IDKW_KV4             : // КВЧ        Місце проживання чоловіка: квартира
        szReplace = pSet->m_MRP_FLAT;
        return;
      case IDKW_KVZ             : // КВЖ        Місце проживання жінки: квартира
        szReplace = pSet->m_WRP_FLAT;
        return;
      case IDKW_STAN4           : // СТАНЧ      Сімейний стан чоловіка
        szReplace = GetFamilyStatus(pSet->m_MFAMILY_STATUS, true);
        return;
      case IDKW_STAN4P          : // СТАНЧП     Сімейний стан нареченого (необхідне підкреслити)
        szReplace = GetFamilyStatusUnderline(pSet->m_MFAMILY_STATUS, true);
        return;
      case IDKW_STANZ           : // СТАНЖ      Сімейний стан жінки
        szReplace = GetFamilyStatus(pSet->m_WFAMILY_STATUS, false);
        return;
      case IDKW_STANZP          : // СТАНЖП     Сімейний стан нареченої (необхідне підкреслити)
        szReplace = GetFamilyStatusUnderline(pSet->m_WFAMILY_STATUS, false);
        return;
      case IDKW_PASPORT4        : // ПАСПОРТЧ   Паспортні дані чоловіка
        szReplace = GetPassport(pSet->m_MPASSPORT_TYPE, pSet->m_MPASSPORT_SERIA, pSet->m_MPASSPORT_NUMBER, pSet->m_MPASSPORT_DATE, pSet->m_MPASSPORT_BY);
        return;
      case IDKW_PASPORTZ        : // ПАСПОРТЖ   Паспортні дані жінки
        szReplace = GetPassport(pSet->m_WPASSPORT_TYPE, pSet->m_WPASSPORT_SERIA, pSet->m_WPASSPORT_NUMBER, pSet->m_WPASSPORT_DATE, pSet->m_WPASSPORT_BY);
        return;
      case IDKW_SS              : // СС         Серія свідоцтва
        szReplace = pSet->m_CERTIFICATE_SERIA;
        return;
      case IDKW_NS              : // НС         Номер свідоцтва
        szReplace = pSet->m_CERTIFICATE_NUMBER;
        return;
      case IDKW_SSNS      : // ССНС     Серія свідоцтва + № + Номер свідоцтва
        if ( false==pSet->m_CERTIFICATE_SERIA.IsEmpty() && false==pSet->m_CERTIFICATE_NUMBER.IsEmpty() ) {
          szReplace.Format(_T("серія %s № %s"), pSet->m_CERTIFICATE_SERIA, pSet->m_CERTIFICATE_NUMBER);
        }
        return;
      case IDKW_POMITKY         : // ПОМІТКИ    Загальні помітки
        szReplace = ReplaceEOL(pSet->m_EXTNOTES);
        return;
      case IDKW_POMITKY4        : // ПОМІТКИЧ   Помітки чоловіка
        szReplace = pSet->m_MNOTICE;
        return;
      case IDKW_POMITKYZ        : // ПОМІТКИЖ   Помітки жінки
        szReplace = pSet->m_WNOTICE;
        return;
      case IDKW_RV4             : // РВЧ        Сімейний стан чоловіка, детально: розлучений/вдівець
        szReplace = GetState(true, pSet->m_MFAMILY_STATUS, pSet->m_MACT_NUMBER, pSet->m_MACT_DATE, pSet->m_MACT_BY);
        return;
      case IDKW_RVZ             : // РВЖ        Сімейний стан жінки, детально: розлучена/вдова
        szReplace = GetState(false, pSet->m_WFAMILY_STATUS, pSet->m_WACT_NUMBER, pSet->m_WACT_DATE, pSet->m_WACT_BY);
        return;
      case IDKW_PIBZ            : // ПІБЗ       20080303 for Marriage_38.7.7.rtf
        szReplace = g_Declarant;
        bConvert = true;
        break;
      case IDKW_PIB4_RV         : // ПІБЧ_РВ
        szReplace = MakeFIO(g_szSurnameM_RV, g_szNameM_RV, g_szPatronymicM_RV);
        bConvert = true;
        break;
      case IDKW_PIBZ_RV         : // ПІБЧ_РВ
        szReplace = MakeFIO(g_szSurnameW_RV, g_szNameW_RV, g_szPatronymicW_RV);
        bConvert = true;
        break;
      case IDKW_VRACSSH_MV      : // ВРАЦСШ_МВ
        szReplace = g_szRagsMarriage;
        return;
      case IDKW_VRACSRSH_MV     : // ВРАЦСРШ_МВ
        szReplace = g_szRagsDivorce;
        return;
      case IDKW_NAZSH           : // НАЗШ     Номер АЗ про шлюб
        szReplace = g_MarriageNum;
        return;
      case IDKW_NAZRSH          : // НАЗРШ    Номер АЗ про розірвання шлюбу
        szReplace = g_DivorceNum;
        return;
      case IDKW_DRSHLUBU        : // ДРШЛЮБУ  Дата реєстрації шлюбу
        szReplace = GetDateDDMMYYYY(g_MarriageDR);
        return;
      case IDKW_DRRSH           : // ДРРШ     Дата реєстрації розірвання шлюбу
        szReplace = GetDateDDMMYYYY(g_DivorceDR);
        return;
      default:
        IsCommonSect(pKeyword, pSet, sUpperKey, szReplace, bConvert, bFirst, &pData->fOwnerFound);
        break;
    }
  }
  else if ( sUpperKey.Left(9)==_T("ДДМММРРРР") ) {      // Дата реєстрації
    szReplace = sUpperKey.Left(9) + sTrimKey.Mid(9);
    szReplace = DDMMMRRRRR(pSet, _T("DATEREG"), szReplace);
  }
  else if ( sUpperKey.Left(8)==_T("ДДММРРРР") ) {      // Дата реєстрації: дд.мм.рррр
    szReplace = sUpperKey.Left(8) + sTrimKey.Mid(8);
    szReplace = DDMMRRRRR(pSet, _T("DATEREG"), szReplace);
  }
  else if ( sUpperKey.Left(11)==_T("ДРДДММРРРР") ) {      // Дата народження: дд.мм.рррр
    szReplace = sUpperKey.Mid(2, 8) + sTrimKey.Mid(10);
    szReplace = DDMMRRRRR(pSet, _T("DATEREG"), szReplace);
  }


  if ( false==szReplace.IsEmpty() ) {
    if ( bFirst ) {
      if ( IsCyrUpper(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt(0, CyrUpper(szReplace.GetAt(0)));
      }
      else if ( IsCyrLower(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt(0, CyrLower(szReplace.GetAt(0)));
      }
    }
    if ( bConvert ) {
      if ( sKey==sUpperKey )
        szReplace = UpperString(szReplace);
      else
        szReplace = MakeCanonicalName(szReplace);
    }
    if ( sTrimKey != sKey ) {
      sKey.Replace(sTrimKey, szReplace);
      szReplace = sKey;
    }
  }
}

BOOL IsManConvicted(const CString& szWhere, const CString& szPatronymic) {
  if ( szWhere.Find(szPatronymic) >= 0 )
    return true;
  return false;
}

CString MakeGroundForDivorce(CRSDivorces* pSet) {
  CString szGround = Trim(pSet->m_GROUND);
  if ( false==szGround.IsEmpty() ) {
    CString szNumber = Trim(pSet->m_GROUND_NUMBER);
    CString szDate   = GetDateDDMMYYYYr(pSet->m_GROUND_DATE);
    if ( false==szNumber.IsEmpty() || false==szDate.IsEmpty() ) {
      if ( szGround.Find(_T("№")) == -1 && szGround.Find(_T(" від "))== -1 ) {
        CString szIns, szNumberIns, szDateIns;
        if ( false==szNumber.IsEmpty() ) {
          szNumberIns.Format(_T(" № %s "), szNumber);
          szIns = szNumberIns;
        }
        if ( false==szDate.IsEmpty() ) {
          szDateIns.Format(_T(" від %s "), szDate);
          szIns += szDateIns;
        }
        szGround.TrimRight('.');
        szGround += szIns;
        /*
        int nFind = szGround.Find(_T(" про "));
        if ( nFind >= 0) {
          //nFind += 5;
          szGround.Insert(nFind, szIns);
          szGround.Replace(_T("  "), _T(" "));
        }
        else {
          szGround += szIns;
        }
        */
        szGround.Replace(_T("  "), _T(" "));
        szGround = Trim(szGround);
        if ( szGround.Right(1) != '.' ) {
          szGround += '.';
        }
      }
    }
  }
  return szGround;
}

void OnDivorceKeyword(LPCTSTR szKeyword, CString& szReplace, DWORD dwData) {
  KWData* pData = (KWData*)dwData;

  CRSDivorces* pSet = (CRSDivorces*)pData->pSet;

  CString sKey(szKeyword);
  CString sTrimKey = Trim(sKey);
  CString sUpperKey = UpperString(sTrimKey);
  CString sLowerKey = LowerString(sTrimKey);
  BOOL bConvert = false;
  BOOL bFirst = false;

  const Keyword* pKeyword = theKeywords.Lookup(sUpperKey);

  if ( pKeyword ) {
    switch( pKeyword->id ) {
      case IDKW_NAZ       : // НАЗ        Номер актового запису
        szReplace = GetFieldString(pSet, _T("NUMBER"));
        return;
      case IDKW_RR        : // РР         Дата реєстрації, рік: рр
        szReplace = GetYear(pSet->m_DATEREG, false);
        return;
      case IDKW_RRRR      : // РРРР       Дата реєстрації, рік: рррр
        szReplace = GetYear(pSet->m_DATEREG);
        return;
      case IDKW_MMM       : // МММ        Дата реєстрації, рік: місяця
        szReplace = GetByMonth(pSet->m_DATEREG);
        return;
      case IDKW_44        : // ЧЧ         Дата реєстрації, число
        szReplace = GetDay(pSet->m_DATEREG);
        return;
      case IDKW_PRMN      : // ПРЧН       Прізвище чоловіка ПІСЛЯ реєстрації розірвання
        szReplace = pSet->m_MNEW_SURNAME;
        bConvert = true;
        break;
      case IDKW_PRMS      : // ПРЧС       Прізвище чоловіка ДО реєстрації розірвання
        szReplace = pSet->m_MOLD_SURNAME;
        bConvert = true;
        break;
      case IDKW_PRWN      : // ПРЖН   Прізвище жінки ПІСЛЯ реєстрації розірвання
        szReplace = pSet->m_WNEW_SURNAME;
        bConvert = true;
        break;
      case IDKW_PRWS      : // ПРЖС       Прізвище жінки ДО реєстрації розірвання
        szReplace = pSet->m_WOLD_SURNAME;
        bConvert = true;
        break;
      case IDKW_PRIN      : // ПРІН       Прізвище ініциатора в родовому відмінку
        if ( IsManConvicted(pSet->m_MNOTICE, pSet->m_MPATRONYMIC) )
          szReplace = WomanSurname_RV(pSet->m_WOLD_SURNAME);
        else
          szReplace = ManSurname_RV(pSet->m_MOLD_SURNAME);
        bConvert = true;
        break;
      case IDKW_PRINOV    : // ПРІНОВ     Прізвище ініциатора в орудному відмінку
        if ( IsManConvicted(pSet->m_MNOTICE, pSet->m_MPATRONYMIC) )
          szReplace = WomanSurname_OV(pSet->m_WOLD_SURNAME);
        else
          szReplace = ManSurname_OV(pSet->m_MOLD_SURNAME);
        bConvert = true;
        break;
      case IDKW_PRBN      : // ПРБВ       Прізвище безвісно відсутнього
        if ( IsManConvicted(pSet->m_MNOTICE, pSet->m_MPATRONYMIC) )
          szReplace = ManSurname_OV(pSet->m_MOLD_SURNAME);
        else
          szReplace = WomanSurname_OV(pSet->m_WOLD_SURNAME);
        bConvert = true;
        break;
      case IDKW_PRMWN     : // ПРЧЖН      Прізвище чоловіка або жінки ПІСЛЯ реєстрації розірвання шлюбу
        szReplace = g_fDivorceDocSex ? pSet->m_MNEW_SURNAME : pSet->m_WNEW_SURNAME;
        bConvert = true;
        break;
      case IDKW_IM4       : // ІМЧ        Ім'я чоловіка
        szReplace = pSet->m_MNAME;
        bConvert = true;
        break;
      case IDKW_IMZ       : // ІМЖ        Ім'я жінки
        szReplace = pSet->m_WNAME;
        bConvert = true;
        break;
      case IDKW_IMIN      : // ІМІН       Ім'я ініциатора в родовому відмінку
        if ( IsManConvicted(pSet->m_MNOTICE, pSet->m_MPATRONYMIC) )
          szReplace = WomanName_RV(pSet->m_WNAME);
        else
          szReplace = ManName_RV(pSet->m_MNAME);
        bConvert = true;
        break;
      case IDKW_IMINOV    : // ІМІНОВ     Ім'я ініциатора в орудному відмінку
        if ( IsManConvicted(pSet->m_MNOTICE, pSet->m_MPATRONYMIC) )
          szReplace = WomanName_OV(pSet->m_WNAME);
        else
          szReplace = ManName_OV(pSet->m_MNAME);
        bConvert = true;
        break;
      case IDKW_IMBV      : // ІМБВ       Ім'я безвісно відсутнього
        if ( IsManConvicted(pSet->m_MNOTICE, pSet->m_MPATRONYMIC) )
          szReplace = ManName_OV(pSet->m_MNAME);
        else
          szReplace = WomanName_OV(pSet->m_WNAME);
        bConvert = true;
        break;
      case IDKW_PB4       : // ПБЧ        По батькові чоловіка
        szReplace = pSet->m_MPATRONYMIC;
        bConvert = true;
        break;
      case IDKW_PBZ       : // ПБЖ        По батькові жінки
        szReplace = pSet->m_WPATRONYMIC;
        bConvert = true;
        break;
      case IDKW_PBIN      : // ПБІН       По батькові ініциатора в родовому відмінку
        if ( IsManConvicted(pSet->m_MNOTICE, pSet->m_MPATRONYMIC) )
          szReplace = WomanFather_RV(pSet->m_WPATRONYMIC);
        else
          szReplace = ManFather_RV(pSet->m_MPATRONYMIC);
        bConvert = true;
        break;
      case IDKW_PBINOV    : // ПБІНОВ     По батькові ініциатора в орудному відмінку
        if ( IsManConvicted(pSet->m_MNOTICE, pSet->m_MPATRONYMIC) )
          szReplace = WomanFather_OV(pSet->m_WPATRONYMIC);
        else
          szReplace = ManFather_OV(pSet->m_MPATRONYMIC);
        bConvert = true;
        break;
      case IDKW_PBBV      : // ПББВ       По батькові безвісно відсутнього в орудному відмінку
        if ( IsManConvicted(pSet->m_MNOTICE, pSet->m_MPATRONYMIC) )
          szReplace = ManFather_OV(pSet->m_MPATRONYMIC);
        else
          szReplace = WomanFather_OV(pSet->m_WPATRONYMIC);
        bConvert = true;
        break;
      case IDKW_DATAN    : // ДАТАНЧЖ    Дата народження (чоловіка або жінки)
        if ( g_fDivorceDocSex ) {
          szReplace = GetDate(pSet->m_MBIRTH_DATE, pSet->m_MNOTICE, _T("Дата народження:"));
        }
        else {
          szReplace = GetDate(pSet->m_WBIRTH_DATE, pSet->m_WNOTICE, _T("Дата народження:"));
        }
        return;
      case IDKW_DATAN4    : // ДАТАНЧ     Дата народження чоловіка
        szReplace = GetDate(pSet->m_MBIRTH_DATE, pSet->m_MNOTICE, _T("Дата народження:"));
        return;
      case IDKW_DATANZ    : // ДАТАНЖ     Дата народження жінки
        szReplace = GetDate(pSet->m_WBIRTH_DATE, pSet->m_WNOTICE, _T("Дата народження:"));
        return;
      case IDKW_4N4       : // ЧНЧ        Дата народження чоловіка: число
        if ( COleDateTime::valid == pSet->m_MBIRTH_DATE.GetStatus())
          szReplace.Format(_T("%02d"), pSet->m_MBIRTH_DATE.GetDay() );
        return;
      case IDKW_MN4       : // МНЧ        Дата народження чоловіка: місяць
        szReplace = GetByMonth(pSet->m_MBIRTH_DATE);
        return;
      case IDKW_RN4       : // РНЧ        Дата народження чоловіка: рік РР (78)
        szReplace = GetYear(pSet->m_MBIRTH_DATE, false);
        return;
      case IDKW_RN4S      : // РНЧС       Дата народження чоловіка : рік із століттям ССРР (1978)
        szReplace = GetYear(pSet->m_MBIRTH_DATE);
        return;
      case IDKW_4NZ       : // ЧНЖ        Дата народження жінки: число
        if ( COleDateTime::valid == pSet->m_WBIRTH_DATE.GetStatus())
          szReplace.Format(_T("%02d"), pSet->m_WBIRTH_DATE.GetDay() );
        return;
      case IDKW_MNZ       : // МНЖ        Дата народження жінки: місяць
        szReplace = GetByMonth(pSet->m_WBIRTH_DATE);
        return;
      case IDKW_RNZ       : // РНЖ        Дата народження жінки: рік  РР  82
        szReplace = GetYear(pSet->m_WBIRTH_DATE, false);
        return;
      case IDKW_RNZS      : // РНЖС       Дата народження жінки із століттям: рік  РР  (1982)
        szReplace = GetYear(pSet->m_WBIRTH_DATE);
        return;
      case IDKW_GROMADYANSTVO : // ГРОМАДЯНСТВО Громадянство (чоловіка або жінки)
        if ( g_fDivorceDocSex ) {
          szReplace = GetCitizenship(true, pSet->m_MCITIZENSHIP, bFirst);
        }
        else {
          szReplace = GetCitizenship(false, pSet->m_WCITIZENSHIP, bFirst);
        }
        return;
      case IDKW_GROMADYANSTVO4  : // ГРОМАДЯНСТВОЧ  Громадянство чоловіка
        szReplace = GetCitizenship(true, pSet->m_MCITIZENSHIP, bFirst);
        bFirst = bConvert = true;
        break;
      case IDKW_GROMADYANSTVOZ  : // ГРОМАДЯНСТВОЖ  Громадянство жінки
        szReplace = GetCitizenship(false, pSet->m_WCITIZENSHIP, bFirst);
        bFirst = bConvert = true;
        return;
      case IDKW_MN4D      : // МНЧД   Місце народження чоловіка: держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_MBIRTH_COUNTRY);
        return;
      case IDKW_MN4O      : // МНЧО   Місце народження чоловіка: область
        szReplace = pSet->m_MBIRTH_REGION;
        return;
      case IDKW_MN4R      : // МНЧР     Місце народження чоловіка: район
        szReplace = pSet->m_MBIRTH_DISTRICT;
        return;
      case IDKW_MN4M      : // МНЧМ     Місце народження чоловіка: місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_MBIRTH_CITY);
        return;
      case IDKW_MN4MSS    : // МНЧМСС   Місце народження чоловіка: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_MBIRTH_CITY);
        return;
      case IDKW_MNZD      : // МНЖД     Місце народження жінки: Держава 
        szReplace = theGeoCache.FindFullCountry(pSet->m_WBIRTH_COUNTRY);
        return;
      case IDKW_MNZO      : // МНЖО     Місце народження жінки: Область
        szReplace = pSet->m_WBIRTH_REGION;
        return;
      case IDKW_MNZR      : // МНЖР     Місце народження жінки: Район
        szReplace = pSet->m_WBIRTH_DISTRICT;
        return;
      case IDKW_MNZM      : // МНЖМ     Місце народження жінки: місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_WBIRTH_CITY);
        return;
      case IDKW_MNZMSS    : // МНЖМСС   Місце народження жінки: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_WBIRTH_CITY);
        return;
      case IDKW_MP4D      : // МПЧД     Місце проживання чоловіка: Держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_MRP_COUNTRY);
        return;
      case IDKW_MPZD      : // МПЖД     Місце проживання жінки: Держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_WRP_COUNTRY);
        return;
      case IDKW_DP        : // ДП       Місце проживання (чоловіка або жінки): Держава
        szReplace = theGeoCache.FindFullCountry(g_fDivorceDocSex ? pSet->m_MRP_COUNTRY : pSet->m_WRP_COUNTRY);
        return;
      case IDKW_MP4O      : // МПЧО     Місце проживання чоловіка: Область
        szReplace = pSet->m_MRP_REGION;
        return;
      case IDKW_MPZO      : // МПЖО     Місце проживання жінки: Область
        szReplace = pSet->m_WRP_REGION;
        return;
      case IDKW_OP        : // ОП       Місце проживання (чоловіка або жінки): Область
        szReplace = g_fDivorceDocSex ? pSet->m_MRP_REGION : pSet->m_WRP_REGION;
        return;
      case IDKW_OPOBL     : // ОПОБЛ      Місце проживання (чоловіка або жінки): Область + область
        szReplace = GetRegion(g_fDivorceDocSex ? pSet->m_MRP_REGION : pSet->m_WRP_REGION, true);
        return;
      case IDKW_OPOBLAST  : // ОПОБЛАСТЬ  Місце проживання (чоловіка або жінки): Область + область
        szReplace = GetRegion(g_fDivorceDocSex ? pSet->m_MRP_REGION : pSet->m_WRP_REGION, false);
        return;
      case IDKW_OPOBL_    : // ОПОБЛ.     Місце проживання (чоловіка або жінки): Область + обл.
        return;
      case IDKW_MP4OBL    : // МПЧОБЛ     Місце проживання чоловіка: Область + область
      case IDKW_MP4OBLAST : // МПЧОБЛАСТЬ Місце проживання чоловіка: Область + область
        szReplace = GetRegion(pSet->m_MRP_REGION, false);
        return;
      case IDKW_MP4OBL_   : // МПЧОБЛ.    Місце проживання чоловіка: Область + обл.
        szReplace = GetRegion(pSet->m_MRP_REGION, true);
        return;
      case IDKW_MPZOBL    : // МПЖОБЛ     Місце проживання жінки: Область + область
      case IDKW_MPZOBLAST : // МПЖОБЛАСТЬ Місце проживання жінки: Область + область
        szReplace = GetRegion(pSet->m_WRP_REGION, false);
        return;
      case IDKW_MPZOBL_   : // МПЖОБЛ.    Місце проживання жінки: Область + обл.
        szReplace = GetRegion(pSet->m_WRP_REGION, true);
        return;
      case IDKW_MP4R       : // МПЧР        Місце проживання чоловіка: Район
        szReplace = pSet->m_MRP_DISTRICT;
        return;
      case IDKW_MP4R_N     : // МПЧР-Н      Місце проживання чоловіка: Район + р-н
        szReplace = GetDistrict(pSet->m_MRP_DISTRICT, true);
        return;
      case IDKW_MP4RAYON   : // МПЧРАЙОН    Місце проживання чоловіка: Район + район
        szReplace = GetDistrict(pSet->m_MRP_DISTRICT, false);
        return;
      case IDKW_MPZR       : // МПЖР        Місце проживання жінки: Район
        szReplace = pSet->m_WRP_DISTRICT;
        return;
      case IDKW_MPZR_N     : // МПЖР-Н      Місце проживання жінки: Район + р-н
        szReplace = GetDistrict(pSet->m_WRP_DISTRICT, true);
        return;
      case IDKW_MPZRAYON   : // МПЖРАЙОН    Місце проживання жінки: Район + район
        szReplace = GetDistrict(pSet->m_WRP_DISTRICT, false);
        return;
      case IDKW_RP         : // РП          Місце проживання (чоловіка або жінки): Район
        szReplace = g_fDivorceDocSex ? pSet->m_MRP_DISTRICT : pSet->m_WRP_DISTRICT;
        return;
      case IDKW_RPRAYON    : // РПРАЙОН     Місце проживання (чоловіка або жінки): Район + район
        szReplace = GetDistrict(g_fDivorceDocSex ? pSet->m_MRP_DISTRICT : pSet->m_WRP_DISTRICT, false);
        return;
      case IDKW_RPR_N      : // РПР-Н       Місце проживання (чоловіка або жінки): Район + р-н
        szReplace = GetDistrict(g_fDivorceDocSex ? pSet->m_MRP_DISTRICT : pSet->m_WRP_DISTRICT, true);
        return;
      case IDKW_MSS        : // МСС         Місце проживання (чоловіка або жінки): місто (село, селище) - тип НП
        szReplace = TypeOfCity(g_fDivorceDocSex ? pSet->m_MRP_CITY : pSet->m_WRP_CITY);
        return;
      case IDKW_MSS4       : // МССЧ        Місце проживання чоловіка: місто (село, селище) - тип НП
      case IDKW_MP4MSS     : // МПЧМСС      Місце проживання чоловіка: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_MRP_CITY);
        return;
      case IDKW_MSSZ       : // МССЖ        Місце проживання жінки: місто (село, селище) - тип НП
      case IDKW_MPZMSS     : // МПЖМСС      Місце проживання жінки: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_WRP_CITY);
        return;
      case IDKW_MP4M       : // МПЧМ        Місце проживання чоловіка: місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_MRP_CITY);
        return;
      case IDKW_MPZM       : // МПЖМ        Місце проживання жінки: місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_WRP_CITY);
        return;
      case IDKW_MP         : // МП          Місце проживання (чоловіка або жінки): місто (село, селище) - назва НП
        szReplace = GetCity(g_fDivorceDocSex ? pSet->m_MRP_CITY : pSet->m_WRP_CITY);
        return;
      case IDKW_VUL        : // ВУЛ         Місце проживання (чоловіка або жінки): вулиця
        szReplace = g_fDivorceDocSex ? pSet->m_MRP_STREET : pSet->m_WRP_STREET;
        return;
      case IDKW_VUL4       : // ВУЛЧ        Місце проживання чоловіка: вулиця
        szReplace = pSet->m_MRP_STREET;
        return;
      case IDKW_VULZ       : // ВУЛЖ        Місце проживання жінки: вулиця
        szReplace = pSet->m_WRP_STREET;
        return;
      case IDKW_BUD        : // БУД         Місце проживання (чоловіка або жінки): будинок
        szReplace = g_fDivorceDocSex ? pSet->m_MRP_HOUSE : pSet->m_WRP_HOUSE;
        return;
      case IDKW_BUD4       : // БУДЧ        Місце проживання чоловіка: будинок
        szReplace = pSet->m_MRP_HOUSE;
        return;
      case IDKW_BUDZ       : // БУДЖ        Місце проживання жінки: будинок
        szReplace = pSet->m_WRP_HOUSE;
        return;
      case IDKW_KV         : // КВ          Місце проживання (чоловіка або жінки): квартира
        szReplace = g_fDivorceDocSex ? pSet->m_MRP_FLAT : pSet->m_WRP_FLAT;
        return;
      case IDKW_KV4        : // КВЧ         Місце проживання чоловіка: квартира
        szReplace = pSet->m_MRP_FLAT;
        return;
      case IDKW_KVZ        : // КВЖ         Місце проживання жінки: квартира
        szReplace = pSet->m_WRP_FLAT;
        return;
      case IDKW_ADRESA     : // АДРЕСА      Адреса чоловіка або жінки
        if ( g_fDivorceDocSex )
          szReplace = GetAddress(pSet->m_MRP_COUNTRY, pSet->m_MRP_REGION, pSet->m_MRP_CITY, pSet->m_MRP_DISTRICT, pSet->m_MRP_STREET, pSet->m_MRP_HOUSE, pSet->m_MRP_FLAT, TRUE);
        else
          szReplace = GetAddress(pSet->m_WRP_COUNTRY, pSet->m_WRP_REGION, pSet->m_WRP_CITY, pSet->m_WRP_DISTRICT, pSet->m_WRP_STREET, pSet->m_WRP_HOUSE, pSet->m_WRP_FLAT, TRUE);
        return;
      case IDKS_PSH       : // ПШ           Перебував(ла) у шлюбі: чоловік (жінка)
        if ( g_fDivorceDocSex )
          szReplace = GetNumMarriageStr(pSet->m_MMARRIAGE_NUMBER, pSet->m_MNEW_SURNAME);
        else
          szReplace = GetNumMarriageStr(pSet->m_WMARRIAGE_NUMBER, pSet->m_WNEW_SURNAME);
        return;
      case IDKS_PSH4      : // ПШЧ          Перебував у шлюбі: чоловік
        szReplace = GetNumMarriage(pSet->m_MMARRIAGE_NUMBER, pSet->m_MNEW_SURNAME);
        return;
      case IDKS_PSHZ      : // ПШЖ          Перебувала у шлюбі: жінка
        szReplace = GetNumMarriage(pSet->m_WMARRIAGE_NUMBER, pSet->m_WNEW_SURNAME);
        return;
      case IDKW_RACSSH_MV : // РАЦСШ_МВ     РАЦС шлюбу у місцевому відмінку
      case IDKW_RAGSSH_MV : // РАГСШ_МВ     РАЦС шлюбу у місцевому відмінку
        szReplace = SVRagsC(pSet->m_MARRIAGE_BY, RC_MV);
        return;
      case IDKW_RACSSH_OV : // РАЦСШ_ОВ     РАЦС шлюбу в орудному відмінку
      case IDKW_RAGSSH_OV : // РАГСШ_ОВ     РАЦС шлюбу в орудному відмінку
        szReplace = SVRagsC(pSet->m_MARRIAGE_BY, RC_OV);
        return;
      case IDKW_NAZSH     : // НАЗШ         Номер актового запису про шлюб
        szReplace.Format(_T("%d"), pSet->m_MARRIAGE_NUMBER);
        return;
      case IDKW_DATASH    : // ДАТАШ        Дата реєстрації шлюбу
        szReplace = GetDateDDMMYYYY(pSet->m_MARRIAGE_DATE);
        return;
      case IDKW_PIDSTAVA  : // ПІДСТАВА
      case IDKW_PIDSTAVY  : // ПІДСТАВИ
        szReplace = MakeGroundForDivorce(pSet);
        bFirst = true;
        break;
      case IDKW_POSTANOVY : // ПОСТАНОВИ
        if ( 0 <= pSet->m_GROUND_TYPE && pSet->m_GROUND_TYPE <= 3 ) {
          szReplace.Format(_T("%s № %s від %s"), pSet->m_GROUND, pSet->m_GROUND_NUMBER, GetDateDDMMYYYYr(pSet->m_GROUND_DATE) );
        }
        if ( szReplace.Left(9)==_T("Постанова") )
          szReplace.Replace(_T("Постанова"), _T("Постанови") );
        bFirst = true;
        break;
      case IDKW_VYROK    : // ВИРОК
        if ( 3==pSet->m_GROUND_TYPE ) {
          szReplace = GetSentence( pSet->m_MNOTICE, _T("Вирок "), _T("р.") );
          szReplace.Replace( _T("Вирок "), _T("") );
        }
        return;
      case IDKW_RISHENNYA: // РІШЕННЯ   Рішення
        szReplace = GetSentence( pSet->m_MNOTICE, _T("Рішення"), _T("р.") );
        szReplace.Replace( _T("Рішення "), _T("") );
        return;
      case IDKW_RSUDU    : // РСУДУ
        if ( 4==pSet->m_GROUND_TYPE ) {
          szReplace.Format(_T("%s від %s"), pSet->m_GROUND, GetDateDDMMYYYYr(pSet->m_GROUND_DATE) );
        }
        else {
          BOOL fSex = IsManConvicted(pSet->m_MNOTICE, pSet->m_MPATRONYMIC);
          szReplace = GetSentence( pSet->m_MNOTICE, _T("Рішення "), _T("відсутнім.") );
          if ( szReplace.IsEmpty() )
            szReplace = GetSentence( pSet->m_MNOTICE, _T("Рішення "), _T("відсутнєю.") );
          if ( szReplace.IsEmpty() )
            szReplace = GetSentence( pSet->m_MNOTICE, _T("Рішення "), _T("хвороби.") );
          if ( szReplace.IsEmpty() )
            szReplace = GetSentence( pSet->m_MNOTICE, _T("Рішення "), _T("недоумства.") );
          if ( szReplace.IsEmpty() )
            szReplace = GetSentence( pSet->m_MNOTICE, _T("Рішення "), _T("недієздатним.") );
          if ( szReplace.IsEmpty() )
            szReplace = GetSentence( pSet->m_MNOTICE, _T("Рішення "), _T("недієздатною.") );
          if ( szReplace.IsEmpty() )
            szReplace = GetSentence( pSet->m_MNOTICE, _T("Вирок "), _T("роки.") );
          if ( szReplace.IsEmpty() )
            szReplace = GetSentence( pSet->m_MNOTICE, _T("Вирок "), _T("років.") );

          if ( fSex ) {
            szReplace.Replace( _T("Вирок "), _T("засудженим вироком ") );
            if ( szReplace.Find(" визнання") >= 0 ) {
              szReplace.Replace( _T("Рішення "), _T("визнаний рішенням ") );
            }
          }
          else {
            szReplace.Replace( _T("Вирок "), _T("засудженою вироком ") );
            if ( szReplace.Find(" визнання") >= 0 ) {
              szReplace.Replace( _T("Рішення "), _T("визнаною рішенням ") );
            }
          }
        }
        bFirst = true;
        break;
      case IDKW_KDITEY   :
        switch(pSet->m_NKIDS) {
          case 0: szReplace = theIniCache.GetDIVORCE_NoChildren();
            break;
          case 1: szReplace = theIniCache.GetDIVORCE_SingleChild();
            break;
          default:
            if ( 1 < pSet->m_NKIDS && pSet->m_NKIDS < 99 )
              szReplace.Format(_T("%s."), GetNKids(pSet->m_NKIDS) );
            break;
        }
        bFirst = true;
        break;
      case IDKW_S14 : // С1Ч
        szReplace = GetTax(TRUE, pSet->m_MMONEY_TYPE, pSet->m_MDUTY, pSet->m_MDUTY2, false);
        return;
      case IDKW_S1Z : // С1Ж
        szReplace = GetTax(FALSE, pSet->m_WMONEY_TYPE, pSet->m_WDUTY, pSet->m_WDUTY2, false);
        return;
      case IDKW_S24 : // С2Ч
        szReplace = GetCash(pSet->m_MDUTY, pSet->m_MDUTY2);
        return;
      case IDKW_S2Z : // С2Ж
        szReplace = GetCash(pSet->m_WDUTY, pSet->m_WDUTY2);
        return;
      case IDKW_ZVILNENA  : // ЗВІЛЬНЕНА    Від сплати держмита звільнена
        szReplace = GetFreeUp(FALSE, pSet->m_WDUTY);
        return;
      case IDKW_ZVILNENY  : // ЗВІЛЬНЕНИЙ   Від сплати держмита звільнений
        szReplace = GetFreeUp(TRUE, pSet->m_MDUTY);
        return;
      case IDKW_NK4       : // НКЧ          Номер квітанції чоловіка
        szReplace = pSet->m_MCHECK_NUMBER;
        return;
      case IDKW_NKZ       : // НКЖ          Номер квітанції жінки
        szReplace = pSet->m_WCHECK_NUMBER;
        return;
      case IDKW_DK4       : // ДКЧ          Дата квітанції чоловіка
        szReplace = GetDateDDMMYYYYr(pSet->m_MCHECK_DATE);
        return;
      case IDKW_DKZ       : // ДКЖ          Дата квітанції жінки
        szReplace = GetDateDDMMYYYYr(pSet->m_WCHECK_DATE);
        return;
      case IDKW_BANK4     : // БАНКЧ        Банк чоловіка
        szReplace = pSet->m_MCHECK_BANK;
        return;
      case IDKW_BANKZ     : // БАНКЖ        Банк жінки
        szReplace = pSet->m_WCHECK_BANK;
        return;
      case IDKW_DERZMYTO  : // ДЕРЖМИТО     Держмито
        {
          bool bFree = GetBoolFreeUp(g_fDivorceDocSex ? pSet->m_MDUTY : pSet->m_WDUTY);
          COleCurrency dMNew = g_fDivorceDocSex ? pSet->m_MDUTY : pSet->m_WDUTY2,
                       dMOld = g_fDivorceDocSex ? pSet->m_MDUTY2 : pSet->m_WDUTY2;
          BYTE bMoneyType = g_fDivorceDocSex ? pSet->m_MMONEY_TYPE : pSet->m_WMONEY_TYPE;
          if ( bFree ) {
            szReplace = GetFreeUp(g_fDivorceDocSex, g_fDivorceDocSex ? pSet->m_MDUTY : pSet->m_WDUTY);
          }
          else {
            if ( COleCurrency::valid==dMNew.GetStatus() ) {
              CString sCheckNumber = g_fDivorceDocSex ? pSet->m_MCHECK_NUMBER : pSet->m_WCHECK_NUMBER;
              CString sCheckDate = GetDateDDMMYYYYr( g_fDivorceDocSex ? pSet->m_MCHECK_DATE : pSet->m_WCHECK_DATE );
              CString sCheckBank = g_fDivorceDocSex ? pSet->m_MCHECK_BANK : pSet->m_WCHECK_BANK;
              szReplace.Format(_T("Сума держмита %s %s, квитанція № %s від %s %s"),
                                GetTax(g_fDivorceDocSex, bMoneyType, dMNew, dMOld, false),
                                GetCash(dMNew, dMOld), sCheckNumber, sCheckDate, sCheckBank );
            }
          }
        }
        return;
      case IDKW_PASPORT    : // ПАСПОРТ     Паспортні дані (чоловіка або жінки)
        szReplace = g_fDivorceDocSex ? GetPassport(pSet->m_MPASSPORT_TYPE, pSet->m_MPASSPORT_SERIA, pSet->m_MPASSPORT_NUMBER, pSet->m_MPASSPORT_DATE, pSet->m_MPASSPORT_BY)
                                     : GetPassport(pSet->m_WPASSPORT_TYPE, pSet->m_WPASSPORT_SERIA, pSet->m_WPASSPORT_NUMBER, pSet->m_WPASSPORT_DATE, pSet->m_WPASSPORT_BY);
        return;
      case IDKW_PASPORT4   : // ПАСПОРТЧ    Паспортні дані чоловіка
        szReplace = GetPassport(pSet->m_MPASSPORT_TYPE, pSet->m_MPASSPORT_SERIA, pSet->m_MPASSPORT_NUMBER, pSet->m_MPASSPORT_DATE, pSet->m_MPASSPORT_BY);
        return;
      case IDKW_PASPORTZ   : // ПАСПОРТЖ    Паспортні дані жінки
        szReplace = GetPassport(pSet->m_WPASSPORT_TYPE, pSet->m_WPASSPORT_SERIA, pSet->m_WPASSPORT_NUMBER, pSet->m_WPASSPORT_DATE, pSet->m_WPASSPORT_BY);
        return;
      case IDKW_SS         : // СС          Серія свідоцтва (чоловіка або жінки)
        szReplace = g_fDivorceDocSex ? pSet->m_MCERTIFICATE_SERIA : pSet->m_WCERTIFICATE_SERIA;
        return;
      case IDKW_SS4        : // ССЧ         Серія свідоцтва чоловіка
        szReplace = pSet->m_MCERTIFICATE_SERIA;
        return;
      case IDKW_SSZ        : // ССЖ         Серія свідоцтва жінки
        szReplace = pSet->m_WCERTIFICATE_SERIA;
        return;
      case IDKW_NS         : // НС          Номер свідоцтва (чоловіка або жінки)
        szReplace = g_fDivorceDocSex ? pSet->m_MCERTIFICATE_NUMBER : pSet->m_WCERTIFICATE_NUMBER;
        return;
      case IDKW_NS4        : // НСЧ         Номер свідоцтва чоловіка
        szReplace = pSet->m_MCERTIFICATE_NUMBER;
        return;
      case IDKW_NSZ        : // НСЖ         Номер свідоцтва жінки
        szReplace = pSet->m_WCERTIFICATE_NUMBER;
        return;
      case IDKW_MISCENAR4  : // МІСЦЕНАРЧ   Місце народження чоловіка
        szReplace = GetBirthPlaceForDivorce(pSet, true);
        return;
      case IDKW_MISCENARZ  : // МІСЦЕНАРЖ   Місце народження жінки
        szReplace = GetBirthPlaceForDivorce(pSet, false);
        return;
      case IDKW_POMITKY4   : // ПОМІТКИЧ    Помітки чоловіка
        szReplace = pSet->m_MNOTICE;
        return;
      case IDKW_POMITKYZ   : // ПОМІТКИЖ    Помітки жінки
        szReplace = pSet->m_WNOTICE;
        return;
      case IDKW_PR4OV      : // ПРЧОВ       Прізвище чоловіка в орудному відмінку
        szReplace = g_sMSurname_OV;
        bConvert = true;
        break;
      case IDKW_PRZOV      : // ПРЖОВ       Прізвище жінки в орудному відмінку
        szReplace = g_sWSurname_OV;
        bConvert = true;
        break;
      case IDKW_IM4OV      : // ІМЧОВ       Ім'я чоловіка в орудному відмінку
        szReplace = g_sMName_OV;
        bConvert = true;
        break;
      case IDKW_IMZOV      : // ІМЖОВ       Ім'я жінки в орудному відмінку
        szReplace = g_sWName_OV;
        bConvert = true;
        break;
      case IDKW_PB4OV      : // ПБЧОВ       По батькові чоловіка в орудному відмінку
        szReplace = g_sMPatronymic_OV;
        bConvert = true;
        break;
      case IDKW_PBZOV      : // ПБЖОВ       По батькові жінки в орудному відмінку
        szReplace = g_sWPatronymic_OV;
        bConvert = true;
        break;
      case IDKW_PRKVS      : // ПРКВС       Прізвище (кому видано свідоцтво)
      case IDKW_PRRV       : // ПРРВ        Прізвище у родовому відмінку
        szReplace = g_SurnameTo;
        bConvert = true;
        break;
      case IDKW_IMKVS      : // ІМКВС       Ім'я (кому видано свідоцтво) в орудному відмінку
      case IDKW_IMRV       : // ІМРВ        Ім'я у родовому відмінку
        szReplace = g_NameTo;
        bConvert = true;
        break;
      case IDKW_PBKVS      : // ПБКВС       По батькові (кому видано свідоцтво)
      case IDKW_PBRV       : // ПБРВ        По батькові у родовому відмінку
        szReplace = g_PatronymicTo;
        bConvert = true;
        break;
      case IDKW_PDT44      : // ПДТЧЧ       першому другому третьому четвертому (чоловік)
        szReplace = GetNumMarriage2(pSet->m_MMARRIAGE_NUMBER);
        break;
      case IDKW_PDT4Z      : // ПДТЧЖ       першому другому третьому четвертому (жінка)
        szReplace = GetNumMarriage2(pSet->m_WMARRIAGE_NUMBER);
        break;
      default:
        IsCommonSect(pKeyword, pSet, sUpperKey, szReplace, bConvert, bFirst, &pData->fOwnerFound);
        break;
    }
  }

  else if ( sUpperKey.Left(5)==_T("ПРЧНП") ){ // Прізвище чоловіка ПІСЛЯ реєстрації розірвання невідоме (ПРОЧЕРК)
    szReplace = pSet->m_MNEW_SURNAME;
    if ( IsEmptyText(szReplace) ) {
      int nSpaces = atoi(sUpperKey.Mid(5));
      if ( 0==nSpaces ) nSpaces = 20;
      szReplace = CString('-', nSpaces);
    }
    bConvert = true;
  }
  else if ( sUpperKey.Left(5)==_T("ПРЖНП") ) { // Прізвище жінки ПІСЛЯ реєстрації розірвання невідоме (ПРОЧЕРК)
    szReplace = pSet->m_WNEW_SURNAME;
    if ( IsEmptyText(szReplace) ) {
      int nSpaces = atoi(sUpperKey.Mid(5));
      if ( 0==nSpaces ) nSpaces = 20;
      szReplace = CString('-', nSpaces);
    }
    bConvert = true;
  }
  else if ( sUpperKey.Left(9)==_T("ДДМММРРРР") ) {     // Дата реєстрації
    szReplace = sUpperKey.Left(9) + sTrimKey.Mid(9);
    szReplace = DDMMMRRRRR(pSet, _T("DATEREG"), szReplace);
  }
  else if ( sUpperKey.Left(8)==_T("ДДММРРРР") ) {      // Дата реєстрації: дд.мм.рррр
    szReplace = sUpperKey.Left(8) + sTrimKey.Mid(8);
    szReplace = DDMMRRRRR(pSet, _T("DATEREG"), szReplace);
  }

  if ( false==szReplace.IsEmpty() ) {
    if ( bFirst ) {
      if ( IsCyrUpper(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt( 0, CyrUpper(szReplace.GetAt(0)) );
      }
      else if ( IsCyrLower(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt( 0, CyrLower(szReplace.GetAt(0)) );
      }
    }
    if ( bConvert ) {
      if ( sKey==sUpperKey )
        szReplace = UpperString(szReplace);
      else
        szReplace = MakeCanonicalName(szReplace);
    }
    if ( sTrimKey != sKey ) {
      sKey.Replace(sTrimKey, szReplace);
      szReplace = sKey;
    }
  }
}

void OnChangeKeyword(LPCTSTR szKeyword, CString& szReplace, DWORD dwData) {
  KWData* pData = (KWData*)dwData;
  CRSChanges* pSet = (CRSChanges*)pData->pSet;

  CString sKey(szKeyword);
  CString sTrimKey = Trim(sKey);
  CString sUpperKey = UpperString(sTrimKey);
  CString sLowerKey = LowerString(sTrimKey);
  BOOL bConvert = false;
  BOOL bFirst = false;

  const Keyword* pKeyword = theKeywords.Lookup(sUpperKey);
  if ( pKeyword ) {
    switch( pKeyword->id ) {
      case IDKW_NAZ       : // НАЗ        Номер актового запису
        szReplace = GetFieldString(pSet, _T("NUMBER"));
        return;
      case IDKW_RR        : // РР         Дата реєстрації, рік: рр
        szReplace = GetYear(pSet->m_DATEREG, false);
        return;
      case IDKW_RRRR      : // РРРР       Дата реєстрації, рік: рррр
        szReplace = GetYear(pSet->m_DATEREG);
        return;
      case IDKW_MMM       : // МММ        Дата реєстрації, рік: місяця
        szReplace = GetByMonth(pSet->m_DATEREG);
        return;
      case IDKW_44        : // ЧЧ         Дата реєстрації, число
        szReplace = GetDay(pSet->m_DATEREG);
        return;
      case IDKW_STPR      : // СТПР       Старе прізвище (ДО зміни)
        szReplace = pSet->m_OLDSURNAME;
        bConvert = true;
        break;
      case IDKW_STPR_DV   : // СТПР_ДВ    Прізвище ДО зміни в давальному відмінку
        szReplace = g_szSurname_DV;
        bConvert = true;
        break;
      case IDKW_STPR_RV   : // СТПР_РВ    Прізвище ДО зміни в родовому відмінку
        szReplace = g_szSurname_RV;
        bConvert = true;
        break;
      case IDKW_NPR       : // НПР        Прізвище ПІСЛЯ зміни
        szReplace = pSet->m_NEWSURNAME;
        bConvert = true;
        break;
      case IDKW_NPR_      : // НПР-       Прізвище ПІСЛЯ зміни або прочерк
        szReplace = pSet->GetNewSurnameOrLine();
        bConvert = true;
        break;
      case IDKW_STIM      : // СТІМ       Старе ім'я (ДО зміни)
        szReplace = pSet->m_OLDNAME;
        bConvert = true;
        break;
      case IDKW_STIM_DV   : // СТІМ_ДВ    Старе ім'я (ДО зміни) в давальному відмінку
        szReplace = g_szName_DV;
        bConvert = true;
        break;
      case IDKW_STIM_RV   : // СТІМ_РВ    Старе ім'я (ДО зміни) в родовому відмінку
        szReplace = g_szName_RV;
        bConvert = true;
        break;
      case IDKW_NIM       : // НІМ        Нове ім'я (ПІСЛЯ зміни)
        szReplace = pSet->m_NEWNAME;
        bConvert = true;
        break;
      case IDKW_NIM_      : // НІМ-       Нове ім'я (ПІСЛЯ зміни) або прочерк
        szReplace = pSet->GetNewNameOrLine();
        bConvert = true;
        break;
      case IDKW_STPB      : // СТПБ       Старе по батькові (ДО зміни)
        szReplace = pSet->m_OLDPATRONYMIC;
        bConvert = true;
        break;
      case IDKW_STPB_DV   : // СТПБ_ДВ    Старе по батькові (ДО зміни) в давальному відмінку
        szReplace = g_szPatronymic_DV;
        bConvert = true;
        break;
      case IDKW_STPB_RV   : // СТПБ_РВ    Старе по батькові (ДО зміни) в родовому відмінку
        szReplace = g_szPatronymic_RV;
        bConvert = true;
        break;
      case IDKW_NPB       : // НПБ        Нове по батькові (ПІСЛЯ зміни)
        szReplace = pSet->m_NEWPATRONYMIC;
        bConvert = true;
        break;
      case IDKW_NPB_      : // НПБ-       Нове по батькові (ПІСЛЯ зміни) або прочерк
        szReplace = pSet->GetNewPatronymicOrLine();
        bConvert = true;
        break;
      case IDKW_DATAN     : // ДАТАН      Дата народження
        szReplace = GetFieldDate(pSet, _T("BIRTH_DATE"), false);
        return;
      case IDKW_44N       : // ЧЧН        Дата народження: дд
      case IDKW_DN44      : // ДНЧЧ       Дата народження: дд (число)
        szReplace = GetDay(pSet->m_BIRTH_DATE);
        return;
      case IDKW_DNMMM     : // ДНМММ      Дата народження: ммм
      case IDKW_MMMN      : // МММН       Дата народження: місяць
        szReplace = GetByMonth(pSet->m_BIRTH_DATE);
        return;
      case IDKW_DNRR      : // ДНРР       Дата народження: рр
      case IDKW_RRN       : // РРН        Дата народження, рік: рр
        szReplace = GetYear(pSet->m_BIRTH_DATE, false);
        return;
      case IDKW_DNRRRR    : // ДНРРРР     Дата народження: рррр
      case IDKW_RRRRN     : // РРРРН      Дата народження, рік: рррр
        szReplace = GetYear(pSet->m_BIRTH_DATE);
        return;
      case IDKW_DN        : // ДН         Держава народження
      case IDKW_MND       : // МНД        Місце народження: держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_BIRTH_COUNTRY);
        return;
      case IDKW_ON        : // ОН         Місце народження: Область
      case IDKW_MNO       : // МНО        Місце народження: область
        szReplace = pSet->m_BIRTH_REGION;
        return;
      case IDKW_MNOBL     : // МНОБЛ      Місце народження: область + область
      case IDKW_ONOBL     : // ОНОБЛ      Місце народження: Область + область
      case IDKW_ONOBLAST  : // ОНОБЛАСТЬ  Місце народження: Область + область
        szReplace = GetRegion(GetFieldString(pSet, _T("BIRTH_REGION")), false);
        return;
      case IDKW_MNOBL_    : // МНОБЛ.     Місце народження: область + обл.
        szReplace = GetRegion(GetFieldString(pSet, _T("BIRTH_REGION")), true);
        return;
      case IDKW_RN        : // РН         Місце народження: Район
      case IDKW_MNR       : // МНР        Місце народження: Район
        szReplace = pSet->m_BIRTH_DISTRICT;
        return;
      case IDKW_RNRAYON   : // РНРАЙОН    Місце народження: Район + район
      case IDKW_MNRAYON   : // МНРАЙОН    Місце народження: Район + район
        szReplace = GetDistrict(pSet->m_BIRTH_DISTRICT, false);
        return;
      case IDKW_RNR_N     : // РНР-Н      Місце народження: Район + р-н
      case IDKW_MNR_N     : // МНР-Н      Місце народження: Район + р-н
        szReplace = GetDistrict(pSet->m_BIRTH_DISTRICT, true);
        return;
      case IDKW_MSSN      : // МССН       Місце народження: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_BIRTH_CITY);
        return;
      case IDKW_MN        : // МН         Місце народження: місто (село, селище) - назва НП
      case IDKW_MNM       : // МНМ        Місце народження: місто (село, селище) - назва населенного пункту
        szReplace = GetCity(pSet->m_BIRTH_CITY);
        return;
      case IDKW_DP        : // ДП         Держава проживання
        szReplace = theGeoCache.FindFullCountry(pSet->m_COUNTRY);
        return;
      case IDKW_OP        : // ОП         Місце проживання: Область
        szReplace = pSet->m_REGION;
        return;
      case IDKW_OPOBL     : // ОПОБЛ      Місце проживання: Область + область
      case IDKW_OPOBLAST  : // ОПОБЛАСТЬ  Місце проживання: Область + область
        szReplace = GetRegion(GetFieldString(pSet, _T("REGION")), false);
        return;
      case IDKW_OPOBL_    : // ОПОБЛ.     Місце проживання: Область + обл.
        szReplace = GetRegion(GetFieldString(pSet, _T("REGION")), true);
        return;
      case IDKW_RP        : // РП         Місце проживання: Район
        szReplace = pSet->m_DISTRICT;
        return;
      case IDKW_RPRAYON   : // РПРАЙОН    Місце проживання: Район + район
        szReplace = GetDistrict(pSet->m_DISTRICT, false);
        return;
      case IDKW_RPR_N     : // РПР-Н      Місце проживання: Район + р-н
        szReplace = GetDistrict(pSet->m_DISTRICT, true);
        return;
      case IDKW_MSSP      : // МССП       Місце проживання: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_CITY);
        return;
      case IDKW_MP        : // МП         Місце проживання: Місто
        szReplace = GetCity(pSet->m_CITY);
        return;
      case IDKW_VUL       : // ВУЛ        Місце проживання: вулиця
        szReplace = pSet->m_STREET;
        return;
      case IDKW_BUD       : // БУД        Місце проживання: будинок
        szReplace = pSet->m_HOUSE;
        return;
      case IDKW_KV        : // КВ         Місце проживання: квартира
        szReplace = pSet->m_FLAT;
        return;
      case IDKW_NAZN      : // НАЗН       Номер АЗ про народження
        szReplace = GetFieldString(pSet, _T("BIRTHACT_NUMBER"));
        return;
      case IDKW_DAZN      : // ДАЗН       Дата АЗ про народження
        szReplace = GetFieldDate(pSet, _T("BIRTHACT_DATE"), true);
        return;
      case IDKW_GROMADYANSTVO : // ГРОМАДЯНСТВО   Громадянство
        szReplace = GetCitizenship(pSet->m_SEX, pSet->m_CITIZENSHIP, bFirst);
        break;
      case IDKW_SPLA4ENO  : // СПЛАЧЕНО   Сплачено держмита
        if ( COleCurrency::valid==pSet->m_DUTY.GetStatus() && pSet->m_DUTY > g_ocZero ) {
          szReplace.Format(_T("сплачено %s грн."), UAH(pSet->m_DUTY) );
        }
        return;
      case IDKW_NK        : // НК         Номер квітанції
        szReplace = pSet->m_CHECKNUM;
        return;
      case IDKW_DK        : // ДК         Дата квітанції
        szReplace = GetFieldDate(pSet, _T("CHECKDATE"), true);
        return;
      case IDKW_BANK      : // БАНК       Банк, де сплачено держмито
        szReplace = pSet->m_CHECKBANK;
        return;
      case IDKW_PASPORT   : // ПАСПОРТ    Паспортні дані (чоловіка або жінки)
        szReplace = GetPassport(pSet->m_PASSPORT_TYPE, pSet->m_PASSPORT_SERIA, pSet->m_PASSPORT_NUMBER, pSet->m_PASSPORT_DATE, pSet->m_PASSPORT_BY);
        return;
      case IDKW_SS        : // СС         Серія свідоцтва
        szReplace = pSet->m_CERTIFICATE_SERIA;
        return;
      case IDKW_NS        : // НС         Номер свідоцтва
        szReplace = pSet->m_CERTIFICATE_NUMBER;
        return;
      case IDKW_POMITKY   : // ПОМІТКИ    Помітки
        szReplace = ReplaceEOL(pSet->GetNotices());
        return;
      case IDKW_ZMINY     : // ЗМІНИ      Які зміни належить внести до АЗ (повідомлення про внесення змін)
        szReplace = g_szChanges;
        return;
      case IDKW_AZPRO     : // АЗПРО      АЗ "про", наприклад про "народження"
        szReplace = g_szChangeAct;
        return;
      case IDKW_AZPRODATA : // АЗПРОДАТА  Дата АЗ "про", наприклад дата АЗ про "народження"
        szReplace = g_szChangeDate;
        return;
      case IDKW_AZPRONAZ  : // АЗПРОНАЗ   № АЗ, де належить внести зміни
        szReplace = g_szChangeNumber;
        return;
      case IDKW_ADRESA    : // АДРЕСА     Адреса
      case IDKW_ADRZ      : // АДРЗ       Адреса заявника
        szReplace = g_ChangeAddr;
        return;
      case IDKW_PIBZ      : // ПІБЗ       ПІБ заявника
        szReplace = g_Declarant;
        bConvert = true;
        break;
      case IDKW_PRIMPB    : // ПРІМПБ     Прізвище, ім'я, по батькові (27)
        szReplace = g_ChangePrImPb;
        bConvert = true;
        break;
      case IDKW_PRIMPBRV  : // ПРІМПБРВ   Прізвище, ім'я, по батькові (27) у родовому відмінку
        szReplace = g_ChangePrImPbRV;
        bConvert = true;
        break;
      case IDKW_STPRIMPB  : // СТПРІМПБ   Старі прізвище, ім'я, по батькові (27)
        szReplace = g_OldPrImPb;
        bConvert = true;
        break;
      case IDKW_NPRIMPB   : // НПРІМПБ    Нові прізвище, ім'я, по батькові (27)
        szReplace = g_NewPrImPb;
        bConvert = true;
        break;
      case IDKW_DVYSN     : // ДВИСН      Дата висновку (29)
        szReplace = g_DVisn;
        return;
      case IDKW_DDOZV     : // ДДОЗВ      Дата дозволу (29)
        szReplace = g_DDozv;
        return;
      case IDKW_NVYSN     : // НВИСН      Номер висновку (29, 30)
        szReplace = g_NVisn;
        return;
      case IDKW_NDOZV     : // НДОЗВ      Номер дозволу (29, 30)
        szReplace = g_NDozv;
        return;
      default:
        IsCommonSect(pKeyword, pSet, sUpperKey, szReplace, bConvert, bFirst, &pData->fOwnerFound);
        break;
    }
  }
  else if ( sUpperKey.Left(9)==_T("ДДМММРРРР") ) {      // Дата реєстрації
    szReplace = sUpperKey.Left(9) + sTrimKey.Mid(9);
    szReplace = DDMMMRRRRR(pSet, _T("DATEREG"), szReplace);
  }
  else if ( sUpperKey.Left(8)==_T("ДДММРРРР") ) {      // Дата реєстрації: дд.мм.рррр
    szReplace = sUpperKey.Left(8) + sTrimKey.Mid(8);
    szReplace = DDMMRRRRR(pSet, _T("DATEREG"), szReplace);
  }
  else if ( sUpperKey.Left(11)==_T("ДНДДМММРРРР") ) {     // Дата народження: дд місяця рррр
    if ( pSet->IsNoticeBirthDate() )
      szReplace = pSet->GetNoticeBirthDateDDMMMYYYY();
    else {
      szReplace = sUpperKey.Mid(2, 9) + sTrimKey.Mid(11);
      szReplace = DDMMMRRRRR(pSet, _T("BIRTH_DATE"), szReplace);
    }
  }

  if ( false==szReplace.IsEmpty() ) {
    if ( bFirst ) {
      if ( IsCyrUpper(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt( 0, CyrUpper(szReplace.GetAt(0)) );
      }
      else if ( IsCyrLower(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt( 0, CyrLower(szReplace.GetAt(0)) );
      }
    }
    if ( bConvert ) {
      if ( sKey==sUpperKey )
        szReplace = UpperString(szReplace);
      else
        szReplace = MakeCanonicalName(szReplace);
    }
    if ( sTrimKey != sKey ) {
      sKey.Replace(sTrimKey, szReplace);
      szReplace = sKey;
    }
  }

}

void OnDeathKeyword(LPCTSTR szKeyword, CString& szReplace, DWORD dwData) {
  KWData* pData = (KWData*)dwData;

  CRSDeathes* pSet = (CRSDeathes*)pData->pSet;

  CString sKey(szKeyword);
  CString sTrimKey = Trim(sKey);
  CString sUpperKey = UpperString(sTrimKey);
  CString sLowerKey = LowerString(sTrimKey);
  BOOL bConvert = false;
  BOOL bFirst = false;

  const Keyword* pKeyword = theKeywords.Lookup(sUpperKey);

  if ( pKeyword ) {
    switch( pKeyword->id ) {
      case IDKW_NAZ       : // НАЗ        Номер актового запису
        szReplace = GetFieldString(pSet, _T("NUMBER"));
        break;
      case IDKW_DDMMMRRRR : // ДДМММРРРР  Дата реєстрації: ДД МММ РРРР
        szReplace = GetFieldDate(pSet, _T("DATEREG"), true);
        break;
      case IDKW_DDMMRRRR  : // ДДММРРРР   Дата реєстрації: ДД.ММ.РРРР
        szReplace = GetFieldDate(pSet, _T("DATEREG"), false);
        break;
      case IDKW_RRRR      : // РРРР     Дата реєстрації, рік: рррр
        szReplace = GetYear(pSet->m_DATEREG);
        break;
      case IDKW_RR        : // РР       Дата реєстрації, рік: рр
        szReplace = GetYear(pSet->m_DATEREG, false);
        break;
      case IDKW_MMM       : // МММ      Дата реєстрації, рік: місяця
        szReplace = GetByMonth(pSet->m_DATEREG);
        break;
      case IDKW_44        : // ЧЧ       Дата реєстрації: число ДД
        szReplace = GetDay(pSet->m_DATEREG);
        break;
      case IDKW_PRP       : // ПРП      Прізвище померлого
        szReplace = pSet->m_SURNAME;
        bConvert = true;
        break;
      case IDKW_IMP       : // ІМП      Ім'я померлого
        szReplace = pSet->m_NAME;
        bConvert = true;
        break;
      case IDKW_PBP       : // ПБП      По батькові померлого
        szReplace = pSet->m_PATRONYMIC;
        bConvert = true;
        break;
      case IDKW_STAT      : // СТАТЬ
        szReplace = ( pSet->m_SEX ) ?  _T("чоловіча") : _T("жіноча");
        break;
      case IDKW_POMERLA   : // Помер або Померла - залежить від статі
        szReplace = ( pSet->m_SEX ) ?  _T("Помер") : _T("Померла");
        bConvert = bFirst = true;
        break;
      case IDKW_DATAS     : // ДАТАС    Дата смерті: дд.мм.рррр
        szReplace = GetFieldDate(pSet, _T("DEATH_DATE"), false);
        break;
      case IDKW_DSDDMMRRRR: // ДСДДММРРРР Дата смерті: дд.мм.рррр
        if ( pSet->IsNoticeDeathDate() )
          szReplace = pSet->GetNoticeDeathDateDDMMMYYYY();
        else
          szReplace = GetFieldDate(pSet, _T("DEATH_DATE"), false);
        break;
      case IDKW_DSDDMMMRRRR:// ДСДДМММРРРР  Дата смерті: дд місяця рррр
        if ( pSet->IsNoticeDeathDate() )
          szReplace = pSet->GetNoticeDeathDateDDMMMYYYY();
        else {
          szReplace = sUpperKey.Mid(2, 9) + sTrimKey.Mid(11);
          szReplace = DDMMMRRRRR(pSet, _T("DEATH_DATE"), szReplace);
        }
        break;
      case IDKW_DSM       : // ДСМ    Дата смерті: дд - день
        if ( pSet->IsNoticeDeathDate() )
          szReplace = pSet->GetNoticeDeathDay();
        else
          szReplace = GetDay(pSet->m_DEATH_DATE);
        break;
      case IDKW_MSM       : // МСМ    Дата смерті: ммм - місяця
        if ( pSet->IsNoticeDeathDate() )
          szReplace = pSet->GetNoticeDeathMonth();
        else
          szReplace = GetByMonth(pSet->m_DEATH_DATE);
        break;
      case IDKW_RSM       : // РСМ    Дата смерті: рррр - рік
        if ( pSet->IsNoticeDeathDate() )
          szReplace = pSet->GetNoticeDeathYear();
        else
          szReplace = GetYear(pSet->m_DEATH_DATE);
        break;
      case IDKW_4MPROPYSOM: // ЧМПРОПИСОМ Дата смерті: число та місяць смерті прописом
        szReplace = strDayMonth(pSet->m_DEATH_DATE);
        break;
      case IDKW_RPROPYSOM : // РПРОПИСОМ  Дата смерті: рік смерті прописом
        szReplace = strYear(pSet->m_DEATH_DATE);
        break;
      case IDKW_GROMADYANSTVO:  // ГРОМАДЯНСТВО
        szReplace = GetCitizenship(pSet->m_SEX, pSet->m_CITIZENSHIP, bFirst);
        break;
      case IDKW_VIK       : // ВІК
        szReplace = GetAge(pSet->m_BIRTH_DATE, pSet->m_DEATH_DATE, false);
        break;
      case IDKW_ROKIV     : // РОКІВ
        szReplace = GetAge(pSet->m_BIRTH_DATE, pSet->m_DEATH_DATE, false, true, true);
        break;
      case IDKW_MISYACIV  : // МІСЯЦІВ
        szReplace = GetAge(pSet->m_BIRTH_DATE, pSet->m_DEATH_DATE, false, true);
        break;
      case IDKW_DNIV      : // ДНІВ
        szReplace = GetAge(pSet->m_BIRTH_DATE, pSet->m_DEATH_DATE, false, false, true);
        break;
      case IDKW_DS        : // ДС Місце смерті: Держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_DP_COUNTRY);
        break;
      case IDKW_OS        : // ОС     Місце смерті: Область
        szReplace = pSet->m_DP_REGION;
        break;
      case IDKW_OSOBL     : // ОСОБЛ      Місце смерті: Область + область
      case IDKW_OSOBLAST  : // ОСОБЛАСТЬ  Місце смерті: Область + область
        szReplace = GetRegion(pSet->m_DP_REGION, false);
        break;
      case IDKW_OSOBL_    : // ОСОБЛ. Місце смерті: Область + обл.
        szReplace = GetRegion(pSet->m_DP_REGION, true);
        break;
      case IDKW_RS        : // РС     Місце смерті: Район           (Старобешівський)
        szReplace = pSet->m_DP_DISTRICT;
        break;
      case IDKW_RSR_N     : // РСР-Н  Місце смерті: Район + р-н     (Старобешівський р-н)
        szReplace = GetDistrict(pSet->m_DP_DISTRICT, true);
        break;
      case IDKW_RSRAYON   : // РСРАЙОН  Місце смерті: Район + район (Старобешівський район)
        szReplace = GetDistrict(pSet->m_DP_DISTRICT, false);
        break;
      case IDKW_MS        : // МС   Місце смерті: Місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_DP_CITY);
        break;
      case IDKW_MSSS      : // МССС   Місце смерті: Місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_DP_CITY);
        break;
      case IDKW_PRY4YNAS  : // ПРИЧИНАС Причина смерті
        szReplace = pSet->m_CAUSE_OF_DEATH;
        break;
      case IDKW_DATAN     : // ДАТАН  Дата народження: дд.мм.рррр
        szReplace = GetFieldDate(pSet, _T("BIRTH_DATE"), false);
        break;
      case IDKW_DNDDMMMRRRR:  // ДНДДМММРРРР    Дата народження: дд місяця рррр
        if ( pSet->IsNoticeBirthDate() )
          szReplace = pSet->GetNoticeBirthDateDDMMMYYYY();
        else {
          szReplace = sUpperKey.Mid(2, 9) + sTrimKey.Mid(11);
          szReplace = DDMMMRRRRR(pSet, _T("BIRTH_DATE"), szReplace);
        }
        break;
      case IDKW_DNRR      : // ДНРР   Дата народження: рр
        szReplace = GetYear(pSet->m_BIRTH_DATE,  false);
        break;
      case IDKW_DNRRRR    : // ДНРРРР Дата народження: рррр
        szReplace = GetYear(pSet->m_BIRTH_DATE,  true);
        break;
      case IDKW_DN        : // ДН     Місце народження: Держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_BP_COUNTRY);
        break;
      case IDKW_ON        : // ОН     Місце народження: Область
        szReplace = pSet->m_BP_REGION;
        break;
      case IDKW_ONOBL     : // ОНОБЛ      Місце народження: Область + область
      case IDKW_ONOBLAST  : // ОНОБЛАСТЬ  Місце народження: Область + область
        szReplace = GetRegion(pSet->m_BP_REGION, false);
        break;
      case IDKW_ONOBL_    : // ОНОБЛ.     Місце народження: Область + обл.
        szReplace = GetRegion(pSet->m_BP_REGION, true);
        break;
      case IDKW_RN        : // РН         Місце народження: Район
        szReplace = pSet->m_BP_DISTRICT;
        break;
      case IDKW_RNRAYON   : // РНРАЙОН    Місце народження: Район + район
        szReplace = GetDistrict(pSet->m_BP_DISTRICT, false);
        break;
      case IDKW_RNR_N     : // РНР-Н      Місце народження: Район + р-н
        szReplace = GetDistrict(pSet->m_BP_DISTRICT, true);
        break;
      case IDKW_MSSN      : // МССН       Місце народження: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_BP_CITY);
        break;
      case IDKW_MN        : // МН         Місце народження: місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_BP_CITY);
        break;
      case IDKW_DP        : // ДП         Місце проживання: Держава
        szReplace = theGeoCache.FindFullCountry(pSet->m_RP_COUNTRY);
        break;
      case IDKW_OP        : // ОП         Місце проживання: Область
        szReplace = pSet->m_RP_REGION;
        break;
      case IDKW_OPOBL     : // ОПОБЛ      Місце проживання: Область + область
      case IDKW_OPOBLAST  : // ОПОБЛАСТЬ  Місце проживання: Область + область
        szReplace = GetRegion(pSet->m_RP_REGION, false);
        break;
      case IDKW_OPOBL_    : // ОПОБЛ.     Місце проживання: Область
        szReplace = GetRegion(pSet->m_RP_REGION, true);
        break;
      case IDKW_RP        : // РП         Місце проживання: Район
        szReplace = pSet->m_RP_DISTRICT;
        break;
      case IDKW_RPRAYON   : // РПРАЙОН    Місце проживання: Район + район
        szReplace = GetDistrict(pSet->m_RP_DISTRICT, false);
        break;
      case IDKW_RPR_N     : // РПР-Н      Місце проживання: Район + р-н
        szReplace = GetDistrict(pSet->m_RP_DISTRICT, true);
        break;
      case IDKW_MSSP      : // МССП       Місце проживання: місто (село, селище) - тип НП
        szReplace = TypeOfCity(pSet->m_RP_CITY);
        break;
      case IDKW_MP        : // МП         Місце проживання: місто (село, селище) - назва НП
        szReplace = GetCity(pSet->m_RP_CITY);
        break;
      case IDKW_VUL       : // ВУЛ        Місце проживання: вулиця
        szReplace = pSet->m_RP_STREET;
        break;
      case IDKW_BUD       : // БУД        Місце проживання: будинок
        szReplace = pSet->m_RP_HOUSE;
        break;
      case IDKW_KV        : // КВ         Місце проживання: квартира
        szReplace = pSet->m_RP_FLAT;
        break;
      case IDKW_ADRP      : // АДРП       Адреса померлого
        szReplace = GetAddress(pSet->m_RP_COUNTRY, pSet->m_RP_REGION, pSet->m_RP_CITY,  pSet->m_RP_DISTRICT,  pSet->m_RP_STREET,  pSet->m_RP_HOUSE, pSet->m_RP_FLAT);
        break;
      case IDKW_NDOC      : // НДОК       Назва документа
        if ( 0==pData->nScan && pSet->IsPassport() )
          szReplace = PassportName(pSet->m_PASSPORT_TYPE, true);
        else if( !pSet->GetMilitaryCardSeria().IsEmpty() )
          szReplace = _T("В-й кв-к");
        break;
      case IDKW_SP        : // СП         Серія паспорта (документа)
        if ( 0==pData->nScan && pSet->IsPassport() )
          szReplace = pSet->m_PASSPORT_SERIA;
        else
          szReplace = pSet->GetMilitaryCardSeria();
        break;
      case IDKW_NP        : // НП         Номер паспорта (документа)
        if ( 0==pData->nScan && pSet->IsPassport() )
          szReplace = pSet->m_PASSPORT_NUMBER;
        else
          szReplace = pSet->GetMilitaryCardNumber();
        break;
      case IDKW_DATAP     : // ДАТАП      Дата паспорта (документа)
        if ( 0==pData->nScan && pSet->IsPassport() )
          szReplace = GetFieldDate(pSet, _T("PASSPORT_DATE"), false );
        else
          szReplace = pSet->GetMilitaryCardDate();
        return;
      case IDKW_KVP       : // КВП        Ким видано паспорт (документ)
        if ( 0==pData->nScan && pSet->IsPassport() )
          szReplace = pSet->m_PASSPORT_BY;
        else
          szReplace = pSet->GetMilitaryCardBy();
        return;
      case IDKW_DOCUMENT  : // ДОКУМЕНТ   Документ, що підтверджує факт смерті
        szReplace = GetDeathDoc(pSet);
        return;
      case IDKW_PIBZ      : // ПІБЗ       Прізвище, ім'я, по батькові заявника
        szReplace = pSet->m_DECLARANT_NAME;
        return;
      case IDKW_ADRZ      : // АДРЗ       Адреса заявника
        szReplace = pSet->m_DECLARANT_ADDRESS;
        return;
      case IDKW_PASZ      : // ПАСЗ       Паспорт заявника
        szReplace = GetPassport(pSet->m_DECLARANT_PASSPORT_TYPE, pSet->m_DECLARANT_PASSPORT_SERIA, pSet->m_DECLARANT_PASSPORT_NUMBER, pSet->m_DECLARANT_PASSPORT_DATE, pSet->m_DECLARANT_PASSPORT_BY);
        return;
      case IDKW_SS        : // СС         Серія свідоцтва
        szReplace = pSet->m_CERTIFICATE_SERIA;
        return;
      case IDKW_NS        : // НС         Номер свідоцтва
        szReplace = pSet->m_CERTIFICATE_NUMBER;
        return;
      case IDKW_SSNS      : // ССНС     Серія свідоцтва + № + Номер свідоцтва
        if ( false==pSet->m_CERTIFICATE_SERIA.IsEmpty() && false==pSet->m_CERTIFICATE_NUMBER.IsEmpty() ) {
          szReplace.Format(_T("серія %s № %s"), pSet->m_CERTIFICATE_SERIA, pSet->m_CERTIFICATE_NUMBER);
        }
        return;
      case IDKW_SNV       : // СНВ        Свідоцтво не видано
        szReplace = pSet->GetSvNeVidano();
        return;
      case IDKW_POMITKY   : // ПОМІТКИ    
        szReplace = ReplaceEOL(pSet->GetNotices());
        return;
      case IDKW_NDS       : // НДС        Номер довідки про смерть
        szReplace = pSet->GetNDov();
        return;
      case IDKW_MISYAC    : // МІСЯЦЬ
        szReplace.LoadString(IDS_UM01+g_iMonth-1);
        bFirst = true;
        break;
      case IDKW_RIK       : // РІК
        szReplace.Format(_T("%04d"), g_RegDate.GetYear() );
        return;
      case IDKW_PIBP      : // ПІБП   Прізвище, ім'я, по батькові померлого
        szReplace = MakeFIO(pSet->m_SURNAME, pSet->m_NAME, pSet->m_PATRONYMIC);
        return;
      case IDKW_N         : // №
        szReplace.Format(_T("%d"), pData->Number);
        return;
      case IDKW_ARKUSH    :
        szReplace.Format(_T("АРКУШ %d"), pData->nPage);
        return;
      case IDKW_MW        : // ЧЖ     Стать: "Ч" або "Ж"
        szReplace = pSet->m_SEX ? _T("Ч") : _T("Ж");
        return;
      case IDKW_IN        : // ІН     Ідентефікаційний номер (код)
        szReplace = pSet->m_TAX_CODE;
        return;
      case IDKW_PIBZDV    : // ПІБЗДВ ПІБ заявника у давальному відмінку
        szReplace = CDlg43::m_sTo;
        bConvert = true;
        break;
      case IDKW_N43       : // №43
        szReplace = CDlg43::m_sNumber;
        return;
      default             :
        IsCommonSect(pKeyword, pSet, sUpperKey, szReplace, bConvert, bFirst, &pData->fOwnerFound);
        break;
    }
  }
  else if ( sUpperKey.Left(9)==_T("ДДМММРРРР") ) {      // Дата реєстрації
    szReplace = sUpperKey.Left(9) + sTrimKey.Mid(9);
    szReplace = DDMMMRRRRR(pSet, _T("DATEREG"), szReplace);
  }
  else if ( sUpperKey.Left(8)==_T("ДДММРРРР") ) {      // Дата реєстрації: дд.мм.рррр
    szReplace = sUpperKey.Left(8) + sTrimKey.Mid(8);
    szReplace = DDMMRRRRR(pSet, _T("DATEREG"), szReplace);
  }
  else if ( sUpperKey.Left(11)==_T("ДСДДМММРРРР") ) {   // Дата смерті: дд місяця рррр
    CString s = sTrimKey.Mid(11);
    if ( pSet->IsNoticeDeathDate() ) {
      szReplace = pSet->GetNoticeDeathDateDDMMMYYYY() + s;
    }
    else {
      szReplace = DDMMMRRRRR(pSet, _T("DEATH_DATE"), s);
    }
  }
  else if ( sUpperKey.Left(11)==_T("ДНДДМММРРРР") ) {  // ДНДДМММРРРР    Дата народження: дд місяця рррр
    if ( pSet->IsNoticeBirthDate() )
      szReplace = pSet->GetNoticeBirthDateDDMMMYYYY();
    else {
      szReplace = sUpperKey.Mid(2, 9) + sTrimKey.Mid(11);
      szReplace = DDMMMRRRRR(pSet, _T("BIRTH_DATE"), szReplace);
    }
  }


  if ( false==szReplace.IsEmpty() ) {
    if ( bFirst ) {
      if ( IsCyrUpper(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt( 0, CyrUpper(szReplace.GetAt(0)) );
      }
      else if ( IsCyrLower(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt( 0, CyrLower(szReplace.GetAt(0)) );
      }
    }
    if ( bConvert ) {
      if ( sKey==sUpperKey )
        szReplace = UpperString(szReplace);
      else
        szReplace = MakeCanonicalName(szReplace);
    }
    if ( sTrimKey != sKey ) {
      sKey.Replace(sTrimKey, szReplace);
      szReplace = sKey;
    }
  }
}

FILE* OpenAndCheckTemplate(const CString& sTemplate) {
  FILE* fIn = fopen(sTemplate, "r");
  if ( NULL==fIn ) {
    ErrorBox(_T("Файл шаблону \"%s\" відсутній.\nСпробуйте відновити файл шаблону або переустанивити ПК ЕРАГС."), sTemplate);
    return NULL;
  }
  char buf[16];
  size_t count = fread(buf, 1, 6, fIn);
  if ( count != 6 || memcmp(buf, "{\\rtf1", 6) != 0 ) {
    ErrorBox(_T("Файл шаблону \"%s\" зруйнований.\nРекомендується перевірити комп'ютер антивірусними засобами і переустановити ПК ЕРАГС."), sTemplate);
    return NULL;
  }
  fseek(fIn, 0, SEEK_SET);
  return fIn;
}

BOOL OpenAndCheckTemplate(CFile& file, const CString& sTemplate) {
  if( FALSE==file.Open(sTemplate, CFile::modeRead | CFile::shareDenyNone) ) {
    ErrorBox(_T("Файл шаблону \"%s\" відсутній.\nСпробуйте відновити файл шаблону або переустанивити ПК ЕРАГС."), sTemplate);
    return false;
  }
  char buf[16];
  UINT count = file.Read(buf, 6);
  if ( count != 6 || memcmp(buf, "{\\rtf1", 6) != 0 ) {
    ErrorBox(_T("Файл шаблону \"%s\" зруйнований.\nРекомендується перевірити комп'ютер антивірусними засобами і переустановити ПК ЕРАГС."), sTemplate);
    return false;
  }
  file.Seek(0, CFile::begin);
  return true;
}

FILE* CreateReportFile(const CString& sOutName) {
  FILE* fOut = fopen(sOutName, "w");
  if ( NULL==fOut ) {
    DWORD dwError = GetLastError();
    ErrorBox(_T("Помилка при спробі створити файл \"%s\".\n")
             _T("Можливо, цей файл вже відкритий іншою програмою.\n")
             _T("Системна помилка %d(0x%04X): %s."),
             sOutName, dwError, dwError, FormatError(dwError));
  }
  return fOut;
}

BOOL CreateReportFile(CFile& file, const CString& sOutName) {
  if ( FALSE==file.Open(sOutName, CFile::modeWrite | CFile::modeCreate) ) {
    DWORD dwError = GetLastError();
    ErrorBox(_T("Помилка при спробі створити файл \"%s\".\n")
             _T("Можливо, цей файл вже відкритий іншою програмою.\n")
             _T("Системна помилка %d(0x%04X): %s."),
             sOutName, dwError, dwError, FormatError(dwError));
    return false;
  }
  return true;
}

void MakeInOutExt(CString& sTemplate, CString& sOutName) {
  switch( theApp.GetOffice() ) {
    case MS_OFFICE  : sTemplate += _T("rtf"); sOutName += _T("rtf"); 
      break;
    case OPEN_OFFICE: sTemplate += _T("odt"); sOutName += _T("odt"); 
      if ( false==FileExists(sTemplate) ) {
        sTemplate = SetFileExt(sTemplate, _T("rtf"));
        sOutName  = SetFileExt(sOutName, _T("rtf"));
      }
      break;
  }
}
//
//
BOOL UConvert(const CString& sTemplate, const CString& sOutName, CRSBirthes* pSet) {
  CWaitCursor wc;
  CUCnv uCnv;
  if ( false==uCnv.Copy(sTemplate, sOutName) ) {
    return false;
  }
  if ( false==uCnv.Read(sOutName) ) {
    return false;
  }

  uCnv.InsertUnderlineStyle();

  g_nPrintCitizen = theIniCache.GetPrintCitizenBIRTH();

  KWData data;
  data.pSet         = pSet;
  data.Number       = 0;
  data.nPage        = 1;
  data.nScan        = 1;
  data.fOwnerFound  = false;

  uCnv.ReplaceContent(OnBirthKeyword, (DWORD)&data);

  uCnv.Write(sOutName);
  
  return true;
}


BOOL UConvert(const CString& sTemplate, const CString& sOutName, CRSMarriages* pSet) {
  CWaitCursor wc;
  CUCnv uCnv;

  if ( false==uCnv.Copy(sTemplate, sOutName) ) {
    return false;
  }
  if ( false==uCnv.Read(sOutName) ) {
    return false;
  }

  g_nPrintCitizen = theIniCache.GetPrintCitizenMARRIAGE();

  KWData data;
  data.pSet         = pSet;
  data.Number       = 0;
  data.nPage        = 1;
  data.nScan        = 1;
  data.fOwnerFound  = false;

  uCnv.InsertUnderlineStyle();
  
  uCnv.ReplaceContent(OnMarriageKeyword, (DWORD)&data);

  return uCnv.Write(sOutName);
}

BOOL UConvert(const CString& sTemplate, const CString& sOutName, CRSDivorces* pSet) {
  CWaitCursor wc;
  CUCnv uCnv;
  if ( false==uCnv.Copy(sTemplate, sOutName) ) {
    return false;
  }
  if ( false==uCnv.Read(sOutName) ) {
    return false;
  }

  uCnv.InsertUnderlineStyle();

  g_nPrintCitizen = theIniCache.GetPrintCitizenDIVORCE();

  KWData data;
  data.pSet         = pSet;
  data.Number       = 0;
  data.nPage        = 1;
  data.nScan        = 1;
  data.fOwnerFound  = false;

  uCnv.ReplaceContent(OnDivorceKeyword, (DWORD)&data);

  return uCnv.Write(sOutName);

}

BOOL UConvert(const CString& sTemplate, const CString& sOutName, CRSChanges* pSet) {

  CWaitCursor wc;
  CUCnv uCnv;
  if ( false==uCnv.Copy(sTemplate, sOutName) ) {
    return false;
  }
  if ( false==uCnv.Read(sOutName) ) {
    return false;
  }

  g_nPrintCitizen = theIniCache.GetPrintCitizenCHANGE();

  KWData data;
  data.pSet         = pSet;
  data.Number       = 0;
  data.nPage        = 1;
  data.nScan        = 1;
  data.fOwnerFound  = false;

  uCnv.ReplaceContent(OnChangeKeyword, (DWORD)&data);

  return uCnv.Write(sOutName);
}

BOOL UConvert(const CString& sTemplate, const CString& sOutName, CRSDeathes* pSet) {
  CWaitCursor wc;
  CUCnv uCnv;
  if ( false==uCnv.Copy(sTemplate, sOutName) ) {
    return false;
  }
  if ( false==uCnv.Read(sOutName) ) {
    return false;
  }
  uCnv.InsertUnderlineStyle();

  KWData data;
  data.pSet         = pSet;
  data.Number       = 0;
  data.nPage        = 1;
  data.nScan        = 1;
  data.fOwnerFound  = false;
  
  g_nPrintCitizen = theIniCache.GetPrintCitizenDEATH();
 
  data.pSet         = pSet;
  data.Number       = 0;
  data.nPage        = 1;
  data.nScan        = 1;
  data.fOwnerFound  = false;

  uCnv.ReplaceContent(OnDeathKeyword, (DWORD)&data);

  uCnv.Write(sOutName);

  return TRUE;
}

BOOL ConvertTable(LPCTSTR szReportName, const CString& sTemplate, const CString& sOutName, LPCTSTR szDBFScript, CRSDeathes* pSet, int nPage1, int nPage2, int (*pDeathFilterFunc)(CRSDeathes* pSet), int scanFrom/*=0*/) {
  CUCnv uCnv;
  CWaitCursor wc;
  if ( false==uCnv.Copy(sTemplate, sOutName) ) {
    return false;
  }
  if ( false==uCnv.Read(sOutName) ) {
    return false;
  }

  g_nTotalRecs  = g_nTotalPages = 0;

  CString sTitleRow, sTableRow, sRow;
  CString szTitle, szEndTitle, szTable, szEndTable;
  bool bTitleRow=false, bTableRow=false;

  sTitleRow = uCnv.GetRow(_T("ПЗ"), _T("КЗ"));
  if ( false==sTitleRow.IsEmpty() ) {
    bTitleRow = true;
  }
  sTableRow = uCnv.GetRow(_T("ПТ"), _T("КТ"));
  if ( false==sTableRow.IsEmpty() ) {
    bTableRow = true;
  }
  CString sBuffer = uCnv.GetData();


  int nPageRows = 0;
  BOOL bRet = false;
  BOOL fCallScript = false;
  char ErrBuf[1024];

  KWData kwData;

  g_szDBFile.Empty();
  
  CString sql, szVBScript;
  try {
    sql.Format(_T("SELECT * FROM %s ORDER BY SURNAME"), pSet->GetSQL() );
    CRSDeathes rs( &theDataManager.m_dbYear );
    rs.Open(dbOpenDynaset, sql, dbReadOnly);

    kwData.pSet        = &rs;
    kwData.Number      = 1;
    kwData.nPage       = 0;
    kwData.nScan       = 0;
    kwData.fOwnerFound = false;
    
    try {
      if ( g_fMakeDBF ) {
        g_szDBFile = SetFileExt(sOutName, _T("dbf"));
        szVBScript.Format(_T("%s\\%s"), GetModulePath(), g_szVBScript);
        fCallScript = CreateDBF(&rs, theIniCache.GetOKPO(), g_szDBFile, szVBScript, ErrBuf);
        if ( false==fCallScript ) {
          g_fMakeDBF = false;
          ErrorBox(_T("%s"), ErrBuf);
        }
      }
    }
    catch (...) {
      g_fMakeDBF = false;
    }
    sRow = sTableRow;
    CString sRows, szBarTitle;
    szBarTitle.Format(_T("Будується %s..."), szReportName);
    CProgressBar bar(szBarTitle, 80, 100, true, 2);
    while ( !rs.IsEOF() ) {
      bar.SetPos( (int)rs.GetPercentPosition() );
      PeekAndPump();
      int nMaxScan;
      if ( pDeathFilterFunc && (nMaxScan=pDeathFilterFunc(&rs))==0 ) {
        rs.MoveNext();
        continue;
      }

      if ( g_fMakeDBF ) {
        OnDBFRecord(&rs);
      }

      for( int i=scanFrom; i < nMaxScan; i++ ) {
        g_nTotalRecs++;
        kwData.nScan = i;
        CString sEncodedRow;
        if ( (kwData.nPage==0 && nPageRows==0) || (kwData.nPage==1 && nPageRows==nPage1) || (kwData.nPage>1 && nPageRows==nPage2)) {
          kwData.nPage++;
          g_nTotalPages++;
          nPageRows = 0;
          if ( false==sTitleRow.IsEmpty() ) {
            sEncodedRow = uCnv.EncodeRow(sTitleRow, OnDeathKeyword, (DWORD)&kwData);
            if ( kwData.nPage==1 )
              sBuffer.Replace(sTitleRow, sEncodedRow);
            else {
              sRows += sEncodedRow;
            }
          }
        }
        sEncodedRow = uCnv.EncodeRow(sTableRow, OnDeathKeyword, (DWORD)&kwData);
        sRows += sEncodedRow;
        nPageRows++;
        kwData.Number++;
      }
      rs.MoveNext();
    }
    
    sBuffer.Replace(sTableRow,  sRows);
    if ( false==szTitle.IsEmpty()    ) sBuffer.Replace(szTitle,     g_szEmpty );
    if ( false==szEndTitle.IsEmpty() ) sBuffer.Replace(szEndTitle,  g_szEmpty );
    if ( false==szTable.IsEmpty()    ) sBuffer.Replace(szTable,     g_szEmpty );
    if ( false==szEndTable.IsEmpty() ) sBuffer.Replace(szEndTable,  g_szEmpty );

    uCnv.SetData(sBuffer);
    uCnv.ReplaceContent(OnDeathKeyword, (DWORD)&kwData);

    rs.Close();
    bRet = uCnv.Write(sOutName);

    if ( g_fMakeDBF ) {
      CloseDBF();
    }

  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return FALSE;
  }
  catch (CException* e) {
    e->Delete();
  }

  return bRet;
}


BOOL ConvertTable(LPCTSTR szReportName, const CString& sTemplate, const CString& sOutName, CRSBirthes* pSet, int nPage1, int nPage2, int (*pBirthFilterFunc)(CRSBirthes* pSet)) {
  CWaitCursor wc;
  CUCnv uCnv;
  if ( false==uCnv.Copy(sTemplate, sOutName) ) {
    return false;
  }
  if ( false==uCnv.Read(sOutName) ) {
    return false;
  }

  g_nTotalRecs  = g_nTotalPages = 0;

  CString sTitleRow, sTableRow, sRow;
  CString szTitle, szEndTitle, szTable, szEndTable;
  bool bTitleRow=false, bTableRow=false;

  sTitleRow = uCnv.GetRow(_T("ПЗ"), _T("КЗ"));
  if ( false==sTitleRow.IsEmpty() ) {
    bTitleRow = true;
  }
  sTableRow = uCnv.GetRow(_T("ПТ"), _T("КТ"));
  if ( false==sTableRow.IsEmpty() ) {
    bTableRow = true;
  }
  CString sBuffer = uCnv.GetData();

  int nPageRows = 0;
  BOOL bRet = false;
  CString sql;

  KWData kwData;

  try {
    sql.Format(_T("SELECT * FROM %s ORDER BY SURNAME"), pSet->GetSQL() );
    CRSBirthes rs( &theDataManager.m_dbYear );
    rs.Open(dbOpenDynaset, sql, dbReadOnly);
    sRow = sTableRow;
    CString sRows, szBarTitle;
    szBarTitle.Format(_T("Будується %s..."), szReportName);
    CProgressBar bar(szBarTitle, 80, 100, true, 2);

    kwData.pSet        = &rs;
    kwData.Number      = 1;
    kwData.nPage       = 0;
    kwData.nScan       = 0;
    kwData.fOwnerFound = false;

    while ( !rs.IsEOF() ) {
      bar.SetPos( (int)rs.GetPercentPosition() );
      PeekAndPump();
      int nMaxScan;
      if ( pBirthFilterFunc && (nMaxScan=pBirthFilterFunc(&rs))==0 ) {
        rs.MoveNext();
        continue;
      }

      for( int i(0); i < nMaxScan; i++ ) {
        g_nTotalRecs++;
        kwData.nScan = i;
        CString sEncodedRow;
        if ( (kwData.nPage==0 && nPageRows==0) || (kwData.nPage==1 && nPageRows==nPage1) || (kwData.nPage>1 && nPageRows==nPage2)) {
          kwData.nPage++;
          g_nTotalPages++;
          nPageRows = 0;
          if ( false==sTitleRow.IsEmpty() ) {
            sEncodedRow = uCnv.EncodeRow(sTitleRow, OnBirthKeyword, (DWORD)&kwData);
            if ( kwData.nPage==1 )
              sBuffer.Replace(sTitleRow, sEncodedRow);
            else {
              sRows += sEncodedRow;
            }
          }
        }
        sEncodedRow = uCnv.EncodeRow(sTableRow, OnBirthKeyword, (DWORD)&kwData);
        sRows += sEncodedRow;
        nPageRows++;
        kwData.Number++;
      }

      rs.MoveNext();
    }
    
    // pSet->SetBookmark(bookmark);

    sBuffer.Replace(sTableRow, sRows);
    if ( false==szTitle.IsEmpty()    ) sBuffer.Replace(szTitle,     g_szEmpty );
    if ( false==szEndTitle.IsEmpty() ) sBuffer.Replace(szEndTitle,  g_szEmpty );
    if ( false==szTable.IsEmpty()    ) sBuffer.Replace(szTable,     g_szEmpty );
    if ( false==szEndTable.IsEmpty() ) sBuffer.Replace(szEndTable,  g_szEmpty );

    uCnv.SetData(sBuffer);
    uCnv.ReplaceContent(OnBirthKeyword, (DWORD)&kwData);

    rs.Close();
    bRet = uCnv.Write(sOutName);

  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return FALSE;
  }
  catch (CException* e) {
    e->Delete();
  }

  return bRet;
}

//
// ABC
//
BOOL CreateABCMDB(CString& sDBName) {
  sDBName.Format(_T("%s\\abc.mdb"), theApp.m_sOutPath);
  DeleteFile(sDBName);
  CDaoDatabase db;
  try {
    db.Create(sDBName, dbLangCyrillic);
    CDaoTableDef td(&db);
    td.Create("ABC");

    td.CreateField(_T("FULLNAME"), dbText,    100);
    td.CreateField(_T("NUMBER"),   dbInteger,   2);
    td.CreateField(_T("DATEREG"),  dbDate,      8);
    td.CreateField(_T("SEX"),      dbBoolean,   1);
    td.CreateField(_T("DATEBIRTH"),dbDate,      8);
    td.CreateField(_T("DATEDEATH"),dbDate,      8);

    td.Append();
    td.Close();
    db.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return FALSE;
  }
  return TRUE;
}


void OnABCKeyword(LPCTSTR szKeyword, CString& szReplace, DWORD dwData) {
  KWData* pData = (KWData*)dwData;
  CString sKey(szKeyword);
  CString sTrimKey = Trim(sKey);
  CString sUpperKey = UpperString(sTrimKey);
  CString sLowerKey = LowerString(sTrimKey);
  BOOL bConvert = false;
  BOOL bFirst = false;

  const Keyword* pKeyword = theKeywords.Lookup(sUpperKey);
  if ( pKeyword ) {
    switch(pKeyword->id) {
      case IDKW_NAZ      :
        szReplace = GetFieldString(pData->pSet, _T("NUMBER"));
        break;
      case IDKW_MW       :
        szReplace = GetFieldBool(pData->pSet, _T("SEX")) ? _T("Ч") : _T("Ж");
        break;
      case IDKW_PIB      :
        szReplace = GetFieldString(pData->pSet, _T("FULLNAME"));
        bConvert = true;
        break;
      case IDKW_DATAN    :
        szReplace = GetFieldDate(pData->pSet, _T("DATEBIRTH"), false);
        break;
      case IDKW_DATAS    :
        szReplace = GetFieldDate(pData->pSet, _T("DATEDEATH"), false);
        break;
      case IDKW_DDMMRRRR :
        szReplace = GetFieldDate(pData->pSet, _T("DATEREG"), false);
        break;
      default            :
        IsCommonSect(pKeyword, pData->pSet, sUpperKey, szReplace, bConvert, bFirst, &pData->fOwnerFound);
        break;
    }
  }
  else if ( sUpperKey.Left(8)==_T("ДДММРРРР") ) {      // Дата реєстрації: дд.мм.рррр
    szReplace = sUpperKey.Left(8) + sTrimKey.Mid(8);
    szReplace = DDMMRRRRR(pData->pSet, _T("DATEREG"), szReplace);
  }

  if ( false==szReplace.IsEmpty() ) {
    if ( bFirst ) {
      if ( IsCyrUpper(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt( 0, CyrUpper(szReplace.GetAt(0)) );
      }
      else if ( IsCyrLower(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt( 0, CyrLower(szReplace.GetAt(0)) );
      }
    }
    if ( bConvert ) {
      if ( sKey==sUpperKey )
        szReplace = UpperString(szReplace);
      else
        szReplace = MakeCanonicalName(szReplace);
    }
    if ( sTrimKey != sKey ) {
      sKey.Replace(sTrimKey, szReplace);
      szReplace = sKey;
    }
  }
}

BOOL RTF_ABC(const CString& sDBName, const CString& sTemplate, const CString& sOutName) {
  CUCnv uCnv;
  CWaitCursor wc;

  if ( false==uCnv.Copy(sTemplate, sOutName) ) {
    return false;
  }
  if ( false==uCnv.Read(sOutName) ) {
    return false;
  }

  g_nTotalRecs  = g_nTotalPages = 0;

  CString sTitleRow, sTableRow, sRows;
  bool bTitleRow=false, bTableRow=false;
  sTitleRow = uCnv.GetRow(_T("ПЗ"), _T("КЗ"));
  if ( false==sTitleRow.IsEmpty() ) {
    bTitleRow = true;
  }
  sTableRow = uCnv.GetRow(_T("ПТ"), _T("КТ"));
  if ( false==sTableRow.IsEmpty() ) {
    bTableRow = true;
  }
  CString sBuffer = uCnv.GetData();

  int nPageRows = 0;
  KWData kwData;

  CProgressBar bar(_T("Будується алфавітний список..."), 80, 100, true, 2);

  CDaoDatabase db;
  try {
    db.Open(sDBName);
    CDaoRecordset rs(&db);
    rs.Open(dbOpenDynaset, _T("SELECT * FROM ABC ORDER BY FULLNAME"), dbReadOnly);
    TCHAR cOldLetter = 0;

    kwData.pSet        = &rs;
    kwData.Number      = 1;
    kwData.nPage       = 0;
    kwData.nScan       = 0;
    kwData.fOwnerFound = false;

    while( !rs.IsEOF() ) {
      bar.SetPos( (int)rs.GetPercentPosition() );
      PeekAndPump();
      TCHAR cNewLetter = 0;
      CString sFullName = GetFieldString(&rs, _T("FULLNAME"));
      if ( sFullName.GetLength() )
        cNewLetter = sFullName.GetAt(0);
      if ( 0==cOldLetter )
        cOldLetter = cNewLetter;
      if ( cNewLetter != cOldLetter ) {
        if ( g_fNewPageForLetter )
          sRows += g_szNewPage;
        cOldLetter = cNewLetter;
      }

      CString sEncodedRow = uCnv.EncodeRow(sTableRow, OnABCKeyword, (DWORD)&kwData);
      sRows += sEncodedRow;
      rs.MoveNext();
      kwData.Number++;
    }
    rs.Close();
    db.Close();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    LogDBError(e, _T("RTF_ABC"));
    e->Delete();
  }

  sBuffer.Replace(sTableRow, sRows);
  /*
  if ( false==szTitle.IsEmpty()    ) sBuffer.Replace(szTitle,     g_szEmpty );
  if ( false==szEndTitle.IsEmpty() ) sBuffer.Replace(szEndTitle,  g_szEmpty );
  if ( false==szTable.IsEmpty()    ) sBuffer.Replace(szTable,     g_szEmpty );
  if ( false==szEndTable.IsEmpty() ) sBuffer.Replace(szEndTable,  g_szEmpty );

  file.WriteHuge(sBuffer, sBuffer.GetLength() );
  file.Close();
  */
  uCnv.SetData(sBuffer);
  uCnv.ReplaceContent(OnABCKeyword, (DWORD)&kwData);
  return uCnv.Write(sOutName);
}

BOOL RTF_ABCBirth(const CString& sTemplate, const CString& sOutName, CRSBirthes* pSet) {
  CWaitCursor wc;
  CString sDBName;
  if ( FALSE==CreateABCMDB(sDBName) )
    return FALSE;


  CProgressBar bar(_T("Будується алфавітний список..."), 80, 100, true, 2);

  try {
    CDaoDatabase db;
    db.Open(sDBName);
    CDaoRecordset rsABC(&db);
    rsABC.Open( dbOpenDynaset, _T("SELECT * FROM ABC"), dbAppendOnly);

    CRSBirthes rs(&theDataManager.m_dbYear);
    rs.Open( dbOpenDynaset, _T("SELECT * FROM BIRTHES"), dbReadOnly);
    while ( !rs.IsEOF() ) {
      bar.SetPos( (int)rs.GetPercentPosition() );
      PeekAndPump();
      if ( IsValidDateReg(rs.m_DATEREG) && false==IsEmptyText(rs.m_SURNAME) ) {
        CString sOldFullName = MakeFIO(rs.m_SURNAME, rs.m_NAME, rs.m_PATRONYMIC);
        CString sNewFullName = MakeFIO(rs.GetNewOrOldSurname(), rs.GetNewOrOldName(), rs.GetNewOrOldPatronymic());
        COleVariant fSex;
        rs.GetFieldValue(_T("SEX"), fSex);

        // For old Surname, Name, Patronymic
        rsABC.AddNew();
        rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sOldFullName);
        rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
        rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
        rsABC.SetFieldValue(_T("SEX"), fSex);
        rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_BIRTH_DATE);
        rsABC.Update();
        // For new Surname, Name, Patronymic
        if ( g_fNewSurnamesABC && sOldFullName != sNewFullName ) {
          rsABC.AddNew();
          rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sNewFullName);
          rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
          rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
          rsABC.SetFieldValue(_T("SEX"), fSex);
          rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_BIRTH_DATE);
          rsABC.Update();
        }
      }
      rs.MoveNext();
    }
    rs.Close();
    rsABC.Close();
    db.Close();
  }

  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    LogDBError(e, _T("RTF_ABCBirth"));
    e->Delete();
    return FALSE;
  }

  return RTF_ABC(sDBName, sTemplate, sOutName);
}

BOOL RTF_BirthBlank(const CString& sTemplate, const CString& sOutName, CRSBirthes* pSet) {
  return UConvert(sTemplate, sOutName, pSet);
}

BOOL RTF_ABCMarriage(const CString& sTemplate, const CString& sOutName, CRSMarriages* pSet) {
  CWaitCursor wc;
  CString sDBName;
  if ( FALSE==CreateABCMDB(sDBName) )
    return FALSE;

  CProgressBar bar(_T("Будується алфавітний список..."), 80, 100, true, 2);

  try {
    CDaoDatabase db;
    db.Open(sDBName);
    CDaoRecordset rsABC(&db);
    rsABC.Open( dbOpenDynaset, _T("SELECT * FROM ABC"), dbAppendOnly);

    CRSMarriages rs(&theDataManager.m_dbYear );
    rs.Open( dbOpenDynaset, _T("SELECT * FROM MARRIAGES"), dbReadOnly);
    while ( !rs.IsEOF() ) {
      bar.SetPos( (int)rs.GetPercentPosition() );
      PeekAndPump();
      if ( IsValidDateReg(rs.m_DATEREG) && false==IsEmptyText(rs.m_MOLD_SURNAME) && false==IsEmptyText(rs.m_WOLD_SURNAME)) {
        CString sMFullName = MakeFIO(rs.m_MOLD_SURNAME, rs.m_MNAME, rs.m_MPATRONYMIC);
        CString sWFullName = MakeFIO(rs.m_WOLD_SURNAME, rs.m_WNAME, rs.m_WPATRONYMIC);

        // For man
        rsABC.AddNew();
        rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sMFullName);
        rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
        rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
        rsABC.SetFieldValue(_T("SEX"), VARIANT_TRUE);
        rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_MBIRTH_DATE);
        rsABC.Update();
        // For woman
        rsABC.AddNew();
        rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sWFullName);
        rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
        rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
        rsABC.SetFieldValue(_T("SEX"), VARIANT_FALSE);
        rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_WBIRTH_DATE);
        rsABC.Update();
        // For man
        if ( g_fNewSurnamesABC && rs.m_MNEW_SURNAME !=rs.m_MOLD_SURNAME && false==IsEmptyText(rs.m_MNEW_SURNAME) ) {
          sMFullName = MakeFIO(rs.m_MNEW_SURNAME, rs.m_MNAME, rs.m_MPATRONYMIC);
          rsABC.AddNew();
          rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sMFullName);
          rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
          rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
          rsABC.SetFieldValue(_T("SEX"), VARIANT_TRUE);
          rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_MBIRTH_DATE);
          rsABC.Update();
        }
        // For woman
        if ( g_fNewSurnamesABC && rs.m_WNEW_SURNAME !=rs.m_WOLD_SURNAME && false==IsEmptyText(rs.m_WNEW_SURNAME) ) {
          sWFullName = MakeFIO(rs.m_WNEW_SURNAME, rs.m_WNAME, rs.m_WPATRONYMIC);
          rsABC.AddNew();
          rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sWFullName);
          rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
          rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
          rsABC.SetFieldValue(_T("SEX"), VARIANT_FALSE);
          rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_WBIRTH_DATE);
          rsABC.Update();
        }
      }
      rs.MoveNext();
    }
    rs.Close();
    rsABC.Close();
    db.Close();
  }

  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    LogDBError(e, _T("RTF_ABCMarriage"));
    e->Delete();
    return FALSE;
  }

  return RTF_ABC(sDBName, sTemplate, sOutName);
}

BOOL RTF_MarriageBlank(const CString& sTemplate, const CString& sOutName, CRSMarriages* pSet) {
  return UConvert(sTemplate, sOutName, pSet);
}
BOOL RTF_ABCDivorce(const CString& sTemplate, const CString& sOutName, CRSDivorces* pSet) {
  CWaitCursor wc;
  CString sDBName;
  if ( FALSE==CreateABCMDB(sDBName) )
    return FALSE;

  CProgressBar bar(_T("Будується алфавітний список..."), 80, 100, true, 2);

  try {
    CDaoDatabase db;
    db.Open(sDBName);
    CDaoRecordset rsABC(&db);
    rsABC.Open( dbOpenDynaset, _T("SELECT * FROM ABC"), dbAppendOnly);

    CRSDivorces rs(&theDataManager.m_dbYear );
    rs.Open( dbOpenDynaset, _T("SELECT * FROM DIVORCES"), dbReadOnly);
    while ( !rs.IsEOF() ) {
      bar.SetPos( (int)rs.GetPercentPosition() );
      PeekAndPump();
      if ( IsValidDateReg(rs.m_DATEREG) && false==IsEmptyText(rs.m_MOLD_SURNAME) && false==IsEmptyText(rs.m_WOLD_SURNAME)) {
        CString sMFullName = MakeFIO(rs.m_MOLD_SURNAME, rs.m_MNAME, rs.m_MPATRONYMIC);
        CString sWFullName = MakeFIO(rs.m_WOLD_SURNAME, rs.m_WNAME, rs.m_WPATRONYMIC);

        // For man
        rsABC.AddNew();
        rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sMFullName);
        rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
        rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
        rsABC.SetFieldValue(_T("SEX"), VARIANT_TRUE);
        rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_MBIRTH_DATE);
        rsABC.Update();
        // For woman
        rsABC.AddNew();
        rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sWFullName);
        rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
        rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
        rsABC.SetFieldValue(_T("SEX"), VARIANT_FALSE);
        rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_WBIRTH_DATE);
        rsABC.Update();
        // For man
        if ( g_fNewSurnamesABC && rs.m_MNEW_SURNAME !=rs.m_MOLD_SURNAME && false==IsEmptyText(rs.m_MNEW_SURNAME) ) {
          sMFullName = MakeFIO(rs.m_MNEW_SURNAME, rs.m_MNAME, rs.m_MPATRONYMIC);
          rsABC.AddNew();
          rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sMFullName);
          rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
          rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
          rsABC.SetFieldValue(_T("SEX"), VARIANT_TRUE);
          rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_MBIRTH_DATE);
          rsABC.Update();
        }
        // For woman
        if ( g_fNewSurnamesABC && rs.m_WNEW_SURNAME !=rs.m_WOLD_SURNAME && false==IsEmptyText(rs.m_WNEW_SURNAME) ) {
          sWFullName = MakeFIO(rs.m_WNEW_SURNAME, rs.m_WNAME, rs.m_WPATRONYMIC);
          rsABC.AddNew();
          rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sWFullName);
          rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
          rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
          rsABC.SetFieldValue(_T("SEX"), VARIANT_FALSE);
          rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_WBIRTH_DATE);
          rsABC.Update();
        }
      }
      rs.MoveNext();
    }
    rs.Close();
    rsABC.Close();
    db.Close();
  }

  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    LogDBError(e, _T("RTF_ABCDivorce"));
    e->Delete();
    return FALSE;
  }

  return RTF_ABC(sDBName, sTemplate, sOutName);
}
BOOL RTF_DivorceBlank(const CString& sTemplate, const CString& sOutName, CRSDivorces* pSet) {
  return UConvert(sTemplate, sOutName, pSet);
}

BOOL RTF_ABCChange(const CString& sTemplate, const CString& sOutName, CRSChanges* pSet) {
  CWaitCursor wc;
  CString sDBName;
  if ( FALSE==CreateABCMDB(sDBName) )
    return FALSE;

  CProgressBar bar(_T("Будується алфавітний список..."), 80, 100, true, 2);

  try {
    CDaoDatabase db;
    db.Open(sDBName);
    CDaoRecordset rsABC(&db);
    rsABC.Open( dbOpenDynaset, _T("SELECT * FROM ABC"), dbAppendOnly);

    CRSChanges rs(&theDataManager.m_dbYear );
    rs.Open( dbOpenDynaset, _T("SELECT * FROM CHANGES"), dbReadOnly);
    while ( !rs.IsEOF() ) {
      bar.SetPos( (int)rs.GetPercentPosition() );
      PeekAndPump();
      if ( IsValidDateReg(rs.m_DATEREG) && false==IsEmptyText(rs.m_OLDSURNAME) ) {
        CString sOldFullName = MakeFIO(rs.m_OLDSURNAME, rs.m_OLDNAME, rs.m_OLDPATRONYMIC);
        CString sNewFullName = MakeFIO(rs.m_NEWSURNAME, rs.m_NEWNAME, rs.m_NEWPATRONYMIC);
        COleVariant fSex;
        rs.GetFieldValue(_T("SEX"), fSex);

        // For old Surname, Name, Patronymic
        rsABC.AddNew();
        rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sOldFullName);
        rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
        rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
        rsABC.SetFieldValue(_T("SEX"), fSex);
        rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_BIRTH_DATE);
        rsABC.Update();
        if ( g_fNewSurnamesABC && sOldFullName !=sNewFullName && false==IsEmptyText(sNewFullName) ) {
          // For new Surname, Name, Patronymic
          rsABC.AddNew();
          rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sNewFullName);
          rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
          rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
          rsABC.SetFieldValue(_T("SEX"), fSex);
          rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_BIRTH_DATE);
          rsABC.Update();
        }
      }
      rs.MoveNext();
    }
    rs.Close();
    rsABC.Close();
    db.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    LogDBError(e, _T("RTF_ABCChange"));
    e->Delete();
    return FALSE;
  }
  return RTF_ABC(sDBName, sTemplate, sOutName);
}
BOOL RTF_ChangeBlank(const CString& sTemplate, const CString& sOutName, CRSChanges* pSet) {
  return UConvert(sTemplate, sOutName, pSet);
}

BOOL RTF_ABCDeath(const CString& sTemplate, const CString& sOutName, CRSDeathes* pSet) {
  CString sDBName;
  if ( FALSE==CreateABCMDB(sDBName) )
    return FALSE;

  CProgressBar bar(_T("Будується алфавітний список..."), 80, 100, true, 2);

  try {
    CDaoDatabase db;
    db.Open(sDBName);
    CDaoRecordset rsABC(&db);
    rsABC.Open( dbOpenDynaset, _T("SELECT * FROM ABC"), dbAppendOnly);

    CRSDeathes rs(&theDataManager.m_dbYear );
    rs.Open( dbOpenDynaset, _T("SELECT * FROM DEATHES"), dbReadOnly);
    while ( !rs.IsEOF() ) {
      bar.SetPos( (int)rs.GetPercentPosition() );
      PeekAndPump();
      if ( IsValidDateReg(rs.m_DATEREG) && false==IsEmptyText(rs.m_SURNAME) ) {
        CString sFullName = MakeFIO(rs.m_SURNAME, rs.m_NAME, rs.m_PATRONYMIC);
        COleVariant fSex;
        rs.GetFieldValue(_T("SEX"), fSex);

        rsABC.AddNew();
        rsABC.SetFieldValue(_T("FULLNAME"), (LPCTSTR)sFullName);
        rsABC.SetFieldValue(_T("DATEREG"), rs.m_DATEREG);
        rsABC.SetFieldValue(_T("NUMBER"), rs.m_NUMBER);
        rsABC.SetFieldValue(_T("SEX"), fSex);
        rsABC.SetFieldValue(_T("DATEBIRTH"), rs.m_BIRTH_DATE);
        rsABC.SetFieldValue(_T("DATEDEATH"), rs.m_DEATH_DATE);
        rsABC.Update();
      }
      rs.MoveNext();
    }
    rs.Close();
    rsABC.Close();
    db.Close();
  }

  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    LogDBError(e, _T("RTF_ABCDeath"));
    e->Delete();
    return FALSE;
  }

  return RTF_ABC(sDBName, sTemplate, sOutName);
}

BOOL RTF_DeathBlank(const CString& sTemplate, const CString& sOutName, CRSDeathes* pSet) {
  return UConvert(sTemplate, sOutName, pSet);
}

void OnEnvelopeKeyword(LPCTSTR szKeyword, CString& szReplace, DWORD dwData) {
  extern CString g_szSender,    g_szSender_Address,     g_szSender_Index;
  extern CString g_szAddressee, g_szAddressee_Address,  g_szAddressee_Index;
  CString MakeCRC(const CString& sKey, BOOL fSender);

  CString sKey(szKeyword);
  CString sTrimKey = Trim(sKey);
  CString sUpperKey = UpperString(sTrimKey);

  if ( sUpperKey==_T("ВІДПРАВНИК") ) {
    szReplace = g_szSender;
  }
  else if ( sUpperKey==_T("ВІДАДРЕСА")) {
    szReplace = g_szSender_Address;
  }
  else if ( sUpperKey==_T("ВІДІНДЕКС")) {
    szReplace = g_szSender_Index;
  }
  else if ( sUpperKey.Find(_T("ВІД "))==0 ) {
    szReplace = MakeCRC(sUpperKey, TRUE);
  }
  else if ( sUpperKey==_T("ОДЕРЖУВАЧ") ) {
    szReplace = g_szAddressee;
  }
  else if ( sUpperKey==_T("ОДАДРЕСА")) {
    szReplace = g_szAddressee_Address;
  }
  else if ( sUpperKey==_T("ОДІНДЕКС")) {
    szReplace = g_szAddressee_Index;
  }
  else if ( sUpperKey.Find(_T("ОД "))==0 ) {
    szReplace = MakeCRC(sUpperKey, FALSE);
  }

}

BOOL ConvertEnvelope(const CString& sTemplate, const CString& sOutName) {
  CUCnv uCnv;
  CWaitCursor wc;

  if ( false==uCnv.Copy(sTemplate, sOutName) ) {
    return false;
  }

  if ( false==uCnv.Read(sOutName) ) {
    return false;
  }

  uCnv.ReplaceContent(OnEnvelopeKeyword, (DWORD)NULL, true);
  return uCnv.Write(sOutName);
}
BOOL ElectEncoder(TCHAR* pDestBuf, int BufSize, LPCTSTR szKey, CElectItem* pItem, int Number) {
  CString sValue;
  CString sKey     = szKey;
  CString sTrimKey = Trim(szKey);
  CString sUpperKey = UpperString(sTrimKey);

  BOOL bOk = true, bConvert = false, bFirst = false;

  if ( pItem ) {
    if ( sUpperKey==_T("ТЕРИТОРІЯ") ) {
      sValue = GetPlace(pItem->m_szRPCountry, pItem->m_szRPRegion, pItem->m_szRPDistrict, pItem->m_szRPCity, false);
      if ( sValue.IsEmpty() ) {
        sValue = _T("Місце проживання не визначене");
      }
    }
    else if ( sUpperKey==_T("№") ) {
      sValue.Format(_T("%d"), Number);
    }
    else if ( sUpperKey==_T("НАЗ") ) {
      sValue.Format(_T("%d"), pItem->m_Number);
    }
    else if ( sUpperKey==_T("ТНАЗ") ) {
      sValue.Format(_T("%s %d"), pItem->m_szType, pItem->m_Number);
    }
    else if ( sUpperKey.Left(9)==_T("ДДМММРРРР") ) {      // Дата реєстрації
      sValue = GetDateDDMMMYYYYr(pItem->m_DateReg);
    }
    else if ( sUpperKey.Left(8)==_T("ДДММРРРР") ) {      // Дата реєстрації: дд.мм.рррр
      sValue = GetDateDDMMYYYY(pItem->m_DateReg);
    }
    else if ( sUpperKey==_T("ПРП") || sUpperKey==_T("СТПР") ) {
      sValue = pItem->m_szOldSurname;
      bConvert = true;
    }
    else if ( sUpperKey==_T("ІМП") || sUpperKey==_T("СТІМ") ) {
      sValue = pItem->m_szOldName;
      bConvert = true;
    }
    else if ( sUpperKey==_T("ПБП") || sUpperKey==_T("СТПБ") ) {
      sValue = pItem->m_szOldPatronymic;
      bConvert = true;
    }
    else if ( sUpperKey==_T("СТПІБ") || sUpperKey==_T("ПІБ")) {
      sValue = pItem->m_szOldSNP;
      bConvert = true;
    }
    else if ( sUpperKey==_T("НПР") ) {
      sValue = pItem->m_szNewSurname;
      bConvert = true;
    }
    else if ( sUpperKey==_T("НІМ") ) {
      sValue = pItem->m_szNewName;
      bConvert = true;
    }
    else if ( sUpperKey==_T("НПБ") ) {
      sValue = pItem->m_szNewPatronymic;
      bConvert = true;
    }
    else if ( sUpperKey==_T("НПІБ") ) {
      sValue = pItem->m_szNewSNP;
      bConvert = true;
    }
    else if ( sUpperKey==_T("ДАТАН") ) {
      sValue = GetDateDDMMYYYY(pItem->m_BirtDate);
    }
    else if ( sUpperKey==_T("МІСЦЕН") ) {
      sValue = pItem->m_szBirthPlace;
    }
    else if ( sUpperKey==_T("АДРЕСА") ) {
      sValue = pItem->m_szAddress;
    }
    else if ( sUpperKey==_T("ДН") ) { // Держава народження
      sValue = pItem->m_szBPCountry;
    }
    else if ( sUpperKey==_T("ОН") ) { // Область народження
      sValue = pItem->m_szBPRegion;
    }
    else if ( sUpperKey==_T("РН") ) { // Район народження
      sValue = pItem->m_szBPDistrict;
    }
    else if ( sUpperKey==_T("МН") ) { // Місто народження
      sValue = GetCity(pItem->m_szBPCity);
    }
    else if ( sUpperKey==_T("МССН") ) { // Місце народження: Місто (село, селище)
      sValue = GetShortTypeOfCity(pItem->m_szBPCity);
    }
    else if ( sUpperKey==_T("ОП") ) {   // Місце проживання: Область
      sValue = pItem->m_szRPRegion;
    }
    else if ( sUpperKey==_T("РП") ) {   // Місце проживання: Район
      sValue = pItem->m_szRPDistrict;
    }
    else if ( sUpperKey==_T("МССП") ) { // Місце проживання: місто (село, селище)
      sValue = GetShortTypeOfCity(pItem->m_szRPCity);
    }
    else if ( sUpperKey==_T("МП") ) {   // Місце проживання: місто
      sValue = GetCity(pItem->m_szRPCity);
    }
    else if ( sUpperKey==_T("ВУЛ") ) {  // Місце проживання: вулиця
      sValue = pItem->m_szRPStreet;
    }
    else if ( sUpperKey==_T("ТВУЛ") ) {  // Місце проживання: тип вулиці (вулиця, прошпект, провулок, площа тощо)
      CString szType;
      sValue = TypeOfStreet(pItem->m_szRPStreet, szType);
    }
    else if ( sUpperKey==_T("НВУЛ") ) {  // Місце проживання: назва вулиці (прошпекту, провулка, площі тощо)
      CString szType;
      sValue = TypeOfStreet(pItem->m_szRPStreet, szType);
      if ( szType.IsEmpty() ) {
        sValue = pItem->m_szRPStreet;
      }
      else {
        sValue = pItem->m_szRPStreet;
        sValue.Replace(szType, _T(""));
      }
      sValue = MakeCanonicalName(Trim(sValue));
      sValue.TrimLeft('.');
      sValue.TrimLeft(' ');
    }
    else if ( sUpperKey==_T("БУД") ) {  // Місце проживання: будинок
      sValue = pItem->m_szRPHouse;
    }
    else if ( sUpperKey==_T("Б") )   {  // Місце проживання: будинок
      CString szSect;
      ParseBuilding(pItem->m_szRPHouse, sValue, szSect);
    }
    else if ( sUpperKey==_T("К") )   {  // Місце проживання: будинок (№ корпусу (блок, секція тощо)
      CString szHouse;
      ParseBuilding(pItem->m_szRPHouse, szHouse, sValue);
    }
    else if ( sUpperKey==_T("КВ") ) {   // Місце проживання: квартира
      sValue = pItem->m_szRPFlat;
    }
    else if ( sUpperKey==_T("ДСДДММРРРР") ) {   // Дата смерті: дд.мм.рррр
      sValue = GetDateDDMMYYYY(pItem->m_DeathDate);
    }
    else if ( sUpperKey==_T("ДСДДМММРРРР") ) {   // Дата смерті: дд ммм рррр
      sValue = GetDateDDMMMYYYYr(pItem->m_DeathDate);
    }
  }
  else if ( IsCommonSect(NULL, sUpperKey, sValue, bConvert, bFirst, NULL) ) {
    bOk = true;
  }
  else
    bOk = false;
  
  int maxsize = sValue.GetLength();
  if ( maxsize+1 > BufSize ) {
    maxsize = BufSize-1;
  }

  if ( bOk ) {
    if ( bFirst && !sValue.IsEmpty() ) {
      if ( IsCyrUpper(sTrimKey.GetAt(0)) ) {
        sValue.SetAt( 0, CyrUpper(sValue.GetAt(0)) );
      }
      else if ( IsCyrLower(sTrimKey.GetAt(0)) ) {
        sValue.SetAt( 0, CyrLower(sValue.GetAt(0)) );
      }
    }
    if ( bConvert ) {
      if ( sTrimKey==sUpperKey )
        sValue = UpperString(sValue);
      else
        sValue = MakeCanonicalName(sValue);
    }
    if ( sTrimKey != sKey ) {
      sKey.Replace(sTrimKey, sValue );
      sValue = sKey;
    }
  }
  if ( sValue.IsEmpty() && g_fEmptyDash ) {
    strcpy(pDestBuf, _T("--"));
  }
  else {
    strncpy(pDestBuf, sValue, maxsize);
    pDestBuf[maxsize] = 0;
  }
  return bOk;
}

struct ElectKWData {
  CElectItem*    pItem;
  int            Number;
};

void OnElectKeyword(LPCTSTR szKeyword, CString& szReplace, DWORD dwData) {
  TCHAR buf[1024];
  buf[0] = 0;
  ElectKWData* pData = (ElectKWData*)dwData;
  if ( pData ) {
    ElectEncoder(buf, 1024, szKeyword, pData->pItem, pData->Number);
  }
  else {
    ElectEncoder(buf, 1024, szKeyword, NULL        , NULL         );
  }
  if ( buf[0] != 0 &&  buf[0] != '-' ) {
    szReplace = buf;
  }
}

BOOL ConvertForElect(const CString& sTemplate, const CString& sOutName, CPtrArray& array) {
  if ( array.GetSize()==0 ) {
    return false;
  }
  CUCnv uCnv;

  if ( false==uCnv.Copy(sTemplate, sOutName) ) {
    return false;
  }

  if ( false==uCnv.Read(sOutName) ) {
    return false;
  }
  CWaitCursor wc;

  // uCnv.ReplaceContent(OnElectKeyword, (DWORD)NULL, false);

  g_fEmptyDash = theIniCache.GetTVKDash();
  g_nTotalRecs  = g_nTotalPages = 0;

  CString sBuffer, sTitleRow, sTableRow, sFootnote;
  CString szTitle, szEndTitle, szTable, szEndTable, szFootnote, szEndFootnote;
  bool bTitleRow=false, bTableRow=false, bFootnote=false;

  sTitleRow = uCnv.GetRow(_T("ПЗ"), _T("КЗ"));
  if ( false==sTitleRow.IsEmpty() ) {
    bTitleRow = true;
  }
  sTableRow = uCnv.GetRow(_T("ПТ"), _T("КТ"));
  if ( false==sTableRow.IsEmpty() ) {
    bTableRow = true;
  }
  sFootnote = uCnv.GetRow(_T("ПВ"), _T("КВ"));
  if ( false==sFootnote.IsEmpty() ) {
    bFootnote = true;
  }
  sBuffer = uCnv.GetData();

  ElectKWData eKWData;
  eKWData.Number = 1;
  eKWData.pItem  = NULL;

  CString sRows;
  BOOL fPlaceChanged = true;
  CString szCountry, szRegion, szDistrict, szCity;
  BOOL fDistrictInCity = true;
  int nCount = array.GetSize();

  BOOL fRags = GetRagsType(theIniCache.GetRAGS())==TCHAR('Р');

  theElections.Clear();

  theElections.m_szPeriod = GetPeriod();

  CTerritory* pTerritory = NULL;

  CProgressBar bar(_T("Будується список для ТВК..."), 80, nCount-1, true, 2);
 
  for( int i(0); i < nCount; i++ ) {
    CElectItem* pItem = (CElectItem*)array.GetAt(i);
    if ( fRags ) {
      if ( szCity != pItem->m_szRPCity || szDistrict != pItem->m_szRPDistrict ||
           szRegion != pItem->m_szRPRegion || szCountry != pItem->m_szRPCountry )
        fPlaceChanged = true;
    }
    else {
      if (szDistrict != pItem->m_szRPDistrict || szRegion != pItem->m_szRPRegion || szCountry != pItem->m_szRPCountry)
        fPlaceChanged = true;
    }
    if ( fPlaceChanged ) {
      CString szTerritory = GetPlace(pItem->m_szRPCountry, pItem->m_szRPRegion, pItem->m_szRPDistrict, pItem->m_szRPCity, false);
      pTerritory = theElections.AddTerritiry(szTerritory);
    }
    pTerritory->Add(pItem);
    eKWData.pItem = pItem;
    szCity    = pItem->m_szRPCity;
    szDistrict= pItem->m_szRPDistrict;
    szRegion  = pItem->m_szRPRegion;
    szCountry = pItem->m_szRPCountry;
    if ( fPlaceChanged ) {
      eKWData.Number = 1;
      fPlaceChanged = false;
      if ( i==0 && bTitleRow ) {
        sBuffer.Replace(sTitleRow, _T("")); 
      }
      else if ( i > 0  ) {
        if ( bFootnote ) {
          sBuffer.Replace(sFootnote, _T("")); 
          CString sNewFootnote = uCnv.EncodeRow(sFootnote, OnElectKeyword, (DWORD)&eKWData);
          sRows += g_szNewString;
          sRows += sNewFootnote;
        }
        sRows += g_szNewPage;
      }
      sRows += uCnv.EncodeRow(sTitleRow, OnElectKeyword, (DWORD)&eKWData);
    }
    CString sEncodedRow = uCnv.EncodeRow(sTableRow, OnElectKeyword, (DWORD)&eKWData);
    sRows += sEncodedRow;
    eKWData.Number++;
    bar.SetPos(i);
    PeekAndPump();
  }

  if ( bFootnote ) {
    sRows += g_szNewString;
    sRows += uCnv.EncodeRow(sFootnote, OnElectKeyword, NULL);
  }
    
  sBuffer.Replace(sTableRow, sRows);
  /*
  if ( false==szTitle.IsEmpty()       ) sBuffer.Replace(szTitle,       g_szEmpty );
  if ( false==szEndTitle.IsEmpty()    ) sBuffer.Replace(szEndTitle,    g_szEmpty );
  if ( false==szTable.IsEmpty()       ) sBuffer.Replace(szTable,       g_szEmpty );
  if ( false==szEndTable.IsEmpty()    ) sBuffer.Replace(szEndTable,    g_szEmpty );
  if ( false==szFootnote.IsEmpty()    ) sBuffer.Replace(szFootnote,    g_szEmpty );
  if ( false==szEndFootnote.IsEmpty() ) sBuffer.Replace(szEndFootnote, g_szEmpty );
  */

  uCnv.SetData(sBuffer);
  uCnv.ReplaceContent(OnElectKeyword, NULL);
  uCnv.Write(sOutName);

  return true;
}

struct BlankKWData {
  RegBlankItem*  pItem;
  int            Number;
};

void OnBlankKeyword(LPCTSTR szKeyword, CString& szReplace, DWORD dwData) {
  BlankKWData*   pData  = (BlankKWData*)dwData;

  CString sKey(szKeyword);
  CString sTrimKey = Trim(szKeyword);
  CString sUpperKey = UpperString(sTrimKey);
  CString sLowerKey = LowerString(sTrimKey);
  BOOL bConvert = false;
  BOOL bFirst = false;
  int  nBeforeSpaces = 0;

  const Keyword* pKeyword = theKeywords.Lookup(sUpperKey);

  RegBlankItem* pItem = (pData && pData->pItem) ? pData->pItem : NULL;

  if ( pKeyword ) {
    switch( pKeyword->id ) {
      case IDKW_N         : // №          Номер з/р
        if ( pData ) { szReplace.Format(_T("%d"), pData->Number); }
        return;
      case IDKW_NAZ       : // НАЗ        Номер актового запису
        if ( pItem ) { szReplace.Format(_T("%d"), pItem->Number); }
        return;
      case IDKW_VYD       : // ВИД        Вид актового запису
        if ( pItem ) {
          switch( TCHAR(pItem->bType) ) {
            case TCHAR('Н'):  szReplace = _T("народження");  break;
            case TCHAR('С'):  szReplace = _T("смерть");      break;
            case TCHAR('О'):  szReplace = _T("одруження");   break;
          }
        }
        return;
      case IDKW_NS        : // НС         Номер свідоцтва
        if ( pItem ) { szReplace.Format(_T("%s"), pItem->szCertNumber); }
        return;
      case IDKW_SS        : // СС         Серія свідоцтва
        if ( pItem ) { szReplace.Format(_T("%s"), pItem->szCertSeria);  }
        return;
      case IDKW_PIB       : // ПІБ        Прізвище, ім'я, по батькові
        if ( pItem ) { szReplace = pItem->szPIB; bConvert = true;       }
        return;
      case IDKW_DDMMMRRRR : // ДДМММРРРР  Дата реєстрації ДД МММ РРРР
        if ( pItem ) { szReplace = GetDateDDMMMYYYYr(pItem->DataReg);   }
        return;
      case IDKW_DDMMRRRR  : // ДДММРРРР   Дата реєстрації: дд.мм.рррр
        if ( pItem ) { szReplace = GetDateDDMMYYYY(pItem->DataReg);     }
        return;
      default             :
        IsCommonSect(pKeyword, NULL, sUpperKey, szReplace, bConvert, bFirst, NULL);
        break;
    }
  }
  else if ( sUpperKey.Left(9)==_T("ДДМММРРРР") ) {     // Дата реєстрації
    szReplace = GetDateDDMMMYYYYr(pItem->DataReg);
  }
  else if ( sUpperKey.Left(8)==_T("ДДММРРРР") ) {      // Дата реєстрації: дд.мм.рррр
    szReplace = GetDateDDMMYYYY(pItem->DataReg);
  }

  if ( false==szReplace.IsEmpty() ) {
    if ( bFirst ) {
      if ( IsCyrUpper(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt( 0, CyrUpper(szReplace.GetAt(0)) );
      }
      else if ( IsCyrLower(sTrimKey.GetAt(0)) ) {
        szReplace.SetAt( 0, CyrLower(szReplace.GetAt(0)) );
      }
    }
    if ( bConvert ) {
      if ( sKey==sUpperKey )
        szReplace = UpperString(szReplace);
      else
        szReplace = MakeCanonicalName(szReplace);
    }
    if ( sTrimKey != sKey ) {
      sKey.Replace(sTrimKey, szReplace);
      szReplace = sKey;
    }
  }

}

BOOL ConvertForBlankRegister(const CString& sTemplate, const CString& sOutName) {
  CUCnv uCnv;

  if ( false==uCnv.Copy(sTemplate, sOutName) ) {
    return false;
  }

  if ( false==uCnv.Read(sOutName) ) {
    return false;
  }
  
  CWaitCursor wc;
  
  CPtrArray Records;

  CDate dFrom(g_odtFrom), dTill(g_odtTill);

  if ( g_dwPrintBlanks & RF_BIRTH ) {
    try {
      CRSBirthes rs(&theDataManager.m_dbYear);
      rs.Open( dbOpenDynaset, _T("SELECT * FROM BIRTHES"), dbReadOnly);
      while ( !rs.IsEOF() ) {
        if ( IsValidDateReg(rs.m_DATEREG) && false==IsEmptyText(rs.m_SURNAME) ) {
          CDate date_reg(rs.m_DATEREG);
          if ( dFrom <= date_reg && date_reg <= dTill ) {
            if ( false==IsEmptyText(rs.m_CERTIFICATE_SERIA) && false==IsEmptyText(rs.m_CERTIFICATE_NUMBER) ) {
              RegBlankItem* pItem = new RegBlankItem;
              pItem->bType = TCHAR('Н');
              pItem->szCertSeria  = rs.m_CERTIFICATE_SERIA;
              pItem->szCertNumber = rs.m_CERTIFICATE_NUMBER;
              pItem->szPIB   = MakeFIO(rs.GetNewOrOldSurname(), rs.GetNewOrOldName(), rs.GetNewOrOldPatronymic());
              pItem->Number  = rs.m_NUMBER;
              pItem->DataReg = rs.m_DATEREG;
              Records.Add( pItem );
            }
          }
        }
        rs.MoveNext();
      }
      rs.Close();
    }
    catch (CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      LogDBError(e, _T("BirthForBlank"));
      e->Delete();
    }
  }
  if ( g_dwPrintBlanks & RF_MARRIAGE ) {
    try {
      CRSMarriages rs(&theDataManager.m_dbYear);
      rs.Open( dbOpenDynaset, _T("SELECT * FROM MARRIAGES"), dbReadOnly);
      while ( !rs.IsEOF() ) {
        if ( IsValidDateReg(rs.m_DATEREG) && false==IsEmptyText(rs.m_MOLD_SURNAME) && false==IsEmptyText(rs.m_WOLD_SURNAME)) {
          CDate date_reg(rs.m_DATEREG);
          if ( dFrom <= date_reg && date_reg <= dTill ) {
            if ( false==IsEmptyText(rs.m_CERTIFICATE_SERIA) && false==IsEmptyText(rs.m_CERTIFICATE_NUMBER) ) {
              RegBlankItem* pItem = new RegBlankItem;
              pItem->bType = TCHAR('О');
              pItem->szCertSeria  = rs.m_CERTIFICATE_SERIA;
              pItem->szCertNumber = rs.m_CERTIFICATE_NUMBER;
              pItem->szPIB.Format(_T("%s %s"),
                                  MakeFIO(rs.m_MOLD_SURNAME, rs.m_MNAME, rs.m_MPATRONYMIC),
                                  MakeFIO(rs.m_WOLD_SURNAME, rs.m_WNAME, rs.m_WPATRONYMIC)
                                 );
              pItem->Number  = rs.m_NUMBER;
              pItem->DataReg = rs.m_DATEREG;
              Records.Add( pItem );
            }
          }
        }
        rs.MoveNext();
      }
      rs.Close();
    }
    catch (CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      LogDBError(e, _T("MarriagesForBlank"));
      e->Delete();
    }
  }
  if ( g_dwPrintBlanks & RF_DEATH ) {
    try {
      CRSDeathes rs(&theDataManager.m_dbYear);
      rs.Open( dbOpenDynaset, _T("SELECT * FROM DEATHES"), dbReadOnly);
      while ( !rs.IsEOF() ) {
        if ( IsValidDateReg(rs.m_DATEREG) && false==IsEmptyText(rs.m_SURNAME) ) {
          CDate date_reg(rs.m_DATEREG);
          if ( dFrom <= date_reg && date_reg <= dTill ) {
            if ( false==IsEmptyText(rs.m_CERTIFICATE_SERIA) && false==IsEmptyText(rs.m_CERTIFICATE_NUMBER) ) {
              RegBlankItem* pItem = new RegBlankItem;
              pItem->bType = TCHAR('С');
              pItem->szCertSeria  = rs.m_CERTIFICATE_SERIA;
              pItem->szCertNumber = rs.m_CERTIFICATE_NUMBER;
              pItem->szPIB   = MakeFIO(rs.m_SURNAME, rs.m_NAME, rs.m_PATRONYMIC);
              pItem->Number  = rs.m_NUMBER;
              pItem->DataReg = rs.m_DATEREG;
              Records.Add( pItem );
            }
          }
        }
        rs.MoveNext();
      }
      rs.Close();
    }
    catch (CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      LogDBError(e, _T("DeathForBlank"));
      e->Delete();
    }
  }

  CString sTitleRow, sTableRow, sRows;
  bool bTitleRow=false, bTableRow=false;
  sTitleRow = uCnv.GetRow(_T("ПЗ"), _T("КЗ"));
  if ( false==sTitleRow.IsEmpty() ) {
    bTitleRow = true;
  }
  sTableRow = uCnv.GetRow(_T("ПТ"), _T("КТ"));
  if ( false==sTableRow.IsEmpty() ) {
    bTableRow = true;
  }
  CString sBuffer = uCnv.GetData();

  BlankKWData bKWData;
  bKWData.Number = 1;
  bKWData.pItem  = NULL;
  int i;

  for( i = 0; i < Records.GetSize(); i++ ) {
    bKWData.pItem = (RegBlankItem*)Records.GetAt(i);
    CString sEncodedRow = uCnv.EncodeRow(sTableRow, OnBlankKeyword, (DWORD)&bKWData);
    sRows += sEncodedRow;
    bKWData.Number++;
  }

  sBuffer.Replace(sTableRow, sRows);
/*
  if ( false==szTitle.IsEmpty()    ) sBuffer.Replace(szTitle,     g_szEmpty );
  if ( false==szEndTitle.IsEmpty() ) sBuffer.Replace(szEndTitle,  g_szEmpty );
  if ( false==szTable.IsEmpty()    ) sBuffer.Replace(szTable,     g_szEmpty );
  if ( false==szEndTable.IsEmpty() ) sBuffer.Replace(szEndTable,  g_szEmpty );
*/

  uCnv.SetData(sBuffer);
  uCnv.ReplaceContent(OnBlankKeyword, NULL);

  BOOL fRet = uCnv.Write(sOutName);

/*
  if ( fRet ) {
    sRow = sTableRow;
    CString sRows;
    int Number = 1;
    CString sEncodedRow;
    for( int i(0); i < Records.GetSize(); i++ ) {
      RegBlankItem* pItem = (RegBlankItem*)Records.GetAt(i);
      sEncodedRow = EncodeRow(sTableRow, pItem, Number);
      sRows += sEncodedRow;
      Number++;
    }
    
    if ( bFootnote ) {
      sRows += g_szNewString;
      sRows += EncodeRow(sFootnote, (RegBlankItem*)NULL, 0);
    }

    sBuffer.Replace(sTableRow, sRows);

    if ( false==szTitle.IsEmpty()       ) sBuffer.Replace(szTitle,       g_szEmpty );
    if ( false==szEndTitle.IsEmpty()    ) sBuffer.Replace(szEndTitle,    g_szEmpty );
    if ( false==szTable.IsEmpty()       ) sBuffer.Replace(szTable,       g_szEmpty );
    if ( false==szEndTable.IsEmpty()    ) sBuffer.Replace(szEndTable,    g_szEmpty );
    if ( false==szFootnote.IsEmpty()    ) sBuffer.Replace(szFootnote,    g_szEmpty );
    if ( false==szEndFootnote.IsEmpty() ) sBuffer.Replace(szEndFootnote, g_szEmpty );
  }
*/

  for( i = 0; i < Records.GetSize(); i++ ) {
    RegBlankItem* pItem = (RegBlankItem*)Records.GetAt(i);
    delete pItem;
  }
  Records.RemoveAll();

  return fRet;

}