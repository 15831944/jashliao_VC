// MultiTypeDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template <class Type1, class Type2> 
class Matrix {
private:
      int Row,Col;
      Type1 **Buffer;                    // �Ĥ@�ظ�ƹ���
      Type2 **Buffer2;				     // �ĤG�ظ�ƹ���
public:
       Matrix(int Row,int Col);
};
template <class Type1,class Type2> 
Matrix<Type1,Type2>::Matrix(int Row,int Col)      // <<<---- �`�N: �n�D�sĶ������(Type1,Type2)�����غc�l
{
    int y;
	// �t�m�Ĥ@��ƹ���    
		Buffer=new Type1*[Row];
        for(y=0;y<Row;y++)
                Buffer[y]=new Type1[Col];
	// �t�m�ĤG��ƹ��� 
		Buffer2=new Type2*[Row];
        for(y=0;y<Row;y++)
                Buffer2[y]=new Type2[Col];
}

int main(int argc, char* argv[])
{
	Matrix<int,char> MyMatrix(2,3);
	return 0;
}

