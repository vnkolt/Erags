# Microsoft Developer Studio Project File - Name="EraSetup" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=EraSetup - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EraSetup.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EraSetup.mak" CFG="EraSetup - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EraSetup - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "EraSetup - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EraSetup - Win32 Release"

# PROP BASE Use_MFC 6
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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x422 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"C:\EraCD\Setup.exe"

!ELSEIF  "$(CFG)" == "EraSetup - Win32 Debug"

# PROP BASE Use_MFC 6
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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "ZLIB_WINAPI" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x422 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"C:\EraCD\Setup.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "EraSetup - Win32 Release"
# Name "EraSetup - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AgreementPage.cpp
# End Source File
# Begin Source File

SOURCE=.\AutoRichEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CDMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\EraPathPage.cpp
# End Source File
# Begin Source File

SOURCE=.\EraSetup.cpp
# End Source File
# Begin Source File

SOURCE=.\EraSetup.rc
# End Source File
# Begin Source File

SOURCE=.\EraSetupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FinishPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MasterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NewWizDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\NewWizPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\Shell.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UnzipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WelcomePage.cpp
# End Source File
# Begin Source File

SOURCE=.\WizButton.cpp
# End Source File
# Begin Source File

SOURCE=.\WizComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\WizEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\WizTreeCtrl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AgreementPage.h
# End Source File
# Begin Source File

SOURCE=.\AutoRichEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CDMenu.h
# End Source File
# Begin Source File

SOURCE=.\EraPathPage.h
# End Source File
# Begin Source File

SOURCE=.\EraSetup.h
# End Source File
# Begin Source File

SOURCE=.\EraSetupDlg.h
# End Source File
# Begin Source File

SOURCE=.\FinishPage.h
# End Source File
# Begin Source File

SOURCE=.\MasterDlg.h
# End Source File
# Begin Source File

SOURCE=.\NewWizDialog.h
# End Source File
# Begin Source File

SOURCE=.\NewWizPage.h
# End Source File
# Begin Source File

SOURCE=.\ProgressPage.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Shell.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UnzipDlg.h
# End Source File
# Begin Source File

SOURCE=.\WelcomePage.h
# End Source File
# Begin Source File

SOURCE=.\WizButton.h
# End Source File
# Begin Source File

SOURCE=.\WizComboBox.h
# End Source File
# Begin Source File

SOURCE=.\WizEdit.h
# End Source File
# Begin Source File

SOURCE=.\WizTreeCtrl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Erags.ico
# End Source File
# Begin Source File

SOURCE=.\res\EraSetup.ico
# End Source File
# Begin Source File

SOURCE=.\res\EraSetup.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Russia.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ukraine.ico
# End Source File
# Begin Source File

SOURCE=.\res\Welcome24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\write.ico
# End Source File
# End Group
# Begin Group "Controls"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\Controls\ShellType.cpp
# End Source File
# End Group
# Begin Group "ZipArchive"

# PROP Default_Filter "cpp;h"
# Begin Group "ZLib"

# PROP Default_Filter "c;h"
# Begin Source File

SOURCE=..\ZipArchive\ZLib\adler32.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\compress.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\crc32.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\crc32.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\deflate.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\deflate.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\gzclose.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\gzguts.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\gzlib.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\gzread.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\gzwrite.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\infback.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\inffast.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\inffast.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\inffixed.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\inflate.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\inflate.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\inftrees.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\inftrees.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\trees.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\trees.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\uncompr.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\zconf.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\zlib.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\zutil.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZLib\zutil.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\ZipArchive\Options.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\Options.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\RegistrySerialize.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\RegistrySerialize.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\zconf.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipAbstractFile.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipArchive.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipArchive.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipAutoBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipAutoBuffer.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipBaseException.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipBigFile.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipBigFile.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipCentralDir.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipCentralDir.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipCollections.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipCompatibility.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipCompatibility.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipException.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipException.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipExport.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipFile.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipFile.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipFileHeader.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipFileHeader.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipFileMapping.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipInternalInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipInternalInfo.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipMemFile.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipMemFile.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipPathComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipPathComponent.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipPlatform.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipPlatform.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipPlatformComm.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipStorage.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipStorage.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipString.cpp
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\ZipString.h
# End Source File
# Begin Source File

SOURCE=..\ZipArchive\zlib.h
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter "cpp;h"
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

SOURCE=..\Common\IsAdmin.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\IsAdmin.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\EULA.rtf
# End Source File
# Begin Source File

SOURCE=.\res\finish.rtf
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
