#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
/*
����C������ 
wasd�W���U�k  j �U��
�t�~�o�O��H��Ԫ�~~(�p�̤��|�gAI= ="
�ǤF�@�Uclass �g�Ӥ��l��
*/
class object
{
    int map;    //private
    
    public:
    int **array;
    int player;
    object()
    {   int i=0;
      player=0;
  
    for(;;)
   {
     cout<<"�п�J�ҭn���a�Ϥj�p:X x X\n";
          cin>>map;
    
    if(map < 10 || map >30)
          cout<<"�п�J�A�X���Ʀr 10~30\n";
      else
      {
        system("cls");
     array= new int* [map];
           for(i=0;i<map;i++)
     array[i]= new int [map];
         
     break;
      }
   }
}
//void test(){ cout<<map;}; 
void print();
void process(int *x,int *y); 
void gotoxy(int x,int y);  
int check();
};
void object::print()
{
  int i,j; 
  
  for(i=0;i<map;i++)
   {
for(j=0;j<map;j++)
    array[i][j]=0;
   }
     for(i=0;i<map;i++)
  {
      for(j=0;j<map;j++)
   {
     if(i==0 && j==0) cout<<"�z";
     else if(i==0 && j==(map-1)) cout<<"�{";
  else if(i==0) cout<<"�s";
     
     if(j==0 && i!=0 && i!=map-1) cout<<"�u";
  else if( i!=map-1 && i!= 0 && j==map-1) cout<<"�t";
  if(i!=0 && j!=0 && i!=map-1 && j!=map-1) cout<<"�q";
  if(i==map-1 && j==0) cout<<"�|";
  if(i==map-1&& j!=0 && j!=map-1) cout<<"�r";
  if(i==map-1 && j==map-1) cout<<"�}";
   }
  
   cout<<"\n";
  }
   cout<<"���a1��"<<"   "<<"���a2��";
}
void object::process(int *x,int *y)
{
  char ch;
  ch=_getch();
  
   switch (ch)
  {
  case 'w': if(*y>0)
   (*y)--;
         break;
   
  case 'a': if(*x>0)
   (*x)=(*x)-2;
         break;
   
  case 's': if(*y<map-1)
   (*y)++;
         break;
   
  case 'd': if(*x/2<map-1)
   (*x)=(*x)+2;
            break;
   
  
  case 'j': if(player%2==0 && array[*x/2][*y]==0)
   {
   cout<<"��";
            array[*x/2][*y]=1;
            player++;
   }
   if(player%2==1 && array[*x/2][*y]==0)
   {
            cout<<"��";
   array[*x/2][*y]=2;
   player++;
   }
            break;
  
  default : break;
  }


}
void object::gotoxy(int x, int y){
static HANDLE hConsole = 0; //��l��
static int instanceCount = 0;
COORD coord;
  if( instanceCount == 0 ){
  //���o�ù�������
  hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
  instanceCount = 1;
}
coord.X = x ;
coord.Y = y ;
//�N��в��ܩҫ��w���y�Ц�m
SetConsoleCursorPosition( hConsole, coord );
}
int object::check()
{ 
   int i,j;
   int set=(player+1)%2+1; 
for(i=0;i<map;i++)
{ 
   for(j=0;j<map;j++)
   {
  
  if(array[i][j]==set && array[i+1][j]==set && array[i+2][j]==set && array[i+3][j]==set && array[i+4][j]==set)
  { cout<<"���a"<<set<<"Ĺ�F!!"; return 0;}
     if(array[i][j]==set && array[i][j+1]==set && array[i][j+2]==set && array[i][j+3]==set && array[i][j+4]==set)
  { cout<<"���a"<<set<<"Ĺ�F!!";  return 0;}
     if(array[i][j]==set && array[i+1][j+1]==set && array[i+2][j+2]==set && array[i+3][j+3]==set && array[i+4][j+4]==set )
  { cout<<"���a"<<set<<"Ĺ�F!!"; return 0;}
     if(array[i][j]==set && array[i+1][j-1]==set && array[i+2][j-2]==set && array[i+3][j-3]==set && array[i+4][j-4]==set )
  { cout<<"���a"<<set<<"Ĺ�F!!"; return 0;}
  
}
}
return 1;
}
int main()
{
int x=0,y=0;
object s1;
// s1.test(); //���M�L�k�� s1.map���覡���ܨ�ȡA�]���L�Oprivate�ݩʡA���o�i�Q�Υ~�b��Ƨ��ܥL�A���G��l�Ƥ@����A
//�N���|���A�A��l�ܤ@��

s1.print();

do
{

s1.gotoxy(x,y);
s1.process(&x,&y);
}while(s1.check());

system("pause");
return (0);
}