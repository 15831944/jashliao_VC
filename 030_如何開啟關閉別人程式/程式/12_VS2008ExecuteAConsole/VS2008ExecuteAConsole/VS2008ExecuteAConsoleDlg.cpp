// VS2008ExecuteAConsoleDlg.cpp : ��@��
//

#include "stdafx.h"
#include "VS2008ExecuteAConsole.h"
#include "VS2008ExecuteAConsoleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CVS2008ExecuteAConsoleDlg ��ܤ��




CVS2008ExecuteAConsoleDlg::CVS2008ExecuteAConsoleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVS2008ExecuteAConsoleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVS2008ExecuteAConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVS2008ExecuteAConsoleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CVS2008ExecuteAConsoleDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CVS2008ExecuteAConsoleDlg �T���B�z�`��

BOOL CVS2008ExecuteAConsoleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CVS2008ExecuteAConsoleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CVS2008ExecuteAConsoleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CVS2008ExecuteAConsoleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CVS2008ExecuteAConsoleDlg::OnBnClickedButton1()
{
	SECURITY_ATTRIBUTES sa,sa2;
	HANDLE hInputRead,hInputWrite;
	HANDLE hOutputRead,hOutputWrite;
	//CreatePipe1
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hOutputRead,&hOutputWrite,&sa,0))
	{
		return;
	}
	//CreatePipe2
	sa2.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa2.lpSecurityDescriptor = NULL;
	sa2.bInheritHandle = TRUE;
	if (!CreatePipe(&hInputRead,&hInputWrite,&sa2,0))
	{
		return;
	}
	//CreateProcess
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hOutputWrite;
	si.hStdOutput = hOutputWrite;
	si.hStdInput = hInputRead;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	DWORD dwWritten;
	if (!CreateProcess(_T("C:\\Windows\\System32\\cmd.exe"),NULL,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))
	{
		MessageBox(L"Error On CreateProcess");
		return;
	}
	CloseHandle(hInputRead);
	CloseHandle(hOutputWrite);
	//Write and read
	char szInPut[20] ="ping 127.0.0.1\n";// �]�m��J���e
	WriteFile(hInputWrite, szInPut, strlen(szInPut), &dwWritten, NULL);
	char buffer[4096] = {0};
	DWORD bytesRead;
	bool blncheck;
	while (true)
	{ 
		Sleep(500);
		blncheck=false;
		buffer[0]='\0';
		blncheck=PeekNamedPipe(hOutputRead,buffer,1024,&bytesRead,0,0);
		if(bytesRead>0)
			blncheck=ReadFile(hOutputRead,buffer,bytesRead,&bytesRead,0);
		else
			break;
		//�p��char *�}�C�j�p�A�H�줸�լ����A�@�Ӻ~�r�e��Ӧ줸��
		int len;
		int charLen = strlen(buffer);
		//�p��h�줸�զr�����j�p�A���r���p��C
		len = MultiByteToWideChar(CP_ACP,0,buffer,charLen,NULL,0);
		//���e�줸�զr���}�C�ӽЪŶ��A�}�C�j�p�����줸�խp�⪺�h�줸�զr���j�p
		TCHAR *buf = new TCHAR[len + 1];
		//�h�줸�սs�X�ഫ���e�줸�սs�X
		MultiByteToWideChar(CP_ACP,0,buffer,charLen,buf,len);
		buf[len] = '\0'; //�K�[�r�굲���A�`�N���Olen+1
		CString pWideChar;
		pWideChar.Append(buf);
		delete [] buf;
		MessageBox(pWideChar);// ��X
		
	}
	CloseHandle(hInputWrite);
	CloseHandle(hOutputRead);
	MessageBox(L"finish...");// ��X	
}
