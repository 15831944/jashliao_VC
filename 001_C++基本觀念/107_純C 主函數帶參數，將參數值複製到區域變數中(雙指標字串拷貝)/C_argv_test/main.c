#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//��C �D��Ʊa�ѼơA�N�ѼƭȽƻs��ϰ��ܼƤ�(�����Цr�����)
int main(int argc, char *argv[]){

    printf("inputchar=%s\n",argv[0]);
    char ch;
    char ch1;
    if(argc>1)
    {
        memcpy(&ch,argv[1],1);//char ch = argv[1];
        printf("inputchar=%c\n",ch)	;
        ch1=*argv[1];//������Ϊk
        printf("inputchar1=%c\n",ch)	;
    }
    else
    {
        printf("inputchar=null\n");
    }

    system("pause");
}
