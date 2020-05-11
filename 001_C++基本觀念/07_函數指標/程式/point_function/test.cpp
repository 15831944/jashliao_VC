#include <iostream>
using namespace std;
void procreation(int,void (*run)(char*,int)); /* �H��ƫ��Ь��Ѽ� */
void slow_run_shoes(char*,int);
void leisure_shoes(char*,int);
void spiked_shoes(char*,int);
int main()
{
	int procreation_number;/* �Ͳ����إN��1~3 */
	int size;/* �ؤo */
	procreation_number=2;
	size=8;
	switch(procreation_number)
	{
		case 1:
			procreation(size,slow_run_shoes); /* �ѼƦC���ǤJ���slow_run_shoes����} */
			break;
		case 2:
			procreation(size,leisure_shoes); /* �ѼƦC���ǤJ���leisure_shoes����} */
			break;
		case 3:
			procreation(size,spiked_shoes); /* �ѼƦC���ǤJ���spiked_shoes����} */
			break;
		default:
			cout <<"����Ͳ�!!!" <<endl;
	}
	getchar();
	return 0;
}
void procreation(int size,void (*run)(char* material,int size))
{
	char* material; /* ��ƦW�� */
	int material_number; /* ��ƥN��1~3 */
	material_number=3;
	switch(material_number)
	{
		case 1:
			material="��";
			break;
		case 2:
			material="�~��";
			break;
		case 3:
			material="�콦";
	}
	(*run)(material,size); /* �I�s��ƫ��� */
}
void slow_run_shoes(char* material,int size)
{
	cout <<"�H��Ƭ�" <<material <<"�B�ؤo��" <<size <<"�ӥͲ��C�]�c" <<endl;
}
void leisure_shoes(char* material,int size)
{
	cout <<"�H��Ƭ�" <<material <<"�B�ؤo��" <<size <<"�ӥͲ��𶢾c" <<endl;
}
void spiked_shoes(char* material,int size)
{
	cout <<"�H��Ƭ�" <<material <<"�B�ؤo��" <<size <<"�ӥͲ��v�c" <<endl;
}
