#include<iostream.h>

void func();

void main()
{
	try
	{
		func();
	}
	catch(int& code)
	{
		cerr<<code<<endl;
		throw;   //�[�J����h�I�sC++ Standard Library�� Terminate().
	}
}

void func()
{
	try
	{
		throw -1;
	}
	catch(int& code)
	{
		cerr<<code<<endl;
		code=100;
		throw;
	}
}