#include <iostream>
using namespace std;
char chrData;
void number2char(int intdata)
{
	if((intdata>=0) &&(intdata<10))
	{
		chrData=(48+intdata);//48->'0'
	}
	else
	{
		chrData=(97+(intdata-10));//97->a�A�Ʀr10->a
	}
}
void main()
{
	int i;
	cout <<"��J�ഫ�Ʀr"<<"\t";
	cin >>i;
	if(i<36)//0~35
	{
		number2char(i);
		cout <<"�ഫ���G"<<"\t"<<chrData<<"\n";
	}
	else
	{
		cout <<"���A�ഫ�d��"<<"\n";
	}
}