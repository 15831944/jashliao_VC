                    /*�^��P�_   �@��:smilediao*/
#include <iostream.h>
#include<string.h>
void main()
{
     int a=1;
     char smile[20];                   //�w�q�̤j�r�ꪺ���׬O20
     cout<<"�п�J�A�P�_���r��:";
     cin>>smile;
     int n=strlen(smile);               //�P�_�A��J���r�ꪺ����
     char *end=&smile[n-1],*start=&smile[0];
     for (;start<=end;start++,end--)
     {
     if (*end!=*start)                 //�P�_��٦r���O�_�ۦP
     a=0;                         //���ۦP�ɱN0�I�ȵ�a
     }
     if (a==1)
     cout<<smile<<"�O�^��!"<<endl;
     else 
     cout<<smile<<"���O�^��!"<<endl;
}