// NoSolution.cpp: implementation of the CNoSolution class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//////////#include "SDIShow.h"
#include "NoSolution.h"
#include "ExternalVar.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNoSolution::CNoSolution()
{

}
CNoSolution::CNoSolution(const CInputData &InputData,const long lngIDNum,const CPoint3D &Point3DRip,const CPoint3D *Point3DCross,const long lngnumber)
{
	long i;
	m_InputData=InputData;
	m_Point3DRip=Point3DRip;
	m_lngnumber=lngnumber;
	m_lngIDNum=lngIDNum;
	m_pPoint3DCross=new CPoint3D[m_lngnumber];
	for(i=0;i<m_lngnumber;i++)
	{
		(m_pPoint3DCross+i)->m_x=(Point3DCross+i)->m_x; 
		(m_pPoint3DCross+i)->m_y=(Point3DCross+i)->m_y;
		(m_pPoint3DCross+i)->m_z=(Point3DCross+i)->m_z;
	}
}
void CNoSolution::SetData(const CInputData &InputData,const long lngIDNum,const CPoint3D &Point3DRip,const CPoint3D *Point3DCross,const long lngnumber)
{
	long i;
	m_InputData=InputData;
	m_Point3DRip=Point3DRip;
	m_lngnumber=lngnumber;
	m_lngIDNum=lngIDNum;
	m_pPoint3DCross=new CPoint3D[m_lngnumber];
	for(i=0;i<m_lngnumber;i++)
	{
		m_pPoint3DCross[i]=Point3DCross[i];
	}
}
void CNoSolution::Calculate()
{
	long i;
	long n;
	long index;
	m_check=false;
	gArrayAnsBuf.RemoveAll(); 
	if(m_InputData.m_lngLineArc==0)
	{
		m_LineRip=m_InputData.m_Line;
		for(i=0;i<m_lngnumber;i++)
		{
			if(m_Point3DRip.m_x==m_LineRip.m_StartPoint.m_x && m_Point3DRip.m_y==m_LineRip.m_StartPoint.m_y)
				break;
			if(m_Point3DRip.m_x==m_LineRip.m_EndPoint.m_x && m_Point3DRip.m_y==m_LineRip.m_EndPoint.m_y)
				break;
			m_TPC.SetData(m_LineRip,m_Point3DRip,m_pPoint3DCross[i]);//�p����I����
			m_Circlebuf.m_Point3DCenter=m_TPC.GetCenter();
			m_Circlebuf.m_fltR=m_TPC.GetR();
			if(m_Circlebuf.m_fltR>0)
			{
				m_CRL.SetData(m_InputData,m_Circlebuf);//�P�_���k��
				if(m_CRL.Check())
				{
					gArrayAnsBuf.Add(m_Circlebuf);//�[�i�Կ����}�C
				}
			}
		}
	}
	else
	{
		m_ArcRip=m_InputData.m_Arc;
		CPoint3D P3DStart,P3DEnd;
		for(i=0;i<m_lngnumber;i++)
		{
			P3DStart.m_x=m_ArcRip.m_Point3DCenter.m_x+m_ArcRip.m_fltR*cos(m_ArcRip.m_fltStartAngle);    
			P3DStart.m_y=m_ArcRip.m_Point3DCenter.m_y+m_ArcRip.m_fltR*sin(m_ArcRip.m_fltStartAngle);
			P3DStart.m_z=m_ArcRip.m_Point3DCenter.m_z+m_ArcRip.m_fltR*0;
			P3DEnd.m_x=m_ArcRip.m_Point3DCenter.m_x+m_ArcRip.m_fltR*cos(m_ArcRip.m_fltEndAngle);    
			P3DEnd.m_y=m_ArcRip.m_Point3DCenter.m_y+m_ArcRip.m_fltR*sin(m_ArcRip.m_fltEndAngle);
			P3DEnd.m_z=m_ArcRip.m_Point3DCenter.m_z+m_ArcRip.m_fltR*0;
			if(m_Point3DRip.m_x==P3DStart.m_x && m_Point3DRip.m_y==P3DStart.m_y)
				break;
			if(m_Point3DRip.m_x==P3DEnd.m_x && m_Point3DRip.m_y==P3DEnd.m_y)
				break;
			m_APC.SetData(m_ArcRip,m_Point3DRip,m_pPoint3DCross[i]);//�p����I����
			m_Circlebuf.m_Point3DCenter=m_APC.GetCenter();
			m_Circlebuf.m_fltR=m_APC.GetR();
			if(m_Circlebuf.m_fltR>0)
			{
				m_CRL.SetData(m_InputData,m_Circlebuf);//�P�_���k��
				if(m_CRL.Check())
				{
					gArrayAnsBuf.Add(m_Circlebuf);//�[�i�Կ����}�C
				}
			}
		}
	}
	n=gArrayAnsBuf.GetSize();//���X�Կ����Ӽ�
	if(n>0)
	{
		for(i=0;i<n;i++)//���X�C�@�ӭԿ����
		{
			m_Circlebuf=gArrayAnsBuf[i];
			if(m_Circlebuf.m_fltR>0)
			{
				if(m_check==false)//���X�̤p�b�|����
				{
					m_check=true;
					index=i;
					m_dblRBuf=m_Circlebuf.m_fltR;
				}
				else
				{
					if(m_dblRBuf>m_Circlebuf.m_fltR)
					{
						index=i;
						m_dblRBuf=m_Circlebuf.m_fltR;
					}
				}
			}
		}
		m_CircleAns=gArrayAnsBuf[index];
	}
////////////////////////////////////////////////////////////////
	CheckEntity();
	
}
void CNoSolution::CheckEntity()
{
	long lngEntityNumber=(long)gArray.GetSize(); //���o����ƶq
	long lngcount=0;
	CInputData InputDataBuffer;//��J����Ȧs��
	if(m_check!=false)//�T�{�B�ꤣ�M��Lentity�ۥ�
	{
		for(long q=0;q<lngEntityNumber;q++)
		{
			if(q!=m_lngIDNum)
			{
				InputDataBuffer.Reset();//�M�żȦs�� 
				InputDataBuffer=gArray[q];//���X�۹諸entity
				if(InputDataBuffer.m_lngLineArc==0)//�Ψ��x�s���A0->Line�F1->Arc)
				{//0->Line
					double angle1,angle2;
					CPoint3D P3D1,P3D2;
					int Ansnumber;
					Ansnumber=m_CircleAns.CircleLine(InputDataBuffer.m_Line,&angle1,&angle2,&P3D1,&P3D2);
					if(Ansnumber==3)//�u�q�b�ꤺ
					{//
						m_check=false;
						lngcount=0;
						break;
					}
					else if(Ansnumber==2)//����ӥ��I
					{
						CLine Line2d;
						Line2d.SetData(P3D1,P3D2); 
						if(Line2d.GetDistance()>0.1)//�P�_��ӥ��I�O�_���P�@��
						{
							m_check=false;
							lngcount=0;
							break;
						}
					}
				}
				else
				{//1->Arc
					int Ansnumber;
					double ang1,ang2;
					CCircle CC1;
					CC1.SetData(InputDataBuffer.m_Arc.m_Point3DCenter,InputDataBuffer.m_Arc.m_fltR);  
					//Ansnumber=InputDataBuffer.m_Arc.ArcCircle(m_CircleAns);
					Ansnumber=CC1.CircleCircle(m_CircleAns,&ang1,&ang2); 
					if(Ansnumber!=11||Ansnumber!=21||Ansnumber!=31)
					{
						m_check=false;
						break;
					}									
				}
			}
			else
			{
					int Ansnumber;
					InputDataBuffer.Reset();//�M�żȦs�� 
					InputDataBuffer=gArray[q];//���X�۹諸entity
					if(InputDataBuffer.m_lngLineArc==1)
					{
						CCircle Arc2Circle;
						double angbuf1,angbuf2;
						Arc2Circle.SetData(InputDataBuffer.m_Arc.m_Point3DCenter,InputDataBuffer.m_Arc.m_fltR);
						Ansnumber=m_CircleAns.CircleCircle(Arc2Circle,&angbuf1,&angbuf2);
						if(Ansnumber==20||Ansnumber==21)
						{
							m_check=false;
							break;
						}
						else if((Ansnumber==10||Ansnumber==11)&& (fabs(m_CircleAns.m_fltR-Arc2Circle.m_fltR)<0.001))
						{
							m_check=false;
							break;
						}
					}
			}
		}
	}
}
bool CNoSolution::GetAns(CCircle *CC)
{
	Calculate();
	CC->m_Point3DCenter=m_CircleAns.m_Point3DCenter;  
	CC->m_fltR=m_CircleAns.m_fltR;  
	return m_check;
}
CNoSolution::~CNoSolution()
{
	if(m_lngnumber>0)	
		delete [] m_pPoint3DCross;
}
