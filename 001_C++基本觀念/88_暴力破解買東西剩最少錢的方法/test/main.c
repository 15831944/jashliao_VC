#include <stdio.h>
#include <stdlib.h>
//AX+BY+CZ ��Dividend
void BoBo(int p[][2],int n)
//============================================================
//
//��ƻ���:��w�ƧǨì����쥻��m
//
//============================================================
{
	long i,j,key;
	double temp,temp1;
	for(i=0;i<n;i++)
	{
		key=0;
		for(j=0;j<(n-i-1);j++)
		{
			if(p[j][1]<p[j+1][1])
			{
				temp1=p[j][1];
				p[j][1]=p[j+1][1];
				p[j+1][1]=temp1;
				///////////////////////////////
				temp=p[j][0];
				p[j][0]=p[j+1][0];
				p[j+1][0]=temp;
				key=1;
			}
		}
		if(key==0)
			break;
	}
}
int main()
{
    int A,B,C,D;
    int X=0,Y=0,Z=0;
    int Quotient=0,Remainder=0;
    //----------------------------
    //ABC �ܼƱƧǥ�
    //__bobo_start
    int i,bobo[3][2];
    for(i=0;i<3;i++)
        bobo[i][0]=i;
    //__bobo_end
    //----------------------------
    //----------------------------
    //Ū����J���Ѽ�
    //__Ū����J���Ѽ�_start
    printf("AX+BY+CZ ��Dividend \n");
    printf("��J�ĶR���B(Dividend)=\t");
    scanf("%d",&D);
    printf("��J�ĶRA�������=\t");
    scanf("%d",&A);
    bobo[0][1]=A;
    printf("��J�ĶRB�������=\t");
    scanf("%d",&B);
    bobo[1][1]=B;
    printf("��J�ĶRC�������=\t");
    scanf("%d",&C);
    bobo[2][1]=C;
    printf("�ҥH�D��: %dX+%dY+%dZ ��%d \n",A,B,C,D);
    //__Ū����J���Ѽ�_end
    BoBo(bobo,3);//����ABC�Ƨ�
    /*
    printf("%d\t%d\n",bobo[0][0],bobo[0][1]);
    printf("%d\t%d\n",bobo[1][0],bobo[1][1]);
    printf("%d\t%d\n",bobo[2][0],bobo[2][1]);
    //*/
    //----------------------------
    //�Ĥ@���p��T�˳��R�i�H�R�X��
    //__�Ĥ@���p��T�˳��R�i�H�R�X��_start
    Quotient=D/(A+B+C);//�p��T�˳��R�i�H�R�X��
    X=Y=Z=Quotient;
    Remainder=D-(Quotient*(A+B+C));//�p��Ѿl����
    //__�Ĥ@���p��T�˳��R�i�H�R�X��_end
    //printf("first=%d\t%d\n",Quotient,Remainder);
    //----------------------------
    //�̧�(�q�����}�l)�p��i�R�ƶq
    //__�̧�(�q�����}�l)�p��i�R�ƶq_start
    while((Remainder>=C)||(Remainder>=B)||(Remainder>A))//��Ѿl������쳣����R����
    {
        D=Remainder;//��Ѿl�����ܰӼ�
        Quotient=0;
        Remainder=0;
        if(D>=bobo[0][1])//���ӶR�̶Q�����~
        {
            Quotient=D/bobo[0][1];//�p��i�H�R�X��
            switch(bobo[0][0])//��R�쪺�ƶq�[��������ܼ�
            {
                case 0:
                    X=X+Quotient;
                    break;
                case 1:
                    Y=Y+Quotient;
                    break;
                case 2:
                    Z=Z+Quotient;
                    break;
            }
            Remainder=D-Quotient*bobo[0][1];//�p��Ѿl����
            D=Remainder;//��Ѿl�����ܰӼ�
            Quotient=0;
            Remainder=0;
        }//if(D>=bobo[0][1])
        if(D>=bobo[1][1])//���ӶR���Q�����~
        {
            Quotient=D/bobo[1][1];//�p��i�H�R�X��
            switch(bobo[1][0])
            {
                case 0:
                    X=X+Quotient;
                    break;
                case 1:
                    Y=Y+Quotient;
                    break;
                case 2:
                    Z=Z+Quotient;
                    break;
            }
            Remainder=D-Quotient*bobo[1][1];//�p��Ѿl����
            D=Remainder;//��Ѿl�����ܰӼ�
            Quotient=0;
            Remainder=0;
        }//if(D>=bobo[1][1])
        if(D>=bobo[2][1])//���ӶR�̫K�y�����~
        {
            Quotient=D/bobo[2][1];//�p��i�H�R�X��
            switch(bobo[2][0])
            {
                case 0:
                    X=X+Quotient;
                    break;
                case 1:
                    Y=Y+Quotient;
                    break;
                case 2:
                    Z=Z+Quotient;
                    break;
            }
            Remainder=D-Quotient*bobo[2][1];//�p��Ѿl����
            D=Remainder;//��Ѿl�����ܰӼ�
            Quotient=0;
            Remainder=0;
        }//if(D>=bobo[2][1])
    }//while((Remainder>=C)||(Remainder>=B)||(Remainder>A))
    //__�̧�(�q�����}�l)�p��i�R�ƶq_end
    printf("�ҥH����: %d*%d+%d*%d+%d*%d=%d\t Remainder=%d \n",A,X,B,Y,C,Z,(A*X+B*Y+C*Z),D);

    return 0;
}
