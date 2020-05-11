#include <stdio.h>
#include <string.h>
#include "animal.h"

/* �]�m�ʪ������ */
void Animal_setName(Animal* t, const char* name)
{
    // �o�̰��wname�p��128�Ӧr�šA��²�ƥܨҥN�X�A�����O�@�]���~�N�X�����n�o�˼g�^
    strcpy(t->name, name);
}
/* �]�m�ʪ����~�� */
void Animal_setAge(Animal* t, int age)
{
    t->age = age;
}
/* �ʪ��M�ڭ̥��۩I */
void Animal_sayHello(Animal* t)
{
    printf("Hello! �ڬO%s�A���~%d���F�I\n", t->name, t->age);
}
/* ��l�ưʪ�����٩M�~�� */
void Animal_init(Animal* t, const char* name, int age)
{
    t->setName(t, name);
    t->setAge(t, age);
}

ABS_CTOR(Animal)
FUNCTION_SETTING(setName, Animal_setName);
FUNCTION_SETTING(setAge, Animal_setAge);
FUNCTION_SETTING(sayHello, Animal_sayHello);
FUNCTION_SETTING(init, Animal_init);
END_ABS_CTOR

/* �����Y�欰 */
void Fish_eat(Animal* t)
{
    printf("���Y����I\n");
}
/* �����I�l�欰 */
void Fish_breathe(Animal* t)
{
    printf("�����ΩI�l�I\n");
}
/* �������ʦ欰 */
void Fish_move(IMoveable* t)
{
    printf("���b���̴�I\n");
}
/* ��l�Ƴ�����٩M�~�� */
void Fish_init(Fish* t, const char* name, int age)
{
    Animal* animal = SUPER_PTR(t, Animal);
    animal->setName(animal, name);
    animal->setAge(animal, age);
}

CTOR(Fish)
SUPER_CTOR(Animal);
FUNCTION_SETTING(Animal.eat, Fish_eat);
FUNCTION_SETTING(Animal.breathe, Fish_breathe);
FUNCTION_SETTING(IMoveable.move, Fish_move);
FUNCTION_SETTING(init, Fish_init);
END_CTOR

/* �����Y�欰 */
void Dog_eat(Animal* t)
{
    printf("���Y���Y�I\n");
}
/* �����I�l�欰 */
void Dog_breathe(Animal* t)
{
    printf("���ΪͩI�l�I\n");
}
/* �������ʦ欰 */
void Dog_move(IMoveable* t)
{
    printf("���b�a�W�]�I\n");
}
/* ��l�ƪ�����٩M�~�� */
void Dog_init(Dog* t, const char* name, int age)
{
    Animal* animal = SUPER_PTR(t, Animal);
    animal->setName(animal, name);
    animal->setAge(animal, age);
}

CTOR(Dog)
SUPER_CTOR(Animal);
FUNCTION_SETTING(Animal.eat, Dog_eat);
FUNCTION_SETTING(Animal.breathe, Dog_breathe);
FUNCTION_SETTING(IMoveable.move, Dog_move);
FUNCTION_SETTING(init, Dog_init);
END_CTOR

void Car_move(IMoveable* t)
{
    printf("�T���b�}�ʡI\n");
}

CTOR(Car)
FUNCTION_SETTING(IMoveable.move, Car_move);
END_CTOR
