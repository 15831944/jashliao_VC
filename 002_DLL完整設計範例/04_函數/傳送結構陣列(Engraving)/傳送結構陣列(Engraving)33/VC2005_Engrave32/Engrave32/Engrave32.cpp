// Engrave32.cpp : �w�q DLL ����l�Ʊ`���C
//

#include "stdafx.h"
#include "Engrave32.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: �p�G�o�� DLL �O�ʺA�a�� MFC DLL �s���A
//		����q�o�� DLL �ץX������|�I�s
//		MFC �������禡�A�������b�禡�@�}�Y�[�W AFX_MANAGE_STATE
//		�����C
//
//		�Ҧp:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// ���B�����`�禡�D��
//		}
//
//		�o�ӥ����@�w�n�X�{�b�C�@��
//		�禡���A�~����I�s MFC �������C�o�N����
//		�������O�禡�����Ĥ@�ӳ��z��
//		�A�Ʀܥ����b���󪫥��ܼƫŧi�e��
//		�A�]�����̪��غc�禡�i��|���͹� MFC
//		DLL �������I�s�C
//
//		�аѾ\ MFC �޳N���� 33 �M 58 ����
//		�ԲӸ�ơC
//


// CEngrave32App

BEGIN_MESSAGE_MAP(CEngrave32App, CWinApp)
END_MESSAGE_MAP()


// CEngrave32App �غc
long EXPORTED_DLL_FUNCTION EngInitial(long lngBlockAmount,double tolerance,long Direction)//���oBlock�`�ơA�ðʺA�t�m�O����w�ΨӦs��C��Block��Entity�ƶq
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
long EXPORTED_DLL_FUNCTION EngGetValue(EngarveElement *p,long lngBlock,long lngAmount)
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
long EXPORTED_DLL_FUNCTION EngLineLineSolve(const CInputData &BaseInputData,const CInputData &RipInputData,const CPoint3D &RipPoint3D,CCircle *AnsCircle)
{
	double ang1=0.0,ang2=0.0;
	long data1=0,data2=0;
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
long EXPORTED_DLL_FUNCTION EngLineArcSolve(const CArc &BaseArc,const CLine &RipLine,const CPoint3D &RipPoint3D,CCircle *AnsCircle)
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
long EXPORTED_DLL_FUNCTION EngArcLineSolve(const CLine &BaseLine,CArc &RipArc,const CPoint3D &RipPoint3D,CCircle *AnsCircle)
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
long EXPORTED_DLL_FUNCTION EngArcArcSolve(const CArc &BaseArc,const CArc &RipArc,const CPoint3D &RipPoint3D,CCircle *AnsCircle)
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
long EXPORTED_DLL_FUNCTION ArcParagraph(CArc &data,const double tolerance)
{
	long i,number;
	bool blnEqual=true; 
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
	if(L!=(tolerance*10*number))
	{
		blnEqual=false;
	}
	if(number<=1)
		return 0;
	if(blnEqual==true)
		Point3DAns=new CPoint3D[number];
	else
		Point3DAns=new CPoint3D[number+1];
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
	if(blnEqual!=true)
	{
		Point3DAns[i].m_x=Center.m_x+R*cos(EndAngle);
		Point3DAns[i].m_y=Center.m_y+R*sin(EndAngle);
		Point3DAns[i].m_z=Center.m_z+0;
		number++;
	}
	return number;
}
long EXPORTED_DLL_FUNCTION LineParagraph(CLine &data,const double tolerance)
{
	double L;
	long i,number;
	bool blnEqual=true; 
	CVector Vector1;
	CPoint3D UnitVector1; 
	L=data.GetDistance();
	Vector1.SetData(data.m_StartPoint,data.m_EndPoint);
	UnitVector1=Vector1.GetUnitVector(); 
	number=(long)(L/(tolerance*20))+1;
	if(L!=(tolerance*20*(number-1)))
	{
		blnEqual=false;
	}
	if(number<=1)
		return 0;
	if(blnEqual==true)
		Point3DAns=new CPoint3D[number];
	else
		Point3DAns=new CPoint3D[number+1];
	for(i=0;i<number;i++)
	{
		Point3DAns[i].m_x=data.m_StartPoint.m_x+i*(tolerance*20)*UnitVector1.m_x;
		Point3DAns[i].m_y=data.m_StartPoint.m_y+i*(tolerance*20)*UnitVector1.m_y;
		Point3DAns[i].m_z=data.m_StartPoint.m_z+i*(tolerance*20)*UnitVector1.m_z;
	}
	if(blnEqual!=true)
	{
		Point3DAns[i]=data.m_EndPoint;
		number++;
	}
	return number;
}
long EXPORTED_DLL_FUNCTION EngCalculate()
{
	long lngEntityNumber=0;//�s�񤸥�ƶq
	long lngParagraphNumber=0;//�s����q�I���ƶq
	long i=0,j=0,k=0;//�T�h�j�骺�X���ܼ�
	long lngAnsNumber=0;//�D��M����|�w�I���ƶq
	long lngCheck=0;//�P�q�O�_����
	lngEntityNumber=(long)gArray.GetSize(); //���o����ƶq
	CPoint3D Point3DBuffer;//���q�I�Ȧs��
	CInputData InputDataBuffer;//��J����Ȧs��
	CInputData IDSmooth1,IDSmooth2;//���FSmooth Soluction�A��J����Ȧs��
	CVector VSmooth1,VSmooth2;//���FSmooth Soluction�A�V�q�Ȧs��
	CVector VSmooth3,VSmooth4;//���FSmooth Soluction�A�V�q�Ȧs��
	CRotateVector RV;//���F���ͦV�q���઺�B�⪫��
	CSmoothSolution SS;//mooth Soluction��ڭp�����O
	double dblSumAngle=0.0;//�s����ਤ��
	CVector VRoate,VRoateUnit;//Smooth Soluction�����ͪ�����V�q
	bool blnSmooth=false;//�P�_�O�_�n����Smooth
	bool blnNextEntiy=false;//�P�_�O�_�b���D��
	long lngSmoothnumber=0;//�P�_����Smooth������
	long lngSmoothAngle=0;//�s��Smooth�����ץ��t��
	CPoint3D P3DUnit;//�s��Smooth Soluction�B��L�{�����V�q
	CRipAngle2Vector RAV;//�DSmooth Soluction�����q�ƩM���ץ��t��
	CCircle CircleBuffer;//�Ȧs�D�X�Ӫ����
	double **DynamicArrayR;//�ʺA�t�m�G���O����A�Ψ��x�s�@�Ӥ��q�I�Ҧ�������b�|
	long l=0;//�ʺA�t�m�G���O����j�骺�X���ܼ�
	long m=0;//�ʺA�t�m�G���O������������ܼ�
	long n=0;//��ƪk���^�ǭȡA�M���o�Ƨǧ������G
	CCircleRightLeft CRLBuf;//�ΨӹB�����O�_�bentity���T��V
	bool blnCRL=false;//�Ψ��x�sCRLBuf�B�⵲�G
	long lngcount=0;//�Ψ��x�s����Pentity�ۥ榸��
	CNoSolution NSBuf;
	blnSmooth=false;
	blnNextEntiy=true;
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
		//for(j=0;j<lngParagraphNumber;j++)//��C�Ӥ��q�I�̧ǨD����//(2)
		//���X�۾F�����entity
		IDSmooth1=gArray[i];
		if((i+1)!=lngEntityNumber)
			IDSmooth2=gArray[i+1];
		else
			IDSmooth2=gArray[0];
		//���X�۾F�����entity
		j=0;
		do//��C�Ӥ��q�I�̧ǨD����//(2)
		{
			gArrayBuffer.RemoveAll();//����Ȧs�@�Ӥ��q�I�P�Ҧ�entity����CArray�M��
			Point3DBuffer=Point3DAns[j];//�̧ǧ���q�I���X
			/////////////////////////////////////////////
			//�P�_�T�{���q�I�O�_�Mentity�����I�ۦP->start
			if(blnSmooth==false&&blnNextEntiy==false)
			{
				if(IDSmooth1.m_lngLineArc==0)//LINE=0
				{
					if(fabs(IDSmooth1.m_Line.m_EndPoint.m_x-Point3DBuffer.m_x)<0.01&&
					   fabs(IDSmooth1.m_Line.m_EndPoint.m_y-Point3DBuffer.m_y)<0.01)
					{
						blnSmooth=true;
						VSmooth1.SetData(IDSmooth1.m_Line.m_StartPoint,IDSmooth1.m_Line.m_EndPoint);
						P3DUnit=VSmooth1.GetUnitVector();//���X���V�q
						P3DUnit=P3DUnit+VSmooth1.m_EndPoint;//�HVSmooth1.m_EndPoint���_�I�D���V�q�����I
						VSmooth3.SetData(VSmooth1.m_EndPoint,P3DUnit);//���ͷs�V�q
						/////////////////////////////////////////////////
						if(IDSmooth2.m_lngLineArc==0)//LINE=0
						{
							VSmooth2.SetData(IDSmooth2.m_Line.m_StartPoint,IDSmooth2.m_Line.m_EndPoint);
							P3DUnit=VSmooth2.GetUnitVector();//���X���V�q
							P3DUnit.m_x*=-1.0;//���V�q����
							P3DUnit.m_y*=-1.0;//���V�q����
							P3DUnit.m_z*=-1.0;//���V�q����
							P3DUnit=P3DUnit+VSmooth2.m_StartPoint;//�HVSmooth2.m_StartPoint���_�I�D���V�q�����I
							VSmooth4.SetData(VSmooth2.m_StartPoint,P3DUnit);//���ͷs�V�q  
						}
						else//ARC=1
						{
							long number=0;
							double L1=0.0,R=0.0;
							double StartAngle=0.0,EndAngle=0.0,UnitAngle=0.0;
							double tolerance=0.0;
							CPoint3D Center;
							CPoint3D P3DStart,P3DEnd;
							tolerance=dblTolerance;//���o�������t
							R=IDSmooth2.m_Arc.m_fltR;//���oentity2���b�|
							StartAngle=IDSmooth2.m_Arc.m_fltStartAngle;//���oentity2���_�l��
							EndAngle=IDSmooth2.m_Arc.m_fltEndAngle;////���oentity2���׭Ȩ�
							L1=sqrt(pow((2.0*PI*R*(EndAngle-StartAngle)/(2.0*PI)),2));//�p��entity2���P��
							number=(long)(L1/(tolerance*10))+1;//���oentity2�����q��
							UnitAngle=(EndAngle-StartAngle)*(tolerance*10)/L1;//entity2����쨤��
							Center=IDSmooth2.m_Arc.m_Point3DCenter;//���oentity2�����
							P3DStart.m_x=Center.m_x+R*cos(StartAngle);//���oentity2���_�l�I��m 
							P3DStart.m_y=Center.m_y+R*sin(StartAngle);
							P3DStart.m_z=Center.m_z+0;
							P3DEnd.m_x=Center.m_x+R*cos(StartAngle+1*UnitAngle);//���oentity2�_�l�I���U�@���q�I��m
							P3DEnd.m_y=Center.m_y+R*sin(StartAngle+1*UnitAngle);
							P3DEnd.m_z=Center.m_z+0;
							VSmooth2.SetData(P3DStart,P3DEnd);
							//////////////////////////////////
							P3DUnit=VSmooth2.GetUnitVector();//���X���V�q
							P3DUnit.m_x*=-1.0;//���V�q����
							P3DUnit.m_y*=-1.0;//���V�q����
							P3DUnit.m_z*=-1.0;//���V�q����
							P3DUnit=P3DUnit+VSmooth2.m_StartPoint;//�HVSmooth2.m_StartPoint���_�I�D���V�q�����I
							VSmooth4.SetData(VSmooth2.m_StartPoint,P3DUnit);//���ͷs�V�q  
						}
					}
					else
					{
						blnSmooth=false;
					}
				}
				else//ARC=1
				{
					//�p��꩷���I
					CPoint3D P3DArcEnd;
					P3DArcEnd.m_x=IDSmooth1.m_Arc.m_Point3DCenter.m_x+IDSmooth1.m_Arc.m_fltR*cos(IDSmooth1.m_Arc.m_fltEndAngle);//�p��entity1�����I��m     
					P3DArcEnd.m_y=IDSmooth1.m_Arc.m_Point3DCenter.m_y+IDSmooth1.m_Arc.m_fltR*sin(IDSmooth1.m_Arc.m_fltEndAngle);
					P3DArcEnd.m_z=IDSmooth1.m_Arc.m_Point3DCenter.m_z+0;
					//�P�_�꩷���I�M�M���q�I�O�_�ۦP
					if((P3DArcEnd.m_x==Point3DBuffer.m_x) && (P3DArcEnd.m_y==Point3DBuffer.m_y))
					{
						blnSmooth=true;
						long number=0;
						double L2=0.0,R=0.0;
						double StartAngle=0.0,EndAngle=0.0,UnitAngle=0.0;
						double tolerance=0.0;
						CPoint3D Center;
						CPoint3D P3DStart,P3DEnd;
						tolerance=dblTolerance;
						R=IDSmooth1.m_Arc.m_fltR;//���oentity1���b�|
						StartAngle=IDSmooth1.m_Arc.m_fltStartAngle;//���oentity1���_�l��
						EndAngle=IDSmooth1.m_Arc.m_fltEndAngle;//���oentity1���פ
						L2=sqrt(pow((2.0*PI*R*(EndAngle-StartAngle)/(2.0*PI)),2));//�p��entity1���P��
						number=(long)(L2/(tolerance*10))+1;//�p����q��
						UnitAngle=(EndAngle-StartAngle)*(tolerance*10)/L2;//�p���쨤��
						Center=IDSmooth1.m_Arc.m_Point3DCenter;//���oentity1�����
						P3DStart.m_x=Center.m_x+R*cos(EndAngle);//�p��entity1�����I��m 
						P3DStart.m_y=Center.m_y+R*sin(EndAngle);
						P3DStart.m_z=Center.m_z+0;
						P3DEnd.m_x=Center.m_x+R*cos(EndAngle-1*UnitAngle);//�p��entity1���I���e�@���q�I��m
						P3DEnd.m_y=Center.m_y+R*sin(EndAngle-1*UnitAngle);
						P3DEnd.m_z=Center.m_z+0;
						VSmooth1.SetData(P3DEnd,P3DStart);
						P3DUnit=VSmooth1.GetUnitVector();
						P3DUnit=P3DUnit+VSmooth1.m_EndPoint;
						VSmooth3.SetData(VSmooth1.m_EndPoint,P3DUnit);  
						///////////////////////////////////////
						if(IDSmooth2.m_lngLineArc==0)//LINE=0
						{
							VSmooth2.SetData(IDSmooth2.m_Line.m_StartPoint,IDSmooth2.m_Line.m_EndPoint);
							P3DUnit=VSmooth2.GetUnitVector();
							P3DUnit.m_x*=-1.0;
							P3DUnit.m_y*=-1.0;
							P3DUnit.m_z*=-1.0;
							P3DUnit=P3DUnit+VSmooth2.m_StartPoint;
							VSmooth4.SetData(VSmooth2.m_StartPoint,P3DUnit);
						}
						else//ARC=1
						{
							tolerance=dblTolerance;//���o�зǤ��t
							R=IDSmooth2.m_Arc.m_fltR;//���oentity2���b�|
							StartAngle=IDSmooth2.m_Arc.m_fltStartAngle;//���oentity2���_�l��
							EndAngle=IDSmooth2.m_Arc.m_fltEndAngle;//���oentity2���פ
							L2=sqrt(pow((2.0*PI*R*(EndAngle-StartAngle)/(2.0*PI)),2));//�p��entity2���P��
							number=(long)(L2/(tolerance*10))+1;//�p����q��
							UnitAngle=(EndAngle-StartAngle)*(tolerance*10)/L2;//�p���쨤��
							Center=IDSmooth2.m_Arc.m_Point3DCenter;//���oentity2�����
							P3DStart.m_x=Center.m_x+R*cos(StartAngle); //���oentity2���_�l�I��m
							P3DStart.m_y=Center.m_y+R*sin(StartAngle);
							P3DStart.m_z=Center.m_z+0;
							P3DEnd.m_x=Center.m_x+R*cos(StartAngle+1*UnitAngle);//���oentity2�_�l�I���U�@���q�I��m
							P3DEnd.m_y=Center.m_y+R*sin(StartAngle+1*UnitAngle);
							P3DEnd.m_z=Center.m_z+0;
							VSmooth2.SetData(P3DStart,P3DEnd);
							//////////////////////////////////
							P3DUnit=VSmooth2.GetUnitVector();
							P3DUnit.m_x*=-1.0;
							P3DUnit.m_y*=-1.0;
							P3DUnit.m_z*=-1.0;
							P3DUnit=P3DUnit+VSmooth2.m_StartPoint;
							VSmooth4.SetData(VSmooth2.m_StartPoint,P3DUnit);
						}
					}
					else
					{
						blnSmooth=false;
					}
				}
			}
			//�P�_�T�{���q�I�O�_�Mentity�����I�ۦP->end
			if((blnSmooth==true) && (lngSmoothnumber==0))
			{
				RAV.SetData(VSmooth4,VSmooth3);
				lngSmoothnumber=RAV.GetNumber();//�P�_����Smooth������
				lngSmoothAngle=RAV.GetUnitAngle();//�s��Smooth�����ץ��t��
				dblSumAngle=0.0;
			}
			if((blnSmooth==true) && (lngSmoothnumber>0))
			{
					lngSmoothnumber--;
					CPoint3D P3Dbuf1;
					CPoint3D P3Dtemp(0.0f,0.0f,0.0f);
					dblSumAngle+=lngSmoothAngle;//�s����ਤ��
					RV.SetData(VSmooth4);
					VRoate=RV.Rotate(2,dblSumAngle);//Smooth Soluction�����ͪ�����V�q
					P3Dbuf1=VRoate.GetUnitVector();
					P3Dtemp=P3Dtemp+Point3DBuffer;
					P3Dbuf1=P3Dbuf1+Point3DBuffer;
					VRoateUnit.SetData(P3Dtemp,P3Dbuf1); 
			}
			for(k=0;k<lngEntityNumber;k++)//�̧ǩM��L��entity�@�B��//(3)
			{
				if(i==k)
					continue;//�P�@��Entity���κ�
				InputDataBuffer.Reset();//�M�żȦs�� 
				InputDataBuffer=gArray[k];//���X�۹諸entity
				if(blnSmooth==false)
				{
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
				}
				else//blnSmooth==true
				{
						if(InputDataBuffer.m_lngLineArc==0)
						{
							SS.SetData(VRoateUnit,InputDataBuffer.m_Line); 
						}
						else
						{
							SS.SetData(VRoateUnit,InputDataBuffer.m_Arc);
						}
						lngCheck=SS.GetAns(&CircleBuffer);
				}
				//if(blnSmooth==false)
				//{
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
										if(blnSmooth==false)
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
										if(blnSmooth==false)
										{
											bool CheckEx=false;
											CheckEx=CircleBuffer.CheckExcircle(InputDataBuffer.m_Line);
											if(CheckEx==false)
											{
												lngCheck=0;
												break;
											}
										}
										else//blnSmooth==true
										{
											double angle1,angle2;
											CPoint3D P3D1,P3D2;
											int Ansnumber;
											Ansnumber=CircleBuffer.CircleLine(InputDataBuffer.m_Line,&angle1,&angle2,&P3D1,&P3D2);
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
										}
									}
							}
						}
					}
				//}
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
				{
					gArrayBuffer.Add(CircleBuffer);
					///////////////////////////////////////////////////
					if(((i+1-k)==0))
						blnNextEntiy=true;//�۾F��entity
					else
						blnNextEntiy=false;//�D�۾F��entity
				}
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
				//////////////////////////////////////////////////
				for(l=0;l<m;l++)//����ʺA�G���O����
					delete [] DynamicArrayR[l];
				delete [] DynamicArrayR;
			}
			if(lngSmoothnumber<=0)
			{
				j++;
				blnSmooth=false;
			}
		}while(j<lngParagraphNumber);//(2)
		delete [] Point3DAns;//����ʺA�@���O����
	}//(1)
	lngAnsNumber=gArrayAns.GetSize();
	FILE *pfAns;
	pfAns=fopen("Ans.txt","w");
	CCircle CC1;
	for(i=0;i< lngAnsNumber;i++)
	{
		CC1=gArrayAns[i];
		fprintf(pfAns,"%f\t%f\t%f\n",CC1.m_Point3DCenter.m_x,CC1.m_Point3DCenter.m_y,CC1.m_fltR);   
	}
	fclose(pfAns);
	delete [] Point3DCross;
	return lngAnsNumber;
}
long EXPORTED_DLL_FUNCTION BubbleSort(double **p,long n)
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
CEngrave32App::CEngrave32App()
{
	// TODO: �b���[�J�غc�{���X�A
	// �N�Ҧ����n����l�]�w�[�J InitInstance ��
}


// �Ȧ����@�� CEngrave32App ����

CEngrave32App theApp;


// CEngrave32App ��l�]�w

BOOL CEngrave32App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
