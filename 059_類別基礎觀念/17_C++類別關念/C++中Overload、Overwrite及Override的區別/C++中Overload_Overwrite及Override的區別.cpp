/*
C++��Overload�BOverwrite��Override���ϧO
Overload(����)�G�bC++�{�����A�i�H�N�y�q�B�\��ۦ����X�Ө�ƥΦP�@�ӦW�r��ܡA���ѼƩΪ�^�Ȥ��P�]�]�A�����B���Ǥ��P�^�A�Y��ƭ����C
�]1�^�ۦP���d��]�b�P�@�������^�F
�]2�^��ƦW�r�ۦP�F
�]3�^�ѼƤ��P�F
�]4�^virtual ����r�i���i�L�C
PS.�����\��P�ɦs�b�A�̷ӶǤJ�ѼƤ��P�ӰϤ��ujash.liao ���� 2015/02/07 �v

Override(�л\)�G�O������������л\������ơA�S�x�O�G
�]1�^���P���d��]���O��󬣥����P�����^�F
�]2�^��ƦW�r�ۦP�F
�]3�^�ѼƬۦP�F
�]4�^������ƥ�����virtual ����r�C
ps.��l����j���ഫ���������ɡA�|�I�s�l���O�\��A�]���w�g�Q�л\

Overwrite(���g)�G�O������������ƾB�n�F�P��P�W��������ơA�W�h�p�U�G
�]1�^�p�G����������ƻP��������ƦP�W�A���O�ѼƤ��P�C���ɡA���צ��Lvirtual����r�A��������ƱN�Q���á]�`�N�O�P�����V�c�^�C
�]2�^�p�G����������ƻP��������ƦP�W�A�åB�ѼƤ]�ۦP�A���O������ƨS��virtual����r�C���ɡA��������ƳQ���á]�`�N�O�P�л\�V�c�^�C
ps.��l����j���ഫ���������ɡA�|�I�s�����O�\��A�]���u�O�Q�B�n
*/
#include <cstdio>  
#include <iostream>

using namespace std;  

class Parent  
{  
public:  
    void F()  
    {  
        printf("Parent.F()\n");  
    }  
    virtual void G()  
    {  
        printf("Parent.G()\n");  
    }
	//����(overload)Add���
    int Add(int x, int y)  
    {  
        return x + y;  
    }  
    float Add(float x, float y)  
    {  
        return x + y;  
    }  
};  
  
class ChildOne: public Parent  
{  
 public:   
    void F()  
    {  
        printf("ChildOne.F()\n");   
    }  
    
    void G()  
    {  
        printf("ChildOne.G()\n");  
    }  
};  
  
  
int main()  
{  
    ChildOne childOne;// = new ChildOne();
    childOne.F();//�����I�s�l���O
    childOne.G();//�����I�s�l���O
    childOne.Parent::F();//�����I�s�����O
    childOne.Parent::G();//�����I�s�����O
    Parent* p = (Parent*)&childOne;  
    p->F();//�l���ഫ�������A��F()�OOverwrite(���g)�A�ҥH�|�I�s������O�\��  
    p->G();//�l���ഫ�������A��G()�OOverride(�л\)�A�ҥH�|�I�s��l���O�\��  
    Parent* p2 = new Parent(); 
    p2->F();//�����O�\��
    p2->G();//�����O�\��
    printf("%d\n",p2->Add(1, 2)); //����(overload)Add��� 
    printf("%f\n",p2->Add(3.4f, 4.5f));//����(overload)Add���  
    delete p2;  
      
    return 0;  
}  