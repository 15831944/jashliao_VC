#include <iostream>
using namespace std;
/*
�Q�λ��j�覡�D�̤j���]�ƩM�D��̤p������
*/
int gcd_1(int a,int b)//�D�̤j���]��_1_�H����۴�k
{
	if(a==b)
		return a;
	if(a>b)
		return gcd_1(a-b,b);
	return gcd_1(a,b-a);
}
int gcd_2(int a,int b)//�D�̤j���]��_2_�H����۰��k
{
	int c=0;
	c=a%b;
	if(c==0)
		return b;
	return gcd_2(b,c);
}
int lcm(int a,int b)//�D��̤p������
{
	return b/gcd_1(a,b)*a;
}
void main(void)
{
	int a,b,c;
	a=30,b=45;
	c=gcd_1(a,b);
	cout<<c<<"\t";
	c=gcd_2(a,b);
	cout<<c<<"\t";
	c=lcm(a,b);
	cout<<c<<"\t";

}