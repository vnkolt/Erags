//
// Crypto.cpp
//
#include "stdafx.h"
#include "Crypto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString AddToLSection(CString& szSection, TCHAR c1, TCHAR c2, BOOL fAdd) {
  CString szResult;
  int iVal = atoi(szSection);
  if ( fAdd ) 
    iVal += (int)c1*(int)c2;
  else
    iVal -= (int)c1*(int)c2;
  if ( iVal >= 1000000 ) {
    iVal -= 1000000;
  }
  else if ( iVal < 0 ) {
    iVal += 1000000;
  }
  szResult.Format(_T("%06d"), iVal);
  return szResult;
}

DWORD HexStringToBin(const char* string, DWORD cbInSize,
                    void* destBuf, DWORD cbOutSize) {

  DWORD cbOutIndex(0);
  memset(destBuf, 0, cbOutSize);
  char hexbuf[8];
  for( DWORD i(0); i < cbInSize; i+=2 ) {
    DWORD b;
    hexbuf[0] = string[i];
    hexbuf[1] = string[i+1];
    hexbuf[2] = 0;
    if ( !(isxdigit(hexbuf[0]) && isxdigit(hexbuf[1])) )
      break;
#ifdef _STRCPY_S
    sscanf_s(hexbuf, "%02X", &b);
#else
    sscanf(hexbuf, "%02X", &b);
#endif
    if ( cbOutIndex==cbOutSize)
      break;
    ((char*)destBuf)[cbOutIndex++] = (TCHAR)b;
  }
  return cbOutIndex;
}

DWORD BinToHexString(const char* pInBuf, DWORD cbInSize, char* string, DWORD cbOutSize) {
  if ( cbOutSize > 0 ) {
    char buf[8];
    string[0] = 0;
    for( DWORD i(0); i < cbInSize; i++ ){
#ifdef _STRCPY_S
      sprintf_s(buf, sizeof(buf), "%02X", (BYTE)pInBuf[i]);
#else
      sprintf(buf, "%02X", (BYTE)pInBuf[i]);
#endif
      if( strlen(string)+3 < cbOutSize ) {
#ifdef _STRCPY_S
        strcat_s(string, cbOutSize, buf);
#else
        strcat(string, buf);
#endif
      }
    }
    return strlen(string);
  }
  else
    return 0;
}
CString BinToHexString(const char* pBuf, DWORD cbSize) {
  CString szRet;
  char szBuf[8];
  for( DWORD i(0); i < cbSize; i++ ) {
#ifdef _STRCPY_S
    sprintf_s(szBuf, sizeof(szBuf), "%02X", (BYTE)(pBuf[i]));
#else
    sprintf(szBuf, "%02X", (BYTE)(pBuf[i]));
#endif
    szRet += szBuf;
  }
  return szRet;
}

CCrypto::CCrypto() {
  m_nKeyIndex = 0;
  m_dwKeySize = 0;
  m_dwCheckSum = 0;
  m_pKeyBuffer = NULL;
}

CCrypto::~CCrypto() {
  DeleteCryptoBuffer();
}

void CCrypto::DeleteCryptoBuffer() {
  if ( m_pKeyBuffer ) {
    delete m_pKeyBuffer;
    m_pKeyBuffer = NULL;
  }
}

BYTE CCrypto::RotL(BYTE bByte, BYTE bShift) {
  BYTE hibit = 0;
  bShift %= 8;

  while (bShift--) {
    hibit = (BYTE)(bByte & 0x80);
    bByte <<= 1;
    if( hibit )
      bByte |= 1;
  }
  return bByte;
}
BYTE CCrypto::RotR(BYTE bByte, BYTE bShift) {
  BYTE lobit = 0;
  bShift %= 8;
  while (bShift--) {
    lobit =  (BYTE)(bByte & 0x01);
    bByte >>= 1;
    if (lobit)
      bByte |= 0x80;
  }
  return bByte;
}

BYTE CCrypto::Mirror(BYTE bSrc) {
  BITS bIn, bOut;
  bIn.byte = bSrc;
  bOut.b0 = bIn.b7;
  bOut.b1 = bIn.b6;
  bOut.b2 = bIn.b5;
  bOut.b3 = bIn.b4;
  bOut.b4 = bIn.b3;
  bOut.b5 = bIn.b2;
  bOut.b6 = bIn.b1;
  bOut.b7 = bIn.b0;
  return bOut.byte;
}

BYTE CCrypto::MirrorXor(BYTE bSrc, BYTE bXor, bool bEncrypt){
  if( bEncrypt ) 
    return (BYTE)(Mirror(bSrc)^bXor);
  else
    return (BYTE)Mirror((BYTE)(bSrc^bXor));
}

void CCrypto::SetKeyIndex(DWORD nIndex){
  if ( nIndex < m_dwKeySize )
    m_nKeyIndex = nIndex;
  else
    m_nKeyIndex = nIndex % m_dwKeySize;
}

void CCrypto::SetCryptoKey(const void *pBuffer, DWORD dwSize) {
  DeleteCryptoBuffer();

  if ( pBuffer ) {
    m_dwKeySize = dwSize / sizeof(SCRYPTOS);
    m_pKeyBuffer = new SCRYPTOS[m_dwKeySize];
    if ( m_pKeyBuffer )
      memcpy( m_pKeyBuffer, pBuffer, m_dwKeySize*sizeof(SCRYPTOS) );
  }
}

void CCrypto::Crypt(BYTE* pSrc, DWORD dwSize, bool bEncrypt) {

  if ( m_pKeyBuffer==NULL )
    return;

  while(dwSize--)  {
    BYTE bSrc = *pSrc,
         bCrypt = m_pKeyBuffer[m_nKeyIndex].ucC;

    if ( bEncrypt==true )
      m_dwCheckSum += bSrc;  // calc checksum for original buffer

    switch( m_pKeyBuffer[m_nKeyIndex].ucM % 8 ){
      case 1: bSrc ^= bCrypt;       // only xor
        break;
      case 2: bSrc = (BYTE)(~bSrc ^ bCrypt);// not and xor
        break;
      case 3: bSrc = Mirror(bSrc);
        break;
      case 4: bSrc = MirrorXor(bSrc, bCrypt, bEncrypt); // mirror and xor
        break;
      case 5:
        if( bEncrypt==true )
          bSrc = RotL(bSrc, bCrypt);// rotate to left
        else
          bSrc = RotR(bSrc, bCrypt);// rotate to right
        break;
      case 6:
        if( bEncrypt==true )
          bSrc = RotR(bSrc, bCrypt);
        else
          bSrc = RotL(bSrc, bCrypt);
        break;
      case 7:
        bSrc = ~bSrc;
        break;
    }

    if (++m_nKeyIndex == m_dwKeySize)
      m_nKeyIndex = 0;

    *pSrc = bSrc;

    if ( bEncrypt==false )
      m_dwCheckSum += bSrc;    // calc checksum for encrypted buffer

    pSrc++;
  }
}


void CCrypto::Encrypt(void* pBuffer, DWORD dwSize) {
  Crypt((BYTE*)pBuffer, dwSize, true);
}

void CCrypto::Decrypt(void* pBuffer, DWORD dwSize) {
  Crypt((BYTE*)pBuffer, dwSize, false);
}

