// PortMonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PortMonitor.h"
#include "PortMonitorDlg.h"
#include "vfw.h"
#include <mmsystem.h>//Step 1
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define WM_SHOWTASK	WM_USER+5//Step 2
int checkData[15];
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPortMonitorDlg dialog

CPortMonitorDlg::CPortMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPortMonitorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPortMonitorDlg)
	m_V01 = FALSE;
	m_V02 = FALSE;
	m_V03 = FALSE;
	m_V04 = FALSE;
	m_V05 = FALSE;
	m_V06 = FALSE;
	m_V07 = FALSE;
	m_V08 = FALSE;
	m_V09 = FALSE;
	m_V10 = FALSE;
	m_V11 = FALSE;
	m_V12 = FALSE;
	m_V13 = FALSE;
	m_V14 = FALSE;
	m_V15 = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPortMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPortMonitorDlg)
	DDX_Check(pDX, IDC_CH01, m_V01);
	DDX_Check(pDX, IDC_CH02, m_V02);
	DDX_Check(pDX, IDC_CH03, m_V03);
	DDX_Check(pDX, IDC_CH04, m_V04);
	DDX_Check(pDX, IDC_CH05, m_V05);
	DDX_Check(pDX, IDC_CH06, m_V06);
	DDX_Check(pDX, IDC_CH07, m_V07);
	DDX_Check(pDX, IDC_CH08, m_V08);
	DDX_Check(pDX, IDC_CH09, m_V09);
	DDX_Check(pDX, IDC_CH10, m_V10);
	DDX_Check(pDX, IDC_CH11, m_V11);
	DDX_Check(pDX, IDC_CH12, m_V12);
	DDX_Check(pDX, IDC_CH13, m_V13);
	DDX_Check(pDX, IDC_CH14, m_V14);
	DDX_Check(pDX, IDC_CH15, m_V15);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPortMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CPortMonitorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SHOWTASK,onShowTask)//Step 5
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPortMonitorDlg message handlers

BOOL CPortMonitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Video=NULL;
	blnmp3=true;
	////////////////////////////////////////////
	TCHAR strCurDrt[500];
	int nLen = ::GetCurrentDirectory(500,strCurDrt);//���o�ثe�{�����|
	if( strCurDrt[nLen]!='\\' )
	{
		strCurDrt[nLen++] = '\\';
		strCurDrt[nLen] = '\0';
	}
	m_Path=strCurDrt;
	m_Path=m_Path+"5TV.mp3";
	//////////////////////////////////////////
	//Step 3 
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDR_MAINFRAME;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage=WM_SHOWTASK;//�۩w�q�������W��
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(nid.szTip,"PortMonitor by Jash");//��T���ܱ���"�p�e���ȴ���"
	Shell_NotifyIcon(NIM_ADD,&nid);//�b�U�L�ϲK�[�ϥ�
	ShowWindow(SW_HIDE);//���åD����
	///////////////////////////////////////////
	m_intCheck=-1;
	SetTimer(1,100,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPortMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPortMonitorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPortMonitorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
LRESULT CPortMonitorDlg::onShowTask(WPARAM wParam,LPARAM lParam)//Step 6
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
			menu.AppendMenu(MF_STRING,WM_DESTROY,"����"); 
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
			SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			Invalidate();
		}
		break;
	}
	return 0;
}

void CPortMonitorDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDR_MAINFRAME;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage=WM_SHOWTASK;//�۩w�q�������W��
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(nid.szTip,"PortMonitor by Jash");//��T���ܱ���"�p�e���ȴ���"
	Shell_NotifyIcon(NIM_ADD,&nid);//�b�U�L�ϲK�[�ϥ�
	ShowWindow(SW_HIDE);//���åD����
}

void CPortMonitorDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	int i;
	int intsum=0;
	for(i=0;i<15;i++)
		checkData[i]=0;
	if(m_intCheck==-1)
	{
		NOTIFYICONDATA nid;
		nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
		nid.hWnd=this->m_hWnd;
		nid.uID=IDR_MAINFRAME;
		nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
		nid.uCallbackMessage=WM_SHOWTASK;//�۩w�q�������W��
		nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
		strcpy(nid.szTip,"PortMonitor by Jash");//��T���ܱ���"�p�e���ȴ���"
		Shell_NotifyIcon(NIM_ADD,&nid);//�b�U�L�ϲK�[�ϥ�
		ShowWindow(SW_HIDE);//���åD����
		m_intCheck=0;
	}
	if(m_intCheck==0 || m_intCheck==1)
	{
		KillTimer(1);
		int intport=1101;
		for(i=0;i<15;i++)
		{
			CSocket *pSocket;
			pSocket=new CSocket();
			pSocket->Create();
			if(!pSocket->Connect("118.163.217.187",intport))
			{
				delete pSocket;
				pSocket=NULL;
				checkData[i]=1;//�L�k�s��
			}
			else
			{
				pSocket->Close();
				delete pSocket;
				pSocket=NULL;
				checkData[i]=0;//�i�H�s��
			}
			intsum=intsum+checkData[i];
			intport++;
		}
		UpdateData(true);
			m_V01 = checkData[0];
			m_V02 = checkData[1];
			m_V03 = checkData[2];
			m_V04 = checkData[3];
			m_V05 = checkData[4];
			m_V06 = checkData[5];
			m_V07 = checkData[6];
			m_V08 = checkData[7];
			m_V09 = checkData[8];
			m_V10 = checkData[9];
			m_V11 = checkData[10];
			m_V12 = checkData[11];
			m_V13 = checkData[12];
			m_V14 = checkData[13];
			m_V15 = checkData[14];
		UpdateData(false);
		if(intsum==0)
		{
			NOTIFYICONDATA nid;
			nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
			nid.hWnd=this->m_hWnd;
			nid.uID=IDR_MAINFRAME;
			nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
			nid.uCallbackMessage=WM_SHOWTASK;//�۩w�q�������W��
			nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
			strcpy(nid.szTip,"PortMonitor by Jash");//��T���ܱ���"�p�e���ȴ���"
			Shell_NotifyIcon(NIM_ADD,&nid);//�b�U�L�ϲK�[�ϥ�
			ShowWindow(SW_HIDE);//���åD����
			m_intCheck=0;
			/////////////////////////
			MCIWndStop(m_Video);
			if(m_Video !=NULL)
			{
				MCIWndDestroy(m_Video);
			}
			m_Video = NULL;
			blnmp3=true;
			/////////////////////////
		}
		else
		{
			m_intCheck=1;
			intsum=0;
			this->ShowWindow(SW_SHOW);//²�檺��ܥD�������ƨ�
			SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			Invalidate();
			/////////////////////
			if(m_Video !=NULL)
			{
				MCIWndStop(m_Video);
				MCIWndDestroy(m_Video);
			}
			m_Video = NULL;
			if(blnmp3)//�u�o�X�@��ĵ�i��
			{
				if(m_Video == NULL)
				{
					m_Video = MCIWndCreate(this->GetSafeHwnd(),
					AfxGetInstanceHandle(),
					WS_CHILD | WS_VISIBLE|MCIWNDF_NOMENU,m_Path);
		
				}
				else
				{
					MCIWndHome(m_Video);
				}
				MCIWndPlay(m_Video);
				blnmp3=false;
			}
			/////////////////////
		}
		SetTimer(1,10000,NULL);
	}
	CDialog::OnTimer(nIDEvent);
}

HBRUSH CPortMonitorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	switch (pWnd->GetDlgCtrlID())
	{
		case IDC_CH01:
			if(checkData[0])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH02:
			if(checkData[1])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH03:
			if(checkData[2])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH04:
			if(checkData[3])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH05:
			if(checkData[4])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH06:
			if(checkData[5])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH07:
			if(checkData[6])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH08:
			if(checkData[7])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH09:
			if(checkData[8])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH10:
			if(checkData[9])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH11:
			if(checkData[10])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH12:
			if(checkData[11])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH13:
			if(checkData[12])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH14:
			if(checkData[13])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
		case IDC_CH15:
			if(checkData[14])
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
			}
			else
			{
				pDC->SetBkColor(RGB(155,255,205));
				pDC->SetTextColor(RGB(0,0,0));
			}
			break;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
