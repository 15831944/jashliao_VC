// testEngraving.cpp : �w�q DLL ����l�Ʊ`���C
//

#include "stdafx.h"
#include "testEngraving.h"

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


// CtestEngravingApp

BEGIN_MESSAGE_MAP(CtestEngravingApp, CWinApp)
END_MESSAGE_MAP()


// CtestEngravingApp �غc
void EXPORTED_DLL_FUNCTION GetValue1(EngarveElement *p,long number)
{
	FILE *p1;
	int k;
	EE=p;
	n=number;
	p1=fopen("data.txt","w");
	for(k=0;k<number;k++)
		fprintf(p1,"%d\t%d\t%f\t%f\t%f\t%f\t%f\t%f\n",(EE+k)->CCW ,(EE+k)->Type,(EE+k)->X1,(EE+k)->Y1,(EE+k)->Z1,(EE+k)->X2,(EE+k)->Y2,(EE+k)->Z2 );
	fclose(p1);
}
long EXPORTED_DLL_FUNCTION SendValue1(EngarveElement *p)
{
	int k;
	FILE *p1;
	p1=fopen("data1.txt","w");
	for(k=0;k<n;k++)
	{
		(EE+k)->CCW+=1;
		(p+k)->CCW=(EE+k)->CCW;
		(EE+k)->Type+=1;
		(p+k)->Type=(EE+k)->Type;
		(EE+k)->X1+=1;
		(p+k)->X1=(EE+k)->X1;
		(EE+k)->Y1+=1;
		(p+k)->Y1=(EE+k)->Y1;
		(EE+k)->Z1+=1;
		(p+k)->Z1=(EE+k)->Z1;
		(EE+k)->X2+=1;
		(p+k)->X2=(EE+k)->X2;
		(EE+k)->Y2+=1;
		(p+k)->Y2=(EE+k)->Y2;
		(EE+k)->Z2+=1;
		(p+k)->Z2=(EE+k)->Z2;
		fprintf(p1,"%d\t%d\t%f\t%f\t%f\t%f\t%f\t%f\n",(EE+k)->CCW ,(EE+k)->Type,(EE+k)->X1,(EE+k)->Y1,(EE+k)->Z1,(EE+k)->X2,(EE+k)->Y2,(EE+k)->Z2 );
	}
	fclose(p1);
	return n;
}
CtestEngravingApp::CtestEngravingApp()
{
	// TODO: �b���[�J�غc�{���X�A
	// �N�Ҧ����n����l�]�w�[�J InitInstance ��
}


// �Ȧ����@�� CtestEngravingApp ����

CtestEngravingApp theApp;


// CtestEngravingApp ��l�]�w

BOOL CtestEngravingApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
