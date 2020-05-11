#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

typedef struct _CardInfo
{
    int intType;//�d������
    int intUsage;//�d���γ~
    int intConfiguration;//�����������

    int intPassThroughCounter;//�q�榸��
    int intHolidayWeekProgramValue;//�P�p�e+����q��]�w

    int intStartExpirationDate;//�d�����Ĵ����]�w
    int intEnd1eExpirationDate;//�d�����Ĵ����]�w
	char strStartExpirationDate[17];//'YYYYMMddHHmm'
	char strEndleExpirationDate[17];//'YYYYMMddHHmm'

    int intFirstPassThroughTimeRange;//�i�q��ɬq
    int intSecondPassThroughTimeRange;//�i�q��ɬq
    int intThirdPassThroughTimeRange;//�i�q��ɬq

    char strUserUniqueIdentifier[17];//�Τ��ѧO�X "AAAAAAAA"(PS���שM�쥻���P)
    char strScramblerCode[5];//�Z�X�]�w "aaaa"(PS���שM�쥻���P)

    //-----------------------------------------------------------
    //�������
    char strUserPasswordCode[9];//�ϥΪ̱K�X�]�w "12345678"(��@��)

    char strDoorName1[9];//���ϦW�ٳ]�w(�ϥ�����ArrayList�覡�s��) GWC_DOOR_NAME_LENGTH_MAXIMUM=8
    char strDoorName2[9];//���ϦW�ٳ]�w(�ϥ�����ArrayList�覡�s��) GWC_DOOR_NAME_LENGTH_MAXIMUM=8
    char strDoorName3[9];//���ϦW�ٳ]�w(�ϥ�����ArrayList�覡�s��) GWC_DOOR_NAME_LENGTH_MAXIMUM=8
    int intDoorNameSize;//����SIZE

    int intDoorAccess[1152];//���ϸs�ճ]�w(�ϥ�����ArrayList�覡�s��) MAX=1152
    int intDoorAccessSize;//����SIZE
}CardInfo;

#ifdef __cplusplus
extern "C"
{
#endif

void DLL_EXPORT SomeFunction(const LPCSTR sometext);
double DLL_EXPORT Add(double a, double b);//test_API
int DLL_EXPORT WCard_init();//�u�����@��
int DLL_EXPORT WCard_detectReader();//����Reader
int DLL_EXPORT WCard_read(CardInfo*& res);//Ū��
int DLL_EXPORT WCard_write(CardInfo &res);//�g�J
int DLL_EXPORT WCard_readTest();
int DLL_EXPORT WCard_writeTest(int state);
int DLL_EXPORT WCard_close();//�����ɰ���
#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
