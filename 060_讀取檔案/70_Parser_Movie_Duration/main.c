//////////////////////////////////////////////////////////////
//
//�z�L���RFFMPEG����T�A���o�v������
//
/////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *pf;
    int i=0;
    char chrfind[]="Duration:";
    char *pchrget='\0';
    char buf[513];
    char buf0[50],buf1[50],buf2[50],buf3[50],buf4[50],buf5[50];
    int intHr,intMin,intSec,intmSec;
    int intAllSec;
    int intHalfSec;
    //----------------------------
    //__��C�@��@��Ū���ɮפ��e_start
    pf=fopen("info1.txt","r");
    while(fgets(buf,512,pf) != NULL)
    //__��C�@��@��Ū���ɮפ��e_end
    //----------------------------
    {
        buf[strlen(buf)-1]='\0';//�R������
        //printf("%s\n",buf);//�����L�X�C�@���T
        //----------------------------
        //__�j�M�ɮפ���Duration�r��_start
        pchrget='\0';
        pchrget=strstr(buf,chrfind);
        if(pchrget!='\0')
        {
            printf("%s\n",buf);
            break;
        }
        //__�j�M�ɮפ���Duration�r��_end
        //----------------------------
    }
    //----------------------------
    //__�j�M�ɮפ���Duration�r��_start
    //----------------------------
    //__�p��v�����ת��@�b_start
    sscanf (buf ,"%[^:]:%[^:]:%[^:]:%[^.].%[^,],%s",buf0,buf1,buf2,buf3,buf4,buf5);
    //printf("%s\n%s\n%s\n%s\n",buf1,buf2,buf3,buf4);
    intHr=atoi(buf1);
    intMin=atoi(buf2);
    intSec=atoi(buf3);
    intmSec=atoi(buf4);
    //printf("%d\n%d\n%d\n%d\n",intHr,intMin,intSec,intmSec);
    intAllSec=intHr*60*60+intMin*60+intSec;
    printf("AllSec=%d\n",intAllSec);
    intHalfSec=intAllSec/2;
    printf("HalfSec=%d\n",intHalfSec);
    intHr=intHalfSec/(60*60);
    intMin=(intHalfSec-(intHr*(60*60)))/60;
    intSec=(intHalfSec-(intHr*(60*60))-(intMin*60));
    printf("%d:%d:%d",intHr,intMin,intSec);
    //__�p��v�����ת��@�b_end
    return 0;
}
