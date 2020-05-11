// ProGram2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProGram2.h"
#include "ProGram2Dlg.h"
#include "CSpreadSheet.h"//����Excel���ݶ�д
#include "Matrix.h"
#include "afx.h"
/*�Ž���.h�ļ���///////////////////////////////
//#include "AFXDB.H"
//#include "ODBCINST.H"
//#include "float.h"//����atof
//#include "Afxdlgs.h"//���ƴ򿪱���Ի���
//#include "CSpreadSheet.h"//����Excel���ݶ�д
//#include "ResultDlg.h"
//#include "Factor.h"
//#include "AMoment.h"
*/
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About//////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CWBButton m_IDOK;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDOK, m_IDOK);
	//}}AFX_DATA_MAP
}
BOOL CAboutDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::Create(IDD, pParentWnd);
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_IDOK.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// FactorsData dialog

class FactorsData : public CDialog
{
// Construction
public:
	FactorsData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FactorsData)
	enum { IDD = IDD_Factors };
	int m_MeanRows;///////////
	int m_MeanCols;///////////////���
	double m_OfferRate;////////////
	BOOL m_CHECK1;
	BOOL m_CHECK2;
	BOOL m_CHECK3;
	BOOL m_CHECK4;
	//}}AFX_DATA

	CWBButton m_Cancel;
	CWBButton	m_OK;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FactorsData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FactorsData)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateOfferRate();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
FactorsData::FactorsData(CWnd* pParent /*=NULL*/)
	: CDialog(FactorsData::IDD, pParent)
{
	//{{AFX_DATA_INIT(FactorsData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void FactorsData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FactorsData)
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Text(pDX, IDC_MeanRows, m_MeanRows);//////////////
	DDX_Text(pDX, IDC_MeanCols, m_MeanCols);//////////////���
	DDX_Text(pDX, IDC_OfferRate, m_OfferRate);//////////////
	DDX_Check(pDX, IDC_CHECK1, m_CHECK1);
	DDX_Check(pDX, IDC_CHECK2, m_CHECK2);
	DDX_Check(pDX, IDC_CHECK3, m_CHECK3);
	DDX_Check(pDX, IDC_CHECK4, m_CHECK4);
	//}}AFX_DATA_MAP
}
BOOL FactorsData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_OK.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	m_Cancel.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	m_CHECK1=0;
	m_CHECK2=0;
	m_CHECK3=0;
	m_CHECK4=0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void FactorsData::OnUpdateOfferRate()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_OfferRate>1 ||m_OfferRate<0)
	{
		MessageBox("    ��Ч���ۻ�������     ","������");
		m_OfferRate=0.8;
	}
	UpdateData(false);

}

BEGIN_MESSAGE_MAP(FactorsData, CDialog)
	//{{AFX_MSG_MAP(FactorsData)
	ON_EN_UPDATE(IDC_OfferRate, OnUpdateOfferRate)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// MainFactorsData dialog
class MainFactorsData : public CDialog
{
// Construction
public:
	MainFactorsData(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(MainFactorsData)
	enum { IDD = IDD_MainFactors };
	CWBButton	m_OK;
	CWBButton	m_Cancel;
	int m_MeanRows;///////////
	int m_MeanCols;///////////////���
	double m_OfferRate;////////////
	int m_ModoKind;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MainFactorsData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MainFactorsData)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateOfferRate();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
MainFactorsData::MainFactorsData(CWnd* pParent /*=NULL*/)
	: CDialog(MainFactorsData::IDD, pParent)
{
	//{{AFX_DATA_INIT(MainFactorsData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MainFactorsData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MainFactorsData)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Text(pDX, IDC_MeanRows, m_MeanRows);//////////////
	DDX_Text(pDX, IDC_MeanCols, m_MeanCols);//////////////���
	DDX_Text(pDX, IDC_OfferRate, m_OfferRate);//////////////
	//}}AFX_DATA_MAP
}
BOOL MainFactorsData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_OK.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	m_Cancel.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	m_ModoKind=2;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void MainFactorsData::OnUpdateOfferRate()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_OfferRate>1 ||m_OfferRate<0)
	{
		MessageBox("    ��Ч���ۻ�������    ","������");
		m_OfferRate=0.8;
	}
	UpdateData(false);

}
void MainFactorsData::OnRadio1()
{
	m_ModoKind=0;
}
void MainFactorsData::OnRadio2()
{
	m_ModoKind=1;
}
BEGIN_MESSAGE_MAP(MainFactorsData, CDialog)
	//{{AFX_MSG_MAP(MainFactorsData)
	ON_EN_UPDATE(IDC_OfferRate, OnUpdateOfferRate)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// ONorINData dialog

class ONorINData : public CDialog
{
// Construction
public:
	ONorINData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ONorINData)
	enum { IDD = IDD_ONorIN };
	CWBButton	m_OK;
	CWBButton	m_Cancel;
	int m_MeanRows;///////////
	int m_MeanCols;///////////////��ӿؼ�������1������������
	double m_OfferRate;////////////
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ONorINData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ONorINData)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateOfferRate();//����ı��ؼ���Ϣ������1������������
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
ONorINData::ONorINData(CWnd* pParent /*=NULL*/)
	: CDialog(ONorINData::IDD, pParent)
{
	//{{AFX_DATA_INIT(ONorINData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ONorINData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ONorINData)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Text(pDX, IDC_MeanRows, m_MeanRows);//////////////
	DDX_Text(pDX, IDC_MeanCols, m_MeanCols);////��ӿؼ�������2�������ӱ����Ϳؼ�ID
	DDX_Text(pDX, IDC_OfferRate, m_OfferRate);//////////////
	//}}AFX_DATA_MAP
}

BOOL ONorINData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_OK.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	m_Cancel.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void ONorINData::OnUpdateOfferRate() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_OfferRate>1 ||m_OfferRate<0)
	{
		MessageBox("    ��Ч���ۻ�������   ","������");
		m_OfferRate=0.8;
	}
	UpdateData(false);

}
BEGIN_MESSAGE_MAP(ONorINData, CDialog)
	//{{AFX_MSG_MAP(ONorINData)
	ON_EN_UPDATE(IDC_OfferRate, OnUpdateOfferRate)	//����ı��ؼ���Ϣ������2�������Ӻ����Ϳռ�ID
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CSureExit dialog

class CSureExit : public CDialog
{//�����ȷ���˳�
// Construction
public:
	CSureExit(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CSureExit)
	enum { IDD = IDD_SureEXIT };
	CWBButton	m_OK;
	CWBButton	m_Cancel;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSureExit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSureExit)
	virtual BOOL OnInitDialog();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
CSureExit::CSureExit(CWnd* pParent /*=NULL*/)
	: CDialog(CSureExit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSureExit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
BOOL CSureExit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_OK.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	m_Cancel.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSureExit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSureExit)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSureExit, CDialog)
	//{{AFX_MSG_MAP(CSureExit)

		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// SheetDlg dialog

class SheetDlg : public CDialog
{
// Construction
public:
	SheetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SheetDlg)
	enum { IDD = IDD_Sheet };
	CWBButton	m_OK;
	CWBButton	m_Cancel;
	CString	m_Sheet;
	int		m_TabelCols;
	int		m_TabelRows;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SheetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SheetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateTabelRows();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
SheetDlg::SheetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SheetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SheetDlg)
	m_Sheet = _T("");
	m_TabelCols = 0;
	m_TabelRows = 0;
	//}}AFX_DATA_INIT
}
BOOL SheetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_OK.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	m_Cancel.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SheetDlg)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Text(pDX, IDC_Sheet, m_Sheet);
	DDX_Text(pDX, IDC_TabelCols, m_TabelCols);
	DDX_Text(pDX, IDC_TabelRows, m_TabelRows);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SheetDlg, CDialog)//��Ϣ���ݺ����ӿ�
	//{{AFX_MSG_MAP(SheetDlg)
	ON_EN_UPDATE(IDC_TabelRows, OnUpdateTabelRows)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SheetDlg message handlers

void SheetDlg::OnUpdateTabelRows() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_TabelRows<1)
	{
		MessageBox("    ���ٰ���һ�б���    ","������");
		m_TabelRows=1;
	}
	UpdateData(false);

}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CProGram2Dlg dialog

CProGram2Dlg::CProGram2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProGram2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProGram2Dlg)
	m_MeanRows = 0;
	m_MeanCols = 0;
	m_sChange = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProGram2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProGram2Dlg)
//DEL	DDX_Control(pDX, IDButtonRowUp, m_ButtonRowUp);
//DEL	DDX_Control(pDX, IDButtonColUp, m_ButtonColUp);
//DEL	DDX_Control(pDX, IDButtonColDown, m_ButtonColDown);
//DEL	DDX_Control(pDX, IDBuntonRowDown, m_ButtonRowDown);
	DDX_Control(pDX, IDC_EDIT1, m_Change);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_FlexGrid);
	DDX_Text(pDX, IDC_EDITMeanRows, m_MeanRows);
	DDX_Text(pDX, IDC_EDITMeanCols, m_MeanCols);
	DDX_Text(pDX, IDC_EDIT1, m_sChange);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProGram2Dlg, CDialog)
	//{{AFX_MSG_MAP(CProGram2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU1_EXIT, OnMenu1Exit)
	ON_COMMAND(ID_MENU3_ABOUT, OnMenu3About)
	ON_COMMAND(ID_MENU1_CLEARN, OnMenu1Clearn)
	ON_COMMAND(ID_MENU1_NEW, OnMenu1New)
	ON_BN_CLICKED(IDC_BuntonRowDown, OnBuntonRowDown)
	ON_BN_CLICKED(IDC_ButtonColDown, OnButtonColDown)
	ON_BN_CLICKED(IDC_ButtonColUp, OnButtonColUp)
	ON_BN_CLICKED(IDC_ButtonRowUp, OnButtonRowUp)
	ON_COMMAND(ID_MENU3_HELP, OnMenu3Help)
	ON_COMMAND(ID_MENU2_MAIN, OnMenu2Main)
	ON_COMMAND(ID_MENU2_ONorIN, OnMENU2ONorIN)
	ON_COMMAND(ID_MENU2_FACTORS, OnMenu2Factors)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEditChange)
	ON_COMMAND(ID_MENU1_GetIn, OnMENU1GetIn)
	ON_COMMAND(ID_MENU1_PutOut, OnMENU1PutOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProGram2Dlg message handlers

BOOL CProGram2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_IsDataHasTabel=0;
	m_IsDataHasTabelOnCol=0;	
//DEL	m_ButtonRowUp.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
//DEL	m_ButtonColUp.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
//DEL	m_ButtonColDown.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
//DEL	m_ButtonRowDown.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	// TODO: Add extra initialization here
///////////////////////////////////////////

	///
	///
	///���г�ʼ��
	m_MeanRows=0;//��Ч���г�ʼ��
	m_MeanCols=0;
	m_lRow=0;
	m_lCol=0;
	m_NumRows=300;
	m_NumCols=100;
	m_FlexGrid.SetCols(m_NumCols);
	m_FlexGrid.SetRows(m_NumRows);
	m_FlexGrid.SetRow(0);
	m_FlexGrid.SetCol(0);
	m_FlexGrid.SetText("Ʒ��\\��״");
	m_FlexGrid.SetRow(0);
	CString s;
	for(int i=1;i<m_NumCols;i++)
	{
		m_FlexGrid.SetCol(i);
		s.Format("   %d ",i);
		m_FlexGrid.SetText(s);
	}
	m_FlexGrid.SetCol(0);
	for(i=1;i<m_NumRows;i++)
	{
		m_FlexGrid.SetRow(i);
		s.Format("   %d ",i);
		m_FlexGrid.SetText(s);
	}
/////////////////////////////////////////////////////////////
	


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProGram2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProGram2Dlg::OnPaint() 
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
HCURSOR CProGram2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



BEGIN_EVENTSINK_MAP(CProGram2Dlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CProGram2Dlg)
	ON_EVENT(CProGram2Dlg, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
/////////////////////////////////////////////////////////////////////////////
///
///����б��
void CProGram2Dlg::OnClickMsflexgrid1() 
{
	long lRow = m_FlexGrid.GetRowSel();//��ȡ������к� 
	long lCol = m_FlexGrid.GetColSel(); //��ȡ������к� 
	// TODO: Add your control notification handler code here

	if(lRow>m_NumRows-2 || lCol>m_NumCols-2) //����������������кţ���������Ч��
		return;
	if(lRow==0 || lCol==0)
		return;
	m_lRow=lRow;
	m_lCol=lCol;
	///
	///
	///�������
//	CString S;
//	S.Format("%d��%d��",lRow,lCol);
//	MessageBox(S);
	///
	///
	///
	CRect rect;
	m_FlexGrid.GetWindowRect(rect); //��ȡ���ؼ��Ĵ��ھ���
	ScreenToClient(rect); //ת��Ϊ�ͻ�������
	// MSFlexGrid �ؼ��ĺ����ĳ��ȵ�λ��"�(twips)"�� 
	//��Ҫ����ת��Ϊ���أ�1440 � = 1 Ӣ��
	CDC* pDC=GetDC();
	int nTwipsPerDotX=1440/pDC->GetDeviceCaps(LOGPIXELSX);
	int nTwipsPerDotY=1440/pDC->GetDeviceCaps(LOGPIXELSY);
	//����ѡ�и�����Ͻǵ����꣨����Ϊ��λ��
	long y=m_FlexGrid.GetRowPos(lRow)/nTwipsPerDotY;
	long x=m_FlexGrid.GetColPos(lCol)/nTwipsPerDotX;
	//������Ӵ�С��3��2.5�ǵ����ܽ�Ľ��
	long width=m_FlexGrid.GetColWidth(lCol)/nTwipsPerDotX+1;
	long height=m_FlexGrid.GetRowHeight(lRow)/nTwipsPerDotY+1;
	//�γ�ѡ�����ڵľ�������
	CRect rc(x,y,x+width,y+height);
	//ת��Ϊ��ԶԻ�������
	rc.OffsetRect(rect.left+3,rect.top+3);

	CString strValue=m_FlexGrid.GetTextMatrix(lRow,lCol);
	m_Change.ShowWindow(SW_SHOW);
	m_Change.SetWindowText(strValue);
//	m_sChange=strValue;
	m_Change.SetFocus();
	m_Change.SetSel(0,-1);
	m_Change.MoveWindow(rc);
}
//////////////////////////////////////////////////////
///
///�˵�����
////////////////
///
///����Excel����
void CProGram2Dlg::OnMENU1GetIn()
{
	// TODO: Add your command handler code here
	CFileDialog File(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"���(*.xls)|*.xls||");
	if(File.DoModal()==IDOK)
	{
		CString sPath=File.GetPathName();
		
		SheetDlg dlg;
		dlg.m_Sheet="Sheet1";
		dlg.m_TabelCols=0;
		dlg.m_TabelRows=1;
		if(dlg.DoModal()==IDOK)
		{
			CString s=dlg.m_Sheet;
			int tabelRows=dlg.m_TabelRows;//��¼����ԭ�ı�ǩ������
			int tabelCols=dlg.m_TabelCols;//
			if(s=="")
				return;
			else
			{
//				AfxMessageBox(sPath+s);//���λ�ü���
				CSpreadSheet SS(sPath,s);
				CStringArray Rows,Column;
				
				///
//				CString s;
//				s.Format("���������%d����%d",SS.GetTotalRows(),SS.GetTotalColumns());//����������
//				MessageBox(s);
				///
				if(SS.GetTotalRows()<=0)
				{
					MessageBox("    ȷ�����Ϊ��    ","������");
					return;
				}
				else
				{
					//ShowWindow(SW_MINIMIZE);//���ش��ڣ��ں�̨¼������
					//ShowWindow(SW_RESTORE);//��ʾ����
					OnMenu1New();//��ձ��
					ShowWindow(SW_MINIMIZE);
					int i,j;
					m_IsDataHasTabel=1;
					if(tabelCols>0)
						m_IsDataHasTabelOnCol=1;
					///
///					CString s="";
 ///   				SS.ReadColumn(Column,1);
///					s=Column.GetAt(0);
///					MessageBox(s);
					///
					UpdateData(true);
					m_MeanRows=SS.GetTotalRows()-tabelRows;
					m_MeanCols=SS.GetTotalColumns()-tabelCols;
					UpdateData(false);
					SS.ReadRow(Rows,tabelRows);
					m_FlexGrid.SetRow(0);
					for(i=1;i<=SS.GetTotalColumns();i++)//�����б�ǩ
					{
						m_FlexGrid.SetCol(i);
						m_FlexGrid.SetText(Rows.GetAt(i-1));
					}
					
					for(i=tabelRows+1;i<=SS.GetTotalRows();i++)
					{
						m_FlexGrid.SetRow(i-tabelRows);
						SS.ReadRow(Rows,i);//��ȡ��i��
						if(tabelCols>0)//����ǩ��
						{
							m_FlexGrid.SetCol(0);
							m_FlexGrid.SetText(Rows.GetAt(0));
						}						
						for(j=tabelCols+1;j<=SS.GetTotalColumns();j++)
						{

							m_FlexGrid.SetCol(j-tabelCols);
							s=Rows.GetAt(j-1);
								if(s=="")
									m_FlexGrid.SetText("0.0000");
								if(IsNumber(s))
								{
									m_FlexGrid.SetText(s);
								}
								
							
						}
					}
					ShowWindow(SW_RESTORE);//��ʾ����
					
				}
			}
		}
	}

}
/////////////////////////////////////////////////
///
///
///�������ݵ�Excel
void CProGram2Dlg::OnMENU1PutOut() 
{
	// TODO: Add your command handler code here
	//������ǩ��û���漰
	if(m_MeanRows==0||m_MeanCols==0)
	{
		MessageBox("    ���ܱ��������    ","������");
		return;
	}

	CFileDialog File(false,NULL,"����.xls",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"���(*.xls)|*.xls||");
	if(File.DoModal()==IDOK)
	{
		int i,j;
		CString s;
		CString sPath=File.GetPathName();

		CSpreadSheet SS(sPath, "Sheet1");

		CStringArray sampleArray, testRow;
	
		SS.BeginTransaction();
//		MessageBox(sPath);
	///
//		s.Format("%d",m_IsDataFromExcel);
//		MessageBox(s);//�����Ƿ���������excel�ļ�
		///
    	if(m_IsDataHasTabel)//�������Ա���б�����
		{
			sampleArray.RemoveAll();
			for(i=1;i<=m_MeanCols;i++)
			{

				sampleArray.Add(m_FlexGrid.GetTextMatrix(0,i));
			}
			SS.AddHeaders(sampleArray);
		}
		for(i=1;i<=m_MeanRows;i++)
		{
			sampleArray.RemoveAll();
			for(j=1;j<=m_MeanCols;j++)
			{
				s=m_FlexGrid.GetTextMatrix(i,j);
				sampleArray.Add(s);
			}
			SS.AddRow(sampleArray);
		}
		AfxMessageBox("�ļ�д��ɹ�!");
	}
	
}
void CProGram2Dlg::OnMenu1Clearn() 
{
	// TODO: Add your command handler code here
	ShowWindow(SW_MINIMIZE);//���ش��ڣ��ں�̨¼������
					
	UpdateData(true);
	m_IsDataHasTabel=0;
	m_IsDataHasTabelOnCol=0;
	m_MeanRows=0;//��Ч���г�ʼ��
	m_MeanCols=0;
	UpdateData(false);
	m_FlexGrid.Clear();
	m_FlexGrid.SetCols(m_NumCols);
	m_FlexGrid.SetRows(m_NumRows);
	m_FlexGrid.SetRow(0);
	m_FlexGrid.SetCol(0);
	m_FlexGrid.SetText("Ʒ��\\��״");
	m_FlexGrid.SetRow(0);
	CString s;
	for(int i=1;i<m_NumCols;i++)
	{
		m_FlexGrid.SetCol(i);
		s.Format("   %d ",i);
		m_FlexGrid.SetText(s);
	}
	m_FlexGrid.SetCol(0);
	for(i=1;i<m_NumRows;i++)
	{
		m_FlexGrid.SetRow(i);
		s.Format("   %d ",i);
		m_FlexGrid.SetText(s);
	}
	m_Change.ShowWindow(SW_HIDE);
	ShowWindow(SW_RESTORE);//��ʾ����
}

void CProGram2Dlg::OnMenu1New() 
{
	// TODO: Add your command handler code here
	ShowWindow(SW_MINIMIZE);//���ش��ڣ��ں�̨¼������
					
	m_FlexGrid.Clear();
	UpdateData(true);
	m_IsDataHasTabel=0;
	m_IsDataHasTabelOnCol=0;
	m_MeanRows=0;//��Ч���г�ʼ��
	m_MeanCols=0;
	UpdateData(false);
	m_NumRows=300;
	m_NumCols=100;
	m_FlexGrid.SetCols(m_NumCols);
	m_FlexGrid.SetRows(m_NumRows);
	m_FlexGrid.SetRow(0);
	m_FlexGrid.SetCol(0);
	m_FlexGrid.SetText("Ʒ��\\��״");
	m_FlexGrid.SetRow(0);
	CString s;
	for(int i=1;i<m_NumCols;i++)
	{
		m_FlexGrid.SetCol(i);
		s.Format("   %d ",i);
		m_FlexGrid.SetText(s);
	}
	m_FlexGrid.SetCol(0);
	for(i=1;i<m_NumRows;i++)
	{
		m_FlexGrid.SetRow(i);
		s.Format("   %d ",i);
		m_FlexGrid.SetText(s);
	}
	m_Change.ShowWindow(SW_HIDE);
	ShowWindow(SW_RESTORE);//��ʾ����
}
void CProGram2Dlg::OnMenu1Exit() 
{
	// TODO: Add your command handler code here
	CSureExit dlg;
	if(dlg.DoModal()==IDOK)
		OnMENU1PutOut();
	else
		exit(0);
}

void CProGram2Dlg::OnMenu2Main() 
{	// TODO: Add your command handler code here
	//���ݸ��²���
//	CString s;
//	s.Format("%d---%d;;;;%d---%d",m_MeanRows,m_MeanCols,m_lRow,m_lCol);
//	MessageBox(s);
	//
	MainFactorsData dlg;
	dlg.m_MeanRows=m_MeanRows;
	dlg.m_MeanCols=m_MeanCols;
	dlg.m_OfferRate=0.80;
	if(dlg.DoModal()==IDOK)
	{		
		if(dlg.m_MeanCols<=0||dlg.m_MeanRows<=0)
		{
			MessageBox("    �������Ч������!    ","������");
			return;
		}
		if(dlg.m_ModoKind==2)
		{
			MessageBox("   û��ѡ�����ģ��!    ","������");
			return;
		}
		//Add our program on Main here
		/*
		CMatrix m_Matrix2;			//��׼����������
		CMatrix m_Result1;			//������ɷֵ��������������ʺ��ۼƹ�����
		CMatrix m_Result2;			//������ɷ�ϵ��
		CMatrix m_Result3;			//�����Ʒ�����ɷֵ÷�ֵ
		CMatrix m_Result4;			//���ɷ��غ�����
		*/
		CMatrix Data(ReadDataToMatrix(dlg.m_MeanRows,dlg.m_MeanCols));
		Data=Data.Transpose();
		MainFactor mainfactor(Data,dlg.m_OfferRate,dlg.m_ModoKind);
		mainfactor.Analyze1();
		CMatrix *a;
		a=new CMatrix[5];
		a[0]=mainfactor.m_Matrix2;
		a[1]=mainfactor.m_Result1;
		a[2]=mainfactor.m_Result2;
		a[3]=mainfactor.m_Result3;
		a[4]=mainfactor.m_Result4;
		int J[5]={1,mainfactor.m_mainNum,1,1,1};//5���������Ҫ���
		CResultDlg result;
		result.TranMemberNumber(1,a,5,J);
		result.DoModal();

	}	
	

}

void CProGram2Dlg::OnMENU2ONorIN() 
{// TODO: Add your command handler code here
	ONorINData dlg;
	dlg.m_MeanRows=m_MeanRows;
	dlg.m_MeanCols=m_MeanCols;
	dlg.m_OfferRate=0.80;
	if(dlg.DoModal()==IDOK)
	{	
		if(dlg.m_MeanCols<=0||dlg.m_MeanRows<=0)
		{
			MessageBox("    �������Ч������!    ","������");
			return;
		}//Add our program on ONorIN here
		CMatrix a(ReadDataToMatrix(dlg.m_MeanRows,dlg.m_MeanCols));
		a=a.Transpose();
		QR_analysis analysis;
		analysis.run(a);
		CMatrix *Data;
		Data=new CMatrix[4];
		Data[0]=analysis.result1;
		Data[1]=analysis.result2;
		Data[2]=analysis.result3;
		Data[3]=analysis.result4;
		int J[4]={1,1,1,1};
		CResultDlg result;
		result.TranMemberNumber(2,Data,4,J);
		result.DoModal();
	}
}

void CProGram2Dlg::OnMenu2Factors() 
{// TODO: Add your command handler code here
	FactorsData dlg;
	dlg.m_MeanRows=m_MeanRows;
	dlg.m_MeanCols=m_MeanCols;
	dlg.m_OfferRate=0.80;
	if(dlg.DoModal()==IDOK)
	{		
		if(dlg.m_MeanCols<=0||dlg.m_MeanRows<=0)
		{
			MessageBox("    �������Ч������!    ","������");
			return;
		}
		//Add our program on Factors here
		//�����ﶨ�����������࣬���õ����

		///���ʹ���������
		CMatrix a;
		a=ReadDataToMatrix(dlg.m_MeanRows,dlg.m_MeanCols);

		Factor factor(a,dlg.m_OfferRate);
		factor.Run();
		CMatrix *Data;
		Data=new CMatrix[7];
		Data[0]=factor.X;//ԭ���ݣ����Ϊ��׼���������
		Data[1]=factor.R;//��ؾ���P*P
		Data[2]=factor.te_R;//����ֵ����������
		CMatrix A1((int)factor.p,(int)factor.m_ColsOfA+2);
		for(int i=0;i<factor.p;i++)
		{
			for(int j=0;j<factor.m_ColsOfA;j++)
			{
				A1.SetElement(i,j,factor.A.GetElement(i,j));
			}
			double *t=factor.h2;
			A1.SetElement(i,(int)factor.m_ColsOfA,t[i]*t[i]);
			A1.SetElement(i,(int)factor.m_ColsOfA+1,1-t[i]*t[i]);
		}
		Data[3]=factor.A;//�����غ���p*p
		Data[4]=A1;//�����غ���p*m+h2+a2
		Data[5]=factor.B;//������ת����������غ���p*m
		Data[6]=factor.F;//���ӵ÷�m_ColsOfA*p
		int J[7]={dlg.m_CHECK1,dlg.m_CHECK2,dlg.m_CHECK3,dlg.m_CHECK4,1,((factor.m_ColsOfA>=2)? 1:0),1};

		CResultDlg result;
		
		result.TranMemberNumber(3,Data,7,J);//�������
		result.DoModal();
		
	}
}

void CProGram2Dlg::OnMenu3Help() 
{
	// TODO: Add your command handler code here
	ShellExecute(NULL, "open", "ʹ��˵��.pdf", NULL, NULL, SW_SHOWNORMAL);
	ShowWindow(SW_MINIMIZE);
}
void CProGram2Dlg::OnMenu3About() 
{
	// TODO: Add your command handler code here
	CAboutDlg dl;
	dl.DoModal();
}
///////////////////////////////////////////////////////
///
///
///�����������ư�ť
void CProGram2Dlg::OnBuntonRowDown() 
{
	// TODO: Add your control notification handler code here
	if(m_NumRows>1)
	{
		m_NumRows-=1;
		m_FlexGrid.SetRows(m_NumRows);
	}
}

void CProGram2Dlg::OnButtonColDown() 
{
	// TODO: Add your control notification handler code here
	if(m_NumCols>1)
	{
		m_NumCols-=1;
		m_FlexGrid.SetCols(m_NumCols);
	}	
}

void CProGram2Dlg::OnButtonColUp() 
{
	// TODO: Add your control notification handler code here
		
		m_NumCols+=1;
		m_FlexGrid.SetCols(m_NumCols);

		m_FlexGrid.SetRow(0);
		m_FlexGrid.SetCol(m_NumCols-1);
		CString s;
		s.Format("   %d",m_NumCols-1);
		m_FlexGrid.SetText(s);
}

void CProGram2Dlg::OnButtonRowUp() 
{
	// TODO: Add your control notification handler code here
		m_NumRows+=1;
		m_FlexGrid.SetRows(m_NumRows);
		m_FlexGrid.SetCol(0);
		m_FlexGrid.SetRow(m_NumRows-1);
		CString s;
		s.Format("   %d",m_NumRows-1);
		m_FlexGrid.SetText(s);
}
/////////////////////////////////////////////////////////////////////
///
///
///�Ի���ʧȥ���㣬ȡֵ
void CProGram2Dlg::OnKillfocusEditChange() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_sChange=="")
		return;
	if(IsNumber(m_sChange))
	{
		m_MeanRows=((m_lRow>m_MeanRows)? m_lRow:m_MeanRows);
		m_MeanCols=((m_lCol>m_MeanCols)? m_lCol:m_MeanCols);
		m_FlexGrid.SetText(m_sChange);
		m_Change.ShowWindow(SW_HIDE);
		m_sChange="";
	}
	else
	{
		MessageBox("   ��������ֵ������!  ","������");
		m_FlexGrid.SetText("");
	}
	UpdateData(false);
	
}
///
///
///�ж�CString�Ƿ�Ϊ�������͵�
bool CProGram2Dlg::IsNumber(CString str)
{
	if(!str.GetLength())
		return false;
	char ch;
	for(int i=0;i<str.GetLength();i++)
	{
		ch=str[i];
		if(ch!=45 && ch!=46 && ch<48 || ch>57)
			return false;
	}
	return true;
}
///
///
///������Ч��������ȡ����
CMatrix CProGram2Dlg::ReadDataToMatrix(int Rows,int Cols)
{
	int i,j;
	CString s,c;
	CMatrix result(Rows,Cols);	
	for(i=1;i<=Rows;i++)
	{
		for(j=1;j<=Cols;j++)
		{
			s=m_FlexGrid.GetTextMatrix(i,j);
//			c.Format("%f",(double)atof(s));
//			MessageBox(c);
			result.SetElement(i-1,j-1,(double)atof(s));
		}
	}
//	MessageBox("���������");
	return result;
}
void CProGram2Dlg::showMatrix(CMatrix a)
{
	if(a.GetNumCols==0)
		return;
	CString s,c;
	for(int i=0;i<a.GetNumRows();i++)
	{
		s="";
		for(int j=0;j<a.GetNumCols();j++)
		{
			c.Format("    %f",(double)a.GetElement(i,j));
			s=s+c;
		}
		MessageBox(s);
	}
}
