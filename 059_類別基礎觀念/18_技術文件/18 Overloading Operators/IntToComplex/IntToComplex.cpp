// IntToComplex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
class Complex {
private:
	int re,im;
public:
	Complex()
	{
		re=0;im=0;
	}
	// ����ഫ��Complex���w�q
	Complex(int i)
	{
		re=1;
		im=0;
	}
};
int main(int argc, char* argv[])
{
	Complex a=3;                   // �|�I�s�غc�l Complex(int i)
	return 0;
}

