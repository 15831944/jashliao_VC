// �ϥΤp���󤽥q���n��
// 1. empolyee.obj
// 2. manager.obj
// 3. program.obj

#include "..\DynamicCastDemo\program.h"
#include <iostream>
using namespace std;

// �]���ڭ̨S�� program ���O��source code
// ���O�ڭ̫o�i�H�s�W�[�@�� method bonus()
void programmer::bonus(){
	cout << "Programer �s�W��method" << endl;
}
void main(){
	programmer obj;

	obj.bonus();

	empolyee *p=&obj;
	p->salary();
}