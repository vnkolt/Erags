// Office.h

//#define Uses_MSO2000

#pragma warning(disable:4146)

#ifdef Uses_MSO2000
// for MS Office 2000
#import "D:\Program Files\Microsoft Office\Office\MSO9.DLL"
#import "D:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"
#import "D:\Program Files\Microsoft Office\Office\MSWORD9.OLB" \
	rename("ExitWindows","_ExitWindows")
#import "C:\Program Files\Microsoft Office\Office\EXCEL9.OLB" \
	rename("DialogBox","_DialogBox") \
	rename("RGB","_RGB") \
	exclude("IFont","IPicture")
//#import "C:\Program Files\Common Files\Microsoft Shared\DAO\DAO360.DLL" \
//	rename("EOF","EndOfFile") rename("BOF","BegOfFile")
//#import "C:\Program Files\Microsoft Office\Office\MSACC9.OLB"
#else
// for MS Office 97
#import "D:\Program Files\Microsoft Office\Office\MSO97.DLL"
#import "D:\Program Files\Common Files\Microsoft Shared\VBA\VBEEXT1.OLB"
#import "D:\Program Files\Microsoft Office\Office\MSWORD8.OLB" \
	rename("ExitWindows","_ExitWindows")
#import "D:\Program Files\Microsoft Office\Office\EXCEL8.OLB" \
	rename("DialogBox","_DialogBox") \
	rename("RGB","_RGB") \
	exclude("IFont","IPicture")
//#import "C:\Program Files\Common Files\Microsoft Shared\DAO\DAO350.DLL" \
//	rename("EOF","EndOfFile") rename("BOF","BegOfFile")
//#import "C:\Program Files\Microsoft Office\Office\MSACC8.OLB"
#endif

#pragma warning(default:4146)
