#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <direct.h>

using namespace std;

//�̦h���]���Ӽ�
#define MAX_FILE_COUNT 1024
//�̤j���|�r������
#define MAX_PATH 260
//����Y
struct FileHead
{
    unsigned int FileCount;//���Ӽ�
    unsigned int FileLen[MAX_FILE_COUNT];//���j�p
    char FileName[MAX_FILE_COUNT][MAX_PATH];//�ɮצW
};
char gchrFileName[200],gchrPath[200];
char gchrFileExt[20];
void GetFileName(char *data);
long GetFileSize(FILE *pf);
int main(int argc, char *argv[])
{
    int i=0;
    FILE *pf='\0';
    char buf[513];
    string strbuf;
    FILE *pWorkFile = '\0';
    FileHead fh;
    FILE *pOutFile = '\0';
    char chrCABFilePath[512];
    unsigned char *pTmpData = NULL;
    char chrOuputPath[256];
    char tmpFileName[MAX_PATH];
    FILE *pCAB = '\0';

    cout << "Hello world!" << endl;
    memset(buf,0,sizeof(buf));
    pf=fopen("filelist.txt","r");
    vector<string> vec_file;
    vec_file.clear();
    while(fgets(buf,512,pf) != NULL)
    {
        buf[strlen(buf)-1]='\0';
        vec_file.push_back(buf);
    }

    //���󤺪����|�s�쵲�c�餺�A�ç���ɮפj�p
    memset(&fh,0,sizeof(FileHead));
    fh.FileCount=0;
    for ( i = 0 ; i < vec_file.size() ; i++ )
    {
        strbuf=vec_file[i];
        strcpy(buf, strbuf.c_str());
        strcpy(fh.FileName[fh.FileCount],buf);
        pWorkFile= fopen(fh.FileName[i],"rb");
        fh.FileLen[i] = GetFileSize(pWorkFile);
        fclose(pWorkFile);
        pWorkFile = '\0';
        //printf("%s,%ld\n",fh.FileName[i],fh.FileLen[i]);
        fh.FileCount++;
    }

    //�N�Ҧ����w�ɮץ��]

    memset(chrCABFilePath,0,sizeof(char));
    strcpy(chrCABFilePath,"test.cab");
    //*
    pOutFile = fopen(chrCABFilePath,"wb");
    fwrite(&fh,sizeof(fh),1,pOutFile);//�g�J���Y
    for (i = 0 ; i < fh.FileCount ; i++ )
    {
        pWorkFile='\0';
        pWorkFile = fopen(fh.FileName[i],"rb");
        if ( NULL == pWorkFile )
        {
            fclose(pWorkFile);
            fclose(pOutFile);
            return -1;
        }

        pTmpData = new unsigned char[fh.FileLen[i]];
        fread(pTmpData,fh.FileLen[i],1,pWorkFile);
        if ( ferror(pWorkFile) )
        {
            fclose(pWorkFile);
            fclose(pOutFile);
            return -2;
        }

        fwrite(pTmpData,fh.FileLen[i],1,pOutFile);
        if ( ferror(pOutFile) )
        {
            fclose(pWorkFile);
            fclose(pOutFile);
            return -3;
        }
        delete [] pTmpData;
        pTmpData='\0';
        fclose(pWorkFile);
    }
    fclose(pOutFile);
    pOutFile='\0';
    //*/
    //�N���]�ɸѶ}�A�����w���|
    strcpy(chrCABFilePath,"D:\\Visual project code\\CB_CustomCAB\\test.cab");
    memset(chrOuputPath,0,sizeof(char));
    strcpy(chrOuputPath, "C:\\CAB_Buf");
    if((mkdir(chrOuputPath)==0)||(chdir(chrOuputPath)==0))
    {
        pCAB = fopen(chrCABFilePath,"rb");
        memset(&fh,0x0,sizeof(fh));
        fread(&fh,sizeof(fh),1,pCAB);//Ū��������Y
        for ( int i = 0 ; i < fh.FileCount ; i++ )
        {
            pTmpData = new unsigned char[fh.FileLen[i]];
            fread(pTmpData,fh.FileLen[i],1,pCAB);
            GetFileName(fh.FileName[i]);

            memset(tmpFileName,0,sizeof(char));
            sprintf(tmpFileName,"%s\\%s%s",chrOuputPath,gchrFileName,gchrFileExt);
            pWorkFile = '\0';
            pWorkFile = fopen(tmpFileName,"wb");
            fwrite(pTmpData,fh.FileLen[i],1,pWorkFile);
            fclose(pWorkFile);
            delete [] pTmpData;
            pTmpData='\0';
        }
        fclose(pCAB);
    }
    return 0;
}
//����ɤj�p(�ǤJ�H�G�i��覡���}���ɫ��w)
long GetFileSize(FILE *pf)
{
    //���w�����ɮ׵���
    fseek(pf,0,/*SEEK_END*/ 2);
    return ftell(pf);
}
void GetFileName(char *data)
{
    gchrPath[0]='\0';
    gchrFileName[0]='\0';
    gchrFileExt[0]='\0';
    int i,intcount;
    int j=0;
    int k=0;
    char d;
    intcount=strlen(data);//�p��쥻�����ɮ׸��|����
    for(i=(intcount-1);i>=0;i--)
    {
        if((data[i]!='/')&&(data[i]!='\\'))
        {
            d=data[i];
            gchrPath[j]=d;
            j++;
        }
        else
        {
            break;
        }
    }
    gchrPath[j]='\0';
    for(int i=0;i<j;i++)
    {
        if(i<(j-4))
        {
            gchrFileName[i]=gchrPath[j-i-1];
            gchrFileName[i+1]='\0';
        }
        else
        {
            gchrFileExt[k]=gchrPath[j-i-1];
            k++;
            gchrFileExt[k]='\0';
        }
    }
    gchrPath[0]='\0';
    for(i=0;i<(intcount-j);i++)
    {
        gchrPath[i]=data[i];
    }
    gchrPath[(intcount-j)]='\0';
    //cout<<chrPath<<"\n";
    //cout<<chrFileName<<"\n";
}
