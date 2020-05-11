// OOP_C.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct fooobj 
{
	//�����ܼ�
	int privateint;
	char *privateString;
};

typedef struct fooobj * FooOBJ;//�O�W
FooOBJ newFooOBJ();//�إߪ���
void deleteFooOBJ(FooOBJ);//�R��Foo����
void setFooNumber(FooOBJ,int);//�]�w�����ܼƪ��������
void setFooString(FooOBJ,char *);//�]�w�����ܼƪ��������
void dumpFooState(FooOBJ);//��sFoo����

void diddle(FooOBJ obj)
{
	setFooNumber(obj, 1);
	setFooString(obj, "somestring");
}

int main()
{
	FooOBJ fobj;
	fobj=newFooOBJ(); /* create a new object of type "FooOBJ" */

	dumpFooState(fobj);
	puts("Tweaking object");
	diddle(fobj);

	dumpFooState(fobj);
	deleteFooOBJ(fobj);

	return 0;
}
/* Any "class static" vars simply get declared as
static int staticvar;
 * or whatever you like here.
 * Whereas instance variables go in the struct above.
 */

FooOBJ newFooOBJ()
{
	FooOBJ foo=(FooOBJ)malloc(sizeof(struct fooobj));
	memset(foo, 0, sizeof(struct fooobj));//bzero(foo, sizeof(struct fooobj));
	return foo;
}

void setFooNumber(FooOBJ foo,int num)
{
	if(foo==NULL) return;  /* you may chose to debugprint something
				*instead
				*/
	foo->privateint=num;
}

void setFooString(FooOBJ foo,char *string)
{
	/* If you malloced the string, you'll want to free() it here!!*/
	if(foo==NULL) return;
	foo->privateString=string;
}
	

void dumpFooState(FooOBJ foo)
{
	if(foo==NULL)
		return;
	printf("value of private int==%d\n", foo->privateint);
    printf("value of private string==");
    if(foo->privateString == NULL)
	{
		puts("(NULL)");
	}
	else
	{
		printf("%s\n", foo->privateString);
	}

}

void deleteFooOBJ(FooOBJ foo)
{
	/* dont forget to free privateString if you malloced it here!!*/
	free(foo);
}
