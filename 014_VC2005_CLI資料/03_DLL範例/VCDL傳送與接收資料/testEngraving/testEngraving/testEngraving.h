// testEngraving.h : testEngraving DLL ���D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CtestEngravingApp
// �o�����O����@�аѾ\ testEngraving.cpp
//
struct EngarveElement{
	long Type;
	long CCW;
	double X1;
	double Y1;
	double Z1;
	double X2;
	double Y2;
	double Z2;
};

struct point
{
	double x;
	double y;
};
EngarveElement *EE;
long n;
#define EXPORTED_DLL_FUNCTION \
 __declspec(dllexport) __stdcall
void EXPORTED_DLL_FUNCTION GetValue1(EngarveElement *p,long number);
long EXPORTED_DLL_FUNCTION SendValue1(EngarveElement *p);
class CtestEngravingApp : public CWinApp
{
public:
	CtestEngravingApp();

// �мg
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
