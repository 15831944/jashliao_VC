#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c;//�D�X���@�س̦h�i�H�R�X��
    int x,y,z;//�n�䪺����
    int i,j,k;//�j���ܼ�

    int Now_D,Ans_D;//�����B�⵲�G�M�̲׵���
    int findAns;//��짹���ŦX���X���ܼ�
    a=100/7;
    b=100/9;
    c=100/11;
    Now_D=Ans_D=0;
    findAns=-1;
    printf("7X+9Y+11Z��100\t�DX�AY�AZ \n");//��n�վ�Ƹ�
    for(i=0;i<=a;i++)//�Q�ΤT�h�j����ըC�زզX
    {
        for(j=0;j<=b;j++)
        {
            for(k=0;k<=c;k++)
            {
               Now_D=i*7+j*9+k*11;
               if((Ans_D<Now_D)&&(Now_D<=100)&&(i>0&&j>0&&k>0))//�C�ئܤ֭n�R�@��
               {
                   Ans_D=Now_D;
                   x=i;
                   y=j;
                   z=k;
                   if(Ans_D==100)//��짹���ŦX�N����Ҧ��B��
                   {
                       findAns=1;
                       break;
                   }
               }
            }
            if(findAns==1)//��짹���ŦX�N����Ҧ��B��
                break;
        }
        if(findAns==1)//��짹���ŦX�N����Ҧ��B��
            break;
    }
    printf("7*%d+9*%d+11*%d=%d\n",x,y,z,Ans_D);

    return 0;
}
