//ExternalVar.h
#include "stdafx.h"
#include <afxtempl.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Arc.h"
#include "ChangePoint.h"
#include "Circle.h"
#include "CircleRightLeft.h"
#include "InputData.h"
#include "Line.h"
#include "LineLine.h"
#include "NoSolution.h"
#include "Point2D.h"
#include "Point3D.h"
#include "PointArc.h"
#include "PointCircle.h"
#include "PointLine.h"
#include "RipArcCircle.h"
#include "Tool.h"
#include "TwoPointCircle.h"
#include "Vector.h"
typedef struct EngarveElement{
	long Type;//1 :Line  2:Arc  3:Circle
	long CCW;//CW:0      CCW:1
	double X1;//XO
	double Y1;//YO
	double Z1;//ZO
	double X2;//R
	double Y2;//A1
	double Z2;//A2
}EngarveElement;
///////////////////////////////////////
extern EngarveElement *gEE;//������c���
extern CArray <CInputData,CInputData> gArray;//�x�s��J���Ҧ�����
extern CArray <CCircle,CCircle> gArrayBuffer;//�Ȧs�@�Ӥ��q�I���Ҧ���
extern CArray <CCircle,CCircle> gArrayAns;
extern  CInputData gInputData;//�x�s�ѵ��c�ন���󪺸��
extern  long lngBlockNumber,*lngBlockData;//�x�s����block�ơA�M�C�@��block����Entity�ƥ�
extern  CPoint3D *Point3DAns;//�Ψ��x�s���ͪ����q�I���
extern  double dblTolerance;//�s�񤽮t
extern  long  lngDirection;//�s��@��block�����f��A0->���F1->�f
extern  CPoint3D *Point3DCross;//�s��C�@��entity�����I
//////////////////////////////////////