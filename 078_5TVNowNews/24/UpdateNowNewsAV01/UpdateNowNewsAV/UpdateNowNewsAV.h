
// UpdateNowNewsAV.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CUpdateNowNewsAVApp:
// �аѾ\��@�����O�� UpdateNowNewsAV.cpp
//

class CUpdateNowNewsAVApp : public CWinAppEx
{
public:
	CUpdateNowNewsAVApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CUpdateNowNewsAVApp theApp;