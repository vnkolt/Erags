# Microsoft Developer Studio Project File - Name="EraABC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=EraABC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EraABC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EraABC.mak" CFG="EraABC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EraABC - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "EraABC - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EraABC - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_ERAABC" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x422 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 SHLWAPI.LIB VERSION.LIB /nologo /subsystem:windows /machine:I386 /out:"C:\Erags\EraABC.exe"

!ELSEIF  "$(CFG)" == "EraABC - Win32 Debug"

# PROP BASE Use_MFC 6
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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_ERAABC" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x422 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SHLWAPI.LIB VERSION.LIB /nologo /subsystem:windows /debug /machine:I386 /out:"R:\Erags\EraABC.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "EraABC - Win32 Release"
# Name "EraABC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ABCList.cpp
# End Source File
# Begin Source File

SOURCE=.\DateFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogEx.cpp
# End Source File
# Begin Source File

SOURCE=.\EraABC.cpp
# End Source File
# Begin Source File

SOURCE=.\EraABC.rc
# End Source File
# Begin Source File

SOURCE=.\EraABCDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\EraABCView.cpp
# End Source File
# Begin Source File

SOURCE=.\FormABC.cpp
# End Source File
# Begin Source File

SOURCE=.\FormBirth.cpp
# End Source File
# Begin Source File

SOURCE=.\FormChange.cpp
# End Source File
# Begin Source File

SOURCE=.\FormDeath.cpp
# End Source File
# Begin Source File

SOURCE=.\FormDivorce.cpp
# End Source File
# Begin Source File

SOURCE=.\FormMarriage.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpMan.cpp
# End Source File
# Begin Source File

SOURCE=.\IniCache.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\RSBirthes.cpp
# End Source File
# Begin Source File

SOURCE=.\RSChanges.cpp
# End Source File
# Begin Source File

SOURCE=.\RSDeathes.cpp
# End Source File
# Begin Source File

SOURCE=.\RSDivorces.cpp
# End Source File
# Begin Source File

SOURCE=.\RSMarriages.cpp
# End Source File
# Begin Source File

SOURCE=.\SetDefDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabView.cpp
# End Source File
# Begin Source File

SOURCE=.\YesNoDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ABCList.h
# End Source File
# Begin Source File

SOURCE=.\DateFunc.h
# End Source File
# Begin Source File

SOURCE=.\DialogEx.h
# End Source File
# Begin Source File

SOURCE=.\EraABC.h
# End Source File
# Begin Source File

SOURCE=.\EraABCDoc.h
# End Source File
# Begin Source File

SOURCE=.\EraABCView.h
# End Source File
# Begin Source File

SOURCE=.\FormABC.h
# End Source File
# Begin Source File

SOURCE=.\FormBirth.h
# End Source File
# Begin Source File

SOURCE=.\FormChange.h
# End Source File
# Begin Source File

SOURCE=.\FormDeath.h
# End Source File
# Begin Source File

SOURCE=.\FormDivorce.h
# End Source File
# Begin Source File

SOURCE=.\FormMarriage.h
# End Source File
# Begin Source File

SOURCE=.\HelpMan.h
# End Source File
# Begin Source File

SOURCE=.\IniCache.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Names.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RSBirthes.h
# End Source File
# Begin Source File

SOURCE=.\RSChanges.h
# End Source File
# Begin Source File

SOURCE=.\RSDeathes.h
# End Source File
# Begin Source File

SOURCE=.\RSDivorces.h
# End Source File
# Begin Source File

SOURCE=.\RSMarriages.h
# End Source File
# Begin Source File

SOURCE=.\SetDefDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabView.h
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# Begin Source File

SOURCE=.\YesNoDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Attention.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Birth.ico
# End Source File
# Begin Source File

SOURCE=.\res\Birth_Gray.ico
# End Source File
# Begin Source File

SOURCE=.\res\BntChange.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BntChangeOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Boy256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\btn_deat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnBirth.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnBirthOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnDeathOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnDivorce.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnDivorceOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnFileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnFirstOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnFolderTree.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnHelpOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnLast.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnLastOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnMarriage.bmp
# End Source File
# Begin Source File

SOURCE=.\res\btnMarriageOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnNext.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnNextOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnPrevOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnRecent.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnRecordDelete.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnRecordDeleteOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnRecordNew.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnRecordNewOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\calendar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Change.ico
# End Source File
# Begin Source File

SOURCE=.\res\Change_Gray.ico
# End Source File
# Begin Source File

SOURCE=.\res\close_app.ico
# End Source File
# Begin Source File

SOURCE=.\res\Death.ico
# End Source File
# Begin Source File

SOURCE=.\res\Death256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Death_Gray.ico
# End Source File
# Begin Source File

SOURCE=.\res\Divorce.ico
# End Source File
# Begin Source File

SOURCE=.\res\Divorce_Gray.ico
# End Source File
# Begin Source File

SOURCE=.\res\EraABC.ico
# End Source File
# Begin Source File

SOURCE=.\res\EraABC.rc2
# End Source File
# Begin Source File

SOURCE=.\res\EraABCDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Fiance256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Fiancee256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\File_Open.bmp
# End Source File
# Begin Source File

SOURCE=.\res\File_Open_Out.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FileNew.ico
# End Source File
# Begin Source File

SOURCE=.\res\FileNewGray.ico
# End Source File
# Begin Source File

SOURCE=.\res\FileOpen.ico
# End Source File
# Begin Source File

SOURCE=.\res\FileOpenGray.ico
# End Source File
# Begin Source File

SOURCE=.\res\FolderTree.ico
# End Source File
# Begin Source File

SOURCE=.\res\Girl256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hdrdown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hdrup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idil_abcsex.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idil_hdr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idil_mes.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_erag.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\Information.ico
# End Source File
# Begin Source File

SOURCE=.\res\Man256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Marriage.ico
# End Source File
# Begin Source File

SOURCE=.\res\Marriage_Gray.ico
# End Source File
# Begin Source File

SOURCE=.\res\NewMenu256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\No.ico
# End Source File
# Begin Source File

SOURCE=.\res\No256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\No256Actived.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StillbornBoy.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StillbornGirl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TabImList.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tfdropcopy.cur
# End Source File
# Begin Source File

SOURCE=.\res\tfnodropcopy.cur
# End Source File
# Begin Source File

SOURCE=.\res\tfnodropmove.cur
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar_Disabled.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar_Hot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar_Normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbars.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Woman256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Yes.ico
# End Source File
# Begin Source File

SOURCE=.\res\Yes256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Yes256Actived.bmp
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\Common\CyrString.cpp

!IF  "$(CFG)" == "EraABC - Win32 Release"

!ELSEIF  "$(CFG)" == "EraABC - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

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

SOURCE=..\Common\EraMessages.h
# End Source File
# Begin Source File

SOURCE=..\Common\FHelpers.cpp
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
# Begin Source File

SOURCE=..\Common\Names.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Names.h
# End Source File
# Begin Source File

SOURCE=..\Common\Version.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Version.h
# End Source File
# End Group
# Begin Group "Controls"

# PROP Default_Filter "cpp;h"
# Begin Group "TCToolBar"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\Controls\TCToolBar\TCImageList.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\TCToolBar\TCToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\TCToolBar\TCToolBar.h
# End Source File
# End Group
# Begin Group "CPPTooltip"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\Controls\CPPTooltip\CeXDib.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\CPPTooltip\PPDrawManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\CPPTooltip\PPHtmlDrawer.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\CPPTooltip\PPTooltip.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\Controls\BaseTabCtrl.cpp

!IF  "$(CFG)" == "EraABC - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "EraABC - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Controls\BkgndCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\BkgndCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Controls\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\BtnST.h
# End Source File
# Begin Source File

SOURCE=..\Controls\EnTabCtrl.cpp

!IF  "$(CFG)" == "EraABC - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "EraABC - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Controls\EraButton.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\erabutton.h
# End Source File
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

SOURCE=..\Controls\EraDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\EraDateTime.h
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

SOURCE=..\Controls\ExtLabel.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ExtLabel.h
# End Source File
# Begin Source File

SOURCE=..\Controls\ExtStatusBarComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ExtStatusBarComboBox.h
# End Source File
# Begin Source File

SOURCE=..\Controls\ExtStatusControlBar.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ExtStatusControlBar.h
# End Source File
# Begin Source File

SOURCE=..\Controls\FileTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\FileTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Controls\FlatHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\FlatHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Controls\FolderTreeBar.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\FolderTreeBar.h
# End Source File
# Begin Source File

SOURCE=..\Controls\ListViewCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ListViewCtrlEx.h
# End Source File
# Begin Source File

SOURCE=..\Controls\MemDC.h
# End Source File
# Begin Source File

SOURCE=..\Controls\MyFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\MyFileDialog.h
# End Source File
# Begin Source File

SOURCE=..\Controls\NewMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\NewMenu.h
# End Source File
# Begin Source File

SOURCE=..\Controls\NewMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\NewMenuBar.h
# End Source File
# Begin Source File

SOURCE=..\Controls\OddButton.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\scbarcf.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\scbarcf.h
# End Source File
# Begin Source File

SOURCE=..\Controls\scbarg.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\scbarg.h
# End Source File
# Begin Source File

SOURCE=..\Controls\ShellType.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ShellType.h
# End Source File
# Begin Source File

SOURCE=..\Controls\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\sizecbar.h
# End Source File
# Begin Source File

SOURCE=..\Controls\TabCtrlBG.cpp

!IF  "$(CFG)" == "EraABC - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "EraABC - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Controls\VisualStylesXP.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\XButtonXP.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\XButtonXP.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
