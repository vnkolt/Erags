#if !defined(CACHES_H_INCLUDED)
#define CACHES_H_INCLUDED

class CNameCache : public CMapStringToString {
public:
  CNameCache();
  ~CNameCache();
// Operations:
public:
  bool Load(LPCTSTR szTableName, LPCTSTR szFieldName, BOOL fSex);
  void FillCombo(CComboBox& cb, const CString& sFieldValue, bool reFill);
};

class CCitizenshipCache : public CMapStringToString {
public:
  CCitizenshipCache();
  ~CCitizenshipCache();
// Operations:
public:
  bool Load();
  void FillCombo(CComboBox& cb, const CString& sKey);
  CString GetValue(const CString& sKey);
};

class CStringCache {
public:
  CStringCache();
  ~CStringCache();
  void Clear();
// Attributes:
  CStringArray  m_array;
// Operations:
public:
  bool Load(LPCSTR szSQL);
  int  Add(CComboBox& cb, const CString& sValue);
  void FillCombo(CComboBox& cb, const CString& sValue);
};

class CHospitalCache {
public:
  CHospitalCache();
  ~CHospitalCache();
  void Clear();
// Attributes:
public:
  CMapStringToString m_map;
// Operations:
public:
  bool  Load();
  void  FillCombo(CComboBox& cbMedCertPseudo, CComboBox& cbMedCertBy, const CString& sFieldValue);
  BOOL  Lookup(const CString& sKey, CString& sValue); 
};

class CSortStringArray : public CStringArray {
public:
   void Sort(BOOL bAscending);
private:
   int	CompareAsc(int i, int j);
   int	CompareDesc(int i, int j);
	 void	Swap(int i, int j);
};

extern CNameCache theMNames;
extern CNameCache theWNames;
extern CNameCache theMPatronymics;
extern CNameCache theWPatronymics;
extern CCitizenshipCache theCitizenships;
extern CHospitalCache theHospitals;
extern CStringCache theMIAs;
extern CStringCache theStreets;
extern CSortStringArray theBanks;

#endif // CACHES_H_INCLUDED
