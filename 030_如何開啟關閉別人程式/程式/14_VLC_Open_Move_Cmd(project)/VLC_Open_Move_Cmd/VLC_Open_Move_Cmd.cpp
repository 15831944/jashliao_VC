// VLC_Open_Move_Cmd.cpp : Defines the entry point for the console application.
//////////////////////////////////////////////////////////////
//
//	�ɮץ\�໡��:�إߤ@��i�H�I�s�i�⪩VLC�M���w��VLC��m�P�����j�p���R�O�Ҧ��{��
//	�̫�ק���:2013/02/01
//	���g�H:jash.liao
//
/////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VLC_Open_Move_Cmd.h"

//----------------------------
//���F�r����Ʀr����ƫŧi
#include<stdio.h>
#include <stdlib.h>
//----------------------------

//----------------------------
//���FC++Ū�ɪ���ƫŧi
#include<iostream>
#include<fstream>

using namespace std;
//----------------------------

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;
//============================================================
//
//�D���:�]�t�Ҧ��ʧ@
//
//============================================================
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
	//----------------------------
	//���FC++Ū���ܼƫŧi
		char chrData01[500];
		char chrData02[500];
		char chrData03[500];
		char chrData04[500];
	//----------------------------

	//----------------------------
	//���FC++Ū��
		fstream a;
		a.open("data.txt",ios::in);
			a.getline(chrData01,500);
			a.getline(chrData02,500);
			a.getline(chrData03,500);
			a.getline(chrData04,500);
		a.close();
	//----------------------------

	//----------------------------
	//���j�M�O�_�w�g�����檺VLC�s�b	
		HWND hWnd1;
		hWnd1 = ::FindWindow(NULL, chrData02);
	//----------------------------
		if(hWnd1==NULL)//��ܨS��VLC
		{
			//----------------------------
			//�ϥ�CreateProcess�I�sVLC	
			//CreateProcess_start
			PROCESS_INFORMATION pi;
			STARTUPINFO si;
			//�ܼƪ�l��
			memset(&si,0,sizeof(si));
			si.cb=sizeof(si);
			si.wShowWindow=SW_SHOW;
			si.dwFlags=STARTF_USESHOWWINDOW;
			//���}�{��
			BOOL fRet=CreateProcess(NULL,
									chrData01,
									NULL,
									NULL,
									FALSE,
									NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
									NULL,
									NULL,
									&si,
									&pi);
			//CreateProcess_end
			//----------------------------

			//----------------------------
			//����VLC�I�s�����ò��ʨ���w��m
			HWND hWnd3;
			do
			{
				hWnd3 = ::FindWindow(NULL, chrData02);
				//cout<<"find HWND\n";
			}while(hWnd3==NULL);
			if(hWnd3)
			{
				MoveWindow(hWnd3,atoi(chrData03),atoi(chrData04),0,0,true);
			}
			//----------------------------
		}//if(hWnd1==NULL)
	}//if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))_else

	return nRetCode;
}


