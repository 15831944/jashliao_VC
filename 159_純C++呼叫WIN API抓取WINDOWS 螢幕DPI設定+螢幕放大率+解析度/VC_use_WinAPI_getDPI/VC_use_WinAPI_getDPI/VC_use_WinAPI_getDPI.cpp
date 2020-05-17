// VC_use_WinAPI_getDPI.cpp : ���x����̨���ó�ʽ���M���c��
//

#include "stdafx.h"
#include <windows.h>

//--
/*
WINAPI GetDeviceCaps(ץȡ�����@ʾ���O��ֵ)��nIndex�����б� [GOOGLE �� GetDeviceCaps C#]


�Y�ρ�Դ:http://www.cnblogs.com/gltan123/p/4494630.html

const int DRIVERVERSION = 0;
const int TECHNOLOGY = 2;
const int HORZSIZE = 4;
const int VERTSIZE = 6;
const int HORZRES = 8;
const int VERTRES = 10;
const int BITSPIXEL = 12;
const int PLANES = 14;
const int NUMBRUSHES = 16;
const int NUMPENS = 18;
const int NUMMARKERS = 20;
const int NUMFONTS = 22;
const int NUMCOLORS = 24;
const int PDEVICESIZE = 26;
const int CURVECAPS = 28;
const int LINECAPS = 30;
const int POLYGONALCAPS = 32;
const int TEXTCAPS = 34;
const int CLIPCAPS = 36;
const int RASTERCAPS = 38;
const int ASPECTX = 40;
const int ASPECTY = 42;
const int ASPECTXY = 44;
const int SHADEBLENDCAPS = 45;
const int LOGPIXELSX = 88;
const int LOGPIXELSY = 90;
const int SIZEPALETTE = 104;
const int NUMRESERVED = 106;
const int COLORRES = 108;
const int PHYSICALWIDTH = 110;
const int PHYSICALHEIGHT = 111;
const int PHYSICALOFFSETX = 112;
const int PHYSICALOFFSETY = 113;
const int SCALINGFACTORX = 114;
const int SCALINGFACTORY = 115;
const int VREFRESH = 116;
const int DESKTOPVERTRES = 117;
const int DESKTOPHORZRES = 118;
const int BLTALIGNMENT = 119;
}
 
GetDeviceCaps��HORZSIZE��
HORZSIZE �Ժ��מ��λ���@ʾ����
VERTSIZE �Ժ��מ��λ���@ʾ�߶�
HORZRES �ԈDԪ���λ���@ʾ���� 0~65535
VERTRES �ԈDԪ���λ���@ʾ�߶� 0~65535
LOGPIXELSX �DԪ/߉݋Ӣ�磨ˮ�ʣ�
LOGPIXELSY �DԪ/߉݋Ӣ�磨��ֱ��
*/
class Point
{
    public:
        float X;
        float Y;
        float Z;
        Point();
};
Point::Point()
{
    X=0;
    Y=0;
    Z=0;
}
//--
static Point GetSystemDpi()
{
    Point result;
    HWND myconsole=GetConsoleWindow();
    HDC mydc = GetDC(myconsole);

    result.X = GetDeviceCaps(mydc, 88);//-lgdi32
    result.Y = GetDeviceCaps(mydc, 90);//-lgdi32
    int LogicalScreenHeight = GetDeviceCaps(mydc, 10);
    int PhysicalScreenHeight = GetDeviceCaps(mydc, 117);
    float ScreenScalingFactor = (float)PhysicalScreenHeight / (float)LogicalScreenHeight;
    result.Z = ScreenScalingFactor; // 1.25 = 125%
    ReleaseDC(myconsole,mydc);

    return result;
}
//--
void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int _tmain(int argc, _TCHAR* argv[])
{
	Point result=GetSystemDpi();
	printf("dpi=%f*%f*%f\n",result.X,result.Y,result.Z);
	Pause();
	return 0;
}

