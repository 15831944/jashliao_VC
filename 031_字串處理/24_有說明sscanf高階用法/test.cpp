#include <stdio.h>

int main ()
{
/*
  char sentence []="Rudolph is 12 years old";
  char str [20];
  int i;

  sscanf (sentence,"%s %*s %d",str,&i);
  printf ("%s -> %d\n",str,i);
*/
/*
sscanf��ƪ����ťΪk
 
����ɽЪ`���X�B�Ghttp://blog.csdn.net/absurd/
 
�j�a�����Dsscanf�O�@�ӫܦn�Ϊ���ơA�Q�Υ��i�H�q�r�ꤤ���X��ơB�B�I�ƩM�r�굥���C�����ϥΤ�k²��A�S�O����ƩM�B�I�ƨӻ��C���s��i��ä����D�B�z�r��ɪ��@�ǰ��ťΪk�A�o�ذ���²�n�����a�C
 
1.         �`���Ϊk�C
char str[512] = {0};
	sscanf("123456 ", "%s", str);
    printf("str=%s\n", str);
 
2.         �����w���ת��r��C�p�b�U�Ҥ��A���̤j���׬�4�줸�ժ��r��C
    sscanf("123456 ", "%4s", str);
    printf("str=%s\n", str);
 
3.         ������w�r������r��C�p�b�U�Ҥ��A���J��Ů欰��r��C
    sscanf("123456 abcdedf", "%[^ ]", str);
    printf("str=%s\n", str);
 
4.         ���ȥ]�t���w�r�������r��C�p�b�U�Ҥ��A���ȥ]�t1��9�M�p�g�r�����r��C
    sscanf("123456abcdedfBCDEF", "%[1-9a-z]", str);
    printf("str=%s\n", str);
 
5.         ������w�r��������r��C�p�b�U�Ҥ��A���J��j�g�r������r��C
    sscanf("123456abcdedfBCDEF", "%[^A-Z]", str);
    printf("str=%s\n", str);
*/
 char sentence []="Rudolph is||12||years old";	
  char str [20];
  char str1 [20];
  int i;

  sscanf (sentence,"%[^||]||%d||%[^||]",str,&i,str1);
  printf ("%s -> %d %s\n",str,i,str1);
  return 0;
}
