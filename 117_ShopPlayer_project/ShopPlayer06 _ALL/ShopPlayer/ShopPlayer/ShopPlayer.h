// ShopPlayer.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CShopPlayerApp:
// �аѾ\��@�����O�� ShopPlayer.cpp
//

class CShopPlayerApp : public CWinApp
{
public:
	CShopPlayerApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CShopPlayerApp theApp;