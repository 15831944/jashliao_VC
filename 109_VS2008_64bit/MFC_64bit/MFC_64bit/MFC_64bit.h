// MFC_64bit.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFC_64bitApp:
// �аѾ\��@�����O�� MFC_64bit.cpp
//

class CMFC_64bitApp : public CWinApp
{
public:
	CMFC_64bitApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMFC_64bitApp theApp;