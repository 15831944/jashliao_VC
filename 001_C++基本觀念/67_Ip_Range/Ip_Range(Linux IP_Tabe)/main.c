#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char chrsrc[100];
    char chrd1[50],chrd2[50];
    int i=0;
    int intd1len=0;
    int intd2len=0;
    int intdotcount=0;
    int intstarcount=0;
    char ip01[5],ip02[5],ip03[5],ip04[5];
    int intA,intB,intD;

    //strcpy(chrsrc,"47.153.128-191.*");
    //strcpy(chrsrc,"58.14-25.*.*");
    //strcpy(chrsrc,"202.3.77.*");
    //strcpy(chrsrc,"202.3.*.*");
    if(argc < 2)
    {
        strcpy(chrsrc,"202.*.*.*");
    }
    else
    {
        strcpy(chrsrc,argv[1]);
    }
    chrsrc[strlen(chrsrc)]='\0';
    //printf("chrsrc=%s\n",chrsrc);

    sscanf (chrsrc ,"%[^-]-%[^.*]",chrd1,chrd2);
    //printf("chrd1=%s\n",chrd1);
    //printf("chrd2=%s\n",chrd2);

    intd1len=strlen(chrd1);
    intd2len=strlen(chrsrc)-strlen(chrd1);
    for(i=0;i<intd1len;i++)
    {
        if(chrd1[i]=='.')
            intdotcount++;
    }
    for(i=0;i<intd1len;i++)
    {
        if(chrd1[i]=='*')
            intstarcount++;
    }
    //printf("intdotcount=%d\n",intdotcount);
    //printf("intstarcount=%d\n",intstarcount);

    //printf("intd1len=%d\n",intd1len);
    //printf("intd2len=%d\n",intd2len);
    if(intd2len>0)
    {
        intB=atol(chrd2);
        switch(intdotcount)
        {
            case 1://2
                sscanf (chrd1 ,"%[^.].%s",ip01,ip02);
                intA=atol(ip02);
                intD=256-(abs(intA-intB)+1);
                for(i=intA;i<=intB;i++)
                    printf("%s.%d.0.0 255.255.0.0\n",ip01,i);//printf("IP Range=%s.%s.1.1-%s.%s.254.254",ip01,ip02,ip01,chrd2);
                break;
            case 2://3
                sscanf (chrd1 ,"%[^.].%[^.].%s",ip01,ip02,ip03);
                intA=atol(ip03);
                intD=256-(abs(intA-intB)+1);
                for(i=intA;i<=intB;i++)
                    printf("%s.%s.%d.0 255.255.255.0\n",ip01,ip02,i);//printf("IP Range=%s.%s.%s.1-%s.%s.%s.254",ip01,ip02,ip03,ip01,ip02,chrd2);
                break;
        }
    }
    else
    {
        switch(intstarcount)
        {
            case 1://3
                sscanf (chrd1 ,"%[^.].%[^.].%[^.*]",ip01,ip02,ip03);
                printf("%s.%s.%s.0 255.255.255.0",ip01,ip02,ip03);//printf("IP Range=%s.%s.%s.1-%s.%s.%s.254",ip01,ip02,ip03,ip01,ip02,ip03);
                break;
            case 2://2
                sscanf (chrd1 ,"%[^.].%[^.*]",ip01,ip02);
                printf("%s.%s.0.0 255.255.0.0",ip01,ip02);//printf("IP Range=%s.%s.1.1-%s.%s.254.254",ip01,ip02,ip01,ip02);
                break;
            case 3://1
                sscanf (chrd1 ,"%[^.].",ip01);
                printf("%s.0.0.0 255.0.0.0",ip01);//printf("IP Range=%s.1.1.1-%s.254.254.254",ip01,ip01);
                break;
        }
    }
    printf("\n");
    return 0;
}
