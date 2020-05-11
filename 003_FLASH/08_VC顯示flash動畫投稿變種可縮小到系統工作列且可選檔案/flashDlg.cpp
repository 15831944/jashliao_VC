// flashDlg.cpp : implementation file
//

#include "stdafx.h"
#include "flash.h"
#include "flashDlg.h"
#include <mmsystem.h>//Step 1
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define WM_SHOWTASK	WM_USER+5//Step 2
bool blnCheckHide=false;
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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlashDlg dialog

CFlashDlg::CFlashDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlashDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlashDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFlashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlashDlg)
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH2, m_FlashPlayer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFlashDlg, CDialog)
	//{{AFX_MSG_MAP(CFlashDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_SHOWTASK,onShowTask)//Step 5
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlashDlg message handlers

BOOL CFlashDlg::OnInitDialog()
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
	///* //�z���{���X
	SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,
		GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	HINSTANCE hInst = LoadLibrary("User32.DLL"); 
	if(hInst) 
	{ 
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
		MYFUNC fun = NULL;
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if(fun)fun(this->GetSafeHwnd(),0,200,2); 
		FreeLibrary(hInst); 
	}
	//*/
	RECT rc;
	this->GetClientRect(&rc);
	rc.bottom-=2;
	rc.left-=2;
	rc.right-=2;
	rc.top-=-2; 
	m_FlashPlayer.MoveWindow( &rc, true );
	/*
	TCHAR strCurDrt[500];
	int nLen = ::GetCurrentDirectory(500,strCurDrt);
	if( strCurDrt[nLen]!='\\' )
	{
		strCurDrt[nLen++] = '\\';
		strCurDrt[nLen] = '\0';
	}

	CString strFileName = strCurDrt;
	strFileName += "startup.swf";
	*/
	CString strFileName;
	CFileDialog fdlg(true,NULL,"openfile",NULL,"FLASH��|*.swf");
	if(fdlg.DoModal()==IDOK)
	{
		strFileName=fdlg.GetPathName();
	}
	m_FlashPlayer.LoadMovie(0, strFileName);
	m_FlashPlayer.Play();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFlashDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFlashDlg::OnPaint() 
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
HCURSOR CFlashDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFlashDlg::OnOK() 
{
	// TODO: Add extra validation here
	//CDialog::OnOK();
	if(blnCheckHide==false)
	{
		NOTIFYICONDATA nid;
		nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
		nid.hWnd=this->m_hWnd;
		nid.uID=IDR_MAINFRAME;
		nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
		nid.uCallbackMessage=WM_SHOWTASK;//�۩w�q�������W��
		nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
		strcpy(nid.szTip,"�p�e���ȴ���");//��T���ܱ���"�p�e���ȴ���"
		Shell_NotifyIcon(NIM_ADD,&nid);//�b�U�L�ϲK�[�ϥ�
		blnCheckHide=true;
	}
	ShowWindow(SW_HIDE);//���åD����
}

void CFlashDlg::OnClose() 
{
	if(blnCheckHide==false)
	{
		NOTIFYICONDATA nid;
		nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
		nid.hWnd=this->m_hWnd;
		nid.uID=IDR_MAINFRAME;
		nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
		nid.uCallbackMessage=WM_SHOWTASK;//�۩w�q�������W��
		nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
		strcpy(nid.szTip,"�p�e���ȴ���");//��T���ܱ���"�p�e���ȴ���"
		Shell_NotifyIcon(NIM_ADD,&nid);//�b�U�L�ϲK�[�ϥ�
		blnCheckHide=true;
	}
	ShowWindow(SW_HIDE);//���åD����
}
LRESULT CFlashDlg::onShowTask(WPARAM wParam,LPARAM lParam)//Step 6
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
		}
		break;
	}
	return 0;
}

void CFlashDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	MessageBox("error");
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFlashDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
    MessageBox("error");
}

BOOL CFlashDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DestroyWindow();
}
