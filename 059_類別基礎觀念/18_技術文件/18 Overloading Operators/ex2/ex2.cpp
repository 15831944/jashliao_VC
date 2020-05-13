// ex2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <stdlib.h>		// for exit()
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

	/*
	Complex add(Complex &b)
	{
		return Complex(re+b.re,im+b.im);
	}
	*/
	Complex operator+(Complex &b)
	{
		return Complex(re+b.re,im+b.im);
	}

	// �U�Ъ��d��
	double operator[](int i)
	{
		
		if(i==0)
			return re;
		else
		if(i==1)
			return im;
		else
		{
			cout<<"error\n";
			exit(1);
		}

	}

	// �޿赥��  (==) �d��
	bool operator==(Complex &b)
	{
		if(re==b.re && im==b.im)
			return true;
		else
			return false;
		
	}

	// ���k �d��
	Complex operator*(Complex &b)
	{
		return Complex(re*b.re,im*b.im);
	}

	// +=���d��
	void operator+=(Complex &b)
	{
		re=re+b.re;
		im+=b.im;
	}
};

int main(int argc, char* argv[])
{
	
	Complex a(2,3),b(3,4);
	Complex c=a+b;

	// �U�Ъ��d��
	double cRE=c[0];
	double cIM=c[1];

	// �޿赥��  (==) �d��
	if(a==b)
		cout<<"a����b"<<endl;
	else
		cout<<"a������b"<<endl;


	Complex d=a*b;	

	a+=b;
	// a++;          �S�w�q ++
	return 0;
}

