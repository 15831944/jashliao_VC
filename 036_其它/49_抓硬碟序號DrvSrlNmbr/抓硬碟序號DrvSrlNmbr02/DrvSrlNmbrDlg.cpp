// DrvSrlNmbrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DrvSrlNmbr.h"
#include "DrvSrlNmbrDlg.h"

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
// CDrvSrlNmbrDlg dialog

CDrvSrlNmbrDlg::CDrvSrlNmbrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrvSrlNmbrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDrvSrlNmbrDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrvSrlNmbrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrvSrlNmbrDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrvSrlNmbrDlg, CDialog)
	//{{AFX_MSG_MAP(CDrvSrlNmbrDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GETSRLNUM, OnGetSrlNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrvSrlNmbrDlg message handlers

BOOL CDrvSrlNmbrDlg::OnInitDialog()
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

	//�г�����������
	FindAllDrivers();
	CComboBox* Driver=(CComboBox*)GetDlgItem(IDC_DRIVER);
	Driver->SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDrvSrlNmbrDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDrvSrlNmbrDlg::OnPaint() 
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
HCURSOR CDrvSrlNmbrDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDrvSrlNmbrDlg::OnGetSrlNum() 
{
	//�������������������
	UpdateData(TRUE);

	//����������ָ�����
	CComboBox* Driver=(CComboBox*)GetDlgItem(IDC_DRIVER);

	//��õ�ǰѡ���������
	CString strRootPathName;
	Driver->GetWindowText(strRootPathName);

	//������������к�
	LPCTSTR lpRootPathName = strRootPathName;
	LPTSTR lpVolumeNameBuffer=new char[12];
	DWORD nVolumeNameSize=12;
	DWORD VolumeSerialNumber;
	DWORD MaximumComponentLength;
	DWORD FileSystemFlags;
	LPTSTR lpFileSystemNameBuffer=new char[10];
	DWORD nFileSystemNameSize=10;
	GetVolumeInformation(lpRootPathName,
				lpVolumeNameBuffer, nVolumeNameSize,
				&VolumeSerialNumber, 
				&MaximumComponentLength,
				&FileSystemFlags,
				lpFileSystemNameBuffer, nFileSystemNameSize);

	//��ʾ���������к�
	CString str;
	str.Format("�X�ʾ�%s���Ǹ���%x",strRootPathName,VolumeSerialNumber);
	AfxMessageBox(str);
	DWORD data;
	data=VolumeSerialNumber^663233909;//27882575
	str="";
	str.Format("�X�ʾ�%s���Ǹ���XOR��%x",strRootPathName,data);
	AfxMessageBox(str);
	FILE *pf;
	pf=fopen("Key_value.dat","w");
	str="";
	str.Format("<key>%x</key>",data);
	fprintf(pf,"%s",str.GetBuffer(0)); 
	fclose(pf);

	
}

void CDrvSrlNmbrDlg::FindAllDrivers()
{
	CComboBox* Driver=(CComboBox*)GetDlgItem(IDC_DRIVER);
	DWORD dwNumBytesForDriveStrings;//ʵ�ʴ洢�������ŵ��ַ�������
	HANDLE hHeap;
	LPSTR lp;
	CString strLogdrive;

	//���ʵ�ʴ洢�������ŵ��ַ�������
	dwNumBytesForDriveStrings=GetLogicalDriveStrings(0,NULL)*sizeof(TCHAR);

	//����ַ�����Ϊ�գ����ʾ������������������
	if (dwNumBytesForDriveStrings!=0) {
		//�����ַ����ռ�
		hHeap=GetProcessHeap();
		lp=(LPSTR)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,
			dwNumBytesForDriveStrings);

		//��ñ����������������ַ���
		GetLogicalDriveStrings(HeapSize(hHeap,0,lp),lp);

		//��������һ�����ŵ���������
		while (*lp!=0) {
			Driver->AddString(lp);
			lp=_tcschr(lp,0)+1;
		}
	}
	else 
		AfxMessageBox("Can't Use The Function GetLogicalDriveStrings!");
}

 
