/*
============================================
 �ɮצW�١Gghld_hallib_define.h
 �{���\��GHAL Library Definition
 �]�p�̡GSeamus Berloz (�a��������ù)
 ���v�֦��̡GSYRIS Technology Corp.
 �̫��s����G2016/05/06 �W�� 11:32:29
 ��L��T�G
============================================
*/
/*---------------------------------------------------------------------------*/
/* �w�q���Y */
#ifndef _GHLD_HAL_LIBRARY_DEFINITION_H
#define _GHLD_HAL_LIBRARY_DEFINITION_H

/*---------------------------------------------------------------------------*/
/* �]�t���Y�� */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �зǥ]�t�� =- */
#ifdef GHLD_BINDING_HAL_LIBRARY_ENABLED
  #ifdef GHLD_BINDING_HAL_LIBRARY_WITH_SDL
    #include <SDL/SDL.h>
  #endif
#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �۩w�q�]�t�� =- */
#include "ggd_global_define.h"

/*---------------------------------------------------------------------------*/
/* �sĶ�ѧO�`�Ʃw�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�νsĶ�ѧO�`�ƫŧi�w�q =- */
/* �w���H�h�{���w�����ŧi�w�q */
#define GHLD_LIBRARY_NONE 0
#define GHLD_LIBRARY_SDL 1

/* �w���H�h�{���w�P��ŧi�w�q */
#ifdef GHLD_BINDING_HAL_LIBRARY_ENABLED
  #ifdef GHLD_BINDING_HAL_LIBRARY_WITH_SDL
    #define GHLD_LIBRARY GHLD_LIBRARY_SDL
  #else
    #define GHLD_LIBRARY GHLD_LIBRARY_NONE
  #endif
#endif

/* �t�Φ줸�սs�Ƥ覡�ѧO�`�Ʃw�q */
/* �f�t SDL �禡�w�w�q */
#if (GHLD_LIBRARY == GHLD_LIBRARY_SDL)
  /* system endian */
  #define GHLD_SYSTEM_BIG_ENDIAN SDL_BIG_ENDIAN
  #define GHLD_SYSTEM_LITTLE_ENDIAN SDL_LIL_ENDIAN
  
  #ifndef GHLD_SYSTEM_ENDIAN
    #if (defined(__hppa__) || defined(__sparc__) || defined(__ARMEB__) || \
        (defined(__MIPS__) && defined(__MISPEB__)) || \
        (defined(__ppc__) || defined(__POWERPC__)  || defined(_M_PPC)) || \
        (defined(__m68k__) || defined(mc68000)  || defined(_M_M68K)))
      
      #define GHLD_SYSTEM_ENDIAN GHLD_SYSTEM_BIG_ENDIAN
    #else
      #define GHLD_SYSTEM_ENDIAN GHLD_SYSTEM_LITTLE_ENDIAN
    #endif
  #endif
  
  #ifndef GHLD_SYSTEM_ENDIAN
    /* ARM embedded system endian */
    #ifdef __ARMEB__
      #define GHLD_SYSTEM_ENDIAN GHLD_SYSTEM_BIG_ENDIAN
    #else
      #define GHLD_SYSTEM_ENDIAN GHLD_SYSTEM_LITTLE_ENDIAN
    #endif
  #endif
#endif

/*---------------------------------------------------------------------------*/
/* ����`�Ʃw�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�Υ���`�Ʃw�q =- */
/* �f�t SDL �禡�w�w�q */
#if (GHLD_LIBRARY == GHLD_LIBRARY_SDL)
  /* ��ܼҦ��]�w�X�Х����`�ƦC�|��ƫ��A�ŧi�w�q */
  #define GHLD_VIDEO_MODE_FLAG_MACRO (SDL_HWSURFACE | SDL_DOUBLEBUF)

#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�α`�ƦW�٧O�W���� =- */
/* �w���H�h�`�ƦW�٧O�W���� */
/* �f�t SDL �禡�w�w�q */
#if (GHLD_LIBRARY == GHLD_LIBRARY_SDL)
  /* Transparency definitions: These define alpha as the opacity of a surface */
  #define GHLD_PIXEL_ALPHA_OPAQUE SDL_ALPHA_OPAQUE
  #define GHLD_PIXEL_ALPHA_TRANSPARENT SDL_ALPHA_TRANSPARENT
  
  /* color in 16 bit screen color space operation */
  #define GHLD_PIXEL_RED_COLOR_MASK 0x1f
  #define GHLD_PIXEL_GREEN_COLOR_MASK 0x1f
  #define GHLD_PIXEL_BLUE_COLOR_MASK 0x1f
  #define GHLD_PIXEL_RED_COLOR_SHIFT GHLD_PIXEL_BITS_FLAGS_FIELD_RED_COLOR_BIT0
  #define GHLD_PIXEL_GREEN_COLOR_SHIFT GHLD_PIXEL_BITS_FLAGS_FIELD_GREEN_COLOR_BIT0
  #define GHLD_PIXEL_BLUE_COLOR_SHIFT GHLD_PIXEL_BITS_FLAGS_FIELD_BLUE_COLOR_BIT0

#endif

/*---------------------------------------------------------------------------*/
/* ����`�Υ����ŧi�w�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�Υ��쥨���ŧi�w�q =- */
/* �f�t SDL �禡�w�w�q */
#if (GHLD_LIBRARY == GHLD_LIBRARY_SDL)
  /* RGB �T���� (in 24-bits) �� 555 �����w�q */
  #define GHLD_GET_RGB555(RedColor, GreenColor, BlueColor) ((((((DWORD)(RedColor)) >> 3) & 0x1f) << 10) | (((((DWORD)(GreenColor)) >> 3) & 0x1f) << 5) | ((((DWORD)(BlueColor)) >> 3) & 0x1f))
  /* RGB �T���� (in 24-bits) �� 565 �����w�q */
  #define GHLD_GET_RGB565(RedColor, GreenColor, BlueColor) ((((((DWORD)(RedColor)) >> 3) & 0x1f) << 11) | (((((DWORD)(GreenColor)) >> 3) & 0x3f) << 5) | ((((DWORD)(BlueColor)) >> 3) & 0x1f))
  
  /* color transformation to 16 bit color space */
  #define GHLD_COLORS_FROM_RGB555(RedColor, GreenColor, BlueColor) (((((DWORD)(RedColor)) << 10) & 0x7c00) | ((((DWORD)(GreenColor)) << 5) & 0x3e0) | (((DWORD)(BlueColor)) & 0x1f))
  #define GHLD_COLORS_FROM_RGB565(RedColor, GreenColor, BlueColor) (((((DWORD)(RedColor)) << 11) & 0xf800) | ((((DWORD)(GreenColor)) << 5) & 0x7e0) | (((DWORD)(BlueColor)) & 0x1f))
  #define GHLD_COLORS_FROM_RGB888(RedColor, GreenColor, BlueColor) GHLD_GET_RGB555(RedColor, GreenColor, BlueColor)
  
#endif

/*---------------------------------------------------------------------------*/
/* ����ŧi���A�w�q */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= ���A�O�W�ŧi�w�q =- */
/* �f�t SDL �禡�w�w�q */
#if (GHLD_LIBRARY == GHLD_LIBRARY_SDL)
  /* SDL ���c�W�٧O�W���� */
  #define SDLRECT SDL_Rect
  #define SDLEVENT SDL_Event
  #define SDLTHREAD SDL_Thread
  #define SDLSURFACE SDL_Surface
  #define SDLVIDEOINFO SDL_VideoInfo
  #define SDLAUDIOSPEC SDL_AudioSpec
  #define SDLAUDIOCONVERTER SDL_AudioCVT
  
#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�α`�ƦC�|��ƫ��A�ŧi�w�q =- */
/* �f�t SDL �禡�w�w�q */
#if (GHLD_LIBRARY == GHLD_LIBRARY_SDL)
  
#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�κX�����`�ƦC�|��ƫ��A�ŧi�w�q =- */
/* �f�t SDL �禡�w�w�q */
#if (GHLD_LIBRARY == GHLD_LIBRARY_SDL)
  /* �����줸�X�б`�ƦC�|���A�ŧi�w�q */
  enum _GHLD_PIXEL_BITS_FLAGS_FIELD_DEFINITION
    {
      /* �Ŧ��C��Ȱ� */
      GHLD_PIXEL_BITS_FLAGS_FIELD_BLUE_COLOR_BIT0,
      GHLD_PIXEL_BITS_FLAGS_FIELD_BLUE_COLOR_BIT1,
      GHLD_PIXEL_BITS_FLAGS_FIELD_BLUE_COLOR_BIT2,
      GHLD_PIXEL_BITS_FLAGS_FIELD_BLUE_COLOR_BIT3,
      GHLD_PIXEL_BITS_FLAGS_FIELD_BLUE_COLOR_BIT4,
      
      /* ����C��Ȱ� */
      GHLD_PIXEL_BITS_FLAGS_FIELD_GREEN_COLOR_BIT0,
      GHLD_PIXEL_BITS_FLAGS_FIELD_GREEN_COLOR_BIT1,
      GHLD_PIXEL_BITS_FLAGS_FIELD_GREEN_COLOR_BIT2,
      GHLD_PIXEL_BITS_FLAGS_FIELD_GREEN_COLOR_BIT3,
      GHLD_PIXEL_BITS_FLAGS_FIELD_GREEN_COLOR_BIT4,
      
      /* �����C��Ȱ� */
      GHLD_PIXEL_BITS_FLAGS_FIELD_RED_COLOR_BIT0,
      GHLD_PIXEL_BITS_FLAGS_FIELD_RED_COLOR_BIT1,
      GHLD_PIXEL_BITS_FLAGS_FIELD_RED_COLOR_BIT2,
      GHLD_PIXEL_BITS_FLAGS_FIELD_RED_COLOR_BIT3,
      GHLD_PIXEL_BITS_FLAGS_FIELD_RED_COLOR_BIT4,
      
      GHLD_PIXEL_BITS_FLAGS_FIELD_AMOUNT = 15
    };
  
#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�κX�б`�ƦC�|���A�O�W�ŧi�w�q =- */
/* �f�t SDL �禡�w�w�q */
#if (GHLD_LIBRARY == GHLD_LIBRARY_SDL)
  /* �����Ȱ�B�n�`�ƦC�|���A�ŧi�w�q */
  enum _GHLD_PIXEL_MASK_DEFINITION
    {
      GHLD_PIXEL_RED_COLOR_FIELD_MASK = GGD_GET_FIELD_MASK(GHLD_PIXEL_RED_COLOR_MASK, GHLD_PIXEL_BITS_FLAGS_FIELD_RED_COLOR_BIT0),
      GHLD_PIXEL_GREEN_COLOR_FIELD_MASK = GGD_GET_FIELD_MASK(GHLD_PIXEL_GREEN_COLOR_MASK, GHLD_PIXEL_BITS_FLAGS_FIELD_GREEN_COLOR_BIT0),
      GHLD_PIXEL_BLUE_COLOR_FIELD_MASK = GGD_GET_FIELD_MASK(GHLD_PIXEL_BLUE_COLOR_MASK, GHLD_PIXEL_BITS_FLAGS_FIELD_BLUE_COLOR_BIT0),
      
    };
  
#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= �`�κX�Х����`�ƦC�|��ƫ��A�ŧi�w�q =- */
/* �f�t SDL �禡�w�w�q */
#if (GHLD_LIBRARY == GHLD_LIBRARY_SDL)
  
#endif

/*---------------------------------------------------------------------------*/
/* �����ܼƫŧi */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= ���줽���ܼƫŧi�w�q =- */
/* �f�t SDL �禡�w�w�q */
#if (GHLD_LIBRARY == GHLD_LIBRARY_SDL)
  
#endif

/*---------------------------------------------------------------------------*/
/* ���Ϊ������O�ŧi */

/*---------------------------------------------------------------------------*/
/* ���Ϊ������O�˪� */

/*---------------------------------------------------------------------------*/
/* ���Ψ�ƫŧi */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -= ��ƧO�W�ŧi�w�q =- */
/* �f�t SDL �禡�w�w�q */
#if (GHLD_LIBRARY == GHLD_LIBRARY_SDL)
  /* SDL ��ƦW�٧O�W���� */
  /* SDL �B�@�T���B�z���� */
  #define SDLSetError SDL_SetError
  #define SDLGetError SDL_GetError
  /* SDL �ɶ��B�@�B�z���� */
  #define SDLGetTicks SDL_GetTicks
  #define SDLDelay SDL_Delay
  /* �ʺA�{���w�B�z���� */
  #define SDLLoadObject SDL_LoadObject
  #define SDLUnloadObject SDL_UnloadObject
  #define SDLLoadFunction SDL_LoadFunction
  /* SDL �h������B�z���� */
  #define SDLCreateThread SDL_CreateThread
  #define SDLThreadID SDL_ThreadID
  #define SDLGetThreadID SDL_GetThreadID
  #define SDLWaitThread SDL_WaitThread
  #define SDLKillThread SDL_KillThread
  /* SDL �B�@��l�ƳB�z���� */
  #define SDLInitialize SDL_Init
  #define SDLQuit SDL_Quit
  #define SDLSubSystemInitialize SDL_InitSubSystem
  #define SDLWasInitial SDL_WasInit
  /* SDL �ƥ�B�@�B�z���� */
  #define SDLPollEvent SDL_PollEvent
  /* SDL �g���J�B�@�B�z���� */
  #define SDLGetKeyState SDL_GetKeyState
  #define SDLWarpMouse SDL_WarpMouse
  #define SDLShowCursor SDL_ShowCursor
  /* SDL ��ܹB�@�B�z���� */
  #define SDLGetVideoInfo SDL_GetVideoInfo
  #define SDLVideoDriverName SDL_VideoDriverName
  #define SDLVideoModeOK SDL_VideoModeOK
  #define SDLSetVideoMode SDL_SetVideoMode
  /* SDL ø�ϹB�@�B�z���� */
  #define SDLCreateRGBSurface SDL_CreateRGBSurface
  #define SDLFreeSurface SDL_FreeSurface
  #define SDLDisplayFormat SDL_DisplayFormat
  #define SDLDisplayFormatAlpha SDL_DisplayFormatAlpha
  #define SDLSetAlpha SDL_SetAlpha
  #define SDLSetColorKey SDL_SetColorKey
  #define SDLBlitSurface SDL_BlitSurface
  #define SDLFillRect SDL_FillRect
  #define SDLMapRGB SDL_MapRGB
  #define SDLFlip SDL_Flip
  #define SDLMustLock SDL_MUSTLOCK
  #define SDLLockSurface SDL_LockSurface
  #define SDLUnlockSurface SDL_UnlockSurface
  /* SDL �����޲z���� */
  #define SDLWMGetWindowInfo SDL_GetWMInfo
  #define SDLWMSetCaption SDL_WM_SetCaption
  #define SDLWMToggleFullScreen SDL_WM_ToggleFullScreen
  /* SDL �n���B�z���� */
  #define SDLOpenAudio SDL_OpenAudio
  #define SDLCloseAudio SDL_CloseAudio
  #define SDLPauseAudio SDL_PauseAudio 
  #define SDLLockAudio SDL_LockAudio
  #define SDLUnlockAudio SDL_UnlockAudio
  #define SDLLoadWaveWithSDLRW SDL_LoadWAV_RW
  #define SDLFreeWave SDL_FreeWAV
  #define SDLMixAudio SDL_MixAudio
  #define SDLConvertAudio SDL_ConvertAudio
  #define SDLBuildAudioConverter SDL_BuildAudioCVT
  /* SDL �S��Ū�g�B�z���� */
  #define SDLRWFromFile SDL_RWFromFile
  #define SDLRWFromMem SDL_RWFromMem
  #define SDLRWTell SDL_RWtell
  #define SDLRWRead SDL_RWread
  #define SDLRWClose SDL_RWclose
  #define SDLRWSeek SDL_RWseek
  /* SDL ��ͦr�`�f�t�S��Ū�g�B�z���� */
  #define SDLReadLE32 SDL_ReadLE32
  
#endif

/*---------------------------------------------------------------------------*/
/* �w�q���Y���� */
#endif

/*---------------------------------------------------------------------------*/
/* �ɮ׵��� */

