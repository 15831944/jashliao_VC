#include <iostream>
using namespace std;
//C�y�����B�~�W�[�ܼƱN2���ܼƭȤ���!
void main()
{	
    float a=9.004, b=-28.5;
	//�@���k... for int or float
    _asm {
     push a
     push b
     pop a
     pop b}
    cout<< a <<"  "<<b<<"\n";
} 