#include<iostream.h>

void main()
{
	try
	{
		cout<<"1. 123    2. String    3. 345.678\n�z�n��X����exception?";
		int a;
		cin>>a;
		switch(a)
		{
		case 1: throw 123;
		case 2: throw "String";
		default: throw 345.678;
		}
	}
	catch(int mes)
	{
		cerr<<mes<<endl;
	}
	catch(char* mes)
	{
		cerr<<mes<<endl;
	}
	catch(...)  //�����b�̫�@��
	{
		cerr<<"��L��exception.\n";
	}
}