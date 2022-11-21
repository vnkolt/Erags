//
// Security.cpp
//
#include "stdafx.h"
#include "Erags.h"

/**************************************** 11/12/2001 6:37:30 PM by VK
#include <atlconv.h>
#include <atlbase.h>
***************************************** 11/12/2001 6:37:32 PM by VK */

#include "..\Common\Crypto.h"
#include "..\Common\CyrString.h"
#include "..\Common\Sections.h"

#define RDFSF_SIGNATURE_SIZE  8
#define RDFSF_SIGNATURE       "RDFSF3.1"

short g_IsRegion[4] = { TRUE, TRUE, TRUE, TRUE};

CString DecodeRagsName(const CString& sRags);

CSecurity theSecurity;

CSecurity::CSecurity() {
  m_error = errNoErrors;
  m_bLoaded = false;
  m_bArrayBuilt = false;
  m_fValidOwner = m_fRegion = false;
}

CSecurity::~CSecurity() {
  m_IniArray.ClearContainer();
}

int CSecurity::IsBadSignature(LPCTSTR pSignature) {
  return memcmp(pSignature, RDFSF_SIGNATURE, RDFSF_SIGNATURE_SIZE);
}

void CSecurity::SetFileName(LPCTSTR pFileName/*=NULL*/) {
  if (pFileName==NULL) { // default:
    // .rdf file will have same name like current ERAGS.dll module
    TCHAR buffer[MAX_PATH];
    GetModuleFileName(AfxGetInstanceHandle(), buffer, MAX_PATH);    m_sFileName = SetFileExt(buffer, _T(".rdf"));
  }
  else
    m_sFileName = pFileName;
}

bool CSecurity::Load() {
  m_bLoaded = false;
  if ( m_sFileName.IsEmpty() )
    return false;
  HANDLE hFile = CreateFile(m_sFileName,     // lpFileName
                    GENERIC_READ,   // dwDesiredAccess
                    FILE_SHARE_READ,// dwShareMode
                    NULL,           // lpSecurityAttributes
                    OPEN_EXISTING,  // dwCreationDisposition
                    FILE_ATTRIBUTE_ARCHIVE |
                    FILE_ATTRIBUTE_HIDDEN |
                    FILE_ATTRIBUTE_READONLY,
                    NULL);
  if ( INVALID_HANDLE_VALUE==hFile ) {
    m_error = errCannotOpen;
    return false;
  }

  DWORD dwSize, dwRead;
  
  dwSize = GetFileSize(hFile, NULL);

  SRDFHeader rdfHeader;
  if ( RDF_MINZIZE <= dwSize ) {
    ReadFile(hFile, &rdfHeader, sizeof(rdfHeader), &dwRead, NULL);
    if ( sizeof(rdfHeader)==dwRead &&
         IsBadSignature(rdfHeader.rdfSignature)==false) {
      DWORD dwBufSize = dwSize-dwRead;
      BYTE* pBuffer = new BYTE[dwBufSize];
      ReadFile(hFile, pBuffer, dwBufSize, &dwRead, NULL);

      // Create CCrypto object
      CString s, sCryptoKey = _T("");
      for( UINT u=IDS_RM01; u < IDS_M12; u++ ) {
        s.LoadString(u);
        sCryptoKey += s;
      }

      CCrypto crypto;
      crypto.SetCryptoKey(sCryptoKey, sCryptoKey.GetLength());
      crypto.SetKeyIndex(rdfHeader.rdfTime);
      crypto.Decrypt(pBuffer, dwBufSize);

      DWORD dwCheckSum = crypto.GetCheckSum();
      if ( dwCheckSum != rdfHeader.rdfCheckSum ) {
        m_error = errBadFormat;
        return false;
      }

      int iNumberOfSections = *(int*)pBuffer;
      LPTSTR p = (LPTSTR)pBuffer + sizeof(int);
      m_IniArray.ClearContainer();

      for (int i(0); i < iNumberOfSections; i++) {
        int nKeys = *(int*)p;
        p += sizeof(int);
        m_IniArray.AddSection(p);
        p += strlen(p)+1;
        for ( int j(0); j < nKeys; j++ ) {
          LPTSTR pKeyName, pKeyValue;
          pKeyName = p; p += strlen(p)+1;
          pKeyValue = p; p += strlen(p)+1;
          m_IniArray.AddValue(pKeyName, pKeyValue);
        }
      }
      m_error = errNoErrors;
      delete pBuffer;
    }
    else
      m_error = errBadFormat;
  }
  else
    m_error = errBadFormat;
  CloseHandle(hFile);
  m_bLoaded = true;
  return (errNoErrors==m_error);
}

CString CSecurity::GetExpiration() {
  if ( !m_sExpiration.IsEmpty() )
    return m_sExpiration;
  CSection* pSection = GetSection(_T("Author"));
  if ( pSection ) {
    m_sExpiration = pSection->GetValue(_T("LTD"));
    return m_sExpiration;
  }
  return _T("");
}

bool CSecurity::IsDisabled(COleDateTime& odt) {
  if ( m_fValidOwner )
    return false;
  if ( COleDateTime::valid==odt.GetStatus() ) {
    CString s = odt.Format(_T("%Y%m%d"));
    if ( atoi(s) >= atoi(GetExpiration()) )
      return true;
  }
  return false;
}

void CSecurity::CheckRegion(LPCTSTR szRegion, LPCTSTR szCity) {
  m_fRegion = false;
  m_sRegionKey.Empty();
  CSection* pSection = m_IniArray.GetSection(_T("Regions"));
  if ( NULL==pSection )
    return;
  for( int i(0); i < pSection->GetNumberOfKeys(); i++ ) {
    CString s = pSection->GetKeyValue(i);
    if ( s==szRegion || s==szCity) {
      m_fRegion = true;
      m_sRegionKey = pSection->GetKeyName(i);
      return;
    }
  }
}

bool CSecurity::CheckForKeys(const CString& sRegion, LPCTSTR szRagsName) {
  if ( m_sRegionKey.IsEmpty() ) 
    return false;
  CString sUserSect, sRagsName;
  sUserSect.Format( _T("Users%s"), m_sRegionKey );
  sRagsName = LatinToCyr(DecodeRagsName(szRagsName));
  sRagsName = UpperString(sRagsName);

  CSection* pSection = m_IniArray.GetSection(sUserSect);
  if ( NULL==pSection ) 
    return false;

  for( int i(0); i < pSection->GetNumberOfKeys(); i++ ) {
    CString sKeys = pSection->GetKeyValue(i);
    CString sToks[3];
    sToks[0] = UpperString(GetTokSpace(sKeys, 0));
    if ( sRagsName.Find(sToks[0]) >= 0 ) {
      sToks[1] = UpperString(GetTokSpace(sKeys, 1));
      if ( sToks[1].IsEmpty() ) {
        m_fValidOwner = true;
        return true;
      }
      if ( sRagsName.Find(sToks[1]) >= 0 ) {
        sToks[2] = UpperString(GetTokSpace(sKeys, 2));
        if ( sToks[2].IsEmpty() ) {
          m_fValidOwner = true;
          return true;
        }
        if ( sRagsName.Find(sToks[2]) >= 0 ) {
          m_fValidOwner = true;
          return true;
        }
      }
    }
  }

  return false;
}

////////////////////////////////////////////////////////////////////////
// end of the module
////////////////////////////////////////////////////////////////////////