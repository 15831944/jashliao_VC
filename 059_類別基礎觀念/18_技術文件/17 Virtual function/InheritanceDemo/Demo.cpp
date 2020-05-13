// Demo.cpp: implementation of the Demo class.
//
//////////////////////////////////////////////////////////////////////
#include<iostream.h>
#include "Demo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Demo::Demo(int na):Base(na)
{
	cout<<this<<"  Demo's constructor\n";
}

Demo::~Demo()
{
	cout<<this<<"  Demo's destructor\n";
}

void main()
{
	Demo *dmp=new Demo(12000);
	dmp->Print();
	delete dmp;
	cout<<endl;

	Base *bsp=new Demo(345);
	((Demo*)bsp)->Print();	// �]��bsp�OBase class���ЩҥH
							//�n���j���ഫ��Demo class ���Ы��O,�~��I�sPrint()
	delete bsp;
	cout<<endl;

	Demo dm(0);
	dm.Set(68000);
	dm.Print();
}

void Demo::Set(int na)
{
	a=na;
}

void Demo::Print()
{
	cout<<a<<endl;
}
