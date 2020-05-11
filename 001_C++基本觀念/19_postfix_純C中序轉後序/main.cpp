#include <cstdlib>
#include <iostream>
#include <cstdio> 
using namespace std;
int postfix(char*); // �������� 
int priority(char); // �M�w�B��l�u������ 
int main(int argc, char *argv[])
{
    char input[80];
    printf("��J���ǹB�⦡�G");
    scanf("%s", input);
    postfix(input); 
    system("PAUSE");
    return EXIT_SUCCESS;
}
int postfix(char* infix) { 
    int i = 0, top = 0; 
    char stack[80] = {'\0'}; 
    char op; 

    while(1) { 
        op = infix[i]; 

        switch(op) { 
            case '\0': 
                while(top > 0) { 
                    printf("%c", stack[top]); 
                    top--; 
                } 
                printf("\n"); 
                return 0; 
            // �B��l���| 
            case '(': 
                if(top < (sizeof(stack) / sizeof(char))) { 
                    top++; 
                    stack[top] = op; 
                } 
                break; 
            case '+': case '-': case '*': case '/': 
                while(priority(stack[top]) >= priority(op)) { 
                    printf("%c", stack[top]); 
                    top--; 
                } 
                // �s�J���| 
                if(top < (sizeof(stack) / sizeof(char))) { 
                    top++; 
                    stack[top] = op; 
                } 
                break; 
            // �J ) ��X�� ( 
            case ')': 
                while(stack[top] != '(') { 
                    printf("%c", stack[top]); 
                    top--; 
                } 
                top--;  // ����X( 
                break; 
            // �B�⤸������X 
            default: 
                printf("%c", op); 
                break; 
        } 
        i++; 
    } 
} 

int priority(char op) { 
    int p; 

    switch(op) { 
       case '+': case '-': 
            p = 1; 
            break; 
        case '*': case '/': 
            p = 2; 
            break; 
        default: 
            p = 0; 
            break; 
    } 

    return p; 
}
