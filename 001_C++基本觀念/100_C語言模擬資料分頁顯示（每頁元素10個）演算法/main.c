#include <stdio.h>
#include <stdlib.h>
/*C�y��������Ƥ�����ܡ]�C������10�ӡ^�t��k*/
int main()
{
    int num=23;
    int obj[10];
    int all_page=0;//n
    int now_page=2;//1~n
    int i,j;
	
	//�p���`����
    all_page=num/10;
    if((num%10)>0)
    {
        all_page++;
    }

    //��ܥثe���A�ܼ�
	printf("num=%d\n",num);
    printf("all_page=%d\n",all_page);
    printf("now_page=%d\n",now_page);

    //��l�Ƥ��������󪺤��e
	for(i=0;i<10;i++)
    {
        obj[i]=-1;
    }

	//���өҦb���Ƴ]�w��������
    if(now_page<=all_page)
    {
        for(i=0;i<10;i++)
        {
            j=i+((now_page-1)*10);
            if(j<num)
            {
                obj[i]=j;
            }
        }
    }
    else
    {
        printf("no page=%d\n",now_page);
    }

	//��ܵ��G
    for(i=0;i<10;i++)
    {
        printf("obj[%d]=%d\n",i,obj[i]);
    }

    return 0;
}
