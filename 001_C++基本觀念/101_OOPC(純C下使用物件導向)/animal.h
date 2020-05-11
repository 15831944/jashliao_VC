#ifndef ANIMAL_H_INCLUDED_
#define ANIMAL_H_INCLUDED_

#include "lw_oopc.h"

INTERFACE(IMoveable)
{
    void (*move)(IMoveable* t);     // Move�欰
};

ABS_CLASS(Animal)
{
    char name[128];     // �ʪ������(���]�p��128�Ӧr��)
    int age;            // �ʪ����~��

    void (*setName)(Animal* t, const char* name);   // �]�m�ʪ������
    void (*setAge)(Animal* t, int age);             // �]�m�ʪ����~�� 
    void (*sayHello)(Animal* t);                    // �ʪ����۩I
    void (*eat)(Animal* t);                         // �ʪ����|�Y�]��H��k�A�Ѥl����{�^
    void (*breathe)(Animal* t);                     // �ʪ����|�I�l�]��H��k�A�Ѥl����{�^
    void (*init)(Animal* t, const char* name, int age); // ��l����٩M�~��
};

CLASS(Fish)
{
    EXTENDS(Animal);        // �~��Animal��H��
    IMPLEMENTS(IMoveable);  // ��{IMoveable���f

    void (*init)(Fish* t, const char* name, int age);
};

CLASS(Dog)
{
    EXTENDS(Animal);        // �~��Animal��H��
    IMPLEMENTS(IMoveable);  // ��{IMoveable���f


    void(*init)(Dog* t, const char* name, int age);
};

CLASS(Car)
{
    IMPLEMENTS(IMoveable);  // ��{IMoveable���f�]���l���O�ʪ��A���i�HMove�^
};

#endif