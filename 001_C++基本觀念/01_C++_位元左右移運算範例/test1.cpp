#include <iostream>
using namespace std; 
int main()
 {     
	int num = 1;     
	cout << "2��0���G" << num << endl;     
	num = num << 1;     
	cout << "2��1���G" << num << endl;     
	num = num << 1;     
	cout << "2��2���G" << num << endl;     
	num = num << 1;     
	cout << "2��3���G" << num << endl;
	num = num >> 1;     
	cout << "2��2���G" << num << endl; 
	num = num >> 1; 
	cout << "2��1���G" << num << endl;     
	num = num >> 1;
	cout << "2��0���G" << num << endl; 
	return 0;
}
