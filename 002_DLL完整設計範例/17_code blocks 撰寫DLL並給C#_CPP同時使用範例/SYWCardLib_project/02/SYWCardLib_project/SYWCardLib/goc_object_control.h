/*
============================================
 �ɮצW�١Ggoc_object_control.h
 �{���\��G���󱱨�Ҳ�
 �]�p�̡GSeamus Berloz (�a��������ù)
 ���v�֦��̡GSYRIS Technology Corp.
 �̫��s����G2015/08/10 �W�� 11:32:29
 ��L��T�G
============================================
*/
/*---------------------------------------------------------------------------*/
/* �w�q���Y */
#ifndef _GOC_OBJECT_CONTROL_H
#define _GOC_OBJECT_CONTROL_H

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

  #ifndef GOCDLLIMPORT
    #define GOCDLLIMPORT __declspec(dllimport)
  #endif

  #ifndef GOCDLLEXPORT
    #define GOCDLLEXPORT __declspec(dllexport)
  #endif

  #ifndef GOCAPI
    #define GOCAPI __cdecl
  #endif

  #ifndef GOCCALLBACK
    #define GOCCALLBACK __cdecl
  #endif

#else

  #define GOCDLLIMPORT
  #define GOCDLLEXPORT

  #define GOCAPI
  #define GOCCALLBACK

#endif

/*---------------------------------------------------------------------------*/
/* ����`�Ʃw�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�Υ��쥨���ŧi�w�q =- */
/* ���������ѧO�`�ƫŧi�w�q */
#define GOC_OBJECT_HAVE_NO_IDENTIFICATION (-1)
/* ���󥼳]�w�ѧO�`�ƫŧi�w�q */
#define GOC_OBJECT_NEED_TO_SETUP_IDENTIFICATION 0

/*---------------------------------------------------------------------------*/
/* ����`�Υ����ŧi�w�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�Υ����ŧi�w�q =- */
/* �����k�����ŧi�w�q */
#define GOC_METHOD_DECLARE(Method) (GOCAPI * Method) /* Define the functions as pointers */

/* �����k���c�^�������ŧi�w�q */
#define GOC_GET_METHOD(Object) (GOCObjectControlGetObjectMethod((GOCObject *)(Object)))
#define GOC_GET_METHOD_IN_TYPE(Object, ObjectMethodType) (ObjectMethodType *)(GOC_GET_METHOD(Object))
#define GOC_GET_PARENT_METHOD(Object) GOCObjectControlGetParentObjectMethod((GOCObject *)(Object))
#define GOC_GET_PARENT_METHOD_IN_TYPE(Object, ParentObjectMethodType) (ParentObjectMethodType *)(GOC_GET_PARENT_METHOD(Object))

/* �������񥨶��ŧi�w�q */
 #define GOC_SAFE_RELEASE(MethodType, Object) \
  { \
    if((Object) != NULL) \
      { \
        ((MethodType *)(GOC_GET_METHOD(Object)))->Release(); \
        (Object) = NULL; \
      } \
  }

/* ����P�������ŧi�w�q */
 #define GOC_SAFE_DESTROY(Object) \
  { \
    if((Object) != NULL) \
      { \
        GOCObjectControlDestroy((GOCObject *)(Object)); \
        (Object) = NULL; \
      } \
  }

/*---------------------------------------------------------------------------*/
/* ����ŧi���A�w�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= ���󫬺A�ŧi�w�q =- */
/* ���󫬺A�ŧi�w�q */
/* Object */
typedef struct SGOCObject GOCObject;
/* Object Method */
typedef struct SGOCObjectMethod GOCObjectMethod;

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �禡���Ы��A�ŧi�w�q =- */
typedef int (GOCAPI * GOCOREGISTERPROC)(void);
typedef void (GOCAPI * GOCOCONSTRUCTOR)(GOCObject *pObject, void *lpParmeter);
typedef void (GOCAPI * GOCOMCONSTRUCTOR)(GOCObjectMethod *pObjectMethod, GOCObjectMethod *pParentObjectMethod);
typedef void (GOCAPI * GOCODECONSTRUCTOR)(GOCObject *pObject);

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= ��Ƶ��c���A�ŧi�w�q =- */
/* ������U��T��Ƶ��c�ŧi�w�q */
typedef struct _GOC_OBJECT_REGISTER_INFORMATION_DATAGRAM_STRUCTURE
  {
    int iParentObjectIdentification;

    /* �����T */
    int iObjectStructureSize;
    int iObjectMethodStructureSize;

    /* ����غc�B�z�禡���� */
    GOCOCONSTRUCTOR pObjectConstructor;
    GOCOMCONSTRUCTOR pObjectMethodConstructor;
    GOCODECONSTRUCTOR pObjectDeconstructor;
  } GOCORIDS, *LPGOCORIDS;

/*---------------------------------------------------------------------------*/
/* ���Ϊ��󵲺c�ŧi�w�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= ���󵲺c�ŧi�w�q =- */
/* Object */
struct SGOCObject;
/* Object Method */
struct SGOCObjectMethod;

/*---------------------------------------------------------------------------*/
/* ���Ϊ��󵲺c�˪��w�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= ���󵲺c�˪��ŧi�w�q =- */
/* Object Structure */
struct SGOCObject
  {
    /*-----------------------------------------*/
    /* -= �����ѧO�B�z =- */
    /* �����ѧO */
    int m_iObjectIdentification;

  };

/* Object Method Structure */
struct SGOCObjectMethod
  {
    /*-----------------------------------------*/
    /* -= �غc�P�Ѻc =- */
    int GOC_METHOD_DECLARE(Constructor)(void);
    void GOC_METHOD_DECLARE(Deconstructor)(void);

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
  /* ��l�ƨ�� */
  extern GOCDLLEXPORT void GOCAPI GOCObjectControlInitialize(void);
  /* �إߤu���� */
  extern GOCDLLEXPORT GOCObject * GOCAPI GOCObjectControlCreate(GOCOREGISTERPROC pObjectRegisterProcessor, void *lpParmeter);
  extern GOCDLLEXPORT void GOCAPI GOCObjectControlDestroy(GOCObject *pObject);
  /* ���U�u���� */
  extern GOCDLLEXPORT int GOCAPI GOCObjectControlObjectRegister(GOCORIDS *lpObjectRegisterInfoDS);
  extern GOCDLLEXPORT int GOCAPI GOCObjectControlObjectMethodRegister(int iObjectIdentification, GOCObjectMethod *lpObjectMethod);
  /* �غc�P�Ѻc�u���� */
  extern GOCDLLEXPORT void GOCAPI GOCObjectControlParentObjectConstructor(GOCObject *pObject, int iObjectIdentification, void *lpParmeter);
  extern GOCDLLEXPORT void GOCAPI GOCObjectControlParentObjectDeconstructor(GOCObject *pObject, int iObjectIdentification);
  /* �s���u���� */
  extern GOCDLLEXPORT GOCObjectMethod * GOCAPI GOCObjectControlGetObjectMethod(GOCObject *pObject);
  extern GOCDLLEXPORT GOCObjectMethod * GOCAPI GOCObjectControlGetParentObjectMethod(GOCObject *pObject);
  extern GOCDLLEXPORT GOCObjectMethod * GOCAPI GOCObjectControlGetObjectMethodFromIdentification(int iObjectIdentification);
  extern GOCDLLEXPORT GOCObjectMethod * GOCAPI GOCObjectControlGetParentObjectMethodFromIdentification(int iObjectIdentification);

#ifdef __cplusplus
  }
#endif

/*---------------------------------------------------------------------------*/
/* �w�q���Y���� */
#endif

/*---------------------------------------------------------------------------*/
/* �ɮ׵��� */

