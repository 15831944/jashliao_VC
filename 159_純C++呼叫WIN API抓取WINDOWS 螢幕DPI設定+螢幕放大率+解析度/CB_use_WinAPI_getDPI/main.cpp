#include <iostream>
#include <cstdio>
//--
//Step_01
#define _WIN32_WINNT 0x0500//GetDC
#include <windows.h>
//--

using namespace std;

//--
/*
WINAPI GetDeviceCaps(����Ҧ���ܾ��]�w��)��nIndex�ѼƦC�� [GOOGLE �d GetDeviceCaps C#]


��ƨӷ�:http://www.cnblogs.com/gltan123/p/4494630.html

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

GetDeviceCaps�]HORZSIZE�^
HORZSIZE �H�@�̬���쪺��ܼe��
VERTSIZE �H�@�̬���쪺��ܰ���
HORZRES �H�Ϥ�����쪺��ܼe�� 0~65535
VERTRES �H�Ϥ�����쪺��ܰ��� 0~65535
LOGPIXELSX �Ϥ�/�޿�^�o�]���ǡ^
LOGPIXELSY �Ϥ�/�޿�^�o�]�����^
*/
//Step_02
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
int main()
{
    Point result=GetSystemDpi();
    cout <<"dpi="<< result.X <<"*"<< result.Y<<"*"<< result.Z<< endl;
    Pause();
    return 0;
}
