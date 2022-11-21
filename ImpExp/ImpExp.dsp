# Microsoft Developer Studio Project File - Name="ImpExp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ImpExp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ImpExp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImpExp.mak" CFG="ImpExp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImpExp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImpExp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ImpExp - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "NDEBUG"
# ADD RSC /l 0x422 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /dll /machine:I386 /out:"C:\Erags\ImpExp.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy r:\erags\ImpExp\Release\impexp.lib r:\erags\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ImpExp - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "_DEBUG"
# ADD RSC /l 0x422 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"R:\Erags\ImpExp.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy r:\erags\ImpExp\Debug\impexp.lib r:\erags\*.*
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ImpExp - Win32 Release"
# Name "ImpExp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Copy2Excel.cpp
# End Source File
# Begin Source File

SOURCE=.\DBF.CPP
# End Source File
# Begin Source File

SOURCE=.\DefBirth.cpp
# End Source File
# Begin Source File

SOURCE=.\Er3ToEr3.cpp
# End Source File
# Begin Source File

SOURCE=.\EraToEr3.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportDlgs.cpp
# End Source File
# Begin Source File

SOURCE=.\ImpExp.cpp
# End Source File
# Begin Source File

SOURCE=.\ImpExp.def
# End Source File
# Begin Source File

SOURCE=.\ImpExp.rc
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportProgessDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OldCaches.cpp
# End Source File
# Begin Source File

SOURCE=.\OOCalcWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\RepairDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SafeArrayHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptObject.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DBF.H
# End Source File
# Begin Source File

SOURCE=.\DefBirth.h
# End Source File
# Begin Source File

SOURCE=.\Er3ToEr3.h
# End Source File
# Begin Source File

SOURCE=.\EraToEr3.h
# End Source File
# Begin Source File

SOURCE=.\ExportDlgs.h
# End Source File
# Begin Source File

SOURCE=.\ImpExp.h
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImportProgessDlg.h
# End Source File
# Begin Source File

SOURCE=.\MyFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\OldCaches.h
# End Source File
# Begin Source File

SOURCE=.\OOCalcWrapper.h
# End Source File
# Begin Source File

SOURCE=.\RepairDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SafeArrayHelper.h
# End Source File
# Begin Source File

SOURCE=.\ScriptObject.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Attention.ico
# End Source File
# Begin Source File

SOURCE=.\res\Birth.ico
# End Source File
# Begin Source File

SOURCE=.\res\Change.ico
# End Source File
# Begin Source File

SOURCE=.\res\CheckBoxIL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Death.ico
# End Source File
# Begin Source File

SOURCE=.\res\Divorce.ico
# End Source File
# Begin Source File

SOURCE=.\res\idil_mes.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ImpExp.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Marriage.ico
# End Source File
# End Group
# Begin Group "Controls"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\Controls\FEButton.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\FEButton.h
# End Source File
# Begin Source File

SOURCE=..\Controls\FileEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\FileEditCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Controls\NewWizDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\NewWizDialog.h
# End Source File
# Begin Source File

SOURCE=..\Controls\NewWizPage.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\NewWizPage.h
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\Common\BasicExcelVC6.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\Common\BasicExcelVC6.hpp
# End Source File
# Begin Source File

SOURCE=..\Common\CyrString.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\DAO36.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\DAO36.h
# End Source File
# Begin Source File

SOURCE=..\Common\DaoErr.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\DaoErr.h
# End Source File
# Begin Source File

SOURCE=..\Common\DB.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\DB.H
# End Source File
# Begin Source File

SOURCE=..\Common\Elections.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Elections.h
# End Source File
# Begin Source File

SOURCE=..\Common\ExpByExcel.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\ExpByExcel.h
# End Source File
# Begin Source File

SOURCE=..\Common\Export.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Export.h
# End Source File
# Begin Source File

SOURCE=..\Common\FHelpers.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\FHelpers.h
# End Source File
# Begin Source File

SOURCE=..\Common\MDB.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\MDB.H
# End Source File
# Begin Source File

SOURCE=..\Common\Monthes.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Monthes.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
