// Check5TVEncoderChannel.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CCheck5TVEncoderChannelApp:
// �аѾ\��@�����O�� Check5TVEncoderChannel.cpp
//

class CCheck5TVEncoderChannelApp : public CWinApp
{
public:
	CCheck5TVEncoderChannelApp();

// �мg
	public:
	virtual BOOL InitInstance();
	/////////////////////////////////////////////////
	BOOL OnlyOneCheck();
// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CCheck5TVEncoderChannelApp theApp;