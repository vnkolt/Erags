# Microsoft Developer Studio Project File - Name="Era2Xml" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Era2Xml - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Era2Xml.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Era2Xml.mak" CFG="Era2Xml - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Era2Xml - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Era2Xml - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Era2Xml - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D _MFC_VER=0x0601 /D "_ERA2XML" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Shlwapi.lib /nologo /subsystem:windows /machine:I386 /out:"C:\Erags\Era2Xml.exe"

!ELSEIF  "$(CFG)" == "Era2Xml - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D _MFC_VER=0x0601 /D "_ERA2XML" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Shlwapi.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\Era2Xml.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Era2Xml - Win32 Release"
# Name "Era2Xml - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CnvBirth.cpp
# End Source File
# Begin Source File

SOURCE=.\CnvDeath.cpp
# End Source File
# Begin Source File

SOURCE=.\DateFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\db.cpp
# End Source File
# Begin Source File

SOURCE=.\Dictionaries.cpp
# End Source File
# Begin Source File

SOURCE=.\Era2Xml.cpp
# End Source File
# Begin Source File

SOURCE=.\Era2Xml.rc
# End Source File
# Begin Source File

SOURCE=.\Era2XmlDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FinishDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Geography.cpp
# End Source File
# Begin Source File

SOURCE=.\Globals.cpp
# End Source File
# Begin Source File

SOURCE=.\Helpers.cpp
# End Source File
# Begin Source File

SOURCE=.\MyFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\RSBirthes.cpp
# End Source File
# Begin Source File

SOURCE=.\RSDeathes.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WitnessDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\XmlFile.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CnvBirth.h
# End Source File
# Begin Source File

SOURCE=.\CnvDeath.h
# End Source File
# Begin Source File

SOURCE=.\DateFunc.h
# End Source File
# Begin Source File

SOURCE=.\db.h
# End Source File
# Begin Source File

SOURCE=.\Dictionaries.h
# End Source File
# Begin Source File

SOURCE=.\Era2Xml.h
# End Source File
# Begin Source File

SOURCE=.\Era2XmlDlg.h
# End Source File
# Begin Source File

SOURCE=.\EraEdit.h
# End Source File
# Begin Source File

SOURCE=.\FinishDlg.h
# End Source File
# Begin Source File

SOURCE=.\Geography.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\Helpers.h
# End Source File
# Begin Source File

SOURCE=.\MyFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RSBirthes.h
# End Source File
# Begin Source File

SOURCE=.\RSDeathes.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WitnessDlg.h
# End Source File
# Begin Source File

SOURCE=.\XmlFile.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Era2Xml.ico
# End Source File
# Begin Source File

SOURCE=.\res\Era2Xml.rc2
# End Source File
# Begin Source File

SOURCE=.\res\NewMenu256.bmp
# End Source File
# End Group
# Begin Group "Controls"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\Controls\EraComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\EraComboBox.h
# End Source File
# Begin Source File

SOURCE=..\Controls\EraControls.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\EraControls.h
# End Source File
# Begin Source File

SOURCE=..\Controls\EraEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\EraEdit.h
# End Source File
# Begin Source File

SOURCE=..\Controls\EraMonthCalCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\EraMonthCalCtrl.h
# End Source File
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

SOURCE=..\Controls\NewMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\NewMenu.h
# End Source File
# Begin Source File

SOURCE=..\Controls\ShellType.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ShellType.h
# End Source File
# Begin Source File

SOURCE=..\Controls\VisualStylesXP.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\VisualStylesXP.h
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\Common\CyrString.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\CyrString.h
# End Source File
# Begin Source File

SOURCE=..\Common\DAO36.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\DAO36.h
# End Source File
# Begin Source File

SOURCE=..\Common\FHelpers.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\FHelpers.h
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
