#if !defined(FHELPERS_H_INCLUDED)
#define FHELPERS_H_INCLUDED

//
// FHelpers.h
//
CString GetFilePath(LPCTSTR szFileName);
CString GetFileName(LPCTSTR szPath);
CString GetFileExt(LPCTSTR szPath);
CString GetModuleFileName();
CString GetModulePath();
BOOL    FileExists(PCSTR pszFilename, WIN32_FIND_DATA* pFindData=NULL);
CString SetFileExt(LPCTSTR szPath, LPCTSTR szExt);
void    DeleteFileIfExist(PCSTR pszFilename);
CString GetHostName();

CString FormatError(DWORD dwError=0);

#endif