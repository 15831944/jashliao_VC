// NewView.cpp : implementation of the CNewView class
//

#include "stdafx.h"
#include "New.h"
//////////////////////////////////
#include "glmfc.h"
#include "OpenGLFun.h"
#include "OpenGLPara.h"
#include "NEWmodel.h"
#include <math.h>
/////////////////////////////////
#include "NewDoc.h"
#include "NewView.h"
#include <gl/glut.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///��������(2)
//#define d2r 3.14159267f/180.0f
/////////////////////////////////////////////////////////////////////////////
GLfloat Xmove, Ymove, Zmove;
GLfloat Theta1, Theta2;
GLfloat Pxr3, Pyr3, Pzr3;
GLfloat Px3, Py3, Pz3;
GLfloat Theta;
GLfloat Theta_Front, Theta_Flank;
GLfloat Xoffset, Yoffset, Zoffset;
GLfloat Xroffset, Yroffset, Zroffset;
GLfloat d2, dr1, dr2;
bool Front_Flag;
bool Flank_Flag;
bool Front1_Flag;
bool Flank1_Flag;
int Front_Index;
int Flank_Index;
int Front1_Index;
int Flank1_Index;
GLfloat d2r = 0.0174532f;
///��������(2)
////////////////////////////////////////////////////////���N�Ҧ���l�ȳ]���s
GLfloat shiftXValue=0.0f;
GLfloat shiftYValue=0.0f;
GLfloat shiftZValue=0.0f;
GLfloat WatchRotate=0.0f;
GLfloat WatchRotate1=0.0f;
int shiftX_switch=0;
int shiftY_switch=0;
int shiftZ_switch=0;
int Watch_switch=0;
int switch_value=0;
/////////////////////////////////////////////////////////////////////////////
bool Line_Flag=false;
bool View_Flag=true;
bool View_Flag1=true;
/////////////////////////////////////////////////////////////////////////////
GLfloat count;
// CNewView


IMPLEMENT_DYNCREATE(CNewView, CView)

BEGIN_MESSAGE_MAP(CNewView, CView)
	//{{AFX_MSG_MAP(CNewView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_shiftX, OnshiftX)
	ON_COMMAND(ID_shiftY, OnshiftY)
	ON_WM_TIMER()
	ON_COMMAND(ID_TimerStart, OnTimerStart)
	ON_COMMAND(ID_shiftZ, OnshiftZ)
	ON_COMMAND(ID_watch_R, OnwatchR)
	ON_COMMAND(ID_Flank, OnFlank)
	ON_COMMAND(ID_Front, OnFront)
	ON_COMMAND(ID_Bar, OnBar)
	ON_COMMAND(ID_Front1, OnFront1)
	ON_COMMAND(ID_Flank1, OnFlank1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewView construction/destruction

CNewView::CNewView()
{
	// TODO: add construction code here
	////////////////////////////////////////////////////////////�N��l�ȳ��]���s
	Xmove = 0.0f;
	Ymove = 0.0f;
	Zmove = 0.0f;
	Theta1 = 0.0f;
	Theta2 = 0.0f;
	Pxr3 = 0.0f;
	Pyr3 = 0.0f;
	Pzr3 = 0.0f;
	Px3 = 0.0f;
	Py3 = 0.0f;
	Pz3 = 0.0f;
	////////////////////////////////////////////////////////////���I�_�k�ɪ��Z��
	Xoffset = 467.15;//482.15f-15.0f;
	Yoffset = 222.85f;
	Zoffset = 568.5f;
	Xroffset = 150.0f;
	Yroffset = 145.0f;
	Zroffset = 390.0f;
	d2 = 130.0f;
	dr1 = 230.0f;
	dr2 = 19.0f;
	/////////////////////////////////////////////////////////////////////////////
	Front_Flag = false;
	Flank_Flag = false;
	Front1_Flag = false;
	Flank1_Flag = false;
	Front_Index = 0;//�j�����
	Flank_Index = 0;//�j�����
	Front1_Index = 0;//�j�����
	Flank1_Index = 0;//�j�����
	////////////////////////////////////////////////////////////////////////////
	count = 0.0f;

	///��������(3)
	
}

CNewView::~CNewView()
{
}

BOOL CNewView::PreCreateWindow(CREATESTRUCT& cs)//�]�wOpen GL
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;//open gl (1)
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNewView drawing

void CNewView::OnDraw(CDC* pDC)//ø�ϰ�
{
	int i,j,k;
	float x,y,z;
	m_pPal = NULL;
	CNewDoc* pDoc = GetDocument();
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
	// Save the matrix state
	if(Line_Flag)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�|���ͦh��Ϊ��~�����
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//�|���Ͷ񺡪��h���
	glPushMatrix();///�϶�13start
	{
		glTranslatef(0.0f,-200.0f,0.0f);
		glRotatef(view_x, 1.0f, 0.0f, 0.0f);//�������ਤ��
		glRotatef(view_y, 0.0f, 1.0f, 0.0f);//�������ਤ��
		glRotatef(view_z, 0.0f, 0.0f, 1.0f);//�������ਤ��
		glColor3ub(0.0f,0.0f,130.0f);
		///////////////////////////////////
		//�w�w100*100*100�A��10*10*10�զX
		glTranslatef(45.0,45.0f,45.0f);
		x=20.0f;
		y=20.0f;
		z=20.0f;
		for(k=0;k<10;k++)
		{
			for(j=0;j<10;j++)
			{
				for(i=0;i<10;i++)
				{
					drawRetc(20.0f,20.0f,20.0f);
					glTranslatef(x,0.0f,0.0f);
				}
				glTranslatef(-200.0f,y,0.0f);
			}
		glTranslatef(0.0f,-200.0f,z);
		}

		/*
		drawRetc(200.0f,400.0f,50.0f);
		//drawRetc(100.0f,100.0f,100.0f);
		glPushMatrix();///�϶�12start
		{
			glTranslatef(0.0f,-200.0f,0.0f);
			drawCir(100.0f,50.0f,16);
		}
		glPopMatrix();///�϶�12end
		glPushMatrix();///�϶�11start
		{
			glTranslatef(0.0f,200.0f,0.0f);
			drawCir(100.0f,50.0f,16);
		}
		glPopMatrix();///�϶�11end
		glPushMatrix();///�϶�10start
		{
			glColor3ub(100.0f,0.0f,130.0f);
			glTranslatef(100.0f,150.0f,-25.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			drawCir(50.0f,10.0f,16);
		}
		glPopMatrix();///�϶�10end
		glPushMatrix();///�϶�09start
		{
			glColor3ub(100.0f,0.0f,130.0f);
			glTranslatef(-100.0f,150.0f,-25.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			drawCir(50.0f,10.0f,16);
		}
		glPopMatrix();///�϶�09end
		glPushMatrix();///�϶�10start
		{
			glColor3ub(100.0f,0.0f,130.0f);
			glTranslatef(100.0f,-150.0f,-25.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			drawCir(50.0f,10.0f,16);
		}
		glPopMatrix();///�϶�10end
		glPushMatrix();///�϶�09start
		{
			glColor3ub(100.0f,0.0f,130.0f);
			glTranslatef(-100.0f,-150.0f,-25.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			drawCir(50.0f,10.0f,16);
		}
		glPopMatrix();///�϶�09end
		*/
/*		
		Base_model();//�I�s���y
		glColor3ub(200.0f,100.0f,0.0f);
		BaseX_model();//�I�sX�b���y
		glColor3ub(170.0f,170.0f,0.0f);
		BaseY_model();//�I�sY�b���y
*/
	}
	glPopMatrix();///�϶�13end

////////////////////////////////////////////////////////////////////////////	
	glFlush();
	SwapBuffers(dc->m_hDC);
	if (ppalOld)
	pDC->SelectPalette(ppalOld, 0);
	wglMakeCurrent(NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CNewView diagnostics

#ifdef _DEBUG
void CNewView::AssertValid() const
{
	
	CView::AssertValid();
}

void CNewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNewDoc* CNewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNewDoc)));
	return (CNewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNewView message handlers

BOOL CNewView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CNewView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	if ((cx <= 0) || (cy <= 0))
		return;
//�]�wOpen_Gl�e��	
//	CClientDC	dc(this);

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
	
	// TODO: Add your message handler code here
}

int CNewView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
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
	return 0;
}

BOOL CNewView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
}
void CNewView::opengl_Initial()
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

void CNewView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)//�]�w��L���s 
{
	switch(nChar)
	{
	case 65://A,4
		view_y+=5.0f;
		//MessageBox("A");
		break;
	case 67://C,3
		View_Flag=!View_Flag;
		if(View_Flag==true)
			view_z=-90.0f;
		else
			view_z=90.0f;
		view_x=-90.0f;
		view_y=0.0f;
		//MessageBox("C");
		break;	
	case 68://D,6
		view_y-=5.0f;
		//MessageBox("D");
		break;
	case 69://E,9
		view_z+=5.0f;
		//MessageBox("E");
		break;
	case 81://Q,7
		view_z-=5.0f;
		//MessageBox("Q");
		break;
	case 83://S,5
		View_Flag1=!View_Flag1;
		if(View_Flag1==true)
			view_z=0.0f;
		else
			view_z=-90.0f;			
		view_x=0.0f;
		view_y=0.0f;
		//MessageBox("S");
		break;
	case 87://W,8
		view_x-=5.0f;
		//MessageBox("W");
		break;
	case 88://X,2
		view_x+=5.0f;
		//MessageBox("X");
		break;
	case 90://Z,1
		view_z=0.0f;
		view_x=-90.0f;
		view_y=0.0f;
		//MessageBox("Z");
		break;
	case VK_NUMPAD0:
//		Line_Side=!Line_Side;
		break;
	case VK_NUMPAD1:
		view_z=0.0f;
		view_x=-90.0f;
		view_y=0.0f;
		break;
	case VK_NUMPAD2:
		view_x+=5.0f;
		break;
	case VK_NUMPAD3:
		View_Flag=!View_Flag;
		if(View_Flag==true)
			view_z=-90.0f;
		else
			view_z=90.0f;
		view_x=-90.0f;
		view_y=0.0f;
		break;
	case VK_NUMPAD4:
		view_y+=5.0f;
		break;
	case VK_NUMPAD6:
		view_y-=5.0f;
		break;
	case VK_NUMPAD7:
		view_z-=5.0f;
		break;
	case VK_NUMPAD8:
		view_x-=5.0f;
		break;
	case VK_NUMPAD9:
		view_z+=5.0f;
		break;
	case VK_NUMPAD5:
		View_Flag1=!View_Flag1;
		if(View_Flag1==true)
			view_z=0.0f;
		else
			view_z=-90.0f;			
		view_x=0.0f;
		view_y=0.0f;

		break;
	case VK_F1:
	view_x+=5.0f;

		break;
	case VK_F2:
	view_y+=5.0f;


		break;
	case VK_F3:
	view_z-=5.0f;


		break;
	case VK_F4:



		break;
	case VK_F5:
		Line_Flag = !Line_Flag;
		break;
	case VK_F6:

		break;
	/////////////////////////
	case VK_F7://x

		break;
	case VK_F8://y

		break;
	case VK_F9://yaw

		break;
//	case VK_F12://pitch


//		break;
//	case VK_F11://row

//		break;
	case VK_UP:
		view_x += 5.0f;
		break;
	case VK_DOWN:
		view_x -= 5.0f;
		break;
	case VK_RIGHT:
		view_y += 5.0f;
		break;
	case VK_LEFT:
		view_y -= 5.0f;
		break;
	case VK_F11:
		view_z += 5.0f;
		break;
	case VK_F12:
		view_z -= 5.0f;
		break;
	}
	Invalidate(true);
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CNewView::Base_model()//���y
{
		// ���y start /////////////////////////////
		drawRetc(Base_W1, Base_L1, Base_H1);
		glRotatef(aRotate, 0.0f, 0.0f, 1.0f);
		glPushMatrix();///�϶�1start
		{
			glTranslatef(Base_W1/2.0f-Base_W2/2.0f,-Base_L1/2.0f+Base_L2/2.0f,Base_H1/2.0f+Base_H2/2.0f);
			//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
			glColor3ub(0.0f,0.0f,130.0f);
			drawRetc(Base_W2, Base_L2, Base_H2);
		}
		glPopMatrix();///�϶�1end
		
		glPushMatrix();///�϶�2start
		{
			glTranslatef(-Base_W1/2.0f+Base_W2/2.0f,-Base_L1/2.0f+Base_L2/2.0f,Base_H1/2.0f+Base_H2/2.0f);
			//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
			drawRetc(Base_W2, Base_L2, Base_H2);
		}
		glPopMatrix();///�϶�2end

		// �U�ƭy /////////////////////////////
		glPushMatrix();///�϶�3start
		{
			glTranslatef(0.0f,Base_L1/2.0f-shift_1-Base_L3/2.0f,Base_H1/2.0f+Base_H3/2.0f);
			//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
			glColor3ub(100.0f,100.0f,100.0f);
			drawRetc(Base_W3, Base_L3, Base_H3);
		}
		glPopMatrix();///�϶�3end

		glPushMatrix();///�϶�4start
		{

			glTranslatef(0.0f,Base_L1/2.0f-shift_1-Base_L3-shift_2-Base_L3/2.0f,Base_H1/2.0f+Base_H3/2.0f);
			//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
			drawRetc(Base_W3, Base_L3, Base_H3);
		}
		glPopMatrix();///�϶�4end

		// �W�ƭy /////////////////////////////
		glPushMatrix();///�϶�5start
		{
			glTranslatef(0.0f,Base_L1/2.0f-shift_1-shift_3-Base_L4/2.0f,Base_H1/2.0f+Base_H3+Base_H4/2.0f);
			//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
			glColor3ub(100.0f,100.0f,100.0f);
			drawRetc(Base_W4, Base_L4, Base_H4);
		}
		glPopMatrix();///�϶�5end

		glPushMatrix();///�϶�6start
		{
			glTranslatef(0.0f,Base_L1/2.0f-shift_1-Base_L3-shift_2-Base_L3+shift_3+Base_L4/2.0f,Base_H1/2.0f+Base_H3+Base_H4/2.0f);
			//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
			drawRetc(Base_W4, Base_L4, Base_H4);
		}
		glPopMatrix();///�϶�6end
		// ���� /////////////////////////////
		glPushMatrix();//�T���γ���///�϶�7start
		{
			glTranslatef(-Base_W1/2.0f+Base_W5/2.0f,-Base_L1/2.0f+Base_L5/2.0f,Base_H1/2.0f+Base_H2+Base_H5/2.0f);
			//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
			glColor3ub(0.0f,0.0f,130.0f);
			drawtriangle_1(Base_W5, Base_L5, Base_H5);
		}
		glPopMatrix();///�϶�7end

		glPushMatrix();///�϶�8start
		{
			glTranslatef(Base_W1/2.0f-Base_W5/2.0f,-Base_L1/2.0f+Base_L5/2.0f,Base_H1/2.0f+Base_H2+Base_H5/2.0f);
			//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
			drawtriangle(Base_W5, Base_L5, Base_H5);
		}
		glPopMatrix();///�϶�8end
    
		glPushMatrix();//����Ϊ�����///�϶�9start
		{
			glTranslatef(-Base_W1/2.0f+Base_W5+Base_W6/2.0f,-Base_L1/2.0f+Base_L5/2.0f,Base_H1/2.0f+Base_H2+Base_H5/2.0f);
			//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
			drawRetc(Base_W6, Base_L6, Base_H6);
		}
		glPopMatrix();///�϶�9end

		glPushMatrix();///�϶�10start
		{
			glTranslatef(Base_W1/2.0f-Base_W5-Base_W6/2.0f,-Base_L1/2.0f+Base_L5/2.0f,Base_H1/2.0f+Base_H2+Base_H5/2.0f);
			//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
			drawRetc(Base_W6, Base_L6, Base_H6);
		}
		glPopMatrix();///�϶�10end

		glPushMatrix();//�����Y�X������///�϶�11start
		{		
			glTranslatef(-Base_W1/2.0f+Base_W5+Base_W6+Base_W7/2.0f,-Base_L1/2.0f+Base_L5/2.0f,Base_H1/2.0f+Base_H2+Base_H5-Base_H7/2.0f);
			//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
			glColor3ub(0.0f,0.0f,130.0f);
			drawRetc(Base_W7, Base_L7, Base_H7);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			left_support();
		}
		glPopMatrix();///�϶�11end


		glPushMatrix();///�϶�12start
		{
			glTranslatef(Base_W1/2.0f-Base_W5-Base_W6-Base_W7/2.0f,-Base_L1/2.0f+Base_L5/2.0f,Base_H1/2.0f+Base_H2+Base_H5-Base_H7/2.0f);
			//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
			glColor3ub(0.0f,0.0f,130.0f);
			drawRetc(Base_W7, Base_L7, Base_H7);
			right_support();
		}
		glPopMatrix();///�϶�12end
		// ���y end /////////////////////////////
}
void CNewView::BaseX_model()//X�b���y
{
	///////////////////////////////////////////////
	////X�bstart
	glTranslatef(shiftXValue+((Base_W4-X_Base_W1)/2.0f)-(X_Base_W4-X_Base_W3)/2.0f/*�ᤩ�ͩR*/,((Base_L1/2.0f-X_Base_L1/2.0f+shift_7+X_Base_L3/2.0f)-(shift_1+shift_3+Base_L4/2.0f)),(Base_H1/2.0f+Base_H3+Base_H4/2.0f)+(X_Base_H1/2.0f+X_Base_H3+shift_10-X_Base_H5/2.0f));
	//(Base_W4+X_Base_W1)/2.0f
	//Base_W4=580
	//X_Base_W1=260
	//X_Base_W4=75.7
	//X_Base_W3=60
	//glTranslatef(0.0f,50.0f,Base_W7+X_Base_H7);
	//Base_W7+X_Base_H7
	drawRetc(X_Base_W1, X_Base_L1, X_Base_H1);
	glRotatef(aRotate, 0.0f, 0.0f, 1.0f);
	glPushMatrix();
	{
		glTranslatef(0.0f,0.0f,X_Base_H1/2.0f+X_Base_H6/2.0f);
		glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		glColor3ub(200.0f,100.0f,0.0f);
		drawRetc(X_Base_W6, X_Base_L6, X_Base_H6);
	}
	glPopMatrix();    
	// X�b���y�W���ƭy /////////////////////////////

	glPushMatrix();
	{
		glTranslatef(-X_Base_W1/2.0f+shift_6-X_Base_W2/2.0f,0.0f,X_Base_H1/2.0f+X_Base_H2/2.0f);
		glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		glColor3ub(100.0f,100.0f,100.0f);
		drawRetc(X_Base_W2, X_Base_L2, X_Base_H2);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(X_Base_W1/2.0f-shift_6+X_Base_W2/2.0f,0.0f,X_Base_H1/2.0f+X_Base_H2/2.0f);
		glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W2, X_Base_L2, X_Base_H2);
	}
	glPopMatrix();

    // 4�ӤU���L /////////////////////////////
	glPushMatrix();
	{
		glTranslatef(-X_Base_W1/2.0f+X_Base_W3/2.0f,-X_Base_L1/2.0f+shift_7+X_Base_L3/2.0f,-X_Base_H1/2.0f-X_Base_H3/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		glColor3ub(200.0f,100.0f,0.0f);
		drawRetc(X_Base_W3, X_Base_L3, X_Base_H3);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-X_Base_W1/2.0f+X_Base_W3/2.0f,X_Base_L1/2.0f-shift_7-X_Base_L3/2.0f,-X_Base_H1/2.0f-X_Base_H3/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W3, X_Base_L3, X_Base_H3);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(X_Base_W1/2.0f-X_Base_W3/2.0f,-X_Base_L1/2.0f+shift_7+X_Base_L3/2.0f,-X_Base_H1/2.0f-X_Base_H3/2.0f);
		glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W3, X_Base_L3, X_Base_H3);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(X_Base_W1/2.0f-X_Base_W3/2.0f,X_Base_L1/2.0f-shift_7-X_Base_L3/2.0f,-X_Base_H1/2.0f-X_Base_H3/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W3, X_Base_L3, X_Base_H3);
	}
	glPopMatrix();
	// X�b���y���U�ƭy /////////////////////////////
	glPushMatrix();//�ƭy�������(�@�|��)
	{
		glTranslatef(-X_Base_W1/2.0f+X_Base_W3/2.0f,-X_Base_L1/2.0f+shift_7+X_Base_L3/2.0f,-X_Base_H1/2.0f-X_Base_H3-shift_8+X_Base_H4/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		glColor3ub(100.0f,100.0f,100.0f);
		drawRetc(X_Base_W4, X_Base_L4, X_Base_H4);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(X_Base_W1/2.0f-X_Base_W3/2.0f,-X_Base_L1/2.0f+shift_7+X_Base_L3/2.0f,-X_Base_H1/2.0f-X_Base_H3-shift_8+X_Base_H4/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W4, X_Base_L4, X_Base_H4);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-X_Base_W1/2.0f+X_Base_W3/2.0f,X_Base_L1/2.0f-shift_7-X_Base_L3/2.0f,-X_Base_H1/2.0f-X_Base_H3-shift_8+X_Base_H4/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W4, X_Base_L4, X_Base_H4);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(X_Base_W1/2.0f-X_Base_W3/2.0f,X_Base_L1/2.0f-shift_7-X_Base_L3/2.0f,-X_Base_H1/2.0f-X_Base_H3-shift_8+X_Base_H4/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W4, X_Base_L4, X_Base_H4);
	}
	glPopMatrix();

	glPushMatrix();//�ƭy����Ӹ}(���@��)
	{
		glTranslatef(-X_Base_W1/2.0f+X_Base_W3/2.0f,-X_Base_L1/2.0f+shift_7+X_Base_L3/2.0f+shift_9/2.0f+X_Base_L5/2.0f,-X_Base_H1/2.0f-X_Base_H3-shift_10+X_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W5, X_Base_L5, X_Base_H5);
	}
	glPopMatrix();
	glPushMatrix();
	{
	    glTranslatef(-X_Base_W1/2.0f+X_Base_W3/2.0f,-X_Base_L1/2.0f+shift_7+X_Base_L3/2.0f-shift_9/2.0f-X_Base_L5/2.0f,-X_Base_H1/2.0f-X_Base_H3-shift_10+X_Base_H5/2.0f);
	    //glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W5, X_Base_L5, X_Base_H5);
	}
	glPopMatrix();
	glPushMatrix();//(���@��)
	{
		glTranslatef(X_Base_W1/2.0f-X_Base_W3/2.0f,-X_Base_L1/2.0f+shift_7+X_Base_L3/2.0f+shift_9/2.0f+X_Base_L5/2.0f,-X_Base_H1/2.0f-X_Base_H3-shift_10+X_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W5, X_Base_L5, X_Base_H5);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(X_Base_W1/2.0f-X_Base_W3/2.0f,-X_Base_L1/2.0f+shift_7+X_Base_L3/2.0f-shift_9/2.0f-X_Base_L5/2.0f,-X_Base_H1/2.0f-X_Base_H3-shift_10+X_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W5, X_Base_L5, X_Base_H5);
	}
	glPopMatrix();
	glPushMatrix();//(���@��)
	{
		glTranslatef(-X_Base_W1/2.0f+X_Base_W3/2.0f,X_Base_L1/2.0f-shift_7-X_Base_L3/2.0f-shift_9/2.0f-X_Base_L5/2.0f,-X_Base_H1/2.0f-X_Base_H3-shift_10+X_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W5, X_Base_L5, X_Base_H5);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-X_Base_W1/2.0f+X_Base_W3/2.0f,X_Base_L1/2.0f-shift_7-X_Base_L3/2.0f+shift_9/2.0f+X_Base_L5/2.0f,-X_Base_H1/2.0f-X_Base_H3-shift_10+X_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W5, X_Base_L5, X_Base_H5);
	}
	glPopMatrix();
	glPushMatrix();//(���@��)
	{
		glTranslatef(X_Base_W1/2.0f-X_Base_W3/2.0f,X_Base_L1/2.0f-shift_7-X_Base_L3/2.0f-shift_9/2.0f-X_Base_L5/2.0f,-X_Base_H1/2.0f-X_Base_H3-shift_10+X_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W5, X_Base_L5, X_Base_H5);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(X_Base_W1/2.0f-X_Base_W3/2.0f,X_Base_L1/2.0f-shift_7-X_Base_L3/2.0f+shift_9/2.0f+X_Base_L5/2.0f,-X_Base_H1/2.0f-X_Base_H3-shift_10+X_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W5, X_Base_L5, X_Base_H5);
	}
	glPopMatrix();

    // X�b���y���U�ƭy���T���l���� /////////////////////////////
    	glPushMatrix();//���������
        {
		glTranslatef(X_Base_W1/2.0f-shift_11-X_Base_W7/2.0f,0.0f,-X_Base_H1/2.0f-X_Base_H7/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		glColor3ub(200.0f,100.0f,0.0f);
		drawRetc(X_Base_W7, X_Base_L7, X_Base_H7);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-X_Base_W1/2.0f+shift_11+X_Base_W7/2.0f,0.0f,-X_Base_H1/2.0f-X_Base_H7/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(X_Base_W7, X_Base_L7, X_Base_H7);
	}
	glPopMatrix();
	////X�bend
}
void CNewView::BaseY_model()//Y�b���y
{
		///////////////////////////////////////////////////////////////////////////////////
	////Y�bstart
	glColor3ub(170.0f,170.0f,0.0f);

	// ���y /////////////////////////////
	float a;
	glTranslatef(0.0f,shiftYValue+((X_Base_L2-Y_Base_W1)/2.0f)-((Y_Base_W4-Y_Base_W2)/2.0f)/*�ᤩ�ͩR*/,(55.0f+X_Base_H1/2.0f+X_Base_H2));
	//((X_Base_L2-Y_Base_W1)/2.0f)
	//X_Base_L2=520
	//Y_Base_W1=260
	//Y_Base_W4=75.7
	//Y_Base_W2=60.0
	a=(55.0f+X_Base_H1/2.0f+X_Base_H2);

	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	drawRetc(Y_Base_W1, Y_Base_L1, Y_Base_H1);
	Z_axis();
	glPushMatrix();
	{

		glTranslatef(-Y_Base_W1/2.0f+Y_Base_W2/2.0f,-Y_Base_L1/2.0f+shift_12+Y_Base_L2/2.0f,-Y_Base_H1/2.0f-Y_Base_H2/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		glColor3ub(170.0f,170.0f,0.0f);
		drawRetc(Y_Base_W2, Y_Base_L2, Y_Base_H2);

	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-Y_Base_W1/2.0f+Y_Base_W2/2.0f,Y_Base_L1/2.0f-shift_12-Y_Base_L2/2.0f,-Y_Base_H1/2.0f-Y_Base_H2/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W2, Y_Base_L2, Y_Base_H2);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(Y_Base_W1/2.0f-Y_Base_W2/2.0f,-Y_Base_L1/2.0f+shift_12+Y_Base_L2/2.0f,-Y_Base_H1/2.0f-Y_Base_H2/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W2, Y_Base_L2, Y_Base_H2);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(Y_Base_W1/2.0f-Y_Base_W2/2.0f,Y_Base_L1/2.0f-shift_12-Y_Base_L2/2.0f,-Y_Base_H1/2.0f-Y_Base_H2/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W2, Y_Base_L2, Y_Base_H2);
	}
	glPopMatrix();


    glPushMatrix();//���y������������
	{
		glTranslatef(0.0f,-Y_Base_L1/2.0f+shift_12+Y_Base_L2/2.0f,-Y_Base_H1/2.0f-Y_Base_H3/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W3, Y_Base_L3, Y_Base_H3);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0.0f,Y_Base_L1/2.0f-shift_12-Y_Base_L2/2.0f,-Y_Base_H1/2.0f-Y_Base_H3/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W3, Y_Base_L3, Y_Base_H3);
	}
	glPopMatrix();

   
	
    // Y�b���y���U�ƭy /////////////////////////////

	glPushMatrix();//�ƭy�������(�@�|��)
	{
		glTranslatef(-Y_Base_W1/2.0f+Y_Base_W2/2.0f,-Y_Base_L1/2.0f+shift_12+Y_Base_L2/2.0f,-Y_Base_H1/2.0f-Y_Base_H2+shift_13-Y_Base_H4/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		glColor3ub(100.0f,100.0f,100.0f);
		drawRetc(Y_Base_W4, Y_Base_L4, Y_Base_H4);
	}
	glPopMatrix();


	glPushMatrix();
	{
		glTranslatef(-Y_Base_W1/2.0f+Y_Base_W2/2.0f,Y_Base_L1/2.0f-shift_12-Y_Base_L2/2.0f,-Y_Base_H1/2.0f-Y_Base_H2+shift_13-Y_Base_H4/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W4, Y_Base_L4, Y_Base_H4);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(Y_Base_W1/2.0f-Y_Base_W2/2.0f,-Y_Base_L1/2.0f+shift_12+Y_Base_L2/2.0f,-Y_Base_H1/2.0f-Y_Base_H2+shift_13-Y_Base_H4/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W4, Y_Base_L4, Y_Base_H4);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(Y_Base_W1/2.0f-Y_Base_W2/2.0f,Y_Base_L1/2.0f-shift_12-Y_Base_L2/2.0f,-Y_Base_H1/2.0f-Y_Base_H2+shift_13-Y_Base_H4/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W4, Y_Base_L4, Y_Base_H4);
	}
	glPopMatrix();

	glPushMatrix();//�ƭy����Ӹ}(���@��)
	{
		glTranslatef(-Y_Base_W1/2.0f+Y_Base_W2/2.0f,-Y_Base_L1/2.0f+shift_12+Y_Base_L2/2.0f+shift_14/2.0f+Y_Base_L5/2.0f,-Y_Base_H1/2.0f-Y_Base_H2-shift_15+Y_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		glColor3ub(100.0f,100.0f,100.0f);
		drawRetc(Y_Base_W5, Y_Base_L5, Y_Base_H5);
	}
	glPopMatrix();

	glPushMatrix();
	{

		glTranslatef(-Y_Base_W1/2.0f+Y_Base_W2/2.0f,-Y_Base_L1/2.0f+shift_12+Y_Base_L2/2.0f-shift_14/2.0f-Y_Base_L5/2.0f,-Y_Base_H1/2.0f-Y_Base_H2-shift_15+Y_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W5, Y_Base_L5, Y_Base_H5);
	}
	glPopMatrix();

	glPushMatrix();//(���@��)
	{
		glTranslatef(Y_Base_W1/2.0f-Y_Base_W2/2.0f,-Y_Base_L1/2.0f+shift_12+Y_Base_L2/2.0f+shift_14/2.0f+Y_Base_L5/2.0f,-Y_Base_H1/2.0f-Y_Base_H2-shift_15+Y_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W5, Y_Base_L5, Y_Base_H5);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(Y_Base_W1/2.0f-Y_Base_W2/2.0f,-Y_Base_L1/2.0f+shift_12+Y_Base_L2/2.0f-shift_14/2.0f-Y_Base_L5/2.0f,-Y_Base_H1/2.0f-Y_Base_H2-shift_15+Y_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W5, Y_Base_L5, Y_Base_H5);
	}
	glPopMatrix();

	glPushMatrix();//(���@��)
	{
		glTranslatef(-Y_Base_W1/2.0f+Y_Base_W2/2.0f,Y_Base_L1/2.0f-shift_12-Y_Base_L2/2.0f+shift_14/2.0f+Y_Base_L5/2.0f,-Y_Base_H1/2.0f-Y_Base_H2-shift_15+Y_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W5, Y_Base_L5, Y_Base_H5);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-Y_Base_W1/2.0f+Y_Base_W2/2.0f,Y_Base_L1/2.0f-shift_12-Y_Base_L2/2.0f-shift_14/2.0f-Y_Base_L5/2.0f,-Y_Base_H1/2.0f-Y_Base_H2-shift_15+Y_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W5, Y_Base_L5, Y_Base_H5);
	}
	glPopMatrix();

	glPushMatrix();//(���@��)
	{
		glTranslatef(Y_Base_W1/2.0f-Y_Base_W2/2.0f,Y_Base_L1/2.0f-shift_12-Y_Base_L2/2.0f+shift_14/2.0f+Y_Base_L5/2.0f,-Y_Base_H1/2.0f-Y_Base_H2-shift_15+Y_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W5, Y_Base_L5, Y_Base_H5);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(Y_Base_W1/2.0f-Y_Base_W2/2.0f,Y_Base_L1/2.0f-shift_12-Y_Base_L2/2.0f-shift_14/2.0f-Y_Base_L5/2.0f,-Y_Base_H1/2.0f-Y_Base_H2-shift_15+Y_Base_H5/2.0f);
		//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		drawRetc(Y_Base_W5, Y_Base_L5, Y_Base_H5);
	}
	glPopMatrix();
	
}
void CNewView::left_support()//����伵�[
{
	
	// ���y start /////////////////////////////
	glTranslatef(Base_W7/2.0f-left_support_W1/2.0f-1.0f,left_support_L1/2.0f+Base_H7/2.0f,(left_support_L1/2.0f-Base_L2/2.0f-5.0f));
	//Base_W7/2.0f-left_support_W1/2.0f-1.0f
	//                            -�P���y���Z��--
	//left_support_L1=144
	//Base_L2 = 215.0f
	glPushMatrix();
	{
		glColor3ub(100.0f,100.0f,100.0f);
		drawRetc(left_support_W1, left_support_L1, left_support_H1);
		
	}
	glPopMatrix();
	glPushMatrix();//���y�᪺�����
	{
		glTranslatef(-left_support_W1/2.0f-shift_18+left_support_W2/2.0f, -left_support_L1/2.0f+shift_19+left_support_L2/2.0f, -left_support_H1/2.0f-left_support_H2/2.0f);
		glColor3ub(100.0f,100.0f,100.0f);
		drawRetc(left_support_W2, left_support_L2, left_support_H2);
		glPushMatrix();//���y�᪺�����
		{
			glTranslatef(-40.0f, 0.0f,(motor_H1/2.0f+left_support_H2/2.0f));
			motor();
		}
		glPopMatrix();

	}
	glPopMatrix();

	// ���y�Y�X�Ӫ��� /////////////////////////////
	glPushMatrix();//(�b�|��35)
	{
		glTranslatef(0.0f, -left_support_L1/2.0f+shift_20, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glColor3ub(100.0f,100.0f,100.0f);
		drawCir(radius_1, left_support_W3, 16);
		
	}
	glPopMatrix();

	glPushMatrix();//(�b�|��20)
	{
		glTranslatef(0.0f, -left_support_L1/2.0f+shift_20, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glColor3ub(100.0f,100.0f,100.0f);
		drawCir(radius_2, left_support_W4, 16);
		/////////////////////////////////////////
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		watchcase_support();
		/////////////////////////////////////////
	}
	glPopMatrix();
	

}
void CNewView::right_support()//�k��伵�[
{
	glColor3ub(100.0f,100.0f,100.0f);
	glRotatef(90.0, 0.0f, 0.0f, 1.0f);
	glTranslatef((Base_L5/2.0f-right_support_W2/2.0f-5.0f),(Base_W7/2.0f-right_support_L1/2.0f-5.0f),(right_support_H1+Base_H7)/2.0f+right_support_H2);
	//right_support_W2=120
	//Base_L5 = 215
	//Base_W7/2.0f-right_support_L1/2.0f-5.0f
	// ���y /////////////////////////////
	drawRetc(right_support_W1, right_support_L1, right_support_H1);
/*
	glPushMatrix();//���W
	{
		glTranslatef(0.0f,0.0f,-right_support_H1/2.0f+69);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		drawCir(12.5, 100, 16);
	}
	glPopMatrix();
*/
	glPushMatrix();//�U���L
	{
		glTranslatef(0.0f,0.0f,-right_support_H1/2.0f-right_support_H2/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(right_support_W2, right_support_L2, right_support_H2);
	}
	glPopMatrix();

	glPushMatrix();//��γ���
	{

		glTranslatef(0.0f,0.0f,right_support_H1/2.0f+right_support_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
	    drawladder(right_support_U3, right_support_L3, right_support_H3, right_support_W3);

	}
	glPopMatrix();
}
void CNewView::watchcase_support()//���ߤ伵�[
{
	// ���y /////////////////////////////
	//float k;
	glRotatef(WatchRotate, 1.0f, 0.0f, 0.0f);
	glTranslatef((watchcase_support_W1+left_support_W4)*-1.0f/2.0f, watchcase_support_L1/-2.0f,0.0f) ;
	
	/*
	k=(watchcase_support_W1+left_support_W4)*-1.0f/2.0f;
	k=shift_25+(left_support_W1-left_support_W4)/2.0f;
	*/
	glColor3ub(130.0f,130.0f,130.0f);
	drawRetc(watchcase_support_W1, watchcase_support_L1, watchcase_support_H1);
	jig_fixed();
	glPushMatrix();//���y�W����L(�b�|��35)
	{
		glTranslatef(0.0f, watchcase_support_L1/2.0f+shift_25/2.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glColor3ub(130.0f,130.0f,130.0f);
		drawCir(watchcase_support_radius_1, shift_25, 16);
	}
	glPopMatrix();

	glPushMatrix();//���y�W����L(�b�|��27.5)
	{
		glTranslatef(0.0f, watchcase_support_L1/2.0f+shift_25+shift_26/2.0f, 0.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glColor3ub(130.0f,130.0f,130.0f);
		drawCir(watchcase_support_radius_2, shift_26, 16);
		
	}
	glPopMatrix();


	glPushMatrix();//���y�W����L(�b�|��15.6)
	{
		glTranslatef(0.0f, watchcase_support_L1/2.0f+shift_25+shift_26+shift_27/2.0f, 0.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glColor3ub(130.0f,130.0f,130.0f);
		drawCir(watchcase_support_radius_3, shift_27, 16);
		jig();
	}
	glPopMatrix();


	glPushMatrix();//���y�W������γ���
	{
		glTranslatef(watchcase_support_W1/2.0f-watchcase_support_W2/2.0f, watchcase_support_L1/2.0f+watchcase_support_L2/2.0f, 0.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		glColor3ub(130.0f,130.0f,130.0f);
		drawRetc(watchcase_support_W2, watchcase_support_L2, watchcase_support_H2);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-watchcase_support_W1/2.0f+watchcase_support_W2/2.0f, watchcase_support_L1/2.0f+watchcase_support_L2/2.0f, 0.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(watchcase_support_W2, watchcase_support_L2, watchcase_support_H2);
	}
	glPopMatrix();

    glPushMatrix();//���y�W����γ���
	{
		glTranslatef(watchcase_support_W1/2.0f-watchcase_support_W2-watchcase_support_W3/2.0f, watchcase_support_L1/2.0f+watchcase_support_L2/2.0f, 0.0f);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glColor3ub(130.0f,130.0f,130.0f);
		drawtriangle_1(watchcase_support_W3, watchcase_support_L3, watchcase_support_H3);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-watchcase_support_W1/2.0f+watchcase_support_W2+watchcase_support_W3/2.0f, watchcase_support_L1/2.0f+watchcase_support_L2/2.0f, 0.0f);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		drawtriangle(watchcase_support_W3, watchcase_support_L3, watchcase_support_H3);
	}
	glPopMatrix();

	glPushMatrix();//�Y�X�Ӫ���
	{
		glTranslatef(-watchcase_support_W1/2.0f-shift_28/2.0f, watchcase_support_L1/2.0f, 0.0f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glColor3ub(130.0f,130.0f,130.0f);
		drawCir(watchcase_support_radius_4, shift_28, 16);
	}
	glPopMatrix();
}
void CNewView::jig()//����
{
	
	glPushMatrix();
	{
	glTranslatef(0.0f,0.0f,(shift_27/2.0f));
	glRotatef(90.0f+WatchRotate1, 0.0f, 0.0f, 1.0f);
	glColor3ub(60.0f,60.0f,60.0f);
	drawCir(jig_radius_1, jig_cir_H1, 16);	
	glPushMatrix();//�ѤU�ܤW�|(�ꪺ�b�|��15.6)
	{
		glTranslatef(0.0f, 0.0f, -jig_cir_H1/2.0f-jig_cir_H2/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		glColor3ub(60.0f,60.0f,60.0f);
		drawCir(jig_radius_2, jig_cir_H2, 16);
		//////////////////////////////////////////����
		
		glPushMatrix();
		{
			glColor3ub(60.0f,0.0f,0.0f);
			glTranslatef(0.0f,-jig_L3/2.0f-6.0f/2.0f,-jig_cir_H2/2.0f-10.0f/2.0f);
			drawRetc(28.0f, 6.0f, 10.0f);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glColor3ub(60.0f,0.0f,0.0f);
			glTranslatef(0.0f,jig_L3/2.0f+6.0f/2.0f,-jig_cir_H2/2.0f-10.0f/2.0f);
			drawRetc(28.0f, 6.0f, 10.0f);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glColor3ub(60.0f,0.0f,0.0f);
			glTranslatef((jig_W3/2.0f+11.545/2.0f),0.0f,-jig_cir_H2/2.0f-10.0f/2.0f);
			drawRetc(11.545f, 30.0f, 10.0f);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glColor3ub(60.0f,0.0f,0.0f);
			glTranslatef((-jig_W3/2.0f-11.545/2.0f),0.0f,-jig_cir_H2/2.0f-10.0f/2.0f);
			drawRetc(11.545f, 30.0f, 10.0f);
		}
		glPopMatrix();
		
		//////////////////////////////////////////
	}
	glPopMatrix();
		///////////////////////////////////////////////////////////////////

	glPushMatrix();//�ѤU�ܤW�|(���ت��T�w�϶�)
	{
		glTranslatef(0.0f, 0.0f, -jig_cir_H1/2.0f-jig_cir_H2-jig_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		glColor3ub(6.0f,60.0f,60.0f);
		drawRetc(jig_W3, jig_L3, jig_H3);
	}
	glPopMatrix();
	}
	glPopMatrix();
}
void CNewView::Z_axis()//Z�b
{
	glPushMatrix();
	{
	//float g;
	glTranslatef(Y_Base_W1/2.0f-Z_axis_H1/2.0f-15.0f,0.0f,Z_axis_L1/2.0f+Y_Base_H1/2.0f);
	//g=Y_Base_L1/2.0f-Z_axis_H1/2.0f;
	//g=Z_axis_L1/2.0f+Y_Base_H1/2.0f;
	glColor3ub(100.0f,0.0f,220.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

	glPushMatrix();//�r�Ū������(���y)

	{

		glTranslatef(Z_axis_W1/2.0f-Z_axis_W6/2.0f,0.0f,0.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_axis_W6, Z_axis_L6, Z_axis_H6);


	}

	glPopMatrix();

	glPushMatrix();

	{

		glTranslatef(-Z_axis_W1/2.0f+Z_axis_W6/2.0f,0.0f,0.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_axis_W6, Z_axis_L6, Z_axis_H6);


	}

	glPopMatrix();

	glPushMatrix();

	{

		glTranslatef(0.0f,Z_axis_L1/2.0f-Z_axis_L7/2.0f,0.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_axis_W7, Z_axis_L7, Z_axis_H7);


	}

	glPopMatrix();

	glPushMatrix();

	{

		glTranslatef(0.0f,-Z_axis_L1/2.0f+Z_axis_L7/2.0f,0.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_axis_W7, Z_axis_L7, Z_axis_H7);


	}

	glPopMatrix();

	glPushMatrix();//���y�e���諬

	{

		glTranslatef(0.0f,0.0f,Z_axis_H1/2.0f+Z_axis_H2/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		glColor3ub(100.0f,0.0f,220.0f);
		drawladder(Z_axis_U2, Z_axis_L2, Z_axis_H2, Z_axis_W2);
		

	}

	glPopMatrix();

	glPushMatrix();//�r�Ū������(�諬�e�������)

	{

		glTranslatef(Z_axis_W3/2.0f-Z_axis_W8/2.0f,0.0f,Z_axis_H1/2.0f+Z_axis_H2+Z_axis_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		glColor3ub(120.0f,0,220.0f);
		drawRetc(Z_axis_W8, Z_axis_L8, Z_axis_H8);
		

	}

	glPopMatrix();

	glPushMatrix();

	{

		glTranslatef(-Z_axis_W3/2.0f+Z_axis_W8/2.0f,0.0f,Z_axis_H1/2.0f+Z_axis_H2+Z_axis_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_axis_W8, Z_axis_L8, Z_axis_H8);


	}

	glPopMatrix();

	glPushMatrix();

	{

		glTranslatef(0.0f,Z_axis_L1/2.0f-Z_axis_L9/2.0f,Z_axis_H1/2.0f+Z_axis_H2+Z_axis_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_axis_W9, Z_axis_L9, Z_axis_H9);


	}

	glPopMatrix();

	glPushMatrix();

	{

		glTranslatef(0.0f,-Z_axis_L1/2.0f+Z_axis_L10/2.0f,Z_axis_H1/2.0f+Z_axis_H2+Z_axis_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_axis_W9, Z_axis_L10, Z_axis_H9);


	}

	glPopMatrix();

	/*glPushMatrix();

	{

		glTranslatef(0.0f,0.0f,Z_axis_H1/2.0f+Z_axis_H2+Z_axis_H3+Z_axis_H4/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_axis_W4, Z_axis_L4, Z_axis_H4);


	}

	glPopMatrix();*/

	glPushMatrix();//������W���ƭy

	{

		glTranslatef(Z_axis_W1/2.0f-shift_29-Z_axis_W5/2.0f,-Z_axis_L1/2.0f+Z_axis_L5/2.0f,Z_axis_H1/2.0f+Z_axis_H2+Z_axis_H3+Z_axis_H5/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		glColor3ub(100.0f,100.0f,100.0f);
		drawRetc(Z_axis_W5, Z_axis_L5, Z_axis_H5);
		Z_Base();

	}

	glPopMatrix();


	glPushMatrix();

	{

		glTranslatef(-Z_axis_W1/2.0f+shift_29+Z_axis_W5/2.0f,-Z_axis_L1/2.0f+Z_axis_L5/2.0f,Z_axis_H1/2.0f+Z_axis_H2+Z_axis_H3+Z_axis_H5/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		glColor3ub(100.0f,100.0f,100.0f);
		drawRetc(Z_axis_W5, Z_axis_L5, Z_axis_H5);


	}

	glPopMatrix();

	}
	glPopMatrix();
}
void CNewView::jig_fixed()//����U��T�w�[
{
	// ���y /////////////////////////////
	glPushMatrix();
	{
		
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f,0.0f,-(watchcase_support_L1+shift_33)/2.0f/*100.0f*/);
		glColor3ub(130.0f,130.0f,130.0f);
		drawRetc(jig_fixed_W1, jig_fixed_L1, jig_fixed_H1);
		glPushMatrix();//���y�Ǧ��W�Ѫ������
		{
			glTranslatef(-jig_fixed_W1/2.0f-jig_fixed_W2/2.0f,-jig_fixed_L1/2.0f+jig_fixed_L2/2.0f,0.0f);
			glColor3ub(130.0f,130.0f,130.0f);
			drawRetc(jig_fixed_W2, jig_fixed_L2, jig_fixed_H2);
			glPushMatrix();
			{
				glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
				glTranslatef(0.0f, 0.0f,(motor_H1/2.0f+jig_fixed_L2/2.0f));
				motor();
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//�Y�X�Ӫ���(�b�|��29.98)
		{
			glTranslatef(jig_fixed_W1/2.0f-shift_30,-jig_fixed_L1/2.0f+shift_31,0.0f);
			//glRotatef(0, 0.0f, 1.0f, 0.0f);
			glColor3ub(130.0f,130.0f,130.0f);
			drawCir(jig_fixed_radius_1, shift_32, 16);
		}
		glPopMatrix();

		glPushMatrix();//�Y�X�Ӫ���(�b�|��15)
		{
			glTranslatef(jig_fixed_W1/2.0f-shift_30,-jig_fixed_L1/2.0f+shift_31,0.0f);
			//glRotatef(0, 0.0f, 1.0f, 0.0f);
			glColor3ub(130.0f,130.0f,130.0f);
			drawCir(jig_fixed_radius_2, shift_33, 16);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void CNewView::Z_Base()//Z�b���y
{
	glTranslatef(-(Z_Base_W1/2.0f-shift_34-Z_Base_W2/2.0f),shiftZValue-(Z_axis_L5/2.0f-Z_axis_L10-Z_axis_L-Z_Base_L1/2.0f+shift_37+Z_Base_L4),Z_Base_H1/2.0f+Z_axis_H5/2.0f+(Z_Base_H2-shift_36));
	//                                                  -- Z�b���ʶq---     
	//Z_axis_L=320;
	//Z_Base_L1=210
	////Z_axis_H3/2.0f+Z_Base_H1/2.0f+Z_Base_H2
	// ���ystart /////////////////////////////

	glColor3ub(170.0f,170.0f,0.0f);
	drawRetc(Z_Base_W1, Z_Base_L1, Z_Base_H1);
	main_shaft();
	glPushMatrix();//���y�U�������(�@�|��)
	{
		glTranslatef(Z_Base_W1/2.0f-shift_34-Z_Base_W2/2.0f, -Z_Base_L1/2.0f-shift_35+Z_Base_L2/2.0f, -Z_Base_H1/2.0f+shift_36-Z_Base_H2/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		glColor3ub(100.0f,100.0f,100.0f);
		drawRetc(Z_Base_W2, Z_Base_L2, Z_Base_H2);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-Z_Base_W1/2.0f+shift_34+Z_Base_W2/2.0f, -Z_Base_L1/2.0f-shift_35+Z_Base_L2/2.0f, -Z_Base_H1/2.0f+shift_36-Z_Base_H2/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W2, Z_Base_L2, Z_Base_H2);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(Z_Base_W1/2.0f-shift_34-Z_Base_W2/2.0f, Z_Base_L1/2.0f+shift_35-Z_Base_L2/2.0f, -Z_Base_H1/2.0f+shift_36-Z_Base_H2/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W2, Z_Base_L2, Z_Base_H2);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-Z_Base_W1/2.0f+shift_34+Z_Base_W2/2.0f, Z_Base_L1/2.0f+shift_35-Z_Base_L2/2.0f, -Z_Base_H1/2.0f+shift_36-Z_Base_H2/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W2, Z_Base_L2, Z_Base_H2);
	}
	glPopMatrix();
	glPushMatrix();//����ΤU����Ӹ}(���@��)(�@�|��)
	{
		glTranslatef(Z_Base_W1/2.0f-shift_34-Z_Base_W3/2.0f, -Z_Base_L1/2.0f-shift_35+Z_Base_L2/2.0f, -Z_Base_H1/2.0f+shift_36-Z_Base_H2-Z_Base_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		glColor3ub(100.0f,100.0f,100.0f);
		drawRetc(Z_Base_W3, Z_Base_L3, Z_Base_H3);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(Z_Base_W1/2.0f-shift_34-Z_Base_W2+Z_Base_W3/2.0f, -Z_Base_L1/2.0f-shift_35+Z_Base_L2/2.0f, -Z_Base_H1/2.0f+shift_36-Z_Base_H2-Z_Base_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W3, Z_Base_L3, Z_Base_H3);
	}
	glPopMatrix();
	glPushMatrix();//(���@��)
	{
		glTranslatef(-Z_Base_W1/2.0f+shift_34+Z_Base_W3/2.0f, -Z_Base_L1/2.0f-shift_35+Z_Base_L2/2.0f, -Z_Base_H1/2.0f+shift_36-Z_Base_H2-Z_Base_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W3, Z_Base_L3, Z_Base_H3);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-Z_Base_W1/2.0f+shift_34+Z_Base_W2-Z_Base_W3/2.0f, -Z_Base_L1/2.0f-shift_35+Z_Base_L2/2.0f, -Z_Base_H1/2.0f+shift_36-Z_Base_H2-Z_Base_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W3, Z_Base_L3, Z_Base_H3);
	}
	glPopMatrix();
	glPushMatrix();//(���@��)
	{
		glTranslatef(Z_Base_W1/2.0f-shift_34-Z_Base_W3/2.0f, Z_Base_L1/2.0f+shift_35-Z_Base_L2/2.0f, -Z_Base_H1/2.0f+shift_36-Z_Base_H2-Z_Base_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W3, Z_Base_L3, Z_Base_H3);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(Z_Base_W1/2.0f-shift_34-Z_Base_W2+Z_Base_W3/2.0f, Z_Base_L1/2.0f+shift_35-Z_Base_L2/2.0f, -Z_Base_H1/2.0f+shift_36-Z_Base_H2-Z_Base_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W3, Z_Base_L3, Z_Base_H3);
	}
	glPopMatrix();
	glPushMatrix();//(���@��)
	{
		glTranslatef(-Z_Base_W1/2.0f+shift_34+Z_Base_W3/2.0f, Z_Base_L1/2.0f+shift_35-Z_Base_L2/2.0f, -Z_Base_H1/2.0f+shift_36-Z_Base_H2-Z_Base_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W3, Z_Base_L3, Z_Base_H3);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-Z_Base_W1/2.0f+shift_34+Z_Base_W2-Z_Base_W3/2.0f, Z_Base_L1/2.0f+shift_35-Z_Base_L2/2.0f, -Z_Base_H1/2.0f+shift_36-Z_Base_H2-Z_Base_H3/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W3, Z_Base_L3, Z_Base_H3);
	}
	glPopMatrix();
	glPushMatrix();//���y�᪺���ĳ���(�j�����)
	{
		glTranslatef(0.0f, -Z_Base_L1/2.0f+shift_37+Z_Base_L4/2.0f, -Z_Base_H1/2.0f-Z_Base_H4/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		glColor3ub(170.0f,170.0f,0.0f);
		drawRetc(Z_Base_W4, Z_Base_L4, Z_Base_H4);
	}
	glPopMatrix();
	glPushMatrix();//���y�᪺���ĳ���(�j������U�������)(�@���)
	{
		glTranslatef(Z_Base_W4/2.0f-Z_Base_W5/2.0f, -Z_Base_L1/2.0f+shift_37-Z_Base_L5/2.0f, -Z_Base_H1/2.0f-Z_Base_H5/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W5, Z_Base_L5, Z_Base_H5);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-Z_Base_W4/2.0f+Z_Base_W5/2.0f, -Z_Base_L1/2.0f+shift_37-Z_Base_L5/2.0f, -Z_Base_H1/2.0f-Z_Base_H5/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W5, Z_Base_L5, Z_Base_H5);
	}
	glPopMatrix();

	glPushMatrix();//���y�᪺���ĳ���(��Ӥp�����)
	{
		glTranslatef(Z_Base_W4/2.0f-Z_Base_W6/2.0f, -Z_Base_L1/2.0f+shift_37-Z_Base_L5-Z_Base_L6/2.0f, -Z_Base_H1/2.0f-Z_Base_H6/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W6, Z_Base_L6, Z_Base_H6);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-Z_Base_W4/2.0f+Z_Base_W6/2.0f, -Z_Base_L1/2.0f+shift_37-Z_Base_L5-Z_Base_L6/2.0f, -Z_Base_H1/2.0f-Z_Base_H6/2.0f);
		glRotatef(0, 0.0f, 1.0f, 0.0f);
		drawRetc(Z_Base_W6, Z_Base_L6, Z_Base_H6);
	}
	glPopMatrix();
	glPushMatrix();//���y�᪺���ĳ���(��ӤT����)
	{
		glTranslatef(Z_Base_W4/2.0f-Z_Base_W6/2.0f, -Z_Base_L1/2.0f+shift_37-Z_Base_L5-Z_Base_L6/2.0f, -Z_Base_H1/2.0f-Z_Base_H6-Z_Base_H7/2.0f);
		glRotatef(90, 0.0f, 0.0f, 1.0f);
		glRotatef(180, 1.0f, 0.0f, 0.0f);
		drawtriangle_1(Z_Base_W7, Z_Base_L7, Z_Base_H7);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-Z_Base_W4/2.0f+Z_Base_W6/2.0f, -Z_Base_L1/2.0f+shift_37-Z_Base_L5-Z_Base_L6/2.0f, -Z_Base_H1/2.0f-Z_Base_H6-Z_Base_H7/2.0f);
		glRotatef(90, 0.0f, 0.0f, 1.0f);
		glRotatef(180, 1.0f, 0.0f, 0.0f);
		drawtriangle_1(Z_Base_W7, Z_Base_L7, Z_Base_H7);
	}
	glPopMatrix();
}
void CNewView::main_shaft()//�D�b
{
	// ���ystart /////////////////////////////
	glPushMatrix();
	{
		glTranslatef(0.0f, shift_38, (Z_Base_H1/2.0f+main_shaft_W1/2.0f)-(main_shaft_W1/2.0f+(main_shaft_W1/2.0f-40.0f)));
		//(Z_Base_H1/2.0f+main_shaft_W1/2.0f)-(main_shaft_W1/2.0f+(main_shaft_W1/2.0f-40.0f))
		//-----------����Z���y����----------  -----�D�b���@�b--  ---------71.5------------
		glRotatef(-90.0, 0.0f, 1.0f, 0.0f);
		glColor3ub(130.0f,130.0f,130.0f);
		drawRetc(main_shaft_W1, main_shaft_L1, main_shaft_H1);
		glPushMatrix();//�ѥ��ܥk�e�L�h(W2�ؤo��10)
		{
			glTranslatef(main_shaft_W1/2.0f+main_shaft_W2/2.0f, 0.0f, 0.0f);
			glRotatef(0, 0.0f, 1.0f, 0.0f);
			drawRetc(main_shaft_W2, main_shaft_L2, main_shaft_H2);
		}
		glPopMatrix();
		glPushMatrix();//(�ꪺ���|��72)
		{
			glTranslatef(main_shaft_W1/2.0f+main_shaft_W2+cir_W1/2.0f, 0.0f, 0.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			drawCir(main_shaft_radius_1, cir_W1, 16);
		}
		glPopMatrix();
		glPushMatrix();//(�ꪺ���|��38)
		{
			glTranslatef(main_shaft_W1/2.0f+main_shaft_W2+cir_W1+cir_W2/2.0f, 0.0f, 0.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			drawCir(main_shaft_radius_2, cir_W2, 16);
		}
		glPopMatrix();
		glPushMatrix();//(�ꪺ���|��25)
		{
			glTranslatef(main_shaft_W1/2.0f+main_shaft_W2+cir_W1+cir_W2+cir_W3/2.0f, 0.0f, 0.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			drawCir(main_shaft_radius_3, cir_W3, 16);
		}
		glPopMatrix();
		glPushMatrix();//(�ꪺ���|��22)
		{
			glTranslatef(main_shaft_W1/2.0f+main_shaft_W2+cir_W1+cir_W2+cir_W3+cir_W4/2.0f, 0.0f, 0.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			drawCir(main_shaft_radius_4, cir_W4, 16);
		}
		glPopMatrix();
		glPushMatrix();//(�ꪺ���|��24)
		{
			glTranslatef(main_shaft_W1/2.0f+main_shaft_W2+cir_W1+cir_W2+cir_W3+cir_W4+cir_W5/2.0f, 0.0f, 0.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			drawCir(main_shaft_radius_5, cir_W5, 16);
		}
		glPopMatrix();
		glRotatef(count, 1.0f, 0.0f, 0.0f);///***********************///
		glPushMatrix();//(�ꪺ���|��10)
		{
			glTranslatef(main_shaft_W1/2.0f+main_shaft_W2+cir_W1+cir_W2+cir_W3+cir_W4+cir_W5+cir_W6/2.0f, 0.0f, 0.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			drawCir(main_shaft_radius_6, cir_W6, 16);
		}
		glPopMatrix();
		glPushMatrix();//(�ꪺ���|��152.4)
		{
			glTranslatef(main_shaft_W1/2.0f+main_shaft_W2+cir_W1+cir_W2+cir_W3+cir_W4+cir_W5+cir_W6+cir_W7/2.0f, 0.0f, 0.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			glColor3ub(10.0f,150.0f,10.0f);
			drawCir(main_shaft_radius_7, cir_W7, 16);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void CNewView::motor()//���F
{
	glPushMatrix();//��W���b�|��25
	{
		glColor3ub(50.0f,50.0f,50.0f);
		drawRetc(motor_W1, motor_L1, motor_H1);
		glPushMatrix();//��W���b�|��25
		{
			glTranslatef(0.0f, 0.0f, -motor_H1/2.0f-motor_cir_H1/2.0f);
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			glColor3ub(50.0f,50.0f,50.0f);
			drawCir(motor_radius_1, motor_cir_H1, 16);
		}
		glPopMatrix();

		glPushMatrix();//��W���b�|��6.98
		{
			glTranslatef(0.0f, 0.0f, -motor_H1/2.0f-motor_cir_H1-motor_cir_H2/2.0f);
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			drawCir(motor_radius_2, motor_cir_H2, 16);
		}
		glPopMatrix();
	}
	glPopMatrix();

}
///////////////////////////////////////////////////////////////////////////
//////�����
void CNewView::OnshiftX() 
{
	// TODO: Add your command handler code here
	switch_value=1;
}

void CNewView::OnshiftY() 
{
	// TODO: Add your command handler code here
	switch_value=2;
}

void CNewView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	/*
	switch(switch_value)
	{
		case 0:
			break;		
		case 1:
			if(shiftXValue<=30 && shiftX_switch==0)
				shiftXValue+=1.0f/3.0f;
			else
				shiftX_switch=1;
			
			if(shiftXValue>=-30 && shiftX_switch==1)
				shiftXValue-=1.0f/3.0f;
			else
				shiftX_switch=0;

			break;
		case 2:
			if(shiftYValue<=30 && shiftY_switch==0)
				shiftYValue+=1.0f/3.0f;
			else
				shiftY_switch=1;
			
			if(shiftYValue>=-30 && shiftY_switch==1)
				shiftYValue-=1.0f/3.0f;
			else
				shiftY_switch=0;
			break;
		case 3:
			if(shiftZValue<=30 && shiftZ_switch==0)
				shiftZValue+=1.0f/3.0f;
			else
				shiftZ_switch=1;
			
			if(shiftZValue>=-30 && shiftZ_switch==1)
				shiftZValue-=1.0f/3.0f;
			else
				shiftZ_switch=0;
			break;
		case 4:
			if(WatchRotate<=30 && Watch_switch==0)
				WatchRotate+=1.0f/3.0f;
			else
				Watch_switch=1;
			
			if(WatchRotate>=-30 && Watch_switch==1)
				WatchRotate-=1.0f/3.0f;
			else
				Watch_switch=0;
			break;
	}
	*/
	//////////////////////////
	if(Front_Flag)
		FrontRun ();
	if(Flank_Flag)
		FlankRun ();
	if(Front1_Flag)
		Front1Run ();
	if(Flank1_Flag)
		Flank1Run();
	shiftXValue=Ymove*-1.0f;
	shiftYValue=Xmove*-1.0f;
	shiftZValue=Zmove*-1.0f;
	WatchRotate=Theta1;
	WatchRotate1=Theta2*-1.0f;
	viewbar1.showdata(Xmove,Ymove,Zmove,Theta1,Theta2, Pxr3, Pyr3, Pzr3, Theta);
	/////////////////////////
	count +=30.0f;//��������
	Invalidate(true);//�^��ø�ϰ�
	
	CView::OnTimer(nIDEvent);
}

void CNewView::OnTimerStart() 
{
	// TODO: Add your command handler code here
	switch_value=0;
	viewbar1.show();
	SetTimer(1,100,NULL);
}

void CNewView::OnshiftZ() 
{
	// TODO: Add your command handler code here
	switch_value=3;
}
//////////////////////////////////////////////////////////////////////////////

void CNewView::OnwatchR() 
{
	// TODO: Add your command handler code here
	switch_value=4;
}

void CNewView::FrontRun () //////////////////////////////////////�������i��k1
{
	int Theta11 = 90.0f;//�Ĥ@�ӱ���b�n�઺����
	int Theta12 = 90.0f;//�ĤG�ӱ���b�n�઺����
	int Theta21 = 90.0f;//�Ĥ@�ӱ���b�n�઺����
	int Theta22 = 90.0f;//�ĤG�ӱ���b�n�઺����
	switch(Front_Index)
	{
	case 1:///////////////////////////////////////////////���w���Ĥ@�ӱ�Ĳ�I
		Theta_Front = -16.128f;
		if((Theta1 >= Theta11) && (Theta2 >= Theta12))///////�ˬd�Ĥ@�M�ĤG����b�O�_����w����m�F
		{
			Front_Index = 2;
		}
		else
		{
			if(Theta1 < Theta11)
			{
				Theta1 += Theta11/30.0f;//����3����
			}
			if(Theta2 < Theta12)
			{
				Theta2 += Theta12/30.0f;
			}
			Pxr3 = 90.0f*sin(Theta_Front*d2r);
			Pyr3 = -14.25f;
			Pzr3 = 90.0f*cos(Theta_Front*d2r)-47.0f;
			Xmove += (-Pxr3*cos(Theta11*d2r)*cos(Theta12*d2r)+Pyr3*cos(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*sin(Theta11*d2r)-dr2*sin(Theta11*d2r)-Xroffset-Pz3-d2+Xoffset)/30.0f;
			Ymove += (Pxr3*sin(Theta12*d2r)+Pyr3*cos(Theta12*d2r)+dr1+Yroffset-Px3-Yoffset)/30.0f;
			Zmove += (Pxr3*sin(Theta11*d2r)*cos(Theta12*d2r)-Pyr3*sin(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*cos(Theta11*d2r)-dr2*cos(Theta11*d2r)-Zroffset-Py3+Zoffset)/30.0f;
		}

		break;
	case 2://///////////////////////////////////////////�}�l���������i
		if(Theta_Front < 16.128f)
			Theta_Front += (2.0*16.128f)/50.0f;
		else 
			Front_Index = 3;
		Pxr3 = 90.0f*sin(Theta_Front*d2r);
		Pyr3 = -14.25f;
		Pzr3 = 90.0f*cos(Theta_Front*d2r)-47.0f;
		Xmove = -Pxr3*cos(Theta11*d2r)*cos(Theta12*d2r)+Pyr3*cos(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*sin(Theta11*d2r)-dr2*sin(Theta11*d2r)-Xroffset-Pz3-d2+Xoffset;
		Ymove = Pxr3*sin(Theta12*d2r)+Pyr3*cos(Theta12*d2r)+dr1+Yroffset-Px3-Yoffset;
		Zmove = Pxr3*sin(Theta11*d2r)*cos(Theta12*d2r)-Pyr3*sin(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*cos(Theta11*d2r)-dr2*cos(Theta11*d2r)-Zroffset-Py3+Zoffset;
		break;
	case 3:////////////////////////////////////////////���������i
		if(Theta_Front > -16.128f)
			Theta_Front -= (2.0*16.128f)/50.0f;
		else 
			Front_Index = 4;
		Pxr3 = 90.0f*sin(Theta_Front*d2r);
		Pyr3 = -14.25f;
		Pzr3 = 90.0f*cos(Theta_Front*d2r)-47.0f;
		Xmove = -Pxr3*cos(Theta11*d2r)*cos(Theta12*d2r)+Pyr3*cos(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*sin(Theta11*d2r)-dr2*sin(Theta11*d2r)-Xroffset-Pz3-d2+Xoffset;
		Ymove = Pxr3*sin(Theta12*d2r)+Pyr3*cos(Theta12*d2r)+dr1+Yroffset-Px3-Yoffset;
		Zmove = Pxr3*sin(Theta11*d2r)*cos(Theta12*d2r)-Pyr3*sin(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*cos(Theta11*d2r)-dr2*cos(Theta11*d2r)-Zroffset-Py3+Zoffset;
		break;
	case 4:///////////////////////////////////////////���I�_�k
		Theta_Front = -16.128f;
		if((Theta1 <= 0.0f) && (Theta2 <= 0.0f))
		{
			Front_Index = 5;
		}
		else
		{
			if(Theta1 > 0.0f)
			{
				Theta1 -= Theta21/30.0f;
			}
			if(Theta2 > 0.0f)
			{
				Theta2 -= Theta22/30.0f;
			}
			Pxr3 = 90.0f*sin(Theta_Front*d2r);
			Pyr3 = -14.25f;
			Pzr3 = 90.0f*cos(Theta_Front*d2r)-47.0f;
			Xmove -= (-Pxr3*cos(Theta21*d2r)*cos(Theta22*d2r)+Pyr3*cos(Theta21*d2r)*sin(Theta22*d2r)-Pzr3*sin(Theta21*d2r)-dr2*sin(Theta21*d2r)-Xroffset-Pz3-d2+Xoffset)/30.0f;
			Ymove -= (Pxr3*sin(Theta22*d2r)+Pyr3*cos(Theta22*d2r)+dr1+Yroffset-Px3-Yoffset)/30.0f;
			Zmove -= (Pxr3*sin(Theta21*d2r)*cos(Theta22*d2r)-Pyr3*sin(Theta21*d2r)*sin(Theta22*d2r)-Pzr3*cos(Theta21*d2r)-dr2*cos(Theta21*d2r)-Zroffset-Py3+Zoffset)/30.0f;
		}

		break;
	}

}

void CNewView::FlankRun () ////////////////////////////////////////////////////////////////////////////////////////////////////////�������i��k1
{
	int Theta11 = 0.0f;//�Ĥ@�ӱ���b�n�઺����
	int Theta12 = 90.0f;//�ĤG�ӱ���b�n�઺����
	int Theta21 = 0.0f;//�Ĥ@�ӱ���b�n�઺����
	int Theta22 = 90.0f;//�ĤG�ӱ���b�n�઺����
	switch(Flank_Index)
	{
	case 1://////////////////////////////////////////////���w���Ĥ@�ӱ�Ĳ�I
		Theta_Flank = -18.21f;
		if((Theta1 >= Theta11) && (Theta2 >= Theta12))//�ˬd�Ĥ@�M�ĤG����b�O�_����w����m�F
		{
			Flank_Index = 2;
		}
		else
		{
			if(Theta1 < Theta11)
			{
				Theta1 += Theta11/30.0f;
			}
			if(Theta2 < Theta12)
			{
				Theta2 += Theta12/30.0f;
			}
			Pxr3 = 80.0f*sin(Theta_Flank*d2r);
			Pyr3 = -80.0f*cos(Theta_Flank*d2r)+60.0f;
			Pzr3 = 38.0f;
			Xmove += (-Pxr3*cos(Theta11*d2r)*cos(Theta12*d2r)+Pyr3*cos(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*sin(Theta11*d2r)-dr2*sin(Theta11*d2r)-Xroffset-Pz3-d2+Xoffset)/30.0f;
			Ymove += (Pxr3*sin(Theta12*d2r)+Pyr3*cos(Theta12*d2r)+dr1+Yroffset-Px3-Yoffset)/30.0f;
			Zmove += (Pxr3*sin(Theta11*d2r)*cos(Theta12*d2r)-Pyr3*sin(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*cos(Theta11*d2r)-dr2*cos(Theta11*d2r)-Zroffset-Py3+Zoffset)/30.0f;
		}
		break;
	case 2://////////////////////////////////////////////////////////////�}�l���������i
		if(Theta_Flank < 18.21f)
			Theta_Flank += (2.0*18.21f)/50.0f;
		else 
			Flank_Index = 3;
		Pxr3 = 80.0f*sin(Theta_Flank*d2r);
		Pyr3 = -80.0f*cos(Theta_Flank*d2r)+60.0f;
		Pzr3 = 38.0f;
		Xmove = -Pxr3*cos(Theta11*d2r)*cos(Theta12*d2r)+Pyr3*cos(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*sin(Theta11*d2r)-dr2*sin(Theta11*d2r)-Xroffset-Pz3-d2+Xoffset;
		Ymove = Pxr3*sin(Theta12*d2r)+Pyr3*cos(Theta12*d2r)+dr1+Yroffset-Px3-Yoffset;
		Zmove = Pxr3*sin(Theta11*d2r)*cos(Theta12*d2r)-Pyr3*sin(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*cos(Theta11*d2r)-dr2*cos(Theta11*d2r)-Zroffset-Py3+Zoffset;
		break;
	case 3://///////////////////////////////////////////////////////////���������i
		if(Theta_Flank > -18.21f)
			Theta_Flank -= (2.0*18.21f)/50.0f;
		else 
			Flank_Index = 4;
		Pxr3 = 80.0f*sin(Theta_Flank*d2r);
		Pyr3 = -80.0f*cos(Theta_Flank*d2r)+60.0f;
		Pzr3 = 38.0f;
		Xmove = -Pxr3*cos(Theta11*d2r)*cos(Theta12*d2r)+Pyr3*cos(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*sin(Theta11*d2r)-dr2*sin(Theta11*d2r)-Xroffset-Pz3-d2+Xoffset;
		Ymove = Pxr3*sin(Theta12*d2r)+Pyr3*cos(Theta12*d2r)+dr1+Yroffset-Px3-Yoffset;
		Zmove = Pxr3*sin(Theta11*d2r)*cos(Theta12*d2r)-Pyr3*sin(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*cos(Theta11*d2r)-dr2*cos(Theta11*d2r)-Zroffset-Py3+Zoffset;
		break;
	case 4:////////////////////////////////////////////////////////////���I�_�k
		Theta_Flank = -18.21f;
		if((Theta1 <= 0.0f) && (Theta2 <= 0.0f))
		{
			Flank_Index = 5;
		}
		else
		{
			if(Theta1 > 0.0f)
			{
				Theta1 -= Theta21/30.0f;
			}
			if(Theta2 > 0.0f)
			{
				Theta2 -= Theta22/30.0f;
			}
			Pxr3 = 80.0f*sin(Theta_Flank*d2r);
			Pyr3 = -80.0f*cos(Theta_Flank*d2r)+60.0f;
			Pzr3 = 38.0f;
			Xmove -= (-Pxr3*cos(Theta21*d2r)*cos(Theta22*d2r)+Pyr3*cos(Theta21*d2r)*sin(Theta22*d2r)-Pzr3*sin(Theta21*d2r)-dr2*sin(Theta21*d2r)-Xroffset-Pz3-d2+Xoffset)/30.0f;
			Ymove -= (Pxr3*sin(Theta22*d2r)+Pyr3*cos(Theta22*d2r)+dr1+Yroffset-Px3-Yoffset)/30.0f;
			Zmove -= (Pxr3*sin(Theta21*d2r)*cos(Theta22*d2r)-Pyr3*sin(Theta21*d2r)*sin(Theta22*d2r)-Pzr3*cos(Theta21*d2r)-dr2*cos(Theta21*d2r)-Zroffset-Py3+Zoffset)/30.0f;
		}

		break;
	}

}

void CNewView::Front1Run () ////////////////////////////////////////////////////�������i��k2
{
	int Theta11 = 90.0f;//�Ĥ@�ӱ���b�n�઺����
	int Theta12 =  0.0f;//�ĤG�ӱ���b�n�઺����
	int Theta21 = 90.0f;//�Ĥ@�ӱ���b�n�઺����
	int Theta22 =  0.0f;//�ĤG�ӱ���b�n�઺����
	switch(Front1_Index)
	{
	case 1:////////////////////////////////////////////////���w���Ĥ@�ӱ�Ĳ�I
		Theta_Front = 0.0f;
		if((Theta1 >= Theta11) && (Theta2 >= Theta12))//�ˬd�Ĥ@�M�ĤG����b�O�_����w����m�F
		{
			Front1_Index = 2;
		}
		else
		{
			if(Theta1 < Theta11)
			{
				Theta1 += Theta11/30.0f;
			}
			if(Theta2 < Theta12)
			{
				Theta2 += Theta12/30.0f;
			}
			Pxr3 = 90.0f*sin(Theta_Front*d2r);
			Pyr3 = 0.0f;
			Pzr3 = 90.0f*cos(Theta_Front*d2r)-47.0f;
			
			Xmove += (-Pxr3*cos(Theta11*d2r)*cos(Theta12*d2r)+Pyr3*cos(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*sin(Theta11*d2r)-dr2*sin(Theta11*d2r)-Xroffset-Pz3-d2+Xoffset)/30.0f;
			Ymove += (Pxr3*sin(Theta12*d2r)+Pyr3*cos(Theta12*d2r)+dr1+Yroffset-Px3-Yoffset)/30.0f;
			Zmove += (Pxr3*sin(Theta11*d2r)*cos(Theta12*d2r)-Pyr3*sin(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*cos(Theta11*d2r)-dr2*cos(Theta11*d2r)-Zroffset-Py3+Zoffset)/30.0f;
		}

		break;
	case 2: ///////////////////////////////////////////////////////////////�}�l���������i
		if(Theta_Front < 16.128f)
		{
			Theta_Front += (1.0*16.128f)/50.0f;
			Pxr3 = 90.0f*sin(Theta_Front*d2r);
			Pyr3 = 0.0f;
			Pzr3 = 90.0f*cos(Theta_Front*d2r)-47.0f;
			Theta1 = Theta11-1/d2r*atan(Pxr3/(Pzr3+dr2));
			Theta2 = Theta12;
			Xmove = -Pxr3*cos(Theta1*d2r)*cos(Theta2*d2r)+Pyr3*cos(Theta1*d2r)*sin(Theta2*d2r)-Pzr3*sin(Theta1*d2r)-dr2*sin(Theta1*d2r)-Xroffset-Pz3-d2+Xoffset;
			Ymove = Pxr3*sin(Theta2*d2r)+Pyr3*cos(Theta2*d2r)+dr1+Yroffset-Px3-Yoffset;
			Zmove = Pxr3*sin(Theta1*d2r)*cos(Theta2*d2r)-Pyr3*sin(Theta1*d2r)*sin(Theta2*d2r)-Pzr3*cos(Theta1*d2r)-dr2*cos(Theta1*d2r)-Zroffset-Py3+Zoffset;
		}
		else 
		{
			Front1_Index = 3;
		}
		break;
	case 3:///////////////////////////////////////////////////////////////���������i
		if(Theta_Front > -16.128f)
		{
			Theta_Front -= (2.0*16.128f)/100.0f;
			Pxr3 = 90.0f*sin(Theta_Front*d2r);
			Pyr3 = 0.0f;
			Pzr3 = 90.0f*cos(Theta_Front*d2r)-47.0f;
			Theta1 = Theta11-1/d2r*atan(Pxr3/(Pzr3+dr2));
			Theta2 = Theta12;
			Xmove = -Pxr3*cos(Theta1*d2r)*cos(Theta2*d2r)+Pyr3*cos(Theta1*d2r)*sin(Theta2*d2r)-Pzr3*sin(Theta1*d2r)-dr2*sin(Theta1*d2r)-Xroffset-Pz3-d2+Xoffset;
			Ymove = Pxr3*sin(Theta2*d2r)+Pyr3*cos(Theta2*d2r)+dr1+Yroffset-Px3-Yoffset;
			Zmove = Pxr3*sin(Theta1*d2r)*cos(Theta2*d2r)-Pyr3*sin(Theta1*d2r)*sin(Theta2*d2r)-Pzr3*cos(Theta1*d2r)-dr2*cos(Theta1*d2r)-Zroffset-Py3+Zoffset;
		}
		else
		{
			Front1_Index = 4;
		}
		break;
	case 4://////////////////////////////////////////////////////////////�k��
		if(Theta_Front < 0.0f)
		{
			Theta_Front += (1.0*16.128f)/50.0f;
			Pxr3 = 90.0f*sin(Theta_Front*d2r);
			Pyr3 = 0.0f;
			Pzr3 = 90.0f*cos(Theta_Front*d2r)-47.0f;
			Theta1 = Theta11-1/d2r*atan(Pxr3/(Pzr3+dr2));
			Theta2 = Theta12;
			Xmove = -Pxr3*cos(Theta1*d2r)*cos(Theta2*d2r)+Pyr3*cos(Theta1*d2r)*sin(Theta2*d2r)-Pzr3*sin(Theta1*d2r)-dr2*sin(Theta1*d2r)-Xroffset-Pz3-d2+Xoffset;
			Ymove = Pxr3*sin(Theta2*d2r)+Pyr3*cos(Theta2*d2r)+dr1+Yroffset-Px3-Yoffset;
			Zmove = Pxr3*sin(Theta1*d2r)*cos(Theta2*d2r)-Pyr3*sin(Theta1*d2r)*sin(Theta2*d2r)-Pzr3*cos(Theta1*d2r)-dr2*cos(Theta1*d2r)-Zroffset-Py3+Zoffset;
		}
		else 
		{
			Front1_Index = 5;
		}
		break;
	case 5://///////////////////////////////////////////////////////////���I�_�k
		Theta_Front = 0.0f;
		if((Theta1 <= 0.0f) && (Theta2 <= 0.0f))
		{
			Front1_Index = 6;
		}
		else
		{
			if(Theta1 > 0.0f)
			{
				Theta1 -= Theta21/30.0f;
			}
			if(Theta2 > 0.0f)
			{
				Theta2 -= Theta22/30.0f;
			}
			Pxr3 = 90.0f*sin(Theta_Front*d2r);
			Pyr3 = 0.0f;
			Pzr3 = 90.0f*cos(Theta_Front*d2r)-47.0f;
			
			Xmove -= (-Pxr3*cos(Theta11*d2r)*cos(Theta12*d2r)+Pyr3*cos(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*sin(Theta11*d2r)-dr2*sin(Theta11*d2r)-Xroffset-Pz3-d2+Xoffset)/30.0f;
			Ymove -= (Pxr3*sin(Theta12*d2r)+Pyr3*cos(Theta12*d2r)+dr1+Yroffset-Px3-Yoffset)/30.0f;
			Zmove -= (Pxr3*sin(Theta11*d2r)*cos(Theta12*d2r)-Pyr3*sin(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*cos(Theta11*d2r)-dr2*cos(Theta11*d2r)-Zroffset-Py3+Zoffset)/30.0f;
		}

		break;



	}

}

void CNewView::Flank1Run () ////////////////////////////////////////////////////�������i��k2
{
	int Theta11 =  0.0f;//�Ĥ@�ӱ���b�n�઺����
	int Theta12 = 90.0f;//�ĤG�ӱ���b�n�઺����
	int Theta21 =  0.0f;//�Ĥ@�ӱ���b�n�઺����
	int Theta22 = 90.0f;//�ĤG�ӱ���b�n�઺����
	switch(Flank1_Index)
	{
	case 1:////////////////////////////////////////////////////////////���w���Ĥ@�ӱ�Ĳ�I
		Theta_Flank = 0.0f;
		if((Theta1 >= Theta11) && (Theta2 >= Theta12))
		{
			Flank1_Index = 2;
		}
		else
		{
			if(Theta1 < Theta11)
			{
				Theta1 += Theta11/30.0f;
			}
			if(Theta2 < Theta12)
			{
				Theta2 += Theta12/30.0f;
			}
			Pxr3 = 80.0f*sin(Theta_Flank*d2r);
			Pyr3 = -80.0f*cos(Theta_Flank*d2r)+60.0f;
			Pzr3 = 38.0f;
			
			Xmove += (-Pxr3*cos(Theta11*d2r)*cos(Theta12*d2r)+Pyr3*cos(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*sin(Theta11*d2r)-dr2*sin(Theta11*d2r)-Xroffset-Pz3-d2+Xoffset)/30.0f;
			Ymove += (Pxr3*sin(Theta12*d2r)+Pyr3*cos(Theta12*d2r)+dr1+Yroffset-Px3-Yoffset)/30.0f;
			Zmove += (Pxr3*sin(Theta11*d2r)*cos(Theta12*d2r)-Pyr3*sin(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*cos(Theta11*d2r)-dr2*cos(Theta11*d2r)-Zroffset-Py3+Zoffset)/30.0f;
		}

		break;
	case 2:///////////////////////////////////////////////////////////////�}�l���������i
		if(Theta_Flank < 18.21f)
		{
			Theta_Flank += (1.0*18.21)/50.0f;
			
			Pxr3 = 80.0f*sin(Theta_Flank*d2r);
			Pyr3 = -80.0f*cos(Theta_Flank*d2r)+60.0f;
			Pzr3 = 38.0f;

			Theta1 = Theta11;
			Theta2 = Theta12-1/d2r*atan(Pxr3/(-Pyr3));
			
			Xmove = -Pxr3*cos(Theta1*d2r)*cos(Theta2*d2r)+Pyr3*cos(Theta1*d2r)*sin(Theta2*d2r)-Pzr3*sin(Theta1*d2r)-dr2*sin(Theta1*d2r)-Xroffset-Pz3-d2+Xoffset;
			Ymove = Pxr3*sin(Theta2*d2r)+Pyr3*cos(Theta2*d2r)+dr1+Yroffset-Px3-Yoffset;
			Zmove = Pxr3*sin(Theta1*d2r)*cos(Theta2*d2r)-Pyr3*sin(Theta1*d2r)*sin(Theta2*d2r)-Pzr3*cos(Theta1*d2r)-dr2*cos(Theta1*d2r)-Zroffset-Py3+Zoffset;
		}
		else 
		{
			Flank1_Index = 3;
		}
		break;
	case 3:///////////////////////////////////////////////////////////////���������i
		if(Theta_Flank > -18.21f)
		{
			Theta_Flank -= (2.0*18.21f)/100.0f;
			
			Pxr3 = 80.0f*sin(Theta_Flank*d2r);
			Pyr3 = -80.0f*cos(Theta_Flank*d2r)+60.0f;
			Pzr3 = 38.0f;
			
			Theta1 = Theta11;
			Theta2 = Theta12-1/d2r*atan(Pxr3/(-Pyr3));
			
			Xmove = -Pxr3*cos(Theta1*d2r)*cos(Theta2*d2r)+Pyr3*cos(Theta1*d2r)*sin(Theta2*d2r)-Pzr3*sin(Theta1*d2r)-dr2*sin(Theta1*d2r)-Xroffset-Pz3-d2+Xoffset;
			Ymove = Pxr3*sin(Theta2*d2r)+Pyr3*cos(Theta2*d2r)+dr1+Yroffset-Px3-Yoffset;
			Zmove = Pxr3*sin(Theta1*d2r)*cos(Theta2*d2r)-Pyr3*sin(Theta1*d2r)*sin(Theta2*d2r)-Pzr3*cos(Theta1*d2r)-dr2*cos(Theta1*d2r)-Zroffset-Py3+Zoffset;
		}
		else
		{
			Flank1_Index = 4;
		}
		break;
	case 4://////////////////////////////////////////////////////////////�k��
		if(Theta_Flank < 0.0f)
		{
			Theta_Flank += (1.0*18.21f)/50.0f;
			
			Pxr3 = 80.0f*sin(Theta_Flank*d2r);
			Pyr3 = -80.0f*cos(Theta_Flank*d2r)+60.0f;
			Pzr3 = 38.0f;
			
			Theta1 = Theta11;
			Theta2 = Theta12-1/d2r*atan(Pxr3/(-Pyr3));

			Xmove = -Pxr3*cos(Theta1*d2r)*cos(Theta2*d2r)+Pyr3*cos(Theta1*d2r)*sin(Theta2*d2r)-Pzr3*sin(Theta1*d2r)-dr2*sin(Theta1*d2r)-Xroffset-Pz3-d2+Xoffset;
			Ymove = Pxr3*sin(Theta2*d2r)+Pyr3*cos(Theta2*d2r)+dr1+Yroffset-Px3-Yoffset;
			Zmove = Pxr3*sin(Theta1*d2r)*cos(Theta2*d2r)-Pyr3*sin(Theta1*d2r)*sin(Theta2*d2r)-Pzr3*cos(Theta1*d2r)-dr2*cos(Theta1*d2r)-Zroffset-Py3+Zoffset;
		}
		else 
		{
			Flank1_Index = 5;
		}
		break;
	case 5://///////////////////////////////////////////////////////////���I�_�k
		Theta_Flank = 0.0f;
		if((Theta1 <= 0.0f) && (Theta2 <= 0.0f))
		{
			Flank1_Index = 6;
		}
		else
		{
			if(Theta1 > 0.0f)
			{
				Theta1 -= Theta21/30.0f;
			}
			if(Theta2 > 0.0f)
			{
				Theta2 -= Theta22/30.0f;
			}
			Pxr3 = 80.0f*sin(Theta_Flank*d2r);
			Pyr3 = -80.0f*cos(Theta_Flank*d2r)+60.0f;
			Pzr3 = 38.0f;
			
			Xmove -= (-Pxr3*cos(Theta11*d2r)*cos(Theta12*d2r)+Pyr3*cos(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*sin(Theta11*d2r)-dr2*sin(Theta11*d2r)-Xroffset-Pz3-d2+Xoffset)/30.0f;
			Ymove -= (Pxr3*sin(Theta12*d2r)+Pyr3*cos(Theta12*d2r)+dr1+Yroffset-Px3-Yoffset)/30.0f;
			Zmove -= (Pxr3*sin(Theta11*d2r)*cos(Theta12*d2r)-Pyr3*sin(Theta11*d2r)*sin(Theta12*d2r)-Pzr3*cos(Theta11*d2r)-dr2*cos(Theta11*d2r)-Zroffset-Py3+Zoffset)/30.0f;
		}

		break;



	}

}

void CNewView::OnBar() 
{
	// TODO: Add your command handler code here
	viewbar1.show();
}  

///��������(5)

void CNewView::OnFront() 
{
	// TODO: Add your command handler code here
		
	Front_Flag = true;
	Flank_Flag = false;
	Front1_Flag = false;
	Flank1_Flag = false;
	Front_Index = 1;
	Flank_Index = 1;
	Front1_Index =1;
	Flank1_Index = 1;
	Xmove = 0.0f;
	Ymove = 0.0f;
	Zmove = 0.0f;
	Theta1 = 0.0f;
	Theta2 = 0.0f;
	Px3 = 0.0f;
	Py3 = 40.0f;
	Pz3 = 40.0f;
}

void CNewView::OnFlank() 
{
	// TODO: Add your command handler code here
	Front_Flag = false;
	Flank_Flag = true;
	Front1_Flag = false;
	Flank1_Flag = false;
	Front_Index = 1;
	Flank_Index = 1;
	Front1_Index =1;
	Flank1_Index = 1;
	Xmove = 0.0f;
	Ymove = 0.0f;
	Zmove = 0.0f;
	Theta1 = 0.0f;
	Theta2 = 0.0f;
	Px3 = 0.0f;
	Py3 = 40.0f;
	Pz3 = 40.0f;	
}

void CNewView::OnFront1() 
{
	// TODO: Add your command handler code here
	Front_Flag = false;
	Flank_Flag = false;
	Front1_Flag = true;
	Flank1_Flag = false;
	Front_Index = 1;
	Flank_Index = 1;
	Front1_Index =1;
	Flank1_Index = 1;
	Xmove = 0.0f;
	Ymove = 0.0f;
	Zmove = 0.0f;
	Theta1 = 0.0f;
	Theta2 = 0.0f;
	Px3 =-40.0f;
	Py3 = 0.0f;
	Pz3 = 40.0f;	
}

void CNewView::OnFlank1() 
{
	// TODO: Add your command handler code here
	Front_Flag = false;
	Flank_Flag = false;
	Front1_Flag = false;
	Flank1_Flag = true;
	Front_Index = 1;
	Flank_Index = 1;
	Front1_Index = 1;
	Flank1_Index = 1;
	Xmove = 0.0f;
	Ymove = 0.0f;
	Zmove = 0.0f;
	Theta1 = 0.0f;
	Theta2 = 0.0f;
	Px3 = 0.0f;
	Py3 = 40.0f;
	Pz3 = 40.0f;
}
