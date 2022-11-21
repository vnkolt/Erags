#if !defined(INICACHE_H_INCLUDED)
#define INICACHE_H_INCLUDED


class CIniCache {
public:
  CIniCache();
  ~CIniCache();
private:
  CDaoRecordset*      m_prs;
  CMapStringToString  m_keys;

public:
  UINT  HashKey(LPCTSTR szKey);

  BOOL  Load(CDaoDatabase& db);
  BOOL  IsOpen();
  BOOL  Open(CDaoDatabase& db);
  void  Close();


  CString   GetPrivateProfileString(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal, BOOL fWrite=FALSE);
  CString   GetPrivateProfileString(LPCTSTR szSect, LPCTSTR szKey);

  CString   GetSVal(LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal);
  CString   GetRAGS();

};

#endif // INICACHE_H_INCLUDED
