// VS2008test02.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CVS2008test02App:
// �аѾ\��@�����O�� VS2008test02.cpp
//

class CVS2008test02App : public CWinApp
{
public:
	CVS2008test02App();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CVS2008test02App theApp;