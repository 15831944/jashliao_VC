#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    int x[6]={25,10,39,40,33,12};
    int spec=11;
    int k;//�x�s�ǭ��ܼƥ洫�����ޭȳ̤j����[=�}�C�j�p-2]
    int times;//�T�{��w�ƧǬO�_��������
    int i;//�j���ܼƯ��ޭ�
    int temp;//�ܼƥ洫�Ȧs�Ŷ�
    int j;
    k=6-1;
    printf("���Ƨ�:");
    for(j=0;j<6;j++)
    {
        printf("%d\t",x[j]);
    }
    printf("\n");
    while(k!=0)
    {
        times=0;
        for(i=0;i<=k-1;i++)//K-1�O�]���B�⤣�n�W�X�}�C�d��
        {
            if(x[i]>x[i+1])
            {
                temp=x[i];
                x[i]=x[i+1];
                x[i+1]=temp;  /* x[i]�Px[i+1]���� */
                times=i;
            }
        }
        k=times;

        for(j=0;j<6;j++)
        {
            printf("%d\t",x[j]);
        }
        printf("\n");
    }

    for(i=0;i<6;i++)
    {
        printf("%d\t",x[i]);
    }

    printf("\n�S�O��\t%d\n",spec);
    /*system("pause");*/
    cout << "Hello world!" << endl;
    return 0;
}
