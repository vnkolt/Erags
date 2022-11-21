#if !defined(DATAMANAGER_H_INCLUDED)
#define DATAMANAGER_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geography.h"
#include "..\Common\CyrString.h"

#pragma warning(disable : 4995)

class CFByP : public CObject {
// data members:
public:
  CString m_sKey;
  CString m_sName;
// Constuctor:
  CFByP(LPCTSTR szKey, LPCTSTR szName);
};

class CFByPArray {
// data members:
public:
  CPtrArray m_array;
  CString   m_sFileName;
// Constructor/Destructor
public:
  CFByPArray();
  ~CFByPArray();
// Operations:
private:
  void Clear();
public:
  CFByP*  Find(LPCTSTR szKey, LPCTSTR szName);
  CString OfferDefault(const CString&  sPatronymic);
  CFByP*  Offer(const CString&  sPatronymic);
  void    Add(LPCTSTR szKey, LPCTSTR szName);
  void    Sort();
  void    Load(LPCTSTR szFileName);
  void    Save();
};

class CDataManager : public CObject {

public:
// Constructors
	CDataManager();
  ~CDataManager();

  void  Init();

// Attributes
public:
  CDaoDatabase    m_dbYear;
  CDaoDatabase    m_dbLists;
  int             m_Year;

  CString         m_strYearDBName;
  CString         m_strListsDBName;
  CFByPArray      m_FByPArray;

  BOOL  m_fBeginTables;
  BOOL  m_fBirthesTable, m_fMarrigesTable, m_fDivorcesTable, m_fChangesTable, m_fDeathesTable;

  BOOL  m_fCausesOfDeathTable, m_fCitizenshipsTable, m_fGeographyTable,
        m_fHospitalsTable, m_fMIATable, m_fNamesTable, m_fPatronymicsTable,
        m_fRListTable, m_fStreetTable;
  BOOL  m_fEndTables;
private:
  BOOL  m_fCashFilled;
// Operations
private:
  BOOL    CreateTextField(CDaoTableDef& td, LPCTSTR szFieldName, LPCTSTR szTableName, long FieldSize, long ordinal, BOOL fMemo=false);
public:

  bool    SetYearDBName(LPCTSTR pszFileName);
  CString GetYearDBName();
  bool    SetListsDBName(LPCTSTR pszFileName);
  CString GetListsDBName();

  void    ResizeTextField(CDaoTableDef& td, CDaoFieldInfo& fieldinfo, int newSize);
  void    ModifyDatabase();
  bool    OpenDatabases(LPCTSTR szYearDBName=NULL);

  void    CloseYearDB();
  void    CloseHelpersDB();
  void    CloseDatabases();
  BOOL    IsHelperOpened();

  void    LoadTextData();

  void    FillCBoxes(LPCTSTR szRSName, LPCTSTR szFldName, int nCount, ...);


  void    FillMNames();
  void    FillWNames();
  void    FillMPatronymics();
  void    FillWPatronymics();
  void    FillCitizenships();
  void    FillMIAs();
  void    FillHospitals();
  void    FillStreets();

  void    FillCaches();

  bool    IsTablePresent(LPCTSTR pszTableName);
  bool    IsFieldPresent(CDaoTableDef& td, LPCTSTR szFieldName);
  bool    IsHelperTablePresent(LPCTSTR pszTableName);
  bool    IsTableInArray(LPCTSTR pszTableName);

  bool    FindAndLoadHelpersDB();

private:
  BOOL  RepairDatabase(LPCTSTR lpszPathName);
  BOOL  OpenDatabase(CDaoDatabase& db, LPCTSTR lpszPathName, BOOL fExclusive, BOOL fReadOnly, LPCTSTR szConnect=NULL);
  bool  OpenYearDB(LPCTSTR szYearDBName=NULL);
  bool  OpenHelpersDB();
protected:

// Flags
  CStringArray m_strTables;
};

extern CDataManager theDataManager;

#endif//DATAMANAGER_H_INCLUDED