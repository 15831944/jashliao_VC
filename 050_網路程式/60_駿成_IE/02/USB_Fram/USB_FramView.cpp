// USB_FramView.cpp : implementation of the CUSB_FramView class
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
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
TCHAR gstrCurDrt[500];//�s��ثe�ؿ��r��
CString gStrLocalFile;//URL
CString gStrDisDriver;
/////////////////////////////////////////////////////////////////////////////
// CUSB_FramView

IMPLEMENT_DYNCREATE(CUSB_FramView, CHtmlView)

BEGIN_MESSAGE_MAP(CUSB_FramView, CHtmlView)
	//{{AFX_MSG_MAP(CUSB_FramView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUSB_FramView construction/destruction

CUSB_FramView::CUSB_FramView()
{
	// TODO: add construction code here

}

CUSB_FramView::~CUSB_FramView()
{
}

BOOL CUSB_FramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUSB_FramView drawing

void CUSB_FramView::OnDraw(CDC* pDC)
{
	CUSB_FramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CUSB_FramView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
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
	if(gStrDisDriver=="�w��")
	{
		if(checkin)
		{
			Navigate2(gStrLocalFile, 0, NULL);
		}
		else
		{
			MessageBox("�ثe���D���L�k�s�W�����A�ШϥΪ̥�����WowTV���ˬd�����O�_���`");
			CMainFrame *f1=(CMainFrame *)AfxGetMainWnd();
			f1->PostMessage(WM_CLOSE);//�����{��
		}
	}
	else
	{
		MessageBox("�˷R���Τ�A�n�A�z�i��w�ܦ��D�k�ϥΪ̡A�о��ֻP��t�s���O�٦ۨ��v�q�C");
		CMainFrame *f2=(CMainFrame *)AfxGetMainWnd();
		f2->PostMessage(WM_CLOSE);//�����{��
	}
	//Navigate2(gStrLocalFile.GetBuffer(0),NULL,NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CUSB_FramView diagnostics

#ifdef _DEBUG
void CUSB_FramView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CUSB_FramView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CUSB_FramDoc* CUSB_FramView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUSB_FramDoc)));
	return (CUSB_FramDoc*)m_pDocument;
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
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUSB_FramView message handlers
