//
// Globals.h
//
#pragma once

class CIniCache {
public:
  CIniCache();
  ~CIniCache();
private:
  BOOL                m_fLoaded;
  CDaoRecordset*      m_prs;

  CMapStringToString  m_AbbrMap;
  CMapStringToString  m_keys;

  LPCTSTR             m_szCommonSect;
  LPCTSTR             m_szAbbrSect;
/*
  LPCTSTR             m_szBirthSect;
  LPCTSTR             m_szMarriageSect;
  LPCTSTR             m_szDivorceSect;
  LPCTSTR             m_szChangeSect;
  LPCTSTR             m_szDeathSect;
*/
public:

  void      FillAbbrCache();
  POSITION  GetAbbrStartPosition();
  void      GetNextAbbr(POSITION& pos, CString& sKey, CString& sValue);
  BOOL      LookupAbbr(LPCTSTR szKey, CString& sValue);


  BOOL    Open(CDaoDatabase& db);
  BOOL    Load(CDaoDatabase& db);
  BOOL    IsOpen();
  void    Close();

  UINT      HashKey(LPCTSTR szKey);
  CString   GetPrivateProfileString(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal);
  CString   GetPrivateProfileString(LPCTSTR szSect, LPCTSTR szKey);
  UINT      GetPrivateProfileInt(LPCTSTR szSect, LPCTSTR szKey, UINT nDefVal);

  CString   GetSVal(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal);
  UINT      GetIVal(LPCTSTR szSect, LPCTSTR szKey, UINT iDefVal);

  CString   GetCOUNTRY();
  CString   GetREGION();
  CString   GetCITY();
  CString   GetDISTRICT();

  CString   GetRAGS();

  
  CString   GetRagsFullName();

  CString   GetRacsName();
  void      SetRacsName(LPCTSTR szName);
  CString   GetRacsDirectorName();
  void      SetRacsDirectorName(LPCTSTR szName);
  CString   GetRacsDirectorPosition();
  void      SetRacsDirectorPosition(LPCTSTR szPosition);

  CString   GetSpecialistNameForBirth();
  void      SetSpecialistNameForBirth(LPCTSTR szName);
  CString   GetSpecialistPosForBirth();
  void      SetSpecialistPosForBirth(LPCTSTR szName);

  CString   GetSpecialistNameForDeath();
  void      SetSpecialistNameForDeath(LPCTSTR szName);
  CString   GetSpecialistPosForDeath();
  void      SetSpecialistPosForDeath(LPCTSTR szName);

  CString   GetPosada();

  BOOL         GetBool(LPCTSTR szValueName, BOOL fDefault=false);
  void         SetBool(LPCTSTR szValueName, BOOL fBool);

  BOOL         GetWriteRacsName();
  void         SetWriteRacsName(BOOL fWrite);
  BOOL         GetWriteRacsDirectorName();
  void         SetWriteRacsDirectorName(BOOL fWrite);
  BOOL         GetWriteRacsDirectorPosition();
  void         SetWriteRacsDirectorPosition(BOOL fWrite);
  BOOL         GetWriteBirthSpecialistName();
  void         SetWriteBirthSpecialistName(BOOL fWrite);
  BOOL         GetWriteBirthSpecialistPosition();
  void         SetWriteBirthSpecialistPosition(BOOL fWrite);
  BOOL         GetWriteDeathSpecialistName();
  void         SetWriteDeathSpecialistName(BOOL fWrite);
  BOOL         GetWriteDeathSpecialistPosition();
  void         SetWriteDeathSpecialistPosition(BOOL fWrite);

  CString   GetPIBPO();

  CString   GetParent();

  BOOL      IsVyconcom(const CString& sRags);

};

BOOL LoadMDBValues();
BOOL LoadCaches(CProgressCtrl* pProgressCtrl, CStatic* pStatic);
void CloseHelperDB();

extern LPCTSTR   g_szEmpty;
extern CIniCache theIniCache;
extern CString   g_szRacsName;
extern CString   g_szRacsDirectorName;
extern CString   g_szRacsDirectorPos;
extern CString   g_szSpecialistNameForBirth;
extern CString   g_szSpecialistPosForBirth;
extern CString   g_szSpecialistNameForDeath;
extern CString   g_szSpecialistPosForDeath;

extern BOOL      g_fWriteRacsName;
extern BOOL      g_fWriteRacsDirectorName;
extern BOOL      g_fWriteRacsDirectorPosition;
extern BOOL      g_fWriteBirthSpecialistName;
extern BOOL      g_fWriteBirthSpecialistPosition;
extern BOOL      g_fWriteDeathSpecialistName;
extern BOOL      g_fWriteDeathSpecialistPosition;

