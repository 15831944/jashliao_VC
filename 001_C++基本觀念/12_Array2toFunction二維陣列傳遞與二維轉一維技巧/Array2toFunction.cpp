#include <stdio.h>
/*
�ѵ{���i�H�o�{�ѤG����@���N�i�H���Ϋ��w�}�C���סA�{�����F��
�����I�O�n���ഫ����
*/
void ShowArray(int *a)
{
	int i,j,k;
	int x=3;
	int y=3;
	 for(i=0;i<x;i++)
	 {
		 for(j=0;j<y;j++)
		 {
			//k=j+i*(j+1);//�G����@�������Gcolumn + row*�u��ڦ�ơv---->���~����
			 k=i*y+j;//�~*����+��
			printf("intarray[%d][%d]=%d\t",i,j,a[k]);
		 }
		printf("\n");
	 }
}
void ShowArray(int a[][3])//�ǰe�G���}�C�ɥ����з������y��ơz
{
	int i,j;
	 for(i=0;i<3;i++)
	 {
		 for(j=0;j<3;j++)
		 {
			printf("intarray[%d][%d]=%d\t",i,j,a[i][j]);
		 }
		printf("\n");
	 }
}
void main(void)
{
	int i,j,k;
	int *pintarray;
	int intarray[3][3];
	 k=0;
	 for(i=0;i<3;i++)
		 for(j=0;j<3;j++)
		 {
			 k++;
			intarray[i][j]=k;
		 }
	ShowArray(intarray);
	pintarray=(int*)intarray;
	printf("�G����@���C�L\n");
	ShowArray(pintarray);
}