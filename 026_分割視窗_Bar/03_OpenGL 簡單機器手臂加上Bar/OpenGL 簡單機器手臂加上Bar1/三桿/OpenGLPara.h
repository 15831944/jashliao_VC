#ifndef __OPENGLPARA_H__
#define __OPENGLPARA_H__
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
//=========	�t�ΰѼƳ]�w =========//

// ����Ѽ�
static GLfloat xRot = 0.0f;		// X�b��������Ѽ�
static GLfloat yRot = 0.0f;		// Y�b��������Ѽ�
static GLfloat zRot = 0.0f;		// Z�b��������Ѽ�
bool Line_Flag=false;

static	GLfloat nRange = 420.0f;//�Ŷ��j�p

// �O���Ѽ�
static GLfloat  ambientLight[]	= { 0.8f, 0.8f, 1.0f, 1.0f };	
static GLfloat  diffuseLight[]	= { 0.7f, 0.7f, 0.7f, 1.0f };
static GLfloat  specular[]		= { 0.7f, 0.7f, 0.7f, 1.0f };	//�O���ʽ�
static GLfloat  specref []		= { 0.5f, 0.5f, 0.2f, 1.0f };	//�Ϯg�ʽ�
static GLfloat	lightPos[]		= { 1000.0f, 1000.0f, 1000.0f, 1.0f}; 

// �X�аѼ�
//static BOOL Line_flag = FALSE;
static BOOL View_lock = TRUE;
int View_flag = 5;						// �Ѽ�(�w�]���������)
#define Up_View    1				// �W����
#define Front_View 2				// �e����
#define Back_View  3				// �����
#define Right_View 4				// �k����
#define Left_View  5				// ������
#define Orign_View 6				// �����
#endif