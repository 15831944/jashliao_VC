// Cute_Main_ControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Cute_Main_Control.h"
#include "Cute_Main_ControlDlg.h"
#include "LaunchDLL.h"//�ĤE��->���F����L����
#include "DibSection.h"
#include <mmsystem.h>//Step �Y�p��t�Τu�@�C1
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define Spday_Max 365	//gStrSpday
#define CommanCount_Max 11	//blnCommandArray
#define CFData_Max 50	//ChangeFormData�̤j�}�C��
#define conData_Max 10	//Control_Data�̤j�}�C��
//#define PDData_Max 10	//ProgramData�̤j�}�C��---->�b12.1������ H �� 
#define WM_SHOWTASK	WM_USER+5//Step �Y�p��t�Τu�@�C2
bool blnCheckHide=false;//Step �Y�p��t�Τu�@�C2
CString gStrSpday[Spday_Max];
int gintSpdayCount=0;
/////////////////////////////////////////////////////////////////////
//��11.0�����\��
bool gblnLogFlag=false;//��11.4�����\��
bool gblnErrFlag=false;//��11.4�����\��
bool gblnControlErrorLog=false;//0�ɮ�1�A1�ɮ�2
FILE *gpfControlError1=NULL;
FILE *gpfControlError2=NULL;
FILE *gpfControlLog1=NULL;
FILE *gpfControlLog2=NULL;
//WCHAR *gpUnicodeDataBuf=NULL;//��12.8��->Unicode
WCHAR gpUnicodeDataBuf[200];
CString gStr2UnicodeData;//��12.8��->Unicode
int gintUnicodeDataLen=0;//��12.8��->Unicode
char gunicode[2];//��12.8��->Unicode   
WCHAR *gpUnicode = L"000000,0,Cute_Main Create\r\n";//��13.1��
bool gblnGetError=false;//��13.2��
CString gStrYesterday="";
bool gblnMonitorOnCheck=false;
bool gblnMonitorOffCheck=false;
/////////////////////////////////////////////////////////////////////
CString gStrNowStyle="";//�s��ب䪩���W��
struct ProgramData//�s��n�Q�Ұʵ{����T
{
	CString StrName;
	CString StrCaption;
}gstructPD[PDData_Max];
int gintProgramNumber=0;//�s��n�Q�Ұʵ{���Ӽ�
int gintProgramZindex[PDData_Max][2];//��12.1����------------------>�x�s��ܼh��
bool gblnRunZindex=false;//��12.2����
/////////////////////////////////////////////////////////////////////
struct ChangeFormData//�s����ܪ����V�T��
{
	int intStart_Hr;
	int intStart_Min;
	int intEnd_Hr;
	int intEnd_Min;
	char chrFormName[100];
}gstructCFD[CFData_Max];
int gintCFDnumber=0;//�s�񪩫��ƶq
bool gblnChangeForm=false;//�s��O�_�n����P�_�󴫪����X��
/////////////////////////////////////////////////////////////////////
//�s��ù��}�����
//step Ū��XML3
struct Control_Data//�s��ù��}�����
{
	int intStart_Hr;
	int intStart_Min;
	int intEnd_Hr;
	int intEnd_Min;
};
struct Control_Data gstruct_SunCD[conData_Max];
struct Control_Data gstruct_MonCD[conData_Max];
struct Control_Data gstruct_TueCD[conData_Max];
struct Control_Data gstruct_WedCD[conData_Max];
struct Control_Data gstruct_ThuCD[conData_Max];
struct Control_Data gstruct_FriCD[conData_Max];
struct Control_Data gstruct_SatCD[conData_Max];
int gintData_Max[7];
TCHAR gstrCurDrt[500];//�s��ب�ؿ��r��
//////////////////////////////////////////////////
int gintMonitorWidthPixels,gintMonitorHeightPixels;//��12.8��
/////////////////////////////////////////////////////////////////////////////
FILE *gpfUpdateProgram;//��13.3��
int gintUpdateProgramCount;//��13.3��
char MAP_NAME0[20]=	"spacesoft1 corp0.";//��13.3��
char MAP_NAME1[20]=	"spacesoft1 corp1.";//��13.3��
char MAP_NAME2[20]=	"spacesoft1 corp2.";//��13.3��
char MAP_NAME3[20]=	"spacesoft1 corp3.";//��13.3��
#define	MAP_LENGTH	8//��13.3��
HANDLE hFileMap[4] ={NULL,NULL,NULL,NULL} ;//��13.3��
static char szOldData[MAP_LENGTH] = "" ;//��13.3��
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
// CCute_Main_ControlDlg dialog

CCute_Main_ControlDlg::CCute_Main_ControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCute_Main_ControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCute_Main_ControlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCute_Main_ControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCute_Main_ControlDlg)
	DDX_Control(pDX, IDC_JPG1, m_JPG);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCute_Main_ControlDlg, CDialog)
	//{{AFX_MSG_MAP(CCute_Main_ControlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_MESSAGE(WM_SHOWTASK,onShowTask)//Step �Y�p��t�Τu�@�C5
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCute_Main_ControlDlg message handlers

BOOL CCute_Main_ControlDlg::OnInitDialog()
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
	InstallLaunchEv();//�ĤE��->���F����L����
	hFileMap[0] = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME0 ) ;//��13.3��
	//hFileMap[1] = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME1 ) ;//��13.3��
	//hFileMap[2] = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME2 ) ;//��13.3��
	//hFileMap[3] = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME3 ) ;//��13.3��
	ShowWindow(SW_MINIMIZE);//�Y�p�D����
	/////////////////////////////////////////////////////////////////
	//��12.1��->���w�ƹ����ʰϰ�
	CRect rc;
	rc.top=1080;
	rc.bottom=(1080+200);
	rc.left=1920;
	rc.right=(1920+200); 
	::SetCursorPos((1920+(200/2)),(1080+(200/2)));  //�t�����ô��
	ClipCursor(&rc);
	////////////////////////////////////////////////////////////////
	m_MainMonitor_On=false;//�ܼƪ�l��->�w�]�������Ʀ�ù��j��ʧ@
	m_MainMonitor_Off=false;//�ܼƪ�l��->�w�]�������Ʀ�ù��j��ʧ@
	gblnRunZindex=false;//��12.2����
	CreateLogFile();//�}�Ҭ�����T�\��//��11.0�����\��
	InitializeXMLMemory();//��l�ƩҦ����c���ܼƨéI�s�۹�����Ȩ�ƶ��
	GetProgramInfo();//���o�n�Q����{�����
	TimerFunction();//��������D�{��
	Sleep(20000);//���{���į୰�C
	OnButton1();//�Ұ�Timer->�T�w�ɶ�����D�{��
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCute_Main_ControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCute_Main_ControlDlg::OnPaint() 
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
HCURSOR CCute_Main_ControlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCute_Main_ControlDlg::OnButton2() //���õ�����t�Τu�@�C
{
	// TODO: Add your control notification handler code here
	if(blnCheckHide==false)
	{
		NOTIFYICONDATA nid;
		nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
		nid.hWnd=this->m_hWnd;
		nid.uID=IDR_MAINFRAME;
		nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
		nid.uCallbackMessage=WM_SHOWTASK;//�۩w�q�������W��
		nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
		strcpy(nid.szTip,"Cute_Control");//��T���ܱ���"�p�e���ȴ���"
		Shell_NotifyIcon(NIM_ADD,&nid);//�b�U�L�ϲK�[�ϥ�
		blnCheckHide=true;
	}
	ShowWindow(SW_HIDE);//���åD����	
}
LRESULT CCute_Main_ControlDlg::onShowTask(WPARAM wParam,LPARAM lParam)//Step �Y�p��t�Τu�@�C6
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

void CCute_Main_ControlDlg::TimerFunction()//�D�{��
{
	int i=0,j=0;
	int startmin,endmin;
	CString StrStyleBuf;
	CString strFileName1;
	CString StrControlFileName;
	CString StrNowday;
	CString StrDayBuf;
	CString StrMonthBuf;
	bool blnSpday;
	bool blnRunChangeForm=false;
	int hr,min;
	/////////////////////////////////////////////////////////////////
	//��12.1��->���w�ƹ����ʰϰ�
	CRect rc;
	rc.top=1080;
	rc.bottom=(1080+200);
	rc.left=1920;
	rc.right=(1920+200); 
	::SetCursorPos((1920+(200/2)),(1080+(200/2)));  //�t�����ô��
	ClipCursor(&rc);
	////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	//���o�ثe�t�ήɶ�
	::SetCursorPos((1920+(200/2)),1080+(200/2));  //�t�����ô��
	CTime t1=CTime::GetCurrentTime();
	int Year=t1.GetYear();//�~ 
	int Month=t1.GetMonth(); //��
	int Day=t1.GetDay();//��
	/////////////////////////////////
	StrNowday.Format("%d",Year);
	if(Month<10)
	{
		StrMonthBuf.Format("0%d",Month); 
	}
	else
	{
		StrMonthBuf.Format("%d",Month);
	}
	if(Day<10)
	{
		StrDayBuf.Format("0%d",Day); 
	}
	else
	{
		StrDayBuf.Format("%d",Day);
	}
	StrNowday=StrNowday+StrMonthBuf+StrDayBuf;
	CreateLogFile();//�}�Ҭ�����T�\��//��11.0�����\��
	/////////////////////////////////
	int week=t1.GetDayOfWeek()-1;//�зǬ�1 -> 7;�令0 -> 6  
	hr=t1.GetHour();
	min=t1.GetMinute();
	min+=hr*60;
	////////////////////////////////////////////////////////////////////////////////
	//�M�ù��}���������A�P��O�_�n���ܺX��
	bool blnMonitor_On=false;
	switch(week)
	{
		case 0:
			for(i=0;i<gintData_Max[week];i++)
			{
				startmin=gstruct_SunCD[i].intStart_Hr*60+gstruct_SunCD[i].intStart_Min;
				endmin=gstruct_SunCD[i].intEnd_Hr*60+gstruct_SunCD[i].intEnd_Min;
				if(min>=startmin && min<endmin)
				{
					blnMonitor_On=true;
					break;
				}
			}
			break;
		case 1:
			for(i=0;i<gintData_Max[week];i++)
			{
				startmin=gstruct_MonCD[i].intStart_Hr*60+gstruct_MonCD[i].intStart_Min;
				endmin=gstruct_MonCD[i].intEnd_Hr*60+gstruct_MonCD[i].intEnd_Min;
				if(min>=startmin && min<endmin)
				{
					blnMonitor_On=true;
					break;
				}
			}
			break;
		case 2:
			for(i=0;i<gintData_Max[week];i++)
			{
				startmin=gstruct_TueCD[i].intStart_Hr*60+gstruct_TueCD[i].intStart_Min;
				endmin=gstruct_TueCD[i].intEnd_Hr*60+gstruct_TueCD[i].intEnd_Min;
				if(min>=startmin && min<endmin)
				{
					blnMonitor_On=true;
					break;
				}
			}
			break;
		case 3:
			for(i=0;i<gintData_Max[week];i++)
			{
				startmin=gstruct_WedCD[i].intStart_Hr*60+gstruct_WedCD[i].intStart_Min;
				endmin=gstruct_WedCD[i].intEnd_Hr*60+gstruct_WedCD[i].intEnd_Min;
				if(min>=startmin && min<endmin)
				{
					blnMonitor_On=true;
					break;
				}
			}
			break;
		case 4:
			for(i=0;i<gintData_Max[week];i++)
			{
				startmin=gstruct_ThuCD[i].intStart_Hr*60+gstruct_ThuCD[i].intStart_Min;
				endmin=gstruct_ThuCD[i].intEnd_Hr*60+gstruct_ThuCD[i].intEnd_Min;
				if(min>=startmin && min<endmin)
				{
					blnMonitor_On=true;
					break;
				}
			}
			break;
		case 5:
			for(i=0;i<gintData_Max[week];i++)
			{
				startmin=gstruct_FriCD[i].intStart_Hr*60+gstruct_FriCD[i].intStart_Min;
				endmin=gstruct_FriCD[i].intEnd_Hr*60+gstruct_FriCD[i].intEnd_Min;
				if(min>=startmin && min<endmin)
				{
					blnMonitor_On=true;
					break;
				}
			}
			break;
		case 6:
			for(i=0;i<gintData_Max[week];i++)
			{
				startmin=gstruct_SatCD[i].intStart_Hr*60+gstruct_SatCD[i].intStart_Min;
				endmin=gstruct_SatCD[i].intEnd_Hr*60+gstruct_SatCD[i].intEnd_Min;
				if(min>=startmin && min<endmin)
				{
					blnMonitor_On=true;
					break;
				}
			}
			break;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	//�����O�_���R�O�T��
	Detect_Command();
	//////////////////////////////////
	//Ū���O�_����������������R�O
	gblnChangeForm=Read_ChangeForm();
	if(gblnChangeForm)
	{
		for(i=0;i<gintCFDnumber;i++)
		{
			startmin=gstructCFD[i].intStart_Hr*60+gstructCFD[i].intStart_Min;  
			endmin=gstructCFD[i].intEnd_Hr*60+gstructCFD[i].intEnd_Min;
			if(min>=startmin && min<endmin)
			{
				StrStyleBuf=gstructCFD[i].chrFormName;
				if(StrStyleBuf!=gStrNowStyle)
				{
					Run_Command(3);//Stop_Program
					ChangeStyle(StrStyleBuf);
					GetProgramInfo();
					Run_Command(2);//Start_Program
					gStrNowStyle=StrStyleBuf;
				}
				blnRunChangeForm=true;//��11.0�����\��,�O���j�Ѧ^��w�]����
				break;//��11.0�����\��,�O���j�Ѧ^��w�]����
			}
			blnRunChangeForm=false;//��11.0�����\��,�O���j�Ѧ^��w�]����
		}
		////////////////////////////////////////////////////
		//��11.0�����\��,�O���j�Ѧ^��w�]����
		if(blnRunChangeForm==false)
		{
			if(gStrNowStyle!="Default")
			{
				gStrNowStyle="Default";
				Run_Command(3);//Stop_Program
				ChangeStyle(gStrNowStyle);
				GetProgramInfo();
				Run_Command(2);//Start_Program
			}
		}
		////////////////////////////////////////////////////
	}
	//////////////////////////////////////////////////////////////////////////
	if(!(m_MainMonitor_On^m_MainMonitor_Off))
	{
		blnSpday=false;
		for(i=0;i<gintSpdayCount;i++)
		{
			if(gStrSpday[i]==StrNowday)
			{
				blnSpday=true;
				break;
			}
		}
		if(blnSpday)
		{
			Run_Command(3);//Stop_Program
			Run_Command(1);//Monitor_Off
			//this->SetWindowText("Cute_Main_Control-Off");//�ĤE�����\�� ->���F�i�H���T�w���D
		}
		else
		{
			if(blnMonitor_On)
			{
				SwitchMonitor();//��12.7��->�eCTRL+ALT+F9�Ϸs��STB���w�n��ʵ�����X
				Run_Command(2);//Start_Program
				Run_Command(0);//Monitor_On
				::SetCursorPos((1920+(200/2)),(1080+(200/2)));  //�t�����ô��
				//this->SetWindowText("Cute_Main_Control-On");//�ĤE�����\�� ->���F�i�H���T�w���D 
			}
			else
			{
				Run_Command(3);//Stop_Program
				CreateCommunication();//�H�T�O�q�T�{���û��s�b----->�ĤK�����\��
				Run_Command(1);//Monitor_Off
				//this->SetWindowText("Cute_Main_Control-Off");//�ĤE�����\�� ->���F�i�H���T�w���D 
			}
		}
	}
	else
	{
		CreateCommunication();//�H�T�O�q�T�{���û��s�b----->�ĤK�����\��
		if(m_MainMonitor_On)
		{
			SwitchMonitor();//��12.7��->�eCTRL+ALT+F9�Ϸs��STB���w�n��ʵ�����X
			Run_Command(0);//Monitor_On
		}
		else
		{
			Run_Command(1);//Monitor_Off
		}
	}
	m_WDT.ResetWDT();//��14.1��->Watch Dog Timer 
}
void CCute_Main_ControlDlg::OnTimer(UINT nIDEvent) //step Ū��XML4
{
	// TODO: Add your message handler code here and/or call default
	TimerFunction();
	CDialog::OnTimer(nIDEvent);
}

void CCute_Main_ControlDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	SetTimer(1,10000,NULL);
}

void CCute_Main_ControlDlg::Read_Monitor()//step Ū��XML4
{
	MSXML2::IXMLDOMDocumentPtr pDoc;
	CTime t1=CTime::GetCurrentTime();
	_variant_t vtStr;
	bool blnRead=false;
	CString strValue;
	//int intHr,intMin;
	char chrDataBuf[1000];
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   return;
	}
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	CString strFileName1 = gstrCurDrt;
	strFileName1 +="Resources\\Setting\\SignageConfig.xml";
	blnRead=pDoc->load((_bstr_t)strFileName1); 
	if(blnRead)//��11.0�����\��
	{
		MSXML2::IXMLDOMNodePtr  Sunday_Start;
		MSXML2::IXMLDOMNodePtr  Monday_Start; 
		MSXML2::IXMLDOMNodePtr  Tuesday_Start; 
		MSXML2::IXMLDOMNodePtr  Wednesday_Start; 
		MSXML2::IXMLDOMNodePtr  Thursday_Start; 
		MSXML2::IXMLDOMNodePtr  Friday_Start; 
		MSXML2::IXMLDOMNodePtr  Saturday_Start; 
		//�b�𤤴M��`�I,"//"��ܦb���N�@�h�d�� 
		////////////////////////////////////////////////////////////
		Sunday_Start=pDoc->selectSingleNode("//Sunday_Start");	
		Sunday_Start->get_nodeTypedValue(&vtStr);  
		strValue=vtStr.bstrVal;
		strcpy(chrDataBuf,strValue.GetBuffer(0)); 
		MonitorRipData(strValue,0);
		//MessageBox(chrDataBuf);
		Monday_Start=pDoc->selectSingleNode("//Monday_Start");	
		Monday_Start->get_nodeTypedValue(&vtStr);  
		strValue=vtStr.bstrVal;
		strcpy(chrDataBuf,strValue.GetBuffer(0));
		MonitorRipData(strValue,1);
		//MessageBox(chrDataBuf);
		Tuesday_Start=pDoc->selectSingleNode("//Tuesday_Start");	
		Tuesday_Start->get_nodeTypedValue(&vtStr);  
		strValue=vtStr.bstrVal;
		strcpy(chrDataBuf,strValue.GetBuffer(0));
		MonitorRipData(strValue,2);
		//MessageBox(chrDataBuf);
		Wednesday_Start=pDoc->selectSingleNode("//Wednesday_Start");	
		Wednesday_Start->get_nodeTypedValue(&vtStr);  
		strValue=vtStr.bstrVal;
		strcpy(chrDataBuf,strValue.GetBuffer(0));
		MonitorRipData(strValue,3);
		//MessageBox(chrDataBuf);
		Thursday_Start=pDoc->selectSingleNode("//Thursday_Start");	
		Thursday_Start->get_nodeTypedValue(&vtStr);  
		strValue=vtStr.bstrVal;
		strcpy(chrDataBuf,strValue.GetBuffer(0));
		MonitorRipData(strValue,4);
		//MessageBox(chrDataBuf);
		Friday_Start=pDoc->selectSingleNode("//Friday_Start");	
		Friday_Start->get_nodeTypedValue(&vtStr);  
		strValue=vtStr.bstrVal;
		strcpy(chrDataBuf,strValue.GetBuffer(0));
		MonitorRipData(strValue,5);
		//MessageBox(chrDataBuf);
		Saturday_Start=pDoc->selectSingleNode("//Saturday_Start");	
		Saturday_Start->get_nodeTypedValue(&vtStr);  
		strValue=vtStr.bstrVal;
		strcpy(chrDataBuf,strValue.GetBuffer(0));
		MonitorRipData(strValue,6);
		//MessageBox(chrDataBuf);
	}
	else//��11.0�����\��
	{
		if(gblnErrFlag==true)
		{
			CString strTime = t1.Format("%H%M%S"); 
			if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
			{
				//fprintf(gpfControlError2,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				//////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError2);//�g��
				gblnGetError=true;//��13.2��
				////delete [] gpUnicodeDataBuf;//����O����
				////gpUnicodeDataBuf=NULL;//����O����
			}
			else
			{
				//fprintf(gpfControlError1,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				//////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError1);//�g��
				gblnGetError=true;//��13.2��
				////delete [] gpUnicodeDataBuf;//����O����
				////gpUnicodeDataBuf=NULL;//����O����
			}
		}
	}
}
void CCute_Main_ControlDlg::MonitorRipData(CString Datainput,int day)
{
	////////////////////////////////////
	CString StrIP="";
	CString StrBuf="";
	char *chrInBuf;//�إ߼Ȧs��J��ƫ���
	char *chrOutBuf;//�إ߼Ȧs��X���θ�ƫ���
	long lngLen=0;//�إߪ��׼Ȧs�ܼ�
	long lngGetLen1=0;//������ƪ���
	long lngGetLen2=0;//�Ѿl��ƪ���
	CString m_strInData="";//�D
	CString strInData="";//m_strInData����
	CString strRemain="";//�Ѿl���
	char chrSeps[]="+";//�إߤ��βŸ�
	chrInBuf=new char('\0');//���Ъ�l��
	chrOutBuf=new char('\0');//���Ъ�l��
	bool blnLen=false;//�P�_���׬O�_��0
	int intCount=0;//�����ĴX�����
	////////////////////////////////////////
	int intHr1,intHr2;
	int intMin1,intMin2;
	m_strInData=Datainput;
	strInData=m_strInData;//���X��Ӹ��
	do
	{
		chrInBuf=strInData.GetBuffer(0);//�ᤩ���
		lngLen=strlen(chrInBuf);
		if(lngLen<= 0)//�����̫�@����ƴ���ҳy���~�P
		{
			blnLen=true;
			break;
		}
		chrOutBuf=strtok(chrInBuf,chrSeps);//�^�������
		sscanf(chrOutBuf,"%d:%d-%d:%d",&intHr1,&intMin1,&intHr2,&intMin2);
		switch(day)
		{
			case 0:
				gstruct_SunCD[intCount].intStart_Hr=intHr1;
				gstruct_SunCD[intCount].intStart_Min=intMin1;
				gstruct_SunCD[intCount].intEnd_Hr=intHr2;
				gstruct_SunCD[intCount].intEnd_Min=intMin2;
				break;
			case 1:
				gstruct_MonCD[intCount].intStart_Hr=intHr1;
				gstruct_MonCD[intCount].intStart_Min=intMin1; 
				gstruct_MonCD[intCount].intEnd_Hr=intHr2; 
				gstruct_MonCD[intCount].intEnd_Min=intMin2; 
				break;
			case 2:
				gstruct_TueCD[intCount].intStart_Hr=intHr1;
				gstruct_TueCD[intCount].intStart_Min=intMin1;  
				gstruct_TueCD[intCount].intEnd_Hr=intHr2; 
				gstruct_TueCD[intCount].intEnd_Min=intMin2;  
				break;
			case 3:
				gstruct_WedCD[intCount].intStart_Hr=intHr1;
				gstruct_WedCD[intCount].intStart_Min=intMin1;
				gstruct_WedCD[intCount].intEnd_Hr=intHr2; 
				gstruct_WedCD[intCount].intEnd_Min=intMin2;  
				break;
			case 4:
				gstruct_ThuCD[intCount].intStart_Hr=intHr1;
				gstruct_ThuCD[intCount].intStart_Min=intMin1;
				gstruct_ThuCD[intCount].intEnd_Hr=intHr2; 
				gstruct_ThuCD[intCount].intEnd_Min=intMin2; 
				break;
			case 5:
				gstruct_FriCD[intCount].intStart_Hr=intHr1;
				gstruct_FriCD[intCount].intStart_Min=intMin1;
				gstruct_FriCD[intCount].intEnd_Hr=intHr2; 
				gstruct_FriCD[intCount].intEnd_Min=intMin2;  
				break;
			case 6:
				gstruct_SatCD[intCount].intStart_Hr=intHr1; 
				gstruct_SatCD[intCount].intStart_Min=intMin1; 
				gstruct_SatCD[intCount].intEnd_Hr=intHr2; 
				gstruct_SatCD[intCount].intEnd_Min=intMin2;  
				break;
		}
		intCount++;
		lngGetLen1=strlen(chrOutBuf);//������ƪ���
		lngGetLen2=lngLen-lngGetLen1;//�Ѿl��ƪ���
		if(intCount==1)
		{
			if(lngGetLen2>0)
				strRemain=m_strInData.Mid(lngGetLen1+1,lngGetLen2);//�Ѿl���
			else
				strRemain="";
		}
		else
		{
			if(lngGetLen2>0)
				strRemain=strRemain.Mid(lngGetLen1+1,lngGetLen2);//�Ѿl���
			else
				strRemain="";
		}
		strInData=strRemain;
	}while(intCount<conData_Max);
	gintData_Max[day]=intCount;
}
void CCute_Main_ControlDlg::InitializeXMLMemory()
{
	int i,j;
	gunicode[0] = 0xFF;//��12.8��->Unicode   
	gunicode[1] = 0xFE;//��12.8��->Unicode 
	gblnRunZindex=false;
	GetSpeciallyDay();
	///////////////////////////////////////////////////
	for(i=0;i<conData_Max;i++)
	{
		gstruct_SunCD[i].intEnd_Hr=0;
		gstruct_SunCD[i].intEnd_Min=0; 
		gstruct_SunCD[i].intStart_Hr=0; 
		gstruct_SunCD[i].intStart_Min=0; 
		/////////////////
		gstruct_MonCD[i].intEnd_Hr=0; 
		gstruct_MonCD[i].intEnd_Min=0; 
		gstruct_MonCD[i].intStart_Hr=0; 
		gstruct_MonCD[i].intStart_Min=0;
		////////////////
		gstruct_TueCD[i].intEnd_Hr=0; 
		gstruct_TueCD[i].intEnd_Min=0; 
		gstruct_TueCD[i].intStart_Hr=0; 
		gstruct_TueCD[i].intStart_Min=0;
		/////////////////
		gstruct_WedCD[i].intEnd_Hr=0; 
		gstruct_WedCD[i].intEnd_Min=0; 
		gstruct_WedCD[i].intStart_Hr=0; 
		gstruct_WedCD[i].intStart_Min=0; 
		/////////////////
		gstruct_ThuCD[i].intEnd_Hr=0; 
		gstruct_ThuCD[i].intEnd_Min=0; 
		gstruct_ThuCD[i].intStart_Hr=0; 
		gstruct_ThuCD[i].intStart_Min=0; 
		////////////////
		gstruct_FriCD[i].intEnd_Hr=0; 
		gstruct_FriCD[i].intEnd_Min=0; 
		gstruct_FriCD[i].intStart_Hr=0; 
		gstruct_FriCD[i].intStart_Min=0;
		/////////////////
		gstruct_SatCD[i].intEnd_Hr=0; 
		gstruct_SatCD[i].intEnd_Min=0; 
		gstruct_SatCD[i].intStart_Hr=0; 
		gstruct_SatCD[i].intStart_Min=0; 
	}
	for(j=0;j<7;j++)
		gintData_Max[j]=0;
	Read_Monitor();//----->�ѩ�睊�]���N�n�N�{�����InitializeXMLMemory
	///////////////////////////////////////////////////////////////////////
	char chrbuf[100]="";
	for(i=0;i<CFData_Max;i++)
	{
		gstructCFD[i].intEnd_Hr=0;
		gstructCFD[i].intEnd_Min=0;
		gstructCFD[i].intStart_Hr=0; 
		gstructCFD[i].intStart_Min=0;
		strcpy(gstructCFD[i].chrFormName,chrbuf); 
	}
	Create_ChangeForm();
	////////////////////////////////////////////////////////////////////////
	SetVolume();
	//////////////
	ChangMonitorSize();//��12.8��->�^���P�]�w�ù��ѪR��
}
void CCute_Main_ControlDlg::Detect_Command()//�����O�_���R�O�T��
{
	CString StrFileName;//��13.3�� 
	MSXML2::IXMLDOMDocumentPtr pDoc;
	_variant_t vtStr;
	CString strValue;
	bool blnRead=false;
	int intCommandNumber=-1;
	char chrDataBuf[1000];
	int intcommand=-1;
	int i=0;
	CTime t1=CTime::GetCurrentTime();
	bool blnCommandArray[CommanCount_Max];
	//////////////////////////////////
	//�X�ϩR�O�X�а}�C
	for(i=0;i<CommanCount_Max;i++)
	{
		/*
		00->reload progran
		01->progran stop
		02->progran start
		03->reload setting
		04->movie stop
		05->movie start
		06->�j�� monitor on
		07->�j�� monitor off
		08->normal
		09->GetMonitorPicture
		10->Reset_Computer
		*/
		blnCommandArray[i]=false;
	}
	//////////////////////////////////////
	//Ū���R�O�ɮ�
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   return;
	}
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	CString strFileName1 = gstrCurDrt;
	strFileName1 +="Resources\\Command\\Command.msg"; 
	blnRead=pDoc->load((_bstr_t)strFileName1);
	///////////////////////////////////////////////////////////////
	//��ѩR�O->�é��X�а}�C����
	if(blnRead)
	{
		MSXML2::IXMLDOMNodePtr  Command;
		//�b�𤤴M��`�I,"//"��ܦb���N�@�h�d�� 
		////////////////////////////////////////////////////////////
		Command=pDoc->selectSingleNode("//Command");	
		Command->get_nodeTypedValue(&vtStr);  
		strValue=vtStr.bstrVal;
		strcpy(chrDataBuf,strValue.GetBuffer(0));
		intcommand=atoi(chrDataBuf);
		////////////////////////////////////////////////////////////
		//��11.0�����\��
		if(gblnLogFlag==true)
		{
			CString strTime = t1.Format("%H%M%S"); 
			if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
			{
				//fprintf(gpfControlLog2,"%s,0,Run Command Number (%d)\n",strTime.GetBuffer(0),intcommand);
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,0,Run Command Number (%d)\r\n",strTime.GetBuffer(0),intcommand);//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				//////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog2);//�g��
				////delete [] gpUnicodeDataBuf;//����O����
				////gpUnicodeDataBuf=NULL;//����O����
			}
			else
			{
				//fprintf(gpfControlLog1,"%s,0,Run Command Number (%d)\n",strTime.GetBuffer(0),intcommand);
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,0,Run Command Number (%d)\r\n",strTime.GetBuffer(0),intcommand);//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				//////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog1);//�g��
				////delete [] gpUnicodeDataBuf;//����O����
				////gpUnicodeDataBuf=NULL;//����O����
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////
		for(i=0;i<CommanCount_Max;i++)
		{
			/*
			00->reload progran
			01->progran stop
			02->progran start
			03->reload setting
			04->movie stop
			05->movie start
			06->�j�� monitor on
			07->�j�� monitor off
			08->normal
			09->GetMonitorPicture
			10->Reset_Computer
			*/
			blnCommandArray[i]=(bool)(intcommand &((int)pow(2,i)));
		}
		//////////////////////////////////////////////
		//////�v����,�u�����@��
		if(blnCommandArray[6])//->�j�� monitor on
		{
			Run_Command(8);
		}
		if(blnCommandArray[7])//->�j�� monitor off
		{
			Run_Command(9);
		}
		if(blnCommandArray[8])//->normal
		{
			Run_Command(10);
		}
		////////////////////////////////////////////////
		//�̧ǰ���C���R�O
		for(i=0;i<CommanCount_Max;i++)
		{
			if(blnCommandArray[i])
			{
				switch(i)
				{
					case 0://->reload progran
						gpfUpdateProgram=fopen("UpdateProgram.txt","w");//�}�ҧ�s�{���O����
						gintUpdateProgramCount=0;//��s�{���ƶq�X�Ъ�l��
						StrFileName = gstrCurDrt;//���o�ثe�{�����|
						StrFileName +="Resources\\Data\\ProgUpdate\\";//���ͧ�s�ɩҦb���|
						BrowseUpdateProgram(StrFileName);//�j�M��s��
						fclose(gpfUpdateProgram);//������s�{���O����
						if(gintUpdateProgramCount>0)//�P�_�O�_�n��s�{��
						{
							/////////////////////////////////////////////////////////
							//�O����M�g��l��
							LPVOID mapView[4];
							char ch1[10];
							//for(int i=0;i<4;i++)
							//{
								//mapView[i] = MapViewOfFile( hFileMap[i],FILE_MAP_WRITE, 0, 0, 0 ) ;
							//}
							mapView[0] = MapViewOfFile( hFileMap[0],FILE_MAP_WRITE, 0, 0, 0 ) ;
							//////////////////////////////////////////////////////////
							if( mapView[0] != NULL ) 
							{
								itoa(gintUpdateProgramCount,ch1,10);//�N��s���Ʊq�ƭ��ܦr��
								strcpy((LPTSTR)mapView[0],ch1);//�N���Ƹ�Ƶ��M�g�ܼ�
								UnmapViewOfFile( (LPVOID)mapView[0]);//��s�M�g�ܼ�
								//strcpy((LPTSTR)mapView[1],ch1);//�N���Ƹ�Ƶ��M�g�ܼ�
								//UnmapViewOfFile( (LPVOID)mapView[1]);//��s�M�g�ܼ�
								//strcpy((LPTSTR)mapView[2],ch1);//�N���Ƹ�Ƶ��M�g�ܼ�
								//UnmapViewOfFile( (LPVOID)mapView[2]);//��s�M�g�ܼ�
								//strcpy((LPTSTR)mapView[3],ch1);//�N���Ƹ�Ƶ��M�g�ܼ�
								//UnmapViewOfFile( (LPVOID)mapView[3]);//��s�M�g�ܼ�	
							}
						}
						else
						{
							Run_Command(4);//���Χ�s�{����������reload progran
						}
						break;
					case 1://->progran stop
						Run_Command(3);
						break;
					case 2://->progran start
						Run_Command(2);
						break;
					case 3://->reload setting
						Run_Command(5);
						break;
					case 4://->movie stop
						Run_Command(6);
						break;
					case 5://->movie start
						Run_Command(7);
						break;
					case 6://->�j�� monitor on
						Run_Command(8);
						break;
					case 7://->�j�� monitor off
						Run_Command(9);
						break;
					case 8://->normal
						Run_Command(10);
						break;
					case 9://GetMonitorPicture
						Run_Command(11);
						break;
					case 10://Reset_Computer
						Run_Command(12);
						break;
				}
			}
		}
		DeleteFile(strFileName1);//�R���R�O��
	}
}
void CCute_Main_ControlDlg::Run_Command(int intCommandNumber)
{
	int nLen;
	CString StrFileName;
	CTime t1=CTime::GetCurrentTime();
	switch(intCommandNumber)
	{
	case 0://Monitor_On
		////////////////////////////////////
		//��11.0�����\��
		if(gblnLogFlag==true)
		{
			if(gblnMonitorOnCheck==false)
			{
				CString strTime = t1.Format("%H%M%S"); 
				if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
				{
					//fprintf(gpfControlLog2,"%s,0,Normal Monitor_On\n",strTime.GetBuffer(0));
					//��12.8��->Unicode
					gStr2UnicodeData.Format("%s,0,Normal Monitor_On\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
					gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
					//////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
					MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
					fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog2);//�g��
					////delete [] gpUnicodeDataBuf;//����O����
					////gpUnicodeDataBuf=NULL;//����O����
				}
				else
				{
					//fprintf(gpfControlLog1,"%s,0,Normal Monitor_On\n",strTime.GetBuffer(0));
					//��12.8��->Unicode
					gStr2UnicodeData.Format("%s,0,Normal Monitor_On\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
					gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
					//////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
					MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
					fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog1);//�g��
					////delete [] gpUnicodeDataBuf;//����O����
					////gpUnicodeDataBuf=NULL;//����O����
				}			
				gblnMonitorOnCheck=true;
				gblnMonitorOffCheck=false;
			}
		}
		/////////////////////////////////////
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) -1);//Turnon
		//MessageBox("Monitor_On");
		break;
	case 1://Monitor_Off
		/////////////////////////////////////
		//��11.0�����\��
		if(gblnLogFlag==true)
		{
			CString strTime = t1.Format("%H%M%S"); 
			if(gblnMonitorOffCheck==false)
			{
				if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
				{
					//fprintf(gpfControlLog2,"%s,0,Normal Monitor_Off\n",strTime.GetBuffer(0));
					//��12.8��->Unicode
					gStr2UnicodeData.Format("%s,0,Normal Monitor_Off\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
					gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
					//////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
					MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
					fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog2);//�g��
					////delete [] gpUnicodeDataBuf;//����O����
					////gpUnicodeDataBuf=NULL;//����O����					
				}
				else
				{
					//fprintf(gpfControlLog1,"%s,0,Normal Monitor_Off\n",strTime.GetBuffer(0));
					//��12.8��->Unicode
					gStr2UnicodeData.Format("%s,0,Normal Monitor_Off\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
					gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
					////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
					MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
					fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog1);//�g��
					//delete [] gpUnicodeDataBuf;//����O����
					//gpUnicodeDataBuf=NULL;//����O����
				}
				gblnMonitorOnCheck=false;
				gblnMonitorOffCheck=true;
			}
		}
		//////////////////////////////////////
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);//Turnoff
		//MessageBox("Monitor_Off");
		break;
	case 2://Start_Program
		Start_Program();
		break;
	case 3://Stop_Program
		Stop_Program();
		nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
		if( gstrCurDrt[nLen]!='\\' )
		{
			gstrCurDrt[nLen++] = '\\';
			gstrCurDrt[nLen] = '\0';
		}
		gpfUpdateProgram=fopen("UpdateProgram.txt","w");//�}�ҧ�s�{���O����
		gintUpdateProgramCount=0;//��s�{���ƶq�X�Ъ�l��
		StrFileName = gstrCurDrt;//���o�ثe�{�����|
		StrFileName +="Resources\\Data\\ProgUpdate\\";//���ͧ�s�ɩҦb���|
		BrowseUpdateProgram(StrFileName);//�j�M��s��
		fclose(gpfUpdateProgram);//������s�{���O����
		if(gintUpdateProgramCount>0)//�P�_�O�_�n��s�{��
		{
			/////////////////////////////////////////////////////////
			//�O����M�g��l��
			LPVOID mapView[4];
			char ch1[10];
			//for(int i=0;i<4;i++)
			//{
				//mapView[i] = MapViewOfFile( hFileMap[i],FILE_MAP_WRITE, 0, 0, 0 ) ;
			//}
			mapView[0] = MapViewOfFile( hFileMap[0],FILE_MAP_WRITE, 0, 0, 0 ) ;
			//////////////////////////////////////////////////////////
			if( mapView[0] != NULL ) 
			{
				itoa(gintUpdateProgramCount,ch1,10);//�N��s���Ʊq�ƭ��ܦr��
				strcpy((LPTSTR)mapView[0],ch1);//�N���Ƹ�Ƶ��M�g�ܼ�
				UnmapViewOfFile( (LPVOID)mapView[0]);//��s�M�g�ܼ�
				//strcpy((LPTSTR)mapView[1],ch1);//�N���Ƹ�Ƶ��M�g�ܼ�
				//UnmapViewOfFile( (LPVOID)mapView[1]);//��s�M�g�ܼ�
				//strcpy((LPTSTR)mapView[2],ch1);//�N���Ƹ�Ƶ��M�g�ܼ�
				//UnmapViewOfFile( (LPVOID)mapView[2]);//��s�M�g�ܼ�
				//strcpy((LPTSTR)mapView[3],ch1);//�N���Ƹ�Ƶ��M�g�ܼ�
				//UnmapViewOfFile( (LPVOID)mapView[3]);//��s�M�g�ܼ�	
			}
		}
		break;
	case 4://Reload_Program
		CWnd* hWnd1;
		hWnd1=FindWindow(NULL, "�������Ϻ� (E:)");
		if(hWnd1!=NULL)
		{
			hWnd1->SendMessage(WM_CLOSE,0,0);
			/*
			ShowWindow(SW_SHOWNORMAL);
			POINT lpPoint; 
			GetCursorPos(&lpPoint);
			SetCursorPos(10,5); 
			mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
			mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
			*/
		}
		Stop_Program();
		InitializeXMLMemory();
		GetProgramInfo();
		Start_Program();
		Sleep(10000);//��11.2�����\��A���C�t�ήį�
		break;
	case 5://Reload_Setting
		InitializeXMLMemory();
		break;
	case 6://Movie_Stop
		OnlyControlMovie(false);
		break;
	case 7://Movie_Start
		OnlyControlMovie(true);
		break;
	case 8://�j��Monitor_On
		m_MainMonitor_On=true;
		m_MainMonitor_Off=false;
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) -1);//Turnon
		break;
	case 9://�j��Monitor_Off
		m_MainMonitor_On=false;
		m_MainMonitor_Off=true;
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);//Turnoff
		break;
	case 10://Normal
		m_MainMonitor_On=false;
		m_MainMonitor_Off=false;
		break;
	case 11://GetMonitorPicture
		GetMonitorPicture();
		break;
	case 12://Reset_Computer
		Reset_Computer();
		break;
	}
}
void CCute_Main_ControlDlg::Start_Program()
{
	CWnd* hWnd0;
	CString StrName,StrCaption;
	CString StrVersion;
	HINSTANCE result;
	CTime t1=CTime::GetCurrentTime();
	KillTimer(1);//��12.1���A���F����{���Q���ƱҰ�
	//////////////////////////////////////////////////////////
	//�̧Ǩ��X�{���W�٩M���D�A�çP�_�O�_�Ͱ���A�Y�L����h����
	int i;
	int j,k;
	for(i=0;i<gintProgramNumber;i++)
	{
		j=gintProgramZindex[i][0];//�{���s���A��12.1��
		k=gintProgramZindex[i][1];//��12.1��
		StrName=gstructPD[j].StrName+".exe"; 
		StrCaption=gstructPD[j].StrCaption;
		hWnd0=NULL;
		hWnd0 = FindWindow(NULL, StrCaption.GetBuffer(0));
		if(hWnd0==NULL)
		{
			/*
			if(StrName=="chtvSignage_Player.exe")
			{
				ShowWindow(SW_SHOWNORMAL);
				POINT lpPoint; 
				GetCursorPos(&lpPoint);
				SetCursorPos(10,5); 
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
			}
			*/		
			result=ShellExecute(NULL,"open",StrName.GetBuffer(0),NULL,NULL,SW_SHOWNORMAL);
			if((int)result>32)//��11.0�����\��
			{
				StrVersion="";//��13.7��->�d�ߵ{������
				StrVersion=GetProgramVersion(StrName);//��13.7��->�d�ߵ{������
				///////////////////////////////////////////////////////////////////////
				gblnRunZindex=true;//��12.2����
				///////////////////////////////////////////////////////////////////////
				CString strTime = t1.Format("%H%M%S"); 
				if(gblnLogFlag==true)
				{
					if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
					{
						//fprintf(gpfControlLog2,"%s,0,Start program OK->%s\n",strTime.GetBuffer(0),StrName.GetBuffer(0));
						//��12.8��->Unicode
						gStr2UnicodeData.Format("%s,0,Start program OK->%s %s\r\n",strTime.GetBuffer(0),StrName.GetBuffer(0),StrVersion.GetBuffer(0));//���ͭn�g�J��� 
						gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
						////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
						MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
						fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog2);//�g��
						//delete [] gpUnicodeDataBuf;//����O����
						//gpUnicodeDataBuf=NULL;//����O����
					}
					else
					{
						//fprintf(gpfControlLog1,"%s,0,Start program OK->%s\n",strTime.GetBuffer(0),StrName.GetBuffer(0));
						//��12.8��->Unicode
						gStr2UnicodeData.Format("%s,0,Start program OK->%s %s\r\n",strTime.GetBuffer(0),StrName.GetBuffer(0),StrVersion.GetBuffer(0));//���ͭn�g�J��� 
						gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
						////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
						MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
						fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog1);//�g��
						//delete [] gpUnicodeDataBuf;//����O����
						//gpUnicodeDataBuf=NULL;//����O����
					}
				}
			}
			else
			{
				CString strTime = t1.Format("%H%M%S"); 
				if(gblnErrFlag==true)
				{
					if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
					{
						//fprintf(gpfControlError2,"%s,9,Not Create program->%s\n",strTime.GetBuffer(0),StrName.GetBuffer(0));
						//��12.8��->Unicode
						gStr2UnicodeData.Format("%s,9,Not Create program->%s\r\n",strTime.GetBuffer(0),StrName.GetBuffer(0));//���ͭn�g�J��� 
						gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
						////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
						MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
						fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError2);//�g��
						gblnGetError=true;//��13.2��
						//delete [] gpUnicodeDataBuf;//����O����
						//gpUnicodeDataBuf=NULL;//����O����
					}
					else
					{
						//fprintf(gpfControlError1,"%s,9,Not Create program->%s\n",strTime.GetBuffer(0),StrName.GetBuffer(0));
						//��12.8��->Unicode
						gStr2UnicodeData.Format("%s,9,Not Create program->%s\r\n",strTime.GetBuffer(0),StrName.GetBuffer(0));//���ͭn�g�J��� 
						gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
						////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
						MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
						fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError1);//�g��
						gblnGetError=true;//��13.2��
						//delete [] gpUnicodeDataBuf;//����O����
						//gpUnicodeDataBuf=NULL;//����O����
					}
				}
			}
		}
		//else//��11.2�����\��A�����H���Ч�s�ӵL�k��ܦb�W�h
		//{
		if(gblnRunZindex)
		{
			hWnd0=NULL;
			do
			{
				hWnd0 = FindWindow(NULL, StrCaption.GetBuffer(0));
			}while(hWnd0==NULL);
			gblnRunZindex=false;
			if(k<1000)
			{
				bool blnget=false;
				this->ShowWindow(SW_SHOWNORMAL);
				::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
				POINT lpPoint; 
				GetCursorPos(&lpPoint);
				SetCursorPos(10,5); 
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
				do
				{
					blnget=::SetWindowPos(hWnd0->m_hWnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
					Sleep(1000);
				}while(blnget==false);
			}
		}
		//}
		
	}
	//////////////////////////////////////////////////////////////////////////////////
	//MessageBox("Start_Program");
	this->ShowWindow(SW_MINIMIZE);
	::SetCursorPos((1920+(200/2)),(1080+(200/2)));  //�t�����ô��
	SetTimer(1,10000,NULL);//��12.1���A���F����{���Q���ƱҰ�
}
void CCute_Main_ControlDlg::Stop_Program()
{
	//MessageBox("Stop_Program");
	CWnd* hWnd[PDData_Max];
	int i;
	CString StrCaption;
	///////////////////////////////////////////////////////////////////
	//�̧Ǩ��X�{���W�٩M���D�A�çP�_�O�_�Ͱ���A�Y������h����
	for(i=0;i<gintProgramNumber;i++)
	{
		StrCaption=gstructPD[i].StrCaption;
		if(StrCaption!="chtvSignage_Communication")//�T���Communication
		{
			hWnd[i]= FindWindow(NULL,StrCaption.GetBuffer(0));
			if(hWnd[i]!=NULL)
				hWnd[i]->SendMessage(WM_CLOSE,0,0);
		}
	}
	//////////////////////////////////////////////////////////////////////
	gblnRunZindex=false;//��12.2����
}

void CCute_Main_ControlDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

BOOL CCute_Main_ControlDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd* hWnd[PDData_Max];
	int i;
	CString StrCaption;
	CTime t1=CTime::GetCurrentTime();
	CString strFileName1;//��13.2��
	CString DeleteFileName;//��13.2��
	///////////////////////////////////////////////////////////////////
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	strFileName1 = gstrCurDrt;
	strFileName1 +="Resources\\Export_Data\\Main\\";
	///////////////////////////////////////////////////////////////////
	//�̧Ǩ��X�{���W�٩M���D�A�çP�_�O�_�Ͱ���A�Y������h����
	for(i=0;i<gintProgramNumber;i++)
	{
		StrCaption=gstructPD[i].StrCaption;
		hWnd[i]= FindWindow(NULL,StrCaption.GetBuffer(0));
		if(hWnd[i]!=NULL)
			hWnd[i]->SendMessage(WM_CLOSE,0,0);
	}
	//////////////////////////////////////////////////////////////////////
	//��11.0�����\��
	if(gblnLogFlag==true)//1�����ɥ��}����,0���n�O��
	{
		CString strTime = t1.Format("%H%M%S"); 
		if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
		{
			//fprintf(gpfControlLog2,"%s,0,End time\n",strTime.GetBuffer(0));
			//��12.8��->Unicode
			gStr2UnicodeData.Format("%s,0,End time\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
			gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
			////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
			MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
			fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog2);//�g��
			//delete [] gpUnicodeDataBuf;//����O����
			//gpUnicodeDataBuf=NULL;//����O����
		}
		else
		{
			//fprintf(gpfControlLog1,"%s,0,End time\n",strTime.GetBuffer(0));
			//��12.8��->Unicode
			gStr2UnicodeData.Format("%s,0,End time\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
			gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
			////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
			MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
			fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog1);//�g��
			//delete [] gpUnicodeDataBuf;//����O����
			//gpUnicodeDataBuf=NULL;//����O����
		}
		if(gpfControlError1!=NULL)
		{
			fclose(gpfControlError1);
			if(gblnGetError!=true)
			{
				DeleteFileName=strFileName1;
				DeleteFileName+=gStrYesterday+"err";
				DeleteFileName+=".log";
				DeleteFile(DeleteFileName);
			}
		}
		if(gpfControlError2!=NULL)
		{
			fclose(gpfControlError2);
			if(gblnGetError!=true)
			{
				DeleteFileName=strFileName1;
				DeleteFileName+=gStrYesterday+"err";
				DeleteFileName+=".log";
				DeleteFile(DeleteFileName);
			}
		}
		if(gpfControlLog1!=NULL)
		{
			fclose(gpfControlLog1);
		}
		if(gpfControlLog2!=NULL)
		{
			fclose(gpfControlLog2);
		}
	}
	//////////////////////////////////////////////////////////////////////
	ClipCursor(NULL);//��12.1��->�Ѱ����w�ƹ����ʰϰ�
	return CDialog::DestroyWindow();
}

bool CCute_Main_ControlDlg::Read_ChangeForm()
{
	gblnChangeForm=false;
	int i;
	char chrbuf[100]="";
	CString StrFindTag="//s";
	CString StrBuf[3];
	bool blnRead=false;
	//int hr,min;
	///////////////////////////////////
	//Ū���~���
	CTime t1=CTime::GetCurrentTime();
	int Year=t1.GetYear();//�~
	int Month=t1.GetMonth(); //��
	int Day=t1.GetDay();//��
	////////////////////////////////////////////////
	//�X���j�M����
	StrBuf[0].Format("%d",Year); 
	StrBuf[1].Format("%d",Month);
	if(StrBuf[1].GetLength()==1)
		StrBuf[1]="0"+StrBuf[1];
	StrBuf[2].Format("%d",Day);
	if(StrBuf[2].GetLength()==1)
		StrBuf[2]="0"+StrBuf[2];
	StrFindTag+=StrBuf[0]+StrBuf[1]+StrBuf[2];
	///////////////////////////////////////////////////
	//Ū�����J�]�w��
	_variant_t vtStr;
	CString strValue;
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hre = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hre))
	{
	   return false;
	}
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	CString strFileName1 = gstrCurDrt;
	strFileName1 +="Resources\\Setting\\changeform.dat";
	blnRead=pDoc->load((_bstr_t)strFileName1);
	if(blnRead)
	{
		//pDoc->load("changeform.dat"); 
		////////////////////////////////////////////////////////////////
		//�j�M�������
		MSXML2::IXMLDOMNodePtr  pNode;
		//�b�𤤬d��W��Book���`�I,"//"��ܦb���N�@�h�d�� 
		pNode=pDoc->selectSingleNode((_bstr_t)StrFindTag);
		//pNode=pDoc->selectSingleNode("//s20080310");
		if(pNode!=NULL)
		{
			//////////////////////////////////////////
			//��l���ܼ�
			for(i=0;i<CFData_Max;i++)
			{
				gstructCFD[i].intEnd_Hr=0;
				gstructCFD[i].intEnd_Min=0;
				gstructCFD[i].intStart_Hr=0; 
				gstructCFD[i].intStart_Min=0;
				strcpy(gstructCFD[i].chrFormName,chrbuf); 
			}
			gintCFDnumber=0;
			//////////////////////////////////////////////
			//���oXML��
			pNode->get_nodeTypedValue(&vtStr);
			strValue=vtStr.bstrVal;
			/////////////////////////////////////////////////
			ChangeFormRipData(strValue);//��Ѹ�Ʃ����w���ܼƤ�
			return true;
		}
		else
		{
			return false;
		}
		///////////////////////////////////////////////
	}
	else
	{
		//��11.0�����\��
		if(gblnErrFlag==true)
		{
			CString strTime = t1.Format("%H:%M:%S");
			if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
			{
				//fprintf(gpfControlError2,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError2);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
			else
			{
				//fprintf(gpfControlError1,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError1);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
		}
		return false;
	}
}

void CCute_Main_ControlDlg::Create_ChangeForm()
{
	bool blnRead=false;
	CTime t1=CTime::GetCurrentTime();
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   return;
	}
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	CString strFileName1 = gstrCurDrt;
	strFileName1 +="Resources\\Setting\\SignageConfig.xml";
	blnRead=pDoc->load((_bstr_t)strFileName1); 
	//pDoc->load("SignageConfig.xml");
	if(blnRead)
	{
		MSXML2::IXMLDOMNodePtr  pNode;
 
		//�b�𤤬d��W��Book���`�I,"//"��ܦb���N�@�h�d�� 
		pNode=pDoc->selectSingleNode("//changeform");
		if(pNode!=NULL)
		{
			_bstr_t bstrData;
			CString StrData;
			CFile file1;
			bstrData=pNode->Getxml();
			StrData=(LPCSTR)bstrData;
			strFileName1 = gstrCurDrt;
			strFileName1 +="Resources\\Setting\\changeform.dat";
			file1.Open(strFileName1.GetBuffer(0),CFile::modeCreate|CFile::modeWrite);
			file1.Write( StrData.GetBuffer(0),StrData.GetLength());
			file1.Close(); 
		}
	}
	else
	{
		//��11.0�����\��
		if(gblnErrFlag==true)
		{
			CString strTime = t1.Format("%H%M%S"); 
			if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
			{
				//fprintf(gpfControlError2,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError2);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����				
			}
			else
			{
				//fprintf(gpfControlError1,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError1);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
		}
	}
}

void CCute_Main_ControlDlg::ChangeFormRipData(CString Datainput)
{
	CString StrIP="";
	CString StrBuf="";
	char *chrInBuf;//�إ߼Ȧs��J��ƫ���
	char *chrOutBuf;//�إ߼Ȧs��X���θ�ƫ���
	long lngLen=0;//�إߪ��׼Ȧs�ܼ�
	long lngGetLen1=0;//������ƪ���
	long lngGetLen2=0;//�Ѿl��ƪ���
	CString m_strInData="";//�D
	CString strInData="";//m_strInData����
	CString strRemain="";//�Ѿl���
	char chrSeps[]=";";//�إߤ��βŸ�
	chrInBuf=new char('\0');//���Ъ�l��
	chrOutBuf=new char('\0');//���Ъ�l��
	bool blnLen=false;//�P�_���׬O�_��0
	int intCount=0;//�����ĴX�����
	////////////////////////////////////////
	char chrxmldata[100];
	int intHr1,intMin1,intHr2,intMin2;
	m_strInData=Datainput;
	strInData=m_strInData;//���X��Ӹ��
	do
	{
		chrInBuf=strInData.GetBuffer(0);//�ᤩ���
		lngLen=strlen(chrInBuf);
		if(lngLen<= 0)//�����̫�@����ƴ���ҳy���~�P
		{
			blnLen=true;
			break;
		}
		chrOutBuf=strtok(chrInBuf,chrSeps);//�^�������
		//////////////////////////////////////////////////////////////////////////////////////////
		//���R
		sscanf(chrOutBuf,"%d:%d-%d:%d-%s",&intHr1,&intMin1,&intHr2,&intMin2,chrxmldata);
		gstructCFD[intCount].intEnd_Hr=intHr2;
		gstructCFD[intCount].intEnd_Min=intMin2;
		gstructCFD[intCount].intStart_Hr=intHr1; 
		gstructCFD[intCount].intStart_Min=intMin1;
		//////////////////////////////////////////////////////////////////////////////////////////
		strcpy(gstructCFD[intCount].chrFormName,chrxmldata); 		
		intCount++;
		lngGetLen1=strlen(chrOutBuf);//������ƪ���
		lngGetLen2=lngLen-lngGetLen1;//�Ѿl��ƪ���
		if(intCount==1)
		{
			if(lngGetLen2>0)
				strRemain=m_strInData.Mid(lngGetLen1+1,lngGetLen2);//�Ѿl���
			else
				strRemain="";
		}
		else
		{
			if(lngGetLen2>0)
				strRemain=strRemain.Mid(lngGetLen1+1,lngGetLen2);//�Ѿl���
			else
				strRemain="";
		}
		strInData=strRemain;
	}while(intCount<CFData_Max);
	gintCFDnumber=intCount;
}

void CCute_Main_ControlDlg::GetProgramInfo()
{
	int i,j;
	int k,l;
	CString StrBuf="";
	gintProgramNumber=0;
	MSXML2::IXMLDOMDocumentPtr pDoc;
	CTime t1=CTime::GetCurrentTime();
	bool blnRead=false;
	///////////////////////////////////////////////////////////////////
	gblnRunZindex=false;//��12.2����
	///////////////////////////////////////////////////////////////////
	//�ܼƪ�l��
	for(i=0;i<PDData_Max;i++)
	{
		gstructPD[i].StrCaption="";
		gstructPD[i].StrName=""; 
		gintProgramZindex[i][0]=0;//��12.1����------------------>�x�s��ܼh��,ID
		gintProgramZindex[i][1]=0;;//��12.1����------------------>�x�s��ܼh��,Z
	}
	//////////////////////////////////////////////////////////////////
	//���J�]�w��
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   return;
	}
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	CString strFileName1 = gstrCurDrt;
	strFileName1 +="Resources\\Setting\\SignageConfig.xml";
	blnRead=pDoc->load((_bstr_t)strFileName1); 
	///////////////////////////////////////////////////////////////
	if(blnRead)
	{
		//pDoc->load("SignageConfig.xml");
		MSXML2::IXMLDOMNodePtr pNodeRoot;
		MSXML2::IXMLDOMNodeListPtr  pNodeList;
		MSXML2::IXMLDOMNodePtr   pNode;
 		MSXML2::IXMLDOMNamedNodeMapPtr pAttrMap=NULL;
		MSXML2::IXMLDOMNodePtr   pAttrItem;
		MSXML2::IXMLDOMNodePtr   pAttrItem_0;
		_variant_t variantValue_0;
		_variant_t variantValue;
		MSXML2::IXMLDOMDocumentPtr   pxmldom1;
		MSXML2::IXMLDOMNodeListPtr  pNodeList1;
		MSXML2::IXMLDOMNodePtr   pNode1;
 		MSXML2::IXMLDOMNamedNodeMapPtr pAttrMap1=NULL;
		MSXML2::IXMLDOMNodePtr   pAttrItem1;
		_variant_t variantValue1;
		//////////////////////////////////////////////////
		MSXML2::IXMLDOMNodeListPtr  pNodeList3;
		MSXML2::IXMLDOMNodePtr   pNode3;
 		MSXML2::IXMLDOMNamedNodeMapPtr pAttrMap3=NULL;
		MSXML2::IXMLDOMNodePtr   pAttrItem2;
		_variant_t variantValue3;
		CString StrZindex;
		char *charZbuf;
		int m;
		///////////////////////////////////////////////////
		//�b�𤤬d��W��Book���`�I,"//"��ܦb���N�@�h�d��
		///////////////////////////////////////////////////////
		//��M�{����Ƽ���
		pNodeRoot=pDoc->selectSingleNode("//startPrograms");
		pNodeRoot->get_childNodes(&pNodeList);
		j=pNodeList->length;
		////////////////////////////////////////////////////////
		//�̧Ǩ��X�l�`�I
		for(i=0;i<j;i++)
		{
			CString StrData;
			pNode=pNodeList->item[i];
			pNode->get_attributes(&pAttrMap);
			pAttrMap->get_item(0,&pAttrItem_0);
			//pAttrMap->get_item(1,&pAttrItem);
			//���o�`�I����
			pAttrItem_0->get_nodeTypedValue(&variantValue_0);
			//pAttrItem->get_nodeTypedValue(&variantValue);
			StrBuf=(char *)pNode->GetnodeName();;
			StrData=(char *)(_bstr_t)variantValue_0;
			////////////////////////////////////////////////////////////
			//�P�_�O�_��TRUE
			StrData.MakeLower();//��13.2��->���b������p�g 
			if(StrData=="true")
			{
				_bstr_t bt1;
				gStrNowStyle=StrBuf;
				bt1=pNode->Getxml();
				hr = pxmldom1.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				pxmldom1->loadXML(bt1);
				pNodeList1=pxmldom1->selectNodes("//program");
				l=pNodeList1->length;
				gintProgramNumber=l;
				//////////////////////////////////////////////////////////
				//�⬰TRUE����Ʃ���ܼ�
				for(k=0;k<l;k++)
				{
					pNode1=pNodeList1->item[k];
					pNode1->get_attributes(&pAttrMap1);
					pAttrMap1->get_item(0,&pAttrItem1);
					//���o�`�I����
					pAttrItem1->get_nodeTypedValue(&variantValue1);
					gstructPD[k].StrName=(char *)(_bstr_t)variantValue1;
					//////////////////////////////////////////////////
					MSXML2::IXMLDOMDocumentPtr   pxmldom2;
					MSXML2::IXMLDOMNodePtr   pNode2;
					_bstr_t bt2;
					bt2=pNode1->Getxml();
					hr = pxmldom2.CreateInstance(__uuidof(MSXML2::DOMDocument30));
					pxmldom2->loadXML(bt2);
					pNode2=pxmldom2->selectSingleNode("//formname");
					_variant_t vtStr;
					pNode2->get_nodeTypedValue(&vtStr);  
					gstructPD[k].StrCaption=vtStr.bstrVal; 	
					//////////////////////////////////////////
					gintProgramZindex[k][0]=k;//��12.1����------------------>�x�s��ܼh��,ID
					pNodeList3=pxmldom2->selectNodes("//zindex");
					m=pNodeList3->length;
					if(m>0)
					{
						pNode3=pNodeList3->item[0];
						pNode3->get_nodeTypedValue(&variantValue3); 
						StrZindex=variantValue3.bstrVal;
						charZbuf=StrZindex.GetBuffer(0);
						gintProgramZindex[k][1]=atoi(charZbuf);//��12.1����------------------>�x�s��ܼh��,Z
					}
					else
					{
						gintProgramZindex[k][1]=1000;;//��12.1����------------------>�x�s��ܼh��,Z
						//Z��,�V�p�V�W�h
					}
				}
				///////////////////////////////////////////////////////////////
				BoBoProgramZindex(gintProgramZindex,gintProgramNumber);
				break;//����I�j��
			}
			///////////////////////////////////////////////////////////////////
		}
		///////////////////////////////////////////////////////////////////////
	}
	else
	{
		//��11.0�����\��
		if(gblnErrFlag==true)
		{
			CString strTime = t1.Format("%H%M%S"); 
			if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
			{
				//fprintf(gpfControlError2,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError2);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����				
			}
			else
			{
				//fprintf(gpfControlError1,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError1);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
		}
	}
}

void CCute_Main_ControlDlg::ChangeStyle(CString StrStyleName)
{
	int i,j;
	CString StrBuf="";
	VARIANT varString;
	CTime t1=CTime::GetCurrentTime();
	bool blnRead=false;
	///////////////////////////////////////////////////////////////////////
	//���J�]�w��
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   return;
	}
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	CString strFileName1 = gstrCurDrt;
	strFileName1 +="Resources\\Setting\\SignageConfig.xml";
	blnRead=pDoc->load((_bstr_t)strFileName1);
	if(blnRead)
	{
		////////////////////////////////////////////////////////////////////////
		//pDoc->load("SignageConfig.xml");
		MSXML2::IXMLDOMNodePtr pNodeRoot;
		MSXML2::IXMLDOMNodeListPtr  pNodeList;
		MSXML2::IXMLDOMNodePtr   pNode;
 		MSXML2::IXMLDOMNamedNodeMapPtr pAttrMap=NULL;
		MSXML2::IXMLDOMNodePtr   pAttrItem;
		MSXML2::IXMLDOMNodePtr   pAttrItem_0;
		_variant_t variantValue_0;
		_variant_t variantValue;
		//�b�𤤬d��W��Book���`�I,"//"��ܦb���N�@�h�d�� 
		////////////////////////////////////////////////////
		//��M�`�I
		pNodeRoot=pDoc->selectSingleNode("//startPrograms");
		pNodeRoot->get_childNodes(&pNodeList);
		j=pNodeList->length;
		/////////////////////////////////////////////////////
		//�̧Ǩ��X�U�l�`�I�ȡA�ק�T�{
		for(i=0;i<j;i++)
		{
			CString StrData;
			pNode=pNodeList->item[i];
			pNode->get_attributes(&pAttrMap);
			pAttrMap->get_item(0,&pAttrItem_0);
			//pAttrMap->get_item(1,&pAttrItem);
			//���o�`�I����
			pAttrItem_0->get_nodeTypedValue(&variantValue_0);
			//pAttrItem->get_nodeTypedValue(&variantValue);
			StrBuf=(char *)pNode->GetnodeName();;
			StrData=(char *)(_bstr_t)variantValue_0;
			if(StrBuf==StrStyleName)
			{
				StrData="true";
			}
			else
			{
				StrData="false";
			}
			variantValue=(_bstr_t)StrData;
			pAttrItem->put_nodeTypedValue(variantValue);
		}
		//////////////////////////////////////////////////////
		//��11.0�����\��
		if(gblnLogFlag==true)
		{
			CString strTime = t1.Format("%H%M%S"); 
			if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
			{
				//fprintf(gpfControlLog2,"%s,0,ChangeStyle->%s\n",strTime.GetBuffer(0),StrStyleName.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,0,ChangeStyle->%s\r\n",strTime.GetBuffer(0),StrStyleName.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog2);//�g��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
			else
			{
				//fprintf(gpfControlLog1,"%s,0,ChangeStyle->%s\n",strTime.GetBuffer(0),StrStyleName.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,0,ChangeStyle->%s\r\n",strTime.GetBuffer(0),StrStyleName.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog1);//�g��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
		}
		//////////////////////////////////////////////////////
		//�x�s�ק�
		varString.bstrVal = strFileName1.AllocSysString ();
		pDoc->save(varString);
	}
	else
	{
		if(gblnErrFlag==true)
		{
			CString strTime = t1.Format("%H:%M:%S");
			if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
			{
				//fprintf(gpfControlError2,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError2);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
			else
			{
				//fprintf(gpfControlError1,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError1);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
		}
	}
}

void CCute_Main_ControlDlg::OnlyControlMovie(bool blnflag)
{
	CWnd* hWnd0;
	CString StrName,StrCaption;
	int i;
	if(blnflag)//�}��
	{
		//////////////////////////////////////////////////////////
		//�̧Ǩ��X�{���W�٩M���D�A�çP�_frmPlayer�O�_�Ͱ���A�Y�L����h����
		for(i=0;i<gintProgramNumber;i++)
		{
			StrName=gstructPD[i].StrName+".exe"; 
			StrCaption=gstructPD[i].StrCaption;
			if(StrCaption=="frmPlayer")
			{
				hWnd0=NULL;
				hWnd0 = FindWindow(NULL, StrCaption.GetBuffer(0));
				if(hWnd0==NULL)
					ShellExecute(NULL,"open",StrName.GetBuffer(0),NULL,NULL,SW_SHOWNORMAL);
				break;
			}
		}
		//////////////////////////////////////////////////////////////////////////////////
	}
	else//����
	{
		///////////////////////////////////////////////////////////////////
		//�̧Ǩ��X�{���W�٩M���D�A�çP�_�O�_�Ͱ���A�Y������h����
		for(i=0;i<gintProgramNumber;i++)
		{
			StrCaption=gstructPD[i].StrCaption;
			if(StrCaption=="frmPlayer")
			{
				hWnd0=NULL;
				hWnd0= FindWindow(NULL,StrCaption.GetBuffer(0));
				if(hWnd0!=NULL)
					hWnd0->SendMessage(WM_CLOSE,0,0);
				break;
			}
		}
		//////////////////////////////////////////////////////////////////////
	}
}

void CCute_Main_ControlDlg::GetMonitorPicture()
{
	CDibSection dib1;
	CDC dc1;
	CString strFileName1;
	CString strFileName2;
	CString strFileName3;
	CString Strbuf;
	/////////////////////////////////////////////////////////////////////////
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	/////////////////////////////////////////////////////////////////////////
	strFileName1=gstrCurDrt;
	strFileName2=gstrCurDrt;
	strFileName1+="Resources\\Export_Data\\NowMonitorPicture.bmp";
	strFileName2+="Resources\\Export_Data\\";
	/////////////////////////////////////////////////////////////////////////
	dc1.CreateDC ("DISPLAY",NULL,NULL,NULL);
	int Width=GetSystemMetrics(SM_CXSCREEN);
	int Height=GetSystemMetrics(SM_CYSCREEN);
	dib1.Create(Width,Height,24);
	BitBlt(CDibDC(dib1), 0, 0, Width, Width, dc1, 0, 0, SRCCOPY);
	dib1.SaveBmp(strFileName1.GetBuffer(0));
	///////////////////////////////////////////////////////////////////////////
	m_JPG.SetBmpFile(strFileName1.GetBuffer(0));
	m_JPG.SetQuality((long)95);
	CTime t1=CTime::GetCurrentTime();
	//strFileName3.Format("%d%d%d%d%d%d.jpg",t1.GetYear(),t1.GetMonth(),t1.GetDay(),t1.GetHour(),t1.GetMinute(),t1.GetSecond());
	strFileName3.Format("%d",t1.GetYear());
	///////////////////////////////////////////////////////////////////////////
	Strbuf="";
	if(t1.GetMonth()<10)
	{
		Strbuf.Format("0%d",t1.GetMonth()); 
	}
	else
	{
		Strbuf.Format("%d",t1.GetMonth());
	}
	strFileName3+=Strbuf;
	///////////////////////////////////////
	Strbuf="";
	if(t1.GetDay()<10)
	{
		Strbuf.Format("0%d",t1.GetDay()); 
	}
	else
	{
		Strbuf.Format("%d",t1.GetDay());
	}
	strFileName3+=Strbuf;
	///////////////////////////////////////
	Strbuf="";
	if(t1.GetHour()<10)
	{
		Strbuf.Format("0%d",t1.GetHour()); 
	}
	else
	{
		Strbuf.Format("%d",t1.GetHour());
	}
	strFileName3+=Strbuf;
	///////////////////////////////////////
	Strbuf="";
	if(t1.GetMinute()<10)
	{
		Strbuf.Format("0%d",t1.GetMinute()); 
	}
	else
	{
		Strbuf.Format("%d",t1.GetMinute());
	}
	strFileName3+=Strbuf;
	///////////////////////////////////////
	Strbuf="";
	if(t1.GetSecond()<10)
	{
		Strbuf.Format("0%d",t1.GetSecond()); 
	}
	else
	{
		Strbuf.Format("%d",t1.GetSecond());
	}
	strFileName3+=Strbuf;
	////////////////////////////////////////////////////////////////////////////
	strFileName2+=strFileName3;
	strFileName2+=".jpg";
	m_JPG.BmpToJPG(strFileName2.GetBuffer(0));	
	//////////////////////////////////////////////////////////////////////////////
}

void CCute_Main_ControlDlg::GetSpeciallyDay()
{
	int i,j;
	CString StrBuf="";
	gintSpdayCount=0;
	MSXML2::IXMLDOMDocumentPtr pDoc;
	CTime t1=CTime::GetCurrentTime();
	bool blnRead=false;
	///////////////////////////////////////////////////////////////////
	//�ܼƪ�l��
	for(i=0;i<Spday_Max;i++)
	{
		gStrSpday[i]="";
	}
	//////////////////////////////////////////////////////////////////
	//���J�]�w��
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   return;
	}
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	CString strFileName1 = gstrCurDrt;
	strFileName1 +="Resources\\Setting\\SignageConfig.xml";
	blnRead=pDoc->load((_bstr_t)strFileName1);
	if(blnRead)
	{
		/////////////////////////////////////////////////////////////////////
		MSXML2::IXMLDOMNodePtr pNodeRoot;
		MSXML2::IXMLDOMNodeListPtr  pNodeList;
		MSXML2::IXMLDOMNodePtr   pNode;
		_variant_t vtStr;
		/////////////////////////////////////////////////////////////////////
		pNodeRoot=pDoc->selectSingleNode("//spday");
		pNodeRoot->get_childNodes(&pNodeList);
		j=pNodeList->length;
		gintSpdayCount=j;
		////////////////////////////////////////////////////////
		//�̧Ǩ��X�l�`�I����
		for(i=0;i<j;i++)
		{
			CString StrData;
			pNode=pNodeList->item[i];
			pNode->get_nodeTypedValue(&vtStr);  
			gStrSpday[i]=vtStr.bstrVal;
		}
	}
	else
	{
		//��11.0�����\��
		if(gblnErrFlag==true)
		{
			CString strTime = t1.Format("%H%M%S"); 
			if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
			{
				//fprintf(gpfControlError2,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError2);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
			else
			{
				//fprintf(gpfControlError1,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError1);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
		}
	}
}

void CCute_Main_ControlDlg::CreateCommunication()
{
	HINSTANCE result;
	CWnd* hWnd0;
	CString StrVersion;
	CTime t1=CTime::GetCurrentTime();
	CString StrCaption,StrName;
	StrCaption=gstructPD[0].StrCaption;
	StrName=gstructPD[0].StrName+".exe"; 
	hWnd0 = FindWindow(NULL,StrCaption.GetBuffer(0));
	if(hWnd0==NULL)
	{
		result=ShellExecute(NULL,"open",StrName.GetBuffer(0),NULL,NULL,SW_SHOWNORMAL);
		if((int)result>32)//��11.0�����\��
		{
			StrVersion="";//��13.7��->�d�ߵ{������
			StrVersion=GetProgramVersion(StrName);//��13.7��->�d�ߵ{������
			if(gblnLogFlag==true)
			{
				CString strTime = t1.Format("%H%M%S"); 
				if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
				{
					//fprintf(gpfControlLog2,"%s,9,Start program OK->%s\n",strTime.GetBuffer(0),StrName.GetBuffer(0));
					//��12.8��->Unicode
					gStr2UnicodeData.Format("%s,9,Start program OK->%s %s\r\n",strTime.GetBuffer(0),StrName.GetBuffer(0),StrVersion.GetBuffer(0));//���ͭn�g�J��� 
					gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
					////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
					MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
					fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog2);//�g��
					//delete [] gpUnicodeDataBuf;//����O����
					//gpUnicodeDataBuf=NULL;//����O����
				}
				else
				{
					//fprintf(gpfControlLog1,"%s,9,Start program OK->%s\n",strTime.GetBuffer(0),StrName.GetBuffer(0));
					//��12.8��->Unicode
					gStr2UnicodeData.Format("%s,9,Start program OK->%s %s\r\n",strTime.GetBuffer(0),StrName.GetBuffer(0),StrVersion.GetBuffer(0));//���ͭn�g�J��� 
					gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
					////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
					MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
					fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog1);//�g��
					//delete [] gpUnicodeDataBuf;//����O����
					//gpUnicodeDataBuf=NULL;//����O����
				}
			}
		}
		else
		{
			if(gblnErrFlag==true)
			{
				CString strTime = t1.Format("%H%M%S"); 
				if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
				{
					//fprintf(gpfControlError2,"%s,9,Not Create program->%s\n",strTime.GetBuffer(0),StrName.GetBuffer(0));
					//��12.8��->Unicode
					gStr2UnicodeData.Format("%s,9,Not Create program->%s\r\n",strTime.GetBuffer(0),StrName.GetBuffer(0));//���ͭn�g�J��� 
					gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
					////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
					MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
					fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError2);//�g��
					gblnGetError=true;//��13.2��
					//delete [] gpUnicodeDataBuf;//����O����
					//gpUnicodeDataBuf=NULL;//����O����
				}
				else
				{
					//fprintf(gpfControlError1,"%s,9,Not Create program->%s\n",strTime.GetBuffer(0),StrName.GetBuffer(0));
					//��12.8��->Unicode
					gStr2UnicodeData.Format("%s,9,Not Create program->%s\r\n",strTime.GetBuffer(0),StrName.GetBuffer(0));//���ͭn�g�J��� 
					gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
					////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
					MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
					fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError1);//�g��
					gblnGetError=true;//��13.2��
					//delete [] gpUnicodeDataBuf;//����O����
					//gpUnicodeDataBuf=NULL;//����O����
				}
			}
		}
	}
}
void CCute_Main_ControlDlg::CreateLogFile()//�}�Ҭ�����T�\��//��11.0�����\��
{
	CString strFileName1;
	CString StrVersion;
	CString StrMeName;
	CString StrControlFileName;
	CString StrNowday;
	CString StrDayBuf;
	CString StrMonthBuf;
	CString DeleteFileName;////��13.2��
	gunicode[0] = 0xFF;//��12.8��->Unicode   
	gunicode[1] = 0xFE;//��12.8��->Unicode 
	///////////////////////////////////////////////////////////////////////////
	//���o�ثe�t�ήɶ�
	CTime t1=CTime::GetCurrentTime();
	int Year=t1.GetYear();//�~ 
	int Month=t1.GetMonth(); //��
	int Day=t1.GetDay();//��
	/////////////////////////////////
	StrNowday.Format("%d",Year);
	if(Month<10)
	{
		StrMonthBuf.Format("0%d",Month); 
	}
	else
	{
		StrMonthBuf.Format("%d",Month);
	}
	if(Day<10)
	{
		StrDayBuf.Format("0%d",Day); 
	}
	else
	{
		StrDayBuf.Format("%d",Day);
	}
	StrNowday=StrNowday+StrMonthBuf+StrDayBuf;
	GetCreateFileFlag();//��11.4�����\��
	//////////////////////////////////////////////////
	//��11.0�����\��
	//�}�ҰO����
	if(gblnLogFlag==true||gblnErrFlag==true)
	{
		if(gStrYesterday!=StrNowday)
		{
			int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
			if( gstrCurDrt[nLen]!='\\' )
			{
				gstrCurDrt[nLen++] = '\\';
				gstrCurDrt[nLen] = '\0';
			}
			StrMeName = gstrCurDrt;
			StrMeName +="Cute_Main_Control.exe";
			StrVersion="";//��13.7��->�d�ߵ{������
			StrVersion=GetProgramVersion(StrMeName);//��13.7��->�d�ߵ{������
			strFileName1 = gstrCurDrt;
			strFileName1 +="Resources\\Export_Data\\Main\\";
			if(gblnControlErrorLog==false)
			{
				//0
				StrControlFileName=strFileName1;
				StrControlFileName+=StrNowday+"err";
				StrControlFileName+=".log";
				gpfControlError1=fopen(StrControlFileName.GetBuffer(0),"wb"); 
				fwrite(gunicode,sizeof(char),2,gpfControlError1);
				fwrite(gpUnicode,sizeof(WCHAR),lstrlenW(gpUnicode),gpfControlError1);
				if(gpfControlError2!=NULL)
				{
					fclose(gpfControlError2);
					gpfControlError2=NULL;
					if(gblnGetError!=true)
					{
						DeleteFileName=strFileName1;
						DeleteFileName+=gStrYesterday+"err";
						DeleteFileName+=".log";
						DeleteFile(DeleteFileName);
					}
				}
				StrControlFileName=strFileName1;
				StrControlFileName+=StrNowday+"run";
				StrControlFileName+=".log";
				gpfControlLog1=fopen(StrControlFileName.GetBuffer(0),"wb");
				fwrite(gunicode,sizeof(char),2,gpfControlLog1);//��12.8��->Unicode
				fwrite(gpUnicode,sizeof(WCHAR),lstrlenW(gpUnicode),gpfControlLog1);
				CString strTime = t1.Format("%H%M%S"); 
				//fprintf(gpfControlLog1,"%s,0,Start time\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,0,Start time %s\r\n",strTime.GetBuffer(0),StrVersion.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog1);//�g��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
				if(gpfControlLog2!=NULL)
				{
					fclose(gpfControlLog2);
					gpfControlLog2=NULL;
				}
			}
			else
			{
				//1
				StrControlFileName=strFileName1;
				StrControlFileName+=StrNowday+"err";
				StrControlFileName+=".log";
				gpfControlError2=fopen(StrControlFileName.GetBuffer(0),"wb");
				fwrite(gunicode,sizeof(char),2,gpfControlError2);
				fwrite(gpUnicode,sizeof(WCHAR),lstrlenW(gpUnicode),gpfControlError2);
				if(gpfControlError1!=NULL)
				{
					fclose(gpfControlError1);
					gpfControlError1=NULL;
					if(gblnGetError!=true)
					{
						DeleteFileName=strFileName1;
						DeleteFileName+=gStrYesterday+"err";
						DeleteFileName+=".log";
						DeleteFile(DeleteFileName);
					}
				}
				StrControlFileName=strFileName1;
				StrControlFileName+=StrNowday+"run";
				StrControlFileName+=".log";
				gpfControlLog2=fopen(StrControlFileName.GetBuffer(0),"wb");
				fwrite(gunicode,sizeof(char),2,gpfControlLog2);//��12.8��->Unicode
				fwrite(gpUnicode,sizeof(WCHAR),lstrlenW(gpUnicode),gpfControlLog2);
				CString strTime = t1.Format("%H%M%S"); 
				//fprintf(gpfControlLog2,"%s,0,Start time\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,0,Start time %s\r\n",strTime.GetBuffer(0),StrVersion.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlLog2);//�g��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
				if(gpfControlLog1!=NULL)
				{
					fclose(gpfControlLog1);
					gpfControlLog1=NULL;
				}
			}
			gStrYesterday=StrNowday;
			gblnControlErrorLog=!gblnControlErrorLog;
		}
	}
	/////////////////////////////////
}
void CCute_Main_ControlDlg::Stop_ALL()
{
	CWnd* hWnd[PDData_Max];
	int i;
	CString StrCaption;
	///////////////////////////////////////////////////////////////////
	//�̧Ǩ��X�{���W�٩M���D�A�çP�_�O�_�Ͱ���A�Y������h����
	for(i=0;i<gintProgramNumber;i++)
	{
		StrCaption=gstructPD[i].StrCaption;
		hWnd[i]= FindWindow(NULL,StrCaption.GetBuffer(0));
		if(hWnd[i]!=NULL)
			hWnd[i]->SendMessage(WM_CLOSE,0,0);
	}
	//////////////////////////////////////////////////////////////////////
}
void CCute_Main_ControlDlg::GetCreateFileFlag()//Ū���O�_�إ߰O���ɮ׺X��
{
	int i,j;
	CString StrBuf="";
	MSXML2::IXMLDOMDocumentPtr pDoc;
	gblnLogFlag=false;//��11.4�����\��
	gblnErrFlag=false;//��11.4�����\��
	CTime t1=CTime::GetCurrentTime();
	bool blnRead=false;
	//���J�]�w��
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   return;
	}
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	CString strFileName1 = gstrCurDrt;
	strFileName1 +="Resources\\Setting\\SignageConfig.xml";
	blnRead=pDoc->load((_bstr_t)strFileName1); 
	///////////////////////////////////////////////////////////////
	if(blnRead)
	{
		//pDoc->load("SignageConfig.xml");
		MSXML2::IXMLDOMNodePtr pNodeRoot;
		MSXML2::IXMLDOMNodeListPtr  pNodeList;
		MSXML2::IXMLDOMNodePtr   pNode;
 		MSXML2::IXMLDOMNamedNodeMapPtr pAttrMap=NULL;
		MSXML2::IXMLDOMNodePtr   pAttrItem;
		MSXML2::IXMLDOMNodePtr   pAttrItem_0;
		_variant_t vtStr;
		CString StrData,StrBuf;
		//�b�𤤬d��W��Book���`�I,"//"��ܦb���N�@�h�d��
		///////////////////////////////////////////////////////
		//��M�{����Ƽ���
		pNodeRoot=pDoc->selectSingleNode("//report");
		pNodeRoot->get_childNodes(&pNodeList);
		j=pNodeList->length;
		////////////////////////////////////////////////////////
		//�̧Ǩ��X�l�`�I
		for(i=0;i<j;i++)
		{
			pNode=pNodeList->item[i];
			StrBuf=(char *)pNode->GetnodeName();;
			if(StrBuf=="errorlog")
			{
				pNode->get_nodeTypedValue(&vtStr); 
				StrBuf=vtStr.bstrVal;
				StrBuf.MakeLower();//��13.2��->���b������p�g
				if(StrBuf=="true")
				{
					gblnErrFlag=true;//��11.4�����\��
				}
				else
				{
					gblnErrFlag=false;//��11.4�����\��
				}
			}
			if(StrBuf=="playbacklog")
			{
				pNode->get_nodeTypedValue(&vtStr); 
				StrBuf=vtStr.bstrVal;
				StrBuf.MakeLower();//��13.2��->���b������p�g
				if(StrBuf=="true")
				{
					gblnLogFlag=true;//��11.4�����\��
				}
				else
				{
					gblnLogFlag=false;//��11.4�����\��
				}
			}
			///////////////////////////////////////////////////////////////////
		}
		///////////////////////////////////////////////////////////////////////
	}
	else
	{
		//��11.0�����\��
		if(gblnErrFlag==true)
		{
			CString strTime = t1.Format("%H%M%S"); 
			if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
			{
				//fprintf(gpfControlError2,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError2);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
			else
			{
				//fprintf(gpfControlError1,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError1);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
		}
	}
}
void CCute_Main_ControlDlg::BoBoProgramZindex(int p[PDData_Max][2],long n)
{
	long i,j,key;
	int temp,temp1;
	for(i=0;i<n;i++)
	{
		key=0;
		for(j=0;j<(n-i-1);j++)
		{
			if(p[j][1]>p[j+1][1])
			{
				temp1=p[j][1];
				p[j][1]=p[j+1][1];
				p[j+1][1]=temp1;
				///////////////////////////////
				temp=p[j][0];
				p[j][0]=p[j+1][0];
				p[j+1][0]=temp;
				key=1;
			}
		}
		if(key==0)
			break;
	}
}
void CCute_Main_ControlDlg::SetSystemVolume( const DWORD dwVolume )//�]�w�t�έ��q//��12.5��->�t�έ��q�]�w
{
    MMRESULT                        result;
    HMIXER                          hMixer;
    MIXERLINE                       ml   = {0};
    MIXERLINECONTROLS               mlc  = {0};
    MIXERCONTROL                    mc   = {0};
    MIXERCONTROLDETAILS             mcd  = {0};
    MIXERCONTROLDETAILS_UNSIGNED    mcdu = {0};


    // get a handle to the mixer device
    result = mixerOpen(&hMixer, MIXER_OBJECTF_MIXER, 0, 0, 0);
    if (MMSYSERR_NOERROR == result)
    {
        ml.cbStruct        = sizeof(MIXERLINE);
        ml.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;

        // get the speaker line of the mixer device
        result = mixerGetLineInfo((HMIXEROBJ) hMixer, &ml, MIXER_GETLINEINFOF_COMPONENTTYPE);
        if (MMSYSERR_NOERROR == result)
        {
            mlc.cbStruct      = sizeof(MIXERLINECONTROLS);
            mlc.dwLineID      = ml.dwLineID;
            mlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
            mlc.cControls     = 1;
            mlc.pamxctrl      = &mc;
            mlc.cbmxctrl      = sizeof(MIXERCONTROL);

            // get the volume controls associated with the speaker line
            result = mixerGetLineControls((HMIXEROBJ) hMixer, &mlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);
            if (MMSYSERR_NOERROR == result)
            {
                mcdu.dwValue    = dwVolume;

                mcd.cbStruct    = sizeof(MIXERCONTROLDETAILS);
                mcd.hwndOwner   = 0;
                mcd.dwControlID = mc.dwControlID;
                mcd.paDetails   = &mcdu;
                mcd.cbDetails   = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
                mcd.cChannels   = 1;

                // set the volume
                result = mixerSetControlDetails((HMIXEROBJ) hMixer, &mcd, MIXER_SETCONTROLDETAILSF_VALUE);
                //if (MMSYSERR_NOERROR == result)
                    //AfxMessageBox("Volume changed!");
                //else
                    //AfxMessageBox("mixerSetControlDetails() failed");
            }
            //else
                //AfxMessageBox("mixerGetLineControls() failed");
        }
        //else
            //AfxMessageBox("mixerGetLineInfo() failed");
    
        mixerClose(hMixer);
    }
    //else
        //AfxMessageBox("mixerOpen() failed");
}

DWORD CCute_Main_ControlDlg::GetSystemVolume( void )//���o�t�έ��q//��12.5��->�t�έ��q�]�w
{
    DWORD                           dwVolume = -1;
    MMRESULT                        result;
    HMIXER                          hMixer;
    MIXERLINE                       ml   = {0};
    MIXERLINECONTROLS               mlc  = {0};
    MIXERCONTROL                    mc   = {0};
    MIXERCONTROLDETAILS             mcd  = {0};
    MIXERCONTROLDETAILS_UNSIGNED    mcdu = {0};


    // get a handle to the mixer device
    result = mixerOpen(&hMixer, 0, 0, 0, MIXER_OBJECTF_HMIXER);
    if (MMSYSERR_NOERROR == result)
    {
        ml.cbStruct        = sizeof(MIXERLINE);
        ml.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;

        // get the speaker line of the mixer device
        result = mixerGetLineInfo((HMIXEROBJ) hMixer, &ml, MIXER_GETLINEINFOF_COMPONENTTYPE);
        if (MMSYSERR_NOERROR == result)
        {
            mlc.cbStruct      = sizeof(MIXERLINECONTROLS);
            mlc.dwLineID      = ml.dwLineID;
            mlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
            mlc.cControls     = 1;
            mlc.pamxctrl      = &mc;
            mlc.cbmxctrl      = sizeof(MIXERCONTROL);

            // get the volume controls associated with the speaker line
            result = mixerGetLineControls((HMIXEROBJ) hMixer, &mlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);
            if (MMSYSERR_NOERROR == result)
            {
                mcd.cbStruct    = sizeof(MIXERCONTROLDETAILS);
                mcd.hwndOwner   = 0;
                mcd.dwControlID = mc.dwControlID;
                mcd.paDetails   = &mcdu;
                mcd.cbDetails   = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
                mcd.cChannels   = 1;

                // get the volume
                result = mixerGetControlDetails((HMIXEROBJ) hMixer, &mcd, MIXER_SETCONTROLDETAILSF_VALUE);
                if (MMSYSERR_NOERROR == result)
                    dwVolume = mcdu.dwValue;
                else
                    AfxMessageBox("mixerGetControlDetails() failed");
            }
            else
                AfxMessageBox("mixerGetLineControls() failed");
        }
        else
            AfxMessageBox("mixerGetLineInfo() failed");
    
        mixerClose(hMixer);
    }
    else
        AfxMessageBox("mixerOpen() failed");

    return (dwVolume);
}
void CCute_Main_ControlDlg::SetVolume()////��12.5��->Ū�����q�]�w�Ȩíק�t�έ�
{
	bool blnRead=false;
	CTime t1=CTime::GetCurrentTime();
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   return;
	}
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	CString strFileName1 = gstrCurDrt;
	strFileName1 +="Resources\\Setting\\SignageConfig.xml";
	blnRead=pDoc->load((_bstr_t)strFileName1); 
	//pDoc->load("SignageConfig.xml");
	if(blnRead)
	{
		MSXML2::IXMLDOMNodeListPtr  pNodeList;
		MSXML2::IXMLDOMNodePtr  pNode;
		_variant_t vtStr;
		CString StrBuf;
		int intVolume;
		int intSetValue;
		int l;
		//�b�𤤬d��W��Book���`�I,"//"��ܦb���N�@�h�d�� 
		pNodeList=pDoc->selectNodes("//volume");
		l=pNodeList->length;
		if(pNodeList!=NULL)
		{
			pNode=pNodeList->item[(l-1)];
			pNode->get_nodeTypedValue(&vtStr); 
			StrBuf=vtStr.bstrVal;
			intVolume=atoi(StrBuf.GetBuffer(0));
			intSetValue=65535*intVolume/100;
			SetSystemVolume(intSetValue);
		}
	}
	else
	{
		//��11.0�����\��
		if(gblnErrFlag==true)
		{
			CString strTime = t1.Format("%H%M%S"); 
			if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
			{
				//fprintf(gpfControlError2,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError2);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
			else
			{
				//fprintf(gpfControlError1,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError1);//�g��
				gblnGetError=true;//��13.2��
				//delete [] gpUnicodeDataBuf;//����O����
				//gpUnicodeDataBuf=NULL;//����O����
			}
		}
	}
}
void CCute_Main_ControlDlg::SwitchMonitor()//��12.7��->�eCTRL+ALT+F9�Ϸs��STB���w�n��ʵ�����X
{
	char cha;
	cha=18;//Alt
	//VK_CONTROL;
	//cha;
	//VK_F9;
	keybd_event(VK_CONTROL, 0, 0 ,0);
	keybd_event(cha, 0, 0 ,0);
	keybd_event(VK_F9, 0, 0 ,0);
	Sleep(1000);
	keybd_event(VK_F9, 0, KEYEVENTF_KEYUP ,0);
	keybd_event(cha, 0, KEYEVENTF_KEYUP ,0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP ,0);
}
void CCute_Main_ControlDlg::ChangMonitorSize()//��12.8��->�^���P�]�w�ù��ѪR��
{
	gintMonitorWidthPixels=0;
	gintMonitorHeightPixels=0;
	MSXML2::IXMLDOMDocumentPtr pDoc;
	CTime t1=CTime::GetCurrentTime();
	_variant_t vtStr;
	bool blnRead=false;
	CString strValue;
	//int intHr,intMin;
	char chrDataBuf[1000];
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   return;
	}
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	CString strFileName1 = gstrCurDrt;
	strFileName1 +="Resources\\Setting\\SignageConfig.xml";
	blnRead=pDoc->load((_bstr_t)strFileName1); 
	if(blnRead)//��11.0�����\��
	{
		MSXML2::IXMLDOMNodePtr   pNode;
		MSXML2::IXMLDOMDocumentPtr   pxmldom1;
		MSXML2::IXMLDOMNodePtr   pNode1;
		_bstr_t bt1;
		_variant_t vtStr;
		CString StrValue;
		char chrDataBuf[1000];
		DEVMODE lpDevMode;
		////////////////////////////////////////////
		pNode=pDoc->selectSingleNode("//Monitor");
		bt1=pNode->Getxml();
		////////////////////////////////////////////
		hr = pxmldom1.CreateInstance(__uuidof(MSXML2::DOMDocument30));
		pxmldom1->loadXML(bt1);
		////////////////////////////////////////////////////////////////
		pNode1=pxmldom1->selectSingleNode("//size");
		pNode1->get_nodeTypedValue(&vtStr);  
		StrValue=vtStr.bstrVal;
		strcpy(chrDataBuf,StrValue.GetBuffer(0));
		sscanf(chrDataBuf,"%dx%d",&gintMonitorWidthPixels,&gintMonitorHeightPixels);
		/////////////////////////////////////////////////////////////////////////////
		lpDevMode.dmBitsPerPel = 32;
		lpDevMode.dmPelsWidth = gintMonitorWidthPixels;
		lpDevMode.dmPelsHeight = gintMonitorHeightPixels;
		lpDevMode.dmSize = sizeof(lpDevMode);
		lpDevMode.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;
		LONG result = ChangeDisplaySettings(&lpDevMode,0);
		if(result == DISP_CHANGE_SUCCESSFUL)
		{
			ChangeDisplaySettings(&lpDevMode,CDS_UPDATEREGISTRY);
			//�ϥ�CDS_UPDATEREGISTRY��ܦ��ק�O���[��,
			//�æb���U���g�J�F��������� 
		}
		else
		{
			ChangeDisplaySettings(NULL,0);
		}
	}
	else//��11.0�����\��
	{
		if(gblnErrFlag==true)
		{
			CString strTime = t1.Format("%H%M%S"); 
			if(!gblnControlErrorLog)//0�ɮ�1�A1�ɮ�2 ->ps �@�w�n���ϦV�]����}���ɮ׮ɤw���ܪ��A
			{
				//fprintf(gpfControlError2,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				//////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError2);//�g��
				gblnGetError=true;//��13.2��
				////delete [] gpUnicodeDataBuf;//����O����
				////gpUnicodeDataBuf=NULL;//����O����
			}
			else
			{
				//fprintf(gpfControlError1,"%s,9,Not Find XML\n",strTime.GetBuffer(0));
				//��12.8��->Unicode
				gStr2UnicodeData.Format("%s,9,Not Find XML\r\n",strTime.GetBuffer(0));//���ͭn�g�J��� 
				gintUnicodeDataLen=gStr2UnicodeData.GetLength();//�p���ƪ���
				//////////////gpUnicodeDataBuf= new WCHAR[gintUnicodeDataLen];//���ͰʺA�t�m�O����
				MultiByteToWideChar(CP_ACP, 0,gStr2UnicodeData.GetBuffer(0),-1,gpUnicodeDataBuf,gStr2UnicodeData.GetLength());//ANSI�ഫUNICODE
				fwrite(gpUnicodeDataBuf,sizeof(WCHAR),gStr2UnicodeData.GetLength(),gpfControlError1);//�g��
				gblnGetError=true;//��13.2��
				////delete [] gpUnicodeDataBuf;//����O����
				////gpUnicodeDataBuf=NULL;//����O����
			}
		}
	}
}

void CCute_Main_ControlDlg::BrowseUpdateProgram(CString strDir)//��13.3��->�j�M��s�{���ƶq�P����
{
	CFileFind ff;
	CString szDir = strDir;
	
	if(szDir.Right(1) != "\\")
		szDir += "\\";
	
	szDir += "*.*";
	CString StrData;
	BOOL res = ff.FindFile(szDir);
	
	while(res)
	{
		res = ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots())
		{
			BrowseUpdateProgram(ff.GetFilePath());
		}
		else if(!ff.IsDirectory() && !ff.IsDots())
		{
			gintUpdateProgramCount++;
			StrData=ff.GetFilePath();
			fprintf(gpfUpdateProgram,"%s\n",StrData.GetBuffer(0));
			StrData=ff.GetFileName();
			fprintf(gpfUpdateProgram,"%s\n",StrData.GetBuffer(0));
		}
	}
	ff.Close();
}
CString CCute_Main_ControlDlg::GetProgramVersion(CString StrDir)//��13.7��->�d�ߵ{������
{
	CString StrOutPut;
	DWORD dwDummy; 
	DWORD dwFVISize = GetFileVersionInfoSize(StrDir.GetBuffer(0),&dwDummy); 
	LPBYTE lpVersionInfo = new BYTE[dwFVISize]; 
	GetFileVersionInfo(StrDir.GetBuffer(0),0,dwFVISize,lpVersionInfo); 
	UINT uLen; 
	VS_FIXEDFILEINFO *lpFfi; 
	VerQueryValue( lpVersionInfo , _T("\\") , (LPVOID *)&lpFfi , &uLen ); 
	DWORD dwFileVersionMS = lpFfi->dwFileVersionMS; 
	DWORD dwFileVersionLS = lpFfi->dwFileVersionLS; 
	delete [] lpVersionInfo; 
	DWORD dwLeftMost = HIWORD(dwFileVersionMS); 
	DWORD dwSecondLeft = LOWORD(dwFileVersionMS); 
	DWORD dwSecondRight = HIWORD(dwFileVersionLS); 
	DWORD dwRightMost = LOWORD(dwFileVersionLS);
	StrOutPut="";
	StrOutPut.Format("Version: %d.%d.%d.%d" ,dwLeftMost,dwSecondLeft,dwSecondRight,dwRightMost);
	return StrOutPut; 
}
void CCute_Main_ControlDlg::Reset_Computer()//��13.8��
{
	CString data;
	data=" -f -r -t 0 ";
	ShellExecute(NULL,"open","C:\\WINDOWS\\system32\\shutdown.exe",data.GetBuffer(0),NULL,SW_SHOW);	
}