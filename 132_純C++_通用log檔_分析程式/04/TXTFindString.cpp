#include<stdio.h>
#include<fstream.h>
#include <stdlib.h>
#include <string.h>
struct check_struct
{
	char chrfindstring[100];
	char chrlogname[100];
	char chrmessage[100];
	int intcount;
};
void main(int argc, char *argv[])
{
	fstream a;//�Ψ�Ū��log��
	fstream checkfile;//�Ψ�Ū�����R�]�w��
	char fg[700];//�s��C�@��log
	char filename[80];//�s��log�ɪ��ɦW
	char check[700];//�s��C�@����R�]�w�ɸ��,���r��
	char *loc;//�s�����r��᪺���G
	int intcount=0;//�Ψӭp�ⵧ��
	if(argc<2)
	{
		/////////////////////////////////////////
		cout<<"input a File Name ="<<"\t";
		cin.getline(filename,80);
		/////////////////////////////////////////
	}
	else
	{
		strcpy(filename,argv[1]);
	}
	//�p����R�]�w�ɪ�����
	checkfile.open("check.txt",ios::in);
	while(!checkfile.eof())
	{
		checkfile.getline(check,500);
		if(strlen(check)>0)
			intcount++;
	}
	checkfile.close();
	//====
	//�t�m�O����ñN���R�]�w�ɸ��J�O����
	char buf0[100],buf1[100],buf2[100];
	struct check_struct *cs;
	cs=new struct check_struct[intcount];
	checkfile.open("check.txt",ios::in);
	intcount=0;
	while(!checkfile.eof())
	{
		checkfile.getline(check,500);
		if(strlen(check)>0)
		{
			sscanf(check,"%[^','],%[^','],%[^','],",buf0,buf1,buf2);
			strcpy((cs+intcount)->chrfindstring,buf0);
			strcpy((cs+intcount)->chrlogname,buf1);
			strcpy((cs+intcount)->chrmessage,buf2);
			(cs+intcount)->intcount=0;
			intcount++;
		}
	}
	checkfile.close();
	///////////////////////////////////////
	//�i���ɮפ��R
	int i;
	a.open(filename,ios::in);
	FILE *pf;
	FILE *pfdata;
	while(!a.eof())
	{
		a.getline(fg,700);
		for(i=0;i<intcount;i++)
		{
			strcpy(check,(cs+i)->chrfindstring);
			loc = strstr(fg, check);
			if(loc!='\0')
			{
				pfdata='\0';
				pfdata=fopen((cs+i)->chrlogname,"a");
				fprintf(pfdata,"%s\n",fg);
				fclose(pfdata);
				pfdata='\0';
				(cs+i)->intcount++;
			}
		}
	}
	pf=fopen("log.txt","w");
	for(i=0;i<intcount;i++)
	{
		fprintf(pf,"%s,%d\n",(cs+i)->chrmessage,(cs+i)->intcount);
	}
	fclose(pf);
	a.close();
	delete []cs;
}