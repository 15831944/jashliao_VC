// SDIShowView.cpp : implementation of the CSDIShowView class
//

#include "stdafx.h"
#include "SDIShow.h"

#include "SDIShowDoc.h"
#include "SDIShowView.h"
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
#include "GlobalVar.h"
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
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CSDIShowView
long EngInitial(long lngBlockAmount,double tolerance,long Direction);//���oBlock�`�ơA�ðʺA�t�m�O����w�ΨӦs��C��Block��Entity�ƶq
long EngGetValue(EngarveElement *p,long lngBlock,long lngAmount);//��ư}�C���СF��ư}�C�ݩ�ĴX��lngBlock�F�}�C�j�p
long EngLineLineSolve(const CInputData &BaseInputData,const CInputData &RipInputData,const CPoint3D &RipPoint3D,CCircle *AnsCircle);//�u�P�u�D����
long EngLineArcSolve(const CArc &BaseArc,const CLine &RipLine,const CPoint3D &RipPoint3D,CCircle *AnsCircle);//�u�P�꩷�D����
long EngArcLineSolve(const CLine &BaseLine,CArc &RipArc,const CPoint3D &RipPoint3D,CCircle *AnsCircle);//�꩷�P�u�D����
long EngArcArcSolve(const CArc &BaseArc,const CArc &RipArc,const CPoint3D &RipPoint3D,CCircle *AnsCircle);//�꩷�P�꩷�D����
long ArcParagraph(CArc &data,const double tolerance);//�꩷�D���q�I
long LineParagraph(CLine &data,const double tolerance);//�u�D���q�I
long EngCalculate();//�p��֤�
long BubbleSort(double **p,long n);//�G���}�C�Ƨ�
long EngInitial(long lngBlockAmount,double tolerance,long Direction)//���oBlock�`�ơA�ðʺA�t�m�O����w�ΨӦs��C��Block��Entity�ƶq
{
	long i;
	lngBlockNumber=lngBlockAmount;
	lngDirection=Direction;//0->���F1->�f
	if(lngBlockNumber<1)
		return 0;
	if(tolerance<=0)
		return 0;
	else
	{
		error=fopen("error.txt","w");
		data=fopen("data.txt","w");
		lngBlockData=new long[lngBlockNumber];
		for(i=0;i<lngBlockNumber;i++)
			lngBlockData[i]=-1;
		dblTolerance=tolerance;
		return 1;
	}
}
long EngGetValue(EngarveElement *p,long lngBlock,long lngAmount)
//��ư}�C���СF��ư}�C�ݩ�ĴX��lngBlock�F�}�C�j�p
{
	long i,n;
	long lngtype,lngblock;
	long return1;
	n=lngAmount;
	lngblock=lngBlock;
	try
	{
		if(lngBlock<0)
			throw 0;
		if(lngAmount<=0)
			throw 1;
	}
	catch(int err)
	{
		if(err==0)
			fprintf(error,"��ƨS�����s��\n");
		else
			fprintf(error,"�}�C���S��������\n");
		return 0;
	}
	lngBlockData[lngblock]=n;
	gEE=p;
	Point3DCross=new CPoint3D[n]; 
	for(i=0;i<n;i++)
	{
		lngtype=(gEE+i)->Type;
		gInputData.Reset();
		if(lngtype==1)//Line
		{
			gInputData.m_lngBlock=lngblock;//�Ψ��x�s�ݩ����Block
			gInputData.m_lngEntity=i;//�Ψ��x�s�ݩ����Entity
			gInputData.m_lngLineArc=0;//�Ψ��x�s���A0->Line�F1->Arc
			gInputData.CCW=(gEE+i)->CCW;//������V�A0->�k�F1->��
			gInputData.Direction=lngDirection;//�������f�A0->���F1->�f
			gInputData.m_Line.SetData((gEE+i)->X1,(gEE+i)->Y1,(gEE+i)->Z1,(gEE+i)->X2,(gEE+i)->Y2,(gEE+i)->Z2);
			Point3DCross[i]=gInputData.m_Line.m_EndPoint;
			fprintf(data,"�� %d block �� %d �� : ���u��ơA�������Ƭ�\t%f\t%f\t%f\t%f\t%f\t%f\n",lngblock,i,gInputData.m_Line.m_StartPoint.m_x,gInputData.m_Line.m_StartPoint.m_y,gInputData.m_Line.m_StartPoint.m_z,
				gInputData.m_Line.m_EndPoint.m_x,gInputData.m_Line.m_EndPoint.m_y,gInputData.m_Line.m_EndPoint.m_z);  
		}
		else if(lngtype==2)//Arc
		{
			gInputData.m_lngBlock=lngblock;//�Ψ��x�s�ݩ����Block
			gInputData.m_lngEntity=i;//�Ψ��x�s�ݩ����Entity
			gInputData.m_lngLineArc=1;//�Ψ��x�s���A0->Line�F1->Arc
			gInputData.CCW=(gEE+i)->CCW;//������V�A0->�k�F1->��
			gInputData.Direction=lngDirection;//�������f�A0->���F1->�f
			CPoint3D P3DCenter((gEE+i)->X1,(gEE+i)->Y1,(gEE+i)->Z1); 
			gInputData.m_Arc.SetData(P3DCenter,(gEE+i)->X2,(gEE+i)->Y2,(gEE+i)->Z2);
			Point3DCross[i].m_x=P3DCenter.m_x+gInputData.m_Arc.m_fltR*cos(gInputData.m_Arc.m_fltEndAngle);   
			Point3DCross[i].m_y=P3DCenter.m_y+gInputData.m_Arc.m_fltR*sin(gInputData.m_Arc.m_fltEndAngle); 
			Point3DCross[i].m_z=P3DCenter.m_z+gInputData.m_Arc.m_fltR*0; 
			fprintf(data,"�� %d block �� %d �� : ������ơA�������Ƭ�\t%f\t%f\t%f\t%f\t%f\t%f\n",lngblock,i,gInputData.m_Arc.m_Point3DCenter.m_x,gInputData.m_Arc.m_Point3DCenter.m_y,gInputData.m_Arc.m_Point3DCenter.m_z,
				gInputData.m_Arc.m_fltR,gInputData.m_Arc.m_fltStartAngle,gInputData.m_Arc.m_fltEndAngle);  
		}
		gArray.Add(gInputData);
	}
	return1=(long)gArray.GetSize(); 
	return return1;
}
long EngLineLineSolve(const CInputData &BaseInputData,const CInputData &RipInputData,const CPoint3D &RipPoint3D,CCircle *AnsCircle)
{
	double ang1,ang2;
	long data1,data2;
	CCircleRightLeft CRL1,CRL2;
	CPoint3D p2;
	CCircle CC1,CC2;
	CLine Line;
	CPoint3D Point3D1,Point3D2; 
	CVector VectorBase,VectorRip;
	CLine BaseLine,RipLine;
	CPoint3D Point3DRip;
	BaseLine=BaseInputData.m_Line;
	RipLine=RipInputData.m_Line; 
	VectorBase.SetData(BaseLine.m_StartPoint,BaseLine.m_EndPoint);
	VectorRip.SetData(RipLine.m_StartPoint,RipLine.m_EndPoint);
	Point3DRip=RipPoint3D;
	CPointLine PL(VectorBase,Point3DRip,VectorRip);
	CC1.SetData(PL.GetCenter(0),PL.GetR(0));
	CC2.SetData(PL.GetCenter(1),PL.GetR(1));
	Line.SetData(BaseLine.m_StartPoint,BaseLine.m_EndPoint); 
	//data=CC1.CircleLine(Line,&ang1,&ang2,&Point3D1,&Point3D2);
	//if((data!=0) && (data!=3))
	data1=0;
	data2=0;
	if(CC1.CheckExcircle(Line)) 
	{
		data1=1;
	}
	if(CC2.CheckExcircle(Line))
	{
		data2=1;
	}
	/////////////////////////
	if((data1==1) && (data2==0))
	{
		AnsCircle->m_Point3DCenter=PL.GetCenter(0);
		AnsCircle->m_fltR=PL.GetR(0);
		return 1;
	}
	else if((data1==0) && (data2==1))
	{
		AnsCircle->m_Point3DCenter=PL.GetCenter(1);
		AnsCircle->m_fltR=PL.GetR(1);
		return 1;
	}
	else if((data1==1) && (data2==1))
	{
		CRL1.SetData(BaseInputData,CC1);
		CRL2.SetData(RipInputData,CC1);
		if(CRL1.Check() && CRL2.Check())
		{
			AnsCircle->m_Point3DCenter=PL.GetCenter(0);
			AnsCircle->m_fltR=PL.GetR(0);
			return 1;
		}
		else
		{
			CRL1.SetData(BaseInputData,CC2);
			CRL2.SetData(RipInputData,CC2);
			if(CRL1.Check() && CRL2.Check())
			{
				AnsCircle->m_Point3DCenter=PL.GetCenter(1);
				AnsCircle->m_fltR=PL.GetR(1);
				return 1;
			}
		}
	}
	else
	{
		/*
		Line.SetData(RipLine.m_StartPoint,RipLine.m_EndPoint);
		if(CC1.CheckExcircle(Line)) 
		{
			data1=1;
		}
		if(CC2.CheckExcircle(Line))
		{
			data2=1;
		}
		if((data1==1) && (data2==0))
		{
			AnsCircle->m_Point3DCenter=PL.GetCenter(0);
			AnsCircle->m_fltR=PL.GetR(0);
			return 1;
		}
		else if((data1==0) && (data2==1))
		{
			AnsCircle->m_Point3DCenter=PL.GetCenter(1);
			AnsCircle->m_fltR=PL.GetR(1);
			return 1;
		}
		*/
	}
	return 0;
}
long EngLineArcSolve(const CArc &BaseArc,const CLine &RipLine,const CPoint3D &RipPoint3D,CCircle *AnsCircle)
{

	bool bolCircle=false;
	CArc ArcBase;
	CLine LineRip;
	CPoint3D Point3DRip;
	CCircle CircleBuf[2];
	ArcBase=BaseArc;
	LineRip=RipLine;
	Point3DRip=RipPoint3D;
	CPointArc PointArc(ArcBase,LineRip,Point3DRip);
	bolCircle=PointArc.GetCircle(CircleBuf);
	int a11=ArcBase.ArcCircle(CircleBuf[0]);
	int a12=ArcBase.ArcCircle(CircleBuf[1]);

	if((a11==1) && (a12==1))
	{
		if((CircleBuf[0].m_fltR>0)&&(CircleBuf[1].m_fltR>0))
		{
			if(CircleBuf[0].m_fltR>CircleBuf[1].m_fltR)
			{
				AnsCircle->m_fltR=CircleBuf[1].m_fltR;
				AnsCircle->m_Point3DCenter=CircleBuf[1].m_Point3DCenter; 
				return 1;
			}
			else
			{
				AnsCircle->m_fltR=CircleBuf[0].m_fltR;
				AnsCircle->m_Point3DCenter=CircleBuf[0].m_Point3DCenter;
				return 1;
			}
		}
		else if(CircleBuf[0].m_fltR>0)
		{
				AnsCircle->m_fltR=CircleBuf[0].m_fltR;
				AnsCircle->m_Point3DCenter=CircleBuf[0].m_Point3DCenter;
				return 1;
		}
		else if(CircleBuf[1].m_fltR>0)
		{
				AnsCircle->m_fltR=CircleBuf[1].m_fltR;
				AnsCircle->m_Point3DCenter=CircleBuf[1].m_Point3DCenter; 
				return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(a11==1)
	{
			AnsCircle->m_fltR=CircleBuf[0].m_fltR;
			AnsCircle->m_Point3DCenter=CircleBuf[0].m_Point3DCenter;
			return 1;
	}
	else if(a12==1)
	{
			AnsCircle->m_fltR=CircleBuf[1].m_fltR;
			AnsCircle->m_Point3DCenter=CircleBuf[1].m_Point3DCenter; 
			return 1;
	}
	return 0;
}
long EngArcLineSolve(const CLine &BaseLine,CArc &RipArc,const CPoint3D &RipPoint3D,CCircle *AnsCircle)
{
	bool bolcheck1=false;
	CCircle CircleBuf;
	CRipArcCircle RAP(BaseLine,RipArc,RipPoint3D);
	bolcheck1=RAP.GetCircle(&CircleBuf);
	if(bolcheck1==true)
	{
		int a11=RipArc.ArcCircle(CircleBuf);
		if(a11==1)
		{
			if(CircleBuf.m_fltR >0)
			{
				AnsCircle->m_fltR=CircleBuf.m_fltR;
				AnsCircle->m_Point3DCenter=CircleBuf.m_Point3DCenter; 				
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
long EngArcArcSolve(const CArc &BaseArc,const CArc &RipArc,const CPoint3D &RipPoint3D,CCircle *AnsCircle)
{
	bool bolCircle=false;
	CArc ArcBase;
	CArc ArcRip;
	CPoint3D Point3DRip;
	CCircle CircleBuf[2];
	ArcBase=BaseArc;
	ArcRip=RipArc;
	Point3DRip=RipPoint3D;
	CPointArc PointArc(ArcBase,ArcRip,Point3DRip);
	bolCircle=PointArc.GetCircle(CircleBuf);
	int a11=ArcBase.ArcCircle(CircleBuf[0]);
	int a12=ArcBase.ArcCircle(CircleBuf[1]);
	if((a11==1) && (a12==1))
	{
		if((CircleBuf[0].m_fltR>0)&&(CircleBuf[1].m_fltR>0))
		{
			if(CircleBuf[0].m_fltR>CircleBuf[1].m_fltR)
			{
				AnsCircle->m_fltR=CircleBuf[1].m_fltR;
				AnsCircle->m_Point3DCenter=CircleBuf[1].m_Point3DCenter; 
				return 1;
			}
			else
			{
				AnsCircle->m_fltR=CircleBuf[0].m_fltR;
				AnsCircle->m_Point3DCenter=CircleBuf[0].m_Point3DCenter;
				return 1;
			}
		}
		else if(CircleBuf[0].m_fltR>0)
		{
				AnsCircle->m_fltR=CircleBuf[0].m_fltR;
				AnsCircle->m_Point3DCenter=CircleBuf[0].m_Point3DCenter;
				return 1;
		}
		else if(CircleBuf[1].m_fltR>0)
		{
				AnsCircle->m_fltR=CircleBuf[1].m_fltR;
				AnsCircle->m_Point3DCenter=CircleBuf[1].m_Point3DCenter; 
				return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(a11==1)
	{
			AnsCircle->m_fltR=CircleBuf[0].m_fltR;
			AnsCircle->m_Point3DCenter=CircleBuf[0].m_Point3DCenter;
			return 1;
	}
	else if(a12==1)
	{
			AnsCircle->m_fltR=CircleBuf[1].m_fltR;
			AnsCircle->m_Point3DCenter=CircleBuf[1].m_Point3DCenter; 
			return 1;
	}
	return 0;
}
long ArcParagraph(CArc &data,const double tolerance)
{
	long i,number;
	double L,R;
	double StartAngle,EndAngle,UnitAngle;
	CPoint3D Center;
	Center=data.m_Point3DCenter;
	StartAngle=data.m_fltStartAngle;
	EndAngle=data.m_fltEndAngle;
	R=data.m_fltR; 
	L=sqrt(pow((2.0*PI*R*(EndAngle-StartAngle)/(2.0*PI)),2));
	//L=2.0*PI*R*(EndAngle-StartAngle)/(2.0*PI);
	number=(long)(L/(tolerance*10))+1;
	if(number<=1)
		return 0;
	Point3DAns=new CPoint3D[number];
	UnitAngle=(EndAngle-StartAngle)*(tolerance*10)/L;
	for(i=0;i<number;i++)
	{
		Point3DAns[i].m_x=Center.m_x+R*cos((StartAngle+i*UnitAngle)); 
		Point3DAns[i].m_y=Center.m_y+R*sin((StartAngle+i*UnitAngle)); 
		Point3DAns[i].m_z=Center.m_z+R*0;		
		
		//Point3DAns[i].m_x=Center.m_x+R*cos(i*UnitAngle); 
		//Point3DAns[i].m_y=Center.m_y+R*sin(i*UnitAngle); 
		//Point3DAns[i].m_z=Center.m_z+R*0;
		
	}
	return number;
}
long LineParagraph(CLine &data,const double tolerance)
{
	double L;
	long i,number;
	CVector Vector1;
	CPoint3D UnitVector1; 
	L=data.GetDistance();
	Vector1.SetData(data.m_StartPoint,data.m_EndPoint);
	UnitVector1=Vector1.GetUnitVector(); 
	number=(long)(L/(tolerance*20))+1;
	if(number<=1)
		return 0;
	Point3DAns=new CPoint3D[number];
	for(i=0;i<number;i++)
	{
		Point3DAns[i].m_x=data.m_StartPoint.m_x+i*(tolerance*20)*UnitVector1.m_x;
		Point3DAns[i].m_y=data.m_StartPoint.m_y+i*(tolerance*20)*UnitVector1.m_y;
		Point3DAns[i].m_z=data.m_StartPoint.m_z+i*(tolerance*20)*UnitVector1.m_z;
	}
	return number;
}
long EngCalculate()
{
	long lngEntityNumber=0;//�s�񤸥�ƶq
	long lngParagraphNumber=0;//�s����q�I���ƶq
	long i=0,j=0,k=0;//�T�h�j�骺�X���ܼ�
	long lngAnsNumber=0;//�D��M����|�w�I���ƶq
	long lngCheck=0;//q042j04g.
	lngEntityNumber=(long)gArray.GetSize(); //���o����ƶq
	CPoint3D Point3DBuffer;//���q�I�Ȧs��
	CInputData InputDataBuffer;//��J����Ȧs��
	CCircle CircleBuffer;//�Ȧs�D�X�Ӫ����
	double **DynamicArrayR;//�ʺA�t�m�G���O����A�Ψ��x�s�@�Ӥ��q�I�Ҧ�������b�|
	long l=0;//�ʺA�t�m�G���O����j�骺�X���ܼ�
	long m=0;//�ʺA�t�m�G���O������������ܼ�
	long n=0;//��ƪk���^�ǭȡA�M���o�Ƨǧ������G
	CCircleRightLeft CRLBuf;//�ΨӹB�����O�_�bentity���T��V
	bool blnCRL=false;//�Ψ��x�sCRLBuf�B�⵲�G
	long lngcount=0;//�Ψ��x�s����Pentity�ۥ榸��
	CNoSolution NSBuf;
	for(i=0;i<lngEntityNumber;i++)//(1)
	{
		gInputData.Reset();//����Ȧs����ƲM��
		gInputData=gArray[i];//�̧Ǩ��X�C��entity
		if(gInputData.m_lngLineArc==0)//�Ψ��x�s���A0->Line�F1->Arc)
		{
			lngParagraphNumber=LineParagraph(gInputData.m_Line,dblTolerance);//�u�D���q�I
		}
		else
		{
			lngParagraphNumber=ArcParagraph(gInputData.m_Arc,dblTolerance);//�꩷�D���q�I
		}
		///////////////////////////////////////////////////////////////////
		for(j=0;j<lngParagraphNumber;j++)//��C�Ӥ��q�I�̧ǨD����//(2)
		{
			gArrayBuffer.RemoveAll();//����Ȧs�@�Ӥ��q�I�P�Ҧ�entity����CArray�M��
			Point3DBuffer=Point3DAns[j];//�̧ǧ���q�I���X 
			for(k=0;k<lngEntityNumber;k++)//�̧ǩM��L��entity�@�B��//(3)
			{
				if(i==k)
					continue;//�P�@��Entity���κ�
				InputDataBuffer.Reset();//�M�żȦs�� 
				InputDataBuffer=gArray[k];//���X�۹諸entity
				switch((gInputData.m_lngLineArc+InputDataBuffer.m_lngLineArc))//�P�U�n�ϥέ��@�Ө�ƹB��
				{
					case 0://0+0
						lngCheck=EngLineLineSolve(InputDataBuffer,gInputData,Point3DBuffer,&CircleBuffer);
						break;
					case 1://1+0,0+1
						if((gInputData.m_lngLineArc==0) && (InputDataBuffer.m_lngLineArc==1))//�u�P�꩷�A�B���q�I�O�q�u�D�X
						{
							lngCheck=EngLineArcSolve(InputDataBuffer.m_Arc,gInputData.m_Line,Point3DBuffer,&CircleBuffer);
						}
						else//�u�P�꩷�A�B���q�I�O�q�꩷�D�X
						{
							lngCheck=EngArcLineSolve(InputDataBuffer.m_Line,gInputData.m_Arc,Point3DBuffer,&CircleBuffer);
						}
						break;
					case 2://1+1
						lngCheck=EngArcArcSolve(InputDataBuffer.m_Arc,gInputData.m_Arc,Point3DBuffer,&CircleBuffer);
						break;
				}
				if(lngCheck!=0)//�T�{�B�ꤣ�M��Lentity�ۥ�
				{
					for(long q=0;q<lngEntityNumber;q++)
					{
						if((q!=k) && (q!=i))
						{
								InputDataBuffer.Reset();//�M�żȦs�� 
								InputDataBuffer=gArray[q];//���X�۹諸entity
								if(InputDataBuffer.m_lngLineArc==0)//�Ψ��x�s���A0->Line�F1->Arc)
								{//0->Line
									double angle1,angle2;
									CPoint3D P3D1,P3D2;
									int Ansnumber;
									Ansnumber=CircleBuffer.CircleLine(InputDataBuffer.m_Line,&angle1,&angle2,&P3D1,&P3D2);
									/*
									if(Ansnumber!=0)
									{
										lngCheck=0;
										break;
									}
									//*/
									///*
									if(Ansnumber==3)//�u�q�b�ꤺ
									{//
										lngCheck=0;
										lngcount=0;
										break;
									}
									else if(Ansnumber==2)//����ӥ��I
									{
										CLine Line2d;
										Line2d.SetData(P3D1,P3D2); 
										if(Line2d.GetDistance()>0.1)//�P�_��ӥ��I�O�_���P�@��
										{
											lngCheck=0;
											lngcount=0;
											break;
										}
										else//����I���P�@��
										{
											lngcount++;
											if(CircleBuffer.CheckExcircle(InputDataBuffer.m_Line)==false)
											{
												lngCheck=0;
												lngcount=0;
												break;
											}
											if(lngcount>1)
											{
												lngCheck=0;
												lngcount=0;
												break;
											}
										}
									}
									else if(Ansnumber==1)
									{
										lngcount++;
										if(CircleBuffer.CheckExcircle(InputDataBuffer.m_Line)==false)
										{
											lngCheck=0;
											lngcount=0;
											break;
										}
										if(lngcount>1)
										{
											lngCheck=0;
											lngcount=0;
											break;
										}
									}
									//*/
								}
								else
								{//1->Arc
									int Ansnumber;
									CCircle Arc2Circle;
									double angbuf1,angbuf2;
									Arc2Circle.SetData(InputDataBuffer.m_Arc.m_Point3DCenter,InputDataBuffer.m_Arc.m_fltR);   
									Ansnumber=Arc2Circle.CircleCircle(CircleBuffer,&angbuf1,&angbuf2); 
									if(Ansnumber==10 )
									{
										lngCheck=0;
										break;
									}
									else if(Ansnumber==2)
									{
										double m_fltStartAngle,m_fltEndAngle;
										bool checkang1=false,checkang2=false;
										if(angbuf1<0)
											angbuf1=angbuf1+PI*2.0;
										if(angbuf2<0)
											angbuf2=angbuf2+PI*2.0;
										m_fltStartAngle=InputDataBuffer.m_Arc.m_fltStartAngle; 
										m_fltEndAngle=InputDataBuffer.m_Arc.m_fltEndAngle; 
										if((m_fltStartAngle<m_fltEndAngle && angbuf1<=m_fltEndAngle && angbuf1>=m_fltStartAngle)
											||(m_fltStartAngle>m_fltEndAngle && angbuf1<=m_fltStartAngle && angbuf1>=m_fltEndAngle))
											checkang1=true;
										if((m_fltStartAngle<m_fltEndAngle && angbuf2<=m_fltEndAngle && angbuf2>=m_fltStartAngle)
											||(m_fltStartAngle>m_fltEndAngle && angbuf2<=m_fltStartAngle && angbuf2>=m_fltEndAngle))
											checkang2=true;
										if(checkang2==true || checkang1==true)
										{
											lngCheck=0;
											break;
										}
									}
									Ansnumber=InputDataBuffer.m_Arc.ArcCircle(CircleBuffer);
									if(Ansnumber!=0)
									{
										lngCheck=0;
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
									Ansnumber=CircleBuffer.CircleCircle(Arc2Circle,&angbuf1,&angbuf2);
									if(Ansnumber==20||Ansnumber==21)
									{
										lngCheck=0;
										break;
									}
									else if((Ansnumber==10||Ansnumber==11)&& (fabs(CircleBuffer.m_fltR-Arc2Circle.m_fltR)<0.001))
									{
										lngCheck=0;
										break;
									}
								}
								else
								{
									bool CheckEx=false;
									CheckEx=CircleBuffer.CheckExcircle(InputDataBuffer.m_Line);
									if(CheckEx==false)
									{
										lngCheck=0;
										break;
									}
								}
						}
					}
				}
				///*
				if(lngCheck!=0)
				{
					InputDataBuffer.Reset();//�M�żȦs�� 
					InputDataBuffer=gArray[i];//���X�۹諸entity
					blnCRL=false;//�M���W�@���B�⵲�G
					CRLBuf.SetData(InputDataBuffer,CircleBuffer);
					blnCRL=CRLBuf.Check();
					if(blnCRL==false)
					{
						lngCheck=0;
					}
					else
					{
						InputDataBuffer.Reset();//�M�żȦs�� 
						InputDataBuffer=gArray[k];//���X�۹諸entity
						blnCRL=false;//�M���W�@���B�⵲�G
						CRLBuf.SetData(InputDataBuffer,CircleBuffer);
						blnCRL=CRLBuf.Check();
						if(blnCRL==false)
						{
							lngCheck=0;
						}
					}
				}
				//*/
				if(lngCheck!=0)//�p�G�S������A�h���ά���
					gArrayBuffer.Add(CircleBuffer);
				long debug1=(long)(gArrayAns.GetSize());
			}//(3)
			m=(long)(gArrayBuffer.GetSize());//��X�@�Ӥ��q�I���X����
			if(m<=0)
			{
				InputDataBuffer.Reset();//�M�żȦs�� 
				InputDataBuffer=gArray[i];//���X�۹諸entity
				NSBuf.SetData(InputDataBuffer,i,Point3DBuffer,Point3DCross,lngEntityNumber);
				if(NSBuf.GetAns(&CircleBuffer)) 
					gArrayBuffer.Add(CircleBuffer);
			}
			m=(long)(gArrayBuffer.GetSize());//��X�@�Ӥ��q�I���X����
			if(m>0)
			{
				DynamicArrayR=new double *[m];//�ʺA�t�m�O����
				for(l=0;l<m;l++)
					DynamicArrayR[l]=new double [2];
				for(l=0;l<m;l++)//�]�w�ʺA�t�m�O���骺��
				{
					DynamicArrayR[l][0]=l;
					CircleBuffer=gArrayBuffer[l];
					DynamicArrayR[l][1]=CircleBuffer.m_fltR; 
				}
				n=BubbleSort(DynamicArrayR,m);//��w�Ƨ�
				n=(long)(DynamicArrayR[0][0]);//���X�̤p�b�|���X��
				CircleBuffer=gArrayBuffer[n];//���X�̤p�b�|������
				gArrayAns.Add(CircleBuffer);//�x�s�̤p�b�|������ 
				for(l=0;l<m;l++)//����ʺA�G���O����
					delete [] DynamicArrayR[l];
				delete [] DynamicArrayR;
			}
		}//(2)
		delete [] Point3DAns;//����ʺA�@���O����
	}//(1)
	lngAnsNumber=gArrayAns.GetSize(); 
	delete [] Point3DCross;
	return lngAnsNumber;
}
long BubbleSort(double **p,long n)
{
	long i,j,key;
	double temp,temp1;
	if(n<=0)
		return 0;
	for(i=0;i<n;i++)
	{
		key=0;
		for(j=0;j<(n-i-1);j++)
		{
			if(p[j][1]>p[j+1][1])
			{
				temp1=p[j][1];
				p[j][1]=p[j+1][1];
				p[j+1][1]=temp1;
				///////////////////////////////
				temp=p[j][0];
				p[j][0]=p[j+1][0];
				p[j+1][0]=temp;
				key=1;
			}
		}
		if(key==0)
			break;
	}	
	return 1;
}
IMPLEMENT_DYNCREATE(CSDIShowView, CView)

BEGIN_MESSAGE_MAP(CSDIShowView, CView)
	//{{AFX_MSG_MAP(CSDIShowView)
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDIShowView construction/destruction

CSDIShowView::CSDIShowView()
{
	// TODO: add construction code here

}

CSDIShowView::~CSDIShowView()
{
}

BOOL CSDIShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSDIShowView drawing

void CSDIShowView::OnDraw(CDC* pDC)
{
	CSDIShowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	COLORREF color;

	///////////////////////////////////////////////////////////////////////////////
/*
	CVector test1,test2,test3;
	test1.SetData(300.0,0.0,0.0,0.0,-300.0,0.0);
	test2.SetData(200.0,0.0,0.0,200.0,400.0,0.0);
	test3.SetData(100.0,0.0,0.0,100.0,400.0,0.0);
	CPointLine PL(test1,test2.m_EndPoint,test2);
	double tests=PL.GetR(); 
//*/
	///////////////////
	float L,R;
	float x1,y1,x2,y2;
	CPoint3D p1,p2;
	color=RGB(255,0,0);
	CPoint3D Point3DO(0.0f,0.0f,0.0f),Point3DA(600.0f,0.0f,0.0f),Point3DP(0.0f,0.0f,0.0f);
	CVector VectorOA(Point3DO,Point3DA);
	CPoint3D Point3DK(300.0f,-300.0f,0.0f);
	CVector Line1(Point3DK,Point3DP);
	int i;
	i=0;
	CPoint3D Point3Dtest[10];
	CClientDC dc1(this);
	CPoint PointHalfBase;//�p��e�����߬����I 
	PointHalfBase.x=PointNowBase.x/2;
	PointHalfBase.y=PointNowBase.y/2;
	dc1.MoveTo(0,PointHalfBase.y);//�ex��ǽu
	dc1.LineTo(PointNowBase.x,PointHalfBase.y);
	dc1.MoveTo(PointHalfBase.x,0);//�ey��ǽu
	dc1.LineTo(PointHalfBase.x,PointNowBase.y);
	double ang1,ang2;
	int data;
	CPoint3D Point3D1,Point3D2; 
	CPen pen(PS_SOLID,1,color); 
	dc1.SelectObject(&pen);
	///////////////////////////////////////////////////////
	dc1.MoveTo(PointHalfBase.x+0,PointHalfBase.y-(-100));
	dc1.LineTo(PointHalfBase.x+100,PointHalfBase.y-0);
	/////
	dc1.MoveTo(PointHalfBase.x+100,PointHalfBase.y-0);
	dc1.LineTo(PointHalfBase.x+0,PointHalfBase.y-100);
	/////
	dc1.MoveTo(PointHalfBase.x+0,PointHalfBase.y-100);
	dc1.LineTo(PointHalfBase.x+100,PointHalfBase.y-100);
	/////
	dc1.MoveTo(PointHalfBase.x+100,PointHalfBase.y-100);
	dc1.LineTo(PointHalfBase.x+200,PointHalfBase.y-200);
	/////
	dc1.MoveTo(PointHalfBase.x+200,PointHalfBase.y-200);
	dc1.LineTo(PointHalfBase.x+300,PointHalfBase.y-100);
	/////
	dc1.MoveTo(PointHalfBase.x+300,PointHalfBase.y-100);
	dc1.LineTo(PointHalfBase.x+400,PointHalfBase.y-100);
	/////
	dc1.MoveTo(PointHalfBase.x+400,PointHalfBase.y-100);
	dc1.LineTo(PointHalfBase.x+300,PointHalfBase.y-0);
	/////
	dc1.MoveTo(PointHalfBase.x+300,PointHalfBase.y-0);
	dc1.LineTo(PointHalfBase.x+400,PointHalfBase.y-(-100));
	/////
	dc1.MoveTo(PointHalfBase.x+400,PointHalfBase.y-(-100));
	dc1.LineTo(PointHalfBase.x+200,PointHalfBase.y-0);
	/////
	dc1.MoveTo(PointHalfBase.x+200,PointHalfBase.y-0);
	dc1.LineTo(PointHalfBase.x+0,PointHalfBase.y-(-100));
	///////////////////////////////////////////////////////
	dc1.MoveTo(PointHalfBase.x+Point3DO.m_x,PointHalfBase.y-Point3DO.m_y);
	dc1.LineTo(PointHalfBase.x+Point3DA.m_x,PointHalfBase.y-Point3DA.m_y);
	dc1.MoveTo(PointHalfBase.x+Line1.m_StartPoint.m_x,PointHalfBase.y-Line1.m_StartPoint.m_y);
	dc1.LineTo(PointHalfBase.x+Line1.m_EndPoint.m_x,PointHalfBase.y-Line1.m_EndPoint.m_y);
	/////////////////////
	EngarveElement L1[10];
	L1[0].Type=1;
	L1[0].CCW=0;
	L1[0].X1=0; 
	L1[0].Y1=-100; 
	L1[0].Z1=0; 
	L1[0].X2=100; 
	L1[0].Y2=0; 
	L1[0].Z2=0;
	////////////////////
	L1[1].Type=1;
	L1[1].CCW=0;
	L1[1].X1=100; 
	L1[1].Y1=0; 
	L1[1].Z1=0; 
	L1[1].X2=0; 
	L1[1].Y2=100; 
	L1[1].Z2=0;
	////////////////////
///*
	L1[2].Type=1;
	L1[2].CCW=0;
	L1[2].X1=0; 
	L1[2].Y1=100; 
	L1[2].Z1=0; 
	L1[2].X2=100; 
	L1[2].Y2=100; 
	L1[2].Z2=0;
	////////////////////
	L1[3].Type=1;
	L1[3].CCW=0;
	L1[3].X1=100; 
	L1[3].Y1=100; 
	L1[3].Z1=0; 
	L1[3].X2=200; 
	L1[3].Y2=200; 
	L1[3].Z2=0;
	////////////////////
	L1[4].Type=1;
	L1[4].CCW=0;
	L1[4].X1=200; 
	L1[4].Y1=200; 
	L1[4].Z1=0; 
	L1[4].X2=300; 
	L1[4].Y2=100; 
	L1[4].Z2=0;
	////////////////////
	L1[5].Type=1;
	L1[5].CCW=0;
	L1[5].X1=300; 
	L1[5].Y1=100; 
	L1[5].Z1=0; 
	L1[5].X2=400; 
	L1[5].Y2=100; 
	L1[5].Z2=0;
	////////////////////
	L1[6].Type=1;
	L1[6].CCW=0;
	L1[6].X1=400; 
	L1[6].Y1=100; 
	L1[6].Z1=0; 
	L1[6].X2=300; 
	L1[6].Y2=0; 
	L1[6].Z2=0;
	////////////////////
	L1[7].Type=1;
	L1[7].CCW=0;
	L1[7].X1=300; 
	L1[7].Y1=0; 
	L1[7].Z1=0; 
	L1[7].X2=400; 
	L1[7].Y2=-100; 
	L1[7].Z2=0;
	////////////////////
	L1[8].Type=1;
	L1[8].CCW=0;
	L1[8].X1=400; 
	L1[8].Y1=-100; 
	L1[8].Z1=0; 
	L1[8].X2=200; 
	L1[8].Y2=0; 
	L1[8].Z2=0;
	////////////////////
	L1[9].Type=1;
	L1[9].CCW=0;
	L1[9].X1=200; 
	L1[9].Y1=0; 
	L1[9].Z1=0; 
	L1[9].X2=0; 
	L1[9].Y2=-100; 
	L1[9].Z2=0;
//*/

//*/
	long y=0;
	y=EngInitial(1,0.1,1);
	y=EngGetValue(L1,0,10);
	y=EngCalculate();
	y=y+0;
	CCircle CC1;
	
	for(i=0;i<y;i++)
	{
		CC1=gArrayAns[i];
		p2=CC1.m_Point3DCenter;
		R=CC1.m_fltR; 
		////////////////////////////////////////////////////////////////////////////////
		x1=PointHalfBase.x+p2.m_x-R; 
		y1=PointHalfBase.y-p2.m_y-R; 
		x2=PointHalfBase.x+p2.m_x+R; 
		y2=PointHalfBase.y-p2.m_y+R; 
		CPen pen(PS_SOLID,1,color); 
		dc1.SelectObject(&pen);
///*
		Sleep(100);
		dc1.Ellipse(x1,y1,x2,y2);
//*/
/*
		Sleep(100);
		if(i==0)
		{
			dc1.MoveTo(PointHalfBase.x+p2.m_x,PointHalfBase.y-p2.m_y);
		}
		else
		{
			dc1.LineTo(PointHalfBase.x+p2.m_x,PointHalfBase.y-p2.m_y);
		}
//*/
	}
	///////////////////////////////////////////////////////
	dc1.MoveTo(PointHalfBase.x+0,PointHalfBase.y-(-100));
	dc1.LineTo(PointHalfBase.x+100,PointHalfBase.y-0);
	/////
	dc1.MoveTo(PointHalfBase.x+100,PointHalfBase.y-0);
	dc1.LineTo(PointHalfBase.x+0,PointHalfBase.y-100);
	/////
	dc1.MoveTo(PointHalfBase.x+0,PointHalfBase.y-100);
	dc1.LineTo(PointHalfBase.x+100,PointHalfBase.y-100);
	/////
	dc1.MoveTo(PointHalfBase.x+100,PointHalfBase.y-100);
	dc1.LineTo(PointHalfBase.x+200,PointHalfBase.y-200);
	/////
	dc1.MoveTo(PointHalfBase.x+200,PointHalfBase.y-200);
	dc1.LineTo(PointHalfBase.x+300,PointHalfBase.y-100);
	/////
	dc1.MoveTo(PointHalfBase.x+300,PointHalfBase.y-100);
	dc1.LineTo(PointHalfBase.x+400,PointHalfBase.y-100);
	/////
	dc1.MoveTo(PointHalfBase.x+400,PointHalfBase.y-100);
	dc1.LineTo(PointHalfBase.x+300,PointHalfBase.y-0);
	/////
	dc1.MoveTo(PointHalfBase.x+300,PointHalfBase.y-0);
	dc1.LineTo(PointHalfBase.x+400,PointHalfBase.y-(-100));
	/////
	dc1.MoveTo(PointHalfBase.x+400,PointHalfBase.y-(-100));
	dc1.LineTo(PointHalfBase.x+200,PointHalfBase.y-0);
	/////
	dc1.MoveTo(PointHalfBase.x+200,PointHalfBase.y-0);
	dc1.LineTo(PointHalfBase.x+0,PointHalfBase.y-(-100));
//*/
	///////////////////////////////////////////////////////
	/////////////
	gArrayAns.RemoveAll(); 
	gArray.RemoveAll(); 

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSDIShowView printing

BOOL CSDIShowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSDIShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSDIShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSDIShowView diagnostics

#ifdef _DEBUG
void CSDIShowView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIShowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIShowDoc* CSDIShowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIShowDoc)));
	return (CSDIShowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDIShowView message handlers

void CSDIShowView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
/*//��ثe�����j�p�ഫ���r��O���_��
	itoa(cx,p,10);
	itoa(cy,q,10);
	str1="X:";
	str1=str1+p;
	str1=str1+"Y:";
	str1=str1+q;
*/
	PointNowBase.x=cx;
	PointNowBase.y=cy; 
	// TODO: Add your message handler code here
	
}

void CSDIShowView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate(true);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
