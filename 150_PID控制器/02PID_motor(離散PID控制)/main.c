#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
PID������ҡ]C++�^
//�����覡�ҥH�S�����ˮɶ��Ѽ�
��ƨӷ�: http://blog.sina.com.cn/s/blog_408540af0100as56.html

*/
typedef struct PID{
	double Command; //��J���O
	double Proportion;  //��ҫY��
	double Integral;   //�n���Y��
	double Derivative;  //�L���Y��
	double preErr;    //�e�@��~�t
	double sumErr;    //�~�t�ֿn
}PID;

double PIDCale(PID *p,double feedback)
{
	double dErr,Err;
	Err=p->Command-feedback;  //��e�~�t
	p->sumErr+=Err;      //�~�t�֥[
	dErr=Err-p->preErr;   //�~�t�L��
	p->preErr=Err;
	return(p->Proportion*Err  //��Ҷ�
	+p->Derivative*dErr   //�L����
	+p->Integral*p->sumErr);  //�n����
}
void PIDInit(PID *p)
{
	memset(p,0,sizeof(PID));  //��l��
}
typedef struct motor{
	double lastY;
	double preY;
	double lastU;
	double preU;
}motor;
void motorInit(motor *m)
{
	memset(m,0,sizeof(motor));
}
double motorCal(motor *m,double u)
{
	double y=1.9753*m->lastY-0.9753*m->preY+0.00003284*u+0.00006568*m->lastU+0.00003284*m->preU;//�G���t��
	m->preY=m->lastY;
	m->lastY=y;
	m->preU=m->lastU;
	m->lastU=u;
	return y;
}
void main()
{
	FILE *fp=fopen("data.txt","w+");
	PID sPID;
	double u;
	double y=0;
	PIDInit(&sPID);
	sPID.Proportion=2;//Kp
	sPID.Derivative=10;//Kd
	sPID.Integral=0.00001;//Ki
	sPID.Command=10;//setpoint
	motor m_motor;//������
	motorInit(&m_motor);
	int k=0;
	while(k<=1000)
	{
		fprintf(fp,"%f %f\n",y,sPID.Command);
		u=PIDCale(&sPID,y);
		y=motorCal(&m_motor,u);
		k++;
	}
	printf("%f\n",y);
	fclose(fp);
}

