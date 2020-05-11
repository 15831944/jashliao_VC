// MountNetDrvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MountNetDrv.h"
#include "MountNetDrvDlg.h"

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
// CMountNetDrvDlg dialog

CMountNetDrvDlg::CMountNetDrvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMountNetDrvDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMountNetDrvDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMountNetDrvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMountNetDrvDlg)
	DDX_Control(pDX, IDC_EDIT_NETPATH, m_NetpathEdit);
	DDX_Control(pDX, IDC_EDIT_DRIVE, m_DriveEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMountNetDrvDlg, CDialog)
	//{{AFX_MSG_MAP(CMountNetDrvDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MOUNT, OnButtonMount)
	ON_BN_CLICKED(IDC_BUTTON_UNMOUNT, OnButtonUnmount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMountNetDrvDlg message handlers

BOOL CMountNetDrvDlg::OnInitDialog()
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

void CMountNetDrvDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMountNetDrvDlg::OnPaint() 
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
HCURSOR CMountNetDrvDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMountNetDrvDlg::OnButtonMount() 
{
	// TODO: Add your control notificationhandler code here
	char netpath[MAX_PATH]; //���������·��
	m_NetpathEdit.GetWindowText(netpath, sizeof(netpath));
	char drv[MAX_PATH]; //���ص��������̷�
	m_DriveEdit.GetWindowText(drv, sizeof(drv));
	NETRESOURCE netres;
	netres.dwScope=RESOURCE_GLOBALNET;
	netres.dwType=RESOURCETYPE_ANY;
	netres.dwDisplayType=RESOURCEDISPLAYTYPE_GENERIC;
	netres.dwUsage=RESOURCEUSAGE_CONNECTABLE;
	netres.lpLocalName=drv;
	netres.lpRemoteName=netpath;
	netres.lpComment=NULL;
	netres.lpProvider=NULL;
	DWORD rslt=WNetAddConnection2(&netres,"jashliao","jashliao",0);
	//DWORD rslt=WNetAddConnection2(&netres,NULL,NULL,0);
	CString str;
	str.Format("WNetAddConnection2() return code=%d", rslt);
	MessageBox(str);
}
	
void CMountNetDrvDlg::OnButtonUnmount() 
{
	// TODO: Add your control notification handlercode here
	char drv[MAX_PATH]; //���ص��������̷�
	m_DriveEdit.GetWindowText(drv, sizeof(drv));
	DWORD rslt=WNetCancelConnection2(drv, 0, FALSE);
	CString str;
	str.Format("WNetCancelConnection2() return code=%d",
		rslt);
	MessageBox(str);
	//��ʾ��Ϣ�ɹ���� return code =0 �ɹ� ���� ����ʧ��
}
