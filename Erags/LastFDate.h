#if !defined(LASTFDATE_H_INCLUDED)
#define LASTFDATE_H_INCLUDED

//#include "..\Controls\ShellType.h"

// LastFDate.h

/************************************** : by VK at 01.10.2005 4:52:46 **\
struct SecurityData {
  short           CheckSum;           // 2
  short           cbSize;             // 2  4
  int             EraVersion;         // 4  
  Win32Type       OsVersion;          // 4
  time_t          SysDirCreationTime; // 4
  int             TableOfficeID;      // 4
  BYTE            LastDateEnteredCnt; // 1
  BYTE            OfficeType;         // 1        1 - городской, 2 - районный в городе, 3 - районный, 4 - виконком
  BYTE            bRDC[32];
};

SecurityData* ReadSecurityFromReg();
SecurityData* BuildSecurityStruct(SecurityData* pSecurityData);
BOOL          WriteSecurityToReg(SecurityData* pData);
\************************************** : by VK at 01.10.2005 4:52:50 **/

COleDateTime FindLastFileTime();
#endif // LASTFDATE_H_INCLUDED