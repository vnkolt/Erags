#if !defined(GEOGRAPHY_H_INCLUDED)
#define GEOGRAPHY_H_INCLUDED


#define GEO_MENU_TYPE_NONE  0
#define GEO_MENU_TYPE_TREE  1
#define GEO_MENU_TYPE_LIST  2

#define GRF_UPDATED   0x0001

class CGeoRecord : public CObject {
public:
  CGeoRecord();
  ~CGeoRecord();
// data members:
public:
  CPtrArray   m_array;
  CGeoRecord* m_pParent;
  long        m_ID;
  long        m_ParentID;
  CString     m_Name;
  CString     m_AltName;
  CString     m_Type;
  CString     m_ZipCode;
  CString     m_PhoneCode;
  CString     m_Directory;
  //bool        m_fLoaded;
  DWORD       m_dwFlags;
  HTREEITEM   m_hItem;

  int         GetCount() { return m_array.GetSize(); }
  bool        IsCountry() const;
  bool        IsRegion() const;
  bool        IsCity() const;
  bool        IsMainCity() const;
  bool        IsVillage(CString* pDest=NULL) const;
  bool        IsDistrict() const;
  int         GetGeoTypeWeight();
  CString     GetTypeName();
  CString     GetShortTypeName();

  CString     GetName();
  CString     GetAltName();
  CString     GetNameWithAltName();
  bool        HasChildren();
};

CString GetGeoPath(CGeoRecord* pRecord);

class CGeoCache : public CObject {
public:
  CGeoCache();
  ~CGeoCache();
// data members:
public:
  CPtrArray   m_array;
// operations:
  void Clear();
  void Sort(CPtrArray* pArray);
  BOOL Load(CDaoDatabase& db, CProgressCtrl* pProgressCtrl, CStatic* pStatic);

  int         GetIndex(CGeoRecord* pRecord, CPtrArray*& pArray);
  CGeoRecord* GetFirstRecord();
  CGeoRecord* GetPrevRecord(CGeoRecord* pRecord);
  CGeoRecord* GetNextRecord(CGeoRecord* pRecord);
  CGeoRecord* GetLastRecord(CPtrArray& array);


  CGeoRecord* GetCountry(CPtrArray* pArray, const CString& s);
  CGeoRecord* GetCountry(const CString& s);
  CGeoRecord* GetRegion(CPtrArray* pArray, const CString& s);
  #ifdef _GEO
  CGeoRecord* GetCity(CPtrArray* pArray, const CString& s, char typeLetter=0);
  #else
  CGeoRecord* GetCity(CPtrArray* pArray, const CString& s, CGeoRecord** ppCity);
  CGeoRecord* GetCityInCity(CPtrArray* pArray, const CString& s);
  #endif
  CGeoRecord* GetDistrict(CPtrArray* pArray, const CString& s, CGeoRecord** ppCity);

  CString FindFullCountry(const CString& sCountry);
  void RemoveRecordFromArray(CGeoRecord* pRecord);
};

CString GetCity(LPCTSTR szCityWithType);
BOOL PASCAL IsDistrictInCity(LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szDistrict, LPCTSTR szCity);

extern CGeoCache theGeoCache;

#endif // GEOGRAPHY_H_INCLUDED