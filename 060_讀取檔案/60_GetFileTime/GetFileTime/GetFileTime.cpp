// GetFileTime.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include "GetFileTime.h"

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
		CString fileName;  //�n�䪺�ɮצW��(�ۭq)
		fileName="C:\\mainvideo.wmv";
		WIN32_FIND_DATA FindFileData; //windows �ɮ׸�T�榡
		SYSTEMTIME avd;               //windows system time �榡 (�Ψӱ����ഫ�L�᪺FileTime)
		FindFirstFile(fileName,&FindFileData);   //���ɮ׸�TŪ�� FindFileData ��
		cout <<"C:\\mainvideo.wmv"<<endl;
		FileTimeToSystemTime( &FindFileData.ftCreationTime, &avd );  //�� FileTime�榡�নSystemTime�榡(�o�̥u���إߤ�����)
		cout <<"�إߤ��:"<<avd.wYear<<"-"<<avd.wMonth<<"-"<<avd.wDay<<endl;
		FileTimeToSystemTime( &FindFileData.ftLastAccessTime, &avd );  //�� FileTime�榡�নSystemTime�榡(�o�̥u���̫�s�����)
		cout <<"�̫�s�����:"<<avd.wYear<<"-"<<avd.wMonth<<"-"<<avd.wDay<<endl;
		FileTimeToSystemTime( &FindFileData.ftLastWriteTime, &avd );  //�� FileTime�榡�নSystemTime�榡(�o�̥u���̫�ק���)
		cout <<"�̫�ק���:"<<avd.wYear<<"-"<<avd.wMonth<<"-"<<avd.wDay<<endl;
	}

	return nRetCode;
}
