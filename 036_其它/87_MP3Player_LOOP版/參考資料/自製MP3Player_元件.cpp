// EasyPlayer.cpp : implementation file
//

#include "stdafx.h"

#include "Player.h"
#include "vfw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


UINT LoopThread(LPVOID pParam);
/////////////////////////////////////////////////////////////////////////////
// Player

Player::Player(HWND hwParent)
{
	hwndParent=hwParent;

	m_sPath="";
	c_Player=NULL;
}

Player::Player()
: mZoom(0)
{
	hwndParent=NULL;

	m_sPath="";
	c_Player=NULL;;
}

Player::~Player()
{
	MCIWndDestroy(c_Player);
	c_Player=NULL;
	m_sPath="";
}

BEGIN_MESSAGE_MAP(Player, CWnd)
	//{{AFX_MSG_MAP(Player)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Player message handlers

void Player::OnDestroy() 
{
	CWnd::OnDestroy();
	
	MCIWndDestroy(c_Player);
	
}
//hwndParent�ķ�����
void Player::SetParent(HWND hParent)
{
	hwndParent=hParent;
}

HWND Player::GetParent()
{
	return hwndParent;
}
//Path�ķ�����
void Player::SetPath(CString sPath)
{
	m_sPath=sPath;
}

CString Player::GetPath()
{
	return m_sPath;
}
//����MCI�豸��ǰ״̬
/*
Operating mode       MCI constant 
not ready            MCI_MODE_NOT_READY 
open                 MCI_MODE_OPEN 
paused               MCI_MODE_PAUSE 
playing              MCI_MODE_PLAY 
recording            MCI_MODE_RECORD 
seeking              MCI_MODE_SEEK 
stopped              MCI_MODE_STOP 
*/
long Player::GetMode()
{
	char lp[3];
	long lMode;
	
	lMode=MCIWndGetMode(c_Player,lp,sizeof(lp));

	return lMode;
}

void Player::Kill()
{
	MCIWndClose(c_Player);
	/*
	�ú����򴰿ڷ���һ��WM_CLOSE��Ϣ,���ڽ��յ�����Ϣ֮��,�ر�����
	����MCI�ļ�,���رմ��ڡ���ȻSDK���ṩ��һ��MCIWndClose����,��
	�ú���ֻ�ܹر���MCIWnd�����д򿪵��ļ�,��MCIWnd�����Դ��ڿ���
	״̬,�Կ��Դ�����MCI�ļ������в��š�
	���³�����http://www.diybl.com/course/3_program/c++/cppsl/200819/96105.html
	*/
	MCIWndDestroy(c_Player);
}

void Player::Resume()
{
	//�ָ�����
	MCIWndResume(c_Player);
}

void Player::Play()
{
	//��ʼ����
	MCIWndPlay(c_Player);
}

void Player::Stop()
{
	//ֹͣ����
	MCIWndStop(c_Player);
}

void Player::Pause()
{
	//��ͣ
	MCIWndPause(c_Player);
}

HWND Player::Initialize()
{
	//�������ž��
	c_Player=MCIWndCreate(hwndParent,AfxGetInstanceHandle(),
		WS_CHILD | WS_VISIBLE| MCIWNDF_NOMENU| MCIWNDF_NOTIFYALL| MCIWNDF_NOPLAYBAR,
		m_sPath);
	//����ʱ���ʽ,"frames"֡����"ms"����
	MCIWndSetTimeFormat(c_Player,_T("ms"));
	//���ø�������
	MCIWndSetActiveTimer(c_Player,100);
	//�õ���ǰ����
	lVolume=MCIWndGetVolume(c_Player);

	return c_Player;
}

void Player::Close()
{
	//�رյ�ǰ�򿪵�mci�ļ�
	MCIWndClose(c_Player);
}

UINT LoopThread(LPVOID pParam)
{

	CParams* pParameters;
	pParameters=(CParams*)pParam;

	Player* pWnd=(Player*)pParameters->pWnd;
	CEvent* pEvent=(CEvent*)pParameters->pEvent;
	HWND c_Player=(HWND)pParameters->hWnd;

	while(WaitForSingleObject(pEvent->m_hObject,5)==WAIT_TIMEOUT)
	{
		if (pWnd->GetMode()==MCI_MODE_STOP)
		::SendMessage(c_Player, MCI_PLAY, 0, 0);
	}

	return 0;
}

void Player::Loop()
{
	CParams Params;
	//�����ں�ʱ��
	m_Event.ResetEvent();

	Params.pWnd=(Player*)this;
	Params.pEvent=&m_Event;
	Params.hWnd=c_Player;

	AfxBeginThread(LoopThread,&Params);
}

void Player::Break()
{
	//ʹ�¼����ڴ���״̬
	m_Event.SetEvent();
	Stop();
}

HWND Player::GetWindowHandle()
{
	return c_Player;
}

void Player::SetPosition(long lPos)
{
	//������Ƶ����λ��
	MCIWndSeek(c_Player,lPos);
}

long Player::GetPosition()
{
	//�õ���ǰ����λ��
	return MCIWndGetPosition(c_Player);
}

long Player::GetLength()
{
	//�õ���Ƶ����
	return MCIWndGetLength(c_Player);
}

void Player::SetVolume(long lVol)
{
	//��������
	lVolume=lVol;
	MCIWndSetVolume(c_Player,lVol);
}

long Player::GetVolume()
{
	//�õ���ǰ����
	return lVolume;
}

void Player::IncreaseVolume()
{
	//������
	lVolume+=50;
	if (lVolume>=1000)
		lVolume=1000;

	SetVolume(lVolume);
}

void Player::DecreaseVolume()
{
	//������
	lVolume-=50;
	if (lVolume<=0)
		lVolume=0;

	SetVolume(lVolume);
}

void Player::Fwd()
{
	//���
	lPos=GetPosition();
	lPos+=10000;
	if (lPos>GetLength())
		lPos=GetLength();

	SetPosition(lPos);
}

void Player::Rwd()
{
	//����
	lPos=GetPosition();
	lPos-=10000;
	if (lPos<0)
		lPos=0;

	SetPosition(lPos);
}

int Player::SetSize(int zoom)
{
	//�������ű�����100Ϊԭ����С
	MCIWndSetZoom(c_Player,zoom);
	return 0;
}

int Player::GetSize(void)
{
	return mZoom;
}
