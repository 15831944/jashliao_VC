///////////////////////////////
// http://ff320232.blogspot.tw///
//  Atien (c) 2013  //
///////////////////////////////

#include "stdafx.h"
#include "stdlib.h"
#include "AES.h"
#include <string.h>

int main(int argc, char* argv[])
{

	int i,j;
	char str[100];
    unsigned char key[20];

    printf("�п�J�n�[�K�����e:");
	scanf("%s",&str);
	printf("�п�J�n�[�K���_��:");
	scanf("%s",&key);

	AES aes(key);//�]�wKEY

	printf("\n");
    i=strlen(str);
    printf("�n�[�K����r");
	for(j=0; j<i;j++)printf("%c",(unsigned char)str[j]);
	printf("\n");

	printf("�[�K��:");
	aes.Cipher((void *)str);
	for(j=0; j<i;j++)printf("%X",(unsigned char)str[j]);
	printf("\n");

    printf("�ѱK��:");
	aes.InvCipher((void *)str,i);
	for(j=0; j<i;j++)printf("%c",(unsigned char)str[j]);
	printf("\n");

	system("pause");
	return 0;
}


