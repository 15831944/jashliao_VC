
// Win7_Volume.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CWin7_VolumeApp:
// �аѾ\��@�����O�� Win7_Volume.cpp
//

class CWin7_VolumeApp : public CWinAppEx
{
public:
	CWin7_VolumeApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CWin7_VolumeApp theApp;