//
// Registry.cpp
//
#include "stdafx.h"
#include "Registry.h"

CRegistry theRegistry;

CRegistry::CRegistry(){
  m_pszRegistryKey = _T("Vladimir Koltsov");
  m_pszProfileName = _T("Erags");
  m_hRootKey = HKEY_CURRENT_USER;
}

HKEY CRegistry::GetAppRegistryKey() {
	ASSERT(m_pszRegistryKey != NULL);
	ASSERT(m_pszProfileName != NULL);

	HKEY hAppKey = NULL;
	HKEY hSoftKey = NULL;
	HKEY hCompanyKey = NULL;
	if (RegOpenKeyEx(m_hRootKey, _T("software"), 0, KEY_WRITE|KEY_READ, &hSoftKey) == ERROR_SUCCESS) {
		DWORD dw;
		if (RegCreateKeyEx(hSoftKey, m_pszRegistryKey, 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL, &hCompanyKey, &dw) == ERROR_SUCCESS) {
			RegCreateKeyEx(hCompanyKey, m_pszProfileName, 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL, &hAppKey, &dw);
		}
	}
	if (hSoftKey != NULL)
		RegCloseKey(hSoftKey);
	if (hCompanyKey != NULL)
		RegCloseKey(hCompanyKey);

	return hAppKey;
}

HKEY CRegistry::GetSectionKey(LPCTSTR lpszSection) {
	ASSERT(lpszSection != NULL);

	HKEY hSectionKey = NULL;
	HKEY hAppKey = GetAppRegistryKey();
	if (hAppKey == NULL)
		return NULL;

	DWORD dw;
	RegCreateKeyEx(hAppKey, lpszSection, 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL, &hSectionKey, &dw);
	RegCloseKey(hAppKey);
	return hSectionKey;
}

UINT CRegistry::GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault) {
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
  ASSERT(m_pszRegistryKey != NULL);

	HKEY hSecKey = GetSectionKey(lpszSection);
	if (hSecKey == NULL)
		return nDefault;
	DWORD dwValue;
	DWORD dwType;
	DWORD dwCount = sizeof(DWORD);
	LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
                            		(LPBYTE)&dwValue, &dwCount);
	RegCloseKey(hSecKey);
	if (lResult == ERROR_SUCCESS)	{
		ASSERT(dwType == REG_DWORD);
		ASSERT(dwCount == sizeof(dwValue));
		return (UINT)dwValue;
	}
	return nDefault;
}

CString CRegistry::GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry,	LPCTSTR lpszDefault) {
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
  ASSERT(m_pszRegistryKey != NULL);

	HKEY hSecKey = GetSectionKey(lpszSection);
	if (hSecKey == NULL)
		return lpszDefault;
	CString strValue;
	DWORD dwType, dwCount;
	LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,	NULL, &dwCount);
	if (lResult == ERROR_SUCCESS) {
		ASSERT(dwType == REG_SZ);
		lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
				                      (LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
		strValue.ReleaseBuffer();
	}
	RegCloseKey(hSecKey);
	if (lResult == ERROR_SUCCESS)	{
		ASSERT(dwType == REG_SZ);
		return strValue;
	}
	return lpszDefault;
}

BOOL CRegistry::GetProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry, BYTE** ppData, UINT* pBytes) {
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
  ASSERT(m_pszRegistryKey != NULL);
	ASSERT(ppData != NULL);
	ASSERT(pBytes != NULL);
	*ppData = NULL;
	*pBytes = 0;

	HKEY hSecKey = GetSectionKey(lpszSection);
	if (hSecKey == NULL)
		return FALSE;

	DWORD dwType, dwCount;
	LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType, NULL, &dwCount);
	*pBytes = dwCount;
	if (lResult == ERROR_SUCCESS)		{
		ASSERT(dwType == REG_BINARY);
		*ppData = new BYTE[*pBytes];
		lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType, *ppData, &dwCount);
	}
	RegCloseKey(hSecKey);
	if (lResult == ERROR_SUCCESS)	{
		ASSERT(dwType == REG_BINARY);
		return TRUE;
	}
	else {
		delete [] *ppData;
		*ppData = NULL;
	}
	return FALSE;
}

BOOL CRegistry::WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry,	int nValue) {
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
  ASSERT(m_pszRegistryKey != NULL);

  HKEY hSecKey = GetSectionKey(lpszSection);
	if (hSecKey == NULL)
	  return FALSE;
  LONG lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_DWORD, (LPBYTE)&nValue, sizeof(nValue));
  RegCloseKey(hSecKey);
  return lResult == ERROR_SUCCESS;
}

BOOL CRegistry::WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue){
	ASSERT(lpszSection != NULL);
  ASSERT(m_pszRegistryKey != NULL);

	LONG lResult;
	if (lpszEntry == NULL) { //delete whole section
		HKEY hAppKey = GetAppRegistryKey();
		if (hAppKey == NULL)
			return FALSE;
		lResult = ::RegDeleteKey(hAppKey, lpszSection);
		RegCloseKey(hAppKey);
	}
	else if (lpszValue == NULL) {
		HKEY hSecKey = GetSectionKey(lpszSection);
		if (hSecKey == NULL)
			return FALSE;
		// necessary to cast away const below
		lResult = ::RegDeleteValue(hSecKey, (LPTSTR)lpszEntry);
		RegCloseKey(hSecKey);
	}
	else {
		HKEY hSecKey = GetSectionKey(lpszSection);
		if (hSecKey == NULL)
			return FALSE;
		lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_SZ,
				(LPBYTE)lpszValue, (lstrlen(lpszValue)+1)*sizeof(TCHAR));
		RegCloseKey(hSecKey);
	}
	return lResult == ERROR_SUCCESS;
}

BOOL CRegistry::WriteProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPBYTE pData, UINT nBytes) {
	ASSERT(lpszSection != NULL);
  ASSERT(m_pszRegistryKey != NULL);

	LONG lResult;
	HKEY hSecKey = GetSectionKey(lpszSection);
	if (hSecKey == NULL)
		return FALSE;
	lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_BINARY,	pData, nBytes);
	RegCloseKey(hSecKey);
	return lResult == ERROR_SUCCESS;
}
