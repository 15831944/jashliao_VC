#include <iostream>
using namespace std;
float oc(float i)     //�����ؤ���
{
	i = i * 9 / 5 + 32;
	return i;
}
float fc(float i)     //�ؤ��������
{
	i = (i - 32) * 5 / 9;
	return i;
}
void main()
{
	float fltInput,fltOutput;
	cout<<"��J�ഫ�Ʀr"<<"\t";
	cin>>fltInput;
	fltOutput=oc(fltInput);
	cout<<"�����ؤ� "<<fltOutput<<"\n";
	fltOutput=fc(fltInput);
	cout<<"�ؤ������ "<<fltOutput<<"\n";

}