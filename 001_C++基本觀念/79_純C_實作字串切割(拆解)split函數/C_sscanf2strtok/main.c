#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
strtok �O�@�ӥi�ֳt���Φr�ꪺ���
�t�~sscanf�]�O�i�H�Ψө�Ѧr��A���O�Ϊk�N�S��strtok��K
*/
int main ()
{
    char str[] ="- This, a sample string.";
    char * pch;
    printf ("Splitting string \"%s\" into tokens:\n",str);
    pch = strtok (str," ,.-");
    while (pch != NULL)
    {
        printf ("%s\n",pch);
        pch = strtok (NULL, " ,.-");
    }
    return 0;
}
