; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=6
Class1=CImpExpApp
LastClass=CImpExpApp
NewFileInclude2=#include "ImpExp.h"
ResourceCount=16
NewFileInclude1=#include "stdafx.h"
Class2=CImportDlg
LastTemplate=CDialog
Resource1=IDD_EXP_BIRTH
Class3=CImportProgessDlg
Resource2=IDD_IMPORT
Resource3=IDD_IMPORT_PROGESS (Russian)
Resource4=IDD_EXPORT_DIALOG (Russian)
Resource5=IDD_REPAIR
Resource6=IDD_REPAIR (Russian)
Resource7=IDD_IMPORT_PROGESS
Resource8=IDD_EXPORT_TYPES (Russian)
Resource9=IDD_DEFBIRTH (Russian)
Class4=CExpTypesPage
Resource10=IDD_IMPORT (Russian)
Class5=CExpBirth
Resource11=IDD_EXP_BIRTH (Russian)
Class6=CExpProgressDlg
Resource12=IDD_EXPORT_PROGRESS (Russian)
Resource13=IDD_DEFBIRTH
Resource14=IDD_EXPORT_DIALOG
Resource15=IDD_EXPORT_TYPES
Resource16=IDD_EXPORT_PROGRESS

[CLS:CImpExpApp]
Type=0
HeaderFile=ImpExp.h
ImplementationFile=ImpExp.cpp
Filter=N
LastObject=CImpExpApp
BaseClass=CWinApp
VirtualFilter=AC

[DLG:IDD_IMPORT]
Type=1
Class=CImportDlg
ControlCount=17
Control1=IDC_OPEN_FILE_DLG,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_SOURCE_FILE,edit,1350633600
Control4=IDC_FORYEAR,button,1476460547
Control5=IDC_NOEMPY,button,1476460547
Control6=IDC_NOEXIST,button,1476460547
Control7=IDOK,button,1476460545
Control8=IDC_IMPORT_BIRTH,button,1476460547
Control9=IDC_STATIC,static,1342179331
Control10=IDC_IMPORT_MARRIAGE,button,1476460547
Control11=IDC_STATIC,static,1342179331
Control12=IDC_IMPORT_DIVORCE,button,1476460547
Control13=IDC_STATIC,static,1342179331
Control14=IDC_IMPORT_DEATH,button,1476460547
Control15=IDC_STATIC,static,1342179331
Control16=IDC_IMPORT_CHANGE,button,1476460547
Control17=IDC_STATIC,static,1342179331

[CLS:CImportDlg]
Type=0
HeaderFile=ImportDlg.h
ImplementationFile=ImportDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CImportDlg

[DLG:IDD_IMPORT_PROGESS]
Type=1
Class=CImportProgessDlg
ControlCount=4
Control1=IDOK,button,1476460545
Control2=IDC_MESSAGE_LIST,SysListView32,1350631425
Control3=IDC_TOTAL_PROGRESS,msctls_progress32,1342177281
Control4=IDC_INFOBOX,static,1342308864

[CLS:CImportProgessDlg]
Type=0
HeaderFile=ImportProgessDlg.h
ImplementationFile=ImportProgessDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CImportProgessDlg

[DLG:IDD_REPAIR (Russian)]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_RAPAIR,edit,1350633540
Control4=IDC_LBL_WHAT,static,1342308352
Control5=IDC_WHAT,edit,1350631552
Control6=IDC_STATIC,static,1342177283
Control7=IDC_NOMORE,button,1342242819

[DLG:IDD_IMPORT (Russian)]
Type=1
Class=CImportDlg
ControlCount=17
Control1=IDC_OPEN_FILE_DLG,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_SOURCE_FILE,edit,1350633600
Control4=IDC_FORYEAR,button,1476460547
Control5=IDC_NOEMPY,button,1476460547
Control6=IDC_NOEXIST,button,1476460547
Control7=IDOK,button,1476460545
Control8=IDC_IMPORT_BIRTH,button,1476460547
Control9=IDC_STATIC,static,1342179331
Control10=IDC_IMPORT_MARRIAGE,button,1476460547
Control11=IDC_STATIC,static,1342179331
Control12=IDC_IMPORT_DIVORCE,button,1476460547
Control13=IDC_STATIC,static,1342179331
Control14=IDC_IMPORT_DEATH,button,1476460547
Control15=IDC_STATIC,static,1342179331
Control16=IDC_IMPORT_CHANGE,button,1476460547
Control17=IDC_STATIC,static,1342179331

[DLG:IDD_IMPORT_PROGESS (Russian)]
Type=1
Class=CImportProgessDlg
ControlCount=4
Control1=IDOK,button,1476460545
Control2=IDC_MESSAGE_LIST,SysListView32,1350631425
Control3=IDC_TOTAL_PROGRESS,msctls_progress32,1342177281
Control4=IDC_INFOBOX,static,1342308864

[DLG:IDD_DEFBIRTH (Russian)]
Type=1
Class=?
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864
Control5=IDC_STATIC,static,1342308864
Control6=IDC_STATIC,static,1342308864
Control7=IDC_COUNTRY,edit,1350631552
Control8=IDC_REGION,edit,1350631552
Control9=IDC_CITY,edit,1350631552
Control10=IDC_DISTRICT,edit,1350631552
Control11=IDC_STATIC,static,1342177283
Control12=IDC_EDIT1,edit,1350633476

[DLG:IDD_REPAIR]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_RAPAIR,edit,1350633540
Control4=IDC_LBL_WHAT,static,1342308352
Control5=IDC_WHAT,edit,1350631552
Control6=IDC_STATIC,static,1342177283
Control7=IDC_NOMORE,button,1342242819

[DLG:IDD_DEFBIRTH]
Type=1
Class=?
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864
Control5=IDC_STATIC,static,1342308864
Control6=IDC_STATIC,static,1342308864
Control7=IDC_COUNTRY,edit,1350631552
Control8=IDC_REGION,edit,1350631552
Control9=IDC_CITY,edit,1350631552
Control10=IDC_DISTRICT,edit,1350631552
Control11=IDC_STATIC,static,1342177283
Control12=IDC_EDIT1,edit,1350633476

[DLG:IDD_EXPORT_DIALOG (Russian)]
Type=1
Class=?
ControlCount=6
Control1=ID_WIZNEXT,button,1342242816
Control2=ID_WIZBACK,button,1342242816
Control3=ID_WIZFINISH,button,1476460544
Control4=IDC_SHEETRECT,static,1073741842
Control5=IDC_SHEETRECT_VISIBLE,static,1342177298
Control6=ID_HELP,button,1342242816

[DLG:IDD_EXPORT_TYPES (Russian)]
Type=1
Class=CExpTypesPage
ControlCount=10
Control1=IDC_CHECK_XLS,button,1342242819
Control2=IDC_CHECK_RTF,button,1342242819
Control3=IDC_CHECK_HTM,button,1342242819
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_CHECK_BIRH,button,1342242819
Control7=IDC_CHECK_MARRIAGE,button,1342242819
Control8=IDC_CHECK_DIVORCE,button,1342242819
Control9=IDC_CHECK_CHANGE,button,1342242819
Control10=IDC_CHECK_DEATH,button,1342242819

[CLS:CExpTypesPage]
Type=0
HeaderFile=ExportDlgs.h
ImplementationFile=ExportDlgs.cpp
BaseClass=CNewWizPage
Filter=D
LastObject=IDC_CHECK_XLS

[CLS:CExpBirth]
Type=0
HeaderFile=ExportDlgs.h
ImplementationFile=ExportDlgs.cpp
BaseClass=CNewWizPage
Filter=D
VirtualFilter=dWC
LastObject=CExpBirth

[DLG:IDD_EXP_BIRTH (Russian)]
Type=1
Class=CExpBirth
ControlCount=10
Control1=IDC_NO_EXPORT,SysListView32,1350631425
Control2=IDC_DO_EXPORT,SysListView32,1350631425
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308864
Control5=IDC_STATIC,static,1342308864
Control6=IDC_ADD,button,1342242816
Control7=IDC_ADD_ALL,button,1342242816
Control8=IDC_SUB_ALL,button,1342242816
Control9=IDC_SUB,button,1342242816
Control10=IDC_SORT_SPIN,msctls_updown32,1342177312

[DLG:IDD_EXPORT_PROGRESS (Russian)]
Type=1
Class=CExpProgressDlg
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PROGRESS,msctls_progress32,1350565888

[CLS:CExpProgressDlg]
Type=0
HeaderFile=ExportDlgs.h
ImplementationFile=ExportDlgs.cpp
BaseClass=CNewWizPage
Filter=D
VirtualFilter=dWC
LastObject=CExpProgressDlg

[DLG:IDD_EXPORT_DIALOG]
Type=1
Class=?
ControlCount=6
Control1=ID_WIZNEXT,button,1342242816
Control2=ID_WIZBACK,button,1342242816
Control3=ID_WIZFINISH,button,1476460544
Control4=IDC_SHEETRECT,static,1073741842
Control5=IDC_SHEETRECT_VISIBLE,static,1342177298
Control6=ID_HELP,button,1342242816

[DLG:IDD_EXPORT_TYPES]
Type=1
Class=?
ControlCount=10
Control1=IDC_CHECK_XLS,button,1342242819
Control2=IDC_CHECK_RTF,button,1342242819
Control3=IDC_CHECK_HTM,button,1342242819
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_CHECK_BIRH,button,1342242819
Control7=IDC_CHECK_MARRIAGE,button,1342242819
Control8=IDC_CHECK_DIVORCE,button,1342242819
Control9=IDC_CHECK_CHANGE,button,1342242819
Control10=IDC_CHECK_DEATH,button,1342242819

[DLG:IDD_EXP_BIRTH]
Type=1
Class=?
ControlCount=10
Control1=IDC_NO_EXPORT,SysListView32,1350631425
Control2=IDC_DO_EXPORT,SysListView32,1350631425
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308864
Control5=IDC_STATIC,static,1342308864
Control6=IDC_ADD,button,1342242816
Control7=IDC_ADD_ALL,button,1342242816
Control8=IDC_SUB_ALL,button,1342242816
Control9=IDC_SUB,button,1342242816
Control10=IDC_SORT_SPIN,msctls_updown32,1342177312

[DLG:IDD_EXPORT_PROGRESS]
Type=1
Class=?
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PROGRESS,msctls_progress32,1350565888

