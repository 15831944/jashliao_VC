/* The following sample illustrates the use of brackets and the
   caret (^) with sscanf().
   Compile options needed: none
�U�C�d����ܦp��ϥ� sscanf () C Run - Time �禡�A �q���㦳�r�� (�A) ���j�������w�İ�Ū���C
���_�O�A �H�U�C�榡�� sscanf () �禡�ϥάA�����C �榡�N�|�O %�A ] '�B ' ^ [ �i���禡�A �����F�r�� (�A) Ū���۸�ƽw�İϨ�
*/ 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

char *tokenstring = "first,25.5,second,15";
int result, i;
double fp;
char o[10], f[10], s[10], t[10];

void main()
{
   result = sscanf(tokenstring, "%[^','],%[^','],%[^','],%s", o, s, t, f);
   fp = atof(s);
   i  = atoi(f);
   printf("%s\n %lf\n %s\n %d\n", o, fp, t, i);
}