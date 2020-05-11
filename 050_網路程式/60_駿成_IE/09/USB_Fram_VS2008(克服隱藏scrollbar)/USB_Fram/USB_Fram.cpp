
// USB_Fram.cpp : �w�q���ε{�������O�欰�C
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "USB_Fram.h"
#include "MainFrm.h"

#include "USB_FramDoc.h"
#include "USB_FramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUSB_FramApp

BEGIN_MESSAGE_MAP(CUSB_FramApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CUSB_FramApp::OnAppAbout)
	// �̾ڤ��R�O���з��ɮ�
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CUSB_FramApp �غc

CUSB_FramApp::CUSB_FramApp()
{

	// TODO: �b���[�J�غc�{���X�A
	// �N�Ҧ����n����l�]�w�[�J InitInstance ��
}

// �Ȧ����@�� CUSB_FramApp ����

CUSB_FramApp theApp;


// CUSB_FramApp ��l�]�w

BOOL CUSB_FramApp::InitInstance()
{
	// ���p���ε{����T�M����w�ϥ� ComCtl32.dll 6 (�t) �H�᪩���A
	// �ӱҰʵ�ı�Ƽ˦��A�b Windows XP �W�A�h�ݭn InitCommonControls()�C
	// �_�h����������إ߳��N���ѡC
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �]�w�n�]�t�Ҧ��z�Q�n�Ω����ε{������
	// �q�α�����O�C
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// ��l�� OLE �{���w
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// �зǪ�l�]�w
	// �p�G�z���ϥγo�ǥ\��åB�Q���
	// �̫᧹�����i�����ɤj�p�A�z�i�H
	// �q�U�C�{���X�������ݭn����l�Ʊ`���A
	// �ܧ��x�s�]�w�Ȫ��n�����X
	// TODO: �z���ӾA�׭ק惡�r��
	// (�Ҧp�A���q�W�٩β�´�W��)
	SetRegistryKey(_T("���� AppWizard �Ҳ��ͪ����ε{��"));
	LoadStdProfileSettings(4);  // ���J�з� INI �ɿﶵ (�]�t MRU)

	// �n�����ε{�������d���C���d���t�d�b���B
	// �ج[�����P�˵����i��s��
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CUSB_FramDoc),
		RUNTIME_CLASS(CMainFrame),       // �D SDI �ج[����
		RUNTIME_CLASS(CUSB_FramView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// ��R�з� Shell �R�O�BDDE�B�ɮ׶}�����ɪ��R�O�C
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// �b�R�O�C�����w�������R�O�C�p�G�w�ϥ� 
	// /RegServer�B/Register�B/Unregserver �� /Unregister �Ұ����ε{���A�N�Ǧ^ FALSE�C
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// �Ȫ�l�Ƥ@�ӵ����A�ҥH��ܨç�s�ӵ���
	m_pMainWnd->SetWindowText("IPTV");
	int intH,intW;
	int intH1,intW1;
	intW=GetSystemMetrics(SM_CXSCREEN);
	intH=GetSystemMetrics(SM_CYSCREEN);
	FILE *pf='\0';
	pf=fopen("size.txt","r");
	fscanf(pf,"%d,%d,",&intW1,&intH1);
	fclose(pf);
	if((intW<intW1)||(intH<intH1))
	{
		m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	}
	else
	{
		m_pMainWnd->SetWindowPos(NULL,0,0,intW1,intH1,SWP_NOZORDER);
	}
	m_pMainWnd->UpdateWindow();
	return TRUE;
}



// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ܤ�����
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �����ܤ�������ε{���R�O
void CUSB_FramApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CUSB_FramApp �T���B�z�`��



