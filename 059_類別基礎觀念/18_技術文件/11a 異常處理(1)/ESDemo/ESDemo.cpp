#include<iostream>
#include<string>
using namespace std;

void func() throw(string);
void func1() throw();

void main()
{
	try
	{
		func();
		func1();
		
	}
	catch(string mes)
	{
		cerr<<mes.c_str()<<endl;
	}
	catch(char *mes)
	{
		cerr<<mes<<endl;
	}
	catch(int msg)
	{
		cerr << "throw int\n";
	}

	
}
void func1() throw()                      // ���|��X����ҥ~
{
	                                      
	// throw "char *type error";          // ��X char* ���A���ҥ~
	// throw 1.0;                         // ��X float type���ҥ~, 
	                                      // �]��catch ���S�� float type ���ҥ~
	                                      // �S�����T��catch��,�h�|�o�� unexpected()�ҥ~
}
void func() throw(string)                 // �u�|��X string �ҥ~
{
	//throw string("abcdef");
	throw 1;                              // ���M��X���Oint,���O�٬O�i�H����!
}
