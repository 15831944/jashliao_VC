#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
   char* pchrsource = "My English Name Jash.liao";
   char pchrresult[1000];//char* pchrresult;
   char* pchrfind="Name";
   char* pchrrep="Name is";
   char* pchrformer;
   char* pchrlocation;
   int intrep;// ������r������
   int intfind;// �j�M��r������
   int intlength;// ���G��r������
   int intgap=0;// �����q

   intfind=strlen(pchrfind);// �j�M��r������
   intrep=strlen(pchrrep);// ������r������
   intlength=strlen(pchrsource)+1;// ���G��r������

   //pchrresult = (char*)malloc(sizeof(char) * intlength);// �t�m�O����
   strcpy(pchrresult, pchrsource);//�ƻs��r

   pchrformer=pchrsource;
   pchrlocation= strstr(pchrformer, pchrfind);//�j�M��r�X�{���_�l��}����

   while(pchrlocation!=NULL){

       intgap+=(pchrlocation - pchrformer);//�w�찾���q
       pchrresult[intgap]='\0';// �N�����Ÿ��w�b�j�M�쪺��}�W

       intlength+=(intrep-intfind);//�p��s������
       //pchrresult = (char*)realloc(pchrresult, intlength * sizeof(char));// �ܧ�O����Ŷ�
       strcat(pchrresult, pchrrep);//�걵�b���G�᭱
       intgap+=intrep;//��s�����q


       pchrformer=pchrlocation+intfind;//��s�|���Q���N���r�ꪺ��}

       strcat(pchrresult, pchrformer);//�N�|���Q���N����r�걵�b���G�᭱


       pchrlocation= strstr(pchrformer, pchrfind);//�j�M��r�X�{���_�l��}����
   }

   pchrresult[strlen(pchrresult)]='\0';

   printf( "source: '%s'\n", pchrsource );
   printf( "result: '%s'\n", pchrresult);

   //free(pchrresult);
   return 0;
}
