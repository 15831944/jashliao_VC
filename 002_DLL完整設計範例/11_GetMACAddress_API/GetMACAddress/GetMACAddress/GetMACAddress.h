// GetMACAddress.h : GetMACAddress DLL ���D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�
///////////////////////////////////////////
//step 01 by jash at 2010/10/20
#include <Iphlpapi.h>
#include <Assert.h>
#include <stdio.h>
#pragma comment(lib, "iphlpapi.lib")
//////////////////////////////////////////
// CGetMACAddressApp
// �o�����O����@�аѾ\ GetMACAddress.cpp
//
////////////////////////////////////////////////////////////////
//step 02 by jash at 2010/10/20
#define EXPORTED_DLL_FUNCTION \
__declspec(dllexport) __stdcall
BSTR EXPORTED_DLL_FUNCTION GetMACAddress ();
/////////////////////////////////////////////////////////////////
class CGetMACAddressApp : public CWinApp
{
public:
	CGetMACAddressApp();

// �мg
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
