
// MFC_get_version.h : PROJECT_NAME ���ó�ʽ����Ҫ���^�n
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �����˙n��ǰ�Ȱ��� 'stdafx.h'"
#endif

#include "resource.h"		// ��Ҫ��̖


// CMFC_get_versionApp: 
// Ո��醌�����e�� MFC_get_version.cpp
//

class CMFC_get_versionApp : public CWinApp
{
public:
	CMFC_get_versionApp();

// ����
public:
	virtual BOOL InitInstance();

// ��ʽ�a����

	DECLARE_MESSAGE_MAP()
};

extern CMFC_get_versionApp theApp;