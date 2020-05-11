
// Monitor_SleepDlg.cpp : ��@��
//

#include "stdafx.h"
#include "Monitor_Sleep.h"
#include "Monitor_SleepDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>//Step 1
#include <string.h>
#include <cstdio>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_SHOWTASK	WM_USER+5//Step 2

// CMonitor_SleepDlg ��ܤ��
int gintY,gintM,gintD;
float gfltT;
bool gblnRun;
////////////////////////////////////////////////
char BASE64CODE[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

void base64en(char *srcStr, char *desStr)
{
    unsigned char srcCode[3];
    unsigned int i,j,len;

    len = strlen(srcStr)/3;
    for (i = 0; i < len; i++)
    {
        srcCode[0] = srcStr[i * 3 + 0];
        srcCode[1] = srcStr[i * 3 + 1];
        srcCode[2] = srcStr[i * 3 + 2];

        desStr[i * 4 + 0] = BASE64CODE[srcCode[0] >> 2];
        desStr[i * 4 + 1] = BASE64CODE[((srcCode[0]&0x03)<<4) + (srcCode[1]>>4)];
        desStr[i * 4 + 2] = BASE64CODE[((srcCode[1]&0x0f)<<2) + (srcCode[2]>>6)];
        desStr[i * 4 + 3] = BASE64CODE[srcCode[2]&0x3f];
    }

    i = len;
    j = strlen(srcStr) - len * 3;
    if (j > 0)
    {
        srcCode[0] = srcStr[i * 3 + 0];
        srcCode[1] = (j > 1) ? srcStr[i * 3 + 1] : '\0';
        srcCode[2] = '\0';

        desStr[i * 4 + 0] = BASE64CODE[srcCode[0] >> 2];
        desStr[i * 4 + 1] = BASE64CODE[((srcCode[0]&0x03)<<4) + (srcCode[1]>>4)];
        desStr[i * 4 + 2] = (srcCode[1] == '\0') ? '=' : BASE64CODE[(srcCode[1]&0x0f)<<2];
        desStr[i * 4 + 3] = '=';

        i++;
    }

    desStr[i * 4] = '\0';
}

int base64_index(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return ch - 'A';
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a' + 26;
    if (ch >= '0' && ch <= '9')
        return ch - '0' + 52;
    if (ch == '+')
        return 62;
    if (ch == '/')
        return 63;
}

void base64de(char *srcStr, char *desStr)
{
    unsigned char srcCode[4];
    unsigned int i, j, len;

    len = strlen(srcStr)/4 - 1;
    for (i = 0; i < len; i++)
    {
        srcCode[0] = base64_index(srcStr[i * 4 + 0]);
        srcCode[1] = base64_index(srcStr[i * 4 + 1]);
        srcCode[2] = base64_index(srcStr[i * 4 + 2]);
        srcCode[3] = base64_index(srcStr[i * 4 + 3]);

        desStr[i * 3 + 0] = (srcCode[0]<<2) + (srcCode[1]>>4);
        desStr[i * 3 + 1] = (srcCode[1]<<4) + (srcCode[2]>>2);
        desStr[i * 3 + 2] = ((srcCode[2]&0x03)<<6) + srcCode[3];
    }

    i = len;

    srcCode[0] = base64_index(srcStr[i * 4 + 0]);
    srcCode[1] = base64_index(srcStr[i * 4 + 1]);

    desStr[i * 3 + 0] = (srcCode[0]<<2) + (srcCode[1]>>4);

    if (srcStr[i * 4 + 2] == '=')
    {
        desStr[i * 3 + 1] = '\0';
    }
    else if (srcStr[i * 4 + 3] == '=')
    {
        srcCode[2] = base64_index(srcStr[i * 4 + 2]);

        desStr[i * 3 + 1] = (srcCode[1]<<4) + (srcCode[2]>>2);
        desStr[i * 3 + 2] = '\0';
    }
    else
    {
        srcCode[2] = base64_index(srcStr[i * 4 + 2]);
        srcCode[3] = base64_index(srcStr[i * 4 + 3]);

        desStr[i * 3 + 1] = (srcCode[1]<<4) + (srcCode[2]>>2);
        desStr[i * 3 + 2] = ((srcCode[2]&0x03)<<6) + srcCode[3];
        desStr[i * 3 + 3] = '\0';
    }
}

CString GetPassword()
{
    char src[1000] = {0};
    char en[1000] = {0},de[1000];
    char chrkey[100];
    int intdatalen,intkeylen;
    int i,j;
    int a=0;
    FILE *pf;
    strcpy_s(chrkey, "jashkey");
	CString StrReturn="OOXXP@$$WORD";//CString StrReturn=L"OOXXP@$$WORD";
	pf='\0';
    fopen_s(&pf,"data.txt","r");
	if(pf!='\0')
	{
		j=0;
		while(fscanf_s(pf,"%d",&a)!=EOF)
		{
			if(a>0)
			{
				 //printf("%d\n",a);
				 en[j]=a;
				 //printf("en=%d\n",en[j]);
				 j++;
			}
		}
		fclose(pf);
		intdatalen=strlen(en);
		intkeylen=strlen(chrkey);
		j=-1;
		for(i=0;i<intdatalen;i++)
		{
			if(j<intkeylen)
			{
				j++;
			}
			else
			{
				j=0;
			}
			en[i]=en[i]^chrkey[j];
		}
		base64de(en, de);
		CString StrBuf(de);
		StrReturn=StrBuf;
	}
	return StrReturn;
}
////////////////////////////////////////////////


CMonitor_SleepDlg::CMonitor_SleepDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMonitor_SleepDlg::IDD, pParent)
	, m_StrSetTime(_T(""))
	, m_StrPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMonitor_SleepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_StrSetTime);
	DDX_Text(pDX, IDC_EDIT2, m_StrPassword);
	DDX_Control(pDX, IDC_BUTTON1, m_b1);
	DDX_Control(pDX, IDC_BUTTON2, m_b2);
}

BEGIN_MESSAGE_MAP(CMonitor_SleepDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMonitor_SleepDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_MESSAGE(WM_SHOWTASK,onShowTask)//Step 5
	ON_BN_CLICKED(IDC_BUTTON2, &CMonitor_SleepDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMonitor_SleepDlg �T���B�z�`��

BOOL CMonitor_SleepDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w
	gblnRun=false;
	m_b1.EnableWindow(!gblnRun);
	m_b2.EnableWindow(gblnRun);

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CMonitor_SleepDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CMonitor_SleepDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMonitor_SleepDlg::OnBnClickedButton1()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	UpdateData(true);
		CString StrBuf="";//CString StrBuf=L"";
		//StrBuf=L"��J���:"+m_StrSetTime+L"\n";
		//StrBuf+=L"��J�K�X:"+ m_StrPassword+L"\n";
		gfltT = _ttof(m_StrSetTime);
		StrBuf=GetPassword();
		CString StrPassword=StrBuf.Mid(0,StrBuf.FindOneOf(","));
		CString StrDate=StrBuf.Mid(StrBuf.FindOneOf(",")+1);
		gintY=_ttoi(StrDate)/10000;
		gintM=(_ttoi(StrDate)%10000)/100;
		gintD=(_ttoi(StrDate)%10000)%100;
		CTime time = CTime::GetCurrentTime();
		int m_nYear = time.GetYear();      ///�~
		int m_nMonth = time.GetMonth();      ///��
		int m_nDay = time.GetDay();      ///��
		if(StrPassword==m_StrPassword && gfltT>0 && (gintY>=m_nYear) && (gintM>=m_nMonth) && (gintD>=m_nDay))
		{
			DeleteFile("data.txt");//DeleteFile(L"data.txt");
			//--
			NOTIFYICONDATA nid;
			nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
			nid.hWnd=this->m_hWnd;
			nid.uID=IDR_MAINFRAME;
			nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
			nid.uCallbackMessage=WM_SHOWTASK;//�۩w�q�������W��
			nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
			lstrcpyn(nid.szTip, _T("����"),sizeof(nid.szTip));
			Shell_NotifyIcon(NIM_ADD,&nid);//�b�U�L�ϲK�[�ϥ�
			ShowWindow(SW_HIDE);//���åD����
			//--
			::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);

			SetTimer(1,gfltT*1000,NULL);
			gblnRun=true;
			m_b1.EnableWindow(!gblnRun);
			m_b2.EnableWindow(gblnRun);

		}
		else
		{
			MessageBox("��J��Ʀ����A�{���Y�N����");//MessageBox(L"��J��Ʀ����A�{���Y�N����");
			AfxGetMainWnd()->SendMessage(WM_CLOSE);
		}

	UpdateData(false);
}


void CMonitor_SleepDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	KillTimer(1);
	gblnRun=false;
	m_b1.EnableWindow(!gblnRun);
	m_b2.EnableWindow(gblnRun);
	CTime time = CTime::GetCurrentTime();
	int m_nYear = time.GetYear();      ///�~
	int m_nMonth = time.GetMonth();      ///��
	int m_nDay = time.GetDay();      ///��
	if((gintY>=m_nYear) && (gintM>=m_nMonth) && (gintD>=m_nDay))
	{
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);
	}
	else
	{
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 1);
		MessageBox("�ϥδ����w�L���A�{���Y�N����");
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
	}

	SetTimer(1,gfltT*1000,NULL);
	gblnRun=true;
	m_b1.EnableWindow(!gblnRun);
	m_b2.EnableWindow(gblnRun);

	CDialogEx::OnTimer(nIDEvent);
}
LRESULT CMonitor_SleepDlg::onShowTask(WPARAM wParam,LPARAM lParam)//Step 6
{
	//wParam�������O�ϥܪ�ID�A��lParam�������O�ƹ����欰
	if(wParam!=IDR_MAINFRAME)
		return 1;
	switch(lParam)
	{
		case WM_RBUTTONUP://�k��_�Ӯɼu�X����\���A�o�إu���@��"����"
		{ 
			LPPOINT lpoint=new tagPOINT;
			::GetCursorPos(lpoint);//�o��ƹ���m
			CMenu menu;
			menu.CreatePopupMenu();//�n���@�Ӽu�X���\���
			//�W�[�\���"����"�A�I���h�o�e����WM_DESTROY���D�����]�w
			//���á^�A�N�{�������C
			menu.AppendMenu(MF_STRING,WM_DESTROY,"����"); //menu.AppendMenu(MF_STRING,WM_DESTROY,L"����"); 
			//�T�w�u�X����檺��m
			menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this);
			//�귽�^��
			HMENU hmenu=menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
		case WM_LBUTTONDBLCLK://�������䪺�B�z
		{
			this->ShowWindow(SW_SHOW);//²�檺��ܥD�������ƨ�
		}
		break;
	}
	return 0;
}


void CMonitor_SleepDlg::OnBnClickedButton2()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	if(gblnRun==true)
	{
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 1);
		KillTimer(1);
		gblnRun=false;
		m_b1.EnableWindow(!gblnRun);
		m_b2.EnableWindow(gblnRun);
	}
}
