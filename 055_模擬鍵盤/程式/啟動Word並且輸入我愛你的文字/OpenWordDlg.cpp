// OpenWordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenWord.h"
#include "OpenWordDlg.h"
#include "Winuser.h"
#include "Windows.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// COpenWordDlg dialog

COpenWordDlg::COpenWordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenWordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenWordDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenWordDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COpenWordDlg, CDialog)
	//{{AFX_MSG_MAP(COpenWordDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenWordDlg message handlers

BOOL COpenWordDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COpenWordDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COpenWordDlg::OnPaint() 
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
HCURSOR COpenWordDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void COpenWordDlg::OnButton1() 
{
	ShellExecute(NULL,"open","C:\\Program Files\\Microsoft Office\\Office\\Winword.exe",NULL,NULL,SW_SHOWNORMAL); 
	Sleep(1000);
	CWnd* hWnd = FindWindow(NULL, "文件1 - Microsoft Word");
	//hWnd->SetActiveWindow();
	INPUT input[2];
	ShowWindow(SW_MINIMIZE);//重點把自己縮小如此才可以使焦點轉移
    ::ZeroMemory(input, sizeof(input));
    input[0].type = INPUT_KEYBOARD; 
    input[1].type = INPUT_KEYBOARD; 

    input[0].ki.wVk = 'I';
    input[1].ki.wVk = 'I';

    input[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, input, sizeof(INPUT));
    input[0].ki.wVk = ' ';
    input[1].ki.wVk = ' ';
	Sleep(1000);
	SendInput(2, input, sizeof(INPUT));
	input[0].ki.wVk = 'L';
    input[1].ki.wVk = 'L';
	SendInput(2, input, sizeof(INPUT));
	input[0].ki.wVk = 'O';
    input[1].ki.wVk = 'O';
	SendInput(2, input, sizeof(INPUT));
	input[0].ki.wVk = 'V';
    input[1].ki.wVk = 'V';
	SendInput(2, input, sizeof(INPUT));
	input[0].ki.wVk = 'E';
    input[1].ki.wVk = 'E';
	SendInput(2, input, sizeof(INPUT));
    input[0].ki.wVk = ' ';
    input[1].ki.wVk = ' ';
	SendInput(2, input, sizeof(INPUT));
	Sleep(1000);
	input[0].ki.wVk = 'Y';
    input[1].ki.wVk = 'Y';
	SendInput(2, input, sizeof(INPUT));
	input[0].ki.wVk = 'O';
    input[1].ki.wVk = 'O';
	SendInput(2, input, sizeof(INPUT));
	input[0].ki.wVk = 'U';
    input[1].ki.wVk = 'U';
	SendInput(2, input, sizeof(INPUT));
	hWnd->SetActiveWindow();	
}
