//
// DateFunc.cpp
//
#include "stdafx.h"
#include "Erags.h"
#include "DateFunc.h"

#include "..\Common\CyrString.h"

const int daysInMonth[][13] = {
  {0,31,28,31,30,31,30,31,31,30,31,30,31},
  {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

inline bool isleap(int y) {
  return y%4 == 0 && y%100 != 0 || y%400 == 0;
}

void swap(int& a, int &b) {
  int t = a;
  a = b;
  b = t;
}

////////////////////////////////////////////////////
// CDate class members
CDate::CDate() {
  // Get current date
  time_t tval = time(0);
  struct tm *now = localtime(&tval);
  m_year = now->tm_year + 1900;
  m_month = now->tm_mon + 1;
  m_day = now->tm_mday;
}

CDate::CDate(int yr, int mon, int dy) {
  ASSERT(1 <= mon && mon <= 12);
  ASSERT(1 <= dy && dy <= daysInMonth[isleap(dy)][mon]);
  m_year = yr;
  m_month = mon;
  m_day = dy;
}

CDate::CDate(COleDateTime odt) {
  ASSERT( COleDateTime::valid==odt.GetStatus());
  m_year  = odt.GetYear();
  m_month = odt.GetMonth();
  m_day   = odt.GetDay();
}

int CDate::GetYear() const  { return m_year;  }
int CDate::GetMonth() const { return m_month; }
int CDate::GetDay() const   { return m_day;   }

int CDate::Compare(const CDate& d2) const {
  int result = m_year - d2.m_year;
  if (result == 0) {
    result = m_month - d2.m_month;
    if (result == 0)
      result = m_day - d2.m_day;
  }
  return result;   
}

int CDate::DaysInPrevMonth(int year, int month) {
  if (month == 1) {
    --year;
    month = 12;
  }
  else
    --month;
  return daysInMonth[isleap(year)][month];
}

bool operator<(const CDate& d1, const CDate& d2) {
  return d1.Compare(d2) < 0;
}
bool operator<=(const CDate& d1, const CDate& d2) {
  return d1.Compare(d2) <= 0;
}
bool operator>(const CDate& d1, const CDate& d2) {
  return d1.Compare(d2) >= 0;
}
bool operator>=(const CDate& d1, const CDate& d2) {
  return d1.Compare(d2) >= 0;
}
bool operator==(const CDate& d1, const CDate& d2) {
  return d1.Compare(d2) == 0;
}
bool operator!=(const CDate& d1, const CDate& d2) {
  return d1.Compare(d2) != 0;
}

////
Duration duration(const CDate& date1, const CDate& date2) {
  int y1 = date1.m_year;
  int y2 = date2.m_year;
  int m1 = date1.m_month;
  int m2 = date2.m_month;
  int d1 = date1.m_day;
  int d2 = date2.m_day;

  // Compute the compare
  int order = date1.Compare(date2);
  if (order == 0)
    return Duration(0,0,1);
  else if (order > 0) {
    // Make date1 precede date2 locally
    swap(y1, y2);
    swap(m1, m2);
    swap(d1, d2);
  }

  int years = y2 - y1;
  int months = m2 - m1;
  int days = d2 - d1;
  ASSERT(years > 0 || years == 0 && months > 0 || years == 0 && months == 0 && days > 0);

  // Do the obvious corrections (must adjust days
  // before months!) - This is a loop in case the
  // previous month is February, and days < -28.
  int lastMonth = m2;
  int lastYear = y2;

  if ( months < 0 ) {
    months += 12;
    years--;
  }

  while (days < 0) {
    // Borrow from month
    ASSERT(months >= 0);
    //days += CDate::DaysInPrevMonth(lastYear, lastMonth--);
    days += daysInMonth[isleap(lastYear)][lastMonth];
    --months;
  }

  if (months < 0) {
    // Borrow from year
    ASSERT(years > 0);
    months += 12;
    --years;
  }
  return Duration(years, months, days);
}

CString GetYear(const COleDateTime& odt, bool fCentury) {
  CString s;
  if ( COleDateTime::valid==odt.GetStatus() ) {
    if ( fCentury )
      s.Format(_T("%04d"), odt.GetYear() );
    else
      s.Format(_T("%02d"), odt.GetYear() % 100 );
  }
  return s;
}
CString GetByMonth(const COleDateTime& odt) {
  CString s;
  if ( COleDateTime::valid==odt.GetStatus() ) {
    s.LoadString(IDS_M01+odt.GetMonth()-1);
  }
  return s;
}
CString GetDay(const COleDateTime& odt) {
  CString s;
  if ( COleDateTime::valid==odt.GetStatus() ) {
    s.Format(_T("%02d"), odt.GetDay() );
  }
  return s;
}

CString GetAge(COleDateTime odtBirth, COleDateTime odtDeath,
              bool fAge/*=false*/, bool fM/*=false*/, bool fD/*=false*/) {
  if ( COleDateTime::valid!=odtBirth.GetStatus() || COleDateTime::valid!=odtDeath.GetStatus() ) {
    return _T("в≥к не встановлено");
  }

  CDate dBirth(odtBirth), dDeath(odtDeath);

  Duration d = duration(dBirth, dDeath); 

  CString sM, sD, sAge;


  if (0==d.years) {
    if ( fM && fD ) {
      return _T("");
    }

    sAge = "";
    if ( 0==d.months )
      sM = CString('-', 8);
    else
      sM.Format(_T("%d"), d.months );

    if ( fM )
      return Trim(sM);

    if (0!=d.months) {
      sAge = sM + _T(" м≥с€ц");
      switch( d.months ) {
        case 1:
          sAge += TCHAR('ь');     break;
        case 2: case 3: case 4:
          sAge += TCHAR('≥');     break;
        default:
          sAge += _T("≥в");       break;
      }
    }

    sD.Format(_T(" %d "), d.days );
    if ( fD )
      return Trim(sD);
    switch( d.days ) {
      case 1: case 21:
        sD += _T(" день");      break;
      case  2: case  3: case  4:
      case 22: case 23: case 24:
        sD += _T(" дн≥");       break;
      default:
        sD += _T(" дн≥в");      break;
    }
    sAge += sD;
  }
  else {
    if ( fM || fD ) {
      if ( fM && fD )
        return _T("рок≥в");
      return _T("");
    }
    sAge.Format(_T("%d"), d.years);
  }

  if (fAge) {
    CString s = _T("у в≥ц≥ ");
    s += sAge;
    sAge = s;
    if (d.years != 0)
      sAge += _T(" р.");
  }
  return sAge;
}

CString strDayMonth(int iDay, int iMonth) {
  const char* szDays[] = { "", "першого", "другого", "третього", "четвертого",
                           "п'€того", "шостого", "сьомого", "восьмого",
                           "дев'€того", "дес€того", "одинадц€того", "дванадц€того",
                           "тринадц€того", "чотирнадц€того", "п'€тнадц€того", "ш≥стнадц€того",
                           "с≥мнадц€того", "в≥с≥мнадц€того", "дев'€тнадц€того", "двадц€того" };
  const char* szMonths[] = {"", "с≥чн€", "лютого", "березн€", "кв≥тн€", "травн€", "червн€",
                            "липн€", "серпн€", "вересн€", "жовтн€", "листопада", "грудн€" };
  CString sRet;
  switch (iDay) {
    case 31:  sRet = _T("тридц€ть першого ");  break;
    case 30:  sRet = _T("тридц€того ");        break;
    default:
      if ( 21 <= iDay && iDay <= 29 )
        sRet.Format(_T("двадц€ть %s "), szDays[iDay-20] );
      else if ( 1 <= iDay && iDay <= 20 )
        sRet = szDays[iDay];
      break;
  }
  if ( 1 <= iMonth && iMonth <= 12 ) {
    sRet += ' ';
    sRet += szMonths[iMonth];
  }
  return sRet;
}
CString strDayMonth(COleDateTime& odt) {
  if ( COleDateTime::valid==odt.GetStatus() )
    return strDayMonth( odt.GetDay(), odt.GetMonth() );
  return CString(_T(""));
}

CString strYearBW(int digit, int iYear) {
  CString s;
  int iMod;
  switch(digit) {
    case 4:
      if (iYear % 1000 == 0)  {
        if (iYear / 1000 == 2)
          s = "двохтис€чного";
        else
          s.Format(_T("%d-го"), iYear);
      }
      else {
        switch(iYear / 1000) {
          case 1:   s = "тис€ча";               break;
          case 2:   s = "дв≥ тис€ч≥";           break;
          default:  s.Format(_T("%d"), iYear);  break;
        }
      }
      break;

    case 3:
      iYear = iYear % 1000;
      iMod = iYear % 100;
      switch(iYear / 100) {
        case 1:
          s = (0==iMod) ? "сотого" : "сто";              break;
        case 2:
          s = (0==iMod) ? "двосотого" : "дв≥сти";        break;
        case 3:
          s = (0==iMod) ? "трьосотого" : "триста";       break;
        case 4:
          s = (0==iMod) ? "чотирьохсотого": "чотириста"; break;
        case 5:
          s = (0==iMod) ? "п'€тисотого" : "п'€тсот";     break;
        case 6:
          s = (0==iMod) ? "ш≥стисотого" : "ш≥стсот";     break;
        case 7:
          s = (0==iMod) ? "сьомисотого" : "с≥мсот";      break;
        case 8:
          s = (0==iMod) ? "в≥сьмисотого" : "в≥с≥мсот";   break;
        case 9:
          s = (0==iMod) ? "дев'€тисотого" : "дев'€тсот"; break;
      }
      break;

    case 2:
      iYear = iYear % 100;
      iMod = iYear % 10;
      switch(iYear / 10) {
        case 1:
           switch (iMod) {
             case 0:
               s = "дес€того";        break;
             case 1:
               s = "одинадц€того";    break;
             case 2:
               s = "дванадц€того";    break;
             case 3:
               s = "тринадц€того";    break;
             case 4:
               s = "чотирнадц€того";  break;
             case 5:
               s = "п'€тнадц€того";   break;
             case 6:
               s = "ш≥стнадц€того";   break;
             case 7:
               s = "с≥мнадц€того";    break;
             case 8:
               s = "в≥с≥мнадц€того";  break;
             case 9:
               s = "дев'€тнадц€того"; break;
           }
           break;
        case 2:
           s = (0==iMod) ? "двадц€того" : "двадц€ть";     break;
        case 3:
           s = (0==iMod) ? "тридц€того" : "тридц€ть";     break;
        case 4:
           s = (0==iMod) ? "сорокового" : "сорок";        break;
        case 5:
           s = (0==iMod) ? "п'€тдес€того" : "п'€тдес€т"; break;
        case 6:
           s = (0==iMod) ? "ш≥стдес€того" : "ш≥стдес€т";  break;
        case 7:
           s = (0==iMod) ? "с≥мдес€того" : "с≥мдес€т";    break;
        case 8:
           s = (0==iMod) ? "в≥с≥мдес€того" : "в≥с≥мдес€т";break;
        case 9:
           s = (0==iMod) ? "дев'€ностого" : "дев'€носто"; break;
      }
      break;
  
    case 1:
      if (iYear % 100 > 20 || iYear % 100 < 10) {
        iMod = iYear % 10;
        switch(iMod) {
          case 1:
            s = "першого";    break;
          case 2:
            s = "другого";    break;
          case 3:
            s = "третього";   break;
          case 4:
            s = "четвертого"; break;
          case 5:
            s = "п'€того";    break;
          case 6:
            s = "шостого";    break;
          case 7:
            s = "сьомого";    break;
          case 8:
            s = "восьмого";   break;
          case 9:
            s = "дев'€того";  break;
        }
      }
      break;
  }
  return s;
}

CString strYear(int iYear) {
  CString sYear;
  for( int d(4); d > 0; d-- ) {
    CString s = strYearBW(d, iYear) + _T(" ");
    sYear += s;
  }
  return sYear;
}
CString strYear(COleDateTime& odt) {
  CString s;
  if ( COleDateTime::valid==odt.GetStatus() ) {
    s = strYear(odt.GetYear());
    s.Replace(_T("  "), _T(" "));
    s.TrimRight();
    // return FindAndReplace(strYear(odt.GetYear()), _T("  "), _T(" "), true);
  }
  return s;
}

CString GetDateDDMMYYYY(const COleDateTime& d) {
  CString sDate;
  if ( d.GetStatus()==COleDateTime::valid && d.m_dt != (DATE)0) {
    sDate.Format( _T("%02d.%02d.%04d"), d.GetDay(), d.GetMonth(), d.GetYear() );
  }
  return sDate;
}

CString GetDateDDMMYYYYr(const COleDateTime& d, BOOL fRoku/*=false*/) {
  CString sDate = GetDateDDMMYYYY(d);
  if ( !sDate.IsEmpty() ) {
    sDate += fRoku ? _T(" року") : _T(" р.");
  }
  return sDate;
}
CString GetDateDDMMMYYYYr(const COleDateTime& d, BOOL fRoku/*=false*/) {
  CString sDate;
  if ( d.GetStatus()==COleDateTime::valid && d.m_dt != (DATE)0) {
    sDate.Format( _T("%02d %s %04d"), d.GetDay(), GetByMonth(d), d.GetYear() );
    sDate += fRoku ? _T(" року") : _T(" р.");
  }
  return sDate;
}
CString GetDateDDMMMYYYYr(LPCTSTR szDate, BOOL fRoku/*=false*/) {
  CString s;
  COleDateTime odt;
  if ( odt.ParseDateTime( szDate, LOCALE_NOUSEROVERRIDE|VAR_DATEVALUEONLY) ) {
    s = GetDateDDMMMYYYYr(odt, fRoku);
  }
  return s;
}
CString  GetDateYYYY(const COleDateTime& d) {
  CString s = GetDateDDMMYYYY(d);
  if ( s.GetLength() > 4 ) {
    s = s.Right(4);
  }
  return s;
}

//
// ‘ункции определени€ числа, мес€ца и года по невалидной строке даты
//
CString GetStrDay(const CString& sDate) {
  CString s, sTok;
  sTok = GetTok(sDate, 0, " ");
  if ( !sTok.IsEmpty() && IsDigit( sTok.GetAt(0) ) && sTok!=GetStrYear(sDate) )
    s = sTok;
  return s;
}
CString GetStrMonth(const CString& sDate) {
  CString s, sTok;
  sTok = GetTok(sDate, 0, " ");
  if ( !sTok.IsEmpty() && UCHAR(sTok.GetAt(0))>=UCHAR('?') )
     s = sTok;
  else {
    sTok = GetTok(sDate, 1, " ");
    if ( !sTok.IsEmpty() && UCHAR(sTok.GetAt(0))>=UCHAR('?') && sTok.GetLength()>4 )
      s = sTok;
  }
  return s;
}
CString GetStrYear(const CString& sDate) {
  CString s, sTok;
  int nTok(0);
  do {
    sTok = GetTok(sDate, nTok, " ").Left(4);
    int nLen = sTok.GetLength();
    if ( sTok.GetLength()==4 ) {
      if ( IsDigit(sTok.GetAt(0)) && IsDigit(sTok.GetAt(1)) && IsDigit(sTok.GetAt(2)) && IsDigit(sTok.GetAt(3)) ) // It's year!
        break;
    }
    nTok++;
  } while ( FALSE==sTok.IsEmpty() );
  s = sTok;
  return s;
}

CString GetPrevWorkDay(const COleDateTime& odt) {
  CString s;
  if ( COleDateTime::valid==odt.GetStatus() ) {
    COleDateTime dt( odt );
    while( TRUE) {
      dt -= COleDateTimeSpan(1, 0, 0, 0);
      switch (dt.GetDayOfWeek() ) {
        case 1: // Sunday
        case 7: // Saturday
          continue;
      }
      switch ( dt.GetMonth() ) {
        case 1:
          switch (dt.GetDay() ) {
            case 1: // Happy New Year!
            case 7: // Merry XMas!
              continue;
          }
          break;
        case 3:
          if ( dt.GetDay() == 8 )
            continue;
          break;
        case 5:
          if ( dt.GetDay() == 9 )
            continue;
          break;
        case 8:
          if ( dt.GetDay() == 24 )  // Independence Day
            continue;
          break;
      }
      break; // Found!
    }
    s.Format( _T("%02d.%02d.%04d р."), dt.GetDay(), dt.GetMonth(), dt.GetYear() );
  }
  return s;
}

BOOL LastDayInMonth(const COleDateTime& odt) {
  COleDateTime dt = odt + COleDateTimeSpan(1, 0, 0, 0);
  if ( odt.GetMonth() != dt.GetMonth() ) {
    return true;
  }
  return false;
}