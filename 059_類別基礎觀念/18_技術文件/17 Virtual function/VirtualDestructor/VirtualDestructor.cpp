
/* ���@�� ���Ѻc���|�Q�I�s ? (Person or Sortable)*/

#include "stdafx.h"

class Sortable
{
public:
	int data;

	Sortable()		//�غc�l
	{
		data=123;
	}
	 ~Sortable()   // virtual   Sortable�Ѻc�l
	{
		data=0;
	}
};
class Person:public Sortable
{
public:
		int id;
	   Person():Sortable()
	   {
		   id=567;
	   }
	   ~Person()
	   {
		data=1;              // Person ���Ѻc�l
	   }
};
int main(int argc, char* argv[])
{
	
	Sortable *b;
	Person *p=new Person;	
	b=p;
	delete b;// ���@�� ���Ѻc���|�Q�I�s ?
	return 0;
}

