// Check5TVEncoderChannel.cpp : �w�q���ε{�������O�欰�C
//

#include "stdafx.h"
#include "Check5TVEncoderChannel.h"
#include "Check5TVEncoderChannelDlg.h"
#include "CWMPCdromCollection.h"
#include "CWMPClosedCaption.h"
#include "CWMPClosedCaption2.h"
#include "CWMPControls.h"
#include "CWMPControls2.h"
#include "CWMPControls3.h"
#include "CWMPDVD.h"
#include "CWMPError.h"
#include "CWMPErrorItem.h"
#include "CWMPErrorItem2.h"
#include "CWMPMedia.h"
#include "CWMPMedia2.h"
#include "CWMPMedia3.h"
#include "CWMPMediaCollection.h"
#include "CWMPMediaCollection2.h"
#include "CWMPMetadataPicture.h"
#include "CWMPMetadataText.h"
#include "CWMPPlayer.h"
#include "CWMPPlayer2.h"
#include "CWMPPlayer3.h"
#include "CWMPPlayer4.h"
#include "CWMPPlaylist.h"
#include "CWMPPlaylistCollection.h"
#include "CWMPSettings.h"
#include "CWMPSettings2.h"
#include "CWMPStringCollection2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCheck5TVEncoderChannelApp

BEGIN_MESSAGE_MAP(CCheck5TVEncoderChannelApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCheck5TVEncoderChannelApp �غc

CCheck5TVEncoderChannelApp::CCheck5TVEncoderChannelApp()
{
	// TODO: �b���[�J�غc�{���X�A
	// �N�Ҧ����n����l�]�w�[�J InitInstance ��
}


// �Ȧ����@�� CCheck5TVEncoderChannelApp ����

CCheck5TVEncoderChannelApp theApp;


// CCheck5TVEncoderChannelApp ��l�]�w

BOOL CCheck5TVEncoderChannelApp::InitInstance()
{
	// ���p���ε{����T�M����w�ϥ� ComCtl32.dll 6 (�t) �H�᪩���A
	// �ӱҰʵ�ı�Ƽ˦��A�b Windows XP �W�A�h�ݭn InitCommonControls()�C
	// �_�h����������إ߳��N���ѡC
	if(!OnlyOneCheck())
	{
		return FALSE;
	}
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �]�w�n�]�t�Ҧ��z�Q�n�Ω����ε{������
	// �q�α�����O�C
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	::CoInitialize(NULL); //step 2:Ū��XML
	AfxEnableControlContainer();

	// �зǪ�l�]�w
	// �p�G�z���ϥγo�ǥ\��åB�Q���
	// �̫᧹�����i�����ɤj�p�A�z�i�H
	// �q�U�C�{���X�������ݭn����l�Ʊ`���A
	// �ܧ��x�s�]�w�Ȫ��n�����X
	// TODO: �z���ӾA�׭ק惡�r��
	// (�Ҧp�A���q�W�٩β�´�W��)
	SetRegistryKey(_T("���� AppWizard �Ҳ��ͪ����ε{��"));

	CCheck5TVEncoderChannelDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �b����m��ϥ� [�T�w] �Ӱ���ϥι�ܤ����
		// �B�z���{���X
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �b����m��ϥ� [����] �Ӱ���ϥι�ܤ����
		// �B�z���{���X
	}

	// �]���w�g������ܤ���A�Ǧ^ FALSE�A�ҥH�ڭ̷|�������ε{���A
	// �ӫD���ܶ}�l���ε{�����T���C
	return FALSE;
}
BOOL CCheck5TVEncoderChannelApp::OnlyOneCheck()
{
	CWnd *pWndPrev,*pWndChild;
	if(pWndPrev=CWnd::FindWindowW(_T("#32770"),_T("Check5TVEncoderChannel")))
	{
		pWndChild=pWndPrev->GetLastActivePopup();
		if(pWndChild->IsIconic())
		{
			pWndPrev->ShowWindow(SW_RESTORE);
		}
		pWndChild->SetForegroundWindow();
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}