#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int **intdata;//��}
    int M;//��}�j�p 
    int i,j;//�j��X��
    int intarry1;//�@���}�C���� 
    int *intadd_del;//���W�βĴ�}�C
    int *intvalue;//�C�@���n�g���U��
    int intinsert;
    bool blnx_y_move=false;//Y=false;X=true
    cout<<"��J��}�j�p"<<"\t";
    cin>>M;
    ////////////////////////
    intdata=new int*[M];
    for(i=0;i<M;i++)
    {
       intdata[i]=new int[M];
    }
    for(i=0;i<M;i++)
    { 
       for(j=0;j<M;j++)
       {
          *(*(intdata+i)+j)=0;
          cout<<*(*(intdata+i)+j)<<"\t";
       }
       cout<<"\n";
    }
    /////////////////////////
    intarry1=(M-1)*2+1;
    intadd_del=new int[intarry1];
    j=0;
    for(i=0;i<intarry1;i++)
    {
       j++;
       if(j==1||j==2)
          intadd_del[i]=1;
       if(j==3||j==4)
          intadd_del[i]=-1;
       if(j==4)
          j=0;
       cout<<intadd_del[i]<<"\t";         
    }
    cout<<"\n";
    //////////////////////////
    intvalue=new int[intarry1];
    intvalue[0]=M;
    cout<<intvalue[0]<<"\t";
    intinsert=M-1;
    for(i=1;i<intarry1;i++)
    {
       intvalue[i]=intinsert;
       if(i%2==0)
          intinsert--;
       cout<<intvalue[i]<<"\t";   
    }
    cout<<"\n";
    ///////////////////////////
    int x,y,z;
    x=0;
    y=-1;//���I 
    z=0;
    int data=0;
    intarry1=(M-1)*2+1;
    cout<<intarry1<<"\n";
    for(i=0;i<intarry1;i++)
    {
       intinsert=intvalue[i];//�C�@�Ӥp�j�骺���� 
       z=intadd_del[i];
       for(j=0;j<intinsert;j++)
       {
          data++;
          if(blnx_y_move==false)//Y=false
          {
             y+=z;
          }
          else//X=true
          {
             x+=z;
          }
          *(*(intdata+x)+y)=data;
       }
       blnx_y_move=!blnx_y_move;
    }
    //////////////////////////////////// 
    for(i=0;i<M;i++)
    { 
       for(j=0;j<M;j++)
       {
          cout<<*(*(intdata+i)+j)<<"\t";
       }
       cout<<"\n";
    } 
    system("PAUSE");
    return EXIT_SUCCESS;
}
