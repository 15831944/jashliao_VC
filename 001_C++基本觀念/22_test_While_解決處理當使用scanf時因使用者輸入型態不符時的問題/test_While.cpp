#include <stdio.h>
/*
���]�H�U�O�{����
int a;
while(1)
{
   scanf("%d",&a);
}
�M��O
���ӬO�L���j�� ~ ����b�C���^�����ӳ��i��J�@���Ʀr!
�n~�O�o�˨S�� !
���O�������J�^��r��~�L���|�A�I�s   scanf  �|�����L�a�j��U�h !!

�M��ڰݤ@�U , �b int  %d �̥��^�� , ���O���ӼƦr�|�ܦ�0��??

�p�G�n�P�_�A��J���۬O���O���T��
�i�H�o�˶�
//////////////////////////////////////////////////////////////
�ѵ�
��J�^���A�]�����ӭ^���٬O�S���QŪ�i�ӡA�ҥH�|�ݦs�ۡA�U��scanf�٬O�]���O�^��ҥH�Ǧ^0
�i�H�P�_�p�G��J���~�N�A scanf �@���A���o���O���� %s�A���O%d�A�o�˴N�i�H�⨺�ӭ^�屵���A
int a;
char b[256];
while(1)
{
  if(scanf("%d", &a)==0)
    scanf("%s", b);
} 
*/
void main()
{
	int a=0;
	char b[256];
	while(1)
	{
		printf("key in a int value\t");

		if(scanf("%d", &a)==0)
		{
			scanf("%s", b);
			printf("you input the data %s\n",b);
		}
		printf("you input the data %d\n",a);
	}
}