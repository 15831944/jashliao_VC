#include <stdio.h>

int main(int argc, char** argv)
{
	char id[11];
	char no[26]={10,11,12,13,14,15,16,17,0,18,19,20,21,22,0,23,24,25,26,27,28,29,32,30,31,33};
	int value[11];
	int y=0;
	int i;
	printf("�п�J�����Ҧr��(�^��r���Фj�g):\t");
    scanf("%s",id);
	value[0]=(no[id[0]-65])/10;
	value[1]=(no[id[0]-65])%10;
    for (i=1;i<10;i++)
	{
		value[i+1]=id[i]-48;//ASCII->int
	}
    for (i=1;i<10;i++)
	{
		y += value[i]*(10-i);
	}

	y += (value[0]+value[10]);

	printf("y=%d\n",y);
	if (y%10==0)
	{
		printf("�����Ҧr�����ҥ��T!!\n");
	}
	else
	{
		printf("���������ҿ��~!!\n");
	}
	return 0;
}
