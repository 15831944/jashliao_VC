#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char source[80];
    char search[80];
    char *loc;
	
    printf("��J�r��G");
    gets(source);
	
    printf("�j�M�l�r��G");
    gets(search);
	
    loc = strstr(source, search);
	
    if(loc == NULL) {
        printf("�䤣��ŦX���l�r��\n");
    }
    else {
        printf("�b���ަ�m %d �B���l�r��\n", loc - source);
    }
	
    return 0; 
}