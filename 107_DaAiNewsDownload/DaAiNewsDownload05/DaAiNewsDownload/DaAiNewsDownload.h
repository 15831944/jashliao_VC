
// DaAiNewsDownload.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CDaAiNewsDownloadApp:
// �аѾ\��@�����O�� DaAiNewsDownload.cpp
//

class CDaAiNewsDownloadApp : public CWinAppEx
{
public:
	CDaAiNewsDownloadApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CDaAiNewsDownloadApp theApp;