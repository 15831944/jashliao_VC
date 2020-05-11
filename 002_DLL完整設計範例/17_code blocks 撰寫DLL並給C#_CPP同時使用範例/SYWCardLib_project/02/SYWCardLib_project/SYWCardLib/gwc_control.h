/*
============================================
 �ɮצW�١Ggwc_control.h
 �{���\��GwCard ����u���Ʈw
 �]�p�̡GSeamus Berloz (�a��������ù)
 ���v�֦��̡GSYRIS Technology Corp.
 �̫��s����G2016/05/31 �W�� 11:32:29
 ��L��T�G
============================================
*/
/*---------------------------------------------------------------------------*/
/* �w�q���Y */
#ifndef _GWC_CONTROL_H
#define _GWC_CONTROL_H

/*---------------------------------------------------------------------------*/
/* �]�t���Y�� */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �۩w�q�]�t�� =- */
#include "ggd_global_define.h"

/*---------------------------------------------------------------------------*/
/* �sĶ�ѧO�`�Ʃw�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�νsĶ�ѧO�`�Ʃw�q =- */
/* ���Ѥ@�ǽsĶ���S���禡�׹�����r */
#if defined(WIN32) || defined(_WIN32)

  #ifndef GWCDLLIMPORT
    #define GWCDLLIMPORT __declspec(dllimport)
  #endif

  #ifndef GWCDLLEXPORT
    #define GWCDLLEXPORT __declspec(dllexport)
  #endif

  #ifndef GWCAPI
    #define GWCAPI __cdecl
  #endif

  #ifndef GWCCALLBACK
    #define GWCCALLBACK __cdecl
  #endif

#else

  #define GWCDLLIMPORT
  #define GWCDLLEXPORT

  #define GWCAPI
  #define GWCCALLBACK

#endif

/*---------------------------------------------------------------------------*/
/* ����`�Ʃw�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�α`�Ʃw�q�ŧi =- */
/* ��Ƹ�T���ױ`�Ʃw�q�ŧi */
#define GWC_AES_KEY_LENGTH_MAXIMUM 16
#define GWC_DOOR_NAME_LENGTH_MAXIMUM 8
#define GWC_SCRAMBLER_CODE_LENGTH_MAXIMUM 4
#define GWC_USER_AES_KEY_LENGTH_MAXIMUM 16
#define GWC_USER_ACCESS_KEY_LENGTH_MAXIMUM 6
#define GWC_USER_PASSWORD_CODE_LENGTH_MAXIMUM 8
#define GWC_USER_UNIQUE_IDENTIFIER_LENGTH_MAXIMUM 8

//#define GWC_DOOR_GROUP_CODE_STRING_LENGTH_MAXIMUM 32

/*---------------------------------------------------------------------------*/
/* ����`�Υ����ŧi�w�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�Υ����ŧi�w�q =- */
/* �P�������ŧi�w�q */
 #define GWC_SAFE_DESTROY(ControlDS) \
  { \
    if((ControlDS) != NULL) \
      { \
        GWCDestroy(ControlDS); \
        (ControlDS) = NULL; \
      } \
  }

/* Reader �P�������ŧi�w�q */
 #define GWC_SAFE_READER_DESTROY(ReaderDS) \
  { \
    if((ReaderDS) != NULL) \
      { \
        GWCReaderDestroy(ReaderDS); \
        (ReaderDS) = NULL; \
      } \
  }

/* WCard �P�������ŧi�w�q */
 #define GWC_SAFE_WCARD_DESTROY(WCardDS) \
  { \
    if((WCardDS) != NULL) \
      { \
        GWCCardDestroy(WCardDS); \
        (WCardDS) = NULL; \
      } \
  }

/*---------------------------------------------------------------------------*/
/* ����ŧi���A�w�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= ��Ƶ��c���A�ŧi�w�q =- */
/* WCard ��Ƶ��c���A�ŧi�w�q */
typedef struct _GWC_WCARD_DATAGRAM_STRUCTURE GWCARDDS;
/* Reader ��Ƶ��c���A�ŧi�w�q */
typedef struct _GWC_READER_DATAGRAM_STRUCTURE GWCREADERDS;
/* Control ��Ƶ��c���A�ŧi�w�q */
typedef struct _GWC_CONTROL_DATAGRAM_STRUCTURE GWCONTROLDS;

/* WCard Fetch Door Name ��Ƶ��c���A�ŧi�w�q */
typedef struct _GWC_WCARD_FETCH_DOOR_NAME_DATAGRAM_STRUCTURE GWCARDFDNDS;
/* WCard Fetch Door Access ��Ƶ��c���A�ŧi�w�q */
typedef struct _GWC_WCARD_FETCH_DOOR_ACCESS_DATAGRAM_STRUCTURE GWCARDFDADS;

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �禡���Ы��A�ŧi�w�q =- */
/* ���q���A�^�I�禡���Ы��A�ŧi�w�q */
typedef void (GWCCALLBACK * GWCOPSTAGECB)(void *lpOPStageCBParameter);

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�α`�ƦC�|��ƫ��A�ŧi�w�q =- */
/* ���A�`�ƦC�|��ƫ��A�ŧi�w�q */
enum _GWC_STATUS_DEFINITION
  {
    GWC_STATUS_OK,
    GWC_STATUS_BUSY,
    GWC_STATUS_SHUTDOWN,

    GWC_STATUS_ERROR,
    GWC_STATUS_NO_DEVICE,
    GWC_STATUS_ERROR_DEVICE,
    GWC_STATUS_INTERNAL_ERROR,

    GWC_STATUS_AMOUNT
  };

/* Reader ���A�`�ƦC�|��ƫ��A�ŧi�w�q */
enum _GWC_READER_STATUS_DEFINITION
  {
    GWC_READER_STATUS_OK,
    GWC_READER_STATUS_BUSY,

    GWC_READER_STATUS_ERROR,
    GWC_READER_STATUS_TIMEOUT,
    GWC_READER_STATUS_NO_CARD,
    GWC_READER_STATUS_ACCESS_DENY,
    GWC_READER_STATUS_FORMAT_ERROR,
    GWC_READER_STATUS_INTERNAL_ERROR,

    GWC_READER_STATUS_AMOUNT
  };

/* WCard �γ~�`�ƦC�|�w�q�ŧi */
enum _GWC_WCARD_USAGE_DEFINITION
  {
    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
    /* -= �γ~�C�� =- */
    /*-----------------------------------------*/
    /* ���� */
    GWC_WCARD_USAGE_UNKNOWN,

    /*-----------------------------------------*/
    /* �`�Υγ~ */
    GWC_WCARD_USAGE_FOR_NORMAL,
    GWC_WCARD_USAGE_FOR_PATROL,

    /*-----------------------------------------*/
    /* �S��γ~ */
    GWC_WCARD_USAGE_FOR_SETUP = 15,

    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
    /* -= �γ~�N�X�`�� =- */
    GWC_WCARD_USAGE_AMOUNT
  };

/* WCard �����`�ƦC�|�w�q�ŧi */
enum _GWC_WCARD_TYPE_DEFINITION
  {
    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
    /* -= �����C�� =- */
    /*-----------------------------------------*/
    /* ���� */
    GWC_WCARD_TYPE_UNKNOWN,

    /*-----------------------------------------*/
    /* �`������ */
    GWC_WCARD_TYPE_NORMAL,
    GWC_WCARD_TYPE_VIP,
    GWC_WCARD_TYPE_ADMIN,

    /*-----------------------------------------*/
    /* �S������ */
    GWC_WCARD_TYPE_DATETIME_SETUP = 14,
    GWC_WCARD_TYPE_AES_KEY_SETUP = 15,

    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
    /* -= �����N�X�`�� =- */
    GWC_WCARD_TYPE_AMOUNT
  };

/* WCard �t�m�`�ƦC�|�w�q�ŧi */
enum _GWC_WCARD_CONFIGURATION_DEFINITION
  {
    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
    /* -= �t�m�C�� =- */
    GWC_WCARD_CONFIGURATION_64_DOOR_1_NAME,
    GWC_WCARD_CONFIGURATION_64_DOOR_WITH_PASSWORD,
    GWC_WCARD_CONFIGURATION_128_DOOR_OR_OTHERS,
    GWC_WCARD_CONFIGURATION_256_DOOR_3_NAME_WITH_PASSWORD,
    GWC_WCARD_CONFIGURATION_320_DOOR_2_NAME_WITH_PASSWORD,
    GWC_WCARD_CONFIGURATION_384_DOOR_1_NAME_WITH_PASSWORD,
    GWC_WCARD_CONFIGURATION_384_DOOR_2_NAME,
    GWC_WCARD_CONFIGURATION_768_DOOR_1_NAME_WITH_PASSWORD,
    GWC_WCARD_CONFIGURATION_768_DOOR_2_NAME,
    GWC_WCARD_CONFIGURATION_1152_DOOR_1_NAME_WITH_PASSWORD,
    GWC_WCARD_CONFIGURATION_1152_DOOR_2_NAME,

    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
    /* -= �����N�X�`�� =- */
    GWC_WCARD_CONFIGURATION_AMOUNT
  };

/*---------------------------------------------------------------------------*/
/* �����ܼƫŧi */

/*---------------------------------------------------------------------------*/
/* ���Ψ�ƫŧi */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�Τ��Ψ�ƫŧi�w�q =- */
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
  extern "C" {
#endif

  /* ��l�P�פ� */
  extern GWCDLLEXPORT int GWCAPI GWCInitialize(void);//�t�m�O����
  extern GWCDLLEXPORT void GWCAPI GWCTerminate(void);//����O����

  /* ������ */
  extern GWCDLLEXPORT GWCONTROLDS * GWCAPI GWCCreate(void);//�إ߱�������ܼ�
  extern GWCDLLEXPORT void GWCAPI GWCDestroy(GWCONTROLDS *lpControlDS);
  extern GWCDLLEXPORT int GWCAPI GWCStart(GWCONTROLDS *lpControlDS);//�إߤu�@�����
  extern GWCDLLEXPORT int GWCAPI GWCStop(GWCONTROLDS *lpControlDS);//�����u�@�����
  extern GWCDLLEXPORT int GWCAPI GWCGetStatus(GWCONTROLDS *lpControlDS);
  extern GWCDLLEXPORT int GWCAPI GWCSelect(GWCONTROLDS *lpControlDS, GWCREADERDS *lpReaderDS, const char *lpSerialNumber);
  extern GWCDLLEXPORT int GWCAPI GWCReadCard(GWCONTROLDS *lpControlDS, GWCOPSTAGECB pOPStageCBFunction, void *lpOPStageCBFunctionParameter);
  extern GWCDLLEXPORT int GWCAPI GWCWriteCard(GWCONTROLDS *lpControlDS, GWCOPSTAGECB pOPStageCBFunction, void *lpOPStageCBFunctionParameter);

  /* Reader ��� */
  extern GWCDLLEXPORT GWCREADERDS * GWCAPI GWCReaderCreate(void);
  extern GWCDLLEXPORT void GWCAPI GWCReaderDestroy(GWCREADERDS *lpReaderDS);
  extern GWCDLLEXPORT int GWCAPI GWCReaderGetStatus(GWCREADERDS *lpReaderDS);
  extern GWCDLLEXPORT int GWCAPI GWCReaderGetCard(GWCREADERDS *lpReaderDS, GWCARDDS *lpWCardDS);
  extern GWCDLLEXPORT int GWCAPI GWCReaderBindCard(GWCREADERDS *lpReaderDS, GWCARDDS *lpWCardDS, BYTE *lpAccessKey, BYTE *lpNewAccessKey, BYTE *lpAESKey, int iOffset);

  /* WCard ��� */
  extern GWCDLLEXPORT GWCARDDS * GWCAPI GWCCardCreate(void);
  extern GWCDLLEXPORT void GWCAPI GWCCardDestroy(GWCARDDS *lpWCardDS);
  extern GWCDLLEXPORT int GWCAPI GWCCardSetType(GWCARDDS *lpWCardDS, int iType);
  extern GWCDLLEXPORT int GWCAPI GWCCardSetUsage(GWCARDDS *lpWCardDS, int iUsage);
  extern GWCDLLEXPORT int GWCAPI GWCCardSetConfiguration(GWCARDDS *lpWCardDS, int iConfiguration);
  extern GWCDLLEXPORT int GWCAPI GWCCardSetAdjustDateTime(GWCARDDS *lpWCardDS, int iAdjustDateTime);
  extern GWCDLLEXPORT int GWCAPI GWCCardSetPassThroughCounter(GWCARDDS *lpWCardDS, int iPassThroughCounter);
  extern GWCDLLEXPORT int GWCAPI GWCCardSetHolidayWeekProgramValue(GWCARDDS *lpWCardDS, int iHolidayWeekProgramValue);
  extern GWCDLLEXPORT int GWCAPI GWCCardSetExpirationDate(GWCARDDS *lpWCardDS, int iStartUpExpirationDate, int iEndleExpirationDate);
  extern GWCDLLEXPORT int GWCAPI GWCCardSetPassThroughTimeRange(GWCARDDS *lpWCardDS, int iFirstPassThroughTimeRange, int iSecondPassThroughTimeRange, int iThirdPassThroughTimeRange);
  extern GWCDLLEXPORT int GWCAPI GWCCardGetType(GWCARDDS *lpWCardDS);
  extern GWCDLLEXPORT int GWCAPI GWCCardGetUsage(GWCARDDS *lpWCardDS);
  extern GWCDLLEXPORT int GWCAPI GWCCardGetConfiguration(GWCARDDS *lpWCardDS);
  extern GWCDLLEXPORT int GWCAPI GWCCardGetAdjustDateTime(GWCARDDS *lpWCardDS);
  extern GWCDLLEXPORT int GWCAPI GWCCardGetPassThroughCounter(GWCARDDS *lpWCardDS);
  extern GWCDLLEXPORT int GWCAPI GWCCardGetHolidayWeekProgramValue(GWCARDDS *lpWCardDS);
  extern GWCDLLEXPORT int GWCAPI GWCCardGetExpirationDate(GWCARDDS *lpWCardDS, int *lpStartUpExpirationDate, int *lpEndleExpirationDate);
  extern GWCDLLEXPORT int GWCAPI GWCCardGetPassThroughTimeRange(GWCARDDS *lpWCardDS, int *lpFirstPassThroughTimeRange, int *lpSecondPassThroughTimeRange, int *lpThirdPassThroughTimeRange);
  extern GWCDLLEXPORT int GWCAPI GWCCardSetScramblerCode(GWCARDDS *lpWCardDS, BYTE *lpScramblerCode);
  extern GWCDLLEXPORT int GWCAPI GWCCardSetUserAESKey(GWCARDDS *lpWCardDS, BYTE *lpUserAESKey);
  extern GWCDLLEXPORT int GWCAPI GWCCardSetUserPasswordCode(GWCARDDS *lpWCardDS, BYTE *lpUserPasswordCode);
  extern GWCDLLEXPORT int GWCAPI GWCCardSetUserUniqueIdentifier(GWCARDDS *lpWCardDS, BYTE *lpUserUniqueIdentifier);
  extern GWCDLLEXPORT BYTE GWCAPI * GWCCardGetScramblerCode(GWCARDDS *lpWCardDS, BYTE *lpScramblerCode);
  extern GWCDLLEXPORT BYTE GWCAPI * GWCCardGetUserAESKey(GWCARDDS *lpWCardDS, BYTE *lpUserAESKey);
  extern GWCDLLEXPORT BYTE GWCAPI * GWCCardGetUserPasswordCode(GWCARDDS *lpWCardDS, BYTE *lpUserPasswordCode);
  extern GWCDLLEXPORT BYTE GWCAPI * GWCCardGetUserUniqueIdentifier(GWCARDDS *lpWCardDS, BYTE *lpUserUniqueIdentifier);
  extern GWCDLLEXPORT int GWCAPI GWCCardAddDoorName(GWCARDDS *lpWCardDS, BYTE *lpName, int iLength);
  extern GWCDLLEXPORT int GWCAPI GWCCardFetchFirstDoorName(GWCARDDS *lpWCardDS, GWCARDFDNDS **lpWCardFetchDoorNameDS, BYTE *lpName);
  extern GWCDLLEXPORT int GWCAPI GWCCardFetchNextDoorName(GWCARDFDNDS *lpWCardFetchDoorNameDS, BYTE *lpName);
  extern GWCDLLEXPORT void GWCAPI GWCCardFetchCloseDoorName(GWCARDFDNDS *lpWCardFetchDoorNameDS);
  extern GWCDLLEXPORT int GWCAPI GWCCardAddDoorAccess(GWCARDDS *lpWCardDS, int iNumber);
  extern GWCDLLEXPORT int GWCAPI GWCCardFetchFirstDoorAccess(GWCARDDS *lpWCardDS, GWCARDFDADS **lpWCardFetchDoorAccessDS);
  extern GWCDLLEXPORT int GWCAPI GWCCardFetchNextDoorAccess(GWCARDFDADS *lpWCardFetchDoorAccessDS);
  extern GWCDLLEXPORT void GWCAPI GWCCardFetchCloseDoorAccess(GWCARDFDADS *lpWCardFetchDoorAccessDS);

#ifdef __cplusplus
  }
#endif

/*---------------------------------------------------------------------------*/
/* �w�q���Y���� */
#endif

/*---------------------------------------------------------------------------*/
/* �ɮ׵��� */

