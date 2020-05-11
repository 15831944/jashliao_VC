// Circle.cpp: implementation of the CCircle class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SDIShow.h"
#include "Circle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCircle::CCircle()
{
	m_fltCircumference=0.0f;//�P��
	m_fltArea=0.0f;
	m_fltR=0.0f;
}
CCircle::CCircle(CPoint3D Center,double R)
{
	m_fltCircumference=0.0f;//�P��
	m_fltArea=0.0f;
	m_fltR=R;
	m_Point3DCenter=Center; 
	Calculate();
}
CCircle::CCircle(double Center_x,double Center_y,double Center_z,double R)
{
	m_fltCircumference=0.0f;//�P��
	m_fltArea=0.0f;
	m_fltR=R;
	m_Point3DCenter.SetData(Center_x,Center_y,Center_z);
	Calculate();
}
double CCircle::GetCircumference()
{
	double temp;
	//Calculate();
	temp=m_fltCircumference;
	return temp;
}
double CCircle::GetArea()
{
	double temp;
	//Calculate();
	temp=m_fltArea;
	return temp;
}
void CCircle::SetData(CPoint3D Center,double R)
{
	m_fltCircumference=0.0f;//�P��
	m_fltArea=0.0f;
	m_fltR=R;
	m_Point3DCenter=Center;
	Calculate();
}
void CCircle::Calculate()
{
	CPoint3D Point3DBuffer;
	m_fltCircumference=2.0f*m_fltR*PI;
	m_fltArea=m_fltR*m_fltR*PI;
	Point3DBuffer.SetData((m_Point3DCenter.m_x+m_fltR),m_Point3DCenter.m_y,m_Point3DCenter.m_z);
	m_VectorBase.SetData(m_Point3DCenter,Point3DBuffer); 
}
double CCircle::GetAngle(double fltBaseX,double fltBaseY,double fltX,double fltY)//���o���I������
{
	CLine LineBuffer;
	double fltDistanceBuffer;
	double fltAngle;
	if(fabs(fltBaseX-fltX)<=0.001 && fabs(fltBaseY-fltY)<=0.001)
		return 0.0f;//�Ǧ^����0
	if(fabs(fltBaseX-fltX)<=0.001)
	{
		if(fltY > fltBaseY)
			fltAngle=(double)(PI/2.0f);
		else
			fltAngle=(double)(PI*3.0f/2.0f);
		return fltAngle;
	}
	else
	{
		LineBuffer.SetData(fltBaseX,fltBaseY,0.0f,fltX,fltY,0.0f);
		fltDistanceBuffer=LineBuffer.GetDistance();
		fltAngle=(double)acos((fltX-fltBaseX)/fltDistanceBuffer);
		if((fltY<fltBaseY))
			fltAngle=(double)(PI*2.0f)-fltAngle;
		return fltAngle;
	}
}
int CCircle::CircleCircle(CCircle Circle1,double *ang1,double *ang2)
{
	double fltang,fltang1;
	double fltx1,flty1,fltr1;//�s�񥻨���߻P�b�|�ܼ�
	double fltx2,flty2,fltr2;//�s��ǤJ�����߻P�b�|�ܼ�
	CLine LineBuffer;//��߻P��߽u
	double fltDistanceBuffer;//��߻P��߶Z��
	double fltBufferR1,fltBufferR2,fltBufferD;
	fltx1=m_Point3DCenter.m_x; 
	flty1=m_Point3DCenter.m_y;
	fltr1=m_fltR;
	fltx2=Circle1.m_Point3DCenter.m_x; 
	flty2=Circle1.m_Point3DCenter.m_y;
	fltr2=Circle1.m_fltR;
	fltang=GetAngle(fltx1,flty1,fltx2,flty2);
	if(fltang>=PI)
		fltang=fltang-(2*PI);
	LineBuffer.SetData(fltx1,flty1,0.0f,fltx2,flty2,0.0f);
	fltDistanceBuffer=LineBuffer.GetDistance();
	if(fltDistanceBuffer < (fltr2-fltr1) )
		return 10;//������b�ǤJ�ꤺ
	else if(fabs(fltDistanceBuffer+fltr1-fltr2)<=0.001)
	{
		*ang1=fltang;
		return 11;//���������ǤJ��
	}
	else if(fabs(fltDistanceBuffer+fltr2-fltr1)<=0.001)
	{
		*ang1=fltang;
		return 21;//�ǤJ����󥻨���
	}
	else if(fabs(fltr2+fltr1-fltDistanceBuffer)<=0.001)
	{
		*ang1=fltang;
		return 31;//���~��
	}
	else if((fltr1-fltr2)>fltDistanceBuffer)
		return 20;//�ǤJ��b�����ꤺ
	else if(fltDistanceBuffer>(fltr2+fltr1))
	{
		return 0;//������
	}
	else
	{
		fltBufferR1=fltr1*fltr1;
		fltBufferR2=fltr2*fltr2;
		fltBufferD=fltDistanceBuffer*fltDistanceBuffer;
		fltang1=(double)acos((fltBufferR1+fltBufferD-fltBufferR2)/(2.0f*fltr1*fltDistanceBuffer));
		*ang1=fltang-fltang1;
		if(*ang1<0)
			*ang1=*ang1+PI*2.0f;
		*ang2=fltang+fltang1;
		if(*ang2>(2.0f*PI))
			*ang2=*ang2-(2.0f*PI);
		return 2;
	}
}
int CCircle::CircleLine(CLine Line1,double *angle1,double *angle2,CPoint3D *Point3D1,CPoint3D *Point3D2)
{
	double fltx1,flty1;
	double fltx2,flty2;
	double fltxx1,fltyy1;
	double fltxx2,fltyy2;
	double fltk,fltk1,fltk2;
	double fltyy,fltminy,fltmaxy;
	int intpb;
	double fltx,flty,fltr;
	///////////////////////////////////////////////////
	fltx=m_Point3DCenter.m_x; //���X��߻P�b�|
	flty=m_Point3DCenter.m_y;
	fltr=m_fltR;
	////////////////////////////////////////////////////
	fltx1=Line1.m_StartPoint.m_x-fltx;  
	flty1=Line1.m_StartPoint.m_y-flty;
	fltx2=Line1.m_EndPoint.m_x-fltx;  
	flty2=Line1.m_EndPoint.m_y-flty;
	////////////////////////////////////////////////////
	if(fabs(fltx1-fltx2)<0.001)//�u�q�������u
	{
		if(fltx1*fltx1>fltr*fltr)//�Y���u�Z���j���Υb�|�A�h���ۥ�
		//if( (fltx1*fltx1-fltr*fltr) > 0.001 )
			return 0;
		else
		{
			fltyy=(double)sqrt(fltr*fltr-fltx1*fltx1);
			fltyy1=-fltyy;
			fltyy2=fltyy;
			////////////
			//�]�w�̤j�̤p��
			if(flty1>flty2)
			{
				fltminy=flty2;
				fltmaxy=flty1;
			}
			else
			{
				fltminy=flty1;
				fltmaxy=flty2;
			}
			//////////////
			if(fltminy>fltyy1 && fltmaxy<fltyy2)
			//if( ((fltminy-fltyy1)>0.001) && ((fltyy2-fltmaxy)>0.001) )
				return 3;
			intpb=0;
			if(fltyy1>=fltminy && fltyy1<=fltmaxy)
			//if( ((fltyy1-fltminy)>=0.001) && ((fltmaxy-fltyy2)>=0.001) )
			{
				Point3D1->m_x=Line1.m_StartPoint.m_x;
				Point3D1->m_y=fltyy1+flty;
				*angle1=GetAngle(0.0f,0.0f,fltx1,fltyy1);
				intpb=1;
			}
			if(fltyy1!=fltyy2 && fltyy2>=fltminy && fltyy2<=fltmaxy)
			//if( (fabs(fltyy1-fltyy2)>0.001) && ((fltyy2-fltminy)>=0.001) && ((fltmaxy-fltyy2)>=0.001) )
			{
				if(intpb==1)
				{
					Point3D2->m_x=Line1.m_StartPoint.m_x;
					Point3D2->m_y=fltyy2+flty;
					*angle2=GetAngle(0.0f,0.0f,fltx1,fltyy2);
					intpb=2;
				}
				else
				{
					Point3D1->m_x=Line1.m_StartPoint.m_x;
					Point3D1->m_y=fltyy2+flty;
					*angle1=GetAngle(0.0f,0.0f,fltx1,fltyy2);
					intpb=1;
				}
			}
			return intpb;
		}
	}
	else
	{
		fltk=(flty1-flty2)/(fltx1-fltx2);
		fltk1=flty1-fltk*fltx1;
		fltk2=(4*fltk*fltk*fltk1*fltk1)-(4*(fltk*fltk+1)*(fltk1*fltk1-fltr*fltr));
		if(fltk2<0)
		//if(fltk2<0.001)
			return 0;
		else
		{
			fltxx1=(-2.0f*fltk*fltk1-(double)sqrt(fltk2))/(2.0f*(fltk*fltk+1));
			fltxx2=(-2.0f*fltk*fltk1+(double)sqrt(fltk2))/(2.0f*(fltk*fltk+1));
			fltyy1=flty1+fltk*(fltxx1-fltx1);
			fltyy2=flty1+fltk*(fltxx2-fltx1);
			if(fltx1>fltxx1 && fltx1<fltxx2 && fltx2>fltxx1 && fltx2<fltxx2)
			//if( ((fltx1-fltxx1)>0.001) && ((fltxx2-fltx1)>0.001) && ((fltx2-fltxx1)>0.001) && ((fltxx2-fltx2)>0.001) )
				return 3;
			intpb=0;
			if(fltxx1>=fltx1 && fltxx1<=fltx2 || fltxx1<=fltx1 && fltxx1>=fltx2)
			//if( (((fltxx1-fltx1)>=0.001) && ((fltx2-fltxx1)>=0.001)) || (((fltx1-fltxx1)>=0.001) && ((fltxx1-fltx2)>=0.001)) )
			{
					Point3D1->m_x=fltxx1+fltx;
					Point3D1->m_y=fltyy1+flty;
					*angle1=GetAngle(0.0f,0.0f,fltxx1,fltyy1);
					intpb=1;
			}
			if(fltk2!=0 && fltxx1!=fltxx2 && fltxx2>=fltx1 && fltxx2<=fltx2 ||fltxx2<=fltx1 && fltxx2>=fltx2)
			//if( (fabs(fltk2)>0.001) && (fabs(fltxx1-fltxx2)>0.001) && ((fltxx2-fltx1)>=0.001) && ((fltx2-fltxx2)>=0.001) || ((fltx1-fltxx2)>=0.001) && ((fltxx2-fltx2)>=0.001) )
			{
				if(intpb==1)
				{
					Point3D2->m_x=fltxx2+fltx;
					Point3D2->m_y=fltyy2+flty;
					*angle2=GetAngle(0.0f,0.0f,fltxx2,fltyy2);
					intpb=2;
				}
				else
				{
					Point3D1->m_x=fltxx2+fltx;
					Point3D1->m_y=fltyy2+flty;
					*angle1=GetAngle(0.0f,0.0f,fltxx2,fltyy2);
					intpb=1;
				}
			}
			return intpb;
		}
	}
	return 0;
}
bool CCircle::CheckExcircle(const CLine Line1)
{
	CPoint3D start,end,max,min,a,UnitVector;
	CVector V1,V2,V3;
	double l,k,Sita,buf;
	start=Line1.m_StartPoint; 
	end=Line1.m_EndPoint;
	V1.SetData(start,m_Point3DCenter);//�إ߽u�q�_�l�I�P��ߪ��V�q
	V2.SetData(start,end);//�إ߽u�q�V�q
	buf=V3.dot(V1,V2,&Sita);//�D��V�q����
	l=V1.GetDistance();//�D�V�qV1����
	k=l*cos(Sita/180.0*PI);//�D�u�q�_�l�I�������I������
	UnitVector=V2.GetUnitVector();//�p��u�q�����V�q 
	a.m_x=start.m_x+UnitVector.m_x*k;//�p���ڥ��I�y��  
	a.m_y=start.m_y+UnitVector.m_y*k;//�p���ڥ��I�y�� 
	a.m_z=start.m_z+UnitVector.m_z*k;//�p���ڥ��I�y��
	if(start.m_x > end.m_x)//�إ߽u�q��x�b�y�нd��
	{
		max.m_x=start.m_x;
		min.m_x=end.m_x; 
	}
	else
	{
		max.m_x=end.m_x;
		min.m_x=start.m_x;		
	}
	///////////////////////
	if(start.m_y > end.m_y)//�إ߽u�q��y�b�y�нd��
	{
		max.m_y=start.m_y;
		min.m_y=end.m_y; 
	}
	else
	{
		max.m_y=end.m_y;
		min.m_y=start.m_y;		
	}
	///////////////////
	if((a.m_x<=max.m_x) && (a.m_x>=min.m_x) && (a.m_y<=max.m_y) && (a.m_y>=min.m_y))//�P�_���I�O�_�b�u�q��
	{
		CLine Linebuf;
		double m;
		Linebuf.SetData(a,m_Point3DCenter);
		m=Linebuf.GetDistance(); 
		if(fabs(m-m_fltR)<=0.001)
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}
}
CCircle::~CCircle()
{

}
