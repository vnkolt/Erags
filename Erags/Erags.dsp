# Microsoft Developer Studio Project File - Name="Erags" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Erags - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Erags.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Erags.mak" CFG="Erags - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Erags - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Erags - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Erags - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GR /GX /Od /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "OEMRESOURCE" /D "ZLIB_WINAPI" /D "_ERAGS" /D _MFC_VER=0x0601 /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Winmm.lib SHLWAPI.LIB Version.lib /nologo /subsystem:windows /map /machine:I386 /out:"C:\Erags\Erags.exe"
# SUBTRACT LINK32 /incremental:yes /debug

!ELSEIF  "$(CFG)" == "Erags - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "OEMRESOURCE" /D "ZLIB_WINAPI" /D "_ERAGS" /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Winmm.lib SHLWAPI.LIB Version.lib /nologo /subsystem:windows /profile /debug /machine:I386 /nodefaultlib:"LIBC.lib" /out:"R:\Erags\Erags.exe"

!ENDIF 

# Begin Target

# Name "Erags - Win32 Release"
# Name "Erags - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ABCDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddGeoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddRsnDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BanksDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BirthDlgs.cpp
# End Source File
# Begin Source File

SOURCE=.\BirthSurnamesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BlanksDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Caches.cpp
# End Source File
# Begin Source File

SOURCE=.\CantOpenDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckDateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Copy2XLDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DataManager.cpp
# End Source File
# Begin Source File

SOURCE=.\DateFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\DBCauses.cpp
# End Source File
# Begin Source File

SOURCE=.\DBCitizenships.cpp
# End Source File
# Begin Source File

SOURCE=.\DBGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\DBGridDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DBHospitals.cpp
# End Source File
# Begin Source File

SOURCE=.\DBMIAs.cpp
# End Source File
# Begin Source File

SOURCE=.\DBStreets.cpp
# End Source File
# Begin Source File

SOURCE=.\Defaults.cpp
# End Source File
# Begin Source File

SOURCE=.\DepDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Div18.cpp
# End Source File
# Begin Source File

SOURCE=.\Div23.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg27.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg29.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg38.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg43.cpp
# End Source File
# Begin Source File

SOURCE=.\DownloadChecker.cpp
# End Source File
# Begin Source File

SOURCE=.\ElectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EmptyTableDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EnvelopeDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\EraDate.cpp
# End Source File
# Begin Source File

SOURCE=.\EraForm.cpp
# End Source File
# Begin Source File

SOURCE=.\Erags.cpp
# End Source File
# Begin Source File

SOURCE=.\Erags.rc
# End Source File
# Begin Source File

SOURCE=.\EragsDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\EragsView.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrDateReg.cpp
# End Source File
# Begin Source File

SOURCE=.\ExpiredDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtBirthDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtNotice.cpp
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

SOURCE=.\Geography.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoView.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpMan.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyWords.cpp
# End Source File
# Begin Source File

SOURCE=.\Led.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalSearchBar.cpp
# End Source File
# Begin Source File

SOURCE=.\LogThread.cpp
# End Source File
# Begin Source File

SOURCE=.\MainDlgBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Menu.cpp
# End Source File
# Begin Source File

SOURCE=.\MltDocDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MonthList.cpp
# End Source File
# Begin Source File

SOURCE=.\MyPrintDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NamesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Navigate.cpp
# End Source File
# Begin Source File

SOURCE=.\NoteChange.cpp
# End Source File
# Begin Source File

SOURCE=.\NoteDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OODocument.cpp
# End Source File
# Begin Source File

SOURCE=.\OOView.cpp
# End Source File
# Begin Source File

SOURCE=.\PassportsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegFinder.cpp
# End Source File
# Begin Source File

SOURCE=.\RFindDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\RFindFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\RFindView.cpp
# End Source File
# Begin Source File

SOURCE=.\RList.cpp
# End Source File
# Begin Source File

SOURCE=.\RListDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\RNames.cpp
# End Source File
# Begin Source File

SOURCE=.\RSBirthes.cpp
# End Source File
# Begin Source File

SOURCE=.\RSChanges.cpp
# End Source File
# Begin Source File

SOURCE=.\RSChangesDep.cpp
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

SOURCE=.\RTFCnv.cpp
# End Source File
# Begin Source File

SOURCE=.\SecReg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetDefDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SVDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TemplDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeType.cpp
# End Source File
# Begin Source File

SOURCE=.\UnzipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WordCntrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\WordDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\WordView.cpp
# End Source File
# Begin Source File

SOURCE=.\XCnv.cpp
# End Source File
# Begin Source File

SOURCE=.\xMachine.cpp
# End Source File
# Begin Source File

SOURCE=.\YesNoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ZipDBDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ABCDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddGeoDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddRsnDlg.h
# End Source File
# Begin Source File

SOURCE=.\BanksDlg.h
# End Source File
# Begin Source File

SOURCE=.\BirthDlgs.h
# End Source File
# Begin Source File

SOURCE=.\BirthSurnamesDlg.h
# End Source File
# Begin Source File

SOURCE=.\BlanksDlg.h
# End Source File
# Begin Source File

SOURCE=.\Caches.h
# End Source File
# Begin Source File

SOURCE=.\CantOpenDlg.h
# End Source File
# Begin Source File

SOURCE=.\CheckDateDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Copy2XLDlg.h
# End Source File
# Begin Source File

SOURCE=.\DataManager.h
# End Source File
# Begin Source File

SOURCE=.\DateFunc.h
# End Source File
# Begin Source File

SOURCE=.\DBCauses.h
# End Source File
# Begin Source File

SOURCE=.\DBCitizenships.h
# End Source File
# Begin Source File

SOURCE=.\DBGrid.h
# End Source File
# Begin Source File

SOURCE=.\DBGridDlg.h
# End Source File
# Begin Source File

SOURCE=.\DBHospitals.h
# End Source File
# Begin Source File

SOURCE=.\DBMIAs.h
# End Source File
# Begin Source File

SOURCE=.\DBStreets.h
# End Source File
# Begin Source File

SOURCE=.\Defaults.h
# End Source File
# Begin Source File

SOURCE=.\DepDlg.h
# End Source File
# Begin Source File

SOURCE=.\DialogEx.h
# End Source File
# Begin Source File

SOURCE=.\Div18.h
# End Source File
# Begin Source File

SOURCE=.\Div23.h
# End Source File
# Begin Source File

SOURCE=.\Dlg27.h
# End Source File
# Begin Source File

SOURCE=.\Dlg29.h
# End Source File
# Begin Source File

SOURCE=.\Dlg38.h
# End Source File
# Begin Source File

SOURCE=.\Dlg43.h
# End Source File
# Begin Source File

SOURCE=.\DownloadChecker.h
# End Source File
# Begin Source File

SOURCE=.\ElectDlg.h
# End Source File
# Begin Source File

SOURCE=.\EmptyTableDlg.h
# End Source File
# Begin Source File

SOURCE=.\EnvelopeDlg.h
# End Source File
# Begin Source File

SOURCE=..\Common\EraDate.h
# End Source File
# Begin Source File

SOURCE=.\EraForm.h
# End Source File
# Begin Source File

SOURCE=.\Erags.h
# End Source File
# Begin Source File

SOURCE=.\EragsDoc.h
# End Source File
# Begin Source File

SOURCE=.\EragsView.h
# End Source File
# Begin Source File

SOURCE=.\ErrDateReg.h
# End Source File
# Begin Source File

SOURCE=.\ExpiredDlg.h
# End Source File
# Begin Source File

SOURCE=.\ExtBirthDlg.h
# End Source File
# Begin Source File

SOURCE=.\ExtNotice.h
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

SOURCE=.\Geography.h
# End Source File
# Begin Source File

SOURCE=.\GeoView.h
# End Source File
# Begin Source File

SOURCE=.\HelpMan.h
# End Source File
# Begin Source File

SOURCE=.\KeyWords.h
# End Source File
# Begin Source File

SOURCE=.\Led.h
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\LoadDlg.h
# End Source File
# Begin Source File

SOURCE=.\LocalSearchBar.h
# End Source File
# Begin Source File

SOURCE=.\LogThread.h
# End Source File
# Begin Source File

SOURCE=.\MainDlgBar.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Menu.h
# End Source File
# Begin Source File

SOURCE=.\MltDocDlg.h
# End Source File
# Begin Source File

SOURCE=.\MonthList.h
# End Source File
# Begin Source File

SOURCE=.\MyPrintDlg.h
# End Source File
# Begin Source File

SOURCE=.\NamesDlg.h
# End Source File
# Begin Source File

SOURCE=.\Navigate.h
# End Source File
# Begin Source File

SOURCE=.\NoteChange.h
# End Source File
# Begin Source File

SOURCE=.\NoteDlg.h
# End Source File
# Begin Source File

SOURCE=.\OODoc.h
# End Source File
# Begin Source File

SOURCE=.\OODocument.h
# End Source File
# Begin Source File

SOURCE=.\OOView.h
# End Source File
# Begin Source File

SOURCE=.\PassportsDlg.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.h
# End Source File
# Begin Source File

SOURCE=.\properties.h
# End Source File
# Begin Source File

SOURCE=.\property.h
# End Source File
# Begin Source File

SOURCE=.\RegDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegFinder.h
# End Source File
# Begin Source File

SOURCE=.\Registrars.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RFindDoc.h
# End Source File
# Begin Source File

SOURCE=.\RFindFrm.h
# End Source File
# Begin Source File

SOURCE=.\RFindView.h
# End Source File
# Begin Source File

SOURCE=.\RList.h
# End Source File
# Begin Source File

SOURCE=.\RListDoc.h
# End Source File
# Begin Source File

SOURCE=.\RNames.h
# End Source File
# Begin Source File

SOURCE=.\RSBirthes.h
# End Source File
# Begin Source File

SOURCE=.\RSChanges.h
# End Source File
# Begin Source File

SOURCE=.\RSChangesDep.h
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

SOURCE=.\RTFCnv.h
# End Source File
# Begin Source File

SOURCE=.\SecReg.h
# End Source File
# Begin Source File

SOURCE=.\SetDefDlg.h
# End Source File
# Begin Source File

SOURCE=.\SettingsDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SVDlg.h
# End Source File
# Begin Source File

SOURCE=.\TemplDlg.h
# End Source File
# Begin Source File

SOURCE=.\TreeType.h
# End Source File
# Begin Source File

SOURCE=.\UnzipDlg.h
# End Source File
# Begin Source File

SOURCE=.\WordCntrItem.h
# End Source File
# Begin Source File

SOURCE=.\WordDocument.h
# End Source File
# Begin Source File

SOURCE=.\WordView.h
# End Source File
# Begin Source File

SOURCE=.\XCnv.h
# End Source File
# Begin Source File

SOURCE=.\xMachine.h
# End Source File
# Begin Source File

SOURCE=.\YesNoDlg.h
# End Source File
# Begin Source File

SOURCE=.\ZipDBDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\abc.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\ActA1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\ActA2.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\ActB.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Actions.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Actions1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Actions2.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Actions256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Actions3.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Actions4.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Actions5.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Actions6.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Actions7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\acts.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Attention.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Birth.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Birth.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Birth256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BntChange.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BntChangeOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Boy256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\browser.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BrowserTB.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\btn_deat.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnABC.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnABCOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnBirth.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnBirthOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnCityHall.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnCityHallOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnDeath.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnDeathOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnDivorce.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnDivorceOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnDown.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnEqu.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnExtNotes.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnExtNotesOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnFileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnFindIn.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnFindOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnFindOutOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnFirstOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnFolderTree.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnGeo.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnGeoOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnHelpOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnLast.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnLastOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnLaws.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnLawsOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnLeft.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnMarriage.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\btnMarriageOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnNext.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnNextOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnOpenRecord.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnPartial.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnPrevOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnPrint.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnPrintOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnRecent.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnRecordDelete.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnRecordDeleteOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnRecordNew.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnRecordNewOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnRedCross.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnRedCrossOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnRight.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnSaveAs.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnSaveAsOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnSetColors.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnSWriter.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnSWriterOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnTeplates.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnTeplatesOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnUAH.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnUAHOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnUkraine.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnUkraineOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnUp.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnWord.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BtnWordOut.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\calendar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Change.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Change.ico
# End Source File
# Begin Source File

SOURCE=.\Res\CheckBoxIL.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\CityType1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\CityType2.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\close_app.ico
# End Source File
# Begin Source File

SOURCE=.\Res\cntr_inp.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\coldtool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\collate1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\CommonSettings.ico
# End Source File
# Begin Source File

SOURCE=.\res\Country.ico
# End Source File
# Begin Source File

SOURCE=.\Res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\Res\cur00002.cur
# End Source File
# Begin Source File

SOURCE=.\Res\cur00004.cur
# End Source File
# Begin Source File

SOURCE=.\res\datagrid.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Death.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Death.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Death256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Divorce.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Divorce.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Dragmove.cur
# End Source File
# Begin Source File

SOURCE=.\Res\drop_mov.cur
# End Source File
# Begin Source File

SOURCE=.\RES\Erags.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Erags.rc2
# End Source File
# Begin Source File

SOURCE=.\RES\EragsDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\EragsGrp.ico
# End Source File
# Begin Source File

SOURCE=.\res\Father.ico
# End Source File
# Begin Source File

SOURCE=.\res\Female.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Fiance256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Fiancee256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\File_Open.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\File_Open_Out.bmp
# End Source File
# Begin Source File

SOURCE=.\res\first.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\FolderTree.ico
# End Source File
# Begin Source File

SOURCE=.\Res\FontIL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\forms.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\FoundList.bmp
# End Source File
# Begin Source File

SOURCE=.\res\geography.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Girl256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\Res\hdrdown.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\hdrup.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\hottoolb.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\idil_abcsex.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\idil_acbsex.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\idil_hdr.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\idil_mes.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\idil_zip.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_data.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_erag.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_form.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_repo.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_sear.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_tabl.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_tree.cur
# End Source File
# Begin Source File

SOURCE=.\Res\idr_word.ico
# End Source File
# Begin Source File

SOURCE=.\Res\il_zip.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\imlist.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Information.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Keys.ico
# End Source File
# Begin Source File

SOURCE=.\res\last.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Leds.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\maintool.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\maintoolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\MainToolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Male.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Man256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\MarCitizen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Marrige.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Marrige.ico
# End Source File
# Begin Source File

SOURCE=.\Res\MCross.ico
# End Source File
# Begin Source File

SOURCE=.\Res\medics.ico
# End Source File
# Begin Source File

SOURCE=.\res\Mlt.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MltDn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MltFocus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\navigate.bmp
# End Source File
# Begin Source File

SOURCE=.\res\new.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\NewMenu256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\newnames.ico
# End Source File
# Begin Source File

SOURCE=.\res\next.bmp
# End Source File
# Begin Source File

SOURCE=.\res\No.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\No.ico
# End Source File
# Begin Source File

SOURCE=.\Res\No256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NoDn.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\NoDn256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\nodrop.cur
# End Source File
# Begin Source File

SOURCE=.\res\NoFocus.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\NoFocus256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\open.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Plus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PlusDn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PlusFocus.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\post.bmp
# End Source File
# Begin Source File

SOURCE=.\res\prev.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\printmenu.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\printmenuDivorce.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\RadioIL.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\record_new.ico
# End Source File
# Begin Source File

SOURCE=.\Res\RecordDelete.ico
# End Source File
# Begin Source File

SOURCE=.\Res\RecordEdit.ico
# End Source File
# Begin Source File

SOURCE=.\Res\RecordNew.ico
# End Source File
# Begin Source File

SOURCE=.\res\reportfr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\req.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\RFind.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\RFind.ico
# End Source File
# Begin Source File

SOURCE=.\Res\rfolders.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\rfolders_tc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SANTAFE.ICO
# End Source File
# Begin Source File

SOURCE=.\Res\SetBirth.ico
# End Source File
# Begin Source File

SOURCE=.\Res\SetChange.ico
# End Source File
# Begin Source File

SOURCE=.\Res\SetColors.ico
# End Source File
# Begin Source File

SOURCE=.\Res\SetDeath.ico
# End Source File
# Begin Source File

SOURCE=.\Res\SetDivorce.ico
# End Source File
# Begin Source File

SOURCE=.\Res\SetMarriage.ico
# End Source File
# Begin Source File

SOURCE=.\Res\SetOffice.ico
# End Source File
# Begin Source File

SOURCE=.\Res\SignFeale.ico
# End Source File
# Begin Source File

SOURCE=.\Res\SignMale.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Stamp.ico
# End Source File
# Begin Source File

SOURCE=.\Res\tfdropcopy.cur
# End Source File
# Begin Source File

SOURCE=.\Res\tfnodropcopy.cur
# End Source File
# Begin Source File

SOURCE=.\Res\tfnodropmove.cur
# End Source File
# Begin Source File

SOURCE=.\RES\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Toolbar_Disabled.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Toolbar_Hot.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Toolbar_Normal.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Toolbars.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ukraine.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Flags\Ukraine.ico
# End Source File
# Begin Source File

SOURCE=.\Res\up.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Users.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Watch.ico
# End Source File
# Begin Source File

SOURCE=.\Res\WCross.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Woman256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\WomanCitizen.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\word8.ico
# End Source File
# Begin Source File

SOURCE=.\Res\word9.ico
# End Source File
# Begin Source File

SOURCE=.\res\Yes.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Yes.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Yes256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\YesDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\YesDn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\YesFocus.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\YesFocus256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Zip.ico
# End Source File
# Begin Source File

SOURCE=.\Res\zipsort.bmp
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\Common\Crypto.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Crypto.h
# End Source File
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

SOURCE=..\Common\DaoErr.cpp
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

SOURCE=..\Common\EraMessages.h
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
# Begin Source File

SOURCE=..\Common\Names.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Names.h
# End Source File
# Begin Source File

SOURCE=..\Common\RDF32.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\RDF32.h
# End Source File
# Begin Source File

SOURCE=..\Common\Sections.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Sections.h
# End Source File
# Begin Source File

SOURCE=..\Common\StdAfx.h
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
# Begin Group "GridCtrl"

# PROP Default_Filter "cpp;h"
# Begin Group "CellTypes"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\Controls\GridCtrl\CellTypes\GridCellCheck.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\CellTypes\GridCellCheck.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\CellTypes\GridCellCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\CellTypes\GridCellCombo.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\CellTypes\GridCellDate.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\CellTypes\GridCellDate.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\CellTypes\GridCellDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\CellTypes\GridCellDateTime.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\CellTypes\GridURLCell.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\CellTypes\GridURLCell.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\CellTypes\StdAfx.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Controls\GridCtrl\CellRange.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\GridCell.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\GridCell.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\GridCellBase.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\GridCellBase.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\InPlaceDateEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\InPlaceDateEdit.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\MemDC.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\TitleTip.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\GridCtrl\TitleTip.h
# End Source File
# End Group
# Begin Group "CPPTooltip"

# PROP Default_Filter "cpp;h"
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
# Begin Source File

SOURCE=..\Controls\CPPTooltip\StdAfx.h
# End Source File
# End Group
# Begin Group "TCToolBar"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\Controls\TCToolBar\TCImageList.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\TCToolBar\TCImageList.h
# End Source File
# Begin Source File

SOURCE=..\Controls\TCToolBar\TCToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\TCToolBar\TCToolBar.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Controls\AutoRichEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\AutoRichEditCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Controls\BaseTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\BaseTabCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Controls\BkgndCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\BkgndCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Controls\BrowseForFolder.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\BrowseForFolder.h
# End Source File
# Begin Source File

SOURCE=..\Controls\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ColourPicker.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ColourPicker.h
# End Source File
# Begin Source File

SOURCE=..\Controls\ColourPopup.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ColourPopup.h
# End Source File
# Begin Source File

SOURCE=..\Controls\EnTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\EnTabCtrl.h
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

SOURCE=..\Controls\EraEdit.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=..\Controls\EraEdit.h
# End Source File
# Begin Source File

SOURCE=..\Controls\EraLabel.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\EraLabel.h
# End Source File
# Begin Source File

SOURCE=..\Controls\EraMonthCalCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\EraMonthCalCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Controls\ExtLabel.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ExtLabel.h
# End Source File
# Begin Source File

SOURCE=..\Controls\ExtStatusControlBar.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\FileTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\FileTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Controls\FolderTreeBar.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\FolderTreeBar.h
# End Source File
# Begin Source File

SOURCE=..\Controls\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\HyperLink.h
# End Source File
# Begin Source File

SOURCE=..\Controls\KMComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\KMComboBox.h
# End Source File
# Begin Source File

SOURCE=..\Controls\Label.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\Label.h
# End Source File
# Begin Source File

SOURCE=..\Controls\ListCtrlStyled.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ListCtrlStyled.h
# End Source File
# Begin Source File

SOURCE=..\Controls\ListViewCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ListViewCtrlEx.h
# End Source File
# Begin Source File

SOURCE=..\Controls\MyBtnST.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\MyBtnST.h
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

SOURCE=..\Controls\NewStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\NewStatusBar.h
# End Source File
# Begin Source File

SOURCE=..\Controls\OddButton.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\OddButton.h
# End Source File
# Begin Source File

SOURCE=..\Controls\ProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ProgressBar.h
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

SOURCE=..\Controls\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\Controls\TabCtrlBG.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\TabCtrlBG.h
# End Source File
# Begin Source File

SOURCE=..\Controls\TextProgressCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\TextProgressCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Controls\ThemeHelperST.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\ThemeHelperST.h
# End Source File
# Begin Source File

SOURCE=..\Controls\TreeListView.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\TreeListView.h
# End Source File
# Begin Source File

SOURCE=..\Controls\VisualStylesXP.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\VisualStylesXP.h
# End Source File
# Begin Source File

SOURCE=..\Controls\XBrowseForFolder.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\XBrowseForFolder.h
# End Source File
# Begin Source File

SOURCE=..\Controls\XButtonXP.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\XButtonXP.h
# End Source File
# Begin Source File

SOURCE=..\Controls\XFontDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\Controls\XFontDialog.h
# End Source File
# End Group
# Begin Group "MSO"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=..\MSO\excel8.cpp
# End Source File
# Begin Source File

SOURCE=..\MSO\excel8.h
# End Source File
# Begin Source File

SOURCE=..\MSO\msoEra.cpp
# End Source File
# Begin Source File

SOURCE=..\MSO\msoEra.h
# End Source File
# Begin Source File

SOURCE=..\MSO\msword8.cpp
# End Source File
# Begin Source File

SOURCE=..\MSO\msword8.h
# End Source File
# End Group
# Begin Group "ZipArchive"

# PROP Default_Filter "cpp;h"
# Begin Group "ZLib"

# PROP Default_Filter "h;c"
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

SOURCE=..\ZipArchive\ZLib\minigzip.c
# SUBTRACT CPP /YX /Yc /Yu
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
# Begin Source File

SOURCE=.\app.manifest
# End Source File
# Begin Source File

SOURCE=.\Res\cantopen.rtf
# End Source File
# Begin Source File

SOURCE=.\Res\cantopen.txt
# End Source File
# Begin Source File

SOURCE=.\Erags.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\Erags.reg
# End Source File
# Begin Source File

SOURCE=.\res\Waves\InSnd.wav
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Res\RegText.rtf
# End Source File
# Begin Source File

SOURCE=.\Res\RegTextCmd.rtf
# End Source File
# Begin Source File

SOURCE=.\Res\RTFEmpty.rtf
# End Source File
# Begin Source File

SOURCE=.\res\Waves\Whoosh.wav
# End Source File
# Begin Source File

SOURCE=..\ImpExp.lib
# End Source File
# Begin Source File

SOURCE=..\zlib.lib
# End Source File
# End Target
# End Project
# Section Erags : {CDE57A52-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CSelBookmarks
# 	2:10:HeaderFile:selbookmarks.h
# 	2:8:ImplFile:selbookmarks.cpp
# End Section
# Section Erags : {67397AA3-7FB1-11D0-B148-00A0C922E820}
# 	2:21:DefaultSinkHeaderFile:datagrid\adodc.h
# 	2:16:DefaultSinkClass:CAdodc
# End Section
# Section Erags : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section Erags : {0000054F-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:C_Recordset
# 	2:10:HeaderFile:_recordset.h
# 	2:8:ImplFile:_recordset.cpp
# End Section
# Section Erags : {00000503-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CProperty
# 	2:10:HeaderFile:property.h
# 	2:8:ImplFile:property.cpp
# End Section
# Section Erags : {CDE57A41-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CDataGrid
# 	2:10:HeaderFile:datagrid\datagrid.h
# 	2:8:ImplFile:datagrid\datagrid.cpp
# End Section
# Section Erags : {CDE57A50-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CColumns
# 	2:10:HeaderFile:columns.h
# 	2:8:ImplFile:columns.cpp
# End Section
# Section Erags : {CDE57A54-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CSplit
# 	2:10:HeaderFile:split.h
# 	2:8:ImplFile:split.cpp
# End Section
# Section Erags : {E675F3F0-91B5-11D0-9484-00A0C91110ED}
# 	2:5:Class:CDataFormatDisp
# 	2:10:HeaderFile:dataformatdisp.h
# 	2:8:ImplFile:dataformatdisp.cpp
# End Section
# Section Erags : {0000054D-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CFields
# 	2:10:HeaderFile:fields.h
# 	2:8:ImplFile:fields.cpp
# End Section
# Section Erags : {99FF4676-FFC3-11D0-BD02-00C04FC2FB86}
# 	2:5:Class:CStdDataFormatsDisp
# 	2:10:HeaderFile:stddataformatsdisp.h
# 	2:8:ImplFile:stddataformatsdisp.cpp
# End Section
# Section Erags : {CDE57A4F-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CColumn
# 	2:10:HeaderFile:column.h
# 	2:8:ImplFile:column.cpp
# End Section
# Section Erags : {47A738F1-7FAF-11D0-B148-00A0C922E820}
# 	2:5:Class:CAdodc
# 	2:10:HeaderFile:datagrid\adodc.h
# 	2:8:ImplFile:datagrid\adodc.cpp
# End Section
# Section Erags : {CDE57A43-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:21:DefaultSinkHeaderFile:datagrid\datagrid.h
# 	2:16:DefaultSinkClass:CDataGrid
# End Section
# Section Erags : {0000054C-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CField
# 	2:10:HeaderFile:field.h
# 	2:8:ImplFile:field.cpp
# End Section
# Section Erags : {CDE57A53-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CSplits
# 	2:10:HeaderFile:splits.h
# 	2:8:ImplFile:splits.cpp
# End Section
# Section Erags : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section Erags : {00000504-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CProperties
# 	2:10:HeaderFile:properties.h
# 	2:8:ImplFile:properties.cpp
# End Section
