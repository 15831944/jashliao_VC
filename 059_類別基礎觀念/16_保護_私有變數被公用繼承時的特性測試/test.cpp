#include <iostream>
using namespace std;
class A
{
public:
	A();
	setvalue(int,int);
	printvalue();
private:
	int m_a;
protected:
	int m_b;

};
A::A()
{
	m_a=0;
	m_b=0;
}
A::setvalue(int a,int b)
{
	m_a=a;
	m_b=b;
}
A::printvalue()
{
	printf("m_a=%d\tm_b=%d\n",m_a,m_b);
}
class B : public A
{
public:
	B();
	setvalue(int,int);
	printvalue();
private:
	int m_a;
protected:
	int m_c;
};
B::B():A()
{
	m_a=0;
	m_c=0;
}
B::setvalue(int a,int b)
{
	m_a=a;
	m_c=b;
	//A::m_a=b;//���X�k �]��private�ܼƧQ��public�~�� �ҥH��private�ܼ��٬O�����O��private�ܼ�
	//A::m_b=b;//�X�k �]��protected�ܼƧQ��public�~�� �ҥH��protected�ܼƷ|�����l���O��private�ܼ�
}
B::printvalue()
{
	printf("m_a=%d\tm_c=%d\n",m_a,m_c);
}

void main()
{
	A a;
	B b;
	a.setvalue(10,20);
	a.printvalue();
	b.A::setvalue(20,30);
	b.A::printvalue();
	b.setvalue(10,40);
	b.printvalue();
}