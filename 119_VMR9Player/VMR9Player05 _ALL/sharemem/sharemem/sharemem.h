// sharemem.h : sharemem DLL ���D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CsharememApp
// �o�����O����@�аѾ\ sharemem.cpp
//
#pragma data_seg("jash")
char chrshare[200]="test";
#pragma data_seg()
#pragma comment(linker, "/Section:jash,RWS")
#define EXPORTED_DLL_FUNCTION \
 __declspec(dllexport) __stdcall
void EXPORTED_DLL_FUNCTION jashGetValue (char *outData);
void EXPORTED_DLL_FUNCTION jashSetValue (char *inData);
class CsharememApp : public CWinApp
{
public:
	CsharememApp();

// �мg
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
