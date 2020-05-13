// ShowHospitalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShowHospital.h"
#include "ShowHospitalDlg.h"
#include "ShowImageDlg.h"
#include "io.h"
#include "fcntl.h"
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
// CShowHospitalDlg dialog

CShowHospitalDlg::CShowHospitalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowHospitalDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowHospitalDlg)
	m_ShowData00 = _T("00");
	m_ShowData01 = _T("01");
	m_ShowData02 = _T("02");
	m_ShowData03 = _T("03");
	m_ShowData04 = _T("04");
	m_ShowData05 = _T("05");
	m_ShowData06 = _T("06");
	m_ShowData07 = _T("07");
	m_ShowData08 = _T("08");
	m_ShowData09 = _T("09");
	m_ShowData10 = _T("10");
	m_ShowData11 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShowHospitalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowHospitalDlg)
	DDX_Text(pDX, IDC_STATIC_00, m_ShowData00);
	DDX_Text(pDX, IDC_STATIC_01, m_ShowData01);
	DDX_Text(pDX, IDC_STATIC_02, m_ShowData02);
	DDX_Text(pDX, IDC_STATIC_03, m_ShowData03);
	DDX_Text(pDX, IDC_STATIC_04, m_ShowData04);
	DDX_Text(pDX, IDC_STATIC_05, m_ShowData05);
	DDX_Text(pDX, IDC_STATIC_06, m_ShowData06);
	DDX_Text(pDX, IDC_STATIC_07, m_ShowData07);
	DDX_Text(pDX, IDC_STATIC_08, m_ShowData08);
	DDX_Text(pDX, IDC_STATIC_09, m_ShowData09);
	DDX_Text(pDX, IDC_STATIC_10, m_ShowData10);
	DDX_Text(pDX, IDC_STATIC_11, m_ShowData11);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShowHospitalDlg, CDialog)
	//{{AFX_MSG_MAP(CShowHospitalDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowHospitalDlg message handlers

BOOL CShowHospitalDlg::OnInitDialog()
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
	InitialVariable();//�I�sŪ���]�w��
	///* //�z���{���X
	if(m_blnAttributes)//Jash.Liao-12.5���O�_�z��
	{
		SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,
			GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
		HINSTANCE hInst = LoadLibrary("User32.DLL"); 
		if(hInst) 
		{ 
			typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
			MYFUNC fun = NULL;
			fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
			if(fun)fun(this->GetSafeHwnd(),RGB(211,227,138),0,1); 
			FreeLibrary(hInst); 
		}
	}
	//*/
	NetGetData();
	GetPlayData();
	ChangeShowData();
	ShowData();
	/////////////////////////////////////////////////////////////////////////////
	SetWindowPositionSize();//�I�s��������(��)
	//////////////////////////////////////////////////////////////////////////////
	SetTimer(1,1000,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShowHospitalDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShowHospitalDlg::OnPaint() 
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
HCURSOR CShowHospitalDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CShowHospitalDlg::InitialVariable(void)
{
	////////////////////////////////////////////////////////////
	//�ϰ��ܼƫŧi��
	MSXML2::IXMLDOMDocumentPtr pDoc;
	int nLen=0;
	bool blnRead=false;
	_variant_t vtStr;
	CString StrValue;
	CString  Strbuf;
	int i=0;
	////////////////////////////////////////////////////////////
	//�����ܼƪ�l�ư�
	m_lngTop=0;m_lngLeft=0;m_lngWidth=0;m_lngHeight=0;
	m_lngGet_Data=0;m_lngChange_Page=0;m_lngData_Count=0;m_lngResetTimeCount=0;
	////////////////////////////////////////////////////////////
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));//�إ�XML����
	if(!SUCCEEDED(hr))
	{
	   return;
	}
	nLen= ::GetCurrentDirectory(500,m_chrCurDrt);//���o�ثe�{�����|
	m_StrSettingFileName=m_chrCurDrt;
	m_StrSettingFileName+="\\Resources\\Config.xml";//���ͳ]�w�ɸ��|
	blnRead=pDoc->load((_bstr_t)m_StrSettingFileName);//Ū���]�w��
	if(blnRead)
	{
		//////////////////////////////////////////////////
		//�̧�Ū�������j�p����m�]�w��
		//�ñN�]�w�ȳ]�w����������ܼ�
		MSXML2::IXMLDOMNodePtr Position_Size;
		Position_Size=pDoc->selectSingleNode("//Top");
		Position_Size->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngTop=atol(StrValue.GetBuffer(0));
		//------
		Position_Size=pDoc->selectSingleNode("//Image_Top");
		Position_Size->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngImageTop=atol(StrValue.GetBuffer(0));
		//************************************************
		Position_Size=pDoc->selectSingleNode("//Left");
		Position_Size->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngLeft=atol(StrValue.GetBuffer(0));
		//-------
		Position_Size=pDoc->selectSingleNode("//Image_Left");
		Position_Size->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngImageLeft=atol(StrValue.GetBuffer(0));
		//************************************************
		Position_Size=pDoc->selectSingleNode("//Width");
		Position_Size->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngWidth=atol(StrValue.GetBuffer(0));
		//-------
		Position_Size=pDoc->selectSingleNode("//Image_Width");
		Position_Size->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngImageWidth=atol(StrValue.GetBuffer(0));
		//************************************************
		Position_Size=pDoc->selectSingleNode("//Height");
		Position_Size->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngHeight=atol(StrValue.GetBuffer(0)); 
		//------
		Position_Size=pDoc->selectSingleNode("//Image_Height");
		Position_Size->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngImageHeight=atol(StrValue.GetBuffer(0)); 
		//////////////////////////////////////////////////
		//Ū���q�Ϥ��ϻP�Ϫ��ɶ�
		MSXML2::IXMLDOMNodePtr ShowImageTime;
		ShowImageTime=pDoc->selectSingleNode("//Change_Image");
		ShowImageTime->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngChangeImage=atol(StrValue.GetBuffer(0)); 
		//////////////////////////////////////////////////
		//����Reset_Time�ɶ�
		MSXML2::IXMLDOMNodeListPtr Reset_Time;
		MSXML2::IXMLDOMNodePtr pNode;
		Reset_Time=pDoc->selectNodes("//Value");
		m_lngResetTimeCount=Reset_Time->length;//Reset Time ���ƶq
		m_RT=new struct Reset_Time[m_lngResetTimeCount];
		for(i=0;i<m_lngResetTimeCount;i++)
		{
			pNode=Reset_Time->item[i];
			pNode->get_nodeTypedValue(&vtStr);
			StrValue=vtStr.bstrVal;
			Strbuf=StrValue.Mid(0,2);
			m_RT[i].lngHours=atol(Strbuf.GetBuffer(0));
			Strbuf=StrValue.Mid(3,2);
			m_RT[i].lngMinute=atol(Strbuf.GetBuffer(0));
			Strbuf=StrValue.Mid(6);//jashliao write at 2008/12/16
			m_RT[i].lngShowImageTime=atol(Strbuf.GetBuffer(0));//jashliao write at 2008/12/16 
		}
		////////////////////////////////////////////////////
		//Ū��
		//long m_lngGet_Data;
		//long m_lngChange_Page;
		//long m_lngData_Count;
		MSXML2::IXMLDOMNodePtr Get_Data,Change_Page,Data_Count;
		Get_Data=pDoc->selectSingleNode("//Get_Data");
		Get_Data->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngGet_Data=atol(StrValue.GetBuffer(0)); 
		//******************************************************
		Change_Page=pDoc->selectSingleNode("//Change_Page");
		Change_Page->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngChange_Page=atol(StrValue.GetBuffer(0)); 
		//******************************************************
		Data_Count=pDoc->selectSingleNode("//Data_Count");
		Data_Count->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngData_Count=atol(StrValue.GetBuffer(0));
		////////////////////////////////////////////////////////
		MSXML2::IXMLDOMNodePtr NetPath;
		NetPath=pDoc->selectSingleNode("//Net_Path");
		NetPath->get_nodeTypedValue(&vtStr);
		m_StrNetPath=vtStr.bstrVal;
		////////////////////////////////////////////////////////
		MSXML2::IXMLDOMNodePtr Attributes;
		Attributes=pDoc->selectSingleNode("//Attributes");
		Attributes->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		if(StrValue=="true")
		{
			m_blnAttributes=true;
		}
		else
		{
			m_blnAttributes=false;
		}
		////////////////////////////////////////////////////////
		UpdateData(true);
		m_ShowData00="��O      �E�O �E��";
		UpdateData(false);
		for(i=0;i<11;i++)
			m_StrShowDataBuff[i]="";
		m_lngPageVariable=0;//���������ܼ�
		m_lngArryDataCount=0;//��ڸ�Ƥ��
		m_bnlInitialPage=false;//���ƧP�_�X��
		m_lngTimerCount=0;
		m_blnArrayed_Data=false;//��ƴN���X��
		/////////////////////////////////////////////////////////
	}
}
void CShowHospitalDlg::SetWindowPositionSize(void)
{
	CRect rect;
	::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	this->MoveWindow((m_lngLeft-5),(m_lngTop-29),(m_lngWidth+12),(m_lngHeight+34),TRUE);
	this->GetClientRect(rect);
	m_rgn.CreateRectRgn(5,29,rect.Width(),(rect.Height()+25));
	::SetWindowRgn(GetSafeHwnd(),(HRGN)m_rgn,TRUE);
	/*
	�Ʀr5���h�������
	�Ʀr29���F�h�����D�C
	�Ʀr12�ɼe��:(12-5)=7
	�Ʀr34�ɰ���:(34-29)=5
	*/
	//this->MoveWindow(m_lngLeft,(m_lngTop-29),m_lngWidth,(m_lngHeight+29),TRUE);
}
void CShowHospitalDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	///////////////////////////////////////////////////////////////////////////
	int i;
	CTime time = CTime::GetCurrentTime();   ///�c�yCTime����
	long lngHour = time.GetHour();      ///�p��
	long lngMinute = time.GetMinute();   ///����
	///////////////////////////////////////////////////////////////////////////
	///*
	//�q���
	m_lngTimerCount++;
	if((m_lngTimerCount%m_lngChange_Page)==0)
	{
		ChangeShowData();
		ShowData();
	}
	//*/
	///////////////////////////////////////////////////////////////////////////
	if((m_lngTimerCount%m_lngGet_Data)==0||(m_blnArrayed_Data==false))
	{
		NetGetData();
		GetPlayData();
		m_lngTimerCount=0;
	}
	///////////////////////////////////////////////////////////////////////////
	///*
	//�R���{��
	for(i=0;i<m_lngResetTimeCount;i++)
	{
		if((lngHour==m_RT[i].lngHours) && (lngMinute==m_RT[i].lngMinute))
		{
			m_blnRest_Flag=true;
			m_lngShowImageTime=m_RT[i].lngShowImageTime;//jashliao write at 2008/12/16 
			break;
		}
		else
		{
			m_blnRest_Flag=false;
		}
	}
	if(m_blnRest_Flag)
	{
		ClearMessageData();
		this->ShowWindow(SW_HIDE);//���åD����
		CShowImageDlg SID(this);
		SID.m_lngHeight=m_lngImageHeight;
		SID.m_lngLeft=m_lngImageLeft;
		SID.m_lngTop=m_lngImageTop;
		SID.m_lngWidth=m_lngImageWidth;
		SID.m_lngShowImageTime=m_lngShowImageTime;
		SID.m_lngChangeImage=m_lngChangeImage;
		SID.DoModal(); 
		this->ShowWindow(SW_SHOW);//²�檺��ܥD�������ƨ�
		NetGetData();//jashliao write at 2008/12/16
		GetPlayData();//jashliao write at 2008/12/16
		ShowData();
		m_lngTimerCount=0;
	}
	//*/
	////////////////////////////////////////////////////////////////////////////
	SetTimer(1,1000,NULL);
	CDialog::OnTimer(nIDEvent);
}

HBRUSH CShowHospitalDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_STATIC)//�]�w�R�A��r����I���C��M��r�C��
	{
		pDC->SetBkColor(RGB(211,227,138));
		pDC->SetTextColor(RGB(0,0,255)); 
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
void CShowHospitalDlg::GetPlayData(void)
{
	int i=0;
	CString StrFileName;
	char chrData[200];
	CString StrFileData;
	FILE *pfMessage;
	pfMessage=NULL;
	m_ArrPlayData.RemoveAll();
	for(i=0;i<m_lngData_Count;i++)
	{
		m_StrPlayDataFileName="";
		StrFileName="";
		StrFileData="";
		StrFileName.Format("%d\\message.txt",(i+1));  
		m_StrPlayDataFileName=m_chrCurDrt;
		m_StrPlayDataFileName+="\\Resources\\Messages\\";//���ͳ]�w�ɸ��|
		m_StrPlayDataFileName+=StrFileName;
		pfMessage=fopen(m_StrPlayDataFileName.GetBuffer(0),"r");
		if(pfMessage)
		{
			fgets(chrData,200,pfMessage);
			StrFileData=chrData;
			StrFileData=StrFileData.Mid(0,StrFileData.GetLength()-1); 
			fclose(pfMessage);
			m_ArrPlayData.Add(StrFileData);
			m_blnArrayed_Data=true;//��ƴN���X��
		}
		pfMessage=NULL;
	}
	////////////////////////////////////////////////////////
	UpdateData(true);
	m_ShowData00="��O      �E�O �E��";
	UpdateData(false);
	for(i=0;i<11;i++)
		m_StrShowDataBuff[i]="";
	//m_lngPageVariable=0;//���������ܼ� //2.4���Ajash.liao �קאּ�F�F���s��ơA�����q�Y��� 20080729 
	m_lngArryDataCount=0;//��ڸ�Ƥ��
	m_bnlInitialPage=false;//���ƧP�_�X��
	m_lngTimerCount=0;
	/////////////////////////////////////////////////////////
	m_lngArryDataCount=m_ArrPlayData.GetSize();//��ڸ�Ƥ��
	/*
	UpdateData(true);
	m_ShowData01=m_ArrPlayData.GetAt(0);
	m_ShowData02=m_ArrPlayData.GetAt(1);
	m_ShowData03=m_ArrPlayData.GetAt(2);
	m_ShowData04=m_ArrPlayData.GetAt(3);
	m_ShowData05=m_ArrPlayData.GetAt(4);
	m_ShowData06=m_ArrPlayData.GetAt(5);
	m_ShowData07=m_ArrPlayData.GetAt(6);
	m_ShowData08=m_ArrPlayData.GetAt(7);
	m_ShowData09=m_ArrPlayData.GetAt(8);
	m_ShowData10=m_ArrPlayData.GetAt(9);
	m_ShowData11=m_ArrPlayData.GetAt(10);
	UpdateData(false);
	//*/
}
void CShowHospitalDlg::ChangeShowData(void)//������ܸ��
{
	int i=0;//�ت��X��
	int j=0;//�ӷ��X��
	bool blnCheckRest=true;//Jash.Liao-12.6������ťխ�
	/////////////////////////////////////////////////
	for(i=0;i<11;i++)
		m_StrShowDataBuff[i]="";
	////////////////////////////////////////////////
	for(i=0;i<11;i++)
	{
		j=m_lngPageVariable+i;
		if(j<m_lngArryDataCount)
		{
			m_StrNormalData=NormalData(m_ArrPlayData.GetAt(j));
			m_StrShowDataBuff[i]=m_StrNormalData;
			blnCheckRest=false;//Jash.Liao-12.6������ťխ�
			//m_StrShowDataBuff[i]=m_ArrPlayData.GetAt(j);//Jash.Liao �b2.5���s�W���W�Ƹ�ƨ��
		}
		else
		{
			m_bnlInitialPage=true;
			break;
		}
	}
	if(m_bnlInitialPage==false)
	{
		m_lngPageVariable+=11;
	}
	else
	{
		m_lngPageVariable=0;
		m_bnlInitialPage=false;
		if(blnCheckRest)//Jash.Liao-12.6������ťխ�
		{//Jash.Liao-12.6������ťխ�
			//ChangeShowData();//Jash.Liao-12.6������ťխ�
			for(i=0;i<11;i++)//Jash.Liao-12.6������ťխ�
			{//Jash.Liao-12.6������ťխ�
				j=m_lngPageVariable+i;//Jash.Liao-12.6������ťխ�
				if(j<m_lngArryDataCount)//Jash.Liao-12.6������ťխ�
				{//Jash.Liao-12.6������ťխ�
					m_StrNormalData=NormalData(m_ArrPlayData.GetAt(j));//Jash.Liao-12.6������ťխ�
					m_StrShowDataBuff[i]=m_StrNormalData;//Jash.Liao-12.6������ťխ�
					blnCheckRest=false;//Jash.Liao-12.6������ťխ�
				}//Jash.Liao-12.6������ťխ�
				else//Jash.Liao-12.6������ťխ�
				{//Jash.Liao-12.6������ťխ�
					m_bnlInitialPage=true;//Jash.Liao-12.6������ťխ�
					break;//Jash.Liao-12.6������ťխ�
				}//Jash.Liao-12.6������ťխ�
			}//Jash.Liao-12.6������ťխ�
		}//Jash.Liao-12.6������ťխ�
	}

}
void CShowHospitalDlg::ClearMessageData(void)//�M����ܸ��
{
	int i=0;
	CString StrFileName;
	//CString StrFileData;
	//FILE *pfMessage;
	//pfMessage=NULL;
	m_ArrPlayData.RemoveAll();
	m_lngPageVariable=0;//���������ܼ�
	m_lngArryDataCount=0;//��ڸ�Ƥ��
	m_bnlInitialPage=false;//���ƧP�_�X��
	m_lngTimerCount=0;
	for(i=0;i<m_lngData_Count;i++)
	{
		m_StrPlayDataFileName="";
		StrFileName="";
		//StrFileData="";
		StrFileName.Format("%d\\message.txt",(i+1));  
		m_StrPlayDataFileName=m_chrCurDrt;
		m_StrPlayDataFileName+="\\Resources\\Messages\\";//���ͳ]�w�ɸ��|
		m_StrPlayDataFileName+=StrFileName;
		DeleteFile(m_StrPlayDataFileName);
	}
	for(i=0;i<11;i++)
	{
		m_StrShowDataBuff[i]="";
	}
	m_blnArrayed_Data=false;//��ƴN���X��
}
void CShowHospitalDlg::NetGetData(void)//����������
{
	int i=0,j=0,k=0;
	CString StrNetFileName;
	CString StrFileName;
	CString StrNetDataBuf,StrLocalDataBuf;
	CString Strtype;
	CString StrCommandPath;
	for(i=0;i<m_lngData_Count;i++)
	{
		///////////////////////////////////////////////////////////////
		m_StrPlayDataFileName="";
		StrFileName="";
		//StrFileData="";
		StrFileName.Format("%d\\message.txt",(i+1));  
		m_StrPlayDataFileName=m_chrCurDrt;
		m_StrPlayDataFileName+="\\Resources\\Messages\\";//���ͳ]�w�ɸ��|
		m_StrPlayDataFileName+=StrFileName;
		//***************************************************************
		StrNetFileName="";
		StrNetFileName=m_StrNetPath;
		StrNetFileName+=StrFileName;
		//****************************************************************
		if(CopyFile(StrNetFileName.GetBuffer(0),m_StrPlayDataFileName.GetBuffer(0),false))
		{
			DeleteFile(StrNetFileName.GetBuffer(0)); 
		}
	}
	//**********************************************************************
	//�ƻs�ϥd
	StrNetFileName=m_StrNetPath;
	StrNetFileName+="web\\";
	//////////////////////////////
	StrCommandPath=StrNetFileName;
	StrCommandPath+="delete.msg";
	if((k=open(StrCommandPath,_O_RDONLY))>=0)
	{
		close(k);
		DeleteFile(StrCommandPath.GetBuffer(0));
		StrLocalDataBuf=m_chrCurDrt;
		StrLocalDataBuf+="\\Resources\\web\\";
		Strtype="*.*";
		m_Array.RemoveAll();
		BrowseDir(StrLocalDataBuf,Strtype);
		j=m_Array.GetSize();
		for(i=0;i<j;i++)
		{
			StrLocalDataBuf=m_chrCurDrt;
			StrLocalDataBuf+="\\Resources\\web\\";
			StrLocalDataBuf+=m_Array.GetAt(i);
			DeleteFile(StrLocalDataBuf.GetBuffer(0)); 
		}
	}
	/////////////////////////////
	m_Array.RemoveAll();
	Strtype="*.jpg";
	BrowseDir(StrNetFileName,Strtype);
	Strtype="*.gif";
	BrowseDir(StrNetFileName,Strtype);
	j=m_Array.GetSize();
	for(i=0;i<j;i++)
	{
		StrNetDataBuf=StrNetFileName;
		StrNetDataBuf+=m_Array.GetAt(i);
		StrLocalDataBuf=m_chrCurDrt;
		StrLocalDataBuf+="\\Resources\\web\\";
		StrLocalDataBuf+=m_Array.GetAt(i);
		if(CopyFile(StrNetDataBuf.GetBuffer(0),StrLocalDataBuf.GetBuffer(0),false))
		{
			DeleteFile(StrNetDataBuf.GetBuffer(0)); 
		}
	}

}
void CShowHospitalDlg::ShowData(void)//��ܼ�����
{
	UpdateData(true);
	m_ShowData01=m_StrShowDataBuff[0];
	m_ShowData02=m_StrShowDataBuff[1];
	m_ShowData03=m_StrShowDataBuff[2];
	m_ShowData04=m_StrShowDataBuff[3];
	m_ShowData05=m_StrShowDataBuff[4];
	m_ShowData06=m_StrShowDataBuff[5];
	m_ShowData07=m_StrShowDataBuff[6];
	m_ShowData08=m_StrShowDataBuff[7];
	m_ShowData09=m_StrShowDataBuff[8];
	m_ShowData10=m_StrShowDataBuff[9];
	m_ShowData11=m_StrShowDataBuff[10];
	UpdateData(false);
}
CString CShowHospitalDlg::NormalData(CString StrSource)//���W�����
{
		//m_Data0 = _T("�j�����g�~��01�E-000");
		CString StrData1,StrData2,StrData3,StrData4; 
		//******************************************************
		StrData1=StrSource.Mid(0,StrSource.Find("��",0))+"��";   
		StrData2 =StrSource.Mid((StrSource.Find("��",0)+2));
		StrData3 =StrData1.Mid(0,10);
		if(StrData3.GetLength()<10)//Jash.Liao-12.6���O�_�ɪťզr��
		{//Jash.Liao-12.6���O�_�ɪťզr��
			StrData4 =StrData3+"  ";//Jash.Liao-12.6���O�_�ɪťզr��
			StrData4 +=StrData2;//Jash.Liao-12.6���O�_�ɪťզr��
		}//Jash.Liao-12.6���O�_�ɪťզr��
		else//Jash.Liao-12.6���O�_�ɪťզr��
		{//Jash.Liao-12.6���O�_�ɪťզr��
			StrData4 =StrData3+StrData2;
		}//Jash.Liao-12.6���O�_�ɪťզr��
		return StrData4;
}
BOOL CShowHospitalDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete [] m_RT;
	return CDialog::DestroyWindow();
}

void CShowHospitalDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
}
void CShowHospitalDlg::BrowseDir(CString strDir,CString strtype)//Step 1:�C�X�ɮײM��
{
	CFileFind ff;
	CString szDir = strDir;
	
	if(szDir.Right(1) != "\\")
		szDir += "\\";
	
	szDir += strtype;
	
	BOOL res = ff.FindFile(szDir);
	while(res)
	{
		res = ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots())
		{
			BrowseDir(ff.GetFilePath(),strtype);
		}
		else if(!ff.IsDirectory() && !ff.IsDots())
		{
			//m_Array.Add(ff.GetFilePath());
			m_Array.Add(ff.GetFileName()); 
		}
	}
	ff.Close();
}