#include "main.h"

/*---------------------------------------------------------------------------*/
/* �]�t���Y�� */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �۩w�q�]�t�� =- */
/* �w���H�h�{���w�w�q�]�t�� */
#ifndef GHLD_LIBRARY
  #include "ghld_hallib_define.h"//���Q�sĶ at 2016/06/01
#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �зǥ]�t�� =- */
/* �b���f�t�w���H�h�{���w�w�q�ɤޤJ�����зǥ]�t�� */
#if ((!defined(GHLD_LIBRARY)) || (GHLD_LIBRARY == GHLD_LIBRARY_NONE))
  #include <stdio.h>//���Q�sĶ at 2016/06/01
  #include <string.h>//���Q�sĶ at 2016/06/01
  #include <unistd.h>//���Q�sĶ at 2016/06/01
  #include <conio.h>//���Q�sĶ at 2016/06/01
  #include <time.h>//���Q�sĶ at 2016/06/01
  #include <stdlib.h>//���Q�sĶ at 2016/06/01
#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �۩w�q�]�t�� =- */
#include "geh_exception_handler.h"
#include "gst_system_time.h"
#include "goc_object_control.h"
#include "gwc_control.h"

/*---------------------------------------------------------------------------*/
/* �Ȩѥ��ҲձM�Τ��`�Ʃw�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�α`�Ʃw�q�ŧi =- */
/*  */

/* �����Ҧ� at 2016/06/01
//�Q��GWC_READ_CARD_MODE�w�q�P�_ �]�w�O�_��Ū���Ҧ�
#define GWC_READ_CARD_MODE
//*/

/* �B�@�O�ɭ���ɶ��`�Ʃw�q�ŧi */
#define GWC_WAIT_AND_PRINT_INTERVAL_TIME_VALUE 125

/*---------------------------------------------------------------------------*/
/* �t�ΰ_�l�p��~���`�Ʃw�q */
#define GRTC_DATE_SINCE_YEARS 2015
/* �C�@�~�ѼƱ`�Ʃw�q */
#define GRTC_TIME_DAY_PER_YEARS 365
/* �C�p�ɤ����Ʊ`�Ʃw�q */
#define GRTC_TIME_HOURS_PER_DAY 24
/* �C�p�ɤ����Ʊ`�Ʃw�q */
#define GRTC_TIME_MINUTES_PER_HOUR 60
/* �C������Ʊ`�Ʃw�q */
#define GRTC_TIME_SECONDS_PER_MINUTE 60
/* �C�p�ɬ�Ʊ`�Ʃw�q */
#define GRTC_TIME_SECONDS_PER_HOUR (GRTC_TIME_SECONDS_PER_MINUTE * GRTC_TIME_MINUTES_PER_HOUR)
/* �C�@�Ѭ�Ʊ`�Ʃw�q */
#define GRTC_TIME_SECONDS_PER_DAY (GRTC_TIME_SECONDS_PER_HOUR * GRTC_TIME_HOURS_PER_DAY)
static const int g_iGRTCMonthElapsedDayList[13] =
{
    /*-----------------------------------------*/
    /* �C�� */
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365,
};

// a sample exported function
#define LogFile "WCardLib.log"

void DLL_EXPORT SomeFunction(const LPCSTR sometext)
{
    MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}
double DLL_EXPORT Add(double a, double b)//test_API
{
    return a + b;
}
//===================================================
typedef struct _GRTC_LOCAL_TIME_DATAGRAM_STRUCTURE
{
    /* Time */
    int iSecond; /* Seconds: 0-59 */
    int iMinutes; /* Minutes: 0-59 */
    int iHours; /* Hours since midnight: 0-23 */

    /* Date */
    int iMDay; /* Day of the month: 1-31 */
    int iMonths; /* Months *since* january: 0-11 */
    int iYears; /* Years *since* 2015 */
} GRTCLOCALTIME, *LPGRTCLOCALTIME;
/* ���o�t�ήɶ� (2015/01/01-00:00:00 �_�ܷ�U�`���) */
long GRTCGetTime(GRTCLOCALTIME *lpLocalTime)
{
    int iMDay, iYears, iMonths, iHours, iMinutes, iSecond;
    long lTotalDays, lTotalSecond;

    /* �p�G�S�����w�ɶ���Ƶ��c */
    if(lpLocalTime == NULL)
      {
        struct tm *lpSystemDatetime;
        time_t stmiSystemSeconds;

        /* �����Ѩt�Ψ��o��e�ɶ� */
        stmiSystemSeconds = time(NULL);
        lpSystemDatetime = localtime(&stmiSystemSeconds);

        /* �ץ��ƾڡA�ë�����p����ܼ� */
        iYears = lpSystemDatetime->tm_year;
        iMonths = lpSystemDatetime->tm_mon;
        iMDay = lpSystemDatetime->tm_mday;
        iHours = lpSystemDatetime->tm_hour;
        iMinutes = lpSystemDatetime->tm_min;
        iSecond = lpSystemDatetime->tm_sec;
      }
    /* ���w�F�ɶ���Ƶ��c */
    else
      {
        /* �ץ��ƾڡA�ë�����p����ܼ� */
        iYears = lpLocalTime->iYears;
        iMonths = lpLocalTime->iMonths;
        iMDay = lpLocalTime->iMDay;
        iHours = lpLocalTime->iHours;
        iMinutes = lpLocalTime->iMinutes;
        iSecond = lpLocalTime->iSecond;
      }

    /* �p���`�Ѽ� */
    lTotalDays = (long)(g_iGRTCMonthElapsedDayList[iMonths] + (iMDay - 1) + (iYears * GRTC_TIME_DAY_PER_YEARS));

    /* finally seconds */
    lTotalSecond = (((((lTotalDays * GRTC_TIME_HOURS_PER_DAY) + iHours) * GRTC_TIME_MINUTES_PER_HOUR) + iMinutes) * GRTC_TIME_SECONDS_PER_MINUTE) + iSecond;

    return lTotalSecond;
}

//WCard_API Start
static int g_intDebug;
static int g_RunOne=1;
static GWCONTROLDS *lpControlDS;
static GWCREADERDS *lpReaderDS;
static GWCARDDS *lpWCardDS;
static int iStatus, iReaderStatus;
void GWCCALLBACK GWCStageCallback(void *lpOPStageCBParameter)
{
    lpOPStageCBParameter = lpOPStageCBParameter;

    //GWCWaitAndPrint(TRUE);
}

void WriteLog(const char *Msg,int state)
{
    if(g_intDebug==1)
    {
        FILE *pf='\0';
        if(state==1)
        {
            pf=fopen(LogFile,"w");
        }
        else
        {
            pf=fopen(LogFile,"a");
        }
        fprintf(pf,Msg);
        fprintf(pf, "\n");
        fclose(pf);
    }
}

int DLL_EXPORT WCard_init()//�ܼƪ�l��
{
    g_intDebug=1;//�M�w�O�_����Log File�X��

    lpControlDS = NULL;
    lpReaderDS = NULL;
    lpWCardDS = NULL;
    iStatus=-1;
    iReaderStatus=-1;
    /* -= ���󱱨��l�� =- */
    WriteLog("WCard_init...Start",1);
    if(g_RunOne==1)
    {
        GOCObjectControlInitialize();
        WriteLog("GOCObjectControlInitialize() Run",0);
        g_RunOne=0;
    }


    /* -= WCard Library ��l�� =- */
    WriteLog("\t[Library] GWCInitialize...",0);
    if(GWCInitialize() < 0)
    {
        WriteLog("\tGWCInitialize error!!",0);
        return (-1);
    }

    /* -= Control �Ҳ� =- */
    /* �إ� Control */
    WriteLog("\t[Control] GWCCreate...",0);
    if((lpControlDS = GWCCreate()) == NULL)
    {
        WriteLog("\tGWCCreate error!!",0);

        GWCTerminate();

        return (-2);
    }

    /* -= Reader �Ҳ� =- */
    /* �إ� Reader */
    WriteLog("\t[Reader] GWCReaderCreate...",0);
    if((lpReaderDS = GWCReaderCreate()) == NULL)
    {
        WriteLog("\tGWCReaderCreate error!!",0);

        GWC_SAFE_DESTROY(lpControlDS);

        GWCTerminate();

        return (-3);
    }

    /* -= WCard �Ҳ� =- */
    /* �إ� WCard */
    WriteLog("\t[WCard] GWCCardCreate...",0);
    if((lpWCardDS = GWCCardCreate()) == NULL)
    {
        WriteLog("\tGWCCardCreate error!!",0);

        GWC_SAFE_READER_DESTROY(lpReaderDS)
        GWC_SAFE_DESTROY(lpControlDS);

        GWCTerminate();

        return (-4);
    }
    WriteLog("WCard_init...finish",0);
    return (0);
}

int DLL_EXPORT WCard_detectReader()//����Reader
{
    WriteLog("WCard_open...Start",0);

    /* -= Control �ާ@ =- */
    /* ��w���w�� Reader �� Control */
    WriteLog("\t[Control] GWCSelect...",0);
    if(GWCSelect(lpControlDS, lpReaderDS, NULL) < 0)
    {
        WriteLog("\tGWCSelect error!!",0);
        return (-1);
        //break;
    }

    /* Control �Ұ� */
    WriteLog("\t[Control] GWCStart...",0);
    if(GWCStart(lpControlDS) < 0)
    {
        WriteLog("\tGWCStart error!!",0);
        return (-2);
        //break;
    }

    /* �ˬd�ýT�w Control ���A���n */
    WriteLog("\t[Control] GWCGetStatus...",0);
    while((iStatus = GWCGetStatus(lpControlDS)) != GWC_STATUS_OK)
    {
        //GWCWaitAndPrint(TRUE);

        /* �H�U���A�N�ݩ���~ */
        if((iStatus == GWC_STATUS_ERROR) ||
            (iStatus == GWC_STATUS_NO_DEVICE) ||
            (iStatus == GWC_STATUS_ERROR_DEVICE) ||
            (iStatus == GWC_STATUS_INTERNAL_ERROR))
        {
            break;
        }
    }

    /* ���R�@�U���G�� */
    if(iStatus == GWC_STATUS_OK)
    {
        WriteLog("\tGWC_STATUS_OK!!",0);
    }
    else if(iStatus == GWC_STATUS_ERROR)
    {
        WriteLog("\tGWC_STATUS_ERROR!!",0);
        return (-3);
        //break;
    }
    else if(iStatus == GWC_STATUS_NO_DEVICE)
    {
        WriteLog("\tGWC_STATUS_NO_DEVICE!!",0);
        return (-4);
        //break;
    }
    else if(iStatus == GWC_STATUS_ERROR_DEVICE)
    {
        WriteLog("\tGWC_STATUS_ERROR_DEVICE!!",0);
        return (-5);
        //break;
    }
    else if(iStatus == GWC_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_STATUS_INTERNAL_ERROR!!",0);
        return (-6);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-7);
        //break;
    }

    WriteLog("WCard_open...finish",0);
    return (0);
}

int DLL_EXPORT WCard_read(CardInfo*& res)//Ū��
{
	res = new CardInfo[1];
	memset(res, 0, sizeof(res[0]));

    WriteLog("WCard_readTest...Start",0);
    /* �N WCard �j�w�� Reader */
    WriteLog("\t[Reader] GWCReaderBindCard...\n",0);;
    if(GWCReaderBindCard(lpReaderDS, NULL, NULL, NULL, NULL, 1) < 0)
    {
        WriteLog("\tGWCReaderBindCard error!!",0);
        return (-1);
        //break;
    }

    //--
    /* -= Control �ާ@ =- */
    /* ��w���w�� Reader �� Control */
    WriteLog("\t[Control] GWCSelect...",0);
    if(GWCSelect(lpControlDS, lpReaderDS, NULL) < 0)
    {
        WriteLog("\tGWCSelect error!!",0);
        return (-2);
        //break;
    }

    /* Control �Ұ� */
    WriteLog("\t[Control] GWCStart...",0);
    if(GWCStart(lpControlDS) < 0)
    {
        WriteLog("\tGWCStart error!!",0);
        return (-3);
        //break;
    }

    /* �ˬd�ýT�w Control ���A���n */
    WriteLog("\t[Control] GWCGetStatus...",0);
    while((iStatus = GWCGetStatus(lpControlDS)) != GWC_STATUS_OK)
    {
        //GWCWaitAndPrint(TRUE);

        /* �H�U���A�N�ݩ���~ */
        if((iStatus == GWC_STATUS_ERROR) ||
            (iStatus == GWC_STATUS_NO_DEVICE) ||
            (iStatus == GWC_STATUS_ERROR_DEVICE) ||
            (iStatus == GWC_STATUS_INTERNAL_ERROR))
        {
            break;
        }
    }

    /* ���R�@�U���G�� */
    if(iStatus == GWC_STATUS_OK)
    {
        WriteLog("\tGWC_STATUS_OK!!",0);
    }
    else if(iStatus == GWC_STATUS_ERROR)
    {
        WriteLog("\tGWC_STATUS_ERROR!!",0);
        return (-4);
        //break;
    }
    else if(iStatus == GWC_STATUS_NO_DEVICE)
    {
        WriteLog("\tGWC_STATUS_NO_DEVICE!!",0);
        return (-5);
        //break;
    }
    else if(iStatus == GWC_STATUS_ERROR_DEVICE)
    {
        WriteLog("\tGWC_STATUS_ERROR_DEVICE!!",0);
        return (-6);
        //break;
    }
    else if(iStatus == GWC_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_STATUS_INTERNAL_ERROR!!",0);
        return (-7);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-8);
        //break;
    }
    //--

    /* �b�ثe�� Control �W�A�i��d��Ū���ާ@ */
    WriteLog("\t[Control] GWCReadCard...",0);
    if(GWCReadCard(lpControlDS, GWCStageCallback, NULL) < 0)
    {
        WriteLog("\tGWCWriteCard error!!",0);
        return (-9);
        //break;
    }

    /* �ˬd�ýT�w Control ���A���n */
    WriteLog("\t[Control] GWCGetStatus...",0);
    if((iStatus = GWCGetStatus(lpControlDS)) == GWC_STATUS_OK)
    {
        WriteLog("\tGWC_STATUS_OK!!",0);
    }
    else if(iStatus == GWC_STATUS_ERROR)
    {
        WriteLog("\tGWC_STATUS_ERROR!!",0);
        return (-10);
        //break;
    }
    else if(iStatus == GWC_STATUS_NO_DEVICE)
    {
        WriteLog("\tGWC_STATUS_NO_DEVICE!!",0);
        return (-11);
        //break;
    }
    else if(iStatus == GWC_STATUS_ERROR_DEVICE)
    {
        WriteLog("\tGWC_STATUS_ERROR_DEVICE!!",0);
        return (-12);
        //break;
    }
    else if(iStatus == GWC_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_STATUS_INTERNAL_ERROR!!",0);
        return (-13);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-14);
        //break;
    }

    /* �ˬd�ýT�w Reader ���A���n */
    WriteLog("\t[Reader] GWCReaderGetStatus...",0);
    if((iReaderStatus = GWCReaderGetStatus(lpReaderDS)) == GWC_READER_STATUS_OK)
    {
        WriteLog("\tGWC_READER_STATUS_OK!!\n",0);
    }
    else if(iReaderStatus == GWC_READER_STATUS_ERROR)
    {
        WriteLog("\tGWC_READER_STATUS_ERROR!!",0);
        return (-15);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_TIMEOUT)
    {
        WriteLog("\tGWC_READER_STATUS_TIMEOUT!!",0);
        return (-16);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_NO_CARD)
    {
        WriteLog("\tGWC_READER_STATUS_NO_CARD!!",0);
        return (-17);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_ACCESS_DENY)
    {
        WriteLog("\tGWC_READER_STATUS_ACCESS_DENY!!",0);
        return (-18);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_FORMAT_ERROR)
    {
        WriteLog("\tGWC_READER_STATUS_FORMAT_ERROR!!",0);
        return (-19);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_READER_STATUS_INTERNAL_ERROR!!",0);
        return (-20);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-21);
        //break;
    }

    /* Control ���� */
    WriteLog("\t[Control] GWCStop...",0);
    if(GWCStop(lpControlDS) < 0)
    {
        WriteLog("\tGWCStop error!!",0);
        return (-22);
        //break;
    }

    /* -= Reader �ާ@ =- */
    /* �q Reader ���� WCard ��ƨ��^ */
    WriteLog("\t[Reader] GWCReaderGetCard...",0);
    if(GWCReaderGetCard(lpReaderDS, lpWCardDS) < 0)
    {
        WriteLog("\tGWCReaderGetCard error!!",0);
        return (-23);
        //break;
    }

    int iValue;

    /* -= WCard �ާ@ =- */
    /* ���X WCard �����Ѽ� */

    if((iValue = GWCCardGetType(lpWCardDS)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-24);
        //break;
    }
    char buffer [200];
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetType...%d",iValue);
    res[0].intType=iValue;
    WriteLog(buffer,0);
    //fprintf(stdout, "%d\n", iValue);

    /* ���X WCard �����Ѽ� */

    if((iValue = GWCCardGetUsage(lpWCardDS)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-25);
        //break;
    }
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetUsage...%d",iValue);
    res[0].intUsage=iValue;
    WriteLog(buffer,0);
    //fprintf(stdout, "%d\n", iValue);

    /* ���X WCard �����Ѽ� */
    if((iValue = GWCCardGetConfiguration(lpWCardDS)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-26);
        //break;
    }
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetConfiguration...%d",iValue);
    res[0].intConfiguration=iValue;
    WriteLog(buffer,0);
    //fprintf(stdout, "%d\n", iValue);

    /* ���X WCard �����Ѽ� */
    if((iValue = GWCCardGetPassThroughCounter(lpWCardDS)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-27);
        //break;
    }
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetPassThroughCounter...%d",iValue);
    res[0].intPassThroughCounter=iValue;
    WriteLog(buffer,0);
    //fprintf(stdout, "%d\n", iValue);

    /* ���X WCard �����Ѽ� */
    if((iValue = GWCCardGetHolidayWeekProgramValue(lpWCardDS)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-28);
        //break;
    }
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetHolidayWeekProgramValue...0x%02X",iValue);
    res[0].intHolidayWeekProgramValue=iValue;
    WriteLog(buffer,0);
    //fprintf(stdout, "0x%02X\n", iValue);

    int iEndleExpirationDate, iStartUpExpirationDate;

    /* ���X WCard �����Ѽ� */
    if(GWCCardGetExpirationDate(lpWCardDS, &iStartUpExpirationDate, &iEndleExpirationDate) < 0)
    {
        WriteLog("\tError!!",0);
        return (-29);
        //break;
    }
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetExpirationDate...%d to %d",iStartUpExpirationDate, iEndleExpirationDate);
    res[0].intStartExpirationDate=iStartUpExpirationDate;
    res[0].intEnd1eExpirationDate=iEndleExpirationDate;
    WriteLog(buffer,0);
    //fprintf(stdout, "%d to %d\n", iStartUpExpirationDate, iEndleExpirationDate);

    int iFirstPassThroughTimeRange, iSecondPassThroughTimeRange, iThirdPassThroughTimeRange;

    /* ���X WCard �����Ѽ� */
    if(GWCCardGetPassThroughTimeRange(lpWCardDS, &iFirstPassThroughTimeRange, &iSecondPassThroughTimeRange, &iThirdPassThroughTimeRange) < 0)
    {
        WriteLog("\tError!!",0);
        return (-30);
        //break;
    }
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetPassThroughTimeRange...%d, %d, %d",iFirstPassThroughTimeRange, iSecondPassThroughTimeRange, iThirdPassThroughTimeRange);
    res[0].intFirstPassThroughTimeRange=iFirstPassThroughTimeRange;
    res[0].intSecondPassThroughTimeRange=iSecondPassThroughTimeRange;
    res[0].intThirdPassThroughTimeRange=iThirdPassThroughTimeRange;
    WriteLog(buffer,0);
    //fprintf(stdout, "%d, %d, %d\n", iFirstPassThroughTimeRange, iSecondPassThroughTimeRange, iThirdPassThroughTimeRange);

    BYTE bytUserUniqueIdentifier[GWC_USER_UNIQUE_IDENTIFIER_LENGTH_MAXIMUM];

    /* ���X WCard �����Ѽ� */
    if(GWCCardGetUserUniqueIdentifier(lpWCardDS, bytUserUniqueIdentifier) < 0)
    {
        WriteLog("\tError!!",0);
        return (-31);
        //break;
    }
    /*
    for(i = 0; i < GWC_USER_UNIQUE_IDENTIFIER_LENGTH_MAXIMUM; i ++)
    {
        fprintf(stdout, "%02X", bytUserUniqueIdentifier[i]);
    }
    fprintf(stdout, "\n");
    */
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    strcpy(buffer,"\t[WCard] GWCCardGetUserUniqueIdentifier...");
    int len=strlen(buffer);
    int j=0;
    for(int i = len; i < (len+GWC_USER_UNIQUE_IDENTIFIER_LENGTH_MAXIMUM); i ++)
    {
        buffer[i]=bytUserUniqueIdentifier[j];
        res->strUserUniqueIdentifier[j]=buffer[i];
        j++;
    }
    //strcat(buffer,(const char *)bytUserUniqueIdentifier);
    WriteLog(buffer,0);

    BYTE bytScramblerCode[GWC_SCRAMBLER_CODE_LENGTH_MAXIMUM];

    /* ���X WCard �����Ѽ� */

    if(GWCCardGetScramblerCode(lpWCardDS, bytScramblerCode) < 0)
    {
        WriteLog("\tError!!",0);
        return (-32);
        //break;
    }
    /*
    for(i = 0; i < GWC_SCRAMBLER_CODE_LENGTH_MAXIMUM; i ++)
    {
        fprintf(stdout, "%02X", bytScramblerCode[i]);
    }
    fprintf(stdout, "\n");
    */
    memset(buffer,'\0',sizeof(buffer));//�O����M��
    strcpy(buffer,"\t[WCard] GWCCardGetScramblerCode...");
    len=strlen(buffer);
    j=0;
    for(int i = len; i < (len+GWC_SCRAMBLER_CODE_LENGTH_MAXIMUM); i ++)
    {
        buffer[i]=bytScramblerCode[j];
        res->strScramblerCode[j]=buffer[i];
        j++;
    }
    //strcat(buffer,(const char *)bytScramblerCode);
    WriteLog(buffer,0);

    BYTE bytUserPasswordCode[GWC_USER_PASSWORD_CODE_LENGTH_MAXIMUM];

    /* ���X WCard �����Ѽ� */
    if(GWCCardGetUserPasswordCode(lpWCardDS, bytUserPasswordCode) < 0)
    {
        WriteLog("\tError!!",0);
        return (-33);
        //break;
    }
    /*
    for(i = 0; i < GWC_USER_PASSWORD_CODE_LENGTH_MAXIMUM; i ++)
    {
        fprintf(stdout, "%02X", bytUserPasswordCode[i]);
    }
    fprintf(stdout, "\n");
    */
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    strcpy(buffer,"\t[WCard] GWCCardGetUserPasswordCode...");
    len=strlen(buffer);
    j=0;
    for(int i = len; i < (len+GWC_USER_PASSWORD_CODE_LENGTH_MAXIMUM); i ++)
    {
        buffer[i]=bytUserPasswordCode[j];
        res->strUserPasswordCode[j]=buffer[i];
        j++;
    }
    //strcat(buffer, (const char *)bytUserPasswordCode);
    WriteLog(buffer,0);

    char strNameString[GWC_DOOR_NAME_LENGTH_MAXIMUM + 1];
    GWCARDFDNDS *lpWCardFetchDoorNameDS = NULL;
    int iNameLength;
    int j1=0;

    /* ���X WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardFetchFirstDoorName...",0);
    if((iNameLength = GWCCardFetchFirstDoorName(lpWCardDS, &lpWCardFetchDoorNameDS, (BYTE *)strNameString)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-34);
        //break;
    }
    else if(iNameLength == 0)
    {
        WriteLog("\tHave no door name.",0);
    }
    else
    {
        WriteLog("\t\t[WCard] GWCCardFetchNextDoorName...",0);

        do
        {
            if(iNameLength >= GWC_DOOR_NAME_LENGTH_MAXIMUM)
            {
                iNameLength = GWC_DOOR_NAME_LENGTH_MAXIMUM;
            }

            strNameString[iNameLength] = '\0';
            if(j1==0)
            {
                strcpy(res[0].strDoorName1,strNameString);
            }
            else if(j1==1)
            {
                strcpy(res[0].strDoorName2,strNameString);
            }
            else
            {
                strcpy(res[0].strDoorName3,strNameString);
            }
            j1++;
            memset (buffer,'\0',sizeof(buffer));//�O����M��
            sprintf (buffer, "\t\t\t%s", strNameString);
            WriteLog(buffer,0);
        }
        while((iNameLength = GWCCardFetchNextDoorName(lpWCardFetchDoorNameDS, (BYTE *)strNameString)) > 0);

        GWCCardFetchCloseDoorName(lpWCardFetchDoorNameDS);

        if(iNameLength < 0)
        {
            WriteLog("\tError!!",0);
            return (-35);
            //break;
        }

    }

    GWCARDFDADS *lpWCardFetchDoorAccessDS = NULL;
    int iNumber;

    /* ���X WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardFetchFirstDoorAccess...",0);
    if((iNumber = GWCCardFetchFirstDoorAccess(lpWCardDS, &lpWCardFetchDoorAccessDS)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-36);
        //break;
    }
    else if(iNumber == 0)
    {
        WriteLog("\t\tHave no door access.",0);
    }
    else
    {

        WriteLog("\t\t[WCard] GWCCardFetchNextDoorAccess...",0);

        do
        {
            memset (buffer,'\0',sizeof(buffer));//�O����M��
            res[0].intDoorAccess[(iNumber-1)]=1;
            sprintf (buffer,"\t\t\t%d",iNumber);
            WriteLog(buffer,0);
        }
        while((iNumber = GWCCardFetchNextDoorAccess(lpWCardFetchDoorAccessDS)) > 0);

        GWCCardFetchCloseDoorAccess(lpWCardFetchDoorAccessDS);

        if(iNumber < 0)
        {
            WriteLog("\tError!!",0);
            return (-37);
            //break;
        }

        //fprintf(stdout, "\n");
    }
    WriteLog("WCard_readTest....finish",0);
    return 0;
}

int DLL_EXPORT WCard_write(CardInfo &res)//�g�J
{
    char buffer [200];
    memset (buffer,'\0',sizeof(buffer));//�O����M��

    //sprintf (buffer, "WCard_writeTest....Start",state);//WriteLog("WCard_writeTest....Start",0);
    WriteLog("WCard_write....Start",0);

    /* -= WCard �ާ@ =- */
    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetType...",0);
    if(GWCCardSetType(lpWCardDS, res.intType) < 0)//if(GWCCardSetType(lpWCardDS, GWC_WCARD_TYPE_NORMAL) < 0)
    {
        WriteLog("\tGWCCardSetType error!!",0);
        return (-1);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetUsage...",0);
    if(GWCCardSetUsage(lpWCardDS, res.intUsage) < 0)//if(GWCCardSetUsage(lpWCardDS, GWC_WCARD_USAGE_FOR_NORMAL) < 0)
    {
        WriteLog("\tGWCCardSetUsage error!!",0);
        return (-2);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetConfiguration...",0);
    if(GWCCardSetConfiguration(lpWCardDS, res.intConfiguration) < 0)//if(GWCCardSetConfiguration(lpWCardDS, GWC_WCARD_CONFIGURATION_1152_DOOR_1_NAME_WITH_PASSWORD) < 0)
    {
        WriteLog("\tGWCCardSetConfiguration error!!",0);
        return (-3);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetPassThroughCounter...",0);
    if(GWCCardSetPassThroughCounter(lpWCardDS, res.intPassThroughCounter) < 0)//if(GWCCardSetPassThroughCounter(lpWCardDS, 128) < 0)
    {
        WriteLog("\tGWCCardSetPassThroughCounter error!!",0);
        return (-4);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetHolidayWeekProgramValue...",0);
    if(GWCCardSetHolidayWeekProgramValue(lpWCardDS, res.intHolidayWeekProgramValue) < 0)//if(GWCCardSetHolidayWeekProgramValue(lpWCardDS, 0xfe) < 0)
    {
        WriteLog("\tGWCCardSetHolidayWeekProgramValue error!!",0);
        return (-5);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetExpirationDate...",0);
    GRTCLOCALTIME gltLocalTime;
    char strYear[6],strMonth[6],strDay[6],strHour[6],strMinute[6];

    memset(&gltLocalTime, 0, sizeof(GRTCLOCALTIME));
    sscanf (res.strEndleExpirationDate ,"%[^/]/%[^/]/%[^/]/%[^/]/%s",strYear,strMonth,strDay,strHour,strMinute);
	gltLocalTime.iYears = atoi(strYear)-2015;
    gltLocalTime.iMonths = atoi(strMonth)-1;
    gltLocalTime.iMDay = atoi(strDay);
	gltLocalTime.iHours=atoi(strHour);
	gltLocalTime.iMinutes=atoi(strMinute);
	gltLocalTime.iSecond=0;
    res.intEnd1eExpirationDate=(GRTCGetTime(&gltLocalTime)/60);

    memset(&gltLocalTime, 0, sizeof(GRTCLOCALTIME));
    sscanf (res.strStartExpirationDate ,"%[^/]/%[^/]/%[^/]/%[^/]/%s",strYear,strMonth,strDay,strHour,strMinute);
	gltLocalTime.iYears = atoi(strYear)-2015;
    gltLocalTime.iMonths = atoi(strMonth)-1;
    gltLocalTime.iMDay = atoi(strDay);
	gltLocalTime.iHours=atoi(strHour);
	gltLocalTime.iMinutes=atoi(strMinute);
	gltLocalTime.iSecond=0;
    res.intStartExpirationDate=(GRTCGetTime(&gltLocalTime)/60);

    if(GWCCardSetExpirationDate(lpWCardDS, res.intStartExpirationDate, res.intEnd1eExpirationDate) < 0)//if(GWCCardSetExpirationDate(lpWCardDS, 200, 200) < 0)
    {
        WriteLog("\tGWCCardSetExpirationDate error!!",0);
        return (-6);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetPassThroughTimeRange...",0);
    if(GWCCardSetPassThroughTimeRange(lpWCardDS, res.intFirstPassThroughTimeRange, res.intSecondPassThroughTimeRange, res.intThirdPassThroughTimeRange) < 0)//if(GWCCardSetPassThroughTimeRange(lpWCardDS, 100, 100, 100) < 0)
    {
        WriteLog("\tGWCCardSetPassThroughTimeRange error!!",0);
        return (-7);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetUserUniqueIdentifier...",0);
    BYTE UserUniqueIdentifier[8];//"AAAAAAAA" jash.liao add at 2016/0601
    /*
    if(state==0)
    {
        memset (UserUniqueIdentifier,'A',sizeof(UserUniqueIdentifier));
    }
    else
    {
        memset (UserUniqueIdentifier,'B',sizeof(UserUniqueIdentifier));
    }
    */
    for(int i=0;i<8;i++)
    {
        UserUniqueIdentifier[i]=res.strUserUniqueIdentifier[i];
    }
    if(GWCCardSetUserUniqueIdentifier(lpWCardDS, UserUniqueIdentifier) < 0)
    {
        WriteLog("\tGWCCardSetUserUniqueIdentifier error!!",0);
        return (-8);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardGetScramblerCode...",0);
    BYTE ScramblerCode[4];//"aaaa" jash.liao add at 2016/0601
    /*
    if(state==0)
    {
        memset (ScramblerCode,'a',sizeof(ScramblerCode));
    }
    else
    {
        memset (ScramblerCode,'b',sizeof(ScramblerCode));
    }
    */
    for(int i=0;i<4;i++)
    {
        ScramblerCode[i]=res.strScramblerCode[i];
    }
    if(GWCCardSetScramblerCode(lpWCardDS, ScramblerCode) < 0)
    {
        WriteLog("\tGWCCardGetScramblerCode error!!",0);
        return (-9);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetUserPasswordCode...",0);
    BYTE UserPasswordCode[8];//"12345678" jash.liao add at 2016/0601
    /*
    if(state==0)
    {
        memset (UserPasswordCode,'1',sizeof(UserPasswordCode));
    }
    else
    {
        memset (UserPasswordCode,'2',sizeof(UserPasswordCode));
    }
    */
    for(int i=0;i<8;i++)
    {
        UserPasswordCode[i]=res.strUserPasswordCode[i];
    }
    if(GWCCardSetUserPasswordCode(lpWCardDS, UserPasswordCode) < 0)
    {
        WriteLog("\tGWCCardSetUserPasswordCode error!!",0);
        return (-10);
        //break;
    }

    bool bError;
    int i;

    /* �]�m WCard �����Ѽ� */
    bError = FALSE;
    WriteLog("\t[WCard] GWCCardAddDoorName...",0);
    for(i = 0; i < res.intDoorNameSize; i++)//for(i = 0; i < 3; i ++)
    {
        BYTE bytDoorName[GWC_DOOR_NAME_LENGTH_MAXIMUM];

        memset(bytDoorName, 0, GWC_DOOR_NAME_LENGTH_MAXIMUM);
        //sprintf((char *)bytDoorName, "Door-%02d", (i + 1));
        switch(i)
        {
            case 0:
                for(int j=0;j<GWC_DOOR_NAME_LENGTH_MAXIMUM;j++)
                {
                    bytDoorName[j]=res.strDoorName1[j];
                }
                break;
            case 1:
                for(int j=0;j<GWC_DOOR_NAME_LENGTH_MAXIMUM;j++)
                {
                    bytDoorName[j]=res.strDoorName2[j];
                }
                break;
            case 2:
                for(int j=0;j<GWC_DOOR_NAME_LENGTH_MAXIMUM;j++)
                {
                    bytDoorName[j]=res.strDoorName3[j];
                }
                break;
        }//switch-case end
        sprintf (buffer, "\t\t%s",bytDoorName);//WriteLog("WCard_writeTest....Start",0);
        WriteLog(buffer,0);
        if(GWCCardAddDoorName(lpWCardDS, bytDoorName, strlen((char *)bytDoorName)) < 0)
        {
            WriteLog("\tGWCCardAddDoorName error!!",0);

            bError = TRUE;

            break;
        }
    }

    if(bError)
    {
        return (-11);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    bError = FALSE;
    WriteLog("\t[WCard] GWCCardAddDoorAccess...",0);
    for(i = 0; i < res.intDoorAccessSize; i ++)//for(i = 0; i < 1152; i += 2)
    {
        //fprintf(stdout, "%d, ", (i + 1));
        if(res.intDoorAccess[i]==1)
        {
            if(GWCCardAddDoorAccess(lpWCardDS, (i+1)) < 0)
            {
                WriteLog("\tGWCCardAddDoorAccess error!!",0);

                bError = TRUE;

                break;
            }
        }
    }

    if(bError)
    {
        return (-11);
        //break;
    }

    /* �N WCard �j�w�� Reader */
    WriteLog("\t[Reader] GWCReaderBindCard...",0);
    if(GWCReaderBindCard(lpReaderDS, lpWCardDS, NULL, NULL, NULL, 1) < 0)
    {
        WriteLog("\tGWCReaderBindCard error!!",0);
        return (-12);
        //break;
    }

    /* -= Control �ާ@ =- */
    /* ��w���w�� Reader �� Control */
    WriteLog("\t[Control] GWCSelect...",0);
    if(GWCSelect(lpControlDS, lpReaderDS, NULL) < 0)
    {
        WriteLog("\tGWCSelect error!!",0);
        return (-13);
        //break;
    }

    /* Control �Ұ� */
    WriteLog("\t[Control] GWCStart...",0);
    if(GWCStart(lpControlDS) < 0)
    {
        WriteLog("\tGWCStart error!!",0);
        return (-14);
        //break;
    }

    //GWCWaitAndPrint(FALSE);

    /* �ˬd�ýT�w Control ���A���n */
    WriteLog("\t[Control] GWCGetStatus...",0);
    while((iStatus = GWCGetStatus(lpControlDS)) != GWC_STATUS_OK)
    {
        //GWCWaitAndPrint(TRUE);

        /* �H�U���A�N�ݩ���~ */
        if((iStatus == GWC_STATUS_ERROR) ||
            (iStatus == GWC_STATUS_NO_DEVICE) ||
            (iStatus == GWC_STATUS_ERROR_DEVICE) ||
            (iStatus == GWC_STATUS_INTERNAL_ERROR))
        {
            break;
        }
    }

    /* ���R�@�U���G�� */
    if(iStatus == GWC_STATUS_OK)
    {
        WriteLog("\tGWC_STATUS_OK!!",0);
    }
    else if(iStatus == GWC_STATUS_ERROR)
    {
        WriteLog("\tGWC_STATUS_ERROR!!",0);
        return (-15);
        //break;
    }
    else if(iStatus == GWC_STATUS_NO_DEVICE)
    {
        WriteLog("\tGWC_STATUS_NO_DEVICE!!",0);
        return (-16);
        //break;
    }
    else if(iStatus == GWC_STATUS_ERROR_DEVICE)
    {
        WriteLog("\tGWC_STATUS_ERROR_DEVICE!!",0);
        return (-17);
        //break;
    }
    else if(iStatus == GWC_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_STATUS_INTERNAL_ERROR!!",0);
        return (-18);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-19);
        //break;
    }

    //GWCWaitAndPrint(FALSE);

    /* �b�ثe�� Control �W�A�i��d���g�J�ާ@ */
    WriteLog("\t[Control] GWCWriteCard...",0);
    if(GWCWriteCard(lpControlDS, GWCStageCallback, NULL) < 0)
    {
        WriteLog("\tGWCWriteCard error!!",0);
        return (-21);
        //break;
    }

    //GWCWaitAndPrint(FALSE);

        /* �ˬd�ýT�w Control ���A���n */
    WriteLog("\t[Control] GWCGetStatus...",0);
    if((iStatus = GWCGetStatus(lpControlDS)) == GWC_STATUS_OK)
    {
        WriteLog("\tGWC_STATUS_OK!!",0);
    }
    else if(iStatus == GWC_STATUS_ERROR)
    {
        WriteLog("\tGWC_STATUS_ERROR!!",0);
        return (-22);
        //break;
    }
    else if(iStatus == GWC_STATUS_NO_DEVICE)
    {
        WriteLog("\tGWC_STATUS_NO_DEVICE!!",0);
        return (-23);
        //break;
    }
    else if(iStatus == GWC_STATUS_ERROR_DEVICE)
    {
        WriteLog("\tGWC_STATUS_ERROR_DEVICE!!",0);
        return (-24);
        //break;
    }
    else if(iStatus == GWC_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_STATUS_INTERNAL_ERROR!!",0);
        return (-25);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-26);
        //break;
    }

    /* �ˬd�ýT�w Reader ���A���n */
    WriteLog("\t[Reader] GWCReaderGetStatus...",0);
    if((iReaderStatus = GWCReaderGetStatus(lpReaderDS)) == GWC_READER_STATUS_OK)
    {
        WriteLog("\tGWC_READER_STATUS_OK!!",0);
    }
    else if(iReaderStatus == GWC_READER_STATUS_ERROR)
    {
        WriteLog("\tGWC_READER_STATUS_ERROR!!",0);
        return (-27);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_TIMEOUT)
    {
        WriteLog("\tGWC_READER_STATUS_TIMEOUT!!",0);
        return (-28);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_NO_CARD)
    {
        WriteLog("\tGWC_READER_STATUS_NO_CARD!!",0);
        return (-29);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_ACCESS_DENY)
    {
        WriteLog("\tGWC_READER_STATUS_ACCESS_DENY!!",0);
        return (-30);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_FORMAT_ERROR)
    {
        WriteLog("\tGWC_READER_STATUS_FORMAT_ERROR!!",0);
        return (-31);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_READER_STATUS_INTERNAL_ERROR!!",0);
        return (-32);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-33);
        //break;
    }

    /* Control ���� */
    WriteLog("\t[Control] GWCStop...",0);
    if(GWCStop(lpControlDS) < 0)
    {
        WriteLog("\tGWCStop error!!",0);
        return (-34);
        //break;
    }

    WriteLog("WCard_write....finish",0);
    return 0;
}

int DLL_EXPORT WCard_readTest()//Ū������[�n��open��X�i��]
{
    WriteLog("WCard_readTest...Start",0);
    /* �N WCard �j�w�� Reader */
    WriteLog("\t[Reader] GWCReaderBindCard...\n",0);;
    if(GWCReaderBindCard(lpReaderDS, NULL, NULL, NULL, NULL, 1) < 0)
    {
        WriteLog("\tGWCReaderBindCard error!!",0);
        return (-1);
        //break;
    }

    //--
    /* -= Control �ާ@ =- */
    /* ��w���w�� Reader �� Control */
    WriteLog("\t[Control] GWCSelect...",0);
    if(GWCSelect(lpControlDS, lpReaderDS, NULL) < 0)
    {
        WriteLog("\tGWCSelect error!!",0);
        return (-2);
        //break;
    }

    /* Control �Ұ� */
    WriteLog("\t[Control] GWCStart...",0);
    if(GWCStart(lpControlDS) < 0)
    {
        WriteLog("\tGWCStart error!!",0);
        return (-3);
        //break;
    }

    /* �ˬd�ýT�w Control ���A���n */
    WriteLog("\t[Control] GWCGetStatus...",0);
    while((iStatus = GWCGetStatus(lpControlDS)) != GWC_STATUS_OK)
    {
        //GWCWaitAndPrint(TRUE);

        /* �H�U���A�N�ݩ���~ */
        if((iStatus == GWC_STATUS_ERROR) ||
            (iStatus == GWC_STATUS_NO_DEVICE) ||
            (iStatus == GWC_STATUS_ERROR_DEVICE) ||
            (iStatus == GWC_STATUS_INTERNAL_ERROR))
        {
            break;
        }
    }

    /* ���R�@�U���G�� */
    if(iStatus == GWC_STATUS_OK)
    {
        WriteLog("\tGWC_STATUS_OK!!",0);
    }
    else if(iStatus == GWC_STATUS_ERROR)
    {
        WriteLog("\tGWC_STATUS_ERROR!!",0);
        return (-4);
        //break;
    }
    else if(iStatus == GWC_STATUS_NO_DEVICE)
    {
        WriteLog("\tGWC_STATUS_NO_DEVICE!!",0);
        return (-5);
        //break;
    }
    else if(iStatus == GWC_STATUS_ERROR_DEVICE)
    {
        WriteLog("\tGWC_STATUS_ERROR_DEVICE!!",0);
        return (-6);
        //break;
    }
    else if(iStatus == GWC_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_STATUS_INTERNAL_ERROR!!",0);
        return (-7);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-8);
        //break;
    }
    //--

    /* �b�ثe�� Control �W�A�i��d��Ū���ާ@ */
    WriteLog("\t[Control] GWCReadCard...",0);
    if(GWCReadCard(lpControlDS, GWCStageCallback, NULL) < 0)
    {
        WriteLog("\tGWCWriteCard error!!",0);
        return (-9);
        //break;
    }

    /* �ˬd�ýT�w Control ���A���n */
    WriteLog("\t[Control] GWCGetStatus...",0);
    if((iStatus = GWCGetStatus(lpControlDS)) == GWC_STATUS_OK)
    {
        WriteLog("\tGWC_STATUS_OK!!",0);
    }
    else if(iStatus == GWC_STATUS_ERROR)
    {
        WriteLog("\tGWC_STATUS_ERROR!!",0);
        return (-10);
        //break;
    }
    else if(iStatus == GWC_STATUS_NO_DEVICE)
    {
        WriteLog("\tGWC_STATUS_NO_DEVICE!!",0);
        return (-11);
        //break;
    }
    else if(iStatus == GWC_STATUS_ERROR_DEVICE)
    {
        WriteLog("\tGWC_STATUS_ERROR_DEVICE!!",0);
        return (-12);
        //break;
    }
    else if(iStatus == GWC_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_STATUS_INTERNAL_ERROR!!",0);
        return (-13);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-14);
        //break;
    }

    /* �ˬd�ýT�w Reader ���A���n */
    WriteLog("\t[Reader] GWCReaderGetStatus...",0);
    if((iReaderStatus = GWCReaderGetStatus(lpReaderDS)) == GWC_READER_STATUS_OK)
    {
        WriteLog("\tGWC_READER_STATUS_OK!!\n",0);
    }
    else if(iReaderStatus == GWC_READER_STATUS_ERROR)
    {
        WriteLog("\tGWC_READER_STATUS_ERROR!!",0);
        return (-15);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_TIMEOUT)
    {
        WriteLog("\tGWC_READER_STATUS_TIMEOUT!!",0);
        return (-16);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_NO_CARD)
    {
        WriteLog("\tGWC_READER_STATUS_NO_CARD!!",0);
        return (-17);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_ACCESS_DENY)
    {
        WriteLog("\tGWC_READER_STATUS_ACCESS_DENY!!",0);
        return (-18);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_FORMAT_ERROR)
    {
        WriteLog("\tGWC_READER_STATUS_FORMAT_ERROR!!",0);
        return (-19);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_READER_STATUS_INTERNAL_ERROR!!",0);
        return (-20);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-21);
        //break;
    }

    /* Control ���� */
    WriteLog("\t[Control] GWCStop...",0);
    if(GWCStop(lpControlDS) < 0)
    {
        WriteLog("\tGWCStop error!!",0);
        return (-22);
        //break;
    }

    /* -= Reader �ާ@ =- */
    /* �q Reader ���� WCard ��ƨ��^ */
    WriteLog("\t[Reader] GWCReaderGetCard...",0);
    if(GWCReaderGetCard(lpReaderDS, lpWCardDS) < 0)
    {
        WriteLog("\tGWCReaderGetCard error!!",0);
        return (-23);
        //break;
    }

    int iValue;

    /* -= WCard �ާ@ =- */
    /* ���X WCard �����Ѽ� */

    if((iValue = GWCCardGetType(lpWCardDS)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-24);
        //break;
    }
    char buffer [200];
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetType...%d",iValue);
    WriteLog(buffer,0);
    //fprintf(stdout, "%d\n", iValue);

    /* ���X WCard �����Ѽ� */

    if((iValue = GWCCardGetUsage(lpWCardDS)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-25);
        //break;
    }
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetUsage...%d",iValue);
    WriteLog(buffer,0);
    //fprintf(stdout, "%d\n", iValue);

    /* ���X WCard �����Ѽ� */
    if((iValue = GWCCardGetConfiguration(lpWCardDS)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-26);
        //break;
    }
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetConfiguration...%d",iValue);
    WriteLog(buffer,0);
    //fprintf(stdout, "%d\n", iValue);

    /* ���X WCard �����Ѽ� */
    if((iValue = GWCCardGetPassThroughCounter(lpWCardDS)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-27);
        //break;
    }
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetPassThroughCounter...%d",iValue);
    WriteLog(buffer,0);
    //fprintf(stdout, "%d\n", iValue);

    /* ���X WCard �����Ѽ� */
    if((iValue = GWCCardGetHolidayWeekProgramValue(lpWCardDS)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-28);
        //break;
    }
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetHolidayWeekProgramValue...0x%02X",iValue);
    WriteLog(buffer,0);
    //fprintf(stdout, "0x%02X\n", iValue);

    int iEndleExpirationDate, iStartUpExpirationDate;

    /* ���X WCard �����Ѽ� */
    if(GWCCardGetExpirationDate(lpWCardDS, &iStartUpExpirationDate, &iEndleExpirationDate) < 0)
    {
        WriteLog("\tError!!",0);
        return (-29);
        //break;
    }
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetExpirationDate...%d to %d",iStartUpExpirationDate, iEndleExpirationDate);
    WriteLog(buffer,0);
    //fprintf(stdout, "%d to %d\n", iStartUpExpirationDate, iEndleExpirationDate);

    int iFirstPassThroughTimeRange, iSecondPassThroughTimeRange, iThirdPassThroughTimeRange;

    /* ���X WCard �����Ѽ� */
    if(GWCCardGetPassThroughTimeRange(lpWCardDS, &iFirstPassThroughTimeRange, &iSecondPassThroughTimeRange, &iThirdPassThroughTimeRange) < 0)
    {
        WriteLog("\tError!!",0);
        return (-30);
        //break;
    }
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    sprintf (buffer, "\t[WCard] GWCCardGetPassThroughTimeRange...%d, %d, %d",iFirstPassThroughTimeRange, iSecondPassThroughTimeRange, iThirdPassThroughTimeRange);
    WriteLog(buffer,0);
    //fprintf(stdout, "%d, %d, %d\n", iFirstPassThroughTimeRange, iSecondPassThroughTimeRange, iThirdPassThroughTimeRange);

    BYTE bytUserUniqueIdentifier[GWC_USER_UNIQUE_IDENTIFIER_LENGTH_MAXIMUM];

    /* ���X WCard �����Ѽ� */
    if(GWCCardGetUserUniqueIdentifier(lpWCardDS, bytUserUniqueIdentifier) < 0)
    {
        WriteLog("\tError!!",0);
        return (-31);
        //break;
    }
    /*
    for(i = 0; i < GWC_USER_UNIQUE_IDENTIFIER_LENGTH_MAXIMUM; i ++)
    {
        fprintf(stdout, "%02X", bytUserUniqueIdentifier[i]);
    }
    fprintf(stdout, "\n");
    */
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    strcpy(buffer,"\t[WCard] GWCCardGetUserUniqueIdentifier...");
    int len=strlen(buffer);
    int j=0;
    for(int i = len; i < (len+GWC_USER_UNIQUE_IDENTIFIER_LENGTH_MAXIMUM); i ++)
    {
        buffer[i]=bytUserUniqueIdentifier[j];
        j++;
    }
    //strcat(buffer,(const char *)bytUserUniqueIdentifier);
    WriteLog(buffer,0);

    BYTE bytScramblerCode[GWC_SCRAMBLER_CODE_LENGTH_MAXIMUM];

    /* ���X WCard �����Ѽ� */

    if(GWCCardGetScramblerCode(lpWCardDS, bytScramblerCode) < 0)
    {
        WriteLog("\tError!!",0);
        return (-32);
        //break;
    }
    /*
    for(i = 0; i < GWC_SCRAMBLER_CODE_LENGTH_MAXIMUM; i ++)
    {
        fprintf(stdout, "%02X", bytScramblerCode[i]);
    }
    fprintf(stdout, "\n");
    */
    memset(buffer,'\0',sizeof(buffer));//�O����M��
    strcpy(buffer,"\t[WCard] GWCCardGetScramblerCode...");
    len=strlen(buffer);
    j=0;
    for(int i = len; i < (len+GWC_SCRAMBLER_CODE_LENGTH_MAXIMUM); i ++)
    {
        buffer[i]=bytScramblerCode[j];
        j++;
    }
    //strcat(buffer,(const char *)bytScramblerCode);
    WriteLog(buffer,0);

    BYTE bytUserPasswordCode[GWC_USER_PASSWORD_CODE_LENGTH_MAXIMUM];

    /* ���X WCard �����Ѽ� */
    if(GWCCardGetUserPasswordCode(lpWCardDS, bytUserPasswordCode) < 0)
    {
        WriteLog("\tError!!",0);
        return (-33);
        //break;
    }
    /*
    for(i = 0; i < GWC_USER_PASSWORD_CODE_LENGTH_MAXIMUM; i ++)
    {
        fprintf(stdout, "%02X", bytUserPasswordCode[i]);
    }
    fprintf(stdout, "\n");
    */
    memset (buffer,'\0',sizeof(buffer));//�O����M��
    strcpy(buffer,"\t[WCard] GWCCardGetUserPasswordCode...");
    len=strlen(buffer);
    j=0;
    for(int i = len; i < (len+GWC_USER_PASSWORD_CODE_LENGTH_MAXIMUM); i ++)
    {
        buffer[i]=bytUserPasswordCode[j];
        j++;
    }
    //strcat(buffer, (const char *)bytUserPasswordCode);
    WriteLog(buffer,0);

    char strNameString[GWC_DOOR_NAME_LENGTH_MAXIMUM + 1];
    GWCARDFDNDS *lpWCardFetchDoorNameDS = NULL;
    int iNameLength;

    /* ���X WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardFetchFirstDoorName...",0);
    if((iNameLength = GWCCardFetchFirstDoorName(lpWCardDS, &lpWCardFetchDoorNameDS, (BYTE *)strNameString)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-34);
        //break;
    }
    else if(iNameLength == 0)
    {
        WriteLog("\tHave no door name.",0);
    }
    else
    {
        WriteLog("\t\t[WCard] GWCCardFetchNextDoorName...",0);

        do
        {
            if(iNameLength >= GWC_DOOR_NAME_LENGTH_MAXIMUM)
            {
                iNameLength = GWC_DOOR_NAME_LENGTH_MAXIMUM;
            }

            strNameString[iNameLength] = '\0';
            memset (buffer,'\0',sizeof(buffer));//�O����M��
            sprintf (buffer, "\t\t\t%s", strNameString);
            WriteLog(buffer,0);
        }
        while((iNameLength = GWCCardFetchNextDoorName(lpWCardFetchDoorNameDS, (BYTE *)strNameString)) > 0);

        GWCCardFetchCloseDoorName(lpWCardFetchDoorNameDS);

        if(iNameLength < 0)
        {
            WriteLog("\tError!!",0);
            return (-35);
            //break;
        }

    }

    GWCARDFDADS *lpWCardFetchDoorAccessDS = NULL;
    int iNumber;

    /* ���X WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardFetchFirstDoorAccess...",0);
    if((iNumber = GWCCardFetchFirstDoorAccess(lpWCardDS, &lpWCardFetchDoorAccessDS)) < 0)
    {
        WriteLog("\tError!!",0);
        return (-36);
        //break;
    }
    else if(iNumber == 0)
    {
        WriteLog("\t\tHave no door access.",0);
    }
    else
    {

        WriteLog("\t\t[WCard] GWCCardFetchNextDoorAccess...",0);

        do
        {
            memset (buffer,'\0',sizeof(buffer));//�O����M��
            sprintf (buffer,"\t\t\t%d",iNumber);
            WriteLog(buffer,0);
        }
        while((iNumber = GWCCardFetchNextDoorAccess(lpWCardFetchDoorAccessDS)) > 0);

        GWCCardFetchCloseDoorAccess(lpWCardFetchDoorAccessDS);

        if(iNumber < 0)
        {
            WriteLog("\tError!!",0);
            return (-37);
            //break;
        }

        //fprintf(stdout, "\n");
    }
    WriteLog("WCard_readTest....finish",0);
    return 0;
}

int DLL_EXPORT WCard_writeTest(int state)//�g�J����[�n��open��X�i��]
{
    char buffer [200];
    memset (buffer,'\0',sizeof(buffer));//�O����M��

    sprintf (buffer, "WCard_writeTest....Start...%d",state);//WriteLog("WCard_writeTest....Start",0);
    WriteLog(buffer,0);

    /* -= WCard �ާ@ =- */
    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetType...",0);
    if(GWCCardSetType(lpWCardDS, GWC_WCARD_TYPE_NORMAL) < 0)
    {
        WriteLog("\tGWCCardSetType error!!",0);
        return (-1);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetUsage...",0);
    if(GWCCardSetUsage(lpWCardDS, GWC_WCARD_USAGE_FOR_NORMAL) < 0)
    {
        WriteLog("\tGWCCardSetUsage error!!",0);
        return (-2);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetConfiguration...",0);
    if(GWCCardSetConfiguration(lpWCardDS, GWC_WCARD_CONFIGURATION_1152_DOOR_1_NAME_WITH_PASSWORD) < 0)
    {
        WriteLog("\tGWCCardSetConfiguration error!!",0);
        return (-3);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetPassThroughCounter...",0);
    if(GWCCardSetPassThroughCounter(lpWCardDS, 128) < 0)
    {
        WriteLog("\tGWCCardSetPassThroughCounter error!!",0);
        return (-4);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetHolidayWeekProgramValue...",0);
    if(GWCCardSetHolidayWeekProgramValue(lpWCardDS, 0xfe) < 0)
    {
        WriteLog("\tGWCCardSetHolidayWeekProgramValue error!!",0);
        return (-5);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetExpirationDate...",0);
    if(GWCCardSetExpirationDate(lpWCardDS, 200, 200) < 0)
    {
        WriteLog("\tGWCCardSetExpirationDate error!!",0);
        return (-6);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetPassThroughTimeRange...",0);
    if(GWCCardSetPassThroughTimeRange(lpWCardDS, 100, 100, 100) < 0)
    {
        WriteLog("\tGWCCardSetPassThroughTimeRange error!!",0);
        return (-7);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetUserUniqueIdentifier...",0);
    BYTE UserUniqueIdentifier[8];//"AAAAAAAA" jash.liao add at 2016/0601
    if(state==0)
    {
        memset (UserUniqueIdentifier,'A',sizeof(UserUniqueIdentifier));
    }
    else
    {
        memset (UserUniqueIdentifier,'B',sizeof(UserUniqueIdentifier));
    }
    if(GWCCardSetUserUniqueIdentifier(lpWCardDS, UserUniqueIdentifier) < 0)
    {
        WriteLog("\tGWCCardSetUserUniqueIdentifier error!!",0);
        return (-8);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardGetScramblerCode...",0);
    BYTE ScramblerCode[4];//"aaaa" jash.liao add at 2016/0601
    if(state==0)
    {
        memset (ScramblerCode,'a',sizeof(ScramblerCode));
    }
    else
    {
        memset (ScramblerCode,'b',sizeof(ScramblerCode));
    }
    if(GWCCardSetScramblerCode(lpWCardDS, ScramblerCode) < 0)
    {
        WriteLog("\tGWCCardGetScramblerCode error!!",0);
        return (-9);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    WriteLog("\t[WCard] GWCCardSetUserPasswordCode...",0);
    BYTE UserPasswordCode[8];//"12345678" jash.liao add at 2016/0601
    if(state==0)
    {
        memset (UserPasswordCode,'1',sizeof(UserPasswordCode));
    }
    else
    {
        memset (UserPasswordCode,'2',sizeof(UserPasswordCode));
    }
    if(GWCCardSetUserPasswordCode(lpWCardDS, UserPasswordCode) < 0)
    {
        WriteLog("\tGWCCardSetUserPasswordCode error!!",0);
        return (-10);
        //break;
    }

    bool bError;
    int i;

    /* �]�m WCard �����Ѽ� */
    bError = FALSE;
    WriteLog("\t[WCard] GWCCardAddDoorName...",0);
    for(i = 0; i < 3; i ++)
    {
        BYTE bytDoorName[GWC_DOOR_NAME_LENGTH_MAXIMUM];

        memset(bytDoorName, 0, GWC_DOOR_NAME_LENGTH_MAXIMUM);
        sprintf((char *)bytDoorName, "Door-%02d", (i + 1));

        if(GWCCardAddDoorName(lpWCardDS, bytDoorName, strlen((char *)bytDoorName)) < 0)
        {
            WriteLog("\tGWCCardAddDoorName error!!",0);

            bError = TRUE;

            break;
        }
    }

    if(bError)
    {
        return (-11);
        //break;
    }

    /* �]�m WCard �����Ѽ� */
    bError = FALSE;
    WriteLog("\t[WCard] GWCCardAddDoorAccess...",0);
    for(i = 0; i < 1152; i += 2)
    {
        //fprintf(stdout, "%d, ", (i + 1));
        if(GWCCardAddDoorAccess(lpWCardDS, (i + 1)) < 0)
        {
            WriteLog("\tGWCCardAddDoorAccess error!!",0);

            bError = TRUE;

            break;
        }
    }

    if(bError)
    {
        return (-11);
        //break;
    }

    /* �N WCard �j�w�� Reader */
    WriteLog("\t[Reader] GWCReaderBindCard...",0);
    if(GWCReaderBindCard(lpReaderDS, lpWCardDS, NULL, NULL, NULL, 1) < 0)
    {
        WriteLog("\tGWCReaderBindCard error!!",0);
        return (-12);
        //break;
    }

    /* -= Control �ާ@ =- */
    /* ��w���w�� Reader �� Control */
    WriteLog("\t[Control] GWCSelect...",0);
    if(GWCSelect(lpControlDS, lpReaderDS, NULL) < 0)
    {
        WriteLog("\tGWCSelect error!!",0);
        return (-13);
        //break;
    }

    /* Control �Ұ� */
    WriteLog("\t[Control] GWCStart...",0);
    if(GWCStart(lpControlDS) < 0)
    {
        WriteLog("\tGWCStart error!!",0);
        return (-14);
        //break;
    }

    //GWCWaitAndPrint(FALSE);

    /* �ˬd�ýT�w Control ���A���n */
    WriteLog("\t[Control] GWCGetStatus...",0);
    while((iStatus = GWCGetStatus(lpControlDS)) != GWC_STATUS_OK)
    {
        //GWCWaitAndPrint(TRUE);

        /* �H�U���A�N�ݩ���~ */
        if((iStatus == GWC_STATUS_ERROR) ||
            (iStatus == GWC_STATUS_NO_DEVICE) ||
            (iStatus == GWC_STATUS_ERROR_DEVICE) ||
            (iStatus == GWC_STATUS_INTERNAL_ERROR))
        {
            break;
        }
    }

    /* ���R�@�U���G�� */
    if(iStatus == GWC_STATUS_OK)
    {
        WriteLog("\tGWC_STATUS_OK!!",0);
    }
    else if(iStatus == GWC_STATUS_ERROR)
    {
        WriteLog("\tGWC_STATUS_ERROR!!",0);
        return (-15);
        //break;
    }
    else if(iStatus == GWC_STATUS_NO_DEVICE)
    {
        WriteLog("\tGWC_STATUS_NO_DEVICE!!",0);
        return (-16);
        //break;
    }
    else if(iStatus == GWC_STATUS_ERROR_DEVICE)
    {
        WriteLog("\tGWC_STATUS_ERROR_DEVICE!!",0);
        return (-17);
        //break;
    }
    else if(iStatus == GWC_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_STATUS_INTERNAL_ERROR!!",0);
        return (-18);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-19);
        //break;
    }

    //GWCWaitAndPrint(FALSE);

    /* �b�ثe�� Control �W�A�i��d���g�J�ާ@ */
    WriteLog("\t[Control] GWCWriteCard...",0);
    if(GWCWriteCard(lpControlDS, GWCStageCallback, NULL) < 0)
    {
        WriteLog("\tGWCWriteCard error!!",0);
        return (-21);
        //break;
    }

    //GWCWaitAndPrint(FALSE);

        /* �ˬd�ýT�w Control ���A���n */
    WriteLog("\t[Control] GWCGetStatus...",0);
    if((iStatus = GWCGetStatus(lpControlDS)) == GWC_STATUS_OK)
    {
        WriteLog("\tGWC_STATUS_OK!!",0);
    }
    else if(iStatus == GWC_STATUS_ERROR)
    {
        WriteLog("\tGWC_STATUS_ERROR!!",0);
        return (-22);
        //break;
    }
    else if(iStatus == GWC_STATUS_NO_DEVICE)
    {
        WriteLog("\tGWC_STATUS_NO_DEVICE!!",0);
        return (-23);
        //break;
    }
    else if(iStatus == GWC_STATUS_ERROR_DEVICE)
    {
        WriteLog("\tGWC_STATUS_ERROR_DEVICE!!",0);
        return (-24);
        //break;
    }
    else if(iStatus == GWC_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_STATUS_INTERNAL_ERROR!!",0);
        return (-25);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-26);
        //break;
    }

    /* �ˬd�ýT�w Reader ���A���n */
    WriteLog("\t[Reader] GWCReaderGetStatus...",0);
    if((iReaderStatus = GWCReaderGetStatus(lpReaderDS)) == GWC_READER_STATUS_OK)
    {
        WriteLog("\tGWC_READER_STATUS_OK!!",0);
    }
    else if(iReaderStatus == GWC_READER_STATUS_ERROR)
    {
        WriteLog("\tGWC_READER_STATUS_ERROR!!",0);
        return (-27);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_TIMEOUT)
    {
        WriteLog("\tGWC_READER_STATUS_TIMEOUT!!",0);
        return (-28);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_NO_CARD)
    {
        WriteLog("\tGWC_READER_STATUS_NO_CARD!!",0);
        return (-29);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_ACCESS_DENY)
    {
        WriteLog("\tGWC_READER_STATUS_ACCESS_DENY!!",0);
        return (-30);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_FORMAT_ERROR)
    {
        WriteLog("\tGWC_READER_STATUS_FORMAT_ERROR!!",0);
        return (-31);
        //break;
    }
    else if(iReaderStatus == GWC_READER_STATUS_INTERNAL_ERROR)
    {
        WriteLog("\tGWC_READER_STATUS_INTERNAL_ERROR!!",0);
        return (-32);
        //break;
    }
    else
    {
        WriteLog("\tUNKNOWN ERROR!!",0);
        return (-33);
        //break;
    }

    /* Control ���� */
    WriteLog("\t[Control] GWCStop...",0);
    if(GWCStop(lpControlDS) < 0)
    {
        WriteLog("\tGWCStop error!!",0);
        return (-34);
        //break;
    }

    WriteLog("WCard_writeTest....finish",0);
    return 0;
}

int DLL_EXPORT WCard_close()
{
    WriteLog("WCard_close...Start",0);
    if(lpControlDS!='\0')
    {
        GWC_SAFE_DESTROY(lpControlDS);
        WriteLog("\tGWC_SAFE_DESTROY...",0);
    }
    if(lpReaderDS!='\0')
    {
        GWC_SAFE_READER_DESTROY(lpReaderDS);
        WriteLog("\tGWC_SAFE_READER_DESTROY...",0);
    }
    if(lpWCardDS!='\0')
    {
        GWC_SAFE_WCARD_DESTROY(lpWCardDS);
        WriteLog("\tGWC_SAFE_WCARD_DESTROY...",0);
    }
    GWCTerminate();
    WriteLog("WCard_close...finish",0);
    return 0;
}
//WCard_API End
//===================================================
extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
