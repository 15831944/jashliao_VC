// Rethrow���d��
// Rethrow.cpp
#include <iostream.h>
class EXCEPT{
 public:
     int data;
     EXCEPT()
     {
         data=134;
     }
     set(int arg)
     {         data=arg;   }
};

EXCEPT myerrobj;    // �ثemyerrobj=134;
void fun2();
void fun3();
void fun1()
{
   fun2();

}
void fun2()
{
    try{
        fun3();
    }
    catch(EXCEPT &errObj)
    {
        cout<< "fun2�B�z�L";
        throw errObj;            //fun2�B�z�L��,�b�ѫ᭱�{���~��B�z
    }

}
void fun3()
{
    throw myerrobj;
}
int main(int argc, char* argv[])
{

        try{
            fun1();
        }
        catch(EXCEPT &errObj)
        {   errObj.set(1234);    //�ثe�ק�errObj=1234;
            int x;               // �O�_��� myerrobj ?
            x++;                 // No! �u��F errObj.
                                 // �]�� throw �ƻs�Fmyerrobj -> errObj
        }

        return 0;
}
