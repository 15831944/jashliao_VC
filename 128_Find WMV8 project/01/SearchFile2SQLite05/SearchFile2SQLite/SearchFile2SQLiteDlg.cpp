
// SearchFile2SQLiteDlg.cpp : ��@��
//

#include "stdafx.h"
#include "SearchFile2SQLite.h"
#include "SearchFile2SQLiteDlg.h"
//////////////////////////////////////////
//sqlite step 01
#include "sqlite3.h"
#pragma comment(lib, "sqlite3.lib")
//////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
TCHAR gstrCurDrt[500];//�s��ب�ؿ��r��
unsigned long gunlognumber=0;
// �� App About �ϥ� CAboutDlg ��ܤ��
/////////////////////////////////////////////
//sqlite step 02
int gintRowNumber=0;
TCHAR strCurDrt[500];
CString StrEXEPath;
CString StrlogPath;
CString StrCmd;
static int _sql_callback(void * notused, int argc, char ** argv, char ** szColName)
{
    int i;
	int j=0;
	FILE *pf;
	pf=fopen("SearchFile2SQLite.txt","a");
	gunlognumber+=(argc/gintRowNumber);
    for ( i=0; i < argc; i++ )
    {
		j++;
		if(!(j < gintRowNumber))
		{
			j=0;
			CFileFind finder;
			BOOL bResult = finder.FindFile(argv[i]);
			if(bResult)
			{
				CString strFileName;
				CString strPathName;
				CString strFileTitle;
				CString strBatPath;
				FILE *pfBat=NULL;
				strPathName=argv[i];
				strFileName=strPathName.Mid((strPathName.ReverseFind('\\')+1),(strPathName.GetLength()-strPathName.ReverseFind('\\')));
				strFileTitle="TXT_data\\"+strFileName;
				strBatPath=strCurDrt;
				strBatPath+="GetMediaInfo.bat";
				pfBat=fopen(strBatPath.GetBuffer(0),"w");
				if(pfBat!=NULL)
				{
					StrEXEPath=strCurDrt;
					StrEXEPath+="MediaInfo_cmd\\MediaInfo.exe";
					StrEXEPath+=" ";
					strPathName+=" > ";
					StrlogPath=strCurDrt;
					StrlogPath+=strFileTitle;
					StrlogPath+=".txt";
					StrCmd=StrEXEPath+strPathName+StrlogPath;
					fprintf(pfBat,"%s\n",StrCmd.GetBuffer(0));
					fclose(pfBat);
					//ShellExecute(NULL,"open",strBatPath.GetBuffer(0),NULL,NULL,SW_SHOWNORMAL); 
					PROCESS_INFORMATION pi;
					STARTUPINFO si;
					memset(&si,0,sizeof(si));
					si.cb=sizeof(si);
					si.wShowWindow=SW_SHOW;
					si.dwFlags=STARTF_USESHOWWINDOW;
					BOOL fRet=CreateProcess(NULL,
										strBatPath.GetBuffer(0),
										NULL,
										NULL,
										FALSE,
										NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
										NULL,
										NULL,
										&si,
										&pi);
						if(!fRet)   
						{   
							int errorNo = ::GetLastError();
							AfxMessageBox("create process failed");     
						}
						else
						{
							::WaitForSingleObject(pi.hProcess, INFINITE); 
						}
				}//if(pfBat!=NULL)
			}//if(bResult)
			fprintf(pf,"%s\n",argv[i] == 0 ? "NUL" : argv[i] );
		}//if(!(j < gintRowNumber))
    }//for
	fclose(pf);
    return 0;
}
/////////////////////////////////////////////
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


// CSearchFile2SQLiteDlg ��ܤ��




CSearchFile2SQLiteDlg::CSearchFile2SQLiteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchFile2SQLiteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSearchFile2SQLiteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSearchFile2SQLiteDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTSearch, &CSearchFile2SQLiteDlg::OnBnClickedButsearch)
END_MESSAGE_MAP()


// CSearchFile2SQLiteDlg �T���B�z�`��

BOOL CSearchFile2SQLiteDlg::OnInitDialog()
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
	GetandSetParameter();//step 5:Ū��XML
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CSearchFile2SQLiteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSearchFile2SQLiteDlg::OnPaint()
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
HCURSOR CSearchFile2SQLiteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSearchFile2SQLiteDlg::GetandSetParameter()//step 4:Ū��XML
{
	MSXML2::IXMLDOMDocumentPtr pDoc;
	CTime t1=CTime::GetCurrentTime();
	_variant_t vtStr;
	bool blnRead=false;
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
	strFileName1 +="Config.xml";
	blnRead=pDoc->load((_bstr_t)strFileName1); 
	if(blnRead)//��11.0�����\��
	{
		MSXML2::IXMLDOMNodePtr  NodeData;
		////////////////////////////////////////////////////////////
		NodeData=pDoc->selectSingleNode("//Dir");	
		NodeData->get_nodeTypedValue(&vtStr);
		m_StrDir=vtStr.bstrVal;
		//MessageBox(m_StrDir);
		//*************************************************
		NodeData=pDoc->selectSingleNode("//SearchStr");	
		NodeData->get_nodeTypedValue(&vtStr);
		m_StrSearch=vtStr.bstrVal;
		//MessageBox(m_StrSearch);
		//*************************************************
	}
}
void CSearchFile2SQLiteDlg::BrowseDir(CString strDir)
{
	CFileFind ff;
	CString szDir = strDir;
	
	if(szDir.Right(1) != "\\")
		szDir += "\\";
	
	szDir += "*.*";
	CTime t1;
	CString StrData;
	BOOL res = ff.FindFile(szDir);
	
	while(res)
	{
		res = ff.FindNextFile();
		if(!ff.IsDirectory() && !ff.IsDots())
		{
			//�����w���ɮ׸�T
			StrData=ff.GetFileName();
			StrData=StrData.Mid(StrData.FindOneOf(".")+1);
			StrData.MakeLower();
			m_StrSearch.MakeLower();
			if(StrData==m_StrSearch)
			{
				StrData=ff.GetFilePath();
				SQLiteInsert(StrData);
				SetDlgItemText(IDC_FilePath,StrData);
			}
		}
	}
	ff.Close();//�����j�M
}
void CSearchFile2SQLiteDlg::OnBnClickedButsearch()
{
	// TODO:
	AfxBeginThread(ThreadRun,this,0,0,0,NULL);
}
void  CSearchFile2SQLiteDlg::SQLiteCreate()
{
	const char * sSQL1 = "create table FileList(id INTEGER PRIMARY KEY,filepath varchar(2000));";
	sqlite3 * db = 0;
	int ret = 0;
	char * pErrMsg = 0;
	ret = sqlite3_open("./SearchFile2SQLite.db", &db);
	if ( ret != SQLITE_OK )
	{
		this->OnOK();
	}
	sqlite3_exec( db, sSQL1, 0, 0, &pErrMsg );
	if ( ret != SQLITE_OK )
	{
		this->OnOK();
		sqlite3_free(pErrMsg);
	}
	sqlite3_close(db);
	db = 0;
}
void CSearchFile2SQLiteDlg::SQLiteInsert(CString StrData)
{
	sqlite3 * db = 0;
	int ret = 0;
	char * pErrMsg = 0;
	CString strSQL02;
	ret = sqlite3_open("./SearchFile2SQLite.db", &db);
	if ( ret != SQLITE_OK )
	{
		this->OnOK();
	}
	strSQL02.Format("insert into FileList values(null,'%s');",StrData.GetBuffer(0));
	sqlite3_exec( db, strSQL02.GetBuffer(0), 0, 0, &pErrMsg);
	sqlite3_close(db);
	db = 0;
}
void CSearchFile2SQLiteDlg::SQLite2File()
{
	sqlite3 * db = 0;
	int ret = 0;
	char * pErrMsg = 0;
	//const char * sSQL3 = "select * from FileList WHERE filepath LIKE '%wmv%';";
	const char * sSQL3 = "select * from FileList;";
	ret = sqlite3_open("./SearchFile2SQLite.db", &db);
	if ( ret != SQLITE_OK )
	{
		this->OnOK();
	}
	gintRowNumber=2;
	ret=sqlite3_exec( db, sSQL3, _sql_callback, 0, &pErrMsg);
	sqlite3_close(db);
	db = 0;
}
void CSearchFile2SQLiteDlg::RunSearch()
{
	DeleteFile("SearchFile2SQLite.db");
	DeleteFile("SearchFile2SQLite.txt");
	SQLiteCreate();
	BrowseDir(m_StrDir);
	SQLite2File();
}
UINT CSearchFile2SQLiteDlg::ThreadRun(LPVOID lpram)
{
	CSearchFile2SQLiteDlg *u=(CSearchFile2SQLiteDlg *)lpram;
	u->ShowWindow(SW_MINIMIZE);
	u->RunSearch();
	CString StrRET;
	StrRET.Format("There are %d rows of information on the SQLite DB",gunlognumber);
	u->MessageBox(StrRET);
	u->ShowWindow(SW_SHOW);
	return 0;
}