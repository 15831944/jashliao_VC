#include <stdio.h>
#include "staticfun.h"
void main()
{
	//Class��public��ƥu���b�ŧi��static�~�i�H�b�D�ŧi����ɿW�ߨϥ�
	int a1,b1,c1;
	double a2,b2,c2;
	a1=1;b1=2;
	a2=1.0;b2=2.0;
	c1=Cstaticfun::add(a1,b1);
	//c2=Cstaticfun::dot(a2,b2);
	Cstaticfun sf;
	c2=sf.dot(a2,b2);
}