#include <iostream>
using namespace std;
void main()
{
	int i=0;
	int intnumber=0;
	double *pdblInput,*pdblOutput;
	double dblDenominator=0.0,dblNumerator=0.0,dblAnswer=0.0;
	cout <<"��J��Ƥ��"<<"\n";
	cin >>intnumber;
	pdblInput=new double [intnumber];
	pdblOutput=new double [intnumber]; 
	cout <<"�Ш̧ǿ�J�C�@�չ���ƾ�(��J ��X)"<<"\n";
	for (i=0;i<intnumber;i++)
	{
		cout <<"�п�J��"<<(i+1)<<"��"<<"\n";
		cin >>pdblInput[i]>>pdblOutput[i];
		dblDenominator+=pdblInput[i]*pdblInput[i];
		dblNumerator+=pdblInput[i]*pdblOutput[i];
	}
	dblAnswer=dblNumerator/dblDenominator;
	cout<<"�̨ΰѼƸѬ�Y="<<dblAnswer<<"X"<<"\n";
}