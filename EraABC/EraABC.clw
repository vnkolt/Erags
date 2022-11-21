; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CComboBoxEx
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "EraABC.h"
LastPage=0

ClassCount=16
Class1=CEraABCApp
Class2=CEraABCDoc
Class3=CEraABCView
Class4=CMainFrame

ResourceCount=27
Resource1=IDD_YESNO
Resource2=IDD_YESNO (Russian)
Class5=CAboutDlg
Resource3=IDR_FILEDROPDOWN
Class6=CFileTree
Class7=CTabView
Resource4=IDR_MAINFRAME (Russian)
Resource5=IDD_FORM_BIRTH
Resource6=IDD_ABOUTBOX (Russian)
Resource7=IDD_FORM_CHANGE (Russian)
Resource8=IDTB_MAIN_TOOLBAR
Class8=CFormBirth
Resource9=IDD_FORM_CHANGE
Class9=CFormChange
Class10=CFormDeath
Class11=CFormDivorce
Class12=CFormMarriage
Class13=CFormABC
Resource10=IDD_FORM_MARRIAGE (Russian)
Class14=CFileTreeView
Resource11=IDD_FORM_DEATH (Russian)
Resource12=IDD_SETDEFVAL (Russian)
Resource13=IDD_FILE_NEW (Russian)
Resource14=IDD_FORM_DEATH
Resource15=IDR_TREEFILECTRL_POPUP
Resource16=IDR_MAINFRAME (English (U.S.))
Resource17=IDD_ABOUTBOX
Resource18=IDD_FORM_MARRIAGE
Resource19=IDD_FORM_DIVORCE
Resource20=IDR_TREEFILECTRL_POPUP (Russian)
Resource21=IDD_FORM_DIVORCE (Russian)
Resource22=IDD_SETDEFVAL
Resource23=IDTB_MAIN_TOOLBAR (Russian)
Class15=CSetDefDlg
Resource24=IDR_FILEDROPDOWN (Russian)
Resource25=IDD_FORM_BIRTH (Russian)
Resource26=IDD_FILE_NEW
Class16=CExtStatusBarComboBox
Resource27=IDR_MAINFRAME

[CLS:CEraABCApp]
Type=0
HeaderFile=EraABC.h
ImplementationFile=EraABC.cpp
Filter=N
LastObject=CEraABCApp

[CLS:CEraABCDoc]
Type=0
HeaderFile=EraABCDoc.h
ImplementationFile=EraABCDoc.cpp
Filter=N
LastObject=CEraABCDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CEraABCView]
Type=0
HeaderFile=EraABCView.h
ImplementationFile=EraABCView.cpp
Filter=C
LastObject=CEraABCView
BaseClass=CSplitterWnd
VirtualFilter=pWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CNewFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=EraABC.cpp
ImplementationFile=EraABC.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_ERABC_VERSION,static,1342308480
Control3=IDC_STATIC,static,1342312448
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342181385
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CFileTree]
Type=0
HeaderFile=FileTree.h
ImplementationFile=FileTree.cpp
BaseClass=CTreeView
Filter=C
LastObject=CFileTree
VirtualFilter=VWC

[CLS:CTabView]
Type=0
HeaderFile=TabView.h
ImplementationFile=TabView.cpp
BaseClass=CView
Filter=C
LastObject=ID_BIRTH
VirtualFilter=VWC

[DLG:IDD_FORM_CHANGE (Russian)]
Type=1
Class=CFormChange
ControlCount=19
Control1=IDC_SEX,button,1342381827
Control2=IDC_STATIC,static,1342308865
Control3=IDC_NUMBER,edit,1350770816
Control4=IDC_STATIC,static,1342308865
Control5=IDC_DATEREG,edit,1350762624
Control6=IDC_STATIC,static,1342308865
Control7=IDC_STATIC,static,1342308865
Control8=IDC_STATIC,static,1342308352
Control9=IDC_OLD_SURNAME,edit,1350762624
Control10=IDC_STATIC,static,1342308352
Control11=IDC_NEW_SURNAME,edit,1350762624
Control12=IDC_STATIC,static,1342308352
Control13=IDC_OLD_NAME,combobox,1344340290
Control14=IDC_STATIC,static,1342308352
Control15=IDC_NEW_NAME,combobox,1344340290
Control16=IDC_STATIC,static,1342308352
Control17=IDC_OLD_PATRONYMIC,combobox,1344340290
Control18=IDC_STATIC,static,1342308352
Control19=IDC_NEW_PATRONYMIC,combobox,1344340290

[DLG:IDD_FORM_BIRTH (Russian)]
Type=1
Class=CFormBirth
ControlCount=13
Control1=IDC_CHILDFACE,static,1342177294
Control2=IDC_SEX,button,1342381827
Control3=IDC_STATIC,static,1342308865
Control4=IDC_NUMBER,edit,1350770816
Control5=IDC_STATIC,static,1342308865
Control6=IDC_DATEREG,edit,1350762624
Control7=IDC_STATIC,static,1342308864
Control8=IDC_SURNAME,edit,1350631808
Control9=IDC_STATIC,static,1342308864
Control10=IDC_NAME,combobox,1344340290
Control11=IDC_STATIC,static,1342308864
Control12=IDC_PATRONYMIC,combobox,1344340290
Control13=IDC_ALIVE_FLAG,button,1073843968

[DLG:IDD_FORM_DEATH (Russian)]
Type=1
Class=CFormDeath
ControlCount=12
Control1=IDC_SEX,button,1342381827
Control2=IDC_STATIC,static,1342308865
Control3=IDC_NUMBER,edit,1350770816
Control4=IDC_STATIC,static,1342308865
Control5=IDC_DATEREG,edit,1350762624
Control6=IDC_STATIC,static,1342308864
Control7=IDC_SURNAME,edit,1350631808
Control8=IDC_STATIC,static,1342308864
Control9=IDC_NAME,combobox,1344340290
Control10=IDC_STATIC,static,1342308864
Control11=IDC_PATRONYMIC,combobox,1344340290
Control12=IDC_STATIC,static,1342177294

[DLG:IDD_FORM_DIVORCE (Russian)]
Type=1
Class=CFormDivorce
ControlCount=24
Control1=IDC_STATIC,static,1342308865
Control2=IDC_NUMBER,edit,1350770816
Control3=IDC_STATIC,static,1342308865
Control4=IDC_DATEREG,edit,1350762624
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_MOLD_SURNAME,edit,1350762624
Control9=IDC_STATIC,static,1342308352
Control10=IDC_MNEW_SURNAME,edit,1350762624
Control11=IDC_STATIC,static,1342308352
Control12=IDC_MNAME,combobox,1344340290
Control13=IDC_STATIC,static,1342308352
Control14=IDC_MPATRONYMIC,combobox,1344340290
Control15=IDC_STATIC,static,1342308352
Control16=IDC_WOLD_SURNAME,edit,1350762624
Control17=IDC_STATIC,static,1342308352
Control18=IDC_WNEW_SURNAME,edit,1350762624
Control19=IDC_STATIC,static,1342308352
Control20=IDC_WNAME,combobox,1344340290
Control21=IDC_STATIC,static,1342308352
Control22=IDC_WPATRONYMIC,combobox,1344340290
Control23=IDC_STATIC,static,1350565902
Control24=IDC_STATIC,static,1350565902

[DLG:IDD_FORM_MARRIAGE (Russian)]
Type=1
Class=CFormMarriage
ControlCount=24
Control1=IDC_STATIC,static,1342308865
Control2=IDC_NUMBER,edit,1350770816
Control3=IDC_STATIC,static,1342308865
Control4=IDC_DATEREG,edit,1350762624
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_MOLD_SURNAME,edit,1350762624
Control9=IDC_STATIC,static,1342308352
Control10=IDC_MNEW_SURNAME,edit,1350762624
Control11=IDC_STATIC,static,1342308352
Control12=IDC_MNAME,combobox,1344340290
Control13=IDC_STATIC,static,1342308352
Control14=IDC_MPATRONYMIC,combobox,1344340290
Control15=IDC_STATIC,static,1342308352
Control16=IDC_WOLD_SURNAME,edit,1350762624
Control17=IDC_STATIC,static,1342308352
Control18=IDC_WNEW_SURNAME,edit,1350762624
Control19=IDC_STATIC,static,1342308352
Control20=IDC_WNAME,combobox,1344340290
Control21=IDC_STATIC,static,1342308352
Control22=IDC_WPATRONYMIC,combobox,1344340290
Control23=IDC_STATIC,static,1350565902
Control24=IDC_STATIC,static,1350565902

[CLS:CFormBirth]
Type=0
HeaderFile=FormBirth.h
ImplementationFile=FormBirth.cpp
BaseClass=CFormABC
Filter=D
LastObject=CFormBirth

[DLG:IDD_YESNO (Russian)]
Type=1
Class=CFormABC
ControlCount=5
Control1=IDYES,button,1342242816
Control2=IDNO,button,1342246656
Control3=IDC_STATIC,static,1342177283
Control4=IDC_YNMESSAGE,static,1342308353
Control5=IDC_YNQUESTION,edit,1350637696

[CLS:CFormChange]
Type=0
HeaderFile=FormChange.h
ImplementationFile=FormChange.cpp
BaseClass=CFormABC
Filter=D
LastObject=CFormChange

[CLS:CFormDeath]
Type=0
HeaderFile=FormDeath.h
ImplementationFile=FormDeath.cpp
BaseClass=CFormABC
Filter=D
LastObject=CFormDeath

[CLS:CFormDivorce]
Type=0
HeaderFile=FormDivorce.h
ImplementationFile=FormDivorce.cpp
BaseClass=CFormABC
Filter=D
LastObject=CFormDivorce

[CLS:CFormMarriage]
Type=0
HeaderFile=FormMarriage.h
ImplementationFile=FormMarriage.cpp
BaseClass=CFormABC
Filter=D
LastObject=CFormMarrige

[CLS:CFormABC]
Type=0
HeaderFile=FormABC.h
ImplementationFile=FormABC.cpp
BaseClass=CFormView
Filter=D
LastObject=32514

[CLS:CFileTreeView]
Type=0
HeaderFile=FileTreeView.h
ImplementationFile=FileTreeView.cpp
BaseClass=CView
Filter=C
LastObject=CFileTreeView
VirtualFilter=VWC

[DLG:IDR_MAINFRAME (Russian)]
Type=1
Class=?
ControlCount=7
Control1=ID_FILE_NEW,button,1342242816
Control2=ID_FILE_OPEN,button,1342242816
Control3=ID_BIRTH,button,1342242816
Control4=ID_MARRIAGE,button,1342242816
Control5=ID_DIVORCE,button,1342242816
Control6=ID_CHANGE,button,1342242816
Control7=ID_DEATH,button,1342242816

[DLG:IDTB_MAIN_TOOLBAR (Russian)]
Type=1
Class=?
ControlCount=15
Control1=ID_FOLDER_TREE,button,1342242816
Control2=ID_FILE_NEW,button,1342242816
Control3=ID_FILE_OPEN,button,1342242816
Control4=ID_FILE_RECENT,button,1342242816
Control5=ID_RECORD_FIRST,button,1342242816
Control6=ID_RECORD_PREV,button,1342242816
Control7=ID_RECORD_NEXT,button,1342242816
Control8=ID_RECORD_LAST,button,1342242816
Control9=ID_RECORD_NEW,button,1342243328
Control10=ID_RECORD_DELETE,button,1342243328
Control11=ID_WHAT_IS_IT,button,1342242816
Control12=65535,static,1342181383
Control13=65535,static,1342181383
Control14=65535,static,1342181383
Control15=65535,static,1342181383

[MNU:IDR_FILEDROPDOWN (Russian)]
Type=1
Class=?
Command1=ID_FILE_MRU_FILE1
CommandCount=1

[MNU:IDR_MAINFRAME (Russian)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FOLDER_TREE
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_BIRTH
Command7=ID_MARRIAGE
Command8=ID_DIVORCE
Command9=ID_CHANGE
Command10=ID_DEATH
Command11=ID_RECORD_FIRST
Command12=ID_RECORD_PREV
Command13=ID_RECORD_NEXT
Command14=ID_RECORD_LAST
Command15=ID_RECORD_NEW
Command16=ID_RECORD_DELETE
Command17=ID_HELP
Command18=ID_HELPER
Command19=ID_WHAT_IS_IT
Command20=ID_HELP_UKR
Command21=ID_HELP_RUS
Command22=ID_APP_ABOUT
CommandCount=22

[DLG:IDD_FILE_NEW (Russian)]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342308864
Control2=IDC_YEAR,edit,1350639744
Control3=IDC_YEAR_SPIN,msctls_updown32,1342177458
Control4=IDC_STATIC,static,1342308864

[DLG:IDD_FORM_BIRTH]
Type=1
Class=CFormBirth
ControlCount=13
Control1=IDC_CHILDFACE,static,1342177294
Control2=IDC_SEX,button,1342381827
Control3=IDC_STATIC,static,1342308865
Control4=IDC_NUMBER,edit,1350770816
Control5=IDC_STATIC,static,1342308865
Control6=IDC_DATEREG,edit,1350762624
Control7=IDC_STATIC,static,1342308864
Control8=IDC_SURNAME,edit,1350631808
Control9=IDC_STATIC,static,1342308864
Control10=IDC_NAME,combobox,1344340290
Control11=IDC_STATIC,static,1342308864
Control12=IDC_PATRONYMIC,combobox,1344340290
Control13=IDC_ALIVE_FLAG,button,1073843968

[DLG:IDD_FORM_CHANGE]
Type=1
Class=CFormChange
ControlCount=19
Control1=IDC_SEX,button,1342381827
Control2=IDC_STATIC,static,1342308865
Control3=IDC_NUMBER,edit,1350770816
Control4=IDC_STATIC,static,1342308865
Control5=IDC_DATEREG,edit,1350762624
Control6=IDC_STATIC,static,1342308865
Control7=IDC_STATIC,static,1342308865
Control8=IDC_STATIC,static,1342308352
Control9=IDC_OLD_SURNAME,edit,1350762624
Control10=IDC_STATIC,static,1342308352
Control11=IDC_NEW_SURNAME,edit,1350762624
Control12=IDC_STATIC,static,1342308352
Control13=IDC_OLD_NAME,combobox,1344340290
Control14=IDC_STATIC,static,1342308352
Control15=IDC_NEW_NAME,combobox,1344340290
Control16=IDC_STATIC,static,1342308352
Control17=IDC_OLD_PATRONYMIC,combobox,1344340290
Control18=IDC_STATIC,static,1342308352
Control19=IDC_NEW_PATRONYMIC,combobox,1344340290

[DLG:IDD_FORM_DEATH]
Type=1
Class=CFormDeath
ControlCount=12
Control1=IDC_SEX,button,1342381827
Control2=IDC_STATIC,static,1342308865
Control3=IDC_NUMBER,edit,1350770816
Control4=IDC_STATIC,static,1342308865
Control5=IDC_DATEREG,edit,1350762624
Control6=IDC_STATIC,static,1342308864
Control7=IDC_SURNAME,edit,1350631808
Control8=IDC_STATIC,static,1342308864
Control9=IDC_NAME,combobox,1344340290
Control10=IDC_STATIC,static,1342308864
Control11=IDC_PATRONYMIC,combobox,1344340290
Control12=IDC_STATIC,static,1342177294

[DLG:IDD_FORM_DIVORCE]
Type=1
Class=CFormDivorce
ControlCount=24
Control1=IDC_STATIC,static,1342308865
Control2=IDC_NUMBER,edit,1350770816
Control3=IDC_STATIC,static,1342308865
Control4=IDC_DATEREG,edit,1350762624
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_MOLD_SURNAME,edit,1350762624
Control9=IDC_STATIC,static,1342308352
Control10=IDC_MNEW_SURNAME,edit,1350762624
Control11=IDC_STATIC,static,1342308352
Control12=IDC_MNAME,combobox,1344340290
Control13=IDC_STATIC,static,1342308352
Control14=IDC_MPATRONYMIC,combobox,1344340290
Control15=IDC_STATIC,static,1342308352
Control16=IDC_WOLD_SURNAME,edit,1350762624
Control17=IDC_STATIC,static,1342308352
Control18=IDC_WNEW_SURNAME,edit,1350762624
Control19=IDC_STATIC,static,1342308352
Control20=IDC_WNAME,combobox,1344340290
Control21=IDC_STATIC,static,1342308352
Control22=IDC_WPATRONYMIC,combobox,1344340290
Control23=IDC_STATIC,static,1350565902
Control24=IDC_STATIC,static,1350565902

[DLG:IDD_FORM_MARRIAGE]
Type=1
Class=CFormMarriage
ControlCount=24
Control1=IDC_STATIC,static,1342308865
Control2=IDC_NUMBER,edit,1350770816
Control3=IDC_STATIC,static,1342308865
Control4=IDC_DATEREG,edit,1350762624
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_MOLD_SURNAME,edit,1350762624
Control9=IDC_STATIC,static,1342308352
Control10=IDC_MNEW_SURNAME,edit,1350762624
Control11=IDC_STATIC,static,1342308352
Control12=IDC_MNAME,combobox,1344340290
Control13=IDC_STATIC,static,1342308352
Control14=IDC_MPATRONYMIC,combobox,1344340290
Control15=IDC_STATIC,static,1342308352
Control16=IDC_WOLD_SURNAME,edit,1350762624
Control17=IDC_STATIC,static,1342308352
Control18=IDC_WNEW_SURNAME,edit,1350762624
Control19=IDC_STATIC,static,1342308352
Control20=IDC_WNAME,combobox,1344340290
Control21=IDC_STATIC,static,1342308352
Control22=IDC_WPATRONYMIC,combobox,1344340290
Control23=IDC_STATIC,static,1350565902
Control24=IDC_STATIC,static,1350565902

[DLG:IDD_YESNO]
Type=1
Class=CFormABC
ControlCount=5
Control1=IDYES,button,1342242816
Control2=IDNO,button,1342246656
Control3=IDC_STATIC,static,1342177283
Control4=IDC_YNMESSAGE,static,1342308353
Control5=IDC_YNQUESTION,edit,1350637696

[DLG:IDTB_MAIN_TOOLBAR]
Type=1
Class=?
ControlCount=15
Control1=ID_FOLDER_TREE,button,1342242816
Control2=ID_FILE_NEW,button,1342242816
Control3=ID_FILE_OPEN,button,1342242816
Control4=ID_FILE_RECENT,button,1342242816
Control5=ID_RECORD_FIRST,button,1342242816
Control6=ID_RECORD_PREV,button,1342242816
Control7=ID_RECORD_NEXT,button,1342242816
Control8=ID_RECORD_LAST,button,1342242816
Control9=ID_RECORD_NEW,button,1342243328
Control10=ID_RECORD_DELETE,button,1342243328
Control11=ID_WHAT_IS_IT,button,1342242816
Control12=65535,static,1342181383
Control13=65535,static,1342181383
Control14=65535,static,1342181383
Control15=65535,static,1342181383

[DLG:IDD_FILE_NEW]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342308864
Control2=IDC_YEAR,edit,1350639744
Control3=IDC_YEAR_SPIN,msctls_updown32,1342177458
Control4=IDC_STATIC,static,1342308864

[MNU:IDR_FILEDROPDOWN]
Type=1
Class=?
Command1=ID_FILE_MRU_FILE1
CommandCount=1

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FOLDER_TREE
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_BIRTH
Command7=ID_MARRIAGE
Command8=ID_DIVORCE
Command9=ID_CHANGE
Command10=ID_DEATH
Command11=ID_RECORD_FIRST
Command12=ID_RECORD_PREV
Command13=ID_RECORD_NEXT
Command14=ID_RECORD_LAST
Command15=ID_RECORD_NEW
Command16=ID_RECORD_DELETE
Command17=ID_HELP
Command18=ID_HELPER
Command19=ID_WHAT_IS_IT
Command20=ID_HELP_UKR
Command21=ID_HELP_RUS
Command22=ID_APP_ABOUT
CommandCount=22

[MNU:IDR_TREEFILECTRL_POPUP (Russian)]
Type=1
Class=?
Command1=ID_TREEFILECTRL_UP
Command2=ID_TREEFILECTRL_OPEN
Command3=ID_TREEFILECTRL_RENAME
Command4=ID_TREEFILECTRL_DELETE
Command5=ID_TREEFILECTRL_PROPERTIES
CommandCount=5

[DLG:IDD_ABOUTBOX (Russian)]
Type=1
Class=CAboutDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_ERABC_VERSION,static,1342308480
Control3=IDC_STATIC,static,1342312448
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342181385
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[CLS:CSetDefDlg]
Type=0
HeaderFile=SetDefDlg.h
ImplementationFile=SetDefDlg.cpp
BaseClass=CDialogEx
Filter=D
VirtualFilter=dWC
LastObject=CSetDefDlg

[DLG:IDD_SETDEFVAL (Russian)]
Type=1
Class=CSetDefDlg
ControlCount=5
Control1=IDC_DONTSHOW,button,1342242819
Control2=IDC_STATIC,static,1342177283
Control3=IDYES,button,1342242945
Control4=IDNO,button,1342242944
Control5=IDC_MSGTEXT,static,1342312448

[DLG:IDD_SETDEFVAL]
Type=1
Class=CSetDefDlg
ControlCount=5
Control1=IDC_DONTSHOW,button,1342242819
Control2=IDC_STATIC,static,1342177283
Control3=IDYES,button,1342242945
Control4=IDNO,button,1342242944
Control5=IDC_MSGTEXT,static,1342312448

[MNU:IDR_TREEFILECTRL_POPUP]
Type=1
Class=?
Command1=ID_TREEFILECTRL_UP
Command2=ID_TREEFILECTRL_OPEN
Command3=ID_TREEFILECTRL_RENAME
Command4=ID_TREEFILECTRL_DELETE
Command5=ID_TREEFILECTRL_PROPERTIES
CommandCount=5

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FOLDER_TREE
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_RECENT
Command5=ID_RECORD_FIRST
Command6=ID_RECORD_PREV
Command7=ID_RECORD_NEXT
Command8=ID_RECORD_LAST
Command9=ID_RECORD_NEW
Command10=ID_RECORD_DELETE
Command11=ID_WHAT_IS_IT
CommandCount=11

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_RECORD_DELETE
Command2=ID_RECORD_LAST
Command3=ID_RECORD_FIRST
Command4=ID_TOGGLE_INSERT
Command5=ID_RECORD_NEW
Command6=ID_RECORD_PREV
Command7=ID_RECORD_NEXT
CommandCount=7

[CLS:CExtStatusBarComboBox]
Type=0
HeaderFile=..\Controls\ExtStatusBarComboBox.h
ImplementationFile=..\Controls\ExtStatusBarComboBox.cpp
BaseClass=CComboBoxEx
Filter=W
LastObject=CExtStatusBarComboBox

[TB:IDR_MAINFRAME (Russian)]
Type=1
Class=?
Command1=ID_FOLDER_TREE
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_RECENT
Command5=ID_RECORD_FIRST
Command6=ID_RECORD_PREV
Command7=ID_RECORD_NEXT
Command8=ID_RECORD_LAST
Command9=ID_RECORD_NEW
Command10=ID_RECORD_DELETE
Command11=ID_WHAT_IS_IT
CommandCount=11

[ACL:IDR_MAINFRAME (Russian)]
Type=1
Class=?
Command1=ID_RECORD_DELETE
Command2=ID_RECORD_LAST
Command3=ID_RECORD_FIRST
Command4=ID_TOGGLE_INSERT
Command5=ID_RECORD_NEW
Command6=ID_RECORD_PREV
Command7=ID_RECORD_NEXT
CommandCount=7

