#ifndef RDF32_H_INCLUDED
#define RDF32_H_INCLUDED

//
// RDF32.h
//
#pragma pack(push, pack_save, 1)

#define RDF32_SIGNATURE (DWORD)('RDFV') + (DWORD)('3.20')

class RDFSection {
public:
  WORD  cbSize;
  UINT  HashKey;
  BYTE  SectNum;
  BYTE  SectType;
  DWORD BodyOffset;
  WORD  OriginSize;
  WORD  PacketSize;
  char  szSectName[256];

  RDFSection()  {
    memset(this, 0, sizeof(RDFSection));
  }
  int   GetSize() {
    return sizeof(RDFSection) - sizeof(szSectName) + strlen(szSectName)+1;
  }
  BOOL  IsValid() {
    return (cbSize && HashKey && SectNum && SectType && BodyOffset && PacketSize && OriginSize && szSectName[0]);
  }
};
struct RDFTail {
  DWORD     Signature;  // RDF32_SIGNATURE
  time_t    MakeTime;
  UINT      CheckSum;
  WORD      nSections;
  WORD      SectBufOriginSize;
  WORD      SectPacketSize;
};

struct RDFItem {
  CString m_szKey;
  CString m_szValue;
};

struct RDFGeoCheck {
  CString szRegion;
  CString szCity;
  CString szDistrict;
  CString szRagsKey;
  TCHAR   RagsType;
};

typedef CArray<RDFItem, RDFItem> CRDFItems;

class CRDF32Reader {
public:
  CRDF32Reader();
  ~CRDF32Reader();
private:
  CByteArray  m_RDF;
  CPtrArray   m_SectInfo;
  RDFTail*    m_pRDFTail;
// Operations:
private:
  void  Clear();
public:
  int               GetNumSections()  { return m_SectInfo.GetSize();             }
  const RDFSection* GetSection(int i) { return (RDFSection*)m_SectInfo.GetAt(i); }
  int               GetSection(LPCTSTR szSect);
  BOOL              Read(LPCTSTR szRDFFile);
  void              GetSectionBody(int i, CRDFItems& Items);
  int               FindItem(CRDFItems& Items, const CString& szRegion);
  int               FindItem(CRDFItems& Items, const CString& szCity, const CString& szDistrict);
  void              FillItem(RDFItem& Item, CString& szCity, CString& szDistrict, CString& szRagsKeys, CString& szCityKeys, CString& szDistrictKeys);
};

UINT MakeRDFHashKey(LPCTSTR key);
#ifdef RDF_WRITER
void Ini2RDF(LPCTSTR szIniFile, LPCTSTR szPackFile);
#endif


#pragma pack(pop, pack_save)

#endif // RDF32_H_INCLUDED