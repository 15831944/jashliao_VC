// test6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
void fun();
class Error1
{
public: 
	int data;
	Error1()
	{
		data=123;
	}
};

Error1 obj;                     // �w�q���ϰ쪫�� 
int main(int argc, char* argv[])
{
	try{
		fun();
	}
	catch(Error1 &errobj)
	{
		errobj.data=567;
	}
	return 0;                   // ok! �{�b���ϰ쪫���ܼ� obj.data ����?
}
void fun()
{
	throw obj;                  // throw �|�إ߷s������. 
}
