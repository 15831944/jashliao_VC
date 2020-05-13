// test_createXMLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test_createXML.h"
#include "test_createXMLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest_createXMLDlg dialog

CTest_createXMLDlg::CTest_createXMLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTest_createXMLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTest_createXMLDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTest_createXMLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest_createXMLDlg)

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTest_createXMLDlg, CDialog)
	//{{AFX_MSG_MAP(CTest_createXMLDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest_createXMLDlg message handlers

BOOL CTest_createXMLDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTest_createXMLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTest_createXMLDlg::OnPaint() 
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
HCURSOR CTest_createXMLDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTest_createXMLDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	MSXML2::IXMLDOMDocumentPtr pDoc;
	MSXML2::IXMLDOMElementPtr xmlRoot;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
		MessageBox("Error");
		return;
	}
	//�ڸ`�I���W�٬�Book
	//�Ыؤ����òK�[����ɤ�
	xmlRoot=pDoc->createElement((_bstr_t)"Book");
	//�]�m�ݩ�
	xmlRoot->setAttribute("id",(const char *)"bk101");
	pDoc->appendChild(xmlRoot);
	MSXML2::IXMLDOMElementPtr pNode;
	//�K�["author"����
	pNode=pDoc->createElement((_bstr_t)"Author");
	pNode->Puttext((_bstr_t)(const char *)"Lizlex");
	xmlRoot->appendChild(pNode);
 
	//�K�["Title"����
	pNode=pDoc->createElement("Title");
	pNode->Puttext((const char *)"Xml User");
	xmlRoot->appendChild(pNode);
 
	//�O�s���� 
	//�p�G���s�b�N�إ�,�s�b�N�л\ 
	pDoc->save("d:\\he.xml");
MessageBox("OK");	
}

void CTest_createXMLDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
//FILE *fp;
//fp=fopen("text.txt","w");
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   MessageBox("Error!");
	   return;
	}
	pDoc->load("d:\\he.xml"); 
 
	MSXML2::IXMLDOMNodePtr  pNode;
 
	//�b�𤤬d��W��Book���`�I,"//"��ܦb���N�@�h�d�� 
	pNode=pDoc->selectSingleNode("//Book");
	MSXML2::DOMNodeType nodeType; 
 
	//�o��`�I���� 
	pNode->get_nodeType(&nodeType); 
 
	//�`�I�W�� 
	CString strName; 
	strName=(char *)pNode->GetnodeName();
	MessageBox(strName);
	//�`�I�ݩ�,��b��� 
	MSXML2::IXMLDOMNamedNodeMapPtr pAttrMap=NULL;
	MSXML2::IXMLDOMNodePtr   pAttrItem;
	_variant_t variantValue;
	pNode->get_attributes(&pAttrMap);

	long count;
	count=pAttrMap->get_length(&count);
 
	pAttrMap->get_item(0,&pAttrItem);
	//���o�`�I����
	pAttrItem->get_nodeTypedValue(&variantValue);
	CString m_strId;
	m_strId=(char *)(_bstr_t)variantValue;
	MessageBox(m_strId);
	MessageBox("OK");
}

void CTest_createXMLDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   MessageBox("Error!");
	   return;
	}
	pDoc->load("d:\\he.xml"); 
 
	MSXML2::IXMLDOMNodePtr  pNode;
 
	//�b�𤤬d��W��Book���`�I,"//"��ܦb���N�@�h�d�� 
	pNode=pDoc->selectSingleNode("//Author");
	MSXML2::DOMNodeType nodeType; 
	//�o��`�I���� 
	pNode->get_nodeType(&nodeType); 
 
	//�`�I�W�� 
	CString strName; 
	strName=(char *)pNode->GetnodeName();
	MessageBox(strName);
	
	_variant_t vtStr;
	CString strValue;
	pNode->get_nodeTypedValue(&vtStr);  
	strValue=vtStr.bstrVal; 
	MessageBox(strValue);
	MessageBox("OK");
}

void CTest_createXMLDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
	   MessageBox("Error!");
	   return;
	}
	pDoc->load("d:\\he.xml"); 
 
	MSXML2::IXMLDOMNodePtr  pNode;
 
	//�b�𤤬d��W��Book���`�I,"//"��ܦb���N�@�h�d�� 
	pNode=pDoc->selectSingleNode("//Title");
	MSXML2::DOMNodeType nodeType; 
 
	//�o��`�I���� 
	pNode->get_nodeType(&nodeType); 
 
	//�`�I�W�� 
	CString strName; 
	strName=(char *)pNode->GetnodeName();
	MessageBox(strName);
	
	_variant_t vtStr;
	CString strValue;
	pNode->get_nodeTypedValue(&vtStr);  
	strValue=vtStr.bstrVal; 
	MessageBox(strValue);
	MessageBox("OK");	
}

void CTest_createXMLDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	MSXML2::IXMLDOMDocumentPtr pDoc;
	MSXML2::IXMLDOMElementPtr xmlRoot;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
		MessageBox("Error");
		return;
	}
	pDoc->load("d:\\he.xml"); 
	xmlRoot=pDoc->selectSingleNode("//Book");
	MSXML2::DOMNodeType nodeType; 
	//�o��`�I���� 
	xmlRoot->get_nodeType(&nodeType); 
	//�`�I�W�� 
	CString strName; 
	strName=(char *)xmlRoot->GetnodeName();
	MessageBox(strName);

	MSXML2::IXMLDOMElementPtr pNode;
	//�K�["author"����
	pNode=pDoc->createElement((_bstr_t)"����1");
	pNode->Puttext((_bstr_t)(const char *)"test");
	xmlRoot->appendChild(pNode);
	pDoc->save("d:\\he.xml");
	MessageBox("OK");
}

void CTest_createXMLDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	MSXML2::IXMLDOMDocumentPtr pDoc;
	MSXML2::IXMLDOMElementPtr xmlRoot;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
		MessageBox("Error");
		return;
	}
	pDoc->load("d:\\he.xml"); 
	xmlRoot=pDoc->selectSingleNode("//����1");
	MSXML2::DOMNodeType nodeType; 
	//�o��`�I���� 
	xmlRoot->get_nodeType(&nodeType); 
	//�`�I�W�� 
	CString strName; 
	strName=(char *)xmlRoot->GetnodeName();
	MessageBox(strName);

	_variant_t vtStr;
	CString strValue;
	xmlRoot->get_nodeTypedValue(&vtStr);  
	strValue=vtStr.bstrVal; 
	MessageBox(strValue);
	xmlRoot->put_text((_bstr_t)(const char *)"200"); 
	pDoc->save("d:\\he.xml");
	MessageBox("OK");	
}
