
// UpdateNowNewsAVDlg.cpp : ��@��
//

#include "stdafx.h"
#include "UpdateNowNewsAV.h"
#include "UpdateNowNewsAVDlg.h"

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
	CString PostData;
	PostData=_T("op=source_nownews&row=1030050 || �F�v || 2010/05/26 09:42 || 12814169 || http://219.85.68.173/1030/v1030050.wmv || �{�������H��x�Ѱ��޺t�@�g��46�T�즡���u ||");
	MessageBox(NowNewsHttpPost(PostData));
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
	strServerName=_T("xpe5tv.tw-airnet.net");
	CInternetSession session;
	CHttpConnection* pConnection = session.GetHttpConnection(strServerName);
	CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,_T("cgi-php/media_transform.php"));
	BOOL result = pFile->SendRequest(strHeaders,(LPVOID)(LPCTSTR)strFormData, strFormData.GetLength());
	char buf[2];
	CString resultString =_T("");
	//BOOL result1= pFile->ReadString(resultString);
	while( pFile->Read(buf, 1) > 0 )
	{
		resultString +=buf[0];
	}
	return resultString;
}
