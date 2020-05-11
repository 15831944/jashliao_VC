#ifndef __OPENGLPARA_H__
#define __OPENGLPARA_H__
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
//=========	�t�ΰѼƳ]�w =========//

// ����Ѽ�
static GLfloat xRot = 285.0f;		// X�b��������Ѽ�
static GLfloat yRot = 0.0f;		// Y�b��������Ѽ�
static GLfloat zRot = 50.0f;		// Z�b��������Ѽ�

// ������u�첾�P��ʰѼ�
static GLfloat X_shift = 0.0f;//�e-��
static GLfloat Y_shift = 0.0f;//��-�k
static GLfloat Rotate1 = 0.0f; //yaw
static GLfloat Rotate2 = 0.0f;//pitch
static GLfloat Rotate3 = 0.0f;//row

static GLfloat Grinder_Rotate = 0.0f;

static GLfloat xView = 0.0f;
static GLfloat yView = -500.0f;
static GLfloat zView = 300.0f;

static	GLfloat nRange = 600.0f;//�Ŷ��j�p



//=== ���c����Ѽ�(���mm)
// ���y
static GLfloat Base_W = 500.0f;
static GLfloat Base_L = 1000.0f;
static GLfloat Base_H =  20.0f;
// ���y
// X�b
static GLfloat X_axis_W = 500.0f;	//(Base_W)
static GLfloat X_axis_L =  70.0f;
static GLfloat X_axis_H =  50.0f;	//(Y_axis_H)
// X�b
// Y�b
static GLfloat Y_axis_W =  70.0f;
static GLfloat Y_axis_L = 1000.0f;	//(Base_L)
static GLfloat Y_axis_H =  50.0f;	//(X_axis_H)
// Y�b
// Servo Motor 1
static GLfloat SM1_Bottom_W = 50.0f;	//(SM_Bottom_L)
static GLfloat SM1_Bottom_L = 50.0f;	//(SM_Bottom_W)
static GLfloat SM1_Bottom_H = 30.0f;
static GLfloat SM1_Middle_R = 25.0f;	//(SM1_Bottom_W/2)
static GLfloat SM1_Middle_L = 40.0f;	 
static GLfloat SM1_Top_R = 20.0f;
static GLfloat SM1_Top_L = 20.0f;		//(SM1_Middle_L/2)
// Servo Motor 1
// Link1-1
static GLfloat Link11_W = 70.0f;		//(Y_axis_W)
static GLfloat Link11_L = 70.0f;		//(Link11_L)
static GLfloat Link11_H = 70.0f;		
// Link1-1
// Bar1-1
static GLfloat Bar11_R = 35.0f;			//(Link11_W/2)
static GLfloat Bar11_L = 100.0f;		
// Bar1-1
// Link1-2
static GLfloat Link12_W = 70.0f;		//(Bar11_R*2)
static GLfloat Link12_L = 70.0f;		//(Link12_W)
static GLfloat Link12_H = 70.0f;		//(Link12_W)
// Link1-2	
// Bar1-2
static GLfloat Bar12_R = 25.0f;			
static GLfloat Bar12_L = 70.0f;
// Bar1-2
// Link2
static GLfloat Link2_W = 100.0f;		
static GLfloat Link2_L = 25.0f*2;		//(Bar12_R*2)
static GLfloat Link2_H = 25.0f*2;		//(Link2_L)
// Link2
// Loadcell
static GLfloat Loadcell1_R = 25.0f;		//(Link2_L/2)
static GLfloat Loadcell1_L = 20.0f;			
static GLfloat Loadcell2_R = 20.0f;
static GLfloat Loadcell2_L = 10.0f;
// Loadcell
// Fixture
static GLfloat Fixture1_R = 54.5f/2;
static GLfloat Fixture1_L = 6.0f;
static GLfloat Fixture2_R = 35.0f/2;
static GLfloat Fixture2_L = 30.0f;
// Fixture
// Grinder Base
static GLfloat GrinderHold_Base_W = 300.0f;		
static GLfloat GrinderHold_Base_L = 1000.0f;	//(Base_L)
static GLfloat GrinderHold_Base_H = 325.0f;		//(Base_H+X_axis_H+Y_axis_H+Link11_H+Bar11_H+Link12_H/2)
static GLfloat GrinderHold1_R =  25.4f;
static GLfloat GrinderHold1_L = 300.0f;			//(GrinderHold_Base_W)
static GLfloat GrinderHold2_W = 300.0f;			//(GrinderHold_Base_W)
static GLfloat GrinderHold2_L = 1000.0f-2*25.4f;//(Base_L-2*GrinderHold1_R)
static GLfloat GrinderHold2_H = 25.4f;			//(GrinderHold1_R)
// Grinder Base
// Grinder
static GLfloat Grinder_init_shift =401.0f;	//(Y_axis_W/2+Link2_W+Loadcell1_L+Loadcell2_L+Fixture1_L+Fixture2_L+Grinder_R)
static GLfloat Grinder_Bar_R = 15.0f;
static GLfloat Grinder_Bar_L = 400.0f;			//(GrinderHold_Base_W+***.*f)
static GLfloat Grinder_R = 400.0f/2;				
static GLfloat Grinder_L = 30.0f;
static GLfloat Grinder_Bar_Distance = 250.0f;
static GLfloat Grinder_Distance = 70.0f;
// Grinder
// Watch Model
static GLfloat Watch1_1_W = 20.0f;
static GLfloat Watch1_1_L = 100.0f;
static GLfloat Watch1_1_H = 20.0f;
static GLfloat Watch1_2_W = 50.0f;
static GLfloat Watch1_2_L = 20.0f;
static GLfloat Watch1_2_H = 20.0f;
// Watch Model


// �O���Ѽ�
static GLfloat  ambientLight[]	= { 0.8f, 0.8f, 1.0f, 1.0f };	
static GLfloat  diffuseLight[]	= { 0.7f, 0.7f, 0.7f, 1.0f };
static GLfloat  specular[]		= { 0.7f, 0.7f, 0.7f, 1.0f };	//�O���ʽ�
static GLfloat  specref []		= { 0.5f, 0.5f, 0.2f, 1.0f };	//�Ϯg�ʽ�
static GLfloat	lightPos[]		= { 1000.0f, 1000.0f, 1000.0f, 1.0f}; 

// �X�аѼ�
static BOOL Line_flag = FALSE;
static BOOL View_lock = TRUE;
int View_flag = 5;						// �Ѽ�(�w�]���������)
#define Up_View    1				// �W����
#define Front_View 2				// �e����
#define Back_View  3				// �����
#define Right_View 4				// �k����
#define Left_View  5				// ������
#define Orign_View 6				// �����
#endif