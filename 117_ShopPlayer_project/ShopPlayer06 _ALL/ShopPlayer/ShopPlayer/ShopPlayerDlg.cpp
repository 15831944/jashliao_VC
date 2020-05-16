// ShopPlayerDlg.cpp : ��@��
//

#include "stdafx.h"
#include "ShopPlayer.h"
#include "ShopPlayerDlg.h"
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
// �� App About �ϥ� CAboutDlg ��ܤ��
int ginttimerrun;
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


// CShopPlayerDlg ��ܤ��




CShopPlayerDlg::CShopPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShopPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShopPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIDEO_WINDOW, m_videoWindow);
}

BEGIN_MESSAGE_MAP(CShopPlayerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_GRAPHNOTIFY, OnGraphNotify)//DirectShow_step 05
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CShopPlayerDlg �T���B�z�`��

BOOL CShopPlayerDlg::OnInitDialog()
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
	InitialVariable();
	/////////////////////////////////////////////////////////////////////////////	
	ModifyStyle(0, WS_SYSMENU);
	SetWindowText(L"ShopPlayer");	
	this->MoveWindow(m_lngLeft,m_lngTop,m_lngWidth,m_lngHeight,TRUE);
	RECT rc;
	this->GetClientRect(&rc);
	m_videoWindow.MoveWindow( &rc, true );
	//////////////////////////////////////////////////////////////////////////////
	hDataMap = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH,	TEXT(MAP_Data) ) ;//MAP memory_step 03
	m_dblPosition=0.0;
	m_sourceFile=GetMapMemory(&m_dblPosition);//MAP memory_step 06
	m_pFilterGraph = NULL;//DirectShow_step 04
	MovieOpen();//DirectShow_step 14
	MoviePlay();//DirectShow_step 15
	SetTimer(1,100,NULL);
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CShopPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShopPlayerDlg::OnPaint()
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
HCURSOR CShopPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CShopPlayerDlg::InitialVariable(void)
{
	MSXML2::IXMLDOMDocumentPtr pDoc;
	int nLen=0;
	bool blnRead=false;
	_variant_t vtStr;
	CString StrValue;
	m_lngTop=0;m_lngLeft=0;m_lngWidth=0;m_lngHeight=0;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   return;
	}
	nLen= ::GetCurrentDirectory(500,m_chrCurDrt);//���o�ثe�{�����|
	m_StrSettingFileName+="Resources\\Config.xml";
	blnRead=pDoc->load((_bstr_t)m_StrSettingFileName);
	if(blnRead)
	{
		//////////////////////////////////////////////////
		MSXML2::IXMLDOMNodePtr Position_Size;
		Position_Size=pDoc->selectSingleNode("//Top");
		Position_Size->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngTop=_ttoi(static_cast<LPCTSTR>(StrValue)); 
		//************************************************
		Position_Size=pDoc->selectSingleNode("//Left");
		Position_Size->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngLeft=_ttoi(static_cast<LPCTSTR>(StrValue));  
		//************************************************
		Position_Size=pDoc->selectSingleNode("//Width");
		Position_Size->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngWidth=_ttoi(static_cast<LPCTSTR>(StrValue));  
		//************************************************
		Position_Size=pDoc->selectSingleNode("//Height");
		Position_Size->get_nodeTypedValue(&vtStr);
		StrValue=vtStr.bstrVal;
		m_lngHeight=_ttoi(static_cast<LPCTSTR>(StrValue)); 
		//////////////////////////////////////////////////
	}
}
LRESULT CShopPlayerDlg::OnGraphNotify(WPARAM inWParam, LPARAM inLParam)//DirectShow_step 07
{
	IMediaEventEx *pEvent = NULL;
	if ((m_pFilterGraph!=NULL) && (pEvent = m_pFilterGraph->GetEventHandle()))
	{
		LONG eventCode = 0;
		LONG eventParam1  = 0;
		LONG eventParam2 = 0;
		
		while (SUCCEEDED(pEvent->GetEvent(&eventCode, &eventParam1, &eventParam2, 0)))
		{
			pEvent->FreeEventParams(eventCode, eventParam1, eventParam2);
			switch (eventCode)
			{
			case EC_COMPLETE:
				MovieStop();
				//MessageBox(L"finish ...");
				ginttimerrun=1;
				break;
			case EC_USERABORT:
			case EC_ERRORABORT:
				MovieStop();
				break;
			default:
				break;
			}
		}
	}
	return 0;
}

void CShopPlayerDlg::CreateGraph()//DirectShow_step 08
{
	DestroyGraph();                  //�����˲�������ͼ
	m_pFilterGraph = new CDXGraph(); //����CDXGraph����
	if (m_pFilterGraph->Create())    //�����˲������������
	{
		//if (!m_pFilterGraph->RenderFile(ch))//��Ⱦý���ļ��������˲�������
		TCHAR *ch1 = m_sourceFile.GetBuffer(m_sourceFile.GetLength());
		
		if (!m_pFilterGraph->RenderFile(ch1))//��Ⱦý���ļ��������˲�������
		{
			MessageBox(_T("�޷���Ⱦ��ý���ļ�����ȷ���Ƿ�װ��ؽ����������\n ���ߴ�ý���ļ����𻵣�"),_T("ϵͳ��ʾ"),MB_ICONWARNING); 
			return;
		}
		m_sourceFile.ReleaseBuffer();
         //����ͼ����ʾ����
		m_pFilterGraph->SetDisplayWindow(m_videoWindow.GetSafeHwnd());
         //���ô�����Ϣ֪ͨ
		m_pFilterGraph->SetNotifyWindow(this->GetSafeHwnd());
		//��ʾ��һ֡ͼ��
		m_pFilterGraph->Pause();

	}
}
void CShopPlayerDlg::DestroyGraph()//DirectShow_step 09
{
	if (m_pFilterGraph != NULL)
	{
		m_pFilterGraph->Stop();
		m_pFilterGraph->SetNotifyWindow(NULL);

		delete m_pFilterGraph;
		m_pFilterGraph = NULL;
	}
}
CString CShopPlayerDlg::GetFileTitleFromFileName(CString FileName, BOOL Ext)//DirectShow_step 10   
{   
    int Where;   
    Where = FileName.ReverseFind('\\');  
    if (Where == -1)  
        Where = FileName.ReverseFind('/');  
    CString FileTitle = FileName.Right(FileName.GetLength() - 1 - Where);  
    if (!Ext)  
    {  
        int Which = FileTitle.ReverseFind('.');   
        if (Which != -1)   
            FileTitle = FileTitle.Left(Which);   
    }   
    return FileTitle;   
}
void CShopPlayerDlg::MovieOpen()//DirectShow_step 11
{
	if(m_sourceFile=="No Data")
		m_sourceFile = _T("D:\\11.wmv");
	m_mediaFileName =GetFileTitleFromFileName(m_sourceFile,1);
	CreateGraph();
}
void CShopPlayerDlg::MoviePlay()//DirectShow_step 12
{
	if (m_pFilterGraph)
	{
		SetWindowText(_T("Media File Name: ") + m_mediaFileName);
		double duration =1.0;
		m_pFilterGraph->GetDuration(&duration);
		m_pFilterGraph->SetCurrentPosition(m_dblPosition);
		m_pFilterGraph->Run();

		//m_pFilterGraph->ChangeAudioVolume(m_volume);
	}
}
void CShopPlayerDlg::MovieStop()//DirectShow_step 13
{
	if (m_pFilterGraph != NULL)
	{
		m_pFilterGraph->Stop();
	}
}
CString CShopPlayerDlg::GetMapMemory(double *dblPosition)//MAP memory_step 05
{
	CString StrData;
	StrData="No Data";
	LPVOID mapView = MapViewOfFile( hDataMap,FILE_MAP_WRITE, 0, 0, 0 ) ;
	if( mapView != NULL ) 
	{
		StrData=(LPTSTR)mapView;
		if(StrData=="")
		{
			StrData="No Data";
			return StrData;
		}
	}

	//************************
	CString theString( "" ); 
	LPTSTR lpsz = new TCHAR[theString.GetLength()+1]; 
	_tcscpy(lpsz, theString);
	_tcscpy((LPTSTR)mapView,lpsz);
	UnmapViewOfFile( (LPVOID)mapView);
	delete []lpsz;

	//***********************
	//Unicode�UCString�ഫ��char *
	//�`�N�G�H�Un�Mlen���Ȥj�p���P,n�O���r���p�⪺�Alen�O���줸�խp�⪺
	int n = StrData.GetLength();
	//����e�줸�զr�����j�p�A�j�p�O���줸�խp�⪺
	int len = WideCharToMultiByte(CP_ACP,0,StrData,StrData.GetLength(),NULL,0,NULL,NULL);
	//���h�줸�զr���}�C�ӽЪŶ��A�}�C�j�p�����줸�խp�⪺�e�줸�զ줸�դj�p
	char * pFileName = new char[len+1];   //�H�줸�լ����
	//�e�줸�սs�X�ഫ���h�줸�սs�X
	WideCharToMultiByte(CP_ACP,0,StrData,StrData.GetLength(),pFileName,len,NULL,NULL);
	pFileName[len] = '\0'; //�K�[�r�굲���A�`�N���Olen+1
	
	//************************
	//sscanf
	char Schrd01[500],Schrd02[500];
	double fltp01;
	sscanf (pFileName ,"%[^','],%s",Schrd01,Schrd02);
	fltp01=atof(Schrd02);
	delete [] pFileName;

	//**********************
	*dblPosition=fltp01;
	StrData=Schrd01;

	return StrData;
}
void CShopPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	TCHAR *ch1;
	if(ginttimerrun==1)
	{
		KillTimer(1);
		ginttimerrun=0;
		m_dblPosition=0.0;
		m_sourceFile=GetMapMemory(&m_dblPosition);
		if(m_sourceFile=="No Data")
			m_sourceFile = _T("D:\\11.wmv");
		m_mediaFileName =GetFileTitleFromFileName(m_sourceFile,1);
		SetWindowText(_T("Media File Name: ") + m_mediaFileName);
		/////////////////////////////////////////////////////////
		CreateGraph();
		ch1 = m_sourceFile.GetBuffer(m_sourceFile.GetLength());
		if (!m_pFilterGraph->RenderFile(ch1))//��Ⱦý���ļ��������˲�������
		{
			MessageBox(_T("�޷���Ⱦ��ý���ļ�����ȷ���Ƿ�װ��ؽ����������\n ���ߴ�ý���ļ����𻵣�"),_T("ϵͳ��ʾ"),MB_ICONWARNING); 
		}
		m_sourceFile.ReleaseBuffer();
		//����ͼ����ʾ����
		m_pFilterGraph->SetDisplayWindow(m_videoWindow.GetSafeHwnd());
		//���ô�����Ϣ֪ͨ
		m_pFilterGraph->SetNotifyWindow(this->GetSafeHwnd());
		//��ʾ��һ֡ͼ��
		m_pFilterGraph->Pause();
		/////////////////////////////////////////////////////////////
		m_pFilterGraph->SetCurrentPosition(m_dblPosition);
		m_pFilterGraph->Run();
		SetTimer(1,100,NULL);
	}

	CDialog::OnTimer(nIDEvent);
}
