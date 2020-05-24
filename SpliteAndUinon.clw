; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CExName
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SpliteAndUinon.h"

ClassCount=6
Class1=CSpliteAndUinonApp
Class2=CSpliteAndUinonDlg

ResourceCount=6
Resource2=IDD_SPLITEANDUINON_DIALOG
Resource1=IDR_MAINFRAME
Class3=CMySplite
Resource3=IDD_SPLITE_DIALOG
Class4=CMyProgress
Resource4=IDD_UNION_DIALOG
Class5=CMyUnion
Resource5=IDD_PROGRESS_DIALOG
Class6=CExName
Resource6=IDD_EXNAME_DIALOG

[CLS:CSpliteAndUinonApp]
Type=0
HeaderFile=SpliteAndUinon.h
ImplementationFile=SpliteAndUinon.cpp
Filter=N

[CLS:CSpliteAndUinonDlg]
Type=0
HeaderFile=SpliteAndUinonDlg.h
ImplementationFile=SpliteAndUinonDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSpliteAndUinonDlg



[DLG:IDD_SPLITEANDUINON_DIALOG]
Type=1
Class=CSpliteAndUinonDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177287
Control2=IDC_BTN_SPLITE,button,1342242816
Control3=IDC_BTN_UNION,button,1342242816
Control4=IDC_BTN_EXNAME,button,1342242816
Control5=IDC_STATIC,static,1342177287
Control6=IDC_MINDER,static,1342308352

[DLG:IDD_SPLITE_DIALOG]
Type=1
Class=CMySplite
ControlCount=14
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_PATH,edit,1350633600
Control3=IDC_BTN_SCAN,button,1342242816
Control4=IDC_STATIC,static,1342177287
Control5=IDC_STATIC,static,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_SMALLMB,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_NUM,edit,1350633600
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_BTN_SPLITE,button,1342242816
Control14=IDC_BTN_EXIT,button,1342242816

[CLS:CMySplite]
Type=0
HeaderFile=MySplite.h
ImplementationFile=MySplite.cpp
BaseClass=CDialog
Filter=D
LastObject=CMySplite
VirtualFilter=dWC

[DLG:IDD_PROGRESS_DIALOG]
Type=1
Class=CMyProgress
ControlCount=2
Control1=IDC_PROGRESS,msctls_progress32,1350565888
Control2=IDC_EDIT_PROG,edit,1342244992

[CLS:CMyProgress]
Type=0
HeaderFile=MyProgress.h
ImplementationFile=MyProgress.cpp
BaseClass=CDialog
Filter=D
LastObject=CMyProgress

[DLG:IDD_UNION_DIALOG]
Type=1
Class=CMyUnion
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_PATH,edit,1350633600
Control3=IDC_BTN_SCAN,button,1342242816
Control4=IDC_STATIC,static,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_LIST,listbox,1352728835
Control7=IDC_STATIC,static,1342177287
Control8=IDC_BTN_HEBING,button,1342242816
Control9=IDC_BTN_ADD,button,1342242816
Control10=IDC_BTN_DELETE,button,1342242816

[CLS:CMyUnion]
Type=0
HeaderFile=MyUnion.h
ImplementationFile=MyUnion.cpp
BaseClass=CDialog
Filter=D
LastObject=CMyUnion
VirtualFilter=dWC

[DLG:IDD_EXNAME_DIALOG]
Type=1
Class=CExName
ControlCount=11
Control1=IDC_BTN_SCAN,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_PATH,edit,1350633600
Control4=IDC_STATIC,static,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_LIST,listbox,1352728835
Control7=IDC_STATIC,static,1342177287
Control8=IDC_BTN_EXEXT,button,1342242816
Control9=IDC_EDIT_EXT,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_BTN_SHOW,button,1342242816

[CLS:CExName]
Type=0
HeaderFile=ExName.h
ImplementationFile=ExName.cpp
BaseClass=CDialog
Filter=D
LastObject=CExName
VirtualFilter=dWC

