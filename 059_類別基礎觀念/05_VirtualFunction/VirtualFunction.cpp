#include <iostream.h>
#include <stdio.h>
class father
{
public :
	void test();
	virtual void f1();
};
void father::test()
{
	cout<<"it's father's test"<<"\n";
}
void father::f1()
{
	cout<<"it's father's virtual function"<<"\n";
}
class child:public father
{
public :
	void test();
	void f1();
};
void child::test()
{
	cout<<"it's child's test"<<"\n";
}
void child::f1()
{
	cout<<"it's child's virtual function"<<"\n";
}
void main()
{
	child c1;
	father f1;
	father *fp;
	/////////////�l�s���l
	c1.test();
	c1.f1(); 
	////////////���s����
	f1.test();
	f1.f1(); 
	////////////�l�s����
	c1.father::test();
	c1.father::f1();
	////////////
	fp=&c1;//�����o�l������
	fp->test();///���s����
	fp->f1();///���s���l
}