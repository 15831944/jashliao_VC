// Ex6Transfer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
class B
{
	double value;
public:
	B()
	{
		value=0;
	}
	B(double i)
	{
		value=i;
	}
};
class Complex
{
private:
	double re,im;
	
public:
	Complex(double argre,double argim)
	{
		re=argre;im=argim;
	}
	Complex()
	{
		re=0;im=0;
	}
	// ����ഫ��Complex�d��
	Complex(int i)
	{
		re=i;
		im=0;
	}
    // Complex�ഫ�� double ���d��
	operator double()
	{
		return re;
	}
	
	// Complex�ഫ�� �t�@�� object���d��
	operator B()
	{
		return B(re);
		/* ��
			return re;
		*/

	}
};
int main(int argc, char* argv[])
{
	Complex a=3;      // ����ഫ��Complex�d��
	
	double dValue=a;  // Complex�ഫ�� double ���d��
	

	B b=a;             // Complex�ഫ�� �t�@�� object���d��
	return 0;
}

