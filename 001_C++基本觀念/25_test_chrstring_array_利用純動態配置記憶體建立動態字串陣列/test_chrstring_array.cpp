#include <iostream>
/*
�Q�ί°ʺA�t�m�O����إ߰ʺA�r��}�C
*/
using namespace std;
void main()
{
	char **chrdata;
	char data[100];
	chrdata=new char*[2];;
	for(int i=0;i<2;i++)
		chrdata[i]=new char[100];
	cin>>data;
	strcpy(*(chrdata+0),data);
	cin>>data;
	strcpy(*(chrdata+1),data);
	cout<<*(chrdata+1)<<"\t"<<*(chrdata+0)<<"\n";
}