#include <stdio.h>
class Father
{
public:
	Father()
	{
	}
	~Father()
	{
	}
int FatherNumber;
};

class Mother
{
public:
	Mother()
	{
	}
	~Mother()
	{
	}
int MotherNumber;
};

class Son : public Father, public Mother
{
public:
	Son()
	{
	}
	~Son()
	{
	}
int SonNumber;
};

//�ϥ�Class���D�{������(.cpp):
void main()
{
Father* pFather = new Son();
Mother* pMother = new Son();

delete ((Son*)pFather); // <= ����ɨS���D
delete ((Son*)pMother); // <= Debug Assertion Failed
} 