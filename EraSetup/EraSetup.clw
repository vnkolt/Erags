; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCDMenu
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "EraSetup.h"

ClassCount=10
Class1=CEraSetupApp
Class2=CEraSetupDlg
Class3=CAboutDlg

ResourceCount=22
Resource1=IDD_UNZIPDLG (Russian)
Resource2=IDR_MAINFRAME
Resource3=IDD_WELCOME (Russian)
Resource4=IDD_ERASETUP_DIALOG (English (U.S.))
Resource5=IDD_WELCOME
Resource6=IDD_WIZARD (Russian)
Resource7=IDD_AGREEMENT (Russian)
Class4=CWelcomePage
Class5=CAgreementPage
Resource8=IDD_ERASETUP_DIALOG (Russian)
Resource9=IDD_UNZIPDLG
Resource10=IDD_OVERWRITE
Resource11=IDD_FINISH
Class6=CEraPathPage
Resource12=IDD_PROGRESS (Russian)
Class7=CProgressPage
Resource13=IDD_ERAPATH (Russian)
Resource14=IDD_ERASETUP_DIALOG
Class8=CFinishPage
Resource15=IDD_MENU
Resource16=IDD_ERAPATH
Resource17=IDD_FINISH (Russian)
Resource18=IDD_OVERWRITE (Russian)
Resource19=IDD_AGREEMENT
Resource20=IDD_ABOUTBOX
Class9=CUnzipDlg
Resource21=IDD_PROGRESS
Class10=CCDMenu
Resource22=IDD_ABOUTBOX (English (U.S.))

[CLS:CEraSetupApp]
Type=0
HeaderFile=EraSetup.h
ImplementationFile=EraSetup.cpp
Filter=N
LastObject=CEraSetupApp

[CLS:CEraSetupDlg]
Type=0
HeaderFile=EraSetupDlg.h
ImplementationFile=EraSetupDlg.cpp
Filter=D
LastObject=CEraSetupDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=EraSetupDlg.h
ImplementationFile=EraSetupDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ERASETUP_DIALOG (English (U.S.))]
Type=1
Class=CEraSetupDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WIZARD (Russian)]
Type=1
Class=?
ControlCount=5
Control1=ID_WIZNEXT,button,1342242816
Control2=ID_WIZBACK,button,1342242816
Control3=IDCANCEL,button,1342242816
Control4=ID_WIZFINISH,button,1342242816
Control5=IDC_SHEETRECT,static,1342177298

[DLG:IDD_AGREEMENT (Russian)]
Type=1
Class=CAgreementPage
ControlCount=2
Control1=IDC_AGREE,button,1342242819
Control2=IDC_AGREEMENT,RICHEDIT,1352730628

[DLG:IDD_WELCOME (Russian)]
Type=1
Class=CWelcomePage
ControlCount=10
Control1=IDC_WELCOME,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342177283
Control7=IDC_STATIC,static,1342177283
Control8=IDC_STATIC,static,1342177283
Control9=IDC_RADIO_UKR,button,1342180361
Control10=IDC_RADIO_RUS,button,1342180361

[CLS:CWelcomePage]
Type=0
HeaderFile=WelcomePage.h
ImplementationFile=WelcomePage.cpp
BaseClass=CNewWizPage
Filter=D
LastObject=IDC_RADIO_RUS

[DLG:IDD_ERASETUP_DIALOG (Russian)]
Type=1
Class=CEraSetupDlg
ControlCount=7
Control1=ID_WIZNEXT,button,1342242816
Control2=ID_WIZBACK,button,1342242816
Control3=ID_WIZFINISH,button,1342242816
Control4=IDC_SHEETRECT,static,1073741842
Control5=IDC_SHEETRECT_VISIBLE,static,1342177298
Control6=IDC_STATIC,static,1342177294
Control7=ID_HELP,button,1342242816

[CLS:CAgreementPage]
Type=0
HeaderFile=AgreementPage.h
ImplementationFile=AgreementPage.cpp
BaseClass=CNewWizPage
Filter=D
LastObject=CAgreementPage

[DLG:IDD_AGREEMENT]
Type=1
Class=CAgreementPage
ControlCount=2
Control1=IDC_AGREE,button,1342242819
Control2=IDC_AGREEMENT,RICHEDIT,1352730628

[DLG:IDD_WELCOME]
Type=1
Class=CWelcomePage
ControlCount=10
Control1=IDC_WELCOME,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342177283
Control7=IDC_STATIC,static,1342177283
Control8=IDC_STATIC,static,1342177283
Control9=IDC_RADIO_UKR,button,1342180361
Control10=IDC_RADIO_RUS,button,1342180361

[DLG:IDD_ERASETUP_DIALOG]
Type=1
Class=CEraSetupDlg
ControlCount=7
Control1=ID_WIZNEXT,button,1342242816
Control2=ID_WIZBACK,button,1342242816
Control3=ID_WIZFINISH,button,1342242816
Control4=IDC_SHEETRECT,static,1073741842
Control5=IDC_SHEETRECT_VISIBLE,static,1342177298
Control6=IDC_STATIC,static,1342177294
Control7=ID_HELP,button,1342242816

[DLG:IDD_ERAPATH (Russian)]
Type=1
Class=CEraPathPage
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342177283
Control3=IDC_ERAPATH,edit,1350631552
Control4=IDC_SELPATH,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ERAGROUP,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_RADIO1,button,1342177289
Control9=IDC_RADIO2,button,1342177289
Control10=IDC_FREE_SPACE,static,1342308352
Control11=IDC_CHECK_LAWS,button,1342242819

[CLS:CEraPathPage]
Type=0
HeaderFile=EraPathPage.h
ImplementationFile=EraPathPage.cpp
BaseClass=CNewWizPage
Filter=D
LastObject=IDC_SELPATH

[DLG:IDD_PROGRESS (Russian)]
Type=1
Class=CProgressPage
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_PROGRESS1,msctls_progress32,1350565888
Control3=IDC_DESTFILENAME,static,1350696960
Control4=IDC_LIST1,SysListView32,1350631437
Control5=IDC_TAB,SysTabControl32,1342177280

[CLS:CProgressPage]
Type=0
HeaderFile=ProgressPage.h
ImplementationFile=ProgressPage.cpp
BaseClass=CNewWizPage
Filter=D
LastObject=CProgressPage

[DLG:IDD_OVERWRITE (Russian)]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDYES,button,1342242816
Control3=IDALL,button,1342242816
Control4=IDNO,button,1342242816
Control5=IDC_MSG1,static,1342308352
Control6=IDC_MSG2,static,1342308352

[DLG:IDD_FINISH (Russian)]
Type=1
Class=CFinishPage
ControlCount=10
Control1=IDC_TITLE,static,1342308352
Control2=IDC_STATIC,static,1342177283
Control3=IDC_FINMSG,RICHEDIT,1352730884
Control4=IDOK,button,1342242816
Control5=IDC_STATIC,static,1342177283
Control6=IDC_STATIC,static,1342177283
Control7=IDC_OPEN_UKR,button,1342242819
Control8=IDC_OPEN_RUS,button,1342242819
Control9=IDC_STATIC,static,1342177283
Control10=IDC_OPEN_ERAGS,button,1342242819

[CLS:CFinishPage]
Type=0
HeaderFile=FinishPage.h
ImplementationFile=FinishPage.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_ERAPATH]
Type=1
Class=CEraPathPage
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342177283
Control3=IDC_ERAPATH,edit,1350631552
Control4=IDC_SELPATH,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ERAGROUP,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_RADIO1,button,1342177289
Control9=IDC_RADIO2,button,1342177289
Control10=IDC_FREE_SPACE,static,1342308352

[DLG:IDD_PROGRESS]
Type=1
Class=CProgressPage
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_PROGRESS1,msctls_progress32,1350565888
Control3=IDC_DESTFILENAME,static,1350696960
Control4=IDC_LIST1,SysListView32,1350631437
Control5=IDC_TAB,SysTabControl32,1342177280
Control6=IDC_SAVE,button,1342242819
Control7=IDC_SELECT_ALL,button,1342242819

[DLG:IDD_OVERWRITE]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDYES,button,1342242816
Control3=IDALL,button,1342242816
Control4=IDNO,button,1342242816
Control5=IDC_MSG1,static,1342308352
Control6=IDC_MSG2,static,1342308352

[DLG:IDD_FINISH]
Type=1
Class=CFinishPage
ControlCount=10
Control1=IDC_TITLE,static,1342308352
Control2=IDC_STATIC,static,1342177283
Control3=IDC_FINMSG,RICHEDIT,1352730884
Control4=IDOK,button,1342242816
Control5=IDC_STATIC,static,1342177283
Control6=IDC_STATIC,static,1342177283
Control7=IDC_OPEN_UKR,button,1342242819
Control8=IDC_OPEN_RUS,button,1342242819
Control9=IDC_STATIC,static,1342177283
Control10=IDC_OPEN_ERAGS,button,1342242819

[DLG:IDD_UNZIPDLG]
Type=1
Class=CUnzipDlg
ControlCount=1
Control1=IDC_PROGRESS,msctls_progress32,1350565888

[DLG:IDD_UNZIPDLG (Russian)]
Type=1
Class=CUnzipDlg
ControlCount=1
Control1=IDC_PROGRESS,msctls_progress32,1350565888

[CLS:CUnzipDlg]
Type=0
HeaderFile=UnzipDlg.h
ImplementationFile=UnzipDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CUnzipDlg

[DLG:IDD_MENU]
Type=1
Class=CCDMenu
ControlCount=5
Control1=65535,static,1342177283
Control2=IDC_DAO,button,1342242816
Control3=IDC_ERAGS,button,1342242816
Control4=IDC_TEMPLATES,button,1342242816
Control5=IDC_UNINSTALL,button,1342242816

[CLS:CCDMenu]
Type=0
HeaderFile=CDMenu.h
ImplementationFile=CDMenu.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCDMenu

