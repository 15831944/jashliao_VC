// PointArc.h: interface for the CPointArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTARC_H__CC8FB041_1A11_422C_942B_B143193300CA__INCLUDED_)
#define AFX_POINTARC_H__CC8FB041_1A11_422C_942B_B143193300CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Point2D.h"
#include "Point3D.h"
#include "Vector.h"
#include "Line.h"
#include "Circle.h"
#include "Arc.h"
#define PI 3.1415926f
class CPointArc  
{
public:
	CArc m_ArcAim;
	CLine m_LineBegin;
	CPoint3D m_Point3DBegin;
	CArc m_ArcBegin;
	CPointArc();
	CPointArc(CArc arc1,CLine line1,CPoint3D point1);
	CPointArc(CArc arc1,CArc arc2,CPoint3D point1);
	bool GetCircle(CCircle *circle1);
	virtual ~CPointArc();
private:
	CVector m_Vectorn;
	CVector m_Vectord;
	double m_fltSiTa;
	int m_intType[2];//��0�ӡG��0�ɬO�u�A��1�ɬO�꩷�F
					//��1�ӡG��0�ɬO�꩷�~�A��1�ɬO�꩷���C
	double m_fltDistance;
	double m_fltA[2],m_fltB[2],m_fltC[2];
	double m_fltR[2];//�s��ѥX�Ӫ��b�|���
	CPoint3D m_Point3DCenter[2];//�s��ѥX�Ӫ���߸��
protected:
	void Calculate();
	bool m_bolSolution;//�����D�ѱ��p�Atrue�O���ѡAfalse�O�L��
	CCircle m_CircleAnswer[2];//������
};

#endif // !defined(AFX_POINTARC_H__CC8FB041_1A11_422C_942B_B143193300CA__INCLUDED_)
