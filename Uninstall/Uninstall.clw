; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUninstallDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Uninstall.h"

ClassCount=3
Class1=CUninstallApp
Class2=CUninstallDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_UNINSTALL_DIALOG

[CLS:CUninstallApp]
Type=0
HeaderFile=Uninstall.h
ImplementationFile=Uninstall.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CUninstallApp

[CLS:CUninstallDlg]
Type=0
HeaderFile=UninstallDlg.h
ImplementationFile=UninstallDlg.cpp
Filter=D
LastObject=IDC_FILES
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=UninstallDlg.h
ImplementationFile=UninstallDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_UNINSTALL_DIALOG]
Type=1
Class=CUninstallDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TEXT,static,1350697472
Control4=IDC_PROGRESS,msctls_progress32,1082130432
Control5=IDC_PROGRAMS,button,1342242819
Control6=IDC_TEMPLATES,button,1342242819
Control7=IDC_DATABASE,button,1342242819
Control8=IDC_LINKS,button,1342242819
Control9=IDC_STATIC,static,1342308352
Control10=IDC_REGISTRY,button,1342242819
Control11=IDC_FILES,SysListView32,1082195969

