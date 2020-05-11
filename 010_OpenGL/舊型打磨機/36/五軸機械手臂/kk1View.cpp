// kk1View.cpp : implementation of the CKk1View class
//

#include "stdafx.h"
#include "kk1.h"
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include <gl/glut.h>
#include "kk1Doc.h"
#include "kk1View.h"
////////////////////////////
#include "OpenGLFun.h"
#include "OpenGLPara.h"
#include "glmfc.h"
/////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
FILE *k;
FILE *k1;
FILE *l;
int Cx,Cy;
int jx=0,jy=0,jz=0,jt=0;
int y_base=0;
int x_main_hand=0;
int senser_Rotate=0;
/////////////////////////////////////////////////////////////////////////////
float Theta=0,PDX=0,PDY=0,PAX=0,PAY=0,DeltaT=0;
///////////////////////////////////////////
//����
#define	MAP_NAME0	"spacesoft corp0."
#define	MAP_NAME1	"spacesoft corp1."
#define	MAP_NAME2	"spacesoft corp2."
#define	MAP_NAME3	"spacesoft corp3."
#define	MAP_NAME4	"spacesoft corp4."
#define	MAP_NAME5	"spacesoft corp5."
#define	MAP_LENGTH	16
HANDLE hFileMap0 = NULL ;
HANDLE hFileMap1 = NULL ;
HANDLE hFileMap2 = NULL ;
HANDLE hFileMap3 = NULL ;
HANDLE hFileMap4 = NULL ;
HANDLE hFileMap5 = NULL ;
static char szOldData[MAP_LENGTH] = "" ;
/////////////////////////////////////////////////////////////////////////////
//�ǰe
#define	MAP_NAME6	"spacesoft corp6."
#define	MAP_NAME7	"spacesoft corp7."
#define	MAP_NAME8	"spacesoft corp8."
#define	MAP_NAME9	"spacesoft corp9."
HANDLE hFileMap6 = NULL ;
HANDLE hFileMap7 = NULL ;
HANDLE hFileMap8 = NULL ;
HANDLE hFileMap9 = NULL ;
/////////////////////////////////////////////////////////////////////////////
//�ᤩ���x�ͩR�ܼ�
float X_offset=48;
float Y_offset=100;
float Z_offset=554;
float X_toffset=145;
float Y_toffset=575;
float Z_toffset=318;
float a1=205;
float d4=150;
float Theta_w0=0;
float Theta_w9=0;
/////////////////////////////////////////////////////////////////////////////
bool ontimer=false;//�p�ƾ��X��
bool map=false;//�O����M�g�X��
int next_number=0;
int next_break1=0;
/////////////////////////////////////////////////////////////////////////////
GLfloat life_x=0;//�ᤩ���x�ͩR�ܼ�
GLfloat life_y=0;
GLfloat life_z=0;
GLfloat life_r=0;


/////////////////////////////////////////////////////////////////////////////
int work_number=0;
/////////////////////////////////////////////////////////////////////////////
// CKk1View

IMPLEMENT_DYNCREATE(CKk1View, CScrollView)

BEGIN_MESSAGE_MAP(CKk1View, CScrollView)
	//{{AFX_MSG_MAP(CKk1View)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_COMMAND(ID_settimer, Onsettimer)
	ON_COMMAND(ID_Directly, OnDirectly)
	ON_COMMAND(ID_Flank, OnFlank)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKk1View construction/destruction

CKk1View::CKk1View()
{
	// TODO: add construction code here
	xRot=0;
	yRot=0;
	zRot=0;
}

CKk1View::~CKk1View()
{
}

BOOL CKk1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CKk1View drawing

void CKk1View::OnDraw(CDC* pDC)
{
	//MessageBox("OnDraw");
	m_pPal = NULL;
	CKk1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// select the palette
	//
	CPalette *	ppalOld	= NULL;
	if (m_pPal) {
		ppalOld	= pDC->SelectPalette(m_pPal, 0);
		pDC->RealizePalette();
	}
	BOOL	bResult	= wglMakeCurrent(pDC->m_hDC, m_hrc);
	if (FALSE == bResult)
		TRACE(_T("wglMakeCurrent() failed %x.\r\n"), ::GetLastError());
	
//	Rend();//�쥻���i���{��

	opengl_Initial();	
//	opengl_disc();//��L���y
opengl_final();
//opengl_ServoMotor();
//	draw_child(dialog_set);
	glFlush();
	SwapBuffers(dc->m_hDC);
	if (ppalOld)
	pDC->SelectPalette(ppalOld, 0);
	wglMakeCurrent(NULL, NULL);
	// TODO: add draw code for native data here
}

void CKk1View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CKk1View printing

BOOL CKk1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKk1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKk1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CKk1View diagnostics

#ifdef _DEBUG
void CKk1View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CKk1View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CKk1Doc* CKk1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKk1Doc)));
	return (CKk1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKk1View message handlers

void CKk1View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnMouseMove(nFlags, point);
}

void CKk1View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPen pen(PS_SOLID,3,RGB(255,255,0));
	cb=point;
	aDC->SelectObject(&pen);
	aDC->MoveTo(ca);
	aDC->LineTo(cb);
	ReleaseCapture();
	CScrollView::OnLButtonUp(nFlags, point);
}

void CKk1View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	SetCapture();
	aDC=new CClientDC(this);
	ca=point;
	/*
	CString a,b;
	char k1[10];
	b="x=";
	_itoa(point.x ,k1,10);
	a=k1;
	b=b+a;
	_itoa(point.y,k1,10);
	a=k1;
	b=b+"y=";
	b=b+a;
	MessageBox(b);
	*/
	CScrollView::OnLButtonDown(nFlags, point);
}
void CKk1View::Rend()
{
	//CGrinderOpenGLDoc * pDoc = GetDocument();
	CKk1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////	
	//
	// enable depth calculations
	//
	glEnable(GL_DEPTH_TEST);		// Hidden surface removal
	glFrontFace(GL_CCW);			// Counter clock-wise polygons face out
	glDisable(GL_CULL_FACE);		// Do not calculate inside of jet
	glShadeModel(GL_SMOOTH);

	//
	// enable lighting calculations
	//	
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glEnable(GL_LIGHT0);
	
	//
	// set the material color to follow the current color
	//
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);	
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	//
	// clear the color and depth buffers
	//
	glClearColor(1.0f, 0.8f, 0.5f, 1.0f );	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

//////Draw Program Start/////////////////////////////////////////////////// 

	glLineWidth(1.5f);	// �u���j�p

	if(Line_flag)
	//if(TRUE)
	{
		glPolygonMode(GL_FRONT_AND_BACK ,GL_LINE);
		glLineWidth(0.1f);	// �u���j�p
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK ,GL_FILL);
		glLineWidth(0.1f);	// �u���j�p
	}

	
	if(View_lock == FALSE)			// �P�_�����O�_��w
	{
		if(View_flag == Up_View)			// �W����
		{
			xRot = yRot = zRot = 0.0f;
//			xView = yView  = 0.0f;
		}
		else if(View_flag == Front_View)	// �e����
		{
			xRot = -90.0f;
			yRot =	0.0f;
			zRot =	90.0f;
//			xView = yView =  0.0f;
		}
		else if(View_flag == Back_View)		// �����
		{
			xRot = -90.0f;
			yRot =	0.0f;
			zRot = -90.0f;
//			xView = yView =  0.0f;
		}
		else if(View_flag == Right_View)	// �k����
		{
			xRot = -90.0f;
			zRot = 0.0f;
			yRot = 0.0f;
//			xView = yView =  0.0f;
		}
		else if(View_flag == Left_View)		// ������
		{
			xRot = -90.0f;
			zRot = 180.0f;
			yRot = 0.0f;
//			xView = yView =  0.0f;
		}
		else if(View_flag == Orign_View)	// �����
		{
			xRot = 285.0f;
			yRot = 0.0f;
			zRot = 50.0f;
//			xView = yView =  0.0f;
		}
	}
	glPushMatrix();
	{
		glTranslatef(xView, yView, zView);
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glRotatef(zRot, 0.0f, 0.0f, 1.0f);
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
	glPushMatrix();
	{
		// ���y
		glTranslatef(Base_W/2, Base_L/2, Base_H/2);
		glColor3ub(96, 96, 96);
		drawRetc(Base_W, Base_L, Base_H);
		// ���y(��)
		glPushMatrix();
		{
			// X�b
			// ��
			glTranslatef(-Base_W/2+X_axis_W/2, -Base_L/2+X_axis_L/2, Base_H/2+X_axis_H/2);
			glColor3ub(128, 128, 200);
			drawRetc(X_axis_W, X_axis_L, X_axis_H);
			// �k
			glTranslatef(0.0f, -X_axis_L/2+2*Base_L/2-X_axis_L/2, 0.0f);
			glColor3ub(128, 128, 200);
			drawRetc(X_axis_W, X_axis_L, X_axis_H);
			// X�b(��)

			// Y�b
			glTranslatef(-X_axis_W/2+Y_axis_W/2+X_shift, X_axis_L/2-Y_axis_L/2, X_axis_H/2+Y_axis_H/2);
			glTranslatef(X_shift, 0.0f, 0.0f);			// X_shift Parameter
			glColor3ub(128, 128, 200);
			drawRetc(Y_axis_W, Y_axis_L, Y_axis_H);
			// Y�b(��)

			// Link1-1
			glTranslatef(0.0f, -Y_axis_L/2+Link11_L/2+Y_shift, Y_axis_H/2+Link11_H/2);
			glTranslatef(0.0f, Y_shift, 0.0f);			// Y_shift Parameter
			glColor3ub(128, 128, 200);
			drawRetc(Link11_W, Link11_L, Link11_H);
			// Link1-1(End)

			// Servo Motor 1
			glPushMatrix();
			{
				glTranslatef(-Y_axis_W/2-SM1_Bottom_W/2, 0.0f, -Link11_H/2+SM1_Bottom_H/2);
				glColor3ub(200, 128, 128);
				drawRetc(SM1_Bottom_W, SM1_Bottom_L, SM1_Bottom_H);

				glTranslatef(0.0f, 0.0f, SM1_Bottom_H/2+SM1_Middle_L/2);
				glColor3ub(96, 128, 96);
				drawCir(SM1_Middle_R, SM1_Middle_L, 16);

				glTranslatef(0.0f, 0.0f, SM1_Middle_L/2+SM1_Top_L/2);
				glColor3ub(96, 128, 200);
				drawCir(SM1_Top_R, SM1_Top_L, 16);

			}
			glPopMatrix();
			// Servo Motor 1(End)
			
			// Bar1-1
			glTranslatef(0.0f, 0.0f, Link11_H/2+Bar11_L/2);
			glRotatef(Rotate1, 0.0f, 0.0f, 1.0f);		// Rotate1 Parameter
			glColor3ub(128, 30, 56);
			drawCir(Bar11_R, Bar11_L, 16);
			// Bar1-1(End)

			// Link1-2
			glTranslatef(0.0f, 0.0f, Bar11_L/2+Link12_H/2);
			glColor3ub(200, 100, 200);
			drawRetc(Link12_W, Link12_L, Link12_H);
			// Link1-2(End)
			
			// Bar1-2
			glTranslatef(0.0f, -Link12_L/2-Bar12_L/2, 0.0f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(Rotate2, 0.0, 0.0f, 1.0f);		// Rotate2 Parameter
			glColor3ub(98, 16, 200);
			drawCir(Bar12_R, Bar12_L, 16);
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			// Bar1-2(End)

			// Link2
			glTranslatef(Link2_W/2, -Bar12_L/2+Link2_L/2-0.1f, 0.0f);
			glColor3ub(128, 128, 200);
			drawRetc(Link2_W, Link2_L, Link2_H);
			// Link2(��)

			// Loadcell
			glTranslatef(Link2_W/2+Loadcell1_L/2, 0.0f, 0.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(Rotate3, 0.0f, 0.0f, 1.0f);		// Rotate3 Parameter
			glColor3ub(128, 64, 64);
			drawCir(Loadcell1_R, Loadcell1_L, 16);
			glTranslatef(0.0f, 0.0f, Loadcell1_L/2+Loadcell2_L/2);
			glColor3ub(156, 64, 64);
			drawCir(Loadcell2_R, Loadcell2_L, 16);
			// Loadcell(��)
			
			// Fixture
			glTranslatef(0.0f, 0.0f, Loadcell2_L/2+Fixture1_L/2);
			glColor3ub(128, 128, 128);
			drawCir(Fixture1_R, Fixture1_L, 16);
			glTranslatef(0.0f, 0.0f, Fixture1_L/2+Fixture2_L/2);
			glColor3ub(128, 128, 128);
			drawCir(Fixture2_R, Fixture2_L, 16);
			// Fixture(��)

			glTranslatef(0.0f, 0.0f, Fixture2_L/2+Watch1_1_H/2);
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
///*�R����ذ_�l��m
			// Watch Model
			// Watch1_1 ��
			glPushMatrix();
			{
				glTranslatef(Watch1_2_W/2+Watch1_1_W/2,0.0f,  0.0f);
				glColor3ub(96, 96, 96);
				drawRetc(Watch1_1_W, Watch1_1_L, Watch1_1_H);
			}	
			glPopMatrix();
			// Watch1_1 ��(End)
			// Watch1_1 �k
			glPushMatrix();
			{
				glTranslatef(-(Watch1_2_W/2+Watch1_1_W/2), 0.0f, 0.0f);
				glColor3ub(96, 96, 96);
				drawRetc(Watch1_1_W, Watch1_1_L, Watch1_1_H);
			}	
			glPopMatrix();
			// Watch1_1 �k(End)
			// Watch1_2 �W
			glPushMatrix();
			{
				glTranslatef(0.0f, Watch1_1_L/2-Watch1_2_L/2, 0.0f);
				glColor3ub(96, 96, 96);
				drawRetc(Watch1_2_W, Watch1_2_L, Watch1_2_H);
			}
			glPopMatrix();
			// Watch1_2 �W(End)
			// Watch1_2 �U
			glPushMatrix();
			{
				glTranslatef( 0.0f, -(Watch1_1_L/2-Watch1_2_L/2),0.0f);
				glColor3ub(96, 96, 96);
				drawRetc(Watch1_2_W, Watch1_2_L, Watch1_2_H);
			}
			glPopMatrix();
			// Watch1_2 �U(End)
			// Watch Model(End)
//*/�R����ص�����m	
		}
		glPopMatrix();

		// ��������y
		// ���yBase
		glTranslatef(Base_W/2+GrinderHold_Base_W/2, 0.0f, -Base_H/2+GrinderHold_Base_H/2);
		glColor3ub(68, 68, 68);
		drawRetc(GrinderHold_Base_W, GrinderHold_Base_L, GrinderHold_Base_H);
		// ���yBase(��)
		// Base1 ��
		glPushMatrix();
		{
			glTranslatef(0.0f, GrinderHold_Base_L/2-GrinderHold1_R, GrinderHold_Base_H/2);
			glRotatef(-90, 0.0f, 1.0f, 0.0f);
			glColor3ub(68, 68, 68);
			drawCir(GrinderHold1_R, GrinderHold1_L, 16);
		}
		glPopMatrix();
		// Base1 ��(��)
		// Base1 �k
		glPushMatrix();
		{
			glTranslatef(0.0f, -GrinderHold_Base_L/2+ GrinderHold1_R, GrinderHold_Base_H/2);
			glRotatef(-90, 0.0f, 1.0f, 0.0f);
			glColor3ub(68, 68, 68);
			drawCir(GrinderHold1_R, GrinderHold1_L, 16);
		}
		glPopMatrix();
		// Base1 �k(��)
		// Base �W
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, GrinderHold_Base_H/2+GrinderHold2_H/2);
			glColor3ub(68, 68, 68);
			drawRetc(GrinderHold2_W, GrinderHold2_L, GrinderHold2_H);
		}
		glPopMatrix();
		// Base �W(��)
		// ��������y(��)
		
		// ���
		glTranslatef(GrinderHold_Base_W/2, -GrinderHold_Base_L/2+GrinderHold1_R+Grinder_init_shift, GrinderHold_Base_H/2);
		glPushMatrix();
		{
			// ���1
			glPushMatrix();
			{
				glTranslatef(-Grinder_Bar_L/2, 0.0f, 0.0f);
				glRotatef(-90, 0.0f, 1.0f, 0.0f);
				glRotatef(Grinder_Rotate, 0.0f, 0.0f, 1.0f);
				glColor3ub(28, 28, 28);
				drawCir(Grinder_Bar_R, Grinder_Bar_L, 16);
				
				glTranslatef(0.0f, 0.0f, Grinder_Bar_L/2-Grinder_L/2);
				glColor3ub(128, 64, 64);
				drawCir(Grinder_R, Grinder_L, 32);
				glRotatef(90, 0.0f, 1.0f, 0.0f);
			}
			glPopMatrix();
			// ���1(End)
			// ���2
			glPushMatrix();
			{
				glTranslatef(-(Grinder_Bar_L+Grinder_Distance)/2, Grinder_Bar_Distance, 0.0f);
				glRotatef(-90, 0.0f, 1.0f, 0.0f);
				glRotatef(Grinder_Rotate, 0.0f, 0.0f, 1.0f);
				glColor3ub(28, 28, 28);
				drawCir(Grinder_Bar_R, Grinder_Bar_L+Grinder_Distance, 16);
				
				glTranslatef(0.0f, 0.0f, (Grinder_Bar_L+Grinder_Distance)/2-Grinder_L/2);
				glColor3ub(200, 200, 200);
				drawCir(Grinder_R, Grinder_L, 32);
				glRotatef(90, 0.0f, 1.0f, 0.0f);
			}
			glPopMatrix();
			// ���2(End)
			// ���3
			glPushMatrix();
			{
				glTranslatef(-(Grinder_Bar_L+2*Grinder_Distance)/2, 2*Grinder_Bar_Distance, 0.0f);
				glRotatef(-90, 0.0f, 1.0f, 0.0f);
				glRotatef(Grinder_Rotate, 0.0f, 0.0f, 1.0f);
				glColor3ub(28, 28, 28);
				drawCir(Grinder_Bar_R, Grinder_Bar_L+2*Grinder_Distance, 16);
				
				glTranslatef(0.0f, 0.0f, (Grinder_Bar_L+2*Grinder_Distance)/2-Grinder_L/2);
				glColor3ub(128, 200, 64);
				drawCir(Grinder_R, Grinder_L, 32);
				glRotatef(90, 0.0f, 1.0f, 0.0f);
			}
			glPopMatrix();
			// ���3(End)
		}
		glPopMatrix();
	}
	glPopMatrix();
	}
	glPopMatrix();
//////Draw Program End/////////////////////////////////////////////////////
	//
	// flush the drawing pipeline
	//
	//glFlush();
	//SwapBuffers(dc->m_hDC);

}

int CKk1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
//	CClientDC		dc(this);
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
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	//
	// create the palette
	//
	CreateRGBPalette(dc->m_hDC, m_pPal);
	k=fopen("k.txt","w");
	// TODO: Add your specialized creation code here
	hFileMap6 = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME6 ) ;
	hFileMap7 = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME7 ) ;
	hFileMap8 = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME8 ) ;
	hFileMap9 = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME9 ) ;
	return 0;
}

void CKk1View::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);	
	if ((cx <= 0) || (cy <= 0))
		return;
//�]�wOpen_Gl�e��	
//	CClientDC	dc(this);

	//
	// make the rendering context m_hrc current
	//
	Cx=cx;
	Cy=cy;
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
    glViewport(0, 0, w, h);

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
	// TODO: Add your message handler code here
	
}
void CKk1View::Update(int x,int y,int pitch,int yaw,int row,int sw)
{
	if(y_base<189)
	{
		y_base+=x;
	}
	else
	{
		senser_Rotate+=10;
		y_base=189;	
	}
/*
	switch(sw)
	{
	case 1:
		if(X_shift<100)
		{
			X_shift+= x;
		}
		else
		{
			X_shift=100;
		}
		if(Y_shift<110)
		{
			Y_shift+=y;
		}
		else
		{
			Y_shift=110;
		}
		Rotate1=0;
		Rotate2=0;
		Rotate3+=row;

		break;
	case 2:
		X_shift=x;
		Y_shift=y;
		Rotate1=pitch;
		Rotate2=yaw;
		Rotate3=row;
		break;
	}
//	Rotate1+=yaw;
//	Rotate2+=pitch;
//	Rotate3+=row;
*/

	Invalidate(true);
}
void CKk1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_NUMPAD5:
		Line_Side=!Line_Side;
		break;
	case VK_NUMPAD2:
		//MessageBox("2");
		View_lock = TRUE;
		xRot += 5.0f;
		break;
	case VK_NUMPAD4:

		View_lock = TRUE;		
		yRot -= 5.0f;
		break;
	case VK_NUMPAD6:

		View_lock = TRUE;
		yRot += 5.0f;
		break;
	case VK_NUMPAD7:

		View_lock = TRUE;
		zRot -= 5.0f;
		break;
	case VK_NUMPAD8:

		View_lock = TRUE;
		xRot-= 5.0f;
		break;
	case VK_NUMPAD9:

		View_lock = TRUE;
		zRot += 5.0f;
		break;
	case VK_F1:
		//View_lock = FALSE;
		xRot=0;
		yRot=0;
		zRot=0;
		jx=0;
		jy=0;
		jz=0;
		break;
	case VK_F2:
		//View_lock = FALSE;
		//jx=30;
		//jy=100;
		xRot=-90;
		yRot=0;
		zRot=0;
		jx=0;
		jy=0;
		jz=0;
		break;
	case VK_F3:
		//View_lock = FALSE;
		//jx=30;
		//jy=170;
		xRot=-90;
		yRot=0;
		zRot=90;
		jx=0;
		jy=0;
		jz=0;
		break;
	case VK_F4:
		//View_lock = FALSE;
		//jx=30;
		//jy=270;
		xRot=-90;
		yRot=0;
		zRot=-90;
		jx=0;
		jy=0;
		jz=0;
		break;
	case VK_F5:

		break;
	case VK_F6:
		View_lock = FALSE;

		break;
	/////////////////////////
	case VK_F7://x
		View_lock = TRUE;
		senser_Rotate+=10;
		break;
	case VK_F8://y
		View_lock = TRUE;

		x_main_hand+=10;
		break;
	case VK_F9://yaw
		View_lock = TRUE;

		jz++;
		break;
	case VK_F12://pitch
		View_lock = TRUE;
		jy+=1;

		break;
	case VK_F11://row
		View_lock = TRUE;

		jx+=1;
		break;
	}
	Invalidate(true);
	
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}
BOOL CKk1View::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
		return TRUE;
}
void CKk1View::draw_child(int IntSwitch)
{
	//�f����x��
	////////////////////////////////
	glPushMatrix();
	{
	glColor3f(10.0f,0.0f,0.0f);
	glLineWidth(1.0);

	glBegin(GL_LINES);
	glVertex3f(600,0,0);//���U
	glVertex3f(600,300,0);//���W
	glEnd();
		
	glBegin(GL_LINES);
	glVertex3f(600,0,0);//���U
	glVertex3f(1000,0,0);//�k�U
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(1000,0,0);//�k�U
	glVertex3f(1000,300,0);//�k�W
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(1000,300,0);//�k�U
	glVertex3f(600,300,0);//�k�W
	glEnd();
	}
	glPopMatrix();
	switch(IntSwitch)
	{
	case 1:
	glColor3f(32.0f,253.0f,253.0f);
	draw_child1();
	glColor3f(0.0f,0.0f,0.0f);
	draw_child2();
	draw_child3();
	draw_child4();
	break;
	case 2:
	glColor3f(32.0f,253.0f,253.0f);
	draw_child2();
	glColor3f(0.0f,0.0f,0.0f);
	draw_child1();
	draw_child3();
	draw_child4();
	break;
	case 3:
	glColor3f(32.0f,253.0f,253.0f);
	draw_child3();
	glColor3f(0.0f,0.0f,0.0f);
	draw_child1();
	draw_child2();
	draw_child4();
	break;
	case 4:
	glColor3f(32.0f,253.0f,253.0f);
	draw_child4();
	glColor3f(0.0f,0.0f,0.0f);
	draw_child1();
	draw_child2();
	draw_child3();
	break;
	default:
	glColor3f(0.0f,0.0f,0.0f);
	draw_child4();
	draw_child1();
	draw_child2();
	draw_child3();
	}

}
void CKk1View::draw_child1(void)//��
{
	glPushMatrix();
	{
	//glColor3f(188.0f,0.0f,200.0f);
	glBegin(GL_QUADS);
	glVertex3f(700,30,0);//���U
	glVertex3f(700,270,0);//���W
	glVertex3f(740,270,0);//�k�W
	glVertex3f(740,30,0);//�k�U
	glEnd();
	}
	glPopMatrix();
}
void CKk1View::draw_child2(void)//�W
{
	glPushMatrix();
	{
	//glColor3f(0.0f,0.0f,10.0f);
	glBegin(GL_QUADS);
	glVertex3f(740,210,0);//���U
	glVertex3f(740,250,0);//���W
	glVertex3f(890,250,0);//�k�W
	glVertex3f(890,210,0);//�k�U
	glEnd();
	}
	glPopMatrix();

}
void CKk1View::draw_child3(void)//�k
{
	glPushMatrix();
	{
	//glColor3f(10.0f,0.0f,10.0f);
	glBegin(GL_QUADS);
	glVertex3f(890,30,0);//���U
	glVertex3f(890,270,0);//���W
	glVertex3f(930,270,0);//�k�W
	glVertex3f(930,30,0);//�k�U
	glEnd();
	}
	glPopMatrix();
}
void CKk1View::draw_child4(void)//�U
{
	glPushMatrix();
	{
	//glColor3f(10.0f,10.0f,0.0f);
	glBegin(GL_QUADS);
	glVertex3f(740,50,0);//���U
	glVertex3f(740,90,0);//���W
	glVertex3f(890,90,0);//�k�W
	glVertex3f(890,50,0);//�k�U
	glEnd();
	}
	glPopMatrix();
}
void CKk1View::opengl_Initial(void)
{

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

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);	
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(1.0f, 0.8f, 0.5f, 1.0f );	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
void CKk1View::opengl_disc(void)//jash_liao writes main programe of open gl
{
	int Cir_R,Cir_L,x_w,x_l,x_h,y_w,y_l,y_h;
			//���Ҿ�start
			glPushMatrix();
			{

				
				glRotatef(-45-jx, 1.0f, 0.0f, 0.0f);
				glRotatef(0-jy, 0.0f, 0.0f, 1.0f);

				//���start
				glRotatef(90, 1.0f, 0.0f, 0.0f);
				glColor3ub(128, 0, 0);
				glTranslatef(250,250,-500);//�� �W �e
				drawCir(100, 20, 1000);
				glTranslatef(0,0,-9);
				glColor3ub(128, 0, 120);
				drawCir(15, 40, 1000);
				glTranslatef(-250,-250,500);
				glRotatef(-90, 1.0f, 0.0f, 0.0f);
				//���end
				
				//��L���ystart
				glColor3ub(128, 64, 64);
					//drawCir(Grinder_R+300, Grinder_L+50, 1000);
				drawCir(500, Grinder_L+50, 1000);
				//��L���yend
				//�������ustart
				glPushMatrix();
				{
					
					//�x�s��L���y���b�|�P�p��,/2����]�O�]�n�ϨC�Ӥ���K�X���ޥ�
						//Cir_R=(Grinder_R+300)/2;
					Cir_R=500/2;
					Cir_L=(Grinder_L+50)/2;
					
					///////////////////////////////////////////////////////
					
					//X�bstart
					//�]�wX�b������,�e��,����
					x_w=140;//y
					x_l=400;//x
					x_h=40;//z
					//�]�wX�b�w�˦�mx=0,y=250,z=��L�p�ת��@�b�[�WX�b�p�ת��@�b
					glTranslatef(0.0f, 250.0f,+Cir_L+x_h/2);
					//�]�wX�b�C��
					glColor3ub(200, 128, 128);
					//�e�XX�b
					drawRetc(x_w, x_l, x_h);
					//X�bend

					//////////////////////////////////////////////////////////
					
					//y�bstart	
					//�w��y�b��h=62,w=96,l=201
					//�]�wy�b�w�˦�mx=X�b�������I,y=(-X�b��y�b�@�b)(ps�]���n������I,�ҥH���t��)�[�W(y�b��y�b�@�b),z=(y�b�p�ת��@�b)�[�W(X�b�p�ת��@�b)
					//�b�o�̥u�n��y�b�[�W�@�ӥ��ƴN�i�H�F��䲾�ʤ��ĪG
					y_h=62;//z
					y_w=201;//x
					y_l=96;//y
					glTranslatef(0, x_l/-2+y_l/2 ,(x_h/2+y_h/2));
					glTranslatef(0,y_base,0);
					//�]�wy�b�C��
					glColor3ub(0, 128, 128);
					//�e�XY�b
					drawRetc(y_w, y_l, y_h);
					//y�bend

					//////////////////////////////////////////////////////////
					//z�bstart
					glTranslatef(-y_l/2, 0 ,y_h/2+96/8);
					/////////////////////////////////////////////////////////
					//servomoter start
					//base start
					glColor3ub(200, 128, 128);
					drawRetc(96, 96, 24);
					//base end
					//body start
					glTranslatef(0.0f, 0.0f, SM1_Bottom_H/2+SM1_Middle_L/2);
					glColor3ub(96, 128, 96);
					drawCir(43, 96, 16);
					//body end
					//head1 start
					glTranslatef(0.0f, 0.0f, 96/2+SM1_Top_L/2);
					glColor3ub(96, 128, 200);
					drawCir(30,20,16);
					//head1 end
					//head2 start
					glTranslatef(0.0f, 0.0f, 20/2+10/2);
					glColor3ub(96, 128, 0);
					drawCir(50,10,16);
					//head2 end
					//servomoter end
					////////////////////////////////////////////////////////
					//��t�� start
					glTranslatef(y_l/2, 0 ,(y_h/2+96/8)*-1);//���^y�b����
					glTranslatef(y_l/2, 0 ,(y_h/2+20/2)*-2);//����y�b�k��
					glRotatef(90, 0.0f, 1.0f, 0.0f);
					glColor3ub(200, 0, 128);
					drawRetc(30, 76, 76);

					glTranslatef((30/2+50/2)*-1, 0 ,0);//����y�b�k��
					glColor3ub(5, 5, 128);
					drawRetc(50, 60, 60);

					glTranslatef((50/2+50/2)*-1, 0 ,0);//����y�b�k��
					glColor3ub(200, 128,0 );
					drawRetc(50, 76, 76);
					//��t�� end
					//////////////////////////////////////////////////////
					//�D���uy�b
					glRotatef(-90, 0.0f, 1.0f, 0.0f);
					glTranslatef(-40, 0 ,(50/2+90/2));//����y�b�k��
					glColor3ub(200, 0,0 );
					drawRetc(210, 90, 54);
					//////////////////////////////////////////////////////
					//�s���D���u�s��1(�p��W)
					glTranslatef((210/2+30/2), 0 ,0);//����y�b�k��
					glRotatef(-90, 0.0f, 1.0f, 0.0f);
					glColor3ub(200,50,150 );
					drawCir(25,30,16);
					//////////////////////////////////////////////////////
					//�s���D���u�s��2(�j��L)
					glTranslatef(0, 0 ,(30/2+20/2)*-1);//����y�b�k��
					glColor3ub(200,150,50 );
					drawCir(30,20,16);
					/////////////////////////////////////////////////////
					//�D���uX�b
					glRotatef(-90+x_main_hand, 0.0f, 0.0f, 1.0f);//�ק�z�b���״N�i�H����
					glTranslatef(0, 0 ,(60/2+20/2)*-1);//����y�b�k��
					glColor3ub(100,150,50 );
					drawRetc(124, 60, 60);
					////////////////////////////////////////////////////
					//�P���� start
					glTranslatef((124/2+14.75/2)*-1, 0 ,0);
					glRotatef(-90, 0.0f, 1.0f, 0.0f);
					glRotatef(senser_Rotate, 0.0f, 0.0f, 1.0f);
					
					glColor3ub(200,50,150 );
					drawCir(10,14.75,16);
					
					glTranslatef(0, 0 ,(5/2+14.75/2));
					glColor3ub(50,0,255 );
					drawCir(32,5,16);
					
					glRotatef(90, 0.0f, 1.0f, 0.0f);
					glTranslatef((30/2+14.8/2)*-1, 0 ,0);
					
					glColor3ub(128,25,25 );
					drawRetc(30, 26, 20);

					////////////////////////////////////////////////
					//load ceal start
						glTranslatef(15, 0 ,0);//����y�b�k��
						glColor3ub(128,250,25 );
						drawRetc(15, 60, 10);//�e,��,�p��//20

						glTranslatef((5/2+15/2)*-1, (30-20/2) ,0);
						drawRetc(5, 20, 10);//�e,��,�p��

						glTranslatef((24.5/2+5/2)*-1, (60/2-20/2)*-1 ,0);
						drawRetc(24.5, 60, 10);//�e,��,�p��

						glTranslatef((5/2+24.5/2)*-1, (60/2-20/2)*-1,0);
						drawRetc(5, 20, 10);//�e,��,�p��
						glTranslatef((15/2)*-1, (60/2-20/2),0);
						glColor3ub(128,250,25 );
						drawRetc(15, 60, 10);//�e,��,�p��
					//load ceal end
					////////////////////////////////////////////////
						
						glTranslatef(0, 0,0);
						glColor3ub(128,25,25 );
						drawRetc(21, 40, 20);
						
						glTranslatef((5/2+21/2)*-1, 0,0);
						glRotatef(-90, 0.0f, 1.0f, 0.0f);
						glColor3ub(50,0,255 );
						drawCir(32,5,16);
					////////////////////////////////////////////
						//����start
						glTranslatef(0,0,(5/2+6/2)*1);
						//glRotatef(-90, 0.0f, 1.0f, 0.0f);
						glColor3ub(50,0,25 );
						drawCir(25,6,16);
						glTranslatef(0,0,(5/2+31.1/2)*1);
						//glRotatef(-90, 0.0f, 1.0f, 0.0f);
						glColor3ub(50,255,25 );
						drawCir(21,31.1,16);
						//����end
					///////////////////////////////////////////
						//���start
						glTranslatef(15,0,(8/2+31.5/2));//����
						glColor3ub(255,255,255 );
						drawRetc(10, 50, 8);
						glTranslatef(-15*2,0,0);//�k��
						drawRetc(10, 50, 8);
						glTranslatef(15,15,0);//�W��
						glRotatef(-90, 0.0f, 0.0f, 1.0f);
						drawRetc(10, 40, 8);
						glTranslatef(15*2,0,0);//�U��
						drawRetc(10, 40, 8);
						//���end
					////////////////////////////////////////

						
				}
				glPopMatrix();

				//�������uend
				//glRotatef(90, 0.0f, 1.0f, 0.0f);
			}
			glPopMatrix();
			//���Ҿ�end
}
void CKk1View::opengl_ServoMotor(void)
{
		glPushMatrix();
		{
		glTranslatef(0, 1400, 0);
		yRot=-90;//�]���D�e��������@�Ө���,�ҥH�n���v
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
				// opengl_ServoMotor 1
			glPushMatrix();
			{
				
				glTranslatef(-Y_axis_W/2-SM1_Bottom_W/2, 0.0f, -Link11_H/2+SM1_Bottom_H/2);
				glColor3ub(200, 128, 128);
				drawRetc(SM1_Bottom_W, SM1_Bottom_L, SM1_Bottom_H);

				glTranslatef(0.0f, 0.0f, SM1_Bottom_H/2+SM1_Middle_L/2);
				glColor3ub(96, 128, 96);
				drawCir(SM1_Middle_R, SM1_Middle_L, 16);

				glTranslatef(0.0f, 0.0f, SM1_Middle_L/2+SM1_Top_L/2);
				glColor3ub(96, 128, 200);
				drawCir(SM1_Top_R, SM1_Top_L, 16);

				

			}
			glPopMatrix();
		}
		glPopMatrix();
			// Servo Motor 1(End)

}
void CKk1View::robot(void)
{
		glPushMatrix();
		{	
			// X�b
			// ��
			glTranslatef(-Base_W/2+X_axis_W/2, -Base_L/2+X_axis_L/2, Base_H/2+X_axis_H/2);
			glColor3ub(128, 128, 200);
			drawRetc(X_axis_W, X_axis_L, X_axis_H);
			// �k
			glTranslatef(0.0f, -X_axis_L/2+2*Base_L/2-X_axis_L/2, 0.0f);
			glColor3ub(128, 128, 200);
			drawRetc(X_axis_W, X_axis_L, X_axis_H);
			// X�b(��)
			
			// Y�b
			glTranslatef(-X_axis_W/2+Y_axis_W/2+X_shift, X_axis_L/2-Y_axis_L/2, X_axis_H/2+Y_axis_H/2);
			glTranslatef(X_shift, 0.0f, 0.0f);			// X_shift Parameter
			glColor3ub(128, 128, 200);
			drawRetc(Y_axis_W, Y_axis_L, Y_axis_H);
			// Y�b(��)
			
			// Link1-1
			glTranslatef(0.0f, -Y_axis_L/2+Link11_L/2+Y_shift, Y_axis_H/2+Link11_H/2);
			glTranslatef(0.0f, Y_shift, 0.0f);			// Y_shift Parameter
			glColor3ub(128, 128, 200);
			drawRetc(Link11_W, Link11_L, Link11_H);
			// Link1-1(End)

			// Servo Motor 1
			glPushMatrix();
			{
				glTranslatef(-Y_axis_W/2-SM1_Bottom_W/2, 0.0f, -Link11_H/2+SM1_Bottom_H/2);
				glColor3ub(200, 128, 128);
				drawRetc(SM1_Bottom_W, SM1_Bottom_L, SM1_Bottom_H);

				glTranslatef(0.0f, 0.0f, SM1_Bottom_H/2+SM1_Middle_L/2);
				glColor3ub(96, 128, 96);
				drawCir(SM1_Middle_R, SM1_Middle_L, 16);

				glTranslatef(0.0f, 0.0f, SM1_Middle_L/2+SM1_Top_L/2);
				glColor3ub(96, 128, 200);
				drawCir(SM1_Top_R, SM1_Top_L, 16);

			}
			glPopMatrix();
			// Servo Motor 1(End)
			
			// Bar1-1
			glTranslatef(0.0f, 0.0f, Link11_H/2+Bar11_L/2);
			glRotatef(Rotate1, 0.0f, 0.0f, 1.0f);		// Rotate1 Parameter
			glColor3ub(128, 30, 56);
			drawCir(Bar11_R, Bar11_L, 16);
			// Bar1-1(End)
			
			// Link1-2
			glTranslatef(0.0f, 0.0f, Bar11_L/2+Link12_H/2);
			glColor3ub(200, 100, 200);
			drawRetc(Link12_W, Link12_L, Link12_H);
			// Link1-2(End)
			
			// Bar1-2
			glTranslatef(0.0f, -Link12_L/2-Bar12_L/2, 0.0f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(Rotate2, 0.0, 0.0f, 1.0f);		// Rotate2 Parameter
			glColor3ub(98, 16, 200);
			drawCir(Bar12_R, Bar12_L, 16);
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			// Bar1-2(End)

			// Link2
			glTranslatef(Link2_W/2, -Bar12_L/2+Link2_L/2-0.1f, 0.0f);
			glColor3ub(128, 128, 200);
			drawRetc(Link2_W, Link2_L, Link2_H);
			// Link2(��)

			// Loadcell
			glTranslatef(Link2_W/2+Loadcell1_L/2, 0.0f, 0.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(Rotate3, 0.0f, 0.0f, 1.0f);		// Rotate3 Parameter
			glColor3ub(128, 64, 64);
			drawCir(Loadcell1_R, Loadcell1_L, 16);
			glTranslatef(0.0f, 0.0f, Loadcell1_L/2+Loadcell2_L/2);
			glColor3ub(156, 64, 64);
			drawCir(Loadcell2_R, Loadcell2_L, 16);
			// Loadcell(��)
			
			// Fixture
			glTranslatef(0.0f, 0.0f, Loadcell2_L/2+Fixture1_L/2);
			glColor3ub(128, 128, 128);
			drawCir(Fixture1_R, Fixture1_L, 16);
			glTranslatef(0.0f, 0.0f, Fixture1_L/2+Fixture2_L/2);
			glColor3ub(128, 128, 128);
			drawCir(Fixture2_R, Fixture2_L, 16);
			// Fixture(��)

			glTranslatef(0.0f, 0.0f, Fixture2_L/2+Watch1_1_H/2);
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
///*�R����ذ_�l��m
			// Watch Model
			// Watch1_1 ��
			glPushMatrix();
			{
				glTranslatef(Watch1_2_W/2+Watch1_1_W/2,0.0f,  0.0f);
				glColor3ub(96, 96, 96);
				drawRetc(Watch1_1_W, Watch1_1_L, Watch1_1_H);
			}	
			glPopMatrix();
			// Watch1_1 ��(End)
			// Watch1_1 �k
			glPushMatrix();
			{
				glTranslatef(-(Watch1_2_W/2+Watch1_1_W/2), 0.0f, 0.0f);
				glColor3ub(96, 96, 96);
				drawRetc(Watch1_1_W, Watch1_1_L, Watch1_1_H);
			}	
			glPopMatrix();
			// Watch1_1 �k(End)
			// Watch1_2 �W
			glPushMatrix();
			{
				glTranslatef(0.0f, Watch1_1_L/2-Watch1_2_L/2, 0.0f);
				glColor3ub(96, 96, 96);
				drawRetc(Watch1_2_W, Watch1_2_L, Watch1_2_H);
			}
			glPopMatrix();
			// Watch1_2 �W(End)
			// Watch1_2 �U
			glPushMatrix();
			{
				glTranslatef( 0.0f, -(Watch1_1_L/2-Watch1_2_L/2),0.0f);
				glColor3ub(96, 96, 96);
				drawRetc(Watch1_2_W, Watch1_2_L, Watch1_2_H);
			}
			glPopMatrix();
			// Watch1_2 �U(End)
			// Watch Model(End)
//*/�R����ص�����m	
		}
		glPopMatrix();
}
void CKk1View::opengl_final(void)
{
	int base_h=50,base_l1=400,base_w1=500/*400*/,base_l2=200,base_w2=300;
	int base_triangle=100;
	int base_watch_h1=200,base_watch_w1=200,base_watch_l1=250;
	int x,y,iPivot;
	int track_h=20,track_w=20,track_l=400;//��y���y�D
	int track_h1=10,track_w1=20,track_l1=200;///�ƭy
	int platform_w1=500,platform_l1=200,platform_h1=32;///���x1
	int track_h2=10,track_w2=20,track_l2=500;//�ƭy2
	int platform_w2=200,platform_l2=200,platform_h2=32;////���x2
	int base_vertical_h2=50,base_vertical_w2=500,base_vertical_l2=200;//�������y
	int track_vertical_h=10,track_vertical_w=500,track_vertical_l=20;//�������y�ƭy
	int track_vertical_h1=32,track_vertical_w1=200,track_vertical_l1=200;//�����ƭy�W�����ʥ��x
	int base_emery_w1=100,base_emery_l1=150,base_emery_h1=20,base_emery_w2=150,base_emery_l2=60,base_emery_h2=20;//�F�������O
	//////////////////////////////////////////////////////////////////���A���F
	int ServoMotor_Cir1=43,ServoMotor_Cir2=20,ServoMotor_Cir3=16;
	int ServoMotor_Retc11=66,ServoMotor_Retc12=66,ServoMotor_Retc13=50;
	int ServoMotor_Retc21=68,ServoMotor_Retc22=68,ServoMotor_Retc23=40;
	//////////////////////////////////////////////////////////////////
	int emery_triangle1=154,emery_triangle2=41,emery_triangle3=20;
	float angle;
	glPushMatrix();//1-1
	{
		glTranslatef(0,-200,0);//�Ͼ�Ӿ��c�V�U����,�H�K�[��
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);//����
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);//����
		glRotatef(zRot, 0.0f, 0.0f, 1.0f);//����
		/////////////////////////////////////////////////////////////////////////
		glRotatef(jx, 1.0f, 0.0f, 0.0f);
		glRotatef(jy, 0.0f, 1.0f, 0.0f);
		glRotatef(jz, 0.0f, 0.0f, 1.0f);
		//////////////////////////////////////////////////////////////////////////
		glPushMatrix();//3-1
		{
			glColor3ub(96, 96, 96);
			///////////////////////////////////////////////
			drawRetc(base_w1, base_l1, base_h);//���y1
			///////////////////////////////////////////////
			glPushMatrix();//7-1//��y���y�D//track_h=20,track_w=20,track_l=400;
			{
				/////////////���϶������Ʀr,�����O�ۥѤߥ��w�X�Ӫ�
				glTranslatef((base_w1-300),0,base_h/2+track_h/2);
				glColor3ub(0, 96, 0);
				drawRetc(track_w,track_l,track_h);//1
				glTranslatef(-150,0,0);
				drawRetc(track_w,track_l,track_h);//3
				glTranslatef(50,0,0);
				drawRetc(track_w,track_l,track_h);//2
				glTranslatef(-150,0,0);
				drawRetc(track_w,track_l,track_h);//4
			}
			glPopMatrix();//7-2
			glPushMatrix();//8-1�D��
			{
				//�ƭy+���x1+���F
				glTranslatef((base_w1-280),0,base_h/2+20+10/2);
				glColor3ub(8, 96, 80);
				////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////���F
				//////////int ServoMotor_Cir1=43,ServoMotor_Cir2=20,ServoMotor_Cir3=16;
				//////////int ServoMotor_Retc11=66,ServoMotor_Retc12=66,ServoMotor_Retc13=50;
				//////////int ServoMotor_Retc21=68,ServoMotor_Retc22=68,ServoMotor_Retc23=40;
				glRotatef(90,1.0f,0.0f,0.0f);
				glTranslatef(-140,-32,base_l1/2+ServoMotor_Cir2/2);
				drawCir(ServoMotor_Cir1, ServoMotor_Cir2, ServoMotor_Cir3);
				glTranslatef(0,0,ServoMotor_Cir2/2+ServoMotor_Retc13/2);
				drawRetc(ServoMotor_Retc11,ServoMotor_Retc12,ServoMotor_Retc13);
				glTranslatef(0,0,ServoMotor_Retc13/2+ServoMotor_Retc23/2);
				drawRetc(ServoMotor_Retc21,ServoMotor_Retc22,ServoMotor_Retc23);
				/////////////////////////////////////////////////////////////////////////
				////////////////�ƭy//track_h1=10,track_w1=20,track_l1=200;
				glTranslatef(0,0,210);////�̪�w��
				glTranslatef(0,0,-life_x);//�ᤩ�ͩR---------------1
				glTranslatef(165,0,0);
				glRotatef(-90,1.0f,0.0f,0.0f);
				glTranslatef(-26,400,20+10);
				drawRetc(track_w1,track_l1,track_h1);//1
				glTranslatef(-290,0,0);
				drawRetc(track_w1,track_l1,track_h1);//2
				////////////////////////////////////platform_w1=500,platform_l1=200,platform_h1=32///���x1
				glTranslatef(120,0,track_h1/2+platform_h1/2);
				drawRetc(platform_w1,platform_l1,platform_h1);
				//////////////////////////////////////
				glPushMatrix();//9-1�]����ɥ��e�ƭy2�Υ��x2�ҥH�n�[���|
				{
					/////////////////���F
					//////////int ServoMotor_Cir1=43,ServoMotor_Cir2=20,ServoMotor_Cir3=16;
					//////////int ServoMotor_Retc11=66,ServoMotor_Retc12=66,ServoMotor_Retc13=50;
					//////////int ServoMotor_Retc21=68,ServoMotor_Retc22=68,ServoMotor_Retc23=40;
					glTranslatef(0,140,43);//�Ѭ��[�M�w
					glRotatef(90,1.0f,0.0f,0.0f);
					glRotatef(90,0.0f,1.0f,0.0f);
					glTranslatef(-140,-32,platform_w1/2+ServoMotor_Cir2/2);
					drawCir(ServoMotor_Cir1, ServoMotor_Cir2, ServoMotor_Cir3);
					glTranslatef(0,0,ServoMotor_Cir2/2+ServoMotor_Retc13/2);
					drawRetc(ServoMotor_Retc11,ServoMotor_Retc12,ServoMotor_Retc13);
					glTranslatef(0,0,ServoMotor_Retc13/2+ServoMotor_Retc23/2);
					drawRetc(ServoMotor_Retc21,ServoMotor_Retc22,ServoMotor_Retc23);
				}
				glPopMatrix();//9-2
				////////////////////////////////////track_h2=10,track_w2=20,track_l2=500;//�ƭy2
				glRotatef(90,0.0f,0.0f,1.0f);
				glTranslatef(60,0,platform_h1/2+track_h2/2);
				glColor3ub(0, 96, 0);
				drawRetc(track_w2,track_l2,track_h2);//1
				glTranslatef(-40,0,0);
				drawRetc(track_w2,track_l2,track_h2);//2
				glTranslatef(-40,0,0);
				drawRetc(track_w2,track_l2,track_h2);//3
				glTranslatef(-40,0,0);
				drawRetc(track_w2,track_l2,track_h2);//4
				////////////////////////////////////////////////platform_w2=200,platform_l2=200,platform_h2=32;////���x2
				glTranslatef(0,-150,0);//�̪�w��
				glTranslatef(0,life_y,0);//�ᤩ�ͩR---------------2
				glTranslatef(60,0,track_h2/2+platform_h2/2);
				glColor3ub(0, 0, 90);
				drawRetc(platform_w2,platform_l2,platform_h2);//1
				//////////////////////////////////////////////////////base_vertical_h2=50,base_vertical_w2=500,base_vertical_l2=200//�������y
				glRotatef(90,0.0f,1.0f,0.0f);
				glTranslatef(base_vertical_w2/-2+platform_h2/-2,0,platform_w2/2-base_vertical_h2/2);
				glColor3ub(0, 50, 100);
				drawRetc(base_vertical_w2,base_vertical_l2,base_vertical_h2);//1
				//////////////////////////////////////////////�������y���F
				glPushMatrix();//10-1
				{
					//////////int ServoMotor_Cir1=43,ServoMotor_Cir2=20,ServoMotor_Cir3=16;
					//////////int ServoMotor_Retc11=66,ServoMotor_Retc12=66,ServoMotor_Retc13=50;
					//////////int ServoMotor_Retc21=68,ServoMotor_Retc22=68,ServoMotor_Retc23=40;
					glTranslatef(base_vertical_w2/-2+ServoMotor_Cir2/-2,0,0);
					glRotatef(-90,0.0f,1.0f,.0f);
					drawCir(ServoMotor_Cir1, ServoMotor_Cir2, ServoMotor_Cir3);
					glTranslatef(0,0,ServoMotor_Cir2/2+ServoMotor_Retc13/2);
					drawRetc(ServoMotor_Retc11,ServoMotor_Retc12,ServoMotor_Retc13);
					glTranslatef(0,0,ServoMotor_Retc13/2+ServoMotor_Retc23/2);
					drawRetc(ServoMotor_Retc21,ServoMotor_Retc22,ServoMotor_Retc23);
				}
				glPopMatrix();//10-2
				//////////////////track_vertical_h=10,track_vertical_w=500,track_vertical_l=20;//�������y�ƭy
				glTranslatef(0,0,(base_vertical_h2/2+track_vertical_h/2)*-1);
				glColor3ub(0, 96, 0);
				glTranslatef(0,20,0);
				drawRetc(track_vertical_w,track_vertical_l,track_vertical_h);//1
				glTranslatef(0,-40,0);
				drawRetc(track_vertical_w,track_vertical_l,track_vertical_h);//1
				glTranslatef(0,-70,0);
				drawRetc(track_vertical_w,track_vertical_l,track_vertical_h);//2
				glTranslatef(0,180,0);
				drawRetc(track_vertical_w,track_vertical_l,track_vertical_h);//2
				/////////////////////////////////track_vertical_h1=32,track_vertical_w1=200,track_vertical_l1=200//�����ƭy�W�����ʥ��x
				glTranslatef(-150,0,0);//�̪�w��
				glTranslatef(life_z,0,0);//�ᤩ�ͩR---------------3
				glTranslatef(0,-90,0);
				glTranslatef(0,0,(track_vertical_h/2+32/2)*-1);
				glColor3ub(0, 50, 80);
				drawRetc(track_vertical_w1,track_vertical_l1,track_vertical_h1);
				/////////////////////////////////base_emery_w1=100,base_emery_l1=150,base_emery_h1=20,base_emery_w2=150,base_emery_l2=60,base_emery_h2=20//�F�������O
				glTranslatef(0,(track_vertical_l1-base_emery_l1)/2,(track_vertical_h1/2+base_emery_h1/2)*-1);
				glColor3ub(50, 30, 40);
				drawRetc(base_emery_w1,base_emery_l1,base_emery_h1);
				glRotatef(90,0.0f,0.0f,1.0f);
				glTranslatef(base_emery_l1/2+base_emery_w2/2,0,0);
				drawRetc(base_emery_w2,base_emery_l2,base_emery_h2);
				///////////////////////////////////////////////////
				//int emery_triangle1=154,emery_triangle2=41,emery_triangle3=20;
				glPushMatrix();//11-1//�F�������O�T����
				{
				glTranslatef(-2,20,0);
				glRotatef(-8,0.0f,0.0f,1.0f);
				drawRetc(emery_triangle1,emery_triangle2,emery_triangle3);
				}
				glPopMatrix();//11-2
				//////////////////////////////////////////////////
				glPushMatrix();//12-1//�F�������O�T����
				{
				glTranslatef(-2,-20,0);
				glRotatef(8,0.0f,0.0f,1.0f);
				drawRetc(emery_triangle1,emery_triangle2,emery_triangle3);
				}
				glPopMatrix();//12-2
				
				//////////////////////////////////////////////�F���ΰ��F
				glPushMatrix();//13-1
				{
					//////////int ServoMotor_Cir1=43,ServoMotor_Cir2=20,ServoMotor_Cir3=16;
					//////////int ServoMotor_Retc11=66,ServoMotor_Retc12=66,ServoMotor_Retc13=50;
					//////////int ServoMotor_Retc21=68,ServoMotor_Retc22=68,ServoMotor_Retc23=40;
					glTranslatef(25,0,emery_triangle3/2+ServoMotor_Cir2/2);
					glColor3ub(0, 50, 100);
					drawCir(ServoMotor_Cir1, ServoMotor_Cir2, ServoMotor_Cir3);
					glTranslatef(0,0,ServoMotor_Cir2/2+ServoMotor_Retc13/2);
					drawRetc(ServoMotor_Retc11,ServoMotor_Retc12,ServoMotor_Retc13);
					glTranslatef(0,0,ServoMotor_Retc13/2+ServoMotor_Retc23/2);
					drawRetc(ServoMotor_Retc21,ServoMotor_Retc22,ServoMotor_Retc23);
				}
				glPopMatrix();//13-2

				/////////////////////////////////////////////////////�F�i��start
				
				glPushMatrix();//14-1
				{
					
					glTranslatef(150/2-45,0,(emery_triangle3/2+10/2)*-1);
					drawCir(15, 10, 16);//�s��
					//glRotatef(-90,0.0f,0.0f,1.0f);
					glRotatef(-life_r,0.0f,0.0f,1.0f);//�ᤩ�ͩR---------------4
					////////////////////////////////////////�F�i���D��start
					glTranslatef(0,0,(10/2+60/2)*-1);
					drawRetc(60,60,60);
					glRotatef(90,0.0f,1.0f,0.0f);
					glTranslatef(0,0,60/2+55.36/2);
					drawCir(25, 55.36, 16);
					///////////////////////////////////////////////////
					glTranslatef(0,0,55.36/2);
					if(Line_Side!=false)
					{
						glBegin(GL_LINES);
						{
							for(angle = 0.0f; angle < (2.0f*GL_PI); angle+=((2.0f*GL_PI)/16))
							{						
								glVertex3f(0.0f, 0.0f, 34.64f);
								x = 25.0f*sin(angle);
								y = 25.0f*cos(angle);
								glVertex2f(x, y);
							}
						}
						glEnd();
					}
					else
					{
					glBegin(GL_TRIANGLE_FAN);//�T���@���D��
					{
						glVertex3f(0.0f, 0.0f, 34.64f);
						for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
						{
							x = 25.0f*sin(angle);
							y = 25.0f*cos(angle);
							glVertex2f(x, y);
						}
					}
					glEnd();
					}
					////////////////////////////////////////�F�i���D��end
					////////////////////////////////////////////////////////���i��1
					glTranslatef(0,0,34.64f);
					drawCir(2.5, 20, 16);
					//////////////////////////////////////////////////////���i��2
					glTranslatef(0,0,20/2+20/2);
					drawCir(5, 20, 16);

				}
				glPopMatrix();//14-2
				
			/////////////////////////////////////////////////////////////////�F�i��end
			}
			glPopMatrix();//8-2
			glTranslatef( -base_w1/2-base_l2/2,base_l1/-2+base_w2/2 ,0.0f);
			glColor3ub(96, 96, 96);
			/////�p�����y//base_l2=200,base_w2=300;,base_h=50
			drawRetc(base_l2,base_w2 , base_h);
			glTranslatef(0,20,0);///�ѩ�W�w���㩳�y�����Z��30mm,�ҥH50-30=20,�䤤50���\��b�������ɪ��Z�����䪺�Z��
			glPushMatrix();//4-1���㩳�y
			{
				////////////int base_watch_h1=200,base_watch_w1=200,base_watch_l1=250;
				glTranslatef(((base_l2/-2)+(base_watch_l1/2)),0,(base_h/2+base_watch_h1/2));
				glColor3ub(96, 96, 80);
				drawRetc(base_watch_l1, base_watch_w1, base_watch_h1);
				glPushMatrix();//5-1//��ا���
				{
				////////////int base_watch_h1=200,base_watch_w1=200,base_watch_l1=250;
				glTranslatef((base_watch_l1/2-74),(base_watch_w1/2-74)*-1,(base_watch_h1/2+10/2));
				glColor3ub(96, 96, 30);
				drawCir(50, 10, 16);
				////////////////////////////////////////
				glTranslatef(0,0,(10+20)/2);
				glColor3ub(50, 96, 30);
				drawCir(43, 20, 16);
				////////////////////////////////////////
				glTranslatef(0,0,(20+5)/2);
				glColor3ub(50, 40, 30);
				drawCir(40, 5, 16);
				////////////////////////////////////////
				glTranslatef(0,0,(5+15)/2);
				glColor3ub(50, 96, 30);
				drawCir(43, 15, 16);
				////////////////////////////////////////
				glTranslatef(0,0,(15+6)/2);
				glColor3ub(60, 96, 70);
				drawCir(30, 6, 16);
				/////////////////////////////////////////
				glTranslatef(0,0,(6+30)/2);
				glColor3ub(60, 20, 70);
				drawCir(25, 30, 16);
				}
				glPopMatrix();//5-2
			}
			glPopMatrix();//4-2
			glPushMatrix();//6-1//��ا��㰨�F
			{
			
				//////////int ServoMotor_Cir1=43,ServoMotor_Cir2=20,ServoMotor_Cir3=16;
				//////////int ServoMotor_Retc11=66,ServoMotor_Retc12=66,ServoMotor_Retc13=50;
				//////////int ServoMotor_Retc21=68,ServoMotor_Retc22=68,ServoMotor_Retc23=40;
				glTranslatef((base_watch_l1/-2+50*3),(base_watch_w1/2+15/2),base_watch_h1-50/2);
				glRotatef(90, 1.0f, 0.0f, 0.0f);
				glColor3ub(96, 58, 80);
				drawCir(ServoMotor_Cir1, ServoMotor_Cir2, ServoMotor_Cir3);
				glTranslatef(0,0,(ServoMotor_Cir2/2+ServoMotor_Retc13/2)*-1);
				drawRetc(ServoMotor_Retc11,ServoMotor_Retc12,ServoMotor_Retc13);
				glTranslatef(0,0,(ServoMotor_Retc13/2+ServoMotor_Retc23/2)*-1);
				drawRetc(ServoMotor_Retc21,ServoMotor_Retc22,ServoMotor_Retc23);

			}
			glPopMatrix();//6-2
		}
		glPopMatrix();//3-2
	}
	glPopMatrix();//1-2
}

BOOL CKk1View::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class


	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CKk1View::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	char ch0[100],ch1[100],ch2[100],ch3[100],ch4[100],ch5[100];
	//int d1,s;
	double a,b,c,d,e,f;
	/////////////////////////////////////////////////////////////
	char *ch6,*ch7,*ch8,*ch9;
	int d1,s;
	LPVOID mapView6,mapView7,mapView8,mapView9;
	mapView6 = MapViewOfFile( hFileMap6,FILE_MAP_WRITE, 0, 0, 0 );
	mapView7 = MapViewOfFile( hFileMap7,FILE_MAP_WRITE, 0, 0, 0 );
	mapView8 = MapViewOfFile( hFileMap8,FILE_MAP_WRITE, 0, 0, 0 );
	mapView9 = MapViewOfFile( hFileMap9,FILE_MAP_WRITE, 0, 0, 0 );
	switch(work_number)
	{
	case 1:
		LPVOID mapView0,mapView1,mapView2,mapView3,mapView4,mapView5;
		mapView0 = MapViewOfFile( hFileMap0,FILE_MAP_WRITE, 0, 0, 0 );
		mapView1 = MapViewOfFile( hFileMap1,FILE_MAP_WRITE, 0, 0, 0 );
		mapView2 = MapViewOfFile( hFileMap2,FILE_MAP_WRITE, 0, 0, 0 );
		mapView3 = MapViewOfFile( hFileMap3,FILE_MAP_WRITE, 0, 0, 0 );
		mapView4 = MapViewOfFile( hFileMap4,FILE_MAP_WRITE, 0, 0, 0 );
		mapView5 = MapViewOfFile( hFileMap5,FILE_MAP_WRITE, 0, 0, 0 );	
		if(mapView0 !=NULL)
		{
			strcpy(ch0,(LPTSTR)mapView0);
			strcpy(ch1,(LPTSTR)mapView1);
			strcpy(ch2,(LPTSTR)mapView2);
			strcpy(ch3,(LPTSTR)mapView3);
			strcpy(ch4,(LPTSTR)mapView4);
			strcpy(ch5,(LPTSTR)mapView5);
			a=(atof(ch0)/10000);
			b=(atof(ch1)/10000);
			c=(atof(ch2)/10000);
			d=(atof(ch3)/10000);
			e=(atof(ch4)/10000);
			f=(atof(ch5)/10000);
			Theta=a;
			PDX=b;
			PDY=c;
			PAX=d;
			PAY=e;
			DeltaT=f;
			fprintf(k1,"%f\t%f\t%f\t%f\t%f\t%f\n",a,b,c,d,e,f);
		}
		break;
	case 2:
		switch(next_number)
		{
			case 0:
				if(life_x<=71.9994 && life_y<=105.75 &&life_z<=191.542)
				{
					life_x+=71.9994/300;
					life_y+=105.75/300;
					life_z+=191.542/300;
				}
				else
				{
					next_number++;
				}
				break;
			case 1:
				if(Theta_w0<=16.128)
				{
					Theta_w0+=(16.128-(-16.128))/500;
					life_x=(90*sin(Theta_w0*3.14/180)+X_toffset-X_offset);
					life_y=-14.25-a1-d4+Y_toffset-Y_offset;
					life_z=42-90*cos(Theta_w0*3.14/180)-Z_toffset+Z_offset;
				}
				else
				{
					next_number++;
				}
				break;
			case 2:
				if(Theta_w0>=-16.128)
				{
					Theta_w0-=(16.128-(-16.128))/500;
					life_x=(90*sin(Theta_w0*3.14/180)+X_toffset-X_offset);
					life_y=-14.25-a1-d4+Y_toffset-Y_offset;
					life_z=42-90*cos(Theta_w0*3.14/180)-Z_toffset+Z_offset;
				}
				else
				{
					next_number++;
				}
				break;
			case 3:
				if(life_x>0)
				{
					life_x-=71.9994/300;
				}
				if(life_y>0)
				{
					life_y-=105.75/300;
					life_z-=191.542/300;
				}
				if(life_x<=0.0f && life_y<=0.0f && life_z <=0.0f && life_r <=0.0f)
					next_number=0;
				break;
		}
		ch6=fcvt(life_x,4,&d1,&s);
		strcpy((LPTSTR)mapView6,ch6);
		ch7=fcvt(life_y,4,&d1,&s);
		strcpy((LPTSTR)mapView7,ch7);
		ch8=fcvt(life_z,4,&d1,&s);
		strcpy((LPTSTR)mapView8,ch8);
		ch9=fcvt((work_number-1),4,&d1,&s);
		strcpy((LPTSTR)mapView9,ch9);
		fprintf(l,"%c\t%c\t%c\t%c\n",ch6,ch7,ch8,ch9);
		UnmapViewOfFile( (LPVOID)mapView6);
		UnmapViewOfFile( (LPVOID)mapView7);
		UnmapViewOfFile( (LPVOID)mapView8);
		UnmapViewOfFile( (LPVOID)mapView9);
		Invalidate(true);
		break;

	case 3:
		switch(next_number)
		{
			case 0:
				if(life_x<=71.9999f)
					life_x+=71.9999f/300.0f;			
				if(life_y <= 249.0066f)
					life_y+=249.0066f/300.0f;
				if(life_z <= 48.0f)
					life_z+=48.0f/300.0f;
				if(life_r <= 90.0f)
					life_r+=90.0f/300.0f;
				if(life_x>=71.9999f && life_y>=249.0066f && life_z>=48.0f && life_r>= 90.0f)
				{
					next_number++;
				}
				break;
			case 1:
				if(Theta_w9<=18.21)
				{
					Theta_w9+=(18.21-(-18.21))/500;
					life_x=(80*sin(Theta_w9*3.14/180)+X_toffset-X_offset);
					life_y=55-a1-80*cos(Theta_w9*3.14/180)+Y_toffset-Y_offset;
					life_z=-38-d4-Z_toffset+Z_offset;
				}
				else
				{
					next_number++;
				}
				break;
			case 2:
				if(Theta_w9>=-18.21)
				{
					Theta_w9-=(18.21-(-18.21))/500;
					life_x=(80*sin(Theta_w9*3.14/180)+X_toffset-X_offset);
					life_y=55-a1-80*cos(Theta_w9*3.14/180)+Y_toffset-Y_offset;
					life_z=-38-d4-Z_toffset+Z_offset;
				}
				else
				{
					next_number++;
				}
				break;
			case 3:
				if(life_x>0.0f)
				{
					life_x-=71.9999f/300.0f;
				}
				if(life_y>0.0f)
				{
					life_y-=249.0066f/300.0f;
				}
				if(life_z>0.0f)
				{
					life_z-=48.0f/300.0f;
				}
				if(life_r>=0.0f)
				{
					life_r-=90.0f/300.0f;
				}
				if(life_x<=0.0f && life_y<=0.0f && life_z <=0.0f && life_r <=0.0f)
					next_number=0;
				break;
		}
		ch6=fcvt(life_x,4,&d1,&s);
		strcpy((LPTSTR)mapView6,ch6);
		ch7=fcvt(life_y,4,&d1,&s);
		strcpy((LPTSTR)mapView7,ch7);
		ch8=fcvt(life_z,4,&d1,&s);
		strcpy((LPTSTR)mapView8,ch8);
		ch9=fcvt((work_number-1),4,&d1,&s);
		strcpy((LPTSTR)mapView9,ch9);
		
		UnmapViewOfFile( (LPVOID)mapView6);
		UnmapViewOfFile( (LPVOID)mapView7);
		UnmapViewOfFile( (LPVOID)mapView8);
		UnmapViewOfFile( (LPVOID)mapView9);
		Invalidate(true);
		break;
	}
	CScrollView::OnTimer(nIDEvent);
}

void CKk1View::Onsettimer() 
{
	// TODO: Add your command handler code here
	///////////////////////////////////////////

	///////////////////////////////////////////
	k1=fopen("mapdata.txt","w");
	hFileMap0 = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME0 ) ;
	hFileMap1 = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME1 ) ;
	hFileMap2 = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME2 ) ;
	hFileMap3 = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME3 ) ;
	hFileMap4 = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME4 ) ;
	hFileMap5 = CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE, 0, MAP_LENGTH, MAP_NAME5 ) ;
	
	if(ontimer==false)
	{
		SetTimer(1,10,NULL);
		ontimer=true;
		work_number=1;
	}
	else
	{
		work_number=1;
	}
	
}

void CKk1View::OnDirectly()//���� 
{
	// TODO: Add your command handler code here
	///////////////////////////////////////////
	life_x=0;//�ᤩ���x�ͩR�ܼ�
	life_y=0;
	life_z=0;
	life_r=0;
	///////////////////////////////////////
	X_offset=48;
	Y_offset=100;
	Z_offset=554;
	X_toffset=145;
	Y_toffset=575;
	Z_toffset=318;
	a1=205;
	d4=150;
	Theta_w0=-16.128;
	Theta_w9=0;
	///////////////////////////////////////////

	if(ontimer==false)
	{
		SetTimer(1,10,NULL);
		ontimer=true;
		work_number=2;
		next_number=0;
	}
	else
	{
		work_number=2;
		next_number=0;
	}
	l=fopen("mapdata.txt","w");

}

void CKk1View::OnFlank()//���� 
{
	// TODO: Add your command handler code here
	///////////////////////////////////////////
	life_x=0;//�ᤩ���x�ͩR�ܼ�
	life_y=0;
	life_z=0;
	life_r=0;
	X_offset=48;
	Y_offset=100;
	Z_offset=554;
	X_toffset=145;
	Y_toffset=575;
	Z_toffset=318;
	a1=205;
	d4=150;
	Theta_w0=0;
	Theta_w9=-18.21;
	///////////////////////////////////////////
	if(ontimer==false)
	{
		SetTimer(1,10,NULL);
		ontimer=true;
		work_number=3;
		next_number=0;

	}
	else
	{
		work_number=3;
		next_number=0;

	}

}
