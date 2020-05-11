/*
============================================
 �ɮצW�١Gggd_global_define.h
 �{���\��GGlobal Defination
 �]�p�̡GSeamus Berloz (�a��������ù)
 ���v�֦��̡GSYRIS Technology Corp.
 �̫��s����G2015/08/12 �W�� 11:32:29
 ��L��T�G
============================================
*/
/*---------------------------------------------------------------------------*/
/* �w�q���Y */
#ifndef _GGD_GLOBAL_DEFINITION_H
#define _GGD_GLOBAL_DEFINITION_H

/*---------------------------------------------------------------------------*/
/* �]�t���Y�� */
#include<windef.h> //jash.liao add at 2016/06/01 �A����287~300��M�t�έ��Ʃw�q�����sĶ���~(error: duplicate)
/*---------------------------------------------------------------------------*/
/* ����`�Ʃw�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�Υ���`�ƫŧi�w�q =- */
/* FALSE */
#ifndef FALSE
  #define FALSE 0
#endif

/* TRUE */
#ifndef TRUE
  #define TRUE 1
#endif

/* Apparently this is needed by several Windows compilers */
#ifndef NULL
  #ifdef __cplusplus
    #define NULL 0
  #else
    #define NULL ((void *)0)
  #endif
#endif

#ifndef GGD_STRING_MAX
  #define GGD_STRING_MAX (255)
  #define GGD_DSTRING_MAX (511)
#endif

#ifndef GGD_UINT_MAX
  #define GGD_UINT_MAX (~0U)
  #define GGD_INT_MAX ((int)(GGD_UINT_MAX >> 1))
  #define GGD_INT_MIN ((-GGD_INT_MAX) - 1)
#endif

#ifndef GGD_ULONG_MAX
  #define GGD_ULONG_MAX (~0UL)
  #define GGD_LONG_MAX ((long)(GGD_ULONG_MAX >> 1))
  #define GGD_LONG_MIN ((-GGD_LONG_MAX) - 1)
#endif

#ifndef GGD_MAX_PATH
  #define GGD_MAX_PATH (260)
  #define _GGD_MAX_PATH GGD_MAX_PATH
  #define _GGD_MAX_DRIVE (3)
  #define _GGD_MAX_DIRECTORY (256)
  #define _GGD_MAX_FILENAME (256)
  #define _GGD_MAX_EXTENSION (256)
#endif

/* �`�Φ^�ǭȩw�q */
#ifndef GGD_NO_ERROR
  /* Return function type */
  #define GGD_NO_ERROR GGD_OK
  #define GGD_ERROR 7

  /* Succeeded type */
  #define GGD_OK ((GRESULT)0x00000000L)
  #define GGD_FALSE GGD_MAKE_GRESULT(FALSE, GGD_NO_ERROR, 1)
  #define GGD_SUSPENDED GGD_MAKE_GRESULT(FALSE, GGD_NO_ERROR, 5)
  #define GGD_STILL_ACTIVE GGD_MAKE_GRESULT(FALSE, GGD_NO_ERROR, 6)
  #define GGD_ACCESS_DENIED GGD_MAKE_GRESULT(FALSE, GGD_NO_ERROR, 7)

  /* Failed type */
  #define GGD_ERROR_FAIL GGD_MAKE_GRESULT(TRUE, GGD_ERROR, 0)
  #define GGD_ERROR_ABORT GGD_MAKE_GRESULT(TRUE, GGD_ERROR, 1)
  #define GGD_ERROR_PENDING GGD_MAKE_GRESULT(TRUE, GGD_ERROR, 2)
  #define GGD_ERROR_POINTER GGD_MAKE_GRESULT(TRUE, GGD_ERROR, 3)
  #define GGD_ERROR_HANDLE GGD_MAKE_GRESULT(TRUE, GGD_ERROR, 4)
  #define GGD_ERROR_NO_INTERFACE GGD_MAKE_GRESULT(TRUE, GGD_ERROR, 5)
  #define GGD_ERROR_OUT_OF_MEMORY GGD_MAKE_GRESULT(TRUE, GGD_ERROR, 6)
  #define GGD_ERROR_INVALID_ARGUMENT GGD_MAKE_GRESULT(TRUE, GGD_ERROR, 7)
  #define GGD_ERROR_ACCESS_DENIED GGD_MAKE_GRESULT(TRUE, GGD_ERROR, 8)
  #define GGD_ERROR_UNEXPECTED GGD_MAKE_GRESULT(TRUE, GGD_ERROR, 15)

#endif

/*---------------------------------------------------------------------------*/
/* ���쥨���w�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�Υ��쥨���ŧi�w�q =- */
#ifndef GGD_FAILED
  /* -= �^�ǭȴ��դu�� =- */
  /* ���ѫ��A�^�ǭȴ��� */
  #define GGD_FAILED(Status) ((GRESULT)(Status) < 0)
  /* ���\���A�^�ǭȴ��� */
  #define GGD_SUCCEEDED(Status) ((GRESULT)(Status) >= 0)

  /* -= �O����u�� =- */
  #ifndef __cplusplus
    /* ���w�O���魫�t�m�u���� */
    #ifndef GGD_MEMORY_REALLOCATE_FUNCTION
      #define GGD_MEMORY_REALLOCATE_FUNCTION realloc
    #endif

    /* ���w�O����t�m�u���� */
    #ifndef GGD_MEMORY_ALLOCATE_FUNCTION
      #define GGD_MEMORY_ALLOCATE_FUNCTION malloc
    #endif

    /* ���w�O��������u���� */
    #ifndef GGD_MEMORY_RELEASE_FUNCTION
      #define GGD_MEMORY_RELEASE_FUNCTION free
    #endif

    /* ���w�O���魫�t�m�u�� */
    #define GGD_MEMORY_REALLOCATE(Pointer, Size) GGD_MEMORY_REALLOCATE_FUNCTION((Pointer), (Size))

    /* ���w�O����t�m�u�� */
    #define GGD_MEMORY_ALLOCATE(Size) GGD_MEMORY_ALLOCATE_FUNCTION(Size)

    /* ���w�O��������u�� */
    #define GGD_MEMORY_RELEASE(Pointer) \
      { \
        if((Pointer) != NULL) \
          { \
            GGD_MEMORY_RELEASE_FUNCTION(Pointer); \
            (Pointer) = NULL; \
          } \
      }

    /* �����ܼƫ��V��ƧR�� */
    #define GGD_SAFE_DELETE(Pointer) \
      { \
        if((Pointer) != NULL) \
          { \
            GGD_MEMORY_RELEASE_FUNCTION(Pointer); \
            (Pointer) = NULL; \
          } \
      }

    /* ������Ы��V�������� */
    #define GGD_SAFE_RELEASE(Pointer) \
      { \
        if((Pointer) != NULL) \
          { \
            (Pointer)->Release(); \
            (Pointer) = NULL; \
          } \
      }

  #else
    /* ���w�O���魫�t�m�u���� */
    #ifndef GGD_MEMORY_REALLOCATE_FUNCTION
      #define GGD_MEMORY_REALLOCATE_FUNCTION realloc
    #endif

    /* ���w�O����t�m�u���� */
    #ifndef GGD_MEMORY_ALLOCATE_FUNCTION
      #define GGD_MEMORY_ALLOCATE_FUNCTION malloc
    #endif

    /* ���w�O��������u���� */
    #ifndef GGD_MEMORY_RELEASE_FUNCTION
      #define GGD_MEMORY_RELEASE_FUNCTION free
    #endif

    /* ���w�O���魫�t�m�u�� */
    #define GGD_MEMORY_REALLOCATE(Pointer, Size) GGD_MEMORY_REALLOCATE_FUNCTION((Pointer), (Size))

    /* ���w�O����t�m�u�� */
    #define GGD_MEMORY_ALLOCATE(Size) GGD_MEMORY_ALLOCATE_FUNCTION(Size)

    /* ���w�O��������u�� */
    #define GGD_MEMORY_RELEASE(Pointer) \
      { \
        if((Pointer) != NULL) \
          { \
            GGD_MEMORY_RELEASE_FUNCTION(Pointer); \
            (Pointer) = NULL; \
          } \
      }

    /* �����ܼƫ��V��ƧR�� */
    #define GGD_SAFE_DELETE(Pointer) \
      { \
        if((Pointer) != NULL) \
          { \
            delete (Pointer); \
            (Pointer) = NULL; \
          } \
      }

    /* �����ܼƫ��V�϶��R�� */
    #define GGD_SAFE_DELETE_ARRAY(Pointer) \
      { \
        if((Pointer) != NULL) \
          { \
            delete[] (Pointer); \
            (Pointer) = NULL; \
          } \
      }

    /* ���w���������ܼƫ��V��ƧR�� */
    #define GGD_SAFE_TYPE_DELETE(TypeName, Pointer) \
      { \
        TypeName *TransTypePointer = (TypeName *)(Pointer); \
        if(TransTypePointer != NULL) \
          { \
            delete (TransTypePointer); \
            (TransTypePointer) = NULL; \
            (Pointer) = NULL; \
          } \
      }

    /* ���w���������ܼƫ��V�϶��R�� */
    #define GGD_SAFE_TYPE_DELETE_ARRAY(TypeName, Pointer) \
      { \
        TypeName *TransTypePointer = (TypeName *)(Pointer); \
        if(TransTypePointer != NULL) \
          { \
            delete[] (TransTypePointer); \
            (TransTypePointer) = NULL; \
            (Pointer) = NULL; \
          } \
      }

    /* ������Ы��V�������� */
    #define GGD_SAFE_RELEASE(Pointer) \
      { \
        if((Pointer) != NULL) \
          { \
            (Pointer)->Release(); \
            (Pointer) = NULL; \
          } \
      }

  #endif

  /* -= ��ƹB�� =- */
  /* �X�в����B�n�B�� */
  #define GGD_GET_FLAG_MASK(ShiftCount) (1 << (ShiftCount))
  #define GGD_GET_FIELD_MASK(Field, ShiftCount) ((Field) << (ShiftCount))
  /* �ƭȹB�� */
  #define GGD_GET_ABSOLUTE(Value) (((Value) >= 0) ? (Value) : (-(Value)))
  #define GGD_GET_MINIMUM(ValueA, ValueB) (((ValueA) < (ValueB)) ? (ValueA) : (ValueB))
  #define GGD_GET_MAXIMUM(ValueA, ValueB) (((ValueA) > (ValueB)) ? (ValueA) : (ValueB))
  /* ���ͼƭ� */
  #define GGD_MAKE_BYTE(ValueA, ValueB) ((BYTE)((((BYTE)((ValueA) & 0x0f)) | (((BYTE)((ValueB) & 0x0f)) << 4)) & 0x000000ff))
  #define GGD_MAKE_WORD(ValueA, ValueB) ((WORD)((((BYTE)(ValueA)) | (((BYTE)(ValueB)) << 8)) & 0x0000ffff))
  #define GGD_MAKE_DWORD(ValueA, ValueB, ValueC, ValueD) ((DWORD)((GGD_MAKE_WORD((ValueA), (ValueB)) | (GGD_MAKE_WORD((ValueC), (ValueD)) << 16))))
  /* ���ͦ^�ǭ� */
  #define GGD_MAKE_GRESULT(IsFailed, FunctionType, ResultCode) ((GRESULT)(((DWORD)(IsFailed) << 31) | ((DWORD)(FunctionType) << 16) | ((DWORD)(ResultCode))))
  /* �줸�ոm�� */
  #define GGD_WORD_SWAP(WORDValue) ((WORD)((((WORDValue) << 8) & 0xff00) | ((((WORDValue) >> 8) & 0x00ff))))
  #define GGD_DWORD_SWAP(DWORDValue) ((DWORD)((((DWORDValue) << 24) & 0xff000000) | (((DWORDValue) << 8) & 0x00ff0000) | (((DWORDValue) >> 8) & 0x0000ff00) | (((DWORDValue) >> 24) & 0x000000ff)))

  /* -= �e����} =- */
  #define GGD_GET_MEMBER_OFFSET(TypeName, MemberName) ((DWORD)&(((TypeName *)0)->MemberName))
  #define GGD_GET_CONTAINER(TypeName, MemberName, Pointer) \
    { \
      const typeof(((TypeName *)0)->MemberName) *MemberPointer = (void *)(Pointer); \
      (TypeName *)((BYTE *)MemberPointer - GGD_GET_MEMBER_OFFSET(TypeName, MemberName)); \
    }

#endif

/*---------------------------------------------------------------------------*/
/* ����ŧi���A�w�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�Υ��쫬�A�ŧi�w�q =- */
/* Basic data type defininition. */
/* bool */
#ifndef __cplusplus
  #ifndef bool
    #define bool int
  #endif
#endif

/* DWORD */
#ifndef DWORD
  #define DWORD unsigned long
#endif

/* WORD */
#ifndef WORD
  #define WORD unsigned short
#endif

/* BYTE */
#ifndef BYTE
  #define BYTE unsigned char
#endif

/* Result */
typedef long GRESULT;

/* Point Data Struct */
typedef struct _GGD_POINT
  {
    long lXOffset;
    long lYOffset;
  } GGDPOINT, *LPGGDPOINT;

/* Rect Data Struct */
typedef struct _GGD_RECT
  {
    long lLeft;
    long lTop;
    long lRight;
    long lBottom;
  } GGDRECT, *LPGGDRECT;

/* Rect Data Struct */
typedef struct _GGD_RECT_EX
  {
    int iXOffset;
    int iYOffset;

    WORD wWidth;
    WORD wHeight;
  } GGDRECTEX, *LPGGDRECTEX;

/* Bitmap �w�q */
typedef struct _GGD_BITMAP
  {
    long lType;

    long lBitmapWidth;
    long lBitmapHeight;

    long lWidthBytes;

    WORD wPlanes;
    WORD wBitsPerPixel;

    BYTE *lpDIB;
  } GGDBITMAP, *LPGGDBITMAP;

/* Bitmap File �w�q */
typedef struct _GGD_BITMAP_FILE
  {
    long lType;

    long lBitmapWidth;
    long lBitmapHeight;

    long lWidthBytes;

    WORD wPlanes;
    WORD wBitsPerPixel;

    BYTE bytDIB[1];
  } GGDBITMAPFILE, *LPGGDBITMAPFILE;

/*---------------------------------------------------------------------------*/
/* �����ܼƫŧi */

/*---------------------------------------------------------------------------*/
/* ���Ψ�ƫŧi */

/*---------------------------------------------------------------------------*/
/* �w�q���Y���� */
#endif

/*---------------------------------------------------------------------------*/
/* �ɮ׵��� */

