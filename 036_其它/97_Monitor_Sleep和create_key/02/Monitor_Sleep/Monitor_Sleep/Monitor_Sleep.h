
// Monitor_Sleep.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMonitor_SleepApp:
// �аѾ\��@�����O�� Monitor_Sleep.cpp
//

class CMonitor_SleepApp : public CWinApp
{
public:
	CMonitor_SleepApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMonitor_SleepApp theApp;