#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
�䴩���X�ާ@�G
�@�@%[a-z] ��ܤǰta��z�����N�r���A�g����(�ɥi��h���ǰt)
�@�@%[aB'] �ǰta�BB�B'���@���A�g����
�@�@%[^a] �ǰt�Da�����N�r���A�g����
*/
int main()
{
	char Info[]="Dec 12/25 School ClassRoom";
	char Data1[16];
	char Data2[16];
	char Data3[16];
        char Data4[16];
	sscanf(Info, "%s %s %s", Data1, Data2,Data3);
        printf("Data1:%s Data2:%s Data3:%s\n", Data1, Data2, Data3);
	sscanf(Info, "%[^ ] %[^ ] %[^ ]", Data1, Data2,Data3);
        printf("Data1:%s Data2:%s Data3:%s\n", Data1, Data2, Data3);
	sscanf(Info, "%s  %[^ ] %[a-z A-Z]", Data1, Data2,Data3);
    sscanf(Info, "%s  %[^ ] %[a-z A-Z]", Data1, Data4);
	printf("Data1:%s Data2:%s Data3:%s\n", Data1, Data4, Data3);

}
