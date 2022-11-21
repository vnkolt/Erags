; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDefBirth
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "era2era3.h"

ClassCount=5
Class1=CEra2era3App
Class2=CEra2era3Dlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_ERA2ERA3_DIALOG
Class4=CRepairDlg
Resource4=IDD_REPAIR
Class5=CDefBirth
Resource5=IDD_DEFBIRTH

[CLS:CEra2era3App]
Type=0
HeaderFile=era2era3.h
ImplementationFile=era2era3.cpp
Filter=N

[CLS:CEra2era3Dlg]
Type=0
HeaderFile=era2era3Dlg.h
ImplementationFile=era2era3Dlg.cpp
Filter=D
LastObject=CEra2era3Dlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=era2era3Dlg.h
ImplementationFile=era2era3Dlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ERA2ERA3_DIALOG]
Type=1
Class=CEra2era3Dlg
ControlCount=11
Control1=IDC_OLDPATH,edit,1350633600
Control2=IDC_CHOOSE_OLD,button,1342242816
Control3=IDC_OLDFILELIST,SysListView32,1350631433
Control4=IDC_NEWPATH,edit,1350633600
Control5=IDC_CHOOSE_NEW,button,1342242816
Control6=IDC_NEWFILELIST,SysListView32,1350631433
Control7=IDOK,button,1342242816
Control8=IDCANCEL,button,1342242816
Control9=IDC_PROGRESS_FILE,msctls_progress32,1082130433
Control10=IDC_PROGRESS_TOTAL,msctls_progress32,1082130433
Control11=IDC_CURRENT_FILE,static,1342308352

[DLG:IDD_REPAIR]
Type=1
Class=CRepairDlg
ControlCount=7
Control1=IDOK,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_RAPAIR,edit,1350633540
Control4=IDC_LBL_WHAT,static,1342308352
Control5=IDC_WHAT,edit,1350631552
Control6=IDC_STATIC,static,1342177283
Control7=IDC_NOMORE,button,1342242819

[CLS:CRepairDlg]
Type=0
HeaderFile=RepairDlg.h
ImplementationFile=RepairDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CRepairDlg
VirtualFilter=dWC

[DLG:IDD_DEFBIRTH]
Type=1
Class=CDefBirth
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

[CLS:CDefBirth]
Type=0
HeaderFile=DefBirth.h
ImplementationFile=DefBirth.cpp
BaseClass=CDialog
Filter=D
LastObject=CDefBirth
VirtualFilter=dWC

