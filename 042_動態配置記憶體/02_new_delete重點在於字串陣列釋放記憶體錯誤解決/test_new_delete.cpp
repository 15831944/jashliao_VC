#include<iostream>
using namespace std;
void main()
{
	char *p=new char[5];
	strcpy(p,"Hello");
	cout<<p<<"\n";
	p=NULL;
	delete []p;
	/*
	���I�����W�O���n��delete []p;����Ap=NULL;
	���o�˦bVC�|�X�{���~�T��
	*/
	int *int1;
	int1=new int[3];
	int1[0]=2;
	int1[1]=4;
	int1[2]=6;
	cout<< 5*int1[0]<<"\t"<< 5*int1[1]<<"\t"<< 5*int1[2]<<"\n";
	int1='\0';
	delete []int1;
	//int1='\0';
	/*
	���I�ƭȫ��Aint1='\0'�S���t�O
	*/

}