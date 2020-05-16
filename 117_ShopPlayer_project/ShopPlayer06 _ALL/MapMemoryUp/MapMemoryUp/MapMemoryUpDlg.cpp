// MapMemoryUpDlg.cpp : ��@��
//

#include "stdafx.h"
#include "MapMemoryUp.h"
#include "MapMemoryUpDlg.h"
#include <winbase.h>//MAP memory_step 01
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////
//MAP memory_step 02
#define	MAP_Data	"data info"
#define	MAP_LENGTH	1024
HANDLE hDataMap = NULL ;
static char szOldData[MAP_LENGTH] = "" ;
//////////////////////////////////////
HANDLE m_hPro;//CreateProcess step01, step 00�PMAP memory_step01
int inttimercount;
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


// CMapMemoryUpDlg ��ܤ��




CMapMemoryUpDlg::CMapMemoryUpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapMemoryUpDlg::IDD, pParent)
	, m_V1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMapMemoryUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_V1);
}

BEGIN_MESSAGE_MAP(CMapMemoryUpDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMapMemoryUpDlg �T���B�z�`��

BOOL CMapMemoryUpDlg::OnInitDialog()
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
	hDataMap = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH,	TEXT(MAP_Data) ) ;//MAP memory_step 03
	LPVOID mapView = MapViewOfFile( hDataMap,FILE_MAP_WRITE, 0, 0, 0 ) ;//MAP memory_step 04
	////////////////////////////////////////////////////////////////////////////////////////
	//MAP memory_step 05
	inttimercount=2;
	CString theString( "d:\\22.wmv,0" ); 
	LPTSTR lpsz = new TCHAR[theString.GetLength()+1]; 
	_tcscpy(lpsz, theString);
	_tcscpy((LPTSTR)mapView,lpsz);
	UnmapViewOfFile( (LPVOID)mapView);
	delete []lpsz;
	////////////////////////////////////////////////////////////////////////////////////////
	SetTimer(1,1000,NULL);
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CMapMemoryUpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMapMemoryUpDlg::OnPaint()
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
HCURSOR CMapMemoryUpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMapMemoryUpDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString StrData;
	CString theString;
	LPVOID mapView = MapViewOfFile( hDataMap,FILE_MAP_WRITE, 0, 0, 0 ) ;
	if(!m_hPro)//�P�_�O�_�i�H�������{��
	{
		CallPlayer();
	}
	UpdateData(true);
	if( mapView != NULL ) 
	{
		StrData=(LPTSTR)mapView;
		if(StrData=="")
		{
			if(inttimercount==2)
			{
				inttimercount=1;
				theString=_T("d:\\11.wmv,0");
			}
			else
			{
				inttimercount=2;
				theString=_T("d:\\22.wmv,0");
			}
			m_V1=theString;
			UpdateData(false);
			LPTSTR lpsz = new TCHAR[theString.GetLength()+1]; 
			_tcscpy(lpsz, theString);
			_tcscpy((LPTSTR)mapView,lpsz);
			UnmapViewOfFile( (LPVOID)mapView);
			delete []lpsz;
		}
	}	

	CDialog::OnTimer(nIDEvent);
}
void CMapMemoryUpDlg::CallPlayer()//CreateProcess step03
{
	///*
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	//�ܼƪ�l��
	ZeroMemory( &si, sizeof(si) );//memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags |= STARTF_USESHOWWINDOW;
	wchar_t  szExeFile[] = L"C:\\Shop\\ShopPlayer.exe";
	//���}�{��
	BOOL fRet=CreateProcess(szExeFile,
							NULL,
							NULL,
							NULL,
							FALSE,
							NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
							NULL,
							NULL,
							&si,
							&pi);

	if(!fRet)
	{//�}�ҥ��ѡA��ܿ��~�T��
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
						FORMAT_MESSAGE_FROM_SYSTEM | 
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						GetLastError(),
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
						(LPTSTR) &lpMsgBuf,
						0,
						NULL );
		AfxMessageBox( (LPCTSTR)lpMsgBuf);
		LocalFree( lpMsgBuf );

	}
	else
	{
		m_hPro=pi.hProcess;
		AfxMessageBox(_T("CreateProcess���\"));
	}
	//*/
}
void CMapMemoryUpDlg::OnDestroy()//CreateProcess step04
{
	CDialog::OnDestroy();
	// TODO: Add your control notification handler code here
	if(m_hPro)//�P�_�O�_�i�H�������{��
	{
		
		if(!TerminateProcess(m_hPro,0))//���������{��
		{
			//����������~�T��
			LPVOID lpMsgBuf;
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
						FORMAT_MESSAGE_FROM_SYSTEM | 
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						GetLastError(),
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
						(LPTSTR) &lpMsgBuf,
						0,
						NULL );
			AfxMessageBox( (LPCTSTR)lpMsgBuf);
			LocalFree( lpMsgBuf );
		}
		else
		{
			AfxMessageBox(_T("TerminateProcess���\"));
		}
		m_hPro=NULL;
	}
	else
	{
		AfxMessageBox(_T("�{�����s�b"));
	}
}
