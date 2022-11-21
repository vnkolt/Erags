#pragma once

//
// Elections.h
//

class CElectItem {
public:
  CString       m_szNewSurname, m_szNewName, m_szNewPatronymic;
  CString       m_szOldSurname, m_szOldName, m_szOldPatronymic;
  CString       m_szNewSNP;
  CString       m_szOldSNP;
  COleDateTime  m_BirtDate;
  COleDateTime  m_DeathDate;
  CString       m_szRPCountry, m_szRPRegion, m_szRPDistrict, m_szRPCity,
                m_szRPStreet, m_szRPHouse, m_szRPFlat;
  CString       m_szBPCountry, m_szBPRegion, m_szBPDistrict, m_szBPCity;
  CString       m_szAddress;
  CString       m_szBirthPlace;
  CString       m_szType;

  COleDateTime  m_DateReg;
  short         m_Number;
  CElectItem();
};

class CTerritory {
public:
  CString   m_szTerritory;
  CPtrArray m_array;
  CTerritory(LPCTSTR szTerritory) {
    m_szTerritory = szTerritory;
  }
  void  Add(CElectItem* pItem);
};

class CElections {
public:
  CElections();
  ~CElections();
public:
  CPtrArray     m_Territories;
  CString       m_szPeriod;
  COleDateTime  m_From;
  COleDateTime  m_Till;
public:
  void          Clear();
  int           CalcTotalItems();
  CTerritory*   AddTerritiry(LPCTSTR szTerritory);
};

typedef void (* pProgressRoutine)(int nCount, int nProcessed, void* lpData);

typedef CString (* pElectEncoder)(LPCTSTR szKey, CElectItem* pItem, int Number);

#ifdef _ERAGS
extern CElections theElections;
#endif

