//
// CnvDeath.h
//

#pragma once

void ConvertDeath(CDaoDatabase& db, LPCTSTR szOutFolder, LPCTSTR szFileMask, long nMaxOutRecords,
                  BOOL fPeriod, COleDateTime& odtFrom, COleDateTime& odtTill,
                  CProgressCtrl& ProgressBar, int& nCurProgressPos);