#include <cstdlib>
#include <iostream>
#include <fstream>//��c++
#include <cstdio>//��c 
using namespace std;

int main(int argc, char *argv[])
{
    char C_chrinputdata[100]="a c_string",C_chroutputdata[100];
    FILE *pf;
    pf=fopen("c.txt","w");
    fprintf(pf,"%s\n",C_chrinputdata);
    fclose(pf);
    pf=fopen("c.txt","r");
    fgets(C_chroutputdata,100,pf);
    printf("���X��J�r��%s\n",C_chroutputdata);
    fclose(pf);
    ////////////////////////////////////////////////////////////
    char Cpp_chrinputdata[100]="a cpp_string",Cpp_chroutputdata[100];
    fstream fp;
    fp.open("cpp.txt",ios::out|ios::trunc);
    fp<<Cpp_chrinputdata;
    fp.close();
    fp.open("cpp.txt",ios::in);
    fp.getline(Cpp_chroutputdata,100);
    cout<<"���X��J�r��"<<Cpp_chroutputdata<<"\n";
    fp.close(); 
    system("PAUSE");
    return EXIT_SUCCESS;
}
