#include <iostream>

using namespace std;
/*
class static variable�\�ΡG�P���O�������Ʀ@��
class static variable ��l�]�w�y�k
class member function ���� static variable����
*/
//////////////////////////////////////
class static_variable
{
    public:
        //static int count;
        int number;
        static_variable();
        void showData();
    private:
        static int pricount;
};
static_variable::static_variable()
{
    //count++;
    number=0;
    number++;
    pricount++;
}
void static_variable::showData()
{
    cout << "pricount:\t" << pricount << endl;
    cout << "number:\t" << number << endl;

    static int count_d=0;
    count_d--;
    cout << "count_d:\t" << count_d << endl;
}
//int static_variable::count=0;
int static_variable::pricount=0;
///////////////////////////////////////////
int main()
{

    static_variable a,b;
    a.showData();
    b.showData();
    static_variable c;
    c.showData();

    cout<<"press enter key to continue:"<<endl;
    cin.get();

    return 0;
}
