// ServerGetDataView.cpp : implementation of the CServerGetDataView class
//

#include "stdafx.h"
#include "ServerGetData.h"

#include "ServerGetDataDoc.h"
#include "ServerGetDataView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerGetDataView

IMPLEMENT_DYNCREATE(CServerGetDataView, CView)

BEGIN_MESSAGE_MAP(CServerGetDataView, CView)
	//{{AFX_MSG_MAP(CServerGetDataView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerGetDataView construction/destruction

CServerGetDataView::CServerGetDataView()
{
	// TODO: add construction code here
	//���J�۹���|�Ϥ�
	TCHAR strCurDrt[500];
	int nLen = ::GetCurrentDirectory(500,strCurDrt);//���o�ثe�{�����|
	if( strCurDrt[nLen]!='\\' )
	{
		strCurDrt[nLen++] = '\\';
		strCurDrt[nLen] = '\0';
	}
	CString strFileName1 = strCurDrt;
	CString strFileName2 = strCurDrt;
	strFileName1 += "images_01.bmp";
	strFileName2 += "images_02.bmp";
	DibBmp1.LoadBmp(strFileName1.GetBuffer(0));
	DibBmp2.LoadBmp(strFileName2.GetBuffer(0));
}

CServerGetDataView::~CServerGetDataView()
{
}

BOOL CServerGetDataView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CServerGetDataView drawing

void CServerGetDataView::OnDraw(CDC* pDC)
{
	CServerGetDataDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CClientDC dc1(this);
	DibBmp1.Draw(dc1, 5, 0, DibBmp1.Width(), DibBmp1.Height());
	DibBmp2.Draw(dc1, 5, DibBmp1.Height()*2.5f, DibBmp2.Width(), DibBmp2.Height());
	/////////////////////////////////////�]�w��X��r�r���j�p�P�C��
	CFont font;
	SIZE size;
	VERIFY(font.CreateFont(
	30,                        // nHeight
	0,                         // nWidth
	0,                         // nEscapement
	0,                         // nOrientation
	FW_NORMAL,                 // nWeight
	FALSE,                     // bItalic
	FALSE,                     // bUnderline
	0,                         // cStrikeOut
	ANSI_CHARSET,              // nCharSet
	OUT_DEFAULT_PRECIS,        // nOutPrecision
	CLIP_DEFAULT_PRECIS,       // nClipPrecision
	DEFAULT_QUALITY,           // nQuality
	DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	"�з���"));                 // lpszFacename
	CFont* def_font = dc1.SelectObject(&font);  
	/////////////////////////////////////////////
	dc1.SetBkColor(RGB(94,236,189)); 
	dc1.SetTextColor(RGB(95,95,201));
	dc1.TextOut(5,85,"��",2);
	dc1.TextOut(5,115,"�e",2);
	dc1.TextOut(5,145,"��",2);
	dc1.TextOut(5,175,"�X",2);
	////////////////////////////////////////////
	dc1.TextOut(5,295,"��",2);
	dc1.TextOut(5,385,"��",2);
	///////////////////////////////////////////
	dc1.TextOut(5,415,"��",2);
	dc1.TextOut(5,505,"��",2);
	///////////////////////////////////////////
	dc1.TextOut(5,535,"�p",2);
	dc1.TextOut(5,580,"��",2);
	dc1.TextOut(5,625,"��",2);
	//////////////////////////////////////////
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CServerGetDataView printing

BOOL CServerGetDataView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CServerGetDataView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CServerGetDataView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CServerGetDataView diagnostics

#ifdef _DEBUG
void CServerGetDataView::AssertValid() const
{
	CView::AssertValid();
}

void CServerGetDataView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CServerGetDataDoc* CServerGetDataView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CServerGetDataDoc)));
	return (CServerGetDataDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CServerGetDataView message handlers

BOOL CServerGetDataView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush brush;//���ܭI���C��
	brush.CreateSolidBrush(RGB(94,236,189));
	CBrush *pOldBrush=pDC->SelectObject(&brush);
	CRect rc;
	GetClientRect(&rc);
	pDC->Rectangle(&rc);
	pDC->SelectObject(pOldBrush);
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}
