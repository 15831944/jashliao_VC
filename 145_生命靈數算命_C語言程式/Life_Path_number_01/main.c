#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int intCount[10];//�C�ӼƦr�X�{���Ӽ�
    int intYear;
    int intMonth;
    int intDay;
    int i;
    printf("�ӤH�ͩR�F�ƭp��G\n");
    printf("�Ш̧ǿ�J�z���ͤ�\n");
    printf("�п�J�褸�~�]ex�G1901�^\t");
    scanf("%d",&intYear);
    printf("�п�J����]ex�G11�^\t");
    scanf("%d",&intMonth);
    printf("�п�J����]ex�G28�^\t");
    scanf("%d",&intDay);
    printf("�z���ͤ�G%d/%d/%d\n",intYear,intMonth,intDay);

    for(i=0;i<10;i++)
    {
        intCount[i]=0;
    }
    int intQuotient=0;
    int intRemainder=0;
    int j;
    intRemainder=intYear;
    for(i=0;i<4;i++)
    {
        j=pow(10,i);
        intQuotient=(intRemainder*j)/1000;
        intCount[intQuotient]++;
        intRemainder=(intRemainder*j)%1000/j;
    }
    intRemainder=intMonth;
    intQuotient=intRemainder/10;
    intCount[intQuotient]++;
    intRemainder=intRemainder%10;
    intCount[intRemainder]++;

    intRemainder=intDay;
    intQuotient=intRemainder/10;
    intCount[intQuotient]++;
    intRemainder=intRemainder%10;
    intCount[intRemainder]++;

    printf("\n���ѼơG\t");
    for(i=1;i<10;i++)
    {
        if(intCount[i]>0)
        {
            printf("%d,\t",i);
        }
    }
    printf("\n�ѽ�ơG\t");
    int intTalent=0;
    for(i=0;i<10;i++)
    {
        if(intCount[i]>0)
        {
            intTalent+=(i*intCount[i]);
        }
    }
    intRemainder=intTalent;
    intQuotient=intRemainder/10;
    intCount[intQuotient]++;
    printf("%d,\t",intQuotient);
    intRemainder=intRemainder%10;
    intCount[intRemainder]++;
    printf("%d,\t",intRemainder);
    printf("\n�R�ơG\t");
    int intMain;
    intMain=intQuotient+intRemainder;
    if(intMain>9)
    {
        intRemainder=intMain;
        intQuotient=intRemainder/10;
        intCount[intQuotient]++;
        printf("%d,\t",intQuotient);
        intRemainder=intRemainder%10;
        intCount[intRemainder]++;

        intMain=intQuotient+intRemainder;
        intCount[intMain]++;
    }
    else
    {
        intCount[intMain]++;
    }
    printf("%d,\n",intMain);

    printf("�ͤ�ơG\t");
    int intBirthday;
    intRemainder=intDay;
    intQuotient=intRemainder/10;
    intRemainder=intRemainder%10;
    intBirthday=intQuotient+intRemainder;
    if(intBirthday>9)
    {
        intRemainder=intBirthday;
        intQuotient=intRemainder/10;
        intCount[intQuotient]++;
        printf("%d,\t",intQuotient);
        intRemainder=intRemainder%10;
        intCount[intRemainder]++;

        intBirthday=intQuotient+intRemainder;
        intCount[intBirthday]++;
    }
    else
    {
        intCount[intBirthday]++;
    }
    printf("%d,\n",intBirthday);

    printf("�P�y�ơG\t");
    int intConstellation=0;
    int intMonth_Day=0;
    intMonth_Day=(intMonth*100)+intDay;
    if((intMonth_Day>=321)&&(intMonth_Day<=419))
    {
        intConstellation=1;
        intCount[intConstellation]++;
        printf("%d,\n",intConstellation);//�զϮy Aries
    }
    if((intMonth_Day>=420)&&(intMonth_Day<=520))
    {
        intConstellation=2;
        intCount[intConstellation]++;
        printf("%d,\n",intConstellation);//�����y Taurus
    }
    if((intMonth_Day>=521)&&(intMonth_Day<=621))
    {
        intConstellation=3;
        intCount[intConstellation]++;
        printf("%d,\n",intConstellation);//���l�y Gemini
    }
    if((intMonth_Day>=622)&&(intMonth_Day<=722))
    {
        intConstellation=4;
        intCount[intConstellation]++;
        printf("%d,\n",intConstellation);//���ɮy Cancer
    }
    if((intMonth_Day>=723)&&(intMonth_Day<=822))
    {
        intConstellation=5;
        intCount[intConstellation]++;
        printf("%d,\n",intConstellation);//��l�y Leo
    }
    if((intMonth_Day>=823)&&(intMonth_Day<=922))
    {
        intConstellation=6;
        intCount[intConstellation]++;
        printf("%d,\n",intConstellation);//�B�k�y Virgo
    }
    if((intMonth_Day>=923)&&(intMonth_Day<=1022))
    {
        intConstellation=7;
        intCount[intConstellation]++;
        printf("%d,\n",intConstellation);//�ѯ��y Libra
    }
    if((intMonth_Day>=1023)&&(intMonth_Day<=1121))
    {
        intConstellation=8;
        intCount[intConstellation]++;
        printf("%d,\n",intConstellation);//���Ȯy Scorpio
    }
    if((intMonth_Day>=1122)&&(intMonth_Day<=1221))
    {
        intConstellation=9;
        intCount[intConstellation]++;
        printf("%d,\n",intConstellation);//�g��y Sagittarius
    }
    if((intMonth_Day>=120)&&(intMonth_Day<=218))
    {
        intConstellation=2;
        intCount[intConstellation]++;
        printf("%d,\n",intConstellation);//���~�y Aquarius
        intConstellation=11;
    }
    if((intMonth_Day>=219)&&(intMonth_Day<=320))
    {
        intConstellation=3;
        intCount[intConstellation]++;
        printf("%d,\n",intConstellation);//�����y Pieces
        intConstellation=12;
    }
    if(intConstellation==0)
    {
        intConstellation=1;
        intCount[intConstellation]++;
        printf("%d,\n",intConstellation);//���~�y Capricorn 12.22-1.19
        intConstellation=10;
    }

    printf("�ůʼơG\t");
    for(i=1;i<10;i++)
    {
        if(intCount[i]==0)
        {
            printf("%d,\t",i);
        }

    }
    printf("\n");

    printf("�H�U�O�A���ͩR�F�ƨC�@�ӼƦr���X�{���Ʋέp�G\n");
    for(i=1;i<10;i++)
    {
        printf("%d\t",i);
    }
    printf("\n");
    for(i=1;i<10;i++)
    {
        printf("%d\t",intCount[i]);
    }
    printf("\n");

    printf("\n�H�U�O�̷ӧA�R�ƪ��өʤ��R�G\n");
    printf("�R�ơG\t%d\n",intMain);
    switch(intMain)
    {
    case 1:
        printf("(�ۥD)	�W�ߡB�n���B�гy�B��ɡB��q\n");
        printf("�u�I�G�I�зN�P�z�ѤO�A���H�o���A���w���\n");
        printf("���I�G�j�աB�W�_�B�Bļ�B�ۨp�B�i���B�j���C�D�[�N�ѱj�A�ڦ�گ��A�H�����Y�H��\n");
        break;
    case 2:
        printf("(����)	�ӷP�B��K�B�X���B�M�ӡB�̿�\n");
        printf("�u�I�G�өʤ��ġA������u�X�@�A�����s�����Y�A���w����O�H�֩w\n");
        printf("���I�G�������w�B�u�X���_�B���H���N�B���L���w�C�e���]�L�H���N���Ө���v�T�A����ԭ@�t�W\n");
        break;
    case 3:
        printf("(�зN)	��ʡB���[�B�۫H�B��{�B����\n");
        printf("�u�I�G�o����ĵ�A���зN�A�h�㦳���N�ѥ��A��F��O�j	�ۿf�B��a�B�ءB���@���U�B�A��������\n");
        printf("���I�G�C���ʡA�h�u�̦ۤv���ߦn��ơA�e���n���c��\n");
        break;
    case 4:
        printf("(�ȹ�)	���ۡB���ǡB�Ĳv�B�U�H�B�۫�\n");
        printf("�u�I�G��´��O�j�A���Ʊ��z�����A�إ��ӾU�A�ਲ਼�t�x�����I\n");
        printf("���I�G�W�_�W��B�߯ݯU���B�e����i�B��������C�T���A�ʥF�w���P�A�����Ӿ᭷�I�A�]���e�������|�Ȩ�\n");
        break;
    case 5:
        printf("(�ۥ�)	�o�o�B�_�I�B�A���j�B�h�ܤơB�ǲߧ�\n");
        printf("�u�I�G�൪���G�A�f�~���ΡA�������n�A���q��A�R�|�ۥ�\n");
        printf("���I�G�զӤ���B����O�t�B�@���b�G�B���D�L�סC�����w��������A�e�����a�A�e���o�o�O�H\n");
        break;
    case 6:
        printf("(�d��)	í�w�B�H��B�����B���q�B�^�m\n");
        printf("�u�I�G���P�ӿ��A�ժ��H�ڶ�����ڡA���w���U�L�H�A���ӿջP�d��\n");
        printf("���I�G�ʥF�۫H�B������ڡB�n�j���G�B�j��z�A�C���z���ɡA�`�|���X���~���M�w�A�I�X���D�^���ɮe�����ۤv����\n");
        break;
    case 7:
        printf("(���s)	���١B�I�q�B��ı�B�u�z�B�z�Q\n");
        printf("�u�I�G�ժ��p��ƪ��A���w�l�D�u�z�A����p�A�J�Ʋz��\n");
        printf("���I�G�N�z�B�ۤj�ƺC�B�ۧک��a�B���������C�B�Ƥ�����ơA���e���Q�Q�n�A�e����⪺�F�褣�|�ñ�\n");
        break;
    case 8:
        printf("(�v��)	���s�B����B��w�B�����B�Ӯ�\n");
        printf("�u�I�G���w�_�I��E�A���ӷ~�Y���A���w�l�D�v�O�A��Y���Y��\n");
        printf("���I�G�ߪ��D�q�B�L�D�w�P�B�߰���ơB�ư��Lĳ�Bź�ơC����w���F�観���`�����ۡA����Ĭ�ɷ|�j�j�ۤv\n");
        break;
    case 9:
        printf("(�i��)	�H�ʡB�ҵo�B���O�B���h�B�F��\n");
        printf("�u�I�G�R���ͩR�O�A��q�зN������o�����P�A�B���H�����ܡA���۩��\n");
        printf("���I�G���`�}���@�L��h�B�������B�S���@�ʡB��Ƥ��ȹ�A�N�Ӥ�����w�A�Q���ӹL��O�״I�h�|�ܦ��Ѱ����\n");
        break;
    }

    printf("\n�Ű��V�h���Ʀr�A��ܨ���O�V�j�P:\n");
    for(i=1;i<10;i++)
    {
        if(intCount[i]>0)
        {
            printf("%d:\t�Ӽ�:%d\t",i,intCount[i]);
            switch(i)
            {
            case 1:
                printf("�зs/�W��\n");
                break;
            case 2:
                printf("���M/��ı\n");
                break;
            case 3:
                printf("�z�Q/���P\n");
                break;
            case 4:
                printf("�w��/����\n");
                break;
            case 5:
                printf("�ۥ�/�_�I\n");
                break;
            case 6:
                printf("�t�d/�^�m\n");
                break;
            case 7:
                printf("���R/�u�z\n");
                break;
            case 8:
                printf("�޿�/���O\n");
                break;
            case 9:
                printf("�Q��/�H�D\n");
                break;
            }

        }
    }

    printf("\n�ůʼƪ�ܦۤv�����ʥH�U�o�譱����O:\n");
    for(i=1;i<10;i++)
    {
        if(intCount[i]==0)
        {
            printf("%d:\t",i);
            switch(i)
            {
            case 1:
                printf("�зs/�W��\n");
                break;
            case 2:
                printf("���M/��ı\n");
                break;
            case 3:
                printf("�z�Q/���P\n");
                break;
            case 4:
                printf("�w��/����\n");
                break;
            case 5:
                printf("�ۥ�/�_�I\n");
                break;
            case 6:
                printf("�t�d/�^�m\n");
                break;
            case 7:
                printf("���R/�u�z\n");
                break;
            case 8:
                printf("�޿�/���O\n");
                break;
            case 9:
                printf("�Q��/�H�D\n");
                break;
            }
        }
    }

    printf("\n�H�U�O���s�u���R�G\n");
    printf("�A�b1-2-3�s�u�s�u���R\n");
    if((intCount[1]>0)&&(intCount[2]>0)&&(intCount[3]>0))
    {
        printf("\t����ǲߨưȬ۷�ӾU�C\n");
    }
    else
    {
        if((intCount[1]==0))
        {
            printf("\t��1�̡G���S�۫H�B�W�ߩʤ����B���z�C\n");
        }
        if((intCount[2]==0))
        {
            printf("\t��2�̡G����F�賣�Q�ǡA���e���J�줺�߻�ê�B�~�V�C\n");
        }
        if((intCount[3]==0))
        {
            printf("\t��3�̡G�ǲ߫ܧ֡A����������A�e���b�~�Ӽo�B�ǦӤ���C\n");
        }

    }
    printf("�A�b4-5-6�s�u�s�u���R\n");
    if((intCount[4]>0)&&(intCount[5]>0)&&(intCount[6]>0))
    {
        printf("\t�޿��´�j�A���Ʊ��z�����B���M���ǡC\n");
    }
    else
    {
        if((intCount[4]==0))
        {
            printf("\t��4�̡G�x�l���p�B�`�ȧ��ܥB�����_����j�C\n");
        }
        if((intCount[5]==0))
        {
            printf("\t��5�̡G�ʥF����O�B�ʤO�C\n");
        }
        if((intCount[6]==0))
        {
            printf("\t��6�̡G�����P�H���ʡC\n");
        }
        if((intCount[4]==0)&&(intCount[5]==0))
        {
            printf("\t��45�̡G�x�l�p�B�j�p�Ʊ��ۤv�~�ۤv�C\n");
        }
        if((intCount[5]==0)&&(intCount[6]==0))
        {
            printf("\t��56�̡G���ɤ����p��P�H�۳B�A�~��N�z�A���ߪi�ܬ���C\n");
        }
        if((intCount[4]==0)&&(intCount[5]==0)&&(intCount[6]==0))
        {
            printf("\t456���ʪ̡G��Ҧ��Ʊ���b�߲z���áB�e�����H�Pı���I�C\n");
        }
    }

    printf("�A�b7-8-9�s�u�s�u���R\n");
    if((intCount[7]>0)&&(intCount[8]>0)&&(intCount[9]>0))
    {
        printf("\t���Q�H���U�A���p���B���ϤߡB���z�S���H�ߡA���N�j�Ʒ~�O���諸�C\n");
    }
    else
    {
        if((intCount[7]==0))
        {
            printf("\t��7�̡G�e�����O�j\n");
        }
        if((intCount[8]==0))
        {
            printf("\t��8�̡G��D�ީθg��Ʒ~�����D�ت��A������~�O�̭��n�C\n");
        }
        if((intCount[9]==0))
        {
            printf("\t��9�̡G�Y�O�޲z�̤���ޤ��ʭ��u�C\n");
        }
        if((intCount[7]==0)&&(intCount[8]==0)&&(intCount[9]==0))
        {
            printf("\t789���ʪ̡G�����ʳs�u�A�b���n�ɯS��~�|��{�A�Ʀܱj�L��ʳs�u�C\n");
        }
    }

    printf("�A�b1-4-7�s�u�s�u���R\n");
    if((intCount[1]>0)&&(intCount[4]>0)&&(intCount[7]>0))
    {
        printf("\t�տ��e���B���]�B�ΡC\n");
    }
    else
    {
        if((intCount[4]==0))
        {
            printf("\t��4�̡G�e���]�����_��Ӫ���C\n");
        }
        if((intCount[7]==0))
        {
            printf("\t��7�̡G���e���V��V�j���C\n");
        }
        if((intCount[4]==0)&&(intCount[7]==0))
        {
            printf("\t��47�̡G�e���l147�s�u���]��C\n");
        }
    }

    printf("�A�b2-5-8�s�u�s�u���R\n");
    if((intCount[2]>0)&&(intCount[5]>0)&&(intCount[8]>0))
    {
        printf("\t����B��ܧֻP�H�����@���A����ڤ����C\n\t�֦����s�u�S��6�G�e�����ݮ�����C\n");
    }
    else
    {
        if((intCount[2]==0))
        {
            printf("\t��2�̡G���߸ܤ����ɶD�C\n");
        }
        if((intCount[5]==0))
        {
            printf("\t��5�̡G���������B�Ȫ����e�����~��B�u����]�w�C\n");
        }
        if((intCount[8]==0))
        {
            printf("\t��8�̡G�����������|�ϤH������O�β{�� (�ѥͪ��~�ȭ�)�C\n");
        }
        if((intCount[2]==0)&&(intCount[5]==0)&&(intCount[8]==0))
        {
            printf("\t258���ʪ̡G�b�H�s����{�����w�R�A���D�`���H�t�C\n");
        }
    }

    printf("�A�b3-6-9�s�u�s�u���R\n");
    if((intCount[3]>0)&&(intCount[6]>0)&&(intCount[9]>0))
    {
        printf("\t�o���D�W�B��F�O�ΡA�ܾA�X�q�����v���u�@�C\n");
    }
    else
    {
        if((intCount[3]==0))
        {
            printf("\t��3�̡G�e���Q�H�T�]�C\n");
        }
        if((intCount[6]==0))
        {
            printf("\t��6�̡G��F����C�C\n");
        }
        if((intCount[9]==0))
        {
            printf("\t��9�̡G���ƤF��B����C\n");
        }
        if((intCount[3]==0)&&(intCount[6]==0)&&(intCount[9]==0))
        {
            printf("\t��369�̡G�����ʳs�u�A�b���n�ɯS��~�|��{�A�Ʀܱj�L��ʳs�u�C\n");
        }
    }

    printf("�A�b1-5-9�s�u�s�u���R\n");
    if((intCount[1]>0)&&(intCount[5]>0)&&(intCount[9]>0))
    {
        printf("\t�֦b�u�@�B�n���V�O�D�W�i�C\n");
    }
    else
    {
        if((intCount[1]==0))
        {
            printf("\t��1�̡G�i�k�B���z�B�Ʊ�O�H�����U�L�C\n");
        }
        if((intCount[5]==0))
        {
            printf("\t��5�̡G�u�@����O�C�B�n���׮z�B�Q�h���֡C\n");
        }
        if((intCount[9]==0))
        {
            printf("\t��9�̡G�D������C�B�L�k�o���~��C\n");
        }
        if((intCount[1]==0)&&(intCount[5]==0)&&(intCount[9]==0))
        {
            printf("\t��159�̡G�����ʳs�u�̡A�b���n�ɡA�S��~�|��{�X�ӡA�Ʀܱj�L��ʳs�u�C\n");
        }
    }

    printf("�A�b3-5-7�s�u�s�u���R\n");
    if((intCount[3]>0)&&(intCount[5]>0)&&(intCount[7]>0))
    {
        printf("\t�`���B�͡B����B�P�Ƴ߷R�C\n");
    }
    else
    {
        if((intCount[5]==0)&&(intCount[7]==0))
        {
            printf("\t��57�̡G����]�B�Q�H�H�H���C\n");
        }
        if((intCount[3]==0)&&(intCount[5]==0))
        {
            printf("\t��35�̡G�e���Q�H�H�H���C\n");
        }
        if((intCount[7]==0))
        {
            printf("\t��7�̡G�R�H�H���O�H�C\n");
        }
        if((intCount[3]==0)&&(intCount[5]==0)&&(intCount[7]==0))
        {
            printf("\t��357�̡G�����ʳs�u���H�A�����n�۳B�L��~�|�`���߷R�C\n");
        }
    }

    printf("�A�b2-4�s�u�s�u���R\n");
    if((intCount[2]>0)&&(intCount[4]>0))
    {
        printf("\t�����֡B�|�@�ϤT�B������ơC\n");
    }
    else
    {
        if((intCount[2]==0))
        {
            printf("\t��2�̡G��[���O���z�B���ߤ~���ּ֡C\n");
        }
        if((intCount[4]==0))
        {
            printf("\t��4�̡G�x�l�p�A�����_��j�C\n");
        }
        if((intCount[2]==0)&&(intCount[4]==0))
        {
            printf("\t��24�̡G�����ʳs�u�A�b���n�ɡA�S��~�|��{�X�ӡA�Ʀܱj�L��ʳs�u�C\n");
        }
    }

    printf("�A�b2-6�s�u�s�u���R\n");
    if((intCount[2]>0)&&(intCount[6]>0))
    {
        printf("\t���ߧU�H�B�n���ꤣ���C\n");
    }
    else
    {
        if((intCount[2]==0))
        {
            printf("\t��2�̡G���߸ܤ����D���C\n");
        }
        if((intCount[6]==0))
        {
            printf("\t��6�̡G��F����z�B�P�H�����W�v�֡C\n");
        }
        if((intCount[2]==0)&&(intCount[6]==0))
        {
            printf("\t��26�̡G�����ʳs�u�A�b���n�ɡA�S��~�|��{�X�ӡA�Ʀܱj�L��ʳs�u�C\n");
        }
    }

    printf("�A�b4-8�s�u�s�u���R\n");
    if((intCount[4]>0)&&(intCount[8]>0))
    {
        printf("\t�u�@�D�`���Ĳv�B�|���Kí�A�O�|�гy�̤j�Z�Ī��H�C\n");
    }
    else
    {
        if((intCount[4]==0))
        {
            printf("\t��4�̡G�e���]�����Ӭy���ͷN�C\n");
        }
        if((intCount[8]==0))
        {
            printf("\t��8�̡G�������η~�Z�A���ϤH���P���O�Υت��C\n");
        }
        if((intCount[4]==0)&&(intCount[8]==0))
        {
            printf("\t��48�̡G�����ʳs�u�A�b���n�ɡA�S��~�|��{�X�ӡA�Ʀܱj�L��ʳs�u�C\n");
        }
    }

    printf("�A�b6-8�s�u�s�u���R\n");
    if((intCount[6]>0)&&(intCount[8]>0))
    {
        printf("\t�֩����U�U�ȡB�ѨM���D�A�����ͷN�A�A�X�A�ȷ~�C\n");
    }
    else
    {
        if((intCount[6]==0))
        {
            printf("\t��6�̡G��F����z�B�P�H�����W�v�֡C\n");
        }
        if((intCount[8]==0))
        {
            printf("\t��8�̡G�P�H�����ʬO���D�^����ت����C\n");
        }
        if((intCount[6]==0)&&(intCount[8]==0))
        {
            printf("\t��68�̡G�����ʳs�u�A�b���n�ɡA�S��~�|��{�X�ӡA�Ʀܱj�L��ʳs�u�C\n");
        }
    }

    printf("\n�H�U�O�̷ӯʼƧ�X�A�����B��\n");
    for(i=1;i<10;i++)
    {
        if(intCount[i]==0)
        {
            printf("%d �N��\t",i);
            switch(i)
            {
            case 1:
                printf("��\n");
                break;
            case 2:
                printf("��\n");
                break;
            case 3:
                printf("��\n");
                break;
            case 4:
                printf("��\n");
                break;
            case 5:
                printf("��\n");
                break;
            case 6:
                printf("�Q\n");
                break;
            case 7:
                printf("��\n");
                break;
            case 8:
                printf("��\n");
                break;
            case 9:
                printf("��\n");
                break;
            }
        }

    }
    printf("\n");

    printf("\n�H�U�O�̷ӧA�ͤ�ƪ��v�T�G\n");
    printf("�ͤ�ơG\t%d\n",intBirthday);
    switch(intBirthday)
    {
    case 1:
        printf("(�C��1��B10��B19��B28��X�ͪ��H)�G�ѥͪ��Ѥj��\n");
        break;
    case 2:
        printf("(�C��2��B11��B20��B29��X�ͪ��H)�G�����M�����~��a\n");
        break;
    case 3:
        printf("(�C��3��B12��B21��B30��X�ͪ��H)�G�h�~�h�����}�ߪG\n");
        break;
    case 4:
        printf("(�C��4��B13��B22��B31��X�ͪ��H)�G�зǹ�F���ҽd��\n");
        break;
    case 5:
        printf("(�C��5��B14��B23��X�ͪ��H)�G�����ܤƪ��ۥѺ��F\n");
        break;
    case 6:
        printf("(�C��6��B15��B24��X�ͪ��H)�G�������q���ʮa�l\n");
        break;
    case 7:
        printf("(�C��7��B16��B25��X�ͪ��H)�G�u�z�ܤW�����F�v\n");
        break;
    case 8:
        printf("(�C��8��B17��B26��X�ͪ��H)�G���N�j�~���Կ�H\n");
        break;
    case 9:
        printf("(�C��9��B18��B27��X�ͪ��H)�G�@�ɤj�P���n���h\n");
        break;
    }

    printf("\n�H�U�O�P�yVS�ͩR�F�Ƽv�T�G\n");
    switch(intConstellation)
    {
    case 1:
        printf("�զϮy Aries 3.21-4.19 \n");
        switch(intMain)
        {
        case 1:
            printf("�ͩR�F��1���H....�A�O�ӥD�[�ܱj���H�A�u�Q�ۦۤv�Q�����ơC \n");
            break;
        case 2:
            printf("�ͩR�F��2���H....�A�|�b�N�O�H�ݧA�������A�өʤ���`�ۤ@�I�C \n");
            break;
        case 3:
            printf("�ͩR�F��3���H....���w��F�ۤv���Q�k�A���]�n�hťť�O�H���N���@�I\n");
            break;
        case 4:
            printf("�ͩR�F��4���H....�A�良�ӫ����ߡA�ܤ֭J��÷Q�A�|�}���a���V�O�C\n");
            break;
        case 5:
            printf("�ͩR�F��5���H....�̷R�����զϫD�A���ݡA�ר���w��B�h����x�C\n");
            break;
        case 6:
            printf("�ͩR�F��6���H....�A�ܩT���@�I�ר�O�P���h���A�ӥB�D�`���D�[�C\n");
            break;
        case 7:
            printf("�ͩR�F��7���H....���ۤvı�o���z���a��D�`������A��ť�O�H���N���C\n");
            break;
        case 8:
            printf("�ͩR�F��8���H....�ܭ�����ڼh�������N�A�|�ܧV�O�b�ǲߩM�u�@�W�C\n");
            break;
        case 9:
            printf("�ͩR�F��9���H....�A�O��������ڪ��H�A���L�A�������i�N���i���ܥi��C\n");
            break;
        }
        break;
    case 2:
        printf("�����y Taurus 4.20-5.20\n");
        switch(intMain)
        {
        case 1:
            printf("�ͩR�F��1���H....�A����ʤO�ܱj�A��Ʀۦ��@�M�A���k�]�����w���z�A�C \n");
            break;
        case 2:
            printf("�ͩR�F��2���H....�A�|�����H�����Y�A�b�P�O�H�۳B�ɤ]����e�����v�T�C\n");
            break;
        case 3:
            printf("�ͩR�F��3���H....�A�O���y������F�����A���w�o��ۤv�Ҭ�s�X�Ӫ��ƪ��C\n");
            break;
        case 4:
            printf("�ͩR�F��4���H....�A�O���y���̩T�����@�I�A���Q�k�`�`�M�O�H���Ӥ@�ˡC\n");
            break;
        case 5:
            printf("�ͩR�F��5���H....�A�O�@���h�~�h�������A�p�G����w�U�ӷ|�󦳦��N�C\n");
            break;
        case 6:
            printf("�ͩR�F��6���H....�A�O�̩��ª����y�A���ۤv�������F��|�D�`���@�C\n");
            break;
        case 7:
            printf("�ͩR�F��7���H....�A�O���q�f�ʮ檺�����A�����Q�O�H���A�A�ۦ��@�M�Q�k�C\n");
            break;
        case 8:
            printf("�ͩR�F��8���H....�A�ܭ�����ڼh�������N�A�|�V�O���ۤv��[���u�q�Φ��\�C\n");
            break;
        case 9:
            printf("�ͩR�F��9���H....�A�O���y���̦��ڷQ���A���O�n�h�ǲߦp�󸨹�b�{�ꤤ�C\n");
            break;
        }
        break;
    case 3:
        printf("���l�y Gemini 5.21-6.21 \n");
        switch(intMain)
        {
        case 1:
            printf("�ͩR�F��1���H....���w�ۥѦۦb���A�A���ۤv�����쪺�Ʊ����|�h�p��@�I \n");
            break;
        case 2:
            printf("�ͩR�F��2���H....�A�O�̳��w�P�O�H���q�����l�y�A���L�ܮe�����~�Ӫ��v�T�C \n");
            break;
        case 3:
            printf("�ͩR�F��3���H....�A�u���O���l�y���̬��h�~�h�����A����F�賣�O�@�ǴN�|�C\n");
            break;
        case 4:
            printf("�ͩR�F��4���H....�A�O��������ͬ��W�ߪ��H�A�ݨ��H�M���ۦ��@�M�W�h�C\n");
            break;
        case 5:
            printf("�ͩR�F��5���H....���w��B�ö]���A�u�O��ͺ��ѤU�A�ߩʤW�]�����í�w�C\n");
            break;
        case 6:
            printf("�ͩR�F��6���H....�A�O���l���̭����H�������A�ר䭫���ѪB�ͤ������P���C\n");
            break;
        case 7:
            printf("�ͩR�F��7���H....�A�O���l���̤N�p�j�Ǫ��A�`�Q�ǧO�H�����|�Q�쪺���D�C\n");
            break;
        case 8:
            printf("�ͩR�F��8���H....�A���w�ɨ��ͬ��A�|�S�O���`���ۤv���ͬ��~��C\n");
            break;
        case 9:
            printf("�ͩR�F��9���H....�A�O���l���̷|�J��÷Q���A�P�ɤ]�O����������C\n");
            break;
        }
        break;
    case 4:
        printf("���ɮy Cancer 6.22-7.22 \n");
        switch(intMain)
        {
        case 1:
            printf("�ͩR�F��1���H....�A�өʤW���I�۳��@�I���e���u���M�O�H���n����y�C \n");
            break;
        case 2:
            printf("�ͩR�F��2���H....�|�ܬݭ��O�H���N���A�n�p�ߦ]���ॢ�ۤv���N���C\n");
            break;
        case 3:
            printf("�ͩR�F��3���H....���w�P���W����F�P���q�A�b���N�W�|���������ѥ����I\n");
            break;
        case 4:
            printf("�ͩR�F��4���H....�A�O�ɤl������t�򪺡A�ר䭫���ۤv�ͬ��W���W�ߡC\n");
            break;
        case 5:
            printf("�ͩR�F��5���H....�A���@�w���w�ö]�A���������Ӧh����A�Q�ۥѦۦb�C\n");
            break;
        case 6:
            printf("�ͩR�F��6���H....�A�O�ɮy���̭��P�����A�ר�b�P���@�ɸ̫ܭn�D�����C\n");
            break;
        case 7:
            printf("�ͩR�F��7���H....�A�O�ɤl���Q�o�̦h���A��{�X�Ӫ��Ҽˤ]�ᬰ�T���v���C\n");
            break;
        case 8:
            printf("�ͩR�F��8���H....�A�ܭ����{��W�����N�Pí�w�A�|�V�O���ۤv���ͬ���n�C\n");
            break;
        case 9:
            printf("�ͩR�F��9���H....�A�O�ɤl���۷�������A�����s�����ҷ|����`�ۡC\n");
            break;
        }
        break;
    case 5:
        printf("��l�y Leo 7.23-8.22 \n");
        switch(intMain)
        {
        case 1:
            printf("�ͩR�F��1���H....�A�O��l�y���̬��ۧڪ��A���i��]���y���H�ڰ��D�C \n");
            break;
        case 2:
            printf("�ͩR�F��2���H....�O�H���֩w��A�ӻ��D�`���n�A�i��]���ӥ��h�ۧڡC\n");
            break;
        case 3:
            printf("�ͩR�F��3���H....�A�O��l�y���̷R��{�ۤv���A�q�`�O�H�����Y����˳˳�̡C\n");
            break;
        case 4:
            printf("�ͩR�F��4���H....�A�O���T������l�A�ӥB�b��ʤW����ʥF�_�I�������믫�C\n");
            break;
        case 5:
            printf("�ͩR�F��5���H....��l���̼��R�ۥѪ��N�O�A�աI�@��ӻ��A�̬O�۷�j�誺�C\n");
            break;
        case 6:
            printf("�ͩR�F��6���H....�A�O��l�y������t�򪺡A�ר�O�P������F�W�|��o�`�ۡC\n");
            break;
        case 7:
            printf("�ͩR�F��7���H....�A�O�ܷ|�Q����l�y�@�I���M����D�[�A���٥i�H���q�C\n");
            break;
        case 8:
            printf("�ͩR�F��8���H....�A�O�@�����s�ͬ��~�����H�@�I���w�q�e�u�쪺�L��l�C\n");
            break;
        case 9:
            printf("�ͩR�F��9���H....�A�������ܮe���P�ʧO�H�A�b�H�s���`�O�H��ܩ������P���I\n");
            break;
        }
        break;
    case 6:
        printf("�B�k�y Virgo 8.23-9.22 \n");
        switch(intMain)
        {
        case 1:
            printf("�ͩR�F��1���H....�A���I�t���A�`�`ı�o�O�H���F�ѧA�A�n�h�P�O�H���ʤ~�n�C \n");
            break;
        case 2:
            printf("�ͩR�F��2���H....�A�|�ܪ`���C�ӤH���N���A�P�O�H�ө��ɤ]�O�D�`�������C \n");
            break;
        case 3:
            printf("�ͩR�F��3���H....��O��Ϊ��A�A�A�X����o���ΥD�������ȡA�|�ӥ��r�֮@�I\n");
            break;
        case 4:
            printf("�ͩR�F��4���H....�A�O�B�k�y���̬��t�򪺡A�ר�e�����a�ۭ��A�n�S�O�`�N�C\n");
            break;
        case 5:
            printf("�ͩR�F��5���H....�A�O�ݩ����~�V���A�e�����\�h�B�͡A�����ߪ��ä��h�C\n");
            break;
        case 6:
            printf("�ͩR�F��6���H....�A�O�D�`�D�`���ª��H�@�I�ר�O�P���W�A�`�`�����αˡC\n");
            break;
        case 7:
            printf("�ͩR�F��7���H....�A���өʤ���誽�A���L�b�P�H�橹�W�٬O�n�h��̧O�H�@�I\n");
            break;
        case 8:
            printf("�ͩR�F��8���H....�A�O�����ƪ��H�A�ܤF�ѤH�ڤW����y�n�p�󤬰ʡC\n");
            break;
        case 9:
            printf("�ͩR�F��9���H....��A��J���Ʊ��D�`���g���A���ɬƦܦ]���Ӽo��ѭ��C\n");
            break;
        }
        break;
    case 7:
        printf("�ѯ��y Libra 9.23-10.22 \n");
        switch(intMain)
        {
        case 1:
            printf("�ͩR�F��1���H....�A�O���l������W�ߪ��A�b�M�w�Ʊ��ɤ]������|�S�ݤ��M�C\n");
            break;
        case 2:
            printf("�ͩR�F��2���H....�b���l���A�O�̻ݭn�O�H���񪺡A�p�G�S����|�P�줣�w�C\n");
            break;
        case 3:
            printf("�ͩR�F��3���H....�A�O���l���̦��~�ت��A�b�U�����N��쳣���������ѥ��C\n");
            break;
        case 4:
            printf("�ͩR�F��4���H....�A�O���l���̬�������ڼh�����A�]�O������d���P���@�I\n");
            break;
        case 5:
            printf("�ͩR�F��5���H....�A�O�@���߷R��C���ѯ��A��P��n�����Ʊ������|��L�C\n");
            break;
        case 6:
            printf("�ͩR�F��6���H....�P�������Q�P�_��A�ӻ��D�`���n�@�I�n�p�ߪ��g��~�n�C\n");
            break;
        case 7:
            printf("�ͩR�F��7���H....�A�O���l���̳��w��Ҫ��A��\�h�Ƴ��|��X�X�z����k�C\n");
            break;
        case 8:
            printf("�ͩR�F��8���H....�ܭ����ͬ����Pı�A����Ԩ��Ӯt���ͬ����ҡA�����}�ɦV�C\n");
            break;
        case 9:
            printf("�ͩR�F��9���H....�A�\�h�Q�k�����Ǥ�����ڡA�ӥB�����`�`�L�k���[�@�I\n");
            break;
        }
        break;
    case 8:
        printf("���Ȯy Scorpio 10.23-11.21 \n");
        switch(intMain)
        {
        case 1:
            printf("�ͩR�F��1���H....�A�ܭ����ۤv���ؼСA���Ӳz�B�����L�H�b���Ǥ���C\n");
            break;
        case 2:
            printf("�ͩR�F��2���H....�A�ܦb�G��H���Y�W�����ۡA�|���ߥ��N����ݥt�@�b�C\n");
            break;
        case 3:
            printf("�ͩR�F��3���H....��󷾳q�P�H�����Y�O�A���M���A�`����o��j�a���U�C\n");
            break;
        case 4:
            printf("�ͩR�F��4���H....�A�O�D�`�D�`�T�����A�@���A�M�w���ƴN���H���ܡC\n");
            break;
        case 5:
            printf("�ͩR�F��5���H....�A�O�Ȥl���̶}�Ԫ��A�]�O�̮e���P�j�a�����@�����C\n");
            break;
        case 6:
            printf("�ͩR�F��6���H....�A�O�ӧ����D�q�̡A�ר�O�D�`�����P���譱���g��C\n");
            break;
        case 7:
            printf("�ͩR�F��7���H....�A�Q���ܦh�A�`�Q��@�ǧO�H�䤣�쪺���D�A�D�`�o���C\n");
            break;
        case 8:
            printf("�ͩR�F��8���H....�A�ܭ����ۤv���a���|�a��A�{�����ӱo�쪺�N�|�h�����C\n");
            break;
        case 9:
            printf("�ͩR�F��9���H....���A���w�ά۫H���ƬO�D�`�g�����A�����W�ݤ��X�ӡC \n");
            break;
        }
        break;
    case 9:
        printf("�g��y Sagittarius 11.22-12.21 \n");
        switch(intMain)
        {
        case 1:
            printf("�ͩR�F��1���H....�A�`�`�ڦ�گ��A�@���ؼдN�|�ܧ֥h����A��ʤO�ܱj�C\n");
            break;
        case 2:
            printf("�ͩR�F��2���H....���w�P�O�H���q�۳B���A�A�b�H�ڤW�|�o��j�a�������C\n");
            break;
        case 3:
            printf("�ͩR�F��3���H....�A�O�۷��~�ت��H�@�I�ܯ����{�ۤv�b���N�W���~�ءC\n");
            break;
        case 4:
            printf("�ͩR�F��4���H....�A�O�g��y���̭����ͬ��W�ߪ��A�ӥB�]�ܦ��ۤv���Q�k�C\n");
            break;
        case 5:
            printf("�ͩR�F��5���H....�z�I�A�u�O�W�R�ö]�A�@���ݦb�P�@�Ӧa��|���A�����L�C\n");
            break;
        case 6:
            printf("�ͩR�F��6���H....�A�O�ܭ����˱����H�@�I�b�H�ڥ�y�W�]�O�ܦ��@�M���C\n");
            break;
        case 7:
            printf("�ͩR�F��7���H....�A�u�O�Q�o�Ӧh�A�S���I�T�����H�A�h�ê��ߺA�ܱj�@�I\n");
            break;
        case 8:
            printf("�ͩR�F��8���H....�A�ܭ����ۤv�����N�M�~�b����{�A���w�I�Ϊ��ͬ����ҡC\n");
            break;
        case 9:
            printf("�ͩR�F��9���H....�A�O�ܦ��z�Q���H�A�]�O�|�쬡�ʪ�����A����j�a�w��I\n");
            break;
        }
        break;
    case 10:
        printf("���~�y Capricorn 12.22-1.19\n");
        switch(intMain)
        {
        case 1:
            printf("�ͩR�F��1���H....�A���۴L�ܱ߫j�@�I�|�q�q���V�O���ۤv���Ҧ��N�C\n");
            break;
        case 2:
            printf("�ͩR�F��2���H....�Aı�o�P�H��C�O�󭫭n���ơA�t�~�P���]�O�ͬ����ߡC \n");
            break;
        case 3:
            printf("�ͩR�F��3���H....�u�n�A�h�[�V�O�N��i�{�X�ۤv���~�ءA�|�ܦ����N�@�I\n");
            break;
        case 4:
            printf("�ͩR�F��4���H....�A�ܭ����}���a���ͬ��A�|�V�O���ۤv�ͬ�í�w�U�ӡC\n");
            break;
        case 5:
            printf("�ͩR�F��5���H....�A�O���~�y������}�Ԫ��A��@�ǨƤ�����|����~�{�C\n");
            break;
        case 6:
            printf("�ͩR�F��6���H....�P���O�A�ͬ���í�����I�A�Ʊ�g�禳���Ӫ��P���ͬ��C\n");
            break;
        case 7:
            printf("�ͩR�F��7���H....�A�O�@�ӫD�`�o�����H�A�����ɷ|�]�����ƦӤU���P�_�C\n");
            break;
        case 8:
            printf("�ͩR�F��8���H....��A�ӻ��\���W�N�l�ޤO�j�A�|�V�O�������n���H���C\n");
            break;
        case 9:
            printf("�ͩR�F��9���H....�A��ۤv�Q�����ƫD�`��J�A���L���ɷ|�ѤF��ڪ��p�C\n");
            break;
        }
        break;
    case 11:
        printf("���~�y Aquarius 1.20-2.18 \n");
        switch(intMain)
        {
        case 1:
            printf("�ͩR�F��1���H....�A�O�~�l�y���̦۳����A���ɭԷ|��o�ӹL�ڦ�گ��F�ǡC \n");
            break;
        case 2:
            printf("�ͩR�F��2���H....�A�|�������O�H���v�T�A���٤��|���h�ۤv�쥻���D�i�C\n");
            break;
        case 3:
            printf("�ͩR�F��3���H....�A�O�@���h�~�h�����~�l���I�ר�ժ����F�P���q�@�I\n");
            break;
        case 4:
            printf("�ͩR�F��4���H....�A�O�~�l�����í�w���A�|�ߺD�����Y�@�إͬ����覡�C\n");
            break;
        case 5:
            printf("�ͩR�F��5���H....�`�`���H�䤣�쪺�N�O�A�o�ز~�l�աI�B�ͤ]�O�h���ӼơC\n");
            break;
        case 6:
            printf("�ͩR�F��6���H....�A�O������P�����~�l�A�]������A�P�����D�|����h�C\n");
            break;
        case 7:
            printf("�ͩR�F��7���H....�A�O�~�l���̬��z�ʪ��A�ӹL�o�����ܦ��ɭԷ|����H���C\n");
            break;
        case 8:
            printf("�ͩR�F��8���H....�A�O�~�l������������誺�A�|�h�l�D�ۤv�ҷQ�n���ͬ��C\n");
            break;
        case 9:
            printf("�ͩR�F��9���H....�A���z�Q�D�`�����A�p�G����V�O�A���\�����|�O�ܤj���C\n");
            break;
        }
        break;
    case 12:
        printf("�����y Pieces 2.19-3.20 \n");
        switch(intMain)
        {
        case 1:
            printf("�ͩR�F��1���H....�A�e���H�Ħb�ۤv���@�ɪ��A�ѱ��F�����٦��O�H�s�b�C\n");
            break;
        case 2:
            printf("�ͩR�F��2���H....�A�ܮe������O�H���޾ɡA�ӧѰO�F�ۤv�쥻����V�@�I\n");
            break;
        case 3:
            printf("�ͩR�F��3���H....�A�O�ѥͪ����N�a�A���L�٬O�n�y���`�N�@�U�{�����ҡC\n");
            break;
        case 4:
            printf("�ͩR�F��4���H....�A�O�l�Dí�w�ͬ������y�A�����w�ӹL�V�ê��ͬ��C\n");
            break;
        case 5:
            printf("�ͩR�F��5���H....�A����S���ؼСA�X�G����Ƴ��|�h�����ݡA�����������[�C\n");
            break;
        case 6:
            printf("�ͩR�F��6���H....�P���O�A�̷дo���ơA�`�`�]���Ө��쥴���ή���C\n");
            break;
        case 7:
            printf("�ͩR�F��7���H....�A�Q�o�ܦh�A���O�@���J��ۤv���Ʊ��N�|����D�[�C\n");
            break;
        case 8:
            printf("�ͩR�F��8���H....�A�O���w�ɨ������y�A���ͬ��W���p�Ƴ��D�`���`�N�C\n");
            break;
        case 9:
            printf("�ͩR�F��9���H....�A���Y�ǨƳ���۫ܤj�����ۡA�L�ת��ܷ|��o�S�O�����C\n");
            break;
        }
        break;
    }
    return 0;
}
