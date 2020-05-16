// VMR9PlayerDlg.cpp : ��@��
//

#include "stdafx.h"
#include "VMR9Player.h"
#include "VMR9PlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////
#define EXPORTED_DLL_FUNCTION \
 __declspec(dllexport) __stdcall
void EXPORTED_DLL_FUNCTION jashGetValue (char *outData);
void EXPORTED_DLL_FUNCTION jashSetValue (char *inData);
//////////////////////////////////////

// �� App About �ϥ� CAboutDlg ��ܤ��
CString StrNameBuf;
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


// CVMR9PlayerDlg ��ܤ��




CVMR9PlayerDlg::CVMR9PlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVMR9PlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVMR9PlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIDEO_WINDOW, m_videoWindow);
}

BEGIN_MESSAGE_MAP(CVMR9PlayerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_GRAPHNOTIFY,OnGraphNotify)////VMR9_step 04
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CVMR9PlayerDlg �T���B�z�`��

BOOL CVMR9PlayerDlg::OnInitDialog()
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
	InitialVariable();
	/////////////////////////////////////////////////////////////////////////////	
	ModifyStyle(0, WS_SYSMENU);	
	this->MoveWindow(m_lngLeft,m_lngTop,m_lngWidth,m_lngHeight,TRUE);
	RECT rc;
	this->GetClientRect(&rc);
	m_videoWindow.MoveWindow( &rc, true );
	//////////////////////////////////////////////////////////////////////////////	// TODO: �b���[�J�B�~����l�]�w
	CWnd * pw = GetDlgItem(IDC_VIDEO_WINDOW);
				CRect rect;
				pw->GetClientRect(&rect);
	mVideoClass.Clean();
	///*
	CString path = _T("C:\\Black.wmv");
	StrNameBuf=path;
	BSTR bstr = path.AllocSysString();  
	mVideoClass.InitInterfaces(bstr, pw,&rect);
	mVideoClass.Play();
	SysFreeString(bstr);
	//*/
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}
LRESULT CVMR9PlayerDlg::OnGraphNotify ( WPARAM wParam, LPARAM lParam )
{
	LONG evCode, evParam1, evParam2 ;
    HRESULT hr = S_OK ;
	CWnd * pw = GetDlgItem(IDC_VIDEO_WINDOW);
	CRect rect;
	pw->GetClientRect(&rect);
    while ( SUCCEEDED ( mVideoClass.pME -> GetEvent ( &evCode, &evParam1, &evParam2, 0 ) ) )
    {
        // Spin through the events
        hr = mVideoClass.pME -> FreeEventParams ( evCode, evParam1, evParam2 ) ;

        if ( evCode == EC_COMPLETE )
		{
			mVideoClass.pMC->Stop();
			mVideoClass.Clean();
			m_dblPosition=0.0;
			m_sourceFile=GetMapMemory(&m_dblPosition);//MAP memory_step 06
			if(m_sourceFile=="No Data")
				m_sourceFile = _T("C:\\Black.wmv");
			m_mediaFileName =GetFileTitleFromFileName(m_sourceFile,1);
			SetWindowText(_T("Media File Name: ") + m_mediaFileName);
			/////////////////////////////////////////////////////////
			BSTR bstr = m_sourceFile.AllocSysString();  
			mVideoClass.InitInterfaces(bstr, pw,&rect);
			SysFreeString(bstr);
			// Seek to the beginning
			mVideoClass.pMS->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
			LONGLONG pos=m_dblPosition*10000000;
			mVideoClass.pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame ,0, AM_SEEKING_NoPositioning);
			mVideoClass.pMC->Run();
		}
    }
    return 0L ;
}
void CVMR9PlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVMR9PlayerDlg::OnPaint()
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
HCURSOR CVMR9PlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CVMR9PlayerDlg::InitialVariable(void)
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
CString CVMR9PlayerDlg::GetMapMemory(double *dblPosition)//MAP memory_step 05
{
	CString StrData;
	CString StrClean=_T("");
	StrData=_T("");
	char data[200]="";
	jashGetValue(data);
	if( data != NULL ) 
	{
		int charLen = strlen(data);
		int len=0;
		len = MultiByteToWideChar(CP_ACP,0,data,charLen,NULL,0);
		TCHAR *buf = new TCHAR[len + 1];
		MultiByteToWideChar(CP_ACP,0,data,charLen,buf,len);
		buf[len] = '\0';
		StrData.Append(buf);
		delete [] buf;
		//MessageBox(StrData);
		if(StrData=="")
		{
			StrData="No Data";
			return StrData;
		}
	}

	//************************
	//sscanf
	char Schrd01[500],Schrd02[500];
	double fltp01;
	sscanf (data ,"%[^','],%s",Schrd01,Schrd02);
	fltp01=atof(Schrd02);

	//**********************
	*dblPosition=fltp01;
	int charLen = strlen(Schrd01);
	int len=0;
	len = MultiByteToWideChar(CP_ACP,0,Schrd01,charLen,NULL,0);
	TCHAR *buf = new TCHAR[len + 1];
	MultiByteToWideChar(CP_ACP,0,Schrd01,charLen,buf,len);
	buf[len] = '\0';
	StrData=_T("");
	StrData.Append(buf);
	delete [] buf;

	strcpy(data,"");
	jashSetValue(data);
	return StrData;
}
CString CVMR9PlayerDlg::GetFileTitleFromFileName(CString FileName, BOOL Ext)
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