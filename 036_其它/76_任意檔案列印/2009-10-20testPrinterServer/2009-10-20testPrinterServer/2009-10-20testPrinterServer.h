// 2009-10-20testPrinterServer.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMy20091020testPrinterServerApp:
// �аѾ\��@�����O�� 2009-10-20testPrinterServer.cpp
//

class CMy20091020testPrinterServerApp : public CWinApp
{
public:
	CMy20091020testPrinterServerApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMy20091020testPrinterServerApp theApp;