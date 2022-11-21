// LogThread.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "LogThread.h"

#include "..\Common\FHelpers.h"
#include "..\Common\Version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CStdioFile  g_LogFile;
extern BOOL g_fLogging;

void WriteLog(LPCTSTR szLogString) {
  if ( g_fLogging && g_LogFile.m_pStream ) {
    g_LogFile.WriteString(szLogString);
    g_LogFile.Flush();
  }
}

void Log(LPCTSTR szLog, LPCTSTR szCaller/*=NULL*/) {
  if ( g_fLogging ) {
    SYSTEMTIME st;
    GetLocalTime(&st);
    CString s;
    s.Format("%02d:%02d:%02d.%03d ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    if ( szCaller ) {
      s += szCaller;
      s += ':';
    }
    s += szLog;
    if ( s.Right(2) != _T("\n") )
      s += _T("\n");
    WriteLog(s);
  }
}

void OpenLog() {
  if ( g_fLogging ) {
    SYSTEMTIME st;
    GetLocalTime(&st);
    CString ServerLogFile;
    CString szHostName = GetHostName();

    ServerLogFile.Format(_T("%s\\Erags%02d%02d%02d%02d%02d.log"),
                         GetModulePath(), st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

    CFileException FileException;
    if ( g_LogFile.Open(ServerLogFile, CFile::modeCreate | CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite, &FileException) ) {
      CString sMsg;
      #ifdef _DEBUG
      sMsg.Format(_T("Erags debug [%s] стартовал на компьютере %s."), extGetAppVersion(), szHostName);
      #else
      sMsg.Format(_T("Erags [%s] стартовал на компьютере %s."),extGetAppVersion(), szHostName);
      #endif
      Log(sMsg);
    }
  }
}
void CloseLog() {
  if ( g_fLogging && g_LogFile.m_pStream ) {
    Log(_T("Erags завершил работу."));
    g_LogFile.Close();
  }
}

void LogDBError(CDaoException* e, LPCTSTR szCaller) {
  if ( false==g_fLogging )
    return;
  CString szErr;
  szErr.Format(_T("%s: ошибка DAO %d: %s."), szCaller, e->m_pErrorInfo->m_lErrorCode, e->m_pErrorInfo->m_strDescription);
  Log(szErr, szCaller);
}

