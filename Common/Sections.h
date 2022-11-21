#if !defined(SECTIONS_H_INCLUDED)
#define SECTIONS_H_INCLUDED

#include <afxcoll.h>

#define RDF_MINZIZE 512

struct SRDFHeader {
  char    rdfSignature[8]; // Now it must RDFSF1.0
  time_t  rdfTime;         // Creating time for .rdf and crypt key
  DWORD   rdfCheckSum;     // Check sum of original buffer
};

class CSection {
public:
  CSection(LPCTSTR szSectionName);
  ~CSection();
// member variables
  CString       m_sSectionName;
  CStringArray  m_aKeyNames;
  CStringArray  m_aKeyValues;
public:
  void    AddValue(LPCTSTR szKeyName, LPCTSTR szKeyValue);
  void    AddValue(LPCTSTR szKeyNameEQUKeyValue);
  CString GetValue(LPCTSTR szKeyName);
  CString GetSectionName() { return m_sSectionName; }
  int     GetNumberOfKeys() { return m_aKeyNames.GetSize(); }
  DWORD   GetSizeForBuffer();
  CString GetKeyName(int i)  { return m_aKeyNames.GetAt(i); }
  CString GetKeyValue(int i) { return m_aKeyValues.GetAt(i); }
};

class CIniContainer {
public:
  CIniContainer();
  ~CIniContainer();
protected:
  CPtrArray*  m_aSections;
  CSection*   m_pLastUsedSection;
public:
  const CSection* AddSection(LPCTSTR szSectionName);
  void  AddValue(LPCTSTR szKeyNameEQUKeyValue);
  void  AddValue(LPCTSTR szKeyName, LPCTSTR szKeyValue);
  DWORD GetSizeForBuffer();
  int   GetNumberOfSections() { return m_aSections->GetSize(); }
  CSection* GetSection(int index);
  CSection* GetSection(LPCTSTR szSectionName);
  void  ClearContainer();
};

#endif