// STBMMSConnectDlg.cpp : ��@��
//

#include "stdafx.h"
#include "STBMMSConnect.h"
#include "STBMMSConnectDlg.h"
#include <Iprtrmib.h>
#include <Iphlpapi.h>
#include <IOSTREAM>
#include <fstream>
#include "NetUsebat.h"
using namespace std;
#define ARP_TABLE_SIZE   1
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


// CSTBMMSConnectDlg ��ܤ��




CSTBMMSConnectDlg::CSTBMMSConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSTBMMSConnectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSTBMMSConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ARPLIST, ARPListBox);
	DDX_Control(pDX, IDC_STBLIST, STBListBox);
	DDX_Control(pDX, IDC_MSGLIST, MSGListBox);
}

BEGIN_MESSAGE_MAP(CSTBMMSConnectDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTRun, &CSTBMMSConnectDlg::OnBnClickedButtrun)
END_MESSAGE_MAP()


// CSTBMMSConnectDlg �T���B�z�`��

BOOL CSTBMMSConnectDlg::OnInitDialog()
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
	m_ArrayARPIP.RemoveAll();//CArray Step_03
	m_ArrayCheckIP.RemoveAll();//CArray Step_03
	m_ArrayMessageIP.RemoveAll();//CArray Step_03
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CSTBMMSConnectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSTBMMSConnectDlg::OnPaint()
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
HCURSOR CSTBMMSConnectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSTBMMSConnectDlg::OnBnClickedButtrun()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	InitVariable();
	//**
	GetARPTable();
	//**
	ShowARPIP();
	//**
	GetIPList();
	//**
	ShowCheckIP();
	//**
	CompareIP();
	//**
	ShowMSGIP();
	//**
	SendMSG();
}
void CSTBMMSConnectDlg::InitVariable()
{
	/*
	CString StrBuf;
	StrBuf=_T("test0");
	ARPListBox.AddString(StrBuf);
	StrBuf=_T("test1");
	ARPListBox.AddString(StrBuf);
	//*/
	m_ArrayARPIP.RemoveAll();//CArray Step_03
	m_ArrayCheckIP.RemoveAll();//CArray Step_03
	m_ArrayMessageIP.RemoveAll();//CArray Step_03

	//**
	int i,j;
	j=ARPListBox.GetCount();
	for(i=0;i<j;i++)
		ARPListBox.DeleteString(0);
	
	j=STBListBox.GetCount();
	for(i=0;i<j;i++)
		STBListBox.DeleteString(0);
	j=MSGListBox.GetCount();
	for(i=0;i<j;i++)
		MSGListBox.DeleteString(0);
}
void CSTBMMSConnectDlg::ShowARPIP()
{
	int i,j;
	CString StrBuf;
	j=m_ArrayARPIP.GetSize();
	for(i=0;i<j;i++)
	{
		StrBuf=m_ArrayARPIP.GetAt(i);
		ARPListBox.AddString(StrBuf);
	}
}
void CSTBMMSConnectDlg::GetARPTable()
{
	CString StrCallWebServiceExeName;
	StrCallWebServiceExeName="MMSConnectIP.exe";
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_MINIMIZE;
	si.dwFlags=STARTF_USESHOWWINDOW;
	BOOL fRet=CreateProcess(NULL,
							StrCallWebServiceExeName.GetBuffer(0),
							NULL,
							NULL,
							FALSE,
							NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
							NULL,
							NULL,
							&si,
							&pi);
	if(fRet)
	{
		WaitForSingleObject(pi.hProcess,INFINITE);
		CString StrIPBuf;
		fstream a;
		char data[500];
		a.open("MMSIP.txt",ios::in);
		if(a.is_open())
		{
			while(!a.eof())
			{
				a.getline(data,500);
				StrIPBuf.Format(_T("%s"),data);
				m_ArrayARPIP.Add(StrIPBuf);
			}
		}
	}
}
void CSTBMMSConnectDlg::GetIPList()
{
	CString StrIPBuf;
	fstream a;
	char data[500];
	a.open("IPList.txt",ios::in);
	if(a.is_open())
	{
		while(!a.eof())
		{
			a.getline(data,500);
			StrIPBuf.Format(_T("%s"),data);
			m_ArrayCheckIP.Add(StrIPBuf);
		}
	}
}
void CSTBMMSConnectDlg::ShowCheckIP()
{
	int i,j;
	CString StrBuf;
	j=m_ArrayCheckIP.GetSize();
	for(i=0;i<j;i++)
	{
		StrBuf=m_ArrayCheckIP.GetAt(i);
		STBListBox.AddString(StrBuf);
	}
}
void CSTBMMSConnectDlg::CompareIP()
{
	int i,j;
	int k,l;
	bool blnfind=false;
	CString StrCheckBuf,StrARPBuf;
	j=m_ArrayCheckIP.GetSize();
	l=m_ArrayARPIP.GetSize();
	for(i=0;i<j;i++)
	{
		blnfind=false;
		StrCheckBuf=m_ArrayCheckIP.GetAt(i);
		StrARPBuf=_T("No Data");
		for(k=0;k<l;k++)
		{
			StrARPBuf=m_ArrayARPIP.GetAt(k);
			if(StrCheckBuf==StrARPBuf)
			{
				blnfind=true;
				break;
			}
		}
		if(!blnfind)
		{
			m_ArrayMessageIP.Add(StrCheckBuf);
		}
	}
	
}
void CSTBMMSConnectDlg::ShowMSGIP()
{
	int i,j;
	CString StrBuf;
	j=m_ArrayMessageIP.GetSize();
	for(i=0;i<j;i++)
	{
		StrBuf=m_ArrayMessageIP.GetAt(i);
		MSGListBox.AddString(StrBuf);
	}
}
void CSTBMMSConnectDlg::SendMSG()
{
	CString StrIP;
	CString StrSourceFileName;
	CString StrNewFileName;
	CString StrBuf;
	CString StrNetPath;
	int i,j;
	j=m_ArrayMessageIP.GetSize();
	for(i=0;i<j;i++)
	{
		StrIP=m_ArrayMessageIP.GetAt(i);
		StrNetPath="\\\\";
		StrNetPath+=StrIP;
		StrNetPath+="\\D$\\NabroClient\\Message\\";
		StrBuf.Format("�ثe���A :�s�uIP=%s��STB...",StrIP.GetBuffer(0));
		this->SetWindowText(StrBuf);
		if(ConnectSTB(StrIP))
		{
			StrBuf.Format(_T("�ثe���A :�ǰeMSG��IP=%s�]�w�� ..."),StrIP.GetBuffer(0));
			this->SetWindowText(StrBuf);
			//this->GetDlgItemText(IDC_EDITTime,StrSourceFileName);
			StrSourceFileName=_T("mmsconnect.msg");
			StrNewFileName=StrSourceFileName;
			StrNewFileName=StrNetPath+StrNewFileName;
			if(CopyFile(StrSourceFileName.GetBuffer(0),StrNewFileName.GetBuffer(0),false))
			{
				StrBuf.Format(_T("�ثe���A :�ǰeMSG��IP=%s�]�w���� ..."),StrIP.GetBuffer(0));
				this->SetWindowText(StrBuf);
			}
		}
		else
		{
			StrBuf.Format(_T("�ثe���A :�s�uIP=%s��STB����"),StrIP.GetBuffer(0));
			this->SetWindowText(StrBuf);
			FILE *pf;
			pf=fopen("connect_error.txt","a");
			fprintf(pf,"%s\n",StrIP.GetBuffer(0));
			fclose(pf);
		}
	}
	MessageBox("OK");
}
bool CSTBMMSConnectDlg::ConnectSTB(CString StrIP)
{
	CNetUsebat NUB;
	CString StrNetPath;
	StrNetPath="\\\\";
	StrNetPath+=StrIP;
	StrNetPath+="\\D$\\NabroClient";
	NUB.Createbat("nabro","nabro",StrNetPath,0);
	if(NUB.CreateShareDir())
	{
		/*
		////////////////////////////////
		//test
		MessageBox(StrIP);
		///////////////////////////////
		*/
		return true;
	}
	return false;
}