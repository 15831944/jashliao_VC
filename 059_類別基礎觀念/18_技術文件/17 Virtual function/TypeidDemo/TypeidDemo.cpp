// TypeidDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

using namespace std;
#include <typeinfo.h>
class Base
    {
        public:
            virtual ~Base(){};		// �@�w�n�[�J virturla �Ѻc�l, typeid�~�|���`working
    };
class Derived: public Base
    {
        public:
            char const *toString()
            {
                return ("Derived object");
            }
	};

int main(int argc, char* argv[])
{
	Derived d;
	Base &br=d;
	Base *pb=&d;
	int kk=12;

	
	
		cout<< typeid(kk).name() << endl;   // �L�X �ܼ� kk �����A�W��: int
		cout<< typeid(br).name() << endl;   // �L�X br ��reference ���󪺫��A�W��: Derived
		cout<< typeid(pb).name() << endl;   // �L�X bp ����ƫ��A:Base* 
		cout<< typeid(*pb).name() << endl;  // �L�X bp �ҫ��V�����󫬺A�W��:Derived
	return 0;
}

