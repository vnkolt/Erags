#if !defined(AFX_LOGTHREAD_H__5AF4FBC2_EF75_4C17_94ED_48EC69EE2CCD__INCLUDED_)
#define AFX_LOGTHREAD_H__5AF4FBC2_EF75_4C17_94ED_48EC69EE2CCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogThread.h : header file
//

void OpenLog();
void CloseLog();

void Log(LPCTSTR szError, LPCTSTR szCaller=NULL);
void LogDBError(CDaoException* e, LPCTSTR szCaller);

extern BOOL g_fLogging;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGTHREAD_H__5AF4FBC2_EF75_4C17_94ED_48EC69EE2CCD__INCLUDED_)
