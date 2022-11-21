#if !defined(OLDCACHES_H_INLCUDED)
#define OLDCACHES_H_INLCUDED

//
// OldCaches.h
//

class CSexRecord : public CObject {
public:
  CString m_Name;
  bool    m_fSex;
  CSexRecord(LPCTSTR szName, bool fSex) {
    m_Name = szName;
    m_fSex = fSex;
  }
};
typedef CMap<long, long&, CSexRecord*, CSexRecord*> SEXMap;
class CSexMap {
public:
  CSexMap();
  ~CSexMap();
private:
  SEXMap  m_map;
public:
  void        Clear();
  CSexRecord* Lookup(long ID);
  void        Add(long ID, CSexRecord* pRecord);
  BOOL        Fill(CDaoDatabase& db, LPCTSTR szTableName, LPCTSTR szKeyField, LPCTSTR szValueField);
};


class C2FieldRecord : public CObject {
public:
  CString m_Value1;
  CString m_Value2;
  C2FieldRecord(LPCTSTR szValue1, LPCTSTR szValue2) {
    m_Value1 = szValue1;
    m_Value2 = szValue2;
  }
};
typedef CMap<long, long&, C2FieldRecord*, C2FieldRecord*> RECORDMap;
class CRecordMap {
public:
  CRecordMap();
  ~CRecordMap();
private:
  RECORDMap   m_map;
public:
  void           Clear();
  C2FieldRecord* Lookup(long ID);
  void           Add(long ID, C2FieldRecord* pRecord);
  BOOL           Fill(CDaoDatabase& db, LPCTSTR szTableName, LPCTSTR szKeyField, LPCTSTR szField1, LPCTSTR szField2);
};


typedef CMap<long, long&, CString, CString> STRINGMap;
class CStringMap {
public:
  CStringMap();
  ~CStringMap();
private:
  STRINGMap m_map;
public:
  void      Clear();
  CString   Lookup(long ID);
  void      Add(long ID, const CString& s);
  BOOL      Fill(CDaoDatabase& db, LPCTSTR szTableName, LPCTSTR szKeyField, LPCTSTR szValueField);
};

extern CStringMap  theNames;       // ������� � ������� �����
extern CStringMap  thePatronymics; // ������� � ������� ��������
extern CStringMap  theBanks;       // �����
extern CRecordMap  theCountries;   // ������ � �����������
extern CStringMap  theRegions;     // �������
extern CRecordMap  theCities;      // �������� �� � ��� ��
extern CStringMap  theDistricts;   // ������
extern CStringMap  theStreets;     // �����
extern CRecordMap  theNations;     // �������������� (�������� ��� �. � �. ����)
extern CStringMap  theRAGSes;      // �����
extern CStringMap  theROVDs;       // ����
extern CStringMap  theMHospitals;  // ��������� ����
extern CStringMap  theHospitals;   // ��������


#endif // OLDCACHES_H_INLCUDED