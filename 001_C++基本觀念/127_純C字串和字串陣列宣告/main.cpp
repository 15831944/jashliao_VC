#include <iostream>
#include <stdio.h>>

using namespace std;

int main()
{
    char string1[]={'W','e','l','c','o','m','e'};
    char string2[]="Welcome";//�t�η|�۰ʥ[�W\0
    char StringArray[][6] ={"human","dog","cat","bird"};//C�y���r��}�C�A�r����פ@�w�n�w�q(PS �o�]�O�G���}�C�b��ƶǻ��ɬ���n���w���S��)
    int a,b,c;
    a=sizeof(string1);
    b=sizeof(string2);
    c=sizeof(StringArray)/6;//�p��r��}�C�Ӽ�
    printf("%s,%d\n",string1,a);
    printf("%s,%d\n",string2,b);
    printf("%d\n",c);
    for(int i=0;i<c;i++)//�̧ǦL�X�r��}�C
    {
        printf("%s\n",StringArray[i]);
    }

    return 0;
}
