// sharemem.cpp : �w�q DLL ����l�Ʊ`���C
//

#include "stdafx.h"
#include "sharemem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: �p�G�o�� DLL �O�ʺA�a�� MFC DLL �s���A
//		����q�o�� DLL �ץX������|�I�s
//		MFC �������禡�A�������b�禡�@�}�Y�[�W AFX_MANAGE_STATE
//		�����C
//
//		�Ҧp:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// ���B�����`�禡�D��
//		}
//
//		�o�ӥ����@�w�n�X�{�b�C�@��
//		�禡���A�~����I�s MFC �������C�o�N����
//		�������O�禡�����Ĥ@�ӳ��z��
//		�A�Ʀܥ����b���󪫥��ܼƫŧi�e��
//		�A�]�����̪��غc�禡�i��|���͹� MFC
//		DLL �������I�s�C
//
//		�аѾ\ MFC �޳N���� 33 �M 58 ����
//		�ԲӸ�ơC
//

// CsharememApp

BEGIN_MESSAGE_MAP(CsharememApp, CWinApp)
END_MESSAGE_MAP()


// CsharememApp �غc

CsharememApp::CsharememApp()
{
	// TODO: �b���[�J�غc�{���X�A
	// �N�Ҧ����n����l�]�w�[�J InitInstance ��
}


// �Ȧ����@�� CsharememApp ����

CsharememApp theApp;


// CsharememApp ��l�]�w

BOOL CsharememApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
void EXPORTED_DLL_FUNCTION jashGetValue (char *outData)
{
	strcpy(outData,chrshare);
}
void EXPORTED_DLL_FUNCTION jashSetValue (char *inData)
{
	strcpy(chrshare,inData);
}