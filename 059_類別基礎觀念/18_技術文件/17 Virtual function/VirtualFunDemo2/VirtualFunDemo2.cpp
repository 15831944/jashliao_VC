
#include "stdafx.h"
class Base 
{
public:
	int BaseData;
	Base()
	{
		BaseData=0;
	}
	virtual ~Base()
	{
		BaseData=1;
	}
	
};
class Derived:public Base
{

public:
	int DerivedData;
	Derived():Base()
	{
		DerivedData=0;
	}
	~Derived()
	{
		DerivedData=1;
	}
};

int main(int argc, char* argv[])
{
	/*
	Delete Derived �|�I�s Derived�����Ѻc��,
	���O�{���|�~��I�s Base ���Ѻc����?

    <sol> �O��. 
		�Ѻc�����Ǭ� 
			~Derived() -> ~Base()
    */

	Derived *Dobj=new Derived();
	Base *Bobj;

	Bobj=Dobj;
	
	delete Bobj;
	return 0;
}

