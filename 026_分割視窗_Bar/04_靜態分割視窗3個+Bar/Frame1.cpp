// Frame1.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "Frame1.h"
#include "View2.h"
#include "testView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrame1

IMPLEMENT_DYNCREATE(CFrame1, CFrameWnd)

CFrame1::CFrame1()
{
}

CFrame1::~CFrame1()
{
}


BEGIN_MESSAGE_MAP(CFrame1, CFrameWnd)
	//{{AFX_MSG_MAP(CFrame1)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrame1 message handlers

BOOL CFrame1::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	StaticSplit.CreateStatic(this,2,1);	//�إ��R�A��������
	StaticSplit.CreateView(0,0,RUNTIME_CLASS(CTestView),CSize(400,120),pContext);
	//�إ��s���ϩҨϥΪ�View����
	StaticSplit.CreateView(1,0,RUNTIME_CLASS(CView2),CSize(400,300),pContext);
	//�إ�ø�ϰϩҨϥΪ�View����
	//StaticSplit.SetActivePane(0,0);	//�]�wø�ϰϬ��@�Ϊ��l����
	//CTestView1=(CTestView*)StaticSplit.GetPane(0,1);
	return true;
}
