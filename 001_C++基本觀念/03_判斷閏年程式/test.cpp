#include <iostream>
using namespace std;
void main(void)
{
	int intYears=0;
	cout<<"��J�n�P�_���~��   ";
	cin >>intYears;
	if((intYears%4==0 && intYears%100!=0)||(intYears%400==0))
		cout<<"��J�O�|�~"<<"\n";
	else
		cout<<"��J���O�|�~"<<"\n";
}