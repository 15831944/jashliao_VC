// VirtualFunDemo1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/*
	[ base ]
	   |
	[ derived ]

     base �O�_�i�H�I�sderived class ��function
*/
class CommPlatForm 
{
public:
	int BaseData;
	CommPlatForm()
	{
		BaseData=0;
	}
	void Algorithm(int data)
	{
		SetData(data);	// <-------------base �O�_�i�H�I�sderived class ��function
	}
	/*
	    ����: Base ����function �u��I�s�ۤv���w�q��function.
		      �Y�n�I�sDerived function,�u��avirtual function
	*/
	virtual void SetData(int data)
	{
		BaseData=data;
	}
	
};
class WindowsPlatForm:public CommPlatForm
{

public:
	int DerivedData;
	WindowsPlatForm():CommPlatForm()
	{
		DerivedData=0;
	}
	void SetData(int data)                //WindowsPlatForm ���x��SetData
	{
		DerivedData=data;
	}
};

int main(int argc, char* argv[])
{
	WindowsPlatForm MyWinAp;

	CommPlatForm *p=&MyWinAp;             // �Q�Φ@�Υ��x����
	p->Algorithm(1234);

    // MyWinAp.Algorithm(1234); 
    return 0;
}

