// Ex3Friend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
class Complex
{
		//�ŧi operator+ �O Complex���n�B��
	friend Complex operator+(Complex &a,Complex &b);
private:
	double re,im;
public:
	Complex(double argre,double argim)
	{
		re=argre;im=argim;
	}

	// --���d��
	Complex& operator--()  // �Ǧ^ reference type
	{
		re=re-1;
		im=im-1;
		return *this;
	}
	Complex()
	{
		re=0;im=0;
	}


};
//�w�q operator+�����e
Complex operator+(Complex &a,Complex &b)
{
	return Complex(a.re+b.re,a.im+b.im);
}
int main(int argc, char* argv[])
{
	Complex a(2,3),b(3,4);

	Complex c=a+b;
	a--;

	return 0;
}

