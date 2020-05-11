// GetPassWordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetPassWord.h"
#include "GetPassWordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGetPassWordDlg dialog

CGetPassWordDlg::CGetPassWordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetPassWordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetPassWordDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetPassWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetPassWordDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetPassWordDlg, CDialog)
	//{{AFX_MSG_MAP(CGetPassWordDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetPassWordDlg message handlers

BOOL CGetPassWordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_tip.Create(this);
	m_tip.AddTool(GetDlgItem(IDC_EDIT_PASS),"���б�������ڼ����κ�����ʱ������\n�Զ��ٻ����룬������ܣ������ָ����\n�������Զ�ȡ�����롣���ڴ˱༭����\n��ʾ������",m_hIcon);

	CWnd *pWnd=GetDlgItem(IDC_EDIT_PASS);
	m_hook.StartHook(pWnd->GetSafeHwnd());

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGetPassWordDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGetPassWordDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CGetPassWordDlg::PreTranslateMessage(MSG* pMsg) 
{
	m_tip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CGetPassWordDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_hook.StopHook();	
}
