#ifndef DATEFUNC_H_INCLUDED
#define DATEFUNC_H_INCLUDED

struct Duration {
  int years;
  int months;
  int days;
  Duration(int y, int m, int d)
    : years(y), months(m), days(d) {}
};

class CDate {
public:
  CDate();
  CDate(int year, int month, int day);
  CDate(COleDateTime odt);
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
  friend Duration 
  duration(const CDate&, const CDate&);
  friend bool 
  operator<(const CDate&, const CDate&);
  friend bool 
  operator<=(const CDate&, const CDate&);
  friend bool 
  operator>(const CDate&, const CDate&);
  friend bool 
  operator>=(const CDate&, const CDate&);
  friend bool 
  operator==(const CDate&, const CDate&);
  friend bool 
  operator!=(const CDate&, const CDate&);
private:
  int m_year;
  int m_month;
  int m_day;
  int Compare(const CDate&) const;
  static int DaysInPrevMonth(int year,int mon);
};

Duration duration(const CDate& date1, const CDate& date2);
CString  GetYear(const COleDateTime& odt, bool fCentury=true);
CString  GetByMonth(const COleDateTime& odt);
CString  GetDay(const COleDateTime& odt);

CString  GetAge(COleDateTime odtBirth, COleDateTime odtDeath, bool fAge=false, bool fM=false, bool fD=false);

CString  strDayMonth(COleDateTime& odt);
CString  strYear(COleDateTime& odt);
CString  GetDateDDMMYYYY(const COleDateTime& d);
CString  GetDateDDMMYYYYr(const COleDateTime& d);
CString  GetDateDDMMMYYYYr(const COleDateTime& d);
CString  GetDateDDMMMYYYYr(LPCTSTR szDate);

CString  GetDateYYYY(const COleDateTime& d);

CString GetStrDay(const CString& sDate);
CString GetStrMonth(const CString& sDate);
CString GetStrYear(const CString& sDate);
CString GetPrevWorkDay(const COleDateTime& odt);

#endif // DATEFUNC_H_INCLUDED