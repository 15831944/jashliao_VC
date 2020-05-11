#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;
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
//SYWCardLib_H start
#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

double DLL_EXPORT Add(double a, double b);//test_API
int DLL_EXPORT WCard_init();
int DLL_EXPORT WCard_detectReader();
int DLL_EXPORT WCard_read(CardInfo*& res);//Ū��
int DLL_EXPORT WCard_write(CardInfo &res);//�g�J
int DLL_EXPORT WCard_readTest();
int DLL_EXPORT WCard_writeTest(int state);
int DLL_EXPORT WCard_close();
#ifdef __cplusplus
}
#endif
//SYWCardLib_H end
void C_pause()
{
    cout <<"Press Enter key to continue..."<< endl;
    fgetc(stdin);
}
int main()
{
    //cout << "Hello world!" << endl;
    cout << "3.1+6.9="<<Add(3.1,6.9)<< endl;
    if(WCard_init()==0)
    {
        int state;
        state=0;
        if(state==0)
        {
            CardInfo res;
            CardInfo *res1='\0';
            memset(&res,0,sizeof(CardInfo));
            res.intType=1;
            res.intUsage=1;
            res.intConfiguration=9;
            res.intPassThroughCounter=127;

            res.intHolidayWeekProgramValue=0xEF;

            strcpy(res.strStartExpirationDate,"2016/06/07/13/34");//'YYYYMMddHHmm'
            strcpy(res.strEndleExpirationDate,"2016/06/07/13/34");//'YYYYMMddHHmm'

            res.intFirstPassThroughTimeRange=100;//�i�q��ɬq
            res.intSecondPassThroughTimeRange=200;//�i�q��ɬq
            res.intThirdPassThroughTimeRange=300;//�i�q��ɬq

            strcpy(res.strUserUniqueIdentifier,"ABCDEFED");

            strcpy(res.strScramblerCode,"abcd");

            strcpy(res.strUserPasswordCode,"19810502");

            res.intDoorNameSize=1;
            strcpy(res.strDoorName1,"Door-99");

            res.intDoorAccessSize=1152;
            for(int i=1;i<1152;i+=2)
            {
                res.intDoorAccess[i]=1;
            }

            cout <<"WCard_writeTest = "<<WCard_write(res)<< endl;
            C_pause();//��d�����}Ū�d������A�^Ū�d������BEEP�~�i�H�i��U�@�Ӱʧ@
            cout <<"WCard_readTest = "<<WCard_read(res1)<< endl;

            cout <<"GWCCardGetTypet = "<< res1[0].intType << endl;
            cout <<"GWCCardGetUsaget = "<< res1[0].intUsage << endl;
            cout <<"GWCCardGetConfigurationt = "<< res1[0].intConfiguration << endl;
            cout <<"GWCCardGetPassThroughCountert = "<< res1[0].intPassThroughCounter << endl;
            cout <<"GWCCardGetHolidayWeekProgramValuet = "<< res1[0].intHolidayWeekProgramValue << endl;
            cout <<"GWCCardGetExpirationDatet = "<< res1[0].intStartExpirationDate << "~" << res1[0].intEnd1eExpirationDate << endl;
            cout <<"GWCCardGetPassThroughTimeRanget = "<< res1[0].intFirstPassThroughTimeRange << "," << res1[0].intSecondPassThroughTimeRange << "," << res1[0].intThirdPassThroughTimeRange << "," << endl;
            cout <<"GWCCardGetUserUniqueIdentifiert = "<< res1[0].strUserUniqueIdentifier << endl;
            cout <<"GWCCardGetScramblerCodet = "<< res1[0].strScramblerCode << endl;
            cout <<"GWCCardGetUserPasswordCodet = "<< res1[0].strUserPasswordCode << endl;
            cout <<"GWCCardFetchFirstDoorNamet = "<< res1[0].strDoorName1 << "," << res1[0].strDoorName2 << "," << res1[0].strDoorName3 << endl;
            cout <<"GWCCardFetchNextDoorAccess = " << endl;;
            for(int i=0;i<1152;i++)
            {
                if(res1[0].intDoorAccess[i]==1)
                {
                    cout <<"\t"<<(i+1) << endl;;
                }
            }
            delete res1;
            /*
            int state=WCard_detectReader();
            cout <<"WCard_detectReader="<<state<<endl;
            C_pause();
            cout <<"WCard_writeTest = "<<WCard_writeTest(1)<< endl;
            C_pause();//��d�����}Ū�d������A�^Ū�d������BEEP�~�i�H�i��U�@�Ӱʧ@
            cout <<"WCard_readTest = "<<WCard_readTest()<< endl;
            C_pause();
            cout <<"WCard_writeTest = "<<WCard_writeTest(0)<< endl;
            C_pause();
            cout <<"WCard_readTest = "<<WCard_readTest()<< endl;
            C_pause();
            */
        }
        else
        {
             cout <<"Detect Reader Fail..."<<state<<endl;
        }
        WCard_close();
    }
    C_pause();
    return 0;
}
