
// MFC_UAC_Execution_Level.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFC_UAC_Execution_LevelApp:
// �аѾ\��@�����O�� MFC_UAC_Execution_Level.cpp
//

class CMFC_UAC_Execution_LevelApp : public CWinAppEx
{
public:
	CMFC_UAC_Execution_LevelApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMFC_UAC_Execution_LevelApp theApp;