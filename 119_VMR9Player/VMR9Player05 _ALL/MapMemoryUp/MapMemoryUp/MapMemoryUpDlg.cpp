// MapMemoryUpDlg.cpp : ��@��
//

#include "stdafx.h"
#include "MapMemoryUp.h"
#include "MapMemoryUpDlg.h"
#include <Mmsystem.h>
///////////////////////////////////////////////////////
//Wininet.lib
#include <afxinet.h>		//http_download
#define BUFFER_SIZE 2048//http_download
///////////////////////////////////////////////////////
#include <fstream>
using namespace std;
///////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////
#define EXPORTED_DLL_FUNCTION \
 __declspec(dllexport) __stdcall
void EXPORTED_DLL_FUNCTION jashGetValue (char *outData);
void EXPORTED_DLL_FUNCTION jashSetValue (char *inData);
//////////////////////////////////////
TCHAR gstrCurDrt[500];//�s��ب�ؿ��r��
TCHAR gstrCurDrt01[500];//�s��ب�ؿ��r��
CString StrListUrl;
CString StrServiceUrl;
CString StrServiceID;
CString StrHostDir;
bool blnMultiDir;
//**********************
CString StrKeepLive;
CString StrService01;
CString StrService00;
int intServiceCount=0;
///////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////////////////
	//MAP memory_step 05
	inttimercount=2;
	ReadXMLConfig();
	if(!XMLList2TXTList())
	{
		CreateDefaultList();
	}
	////////////////////////////////////////////////////////////////////////////////////////
	InitList2CArray();
	SetTimer(1,1000,NULL);
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}
void CMapMemoryUpDlg::List2CArray()
{
	fstream a;
	CString StrDataBuf;
	char data[500];
	char chrd00[200],chrd01[200],chrd02[200],chrd03[200];
	a.open("list.txt",ios::in);
	m_intArrayCount=0;
	m_intArrayIndex=0;
	m_ArraySource.RemoveAll();
	if(a)
	{
		while(!a.eof())
		{
			a.getline(data,500);
			sscanf (data ,"%[^' || '] || %[^' || '] || %[^' || '] || %s",chrd00,chrd01,chrd02,chrd03);
			StrDataBuf.Format("%s,0",chrd00);
			m_ArraySource.Add(StrDataBuf);
		}
		a.close();
		m_intArrayCount=m_ArraySource.GetSize();
		m_intArrayIndex=0;
	}
}
void CMapMemoryUpDlg::InitList2CArray()
{
	bool blnfirst=false;
	fstream a;
	char data[500];
	char chrd00[200],chrd01[200],chrd02[200],chrd03[200];
	CString StrDataBuf;
	int inttmp;
	int intSYear,intSMonth,intSDay,intSHour,intSMinute,intSSecond;
	int intEYear,intEMonth,intEDay,intEHour,intEMinute,intESecond;
	int intMovieDay,intMovieHour,intMovieMinute,intMovieSecond;
	a.open("list.txt",ios::in);
	m_intArrayCount=0;
	m_intArrayIndex=0;
	m_ArraySource.RemoveAll();
	if(a)
	{
		while(!a.eof())
		{
			a.getline(data,500);
			sscanf (data ,"%[^' || '] || %[^' || '] || %[^' || '] || %s",chrd00,chrd01,chrd02,chrd03);
			if(!blnfirst)
			{
				//******
				inttmp=atoi(chrd02);
				intSYear=inttmp/10000;
				intSMonth=(inttmp%10000)/100;
				intSDay=(inttmp%10000)%100;
				inttmp=atoi(chrd03);
				intSHour=inttmp/10000;
				intSMinute=(inttmp%10000)/100;
				intSSecond=(inttmp%10000)%100;
				//CTime time4( 1999, 3, 19, 22, 15, 0 ); // 10:15PM March 19, 1999
				CTime STime(intSYear,intSMonth,intSDay,intSHour,intSMinute,intSSecond);
				
				//******
				CTime CuttTime = CTime::GetCurrentTime();
				
				//******
				inttmp=atoi(chrd01);
				intMovieSecond=inttmp%60;
				intMovieMinute=inttmp/60;
				if(intMovieMinute>=60)
				{
					intMovieMinute=(inttmp/60)%60;
					intMovieHour=(inttmp/60)/60;
					if(intMovieHour>=24)
					{
						intMovieHour=((inttmp/60)/60)%24;
						intMovieDay=((inttmp/60)/60)/24;
					}
					else
					{
						intMovieDay=0;
					}
				}
				else
				{
					intMovieHour=0;
					intMovieDay=0;
				}
				CTimeSpan ts_day(intMovieDay,intMovieHour,intMovieMinute,intMovieSecond); // �� �� �� ��
				CTime ETime=STime+ts_day;
				if(STime <=CuttTime && CuttTime<=ETime)
				{
					blnfirst=true;
					CTimeSpan ts=CuttTime-STime;
					double dbltime;
					dbltime=ts.GetTotalSeconds();
					dbltime+=7.0;
					StrDataBuf.Format("%s,%d",chrd00,((int)dbltime));
					m_ArraySource.Add(StrDataBuf);
				}
			}
			else
			{
					StrDataBuf.Format("%s,0",chrd00);
					m_ArraySource.Add(StrDataBuf);
			}
		}
		//********
		a.close();
	}
	m_intArrayCount=m_ArraySource.GetSize();
	m_intArrayIndex=0;
	char chrdata[200]="";
	CString theString=m_ArraySource.GetAt(m_intArrayIndex);
	strcpy(chrdata,theString.GetBuffer(0));
	jashSetValue (chrdata);
	char outData[200];
	jashGetValue (outData);
	MessageBox(outData);
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
	char data[200]="";
	if(!m_hPro)//�P�_�O�_�i�H�������{��
	{
		CallPlayer();
	}
	UpdateData(true);
	jashGetValue(data);
	if( data != NULL ) 
	{
		strcpy(StrData.GetBuffer(0),data);
		if(StrData=="")
		{
			char data[200];
			if((m_intArrayIndex+1)<m_intArrayCount)
			{
				m_intArrayIndex++;
				theString=m_ArraySource.GetAt(m_intArrayIndex);
			}
			else
			{
				if(!XMLList2TXTList())
				{
					CreateDefaultList();
				}
				List2CArray();
				theString=m_ArraySource.GetAt(m_intArrayIndex);
			}
			m_V1=theString;
			UpdateData(false);
			strcpy(data,theString.GetBuffer(0));
			jashSetValue(data);
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
	char  szExeFile[] = "C:\\Shop\\VMR9Player.exe";
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
bool CMapMemoryUpDlg::ReadXMLConfig()//step 3:Ū��XML
{
	MSXML2::IXMLDOMDocumentPtr pDoc;
	_variant_t vtStr;
	bool blnRead=false;
	blnMultiDir=false;
	CString StrMessage;
	CString StrBuff;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   StrMessage="�إ�Ū���M�檫�󥢱�";
	   WriteLogFile(0,StrMessage);
	   EmailError(StrMessage);
	   return false;
	}
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt01);//���o�ثe�{�����|
	if( gstrCurDrt01[nLen]!='\\' )
	{
		gstrCurDrt01[nLen++] = '\\';
		gstrCurDrt01[nLen] = '\0';
	}
	CString strFileName1 = gstrCurDrt01;
	strFileName1 +="Config.xml";
	blnRead=pDoc->load((_bstr_t)strFileName1); 
	if(blnRead)//��11.0�����\��
	{
		MSXML2::IXMLDOMNodePtr pNodeRoot;
		pNodeRoot=pDoc->selectSingleNode("//ListURL");
		pNodeRoot->get_nodeTypedValue(&vtStr);
		StrBuff=vtStr.bstrVal;
		StrListUrl=StrBuff;
		//**********************************************
		pNodeRoot=pDoc->selectSingleNode("//ServicURL");
		pNodeRoot->get_nodeTypedValue(&vtStr);
		StrBuff=vtStr.bstrVal;
		StrServiceUrl=StrBuff;
		//**********************************************
		pNodeRoot=pDoc->selectSingleNode("//ServicID");
		pNodeRoot->get_nodeTypedValue(&vtStr);
		StrBuff=vtStr.bstrVal;
		StrServiceID=StrBuff;
		//**********************************************
		pNodeRoot=pDoc->selectSingleNode("//HostDir");
		pNodeRoot->get_nodeTypedValue(&vtStr);
		StrBuff=vtStr.bstrVal;
		StrHostDir=StrBuff;
		//**********************************************
		pNodeRoot=pDoc->selectSingleNode("//MultiDir");
		pNodeRoot->get_nodeTypedValue(&vtStr);
		StrBuff=vtStr.bstrVal;
		StrBuff.MakeLower();
		if(StrBuff=="false")
		{
			blnMultiDir=false;
		}
		else
		{
			blnMultiDir=true;
		}
		//**********************************************
		StrKeepLive=StrServiceUrl+"OP=KeepaLive&ServiceID="+StrServiceID;
		StrService01=StrServiceUrl+"OP=SetServiceStatusByID&ServiceID="+StrServiceID+"&Status=1&Value=0";
		StrService00=StrServiceUrl+"OP=SetServiceStatusByID&ServiceID="+StrServiceID+"&Status=0&Value=0";;
		return true;
	}
	else
	{
		return false;
	}
}
void CMapMemoryUpDlg::EmailError(CString StrWriteMessage)
{
	FILE *pfError;
	pfError=NULL;
	pfError=fopen("ErrorInfo.txt","w");
	if(pfError!=NULL)
	{
		fprintf(pfError,"%s\t%s",StrListUrl.GetBuffer(0),StrWriteMessage.GetBuffer(0));
		fclose(pfError);
	}
	ShellExecute(NULL,"open","MyEmailClient.exe",NULL,NULL,SW_SHOWNORMAL); 
}
void CMapMemoryUpDlg::WriteLogFile(int intindex,CString StrMessage)
{
	FILE *pf=NULL;
	CTime TimeNow;
	CString StrWriteMessage;
	TimeNow=CTime::GetCurrentTime();
	StrWriteMessage=TimeNow.Format("%Y-%m-%d %H:%M:%S ::");
	StrWriteMessage+=StrMessage;
	if(intindex==0)
	{
		//Errlog
		pf=fopen("Errlog.txt","a");
	}
	else
	{
		//Meslog
		pf=fopen("Meslog.txt","a");
	}
	if(pf!=NULL);
	{
		fprintf(pf,"%s\n",StrWriteMessage.GetBuffer(0));
		fclose(pf);
	}
}
bool CMapMemoryUpDlg::XMLList2TXTList()//step 4:Ū��XML
{
	FILE *pf=NULL;
	MSXML2::IXMLDOMDocumentPtr pDoc;
	int i,j;
	int k,l;
	CString StrData;
	_variant_t vtStr;
	bool blnRead=false;
	CString StrMessage;
	StrMessage="";
	///////////////////////////////////////////////////////////
	CTime t1;
	t1=CTime::GetCurrentTime();
	int inthr,intmin,intsec;
	inthr=0;
	intmin=0;
	intsec=0;
	CString StrtimeData01,StrtimeData02;
	CString StrHr,StrMin,StrSec;
	CString StrDate;
	CString StrTime;
	long lngDate;
	long lngTime;
	long lngtimeData01;
	long lngtimeData02; 
	StrtimeData01=t1.Format("%Y%m%d");
	inthr=t1.GetHour();
	intmin=t1.GetMinute();
	intsec=t1.GetSecond();
	if(inthr<10)
	{
		StrHr.Format("0%d",inthr);
	}
	else
	{
		StrHr.Format("%d",inthr);
	}
	if(intmin<10)
	{
		StrMin.Format("0%d",intmin);
	}
	else
	{
		StrMin.Format("%d",intmin);
	}
	if(intsec<10)
	{
		StrSec.Format("0%d",intsec);
	}
	else
	{
		StrSec.Format("%d",intsec);
	}
	StrtimeData02=StrHr+StrMin+StrSec;
	lngtimeData01=atoi(StrtimeData01.GetBuffer(0));
	lngtimeData02=atoi(StrtimeData02.GetBuffer(0));
	///////////////////////////////////////////
	if(DownLoadList())
	{
		StrMessage="�M��U������";
		WriteLogFile(1,StrMessage);
	}
	else
	{
		StrMessage="�M��U������";
		WriteLogFile(0,StrMessage);
		EmailError(StrMessage);
		return false;
	}
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   StrMessage="�إ�Ū���M�檫�󥢱�";
	   WriteLogFile(0,StrMessage);
	   EmailError(StrMessage);
	   return false;
	}
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	CString strFileName1 = gstrCurDrt;
	strFileName1 +="list.xml";
	try//����M���ɮ׮ڥ��S������r��
	{
		blnRead=pDoc->load((_bstr_t)strFileName1);
	}
	catch(...)
	{
		StrMessage="Ū���M�楢��";
		WriteLogFile(0,StrMessage);
		EmailError(StrMessage);
		if(pf!=NULL)
		{
			fclose(pf);
		}
		return false;
	}
	if(blnRead)//��11.0�����\��
	{
		pf=fopen("list.txt","w");
		UpdateData(true);
		MSXML2::IXMLDOMNodeListPtr  pNodeList;
		MSXML2::IXMLDOMNodePtr pNodeRoot;
		pNodeRoot=pDoc->selectSingleNode("//list");
		pNodeRoot->get_childNodes(&pNodeList);
		j=pNodeList->length;
		if(j<=0)
		{
			StrMessage="Ū���M�楢��";
			WriteLogFile(0,StrMessage);
			EmailError(StrMessage);
			if(pf!=NULL)
			{
				fclose(pf);
			}
			return false;
		}
		for(i=0;i<j;i++)
		{
			k=0;
			l=0;
			StrData="";
			CString StrBuff,StrFileName,StrMediaLen,StrGetMediaLen;
			int intMediaLen,intGetMediaLen;
			MSXML2::IXMLDOMNodePtr pRootchildNode;
			MSXML2::IXMLDOMNodeListPtr pchildNodeList;
			pRootchildNode=pNodeList->item[i];
			pRootchildNode->get_childNodes(&pchildNodeList);
			l=pchildNodeList->length;
			if(l<=3)
			{
				StrMessage="Ū���M�楢��";
				WriteLogFile(0,StrMessage);
				EmailError(StrMessage);
				if(pf!=NULL)
				{
					fclose(pf);
				}
				return false;
			}
			for(k=0;k<l;k++)
			{
				MSXML2::IXMLDOMNodePtr pchildNode;
				////////////////////////////////////////////////////////
				pchildNode=pchildNodeList->item[k];
				pchildNode->get_nodeTypedValue(&vtStr);
				StrBuff=vtStr.bstrVal;
				StrBuff.MakeLower();//���b�@����p�g
				////////////////////////////////////////////////////////
				switch(k)
				{
				case 0:
					if(blnMultiDir==false)
					{
						StrBuff=StrHostDir+StrBuff;//�T�w��@�����Ϻо�
					}
					else
					{
						StrBuff.Replace("5tv-m1","I:");
						StrBuff.Replace("5tv-m2","J:");
						StrBuff.Replace("5tv-m3","K:");
						StrBuff.Replace("5tv-m4","L:");
						StrBuff.Replace("mms1","I:");
						StrBuff.Replace("mms2","J:");
						StrBuff.Replace("mms3","K:");
						StrBuff.Replace("mms4","L:");
					}
					StrBuff.Replace("/","\\");
					StrFileName=StrBuff;
					break;
				case 1:
					StrMediaLen=StrBuff;
					break;
				case 2:
					StrDate=StrBuff;
					lngDate=atoi(StrDate.GetBuffer(0));
					break;
				case 3:
					StrTime=StrBuff;
					lngTime=atoi(StrTime.GetBuffer(0));;
					break;
				}
				//*********************************************
				StrData+=StrBuff;
				StrData+=" || ";
			}
			if(i==0)
			{
				if(!((lngDate<=lngtimeData01) && (lngTime<=lngtimeData02)))
				{
					StrMessage="�M��ɶ����~:";
					StrMessage+=StrFileName;
					WriteLogFile(0,StrMessage);
					if(pf!=NULL)
					{
						fclose(pf);
					}
					EmailError(StrMessage);
					return false;
				}
			}
			///*//�v����T�ˬd start
			CFileStatus rStatus;
			if(CFile::GetStatus(StrFileName, rStatus))
			//if(::PathFileExists(StrFileName.GetBuffer(0)))
			{
				StrMessage=StrFileName;
				StrMessage+="�ɮצs�b";
				WriteLogFile(1,StrMessage);				
			}
			else
			{
				StrMessage=StrFileName;
				StrMessage+="�ɮװ�������";
				WriteLogFile(0,StrMessage);
				if(pf!=NULL)
				{
					fclose(pf);
				}
				EmailError(StrMessage);
				return false;
			}
			StrGetMediaLen=GetMediaLen(StrFileName);
			char *chrlen;
			chrlen=StrMediaLen.GetBuffer(0);
			intMediaLen=atoi(chrlen);
			chrlen=StrGetMediaLen.GetBuffer(0);
			intGetMediaLen=atoi(chrlen);

			if(intMediaLen<=intGetMediaLen)
			{
				StrData=StrData.Mid(0,(StrData.GetLength()-1));
				fprintf(pf,"%s\n",StrData.GetBuffer(0));
				StrMessage=StrFileName;
				StrMessage+="�v�����ץ��T";
				WriteLogFile(1,StrMessage);	
			}
			else
			{
				int intsubMediaLen;
				intsubMediaLen=intMediaLen-intGetMediaLen;//�ۮt���
				StrData.Format("%s || %d || %s || %s||",StrFileName.GetBuffer(0),intGetMediaLen,StrDate.GetBuffer(0),StrTime.GetBuffer(0));
				fprintf(pf,"%s\n",StrData.GetBuffer(0));
				if(intsubMediaLen<60)
				{
					int year = lngDate/10000;
					int month = (lngDate-(year*10000))/100;
					int date = (lngDate-(year*10000))%100;
					int hour = lngTime/10000;
					int minute = (lngTime-(hour*10000))/100;
					int second = (lngTime-(hour*10000))%100;
					CTime tm01(year,month,date,hour,minute,second);//�o�N�H���ݴ����ɶ�
					CTimeSpan ts_day(0,0,0,intGetMediaLen); // �� �� �� ��
					CTime tm02=tm01+ts_day;
					StrData.Format("C:\\Base.wmv || %d || %04d%02d%02d || %02d%02d%02d ||",intsubMediaLen,tm02.GetYear(),tm02.GetMonth(),tm02.GetDay(),tm02.GetHour(),tm02.GetMinute(),tm02.GetSecond());
					fprintf(pf,"%s\n",StrData.GetBuffer(0));

					//*****************************************
					StrMessage=StrFileName;
					StrMessage+="�v�����׿��~";
					WriteLogFile(0,StrMessage);
					EmailError(StrMessage);
				}
				else
				{
					StrMessage=StrFileName;
					StrMessage+="�v�����׿��~�A�åB�W�L60��";
					WriteLogFile(0,StrMessage);
					if(pf!=NULL)
					{
						fclose(pf);
					}
					EmailError(StrMessage);
					return false;
				}
			}
			//*///�v����T�ˬd end
		}
		//StrData="@ || 30 || 30001231 || 0000 || ";
		//StrData=StrData.Mid(0,(StrData.GetLength()-1));
		//fprintf(pf,"%s",StrData.GetBuffer(0));
	}
	if(pf!=NULL)
	{
		StrMessage="Ū���M�槹��";
		WriteLogFile(1,StrMessage);
		if(pf!=NULL)
		{
			fclose(pf);
		}
		return true;
	}
	else
	{
		StrMessage="Ū���M�楢��";
		WriteLogFile(0,StrMessage);
		EmailError(StrMessage);
		return false;
	}
}
bool CMapMemoryUpDlg::CreateDefaultList()
{
	CTime t1;
	t1=CTime::GetCurrentTime();
	int inthr,intmin;
	inthr=0;
	intmin=0;
	CString StrData,StrDataBuf;
	CString StrHr,StrMin;
	FILE *pf=NULL;
	pf=fopen("list.txt","w");
	if(pf==NULL)
	{
		return false;
	}
	do
	{
		StrData="C:\\Base.wmv || 1800 || ";
		StrDataBuf=t1.Format("%Y%m%d || ");
		if(inthr<10)
		{
			StrHr.Format("0%d",inthr);
		}
		else
		{
			StrHr.Format("%d",inthr);
		}
		if(intmin<10)
		{
			StrMin.Format("0%d",intmin);
		}
		else
		{
			StrMin.Format("%d",intmin);
		}
		StrData=StrData+StrDataBuf;
		StrData=StrData+StrHr+StrMin;
		StrData=StrData+"00";
		StrData=StrData+" ||";
		fprintf(pf,"%s\n",StrData.GetBuffer(0));
		intmin+=30;
		if( intmin>=60)
		{
			inthr++;
			intmin=0;
		}
	}while(inthr<24);
	//StrData="@ || 1800 || 30001231 || 0000 || ";
	//StrData=StrData.Mid(0,(StrData.GetLength()-1));
	//fprintf(pf,"%s",StrData.GetBuffer(0));
	if(pf!=NULL)
	{
		fclose(pf);
		return true;
	}
}
bool CMapMemoryUpDlg::GetWebFile(CString theUrl, CString Filename)//http_download
{
    CInternetSession session;
    CInternetFile* file = NULL;
    try
    {
        // Try to connect with the URL
        file = (CInternetFile*)session.OpenURL(theUrl); 
    }
    catch (CInternetException* m_pException)
    {
        // if some error occurs, set the file with NULL
        file = NULL; 
        m_pException->Delete();
        return FALSE;
    }

    BOOL bRet = FALSE;
    // use dataStore to save the file content
    CStdioFile dataStore;
    if(dataStore.Open(Filename, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite | CFile::typeBinary))
    {
        if (file)
        {
            UINT somelen = 0;
            BYTE somecode[BUFFER_SIZE];
            while((somelen = file->Read(somecode, BUFFER_SIZE)) > 0)
            {
                dataStore.Write(somecode, somelen);
            }
            bRet = TRUE;
        }
        dataStore.Close();
    }
    if(file)
    {
        file->Close();
        delete file;
    }
    return bRet;
}
bool CMapMemoryUpDlg::DownLoadList()
{
	//DeleteFile("live.wme");
	DeleteFile("list.xml");
	DeleteFile("list.txt");
	bool blnGetFile; 
	CString theUrl=StrListUrl;
	CString Filename="list.xml";
	blnGetFile=GetWebFile(theUrl,Filename);//for .net & PHP
	return blnGetFile;
	
}
CString CMapMemoryUpDlg::GetMediaLen(CString StrSouFileName)
{
	char chrLen[128];
	int i=0;
	long re=-1;
	CString MediaLen;
	CString StrFileName="open ";
	StrFileName+=StrSouFileName;
	StrFileName+=" type MPEGVideo alias Media";
	re=mciSendString(StrFileName.GetBuffer(0),"",0,0);//Winmm.lib,Mmsystem.h
	re=mciSendString("status Media length", chrLen, 128, 0);//Winmm.lib,Mmsystem.h
	//i=atoi(chrLen)/1000/60;//��
	i=atoi(chrLen)/1000;//��
	MediaLen.Format("%d",i);
	re=mciSendString("close Media","",0,0);
	return MediaLen;
}