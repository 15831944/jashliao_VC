
// test_VS2008_MFC_NET.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// Ctest_VS2008_MFC_NETApp:
// �аѾ\��@�����O�� test_VS2008_MFC_NET.cpp
//

class Ctest_VS2008_MFC_NETApp : public CWinAppEx
{
public:
	Ctest_VS2008_MFC_NETApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern Ctest_VS2008_MFC_NETApp theApp;