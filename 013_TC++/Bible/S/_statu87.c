
/*                           */
/* Program Name : statu87.c  */
/*                           */

#include <stdio.h>
#include <float.h>

void main(void)
{
   float float_val;
   double double_val=1.5e-100;
   printf("Status 87 before error: %X\n",_status87());
   /* create underflow and precision loss */
   float_val=double_val;
   printf("Status 87 after  error: %X\n",_status87());
}

