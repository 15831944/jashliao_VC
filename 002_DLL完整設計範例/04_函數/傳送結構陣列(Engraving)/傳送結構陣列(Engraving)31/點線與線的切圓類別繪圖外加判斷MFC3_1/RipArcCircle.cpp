// RipArcCircle.cpp: implementation of the CRipArcCircle class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SDIShow.h"
#include "RipArcCircle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRipArcCircle::CRipArcCircle()
{
	m_dblSita=0.0;//�PLineBase�����I���s�߽u������
	m_r=0.0;//L=r+a
	m_a=0.0;
	m_bolSolution=false;
}
CRipArcCircle::CRipArcCircle(CLine LineBase,CArc ArcRip,CPoint3D Point3DRip)
{
	m_dblSita=0.0;//�PLineBase�����I���s�߽u������
	m_r=0.0;//L=r+a�Ar������
	m_a=0.0;//L=r+a�Aa������
	m_LineBase=LineBase;
	m_ArcRip=ArcRip;
	m_Point3DRip=Point3DRip;
	m_bolSolution=false;
}
void CRipArcCircle::Calculate()
{
	bool blnCheckCross=false;
	double dblL=0.0,dotData=0.0;
	CVector VectorSolAng,VectorL,VectorBase;
	CPoint3D Point3DVector; 
	m_L.SetData(m_ArcRip.m_Point3DCenter,m_Point3DRip);//���Ͷ꩷�s�߽u
	m_LL1.SetValue(m_L,m_LineBase);//�DLineBase�P�s�߽u�����I
	blnCheckCross=m_LL1.GetAns(&m_Point3DCross);//�DLineBase�P�s�߽u�����I
	if(blnCheckCross==true)
	{
		m_L.SetData(m_Point3DCross,m_Point3DRip);//�꩷�W�@�I��LineBase
		dblL=m_L.GetDistance();//���X�꩷�W�@�I��LineBase������ 
		VectorL.SetData(m_Point3DCross,m_Point3DRip);//����L�V�q 
		VectorBase.SetData(m_Point3DCross,m_LineBase.m_EndPoint);//����Base�V�q
		dotData=VectorSolAng.dot(VectorL,VectorBase,&m_dblSita);//�DL�MBase������
		if(m_dblSita>90.0)
			m_dblSita=180.0-m_dblSita;//�Ϩ��פ���0��90
		m_a=dblL/(1.0+sin(m_dblSita/180.0*PI));
		m_r=dblL-m_a;//L=a+r
		VectorL.SetData(m_Point3DRip,m_Point3DCross);//���s�p��L�����V�q
		Point3DVector=VectorL.GetUnitVector();//���s�p��L�����V�q
		m_CircleAnswer.m_fltR=m_r;//�]�w���G
		m_CircleAnswer.m_Point3DCenter.m_x=m_Point3DRip.m_x+m_r*Point3DVector.m_x;//�]�w���G  
		m_CircleAnswer.m_Point3DCenter.m_y=m_Point3DRip.m_y+m_r*Point3DVector.m_y;//�]�w���G  
		m_CircleAnswer.m_Point3DCenter.m_z=m_Point3DRip.m_z+m_r*Point3DVector.m_z;//�]�w���G  
		m_bolSolution=true;
	}
	else
	{
		m_bolSolution=false;
	}

}
bool CRipArcCircle::GetCircle(CCircle *circle1)
{
	Calculate();
	*circle1=m_CircleAnswer;
	return m_bolSolution;
}
CRipArcCircle::~CRipArcCircle()
{

}
