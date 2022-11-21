//
// Registry.h
//
#if !defined(__REGISTRY_H_ICNLUDED)
#define __REGISTRY_H_ICNLUDED

class CRegistry {
public:
    CRegistry(LPCTSTR szProfileName);
    HKEY GetAppRegistryKey();
    HKEY GetSectionKey(LPCTSTR lpszSection);

    UINT    GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault);
    CString GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry,	LPCTSTR lpszDefault);
    BOOL    GetProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry, BYTE** ppData, UINT* pBytes);
    BOOL    WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry,	int nValue);
    BOOL    WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue);
    BOOL    WriteProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPBYTE pData, UINT nBytes);
public:
    HKEY    m_hRootKey;
protected:
    LPCTSTR m_pszRegistryKey;
    LPCTSTR m_pszProfileName;

};

#endif// __REGISTRY_H_ICNLUDED