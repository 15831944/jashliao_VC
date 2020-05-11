// Get_LenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Get_Len.h"
#include "Get_LenDlg.h"

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
// CGet_LenDlg dialog

CGet_LenDlg::CGet_LenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGet_LenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGet_LenDlg)
	m_v1 = _T("�`�Z�� 3078 m  ");
	m_v2 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGet_LenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGet_LenDlg)
	DDX_Text(pDX, IDC_EDIT1, m_v1);
	DDX_Text(pDX, IDC_EDIT2, m_v2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGet_LenDlg, CDialog)
	//{{AFX_MSG_MAP(CGet_LenDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGet_LenDlg message handlers

BOOL CGet_LenDlg::OnInitDialog()
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

void CGet_LenDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGet_LenDlg::OnPaint() 
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
HCURSOR CGet_LenDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGet_LenDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	char *chrInBuf;//�إ߼Ȧs��J��ƫ���
	char *chrOutBuf;//�إ߼Ȧs��X���θ�ƫ���
	long lngLen=0;//�إߪ��׼Ȧs�ܼ�
	long lngGetLen1=0;//������ƪ���
	long lngGetLen2=0;//�Ѿl��ƪ���
	CString strInData="";//m_strInData����
	CString strRemain="";//�Ѿl���
	CString m_strHead="";
	long lngIndex=0;//����ƺX��
	CString strbuf="";//�إߤ�����Y��ƼȦs��
	char chrSeps[]=" ";//�إߤ��βŸ�
	chrInBuf=new char('\0');//���Ъ�l��
	chrOutBuf=new char('\0');//���Ъ�l��
	UpdateData(true);
	strInData=m_v1;
	chrInBuf=strInData.GetBuffer(0);//�ᤩ���
	chrOutBuf=strtok(chrInBuf,chrSeps);//�^�����Y
	m_strHead=chrOutBuf;//��X�ܦ����ܼ�
	/////////////////////////////////////////
	strInData=m_v1;//���X��Ӹ��
	chrInBuf=strInData.GetBuffer(0);//�ᤩ���
	lngLen=strlen(chrInBuf);
	chrOutBuf=strtok(chrInBuf,chrSeps);//�^�����Y
	lngGetLen1=strlen(chrOutBuf);//������ƪ���
	lngGetLen2=lngLen-lngGetLen1;//�Ѿl��ƪ���
	strRemain=m_v1.Mid(lngGetLen1+1,lngGetLen2);//�Ѿl���
	//////////////////////////////////////////////////////
	lngIndex++;
	strInData=strRemain;//���X��Ӹ��
	chrInBuf=strInData.GetBuffer(0);//�ᤩ���
	lngLen=strlen(chrInBuf);
	chrOutBuf=strtok(chrInBuf,chrSeps);//�^��
	m_v2=atoi(chrOutBuf);
	lngGetLen1=strlen(chrOutBuf);//������ƪ���
	lngGetLen2=lngLen-lngGetLen1;//�Ѿl��ƪ���
	if(lngGetLen2!=0)
	{
		strRemain=strRemain.Mid(lngGetLen1+1,lngGetLen2);//�Ѿl���
	}
	UpdateData(false);

}
