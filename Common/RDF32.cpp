//
// RDF32.cpp
//
#include "stdafx.h"

#include "..\Common\CyrString.h"
#include "..\Common\Crypto.h"
#include "..\Common\FHelpers.h"
#include "..\ZipArchive\zlib\zlib.h"

// #define RDF_WRITER
#include "RDF32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT MakeRDFHashKey(LPCTSTR key) {
	UINT nHash = 0;
	while (*key)
		nHash = (nHash<<5) + nHash + *key++;
	return nHash;
}

#ifdef RDF_WRITER
void Ini2RDF(LPCTSTR szIniFile, LPCTSTR szPackFile) {
  FILE* f = fopen(szPackFile, "w+b");
  if ( NULL==f )
    return;

  const int BUF_SIZE = 0x8000;
  char* pBuf = new char[BUF_SIZE];
  char* pSectBuf = new char[BUF_SIZE];
  DWORD dwSize = ::GetPrivateProfileSectionNames(pBuf, BUF_SIZE, szIniFile);
  char* p = pBuf;
  CStringArray SectNames;
  CPtrArray    SectionsBodies;
  CByteArray   SectInfoBuffer;
  BYTE SectNum = 1;
  RDFTail rdfTail;
  memset(&rdfTail, 0, sizeof(rdfTail));
  rdfTail.Signature = RDF32_SIGNATURE;
  rdfTail.MakeTime = time(NULL);

  char szKeyBuf[32];
  sprintf(szKeyBuf, "%08x%08x", rdfTail.MakeTime, rdfTail.Signature);

  DWORD BodyOffset = 0;
  while ( *p ) {
    dwSize = ::GetPrivateProfileSection(p, pSectBuf, BUF_SIZE, szIniFile);
    if ( dwSize ) {
      DWORD PacketSize = dwSize + (long)(dwSize*0.01) +  12;
      BYTE* pBody = new BYTE[PacketSize];
      int zRet = compress(pBody, &PacketSize, (BYTE*)pSectBuf, dwSize);
      if ( Z_OK!=zRet ) {
        delete pBody;
        p+= strlen(p)+1;
        continue;
      }

      CCrypto crypto;
      crypto.SetCryptoKey(szKeyBuf, strlen(szKeyBuf));
      crypto.Encrypt(pBody, PacketSize);

      fwrite(pBody, 1, PacketSize, f);

      SectNames.Add( p );
      UINT HashKey = MakeRDFHashKey(p);
      rdfTail.nSections++;
      rdfTail.CheckSum += HashKey;

      memcpy(pBody, pSectBuf, PacketSize);
      SectionsBodies.Add( pBody );

      RDFSection SectInfo;
      strcpy(SectInfo.szSectName, p);
      SectInfo.cbSize     = SectInfo.GetSize();
      SectInfo.SectNum    = SectNum++;
      SectInfo.SectType   = *p;
      SectInfo.OriginSize = dwSize;
      SectInfo.PacketSize = PacketSize;
      SectInfo.BodyOffset = BodyOffset;

      BYTE* pSect = (BYTE*)&SectInfo;
      for( int i(0); i < SectInfo.cbSize; i++ ) {
        SectInfoBuffer.Add( *pSect++ );
      }

      BodyOffset += PacketSize;

      #ifdef _DEBUG
      fpos_t fpos;
      fgetpos(f, &fpos);
      ASSERT(fpos == BodyOffset);
      #endif

    }
    p+= strlen(p)+1;
  }

  rdfTail.SectBufOriginSize = SectInfoBuffer.GetSize();
  DWORD PacketSize = rdfTail.SectBufOriginSize + (DWORD)(rdfTail.SectBufOriginSize*0.1) + 12;

  BYTE* pZBuf = new BYTE[PacketSize];
  int zRet = compress(pZBuf, &PacketSize, SectInfoBuffer.GetData(), SectInfoBuffer.GetSize());
  if ( Z_OK==zRet ) {
    rdfTail.SectPacketSize = PacketSize;
    fwrite(pZBuf, 1, PacketSize, f);
  }
  delete pZBuf;

  fwrite(&rdfTail, 1, sizeof(rdfTail), f);

  for ( int i(0); i < SectionsBodies.GetSize(); i++ ) {
    char* pBody           = (char*)SectionsBodies.GetAt(i);
    delete pBody;
  }
  delete pSectBuf;
  delete pBuf;
  fclose(f);
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CRDF32Reader
CRDF32Reader::CRDF32Reader() {
  m_pRDFTail = NULL;
}
CRDF32Reader::~CRDF32Reader() {
  Clear();
}
void CRDF32Reader::Clear() {
  for( int i(0); i < m_SectInfo.GetSize(); i++ ) {
    delete m_SectInfo.GetAt(i);
  }
  m_SectInfo.RemoveAll();
}

int CRDF32Reader::GetSection(LPCTSTR szSect) {
  for ( int i(0); i < GetNumSections(); i++) {
    if ( CyrStriCmp(GetSection(i)->szSectName, szSect)==0 )
      return i;
  }
  return -1;
}
BOOL CRDF32Reader::Read(LPCTSTR szRDFFile) {
  Clear();

  WIN32_FIND_DATA FindData;

  if ( false==FileExists(szRDFFile, &FindData) )
    return false;

  FILE* f = fopen(szRDFFile, "rb");
  if ( NULL==f )
    return false;

  m_RDF.SetSize(FindData.nFileSizeLow);

  if ( FindData.nFileSizeHigh > 0 || FindData.nFileSizeLow < sizeof(RDFTail)) {
    fclose(f);
    return false;
  }

  fread(m_RDF.GetData(), 1, FindData.nFileSizeLow, f);
  m_pRDFTail = (RDFTail *)(m_RDF.GetData() + FindData.nFileSizeLow - sizeof(RDFTail));
  BYTE* pSectBuf = ((BYTE*)m_pRDFTail) - m_pRDFTail->SectPacketSize;

  BYTE* pZBuf = new BYTE[m_pRDFTail->SectBufOriginSize];
  ULONG lSize = m_pRDFTail->SectBufOriginSize;

  if ( Z_OK == uncompress(pZBuf, &lSize, pSectBuf, m_pRDFTail->SectPacketSize) ) {
    BYTE* p = pZBuf;
    for ( WORD i = 0; i < m_pRDFTail->nSections; i++ ) {
      WORD cbSize = *(WORD*)p;
      RDFSection* pSect = (RDFSection*)new char[cbSize];
      memcpy(pSect, p, cbSize);
      m_SectInfo.Add( pSect );
      p += cbSize;
    }
  }

  if ( pZBuf )
    delete pZBuf;
  fclose(f);
  return (m_SectInfo.GetSize()>0);
}

void CRDF32Reader::GetSectionBody(int i, CRDFItems& Items) {
  const RDFSection* pSection = GetSection(i);
  BYTE* pRBuf = m_RDF.GetData() + pSection->BodyOffset;
  ULONG lSize = pSection->OriginSize;
  BYTE* pZBuf = new BYTE[lSize];

  char szKeyBuf[32];
  sprintf(szKeyBuf, "%08x%08x", m_pRDFTail->MakeTime, m_pRDFTail->Signature);

  CCrypto crypto;
  crypto.SetCryptoKey(szKeyBuf, strlen(szKeyBuf));
  crypto.Decrypt(pRBuf, pSection->PacketSize);

  if ( Z_OK == uncompress(pZBuf, &lSize, pRBuf, pSection->PacketSize) ) {
    char* pEnd = (char*)pZBuf + lSize;
    char* p = (char*)pZBuf;
    while (p < pEnd) {
      RDFItem rdfItem;
      rdfItem.m_szKey   = GetTok(p, 0, "=");
      rdfItem.m_szValue = GetTok(p, 1, "=");
      Items.Add( rdfItem );
      p += strlen(p) + 1;
    }
  }

  delete pZBuf;
}


int CRDF32Reader::FindItem(CRDFItems& Items, const CString& szRegion) {
  CString szRegionKey = "Î " + szRegion;
  for( int i(0); i < Items.GetSize(); i++ ) {
    RDFItem Item = Items.GetAt(i);
    if ( CyrStriCmp(Item.m_szKey, szRegionKey)==0 )
      return i;
  }
  return -1;
}
int CRDF32Reader::FindItem(CRDFItems& Items, const CString& szCity, const CString& szDistrict) {
  CString szCityKey       = "Ì " + szCity;
  CString szDistrictKey   = "Ð " + szDistrict;
  for( int i(0); i < Items.GetSize(); i++ ) {
    RDFItem Item = Items.GetAt(i);
    if ( CyrStriCmp(Item.m_szKey, szCityKey)==0 || CyrStriCmp(Item.m_szKey, szDistrictKey)==0 )
      return i;
  }
  return -1;
}
void CRDF32Reader::FillItem(RDFItem& Item, CString& szCity, CString& szDistrict, CString& szRagsKeys, CString& szCityKeys, CString& szDistrictKeys) {
  if ( Item.m_szKey[0]==TCHAR('Ì')) {
    szCity = Item.m_szKey.Mid(2);
  }
  else if ( Item.m_szKey[0]==TCHAR('Ð')) {
    szDistrict = Item.m_szKey.Mid(2);
  }
  for( int i(0); ; i++ ) {
    CString s = GetTok(Item.m_szValue, i, " ");
    if ( s.IsEmpty() )
      break;
    switch ( s[0] ) {
      case '@': szRagsKeys = s.Mid(1);
        break;
      case '#':
        szCityKeys += s.Mid(1);
        szCityKeys += '&';
        break;
      //case '$': szDistrict = s.Mid(1);  break;
      case '$': s = s.Mid(1);
        if ( s.Find("|") == -1 ) {
          szDistrict = s;
        }
        else {
          szDistrictKeys = s;
        }
        break;
    }
  }
  szCityKeys.Replace('^', ' ');
  szCityKeys.TrimRight();
}
