// ANSI2Unicode_File.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include "ANSI2Unicode_File.h"

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
		CStdioFile fileANSI;
		CFile fileUnicode;
		CFile file;
		WORD wSignature = 0xFEFF;
		int intLen;
		char pstrANSI[500];
		CString StrANSI;
		WCHAR pszUnicodeAll[500];//OK->CString����=�}�C����
		WCHAR pszUnicodeBuf[500]={NULL};
		fileUnicode.Open(_T("123Unicode.txt"), CFile::modeCreate|CFile::modeWrite);
		file.Open(_T("test.txt"), CFile::modeCreate|CFile::modeWrite);
		fileUnicode.Write(&wSignature, 2);
		fileANSI.Open(_T("123.txt"),CFile::modeRead);
		while(fileANSI.ReadString(StrANSI))
		{
			StrANSI+="\r\n";
			////////////////////////////////////////////////////
			//Unicode�{��ŪANSI�ɮ�
			const size_t strsize02=(StrANSI.GetLength()+1)*2;
			size_t sz02=0;
			wcstombs_s(&sz02,pstrANSI,strsize02,StrANSI,_TRUNCATE);
			StrANSI=pstrANSI;
			intLen=StrANSI.GetLength();
			/////////////////////////////////////////////////////
			//ANSI�r����Unicode�r��
			wcsncpy(pszUnicodeAll,pszUnicodeBuf,500);
			MultiByteToWideChar(CP_ACP, 0,pstrANSI,-1,pszUnicodeAll,sz02);
			fileUnicode.Write(pszUnicodeAll, lstrlenW(pszUnicodeAll) * sizeof(WCHAR));
			/////////////////////////////////////////////////////
			//Unicode�{���gANSI�ɮ�
			file.Write(pstrANSI,sz02);
		}
		fileUnicode.Close();
		fileANSI.Close();
		file.Close();
	}

	return nRetCode;
}
