# Microsoft Developer Studio Project File - Name="EraWiz" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=EraWiz - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EraWiz.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EraWiz.mak" CFG="EraWiz - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EraWiz - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EraWiz - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EraWiz - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D _MFC_VER=0x0601 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "NDEBUG"
# ADD RSC /l 0x422 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"C:\Erags\EraWiz.dll"

!ELSEIF  "$(CFG)" == "EraWiz - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "_DEBUG"
# ADD RSC /l 0x422 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"R:\Erags\EraWiz.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "EraWiz - Win32 Release"
# Name "EraWiz - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BirthPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DivorcePage.cpp
# End Source File
# Begin Source File

SOURCE=.\EraWiz.cpp
# End Source File
# Begin Source File

SOURCE=.\EraWiz.def
# End Source File
# Begin Source File

SOURCE=.\EraWiz.rc
# End Source File
# Begin Source File

SOURCE=.\LoadDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MasterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MedicsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\NewWizDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\NewWizPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGeoPlace.cpp
# End Source File
# Begin Source File

SOURCE=.\SetRagsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UkraineMap.cpp
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

SOURCE=.\BirthPage.h
# End Source File
# Begin Source File

SOURCE=.\DivorcePage.h
# End Source File
# Begin Source File

SOURCE=.\EraWiz.h
# End Source File
# Begin Source File

SOURCE=.\LoadDlg.h
# End Source File
# Begin Source File

SOURCE=.\MasterDlg.h
# End Source File
# Begin Source File

SOURCE=.\MedicsPage.h
# End Source File
# Begin Source File

SOURCE=.\NewWizDialog.h
# End Source File
# Begin Source File

SOURCE=.\NewWizPage.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SetGeoPlace.h
# End Source File
# Begin Source File

SOURCE=.\SetRagsPage.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UkraineMap.h
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

SOURCE=.\res\birth.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Birth.ico
# End Source File
# Begin Source File

SOURCE=.\res\BtnRedCross.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Change.ico
# End Source File
# Begin Source File

SOURCE=.\res\Cherkaska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Cherkasy.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Chernihiv.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Chernihivska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Chernivtska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Chernovtsy.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Crimea.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Death.ico
# End Source File
# Begin Source File

SOURCE=.\res\Divorce.ico
# End Source File
# Begin Source File

SOURCE=.\res\Dnipropetrovsk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Dnipropetrovska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Donetsk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Donetska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EraWiz.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Frankivsk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\geography.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\htree.cur
# End Source File
# Begin Source File

SOURCE=".\res\Ivano-Frankivska_Oblast.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\Kharkiv.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Kharkivska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Kherson.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Khersonska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Khmelnitsky.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Khmelnytska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Kiev.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Kirovohrad.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Kirovohradska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Kyivska_oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\leftdown.ico
# End Source File
# Begin Source File

SOURCE=.\res\leftup.ico
# End Source File
# Begin Source File

SOURCE=.\res\Luhansk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Luhanska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Lutsk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Lviv.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Lvivska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Marriage.ico
# End Source File
# Begin Source File

SOURCE=.\res\Mykolaiv.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Mykolaivska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Odeska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Odessa.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Poltava.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Poltavska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rfolders.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rfolders_tc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\right.ico
# End Source File
# Begin Source File

SOURCE=.\res\rightdown.ico
# End Source File
# Begin Source File

SOURCE=.\res\Rivne.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Rivnenska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Sevastopol.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Simferopol.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Sumska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Sumy.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Ternopil.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Ternopilska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Ukraine.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Ukraine256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\uppoint.ico
# End Source File
# Begin Source File

SOURCE=.\res\Uzhgorod.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Vinnytsia.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Vinnytska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Volynska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Wizard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Wizard.ico
# End Source File
# Begin Source File

SOURCE=.\res\Zakarpakska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Zaporizha.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Zaporizhzhska_Oblast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Zhytomyr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Zhytomyrska_Oblast.bmp
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

SOURCE=..\Common\DB.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\DB.H
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
# Begin Group "Controls"

# PROP Default_Filter "cpp;h"
# Begin Group "CPPTooltip"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Controls\CPPTooltip\CeXDib.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\CPPTooltip\CeXDib.h
# End Source File
# Begin Source File

SOURCE=..\Controls\CPPTooltip\PPDrawManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\CPPTooltip\PPDrawManager.h
# End Source File
# Begin Source File

SOURCE=..\Controls\CPPTooltip\PPHtmlDrawer.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\CPPTooltip\PPHtmlDrawer.h
# End Source File
# Begin Source File

SOURCE=..\Controls\CPPTooltip\PPTooltip.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\CPPTooltip\PPTooltip.h
# End Source File
# End Group
# Begin Group "TCToolBar"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\Controls\TCToolBar\TCImageList.cpp
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
