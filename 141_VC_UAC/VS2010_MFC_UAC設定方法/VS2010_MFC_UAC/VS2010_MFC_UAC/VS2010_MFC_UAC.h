
// VS2010_MFC_UAC.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CVS2010_MFC_UACApp:
// �аѾ\��@�����O�� VS2010_MFC_UAC.cpp
//

class CVS2010_MFC_UACApp : public CWinApp
{
public:
	CVS2010_MFC_UACApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CVS2010_MFC_UACApp theApp;