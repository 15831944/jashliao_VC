
// MFC_configuring_Firewalls.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFC_configuring_FirewallsApp:
// �аѾ\��@�����O�� MFC_configuring_Firewalls.cpp
//

class CMFC_configuring_FirewallsApp : public CWinApp
{
public:
	CMFC_configuring_FirewallsApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMFC_configuring_FirewallsApp theApp;