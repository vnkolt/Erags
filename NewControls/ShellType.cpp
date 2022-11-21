//
// ShellType.cpp
//
#include <afxwin.h>
#include "ShellType.h"

static Win32Type g_Shell = IsShellType(); 

Win32Type IsShellType() {
	Win32Type  ShellType;
	DWORD winVer;
	OSVERSIONINFO *osvi;
	
	winVer=GetVersion();
	if(winVer<0x80000000){/*NT */
		ShellType=WinNT3;
		osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
		if (osvi!=NULL){
			memset(osvi,0,sizeof(OSVERSIONINFO));
			osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
			GetVersionEx(osvi);
			if(osvi->dwMajorVersion==4L)ShellType=WinNT4;
			else if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==0L)ShellType=Win2000;
			else if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==1L)ShellType=WinXP;
			else if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==2L)ShellType=Win2003;
			free(osvi);
		}
	}
	else if  (LOBYTE(LOWORD(winVer))<4)
		ShellType=Win32s;
	else{
		ShellType=Win95;
		osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
		if (osvi!=NULL){
			memset(osvi,0,sizeof(OSVERSIONINFO));
			osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
			GetVersionEx(osvi);
			if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==10L)ShellType=Win98;
			else if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==90L)ShellType=WinME;
			free(osvi);
		}
	}
	return ShellType;
}

