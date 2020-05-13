// NetWork_Browse_CopyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetWork_Browse_Copy.h"
#include "NetWork_Browse_CopyDlg.h"
#include <string.h>
#include <fstream.h>//��c++
#include <Winnetwk.h> 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//////////////////////////////
FILE *pf;
CString StrIP,StrNetWorkDir;
CString StrSearchDrt="";
struct FileData{
       int intnumber;
       char chrDir[500];
	   char chrFilName[100];
};
struct FileData *FD;
bool blnnewFileData=false;
int intShowCount=0;
///////////////////////////////
struct IPData{
       int intnumber;
       char chrIP[20];
};
struct IPData *IPD;
bool blnnewIPData=false;
int intTimer2Step=0;
int intIPCount=0;
FILE *pfNotConnect;//�L�s�uIP
FILE *pfNotDelete;//�L�k�R��FileName�PUP
FILE *pfDeleteOK;//�����R�����\���
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
// CNetWork_Browse_CopyDlg dialog

CNetWork_Browse_CopyDlg::CNetWork_Browse_CopyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetWork_Browse_CopyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetWork_Browse_CopyDlg)
	m_FileAmount = 0;
	m_StrNetWorkDir = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetWork_Browse_CopyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetWork_Browse_CopyDlg)
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPData);
	DDX_Text(pDX, IDC_EDIT1, m_FileAmount);
	DDX_Text(pDX, IDC_EDIT3, m_StrNetWorkDir);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNetWork_Browse_CopyDlg, CDialog)
	//{{AFX_MSG_MAP(CNetWork_Browse_CopyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetWork_Browse_CopyDlg message handlers

BOOL CNetWork_Browse_CopyDlg::OnInitDialog()
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
	m_IPData.SetWindowText("172.19.0.0"); 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNetWork_Browse_CopyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNetWork_Browse_CopyDlg::OnPaint() 
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
HCURSOR CNetWork_Browse_CopyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNetWork_Browse_CopyDlg::OnButton1()//���o����ɮ׼ƨì����ɦW 
{
	// TODO: Add your control notification handler code here
	/*
	////////////////////////���o�ثe���|
	TCHAR strCurDrt[500];
	m_FileAmount=0;
	int nLen = ::GetCurrentDirectory(500,strCurDrt);//���o�ثe�{�����|
	if( strCurDrt[nLen]!='\\' )
	{
		strCurDrt[nLen++] = '\\';
		strCurDrt[nLen] = '\0';
	}
	///////////////////////���ͷj�M���|
	StrSearchDrt=strCurDrt;
	StrSearchDrt=StrSearchDrt+"\\AV";
	/////////////////////�����ɮ�
	pf=fopen("data.txt","w");
	BrowseDir(StrSearchDrt);
	fclose(pf);
	UpdateData(false);
	////////////////////
	*/
	GetLocalFileAmount();
	//MessageBox("OK");

}
void CNetWork_Browse_CopyDlg::BrowseDir(CString strDir)//�C�X�Ҧ���Ƨ������ɮ�
{
	CFileFind ff;
	CString szDir = strDir;
	CString StrData;
	
	if(szDir.Right(1) != "\\")
		szDir += "\\";
	
	szDir += "*.*";
	
	BOOL res = ff.FindFile(szDir);
	while(res)
	{
		res = ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots())
		{
			//�笰��Ƨ�
			BrowseDir(ff.GetFilePath());
		}
		else if(!ff.IsDirectory() && !ff.IsDots())
		{
			//���ɮ�
			StrData=ff.GetFilePath();
			fprintf(pf,"%s\n",StrData.GetBuffer(0));//������|
			StrData=ff.GetFileName();
			fprintf(pf,"%s\n",StrData.GetBuffer(0));//���ɦW
			m_FileAmount++;
		}
	}
	ff.Close();//����
}

void CNetWork_Browse_CopyDlg::OnButton2() //���ͥؼи��|
{
	// TODO: Add your control notification handler code here
	/*
	m_IPData.GetWindowText(StrIP); 
	StrNetWorkDir="\\\\";
	StrNetWorkDir+=StrIP;
	StrNetWorkDir+="\\d$\\NabroClient\\AV";
	m_StrNetWorkDir=StrNetWorkDir;
	UpdateData(false);
	*/
	CreateNetWorkPath();
}

void CNetWork_Browse_CopyDlg::OnButton3() //�����ɮצW���x�s��O����
{
	// TODO: Add your control notification handler code here
	pfNotConnect=fopen("NotConnect.txt","w");//�L�s�uIP
	pfNotDelete=fopen("NotDelete.txt","w");//�L�k�R��FileName�PUP
	/*
	int i=0;
	char chrSeps='\\';//�إߤ��βŸ�
	char *chrInBuf;//�إ߼Ȧs��J��ƫ���
	char *chrOutBuf;//�إ߼Ȧs��X���θ�ƫ���
	chrInBuf=new char('\0');//���Ъ�l��
	chrOutBuf=new char('\0');//���Ъ�l��
	char strdata[500];
	char strdata1[100];
	fstream fp;
    fp.open("data.txt",ios::in);
	intShowCount=0;
	if(blnnewFileData==false)
	{
		FD=new FileData[m_FileAmount];
	}
	else
	{
		delete []FD;
		FD=new FileData[m_FileAmount];
	}
	blnnewFileData=true;
	do
	{
		fp.getline(strdata,500);
		m_FileData=strdata;//���X�t�����|�ɦW
		(FD+i)->intnumber=i;
		strcpy((FD+i)->chrDir,m_FileData.GetBuffer(0));
		/////////////////////////////���X���ɦW 
		fp.getline(strdata1,100);
		m_FileName=strdata1;
		strcpy((FD+i)->chrFilName,m_FileName.GetBuffer(0));
		i++;
	}while(i<m_FileAmount);
	fp.close();
	*/
	GetFileName2Memory();
	/////////////////////////////////////////////////////////
	/*
	char netpath[100]; 
	char drv[100];
	strcpy(netpath,m_StrNetWorkDir.GetBuffer(0));
	strcpy(drv,"X:");
	NETRESOURCE netres;
	netres.dwScope=RESOURCE_GLOBALNET;
	netres.dwType=RESOURCETYPE_ANY;
	netres.dwDisplayType=RESOURCEDISPLAYTYPE_GENERIC;
	netres.dwUsage=RESOURCEUSAGE_CONNECTABLE;
	netres.lpLocalName=drv;
	netres.lpRemoteName=netpath;
	netres.lpComment=NULL;
	netres.lpProvider=NULL;	
	CButton *but1;
	but1=(CButton *)this->GetDlgItem(IDC_BUTTON3);
	but1->EnableWindow(false);
	DWORD rslt=WNetAddConnection2(&netres,"nabro","nabro",0);//NABRO
	if(rslt==0)
	{
		this->SetDlgItemText(IDC_EDIT6,"�w�إ߳s�u...");
		SetTimer(1,1000,NULL);
	}
	else
	{
		NETRESOURCE netres1;
		netres1.dwScope=RESOURCE_GLOBALNET;
		netres1.dwType=RESOURCETYPE_ANY;
		netres1.dwDisplayType=RESOURCEDISPLAYTYPE_GENERIC;
		netres1.dwUsage=RESOURCEUSAGE_CONNECTABLE;
		netres1.lpLocalName=drv;
		netres1.lpRemoteName=netpath;
		netres1.lpComment=NULL;
		netres1.lpProvider=NULL;
		DWORD rslt1=WNetAddConnection2(&netres1,"hermes","Administrator",0);//HERMES
		if(rslt1==0)
		{
			this->SetDlgItemText(IDC_EDIT6,"�w�إ߳s�u...");
			SetTimer(1,1000,NULL);
		}
		else
		{
			but1->EnableWindow(true);
			MessageBox("�L�k�إߺ����Ϻо�");
		}
	}
	*/
	bool return1=MountNetWorkDir(1);
}
bool CNetWork_Browse_CopyDlg::SearchFile(CString strDir,CString strFile)//�M���ɮ׬O�_�s�b
{
	CFileFind ff;
	CString szDir = strDir;
	bool blnretien=false;
	if(szDir.Right(1) != "\\")
		szDir += "\\";
	
	szDir += "*.*";
	
	BOOL res = ff.FindFile(szDir);
	while(res)
	{
		res = ff.FindNextFile();
		if(ff.GetFileName()==strFile)
		{
			blnretien=true;
		}
		if(ff.IsDirectory() && !ff.IsDots())
		{
			//�l�ؿ�
			SearchFile(ff.GetFilePath(),strFile);
		}
	}
	ff.Close();//����
	return blnretien;

}

void CNetWork_Browse_CopyDlg::OnTimer(UINT nIDEvent)//�u�����檺�D�{�� 
{
	// TODO: Add your message handler code here and/or call default
	/*
	CString StrDir,StrFileName;//UI�ܼ�
	CString StrState,StrBuf;//UI�ܼ�
	CString StrNetWorkDir;
	StrNetWorkDir="X:\\";
	bool blnSearch=false;
	CString StrNetWorkFile;
	CButton *but1;
	but1=(CButton *)this->GetDlgItem(IDC_BUTTON3);
	//////////////////////////////////////////////UI�������
	StrDir=(FD+intShowCount)->chrDir;
	StrFileName=(FD+intShowCount)->chrFilName;
	this->SetDlgItemText(IDC_EDIT4,StrDir);
	this->SetDlgItemText(IDC_EDIT5,StrFileName);
	this->SetDlgItemInt(IDC_EDIT2,(intShowCount+1));
	///////////////////////////////////////////////
	//����ɮ�
	KillTimer(1);
	StrState="�� ";
	this->GetDlgItemText(IDC_EDIT2,StrBuf);
	StrState+=StrBuf;
	StrState+=" ������ɮ�";
	this->SetDlgItemText(IDC_EDIT6,StrState);
	blnSearch=SearchFile(StrNetWorkDir,StrFileName);//�ɮ׷j�M
	if(blnSearch)
	{//���ɮ�
		StrNetWorkFile=StrNetWorkDir+"\\"+StrFileName;
		if(DeleteFile(StrNetWorkFile.GetBuffer(0)))
		{

			this->SetDlgItemText(IDC_EDIT6,"�����ɮקR����...");
		}
		else
		{
			MessageBox("�ɮקR������");
		}	
	}
	else
	{//�L�ɮ�
		StrState+="->�L�ɮ�";
		this->SetDlgItemText(IDC_EDIT6,StrState);
	}
	//////////////////////////////////////////
	intShowCount++;
	if(intShowCount==m_FileAmount)
	{
		this->SetDlgItemText(IDC_EDIT6,"�Ҧ��ɮ׽ƻs����");
		but1->EnableWindow(true);
		char drv[100];
		strcpy(drv,"X:");
		DWORD rslt=WNetCancelConnection2(drv, 0, FALSE);
		if(rslt!=0)
			MessageBox("�L�k���_�����Ϻо�");
		MessageBox("����");
	}
	else
	{
		SetTimer(1,1000,NULL);
	}
	*/
	bool return1;
	CButton *but1;
	switch(nIDEvent)
	{
		case 1:
			Timer1Function();
			break;
		case 2:
			switch(intTimer2Step)
			{
				case 1://�]�wIP
					m_IPData.SetWindowText((IPD+intIPCount)->chrIP);
					intTimer2Step=2;
					intIPCount++;
					break;
				case 2://���ͺ�����m�M���ɮצW�٩��O����
					CreateNetWorkPath();
					GetFileName2Memory();
					intTimer2Step=3;
					break;
				case 3://�إߺ����Ϻ�
					KillTimer(2);
					return1=MountNetWorkDir(2);
					if(return1)
					{
						intTimer2Step=4;
					}
					else
					{
						intTimer2Step=5;
					}
					break;
					SetTimer(2,1000,NULL);//�Ұ�Timer2
				case 4://����R��
					return1=AutomaticDeleteFile();
					if(return1)
					{
						intTimer2Step=5;
					}
					else
					{
						intTimer2Step=4;
					}
					break;
				case 5://�P�_�Ҧ�IP�O�_����
					if(intIPCount<lngIPDataAmount)
					{
						intTimer2Step=1;
					}
					else
					{
						intTimer2Step=0;
						fclose(pfNotConnect);//�L�s�uIP
						fclose(pfNotDelete);//�L�k�R��FileName�PUP
						fclose(pfDeleteOK);//�����R�����\���
						KillTimer(2);
						but1=(CButton *)this->GetDlgItem(IDC_BUTTON4);
						but1->EnableWindow(true);
						MessageBox("�����Ҧ�IP_�Ьd�ݰO����");
					}
					break;
			}
			break;
	}
	CDialog::OnTimer(nIDEvent);
}
void CNetWork_Browse_CopyDlg::GetLocalFileAmount()//�p���ɮ׼ƶq
{
	////////////////////////���o�ثe���|
	TCHAR strCurDrt[500];
	m_FileAmount=0;
	int nLen = ::GetCurrentDirectory(500,strCurDrt);//���o�ثe�{�����|
	if( strCurDrt[nLen]!='\\' )
	{
		strCurDrt[nLen++] = '\\';
		strCurDrt[nLen] = '\0';
	}
	///////////////////////���ͷj�M���|
	StrSearchDrt=strCurDrt;
	StrSearchDrt=StrSearchDrt+"\\AV";
	/////////////////////�����ɮ�
	pf=fopen("data.txt","w");
	BrowseDir(StrSearchDrt);
	fclose(pf);
	UpdateData(false);
	////////////////////
}
void CNetWork_Browse_CopyDlg::CreateNetWorkPath()//���ͳs�u���}
{
	m_IPData.GetWindowText(StrIP); 
	StrNetWorkDir="\\\\";
	StrNetWorkDir+=StrIP;
	StrNetWorkDir+="\\d$\\NabroClient\\Data\\Schedule";
	m_StrNetWorkDir=StrNetWorkDir;
	UpdateData(false);
}
void CNetWork_Browse_CopyDlg::GetFileName2Memory()//���ɮצW�٦s�J�O����
{
	int i=0;
	char chrSeps='\\';//�إߤ��βŸ�
	char *chrInBuf;//�إ߼Ȧs��J��ƫ���
	char *chrOutBuf;//�إ߼Ȧs��X���θ�ƫ���
	chrInBuf=new char('\0');//���Ъ�l��
	chrOutBuf=new char('\0');//���Ъ�l��
	char strdata[500];
	char strdata1[100];
	fstream fp;
    fp.open("data.txt",ios::in);
	intShowCount=0;
	if(blnnewFileData==false)
	{
		FD=new FileData[m_FileAmount];
	}
	else
	{
		delete []FD;
		FD=new FileData[m_FileAmount];
	}
	blnnewFileData=true;
	do
	{
		fp.getline(strdata,500);
		m_FileData=strdata;//���X�t�����|�ɦW
		(FD+i)->intnumber=i;
		strcpy((FD+i)->chrDir,m_FileData.GetBuffer(0));
		/////////////////////////////���X���ɦW 
		fp.getline(strdata1,100);
		m_FileName=strdata1;
		strcpy((FD+i)->chrFilName,m_FileName.GetBuffer(0));
		i++;
	}while(i<m_FileAmount);
	fp.close(); 
}
bool CNetWork_Browse_CopyDlg::MountNetWorkDir(int intTimer)//�إߺ����Ϻо�
{
	/////////////////////////////////////////////////////////
	char netpath[100]; 
	char drv[100];
	strcpy(netpath,m_StrNetWorkDir.GetBuffer(0));
	strcpy(drv,"X:");
	NETRESOURCE netres;
	netres.dwScope=RESOURCE_GLOBALNET;
	netres.dwType=RESOURCETYPE_ANY;
	netres.dwDisplayType=RESOURCEDISPLAYTYPE_GENERIC;
	netres.dwUsage=RESOURCEUSAGE_CONNECTABLE;
	netres.lpLocalName=drv;
	netres.lpRemoteName=netpath;
	netres.lpComment=NULL;
	netres.lpProvider=NULL;	
	CButton *but1;
	but1=(CButton *)this->GetDlgItem(IDC_BUTTON3);
	but1->EnableWindow(false);
	DWORD rslt=WNetAddConnection2(&netres,"nabro","nabro",0);//NABRO
	if(rslt==0)
	{
		this->SetDlgItemText(IDC_EDIT6,"�w�إ߳s�u...");
		if(intTimer==1)
		{
			SetTimer(1,1000,NULL);
		}
		else
		{
			SetTimer(2,1000,NULL);
		}
		return true;
	}
	else
	{
		NETRESOURCE netres1;
		netres1.dwScope=RESOURCE_GLOBALNET;
		netres1.dwType=RESOURCETYPE_ANY;
		netres1.dwDisplayType=RESOURCEDISPLAYTYPE_GENERIC;
		netres1.dwUsage=RESOURCEUSAGE_CONNECTABLE;
		netres1.lpLocalName=drv;
		netres1.lpRemoteName=netpath;
		netres1.lpComment=NULL;
		netres1.lpProvider=NULL;
		DWORD rslt1=WNetAddConnection2(&netres1,"hermes","Administrator",0);//HERMES
		if(rslt1==0)
		{
			this->SetDlgItemText(IDC_EDIT6,"�w�إ߳s�u...");
			if(intTimer==1)
			{
				SetTimer(1,1000,NULL);
			}
			else
			{
				SetTimer(2,1000,NULL);
			}
			return true;
		}
		else
		{
			but1->EnableWindow(true);
			m_IPData.GetWindowText(StrIP); 
			fprintf(pfNotConnect,"%s\n",StrIP.GetBuffer(0));//�L�s�uIP
			if(intTimer==1)
			{
				MessageBox("�L�k�إߺ����Ϻо�");
			}
			else
			{
				SetTimer(2,1000,NULL);
			}
			return false;
			
		}
	}
	/////////////////////////////////////////////////////////////
}
void CNetWork_Browse_CopyDlg::Timer1Function()
{
	CString StrDir,StrFileName;//UI�ܼ�
	CString StrState,StrBuf;//UI�ܼ�
	CString StrNetWorkDir;
	StrNetWorkDir="X:\\";
	bool blnSearch=false;
	CString StrNetWorkFile;
	CButton *but1;
	but1=(CButton *)this->GetDlgItem(IDC_BUTTON3);
	//////////////////////////////////////////////UI�������
	StrDir=(FD+intShowCount)->chrDir;
	StrFileName=(FD+intShowCount)->chrFilName;
	this->SetDlgItemText(IDC_EDIT4,StrDir);
	this->SetDlgItemText(IDC_EDIT5,StrFileName);
	this->SetDlgItemInt(IDC_EDIT2,(intShowCount+1));
	///////////////////////////////////////////////
	//����ɮ�
	KillTimer(1);
	StrState="�� ";
	this->GetDlgItemText(IDC_EDIT2,StrBuf);
	StrState+=StrBuf;
	StrState+=" ������ɮ�";
	this->SetDlgItemText(IDC_EDIT6,StrState);
	blnSearch=SearchFile(StrNetWorkDir,StrFileName);//�ɮ׷j�M
	if(blnSearch)
	{//���ɮ�
		StrNetWorkFile=StrNetWorkDir+"\\"+StrFileName;
		if(DeleteFile(StrNetWorkFile.GetBuffer(0)))
		{

			this->SetDlgItemText(IDC_EDIT6,"�����ɮקR����...");
		}
		else
		{
			MessageBox("�ɮקR������");
		}	
	}
	else
	{//�L�ɮ�
		StrState+="->�L�ɮ�";
		this->SetDlgItemText(IDC_EDIT6,StrState);
	}
	//////////////////////////////////////////
	intShowCount++;
	if(intShowCount==m_FileAmount)
	{
		this->SetDlgItemText(IDC_EDIT6,"�Ҧ��ɮקR������");
		but1->EnableWindow(true);
		char drv[100];
		strcpy(drv,"X:");
		DWORD rslt=WNetCancelConnection2(drv, 0, FALSE);
		if(rslt!=0)
			MessageBox("�L�k���_�����Ϻо�");
		MessageBox("����");
	}
	else
	{
		SetTimer(1,1000,NULL);
	}
}

void CNetWork_Browse_CopyDlg::OnButton4()//�۰��ɮקR�� 
{
	// TODO: Add your control notification handler code here
	CButton *but1;
	but1=(CButton *)this->GetDlgItem(IDC_BUTTON4);
	but1->EnableWindow(false);
	//Step 0_0 Ū���ɮ׭p��ƶq
	char chrstringbuf[20];//�ȦsIP���
	lngIPDataAmount=0;//IP�ƶq�ܼƪ�l��_�����ܼ�
	pf=fopen("IP_Data.txt","r");
	while(fscanf(pf,"%s",chrstringbuf)!=EOF)
		lngIPDataAmount++;
	fclose(pf);
	//Step 0_1 ���ɮק�IP���O����
	fstream fp;
	int i=0;
    fp.open("IP_Data.txt",ios::in);
	if(blnnewIPData==false)
	{
		IPD=new IPData[lngIPDataAmount];
	}
	else
	{
		delete []IPD;
		IPD=new IPData[lngIPDataAmount];
	}
	blnnewFileData=true;
	do
	{
		fp.getline(chrstringbuf,500);
		(IPD+i)->intnumber=i;  
		strcpy((IPD+i)->chrIP,chrstringbuf);
		i++;
	}while(i<lngIPDataAmount);
	fp.close(); 
	//Step 0_2 �I�stimer2
	intTimer2Step=1;//intTimer2Step��l�Ƴ]�w
	intIPCount=0;//intIPCount��l�Ƴ]�w
	GetLocalFileAmount();
	pfNotConnect=fopen("NotConnect.txt","w");//�L�s�uIP
	pfNotDelete=fopen("NotDelete.txt","w");//�L�k�R��FileName�PUP
	pfDeleteOK=fopen("DeleteOK.txt","w");//�����R�����\���
	SetTimer(2,1000,NULL);//�Ұ�Timer2
}
bool CNetWork_Browse_CopyDlg::AutomaticDeleteFile()
{
	CString StrDir,StrFileName;//UI�ܼ�
	CString StrState,StrBuf;//UI�ܼ�
	CString StrNetWorkDir;
	StrNetWorkDir="X:\\";
	bool blnSearch=false;
	CString StrNetWorkFile;
	CButton *but1;
	but1=(CButton *)this->GetDlgItem(IDC_BUTTON3);
	//////////////////////////////////////////////UI�������
	StrDir=(FD+intShowCount)->chrDir;
	StrFileName=(FD+intShowCount)->chrFilName;
	this->SetDlgItemText(IDC_EDIT4,StrDir);
	this->SetDlgItemText(IDC_EDIT5,StrFileName);
	this->SetDlgItemInt(IDC_EDIT2,(intShowCount+1));
	///////////////////////////////////////////////
	//����ɮ�
	KillTimer(2);
	StrState="�� ";
	this->GetDlgItemText(IDC_EDIT2,StrBuf);
	StrState+=StrBuf;
	StrState+=" ������ɮ�";
	this->SetDlgItemText(IDC_EDIT6,StrState);
	blnSearch=SearchFile(StrNetWorkDir,StrFileName);//�ɮ׷j�M
	if(blnSearch)
	{//���ɮ�
		StrNetWorkFile=StrNetWorkDir+"\\"+StrFileName;
		if(DeleteFile(StrNetWorkFile.GetBuffer(0)))
		{
			m_IPData.GetWindowText(StrIP); 
			fprintf(pfDeleteOK,"%s\t%s\n",StrIP.GetBuffer(0),StrFileName.GetBuffer(0));//�����R�����\���
			this->SetDlgItemText(IDC_EDIT6,"�����ɮקR����...");
		}
		else
		{
			//MessageBox("�ɮקR������");
			m_IPData.GetWindowText(StrIP); 
			fprintf(pfNotDelete,"%s\t%s\n",StrIP.GetBuffer(0),StrFileName.GetBuffer(0));//�L�k�R��FileName�PUP
		}	
	}
	else
	{//�L�ɮ�
		StrState+="->�L�ɮ�";
		this->SetDlgItemText(IDC_EDIT6,StrState);
	}
	//////////////////////////////////////////
	intShowCount++;
	if(intShowCount==m_FileAmount)
	{
		this->SetDlgItemText(IDC_EDIT6,"�Ҧ��ɮקR������");
		but1->EnableWindow(true);
		char drv[100];
		strcpy(drv,"X:");
		DWORD rslt=WNetCancelConnection2(drv, 0, FALSE);
		if(rslt!=0)
		{
			MessageBox("�L�k���_�����Ϻо�");
		}
		else
		{
			SetTimer(2,1000,NULL);
			return true;
		}
		//MessageBox("����");
	}
	else
	{
		SetTimer(2,1000,NULL);
		return false;
	}
	return false;
}