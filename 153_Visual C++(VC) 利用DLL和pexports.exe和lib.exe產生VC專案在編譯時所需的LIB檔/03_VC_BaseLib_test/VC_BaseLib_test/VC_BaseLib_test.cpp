// VC_BaseLib_test.cpp : ���x����̨���ó�ʽ���M���c��
//

#include "stdafx.h"

//---
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

#ifdef __cplusplus
}
#endif
//---

int _tmain(int argc, _TCHAR* argv[])
{
	printf("%d",Add(10,25));
	return 0;
}

