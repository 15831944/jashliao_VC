// ErrorInitialValue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/*
	�ŧi�@�Ӥ��X�k���w�]��
*/
template <class Type=int,int size>
	class Buffer;
/*
	class Buffer���w�q
*/
template <class Type,int size>
	class Buffer
	{	
	public:
		Type kk;
		int _size;
		Buffer()
		{
			unsigned char BB[800*600*3];
			kk=5;
			_size=size;
		}

	};


int main(int argc, char* argv[])
{
	Buffer<int> buf;
	//Buffer<> buf2;
	//Buffer<123> buf4;   // <<------ ���~

	Buffer<int> *buf3=new Buffer<int>();
	printf("Hello World!\n");
	return 0;
}