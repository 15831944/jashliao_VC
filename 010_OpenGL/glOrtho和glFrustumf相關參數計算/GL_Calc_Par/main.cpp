#include <iostream>
#include <cmath>
using namespace std;
////////////////////////////////////
double ToRadians (double d);//����|��
double ToDegrees (double r);//�|�����
float g_fltWidth=640;//�ù��e��
float g_fltHight=480;//�ù�����
float g_fltAspectRatio;//�e����
float g_fltFieldOfView = 45.0; //��������
float g_fltNear = 0.1; //���
float g_fltFar = 1000; //����
float g_fltSize;//glFrustumf��ưѼ�
float g_fltOrthoRange = 420.0f;//�Ŷ��j�p
///////////////////////////////////
double ToRadians (double d)//����|��
{
    return d * M_PI / 180;
}
double ToDegrees (double r)//�|�����
{
    return r * 180/ M_PI;
}

int main()
{
    //////////////////////////////
    if(g_fltWidth>g_fltHight)
    {
        g_fltAspectRatio=g_fltWidth/g_fltHight;
    }
    else
    {
        g_fltAspectRatio=g_fltHight/g_fltWidth;
    }
    ///////////////////////////////
    g_fltSize=g_fltNear * tanf(ToRadians(g_fltFieldOfView ) / 2.0);
    cout <<"Width="<<g_fltWidth<< endl;
    cout<<"Hight="<<g_fltHight<< endl;
    cout<<"Aspect Ratio="<<g_fltAspectRatio<< endl;
    cout<<"Field Of View="<<g_fltFieldOfView<<" Degrees"<<endl;
    cout<<"glFrustumf Near="<<g_fltNear<< endl;
    cout<<"glFrustumf Far="<<g_fltFar<< endl;
    cout<<"glFrustumf Left="<<-1*g_fltSize<< endl;
    cout<<"glFrustumf Right="<<g_fltSize<< endl;
    cout<<"glFrustumf Bottom="<<-1*g_fltSize/g_fltAspectRatio<< endl;
    cout<<"glFrustumf Top="<<g_fltSize/g_fltAspectRatio<< endl;
    //glFrustumf(-g_fltSize, g_fltSize, -g_fltSize/g_fltAspectRatio, g_fltSize/g_fltAspectRatio, g_fltNear, g_fltFar);
    cout<<"glOrtho Range"<<g_fltOrthoRange<< endl;
    cout<<"glOrtho Near="<<-1*g_fltOrthoRange*2<< endl;
    cout<<"glOrtho Far="<<g_fltOrthoRange*2<< endl;
    cout<<"glOrtho Left="<<-1*g_fltOrthoRange<< endl;
    cout<<"glOrtho Right="<<g_fltOrthoRange<< endl;
    cout<<"glOrtho Bottom="<<-1*g_fltOrthoRange*g_fltAspectRatio<< endl;
    cout<<"glOrtho Top="<<g_fltOrthoRange*g_fltAspectRatio<< endl;
    //void glOrtho(left,right,bottom,top,nearVal,farVal);
    /*
    if (w <= h)
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2, nRange*2);
    else
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2, nRange*2);
    */
    cout << "Hello world!" << endl;
    return 0;
}
