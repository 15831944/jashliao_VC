// CircleRightLeft.cpp: implementation of the CCircleRightLeft class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "SDIShow.h"
#include "CircleRightLeft.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCircleRightLeft::CCircleRightLeft()
{
	m_CCW=-1;//������V�A0->�k�F1->��
	m_Direction=-1;//�������f�A0->���F1->�f
	m_lngLineArc=-1;//�Ψ��x�s���A0->Line�F1->Arc
	m_blnAns=false;//�����B�⵲�G
}
bool CCircleRightLeft::Check()//��X���
{
	calculate();
	return m_blnAns;
}
void CCircleRightLeft::SetData(const CInputData &ID,const CCircle &CC)//��l�ƨ��
{
	m_CCW=-1;//������V�A0->�k�F1->��
	m_Direction=-1;//�������f�A0->���F1->�f
	m_lngLineArc=-1;//�Ψ��x�s���A0->Line�F1->Arc
	m_blnAns=false;//�����B�⵲�G
	m_InputData.Reset();
	m_InputData=ID;
	m_Circle=CC;
}
void CCircleRightLeft::calculate()
{
	m_blnAns=false;//�����B�⵲�G
	m_CCW=m_InputData.CCW;//������V�A0->�k�F1->��
	m_Direction=m_InputData.Direction;//�������f�A0->���F1->�f
	m_lngLineArc=m_InputData.m_lngLineArc;//�Ψ��x�s���A0->Line�F1->Arc
	////////////////////////////////////////////////
	CLine LineBuf;
	CArc ArcBuf;
	if(m_lngLineArc==0)//0->Line
	{
		double angle1,angle2;
		CPoint3D Point3D1,Point3D2;
		CVector V1,V2;
		CPoint3D V3;
		LineBuf=m_InputData.m_Line;
		V1.SetData(LineBuf.m_StartPoint,LineBuf.m_EndPoint);//from LineBuf
		long lng1=m_Circle.CircleLine(LineBuf,&angle1,&angle2,&Point3D1,&Point3D2);
		///*
		if(lng1==0)
		{
			CPoint3D Centerbuf;//������ߪ��Ȧs��
			CVector VectorCenterbuf,Vectordot;
			Centerbuf=m_Circle.m_Point3DCenter;
			VectorCenterbuf.SetData(LineBuf.m_StartPoint,Centerbuf);//�إ߶�߻P�u�q�_�l�I���s�u
			angle2=Vectordot.dot(V1,VectorCenterbuf,&angle1);//�D����u�������A���ɪ�angle2�x�sdot��Ƴ���
			angle2=VectorCenterbuf.GetDistance()*cos(angle1/180.0*PI);
			Point3D2=V1.GetUnitVector();
			Point3D1.m_x=LineBuf.m_StartPoint.m_x+Point3D2.m_x*angle2;  
			Point3D1.m_y=LineBuf.m_StartPoint.m_y+Point3D2.m_y*angle2; 
			Point3D1.m_z=LineBuf.m_StartPoint.m_z+Point3D2.m_z*angle2; 
		}
		//*/
		V2.SetData(Point3D1,m_Circle.m_Point3DCenter);//from m_Circle�F�k�V�q 
		V3=V1*V2;//�V�q*�k�V�q�F�j��0��ܦb�����A�p�󵥩�0��ܦb�k��
		if(V3.m_z>0)//�k�V�q�b�V�q����A��b�u������
		{
			if(m_CCW==1)//������V�A0->�k�F1->��
			{
				m_blnAns=true;//������
			}
			else
			{
				m_blnAns=false;//�@���@�k
			}
		}
		else//�k�V�q�b�V�q�k��A��b�u���k��
		{
			if(m_CCW==1)//������V�A0->�k�F1->��
			{
				m_blnAns=false;//�@�k�@��
			}
			else
			{
				m_blnAns=true;//�����k
			}
		}
	}
	else//1->Arc
	{
		long lng2,lng3;
		double R1,R2;
		CPoint3D Point3D1,Point3D2;
		ArcBuf=m_InputData.m_Arc;
		Point3D1=ArcBuf.m_Point3DCenter;//Xbar,Ybar
		R1=ArcBuf.m_fltR; 
		Point3D2=m_Circle.m_Point3DCenter;//Xc,Yc
		R2=m_Circle.m_fltR;
		////////////////////////�P�_��b���~�٬O����
		if( ( pow((Point3D2.m_x-Point3D1.m_x),2) + pow((Point3D2.m_y-Point3D1.m_y),2) ) > (pow((R2-R1),2)) )//���~  
		{
			lng2=1;//���~
		}
		else//����
		{
			lng2=0;//����
		}
		///////////////////////////////////
		///�P�_�ثe�����کҦb��m
		if(m_Direction==0)//0->��
		{
			if(lng2==1)//���~
			{
				lng3=1;//����
			}
			else//����
			{
				lng3=0;//�k��
			}
		}
		else//1->�f
		{
			if(lng2==1)//���~
			{
				lng3=0;//�k��
			}
			else//����
			{
				lng3=1;//����
			}
		}
		/////////////////////////////
		if((lng3-m_CCW)==0)
		{
			m_blnAns=true;
		}
		else
		{
			m_blnAns=false;
		}
	}
}
CCircleRightLeft::~CCircleRightLeft()
{

}
