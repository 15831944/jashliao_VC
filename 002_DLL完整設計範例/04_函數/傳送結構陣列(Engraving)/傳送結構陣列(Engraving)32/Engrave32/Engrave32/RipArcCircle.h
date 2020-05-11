// RipArcCircle.h: interface for the CRipArcCircle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIPARCCIRCLE_H__C94038A6_9F0C_4A19_983A_B5965D4C7E63__INCLUDED_)
#define AFX_RIPARCCIRCLE_H__C94038A6_9F0C_4A19_983A_B5965D4C7E63__INCLUDED_

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
#include "LineLine.h"
#include "Circle.h"
#include "Arc.h"
#define PI 3.1415926f
class CRipArcCircle  
{
public:
	CLine m_LineBase;
	CPoint3D m_Point3DRip;
	CArc m_ArcRip;
	CRipArcCircle();
	CRipArcCircle(CLine LineBase,CArc ArcRip,CPoint3D Point3DRip);
	bool GetCircle(CCircle *circle1);
	virtual ~CRipArcCircle();
private:
	CPoint3D m_Point3DCross;//LineBase�P�s�߽u�����I
	CLine m_L;//Line1���@�����A�꩷�W�@�I��LineBase
	CLineLine m_LL1;//�DLineBase�P�s�߽u�����I
	double m_dblSita;//�PLineBase�����I���s�߽u������
	double m_r;//L=r+a�Ar������
	double m_a;//L=r+a�Aa������
	//int m_intType;//0:�꩷�~�A1:�꩷��
protected:
	void Calculate();
	bool m_bolSolution;//�����D�ѱ��p�Atrue�O���ѡAfalse�O�L��
	CCircle m_CircleAnswer;//������
};

#endif // !defined(AFX_RIPARCCIRCLE_H__C94038A6_9F0C_4A19_983A_B5965D4C7E63__INCLUDED_)
