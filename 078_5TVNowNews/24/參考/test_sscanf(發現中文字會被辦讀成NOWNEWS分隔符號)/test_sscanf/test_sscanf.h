
// test_sscanf.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// Ctest_sscanfApp:
// �аѾ\��@�����O�� test_sscanf.cpp
//

class Ctest_sscanfApp : public CWinAppEx
{
public:
	Ctest_sscanfApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern Ctest_sscanfApp theApp;