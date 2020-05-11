// VS2008CString.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include "VS2008CString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
/*
<stdlib.h> <math.h> <wchar.h>
	ASCII		UNICODE		TCHAR		VS2005
int	atoi		_wtoi		_tstoi 		_atoi_l 
							_ttoi		_wtoi_l

long	atol	_wtol		_tstoi		_atoi_l  
							_ttoi		_wtoi_l

double	atof	_wtof		_tstof		_atof_l 
							_ttof		_wtof_l 
*/

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
	/* CString �ഫ�� LPTSTR */
	//(1)�j���ഫ
	CString strText( _T("This is a test") );
	LPTSTR lpszText =(LPTSTR)(LPCTSTR)strText;
	::MessageBox(NULL,lpszText, _T("���D"),MB_ICONASTERISK|MB_TASKMODAL|MB_OK);
	//(2)�ϥ�lstrcpy()
	lpszText = new TCHAR[strText.GetLength()+1];
	lstrcpy( lpszText, strText );
	::MessageBox(NULL,lpszText, _T("���D"), MB_ICONASTERISK|MB_TASKMODAL|MB_OK);

	CString theString=_T("This is a test");
	theString=_T("100");

	/* CString -> LPTSTR */
	LPTSTR lpsz = new TCHAR[theString.GetLength()+1];
	_tcscpy(lpsz, theString);

	/* LPTSTR ->int */
	int chr2int;
	chr2int=_wtoi(lpsz);//chr2int=_ttoi(lpsz);

	/* LPTSTR ->float */
	float chr2float;
	chr2float=_wtof(lpsz);

	/*int -> CString*/
	CString s;
	int i = 64;
	s.Format(L"%d",i);

	//Unicode�UCString�ഫ��char *
	CString str = _T("123,456,789");
	//�`�N�G�H�Un�Mlen���Ȥj�p���P,n�O���r���p�⪺�Alen�O���줸�խp�⪺
	int n = str.GetLength();
	//����e�줸�զr�����j�p�A�j�p�O���줸�խp�⪺
	int len = WideCharToMultiByte(CP_ACP,0,str,str.GetLength(),NULL,0,NULL,NULL);
	//���h�줸�զr���}�C�ӽЪŶ��A�}�C�j�p�����줸�խp�⪺�e�줸�զ줸�դj�p
	char * pFileName = new char[len+1];   //�H�줸�լ����
	//�e�줸�սs�X�ഫ���h�줸�սs�X
	WideCharToMultiByte(CP_ACP,0,str,str.GetLength(),pFileName,len,NULL,NULL);
	pFileName[len] = '\0'; //�K�[�r�굲���A�`�N���Olen+1

	//sscanf
	char Schrd01[500],Schrd02[500],Schrd03[500];
	int ih01,ih02,ih03;
	float fh01,fh02,fh03;

	sscanf (pFileName ,"%[^','],%[^','],%s",Schrd01,Schrd02,Schrd03);
	ih01=atoi(Schrd01);
	ih02=atoi(Schrd02);
	ih03=atoi(Schrd03);
	fh01=atof(Schrd01);
	fh02=atof(Schrd02);
	fh03=atof(Schrd03);

	delete [] pFileName;
	//Unicode�Uchar *�ഫ��CString
	char *pFileName1 = "D:\\�դ�����\\QQ.bmp";
	//�p��char *�}�C�j�p�A�H�줸�լ����A�@�Ӻ~�r�e��Ӧ줸��
	int charLen = strlen(pFileName1);
	//�p��h�줸�զr�����j�p�A���r���p��C
	len = MultiByteToWideChar(CP_ACP,0,pFileName1,charLen,NULL,0);
	//���e�줸�զr���}�C�ӽЪŶ��A�}�C�j�p�����줸�խp�⪺�h�줸�զr���j�p
	TCHAR *buf = new TCHAR[len + 1];
	//�h�줸�սs�X�ഫ���e�줸�սs�X
	MultiByteToWideChar(CP_ACP,0,pFileName1,charLen,buf,len);
	buf[len] = '\0'; //�K�[�r�굲���A�`�N���Olen+1
	CString pWideChar;
	pWideChar.Append(buf);
	delete [] buf;

	return nRetCode;
}
