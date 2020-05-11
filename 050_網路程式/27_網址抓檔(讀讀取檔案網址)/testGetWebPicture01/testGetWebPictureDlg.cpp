// testGetWebPictureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testGetWebPicture.h"
#include "testGetWebPictureDlg.h"
#include<fstream.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
char *chrdata;
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
// CTestGetWebPictureDlg dialog

CTestGetWebPictureDlg::CTestGetWebPictureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestGetWebPictureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestGetWebPictureDlg)
	m_V1 = _T("");
	m_V2 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestGetWebPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestGetWebPictureDlg)
	DDX_Text(pDX, IDC_EDIT1, m_V1);
	DDX_Text(pDX, IDC_EDIT2, m_V2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestGetWebPictureDlg, CDialog)
	//{{AFX_MSG_MAP(CTestGetWebPictureDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestGetWebPictureDlg message handlers

BOOL CTestGetWebPictureDlg::OnInitDialog()
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

void CTestGetWebPictureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestGetWebPictureDlg::OnPaint() 
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
HCURSOR CTestGetWebPictureDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestGetWebPictureDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	fstream a;
	char data[100];
	a.open("123.txt",ios::in);
	while(!a.eof())
	{
		a>>data;
		UpdateData(true);
			m_V1=data;
			m_V2=m_V1.Mid(m_V1.GetLength()-26);  
			GetSourceHtml(m_V1,m_V2);
		UpdateData(false);
	}	
	MessageBox("OK");
	
}

BOOL CTestGetWebPictureDlg::GetSourceHtml(CString theUrl,CString Filename) 
{
 CInternetSession session;
 CInternetFile* file = NULL;
 try
 {
    // ???接到指定URL
    file = (CInternetFile*) session.OpenURL(theUrl); 
 }
 catch (CInternetException* m_pException)
 {
    // 如果有??的?，置文件?空
    file = NULL; 
    m_pException->Delete();
    return FALSE;
 }

 // 用dataStore?保存?取的网?文件
 CStdioFile dataStore;
 if (file)
 {
    CString  somecode;	//也可采用LPTSTR?型，?不??除文本中的\n回?符
    BOOL bIsOk = dataStore.Open(Filename,
		CFile::modeCreate 
		| CFile::modeWrite 
		| CFile::shareDenyWrite 
		| CFile::typeBinary);
	
    if (!bIsOk)
	return FALSE;
	DWORD dwordValue;
	dwordValue=file->GetLength();
	chrdata=new char[dwordValue];
	file->Read(chrdata,dwordValue); 
	dataStore.Write(chrdata,dwordValue); 
    // ??网?文件，直到?空
	/*
    while (file->ReadString(somecode) != NULL) //如果采用LPTSTR?型，?取最大??nMax置0，使它遇空字符??束
    {	
		
		dataStore.WriteString(somecode);
		dataStore.WriteString("\n");		   //如果somecode采用LPTSTR?型,可不用此句
    }
	*/
	delete [] chrdata;
	file->Close();
	delete file;
 }
 else
 {
    dataStore.WriteString(_T("到指定服?器的?接建立失?..."));	
    return FALSE;
 }
 return TRUE;
}

