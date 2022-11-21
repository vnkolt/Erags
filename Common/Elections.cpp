//
// Elections.cpp
//
#include "stdafx.h"
#include "Elections.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _ERAGS
CElections theElections;
#endif

//
// CElectItem
//
CElectItem::CElectItem() {
  m_BirtDate = m_DeathDate = (DATE)0;
  m_DateReg  = (DATE)0;
  m_Number = 0;
}
//
// CTerritory
//
void CTerritory::Add(CElectItem* pItem) {
  m_array.Add(pItem);
}

//
// CElections
//
CElections::CElections() {
}
CElections::~CElections() {
  Clear();
}
void CElections::Clear() {
  for( int i(0); i < m_Territories.GetSize(); i++ ) {
    CTerritory* pTerritory = (CTerritory*)m_Territories.GetAt(i);
    delete pTerritory;
  }
  m_Territories.RemoveAll();
}

int CElections::CalcTotalItems() {
  int nItems = 0;
  for( int i(0); i < m_Territories.GetSize(); i++ ) {
    CTerritory* pTerritory = (CTerritory*)m_Territories.GetAt(i);
    nItems += pTerritory->m_array.GetSize();
  }

  return nItems;
}
CTerritory* CElections::AddTerritiry(LPCTSTR szTerritory) {
  CTerritory* pTerritory = new CTerritory(szTerritory);
  m_Territories.Add(pTerritory);
  return pTerritory;
}