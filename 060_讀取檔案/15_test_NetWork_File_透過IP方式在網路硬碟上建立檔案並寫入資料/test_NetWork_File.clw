; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTest_NetWork_FileDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "test_NetWork_File.h"

ClassCount=4
Class1=CTest_NetWork_FileApp
Class2=CTest_NetWork_FileDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TEST_NETWORK_FILE_DIALOG

[CLS:CTest_NetWork_FileApp]
Type=0
HeaderFile=test_NetWork_File.h
ImplementationFile=test_NetWork_File.cpp
Filter=N

[CLS:CTest_NetWork_FileDlg]
Type=0
HeaderFile=test_NetWork_FileDlg.h
ImplementationFile=test_NetWork_FileDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=test_NetWork_FileDlg.h
ImplementationFile=test_NetWork_FileDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TEST_NETWORK_FILE_DIALOG]
Type=1
Class=CTest_NetWork_FileDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816

