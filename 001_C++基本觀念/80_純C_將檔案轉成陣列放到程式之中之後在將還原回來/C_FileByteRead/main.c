#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {

    if(argc != 2) {
        puts("���O: read <filename>");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if(!file) {
        puts("�L�kŪ���ɮ�");
        return 1;
    }

    unsigned char ch;
    int count = 0;

    while(!feof(file)) {
        fread(&ch, sizeof(char), 1, file);

        printf("%d,", ch);//printf("%2X ", ch);
        count++;
        if(count > 16) {  // ����
            putchar('\n');
            count = 0;
        }
    }
    putchar('\n');

    fclose(file);

    return 0;
}
