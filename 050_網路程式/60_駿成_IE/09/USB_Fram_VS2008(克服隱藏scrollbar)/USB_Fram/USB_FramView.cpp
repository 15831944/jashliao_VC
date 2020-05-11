
// USB_FramView.cpp : CUSB_FramView ���O����@
//

#include "stdafx.h"
#include "USB_Fram.h"

#include "USB_FramDoc.h"
#include "USB_FramView.h"
#include "StrXorEncoder.h"
#include "MainFrm.h"
#include <Wininet.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

TCHAR gstrCurDrt[500];//�s��ثe�ؿ��r��
CString gStrLocalFile;//URL
CString gStrDisDriver;
/////////////////////////////////////////////////////////////////////////////
// CUSB_FramView

IMPLEMENT_DYNCREATE(CUSB_FramView, CHtmlView)

BEGIN_MESSAGE_MAP(CUSB_FramView, CHtmlView)
END_MESSAGE_MAP()

// CUSB_FramView �غc/�Ѻc

CUSB_FramView::CUSB_FramView()
{
	// TODO: �b���[�J�غc�{���X

}

CUSB_FramView::~CUSB_FramView()
{
}

BOOL CUSB_FramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �b���g�ѭק� CREATESTRUCT cs 
	// �F��ק�������O�μ˦����ت�

	return CHtmlView::PreCreateWindow(cs);
}

void CUSB_FramView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	int nLen = ::GetCurrentDirectory(500,gstrCurDrt);//���o�ثe�{�����|
	if( gstrCurDrt[nLen]!='\\' )
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}
	FILE *pf='\0';
	CStrXorEncoder CSXE;
	int j,data;
	j=0;
	data=-1;
	pf=fopen("url.txt","r");
	while(fscanf(pf,"%d,",&data)!=EOF)
	{
		CSXE.intDecoder[j]=data;
		j++;
	}
	fclose(pf);
	CSXE.XorDecoder(j);
	gStrLocalFile=CSXE.chrDecoder;
	bool checkin=false;
	checkin=CheckInternet(gStrLocalFile);
	DisDriver();
	int intHW=1;
	//if(gStrDisDriver=="�w��")
	if(intHW==1)
	{
		if(checkin)
		{
			ModifyStyle(WS_VSCROLL,0);// hide the scrollbar(s)
			ShowScrollBar(SB_VERT,false);// hide the scrollbar(s)
			CScrollBar* pSB=AfxGetMainWnd()->GetScrollBarCtrl(SB_VERT);// hide the scrollbar(s)
			SetSilent(TRUE);
			Navigate2(gStrLocalFile, 0, NULL);
		}
		else
		{
			MessageBox("The Internet connection fails, please check the status of the primary network");
			CMainFrame *f1=(CMainFrame *)AfxGetMainWnd();
			f1->PostMessage(WM_CLOSE);//�����{��
		}
	}
	else
	{
		//MessageBox("�˷R���Τ�A�n�A�z�i��w�ܦ��D�k�ϥΪ̡A�о��ֻP��t�s���O�٦ۨ��v�q�C");
		CMainFrame *f2=(CMainFrame *)AfxGetMainWnd();
		f2->PostMessage(WM_CLOSE);//�����{��
	}
}

BOOL CUSB_FramView::CheckInternet(LPCTSTR URL)
{
	// TODO: Add your dispatch handler code here
	DWORD dwFlags;
	dwFlags=0;
	if(InternetCheckConnection(URL,FLAG_ICC_FORCE_CONNECTION,dwFlags))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CUSB_FramView::DisDriver()
{
	CString strResult,strRootPathName;
	strRootPathName=gstrCurDrt;
	strRootPathName=strRootPathName.Mid(0,3);
	UINT DrvType = GetDriveType(strRootPathName);
	switch(DrvType)
	{
	case DRIVE_CDROM:
		strResult = "����";
		break;
	case DRIVE_FIXED:
		strResult = "�w��";
		break;
	case DRIVE_REMOVABLE:
		strResult = "�Ϥ�/USB";
		break;
	default:
		return;
		break;
	}
	gStrDisDriver=strResult;
	//MessageBox(strResult);
}
HRESULT CUSB_FramView::OnGetHostInfo(DOCHOSTUIINFO *pInfo)
{
	pInfo->dwFlags |= DOCHOSTUIFLAG_SCROLL_NO | DOCHOSTUIFLAG_NO3DBORDER;
	return S_OK;
}
// CUSB_FramView �E�_

#ifdef _DEBUG
void CUSB_FramView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CUSB_FramView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CUSB_FramDoc* CUSB_FramView::GetDocument() const // ���O�D��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUSB_FramDoc)));
	return (CUSB_FramDoc*)m_pDocument;
}
#endif //_DEBUG


// CUSB_FramView �T���B�z�`��
