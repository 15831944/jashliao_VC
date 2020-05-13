#include <stdio.h>
#include <iostream.h>
struct point_data
{
	float x,y;
};
class CP
{
/*
	���O�����Ѫ��{���X�A���]�O���i�A�и��޼ƬۦP���	
*/
public:

	struct point_data data;
	CP();
	~CP();
	void operator++();
	//CP operator++();
	void operator--();
	//CP operator--();
	CP operator+(CP a);
	CP operator-(CP a);
	CP operator*(CP a);
	CP operator/(CP a);
	bool operator==(CP a);

};
CP::CP()
{
	data.x=0;
	data.y=0; 
}
CP::~CP()
{
}
void CP::operator ++()
{
	data.x=data.x+1;
	data.y=data.y+1;
}
void CP::operator --()
{
	data.x=data.x-1;
	data.y=data.y-1;
}
CP CP::operator +(CP a)
{
	CP temp;
	temp.data.x=data.x+a.data.x;
	temp.data.y=data.y+a.data.y;
	return temp;
}
CP CP::operator -(CP a)
{
	CP temp;
	temp.data.x=data.x-a.data.x;
	temp.data.y=data.y-a.data.y;
	return temp;
}
CP CP::operator *(CP a)
{
	CP temp;
	temp.data.x=data.x*a.data.x;
	temp.data.y=data.y*a.data.y;
	return temp;
}
CP CP::operator /(CP a)
{
	CP temp;
	temp.data.x=data.x/a.data.x;
	temp.data.y=data.y/a.data.y;
	return temp;
}
bool CP::operator ==(CP a)
{
	bool b;
	if((data.x==a.data.x) && (data.y==a.data.y))
		b=true;
	else
		b=false;
	return b;
}
/*
CP CP::operator ++()
{
	CP temp;
	data.x=data.x+1;
	data.y=data.y+1;
	temp.data=data;
	return temp;
}
CP CP::operator --()
{
	CP temp;
	data.x=data.x-1;
	data.y=data.y-1;
	temp.data=data;
	return temp;
}
*/
void main()
{
	CP a,b,c;
	if(a==b)
		printf("��l���ܼƬۦP\n");
	else
		printf("��l���ܼƥ���\n");
	a.data.x=10;
	a.data.y=10;
	b.data.x=10;
	b.data.y=10;
	c=a+b;
	cout <<"�[�k"<<"\n"; 
	cout<<c.data.x<<"\t"<<c.data.x<<"\n";  
	c=a-b;
	cout <<"��k"<<"\n"; 
	cout<<c.data.x<<"\t"<<c.data.x<<"\n";
	c=a*b;
	cout <<"���k"<<"\n"; 
	cout<<c.data.x<<"\t"<<c.data.x<<"\n";
	c=a/b;
	cout <<"���k"<<"\n"; 
	cout<<c.data.x<<"\t"<<c.data.x<<"\n";
}