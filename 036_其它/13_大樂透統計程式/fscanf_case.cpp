#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
#include <time.h>
void main()
{
	FILE *p;
	int a[7];//�C�@�����X
	int i,k,j,temp[2],key;//��ƪk�ܼ�
	int number[50];//�s��C�@�Ӹ��X�X�{����
	int sol[50][2];//��w�ƧǪ����G�C0���Ʀr�C1������
	int sum[50][2];//�έp���v���
	int intSwitch;//����U��
	int SwitchNumber[7];
	for(i=0;i<50;i++)
		number[i]=0;
/////////////////////////////////
	p=fopen("�}�����X.txt","r");//Ū���}�����X
	while(fscanf(p,"%d%d%d%d%d%d%d",(a+0),(a+1),(a+2),(a+3),(a+4),(a+5),(a+6))!=EOF)
	{
		for(i=0;i<7;i++)
		{
			k=a[i];
			number[k]+=1;
		}
	}
///////////////////////////////
	for(i=0;i<50;i++)//��l�Ƨǫe�����
	{
		sol[i][0]=i;
		sol[i][1]=number[i];
	}
//////////////////////////////
	for(i=0;i<50;i++)//��w�ƧǥD��
	{
		key=0;
		for(j=0;j<50-i-1;j++)
		{
			if(sol[j][1]<sol[j+1][1])
			{
				temp[1]=sol[j][1];
				sol[j][1]=sol[j+1][1];
				sol[j+1][1]=temp[1];
				////////////////////////
				temp[0]=sol[j][0];
				sol[j][0]=sol[j+1][0];
				sol[j+1][0]=temp[0];
				key=1;
			}
		}
		if(key==0)
			break;
	}
//////////////////////////////
		for(k=0;k<50;k++)//��ܱƧǵ��G
			cout <<sol[k][0]<<"\t";
		cout <<"\n";
		for(k=0;k<50;k++)
			cout <<sol[k][1]<<"\t";
		cout <<"\n";
/////////////////////////////////
		for(k=0;k<50;k++)//�έp���v��ƪ�l��
		{
			sum[k][0]=0;//�X��
			sum[k][1]=0;//����

		}
/////////////////////////////
		key=0;
int count=0;
		int index=0;
		int index1=0;
		for(k=0;k<50;k++)//�έp���v�D��
		{
			if(key!=sol[k][1])//���Ƥ��P
			{
				sum[index][0]=k;
				sum[index][1]+=1;
				key=sol[k][1];
				index++;
				count=0;
			}
			else
			{
				if(count==0)
				{
					index1=index;
					index1--;
					count++;
				}
				sum[index1][1]+=1;
			}
		}
//////////////////////////////////////////////
		for(k=0;k<50;k++)//��ܲέp���
			cout <<sum[k][0]<<"\t";
		cout <<"\n";
		for(k=0;k<50;k++)
			cout <<sum[k][1]<<"\t";
		cout <<"\n";
//////////////////////////////////////////
///*
intSwitch=7;//�j�ֳz7�Ӹ��X
k=0;//Ū�����vindex
i=0;//Ū���Ʀrindex
j=0;//����index
int Getnumber1,Getnumber2;//1�����v���ƭȡA2����ڼƦr
int buffer1;
//SwitchNumber[6]
do
{
	Getnumber1=sum[k][1];
	
	if(intSwitch>=Getnumber1)
	{
		intSwitch-=Getnumber1;
		for(i=0;i<Getnumber1;i++)
		{
			buffer1=(i+sum[k][0]);
			Getnumber2=sol[buffer1][0];
			SwitchNumber[j]=Getnumber2;
			j++;
		}
	}
	else
	{
		int intRand;
		int *intRandBuffer;
		////////////////
		int l,y,m;
		intRandBuffer=new int[Getnumber1];
		for(l=0;l<Getnumber1;l++)
			*(intRandBuffer+l)=-1;
		m=0;//�ʺA�O����index
		////////////////
		do
		{
			srand((unsigned)time(NULL));//�üƺؤl��l��
			intRand=(rand()%(Getnumber1));//���X0��(Getnumber1-1)���ü�
			y=0;//�P�_�O�_�ۦP�X��
			for(l=0;l<Getnumber1;l++)
			{
				if(intRand!=*(intRandBuffer+l))
				{
					y=1;
				}
				else
				{
					y=0;
					break;
				}
			}
			if(y==1)
			{
				*(intRandBuffer+m)=intRand;
				m++;
				buffer1=(intRand+sum[k][0]);
				Getnumber2=sol[buffer1][0];
				SwitchNumber[j]=Getnumber2;
				j++;
				intSwitch--;
			}
		}while(intSwitch>0);
	}
	k++;	
}
while(intSwitch>0);
printf("OUTPut:%d\t%d\t%d\t%d\t%d\t%d\t%d\n",SwitchNumber[0],SwitchNumber[1],SwitchNumber[2],SwitchNumber[3],SwitchNumber[4],SwitchNumber[5],SwitchNumber[6]);
//*/
////////////////////////////////////////////
	fclose(p);
}