// glView.cpp : implementation of the CGlView class
//

#include "stdafx.h"
#include "gl.h"
#include "glmfc.h"
#include "glDoc.h"
#include "glView.h"
#include "OpenGLFun.h"
#include "OpenGLPara.h"
#include "ontrolDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
float a1,a2,a3;
int next_work=0;
int x;

/////////////////////////////////////////////////////////////////////////////
// CGlView

IMPLEMENT_DYNCREATE(CGlView, CView)

BEGIN_MESSAGE_MAP(CGlView, CView)
	//{{AFX_MSG_MAP(CGlView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_input, Oninput)
	ON_WM_TIMER()
	ON_COMMAND(ID_walkstart, Onwalkstart)
	ON_COMMAND(ID_TT, OnTt)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlView construction/destruction

CGlView::CGlView()
{
	// TODO: add construction code here
	a1=220.0f;
	a2=400.0f;
	a3=135.0f;
//////////////////////�y�����V�q�ܼ�
waist_x=0.0f;
waist_y=0.0f;
waist_z=0.0f;
rfoot_x=0.0f;
rfoot_y=0.0f;
rfoot_z=0.0f;

lfoot_x=0.0f;
lfoot_y=0.0f;
lfoot_z=0.0f;
//////////////////////left1
left1=0.0f;
//////////////////////left2
left2=0.0f;
//////////////////////left3
left3=0.0f;
//////////////////////right1
right1=0.0f;
//////////////////////right2
right2=0.0f;
//////////////////////right
right3=0.0f;
}


CGlView::~CGlView()
{
}

BOOL CGlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGlView drawing

void CGlView::OnDraw(CDC* pDC)
{
	m_pPal = NULL;
	CGlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
		CPalette *	ppalOld	= NULL;
	if (m_pPal) {
		ppalOld	= pDC->SelectPalette(m_pPal, 0);
		pDC->RealizePalette();
	}
	BOOL	bResult	= wglMakeCurrent(pDC->m_hDC, m_hrc);
	if (FALSE == bResult)
		TRACE(_T("wglMakeCurrent() failed %x.\r\n"), ::GetLastError());

	//
	// render
	//
	//////////////////////
	//�N�b�o�̵e��
	opengl_Initial();
	/////////////////////////////////////////////////////////////////////////	
	static GLfloat  ambientLight[]	= { 1.0f, 1.0f, 1.0f, 1.0f };	
	static GLfloat  diffuseLight[]	= { 0.7f, 0.7f, 0.7f, 1.0f };
	static GLfloat  specular[]		= { 0.7f, 0.7f, 0.7f, 1.0f };	//�O���ʽ�
	static GLfloat  specref []		= { 0.5f, 0.5f, 0.2f, 1.0f };	//�Ϯg�ʽ�
	static float normal[3];//�]�w�k�V�q
	///////////////////////////////////////////////////////////////

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�M���e�����ʧ@
	if(Line_Flag)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�|���ͦh��Ϊ��~�����
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//�|���Ͷ񺡪��h���
	glPushMatrix();///�϶�13start
	{

		glRotatef(xRot, 1.0f, 0.0f, 0.0f);//�������ਤ��
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);//�������ਤ��
		glRotatef(zRot, 0.0f, 0.0f, 1.0f);//�������ਤ��
		
		/*	
		glPushMatrix();
		{
			glTranslatef(75.0f,-405.0f,-112.5f);
			glTranslatef(lfoot_x,lfoot_y,lfoot_z);//////////////////////�ϥ��ܼƪ��a��
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
			drawCir(10.0f,15.0f,16.0f);
		
		}
		glPopMatrix();
		
		glPushMatrix();
		{
			glTranslatef(-75.0f,-405.0f,-112.5f);
			glTranslatef(rfoot_x,rfoot_y,rfoot_z);//////////////////////�ϥ��ܼƪ��a��
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
			drawCir(10.0f,15.0f,16.0f);
		
		}
		glPopMatrix();
		*/

		glPushMatrix();
			{
				
			glTranslatef(0.0f,400.0f,-112.5f);//���ʶZ��
			glTranslatef(waist_x,waist_y,waist_z);////////////////�ϥ��ܼƪ��a��
			waist();//�y��
			///////
			glPushMatrix();//�k�}
			{	
			glPushMatrix();
			{	
			glTranslatef(75.0f,-100.0f,0.0f);//���ʶZ��
			glRotatef(180.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
			joint();//���`
			////////////////////////
			glPushMatrix();
			{
			glTranslatef(0.0f,35.0f,0.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
			drawCir(10.0f,15.0f,16);//�j�L�W���p�����b
			/////////////////////////
			glPushMatrix();//�j�L
			{
			glRotatef(left1, 0.0f, 0.0f, 1.0f);/////////////////�ϥ��ܼƪ��a��
			glTranslatef(0.0f,200.0f,0.0f);//���ʶZ��
			a_thigh();//�j�L
			//////////////////////
			glPushMatrix();
			{
			glTranslatef(0.0f,200.0f,0.0f);//���ʶZ��
			drawCir(10.0f,15.0f,16);//�p�L�W���p�����b
			/////////////////////////////
			glPushMatrix();//�p�L
			{
			glRotatef(left2, 0.0f, 0.0f, 1.0f);///////////////�ϥ��ܼƪ��a��
			glTranslatef(0.0f,100.0f,0.0f);//���ʶZ��
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);//�������ਤ��
			a_shank();//�p�L
			/////////////////////////////
			glPushMatrix();//���`
			{	
			glTranslatef(135.0f,0.0f,0.0f);//���ʶZ��
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
			joint();
			///////////////////////////////
			glPushMatrix();
			{
			glTranslatef(0.0f,35.0f,0.0f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
			drawCir(10.0f,15.0f,16);//���`�W���p�����b
			///////////////////////////////
			glPushMatrix();//�}�x
			{
			glRotatef(left3, 1.0f, 0.0f, 0.0f);////////////////////�ϥ��ܼƪ��a��
			glTranslatef(0.0f,112.5f,0.0f);//���ʶZ��
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);//�������ਤ��
			foot();
			}							  
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
	//////////////////////////		
	/////////////////////////
			glPushMatrix();//���}
			{	
			glPushMatrix();
			{	
			glTranslatef(-75.0f,-100.0f,0.0f);//���ʶZ��
			glRotatef(180.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
			joint();//���`
			////////////////////////
			glPushMatrix();
			{
			glTranslatef(0.0f,35.0f,0.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
			drawCir(10.0f,15.0f,16);//�j�L�W���p�����b
			/////////////////////////
			glPushMatrix();//�j�L
			{
			glRotatef(right1, 0.0f, 0.0f, 1.0f);/////////////////////////�ϥ��ܼƪ��a��
			glTranslatef(0.0f,200.0f,0.0f);//���ʶZ��
			a_thigh();//�j�L
			//////////////////////
			glPushMatrix();
			{
			glTranslatef(0.0f,200.0f,0.0f);//���ʶZ��
			drawCir(10.0f,15.0f,16);//�p�L�W���p�����b
			/////////////////////////////
			glPushMatrix();//�p�L
			{
			glRotatef(right2, 0.0f, 0.0f, 1.0f);///////////////////////////�ϥ��ܼƪ��a��
			glTranslatef(0.0f,100.0f,0.0f);//���ʶZ��
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);//�������ਤ��
			a_shank();//�p�L
			//////////////////////////////
			glPushMatrix();//���`
			{	
			glTranslatef(135.0f,0.0f,0.0f);//���ʶZ��
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
			joint();
			///////////////////////////////
			glPushMatrix();
			{	
			glTranslatef(0.0f,35.0f,0.0f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
			drawCir(10.0f,15.0f,16);//���`�W���p�����b
			////////////////////////////
			glPushMatrix();//�}�x
			{
			glRotatef(right3, 1.0f, 0.0f, 0.0f);//////////////////////�ϥ��ܼƪ��a��
			glTranslatef(0.0f,112.5f,0.0f);//���ʶZ��
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);//�������ਤ��
			foot();
			}							  
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
			}
			glPopMatrix();
	}
	glPopMatrix();
	}
	glPopMatrix();///�϶�13end
	// Save the matrix state
	////////////////////////

	//
	// swap buffers
	//
	glFlush();
	SwapBuffers(pDC->m_hDC);

	//
	// select old palette if we altered it
	//
	if (ppalOld)
		pDC->SelectPalette(ppalOld, 0);

	wglMakeCurrent(NULL, NULL);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGlView printing

BOOL CGlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGlView diagnostics

#ifdef _DEBUG
void CGlView::AssertValid() const
{
	CView::AssertValid();
}

void CGlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGlDoc* CGlView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGlDoc)));
	return (CGlDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGlView message handlers

BOOL CGlView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CGlView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	dc = new CClientDC (this);
	//CClientDC		dc(this);
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
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CGlView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if ((cx <= 0) || (cy <= 0))
		return;
	//�]�wOpen_Gl�e��	
	//CClientDC	dc(this);

	//
	// make the rendering context m_hrc current
	//
	//Cx=cx;
	//Cy=cy;
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

BOOL CGlView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
}
void CGlView::opengl_Initial()
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
	glClearColor(1.0f, 0.8f, 0.5f, 1.0f );//�]�w�६�C��	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�M���ù��ʧ@

}

void CGlView::OnDestroy() 
{
	CView::OnDestroy();
	wglMakeCurrent(NULL, NULL);
	if (m_hrc) {
		wglDeleteContext(m_hrc);
		m_hrc	= NULL;
	}
	// TODO: Add your message handler code here
	
}

void CGlView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar)
	{
	case 65://A,4
		xRot+=1.0f;
		break;
	case 67://C,3

		break;	
	case 68://D,6
		xRot+=-1.0f;
		break;
	case 69://E,9
		yRot+=-1.0f;
		break;
	case 81://Q,7
		yRot+=1.0f;
		break;
	case 83://S,5
		Line_Flag=!Line_Flag;
		break;
	case 87://W,8
		zRot+=1.0f;
		break;
	case 88://X,2
		zRot+=-1.0f;
		break;
	case 90://Z,1
		
		break;
	}
	Invalidate(true);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CGlView::joint()//���` 
{
	glColor3ub(128,128,128);//���`
	drawRetc(50.0f,20.0f,50.0f);//����Retc
	glPushMatrix();//�k�WRetc
		{
		glTranslatef(17.5f,22.f,0.0f);
		glColor3ub(128,128,128);
		drawRetc(15.0f,25.0f,50.0f);
		}
		glPopMatrix();
		glPushMatrix();//���WRetc
		{
		glTranslatef(-17.5f,22.5f,0.0f);
		glColor3ub(128,128,128);
		drawRetc(15.0f,25.0f,50.0f);
			}
			glPopMatrix();
			glPushMatrix();//�k�W��
			{
				glTranslatef(17.5f,35.0f,0.0f);
				glColor3ub(128,128,128);
				glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
				drawCir(25.0f,15.0f,16);
			}
			glPopMatrix();
			glPushMatrix();//���W��
			{
				glTranslatef(-17.5f,35.0f,0.0f);
				glColor3ub(128,128,128);
				glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
				drawCir(25.0f,15.0f,16);
			}
			glPopMatrix();
			glPushMatrix();//���W�p��
			{
				glTranslatef(-17.5f,35.0f,0.0f);
				glColor3ub(0,255,64);
				glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
				drawCir(10.0f,15.0f,16);
			}
			glPopMatrix();
			glPushMatrix();//�k�W�p��
			{
				glTranslatef(17.5f,35.0f,0.0f);
				glColor3ub(0,255,64);
				glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
				drawCir(10.0f,15.0f,16);
			}
			glPopMatrix();
			glPushMatrix();//���URetc
				{
				glTranslatef(0.0f,-(10.0f+25.0f/2.0f),0.0f);
				glColor3ub(128,128,128);
				drawRetc(50.0f,25.0f,20.0f);
				}
			glPopMatrix();
			glPushMatrix();//���U�j��
			{
				glTranslatef(0.0f,-(10.0f+25.0f),0.0f);
				glColor3ub(128,128,128);
				drawCir(25.0f,20.0f,16);
			}
			glPopMatrix();
			glPushMatrix();//���U�p��
			{
				glTranslatef(0.0f,-(10.0f+25.0f),0.0f);
				glColor3ub(0,255,64);
				drawCir(10.0f,20.0f,16);
			}
			glPopMatrix();
}	
////////////////////////////////////////////
void CGlView::a_shank()//�p�L
{
	glColor3ub(128,128,128);//�p�L
	drawRetc(150.0f,50.0f,50.0f);
		glPushMatrix();//����WRetc
		{
		glTranslatef(-87.5f,0.0f,17.5f);
		glColor3ub(128,128,128);
		drawRetc(25.0f,50.0f,15.0f);
		}
		glPopMatrix();
		glPushMatrix();//�����
		{
		glTranslatef(-100.0f,0.0f,17.5f);
		glColor3ub(128,128,128);
		drawCir(25.0f,15.0f,16);
		}
		glPopMatrix();
		glPushMatrix();//����p��
		{
		glTranslatef(-100.0f,0.0f,17.5f);
		glColor3ub(0,255,64);
		drawCir(10.0f,15.0f,16);
		}
		glPopMatrix();
		glPushMatrix();//����URetc
		{
		glTranslatef(-87.5f,0.0f,-17.5f);
		glColor3ub(128,128,128);
		drawRetc(25.0f,50.0f,15.0f);
		}
		glPopMatrix();
		glPushMatrix();//�����
		{
		glTranslatef(-100.0f,0.0f,-17.5f);
		glColor3ub(128,128,128);
		drawCir(25.0f,15.0f,16);
		}
		glPopMatrix();
		glPushMatrix();//����p��
		{
		glTranslatef(-100.0f,0.0f,-17.5f);
		glColor3ub(0,255,64);
		drawCir(10.0f,15.0f,16);
		}
		glPopMatrix();
		glPushMatrix();//�k��WRetc
		{
		glTranslatef(150.0f/2.0f+25.0f/2.0f,17.5f,0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
		glColor3ub(128,128,128);
		drawRetc(25.0f,50.0f,15.0f);
		}
		glPopMatrix();
		glPushMatrix();//�k���
		{
		glTranslatef(150.0f/2.0f+25.0f,17.5f,0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
		glColor3ub(128,128,128);
		drawCir(25.0f,15.0f,16);
		}
		glPopMatrix();
		glPushMatrix();//�k��p��
		{
		glTranslatef(150.0f/2.0f+25.0f,17.5f,0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
		glColor3ub(0,255,64);
		drawCir(10.0f,15.0f,16);
		}
		glPopMatrix();
		glPushMatrix();//�k��URetc
		{
		glTranslatef(150.0f/2.0f+25.0f/2.0f,-17.5f,0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
		glColor3ub(128,128,128);
		drawRetc(25.0f,50.0f,15.0f);
		}
		glPopMatrix();
		glPushMatrix();//�k���
		{
		glTranslatef(150.0f/2.0f+25.0f,-17.5f,0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
		glColor3ub(128,128,128);
		drawCir(25.0f,15.0f,16);
		}
		glPopMatrix();
		glPushMatrix();//�k��p��
		{
		glTranslatef(150.0f/2.0f+25.0f,-17.5f,0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
		glColor3ub(0,255,64);
		drawCir(10.0f,15.0f,16);
		}
		glPopMatrix();
}
////////////////////////////////////////
void CGlView::foot()//�}�x
{	
	glColor3ub(128,128,128);//�}�x
	drawRetc(175.0f,100.0f,50.0f);
	glPushMatrix();//�}�x���U-Retc
	{
	glTranslatef(-(175.0f/2.0f+50.0f/2.0f),-(50.0f/2.0f+25.0f/2.0f),0.0f);
	glColor3ub(128,128,128);
	drawRetc(50.0f,25.0f,50.0f);
	}
	glPopMatrix();
	glPushMatrix();//�}�x���U-Retc-�p��
	{
	glTranslatef(-(175.0f/2.0f+50.0f/2.0f),-(50.0f/2.0f+25.0f/2.0f),0.0f);
	glColor3ub(0,255,64);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
	drawCir(10.0f,25.0f,16);
	}
	glPopMatrix();
	glPushMatrix();//�}�x����-Retc
	{
	glTranslatef(-(175.0f/2.0f+50.0f/2.0f),0.0f,0.0f);
	glColor3ub(128,128,128);
	drawRetc(50.0f,25.0f,50.0f);
	}
	glPopMatrix();
	glPushMatrix();//�}�x����-Retc-�p��
	{		
	glTranslatef(-(175.0f/2.0f+50.0f/2.0f),0.0f,0.0f);
	glColor3ub(0,255,64);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
	drawCir(10.0f,25.0f,16);
	}
	glPopMatrix();
	glPushMatrix();//�}�x���W-Retc
	{
	glTranslatef(-(175.0f/2.0f+50.0f/2.0f),(50.0f/2.0f+25.0f/2.0f),0.0f);
	glColor3ub(128,128,128);
	drawRetc(50.0f,25.0f,50.0f);
	}
	glPopMatrix();
	glPushMatrix();//�}�x���W-Retc-�p��
	{		
	glTranslatef(-(175.0f/2.0f+50.0f/2.0f),(50.0f/2.0f+25.0f/2.0f),0.0f);
	glColor3ub(0,255,64);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
	drawCir(10.0f,25.0f,16);
	}
	glPopMatrix();		
}
void CGlView::a_thigh()//�j�L
{
	glColor3ub(128,128,128);//�j�L
	drawRetc(50.0f,350.0f,50.0f);
	glPushMatrix();//�j�L�WRetc
	{
	glTranslatef(0.0f,350.0f/2.0f+25.0f/2.0f,0.0f);
	glColor3ub(128,128,128);
	drawRetc(50.0f,25.0f,20.0f);
	}
	glPopMatrix();		
	glPushMatrix();//�j�L�W��
	{
	glTranslatef(0.0f,350.0f/2.0f+25.0f,0.0f);
	glColor3ub(128,128,128);
	drawCir(25.0f,20.0f,16);
	}
	glPopMatrix();
	glPushMatrix();//�j�L�W-�p��
	{
	glTranslatef(0.0f,350.0f/2.0f+25.0f,0.0f);
	glColor3ub(0,255,64);
	drawCir(10.0f,20.0f,16);
	}
	glPopMatrix();
	glPushMatrix();//�j�L�WRetc
	{
	glTranslatef(0.0f,-(350.0f/2.0f+25.0f/2.0f),0.0f);
	glColor3ub(128,128,128);
	drawRetc(50.0f,25.0f,20.0f);
	}
	glPopMatrix();		
	glPushMatrix();//�j�L�W��
	{
	glTranslatef(0.0f,-(350.0f/2.0f+25.0f),0.0f);
	glColor3ub(128,128,128);
	drawCir(25.0f,20.0f,16);
	}
	glPopMatrix();
	glPushMatrix();//�j�L�W-�p��
	{
	glTranslatef(0.0f,-(350.0f/2.0f+25.0f),0.0f);
	glColor3ub(0,255,64);
	drawCir(10.0f,20.0f,16);
	}
	glPopMatrix();
}
void CGlView::waist()//�y��
{			
	glPushMatrix();//�y��
	{		
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
	glColor3ub(128,128,128);//�y��
	drawRetc(300.0f,20.0f,100.0f);
	glPushMatrix();//�y�����W��W
	{
	glColor3ub(128,128,128);
	glTranslatef(-(150.0f/2.0f),15.0f,0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
	drawCir(40.0f,50.0f,16);//�y�����W��W-�j��
	glColor3ub(0,255,64);//�y�����W��W-�p��
	drawCir(10.0f,50.0f,16);
	}
	glPopMatrix();
	glPushMatrix();//�y�����W��W-���䪺Retc
	{
	glTranslatef(-(150.0f/2.0f),(40.0f+25.0f/2.0f),(10.0f/2.0f+25.0f/2.0f));
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
	glColor3ub(128,128,128);
	drawRetc(15.0f,25.0f,50.0f);
	}
	glPopMatrix();
	glPushMatrix();//�y�����W��W-�k�䪺Retc
	{
	glTranslatef(-(150.0f/2.0f),(40.0f+25.0f/2.0f),-(10.0f/2.0f+25.0f/2.0f));
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
	glColor3ub(128,128,128);
	drawRetc(15.0f,25.0f,50.0f);
	}
	glPopMatrix();
	glPushMatrix();
	{
	glTranslatef(-(150.0f/2.0f),(40.0f+25.0f),-(10.0f/2.0f+25.0f/2.0f));
	glColor3ub(128,128,128);
	drawCir(25.0f,15.0f,16);//�y�����W��W-���䪺�j��
	glColor3ub(0,255,64);
	drawCir(10.0f,15.0f,16);//�y�����W��W-���䪺�p��
	}
	glPopMatrix();
	glPushMatrix();
	{
	glTranslatef(-(150.0f/2.0f),(40.0f+25.0f),(10.0f/2.0f+25.0f/2.0f));
	glColor3ub(128,128,128);
	drawCir(25.0f,15.0f,16);//�y�����W��W-�k�䪺�j��
	glColor3ub(0,255,64);
	drawCir(10.0F,15.0F,16);//�y�����W��W-�k�䪺�p��
	}
	glPopMatrix();
	glPushMatrix();//�y���k�W��W
	{
	glColor3ub(128,128,128);
	glTranslatef(150.0f/2.0f,15.0f,0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);//�������ਤ��
	drawCir(40.0f,50.0f,16);//�y���k�W��W-�j��
	glColor3ub(0,255,64);//�y���k�W��W-�p��
	drawCir(10.0f,50.0f,16);
	}
	glPopMatrix();
	glPushMatrix();//�y���k�W��W-�k�䪺Retc
	{
	glTranslatef(150.0f/2.0f,(40.0f+25.0f/2.0f),10.0f/2.0f+25.0f/2.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
	glColor3ub(128,128,128);
	drawRetc(15.0F,25.0F,50.0F);
	}
	glPopMatrix();
	glPushMatrix();//�y���k�W��W-���䪺Retc
	{
	glTranslatef(150.0f/2.0f,(40.0f+25.0f/2.0f),-(10.0f/2.0f+25.0f/2.0f));
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
	glColor3ub(128,128,128);
	drawRetc(15.0F,25.0F,50.0F);
	}
	glPopMatrix();
	glPushMatrix();
	{
	glTranslatef(150.0f/2.0f,(40.0F+25.0F),-(10.0F/2.0F+25.0F/2.0f));
	glColor3ub(128,128,128);
	drawCir(25.0f,15.0f,16);//�y���k�W��W-�k�䪺�j��
	glColor3ub(0,255,64);
	drawCir(10.0f,15.0f,16);//�y���k�W��W-�k�䪺�p��
	}
	glPopMatrix();
	glPushMatrix();
	{
	glTranslatef(150.0f/2.0f,(40.0F+25.0F),(10.0F/2.0F+25.0F/2.0f));
	glColor3ub(128,128,128);
	drawCir(25.0F,15.0F,16);//�y���k�W��W-���䪺�j��
	glColor3ub(0,255,64);
	drawCir(10.0f,15.0f,16);//�y���k�W��W-���䪺�p��
	}
	glPopMatrix();	
	glPushMatrix();//�y�����U��Retc
	{
	glColor3ub(128,128,128);
	glTranslatef(0.0f,-(20.0f/2.0f+25.0f/2.0f),0.0f);
	drawRetc(20.0f,25.0f,50.0f);
	}
	glPopMatrix();
	glPushMatrix();
	{
	glColor3ub(128,128,128);
	glTranslatef(0.0f,-(20.0f/2.0f+25.0f),0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
	drawCir(25.0f,20.0f,16);//�y�����U���j��
	glColor3ub(0,255,64);
	drawCir(10.0f,20.0f,16);//�y�����U���p��
	}
	glPopMatrix();
	glPushMatrix();//�y�����U����Retc	
	{
	glColor3ub(128,128,128);
	glTranslatef(-140.0f,-(20.0f/2.0f+25.0f/2.0f),0.0f);
	drawRetc(10.0f,25.0f,50.0f);
	}
	glPopMatrix();
	glPushMatrix();
	{
	glColor3ub(128,128,128);
	glTranslatef(-140.0f,-(20.0f/2.0f+25.0f),0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
	drawCir(25.0f,10.0f,16);//�y�����U�����j��
	glColor3ub(0,255,64);
	drawCir(10.0f,10.0f,16);//�y�����U�����p��
	}
	glPopMatrix();
	glPushMatrix();//�y�����U�k��Retc	
	{
	glColor3ub(128,128,128);
	glTranslatef(140.0f,-(20.0f/2.0f+25.0f/2.0f),0.0f);
	drawRetc(10.0f,25.0f,50.0f);
	}
	glPopMatrix();
	glPushMatrix();
	{
	glColor3ub(128,128,128);
	glTranslatef(140.0f,-(20.0f/2.0f+25.0f),0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);//�������ਤ��
	drawCir(25.0f,10.0f,16);//�y�����U�k���j��
	glColor3ub(0,255,64);
	drawCir(10.0f,10.0f,16);//�y�����U�k���p��
	}
	glPopMatrix();
	}
	glPopMatrix();
}				

void CGlView::FWKinematic()
{

}



void CGlView::BWKinematic()	//�f�V�B�ʤ�{
{
float rvx,rvy;
float lvx,lvy;
float rpx,rpy;
float lpx,lpy;
float a,b,c,d,e,k;
float pi=3.14159f;
float allangle;
float Langle1,Langle2,Langle3;
float Rangle1,Rangle2,Rangle3;

allangle=pi/2;

///////////////////////����//////////////////////////
lvy=755.0f-lfoot_y;
lvx=-lfoot_z;

lpx=lvx;
lpy=lvy-a3;

k=((lpx*lpx+lpy*lpy-a1*a1-a2*a2)/(2*a1*a2));

if(fabs(k-1)<=0.001)
{Langle2=0;}
else 
{Langle2=float(-acos(k));}

a=float((lpx*(a1+a2*cos(Langle2))+lpy*a2*sin(Langle2))/(a1*a1+a2*a2+2*a1*a2*cos(Langle2)));//cos(1)
b=float((-lpx*a2*sin(Langle2)+lpy*(a1+a2*cos(Langle2)))/(a1*a1+a2*a2+2*a1*a2*cos(Langle2)));//sin(1)

if(fabs(a<=0.001) && fabs(b-1)<=0.001)
{Langle1=pi/2;}
else 
{Langle1=float(atan2(b,a));}

Langle3=allangle-Langle1-Langle2;

left3=Langle1*(180.0f/pi);
left2=Langle2*(180.0f/pi);
left1=Langle3*(180.0f/pi);



////////////////////////�k��//////////////////////////

rvy=755.0f-rfoot_y;
rvx=-rfoot_z;

rpx=rvx;
rpy=rvy-a3;

c=((rpx*rpx+rpy*rpy-a1*a1-a2*a2)/(2*a1*a2));

if(fabs(c-1)<=0.001)
{
	Rangle2=0.0;
}
else
{Rangle2=float(-acos(c));}

d=float((rpx*(a1+a2*cos(Rangle2))+rpy*a2*sin(Rangle2))/(a1*a1+a2*a2+2*a1*a2*cos(Rangle2)));//cos(1)
e=float((-rpx*a2*sin(Rangle2)+rpy*(a1+a2*cos(Rangle2)))/(a1*a1+a2*a2+2*a1*a2*cos(Rangle2)));//sin(1)

if(fabs(d<=0.001) && fabs(e-1)<=0.001)
{Rangle1=pi/2;}
else
{Rangle1=float(atan2(e,d));}

Rangle3=allangle-Rangle1-Rangle2;

right3=Rangle1*(180.0f/pi);
right2=Rangle2*(180.0f/pi);
right1=Rangle3*(180.0f/pi);


}

void CGlView::transform()
{
if(left1<0)
	{left1=360+left1;}
if(left2<0)
	{left2=360+left2;}
if(left3<0)
	{left3=360+left3;}
if(right1<0)
	{right1=360+right1;}
if(right2<0)
	{right2=360+right2;}
if(right3<0)
	{right3=360+right3;}

if(left1<90)
{left1=-left1;}
else if (270<=left1 && left1<360)
{left1=360-left1;}

if(right1<90)
{right1=-right1;}
else if (270<=right1 && right1<360)
{right1=360-right1;}

left2=360-left2;

right2=360-right2;

if(left3>90)
	{left3=left3-90;}
else if(left3<90)
	{left3=-(90-left3);}
else
	{left3=0;} 

if(right3>90)
	{right3=right3-90;}
else if(right3<90)
	{right3=-(90-right3);}
else
	{right3=0;}
	
  }


void CGlView::Onwalkstart() 
{
			waist_y=0.0f;
			waist_z=0.0f;
						
			rfoot_y=83.64f;
			rfoot_z=-310.0f;
		
			lfoot_y=0.0f;
			lfoot_z=0.0f;		
			SetTimer(1,100,NULL);
			
}


void CGlView::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 1:	
 			CGlView::BWKinematic();
			CGlView::transform();		
			if(rfoot_y!=0.0f)
			{	
				rfoot_y=rfoot_y-83.64f/30.0f;
				rfoot_z=rfoot_z+310.0f/30.0f;

			}
			if(rfoot_y<0.0f)
			{
				//SetTimer(2,100,NULL);
				KillTimer(1);
			}
  
			Invalidate(true);

			break;

	case 2:	
		 	CGlView::BWKinematic();
			CGlView::transform();  
			if(lfoot_y!=0.0f)
			{	
				lfoot_y=lfoot_y-83.64f/20.0f;
				lfoot_z=lfoot_z+310.0f/20.0f;

			}
			if(lfoot_y<0.0f)
			{
				KillTimer(2);
			}

			Invalidate(true);
			break;
	case 3:
			
			if(next_work==0)
			{
 				CGlView::BWKinematic();
				CGlView::transform();		
				if(rfoot_y!=0.0f)
				{	
					rfoot_y=rfoot_y-83.64f/30.0f;
					rfoot_z=rfoot_z+310.0f/30.0f;

				}
				if(rfoot_y<0.0f)
				{
					next_work=1;

					waist_y=0.0f;
					waist_z=0.0f;
					
					rfoot_y=0.0f;
					rfoot_z=0.0f;		
				
					lfoot_y=83.64f;
					lfoot_z=-310.0f;
				}
				Invalidate(true);
			}
			else
			{
				
				CGlView::BWKinematic();
				CGlView::transform(); 
				
				if(lfoot_y!=0.0f)
				{	
					lfoot_y=lfoot_y-83.64f/20.0f;
					lfoot_z=lfoot_z+310.0f/20.0f;

				}
				if(lfoot_y<0.0f)
				{
					next_work=0;
					if(x<24)
					{
						x=x+1;
						waist_y=0.0f;
						waist_z=0.0f;
						
						lfoot_y=0.0f;
						lfoot_z=0.0f;
		
						rfoot_y=83.64f;
						rfoot_z=-310.0f;
					}
					else
					{
						KillTimer(3);
					}
				/*
					if(x<3)
					{
					x=x+1;
					CGlView::OnTt();
					}
				*/

				}
				
				Invalidate(true);
			}
		break;
	}
	CView::OnTimer(nIDEvent);
}




void CGlView::Oninput() 
{
   
 //   ControlDialog a(this);
	
//	if(a.DoModal())
//	{ 
			waist_y=0.0f;
			waist_z=0.0f;
						
			rfoot_y=0.0f;
			rfoot_z=0.0f;
		
			lfoot_y=83.64f;
			lfoot_z=-310.0f;


			SetTimer(2,100,NULL);
//	}	
	Invalidate(true);
	// TODO: Add your command handler code here
}

void CGlView::OnTt() 
{

//
//CGlView::Onwalkstart();	
//CGlView::Oninput();	

		waist_y=0.0f;
		waist_z=0.0f;			
		
		rfoot_y=83.64f;
		rfoot_z=-310.0f;
		
		lfoot_y=0.0f;
		lfoot_z=0.0f;

		SetTimer(3,25,NULL);
	
}
