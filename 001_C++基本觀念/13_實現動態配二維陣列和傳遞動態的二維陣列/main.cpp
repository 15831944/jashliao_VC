#include <iostream>
using namespace std;
//////////////////////////////////
//��{�ʺA�t�G���}�C�M�ǻ��ʺA���G���}�C
void showarray(int **array)
{
	int i,j,k=0;
	 for(i=0;i<3;i++)
	 {
		 for(j=0;j<3;j++)
		 {
			printf("array[%d][%d]=%d\t",i,j,*(*(array+i)+j));
		 }
		printf("\n");
	 }
}
void main()
{
	int **array;
	int i,j,k=0;
	/////////////////////////////////
	//�ʺA�t�G���}�C
	array = new int*[3];
	for(i=0;i<3;i++)
		array[i] = new int[3];
	////////////////////////////////
	//���
	 for(i=0;i<3;i++)
		 for(j=0;j<3;j++)
		 {
			 k++;
			*(*(array+i)+j) = k;
		 }
	//////////////////////////////
	//�ǻ��ʺA���G���}�C
	showarray(array);
	delete [] array;
}