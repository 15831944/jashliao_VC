// CdToWav.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CCdToWavApp:
// �йش����ʵ�֣������ CdToWav.cpp
//

class CCdToWavApp : public CWinApp
{
public:
	CCdToWavApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCdToWavApp theApp;
