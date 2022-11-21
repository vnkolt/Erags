
#pragma once


#pragma pack(push, pack_recent_save, 1)

typedef unsigned short uint16;
typedef unsigned long  uint32;

struct ValidOwner {
  DWORD  RagsHash;
  time_t FirstStartDate;
  DWORD  TotalRecords;
  DWORD  dwValidGeoRecords;
  DWORD  dwInvalidGeoRecors;
  DWORD  dwValidRagsRecords;
  DWORD  dwVyconcom;
};

struct RegTimerData {
  uint16 cbSize;          // 2    2
  uint16 cbCheckSum;      // 2    4
  uint32 cbShutdownCount; // 4   10
  uint16 cbWorkedDays;    // 2   12
  uint32 FirstWorkedDate; // 4   16     YYYYMMDD
  uint32 LastWorkedTime;  // 4   20     HHMMSSmmm
  uint32 LastWorkedDate;  // 4   24     YYYYMMDD
  uint16 OverSysDates;    // 2   26
  uint16 Reserved1;       // 2   28
  uint16 Reserved2;       // 2   30
  uint16 Reserved3;       // 2   32
  //uint32 FutureDates;
};


#pragma pack(pop, pack_recent_save)
