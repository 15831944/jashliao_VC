
// SearchFile2SQLite.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CSearchFile2SQLiteApp:
// �аѾ\��@�����O�� SearchFile2SQLite.cpp
//

class CSearchFile2SQLiteApp : public CWinAppEx
{
public:
	CSearchFile2SQLiteApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CSearchFile2SQLiteApp theApp;