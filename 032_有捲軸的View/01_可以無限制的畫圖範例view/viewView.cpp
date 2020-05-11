// viewView.cpp : implementation of the CViewView class
//

#include "stdafx.h"
#include "view.h"

#include "viewDoc.h"
#include "viewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewView

IMPLEMENT_DYNCREATE(CViewView, CScrollView)

BEGIN_MESSAGE_MAP(CViewView, CScrollView)
	//{{AFX_MSG_MAP(CViewView)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewView construction/destruction

CViewView::CViewView()
{
	// TODO: add construction code here

}

CViewView::~CViewView()
{
}

BOOL CViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CViewView drawing

void CViewView::OnDraw(CDC* pDC)
{
	CViewDoc* pDoc = GetDocument();
	CClientDC aDC(this);	//�إߵe��
	ASSERT_VALID(pDoc);
	POSITION pos;
	CView::OnDraw(pDC);	//�I�sCView���O��OnDraw�������
	pos=list1.GetHeadPosition();
	while(pos !=NULL)
	{
		p1=list1.GetNext(pos);
		p2=list1.GetNext(pos);
		PhysicalCoor(&p1);
		aDC.MoveTo ( p1 );
		PhysicalCoor(&p2);
		aDC.LineTo ( p2 );
	}

	// TODO: add draw code for native data here
}

void CViewView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;

	SetScrollSizes( MM_TEXT, CSize ( 4096, 4096 ) );

}

/////////////////////////////////////////////////////////////////////////////
// CViewView printing

BOOL CViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CViewView diagnostics

#ifdef _DEBUG
void CViewView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CViewView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CViewDoc* CViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CViewDoc)));
	return (CViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewView message handlers

BOOL CViewView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CViewView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (this == GetCapture())	//�P�_�ƹ���ЬO�_�b���b���檺������
	{
		CClientDC aDC(this);	//�إߵe��
		aDC.SetROP2(R2_NOT);	//�]�wø�ϼҦ�
		OnPrepareDC(&aDC);	//�ץ��e�� ScrollView new
		LogicalCoor(&point);	//�ഫ���޿�y�� ScrollView new
		aDC.MoveTo ( p1 );
		p2=point;
		aDC.LineTo ( p2 );
		list1.AddTail(p1);
		list1.AddTail(p2);
	}
	// �e�X�s�u�q //
	PhysicalCoor(&p1);	//�ഫ�ܪ��z�y�� ScrollView new
	PhysicalCoor(&p2);	//�ഫ�ܪ��z�y�� ScrollView new
	CRect rect(p1, p2);//�إ߭�ø�ϰ쪺�x��
	rect.NormalizeRect();	//�N�x�Υ��W��
	rect.InflateRect(5,5);	//�[�j��ø�ϰ쪺�x�νd��
	InvalidateRect(&rect,true);	//�Хܭ�ø�ϰ�A�ä޵oWM_PAINT�T��

	ReleaseCapture();	//����ƹ��T�������v
	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CViewView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();	//���o�ƹ��T���������v
	if (this == GetCapture())	//�P�_�ƹ���ЬO�_�b���b���檺������
	{
		LogicalCoor(&point);
		p1 = p2 = point;
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CViewView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	/*
	if (this == GetCapture())	//�P�_�ƹ���ЬO�_�b���b���檺������
	{
		CClientDC aDC(this);	//�إߵe��
		aDC.SetROP2(R2_NOT);	//�]�wø�ϼҦ�
		OnPrepareDC(&aDC);	//�ץ��e�� ScrollView new
		LogicalCoor(&point);	//�ഫ���޿�y�� ScrollView new
		aDC.MoveTo ( p1 );
		p2=point;
		aDC.LineTo ( p2 );
	}
	*/

	CScrollView::OnMouseMove(nFlags, point);
}

CScrollBar* CViewView::GetScrollBarCtrl(int nBar) const
{
	// TODO: Add your specialized code here and/or call the base class
	return CScrollView::GetScrollBarCtrl(nBar);
}

BOOL CViewView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class
	Invalidate(true);
	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}
