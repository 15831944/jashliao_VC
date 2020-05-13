#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>

using namespace std;

//https://cg2010studio.com/2011/04/16/cc-%E5%88%97%E5%87%BA%E8%B3%87%E6%96%99%E5%A4%BE%E4%B8%AD%E6%AA%94%E6%A1%88%E5%90%8D%E7%A8%B1-list-a-directory/
int getdir(string dir, vector<string> &files);
int main(){
    string dir = string("./");//[./�O��U�ؿ�] ��Ƨ����|(�����}or�۹��})
    vector<string> files = vector<string>();
    getdir(dir, files);
    FILE *pf=fopen("00_filelist.txt","w");
    //��X��Ƨ��M�ɮצW�٩�ù�
    for(int i=0; i<files.size(); i++){
        cout << files[i] << endl;
        fprintf(pf,"%s\n",files[i].c_str());
    }
    fclose(pf);
    return 0;
}
int getdir(string dir, vector<string> &files){
    DIR *dp;//�Х߸�Ƨ�����
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == NULL){
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while((dirp = readdir(dp)) != NULL){//�p�Gdirent���ЫD��
        files.push_back(string(dirp->d_name));//�N��Ƨ��M�ɮצW��Jvector
    }
    closedir(dp);//������Ƨ�����
    return 0;
}
