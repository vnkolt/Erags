//
// SecReg.cpp
//
#include "stdafx.h"
#include "Erags.h"

#include "SecReg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////
// CSecReg
CSecReg::CSecReg() {
  sign1  = 0x00000001;
  sign2  = 0x000000D3;
  memset(&rec, 0, sizeof(rec));
  sign1 |= 0x80040000;
}

////////////////////////////////////////////////////////////////////////////////////
// CSecurityReg
CSecurityReg::CSecurityReg() {
}

int CSecurityReg::SetD1(CSecReg& reg, COleDateTime& odt) {
  int i;
  BYTE d = (BYTE)(odt.GetDay());
  BYTE y = (BYTE)(odt.GetYear()-FIRST_CHECK_YEAR);
  BYTE m = (BYTE)(odt.GetMonth());
  for ( i = 0; i < TRIAL_DAYS; i++ ) {
    if ( reg.rec[i].y==0 ) {
      reg.rec[i].m = m;
      reg.rec[i].y = y;
      reg.rec[i].d = d;
      break;
    }
    if ( d==reg.rec[i].d && m==reg.rec[i].m && y==reg.rec[i].y )
      break;
  }
  if ( i < TRIAL_DAYS ) {
    reg.rec[i].c++;
  }
  return i;
}
CString CSecurityReg::GetSubkey1() {
  CString s;
                          /* Software\Microsoft\Ole */
  static BYTE szKey[] = { BYTE('S'<<1), BYTE('o'<<1), BYTE('f'<<1), BYTE('t'<<1), BYTE('w'<<1), BYTE('a'<<1), BYTE('r'<<1), BYTE('e'<<1), BYTE('\\'<<1),
                          BYTE('M'<<1), BYTE('i'<<1), BYTE('c'<<1), BYTE('r'<<1), BYTE('o'<<1), BYTE('s'<<1), BYTE('o'<<1), BYTE('f'<<1), BYTE('t'<<1), BYTE('\\'<<1),
                          BYTE('O'<<1), BYTE('l'<<1), BYTE('e'<<1) };
  for( int i(0); i < sizeof(szKey); i++ )
    s += (TCHAR)(szKey[i]>>1);
  return s;
}
CString CSecurityReg::GetValueName1() {
  CString s;              /* DefaultWritePermission */
  static BYTE szKey[] = { 'D'^0x08, 'e'^0x09, 'f'^0x0A, 'a'^0x0B, 'u'^0x0C, 'l'^0x0D, 't'^0x0E,
                          'W'^0x0F, 'r'^0x10, 'i'^0x11, 't'^0x12, 'e'^0x13,
                          'P'^0x14, 'e'^0x15, 'r'^0x16, 'm'^0x17, 'i'^0x18, 's'^0x19, 's'^0x1A, 'i'^0x1B, 'o'^0x1C, 'n'^0x1D };
  BYTE xorByte = 0x08;
  for( int i(0); i < sizeof(szKey); i++ )
    s += (TCHAR)(szKey[i]^xorByte++);
  return s;
}

CString CSecurityReg::GetSubkey2() {
                          /* Control Panel\Desktop */
  static BYTE szKey[] = { BYTE('C'<<1),BYTE('o'<<1),BYTE('n'<<1),BYTE('t'<<1),BYTE('r'<<1),BYTE('o'<<1),BYTE('l'<<1),BYTE(' '<<1),
                          BYTE('P'<<1),BYTE('a'<<1),BYTE('n'<<1),BYTE('e'<<1),BYTE('l'<<1),BYTE('\\'<<1),BYTE('D'<<1),BYTE('e'<<1),BYTE('s'<<1),BYTE('k'<<1),BYTE('t'<<1),BYTE('o'<<1),BYTE('p'<<1) };
  CString s;
  for( int i(0); i < sizeof(szKey); i++ )
    s += (TCHAR)(szKey[i]>>1);
  return s;
}
CString CSecurityReg::GetValueName2() {
  CString s;              /* Appearance */
  static BYTE szKey[] = { 'A'^0x29, 'p'^0x2B, 'p'^0x2D, 'e'^0x2F, 'a'^0x31, 'r'^0x33, 'a'^0x35, 'n'^0x37, 'c'^0x39, 'e'^0x3B };
  BYTE xorByte = 0x29;
  for( int i(0); i < sizeof(szKey); i++ ) {
    s += (TCHAR)(szKey[i]^xorByte);
    xorByte += 2;
  }
  return s;
}
int CSecurityReg::SetD2(CSecReg& reg, COleDateTime& odt) {
  int i;
  BYTE m = (BYTE)(odt.GetMonth());
  BYTE y = (BYTE)(odt.GetYear()-FIRST_CHECK_YEAR);
  BYTE d = (BYTE)(odt.GetDay());
  for ( i = 0; i < TRIAL_DAYS; i++ ) {
    if ( reg.rec[i].m==0 ) {
      reg.rec[i].y = y;
      reg.rec[i].d = d;
      reg.rec[i].m = m;
      break;
    }
    if ( y==reg.rec[i].y && d==reg.rec[i].d && m==reg.rec[i].m )
      break;
  }
  if ( i < TRIAL_DAYS ) {
    reg.rec[i].c++;
  }
  return i;
}

int CSecurityReg::Set1(COleDateTime& odt) {
  int iRet = 1;
  LONG lRes;
  HKEY hKey;
  CSecReg reg;
  lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, GetSubkey1(), 0L, KEY_ALL_ACCESS, &hKey);
  if ( ERROR_SUCCESS!=lRes ) {  // A key does not exist. We should create the key.
    lRes = ::RegCreateKey(HKEY_LOCAL_MACHINE, GetSubkey1(), &hKey); 
    iRet++;
  }
  else {
    DWORD dwType = REG_BINARY;
    DWORD dwSize = sizeof(reg);
    ::RegQueryValueEx(hKey, GetValueName1(), NULL, &dwType, (BYTE*)&reg, &dwSize);
    iRet++;
  }
  if ( lRes==ERROR_SUCCESS ) {
    iRet = SetD1(reg, odt);
    ::RegSetValueEx(hKey, GetValueName1(), NULL, REG_BINARY, (BYTE*)&reg, sizeof(reg) );
    ::RegCloseKey(hKey);
  }
  return iRet;
}
int CSecurityReg::Set2(COleDateTime& odt) {
  LONG lRes;
  HKEY hKey;
  CSecReg reg;
  int iRet = 0;
  lRes = ::RegOpenKeyEx(HKEY_CURRENT_USER, GetSubkey2(), 0L, KEY_ALL_ACCESS, &hKey);
  if ( ERROR_SUCCESS!=lRes ) {  // A key does not exist. We should create the key.
    lRes = ::RegCreateKey(HKEY_CURRENT_USER, GetSubkey2(), &hKey); 
    iRet++;
  }
  else {
    DWORD dwType = REG_BINARY;
    DWORD dwSize = sizeof(reg);
    ::RegQueryValueEx(hKey, GetValueName2(), NULL, &dwType, (BYTE*)&reg, &dwSize);
    iRet++;
  }
  if ( lRes==ERROR_SUCCESS ) {
    iRet = SetD2(reg, odt);
    ::RegSetValueEx(hKey, GetValueName2(), NULL, REG_BINARY, (BYTE*)&reg, sizeof(reg) );
    ::RegCloseKey(hKey);
  }
  return iRet;
}

BOOL CSecurityReg::WriteBinary1(void* pData, DWORD dwSize) {
  BOOL fRet = false;
  LONG lRes;
  HKEY hKey;
  lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, GetSubkey1(), 0L, KEY_ALL_ACCESS, &hKey);
  if ( ERROR_SUCCESS!=lRes ) {  // A key does not exist. We should create the key.
    lRes = ::RegCreateKey(HKEY_LOCAL_MACHINE, GetSubkey1(), &hKey); 
  }
  if ( lRes==ERROR_SUCCESS ) {
    ::RegSetValueEx(hKey, GetValueName1(), NULL, REG_BINARY, (BYTE*)pData, dwSize);
    ::RegCloseKey(hKey);
  }
  return fRet;
}

BOOL CSecurityReg::ReadBinary1(void* pData, DWORD dwSize) {
  BOOL fRet = false;
  LONG lRes;
  HKEY hKey;
  lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, GetSubkey1(), 0L, KEY_ALL_ACCESS, &hKey);
  if ( lRes==ERROR_SUCCESS ) {
    DWORD dwType = REG_BINARY;
    ::RegQueryValueEx(hKey, GetValueName1(), NULL, &dwType, (BYTE*)pData, &dwSize);
    ::RegCloseKey(hKey);
    fRet = true;
  }
  return fRet;
}