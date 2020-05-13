
// UpdateNowNewsAVDlg.cpp : ��@��
//

#include "stdafx.h"
#include "UpdateNowNewsAV.h"
#include "UpdateNowNewsAVDlg.h"
#include <stdio.h>				//C file lib
#include <fstream>				//C++ file lib
#include <stdio.h>
using namespace std;
using namespace net_tw_airnetnoc;//Step 1_WebService
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CUpdateNowNewsAVDlg ��ܤ��




CUpdateNowNewsAVDlg::CUpdateNowNewsAVDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateNowNewsAVDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpdateNowNewsAVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUpdateNowNewsAVDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CUpdateNowNewsAVDlg �T���B�z�`��

BOOL CUpdateNowNewsAVDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	//CString PostData;
	//PostData=_T("op=source_nownews&row=1030050 || �F�v || 2010/05/26 09:42 || 12814169 || http://219.85.68.173/1030/v1030050.wmv || �{�������H��x�Ѱ��޺t�@�g��46�T�즡���u ||");
	//MessageBox(NowNewsHttpPost(PostData));
	SetTimer(1,100,NULL);
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CUpdateNowNewsAVDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUpdateNowNewsAVDlg::OnPaint()
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
HCURSOR CUpdateNowNewsAVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
CString CUpdateNowNewsAVDlg::NowNewsHttpPost(CString StrPostData)
{
	CString strHeaders =_T("Content-Type: application/x-www-form-urlencoded");
	// URL-encoded form variables -
	// name = "John Doe", userid = "hithere", other = "P&Q"
	CString strFormData; //= _T("op=source_nownews&row=1030050 || �F�v || 2010/05/26 09:42 || 12814169 || [Mail�t�� ĵ�i: �a���ƦrIP�����}�q�`���O�����D��]: http://219.85.68.173/1030/v1030050.wmv || �{�������H��x�Ѱ��޺t�@�g��46�T�즡���u ||");
	CString strServerName;
	strFormData=StrPostData;
	char buf[2];
	CString resultString =_T("");
	strServerName=_T("xpe5tv.tw-airnet.net");
	CInternetSession session;
	CHttpConnection* pConnection = session.GetHttpConnection(strServerName);
	try
	{
		if(pConnection!= NULL)
		{
			CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,_T("cgi-php/media_transform2.php"));
			BOOL result = pFile->SendRequest(strHeaders,(LPVOID)(LPCTSTR)strFormData, strFormData.GetLength());
			if(result)
			{
				//BOOL result1= pFile->ReadString(resultString);
				while( pFile->Read(buf, 1) > 0 )
				{
					resultString +=buf[0];
				}
			}
			else
			{
				resultString="Server time out";
			}
		}
		else
		{
			resultString="not Connecting Server";
		}
	}
	catch(...)
	{
		resultString="Server error";
	}
	return resultString;
}
BYTE CUpdateNowNewsAVDlg::toHex(const BYTE &x)
{
       return x > 9 ? x + 55: x + 48;
}
CString CUpdateNowNewsAVDlg::URLEncode(CString sIn)
{
       CString sOut;
       
       const int nLen = sIn.GetLength() + 1;
 
       register LPBYTE pOutTmp = NULL;
       LPBYTE pOutBuf = NULL;
       register LPBYTE pInTmp = NULL;
       LPBYTE pInBuf =(LPBYTE)sIn.GetBuffer(nLen);
       BYTE b = 0;
       
       //alloc out buffer
       pOutBuf = (LPBYTE)sOut.GetBuffer(nLen*3 - 2);//new BYTE [nLen  * 3];
 
       if(pOutBuf)
       {
              pInTmp   = pInBuf;
              pOutTmp = pOutBuf;
              
              // do encoding
              while (*pInTmp)
              {
                     if(isalnum(*pInTmp))
                            *pOutTmp++ = *pInTmp;
                     else
                            if(isspace(*pInTmp))
                                   *pOutTmp++ = '+';
                            else
                            {
                                   *pOutTmp++ = '%';
                                   *pOutTmp++ = toHex(*pInTmp>>4);
                                   *pOutTmp++ = toHex(*pInTmp%16);
                            }
                     pInTmp++;
              }
              *pOutTmp = '\0';
              //sOut=pOutBuf;
              //delete [] pOutBuf;
              sOut.ReleaseBuffer();
       }
       sIn.ReleaseBuffer();
       return sOut;
}
DWORD CUpdateNowNewsAVDlg::GetFileSize(CString filepath) 
{
    WIN32_FIND_DATA fileInfo;
    HANDLE hFind;
    DWORD fileSize;
    CString filename;
    filename = filepath;
    hFind = FindFirstFile(filename,&fileInfo);
    if(hFind != INVALID_HANDLE_VALUE)
        fileSize = fileInfo.nFileSizeLow;
    
    FindClose(hFind); 
    return fileSize;
}
void CUpdateNowNewsAVDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	//study
	//Step1:read filepath.txt and filename.txt
	KillTimer(1);
	fstream filename,filepath;//filename.txt//filepath.txt
	fstream fileAllList;
	int intfilenamecount,intfilepathcount;
	int intAllListCount;
	CString StrUpdateNowNewsAVLog;
	CString StrAllListFileName; 
	CTime timeNow=CTime::GetCurrentTime();
	FILE *pfUpdateNowNewsAVLog;
	FILE *pFileSize;
	DWORD dwFileSize;
	int i,j;
	i=0;
	j=0;
	StrUpdateNowNewsAVLog=timeNow.Format("%Y%m%d");
	StrAllListFileName=timeNow.Format("%Y%m%d.txt");
	StrUpdateNowNewsAVLog+="Updatelog.txt";
	char chrdata[500];
	CString StrAll;
	CString StrName;
	CString StrName1;
	CString StrName2;
	CString StrPath;
	CString StrNetPath;
	CString StrNetPath1;
	CString StrNetPath2;
	CString StrHttpPostAns;
	CString PostData;
	CString StrYearFolder;
	CString StrYearFolder1;
	CString StrWebServiceError;
	char chrd1[100],chrd2[100],chrd3[100],chrd4[100],chrd5[100],chrd6[100],chrd7[100],chrd8[100];
	CString StrFtpPath;
	CString StrWMVFileName;
	bool blncopy;
	noc_Service noc_S;
	CoInitialize(NULL);
	try
	{
		noc_S.KeepaLive(320);
	}
	catch(...)
	{
		StrWebServiceError="WebService Error...";
	}

	filename.open("filename.txt",ios::in);
	filepath.open("filepath.txt",ios::in);
	fileAllList.open(StrAllListFileName.GetBuffer(0),ios::in);

	intAllListCount=-1;//-1�O�]���ɩM�̫�@�欰����ҳy��
	while(!fileAllList.eof())
	{
		fileAllList.getline(chrdata,500);
		intAllListCount++;
	}
	while(!filename.eof())
	{
		filename.getline(chrdata,500);
		StrAll=chrdata;
		if(StrAll.GetLength()>3)
		{
			m_Array1.Add(StrAll);
		}
	}
	intfilenamecount=m_Array1.GetSize();
	while(!filepath.eof())
	{
		filepath.getline(chrdata,500);
		StrAll=chrdata;
		sscanf (StrAll.GetBuffer(0) ,"%[^||] || %s || %s %s || %s || %s || %[^||] || %[^||]",chrd1,chrd2,chrd3,chrd4,chrd5,chrd6,chrd7,chrd8);
		StrYearFolder=chrd3;
		StrYearFolder=StrYearFolder.Mid(0,4);
		StrYearFolder1=StrYearFolder;
		StrYearFolder+="\\";
		StrYearFolder1+="_big\\";		
		if(StrAll.GetLength()>3)
		{
			m_Array2.Add(StrAll);
		}
	}
	intfilepathcount=m_Array2.GetSize();
	if(intfilenamecount>=intfilepathcount)
	{
		j=intfilepathcount;
	}
	else
	{
		j=intfilenamecount;
	}
	filename.close();
	filepath.close();
	fileAllList.close();
	//////////////////////////////////////////////////////////////
	//Loop
	//Step2:copy the wmv to mms Server
	//Step3:http post message
	//Step4: call WebService
	//CTime t1=CTime::GetCurrentTime();
	//CString StrYearFolder;
	//StrYearFolder.Format("%d\\",t1.GetYear());
	String ^netStrBuf;
	netStrBuf= gcnew String ("");
	pFileSize=fopen("WMVFileSize.txt","w");
	for(i=0;i<j;i++)
	{
		StrNetPath="W:\\";
		StrNetPath1="X:\\";
		StrNetPath2="X:\\";
		StrNetPath+=StrYearFolder;
		StrNetPath1+=StrYearFolder;
		//StrNetPath2+=StrYearFolder;
		StrNetPath2+=StrYearFolder1;
		StrName=m_Array1.GetAt(i);

		StrName1=StrName.Mid(0,(StrName.GetLength()-4));
		StrName1+=".jpg";
		
		StrName2=StrName.Mid(0,(StrName.GetLength()-4));
		StrName2+="_0.jpg";

		StrPath=m_Array2.GetAt(i);
		sscanf (StrPath.GetBuffer(0) ,"%[^||] || %s || %s %s || %s || %s || %[^||] || %[^||]",chrd1,chrd2,chrd3,chrd4,chrd5,chrd6,chrd7,chrd8);
		
		StrFtpPath="ftp://jash:chwbnnoc@";
		StrFtpPath+=chrd6;
		StrFtpPath=StrFtpPath.Mid(0,(StrFtpPath.GetLength()-3));
		StrFtpPath+="wmv";
		
		//////////////////////////
		//��±N�ɦW�qMP4��WMV �]���n�p���ɮפj�p
		int intnumber,n;
		bool blncheck;
		CString StrOne;
		blncheck=false;
		intnumber=StrFtpPath.GetLength();
		for(n=(intnumber-1);n>=0;n--)
		{
			StrOne=StrFtpPath.Mid(n,1);
			if((StrOne=="/") && (!blncheck))
			{
				blncheck=true;
				continue;
			}
			if(!blncheck)
			{
				StrWMVFileName=StrOne+StrWMVFileName;
			}
		}
		/////////////////////////
		dwFileSize=GetFileSize(StrWMVFileName);
		fprintf(pFileSize,"%s,%d\n",StrWMVFileName.GetBuffer(0),dwFileSize);
		StrWMVFileName="";
		StrAll="";
		//////////////////////////////
		//StrAll.Format("%s|| %s || %s %s || %d || %s || %s|| %s||",chrd1,chrd2,chrd3,chrd4,dwFileSize,StrFtpPath,chrd7,chrd8);//���s�զX��T
		CString StrSize;
		StrSize.Format("|| %d ||",dwFileSize);
		
		StrAll=StrPath;
		StrAll.Replace("192.168.0.200","ftp://jash:chwbnnoc@192.168.0.200");
		StrAll.Replace(".mp4",".wmv");
		StrAll.Replace("|| 9999 ||",StrSize);
		//////////////////////////////

		StrNetPath+=StrName;
		StrNetPath1+=StrName1;
		StrNetPath2+=StrName2;
		blncopy=CopyFile(StrName2,StrNetPath2,false);
		blncopy=CopyFile(StrName1,StrNetPath1,false);
		blncopy=CopyFile(StrName,StrNetPath,false);
		//blncopy=true;
		if(blncopy==true)
		{
			pfUpdateNowNewsAVLog=fopen(StrUpdateNowNewsAVLog.GetBuffer(0),"a");
			PostData="op=source_nownews&row=";
			PostData+=URLEncode(StrAll);//PostData+=URLEncode(StrPath);
			StrHttpPostAns=NowNewsHttpPost(PostData);
			fprintf(pfUpdateNowNewsAVLog,"%s;;;%s\n",StrAll.GetBuffer(0),StrHttpPostAns.GetBuffer(0));//fprintf(pfUpdateNowNewsAVLog,"%s;;;%s\n",StrPath.GetBuffer(0),StrHttpPostAns.GetBuffer(0));
			fclose(pfUpdateNowNewsAVLog);
			pfUpdateNowNewsAVLog=NULL;
			DeleteFile(StrName);
			DeleteFile(StrName1);
			DeleteFile(StrName2);
			try
			{
				//noc_S.SetServiceStatusByID(320,0,j,netStrBuf);//�ǰe��������
				noc_S.SetServiceStatusByID(320,0,intAllListCount,netStrBuf);//�ǰe���ѵ���
			}
			catch(...)
			{
				StrWebServiceError="WebService Error...";
			}
		}
		else
		{
			try
			{
				netStrBuf="�ɮ׵L�k�ƻs������Ϻо�";
				noc_S.SetServiceStatusByID(320,1,0,netStrBuf);
			}
			catch(...)
			{
				StrWebServiceError="WebService Error...";
			}
		}
	}
	//////////////////////////////////////////////////////////////
	fclose(pFileSize);
	CoUninitialize();
	this->OnOK();
	CDialog::OnTimer(nIDEvent);
}
