// VS2008ExecuteAConsole.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CVS2008ExecuteAConsoleApp:
// �аѾ\��@�����O�� VS2008ExecuteAConsole.cpp
//

class CVS2008ExecuteAConsoleApp : public CWinApp
{
public:
	CVS2008ExecuteAConsoleApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CVS2008ExecuteAConsoleApp theApp;