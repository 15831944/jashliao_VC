// VirtualDerived.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//�����~�� �d��
class Base {
public:
	int getWeight() {         
		return 10;
	}
};
class Land:virtual public Base {
};
class Air:virtual public Base{
};
class AirAuto:public Land,public Air {
};
int main(int argc, char* argv[])
{
	AirAuto cool;
	int weight=cool.getWeight();               // �[�J�����~�ӫ�,���|��ambigous�����D�F
	// int weight=cool.Land::getWeight();
	return 0;
}

