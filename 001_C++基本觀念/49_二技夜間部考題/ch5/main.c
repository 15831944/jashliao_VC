#include <stdio.h>
#include <stdlib.h>
#include <math.h>//�ޥμƾǨ禡�w 

int main(int argc, char *argv[])
{
  float fltPI;//�t�Ϊ�PI�w�q 
  float fltpi=3.14;//�ۤv��PI�w�q
  float fltinput=0;//�����s���ܼ� 
  float flt_r01=0;//�b�|1 
  float flt_r02=0;//�b�|2
  float flt_2r01=0;//���|1 
  float flt_2r02=0;//���|2
  fltPI=4*atan(1);//atan(1)=PI/4 
  printf("�п�J�ꪺ�b�|�Ϊ��|\t"); 
  scanf("%f",&fltinput); 
  flt_r01=fltinput;//�b�|1 
  flt_2r01=fltinput*2.0;//���|1 
  flt_r02=fltinput/2.0;//�b�|2
  flt_2r02=fltinput;//���|2
  
  printf("�Y�z��~��J���b�|=%f\n",flt_r01); 
  printf("�h�Ӷꪺ���|��=%f\n",flt_2r01);
  printf("�h�Ӷꪺ�P����=%f\n",(2*fltpi*flt_r01));
  printf("�h�Ӷꪺ���n��=%f\n",(flt_r01*flt_r01*fltpi));
  printf("===============================================\n"); 
  printf("�Y�z��~��J�����|=%f\n",flt_2r02);
  printf("�h�Ӷꪺ�b�|��=%f\n",flt_r02); 
  printf("�h�Ӷꪺ�P����=%f\n",(2*fltpi*flt_r02));
  printf("�h�Ӷꪺ���n��=%f\n",(flt_r02*flt_r02*fltpi));
  printf("===============================================\n"); 
  printf("�H�W�p�⪺��g�v�w�q��=%f\n",fltpi);
  printf("C�y������g�v�w�q��=%f\n",fltPI);
  printf("�t�ζ�P�v�M�ۦ�w�q���~�t=%f\n",(fltPI-fltpi));
  system("PAUSE");	
  return 0;
}
