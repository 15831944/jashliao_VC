#include <iostream>
using namespace std;
void main()
{
	float fltKG,fltCM,yourbmi;
	cout<<"�p��BMI�п�J�魫(kg)"<<"\t";
	cin>>fltKG;
	cout<<"�p��BMI�п�J����(cm)"<<"\t";
	cin>>fltCM;
	yourbmi=fltKG/((fltCM/100)*(fltCM/100));
	if(yourbmi >50)//->"�D�즺"
	{
		cout<<"�D�즺";
	}
	else if(yourbmi >=30) //->"���תέD"
	{
		cout<<"���תέD";
	}
	else if(yourbmi >24.99 && yourbmi <=29.9) //->"���תέD"
	{
		cout<<"���תέD";
	}
	else if(yourbmi >=18.5 && yourbmi <=22.9) //->"���`"
	{
		cout<<"���`";
	}
	else if(yourbmi >=17.0 && yourbmi <18.5) //->"���׮��G"
	{
		cout<<"���׮��G";
	}
	else if(yourbmi >=16 && yourbmi <16.9) //->"���׮��G"
	{
		cout<<"���׮��G";
	}
	else if(yourbmi <16) //->"���׮��G"
	{
		cout<<"���׮��G";
	}
	else if(yourbmi <5) //->"�ФƦ��P"
	{
		cout<<"�ФƦ��P";
	}
}