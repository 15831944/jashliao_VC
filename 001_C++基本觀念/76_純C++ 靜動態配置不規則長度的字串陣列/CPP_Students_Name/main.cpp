#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;
/*
    ��C++ �R/�ʺA�t�m���W�h���ת��r��}�C
    �ت��`�ٰO���骺�ζq
*/
int main()
{
    /*
    //�R�A�ŧi2�Ӫ��פ��P���r��]�r���}�C�^
    char *pchrStudentName[2]={"Tom lin","Jash liao"};
    cout << pchrStudentName[0] << endl;
    cout << pchrStudentName[1] << endl;
    //*/

    //*
    //�ʺA�A�ŧiN�Ӫ��פ��P���r��]�r���}�C�^
    char **pchrStudentName;
    char buf[100];
    int num=0,i=0,j=0;
    cout<<"��J�Ӽ�:"<< "\t";
    cin>>num;
    pchrStudentName= new char*[i];
    for(i=0;i<num;i++)
    {
        buf[0]='\0';
        cout<<"��J��"<<i<<"�ӤH�W:"<< "\t";

        cin>>buf;
        j=strlen(buf);
        pchrStudentName[i] = new char[j];
        strcpy(pchrStudentName[i],buf);
    }
    for(i=0;i<num;i++)
    {

        cout<<"��J��"<<i<<"�ӤH�W:"<< "\t";
        cout<<pchrStudentName[i]<< endl;
    }
    //*/
    return 0;
}
