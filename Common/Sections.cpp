//
// Section.cpp
//
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Sections.h"

//
// CSection methods
//
CSection::CSection(LPCTSTR szSectionName) {
  m_sSectionName = szSectionName;
}

CSection::~CSection() {
  m_aKeyNames.RemoveAll();
  m_aKeyValues.RemoveAll();
}

void CSection::AddValue(LPCTSTR szKeyName, LPCTSTR szKeyValue) {
  m_aKeyNames.Add(szKeyName);
  m_aKeyValues.Add(szKeyValue);
}

void CSection::AddValue(LPCTSTR szKeyNameEQUKeyValue) {
  CString str = szKeyNameEQUKeyValue;
  int iEQ = str.Find('=');
  if (iEQ == -1)
    AddValue(szKeyNameEQUKeyValue, szKeyNameEQUKeyValue);
  else
    AddValue(str.Left(iEQ), str.Mid(iEQ+1));
}

CString CSection::GetValue(LPCTSTR szKeyName) {
  for ( int i(0); i < m_aKeyNames.GetSize(); i++) {
    if ( m_aKeyNames.GetAt(i).CompareNoCase(szKeyName)==0 )
      return m_aKeyValues.GetAt(i);
  }
  return CString(_T(""));
}

DWORD CSection::GetSizeForBuffer() {
  DWORD dwSize = sizeof(int) +                      // 
                 m_sSectionName.GetLength()+1;      // szSectionName
  for ( int i(0); i < m_aKeyNames.GetSize(); i++) {
    dwSize += m_aKeyNames.GetAt(i).GetLength()+1;   // szKeyName
    dwSize += m_aKeyValues.GetAt(i).GetLength()+1;  // szKeyValue
  }
  return dwSize;
}
//
// CIniContainer methods
//
CIniContainer::CIniContainer() {
  m_pLastUsedSection = NULL;
  m_aSections = new CPtrArray;
}

CIniContainer::~CIniContainer() {
  ClearContainer();
  delete m_aSections;
}

void CIniContainer::ClearContainer() {
  for( int i(0); i < m_aSections->GetSize(); i++ ) {
    CSection* pSection = (CSection*)m_aSections->GetAt(i);
    delete pSection;
  }
  m_aSections->RemoveAll();
}

const CSection* CIniContainer::AddSection(LPCTSTR szSectionName) {
CSection* pSection = new CSection(szSectionName);
  m_pLastUsedSection = pSection;
  m_aSections->Add(pSection);
  return (const CSection*)pSection;
}

void CIniContainer::AddValue(LPCTSTR szKeyNameEQUKeyValue) {
  if ( m_pLastUsedSection )
    m_pLastUsedSection->AddValue(szKeyNameEQUKeyValue);
}

void CIniContainer::AddValue(LPCTSTR szKeyName, LPCTSTR szKeyValue) {
  if ( m_pLastUsedSection )
    m_pLastUsedSection->AddValue(szKeyName, szKeyValue);
}

DWORD CIniContainer::GetSizeForBuffer() {
DWORD dwSize(0);
  for( int i(0); i < m_aSections->GetSize(); i++ )
    dwSize += ((CSection*)m_aSections->GetAt(i))->GetSizeForBuffer();
  return dwSize;
}

CSection* CIniContainer::GetSection(int index){
  return (CSection*)m_aSections->GetAt(index);
}
CSection* CIniContainer::GetSection(LPCTSTR szSectionName) {
  for (int i(0); i < m_aSections->GetSize(); i++) {
    CSection* pSections = GetSection(i);
    if ( pSections->m_sSectionName.CompareNoCase(szSectionName)==0 )
      return pSections;
  }
  return NULL;
}

