// hide_mouse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "hide_mouse.h"
//========================
#include <windows.h>

#include <iostream>
#include<fstream>//7
#include <stdlib.h> //srand() ,rand() ,system()
#include <time.h>   //time()
#include <atlbase.h>
#include <afxtempl.h>//CArray Step_01 
using namespace std;
//========================
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//===============
extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow ();//���o����API�ŧi
void CALLBACK TimeProc( HWND hwnd, UINT message, UINT idTimer, DWORD dwTime);//TIMER��ƫŧi
/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

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
		// TODO: code your application's behavior here.
		cout <<"30������÷ƹ��M�Y�p�{��"<< endl;
		HWND hWnd = ::GetConsoleWindow();//���o����HAND
		::ShowWindow( hWnd, SW_MINIMIZE );//�Y�p����
		//=========================
		SetTimer(NULL,1,3000,TimeProc);//�Ұ�TIMER
		MSG   msg;   
		while(GetMessage(&msg,NULL,0,0)) //�ƥ�^����
		{   
			if(msg.message==WM_TIMER)   
			{   
				DispatchMessage(&msg);   
			}
		}
		//=========================
	}

	return nRetCode;
}
void CALLBACK TimeProc( HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)   
{
		int intH,intW;
		intW=GetSystemMetrics(SM_CXSCREEN);//���o�����e��
		intH=GetSystemMetrics(SM_CYSCREEN);//���o��������
		cout << intW << " X " << intH << endl;//�q�X�ѪR��
		CRect rc;
		rc.top=intH;
		rc.bottom=intH+10;
		rc.left=intW;
		rc.right=intW+10; 
		::SetCursorPos(intW/2,intH+10);  //�]�w�ƹ���m�A�t�����ô��
		//ClipCursor(&rc);//��w�ƹ��d��
		//=========================

}

