//
// LastFDate.cpp
//
#include "stdafx.h"
#include <ShlObj.h>

#include "LastFDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ERA_VERSION 50602

/************************************** : by VK 03.06.2005 at 13:12:08 **\
  That's all RULES.

  1. To get MAXDATE: MAXDATE = MAX(SYSDATE, LASTFDATE)

  2. MAXDATE >= LIMITDATE and LastDateEntered >= LIMITDATE -> That's all.

  3. If LastDateEntered >= LIMITDATE and LastDateEnteredCnt > 3 -> That's all.

  4. Write "That's all" to registry, Helpers.mdb, Erags.rdf (SLOT)

  5. Zip .er3 files with password.

\************************************** : by VK 03.06.2005 at 13:12:10 **/

// HKEY_USERS\.DEFAULT\Control Panel\PowerCfg\GlobalPowerPolicy\Policies - real value
LPCTSTR szRegKey   = _T(".DEFAULT\\Control Panel\\PowerCfg\\GlobalPowerPolicy");
//LPCTSTR szRegValue = _T("Policies");
LPCTSTR szRegValue = _T("CurrentPolicyData");
// HKEY_USERS\.DEFAULT\Control Panel\PowerCfg\GlobalPowerPolicy\CurrentPolicyData - my value

time_t GetSysDirCreationTime() {
  time_t t = 0;
  CString szSysDir;
  GetSystemDirectory(szSysDir.GetBuffer(MAX_PATH), MAX_PATH);
  szSysDir.ReleaseBuffer();
  CFileFind finder;  
  BOOL bResult = finder.FindFile(szSysDir);
  while ( bResult ) {
    bResult = finder.FindNextFile();
    CTime ft;
    finder.GetCreationTime(ft);
    t = ft.GetTime();
  }
  return t;
}
/************************************** : by VK at 01.10.2005 4:53:01 **\
SecurityData* ReadSecurityFromReg() {
  LONG   lResult;
  HKEY   hKey = NULL;
  DWORD  dwType = NULL;
  DWORD  cbData = NULL;
  BYTE*  pData  = NULL;
  lResult = RegOpenKeyEx(HKEY_USERS, szRegKey, 0, KEY_QUERY_VALUE, &hKey);
  //lResult = RegOpenKey(HKEY_USERS, szRegKey, &hKey);
  if (lResult != ERROR_SUCCESS) {
    return NULL;
  }
  lResult = RegQueryValueEx(hKey, szRegValue, NULL, &dwType, NULL, &cbData);
  if (ERROR_SUCCESS==lResult && REG_BINARY == dwType) {
    BYTE* pData = new BYTE[cbData];
    lResult = RegQueryValueEx(hKey, szRegValue, NULL, &dwType, pData, &cbData);
  }
  RegCloseKey(hKey);
  return (SecurityData*)pData;
}
SecurityData* BuildSecurityStruct(SecurityData* pSecurityData) {
  memset(pSecurityData, 0, sizeof(SecurityData) );
  pSecurityData->EraVersion = ERA_VERSION;
  pSecurityData->cbSize = sizeof(SecurityData);
  pSecurityData->OsVersion = g_Shell;
  pSecurityData->SysDirCreationTime = GetSysDirCreationTime();
  for( int i(0); i < sizeof(SecurityData); i++ ) {
    pSecurityData->CheckSum += ((char*)pSecurityData)[i];
  }
  return pSecurityData;
}
BOOL WriteSecurityToReg(SecurityData* pData) {
  LONG   lResult;
  HKEY   hKey = NULL;
  BOOL   bRet = FALSE;
  lResult = RegOpenKeyEx(HKEY_USERS, szRegKey, 0, KEY_WRITE, &hKey);
  if (lResult != ERROR_SUCCESS) {
    return bRet;
  }
  lResult = RegSetValueEx(hKey, szRegValue, 0, REG_BINARY, (BYTE*)pData, sizeof(SecurityData));
  if (ERROR_SUCCESS == lResult) {
    bRet++;
  }
  RegCloseKey(hKey);

  return bRet;
}
\************************************** : by VK at 01.10.2005 4:53:06 **/

CString GetSpecialFolder(int nFolderID) {
   // Allocate a pointer to an Item ID list
   LPITEMIDLIST pidl;

   // Get a pointer to an item ID list that
   // represents the path of a special folder
   HRESULT hr = SHGetSpecialFolderLocation(NULL, nFolderID, &pidl);

   // Convert the item ID list's binary
   // representation into a file system path
   char szPath[_MAX_PATH];
   BOOL f = SHGetPathFromIDList(pidl, szPath);

   // Allocate a pointer to an IMalloc interface
   LPMALLOC pMalloc;

   // Get the address of our task allocator's IMalloc interface
   hr = SHGetMalloc(&pMalloc);

   // Free the item ID list allocated by SHGetSpecialFolderLocation
   pMalloc->Free(pidl);

   // Free our task allocator
   pMalloc->Release();

   // Work with the special folder's path (contained in szPath)
   return CString(szPath);
}


CTime SearchLatestFile(CTime MinTime, CString& szSearchFolder, CString& szFile) {
  CTime t = MinTime;
  CString szMask;
  szMask.Format(_T("%s\\*.*"), szSearchFolder);
  CFileFind finder;
  BOOL bResult = finder.FindFile(szMask);
  while ( bResult ) {
    bResult = finder.FindNextFile();
    CTime ft;
    finder.GetCreationTime(ft);
    if ( t < ft ) {
      t = ft;
      szFile = finder.GetFilePath();
    }
    finder.GetLastWriteTime(ft);
    if ( t < ft ) {
      t = ft;
      szFile = finder.GetFilePath();
    }
/************************************** : by VK at 01.10.2005 5:32:51 **\
    finder.GetLastAccessTime(ft);
    if ( t < ft ) {
      t = ft;
      szFile = finder.GetFilePath();
    }
\************************************** : by VK at 01.10.2005 5:32:55 **/
  }
  return t;
}

COleDateTime FindLastFileTime() {
  CString szFile;
  CTime t = CTime::GetCurrentTime();

  CString szMyDocumentsFolder = GetSpecialFolder(CSIDL_PERSONAL);
  t = SearchLatestFile(t, szMyDocumentsFolder, szFile);

  CString szDir;
  GetSystemDirectory(szDir.GetBuffer(MAX_PATH), MAX_PATH);
  szDir.ReleaseBuffer();

  t = SearchLatestFile(t, szDir, szFile);

  return COleDateTime( t.GetYear(), t.GetMonth(), t.GetDay(),
                       t.GetHour(), t.GetMinute(), t.GetSecond() );
}