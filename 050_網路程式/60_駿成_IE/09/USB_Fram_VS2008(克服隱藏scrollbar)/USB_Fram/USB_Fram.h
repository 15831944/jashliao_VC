
// USB_Fram.h : USB_Fram ���ε{�����D���Y��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"       // �D�n�Ÿ�


// CUSB_FramApp:
// �аѾ\��@�����O�� USB_Fram.cpp
//

class CUSB_FramApp : public CWinApp
{
public:
	CUSB_FramApp();


// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CUSB_FramApp theApp;
