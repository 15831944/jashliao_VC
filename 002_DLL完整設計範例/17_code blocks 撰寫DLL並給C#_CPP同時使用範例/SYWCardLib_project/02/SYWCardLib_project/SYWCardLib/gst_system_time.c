/*
============================================
 �ɮצW�١Ggst_system_time.c
 �{���\��G�ɶ��u��
 �]�p�̡GSeamus Berloz (�a��������ù)
 ���v�֦��̡GSYRIS Technology Corp.
 �̫��s����G2016/05/30 �W�� 11:32:29
 ��L��T�G
============================================
*/
/*---------------------------------------------------------------------------*/
/* �]�t���Y�� */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �۩w�q�]�t�� =- */
/* �w���H�h�{���w�w�q�]�t�� */
#ifndef GHLD_LIBRARY
  #include "ghld_hallib_define.h"
#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �зǥ]�t�� =- */
/* �b���f�t�w���H�h�{���w�w�q�ɤޤJ�����зǥ]�t�� */
#if ((!defined(GHLD_LIBRARY)) || (GHLD_LIBRARY == GHLD_LIBRARY_NONE))
  //#include <errno.h>
#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* Include system network headers */
#if (defined(WIN32) || defined(_WIN32))
  #include <windows.h>
  #include <unistd.h>

/* UNIX or others */
#else
  #include <sys/time.h>
  #include <unistd.h>

#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �۩w�q�]�t�� =- */
//#include "include/gnet.h"

/*---------------------------------------------------------------------------*/
/* �Ȩѥ��ҲձM�Τ��`�Ʃw�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�α`�ƫŧi�w�q =- */
/* �ɶ��ץ��ȱ`�ƫŧi�w�q */
#define GST_TIME_DELTA_EPOCH_IN_MICROSECOND 11644473600000000ULL

/*---------------------------------------------------------------------------*/
/* �Ȩѥ��ҲձM�Τ��ŧi���A�w�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�θ�ƫ��A�ŧi�w�q =- */
/* struct timeval ���A�O�W�ŧi�w�q */
#ifndef TIMEVALUE
  #define TIMEVALUE struct timeval
#endif

/*---------------------------------------------------------------------------*/
/* �Ȩѥ��ҲձM�Τ��ܼƩw�q */

/*---------------------------------------------------------------------------*/
/* �禡�쫬�w�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�Τ��Ψ�ƫŧi�w�q =- */
long GSTTimeGetTime(void);
int GSTTimeSleep(long lMillisecondValue);
int GSTTimeCheckTimeUp(long lMillisecondValue, long lMillisecondValueLimit);

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �p�Ψ�ƫŧi�w�q =- */
#if (defined(WIN32) || defined(_WIN32))
static unsigned long long FiletimeToUnixEpoch(const FILETIME *lpFiletime);
#endif

/*---------------------------------------------------------------------------*/
/* ���o�ɶ� */
long GSTTimeGetTime(void)
  {
    long lDeltaMillisecond, lCurrentMillisecond;
    TIMEVALUE timTimeValue;

    static long s_lTotalMillisecond = 0;
    static long s_lLastMillisecond = 0;

    #if (defined(WIN32) || defined(_WIN32))

    unsigned long long ullTime;
    FILETIME ftFiletime;

    GetSystemTimeAsFileTime(&ftFiletime);
    ullTime = FiletimeToUnixEpoch(&ftFiletime);

    timTimeValue.tv_usec = (long)(ullTime % 1000000L);
    timTimeValue.tv_sec = ((long)(ullTime / 1000000L) % GGD_LONG_MAX);

    #else

    gettimeofday(&timTimeValue, NULL);

    //printf("timTimeValue.tv_sec=%ld\n", timTimeValue.tv_sec);

    timTimeValue.tv_sec %= GGD_LONG_MAX;

    #endif

    lCurrentMillisecond = (((timTimeValue.tv_sec % 1000000L) * 1000L) + (timTimeValue.tv_usec / 1000L)) % GGD_LONG_MAX;
    if(lCurrentMillisecond >= s_lLastMillisecond)
      {
        lDeltaMillisecond = (lCurrentMillisecond - s_lLastMillisecond);
      }
    else
      {
        lDeltaMillisecond = ((GGD_LONG_MAX - lCurrentMillisecond) + s_lLastMillisecond);
      }

    s_lLastMillisecond = lCurrentMillisecond;
    s_lTotalMillisecond = (s_lTotalMillisecond + lDeltaMillisecond) % GGD_LONG_MAX;

    //printf("s_lTotalMillisecond=%ld, s_lLastMillisecond=%ld, lCurrentMillisecond=%ld\n", s_lTotalMillisecond, s_lLastMillisecond, lCurrentMillisecond);

    return s_lTotalMillisecond;
  }

/*---------------------------------------------------------------------------*/
/* �p�ɥ�v */
int GSTTimeSleep(long lMillisecondValue)
  {
    int iReturnValue;

    #if 0

    #if (defined(WIN32) || defined(_WIN32))

    iReturnValue = 0;
    Sleep(lMillisecondValue);

    #else

    TIMEVALUE timTimeValue;

    /* �]�w���ԹO�ɮɶ��A�H�@����p�⦡�ӭp��ɶ� */
    timTimeValue.tv_sec = lMillisecondValue / 1000;
    timTimeValue.tv_usec = (lMillisecondValue % 1000) * 1000;

    /* �ȶȥu�����߮ɶ��]�m */
    iReturnValue = select((int)NULL, NULL, NULL, NULL, &timTimeValue);

    #endif

    #else

    iReturnValue = 0;
    usleep(lMillisecondValue);

    #endif

    return iReturnValue;
  }

/*---------------------------------------------------------------------------*/
/* �O�ɹB�� */
int GSTTimeCheckTimeUp(long lMillisecondValue, long lMillisecondValueLimit)
  {
    long lCurrentMillisecond;

    return ((((lCurrentMillisecond = GSTTimeGetTime()) >= lMillisecondValue) ? (lCurrentMillisecond - lMillisecondValue) : ((GGD_LONG_MAX - lMillisecondValue) + lCurrentMillisecond)) >= lMillisecondValueLimit);
  }

/*---------------------------------------------------------------------------*/
/* �t�ήɶ��ȭץ� */
#if (defined(WIN32) || defined(_WIN32))

static unsigned long long  FiletimeToUnixEpoch(const FILETIME *lpFiletime)
  {
    unsigned long long ullReturnValue = (unsigned long long)(lpFiletime->dwHighDateTime) << 32;

    ullReturnValue |= lpFiletime->dwLowDateTime;

    /* from 100 nano-sec periods to usec */
    ullReturnValue /= 10;

    /* from Win epoch to Unix epoch */
    ullReturnValue -= GST_TIME_DELTA_EPOCH_IN_MICROSECOND;

    return ullReturnValue;
  }

#endif

/*---------------------------------------------------------------------------*/
/* �ɮ׵��� */

