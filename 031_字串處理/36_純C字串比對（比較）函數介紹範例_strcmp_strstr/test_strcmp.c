#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
                                                                                
int main(int argc, char* argv[]) {
    char passwd[] = "123456";
    char input[7];
	
    printf("�п�J�K�X�G");
    gets(input);
	
    if(strcmp(passwd, input) == 0) {
        puts("�K�X���T");
    }
    else {
        puts("�K�X���~");
    }
	
    return 0; 
}