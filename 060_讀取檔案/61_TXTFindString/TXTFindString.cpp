#include<stdio.h>
#include<fstream.h>
#include <stdlib.h>
#include <string.h>
void main(void)
{
	fstream a;
	char fg[700];
	char check[700];
	char *loc;
	bool blnfind=false;
	int intcount=0;
	cout<<"input a check string ="<<"\t";
	cin.getline(check, 700);
	a.open("media.txt",ios::in);
	while(!a.eof())
	{
		intcount++;
		a.getline(fg,700);
		loc = strstr(fg, check);
		if(loc != NULL)
		{
			cout<< "�ɮפ��e= " << fg <<"\n";
			cout<< "������e= " << check <<"\n";
			printf("�渹%d�B���l�r��\n",intcount);
			printf("�b���ަ�m %d �B���l�r��\n", loc - fg);
			blnfind=true;
			break;
		}
	}
	if(blnfind==false)
		printf("�䤣��ŦX���l�r��\n");
	a.close();
}