#if !defined(INICACHE_H_INCLUDED)
#define INICACHE_H_INCLUDED

class CAbbrCache {
public:
  CAbbrCache();
  virtual ~CAbbrCache();
public:
  CMapStringToString m_map;
// operations
  void    Load(LPCTSTR szFileName);
  BOOL    Lookup(LPCTSTR key, CString& rValue);

};

class CFormsCache {
public:
  CFormsCache();
  virtual ~CFormsCache();
// data members:
private:
  CString m_sCommonSect,
          m_sBirthSect,
          m_sMarriageSect,
          m_sDivorceSect,
          m_sChangeSect,
          m_sDeathSect,
          m_sIniFile;
// operations:
public:
  const CString&  GetIniFile()  { return m_sIniFile; }

  void      Load(LPCTSTR szFileName);
  CString   GetSVal(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal);
  void      SetSVal(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szValue);
  UINT      GetIVal(LPCTSTR szSect, LPCTSTR szKey, UINT iDefVal);
  void      SetIVal(LPCTSTR szSect, LPCTSTR szKey, UINT uValue);

  CString   GetCOUNTRY();
  void      SetCOUNTRY(LPCTSTR szCountry);
  CString   GetREGION();
  void      SetREGION(LPCTSTR szRegion);
  CString   GetCITY();
  void      SetCITY(LPCTSTR szCity);
  CString   GetDISTRICT();
  void      SetDISTRICT(LPCTSTR szDistrict);

  CString   GetRAGS();
  void      SetRAGS(LPCTSTR szRags);
  CString   GetBoss();
  void      SetBoss(LPCTSTR szBoss);

  CString   GetParent();
  void      SetParent(LPCTSTR szParent);

  BOOL      IsChildRags(const CString& sRags);

  CString   GetByROVD();
  void      SetByROVD(LPCTSTR szBy);
  CString   GetToROVD();
  void      SetToROVD(LPCTSTR szTo);

  CString   GetByMil();
  void      SetByMil(LPCTSTR szBy);

  CString   GetToMil();
  void      SetToMil(LPCTSTR szTo);

  CString   GetByCourt();
  void      SetByCourt(LPCTSTR szBy);

  CString   GetToTax();
  void      SetToTax(LPCTSTR szTo);

  CString   GetNoCert();

  CString   GetMDN();

  CString   GetBIRTH_BP_COUNTRY();
  void      SetBIRTH_BP_COUNTRY(LPCTSTR szCountry);
  UINT      GetBIRTH_BP_COUNTRY_CHECK();
  void      SetBIRTH_BP_COUNTRY_CHECK(UINT uCheck);
  CString   GetBIRTH_BP_REGION();
  void      SetBIRTH_BP_REGION(LPCTSTR szRegion);
  UINT      GetBIRTH_BP_REGION_CHECK();
  void      SetBIRTH_BP_REGION_CHECK(UINT uCheck);

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

  CString   GetMARRIAGE_Seria();
  void      SetMARRIAGE_Seria(LPCTSTR szSeria);

  CString   GetDIVORCE_Seria();
  void      SetDIVORCE_Seria(LPCTSTR szSeria);

  CString   GetCHANGE_Seria();
  void      SetCHANGE_Seria(LPCTSTR szSeria);

  CString   GetDEATH_Seria();
  void      SetDEATH_Seria(LPCTSTR szSeria);

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
};


extern LPCTSTR g_szSvNeVidano;

extern CAbbrCache   theAbbrCache;
extern CFormsCache  theIniCache;

#endif // INICACHE_H_INCLUDED