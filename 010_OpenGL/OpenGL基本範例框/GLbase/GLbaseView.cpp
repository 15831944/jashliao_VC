// GLbaseView.cpp : implementation of the CGLbaseView class
//

#include "stdafx.h"
#include "GLbase.h"
#include <gl/glut.h>//�ĤQ�T�B
#include "glmfc.h"//�ĤT�B
#include "GLbaseDoc.h"
#include "GLbaseView.h"
#include "OpenGLFun.h"//�Ĥ��B
#include "OpenGLPara.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLbaseView

IMPLEMENT_DYNCREATE(CGLbaseView, CView)

BEGIN_MESSAGE_MAP(CGLbaseView, CView)
	//{{AFX_MSG_MAP(CGLbaseView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLbaseView construction/destruction

CGLbaseView::CGLbaseView()
{
	// TODO: add construction code here

}

CGLbaseView::~CGLbaseView()
{
}

BOOL CGLbaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGLbaseView drawing

void CGLbaseView::OnDraw(CDC* pDC)
{
	m_pPal = NULL;//�ĤQ�B
	CGLbaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	////////////////////////////////////////�ĤC�B
	CPalette *	ppalOld	= NULL;
	if (m_pPal) {
		ppalOld	= pDC->SelectPalette(m_pPal, 0);
		pDC->RealizePalette();
	}
	BOOL	bResult	= wglMakeCurrent(pDC->m_hDC, m_hrc);
	if (FALSE == bResult)
		TRACE(_T("wglMakeCurrent() failed %x.\r\n"), ::GetLastError());

	opengl_Initial();

	static GLfloat  ambientLight[]	= { 1.0f, 1.0f, 1.0f, 1.0f };	
	static GLfloat  diffuseLight[]	= { 0.7f, 0.7f, 0.7f, 1.0f };
	static GLfloat  specular[]		= { 0.7f, 0.7f, 0.7f, 1.0f };	//�O���ʽ�
	static GLfloat  specref []		= { 0.5f, 0.5f, 0.2f, 1.0f };	//�Ϯg�ʽ�
	static float normal[3];//�]�w�k�V�q

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�M���e�����ʧ@
	if(Line_Flag)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�|���ͦh��Ϊ��~�����
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//�|���Ͷ񺡪��h���
///////////////////////////////////////////
//////////////////////////////////////////
////////////////////////�ĤQ�@�B
	glFlush();
	SwapBuffers(pDC->m_hDC);

	if (ppalOld)
		pDC->SelectPalette(ppalOld, 0);

	wglMakeCurrent(NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CGLbaseView diagnostics

#ifdef _DEBUG
void CGLbaseView::AssertValid() const
{
	CView::AssertValid();
}

void CGLbaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLbaseDoc* CGLbaseView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLbaseDoc)));
	return (CGLbaseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGLbaseView message handlers

int CGLbaseView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	///////////////////////////////////////////�ĥ|�B
	dc = new CClientDC (this);
	PIXELFORMATDESCRIPTOR	pfd;

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.cColorBits	= 24;
	pfd.cDepthBits	= 32;
	pfd.dwFlags	= PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pfd.iLayerType	= PFD_MAIN_PLANE;
	pfd.iPixelType	= PFD_TYPE_RGBA;
	pfd.nSize	= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion	= 1;

	int	nPixelFormat	= ChoosePixelFormat(dc->m_hDC, &pfd);
	if (0 == nPixelFormat) {
		TRACE(_T("ChoosePixelFormat() failed %d.\r\n"), GetLastError());
		return -1;
	}
	TRACE(_T("pixel format %d.\r\n"), nPixelFormat);
	
	BOOL	bResult	= SetPixelFormat(dc->m_hDC, nPixelFormat, &pfd);
	if (FALSE == bResult) {
		TRACE(_T("SetPixelFormat() failed %d.\r\n"),GetLastError());
		return -1;
	}

	//
	// create a rendering context
	//
	m_hrc	= wglCreateContext(dc->m_hDC);
	if (NULL == m_hrc) {
		TRACE(_T("wglCreateContext() failed %x.\r\n"), GetLastError());
		return -1;
	}

	//
	// create the palette
	//
	CreateRGBPalette(dc->m_hDC, m_pPal);		
	return 0;
}

void CGLbaseView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
///////////////////////////////////////////�Ĥ��B
	if ((cx <= 0) || (cy <= 0))
		return;

	BOOL	bResult = wglMakeCurrent(dc->m_hDC, m_hrc);
	if (FALSE == bResult) {
		TRACE(_T("wglMakeCurrent() failed %x.\r\n"), GetLastError());
		return;
	}
	
	int w = cx;
	int h = cy;
	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);//�]�w�������i�H��Open GLø�Ϫ�����

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2, nRange*2);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2, nRange*2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	wglMakeCurrent(NULL, NULL);		
	
}
void CGLbaseView::opengl_Initial()//�ĤE�B
{
	//open gl��l�ȳ]�w	
	glEnable(GL_DEPTH_TEST);		// Hidden surface removal
	glFrontFace(GL_CCW);			// Counter clock-wise polygons face out
	glDisable(GL_CULL_FACE);		// Do not calculate inside of jet
	glShadeModel(GL_SMOOTH);


	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glEnable(GL_LIGHT0);
	
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);//�N�h��γ]���㦳�Ϯg�ʽ�	
	glMateriali(GL_FRONT, GL_SHININESS, 128);//�]�w�Ϯg�ʽ誺�G��
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );//�]�w�६�C��	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�M���ù��ʧ@

}

BOOL CGLbaseView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;//�ĤQ�G�B
}
