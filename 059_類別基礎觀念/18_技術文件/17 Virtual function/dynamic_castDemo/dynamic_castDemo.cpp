// �ϥ� dynamic_cast���d��: �N base class �������ন�l�����O������
//

#include "stdafx.h"
#include <iostream>
using namespace std;
class Base
    {
        public:
            virtual ~Base(){};
    };
class Derived: public Base
    {
        public:
            char const *toString()
            {
                return ("Derived object");
            }
	};
    int main()
    {
        Base   *bp,b;
        Derived  *dp,   d;

        bp = &d;
		//bp=&b;  // �L�k�ഫ��ex

        if ((dp = dynamic_cast<Derived *>(bp)))
            cout << dp->toString() << endl;
        else
            cout << "dynamic cast conversion failed\n";

        return (0);
    }

