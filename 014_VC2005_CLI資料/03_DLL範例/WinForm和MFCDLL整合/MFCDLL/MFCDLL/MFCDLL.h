// MFCDLL.h : MFCDLL DLL ���D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFCDLLApp
// �o�����O����@�аѾ\ MFCDLL.cpp
//
#define EXPORTED_DLL_FUNCTION \
 __declspec(dllexport) __stdcall

int EXPORTED_DLL_FUNCTION add (int a, int b);
class CMFCDLLApp : public CWinApp
{
public:
	CMFCDLLApp();

// �мg
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
