#include <iostream>
using namespace std;
void main()
{
	int a=0;
	int b=0;
	float k=0.0f;
	cout <<"��J�~�~:";
	cin >>a;
	cout <<"��J�X�Ӥ�";
	cin >>b;
	try
	{
		if(a==0)
			throw 0;
		if(b==0)
			throw 1;
		cout<<"���~= "<<(k=(float)a/(float)b)<<"\n";
	}
	catch(int err)
	{
		if(err==0)
			cout <<"�S���~���A�|�j��"<<"\n";
		else
			cout <<"�m�Ӫ��A�|�P�D"<<"\n";
	}
}