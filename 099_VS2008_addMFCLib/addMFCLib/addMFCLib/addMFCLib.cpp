// addMFCLib.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include "addMFCLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �Ȧ����@�����ε{������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��l�� MFC �é󥢱ѮɦC�L���~
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: �t�X�z���ݭn�ܧ���~�X
		_tprintf(_T("�Y�����~: MFC ��l�ƥ���\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: �b�����g���ε{���欰���{���X�C
	}

	return nRetCode;
}
