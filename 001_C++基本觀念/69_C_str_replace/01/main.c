#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* str_replace [�r����N]
* @param {char*} source ��l����r
* @param {char*} find �j�M����r
* @param {char*} rep ��������r
* */
char *str_replace (char *source, char *find,  char *rep){
   // �j�M��r������
   int find_L=strlen(find);
   // ������r������
   int rep_L=strlen(rep);
   // ���G��r������
   int length=strlen(source)+1;
   // �w�찾���q
   int gap=0;

   // �إߵ��G��r�A�ýƻs��r
   char *result = (char*)malloc(sizeof(char) * length);
   strcpy(result, source);

   // �|���Q���N���r��
   char *former=source;
   // �j�M��r�X�{���_�l��}����
   char *location= strstr(former, find);

   // ���i�j�M����������r
   while(location!=NULL){
       // �W�[�w�찾���q
       gap+=(location - former);
       // �N�����Ÿ��w�b�j�M�쪺��}�W
       result[gap]='\0';

       // �p��s������
       length+=(rep_L-find_L);
       // �ܧ�O����Ŷ�
       result = (char*)realloc(result, length * sizeof(char));
       // ��������r�걵�b���G�᭱
       strcat(result, rep);
       // ��s�w�찾���q
       gap+=rep_L;

       // ��s�|���Q���N���r�ꪺ��}
       former=location+find_L;
       // �N�|���Q���N����r�걵�b���G�᭱
       strcat(result, former);

       // �j�M��r�X�{���_�l��}����
       location= strstr(former, find);
   }

   return result;

}


int main(){
   char* str1 = "My English Name Jash.liao";
   char* str2 = str_replace(str1, "Name","Name is");

   printf( "str1: '%s'\n", str1 );
   printf( "str2: '%s'\n", str2 );

   return 0;
}
