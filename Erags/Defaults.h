#if !defined(DEFAULTS_H_INCLUDED)
#define DEFAULTS_H_INCLUDED

// Defaults.h

#pragma warning(disable : 4995)

struct LIC_KEY {
  BYTE  RegionKey[4];   //  3  6   8
  BYTE  DistrictKey[4]; //  3  6  16
  BYTE  CityKey[4];     //  3  6  24
  BYTE  RagsKey[4];     //  4  6  32
  WORD  rcSum;          //  4  4  36
};

struct SecurityData {
  short           CheckSum;           // 2
  short           cbSize;             // 2
  int             EraVersion;         // 4  
  Win32Type       OsVersion;          // 4
  BYTE            nDates[8];          // 8
};

typedef unsigned short uint16;
typedef unsigned long  uint32;


#ifndef FREE_LICENCE
#pragma pack(push, r1, 1)
struct RegTimerData {
  uint16 cbSize;          // 2    2
  uint16 cbCheckSum;      // 2    4
  uint32 cbShutdownCount; // 4   10
  uint16 cbWorkedDays;    // 2   12
  uint32 FirstWorkedDate; // 4   16     YYYYMMDD
  uint32 LastWorkedTime;  // 4   20     HHMMSSmmm
  uint32 LastWorkedDate;  // 4   24     YYYYMMDD
  uint16 OverSysDates;    // 2   26
  uint16 Reserved1;       // 2   28
  uint16 Reserved2;       // 2   30
  uint16 Reserved3;       // 2   32
  //uint32 FutureDates;
};
#pragma pack(pop, r1)

enum LK_VALUE { LK_INVALID_LICENCE    = 0,
                LK_VALID_LICENCE      = 1,
                LK_LICENCE_EXPIRED    = 2,
                LK_LICENCE_NOTEXPIRED = 3
              };

class CRegTimer {
private:
  RegTimerData m_rtd;
public:
  CRegTimer();

private:
  CString GetSubkey1();
  CString GetValueName1();
  CString GetSubkey2();

  void            PrepareForWriting(RegTimerData& dest);
  void            EncryptData(RegTimerData& dest);
  void            DecryptData(RegTimerData& dest);
  uint32          GetLastTime();
  uint32          GetLastDate();
  COleDateTime    GetDate(uint32 u32);
  BOOL            IsValid(const RegTimerData& rtd);
  BOOL            ReadGobalData(RegTimerData& dest);
  void            WriteGlobalData();
  BOOL            ReadLocalData(RegTimerData& dest);
  void            WriteLocalData();
  void            Write();

  void            Initialize();
  void            Normalize(RegTimerData& rtd);
  BOOL            ReadMax();
public:
  void    Next();
  void    Startup();
  void    Shutdown();
  void    Reinit(COleDateTime* pStartDate=NULL);
  CString GetMaxDate();
};
extern CRegTimer theRegTimer;

#endif // FREE_LICENCE

#define PRINT_CITIZENSHIP_ACT   1
#define PRINT_CITIZENSHIP_CERT  2
#define PRINT_CITIZENSHIP_OTHER 4
#define PRINT_CITIZENSHIP_ALL   (PRINT_CITIZENSHIP_ACT|PRINT_CITIZENSHIP_CERT|PRINT_CITIZENSHIP_OTHER)


#define MAX_BANKS 20

class CIniCache {
public:
  CIniCache();
  ~CIniCache();
private:
  CDaoRecordset*      m_prs;
  CMapStringToString  m_keys;
  CMapStringToString  m_AbbrMap;
  SecurityData        m_Security;

  LPCTSTR             m_szCommonSect;
  LPCTSTR             m_szBirthSect;
  LPCTSTR             m_szMarriageSect;
  LPCTSTR             m_szDivorceSect;
  LPCTSTR             m_szChangeSect;
  LPCTSTR             m_szDeathSect;
  LPCTSTR             m_szAbbrSect;

#ifndef FREE_LICENCE
public:
  BOOL m_fLimitedLicence;
#endif

private:
  CString GetXorForNewReg();
public:
  CString GetNewRegCode();
  UINT    HashKey(LPCTSTR szKey);
  void    MakeFromIni();

  BOOL  Load();
  BOOL  IsOpen();
  BOOL  Open();
  BOOL  IsEmpty();
  void  Close();

  void      FillAbbrCache();
  POSITION  GetAbbrStartPosition();
  void      GetNextAbbr(POSITION& pos, CString& sKey, CString& sValue);
  BOOL      LookupAbbr(LPCTSTR szKey, CString& sValue);

  CString   GetPrivateProfileString(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal, BOOL fWrite=FALSE);
  CString   GetPrivateProfileString(LPCTSTR szSect, LPCTSTR szKey);
  UINT      GetPrivateProfileInt(LPCTSTR szSect, LPCTSTR szKey, UINT nDefVal);
  BOOL      GetPrivateProfileBinary(LPCTSTR szSect, LPCTSTR szKey, void* pData, UINT cbBytes);

  void      WritePrivateProfileString(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal);
  void      WritePrivateProfileInt(LPCTSTR szSect, LPCTSTR szKey, UINT nDefVal);
  void      WritePrivateProfileBinary(LPCTSTR szSect, LPCTSTR szKey, void* pData, UINT cbBytes);

  CString   GetSVal(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal);
  void      SetSVal(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szValue);
  UINT      GetIVal(LPCTSTR szSect, LPCTSTR szKey, UINT iDefVal);
  void      SetIVal(LPCTSTR szSect, LPCTSTR szKey, UINT uValue);

  BOOL      GetCityUnderline();
  void      SetCityUnderline(BOOL fUnderline);

  CString   GetCOUNTRY();
  void      SetCOUNTRY(LPCTSTR szCountry);
  CString   GetREGION();
  void      SetREGION(LPCTSTR szRegion);
  CString   GetCITY();
  CString   GetCITY_();
  void      SetCITY(LPCTSTR szCity);
  CString   GetDISTRICT();
  void      SetDISTRICT(LPCTSTR szDistrict);

  CString   GetRAGS();
  void      SetRAGS(LPCTSTR szRags);
  CString   GetOKPO();
  void      SetOKPO(LPCTSTR szOKPO);

  CString   GetBoss();
  void      SetBoss(LPCTSTR szBoss);

  CString   GetPosada();
  void      SetPosada(LPCTSTR szPosada);

  CString   GetPIBPO();
  void      SetPIBPO(LPCTSTR szPIBPO);

  CString   GetParent();
  void      SetParent(LPCTSTR szParent);

  BOOL      IsChildRags(const CString& sRags);
  BOOL      IsVyconcom(const CString& sRags);
  CString   GetVyconcomParent(const CString& sRags);

  CString   GetDefStamp();
  UINT      GetUseStamp1();
  CString   GetStamp1();
  void      SetUseStamp1(UINT fUse);
  void      SetStamp1(LPCTSTR szStamp);
  UINT      GetUseStamp2();
  void      SetUseStamp2(UINT fUse);
  CString   GetStamp2();
  void      SetStamp2(LPCTSTR szStamp);


  CString   GetByROVD();
  void      SetByROVD(LPCTSTR szBy);
  CString   GetToROVD();
  void      SetToROVD(LPCTSTR szTo);

  CString   GetByMil();
  void      SetByMil(LPCTSTR szBy);

  CString   GetToMil();
  void      SetToMil(LPCTSTR szTo);

  CString   GetToSocProt();
  void      SetToSocProt(LPCTSTR szTo);

  CString   GetByCourt();
  void      SetByCourt(LPCTSTR szBy);

  CString   GetToTax();
  void      SetToTax(LPCTSTR szTo);

  CString   GetNoCert();

  CString   GetMDN();

  UINT      GetMakeTVKXLS();
  void      SetMakeTVKXLS(UINT uCheck);

  UINT      GetTVKDash();
  void      SetTVKDash(UINT uCheck);

  CString   GetBIRTH_BP_COUNTRY();
  void      SetBIRTH_BP_COUNTRY(LPCTSTR szCountry);
  UINT      GetBIRTH_BP_COUNTRY_CHECK();
  void      SetBIRTH_BP_COUNTRY_CHECK(UINT uCheck);
  CString   GetBIRTH_BP_REGION();
  void      SetBIRTH_BP_REGION(LPCTSTR szRegion);
  UINT      GetBIRTH_BP_REGION_CHECK();
  void      SetBIRTH_BP_REGION_CHECK(UINT uCheck);

  CString   GetBIRTH_DefNotice();
  void      SetBIRTH_DefNotice(LPCTSTR szDefNotice);

  CString   GetBIRTH_DefNotice2();
  void      SetBIRTH_DefNotice2(LPCTSTR szDefNotice);

  CString   GetBIRTH_BP_DISTRICT();
  void      SetBIRTH_BP_DISTRICT(LPCTSTR szDistrict);
  UINT      GetBIRTH_BP_DISTRICT_CHECK();
  void      SetBIRTH_BP_DISTRICT_CHECK(UINT uCheck);
  CString   GetBIRTH_BP_CITY();
  void      SetBIRTH_BP_CITY(LPCTSTR szCity);
  UINT      GetBIRTH_BP_CITY_CHECK();
  void      SetBIRTH_BP_CITY_CHECK(UINT uCheck);

  CString   GetBIRTH_Seria();
  void      SetBIRTH_Seria(LPCTSTR szSeria);
  int       GetBIRTH_NActPages();
  void      SetBIRTH_NActPages(int nPages);

  CString   GetMARRIAGE_Seria();
  void      SetMARRIAGE_Seria(LPCTSTR szSeria);

  CString   GetMARRIAGE_DefNotice();
  void      SetMARRIAGE_DefNotice(LPCTSTR szDefNotice);

  
  int       GetMARRIAGE_NActPages();
  void      SetMARRIAGE_NActPages(int nPages);

  CString   GetDIVORCE_Seria();
  void      SetDIVORCE_Seria(LPCTSTR szSeria);
  int       GetDIVORCE_NActPages();
  void      SetDIVORCE_NActPages(int nPages);

  CString   GetCHANGE_Seria();
  void      SetCHANGE_Seria(LPCTSTR szSeria);
  int       GetCHANGE_NActPages();
  void      SetCHANGE_NActPages(int nPages);

  CString   GetDEATH_Seria();
  void      SetDEATH_Seria(LPCTSTR szSeria);
  int       GetDEATH_NActPages();
  void      SetDEATH_NActPages(int nPages);
  CString   GetDEATH_DefNotice();
  void      SetDEATH_DefNotice(LPCTSTR szDefNotice);

  CString   GetBIRTH_CNum();
  CString   GetMARRIAGE_CNum();
  CString   GetDIVORCE_CNum();
  CString   GetCHANGE_CNum();
  CString   GetDEATH_CNum();

  CString   GetRenew();

  CString   GetDIVORCE_NoChildren();
  void      SetDIVORCE_NoChildren(LPCTSTR szNoChildren);

  CString   GetDIVORCE_SingleChild();
  void      SetDIVORCE_SingleChild(LPCTSTR szSingleChild);

/************************************** : by VK at 22.07.2005 21:03:10 **\
  void      FillChildList(CListBox& lb);
\************************************** : by VK at 22.07.2005 21:03:13 **/
  void      FillChildList(CTreeCtrl& tc);

  void      FillChildList(CStringArray& sa);
  CString   GetRPChild(long lID, LPCTSTR szSect);
  void      SetRPChild(long lID, LPCTSTR szSect, LPCTSTR szRP);

  CString   GetOverByDistrict(LPCTSTR szDistr);
  bool      FillForLists(CComboBox& cb);


  CString   GetOwner(LPCTSTR szSect);
  void      SetOwner(LPCTSTR szSect, LPCTSTR szOwner);

  void      FillBanks();

  void      SetNextCNum(LPCSTR szSect, CWnd* pWnd);
  void      SetBIRTH_CNum(CWnd* pWnd);
  void      SetMARRIAGE_CNum(CWnd* pWnd);
  void      SetDIVORCE_CNum(CWnd* pWnd);
  void      SetCHANGE_CNum(CWnd* pWnd);
  void      SetDEATH_CNum(CWnd* pWnd);

  CString   GetNextNum(LPCSTR szSection, int num);
  void      SetNum(LPCSTR szSection, int num, LPCSTR szValue);

  CString   GetNext41Num();
  void      Set41Num(LPCTSTR szNum);

  CString   GetNext42Num();
  void      Set42Num(LPCTSTR szNum);

  CString   GetNext43Num();
  void      Set43Num(LPCTSTR szNum);

  UINT      GetRagsID();
  void      SetRagsID(UINT id);

#ifndef FREE_LICENCE
  CString   GetLKey();
  void      SetLKey(const CString& szLKey);
  LK_VALUE  IsValidDigitLKey(const CString& szLKey);
  LK_VALUE  IsValidLKey(LIC_KEY* pLC=NULL, CString* pszLKey=NULL);
  CString   GetDateCountStr();

  CString   GetMaxSysDate();
  CString   GetLastDate(LPCTSTR szKey, BOOL fShort = true);
  void      SetLastDate(const CString& szLDate, LPCTSTR szKey);
  void      SetDateCount(const COleDateTime& odt);
  int       CalcDates();
#endif // FREE_LICENCE

  UINT      GetPrintCitizen(LPCSTR szSection);
  UINT      GetPrintCitizenBIRTH();
  UINT      GetPrintCitizenMARRIAGE();
  UINT      GetPrintCitizenDIVORCE();
  UINT      GetPrintCitizenCHANGE();
  UINT      GetPrintCitizenDEATH();

  void      SetPrintCitizen(LPCSTR szSection, UINT nValue);
  void      SetPrintCitizenBIRTH(UINT nValue);
  void      SetPrintCitizenMARRIAGE(UINT nValue);
  void      SetPrintCitizenDIVORCE(UINT nValue);
  void      SetPrintCitizenCHANGE(UINT nValue);
  void      SetPrintCitizenDEATH(UINT nValue);

};

extern LPCTSTR   g_szSvNeVidano;
extern CIniCache theIniCache;

#ifndef FREE_LICENCE
extern CString   g_szLastLDate;
extern long      g_nDaysRemaining;
#endif

#endif //DEFAULTS_H_INCLUDED