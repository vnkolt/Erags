//
// Version.cpp
//
#include "stdafx.h"
#include <Shlwapi.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CModuleVersion : public VS_FIXEDFILEINFO 
{
protected:
   BYTE* m_pVersionInfo;   // all version info

   struct TRANSLATION 
	 {
      WORD langID;         // language ID
      WORD charset;        // character set (code page)
   } m_translation;

public:
   CModuleVersion()
		: m_pVersionInfo(NULL) {}
   virtual ~CModuleVersion();

   BOOL    GetFileVersionInfo(LPCTSTR modulename);
   CString GetValue(LPCTSTR lpKeyName);
   CString GetCompanyName();
   CString GetInternalName();
   CString GetOriginalFilename();
};

CModuleVersion::~CModuleVersion()
{
	 if (m_pVersionInfo)
     delete [] m_pVersionInfo;
}

BOOL CModuleVersion::GetFileVersionInfo(LPCTSTR modulename)
{
	 if (m_pVersionInfo) {
     delete [] m_pVersionInfo;
     m_pVersionInfo = NULL;
	}

   m_translation.charset = 1252;    // default = ANSI code page
   memset((VS_FIXEDFILEINFO*)this, 0, sizeof(VS_FIXEDFILEINFO));

   // get module handle
   TCHAR filename[_MAX_PATH];
	 lstrcpy(filename,modulename);
	 if (!::PathFileExists(filename))
		 return FALSE;

   // read file version info
   DWORD dwDummyHandle; // will always be set to zero
   DWORD len = GetFileVersionInfoSize(filename, &dwDummyHandle);
   if (len <= 0)
      return FALSE;

   m_pVersionInfo = new BYTE[len]; // allocate version info
   if (!::GetFileVersionInfo(filename, 0, len, m_pVersionInfo))
      return FALSE;

   LPVOID lpvi;
   UINT iLen;
   if (!VerQueryValue(m_pVersionInfo, _T("\\"), &lpvi, &iLen))
      return FALSE;

   // copy fixed info to myself, which am derived from VS_FIXEDFILEINFO
   *(VS_FIXEDFILEINFO*)this = *(VS_FIXEDFILEINFO*)lpvi;

   // Get translation info
   if (VerQueryValue(m_pVersionInfo,
      "\\VarFileInfo\\Translation", &lpvi, &iLen) && iLen >= 4) {
      m_translation = *(TRANSLATION*)lpvi;
      TRACE("code page = %d\n", m_translation.charset);
   }

   return dwSignature == VS_FFI_SIGNATURE;
}

CString CModuleVersion::GetValue(LPCTSTR lpKeyName)
{
   CString sVal;
   if (m_pVersionInfo) {

      // To get a string value must pass query in the form
      //
      //    "\StringFileInfo\<langID><codepage>\keyname"
      //
      // where <langID><codepage> is the languageID concatenated with the
      // code page, in hex. Wow.
      //
      CString query;
      query.Format(_T("\\StringFileInfo\\%04x%04x\\%s"),
                   m_translation.langID,
                   m_translation.charset,
                   lpKeyName);

      LPCTSTR pVal;
      UINT iLenVal;
      if (VerQueryValue(m_pVersionInfo, (LPTSTR)(LPCTSTR)query,
          (LPVOID*)&pVal, &iLenVal)) {

         sVal = pVal;
      }
   }
   return sVal;
}

CString CModuleVersion::GetCompanyName() {
  return GetValue(_T("CompanyName"));
}
CString CModuleVersion::GetInternalName() {
  return GetValue(_T("InternalName"));
}
CString CModuleVersion::GetOriginalFilename() {
  return GetValue(_T("OriginalFilename"));
}

// extern 
CString extGetModuleVersion(HINSTANCE hInstance)
{
	CString s;
  TCHAR szFullPath[MAX_PATH];
	::GetModuleFileName(hInstance, szFullPath, sizeof(szFullPath));
	CModuleVersion ver;
	if (ver.GetFileVersionInfo(szFullPath)) {
		// Version
    if ( 0==LOWORD(ver.dwFileVersionMS) && 0==LOWORD(ver.dwFileVersionLS) ) {
      s.Format(_T("%d"),(int) HIWORD(ver.dwFileVersionMS));
    }
    else {
		  s.Format(_T("%d.%02d.%02d"),(int) HIWORD(ver.dwFileVersionMS),(int) LOWORD(ver.dwFileVersionMS),(int)LOWORD(ver.dwFileVersionLS));
    }
	}
	return s;
}

// extern 
CString extGetAppVersion() {
	return extGetModuleVersion(NULL);
}

CString extGetCompanyName() {
  CString sCompanyName = _T("");
  TCHAR szFullPath[MAX_PATH];
	::GetModuleFileName(::AfxGetInstanceHandle(), szFullPath, sizeof(szFullPath));
	CModuleVersion ver;
  if (ver.GetFileVersionInfo(szFullPath))
    sCompanyName = ver.GetCompanyName();
  return sCompanyName;
}
CString extGetInternalName() {
  CString sInternalName = _T("");
  TCHAR szFullPath[MAX_PATH];
	::GetModuleFileName(::AfxGetInstanceHandle(), szFullPath, sizeof(szFullPath));
	CModuleVersion ver;
  if (ver.GetFileVersionInfo(szFullPath))
    sInternalName = ver.GetInternalName();
  return sInternalName;
}
CString extGetOriginalFilename() {
  CString sOriginalFilename = _T("");
  TCHAR szFullPath[MAX_PATH];
	::GetModuleFileName(::AfxGetInstanceHandle(), szFullPath, sizeof(szFullPath));
	CModuleVersion ver;
  if (ver.GetFileVersionInfo(szFullPath))
    sOriginalFilename = ver.GetOriginalFilename();
  return sOriginalFilename;
}

