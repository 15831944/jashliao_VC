#include <stdio.h>
#include <stdlib.h>
/*
C�y���G�����ܼơA�����ϰ��ܼơA�ϰ��R�A�ܼơAx++�A++x��X�[���d��
*/
int x=5;
void f(int x)
{
	printf ("%d\n", x++);
}
void g(void)
{
	static int x=0;
	printf ("%d\n", x++);//�ϰ��ܼ�x��X��+1
}
void main ()
{
	printf ("%d\n", ++x);//�����ܼ�x��+1���X---->5+1=6
	{
		int x=4;
		printf ("%d\n" ,x++);//�ϰ��ܼ�x��X��+1---->4
	}
	g();//�R�A�ϰ��ܼ�x��X��+1---->0
	f(x);//�����ܼ�x��X��+1---->6
	g();//�R�A�ϰ��ܼ�x��X��+1---->1
}
/*
6
4
0
6
1
*/
