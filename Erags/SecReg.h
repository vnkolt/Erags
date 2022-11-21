#if !defined(SECREG_H_INCLUDED)
#define SECREG_H_INCLUDED

#define TRIAL_DAYS        61
#define FIRST_CHECK_YEAR  2000

struct YMDC {
  unsigned int m:4;  //  4
  unsigned int y:7;  // 11  Year - FIRST_CHECK_YEAR
  unsigned int d:5;  // 16
  unsigned int c:16; // 32
};

class CSecReg {
public:
  int   sign1; // 0x80040001
  int   sign2; // 0x000000D3
  YMDC  rec[TRIAL_DAYS];
public:
  CSecReg();
};

class CSecurityReg {
public:
  CSecurityReg();
public:
  CString GetSubkey1();
  CString GetSubkey2();
  CString GetValueName1();
  CString GetValueName2();
  int     SetD1(CSecReg& reg, COleDateTime& odt);
  int     SetD2(CSecReg& reg, COleDateTime& odt);
  int     Set1(COleDateTime& odt);
  int     Set2(COleDateTime& odt);
  
  // key           is Software\Microsoft\Ole
  // Name of value is DefaultWritePermission           /* unused by Microsoft Ole */
  BOOL WriteBinary1(void* pData, DWORD dwSize);
  BOOL ReadBinary1(void* pData, DWORD dwMaxSize);
};

#endif // SECREG_H_INCLUDED