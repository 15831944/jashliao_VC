// ====================================
#include <iostream>
using namespace std;

#define ROW                2
#define COL                4

// ==================================== 
// main function
int main(int argc, char**argv)
{        
        int i=0, j=0;
        int **ptr2 = NULL;

        // �ͦ��@�����а}�C
        ptr2 = new int*[ROW];

        // �C�ӫ��а}�C�A�ͦ���ư}�C
        for(i=0; i<ROW; i++) ptr2[i] = new int[COL];

        // write
        int cnt = 0;
        for(i=0; i<ROW; i++) {
                for(j=0; j<COL; j++) ptr2[i][j] = cnt++;
        }

        // read value and address
        for(i=0; i<ROW; i++) {
                for(j=0; j<COL; j++) {
                        cout << "ptr2[" << i << "][" << j<< "]=" << ptr2[i][j];
                        cout << "(" << hex << &ptr2[i][j] << ")" << endl;
                }
        }

        // ������а}�C
         for(i=0; i<ROW; i++) delete ptr2[i];

        // �������
        delete ptr2;

        // �ƹ�W, �W�����G��� delete [] ptr2; �N��F

        return 0;
}